#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"

//////////////////////////////////////////////////////////////////////////
// Line scan trigger cycle.
//
// Shape follows AllHomeM / AllHomeC: ScanTriggerM() arms the cycle by setting
// bit.ScanTriggerRun, ScanTriggerC() runs from CommonCycle() while that bit is
// set and clears it when the scan finishes.
//
// The trigger itself is not generated here. SIO-HPC4 compares the encoder
// position in hardware and emits one pulse every dPitch of travel, so the scan
// stays correct however irregularly this loop happens to run.
//////////////////////////////////////////////////////////////////////////

// Distance one encoder count represents, in mm. Machine constant: it is the
// counter channel's unit, set through AxcMotSetMoveUnitPerPulse, and is what
// makes dPitch land on a whole number of counts.
//
// 1 um, confirmed against the linear encoder on this machine and against
// EzManager's CounterAgent, which shows Count Unit/Pulse 0.001 for channel 0.
// It was 0.0001 here, which claimed ten times the resolution the counter
// actually has: every block position and every pitch would have been written
// to the board ten times too small.
//
// Consequence for the recipe: the comparator can only place a trigger on a
// whole micrometre. A pixel resolution of 18.1 um is not reachable - the
// nearest pitches are 18 um and 19 um - and ScanTriggerValidate() below
// refuses it with SCANTRIGGER_VALIDATE_PITCH_FRACTION rather than letting the
// board round it silently.
static const double SCANTRIGGER_DEFAULT_ENC_UNIT_MM = 0.001;   // 1 um

// Reverse the counter input, so the counter agrees with the machine.
//
// Measured: the stage was commanded from 100 mm to 600 mm and the counter ran
// from +100000 to -399998. The magnitude is right to four decimal places -
// 500.0040 mm against 500.0000 commanded - so the scale, the wiring and the
// 1 um resolution are all correct and only the sign is inverted: the linear
// scale's A and B are swapped with respect to the motor's positive direction.
//
// With the counter running down, a block armed for the up direction rejects
// every position and the comparator never fires. Reversing it here makes the
// counter count up over the same move, which is also what every position in
// the recipe already assumes.
static const bool   SCANTRIGGER_DEFAULT_ENC_REVERSE = true;

// How far the counter may run the wrong way before the scan is called off,
// in counts. Large enough not to trip on a count of dither at the start.
static const double SCANTRIGGER_DEFAULT_WRONG_WAY_COUNTS = 200.0;

// Where the scan geometry lives: four entries in the motor index table, which
// the motor screen edits and the operator names. 50 and above are MOTOR_COMMON
// rows, so they belong to the machine rather than to one device - which is what
// a scan geometry is.
//
//   50  SCAN START          approach begins here, and where the stage is parked
//                           again once the scan has finished
//   51  SCAN TRIGGER START  block lower - the axis is already at speed
//   52  SCAN TRIGGER END    block upper
//   53  SCAN END            deceleration ends here
//
// Splitting the move from the block is the point: the old cycle ran from the
// block's own start to its own end, so the ramps happened inside the block and
// the first and last lines were taken while the stage was still changing speed.
static const int    SCANTRIGGER_IDX_MOTION_START = 50;
static const int    SCANTRIGGER_IDX_TRIG_START   = 51;
static const int    SCANTRIGGER_IDX_TRIG_END     = 52;
static const int    SCANTRIGGER_IDX_MOTION_END   = 53;

// Counter channel and trigger output the camera is wired to.
static const long   SCANTRIGGER_DEFAULT_CHANNEL = 0;
static const DWORD  SCANTRIGGER_DEFAULT_OUTPORT = 0x1;
// The channel reads its own encoder input, the output is high active, and the
// comparator counts only in the scan direction.
static const DWORD  SCANTRIGGER_DEFAULT_ENCODER_INPUT   = 0;
static const DWORD  SCANTRIGGER_DEFAULT_TRIGGER_LEVEL   = 1;
static const DWORD  SCANTRIGGER_DEFAULT_DIRECTION_CHECK = 1;

// The board settings the cycle actually uses. They start as the commissioned
// values above, which is what every comment in this file is written about,
// and the engineer screen can change them while the cycle is idle - for a
// replacement scale, a camera moved to another output, or a second machine
// wired differently. Nothing here is saved: SEQ comes up on the defaults and
// the MMI sends its saved settings once it is connected.
static _scantriggerhwcfg ScanTriggerHwDefaults(void)
{
	_scantriggerhwcfg cfg;
	memset(&cfg, 0, sizeof(cfg));
	cfg.nChannel        = (int)SCANTRIGGER_DEFAULT_CHANNEL;
	cfg.uEncoderInput   = SCANTRIGGER_DEFAULT_ENCODER_INPUT;
	cfg.uOutPortMask    = SCANTRIGGER_DEFAULT_OUTPORT;
	cfg.dEncUnitMM      = SCANTRIGGER_DEFAULT_ENC_UNIT_MM;
	cfg.bEncReverse     = SCANTRIGGER_DEFAULT_ENC_REVERSE ? 1 : 0;
	cfg.uTriggerLevel   = SCANTRIGGER_DEFAULT_TRIGGER_LEVEL;
	cfg.uDirectionCheck = SCANTRIGGER_DEFAULT_DIRECTION_CHECK;
	cfg.dWrongWayCounts = SCANTRIGGER_DEFAULT_WRONG_WAY_COUNTS;
	return cfg;
}
static _scantriggerhwcfg g_ScanTriggerHw = ScanTriggerHwDefaults();

static long   ScanTriggerChannel(void)  { return (long)g_ScanTriggerHw.nChannel; }
static double ScanTriggerEncUnitMM(void) { return g_ScanTriggerHw.dEncUnitMM; }
// Bounds on the pulse width the operator enters.
//
// The floor is the board's, measured 2026-09-30: the SIO-HPC4L emits pulses
// down to 1 us. Ajinextek's counter trigger guide gives [10 .. 50,000] us for
// AxcTriggerSetTime, but that is in its SIO-CN2CH section and does not apply
// here - which matters, because at a 64 kHz line rate a 15.625 us period leaves
// no room for a 10 us pulse.
//
// The ceiling is a fraction of the line period. The guide asks for a period of
// at least twice the distance travelled while the pulse is high - 50 % duty -
// and its worked example gets 21 of 50 triggers at 100 % and 50 of 50 at 50 %,
// so above the limit triggers are DROPPED, not merged. 40 % keeps a margin
// inside that.
static const double SCANTRIGGER_PULSE_MIN_US   = 1.0;
static const double SCANTRIGGER_PULSE_MAX_DUTY = 0.4;

// Used only when the recipe carries nothing, which is what a database written
// before the pulse width was an entered value looks like.
static const double SCANTRIGGER_PULSE_DEFAULT_US = 10.0;

// A scan longer than this is a data entry mistake, not a recipe.
static const int    SCANTRIGGER_MAX_LINES = 2000000;

// AxcTriggerSetFreq, from AXC.h: "Unit : Hz, Range : 1Hz ~ 500 kHz". In timer
// mode this is the only quantised quantity in the whole setup, which is the
// point of the mode - see ScanTriggerSolveTimer() below.
static const double SCANTRIGGER_TIMER_FREQ_MIN = 1.0;
static const double SCANTRIGGER_TIMER_FREQ_MAX = 500000.0;

// How long the axis must read stopped before the trigger is armed. Guards
// against arming while the stage is still ringing down.
static const LONGLONG SCANTRIGGER_SETTLE_MS = 200;

// How long the scan move has to get going before it is called a failure. The
// axis reads stopped for the first few passes after the move command, so the
// end of the move cannot be tested until it has been seen moving.
static const LONGLONG SCANTRIGGER_MOVE_START_MS = 1000;

// How often the running scan reports what the counter is doing. The trigger
// itself is hardware, so this is the only window into whether the encoder is
// moving, which way, and whether pulses are actually coming out.
static const LONGLONG SCANTRIGGER_LOG_MS = 200;

// Output self test: a slow square wave driven straight onto the trigger pin,
// for probing CON1 with a scope. Slow enough to see, short enough that nobody
// waits for it. This bypasses the encoder and the comparator completely, so a
// flat line here means the fault is the output stage or the wiring, not any
// trigger setting.
static const int      SCANTRIGGER_TEST_PULSES  = 20;
static const LONGLONG SCANTRIGGER_TEST_HALF_MS = 250;

// ...and then one burst of real trigger pulses, at the width and level a scan
// uses, from the board's own pulse generator. 1 kHz for a quarter of a second.
static const long     SCANTRIGGER_TEST_BURST_PULSES = 250;
static const DWORD    SCANTRIGGER_TEST_BURST_HZ     = 1000;

