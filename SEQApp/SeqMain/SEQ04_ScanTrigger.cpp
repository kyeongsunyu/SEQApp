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
static const double SCANTRIGGER_ENC_UNIT_MM = 0.001;       // 1 um

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
static const bool   SCANTRIGGER_ENC_REVERSE = true;

// How far the counter may run the wrong way before the scan is called off,
// in counts. Large enough not to trip on a count of dither at the start.
static const double SCANTRIGGER_WRONG_WAY_COUNTS = 200.0;

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
static const long   SCANTRIGGER_CHANNEL = 0;
static const DWORD  SCANTRIGGER_OUTPORT = 0x1;
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

	const bool bPos   = AjinTrigger->GetActPos(SCANTRIGGER_CHANNEL, &dPos);
	const bool bCount = AjinTrigger->ReadTriggerCount(SCANTRIGGER_CHANNEL, &lCount);
	const bool bOutOk = AjinTrigger->ReadOutputState(SCANTRIGGER_CHANNEL, &bOut);

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
		   dPos, dPos * SCANTRIGGER_ENC_UNIT_MM, bPos ? "" : " (read failed)",
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
	if (!AjinTrigger->ReadOutputState(SCANTRIGGER_CHANNEL, &bOut, &dwRet)) {
		printf("[SCANTRIGGER] trigger output line not readable:"
			   " AxcStatusGetChannel(%ld) returned %lu (%s).\n",
			   SCANTRIGGER_CHANNEL, (unsigned long)dwRet, ScanTriggerAxlError(dwRet));

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
	ScanTriggerDisplay.dPitchCounts = ScanTriggerRecipe.dPitch / SCANTRIGGER_ENC_UNIT_MM;
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
		ScanTriggerDisplay.dPitchAchieved  = dNearest * SCANTRIGGER_ENC_UNIT_MM;
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
	if (AjinTrigger == NULL || AjinTrigger->GetChannelCount() <= SCANTRIGGER_CHANNEL) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_NO_COUNTER;
		return ScanTriggerDisplay.nValidateCode;
	}

	ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_OK;
	return ScanTriggerDisplay.nValidateCode;
}

