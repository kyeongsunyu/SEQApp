#include "..\pch.h"
#include "CLASS_AjinIO.h"

#define AXT_OUT_START_ADDRESS	20

#define AXT_SMC_2V01					0x01				// CAMC-5M, 2 Axis
#define AXT_SMC_2V02					0x02				// CAMC-FS, 2 Axis
#define AXT_SMC_1V01					0x03				// CAMC-5M, 1 Axis
#define AXT_SMC_1V02					0x04				// CAMC-FS, 1 Axis
#define AXT_SMC_2V03					0x05				// CAMC-IP, 2 Axis
#define AXT_SMC_4V51					0x33				// MCX314,  4 Axis
#define AXT_SMC_2V53					0x35				// PMD, 2 Axis
#define AXT_SMC_2V54					0x36				// MCX312,  2 Axis
#define AXT_SIO_DI32					0x97				// Digital IN  32점
#define AXT_SIO_DO32P					0x98				// Digital OUT 32점
#define AXT_SIO_DB32P					0x99				// Digital IN 16점 / OUT 16점
#define AXT_SIO_DO32T					0x9E				// Digital OUT 16점, Power TR 출력
#define AXT_SIO_DB32T					0x9F				// Digital IN 16점 / OUT 16점, Power TR 출력
#define AXT_SIO_AI4R					0xA1				// A1h(161) : AI 4Ch, 12 bit
#define AXT_SIO_AI16H					0xA3				// A3h(163) : AI 4Ch, 16 bit
#define AXT_SIO_AO4R					0xA2				// A2h(162) : AO 4Ch, 12 bit
#define AXT_SIO_AO8H					0xA4				// A4h(164) : AO 4Ch, 16 bit
#define AXT_COM_234R					0xD3				// COM-234R
#define AXT_COM_484R					0xD4				// COM-484R

DWORD	AxdInfoGetInputModuleCount(long* lpCount);
DWORD	AxdInfoGetOutputModuleCount(long* lpCount);
DWORD	AxmTriggerSetBlockByEvent(long lAxisNo, DWORD dwEventSignal, double dPeriod, double dTrigTime, long lTrigLevel, DWORD dwSelect, DWORD dwOnce);
long	FLOAT_To_INT(double data);

CAjinIO::~CAjinIO()
{
	if (Isct2dMode()) return;
	if (AxlIsOpened()) {
		for (int i = 0; i < uOutputCount; i++) {
			uAddress = (uOutputStartAddress + i) / 2;
			uOffset = (uOutputStartAddress + i) % 2;
			AxdoWriteOutportDword(uAddress, uOffset, 0);
		}
	}
}

CAjinIO::CAjinIO():uInputCount(0),uMaxBaseBoard(0),uOutputCount(0),uOutputStartAddress(0),uct2dMode(0)
{
	DWORD	uModuleID = 0;
	long	lInModuleCnt = 0, lOutModuleCnt = 0;
	DWORD   dwStatus;
	uAddress = 0;
	uOffset = 0;
	if (AxlIsOpened()) {
		AxdInfoIsDIOModule(&dwStatus);
		if (dwStatus == STATUS_NOTEXIST) {
			//	AxlClose();
			printf("DIO is not founded\n");
			uOutputStartAddress = 1;
			uInputCount = 2;
			uOutputCount = 2;
		}
		else if (dwStatus == STATUS_EXIST) {
			AxdInfoGetInputModuleCount(&lInModuleCnt);
			AxdInfoGetOutputModuleCount(&lOutModuleCnt);

			uOutputStartAddress = (unsigned short int)lInModuleCnt * 2;

			uInputCount = uOutputStartAddress;
			printf("\nDI32 Card Initialize Complete [%hu] CH.........", uOutputStartAddress);

			uOutputCount = (unsigned short int)(lOutModuleCnt * 2);
			printf("\nDO32 Card Initialize Complete [%hu] CH.........", uOutputCount);
			Setct2dMode(FALSE);
			uct2dMode = 0;
		}
	}
	else {
		Setct2dMode(TRUE);
		uct2dMode = 1;
		uDioCardCount = 4;
		uOutputStartAddress = 2;
		uInputCount = 2;
		uOutputCount = 2;
		printf("\n[INPUT/OUTPUT CARD] : INITIALIZE ct2d MODE!!!");
	}
}