static int       g_nScanTriggerState = SCANTRIGGER_IDLE;
static CRtTimer  g_tmScanTriggerSettle;
static CRtTimer  g_tmScanTriggerLog;

// Set once the axis has actually been seen moving in SCANTRIGGER_WAIT_END.
static bool      g_bScanTriggerMoving = false;
static CRtTimer  g_tmScanTriggerMoveStart;

// Timer mode only: whether the free running pulse train is currently enabled,
// and where the counter stood when it was switched. In periodic mode the
// hardware opens and closes the window from the block and none of this exists;
// here it is a software decision taken once per cycle pass, so record what it
// actually caught rather than what it was aiming at.
// The rate the board actually took, once ARM has asked it. Zero until then.
//
// It has to live outside ScanTriggerDisplay because ScanTriggerValidate() wipes
// that struct and rebuilds it from the recipe on every MMI poll - so a speed
// corrected at ARM would be overwritten a few milliseconds later, and RUN would
// command the uncorrected one.
//
// It is the ONLY number the panel shows that is not derived from the recipe
// currently loaded, so its lifetime has to be exactly the recipe's. It used to
// be guarded by comparing the rate the recipe asks for against the rate that
// produced it, which is a derived test standing in for the real event: a new
// recipe. ScanTriggerSetRecipe() now clears it outright, so it can only ever
// describe the recipe that is loaded, and the comparison is gone.
static double    g_dScanTriggerTimerHz   = 0.0;

static bool      g_bScanTriggerTimerOn   = false;
static double    g_dScanTriggerTimerOnAt  = 0.0;
static double    g_dScanTriggerTimerOffAt = 0.0;

// Counter position when the block was armed, so the travel the counter saw can
// be compared against the travel that was commanded.
static double    g_dScanTriggerEncArm = 0.0;

// Last trigger count read from the board, or -1 when it has not been read.
// ScanTriggerValidate() rebuilds the display struct from the recipe on every
// MMI poll, so without somewhere to keep this the count would be erased a few
// milliseconds after it was measured and the MMI would never see it.
static int       g_nScanTriggerLastCount = -1;

// Output self test progress.
static CRtTimer  g_tmScanTriggerTest;
static int       g_nScanTriggerTestStep = 0;
static bool      g_bScanTriggerTestHigh = false;

//////////////////////////////////////////////////////////////////////////
// One line of "what is the counter doing right now". Called while the scan
// runs and again at each end of it.
static void ScanTriggerLogCounter(const char* pszWhen)
{
	if (AjinTrigger == NULL) return;

	double dPos   = 0.0;
	long   lCount = 0;
	bool   bOut   = false;

	const bool bPos   = AjinTrigger->GetActPos(ScanTriggerChannel(), &dPos);
	const bool bCount = AjinTrigger->ReadTriggerCount(ScanTriggerChannel(), &lCount);
	const bool bOutOk = AjinTrigger->ReadOutputState(ScanTriggerChannel(), &bOut);

	if (bCount) {
		g_nScanTriggerLastCount = (int)lCount;
		ScanTriggerDisplay.nTriggerCount = (int)lCount;
	}

	// A column the board cannot fill is left out rather than printed as "n/a".
	// Neither of these changes during a scan - the call is there or it is not -
	// so twenty rows of "n/a" say the same thing twenty times, crowd out the
	// encoder counts that do change, and make an absence that was explained
	// once at arming look like a fresh failure on every line.
	char szTail[64];
	szTail[0] = '\0';

	if (bCount) {
		sprintf(szTail + strlen(szTail), "  triggers %ld", lCount);
	}
	if (bOutOk) {
		sprintf(szTail + strlen(szTail), "  out %s", bOut ? "HIGH" : "low");
	}

	printf("[SCANTRIGGER] %-8s enc %.0f counts = %.4f mm%s%s\n",
		   (pszWhen != NULL) ? pszWhen : "",
		   dPos, dPos * ScanTriggerEncUnitMM(), bPos ? "" : " (read failed)",
		   szTail);
}

//////////////////////////////////////////////////////////////////////////
// The AXL return codes that turn up on this path, by name. A bare number in a
// log is something the reader has to go and look up, and the one that matters
// here - 1054 - says the board refused the call rather than that the call went
// wrong, which is a different thing to do about it.
static const char* ScanTriggerAxlError(DWORD dwCode)
{
	switch (dwCode) {
	case AXT_RT_SUCCESS:                return "SUCCESS";
	case AXT_RT_OPEN_ERROR:             return "AXT_RT_OPEN_ERROR, the library is not open";
	case AXT_RT_NOT_OPEN:               return "AXT_RT_NOT_OPEN";
	case AXT_RT_NOT_SUPPORT_VERSION:    return "AXT_RT_NOT_SUPPORT_VERSION, unsupported hardware";
	default:                            break;
	}
	return "see AXT_FUNC_RESULT in AXHS.h";
}

