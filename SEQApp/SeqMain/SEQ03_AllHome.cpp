#include "..\pch.h"
#include "CLASS_Main.h"
#include "Define\DEFINE_MotorPosition.h"

//////////////////////////////////////////////////////////////////////////
void CSeqMain::AllHomeC(void)
{
	if (bit.AutoRun || !bit.AllHome) return;

	////////////////////////////////////////////////////
	// Door Check
	//if (OUTON(oDoorOpen)) {
	//	_OFF(oDoorOpen);
	//	return;
	//}
	//else if(OUTOFF(oDoorOpen) && tm_oDoorOpen_Off.TimeOvermS(1000)){
	//	if (AINOFF(iDoorFront)) {
	//		NOTIFY_MSG notify_msg;
	//		memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//		sprintf(notify_msg.strMsg, "Front Door Opened. Close the Door");
	//		SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//		bit.AllHome = 0;
	//		return;
	//	}
	//	else if (AINOFF(iDoorRear)) {
	//		NOTIFY_MSG notify_msg;
	//		memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//		sprintf(notify_msg.strMsg, "Rear Door Opened. Close the Door");
	//		SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//		bit.AllHome = 0;
	//		return;
	//	}
	//	else if (AINOFF(iDoorSide)) {
	//		NOTIFY_MSG notify_msg;
	//		memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//		sprintf(notify_msg.strMsg, "Side Door Opened. Close the Door");
	//		SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//		bit.AllHome = 0;
	//		return;
	//	}
	//}

	//if (OUTON(oEmptyDoorOpen)) {
	//	_OFF(oEmptyDoorOpen);
	//	return;
	//}
	//else if (OUTOFF(oEmptyDoorOpen) && tm_oEmptyDoorOpen_Off.TimeOvermS(1000)) {
	//	if (AINOFF(iEmptyDoorFront)) {
	//		NOTIFY_MSG notify_msg;
	//		memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//		sprintf(notify_msg.strMsg, "Empty Tray Front Door Opened. Close the Door");
	//		SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//		bit.AllHome = 0;
	//		return;
	//	}
	//	else if (AINOFF(iEmptyDoorSideRear)) {
	//		NOTIFY_MSG notify_msg;
	//		memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//		sprintf(notify_msg.strMsg, "Empty Tray Rear or Side Door Opened. Close the Door");
	//		SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//		bit.AllHome = 0;
	//		return;
	//	}
	//}

	//if (AINOFF(iDoorFront) || AINOFF(iDoorRear) || AINOFF(iDoorSide) ||
	//	AINOFF(iEmptyDoorFront) || AINOFF(iEmptyDoorSideRear)) {
	//	return;
	//}

	////////////////////////////////////////////////////
	// imrs is the "this axis has found its origin" flag. Reaching the else
	// below already means it is clear, so the home command belongs there
	// unconditionally. The inner "if (imrs)" that used to sit there could
	// never be true, and the home command was never issued from here.
	// AXIS 01 MTStageX
	if (!bMTAxisHomeFinished[0]) {
		if (MTStageX->imrs) bMTAxisHomeFinished[0] = true;
		else                MTStageXHomeM();
	}
	// AXIS 02 MTStageY
	if (!bMTAxisHomeFinished[1]) {
		// This branch set index 0, not 1, so axis 2 never recorded its own
		// completion and axis 1's flag could be set by the wrong axis.
		if (MTStageY->imrs) bMTAxisHomeFinished[1] = true;
		else                MTStageYHomeM();
	}

	// One flag per axis, so the loop runs to the axis count. It stopped at
	// index 0, which let "all home" complete on the first axis alone.
	bool allHomeDone = true;
	for (int n = 0; n < (int)totalAxisCnt; n++)
		allHomeDone &= bMTAxisHomeFinished[n];

	//////////////////////////////
	if (allHomeDone) {
		bit.AllHome = 0;
		SendCopyDataToMMI(WM_SEQ_TO_MMI_ALLHOME_COMPLETE, 0, NULL);
		sprintf(strFileLog, "%s", "All Home Finish");
		LOG_TRACE(strFileLog);
	}
}

void CSeqMain::AllHomeM(void)
{
	if (bit.AllHome)	return;

	MTStageXHomeM();
	MTStageYHomeM();	
	//NOTIFY_MSG notify_msg;
	//if (AINOFF(iGoodElev1Door) && tm_iGoodElev1Door_Off.TimeOvermS(200)) {
	//	memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//	sprintf(notify_msg.strMsg, "GOOD Tray 1 Elevator Door Opened. Close the Door");
	//	SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return;
	//}
	//if (AINOFF(iGoodElev2Door) && tm_iGoodElev2Door_Off.TimeOvermS(200)) {
	//	memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//	sprintf(notify_msg.strMsg, "GOOD Tray 2 Elevator Door Opened. Close the Door");
	//	SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return;
	//}
	//if (AINOFF(iRewElevDoor) && tm_iRewElevDoor_Off.TimeOvermS(200)) {
	//	memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//	sprintf(notify_msg.strMsg, "Rework Tray Elevator Door Opened. Close the Door");
	//	SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return;
	//}
	//if (AINOFF(iNGElevDoor) && tm_iNGElevDoor_Off.TimeOvermS(200)) {
	//	memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//	sprintf(notify_msg.strMsg, "NG Tray Elevator Door Opened. Close the Door");
	//	SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return;
	//}
	//if (AINOFF(iEmptyElev1Door) && tm_iEmptyElev1Door_Off.TimeOvermS(200)) {
	//	memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//	sprintf(notify_msg.strMsg, "EMPTY Tray 1 Elevator Door Opened. Close the Door");
	//	SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return;
	//}
	//if (AINOFF(iEmptyElev2Door) && tm_iEmptyElev2Door_Off.TimeOvermS(200)) {
	//	memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//	sprintf(notify_msg.strMsg, "EMPTY Tray 2 Elevator Door Opened. Close the Door");
	//	SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return;
	//}
	//if (AINOFF(iEmptyElev3Door) && tm_iEmptyElev3Door_Off.TimeOvermS(200)) {
	//	memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//	sprintf(notify_msg.strMsg, "EMPTY Tray 3 Elevator Door Opened. Close the Door");
	//	SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return;
	//}

	// Motor bMTAxisHomeFinished clear..
	for (int mtno = 0; mtno < totalAxisCnt; mtno++) {
		MTAxis[mtno+1]->imrs = 0;
		bMTAxisHomeFinished[mtno] = false;
	}
	bit.AllHome = 1;

	sprintf(strFileLog, "%s", "All Home Start");
	LOG_TRACE(strFileLog);
}






