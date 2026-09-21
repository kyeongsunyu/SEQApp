#include "..\pch.h"
#include "CLASS_AjinMotor.h"
#include "..\SeqMain\DEFINE_GVX.h"
#include "..\Tools\CLASS_INI.h"

extern DWORD	AxmTriggerSetBlockByEvent(long lAxisNo, DWORD dwEventSignal, double dPeriod, double dTrigTime, long lTrigLevel, DWORD dwSelect, DWORD dwOnce);

// Where the machine configuration lives. The ANSI copy of the directory is
// separate only because the console diagnostics below go through printf.
static const TCHAR* const CONFIG_INI_PATH  = _T("C:/WORK/Config.ini");
static const char*  const CONFIG_DIR_ANSI  = "C:\\WORK";
static const char*  const CONFIG_INI_ANSI  = "C:\\WORK\\Config.ini";

// Renders a Win32 error code as text, so a failure says what went wrong
// instead of only which number came back. Always returns pszBuf.
static const char* Win32ErrText(DWORD dwErr, char* pszBuf, DWORD dwBufLen)
{
	if (pszBuf == NULL || dwBufLen == 0)
		return "";

	pszBuf[0] = '\0';
	DWORD dwLen = ::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								   NULL, dwErr, 0, pszBuf, dwBufLen, NULL);

	// FormatMessage ends its text with CRLF, which would split the log line.
	while (dwLen > 0 && (pszBuf[dwLen - 1] == '\r' || pszBuf[dwLen - 1] == '\n'))
		pszBuf[--dwLen] = '\0';

	return pszBuf;
}


//////////////////////////////////////////////////////////////////////////
CAjinBase::CAjinBase():address(0),axis(0),output(0)
{
	bct2dMode = FALSE;
}
CAjinBase::~CAjinBase()
{
	AxlClose();
}

unsigned short int CAjinBase::Isct2dMode()
{
	return bct2dMode;
}


// ---------------------------------------------------------------------------
// Motion hardware type, resolved once from Config.ini.
//
// CAjinBase is not the only class that needs to know how this machine is
// built, and it is not always the first one constructed. Keeping the answer
// here means every caller gets the same value no matter the construction
// order, and the file is read once instead of once per class.
// ---------------------------------------------------------------------------
static BOOL g_bMotionTypeResolved = FALSE;
static BOOL g_bPulseType          = TRUE;   // matches the MotionType=1 default
static int  g_nMotionType         = 1;

static void ResolveMotionType()
{
	if (g_bMotionTypeResolved) {
		return;
	}
	g_bMotionTypeResolved = TRUE;

	// WritePrivateProfileString() creates the file but never the directory it
	// sits in, so on a machine without C:\WORK the first-run write failed and no
	// Config.ini ever appeared - silently, because nobody read the result.
	char szErr[256] = { 0 };
	if (!::CreateDirectoryA(CONFIG_DIR_ANSI, NULL)) {
		DWORD dwErr = ::GetLastError();
		if (dwErr != ERROR_ALREADY_EXISTS) {
			printf("[AXL] cannot create %s : error %lu (%s)\n",
				   CONFIG_DIR_ANSI, dwErr, Win32ErrText(dwErr, szErr, sizeof(szErr)));
			printf("[AXL] the config file cannot be written there;"
				   " create the folder by hand, or run elevated\n");
		}
	}
	else {
		printf("[AXL] created %s\n", CONFIG_DIR_ANSI);
	}

	CIni Ini(CONFIG_INI_PATH);
	int nMotionType = 1;
	if (Ini.IsKeyExist(_T("HARDWARE"), _T("MotionType"))) {
		nMotionType = Ini.GetInt(_T("HARDWARE"), _T("MotionType"), 1);
	}
	else {
		// First run on this machine: write the default back so the setting is
		// visible in the file rather than hidden in the binary.
		::SetLastError(ERROR_SUCCESS);
		if (Ini.WriteInt(_T("HARDWARE"), _T("MotionType"), nMotionType)) {
			printf("[AXL] Config.ini [HARDWARE] MotionType was missing;"
				   " defaulted to %d and written back\n", nMotionType);
		}
		else {
			DWORD dwErr = ::GetLastError();
			printf("[AXL] could not write [HARDWARE] MotionType to %s : error %lu (%s)\n",
				   CONFIG_INI_ANSI, dwErr,
				   Win32ErrText(dwErr, szErr, sizeof(szErr)));
			printf("[AXL] continuing with the built in default MotionType=%d;"
				   " the setting stays invisible until the file can be written\n",
				   nMotionType);
		}
	}

	g_nMotionType = nMotionType;
	g_bPulseType  = (nMotionType != 0) ? TRUE : FALSE;
	printf("[AXL] hardware type : %s  ([HARDWARE] MotionType=%d)\n",
		   g_bPulseType ? "ct2d / pulse" : "EtherCAT", g_nMotionType);
}