//////////////////////////////////////////////////////////////////////////
// Once, at arming: what the board will not be able to tell us about this scan,
// and why. Said here so the rows that follow can carry only what changes.
static void ScanTriggerLogReadbackLimits(void)
{
	if (AjinTrigger == NULL) return;

	if (!CAjinTrigger::HasTriggerCountApi()) {
		printf("[SCANTRIGGER] trigger count not readable:"
			   " this AXL has no AxcTriggerReadTriggerCount.\n");
		printf("[SCANTRIGGER]  the expected count is reported instead, so only"
			   " a scope separates a scan that emitted nothing from one that emitted"
			   " every line.\n");
	}

	bool  bOut  = false;
	DWORD dwRet = 0;
	if (!AjinTrigger->ReadOutputState(ScanTriggerChannel(), &bOut, &dwRet)) {
		printf("[SCANTRIGGER] trigger output line not readable:"
			   " AxcStatusGetChannel(%ld) returned %lu (%s).\n",
			   ScanTriggerChannel(), (unsigned long)dwRet, ScanTriggerAxlError(dwRet));

		if (dwRet == AXT_RT_NOT_SUPPORT_VERSION) {
			// Measured on this machine. AXC.h does not head this one
			// "API for SIO-CN2CH only", but the SIO-HPC4L refuses it all the
			// same - the same trap AxcMotSetMoveUnitPerPulse set, except that
			// one returned success and did nothing.
			//
			// This is the board, not the library, so a newer AXL will not
			// bring it back - unlike the trigger count above, which is simply
			// missing from this AXL's exports.
			printf("[SCANTRIGGER]  the SIO-HPC4L does not implement it,"
				   " so the output pin has no software readback at all on this board.\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// The pulse width the recipe carries, or the default when it carries nothing.
// A recipe saved before the width became an entered value reads back as zero,
// and zero would fail validation for a reason the operator never chose.
static double ScanTriggerPulseWidthUS(void)
{
	return (ScanTriggerRecipe.dPulseWidthUS > 0.0)
			   ? ScanTriggerRecipe.dPulseWidthUS
			   : SCANTRIGGER_PULSE_DEFAULT_US;
}

//////////////////////////////////////////////////////////////////////////
static bool ScanTriggerIsTimerMode(void)
{
	return (ScanTriggerRecipe.uTriggerMode == (unsigned int)SCANTRIGGER_MODE_TIMER);
}

//////////////////////////////////////////////////////////////////////////
// Timer mode: what rate to program, and what it does to the pitch.
//
// The pitch is v / f and f has to be a whole number of Hz, so the obvious way
// round - keep the entered speed, round the rate - leaves a pitch error of
// about pitch^2 / v per Hz of rounding. At 18 um and 200 mm/s that is 1.6 nm,
// which is already far below anything the optics can see.
//
// But it does not have to be there at all. The speed is a free parameter: the
// operator entered it to fix the tact time, not to a nanometre. So round the
// rate, then set the speed to pitch x rate. The pitch comes out exactly as
// asked, the speed moves by at most one part in f - 0.009 % at 11 kHz - and
// the quantisation term is gone rather than merely small.
//
// What is left is velocity error, and no arithmetic here can do anything about
// that: in this mode the pitch is right only while the stage actually holds
// the speed. That is the trade against periodic mode, where the encoder keeps
// the pitch right no matter what the velocity does.
static void ScanTriggerSolveTimer(double dPitchMM, double dSpeedMMS,
								  double* dpRateHz, double* dpSpeedMMS,
								  double* dpAchievedMM, double* dpErrorNM)
{
	const double dIdeal   = dSpeedMMS / dPitchMM;
	const double dRounded = floor(dIdeal + 0.5);

	*dpRateHz     = dRounded;
	*dpSpeedMMS   = dPitchMM * dRounded;    // exactly dPitchMM per pulse
	*dpAchievedMM = dPitchMM;
	*dpErrorNM    = 0.0;

	// Only if the rate could not be programmed at all does the pitch have to
	// give instead, and then the caller refuses rather than running it.
	if (dRounded < SCANTRIGGER_TIMER_FREQ_MIN || dRounded > SCANTRIGGER_TIMER_FREQ_MAX) {
		*dpSpeedMMS   = dSpeedMMS;
		*dpAchievedMM = (dRounded > 0.0) ? (dSpeedMMS / dRounded) : 0.0;
		*dpErrorNM    = (*dpAchievedMM - dPitchMM) * 1.0e6;
	}
}

//////////////////////////////////////////////////////////////////////////
// A motor index position in mm. PositionArray holds pulses, because the MMI
// multiplies by the pulse rate before sending the table.
static double ScanTriggerIndexMM(const CAjinMotor* pAxis, int nIdx)
{
	if (pAxis == NULL || pAxis->MMI_PulseRate == 0) {
		return 0.0;
	}
	return pAxis->PositionArray[nIdx] / (double)pAxis->MMI_PulseRate;
}

//////////////////////////////////////////////////////////////////////////
static CAjinMotor* ScanTriggerAxis(void)
{
	const int nIdx = (int)ScanTriggerRecipe.uAxisNo + 1;
	if (nIdx < 1 || nIdx > (int)totalAxisCnt) {
		return NULL;
	}
	return MTAxis[nIdx];
}

//////////////////////////////////////////////////////////////////////////
// Recompute ScanTriggerDisplay from ScanTriggerRecipe. Called whenever the MMI changes a
// value and again before the cycle starts, so the operator sees the same
// numbers the cycle will use.
int CSeqMain::ScanTriggerValidate(void)
{
	memset(&ScanTriggerDisplay, 0, sizeof(ScanTriggerDisplay));
	ScanTriggerDisplay.nState = g_nScanTriggerState;
	ScanTriggerDisplay.nTriggerCount = g_nScanTriggerLastCount;

	// Echoed before any test can return early, so the panel can always see which
	// recipe the numbers beside it came from - including on a refusal.
	ScanTriggerDisplay.dRecipePitch   = ScanTriggerRecipe.dPitch;
	ScanTriggerDisplay.dRecipeSpeed   = ScanTriggerRecipe.dSpeed;
	ScanTriggerDisplay.dRecipePulseUS = ScanTriggerRecipe.dPulseWidthUS;

	CAjinMotor* pAxis = ScanTriggerAxis();
	if (pAxis == NULL) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_AXIS;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (ScanTriggerRecipe.dPitch <= 0.0) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_PITCH;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (ScanTriggerRecipe.dSpeed <= 0.0) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_SPEED_ZERO;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (pAxis->MMI_PulseRate == 0) {
		// Without it the index table cannot be read as mm at all.
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_PULSERATE;
		return ScanTriggerDisplay.nValidateCode;
	}

	// The geometry, straight out of the motor index table.
	ScanTriggerDisplay.dMotionStart = ScanTriggerIndexMM(pAxis, SCANTRIGGER_IDX_MOTION_START);
	ScanTriggerDisplay.dTrigStart   = ScanTriggerIndexMM(pAxis, SCANTRIGGER_IDX_TRIG_START);
	ScanTriggerDisplay.dTrigEnd     = ScanTriggerIndexMM(pAxis, SCANTRIGGER_IDX_TRIG_END);
	ScanTriggerDisplay.dMotionEnd   = ScanTriggerIndexMM(pAxis, SCANTRIGGER_IDX_MOTION_END);

	// 50 <= 51 < 52 <= 53. The run-up and run-out may be zero length - that is
	// a scan with no room to accelerate outside the block, which is what the
	// cycle used to do - but the block itself has to have length, and nothing
	// may be out of order.
	if (ScanTriggerDisplay.dTrigEnd   <= ScanTriggerDisplay.dTrigStart ||
		ScanTriggerDisplay.dTrigStart <  ScanTriggerDisplay.dMotionStart ||
		ScanTriggerDisplay.dMotionEnd <  ScanTriggerDisplay.dTrigEnd) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_INDEXPOS;
		return ScanTriggerDisplay.nValidateCode;
	}

	const double dLength = ScanTriggerDisplay.dTrigEnd - ScanTriggerDisplay.dTrigStart;

	// speed = pitch x line rate, entered from the speed end. The camera is then
	// set from a line rate nobody had to work out by hand.
	ScanTriggerDisplay.nTriggerMode = (int)ScanTriggerRecipe.uTriggerMode;
	ScanTriggerDisplay.dSpeed       = ScanTriggerRecipe.dSpeed;
	ScanTriggerDisplay.dLineRate    = ScanTriggerDisplay.dSpeed / ScanTriggerRecipe.dPitch;

	// The comparator counts whole encoder counts. A fractional pitch is
	// rounded, and that error repeats for the whole scan rather than
	// cancelling out. Reported in both modes, because it is the number that
	// says why one of them had to be chosen.
	ScanTriggerDisplay.dPitchCounts = ScanTriggerRecipe.dPitch / ScanTriggerEncUnitMM();
	const double dNearest = floor(ScanTriggerDisplay.dPitchCounts + 0.5);
	ScanTriggerDisplay.bPitchIsInteger =
		(dNearest >= 1.0 &&
		 fabs(ScanTriggerDisplay.dPitchCounts - dNearest) <= dNearest * 1e-6);

	if (ScanTriggerIsTimerMode()) {
		// The encoder is not in the loop, so the pitch is not tied to its 1 um
		// step and bPitchIsInteger is reported but not enforced. The rate is
		// rounded to a whole Hz and the speed trimmed to suit, which leaves the
		// pitch exactly as asked - see ScanTriggerSolveTimer().
		ScanTriggerSolveTimer(ScanTriggerRecipe.dPitch, ScanTriggerRecipe.dSpeed,
							  &ScanTriggerDisplay.dLineRate,
							  &ScanTriggerDisplay.dSpeedAdjusted,
							  &ScanTriggerDisplay.dPitchAchieved,
							  &ScanTriggerDisplay.dPitchErrorNM);

		// Once the board has been asked, what it gave beats what was computed.
		// AxcTriggerSetFreq takes whole Hz but the hardware divides a fixed
		// clock, so the rates it can actually produce are C/N - 253,807.11 Hz
		// where 253,485 was asked for. The pitch stays exact by running the
		// stage at pitch x the rate the board really has.
		//
		// Cleared by ScanTriggerSetRecipe(), so this is always this recipe's
		// answer or nothing.
		if (g_dScanTriggerTimerHz > 0.0) {
			ScanTriggerDisplay.dLineRate      = g_dScanTriggerTimerHz;
			ScanTriggerDisplay.dSpeedAdjusted =
				ScanTriggerDisplay.dPitchAchieved * g_dScanTriggerTimerHz;
		}

		if (ScanTriggerDisplay.dLineRate < SCANTRIGGER_TIMER_FREQ_MIN ||
			ScanTriggerDisplay.dLineRate > SCANTRIGGER_TIMER_FREQ_MAX) {
			ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_LINERATE;
			return ScanTriggerDisplay.nValidateCode;
		}

		// From here on the scan runs at the trimmed speed, not the entered one.
		ScanTriggerDisplay.dSpeed = ScanTriggerDisplay.dSpeedAdjusted;
	}
	else {
		ScanTriggerDisplay.dSpeedAdjusted  = ScanTriggerRecipe.dSpeed;
		ScanTriggerDisplay.dPitchAchieved  = dNearest * ScanTriggerEncUnitMM();
		ScanTriggerDisplay.dPitchErrorNM   =
			(ScanTriggerDisplay.dPitchAchieved - ScanTriggerRecipe.dPitch) * 1.0e6;

		if (!ScanTriggerDisplay.bPitchIsInteger) {
			ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_PITCH_FRACTION;
			return ScanTriggerDisplay.nValidateCode;
		}
	}

	ScanTriggerDisplay.dScanTime  = dLength / ScanTriggerDisplay.dSpeed;
	ScanTriggerDisplay.nLineCount = (int)(dLength / ScanTriggerDisplay.dPitchAchieved + 0.5);
	if (ScanTriggerDisplay.nLineCount <= 0 || ScanTriggerDisplay.nLineCount > SCANTRIGGER_MAX_LINES) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_LINECOUNT;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (ScanTriggerDisplay.dSpeed * (double)pAxis->MMI_PulseRate > (double)pAxis->MaxSpeed) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_SPEED_MAX;
		return ScanTriggerDisplay.nValidateCode;
	}

	// The entered pulse width, against the line period the entered speed gives.
	// Too narrow and the camera never sees it; wider than the period and the
	// output has no gap between lines at all.
	const double dPeriodUS = 1.0e6 / ScanTriggerDisplay.dLineRate;
	if (ScanTriggerPulseWidthUS() < SCANTRIGGER_PULSE_MIN_US ||
		ScanTriggerPulseWidthUS() > dPeriodUS * SCANTRIGGER_PULSE_MAX_DUTY) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_PULSEWIDTH;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (AjinTrigger == NULL || AjinTrigger->GetChannelCount() <= ScanTriggerChannel()) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_NO_COUNTER;
		return ScanTriggerDisplay.nValidateCode;
	}

	// The machine's state, not the recipe's - but tested here all the same,
	// and last, so the derived numbers above are still filled in and visible
	// beside the refusal.
	//
	// These two used to be tested only in ScanTriggerM(), which runs on START.
	// SET therefore reported a recipe that was perfectly good and START then
	// refused it, printing the reason to SEQ's console and nowhere else - so
	// the screen said the recipe was accepted, the button did nothing, and
	// there was no way to find out why without the console. Testing them at SET
	// puts the answer where the operator is looking.
	//
	// ScanTriggerM() still tests them too: an axis can be homed when SET is
	// pressed and jogged away from home before START is.
	// OriginFound, not imrs. imrs means "at a known index position" and any jog
	// clears it, so gating on it refused every scan that followed an operator
	// nudging the stage to look at something - while the absolute coordinates
	// the scan actually uses were perfectly valid the whole time.
	if (!pAxis->OriginFound) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_NOT_HOMED;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (!pAxis->IsStop && !bit.ScanTriggerRun) {
		// Not while a scan is running: the cycle moves the axis itself, and
		// re-reading the display mid-scan must not turn that into a refusal.
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_MOVING;
		return ScanTriggerDisplay.nValidateCode;
	}

	ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_OK;
	return ScanTriggerDisplay.nValidateCode;
}

//////////////////////////////////////////////////////////////////////////
// A recipe from the MMI.
//
// Everything the panel shows is derived from these four numbers, so when the
// panel disagrees with what was typed, this is the line that says which side is
// wrong - and the one way a recipe can be dropped is printed right beside it.
void CSeqMain::ScanTriggerSetRecipe(const _scantriggerrecipe& rcp)
{
	// Not while a scan is running: the cycle reads the recipe every pass, so
	// swapping it mid-scan moves the target out from under it.
	if (bit.ScanTriggerRun) {
		printf("[SCANTRIGGER] recipe IGNORED, a scan is running -"
			   " the panel is still showing the old one\n");
		return;
	}

	ScanTriggerRecipe = rcp;

	// The board's measured rate belongs to the recipe that was loaded when it
	// was measured. Anything the panel shows from here has to come from the new
	// one, or it is a set of numbers that agree with each other and with
	// nothing the operator typed - which is exactly how a lost recipe write
	// reads on screen, and took three rounds to tell apart from a real fault.
	g_dScanTriggerTimerHz = 0.0;

	printf("[SCANTRIGGER] recipe: %s, pitch %.6f mm, speed %.4f mm/s,"
		   " pulse %.2f us, axis %u\n",
		   ScanTriggerIsTimerMode() ? "TIMER" : "PERIODIC",
		   ScanTriggerRecipe.dPitch, ScanTriggerRecipe.dSpeed,
		   ScanTriggerRecipe.dPulseWidthUS, ScanTriggerRecipe.uAxisNo);

	ScanTriggerValidate();

	// A new recipe means the last cycle's verdict is no longer what the panel
	// should be reporting. Leaving the state at DONE let the next poll
	// overwrite this SET's result with the previous run's, a few milliseconds
	// after SET had written it - so the screen said DONE where it should have
	// said OK, and the operator had no way to tell a fresh SET from a stale
	// one.
	if (g_nScanTriggerState == SCANTRIGGER_DONE ||
		g_nScanTriggerState == SCANTRIGGER_ABORTED) {
		g_nScanTriggerState = SCANTRIGGER_IDLE;
		ScanTriggerDisplay.nState = g_nScanTriggerState;
	}
}

//////////////////////////////////////////////////////////////////////////
void CSeqMain::ScanTriggerAbort(const char* pszWhy)
{
	if (AjinTrigger != NULL) {
		// Both modes stop the same way - AxcTriggerSetEnable(ch, 0) - but the
		// timer's own flag has to come down with it, or the next cycle starts
		// believing its window is already open.
		AjinTrigger->StopPeriodicTrigger(ScanTriggerChannel());
	}
	g_bScanTriggerTimerOn = false;

	CAjinMotor* pAxis = ScanTriggerAxis();
	if (pAxis != NULL && !pAxis->IsStop) {
		pAxis->MTEStop();
	}

	g_nScanTriggerState = SCANTRIGGER_ABORTED;
	ScanTriggerDisplay.nState = g_nScanTriggerState;
	bit.ScanTriggerRun = 0;

	printf("[SCANTRIGGER] aborted: %s\n", (pszWhy != NULL) ? pszWhy : "");
	sprintf(strFileLog, "Scan aborted: %s", (pszWhy != NULL) ? pszWhy : "");
	LOG_TRACE(strFileLog);
}

//////////////////////////////////////////////////////////////////////////
// Arm the cycle. Refuses rather than starting a scan that cannot be correct,
// because a bad pitch or speed is only visible afterwards, in the image.
void CSeqMain::ScanTriggerM(void)
{
	if (bit.ScanTriggerRun) {
		printf("[SCANTRIGGER] already running\n");
		return;
	}

	const int nCode = ScanTriggerValidate();
	if (nCode != SCANTRIGGER_VALIDATE_OK) {
		printf("[SCANTRIGGER] recipe refused, code %d\n", nCode);
		return;
	}

	CAjinMotor* pAxis = ScanTriggerAxis();
	if (!pAxis->OriginFound) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_NOT_HOMED;
		printf("[SCANTRIGGER] axis %u has not found its origin since power up\n",
			   ScanTriggerRecipe.uAxisNo);
		return;
	}
	if (!pAxis->IsStop) {
		// Leave the reason where the MMI can read it, not only on the console.
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_MOVING;
		printf("[SCANTRIGGER] axis %u is still moving\n", ScanTriggerRecipe.uAxisNo);
		return;
	}

	g_nScanTriggerState = SCANTRIGGER_GOTO_START;
	ScanTriggerDisplay.nState = g_nScanTriggerState;
	bit.ScanTriggerRun = 1;

	// The last cycle's answer is kept. It is only used when the request matches
	// the one that produced it, so a recipe with a different rate falls back to
	// the estimate until ARM has asked the board again.

	printf("[SCANTRIGGER] move %.4f -> %.4f mm [idx %d..%d],"
		   " trigger %.4f .. %.4f mm [idx %d..%d], run-up %.3f mm, run-out %.3f mm\n",
		   ScanTriggerDisplay.dMotionStart, ScanTriggerDisplay.dMotionEnd,
		   SCANTRIGGER_IDX_MOTION_START, SCANTRIGGER_IDX_MOTION_END,
		   ScanTriggerDisplay.dTrigStart, ScanTriggerDisplay.dTrigEnd,
		   SCANTRIGGER_IDX_TRIG_START, SCANTRIGGER_IDX_TRIG_END,
		   ScanTriggerDisplay.dTrigStart - ScanTriggerDisplay.dMotionStart,
		   ScanTriggerDisplay.dMotionEnd - ScanTriggerDisplay.dTrigEnd);

	printf("[SCANTRIGGER] %s mode, pitch %.4f mm (%.4f counts), %.4f mm/s -> %.0f Hz,"
		   " %.2f us pulse, %d lines, %.3f s\n",
		   ScanTriggerIsTimerMode() ? "TIMER" : "PERIODIC",
		   ScanTriggerRecipe.dPitch, ScanTriggerDisplay.dPitchCounts,
		   ScanTriggerDisplay.dSpeed, ScanTriggerDisplay.dLineRate,
		   ScanTriggerPulseWidthUS(), ScanTriggerDisplay.nLineCount, ScanTriggerDisplay.dScanTime);

	// What the mode does to the number the operator actually cares about.
	if (ScanTriggerIsTimerMode()) {
		printf("[SCANTRIGGER] timer: rate rounded to a whole %.0f Hz and the speed trimmed"
			   " %.4f -> %.4f mm/s, so the pitch is exactly %.6f mm.\n",
			   ScanTriggerDisplay.dLineRate,
			   ScanTriggerRecipe.dSpeed, ScanTriggerDisplay.dSpeedAdjusted,
			   ScanTriggerDisplay.dPitchAchieved);
		printf("[SCANTRIGGER]  the encoder no longer holds the pitch: a %.2f %% velocity"
			   " error is a %.1f nm pitch error, against %.2f nm per Hz of rate.\n",
			   0.1, ScanTriggerRecipe.dPitch * 0.001 * 1.0e6,
			   (ScanTriggerDisplay.dLineRate > 0.0)
				   ? (ScanTriggerDisplay.dPitchAchieved / ScanTriggerDisplay.dLineRate * 1.0e6)
				   : 0.0);
	}
	else if (fabs(ScanTriggerDisplay.dPitchErrorNM) > 0.5) {
		printf("[SCANTRIGGER] periodic: the pitch rounds to %.6f mm, %+.1f nm per line.\n",
			   ScanTriggerDisplay.dPitchAchieved, ScanTriggerDisplay.dPitchErrorNM);
	}

	// The distance the stage has to get up to speed in, against the distance it
	// needs. Accel is set to Speed * 5 in the RUN state below.
	{
		const double dRunUp  = ScanTriggerDisplay.dTrigStart - ScanTriggerDisplay.dMotionStart;
		const double dNeeded = ScanTriggerDisplay.dSpeed / 10.0;   // v^2 / (2 * v*5)
		if (dRunUp < dNeeded) {
			printf("[SCANTRIGGER] WARNING: run-up is %.3f mm but reaching %.1f mm/s needs"
				   " %.3f mm. The first lines will be taken while still accelerating.\n",
				   dRunUp, ScanTriggerDisplay.dSpeed, dNeeded);
		}
	}

	sprintf(strFileLog, "Scan start %.4f to %.4f mm, %d lines",
			ScanTriggerDisplay.dTrigStart, ScanTriggerDisplay.dTrigEnd, ScanTriggerDisplay.nLineCount);
	LOG_TRACE(strFileLog);
}