DWORD CAjinIO::READINPUT(unsigned short int moduleno)
{	
	uAddress = moduleno;// CHNO / 2;
	uOffset = 0;// CHNO % 2;

	if (Isct2dMode()) return TRUE;
	DWORD readval;
	DWORD aa = AxdiReadInportWord(uAddress, uOffset, &readval);

	return readval;
}
DWORD CAjinIO::READOUTPUT(unsigned short int moduleno)
{
	uAddress = moduleno;// moduleno / 2;
	uOffset = 0;// moduleno % 2;

	if (Isct2dMode()) return TRUE;

	DWORD outval;
	AxdoReadOutportWord(uAddress, uOffset, &outval);
	return outval;
}

bool CAjinIO::WRITE(unsigned short int moduleno, unsigned short int Value)
{
	uAddress = moduleno;// CHNO / 2;
	uOffset = 0;// CHNO % 2;

	if(Isct2dMode()) return TRUE;

	AxdoWriteOutportWord(uAddress, uOffset, Value);

	return true;
}

void CAjinIO::ReOpen()
{
	DWORD	uModuleID = 0;
	long	lInModuleCnt = 0, lOutModuleCnt = 0;
	DWORD   dwStatus;
	if (AxlIsOpened()) {
		AxdInfoIsDIOModule(&dwStatus);
		if (dwStatus == STATUS_NOTEXIST) {
			AxlClose();
			printf("DIO is not founded\n");
		}
		else if (dwStatus == STATUS_EXIST) {
			AxdInfoGetInputModuleCount(&lInModuleCnt);
			AxdInfoGetOutputModuleCount(&lOutModuleCnt);

			uOutputStartAddress = (unsigned short int)lInModuleCnt * 2;

			uInputCount = uOutputStartAddress;
			printf("\n DI32 Card Initialize Complete [%hu] CH.........", uOutputStartAddress);

			uOutputCount = (unsigned short int)(lOutModuleCnt * 2);
			printf("\n DO32 Card Initialize Complete [%hu] CH.........", uOutputCount);
			Setct2dMode(FALSE);

		}
	}
}

#define AXIS_QUR(AXIS_NO)		(AXIS_NO % 4)
#define SCR_CMD(AXIS, CMD)		(((CMD) << (AXIS_QUR(AXIS) * 8)) | (0xCFCFCFCF & ~(0x000000FF << (AXIS_QUR(AXIS) * 8))))
#define Bound(MIN, MAX, VALUE)	((MIN) > (VALUE) ? (MIN) : (VALUE) > (MAX) ? (MAX) : VALUE)

DWORD	AxdInfoGetInputModuleCount(long* lpCount)
{
	DWORD	dwReturn = 0, dwModuleID = 0;
	long	lTotalModuleCnt = 0, lCnt = 0;
	long	lInModuleCnt = 0;

	dwReturn = AxdInfoGetModuleCount(&lTotalModuleCnt);

	for (lCnt = 0; lCnt < lTotalModuleCnt; lCnt++)
	{
		dwReturn = AxdInfoGetModule(lCnt, NULL, NULL, &dwModuleID);
		if (dwModuleID == AXT_SIO_RDI32RTEX)	lInModuleCnt++;
	}

	if (lpCount != NULL)
		*lpCount = lInModuleCnt;

	return dwReturn;
}

DWORD	AxdInfoGetOutputModuleCount(long* lpCount)
{
	DWORD	dwReturn = 0, dwModuleID = 0;
	long	lTotalModuleCnt = 0, lCnt = 0;
	long	lOutModuleCnt = 0;

	dwReturn = AxdInfoGetModuleCount(&lTotalModuleCnt);

	for (lCnt = 0; lCnt < lTotalModuleCnt; lCnt++)
	{
		dwReturn = AxdInfoGetModule(lCnt, NULL, NULL, &dwModuleID);
		if (dwModuleID == AXT_SIO_RDO32RTEX)	lOutModuleCnt++;
	}

	if (lpCount != NULL)
		*lpCount = lOutModuleCnt;

	return dwReturn;
}

