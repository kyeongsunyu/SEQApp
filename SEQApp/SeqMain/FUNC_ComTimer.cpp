#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"

void CSeqMain::CommonTimer(void)
{
	if (dm.SystemInitialize == 1)	return;

	if (bit.AutoRun) {
		dm.SEQLAMPSTATUS = 1;
	}
	else {
		dm.SEQLAMPSTATUS = 0;
	}

#pragma region GENERAL_TIMER
	
#pragma endregion

#pragma region MOTOR_TIMER
	for (int i = 1; i < totalAxisCnt; i++) {
		tmReady_MTAxis[i].TimerCondition(MTRDY(MTAxis[i]));
	}

	tmReady_MTStageX				.TimerCondition(MTRDY(MTStageX));
	tmReady_MTStageY				.TimerCondition(MTRDY(MTStageY));
	tmReady_MTStageZ				.TimerCondition(MTRDY(MTStageZ));

	tmMoving_MTStageX				.TimerCondition	(!MTStageX->IsStop);
	tmMoving_MTStageY				.TimerCondition(!MTStageY->IsStop);
	tmMoving_MTStageZ				.TimerCondition(!MTStageZ->IsStop);
#pragma endregion

#pragma region INPUT_TIMER
	// CH 01
	tm_iKeyStart_On					.TimerCondition(AINON(iKeyStart));
	tm_iKeyStart_Off					.TimerCondition(AINOFF(iKeyStart));

	tm_iKeyStop_On					.TimerCondition(AINON(iKeyStop));
	tm_iKeyStop_Off					.TimerCondition(AINOFF(iKeyStop));

	tm_iKeyReset_On					.TimerCondition(AINON(iKeyReset));
	tm_iKeyReset_Off					.TimerCondition(AINOFF(iKeyReset));


#pragma endregion
	
#pragma region OUTPUT_TIMER
	// CH 01
	tm_oKeyStart_On					.TimerCondition(OUTON(oKeyStart));
	tm_oKeyStart_Off					.TimerCondition(OUTOFF(oKeyStart));

	tm_oKeyStop_On					.TimerCondition(OUTON(oKeyStop));
	tm_oKeyStop_Off					.TimerCondition(OUTOFF(oKeyStop));

	tm_oKeyReset_On					.TimerCondition(OUTON(oKeyReset));
	tm_oKeyReset_Off					.TimerCondition(OUTOFF(oKeyReset));

	tm_oTowerLampRed_On			.TimerCondition(OUTON(oTowerLampRed));
	tm_oTowerLampRed_Off			.TimerCondition(OUTOFF(oTowerLampRed));

	tm_oTowerLampYellow_On		.TimerCondition(OUTON(oTowerLampYellow));
	tm_oTowerLampYellow_Off		.TimerCondition(OUTOFF(oTowerLampYellow));

	tm_oTowerLampGreen_On		.TimerCondition(OUTON(oTowerLampGreen));
	tm_oTowerLampGreen_Off		.TimerCondition(OUTOFF(oTowerLampGreen));

	tm_oBuzzer1_On					.TimerCondition(OUTON(oBuzzer1));
	tm_oBuzzer1_Off					.TimerCondition(OUTOFF(oBuzzer1));

#pragma endregion

#pragma region MACHINE_STATE
	MachineStatus.nDeviceNo = DeviceInfo.nDeviceNumber;
	strcpy(MachineStatus.strDeviceName, DeviceInfo.strDeviceName);

	MachineStatus.UPH = dm.UPH;
	MachineStatus.TPH = dm.TPH;

	#pragma region IO_STATE
	// CH 01

	// CH 02
	/*MachineStatus.bInputState[02][3] = AINON(iMZOutBufferAlignFwd) ? true : false;
	MachineStatus.bInputState[02][4] = AINON(iMZOutBufferAlignBwd) ? true : false;*/
	
	// CH 03

	// CH 04
	
	#pragma endregion

	#pragma region HOME_SATE
	for (int i = 1; i <= totalAxisCnt; i++) {
		if (MTAxis[i]->idrvalm) {
			MachineStatus.HomeState[MTAxis[i]->AxisNO] = HOME_STATE_ALARM;
		}
		else {
			if (MTAxis[i]->imrs) {
				MachineStatus.HomeState[MTAxis[i]->AxisNO] = HOME_STATE_COMPLETE;
			}
			else {
				if (MTAxis[i]->fDoHome) {
					MachineStatus.HomeState[MTAxis[i]->AxisNO] = HOME_STATE_HOMMING;
				}
				else {
					MachineStatus.HomeState[MTAxis[i]->AxisNO] = HOME_STATE_READY;
				}
			}
		}
	}
	#pragma endregion
		
	
#pragma region RUN_CYCLE_TIMER
	tm_gPautostop.TimerCondition(bit.PAutoStop);

	bool AllMotionDone = true;
	for (int i = 0; i < totalAxisCnt; i++) {
		AllMotionDone &= MTAxis[i + 1]->IsStop;
	}
	bit.AllMotionDone = AllMotionDone;

	tm_gAllMotionDone.TimerCondition(bit.AllMotionDone);
	tm_gAllCycleStop.TimerCondition(bit.AllCycleStop);
#pragma endregion

#pragma region CAL_UPH
	if (bit.AutoRun) {
		if (tm_gUPH.TimeOvermS(20000)) {
			tm_gUPH.SetTime();
			if (uphstackno >= 180) {
				for (int i = 0; i < 180; i++) {
					stack[i] = stack[i + 1];
				}
				uphstackno = 179;
			}
			if (unloadingunitcount)		stack[uphstackno] = unloadingunitcount;
			else						stack[uphstackno] = 0;
			uphstackno++;
			WORD uphsum = 0;
			for (int i = 0; i < uphstackno; i++) {
				uphsum += stack[i];
			}
			dm.UPH = long(uphsum * 180. / uphstackno);
			unloadingunitcount = 0;
		}
	}
	else {
		unloadingunitcount = 0;
		tm_gUPH.SetTime();
	}
	// TPH COUNT
	if (bit.AutoRun) {
		if (tm_gTPH.TimeOvermS(20000)) {
			tm_gTPH.SetTime();
			if (tphstackno >= 180) {
				for (int i = 0; i < 180; i++) {
					tphstack[i] = tphstack[i + 1];
				}
				tphstackno = 179;
			}
			if (unloadingTrayCount)		tphstack[tphstackno] = unloadingTrayCount;
			else						tphstack[tphstackno] = 0;
			tphstackno++;
			WORD tphsum = 0;
			for (int i = 0; i < tphstackno; i++) {
				tphsum += tphstack[i];
			}
			dm.TPH = long(tphsum * 180. / tphstackno);
			unloadingTrayCount = 0;
		}
	}
	else {
		unloadingTrayCount = 0;
		tm_gTPH.SetTime();
	}
#pragma endregion
}