BOOL AxlIsPulseTypeMachine()
{
	ResolveMotionType();
	return g_bPulseType;
}

void CAjinBase::InitBase()
{
	const long lIrqNo = 7;

	// How the machine is built and whether the library came up are different
	// questions. Deriving the hardware type from AxlOpen()'s result conflated
	// them: a driver that never loaded looked exactly like a pulse system, and
	// once the open started succeeding the same code would have called this an
	// EtherCAT machine. So the type comes from configuration.
	//
	//   [HARDWARE] MotionType = 0  EtherCAT node network
	//                         = 1  pulse train (ct2d)   <- default

	bct2dMode = AxlIsPulseTypeMachine();

	// Which AXL.dll actually got loaded, and what version it is. Copies exist in
	// the output folder, in System32 and in the installed SDK, so the loader's
	// choice is not obvious - and a DLL whose SHM version does not match the
	// running EzManager reports AXT_RT_NOT_RUN_EZMANAGER (1057) even while
	// EzManager is up.
	HMODULE hAxl = ::GetModuleHandleA("AXL.dll");
	if (hAxl != NULL) {
		char szPath[MAX_PATH] = { 0 };
		if (::GetModuleFileNameA(hAxl, szPath, MAX_PATH) > 0) {
			printf("[AXL] module  : %s\n", szPath);
		}
	}

	char szVer[64] = { 0 };
	DWORD dwVer = AxlGetLibVersion(szVer);
	if (dwVer == AXT_RT_SUCCESS) {
		printf("[AXL] version : %s\n", szVer);
	}
	else {
		printf("[AXL] AxlGetLibVersion() failed, code %lu (0x%lx)\n", dwVer, dwVer);
	}

	// AxlOpen() resets the hardware chip; AxlOpenNoReset() skips that. Try both
	// before giving up - neither changes the hardware type decided above.
	DWORD dwCode = AxlOpen(lIrqNo);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXL] AxlOpen(%ld) returned %lu (0x%lx), retrying with"
			   " AxlOpenNoReset()\n", lIrqNo, dwCode, dwCode);
		dwCode = AxlOpenNoReset(lIrqNo);
	}

	if (dwCode == AXT_RT_SUCCESS) {
		long lAxisCount = 0;
		DWORD dwAxis = AxmInfoGetAxisCount(&lAxisCount);
		if (dwAxis == AXT_RT_SUCCESS) {
			printf("[AXL] open OK (IRQ %ld) - %ld axis available\n",
				   lIrqNo, lAxisCount);
		}
		else {
			printf("[AXL] open OK (IRQ %ld) - AxmInfoGetAxisCount() failed,"
				   " code 0x%lx\n", lIrqNo, dwAxis);
		}
		return;
	}

	printf("[AXL] open FAILED, code %lu (0x%lx)\n", dwCode, dwCode);

	// A closed library is a fault, not a hardware type: every AXL call then
	// returns AXT_RT_NOT_OPEN (1053) and no board is reachable either way.
	if (!AxlIsOpened()) {
		printf("[AXL] WARNING: library is NOT open - every AXL call will fail with"
			   " 1053 (AXT_RT_NOT_OPEN).\n");
		if (dwCode == 1057) {   // AXT_RT_NOT_RUN_EZMANAGER
			printf("      1057 = EzManager not running. If EzManager IS running,"
				   " the AXL.dll listed\n"
				   "      above does not match it - AXL and EzManager handshake"
				   " through shared memory\n"
				   "      and the SHM versions must agree. Compare its version with"
				   " the EzSoftware\n"
				   "      installation under Program Files.\n");
		}
		else {
			printf("      Check the AXL driver installation, board detection in"
				   " Device Manager,\n"
				   "      whether another process holds the boards, and IRQ %ld.\n",
				   lIrqNo);
		}
	}
}
DWORD CAjinBase::GetModuleNodeStatus(long lBoardNo, long lModulePos)
{
	if (bct2dMode) {
		return 0;
	}

	return AxlGetModuleNodeStatus(lBoardNo, lModulePos);
}

