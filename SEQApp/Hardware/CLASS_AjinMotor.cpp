#include "..\pch.h"
#include "CLASS_AjinMotor.h"
#include "..\SeqMain\DEFINE_GVX.h"

extern DWORD	AxmTriggerSetBlockByEvent(long lAxisNo, DWORD dwEventSignal, double dPeriod, double dTrigTime, long lTrigLevel, DWORD dwSelect, DWORD dwOnce);


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

void CAjinBase::InitBase()
{
	const long lIrqNo = 7;

	// bct2dMode selects the hardware type, not a simulation: FALSE for EtherCAT
	// based motion, TRUE for a pulse-train (ct2d) system, where the wrappers
	// below skip the calls that only exist on an EtherCAT node network.
	//
	// Whether the library came up at all is a separate question from which type
	// of hardware is attached. The old code answered both with one branch and
	// printed "Success" either way, so a driver that never loaded looked exactly
	// like a working pulse system.
	// Which AXL.dll actually got loaded, and what version it is. Copies exist in
	// the output folder, in System32 and in the installed SDK, so the loader's
	// choice is not obvious - and a DLL that does not match the running EzManager
	// reports AXT_RT_NOT_RUN_EZMANAGER (1057) even while EzManager is up.
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

	// AxlOpen() resets the hardware chip and brings up the EtherCAT master, which
	// is why it returns 1057 (EzManager not running) on a pulse-type board set
	// even while EzManager is up. AxlOpenNoReset() skips that reset - it is what
	// the AutoFocus SEQ project uses to drive this same board set on x64.
	//
	// So the two calls also tell the hardware types apart, which is a firmer
	// basis than the old "AxlOpen failed, must be ct2d" guess:
	//   AxlOpen OK          -> EtherCAT node network
	//   only NoReset OK     -> pulse (ct2d) system
	//   neither             -> library never came up; nothing is reachable
	DWORD dwCode = AxlOpen(lIrqNo);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[AXL] AxlOpen(%ld) returned %lu (0x%lx), retrying with"
			   " AxlOpenNoReset()\n", lIrqNo, dwCode, dwCode);

		DWORD dwNoReset = AxlOpenNoReset(lIrqNo);
		if (dwNoReset == AXT_RT_SUCCESS) {
			bct2dMode = TRUE;
			printf("[AXL] AxlOpenNoReset(%ld) OK -> ct2d (pulse) mode\n", lIrqNo);

			long lAxisCount = 0;
			if (AxmInfoGetAxisCount(&lAxisCount) == AXT_RT_SUCCESS) {
				printf("[AXL] %ld axis available\n", lAxisCount);
			}
			return;
		}

		printf("[AXL] AxlOpenNoReset(%ld) also failed, code %lu (0x%lx)\n",
			   lIrqNo, dwNoReset, dwNoReset);
		dwCode = dwNoReset;
	}

	bct2dMode = (dwCode != AXT_RT_SUCCESS);

	if (!bct2dMode) {
		long lAxisCount = 0;
		DWORD dwAxis = AxmInfoGetAxisCount(&lAxisCount);
		if (dwAxis == AXT_RT_SUCCESS) {
			printf("[AXL] open OK (IRQ %ld) - EtherCAT mode, %ld axis\n",
				   lIrqNo, lAxisCount);
		}
		else {
			printf("[AXL] open OK (IRQ %ld) - EtherCAT mode, AxmInfoGetAxisCount()"
				   " failed, code 0x%lx\n", lIrqNo, dwAxis);
		}
		return;
	}

	printf("[AXL] AxlOpen(%ld) returned %lu (0x%lx) -> ct2d (pulse) mode\n",
		   lIrqNo, dwCode, dwCode);

	// A closed library is not a hardware type, it is a fault: every AXL call
	// then returns AXT_RT_NOT_OPEN (1053) and no board is reachable, pulse or
	// otherwise. Say so plainly instead of leaving it to be inferred later.
	if (!AxlIsOpened()) {
		printf("[AXL] WARNING: library is NOT open - every AXL call will fail with"
			   " 1053 (AXT_RT_NOT_OPEN).\n");
		if (dwCode == 1057) {   // AXT_RT_NOT_RUN_EZMANAGER
			printf("      1057 = EzManager not running. If EzManager IS running,"
				   " the loaded AXL.dll\n"
				   "      above most likely does not match it - compare its version"
				   " and bitness with\n"
				   "      the EzSoftware installation, and check that both run in the"
				   " same session.\n");
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
	AxisNO = axs_no;
	AxisLogicNO = logical_no;
	bOverRide = false;
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
	AxmStatusSetPosMatch(AxisNO, (double)Position);
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
	AxmStatusSetPosMatch(AxisNO, (double)Position);
}

int CAjinMotor::GetActualPosition()
{
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
	AxmSignalSetInpos(AxisNO, Enable);	// 0:LOW, 1: HIGH, 2: disable
}

void CAjinMotor::SetAlarmEnable(int Enable)
{
	AxmSignalSetServoAlarm(AxisNO, Enable);	// 0: LOW, 1: HIGH, 2: disable
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
	AxmMotSetPulseOutMethod(AxisNO, mode);
}

// Encoder �Է¹�� ����, Sqr4Mode=4ü�� 
void CAjinMotor::SetEncoderInputMethos(unsigned char method)
{
	AxmMotSetEncInputMethod(AxisNO, method);	// encoder direction ����
}

// pulse ���� 
void CAjinMotor::SetMoveRatio()
{
	AxmMotSetMoveUnitPerPulse(AxisNO, 1, 1);
}

void CAjinMotor::SetServoOnLogic(DWORD LogicLevel)
{
	AxmSignalSetServoOnLevel(AxisNO, LogicLevel);
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

	DWORD ret = AxmStatusReadMotionInfo(AxisNO, &MS);

	ActualPosition = (int)MS.dActPos;
	CommandPosition = (int)MS.dCmdPos;

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