DWORD	AxmTriggerSetBlockByEvent(long lAxisNo, DWORD dwEventSignal, double dPeriod, double dTrigTime, long lTrigLevel, DWORD dwSelect, DWORD dwOnce)
{
	QIEVENT		QIEvent1 = (_QIEVENT)EVENT_QINOOP, QIEvent2 = (_QIEVENT)EVENT_QINOOP;
	DWORD		dwSCRCON = 0, dwQiCommand = 0, dwRemain = 0;
	DWORD		dwEncoderInput = 0, dwData = 0, dwLevel = 0;
	long		lPulseWidth = 0, lPulse = 0;
	double		dMoveUnit = 0., dUnit = 0.;

	AxmMotGetEncInputMethod(lAxisNo, &dwEncoderInput);
	AxmMotGetMoveUnitPerPulse(lAxisNo, &dUnit, &lPulse);

	dMoveUnit = dUnit / lPulse;

	if (dwSelect == ACTUAL && (dwEncoderInput == ObverseSqr1Mode || dwEncoderInput == ReverseSqr1Mode))
	{
		dPeriod = dPeriod * 4.0;
	}

	switch (dwEventSignal)
	{
	case In0DownEdge:	QIEvent1 = EVENT_QIUIO5FALLING;	QIEvent2 = EVENT_QIUIO5RISING;	break;
	case In1DownEdge:	QIEvent1 = EVENT_QIUIO6FALLING;	QIEvent2 = EVENT_QIUIO6RISING;	break;
	case In2DownEdge:	QIEvent1 = EVENT_QIUIO7FALLING;	QIEvent2 = EVENT_QIUIO7RISING;	break;
	case In3DownEdge:	QIEvent1 = EVENT_QIUIO8FALLING;	QIEvent2 = EVENT_QIUIO8RISING;	break;
	case In0UpEdge:		QIEvent1 = EVENT_QIUIO5RISING;	QIEvent2 = EVENT_QIUIO5FALLING;	break;
	case In1UpEdge:		QIEvent1 = EVENT_QIUIO6RISING;	QIEvent2 = EVENT_QIUIO6FALLING;	break;
	case In2UpEdge:		QIEvent1 = EVENT_QIUIO7RISING;	QIEvent2 = EVENT_QIUIO7FALLING;	break;
	case In3UpEdge:		QIEvent1 = EVENT_QIUIO8RISING;	QIEvent2 = EVENT_QIUIO8FALLING;	break;
	}

	switch (lTrigLevel)
	{
	case LOW:		dwLevel = 0x00000010;	break;
	case HIGH:		dwLevel = 0x00000000;	break;
	case UNUSED:	dwLevel = 0x00000000;	break;
	case USED:		dwLevel = 0x00000000;	break;
	}

	AxmSetCommandQi(lAxisNo, QiCLRTRIG);
	AxmSetCommandData32Qi(lAxisNo, QiINITSQWrite, 0x01);

	if (dwOnce == 1)	dwRemain = QI_OPERATION_ONCE_RUN;
	else			dwRemain = QI_OPERATION_CONTINUE_RUN;

	// TRGPW 설정
	AxmGetCommandData32Qi(lAxisNo, QiTRGPWRead, &dwData);

	dwData &= 0xFFFFFFEF;	// Level 초기화
	dwData &= 0xFFFFFFFE;	// 주기모드 설정 
	dwData |= 0x00000080;	// 트리거 출력 사용 설정

	// Trigger Level
	lPulseWidth = FLOAT_To_INT((Bound(1, 50000, dTrigTime) / 1000000.0) * 39321600L) - 1;
	dwLevel |= ((lPulseWidth << 8) & 0xFFFFFF00);
	dwData |= dwLevel;

	// Trigger 주기 설정
	dwSCRCON = dwRemain |
		QI_INTERRUPT_GEN_DISABLE |
		QI_OPERATION_EVENT_AND |
		QI_SND_EVENT_AXIS(lAxisNo) |
		QI_FST_EVENT_AXIS(lAxisNo) |
		QI_OPERATION_EVENT_2(EVENT_QIBUSY) |
		QI_OPERATION_EVENT_1(QIEvent1);

	dwQiCommand = SCR_CMD(lAxisNo, QiPTRGPOSWrite);
	AxmSetScriptCaptionQi(lAxisNo, QI_SCR_REG1, dwSCRCON, dwQiCommand, FLOAT_To_INT(dPeriod / dMoveUnit));

	// Trigger Start Position
	dwSCRCON = dwRemain |
		QI_INTERRUPT_GEN_DISABLE |
		QI_OPERATION_EVENT_NONE |
		QI_SND_EVENT_AXIS(lAxisNo) |
		QI_FST_EVENT_AXIS(lAxisNo) |
		QI_OPERATION_EVENT_2(EVENT_QINOOP) |
		QI_OPERATION_EVENT_1(EVENT_QIALWAYS);

	dwQiCommand = SCR_CMD(lAxisNo, QiTRGSPWrite);
	AxmSetScriptCaptionQi(lAxisNo, QI_SCR_REG1, dwSCRCON, dwQiCommand, 0x8000000);

	// Trigger End Position
	dwSCRCON = dwRemain |
		QI_INTERRUPT_GEN_DISABLE |
		QI_OPERATION_EVENT_NONE |
		QI_SND_EVENT_AXIS(lAxisNo) |
		QI_FST_EVENT_AXIS(lAxisNo) |
		QI_OPERATION_EVENT_2(EVENT_QINOOP) |
		QI_OPERATION_EVENT_1(EVENT_QIALWAYS);

	dwQiCommand = SCR_CMD(lAxisNo, QiTRGEPWrite);
	AxmSetScriptCaptionQi(lAxisNo, QI_SCR_REG1, dwSCRCON, dwQiCommand, 0x7FFFFFF);

	// Trigger Enable
	dwSCRCON = dwRemain |
		QI_INTERRUPT_GEN_DISABLE |
		QI_OPERATION_EVENT_NONE |
		QI_SND_EVENT_AXIS(lAxisNo) |
		QI_FST_EVENT_AXIS(lAxisNo) |
		QI_OPERATION_EVENT_2(EVENT_QINOOP) |
		QI_OPERATION_EVENT_1(EVENT_QIALWAYS);

	dwQiCommand = SCR_CMD(lAxisNo, QiTRGPWWrite);
	AxmSetScriptCaptionQi(lAxisNo, QI_SCR_REG1, dwSCRCON, dwQiCommand, dwData);

	// QIEvent2에서 트리거 출력 해제
	dwSCRCON = dwRemain |
		QI_INTERRUPT_GEN_DISABLE |
		QI_OPERATION_EVENT_NONE |
		QI_SND_EVENT_AXIS(lAxisNo) |
		QI_FST_EVENT_AXIS(lAxisNo) |
		QI_OPERATION_EVENT_2(EVENT_QINOOP) |
		QI_OPERATION_EVENT_1(QIEvent2);

	dwQiCommand = SCR_CMD(lAxisNo, QiTRGPWWrite);
	AxmSetScriptCaptionQi(lAxisNo, QI_SCR_REG1, dwSCRCON, dwQiCommand, dwData & 0xFFFFFF7F);

	return AXT_RT_SUCCESS;
}