DWORD CAjinBase::ReadInportFallback(long lOffset, DWORD* upValue)
{
	if (upValue == NULL) {
		return 0;
	}

	if (bct2dMode) {
		*upValue = 0;
		return 0;
	}

	return AxdiReadInport(lOffset, upValue);
}

void CAjinBase::ReadECATPdoInput(DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData)
{
	if (bct2dMode) {
		DWORD bytes = (dwDataBitLength + 7) / 8;
		if (pbyData && bytes) {
			memset(pbyData, 0, bytes);
		}
		return;
	}

	AxlECatReadPdoInput(dwBitOffset, dwDataBitLength, pbyData);
}

DWORD CAjinBase::WriteOutportFallback(long lOffset, DWORD dwValue)
{
	if (bct2dMode) {
		return 0;
	}

	return AxdoWriteOutportDword((unsigned short int)(lOffset / 2), (unsigned short int)(lOffset % 2), dwValue);
}

void CAjinBase::WriteECATPdoOutput(DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData)
{
	if (bct2dMode) {
		(void)dwBitOffset;
		(void)dwDataBitLength;
		(void)pbyData;
		return;
	}

	AxlECatWritePdoOutput(dwBitOffset, dwDataBitLength, pbyData);
}
//////////////////////////////////////////////////////////////////////////

CAjinMotor::CAjinMotor(unsigned short int axs_no, unsigned short int logical_no)
{
	// Everything below used to be left as whatever was on the heap: this
	// constructor set three members out of eighty, and the rest were filled in
	// by InitMotor(). That works only for an axis InitMotor() reaches, and it
	// loops j = 1..totalAxisCnt. An axis built as an object but left out of
	// that count - the second one on this machine - kept its indeterminate
	// state for the whole run.
	//
	// GetMotorStatus() then reads it every millisecond:
	//
	//     if (err || fMotorPause || fDriving) IsDriving = true;
	//
	// and fDriving coming up non-zero pins IsDriving on regardless of what the
	// board says. IsDriving is what the MMI shows as MOVING, which is why the
	// second axis came up moving and stayed that way.

	memset(&MS, 0, sizeof(MS));

	SensorType = 0;
	MotorType  = 0;

	ActualPosition  = 0;
	CommandPosition = 0;
	SpeedDevide     = 1;
	MinMovingTime   = 0;
	AxisNO          = axs_no;
	AxisLogicNO     = logical_no;
	sHomeState      = 0;
	CancelCmd       = 0;
	CmdMode         = 0;

	Speed = Accel = Decel = Jerk = 0.0;
	SaveSpeed = SaveAccel = SaveJerk = 0.0;
	InitSpeed = 0.0;
	MaxSpeed  = 0.0;

	CurPos = NxtPos = 0;
	WorkPos = DfltWorking = 0;

	bOverRide     = false;
	OverRidePos   = 0.0;
	OverRideRatio = 0.0;

	// The flags, which are what actually caused the trouble. An axis with no
	// drive behind it must read as stopped and idle, not as moving.
	fDoHome = fIMRS = fMotorPause = fMotorHome = fDriving = 0;
	IsHWLimitCW = IsHWLimitCCW = IsDRVRDY = IsORG = IsAlarm = 0;
	IsInposition = IsServoOn = PrevIsServoOn = 0;
	IsDriving = 0;
	IsStop    = 1;
	IsZPhase = EncoderSet = AlramReset = EncoderType = IsHomming = 0;
	omove = moving = relative = 0;
	imrs = irdy = isend = idrvalm = idrvrdy = canmovejog = ostart = 0;
	bStatusReadFailed = 0;

	ZPhaseSpeed = NULL;
	HomeSpeed   = NULL;

	MovingDistance = 0.0;
	TimeDesier     = 0.0;
	AdjustPosition = 0;
	CurArrpos      = 0.0;
	NxtArrpos      = 0.0;
	Direction      = 0;

	memset(PositionArray, 0, sizeof(PositionArray));
	memset(SpeedArray,    0, sizeof(SpeedArray));
	memset(AccelArray,    0, sizeof(AccelArray));
	memset(DecelArray,    0, sizeof(DecelArray));

	bCwLimitLevel = bCCwLimitLevel = bServoOnLevel = bAlarmLevel = 0;
	bInpLevel = bInpEnable = 0;
	nPulseOutM = nEncDir = nEncType = nMotorType = nSensorType = 0;

	MMI_PulseRate = MMI_MaxVel = MMI_JogVel = MMI_HomeVel = MMI_Accel = 0;
	MMI_HomeLevel = MMI_LimitLevel = MMI_ServoOnLevel = MMI_AlarmLevel = 0;
	MMI_InpUse = MMI_MtrDir = MMI_EncDir = MMI_MotorType = MMI_Enc_Type = 0;

	bCamType = 0;

	dwServoAlarmCode = 0;
	strServoAlarmName[0] = '\0';
	dServoLoadRatio  = 0.0;

	dwBitOffset      = 0;
	dwDataBitLength  = 0;
	byTorqueValue    = 0;
}

