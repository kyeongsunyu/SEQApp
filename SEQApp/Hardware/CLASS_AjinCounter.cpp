#include "CLASS_AjinCounter.h"
#include <stdio.h>

CAjinCounter::CAjinCounter(void)
{
	DWORD uStatus;
	DWORD Code;

	if (AxlIsOpened()) {
		Code = AxcInfoIsCNTModule(&uStatus);
		if (Code == AXT_RT_SUCCESS) {
			if (uStatus == STATUS_EXIST) {
				long lModuleCounts;
				Code = AxcInfoGetModuleCount(&lModuleCounts);
				if (Code == AXT_RT_SUCCESS) {
					printf("Number of CNT Module : %d\n", lModuleCounts);
				}
				else
					printf("AxcInfoGetModuleCounts() : ERRORcode 0x%x\n", Code);

				//CNT Ã¤³ÎÀÇ °³¼ö¸¦ È®ÀÎ
				long lChCounts;
				for (int ModuleNo = 0; ModuleNo < lModuleCounts; ModuleNo++)
				{
					Code = AxcInfoGetChannelCount(ModuleNo, &lChCounts);
					if (Code == AXT_RT_SUCCESS)
						//printf("%d¹øÂ° ¸ðµâ : CNT Ã¤³Î %d°³ \n", ModuleNo, lChCounts);
					if (Code != AXT_RT_SUCCESS)
						printf("AxcnfoGetChannelcount()) : ERROR code 0x%x\n", Code);
				}
				//µî·ÏµÇ¾î ÀÖ´Â ÀüÃ¼ CNT Ã¤³ÎÀÇ °³¼ö¸¦ ¹ÝÈ¯
				long lCNTChannelCounts;
				Code = AxcInfoGetTotalChannelCount(&lCNTChannelCounts);
				//printf("µî·ÏµÇ¾î ÀÖ´Â ÀüÃ¼ CNTÃ¤³Î °³¼ö´Â %d°³ÀÔ´Ï´Ù.\n", lCNTChannelCounts);

			}
		}
		else {
			printf("AxcInfoIsCNTModule() : ERROR ( Return FALSE ) code 0x%x\n", Code);
		}
	}
}
CAjinCounter::~CAjinCounter(void)
{

}

void CAjinCounter::TriggerEnable(long chNum)
{
	AxcTriggerSetEnable(chNum, TRUE);
}
void CAjinCounter::TriggerDisable(long chNum)
{
	AxcTriggerSetEnable(chNum, FALSE);
}
void CAjinCounter::SetActualPos(long chNum, double pos)
{
	AxcStatusSetActPos(chNum, pos);
}
void CAjinCounter::TriggerOut(long chNum, BOOL OnOff)
{
	AxcTriggerSetOutput(chNum, OnOff);
}
void CAjinCounter::SetTriggerPosition(long chNum, DWORD trigNum, double dPos[8], double dUpper)
{
	//DWORD dAbsPos[10] = { 0, };
	//for (int i = 0; i < 8; i++) {
	//	dAbsPos[i] = (DWORD)dPos[i];
	//}
	//// ÀÎÄÚ´õ ÀÔ·Â ¹æ½ÄÀ» 2»ó 4Ã¼¹è·Î ¼³Á¤
	//AxcSignalSetEncInputMethod(0, 0x3); 	

	//// CNT Ã¤³ÎÀÇ ÇöÀç À§Ä¡ Á¤º¸¸¦ ÃÊ±âÈ­ ÇÑ´Ù. ÇÊ¿ä µû¶ó Offset °ªÀ» ¼³Á¤ÇÒ ¼ö ÀÖ´Ù.
	//
	//AxcTriggerSetEnable(chNum, FALSE);	//Æ®¸®°Å Ãâ·Â ½ÅÈ£¸¦ Disable ÇÑ´Ù.
	//AxcTriggerSetFunction(chNum, 0x2);	//Æ®¸®°Å Ãâ·Â ±â´ÉÀ» Àý´ë À§Ä¡ ¸ðµå·Î ¼³Á¤ÇÑ´Ù.
	//WORD wData;
	//AxcKeGetCommandData16(0, 22, &wData);
	//AxcKeSetCommandData16(0, 150, wData|2);

	//AxcTriggerSetBlockUpperPos(0, dUpper);	// ¹üÀ§ ÁöÁ¤
	//AxcTriggerSetBlockLowerPos(0, 0);
	//
	//AxcTriggerSetLevel(chNum, 1);		//Æ®¸®°Å Ãâ·Â ·¹º§À» ¼³Á¤ÇÑ´Ù.
	//AxcTriggerSetTime(chNum, 10);		//Æ®¸®°Å Ãâ·Â ÆÞ½º ÆøÀ» 1mSec·Î ¼³Á¤ÇÑ´Ù.
	//AxcTriggerSetAbs(chNum, trigNum, dAbsPos, 1); // Æ®¸®°Å À§Ä¡ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
	////AxcTriggerSetEnable(chNum, TRUE);



	DWORD dAbsPos[10] = { 0, };
	for (int i = 0; i < 8; i++) {
		dAbsPos[i] = (DWORD)dPos[i];
	}
	AxcSignalSetEncInputMethod(chNum, 0x3);

	// 0번 채널 Trigger Level [High] 설정
	AxcTriggerSetLevel(chNum, 1);
	// 0번 채널 Trigger [절대 위치 모드]로 설정
	AxcTriggerSetFunction(chNum, 2);
	// 0번 채널 Trigger [비활성화]
	AxcTriggerSetEnable(chNum, 0);
	// 0번 채널 레지스터 설정
	WORD wData;
	AxcKeGetCommandData16(chNum, 22, &wData);
	AxcKeSetCommandData16(chNum, 150, wData | 2);
	// 0번 채널 Trigger 펄스폭 [10usec] 설정
	AxcTriggerSetTime(chNum, 10);
	// 0번 채널 Trigger 상한위치 [1000] 설정
	AxcTriggerSetBlockUpperPos(chNum, dUpper);
								  
	// 0번 채널 Trigger 하한위치 [0] 설정
	AxcTriggerSetBlockLowerPos(chNum, 0);

	int ret = AxcTriggerSetAbs(chNum, trigNum, dAbsPos, 1);
	// 0번 채널 Trigger [활성화]
	//AxcTriggerSetEnable(0, 1);

}