//////////////////////////////////////////////////////////////////////////
// Drive the trigger pin directly, with no encoder and no comparator involved.
//
// This is the measurement that splits the problem in two. If the scope shows
// this square wave on CON1 but a scan shows nothing, the output stage and the
// wiring are fine and the fault is in the encoder or the comparator settings.
// If even this is flat, no trigger setting will ever help.
void CSeqMain::ScanTriggerOutputTestM(void)
{
	// A second press during a test restarts it rather than being refused - the
	// operator is at the scope and pressing it again means "do that again".
	if (bit.ScanTriggerRun && g_nScanTriggerState != SCANTRIGGER_OUTPUT_TEST) {
		printf("[SCANTRIGGER] output test refused, a scan is running\n");
		return;
	}
	if (AjinTrigger == NULL || AjinTrigger->GetChannelCount() <= ScanTriggerChannel()) {
		printf("[SCANTRIGGER] output test refused, no counter channel %ld\n",
			   ScanTriggerChannel());
		return;
	}

	// AxcTriggerSetEnable is the final gate in front of the output stage, so the
	// line has to be ENABLED for a forced level to reach the pin. The first
	// version of this test disabled it first and the flat scope it produced
	// said nothing about the wiring. Nothing moves during the test, and
	// periodic mode only fires on encoder movement, so enabling is safe.
	if (!AjinTrigger->BeginOutputTest(ScanTriggerChannel())) {
		printf("[SCANTRIGGER] output test refused, the output stage could not be enabled\n");
		return;
	}
	AjinTrigger->ReportChannelConfig(ScanTriggerChannel(), "output test, line enabled");

	g_nScanTriggerTestStep = 0;
	g_bScanTriggerTestHigh = false;
	g_tmScanTriggerTest.SetTime();

	g_nScanTriggerState = SCANTRIGGER_OUTPUT_TEST;
	ScanTriggerDisplay.nState = g_nScanTriggerState;
	g_nScanTriggerLastCount = -1;
	bit.ScanTriggerRun = 1;

	printf("[SCANTRIGGER] output self test on channel %ld : %d pulses, %lld ms high"
		   " and %lld ms low. Probe CON1 pin 1-2 now; the stage does not move.\n",
		   ScanTriggerChannel(), SCANTRIGGER_TEST_PULSES,
		   SCANTRIGGER_TEST_HALF_MS, SCANTRIGGER_TEST_HALF_MS);

	ScanTriggerLogReadbackLimits();

	sprintf(strFileLog, "Scan trigger output self test, %d pulses", SCANTRIGGER_TEST_PULSES);
	LOG_TRACE(strFileLog);
}

