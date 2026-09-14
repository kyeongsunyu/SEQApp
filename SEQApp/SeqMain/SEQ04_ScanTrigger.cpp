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
static const double SCANTRIGGER_ENC_UNIT_MM = 0.0001;      // 0.1 um

// Counter channel and trigger output the camera is wired to.
static const long   SCANTRIGGER_CHANNEL = 0;
static const DWORD  SCANTRIGGER_OUTPORT = 0x1;
static const double SCANTRIGGER_PULSE_US = 2.0;       // camera minimum is 1.0

// A scan longer than this is a data entry mistake, not a recipe.
static const int    SCANTRIGGER_MAX_LINES = 2000000;

// How long the axis must read stopped before the trigger is armed. Guards
// against arming while the stage is still ringing down.
static const LONGLONG SCANTRIGGER_SETTLE_MS = 200;

static int       g_nScanTriggerState = SCANTRIGGER_IDLE;
static CRtTimer  g_tmScanTriggerSettle;

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
	ScanTriggerDisplay.nTriggerCount = -1;
	ScanTriggerDisplay.dLineRate = ScanTriggerRecipe.dLineRate;

	CAjinMotor* pAxis = ScanTriggerAxis();
	if (pAxis == NULL) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_AXIS;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (ScanTriggerRecipe.dPitch <= 0.0) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_PITCH;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (ScanTriggerRecipe.dLineRate <= 0.0) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_LINERATE;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (ScanTriggerRecipe.dTrigEnd <= ScanTriggerRecipe.dTrigStart) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_RANGE;
		return ScanTriggerDisplay.nValidateCode;
	}

	const double dLength = ScanTriggerRecipe.dTrigEnd - ScanTriggerRecipe.dTrigStart;

	ScanTriggerDisplay.dSpeed       = ScanTriggerRecipe.dPitch * ScanTriggerRecipe.dLineRate;
	ScanTriggerDisplay.dScanTime    = dLength / ScanTriggerDisplay.dSpeed;
	ScanTriggerDisplay.dMotionStart = ScanTriggerRecipe.dTrigStart;
	ScanTriggerDisplay.dMotionEnd   = ScanTriggerRecipe.dTrigEnd;
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
	if (pAxis->MMI_PulseRate == 0) {
		// Without it mm cannot be converted to the pulses the axis moves in.
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_PULSERATE;
		return ScanTriggerDisplay.nValidateCode;
	}
	if (ScanTriggerDisplay.dSpeed * (double)pAxis->MMI_PulseRate > (double)pAxis->MaxSpeed) {
		ScanTriggerDisplay.nValidateCode = SCANTRIGGER_VALIDATE_SPEED;
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

	printf("[SCANTRIGGER] start %.4f -> %.4f mm, pitch %.4f mm (%.0f counts),"
		   " %.0f Hz, %.1f mm/s, %d lines, %.3f s\n",
		   ScanTriggerRecipe.dTrigStart, ScanTriggerRecipe.dTrigEnd, ScanTriggerRecipe.dPitch,
		   ScanTriggerDisplay.dPitchCounts, ScanTriggerRecipe.dLineRate, ScanTriggerDisplay.dSpeed,
		   ScanTriggerDisplay.nLineCount, ScanTriggerDisplay.dScanTime);

	sprintf(strFileLog, "Scan start %.4f to %.4f mm, %d lines",
			ScanTriggerRecipe.dTrigStart, ScanTriggerRecipe.dTrigEnd, ScanTriggerDisplay.nLineCount);
	LOG_TRACE(strFileLog);
}

//////////////////////////////////////////////////////////////////////////
void CSeqMain::ScanTriggerC(void)
{
	if (!bit.ScanTriggerRun) return;

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
		pAxis->MTSAMove((int)(ScanTriggerRecipe.dTrigStart * dRate + 0.5));
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
		if (!AjinTrigger->ResetScanOrigin(SCANTRIGGER_CHANNEL, ScanTriggerRecipe.dTrigStart)) {
			ScanTriggerAbort("could not preset the counter position");
			break;
		}

		PERIODIC_TRIG_CFG cfg;
		cfg.lChannelNo       = SCANTRIGGER_CHANNEL;
		cfg.dwEncoderInput   = (DWORD)SCANTRIGGER_CHANNEL;
		cfg.dwTriggerOutPort = SCANTRIGGER_OUTPORT;
		cfg.dMoveUnitPerPulse= SCANTRIGGER_ENC_UNIT_MM;
		cfg.dPitch           = ScanTriggerRecipe.dPitch;
		cfg.dScanStart       = ScanTriggerRecipe.dTrigStart;
		cfg.dScanEnd         = ScanTriggerRecipe.dTrigEnd;
		cfg.dPulseWidthUS    = SCANTRIGGER_PULSE_US;
		cfg.dwTriggerLevel   = 1;
		cfg.dwDirectionCheck = 1;          // count up only, the scan direction
		cfg.bEncReverse      = false;

		if (!AjinTrigger->StartPeriodicTrigger(cfg)) {
			ScanTriggerAbort("StartPeriodicTrigger refused the configuration");
			break;
		}
		g_nScanTriggerState = SCANTRIGGER_RUN;
		break;
	}

	case SCANTRIGGER_RUN:
		pAxis->Speed = ScanTriggerDisplay.dSpeed * dRate;
		pAxis->Accel = fabs(pAxis->Speed * 5);
		pAxis->Decel = pAxis->Accel;
		pAxis->MTSAMove((int)(ScanTriggerRecipe.dTrigEnd * dRate + 0.5));
		g_nScanTriggerState = SCANTRIGGER_WAIT_END;
		break;

	case SCANTRIGGER_WAIT_END:
		if (pAxis->IsStop) {
			g_nScanTriggerState = SCANTRIGGER_DISARM;
		}
		break;

	case SCANTRIGGER_DISARM:
	{
		long lCount = 0;
		// Only a newer AXL can read the trigger counter back; on this one the
		// call reports failure and the count stays unknown.
		ScanTriggerDisplay.nTriggerCount =
			AjinTrigger->ReadTriggerCount(SCANTRIGGER_CHANNEL, &lCount) ? (int)lCount : -1;

		AjinTrigger->StopPeriodicTrigger(SCANTRIGGER_CHANNEL);
		g_nScanTriggerState = SCANTRIGGER_DONE;
		break;
	}

	case SCANTRIGGER_DONE:
		bit.ScanTriggerRun = 0;
		if (ScanTriggerDisplay.nTriggerCount >= 0) {
			printf("[SCANTRIGGER] finished, %d triggers (expected %d)\n",
				   ScanTriggerDisplay.nTriggerCount, ScanTriggerDisplay.nLineCount);
		}
		else {
			printf("[SCANTRIGGER] finished, expected %d triggers"
				   " (counter read back not available)\n", ScanTriggerDisplay.nLineCount);
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
