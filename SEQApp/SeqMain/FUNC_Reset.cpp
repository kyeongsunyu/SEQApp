#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"

//////////////////////////////////////////////////////////////////////////
void CSeqMain::DRVRESETIFDRVERR(void)
{
	for (int motionNum = 1; motionNum <= totalAxisCnt; motionNum++) {
		if (MTAxis[motionNum]->idrvalm || !MTAxis[motionNum]->IsServoOn) {
			if ((MTAxis[motionNum]->MotorType == 1) || (MTAxis[motionNum]->MotorType == 2) || (MTAxis[motionNum]->MotorType == 5)) {
				MTAxis[motionNum]->SetAlarmEnable(DISABLE);
				MTAxis[motionNum]->SetAlarmClearOn();
				MTAxis[motionNum]->MotorAlarmResetOn.SetTime();
			}
			else {	// step motor (SANYO DENKI)
				MTAxis[motionNum]->SetAlarmClearOff();
				MTAxis[motionNum]->MotorAlarmResetOn.SetTime();
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void CSeqMain::KeyReset(void)
{
	//if (tm_gSystemOn.TimeOvermS(1000)) {
	//	_ON(oSystemReady);
	//}

	DRVRESETIFDRVERR();

	if ((errorcode[0] == 0) && bit.AllCycleStop) {
		bit.PAutoStop = 0;
	}

	if (bit.LotEndMem) {
		bit.LotEnd = 0;
		bit.LotEndMem = 0;

		MachineStatus.UnitInCnt = 0;
		MachineStatus.UnitOutCnt = 0;

		strcpy(LotInfo.strLotID, "");
		LotInfo.nLotCount = 0;

		CSeqMain* seqMain = CSeqMain::GetInstance();
		assert(seqMain != nullptr);
		seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_LOTEND_CLAR, 0, NULL);
	}

	// PNEUMATIC 
	/*ioErrSawPkAirKnifeUpDn.Reset();
	ioErrPallet1UpDn.Reset();
	ioErrPallet2UpDn.Reset();
	ioErrTrayPkLeftClampOpenClose.Reset();
	ioErrTrayPkRightClampOpenClose.Reset();
	ioErrGoodElev1LockUnlock.Reset();
	ioErrGoodElev2LockUnlock.Reset();
	ioErrNGElevLockUnlock.Reset();
	ioErrRewElevLockUnlock.Reset();

	ioErrEmptyTrayPkLeftClampOpenClose.Reset();
	ioErrEmptyTrayPkRightClampOpenClose.Reset();
	ioErrEmptyElev1LockUnlock.Reset();
	ioErrEmptyElev2LockUnlock.Reset();
	ioErrEmptyElev3LockUnlock.Reset();*/

	/*if (SAFETYON()) {
		bit.SafetyReset = 1;
	}*/


	/*int nEmptyPkCheck = EmptyPkTrayCheck();
	if (bit.Err_EmptyPkFrontTrayCheck){
		if (nEmptyPkCheck == TRAY_CHECK_ON ||
			nEmptyPkCheck == TRAY_CHECK_OFF) {
			bit.Err_EmptyPkFrontTrayCheck = 0;
		}
	}
	if (bit.Err_EmptyPkRearTrayCheck){
		if (nEmptyPkCheck == TRAY_CHECK_ON ||
			nEmptyPkCheck == TRAY_CHECK_OFF) {
			bit.Err_EmptyPkRearTrayCheck = 0;
		}
	}

	int nTrayPkCheck = TrayPkTrayCheck();
	if (bit.Err_TrayPkFrontTrayCheck) {
		if (nTrayPkCheck == TRAY_CHECK_ON ||
			nTrayPkCheck == TRAY_CHECK_OFF) {
			bit.Err_TrayPkFrontTrayCheck = 0;
		}
	}
	if (bit.Err_TrayPkRearTrayCheck) {
		if (nTrayPkCheck == TRAY_CHECK_ON ||
			nTrayPkCheck == TRAY_CHECK_OFF) {
			bit.Err_TrayPkRearTrayCheck = 0;
		}
	}*/


	//if (bit.FrontPkPkgPickUp1 && AINOFF(iFrontPkVacOn1) && bIsPkZUp(FRONT_PK, 0)) {
	//	bit.FrontPkPkgPickUp1 = 0;
	//	_OFF(oFrontPkVacOn1);
	//	_ON(oFrontPkVacOff1);
	//}
	//if (bit.FrontPkPkgPickUp2 && AINOFF(iFrontPkVacOn2) && bIsPkZUp(FRONT_PK, 1)) {
	//	bit.FrontPkPkgPickUp2 = 0;
	//	_OFF(oFrontPkVacOn2);
	//	_ON(oFrontPkVacOff2);
	//}
	//if (bit.FrontPkPkgPickUp3 && AINOFF(iFrontPkVacOn3) && bIsPkZUp(FRONT_PK, 2)) {
	//	bit.FrontPkPkgPickUp3 = 0;
	//	_OFF(oFrontPkVacOn3);
	//	_ON(oFrontPkVacOff3);
	//}
	//if (bit.FrontPkPkgPickUp4 && AINOFF(iFrontPkVacOn4) && bIsPkZUp(FRONT_PK, 3)) {
	//	bit.FrontPkPkgPickUp4 = 0;
	//	_OFF(oFrontPkVacOn4);
	//	_ON(oFrontPkVacOff4);
	//}
	//if (bit.FrontPkPkgPickUp5 && AINOFF(iFrontPkVacOn5) && bIsPkZUp(FRONT_PK, 4)) {
	//	bit.FrontPkPkgPickUp5 = 0;
	//	_OFF(oFrontPkVacOn5);
	//	_ON(oFrontPkVacOff5);
	//}
	//if (bit.FrontPkPkgPickUp6 && AINOFF(iFrontPkVacOn6) && bIsPkZUp(FRONT_PK, 5)) {
	//	bit.FrontPkPkgPickUp6 = 0;
	//	_OFF(oFrontPkVacOn6);
	//	_ON(oFrontPkVacOff6);
	//}
	//if (bit.FrontPkPkgPickUp7 && AINOFF(iFrontPkVacOn7) && bIsPkZUp(FRONT_PK, 6)) {
	//	bit.FrontPkPkgPickUp7 = 0;
	//	_OFF(oFrontPkVacOn7);
	//	_ON(oFrontPkVacOff7);
	//}
	//if (bit.FrontPkPkgPickUp8 && AINOFF(iFrontPkVacOn8) && bIsPkZUp(FRONT_PK, 7)) {
	//	bit.FrontPkPkgPickUp8 = 0;
	//	_OFF(oFrontPkVacOn8);
	//	_ON(oFrontPkVacOff8);
	//}

	//if (bit.RearPkPkgPickUp1 && AINOFF(iRearPkVacOn1) && bIsPkZUp(REAR_PK, 0)) {
	//	bit.RearPkPkgPickUp1 = 0;
	//	_OFF(oRearPkVacOn1);
	//	_ON(oRearPkVacOff1);
	//}
	//if (bit.RearPkPkgPickUp2 && AINOFF(iRearPkVacOn2) && bIsPkZUp(REAR_PK, 1)) {
	//	bit.RearPkPkgPickUp2 = 0;
	//	_OFF(oRearPkVacOn2);
	//	_ON(oRearPkVacOff2);
	//}
	//if (bit.RearPkPkgPickUp3 && AINOFF(iRearPkVacOn3) && bIsPkZUp(REAR_PK, 2)) {
	//	bit.RearPkPkgPickUp3 = 0;
	//	_OFF(oRearPkVacOn3);
	//	_ON(oRearPkVacOff3);
	//}
	//if (bit.RearPkPkgPickUp4 && AINOFF(iRearPkVacOn4) && bIsPkZUp(REAR_PK, 3)) {
	//	bit.RearPkPkgPickUp4 = 0;
	//	_OFF(oRearPkVacOn4);
	//	_ON(oRearPkVacOff4);
	//}
	//if (bit.RearPkPkgPickUp5 && AINOFF(iRearPkVacOn5) && bIsPkZUp(REAR_PK, 4)) {
	//	bit.RearPkPkgPickUp5 = 0;
	//	_OFF(oRearPkVacOn5);
	//	_ON(oRearPkVacOff5);
	//}
	//if (bit.RearPkPkgPickUp6 && AINOFF(iRearPkVacOn6) && bIsPkZUp(REAR_PK, 5)) {
	//	bit.RearPkPkgPickUp6 = 0;
	//	_OFF(oRearPkVacOn6);
	//	_ON(oRearPkVacOff6);
	//}
	//if (bit.RearPkPkgPickUp7 && AINOFF(iRearPkVacOn7) && bIsPkZUp(REAR_PK, 6)) {
	//	bit.RearPkPkgPickUp7 = 0;
	//	_OFF(oRearPkVacOn7);
	//	_ON(oRearPkVacOff7);
	//}
	//if (bit.RearPkPkgPickUp8 && AINOFF(iRearPkVacOn8) && bIsPkZUp(REAR_PK, 7)) {
	//	bit.RearPkPkgPickUp8 = 0;
	//	_OFF(oRearPkVacOn8);
	//	_ON(oRearPkVacOff8);
	//}


	//for (int i = 0; i < 8; i++) {
	//	// front picker offset 
	//	if (bErr_FrontPk_OffsetX_Range[i]) {
	//		bErr_FrontPk_OffsetX_Range[i] = false;
	//	}
	//	
	//	if (bErr_FrontPk_OffsetY_Range[i]) {
	//		bErr_FrontPk_OffsetY_Range[i] = false;
	//	}

	//	if (bErr_FrontPk_OffsetT_Range[i]) {
	//		bErr_FrontPk_OffsetT_Range[i] = false;
	//	}

	//	if (bErr_FrontPk_OffsetX_InvalidValue[i]) {
	//		bErr_FrontPk_OffsetX_InvalidValue[i] = false;
	//	}

	//	if (bErr_FrontPk_OffsetY_InvalidValue[i]) {
	//		bErr_FrontPk_OffsetY_InvalidValue[i] = false;
	//	}

	//	if (bErr_FrontPk_OffsetT_InvalidValue[i]) {
	//		bErr_FrontPk_OffsetT_InvalidValue[i] = false;
	//	}

	//	// rear picker offset
	//	if (bErr_RearPk_OffsetX_Range[i]) {
	//		bErr_RearPk_OffsetX_Range[i] = false;
	//	}

	//	if (bErr_RearPk_OffsetY_Range[i]) {
	//		bErr_RearPk_OffsetY_Range[i] = false;
	//	}

	//	if (bErr_RearPk_OffsetT_Range[i]) {
	//		bErr_RearPk_OffsetT_Range[i] = false;
	//	}

	//	if (bErr_RearPk_OffsetX_InvalidValue[i]) {
	//		bErr_RearPk_OffsetX_InvalidValue[i] = false;
	//	}

	//	if (bErr_RearPk_OffsetY_InvalidValue[i]) {
	//		bErr_RearPk_OffsetY_InvalidValue[i] = false;
	//	}

	//	if (bErr_RearPk_OffsetT_InvalidValue[i]) {
	//		bErr_RearPk_OffsetT_InvalidValue[i] = false;
	//	}

	//}

	//////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 10; i++) {
		errorcode[i] = 0;
	}

	ErrorProcedure();

	_OFF(oBuzzer1);

	cntbuzzer = 0;

	if (!errorcode[0] || (errorcode[0] >= 0x013f)) {
		bit.PAutoStop = 0;
	}
}