//////////////////////////////////////////////////////////////////////////
void CSeqMain::ScanTriggerC(void)
{
	if (!bit.ScanTriggerRun) return;

	// The output test moves nothing, so it runs before the axis checks below.
	// It has to work on a machine whose axis is not homed or not even built -
	// that is precisely when somebody is standing at the scope.
	if (g_nScanTriggerState == SCANTRIGGER_OUTPUT_TEST) {
		if (!g_tmScanTriggerTest.TimeOvermS(SCANTRIGGER_TEST_HALF_MS)) {
			return;
		}
		g_tmScanTriggerTest.SetTime();

		if (g_nScanTriggerTestStep >= SCANTRIGGER_TEST_PULSES * 2) {
			// One burst of real trigger pulses before standing down: same
			// width and level the scan uses, straight from the board's pulse
			// generator, with nothing moving. Seeing these but not seeing a
			// scan means only the position comparator is left to explain.
			AjinTrigger->PulseBurst(ScanTriggerChannel(),
									SCANTRIGGER_TEST_BURST_PULSES,
									SCANTRIGGER_TEST_BURST_HZ);

			AjinTrigger->EndOutputTest(ScanTriggerChannel());
			printf("[SCANTRIGGER] output self test finished, %d pulses driven.\n",
				   SCANTRIGGER_TEST_PULSES);
			printf("[SCANTRIGGER]  scope showed them -> output stage and wiring are good,"
				   " the fault is in the encoder or the comparator.\n");
			printf("[SCANTRIGGER]  scope flat        -> wrong pin, wrong channel, or the"
				   " output stage. No trigger setting can fix that.\n");
			printf("[SCANTRIGGER]  the trigger polarity was restored to active high.\n");

			// DONE rather than IDLE: the MMI stops following the panel on DONE,
			// and clearing the run bit means the switch below never sees this
			// state, so the scan report is not printed for a test.
			g_nScanTriggerState = SCANTRIGGER_DONE;
			ScanTriggerDisplay.nState = g_nScanTriggerState;
			bit.ScanTriggerRun = 0;
			SendCopyDataToMMI(WM_SEQ_TO_MMI_SCANTRIGGER_DONE, 0, NULL);
			return;
		}

		g_bScanTriggerTestHigh = !g_bScanTriggerTestHigh;
		const bool bSet = AjinTrigger->ForceOutput(ScanTriggerChannel(), g_bScanTriggerTestHigh);

		// Read the line back the way the board sees it, so the log stands on
		// its own when nobody has a scope on the connector. On a board that
		// refuses AxcStatusGetChannel there is nothing to read and the scope is
		// the whole test, which is said once at the start rather than as "n/a"
		// against every pulse.
		bool bSeen = false;
		const bool bRead = AjinTrigger->ReadOutputState(ScanTriggerChannel(), &bSeen);

		if (g_bScanTriggerTestHigh) {
			if (bRead) {
				printf("[SCANTRIGGER] test pulse %d/%d : driven HIGH%s,"
					   " board reports %s\n",
					   (g_nScanTriggerTestStep / 2) + 1, SCANTRIGGER_TEST_PULSES,
					   bSet ? "" : " (AxcTriggerSetOutput REFUSED)",
					   bSeen ? "HIGH" : "low");
			}
			else {
				printf("[SCANTRIGGER] test pulse %d/%d : driven HIGH%s\n",
					   (g_nScanTriggerTestStep / 2) + 1, SCANTRIGGER_TEST_PULSES,
					   bSet ? "" : " (AxcTriggerSetOutput REFUSED)");
			}
		}

		g_nScanTriggerTestStep++;
		return;
	}

	CAjinMotor* pAxis = ScanTriggerAxis();
	if (pAxis == NULL) {
		ScanTriggerAbort("axis disappeared");
		return;
	}
	if (pAxis->idrvalm || pAxis->IsAlarm) {
		ScanTriggerAbort("drive alarm");
		return;
	}

	const double dRate = (double)pAxis->MMI_PulseRate;

	switch (g_nScanTriggerState)
	{
	case SCANTRIGGER_GOTO_START:
		// Approach at the scan speed. The trigger block is not armed yet, so
		// nothing is exposed on the way in.
		pAxis->Speed = ScanTriggerDisplay.dSpeed * dRate;
		pAxis->Accel = fabs(pAxis->Speed * 5);
		pAxis->Decel = pAxis->Accel;
		pAxis->MTSAMove((int)(ScanTriggerDisplay.dMotionStart * dRate + 0.5));
		g_tmScanTriggerSettle.SetTime();
		g_nScanTriggerState = SCANTRIGGER_WAIT_START;
		break;

	case SCANTRIGGER_WAIT_START:
		if (!pAxis->IsStop) {
			g_tmScanTriggerSettle.SetTime();
			break;
		}
		if (g_tmScanTriggerSettle.TimeOvermS(SCANTRIGGER_SETTLE_MS)) {
			g_nScanTriggerState = SCANTRIGGER_ARM;
		}
		break;

	case SCANTRIGGER_ARM:
	{
		// Tie the counter to machine coordinates. The recipe is in absolute
		// positions, so the counter has to read the same scale before the
		// block limits mean anything.
		// The counter works in raw encoder counts - AxcMotSetMoveUnitPerPulse is
		// CN2CH-only and does nothing on this board - so the preset is in counts.
		if (!AjinTrigger->ResetScanOrigin(ScanTriggerChannel(),
										  ScanTriggerDisplay.dMotionStart / ScanTriggerEncUnitMM())) {
			ScanTriggerAbort("could not preset the counter position");
			break;
		}

		PERIODIC_TRIG_CFG cfg;
		cfg.lChannelNo       = ScanTriggerChannel();
		cfg.dwEncoderInput   = g_ScanTriggerHw.uEncoderInput;
		cfg.dwTriggerOutPort = g_ScanTriggerHw.uOutPortMask;
		cfg.dMoveUnitPerPulse= ScanTriggerEncUnitMM();
		cfg.dPitch           = ScanTriggerDisplay.dPitchAchieved;
		cfg.dScanStart       = ScanTriggerDisplay.dTrigStart;
		cfg.dScanEnd         = ScanTriggerDisplay.dTrigEnd;
		cfg.dPulseWidthUS    = ScanTriggerPulseWidthUS();
		// Whole Hz, because that is what AxcTriggerSetFreq takes. Once an answer
		// has been cached, dLineRate carries the board's own rate - 253164.56 -
		// which is not a whole number, and passing it straight through had
		// StartTimerTrigger refusing the second run of a recipe that had just
		// worked. Rounding lands on the same grid point the board gave.
		cfg.dLineRateHz      = floor(ScanTriggerDisplay.dLineRate + 0.5);
		// Timer mode only: the board stops itself after this many pulses, so
		// the number of lines is exact however late the cycle closes the
		// window. Ignored by the periodic path, which gets its end from the
		// block.
		cfg.lTriggerCount    = ScanTriggerDisplay.nLineCount;
		cfg.dwTriggerLevel   = g_ScanTriggerHw.uTriggerLevel;
		cfg.dwDirectionCheck = g_ScanTriggerHw.uDirectionCheck;   // 1 = up only, the scan direction
		cfg.bEncReverse      = (g_ScanTriggerHw.bEncReverse != 0);

		g_bScanTriggerTimerOn    = false;
		g_dScanTriggerTimerOnAt  = 0.0;
		g_dScanTriggerTimerOffAt = 0.0;

		if (ScanTriggerIsTimerMode()) {
			// Configured but not started: the pulse train free runs, so
			// enabling it here would fire it all the way in from the approach.
			// The counter is still preset and still read, but only so this
			// cycle can open the window at dTrigStart and close it at dTrigEnd
			// - which is the guarantee this mode gives up.
			double dActualHz = 0.0;
			if (!AjinTrigger->StartTimerTrigger(cfg, &dActualHz)) {
				ScanTriggerAbort("StartTimerTrigger refused the configuration");
				break;
			}

			// The board's rate grid is coarser than whole Hz, so the rate it
			// settled on is not the one asked for. Run the stage at the speed
			// that rate implies and the pitch is exact again; keep the entered
			// speed and it would be out by the grid step, which is 0.25 % at
			// 253 kHz - 2 nm on a 0.789 um pixel, and a quarter of a percent
			// on the image's length.
			if (dActualHz > 0.0) {
				g_dScanTriggerTimerHz = dActualHz;

				const double dNewSpeed = ScanTriggerDisplay.dPitchAchieved * dActualHz;

				if (dNewSpeed * dRate > (double)pAxis->MaxSpeed) {
					ScanTriggerAbort("the speed the board's rate needs is beyond the axis");
					break;
				}

				printf("[SCANTRIGGER] board rate %.2f Hz: running at %.4f mm/s"
					   " instead of %.4f mm/s so the pitch stays %.6f um\n",
					   dActualHz, dNewSpeed, ScanTriggerDisplay.dSpeed,
					   ScanTriggerDisplay.dPitchAchieved * 1000.0);

				ScanTriggerDisplay.dLineRate      = dActualHz;
				ScanTriggerDisplay.dSpeed         = dNewSpeed;
				ScanTriggerDisplay.dSpeedAdjusted = dNewSpeed;
			}
			printf("[SCANTRIGGER] timer mode: the encoder does not gate the output."
				   " The board stops itself after %d pulses, so the line count is exact;"
				   " what carries a pass of jitter is where the first line lands.\n",
				   ScanTriggerDisplay.nLineCount);
			printf("[SCANTRIGGER]  the pitch holds only while the stage holds"
				   " %.4f mm/s - the encoder is not checking it.\n",
				   ScanTriggerDisplay.dSpeed);
		}
		else if (!AjinTrigger->StartPeriodicTrigger(cfg)) {
			ScanTriggerAbort("StartPeriodicTrigger refused the configuration");
			break;
		}

		// Where the counter stood when the block went live. Comparing this
		// against the counter at the end says whether the encoder was being
		// read at all, and in which direction it counted - a block armed for
		// one direction emits nothing while the count runs the other way.
		AjinTrigger->ClearTriggerCount(ScanTriggerChannel());
		g_dScanTriggerEncArm = 0.0;
		AjinTrigger->GetActPos(ScanTriggerChannel(), &g_dScanTriggerEncArm);
		g_nScanTriggerLastCount = -1;
		ScanTriggerLogReadbackLimits();
		ScanTriggerLogCounter("armed");

		g_tmScanTriggerLog.SetTime();
		g_nScanTriggerState = SCANTRIGGER_RUN;
		break;
	}

	case SCANTRIGGER_RUN:
		pAxis->Speed = ScanTriggerDisplay.dSpeed * dRate;
		pAxis->Accel = fabs(pAxis->Speed * 5);
		pAxis->Decel = pAxis->Accel;
		pAxis->MTSAMove((int)(ScanTriggerDisplay.dMotionEnd * dRate + 0.5));

		g_bScanTriggerMoving = false;
		g_tmScanTriggerMoveStart.SetTime();
		g_nScanTriggerState = SCANTRIGGER_WAIT_END;
		break;

	case SCANTRIGGER_WAIT_END:
		// IsStop is still true for the first few passes after MTSAMove: the
		// command has gone out but the status poll has not caught up. Testing
		// it straight away read "already stopped" and disarmed the trigger
		// before the stage had moved a single count - the scan then ran its
		// whole 500 mm with the trigger switched off, which is exactly what
		// the counter showed afterwards: armed at 100000, ended at 100000.
		//
		// So wait for the axis to be seen moving before the end of the move
		// means anything. WAIT_START has the same race and is already covered,
		// by its settle timer.
		if (!g_bScanTriggerMoving) {
			if (!pAxis->IsStop) {
				g_bScanTriggerMoving = true;
				g_tmScanTriggerLog.SetTime();
				ScanTriggerLogCounter("moving");
			}
			else if (g_tmScanTriggerMoveStart.TimeOvermS(SCANTRIGGER_MOVE_START_MS)) {
				ScanTriggerAbort("the axis never started moving");
			}
			break;
		}

		// The trigger runs in hardware, so this loop cannot miss a pulse by
		// running late. What it can do is say whether any are coming out.
		if (g_tmScanTriggerLog.TimeOvermS(SCANTRIGGER_LOG_MS)) {
			g_tmScanTriggerLog.SetTime();
			ScanTriggerLogCounter("running");
		}

		// A counter running away from the block will never produce a trigger,
		// so say so now rather than after the whole scan has been made.
		{
			double dNow = 0.0;
			const bool bGotPos = AjinTrigger->GetActPos(ScanTriggerChannel(), &dNow);

			if (bGotPos && (dNow - g_dScanTriggerEncArm) < -g_ScanTriggerHw.dWrongWayCounts) {
				ScanTriggerAbort("the counter is running away from the block;"
								 " the encoder direction is inverted");
				break;
			}

			// Timer mode has no block. The hardware will free run from the
			// moment it is enabled, so this is where the window is opened and
			// closed, one cycle pass at a time. The counter is read anyway for
			// the log, so the comparison costs nothing - but the edges land
			// wherever the pass happened to fall, which is the accuracy this
			// mode trades away and is why the position at each switch is
			// recorded and reported at the end.
			if (bGotPos && ScanTriggerIsTimerMode()) {
				const double dPosMM = dNow * ScanTriggerEncUnitMM();

				if (!g_bScanTriggerTimerOn) {
					if (dPosMM >= ScanTriggerDisplay.dTrigStart &&
						dPosMM <  ScanTriggerDisplay.dTrigEnd) {
						if (AjinTrigger->SetTimerRunning(ScanTriggerChannel(), true)) {
							g_bScanTriggerTimerOn   = true;
							g_dScanTriggerTimerOnAt = dPosMM;
							ScanTriggerLogCounter("trig on");
						}
						else {
							ScanTriggerAbort("the timer could not be started at the"
											 " block entry");
							break;
						}
					}
				}
				else if (ScanTriggerDisplay.nLineCount <= 0 &&
						 dPosMM >= ScanTriggerDisplay.dTrigEnd) {
					// Only when the board is NOT counting the pulses itself.
					//
					// With Timer Mode (Count) the board stops after exactly
					// nLineCount pulses, and closing the window on position cut
					// that short: the window opened 0.191 mm late, so the last
					// pulses were still to come when the stage reached Trig End,
					// and 130 of 126,743 lines were thrown away. That is the
					// size error this mode exists to prevent - a window that
					// opens late should shift the image, not shorten it.
					//
					// The run-out past Trig End is there to absorb exactly this.
					// DISARM switches the trigger off when the move ends, which
					// is the backstop.
					AjinTrigger->SetTimerRunning(ScanTriggerChannel(), false);
					g_bScanTriggerTimerOn    = false;
					g_dScanTriggerTimerOffAt = dPosMM;
					ScanTriggerLogCounter("trig off");
				}
			}
		}

		if (pAxis->IsStop) {
			g_nScanTriggerState = SCANTRIGGER_DISARM;
		}
		break;

	case SCANTRIGGER_DISARM:
	{
		// Timer mode: the stage stopped before the software saw it reach
		// dTrigEnd, so the pulse train is still running. Shut it off before
		// anything else.
		if (ScanTriggerIsTimerMode() && g_bScanTriggerTimerOn) {
			double dNow = 0.0;
			AjinTrigger->SetTimerRunning(ScanTriggerChannel(), false);
			g_bScanTriggerTimerOn = false;
			if (AjinTrigger->GetActPos(ScanTriggerChannel(), &dNow)) {
				g_dScanTriggerTimerOffAt = dNow * ScanTriggerEncUnitMM();
			}
		}

		long lCount = 0;
		g_nScanTriggerLastCount =
			AjinTrigger->ReadTriggerCount(ScanTriggerChannel(), &lCount) ? (int)lCount : -1;
		ScanTriggerDisplay.nTriggerCount = g_nScanTriggerLastCount;

		// Read everything back before the trigger is switched off, so what is
		// printed is the state the scan actually ran with.
		ScanTriggerLogCounter("end");
		AjinTrigger->ReportChannelConfig(ScanTriggerChannel(), "end of scan");

		double dEncEnd = 0.0;
		if (AjinTrigger->GetActPos(ScanTriggerChannel(), &dEncEnd)) {
			const double dEncTravel = (dEncEnd - g_dScanTriggerEncArm) * ScanTriggerEncUnitMM();
			const double dCmdTravel = ScanTriggerDisplay.dMotionEnd - ScanTriggerDisplay.dMotionStart;

			printf("[SCANTRIGGER] counter travelled %.4f mm, the stage was told to travel"
				   " %.4f mm\n", dEncTravel, dCmdTravel);

			if (fabs(dEncTravel) < dCmdTravel * 0.01) {
				printf("[SCANTRIGGER]  the counter barely moved. The encoder is not reaching"
					   " this channel - check the encoder input wiring and"
					   " AxcSignalSetEncSource / AxcSignalSetEncInputMethod.\n");
			}
			else if (dEncTravel < 0.0) {
				printf("[SCANTRIGGER]  the counter ran DOWN while the block is armed for the"
					   " up direction, so the comparator rejected every position."
					   " Set bEncReverse, or arm the other direction.\n");
			}
			else if (fabs(dEncTravel - dCmdTravel) > dCmdTravel * 0.05) {
				printf("[SCANTRIGGER]  counter travel is %.1f %% of the commanded travel,"
					   " so the counter unit does not match the encoder.\n",
					   dEncTravel / dCmdTravel * 100.0);
			}
		}

		if (ScanTriggerDisplay.nTriggerCount == 0) {
			printf("[SCANTRIGGER]  zero triggers emitted. Run the output self test to"
				   " separate the output stage from the comparator.\n");
		}

		// What the software window actually caught, against what was asked
		// for. In periodic mode the hardware guarantees these are the block
		// edges; in timer mode they are wherever the cycle pass fell, and the
		// difference is the line count this scan is uncertain by.
		if (ScanTriggerIsTimerMode()) {
			const double dSpanMM = g_dScanTriggerTimerOffAt - g_dScanTriggerTimerOnAt;
			const double dWantMM = ScanTriggerDisplay.dTrigEnd - ScanTriggerDisplay.dTrigStart;

			printf("[SCANTRIGGER] timer window %.4f .. %.4f mm = %.4f mm,"
				   " asked for %.4f .. %.4f mm = %.4f mm\n",
				   g_dScanTriggerTimerOnAt, g_dScanTriggerTimerOffAt, dSpanMM,
				   ScanTriggerDisplay.dTrigStart, ScanTriggerDisplay.dTrigEnd, dWantMM);

			if (ScanTriggerDisplay.dPitchAchieved > 0.0) {
				// The pulse count is bounded in hardware, so this is not a line
				// count error - it is where the lines landed. A window opened
				// late shifts the image; one opened early leaves the last lines
				// beyond the block, which is what a span shorter than asked for
				// means here.
				printf("[SCANTRIGGER]  %d lines were programmed and the window covers"
					   " %.0f of them; the %+.4f mm difference is an image offset,"
					   " not a size error\n",
					   ScanTriggerDisplay.nLineCount,
					   dSpanMM / ScanTriggerDisplay.dPitchAchieved,
					   dSpanMM - dWantMM);

				// There was a "measured mean pitch" line here and it measured
				// nothing. It divided the window span by the number of lines
				// the span contains - which is the span divided by the pitch -
				// so it returned the pitch it was given and reported +0.00 nm
				// every time, whatever the stage did. A number that cannot come
				// out wrong is not a measurement.
				//
				// The real one needs the count of pulses the board actually
				// emitted, against the distance travelled while it emitted
				// them. This AXL has no AxcTriggerReadTriggerCount, so the
				// count is known only as the number programmed, and the
				// distance only between two software switch points that do not
				// coincide with the first and last pulse. Neither end is tight
				// enough to divide.
				//
				// So it is not claimed. In this mode the pitch is the commanded
				// speed divided by the board's rate, and how well the stage
				// held that speed is measured with a scope on the trigger
				// output or by replacing the AXL.
				printf("[SCANTRIGGER]  the achieved pitch cannot be measured from here:"
					   " this AXL cannot report how many triggers were emitted\n");
			}

			AjinTrigger->StopTimerTrigger(ScanTriggerChannel());
		}
		else {
			AjinTrigger->StopPeriodicTrigger(ScanTriggerChannel());
		}
		g_nScanTriggerState = SCANTRIGGER_RETURN;
		break;
	}

	case SCANTRIGGER_RETURN:
		// Back to SCAN START, so the next scan can be started without anybody
		// first driving the stage back by hand - and so a scan always leaves the
		// machine where it found it. The trigger is already off, so nothing is
		// exposed on the way back.
		//
		// The return is always a real move: the block has length, so SCAN END is
		// always beyond SCAN START and the axis cannot already be there.
		pAxis->Speed = ScanTriggerDisplay.dSpeed * dRate;
		pAxis->Accel = fabs(pAxis->Speed * 5);
		pAxis->Decel = pAxis->Accel;
		pAxis->MTSAMove((int)(ScanTriggerDisplay.dMotionStart * dRate + 0.5));

		printf("[SCANTRIGGER] returning to the scan start position, %.3f mm\n",
			   ScanTriggerDisplay.dMotionStart);

		g_bScanTriggerMoving = false;
		g_tmScanTriggerMoveStart.SetTime();
		g_nScanTriggerState = SCANTRIGGER_WAIT_RETURN;
		break;

	case SCANTRIGGER_WAIT_RETURN:
		// Same race as WAIT_END: IsStop still reads true for the first few
		// passes after MTSAMove, so the axis has to be seen moving before the
		// end of the move means anything.
		if (!g_bScanTriggerMoving) {
			if (!pAxis->IsStop) {
				g_bScanTriggerMoving = true;
			}
			else if (g_tmScanTriggerMoveStart.TimeOvermS(SCANTRIGGER_MOVE_START_MS)) {
				// The scan itself is finished and its count is already reported,
				// so say which half failed rather than letting "aborted" suggest
				// the scan was no good.
				ScanTriggerAbort("the scan finished, but the stage never started"
								 " its return move");
			}
			break;
		}

		if (pAxis->IsStop) {
			g_nScanTriggerState = SCANTRIGGER_DONE;
		}
		break;

	case SCANTRIGGER_DONE:
		// The cycle is over. Clearing this is what lets the next recipe be
		// set - ScanTriggerSetRecipe() refuses while it is up - so it is the
		// first thing done here rather than something left to fall out of the
		// state machine.
		bit.ScanTriggerRun = 0;

		// Parked first, then the verdict. The log is read as the story of the
		// cycle, and the cycle parks before it is finished.
		printf("[SCANTRIGGER] parked at the scan start position, %.3f mm\n",
			   ScanTriggerDisplay.dMotionStart);

		if (ScanTriggerDisplay.nTriggerCount >= 0) {
			printf("[SCANTRIGGER] finished, %d triggers (expected %d, %+.2f %%)\n",
				   ScanTriggerDisplay.nTriggerCount, ScanTriggerDisplay.nLineCount,
				   (ScanTriggerDisplay.nLineCount > 0)
					   ? ((double)ScanTriggerDisplay.nTriggerCount
						  / (double)ScanTriggerDisplay.nLineCount - 1.0) * 100.0
					   : 0.0);
		}
		else {
			printf("[SCANTRIGGER] finished, expected %d triggers"
				   " (the board could not be asked how many it emitted)\n",
				   ScanTriggerDisplay.nLineCount);
		}

		sprintf(strFileLog, "%s", "Scan finished");
		LOG_TRACE(strFileLog);

		// The MMI cannot poll fast enough to catch the end of a scan, so tell it,
		// the same way AllHomeC() reports a completed home.
		SendCopyDataToMMI(WM_SEQ_TO_MMI_SCANTRIGGER_DONE, 0, NULL);
		break;

	default:
		ScanTriggerAbort("unexpected state");
		break;
	}

	ScanTriggerDisplay.nState = g_nScanTriggerState;
}