// Destructor Function
CAjinMotor::~CAjinMotor()
{

}

long CAjinMotor::GetTotalAxisCount()
{
	long cnt;
	AxmInfoGetAxisCount(&cnt);
	return cnt;
}

void CAjinMotor::SetCommandPosition(int Position)
{
	// AxmStatusSetPosMatch() is marked "Only RTEX use" in AXM.h. This machine
	// is a pulse (ct2d) system, so that call could not set anything and the
	// counter was never cleared at the end of a home.
	DWORD dwCode = AxmStatusSetCmdPos(AxisNO, (double)Position);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXM] axis %ld : AxmStatusSetCmdPos(%d) failed, code %lu\n",
			   (long)AxisNO, Position, dwCode);
	}
}

int CAjinMotor::GetCommandPosition()
{
	double d_CommandPosition = 0;
	AxmStatusGetCmdPos(AxisNO, &d_CommandPosition);
	CommandPosition = (int)d_CommandPosition;
	return CommandPosition;
}

void CAjinMotor::SetActualPosition(int Position)
{
	// Same reason as SetCommandPosition().
	DWORD dwCode = AxmStatusSetActPos(AxisNO, (double)Position);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXM] axis %ld : AxmStatusSetActPos(%d) failed, code %lu\n",
			   (long)AxisNO, Position, dwCode);
	}
}

int CAjinMotor::GetActualPosition()
{
	if (!EncoderType) {
		// No encoder - see GetMotorStatus(). Keep ActualPosition in step too,
		// since callers read the member as well as the return value.
		ActualPosition = GetCommandPosition();
		return ActualPosition;
	}

	double d_ActualPosition = 0;
	AxmStatusGetActPos(AxisNO, &d_ActualPosition);
	ActualPosition = (int)d_ActualPosition;
	return ActualPosition;
}

void CAjinMotor::MTStop()
{
	AxmMoveStop(AxisNO, 700 * (double)MMI_PulseRate * 10);	// ������, Ŭ���� ���� ����
}

void CAjinMotor::MTEStop()
{
	AxmMoveEStop(AxisNO);
}

void CAjinMotor::SetHWLimitMode(DWORD CW_LogicLevel, DWORD CCW_LogicLevel)
{
	AxmSignalSetLimit(AxisNO, EMERGENCY_STOP, CW_LogicLevel, CCW_LogicLevel);
}

void CAjinMotor::SetSWLimitMode(bool Enable)
{
	AxmSignalSetSoftLimit(AxisNO, Enable, EMERGENCY_STOP, COMMAND, 0, 0);
}

void CAjinMotor::SetInpositionMode(DWORD LogicLevel, DWORD Enable)
{
	// AXM.h: AxmSignalSetInpos(lAxisNo, uUse) takes LOW(0), HIGH(1),
	// UNUSED(2) or USED(3) - one argument that carries both the level and
	// whether the signal is used at all.
	//
	// The old line passed Enable into that slot and threw LogicLevel away, so
	// MotorConfig.xml's InpL never reached the board and InpE=0 asked for
	// "in position, active low" instead of "do not use in position".
	const DWORD IN_POS_UNUSED = 2;
	DWORD uUse = (Enable != 0) ? ((LogicLevel != 0) ? 1u : 0u) : IN_POS_UNUSED;

	DWORD dwCode = AxmSignalSetInpos(AxisNO, uUse);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXM] axis %ld : AxmSignalSetInpos(%lu) failed, code %lu\n",
			   (long)AxisNO, uUse, dwCode);
	}
}

