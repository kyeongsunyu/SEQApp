#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"

#define SET_ERROR(code)\
{\
	ERRIF0(code);\
	if(!bAlarmCheck[code]){\
		bAlarmCheck[code] = true;\
		LOG_ERROR("CODE = %d, SET, %s", code, #code);\
	}\
}

#define SET_MOTOR_ERROR(axis, code)\
{\
	ERRIF0(code);\
	if(!bAlarmCheck[code]){\
		bAlarmCheck[code] = true;\
		LOG_ERROR("CODE = %d, SET, %s", code, #code);\
	}\
}
#define RESET_ERROR(code)\
{\
	if (bAlarmCheck[code]) {\
		bAlarmCheck[code] = false;\
		LOG_ERROR("CODE = %d, RESET, %s", code, #code);\
	}\
}

union {
	DWORD dwDM;
	struct {
		WORD wErrorCode;
		WORD wRunCode;
	};
} MTBAMTBF;

void CSeqMain::ERRIF0(int ec)
{
	if ((tmperrorcode < 20) && ec) {
		errorcode[tmperrorcode] = ec;
		tmperrorcode++;
	}
}

void CSeqMain::ERRCLRIF0(int ec)
{
	for (int i = 0; i < 20; i++) {
		if (errorcode[i] == ec)	errorcode[i] = 0;
	}
}

int CSeqMain::ErrorProcedure(void)
{
	tmperrorcode = 0;

	if (dm.SystemInitialize == 1 || !bit.DeviceDataReceived ||
		MachineStatus.nDeviceNo == 0) {
		return 1;
	}

#pragma region NETWORK_MODULE_ERROR
	// For RTEX
	//DWORD dwReturn;
	//for (int i = 0; i <= 11; i++) {
	//	dwReturn = AjinBase->GetModuleNodeStatus(0, i);
	//	if (dwReturn) {
	//		ERRIF0(ERROR_MASTER_BOARD1_SLAVE1 +i);
	//		if (!bAlarmCheck[ERROR_MASTER_BOARD1_SLAVE1 +i]) {
	//			bAlarmCheck[ERROR_MASTER_BOARD1_SLAVE1 +i] = true;
	//			LOG_ERROR("CODE = %d, SET, ERROR_MASTER_BOARD1_SLAVE%d", ERROR_MASTER_BOARD1_SLAVE1 + i, i);
	//		}
	//	}
	//	else {
	//		if (bAlarmCheck[ERROR_MASTER_BOARD1_SLAVE1 + i]) {
	//			bAlarmCheck[ERROR_MASTER_BOARD1_SLAVE1 + i] = false;
	//			LOG_ERROR("CODE = %d, RESET, ERROR_MASTER_BOARD1_SLAVE%d", ERROR_MASTER_BOARD1_SLAVE1 + i, i);
	//		}
	//	}
	//}
#pragma endregion

#pragma region EMERGENCY_ERRROR
	//if (EMERON()) {
	//	_OFF(oMCPower);
	//	EmerOffProcess();
	//	if (BINON(iEMO)) {
	//		SET_ERROR(ERROR_EMERGENCY);
	//	}
	//	if (BINON(iEmptyEMO)) {
	//		SET_ERROR(ERROR_EMERGENCY_EMPTY_OPTION);
	//	}
	//	dm.errorcode = errorcode[0];
	//	//dm.errorcode = errorcode[tmperrorcode];
	//	//tmperrorcode++;

	//	bit.PAutoStop = 0;
	//	bit.MotorTunning = 0;

	//	if (!bit.BeforeEmer) {
	//		tm_gEmergencyOn.SetTime();
	//		bit.BeforeEmer = 1;
	//		bit.PAutoStop = 0;
	//	}
	//	else {
	//		if (tm_gEmergencyOn.TimeOvermS(500) && !tm_gEmergencyOn.TimeOvermS(600)) {
	//			for (int mtno = 1; mtno <= totalAxisCnt; mtno++) {
	//				MTAxis[mtno]->ServoOff();
	//			//	EmerOffProcess();
	//				Sleep(10);
	//			}
	//		}
	//	}
	//	bit.BeforeEmer = 1;
	//	dm.LampStatus = 0;
	//	tm_gEmergencyOff.SetTime();
	//	return 1;

	//}
	//else {
	//	RESET_ERROR(ERROR_EMERGENCY);
	//	RESET_ERROR(ERROR_EMERGENCY_EMPTY_OPTION);

	//	tm_gEmergencyOn.SetTime();
	//	if (bit.BeforeEmer) {
	//		errorcode[0] = tmperrorcode = 0;
	//		bit.BeforeEmer = 0;
	//	}
	//	_OFF(oSawEStop);
	//	_ON(oE84_ES_1);
	//	_ON(oLight);
	//	_ON(oEmptyLight);
	//}
#pragma endregion

#pragma region RESET_SERVO_ON
	for (int mtno = 1; mtno <= totalAxisCnt; mtno++) {
		if (MTAxis[mtno]->MotorAlarmResetOn.TimeOvermS(1000)&&
			!MTAxis[mtno]->MotorAlarmResetOn.TimeOvermS(1100)) {
			MTAxis[mtno]->MTEStop();
			MTAxis[mtno]->ServoOn();
		}
	}
#pragma endregion

	///////////////////////////////////////////////////////////////////////////
#pragma region MAIN_POWER
	//if (AINOFF(iMCPower)) {
	//	SET_ERROR(ERROR_MACHINE_POWER);
	//	AllCycleStop();
	//	bit.AllHome = 0;
	//	bit.PAutoStop = 1;
	//}
	//else {
	//	RESET_ERROR(ERROR_MACHINE_POWER);
	//}

//	if (AINOFF(iSystemReady)) {
//		ERRIF0(ERROR_SYSTEM_NOT_READY);
//		if (!bAlarmCheck[ERROR_SYSTEM_NOT_READY]) {
//			bAlarmCheck[ERROR_SYSTEM_NOT_READY] = true;
////			LOG_ERROR(ERROR_SYSTEM_NOT_READY, "Error Set ERROR_SYSTEM_NOT_READY");
//			LOG_ERROR("CODE = %d, %s", ERROR_SYSTEM_NOT_READY, "SET, ERROR_SYSTEM_NOT_READY");
//		}
//		AllCycleStop();
//		bit.AllHome = 0;
//		bit.PAutoStop = 1;
//	}
//	else {
//		if (bAlarmCheck[ERROR_SYSTEM_NOT_READY]) {
//			bAlarmCheck[ERROR_SYSTEM_NOT_READY] = false;
////			LOG_ERROR(ERROR_SYSTEM_NOT_READY, "Error Reset ERROR_SYSTEM_NOT_READY");
//			LOG_ERROR("CODE = %d, %s", ERROR_SYSTEM_NOT_READY, "RESET, ERROR_SYSTEM_NOT_READY");
//		}
//	}
#pragma endregion

	///////////////////////////////////////////////////////////////////////////
#pragma region AIR_PRESSURE
	/*if (AINOFF(iMainAir1High)) {
		SET_ERROR(ERROR_MAIN_AIR1);
		AllCycleStop();
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_MAIN_AIR1);
	}

	if (AINOFF(iMainAir2High)) {
		SET_ERROR(ERROR_MAIN_AIR2);
		AllCycleStop();
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_MAIN_AIR2);
	}*/


#pragma endregion

	///////////////////////////////////////////////////////////////////////////
#pragma region SAFETY_DOOR
	/*if (AINOFF(iDoorFront)) {
		SET_ERROR(ERROR_FRONT_DOOR);
		AllCycleStop();
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		ERRCLRIF0(ERROR_FRONT_DOOR);
		RESET_ERROR(ERROR_FRONT_DOOR);
	}
	if (AINOFF(iDoorRear)) {
		SET_ERROR(ERROR_REAR_DOOR);
		AllCycleStop();
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		ERRCLRIF0(ERROR_REAR_DOOR);
		RESET_ERROR(ERROR_REAR_DOOR);
	}
	if (AINOFF(iDoorSide)) {
		SET_ERROR(ERROR_SIDE_DOOR);
		AllCycleStop();
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		ERRCLRIF0(ERROR_SIDE_DOOR);
		RESET_ERROR(ERROR_SIDE_DOOR);
	}*/
#pragma endregion

#pragma region MOTOR_DRIVER_ALARM
	//// AXIS 01 MTStageX DRIVE ALARM
	//if (MTStageX->idrvalm) {
	//	SET_MOTOR_ERROR(MTStageX, ERROR_DRIVER_ALARM_STAGE_X);
	//	MTEMEROFF(MTStageX);
	//	AllCycleStop();
	//	bit.AllHome = 0;
	//	bit.PAutoStop = 1;
	//}
	//else {
	//	RESET_ERROR(ERROR_DRIVER_ALARM_STAGE_X);
	//}
	//// AXIS 02 MTStageY DRIVE ALARM
	//if (MTStageY->idrvalm) {
	//	SET_MOTOR_ERROR(MTStageY, ERROR_DRIVER_ALARM_STAGE_Y);
	//	MTEMEROFF(MTStageY);
	//	AllCycleStop();
	//	bit.AllHome = 0;
	//	bit.PAutoStop = 1;
	//}
	//else {
	//	RESET_ERROR(ERROR_DRIVER_ALARM_STAGE_Y);
	//}
	//// AXIS 03 MTStageZ DRIVE ALARM
	//if (MTStageZ->idrvalm) {
	//	SET_MOTOR_ERROR(MTStageZ, ERROR_DRIVER_ALARM_STAGE_Z);
	//	MTEMEROFF(MTStageZ);
	//	AllCycleStop();
	//	bit.AllHome = 0;
	//	bit.PAutoStop = 1;
	//}
	//else {
	//	RESET_ERROR(ERROR_DRIVER_ALARM_STAGE_Z);
	//}
#pragma endregion

#pragma region MOTOR_SERVO_OFF
	//// AXIS 01 MTStageX SERVO OFF
	//if (!MTStageX->IsServoOn) {
	//	SET_MOTOR_ERROR(MTStageX, ERROR_SERVO_OFF_STAGE_X);
	//	MTEMEROFF(MTStageX);
	//	//AllCycleStop();
	//	bit.AllHome = 0;
	//	bit.PAutoStop = 1;
	//}
	//else {
	//	RESET_ERROR(ERROR_SERVO_OFF_STAGE_X);
	//}
	//// AXIS 02 MTLoadPkX SERVO OFF
	//if (!MTStageY->IsServoOn) {
	//	SET_MOTOR_ERROR(MTStageY, ERROR_SERVO_OFF_STAGE_Y);
	//	MTEMEROFF(MTStageY);
	//	//AllCycleStop();
	//	bit.AllHome = 0;
	//	bit.PAutoStop = 1;
	//}
	//else {
	//	RESET_ERROR(ERROR_SERVO_OFF_STAGE_Y);
	//}
	//// AXIS 03 MTLoadPkX SERVO OFF
	//if (!MTStageZ->IsServoOn) {
	//	SET_MOTOR_ERROR(MTStageZ, ERROR_SERVO_OFF_STAGE_Z);
	//	MTEMEROFF(MTStageZ);
	//	//AllCycleStop();
	//	bit.AllHome = 0;
	//	bit.PAutoStop = 1;
	//}
	//else {
	//	RESET_ERROR(ERROR_SERVO_OFF_STAGE_Z);
	//}

#pragma endregion

#pragma region STROKE_END
	// AXIS 01 MTStageZ STROKE END
	if (MTStageX->IsHWLimitCCW && (MTStageX->NxtPos != 0)) {
		SET_MOTOR_ERROR(MTStageX, ERROR_LIMIT_CCW_STAGE_X);
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_LIMIT_CCW_STAGE_X);
	}

	if (MTStageX->IsHWLimitCW && (MTStageX->NxtPos != 0)) {
		SET_MOTOR_ERROR(MTStageX, ERROR_LIMIT_CW__STAGE_X);
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_LIMIT_CW__STAGE_X);
	}
	// AXIS 02 MTStageZ STROKE END
	if (MTStageY->IsHWLimitCCW && (MTStageY->NxtPos != 0)) {
		SET_MOTOR_ERROR(MTStageY, ERROR_LIMIT_CCW_STAGE_Y);
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_LIMIT_CCW_STAGE_Y);
	}

	if (MTStageY->IsHWLimitCW && (MTStageY->NxtPos != 0)) {
		SET_MOTOR_ERROR(MTStageY, ERROR_LIMIT_CW__STAGE_Y);
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_LIMIT_CW__STAGE_Y);
	}
	// AXIS 03 MTStageZ STROKE END
	if (MTStageZ->IsHWLimitCCW && (MTStageZ->NxtPos != 0)) {
		SET_MOTOR_ERROR(MTStageZ, ERROR_LIMIT_CCW_STAGE_Z);
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_LIMIT_CCW_STAGE_Z);
	}

	if (MTStageZ->IsHWLimitCW && (MTStageZ->NxtPos != 0)) {
		SET_MOTOR_ERROR(MTStageZ, ERROR_LIMIT_CW__STAGE_Z);
		bit.AllHome = 0;
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_LIMIT_CW__STAGE_Z);
	}
	// AXIS 01 MTStageX MOTOR HOME
	if (!MTStageX->imrs) {
		SET_MOTOR_ERROR(MTStageX, ERROR_NOT_INITIALIZED_STAGE_X);
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_NOT_INITIALIZED_STAGE_X);
		ERRCLRIF0(ERROR_NOT_INITIALIZED_STAGE_X);
	}
	// AXIS 02 MTStageY MOTOR HOME
	if (!MTStageY->imrs) {
		SET_MOTOR_ERROR(MTStageY, ERROR_NOT_INITIALIZED_STAGE_Y);
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_NOT_INITIALIZED_STAGE_Y);
		ERRCLRIF0(ERROR_NOT_INITIALIZED_STAGE_Y);
	}
	// AXIS 03 MTLoadPkX MOTOR HOME
	if (!MTStageZ->imrs) {
		SET_MOTOR_ERROR(MTStageZ, ERROR_NOT_INITIALIZED_STAGE_Z);
		bit.PAutoStop = 1;
	}
	else {
		RESET_ERROR(ERROR_NOT_INITIALIZED_STAGE_Z);
		ERRCLRIF0(ERROR_NOT_INITIALIZED_STAGE_Z);
	}