//////////////////////////////////////////////////////////////////////////
// Engineer screen.
//
// The settings and the counter clear are refused while bit.ScanTriggerRun is
// set, which covers a scan and an output test alike: both have the channel
// programmed with the settings they started from, and changing them under a
// running cycle would leave the board and this file disagreeing about it.
//////////////////////////////////////////////////////////////////////////
void CSeqMain::ScanTriggerGetHwCfg(_scantriggerhwcfg& cfg)
{
	cfg = g_ScanTriggerHw;
	cfg.nResult = SCANTRIGGER_HWCFG_OK;
}

int CSeqMain::ScanTriggerSetHwCfg(const _scantriggerhwcfg& cfg)
{
	if (bit.ScanTriggerRun) {
		printf("[SCANTRIGGER] settings refused, the cycle is running\n");
		return SCANTRIGGER_HWCFG_BUSY;
	}

	const long lChannels = (AjinTrigger != NULL) ? AjinTrigger->GetChannelCount() : 0;
	const bool bChannelOk = (cfg.nChannel >= 0) &&
							(lChannels == 0 || cfg.nChannel < lChannels);
	if (!bChannelOk ||
		cfg.uEncoderInput > 3 ||
		cfg.uOutPortMask == 0 || cfg.uOutPortMask > 0xF ||
		!(cfg.dEncUnitMM > 0.0) || cfg.dEncUnitMM > 1.0 ||
		cfg.uTriggerLevel > 1 ||
		cfg.uDirectionCheck > 2 ||
		cfg.dWrongWayCounts < 0.0) {
		printf("[SCANTRIGGER] settings refused, a value is out of range"
			   " (ch %d of %ld, enc %u, out 0x%X, unit %.6f mm, level %u, dir %u, wrong way %.0f)\n",
			   cfg.nChannel, lChannels, cfg.uEncoderInput, cfg.uOutPortMask, cfg.dEncUnitMM,
			   cfg.uTriggerLevel, cfg.uDirectionCheck, cfg.dWrongWayCounts);
		return SCANTRIGGER_HWCFG_RANGE;
	}

	g_ScanTriggerHw = cfg;
	g_ScanTriggerHw.nResult = SCANTRIGGER_HWCFG_OK;
	memset(g_ScanTriggerHw.uReserved, 0, sizeof(g_ScanTriggerHw.uReserved));

	printf("[SCANTRIGGER] settings: ch %d, enc input %u, out 0x%X, %.6f mm/count, %s,"
		   " level %s, direction %u, wrong way %.0f counts\n",
		   g_ScanTriggerHw.nChannel, g_ScanTriggerHw.uEncoderInput, g_ScanTriggerHw.uOutPortMask,
		   g_ScanTriggerHw.dEncUnitMM, g_ScanTriggerHw.bEncReverse ? "reversed" : "normal",
		   g_ScanTriggerHw.uTriggerLevel ? "high" : "low", g_ScanTriggerHw.uDirectionCheck,
		   g_ScanTriggerHw.dWrongWayCounts);
	sprintf(strFileLog, "Scan trigger settings written: ch %d, %.6f mm/count",
			g_ScanTriggerHw.nChannel, g_ScanTriggerHw.dEncUnitMM);
	LOG_TRACE(strFileLog);

	// The pitch in counts and everything derived from it depend on the unit.
	ScanTriggerValidate();
	return SCANTRIGGER_HWCFG_OK;
}