long FLOAT_To_INT(double data)
{
	long lConvData;

	data *= 10.0f;
	data += 0.5f;
	data = floor(data);
	data /= 10.0f;

	lConvData = (long)data;

	return lConvData;
}

//////////////////////////////////////////////////////////////////////

CAjinAIO::CAjinAIO()
{
	nCHList[0] = 0;
	nCHList[1] = 2;

	d_thickres = 50;
}

CAjinAIO::~CAjinAIO()
{

}

void CAjinAIO::InitCard()
{
	// 	if(InitializeAIO() == 0){
	// 		printf("Axt SIO-AI4RB Module initial error\n");
	// 	}
	DWORD dwStatus;
	DWORD Code;

	AxaInfoIsAIOModule(&dwStatus);
	if (dwStatus != STATUS_EXIST) {
		printf("AIO Module Not Exist\n");
	}

	long IModuleCounts;
	Code = AxaInfoGetModuleCount(&IModuleCounts);
	if (Code == AXT_RT_SUCCESS)
		printf("Number of AIO module: %d\n", IModuleCounts);
	else
		printf("AxaInfoGetModuleCount() : ERROR code Ox%x\n", Code);


	long IInputCounts;
	long IOutputCounts;

	long IBoardNo;
	long IModulePos;
	DWORD dwModuleID;

	for (int ModuleNo = 0; ModuleNo < IModuleCounts; ModuleNo++)
	{
		// Grasp IO channel
		Code = AxaInfoGetInputCount(ModuleNo, &IInputCounts);//입력 채널 개수 확인
		DWORD Code2 = AxaInfoGetOutputCount(ModuleNo, &IOutputCounts);//출력 채널 개수 확인
		if (Code == AXT_RT_SUCCESS || Code2 == AXT_RT_SUCCESS) {
			printf("%d Module : Input Channel %d, Output Channel %d\n", ModuleNo, IInputCounts, IOutputCounts);
		}
		if (Code != AXT_RT_SUCCESS) {
			printf("AxaInfoGetInputCounts(): Error code 0x%x\n", Code);
		}
		if (Code2 != AXT_RT_SUCCESS) {
			printf("AxoInfoGetInputCounts(): Error code 0x%x\n", Code2);
		}

		long lAdcChannelCounts;
		Code = AxaiInfoGetChannelCount(&lAdcChannelCounts);
		printf("Total Input Channel %d\n", lAdcChannelCounts);
		long lDacChannelCounts;
		Code = AxaoInfoGetChannelCount(&lDacChannelCounts);
		printf("Total Output Channel %d\n", lDacChannelCounts);

		if (AxaInfoGetModule(ModuleNo, &IBoardNo, &IModulePos, &dwModuleID) == AXT_RT_SUCCESS)
		{
			switch (dwModuleID)
			{
			case AXT_SIO_RDI32MLIII:			printf("[BD No:%d - MD No:%d] RDI32MLIII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDI32MSMLIII:		printf("[BD No:%d - MD No:%d] RDI32MSMLIII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDI32PMLIII:			printf("[BD No:%d - MD No:%d] RDI32PMLIII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDI32RTEX:			printf("[BD No:%d - MD No:%d] RDI32RTEX", IBoardNo, ModuleNo); break;
			case AXT_SIO_DI32_P:				printf("[BD No:%d - MD No:%d] DI32_P", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDI32:					printf("[BD No:%d - MD No:%d] RDI32", IBoardNo, ModuleNo); break;
			case AXT_SIO_DI32:					printf("[BD No:%d - MD No:%d] DI32", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDO32MLIII:			printf("[BD No:%d - MD No:%d] RDO32MLIII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDO32AMSMLIII:	printf("[BD No:%d - MD No:%d] RDO32AMSMLIII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDO32PMLIII:		printf("[BD No:%d - MD No:%d] RDO32PMLIII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDO16AMLII:			printf("[BD No:%d - MD No:%d] RDO16AMLII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDO16BMLII:			printf("[BD No:%d - MD No:%d] RDO16BMLII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDO32RTEX:			printf("[BD No:%d - MD No:%d] RDO32RTEX", IBoardNo, ModuleNo); break;
			case AXT_SIO_DO32T_P:				printf("[BD No:%d - MD No:%d] DO32T_P", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDO32:				printf("[BD No:%d - MD No:%d] RDO32", IBoardNo, ModuleNo); break;
			case AXT_SIO_DO32P:				printf("[BD No:%d - MD No:%d] DO32P", IBoardNo, ModuleNo); break;
			case AXT_SIO_DO32T:				printf("[BD No:%d - MD No:%d] DO32T", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDB32MLIII:			printf("[BD No:%d - MD No:%d] RDB32MLIII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDB32PMLIII:			printf("[BD No:%d - MD No:%d] RDB32PMLIII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDB128MLIIIAI:		printf("[BD No:%d - MD No:%d] RDB128MLIIIAI", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDB96MLII:			printf("[BD No:%d - MD No:%d] RDB96MLII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDB32RTEX:			printf("[BD No:%d - MD No:%d] RDB32RTEX", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDB128MLII:			printf("[BD No:%d - MD No:%d] RDB128MLII", IBoardNo, ModuleNo); break;
			case AXT_SIO_DB32P:					printf("[BD No:%d - MD No:%d] DB32P", IBoardNo, ModuleNo); break;
			case AXT_SIO_RDB32T:				printf("[BD No:%d - MD No:%d] RDB32T", IBoardNo, ModuleNo); break;
			case AXT_SIO_DB32T:					printf("[BD No:%d - MD No:%d] DB32T", IBoardNo, ModuleNo); break;
			case AXT_SIO_UNDEFINEMLIII:		printf("[BD No:%d - MD No:%d] UNDEFINEMLIII", IBoardNo, ModuleNo); break;
			case AXT_SIO_RSIMPLEIOMLII:		printf("[BD No:%d - MD No:%d] RSIMPLEIOMLII", IBoardNo, ModuleNo); break;
			default:
				printf("[BD No:%d - MD No:%d] Unknown", IBoardNo, ModuleNo);
				break;
			}
		}
	}
}

void CAjinAIO::SetTriggerMode()
{
	AxaiSetTriggerMode(0, NORMAL_MODE);
}

void CAjinAIO::ExtTriggerStart()
{
	//	AxaiExternalStartADC(0,2,nCHList);
}

int CAjinAIO::GetFIFO_Status()
{
	//	DWORD dwStatus;
	return 0;//AxaiExternalReadFifoStatus(0,&dwStatus);
}

double CAjinAIO::ReadOneVolt(int nCH)
{
	double dVolt = 0.0;
	AxaiSwReadVoltage(nCH, &dVolt);
	return dVolt;
}