#pragma endregion

#pragma region PNEUMATIC_ERROR

#pragma endregion	

	//////////////////////////////////////////////////////////////////////////
	if (errorcode[0]) {
		if (!bferrorcode || (errorcode[0] < bferrorcode)) {
			bit.NewBuzzer = 1;
			bit.BuzzerOn = 1;
		}
	}
	else {
		bit.NewBuzzer = 0;
		bit.BuzzerOn = 0;
	}

	bferrorcode = errorcode[0];
	dm.errorcode = errorcode[0];

	return 0;
}
void CSeqMain::AllCycleStop(void)
{
	bit.StageZCycle = 0;
}
void CSeqMain::MTBA_MTBF(void)
{
	//-- MTBA/MTBF --//
	dm.FirstErrorCode = 0;
	if (bit.AutoRun != bit.AutoRunB) {
		if (!bit.AutoRun) {
			if (errorcode[0] && errorcode[0] <= 0x0350) {
				dm.FirstErrorCode = errorcode[0];
				dm.MTBA_MTBF = 2;	// 2: Error
			}
			else {
				dm.MTBA_MTBF = 3;	// 3: NoError Stop
			}
//			pFileLog->LOG_MSG_F(LT_ERROR, "ERROR CODE = %d", errorcode[0]);
		}
		else {
			dm.MTBA_MTBF = 1;		// 1: auto run
		}
	}
	bit.AutoRunB = bit.AutoRun;
}