void CSeqMain::ScanTriggerReadCounter(_scantriggercounter& cnt)
{
	memset(&cnt, 0, sizeof(cnt));
	cnt.nTriggerCount = -1;
	cnt.nOutput       = -1;
	cnt.nState        = g_nScanTriggerState;
	cnt.dArmCount     = g_dScanTriggerEncArm;

	const double dUnit = ScanTriggerEncUnitMM();
	if (dUnit > 0.0) {
		cnt.dBlockLowerCnt = ScanTriggerDisplay.dTrigStart / dUnit;
		cnt.dBlockUpperCnt = ScanTriggerDisplay.dTrigEnd / dUnit;
	}

	if (AjinTrigger == NULL) return;

	double dPos = 0.0;
	if (AjinTrigger->GetActPos(ScanTriggerChannel(), &dPos)) {
		cnt.bRead     = 1;
		cnt.dEncCount = dPos;
		cnt.dEncPosMM = dPos * dUnit;
	}
	long lCount = 0;
	if (CAjinTrigger::HasTriggerCountApi() &&
		AjinTrigger->ReadTriggerCount(ScanTriggerChannel(), &lCount)) {
		cnt.nTriggerCount = (int)lCount;
	}
	bool bOut = false;
	if (AjinTrigger->ReadOutputState(ScanTriggerChannel(), &bOut)) {
		cnt.nOutput = bOut ? 1 : 0;
	}
}