void CAjinMotor::SetAlarmEnable(int Enable)
{
	// AXM.h: AxmSignalSetServoAlarm(lAxisNo, uUse) takes LOW(0), HIGH(1),
	// UNUSED(2) or USED(3) - one argument carrying both the active level and
	// whether an alarm stops the axis at all. MotorConfig.xml's AlmL is written
	// straight into it, so AlmL=2 is how a drive with no usable alarm output is
	// told to stop asserting one.
	const DWORD ALARM_UNUSED = 2;
	DWORD uUse = (DWORD)Enable;

	if (uUse > 3) {
		printf("[AXM] axis %ld : AlmL=%d is outside LOW(0)/HIGH(1)/UNUSED(2)/"
			   "USED(3); the alarm is left unused\n", (long)AxisNO, Enable);
		uUse = ALARM_UNUSED;
	}

	DWORD dwCode = AxmSignalSetServoAlarm(AxisNO, uUse);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXM] axis %ld : AxmSignalSetServoAlarm(%lu) failed, code %lu\n",
			   (long)AxisNO, uUse, dwCode);
	}
}

void CAjinMotor::SetAlarmClearOn()
{
	AxmSignalServoAlarmReset(AxisNO, TRUE);
}

void CAjinMotor::SetAlarmClearOff()
{
	AxmSignalServoAlarmReset(AxisNO, FALSE);
}

void CAjinMotor::SetPulseMode(int mode)
{
	// AXM.h: uMethod 0..9. 0-3 are the one pulse (PULSE + DIR) forms, 4-7 the
	// two pulse (CW/CCW) forms, 8-9 the two phase forms. A value outside that
	// range is rejected by the library, and the axis then keeps whatever pulse
	// form it had - which is how an axis ends up running backwards.
	if (mode < 0 || mode > 9) {
		printf("[AXM] axis %ld : pulse out method %d is outside the documented"
			   " range 0..9, ignored\n", (long)AxisNO, mode);
		return;
	}

	DWORD dwCode = AxmMotSetPulseOutMethod(AxisNO, (DWORD)mode);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXM] axis %ld : AxmMotSetPulseOutMethod(%d) failed, code %lu\n",
			   (long)AxisNO, mode, dwCode);
	}
}

// Encoder �Է¹�� ����, Sqr4Mode=4ü�� 
void CAjinMotor::SetEncoderInputMethos(unsigned char method)
{
	// AXM.h: 0..3 obverse (1x/2x/4x), 4..7 reverse. Sets both the counting
	// method and the direction in which the actual position increases.
	DWORD dwCode = AxmMotSetEncInputMethod(AxisNO, method);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXM] axis %ld : AxmMotSetEncInputMethod(%u) failed, code %lu\n",
			   (long)AxisNO, (unsigned)method, dwCode);
	}
}

// pulse ���� 
void CAjinMotor::SetMoveRatio()
{
	// 1 unit per 1 pulse: every speed and position in this program is then in
	// pulses. AXM.h documents the same call as the place to set a mechanical
	// ratio, so if this ever fails the axis silently keeps the previous ratio
	// and every distance afterwards is wrong by that factor.
	DWORD dwCode = AxmMotSetMoveUnitPerPulse(AxisNO, 1.0, 1);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXM] axis %ld : AxmMotSetMoveUnitPerPulse(1,1) failed, code %lu\n",
			   (long)AxisNO, dwCode);
	}
}

