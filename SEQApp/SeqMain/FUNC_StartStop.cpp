#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"
#include "Define\DEFINE_WinMsg.h"



//////////////////////////////////////////////////////////////////////////
void CSeqMain::AutoStart(void)
{
	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	NOTIFY_MSG notify_msg;
	memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));

	
	if (errorcode[0] && errorcode[0] < 0x0350) {
		sprintf(notify_msg.strMsg, "Clear Alarm First");
		seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
		return;
	}

	//if (!strcmp(LotInfo.strLotID, "")) {
	//	sprintf(notify_msg.strMsg, "LOT ID를 먼저 입력하세요.");
	//	seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return;
	//}

	if (bit.AutoRun) return;

	ErrorProcedure();

	ManualNumber = 0;


	//if (IsCartDetect(200) != CART_STATE_DETECT) {
	//	bit.Error_CartDetect = 1;
	//	return;
	//}
	 
	if (dm.ScreenNo == 11 || dm.ScreenNo == 12) {
		//_OFF(oDoorOpen);
		//_OFF(oEmptyDoorOpen);
		bit.AutoRun = 1;
		bit.PAutoStop = 0;
	}
	else {
		NOTIFY_MSG notify_msg;
		memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
		sprintf(notify_msg.strMsg, "MMI NOT Auto Screen! ");
		SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);

		bit.NotAutoScreen = 1;
	}

	if (bit.LotEndCntClear) {
		_tzset();
		time(&lstarttime);
		tm_LotStart = localtime(&lstarttime);
		strftime(lotstarttime, 128, "%H:%M:%S", tm_LotStart);
//		printf("[%s]\n",lotstarttime);

		//MachineStatus.inputcnt = 0;
		//MachineStatus.TrayInputCnt = 0;
		//MachineStatus.TrayOutCnt = 0;
		//MachineStatus.VisionTriggerCnt = 0;
		//memset(MachineStatus.TrayInUnitCnt, 0x00, sizeof(int) * 200);

		bit.LotEndCntClear = 0;
	}
}

void CSeqMain::AutoStop(void)
{
	bit.PAutoStop = 1;

	//_ON(oDoorOpen);
	//_ON(oEmptyDoorOpen);
	//if (bit.Run_MTWfEjectXHome) {
	//	MTWfEjectX->MTEStop();
	//	bit.Run_MTWfEjectXHome = 0;
	//}

}