int CSeqMain::ScanTriggerClearCounter(int nMode)
{
	if (bit.ScanTriggerRun) {
		printf("[SCANTRIGGER] counter clear refused, the cycle is running\n");
		return SCANTRIGGER_HWCFG_BUSY;
	}
	if (AjinTrigger == NULL || AjinTrigger->GetChannelCount() <= ScanTriggerChannel()) {
		return SCANTRIGGER_HWCFG_RANGE;
	}

	if (nMode == SCANTRIGGER_CNTCLR_TRIGGER_COUNT) {
		if (!AjinTrigger->ClearTriggerCount(ScanTriggerChannel())) {
			return SCANTRIGGER_HWCFG_RANGE;
		}
		g_nScanTriggerLastCount = -1;
		printf("[SCANTRIGGER] trigger count cleared on channel %ld\n", ScanTriggerChannel());
		return SCANTRIGGER_HWCFG_OK;
	}

	if (nMode == SCANTRIGGER_CNTCLR_ENC_TO_AXIS) {
		// Puts the counter in machine coordinates the same way arming does,
		// so the live position can be checked against the motor screen
		// without running a scan.
		CAjinMotor* pAxis = ScanTriggerAxis();
		const double dUnit = ScanTriggerEncUnitMM();
		if (pAxis == NULL || pAxis->MMI_PulseRate == 0 || !(dUnit > 0.0)) {
			return SCANTRIGGER_HWCFG_RANGE;
		}
		const double dAxisMM = (double)pAxis->GetActualPosition() / (double)pAxis->MMI_PulseRate;
		if (!AjinTrigger->ResetScanOrigin(ScanTriggerChannel(), dAxisMM / dUnit)) {
			return SCANTRIGGER_HWCFG_RANGE;
		}
		printf("[SCANTRIGGER] counter set to the axis position, %.4f mm = %.0f counts\n",
			   dAxisMM, dAxisMM / dUnit);
		return SCANTRIGGER_HWCFG_OK;
	}
	return SCANTRIGGER_HWCFG_RANGE;
}