void CAjinMotor::SetServoOnLogic(DWORD LogicLevel)
{
	// AXM.h: AxmSignalSetServoOnLevel(lAxisNo, uLevel) takes LOW(0) or HIGH(1)
	// and nothing else - it decides which physical output level means "servo
	// on". ServoOn()/ServoOff() carry the logical state; this decides how that
	// state reaches the drive.
	if (LogicLevel > 1) {
		printf("[AXM] axis %ld : SONL=%lu is neither LOW(0) nor HIGH(1);"
			   " the servo on level is left as it is\n", (long)AxisNO, LogicLevel);
		return;
	}

	// Read the board first. This call was commented out for a long time, so
	// every axis has been running on the board's own default and the configured
	// value has never reached it. On an axis that already works, applying it is
	// exactly what would invert servo on and off, so say when the file and the
	// board disagree rather than changing the polarity in silence.
	DWORD uPrev = 0;
	DWORD dwGet = AxmSignalGetServoOnLevel(AxisNO, &uPrev);

	DWORD dwCode = AxmSignalSetServoOnLevel(AxisNO, LogicLevel);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXM] axis %ld : AxmSignalSetServoOnLevel(%lu) failed, code %lu\n",
			   (long)AxisNO, LogicLevel, dwCode);
		return;
	}

	if (dwGet != AXT_RT_SUCCESS) {
		printf("[AXM] axis %ld : servo on level set to %lu, previous value unknown"
			   " (AxmSignalGetServoOnLevel failed, code %lu)\n",
			   (long)AxisNO, LogicLevel, dwGet);
	}
	else if (uPrev != LogicLevel) {
		printf("[AXM] axis %ld : servo on level CHANGED %lu -> %lu"
			   " (SONL in MotorConfig.xml). Verify servo on/off before moving.\n",
			   (long)AxisNO, uPrev, LogicLevel);
	}
}

void CAjinMotor::ServoOn()
{
	int ret = AxmSignalServoOn(AxisNO, HIGH);
	MotorResetOff.SetTime();
}

void CAjinMotor::ServoOff()
{
	int ret = AxmSignalServoOn(AxisNO, LOW);
	MotorResetOff.SetTime();
}

void CAjinMotor::SetInitSpeed(double InitSpeed)
{
	AxmMotSetMinVel(AxisNO, InitSpeed);
}

void CAjinMotor::SetMaxSpeed(int maxspeed)
{
	MaxSpeed = maxspeed;
	AxmMotSetMaxVel(AxisNO, maxspeed);
}

// Relative S Curve Move
void CAjinMotor::MTSRMove(int Position)
{
	GetActualPosition();

	AdjustPosition = Position;

	if (Speed > MaxSpeed) {
		if (!bCamType)
			Speed = MaxSpeed;
	}

	AxmMotSetAbsRelMode(AxisNO, POS_REL_MODE);
	AxmMoveStartPos(AxisNO, AdjustPosition, Speed, Accel, Decel);
}
// Absolute S Curve Move
void CAjinMotor::MTSAMove(int Position)
{
	GetActualPosition();

	AdjustPosition = Position;

	if (Speed > MaxSpeed) {
		if (!bCamType)
			Speed = MaxSpeed;
	}

	/*if (fMotorPause) {
		AxmMotSetAbsRelMode(AxisNO, POS_ABS_MODE);
		AxmMoveStartPos(AxisNO, AdjustPosition, Speed, Accel, Decel);
	}
	else {
		AxmMotSetAbsRelMode(AxisNO, POS_ABS_MODE);
		AxmMoveStartPos(AxisNO, AdjustPosition, Speed, Accel, Decel);
	}
	fMotorPause = 0;*/
	AxmMotSetAbsRelMode(AxisNO, POS_ABS_MODE);

	if (bOverRide) {
		AxmOverrideAccelVelDecelAtPos(AxisNO,
		NxtArrpos, Speed, Accel, Decel,
		OverRidePos, Speed * OverRideRatio, Accel * OverRideRatio, Decel * OverRideRatio, 0);
		bOverRide = false;
	}
	else {
		AxmMotSetAbsRelMode(AxisNO, POS_ABS_MODE);
		AxmMoveStartPos(AxisNO, AdjustPosition, Speed, Accel, Decel);
	}
	fMotorPause = 0;
}

