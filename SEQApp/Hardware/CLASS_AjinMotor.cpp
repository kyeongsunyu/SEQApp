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
	long lAxisCount;
	if (AxlOpen(7) == AXT_RT_SUCCESS) {	// success
		bct2dMode = FALSE;
		AxmInfoGetAxisCount(&lAxisCount);
		printf("Motion Board Initialize Success for EtherCat!...\n");
	}
	else {
		bct2dMode = TRUE;
		printf("Motion Board Initialize Success for FallBack!...\n");
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
	InitMember();

	AxisNO = axs_no;
	AxisLogicNO = logical_no;
}

// The object is allocated with new, so every member that is not assigned here
// keeps the content of the memory it was given (0xCDCDCDCD in a debug build,
// anything in a release build). Those values are used as flags, as array indices
// and as motion parameters, so the axis has to start from a defined state :
// not homed, not moving, no pending command, empty position tables.
void CAjinMotor::InitMember()
{
	memset(&MS, 0x00, sizeof(MS));

	SensorType = 0;
	MotorType = 0;

	ActualPosition = 0;
	CommandPosition = 0;
	SpeedDevide = AUTOSPEED;
	MinMovingTime = 0;
	AxisNO = 0;
	AxisLogicNO = 0;
	sHomeState = Init;
	nOriginSetRetry = 0;
	CancelCmd = 0;
	CmdMode = Wait_Cmd;

	Speed = 0.;
	Accel = 0.;
	Decel = 0.;
	Jerk = 0.;
	SaveSpeed = 0.;
	SaveAccel = 0.;
	SaveJerk = 0.;
	InitSpeed = 0.;
	MaxSpeed = 0.;

	CurPos = 299;
	NxtPos = 299;
	WorkPos = 0;
	DfltWorking = 0;
	bOverRide = false;
	OverRidePos = 0.;
	OverRideRatio = 0.;

	//-- FLAG --//
	fDoHome = 0;
	fIMRS = 0;			// never report "home finished" before a home really ran
	fMotorPause = 0;
	fMotorHome = 0;
	fDriving = 0;
	IsHWLimitCW = 0;
	IsHWLimitCCW = 0;
	IsDRVRDY = 1;
	IsORG = 0;
	IsAlarm = 0;
	IsInposition = 1;
	IsServoOn = 0;
	PrevIsServoOn = 0;
	IsDriving = 0;
	IsStop = 1;
	IsZPhase = 0;
	EncoderSet = 0;
	AlramReset = 0;
	EncoderType = 0;
	IsHomming = 0;
	fMoveCmdFailed = 0;
	fHomeFailed = 0;

	omove = 0;
	moving = 0;			// no move is in progress at power on
	relative = 0;

	imrs = 0;			// not homed
	irdy = 0;
	isend = 0;
	idrvalm = 0;
	idrvrdy = 0;
	canmovejog = 0;
	ostart = 1;

	ZPhaseSpeed = NULL;
	HomeSpeed = NULL;
	MovingDistance = 0.;
	TimeDesier = 0.;
	AdjustPosition = 0;
	CurArrpos = 0.;
	NxtArrpos = 0.;
	Direction = 0;

	memset(PositionArray, 0x00, sizeof(PositionArray));
	memset(SpeedArray, 0x00, sizeof(SpeedArray));
	memset(AccelArray, 0x00, sizeof(AccelArray));
	memset(DecelArray, 0x00, sizeof(DecelArray));

	/* Motor Config Data from Data File */
	bCwLimitLevel = 0;
	bCCwLimitLevel = 0;
	bServoOnLevel = 0;
	bAlarmLevel = 0;
	bInpLevel = 0;
	bInpEnable = 0;
	nPulseOutM = 0;
	nEncDir = 0;
	nEncType = 0;
	nMotorType = 0;
	nSensorType = 0;

	/* Motor Config Data from MMI Data */
	MMI_PulseRate = 0;
	MMI_MaxVel = 0;
	MMI_JogVel = 0;
	MMI_HomeVel = 0;
	MMI_Accel = 0;
	MMI_HomeLevel = 0;
	MMI_LimitLevel = 0;
	MMI_ServoOnLevel = 0;
	MMI_AlarmLevel = 0;
	MMI_InpUse = 0;
	MMI_MtrDir = 0;
	MMI_EncDir = 0;
	MMI_MotorType = 0;
	MMI_Enc_Type = 0;

	bCamType = 0;

	dwServoAlarmCode = 0;
	memset(strServoAlarmName, 0x00, sizeof(strServoAlarmName));
	dServoLoadRatio = 0.;

	// EtherCat
	dwBitOffset = 0;
	dwDataBitLength = 0;
	byTorqueValue = 0;
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
	// AxmStatusSetPosMatch() is "Only RTEX use" (see AXM.h). On an EtherCAT
	// network it is refused, so the command position used to keep its pre home
	// value and the first absolute move after homing ran the whole stale offset.
	DWORD dwRet = AxmStatusSetCmdPos(AxisNO, (double)Position);
	if (dwRet != AXT_RT_SUCCESS) {
		dwRet = AxmStatusSetPosMatch(AxisNO, (double)Position);		// RTEX
	}
	if (dwRet == AXT_RT_SUCCESS) {
		CommandPosition = Position;
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
	DWORD dwRet = AxmStatusSetActPos(AxisNO, (double)Position);
	if (dwRet != AXT_RT_SUCCESS) {
		dwRet = AxmStatusSetPosMatch(AxisNO, (double)Position);		// RTEX
	}
	if (dwRet == AXT_RT_SUCCESS) {
		ActualPosition = Position;
	}
}

// Move the origin of the axis and verify it by reading both counters back.
// Returns false when the motion board did not take the new origin : the caller
// must not start an absolute move then, the axis would run to a target that is
// expressed in the old coordinate system.
bool CAjinMotor::SetOrigin(int Position, int Tolerance)
{
	SetCommandPosition(Position);
	SetActualPosition(Position);

	GetCommandPosition();
	GetActualPosition();

	return ((abs(CommandPosition - Position) <= Tolerance) &&
			(abs(ActualPosition - Position) <= Tolerance));
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
DWORD CAjinMotor::MTSRMove(int Position)
{
	GetActualPosition();

	AdjustPosition = Position;

	if (Speed > MaxSpeed) {
		if (!bCamType)
			Speed = MaxSpeed;
	}

	AxmMotSetAbsRelMode(AxisNO, POS_REL_MODE);
	return AxmMoveStartPos(AxisNO, AdjustPosition, Speed, Accel, Decel);
}
// Absolute S Curve Move
DWORD CAjinMotor::MTSAMove(int Position)
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

	DWORD dwRet;
	if (bOverRide) {
		dwRet = AxmOverrideAccelVelDecelAtPos(AxisNO,
		NxtArrpos, Speed, Accel, Decel,
		OverRidePos, Speed * OverRideRatio, Accel * OverRideRatio, Decel * OverRideRatio, 0);
		bOverRide = false;
	}
	else {
		AxmMotSetAbsRelMode(AxisNO, POS_ABS_MODE);
		dwRet = AxmMoveStartPos(AxisNO, AdjustPosition, Speed, Accel, Decel);
	}
	fMotorPause = 0;

	return dwRet;
}

// Continue S_Curve move
DWORD CAjinMotor::MTSCMove()
{
	DWORD ret = AxmMoveVel(AxisNO, Speed, Accel, Decel);
	//	printf("(%d)AxmMoveVel(%d,%ld,%ld,%ld)\n",ret,AxisNO,Speed,Accel,Decel);
	return ret;
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