//////////////////////////////////////////////////////////////////////////
void CSeqMain::ScanTriggerAbort(const char* pszWhy)
{
	if (AjinTrigger != NULL) {
		// Both modes stop the same way - AxcTriggerSetEnable(ch, 0) - but the
		// timer's own flag has to come down with it, or the next cycle starts
		// believing its window is already open.
		AjinTrigger->StopPeriodicTrigger(SCANTRIGGER_CHANNEL);
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
	if (!pAxis->imrs) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_NOT_HOMED;
		printf("[SCANTRIGGER] axis %u has not been homed\n", ScanTriggerRecipe.uAxisNo);
		return;
	}
	if (!pAxis->IsStop) {
		printf("[SCANTRIGGER] axis %u is still moving\n", ScanTriggerRecipe.uAxisNo);
		return;
	}

	g_nScanTriggerState = SCANTRIGGER_GOTO_START;
	ScanTriggerDisplay.nState = g_nScanTriggerState;
	bit.ScanTriggerRun = 1;

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
	if (AjinTrigger == NULL || AjinTrigger->GetChannelCount() <= SCANTRIGGER_CHANNEL) {
		printf("[SCANTRIGGER] output test refused, no counter channel %ld\n",
			   SCANTRIGGER_CHANNEL);
		return;
	}

	// AxcTriggerSetEnable is the final gate in front of the output stage, so the
	// line has to be ENABLED for a forced level to reach the pin. The first
	// version of this test disabled it first and the flat scope it produced
	// said nothing about the wiring. Nothing moves during the test, and
	// periodic mode only fires on encoder movement, so enabling is safe.
	if (!AjinTrigger->BeginOutputTest(SCANTRIGGER_CHANNEL)) {
		printf("[SCANTRIGGER] output test refused, the output stage could not be enabled\n");
		return;
	}
	AjinTrigger->ReportChannelConfig(SCANTRIGGER_CHANNEL, "output test, line enabled");

	g_nScanTriggerTestStep = 0;
	g_bScanTriggerTestHigh = false;
	g_tmScanTriggerTest.SetTime();

	g_nScanTriggerState = SCANTRIGGER_OUTPUT_TEST;
	ScanTriggerDisplay.nState = g_nScanTriggerState;
	g_nScanTriggerLastCount = -1;
	bit.ScanTriggerRun = 1;

	printf("[SCANTRIGGER] output self test on channel %ld : %d pulses, %lld ms high"
		   " and %lld ms low. Probe CON1 pin 1-2 now; the stage does not move.\n",
		   SCANTRIGGER_CHANNEL, SCANTRIGGER_TEST_PULSES,
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
			AjinTrigger->PulseBurst(SCANTRIGGER_CHANNEL,
									SCANTRIGGER_TEST_BURST_PULSES,
									SCANTRIGGER_TEST_BURST_HZ);

			AjinTrigger->EndOutputTest(SCANTRIGGER_CHANNEL);
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
		const bool bSet = AjinTrigger->ForceOutput(SCANTRIGGER_CHANNEL, g_bScanTriggerTestHigh);

		// Read the line back the way the board sees it, so the log stands on
		// its own when nobody has a scope on the connector. On a board that
		// refuses AxcStatusGetChannel there is nothing to read and the scope is
		// the whole test, which is said once at the start rather than as "n/a"
		// against every pulse.
		bool bSeen = false;
		const bool bRead = AjinTrigger->ReadOutputState(SCANTRIGGER_CHANNEL, &bSeen);

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
		if (!AjinTrigger->ResetScanOrigin(SCANTRIGGER_CHANNEL,
										  ScanTriggerDisplay.dMotionStart / SCANTRIGGER_ENC_UNIT_MM)) {
			ScanTriggerAbort("could not preset the counter position");
			break;
		}

		PERIODIC_TRIG_CFG cfg;
		cfg.lChannelNo       = SCANTRIGGER_CHANNEL;
		cfg.dwEncoderInput   = (DWORD)SCANTRIGGER_CHANNEL;
		cfg.dwTriggerOutPort = SCANTRIGGER_OUTPORT;
		cfg.dMoveUnitPerPulse= SCANTRIGGER_ENC_UNIT_MM;
		cfg.dPitch           = ScanTriggerDisplay.dPitchAchieved;
		cfg.dScanStart       = ScanTriggerDisplay.dTrigStart;
		cfg.dScanEnd         = ScanTriggerDisplay.dTrigEnd;
		cfg.dPulseWidthUS    = ScanTriggerPulseWidthUS();
		cfg.dLineRateHz      = ScanTriggerDisplay.dLineRate;
		// Timer mode only: the board stops itself after this many pulses, so
		// the number of lines is exact however late the cycle closes the
		// window. Ignored by the periodic path, which gets its end from the
		// block.
		cfg.lTriggerCount    = ScanTriggerDisplay.nLineCount;
		cfg.dwTriggerLevel   = 1;
		cfg.dwDirectionCheck = 1;          // count up only, the scan direction
		cfg.bEncReverse      = SCANTRIGGER_ENC_REVERSE;

		g_bScanTriggerTimerOn    = false;
		g_dScanTriggerTimerOnAt  = 0.0;
		g_dScanTriggerTimerOffAt = 0.0;

		if (ScanTriggerIsTimerMode()) {
			// Configured but not started: the pulse train free runs, so
			// enabling it here would fire it all the way in from the approach.
			// The counter is still preset and still read, but only so this
			// cycle can open the window at dTrigStart and close it at dTrigEnd
			// - which is the guarantee this mode gives up.
			if (!AjinTrigger->StartTimerTrigger(cfg)) {
				ScanTriggerAbort("StartTimerTrigger refused the configuration");
				break;
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
		AjinTrigger->ClearTriggerCount(SCANTRIGGER_CHANNEL);
		g_dScanTriggerEncArm = 0.0;
		AjinTrigger->GetActPos(SCANTRIGGER_CHANNEL, &g_dScanTriggerEncArm);
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
			const bool bGotPos = AjinTrigger->GetActPos(SCANTRIGGER_CHANNEL, &dNow);

			if (bGotPos && (dNow - g_dScanTriggerEncArm) < -SCANTRIGGER_WRONG_WAY_COUNTS) {
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
				const double dPosMM = dNow * SCANTRIGGER_ENC_UNIT_MM;

				if (!g_bScanTriggerTimerOn) {
					if (dPosMM >= ScanTriggerDisplay.dTrigStart &&
						dPosMM <  ScanTriggerDisplay.dTrigEnd) {
						if (AjinTrigger->SetTimerRunning(SCANTRIGGER_CHANNEL, true)) {
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
				else if (dPosMM >= ScanTriggerDisplay.dTrigEnd) {
					// The board has already stopped itself at the programmed
					// pulse count by now. Switching it off here is what keeps
					// a miscount from running on past the block, and costs
					// nothing when there was not one.
					AjinTrigger->SetTimerRunning(SCANTRIGGER_CHANNEL, false);
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
			AjinTrigger->SetTimerRunning(SCANTRIGGER_CHANNEL, false);
			g_bScanTriggerTimerOn = false;
			if (AjinTrigger->GetActPos(SCANTRIGGER_CHANNEL, &dNow)) {
				g_dScanTriggerTimerOffAt = dNow * SCANTRIGGER_ENC_UNIT_MM;
			}
		}

		long lCount = 0;
		g_nScanTriggerLastCount =
			AjinTrigger->ReadTriggerCount(SCANTRIGGER_CHANNEL, &lCount) ? (int)lCount : -1;
		ScanTriggerDisplay.nTriggerCount = g_nScanTriggerLastCount;

		// Read everything back before the trigger is switched off, so what is
		// printed is the state the scan actually ran with.
		ScanTriggerLogCounter("end");
		AjinTrigger->ReportChannelConfig(SCANTRIGGER_CHANNEL, "end of scan");

		double dEncEnd = 0.0;
		if (AjinTrigger->GetActPos(SCANTRIGGER_CHANNEL, &dEncEnd)) {
			const double dEncTravel = (dEncEnd - g_dScanTriggerEncArm) * SCANTRIGGER_ENC_UNIT_MM;
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

				// The one measurement timer mode does allow.
				//
				// The encoder cannot set the pitch here, but it can still say
				// what the pitch turned out to be: the board emitted a known
				// number of pulses and the counter says how far the stage went
				// while it did. Dividing one by the other gives the mean pitch
				// actually achieved - and because the division is over a whole
				// scan, one encoder count of uncertainty spreads across every
				// line, so a 100 mm scan at this pitch resolves the mean to
				// well under a nanometre.
				//
				// This is what stands in for the trigger count readback this
				// AXL does not have, and it measures the thing that actually
				// matters in this mode: whether the stage held its speed.
				const double dLines = dSpanMM / ScanTriggerDisplay.dPitchAchieved;
				if (dLines >= 1.0) {
					const double dMeasuredMM = dSpanMM / dLines;
					printf("[SCANTRIGGER]  measured mean pitch %.6f um against the"
						   " %.6f um asked for, %+.2f nm (%+.4f %%) - this is the"
						   " stage's speed holding, which is the only thing setting"
						   " the pitch in this mode\n",
						   dMeasuredMM * 1000.0,
						   ScanTriggerDisplay.dPitchAchieved * 1000.0,
						   (dMeasuredMM - ScanTriggerDisplay.dPitchAchieved) * 1.0e6,
						   (dMeasuredMM / ScanTriggerDisplay.dPitchAchieved - 1.0) * 100.0);
				}
			}

			AjinTrigger->StopTimerTrigger(SCANTRIGGER_CHANNEL);
		}
		else {
			AjinTrigger->StopPeriodicTrigger(SCANTRIGGER_CHANNEL);
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
