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
// Bounds on the pulse width the operator enters. The floor is the shortest
// pulse a camera input can be relied on to see at all; the ceiling is a
// fraction of the line period, so the output cannot end up high for more of
// the line than it is low.
static const double SCANTRIGGER_PULSE_MIN_US   = 1.0;
static const double SCANTRIGGER_PULSE_MAX_DUTY = 0.4;

// Used only when the recipe carries nothing, which is what a database written
// before the pulse width was an entered value looks like.
static const double SCANTRIGGER_PULSE_DEFAULT_US = 10.0;

// A scan longer than this is a data entry mistake, not a recipe.
static const int    SCANTRIGGER_MAX_LINES = 2000000;

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

	char szCount[32];
	if (bCount) {
		sprintf(szCount, "%ld", lCount);
	}
	else {
		strcpy(szCount, "n/a");
	}

	printf("[SCANTRIGGER] %-8s enc %.0f counts = %.4f mm%s  triggers %s  out %s\n",
		   (pszWhen != NULL) ? pszWhen : "",
		   dPos, dPos * SCANTRIGGER_ENC_UNIT_MM, bPos ? "" : " (read failed)",
		   szCount,
		   bOutOk ? (bOut ? "HIGH" : "low") : "n/a");
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
	ScanTriggerDisplay.dSpeed       = ScanTriggerRecipe.dSpeed;
	ScanTriggerDisplay.dLineRate    = ScanTriggerDisplay.dSpeed / ScanTriggerRecipe.dPitch;
	ScanTriggerDisplay.dScanTime    = dLength / ScanTriggerDisplay.dSpeed;
	ScanTriggerDisplay.nLineCount   = (int)(dLength / ScanTriggerRecipe.dPitch + 0.5);

	// The comparator counts whole encoder counts. A fractional pitch is
	// rounded, and that error repeats for the whole scan rather than
	// cancelling out.
	ScanTriggerDisplay.dPitchCounts = ScanTriggerRecipe.dPitch / SCANTRIGGER_ENC_UNIT_MM;
	const double dNearest = floor(ScanTriggerDisplay.dPitchCounts + 0.5);
	ScanTriggerDisplay.bPitchIsInteger =
		(dNearest >= 1.0 &&
		 fabs(ScanTriggerDisplay.dPitchCounts - dNearest) <= dNearest * 1e-6);

	if (!ScanTriggerDisplay.bPitchIsInteger) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_PITCH_FRACTION;
		return ScanTriggerDisplay.nValidateCode;
	}
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
		AjinTrigger->StopPeriodicTrigger(SCANTRIGGER_CHANNEL);
	}

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

	printf("[SCANTRIGGER] pitch %.4f mm (%.0f counts), %.1f mm/s -> %.0f Hz,"
		   " %.2f us pulse, %d lines, %.3f s\n",
		   ScanTriggerRecipe.dPitch, ScanTriggerDisplay.dPitchCounts,
		   ScanTriggerDisplay.dSpeed, ScanTriggerDisplay.dLineRate,
		   ScanTriggerPulseWidthUS(), ScanTriggerDisplay.nLineCount, ScanTriggerDisplay.dScanTime);

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
		// its own when nobody has a scope on the connector.
		bool bSeen = false;
		const bool bRead = AjinTrigger->ReadOutputState(SCANTRIGGER_CHANNEL, &bSeen);

		if (g_bScanTriggerTestHigh) {
			printf("[SCANTRIGGER] test pulse %d/%d : driven HIGH%s, board reports %s\n",
				   (g_nScanTriggerTestStep / 2) + 1, SCANTRIGGER_TEST_PULSES,
				   bSet ? "" : " (AxcTriggerSetOutput REFUSED)",
				   bRead ? (bSeen ? "HIGH" : "low") : "n/a");
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
		cfg.dPitch           = ScanTriggerRecipe.dPitch;
		cfg.dScanStart       = ScanTriggerDisplay.dTrigStart;
		cfg.dScanEnd         = ScanTriggerDisplay.dTrigEnd;
		cfg.dPulseWidthUS    = ScanTriggerPulseWidthUS();
		cfg.dLineRateHz      = ScanTriggerDisplay.dLineRate;
		cfg.dwTriggerLevel   = 1;
		cfg.dwDirectionCheck = 1;          // count up only, the scan direction
		cfg.bEncReverse      = SCANTRIGGER_ENC_REVERSE;

		if (!AjinTrigger->StartPeriodicTrigger(cfg)) {
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
			if (AjinTrigger->GetActPos(SCANTRIGGER_CHANNEL, &dNow) &&
				(dNow - g_dScanTriggerEncArm) < -SCANTRIGGER_WRONG_WAY_COUNTS) {
				ScanTriggerAbort("the counter is running away from the block;"
								 " the encoder direction is inverted");
				break;
			}
		}

		if (pAxis->IsStop) {
			g_nScanTriggerState = SCANTRIGGER_DISARM;
		}
		break;

	case SCANTRIGGER_DISARM:
	{
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

		AjinTrigger->StopPeriodicTrigger(SCANTRIGGER_CHANNEL);
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
				   " (this AXL has no AxcTriggerReadTriggerCount)\n",
				   ScanTriggerDisplay.nLineCount);
		}
		printf("[SCANTRIGGER] parked at the scan start position, %.3f mm\n",
			   ScanTriggerDisplay.dMotionStart);

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