// Continue S_Curve move
void CAjinMotor::MTSCMove()
{
	int ret = AxmMoveVel(AxisNO, Speed, Accel, Decel);
	//	printf("(%d)AxmMoveVel(%d,%ld,%ld,%ld)\n",ret,AxisNO,Speed,Accel,Decel);
}
void CAjinMotor::GetMotorStatus()
{
	unsigned short int io_status, in_user, out_user;

	MS.dwMask = 0x1F;

	// The return used to be assigned and never looked at. On a failure MS keeps
	// whatever it last held, and every flag below was then derived from stale
	// data as though it had just been read from the board.
	DWORD ret = AxmStatusReadMotionInfo(AxisNO, &MS);
	if (ret != AXT_RT_SUCCESS) {
		if (!bStatusReadFailed) {
			bStatusReadFailed = 1;
			printf("[AXM] axis %ld : AxmStatusReadMotionInfo() failed, code 0x%lx."
				   " Reporting the axis stopped rather than acting on a stale read.\n",
				   (long)AxisNO, ret);
		}
		IsDriving = 0;
		IsStop    = 1;
		return;
	}
	bStatusReadFailed = 0;

	ActualPosition = (int)MS.dActPos;
	CommandPosition = (int)MS.dCmdPos;

	// The actual-position counter counts encoder input. On an axis built
	// without an encoder it never moves, so it is not a position at all - the
	// only count the board has is the command counter, which follows the pulses
	// actually sent. Mirror it so every reader, the MMI included, sees a
	// position that moves. [EncType = 0] in MotorConfig.xml selects this.
	if (!EncoderType) {
		ActualPosition = CommandPosition;
	}

	io_status = (unsigned short int)MS.dwMechSig;
	in_user = (unsigned short int)MS.dwInput;
	out_user = (unsigned short int)MS.dwOutput;

	IsORG = ((in_user & 0x01) ? 1 : 0);
	IsZPhase = ((in_user & 0x02) ? 1 : 0);

	if (MotorType == 1)	IsDRVRDY = ((in_user & 0x04) ? 1 : 0);
	else				IsDRVRDY = 0;

	IsInposition = ((io_status & QIMECHANICAL_INP_LEVEL) ? 1 : 0);
	IsAlarm = ((io_status & QIMECHANICAL_ALARM_LEVEL) ? 1 : 0);
	IsHWLimitCCW = ((io_status & QIMECHANICAL_NELM_LEVEL) ? 1 : 0);
	IsHWLimitCW = ((io_status & QIMECHANICAL_PELM_LEVEL) ? 1 : 0);
	IsServoOn = ((out_user & 0x01) ? 1 : 0);

	if (PrevIsServoOn != IsServoOn) {
		if (IsServoOn) printf("AxisNo = %d Servo ON \n", AxisNO);
		if (!IsServoOn) printf("AxisNo = %d Servo OFF \n", AxisNO);
		PrevIsServoOn = IsServoOn;
	}

	if (IsAlarm) {
		GetServoAlarmCodeName();
	}
	GetServoLoadRatio();
	 
	int err;
	err = MS.dwDrvStat & 0x01;

	if (err || fMotorPause || fDriving)
		IsDriving = true;
	else
		IsDriving = false;

	if (!err)
		IsStop = true;
	else
		IsStop = false;

	Sleep(1);
	// Get Torque Value
//	AxlECatReadPdoInput(dwBitOffset, dwDataBitLength, &byTorqueValue);

//	Sleep(1);

	// 	DWORD io_status, in_user, out_user;
	// 	
	//  double d_realposition;
	//  AxmStatusGetActPos(AxisNO,&d_realposition);
	//  ActualPosition=(int)d_realposition;
	// 	
	// 	double d_comandposition;
	// 	AxmStatusGetCmdPos(AxisNO,&d_comandposition);
	// 	CommandPosition= (int)d_comandposition;
	// 
	// 	AxmSignalReadInput(AxisNO,&in_user);
	//  AxmSignalReadOutput(AxisNO,&out_user);
	//  AxmStatusReadMechanical(AxisNO,&io_status);
	// 
	// 	if(AxisNO==12){
	// 		if(bfin_user!=in_user){
	// 			printf("In_user=%d\n",in_user);
	// 			bfin_user=in_user;
	// 		}
	// 	}
	// 
	// 	if(SensorType==1)
	// 		IsORG		=  ((in_user & 0x01)? 0:1);	// limit A�� , Home B�� 
	// 	else
	// 		IsORG		=  ((in_user & 0x01)? 1:0);	// limit A�� , Home B�� 
	// 
	// 
	// 	IsZPhase	=  ((in_user & 0x02)? 1:0);
	// 	if(MotorType==1)
	// 		IsDRVRDY = ((in_user & 0x04)? 1:0);
	// 	else 
	// 		IsDRVRDY = 0;
	// 
	// 	IsInposition = ((io_status & QIMECHANICAL_INP_LEVEL)? 1:0);
	// 
	// 	IsAlarm =  ((io_status & QIMECHANICAL_ALARM_LEVEL) ? 1:0);
	// 
	// 	IsHWLimitCCW=  ((io_status & QIMECHANICAL_NELM_LEVEL)  ? 1:0);
	// 	IsHWLimitCW =  ((io_status & QIMECHANICAL_PELM_LEVEL)  ? 1:0);
	// 
	// 	IsServoOn= ((out_user & 0x01) ? 1:0);
	// 
	// 	int err;
	// 	DWORD d_err;
	// //	AxmStatusReadMotion(AxisNO,&d_err);
	// 	err=d_err & 0x01;
	// 
	// 	if(err||fMotorPause||fDriving) 
	// 		IsDriving=true;
	// 	else
	// 		IsDriving=false;
	// 
	// 	if(!err)  
	// 		IsStop=true;
	// 	else    
	// 		IsStop=false;
	// 	RtSleep(5);
}

