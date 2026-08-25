#include "..\pch.h"
#include "CLASS_Main.h"



//////////////////////////////////////////////////////////////////////////
void CSeqMain::LotEndCheck(void)
{
	//if (MTRDY(MTLdElev) && MTRDY(MTFrontTrayIndex) &&
	//	MTRDY(MTRearTrayIndex) && MTRDY(MTLdElev)) {
	//	if ((bISLdTrayCoverLoadingOn() && (TrayInCnt >= nTrayStockCount)) ||
	//		(dm.LotEndMMICheck == 2)) {	// lot end 처리
	//		if (AINOFF(iFrontIndexTrayDetect) && tm_iFrontIndexTrayDetect_Off.TimeOvermS(10000) &&
	//			AINOFF(iRearIndexTrayDetect) && tm_iRearIndexTrayDetect_Off.TimeOvermS(10000)) {
	//			if (bit.AllCycleStop) {
	//				bit.LotEnd = 1;
	//				bit.LotEndMem = 1;
	//				bit.LotEndCntClear = 1;
	//				bit.ButtonLotEnd = 0;
	//				dm.LotEndMMICheck = 0;
	//				_ON(oLotEnd);

	//				CSeqMain* seqMain = CSeqMain::GetInstance();
	//				assert(seqMain != nullptr);

	//				LOTEND_RESULT lotend_result;
	//				memset(&lotend_result, 0x00, sizeof(LOTEND_RESULT));

	//				sprintf(lotend_result.strLotID, "%s", LotInfo.strLotID);
	//				lotend_result.nLotCount = LotInfo.nLotCount;
	//				lotend_result.TotalUnitCnt = MachineStatus.TotalUnitCnt;
	//				if (LotInfo.nLotCount != MachineStatus.TotalUnitCnt) {
	//					lotend_result.nResult = 1;
	//				}
	//				else {
	//					lotend_result.nResult = 0;
	//				}
	//				sprintf(lotend_result.strUserName, "%s", strUserName);
	//				seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_LOTEND_RESULT, sizeof(LOTEND_RESULT), (void*)&lotend_result);
	//			}
	//		}
	//	}
	//	else if (AINOFF(iLdTrayDetect) && tm_iLdTrayDetect_Off.TimeOvermS(30000) &&
	//		AINOFF(iLdTrayCoverDetect) && tm_iLdTrayCoverDetect_Off.TimeOvermS(30000) ||
	//		bit.ButtonLotEnd) {
	//		if (AINOFF(iFrontIndexTrayDetect) && tm_iFrontIndexTrayDetect_Off.TimeOvermS(5000) &&
	//			AINOFF(iRearIndexTrayDetect) && tm_iRearIndexTrayDetect_Off.TimeOvermS(5000) ||
	//			bit.ButtonLotEnd) {
	//			if (dm.LotEndMMICheck == 0) {	// lot end 처리 확인
	//				dm.LotEndMMICheck = 1;
	//			}
	//		}
	//	}

	//	if (dm.LotEndMMICheck == 99) {	// lot end 처리하시겠습니까?
	//		if (AINON(iLdTrayDetect) && tm_iLdTrayDetect_On.TimeOvermS(200) ||
	//			AINON(iLdTrayCoverDetect) && tm_iLdTrayCoverDetect_On.TimeOvermS(200)) {
	//			dm.LotEndMMICheck = 0;
	//		}
	//	}
	//	else if (dm.LotEndMMICheck == 3) {	// lot end cacel
	//		bit.ButtonLotEnd = 0;
	//		dm.LotEndMMICheck = 0;
	//	}
	//}
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::LotEndProcess_Cycle(void)
{
	if (!bit.LotEnd || bit.AutoRun) return;

	if (tm_gAllCycleStop.TimeOvermS(3000)) {
		//AllHomeM();

		//_tzset();
		//time(&lendtime);
		//tm_LotEnd = localtime(&lendtime);
		//strftime(lotendtime, 128, "%H:%M:%S", tm_LotEnd);
		////		printf("[%s]\n",lotendtime);

		////		pFileLog->LOTINFO_LOTEND_MSG_F("LotStart=%s",lotstarttime);
		////		pFileLog->LOTINFO_LOTEND_MSG_F("LotEnd=%s",lotendtime);

		//memset(LotInfo.strLotID, 0, sizeof(LotInfo.strLotID));

		bit.LotEnd = 0;
	}
}