void CAjinMotor::SetInitPosition()
{
	CurPos = 1;
	CurArrpos = 0;
	NxtPos = 1;
	NxtArrpos = PositionArray[2];
	SetActualPosition(0);
	SetCommandPosition(0);
}

void CAjinMotor::SetTriggerEnable()
{
	AxmTriggerSetReset(AxisNO);
}

void CAjinMotor::SetTriggerProfile(int pulse, int time)
{
	AxmTriggerSetBlockByEvent(AxisNO, In3UpEdge, pulse, time, HIGH, ACTUAL, 0);
}
void CAjinMotor::SetSignalStop(DWORD uStopMode, DWORD uLevel)
{
	AxmSignalSetStop(AxisNO, uStopMode, uLevel);
}
void CAjinMotor::SetHomeSignalLevel(DWORD uLevel)
{
	AxmHomeSetSignalLevel(AxisNO, HIGH);
}
void CAjinMotor::MTOverRideMove(double ratio)
{
	DWORD upStatus;
	AxmStatusReadInMotion(AxisNO, &upStatus);
	if (upStatus == 1) {
		AxmOverrideSetMaxVel(AxisNO, Speed);
		AxmOverrideVel(AxisNO, Speed * ratio);
		/*
		AxmOverrideAccelVelDecelAtPos(AxisNO,
			NxtArrpos, Speed, Accel, Decel,
			90.0 * MTFlipTurn1->MMI_PulseRate, Speed * ratio, Accel * ratio, Decel * ratio, 0);
		*/

		//DWORD nRet = AxmOverrideAccelVelDecel(AxisNO, Speed * ratio, Accel * ratio, Accel * ratio);
		//printf("AxmOverrideAccelVelDecel\n");
	}
	else {
		AxmMoveVel(AxisNO, Speed, Accel * ratio, Accel * ratio);
		//printf("AxmMoveVel\n");
	}
}

void CAjinMotor::MTDecelStopRate(double rate)
{
	AxmMoveStop(AxisNO, rate); // Pause !!!!
//	printf("AxmMoveStop %d, %lf\n", AxisNO, rate);
}

void CAjinMotor::GetServoAlarmCodeName(void)
{
	DWORD uReturn;
	uReturn = AxmStatusRequestServoAlarm(AxisNO);
	if (uReturn == AXT_RT_SUCCESS){
		uReturn = AxmStatusReadServoAlarm(AxisNO, FUNC_RETURN_IMMEDIATE, &dwServoAlarmCode);
		if (uReturn == AXT_RT_SUCCESS){
			AxmStatusGetServoAlarmString(AxisNO, dwServoAlarmCode, 1024, strServoAlarmName);
		//	printf("�˶��ڵ�[0x%X] : %s\n", uServoAlarmCode, strServoAlarmName);
		}
	}
}
void CAjinMotor::SetServoLoadRatio(DWORD dwSelMon)
{
	DWORD uReturn;
	uReturn = AxmStatusSetReadServoLoadRatio(AxisNO, dwSelMon);
}

double CAjinMotor::GetServoLoadRatio(void)
{
	DWORD uReturn;
	uReturn = AxmStatusReadServoLoadRatio(AxisNO, &dServoLoadRatio);
	return dServoLoadRatio;
}

