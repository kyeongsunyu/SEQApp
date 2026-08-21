#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"

#define INKEYCH 0
#define OUTNUMCH 2
#define INKEYMASK 0x1fff


//////////////////////////////////////////////////////////////////////////
void CSeqMain::OutManualNumber(WORD num)
{
//	if(AINON(iautomode)||AINOFF(imanualmode)) return;
//	if(!AIRERR()){
	if (Key10.GetKeyDigit() == TKeyDigit::KEYDIGIT3) {
		_OUT.ofunnum100 = ~(num / 100);
		if ((num / 100) != 1) {
			_OUT.ofunnum100 = 0x0;//0xf;
		}
		else {
			_OUT.ofunnum100 = 0xf;//0xe;
		}
	}
	num %= 100;
	_OUT.ofunnuml = ~(num % 10);
	_OUT.ofunnumh = ~(num / 10);
	//	}
}

void CSeqMain::KeySetProcess(void)
{
	if( /* (!AIRERR() && !EMERON() && */!bit.AutoRun && !bit.AllHome && !dm.SystemInitialize || (ManualNumber == 0)) {  // && not auto
		CHOUT(OUTNUMCH, CHIN(OUTNUMCH) & ~0x0fff);
		tm_gManualNumberOff.SetTime();
		if (Key10.GetManualNumber() == 0) {
			if (!bit.AutoRun/*&&tmManualNumberOff.TimeOvermS(100)*/) {
				//				pFileLog->LOG_MSG_F(LT_OPERATION,"TenKeyNum %d Pressed",ManualNumber);
				KeyReset();
			}
		}
		else {
			//			pFileLog->LOG_MSG_F(LT_OPERATION,"TenKeyNum %d Pressed",ManualNumber);
			ManualTenkeyOperation();
		}
	}
}
void CSeqMain::TenKeyProcess(void)
{
	if (bit.AutoRun) {
		CHOUT(OUTNUMCH, CHIN(OUTNUMCH) & ~0x0fff);
		//		return;
	}

	if (Key10.ReadKey((CHIN(INKEYCH)) & INKEYMASK)) {
		switch (Key10.MakeKeyCode()) {
		case KC_0:
		case KC_1:
		case KC_2:
		case KC_3:
		case KC_4:
		case KC_5:
		case KC_6:
		case KC_7:
		case KC_8:
		case KC_9:
			ManualNumber *= 10;  // shift to upper level
			ManualNumber += (Key10.GetKeyCode() % 0x10);
			if (Key10.GetKeyDigit() == TKeyDigit::KEYDIGIT3) {
				ManualNumber %= 1000;
				if (ManualNumber >= 200) {
					ManualNumber %= 100;
				}
			}
			else {
				ManualNumber %= 100;
			}
			Key10.SetManualNumber(ManualNumber);
			OutManualNumber(ManualNumber);
			break;
		case KC_CLR:
			if (!bTenKeyJog) {
				ManualNumber = 0;
				Key10.SetManualNumber(ManualNumber);
				OutManualNumber(ManualNumber);
			}
			break;
		case KC_SET:
			if (!bTenKeyJog) {
				KeySetProcess();
			}
			break;
		case KC_START:
		{
			sprintf(strFileLog, "%s", "START LAMP BUTTON PRESSED");
			LOG_TRACE(strFileLog);

			SEQ_RSP seq_rsp;
			memset(&seq_rsp, 0x00, sizeof(SEQ_RSP));

			if (errorcode[0] && errorcode[0] < 0x013f) {
				seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
				seq_rsp.nResult = RESPONSE_NAK;
				strcpy(seq_rsp.strResultMsg, "Clear Alarm at First");
			}
			else if (!strcmp(strUserName, "")) {
				seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
				seq_rsp.nResult = RESPONSE_NAK;
				sprintf(seq_rsp.strResultMsg, "There is no User Information. Do log in");
			}
			else if (!strcmp(LotInfo.strLotID, "")) {
				seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
				seq_rsp.nResult = RESPONSE_NAK;
				sprintf(seq_rsp.strResultMsg, "Input Lot Information.");
			}
			else {
				seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
				seq_rsp.nResult = RESPONSE_ACK;

				AutoStart();
				printf("SEQ_START\n");
				
				sprintf(strFileLog, "%s", "SEQ_START");
				LOG_TRACE(strFileLog);

			}
			SendCopyDataToMMI(seq_rsp.nMsgNo, sizeof(SEQ_RSP), (void*)&seq_rsp);
		}
			break;
		case KC_STOP:
		{
			sprintf(strFileLog, "%s", "STOP LAMP BUTTON PRESSED");
			LOG_TRACE(strFileLog);

			SEQ_RSP seq_rsp;
			memset(&seq_rsp, 0x00, sizeof(SEQ_RSP));

			seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			seq_rsp.nResult = RESPONSE_ACK;
			SendCopyDataToMMI(seq_rsp.nMsgNo, sizeof(SEQ_RSP), (void*)&seq_rsp);

			AutoStop();
			printf("RESET LAMP BUTTON PRESSED\n");;

		}
			break;
		case KC_RST:
		{
			sprintf(strFileLog, "%s", "RESET LAMP BUTTON PRESSED");
			LOG_TRACE(strFileLog);

			KeyReset();
			printf("RESET LAMP BUTTON PRESSED\n");

			//SEQ_RSP seq_rsp;
			//memset(&seq_rsp, 0x00, sizeof(SEQ_RSP));

			//if (bit.AutoRun) {
			//	seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			//	seq_rsp.nResult = RESPONSE_NAK;
			//	sprintf(seq_rsp.strResultMsg, "Auto Run 중입니다. RESET 할수 없습니다");
			//}
			//else {
			//	seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			//	seq_rsp.nResult = RESPONSE_ACK;

			//	KeyReset();
			//	printf("RESET LAMP BUTTON PRESSED\n");
			//}

			//SendCopyDataToMMI(seq_rsp.nMsgNo, sizeof(SEQ_RSP), (void*)&seq_rsp);
		}
			break;
		case KC_LOTEND:
		{
			sprintf(strFileLog, "%s", "LOTEND LAMP BUTTON PRESSED\n");
			LOG_TRACE(strFileLog);

			SEQ_RSP seq_rsp;
			memset(&seq_rsp, 0x00, sizeof(SEQ_RSP));

			//if (bit.AutoRun) {
			//	seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			//	seq_rsp.nResult = RESPONSE_NAK;
			//	sprintf(seq_rsp.strResultMsg, "Auto Run 중입니다. LOT END 할수 없습니다");
			//}
			//else {
				seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
				seq_rsp.nResult = RESPONSE_ACK;
				bit.ButtonLotEnd = 1;
				printf("WM_SEQ_OPERATION_REQ : SEQ_LOTEND\n");
			//}

			SendCopyDataToMMI(seq_rsp.nMsgNo, sizeof(SEQ_RSP), (void*)&seq_rsp);
		}
			break;
		case KC_DRY:
		{
			if (!bit.AllDry) {
				bit.AllDry = 1;
			}
			else {
				bit.AllDry = 0;
			}
		}
//		pFileLog->LOG_MSG(LT_OPERATION,"DRY BUTTON PRESSED");
		break;
		default:
			break;
		}
	}

	if (bTenKeyJog) {
		//if (!AIRERR()) {
			if (Key10.IsKeyOn()) {
				if (Key10.GetKeyCode() == KC_CLR) {
					if (!bit.TenkeyJogMove) {
						TenKeyJogMove(MINUS);
						bit.TenkeyJogMove = 1;
					}
				}
				else if (Key10.GetKeyCode() == KC_SET) {
					if (!bit.TenkeyJogMove) {
						TenKeyJogMove(PLUS);
						bit.TenkeyJogMove = 1;
					}
				}
			}
		/*	else {
				MTAxis[tenkeyJogmtno + 1]->MTEStop();
				MTAxis[tenkeyJogmtno + 1]->omove = 0;
				bit.TenkeyJogMove = 0;
			}
		}*/
	}

	if (!bit.AutoRun && tm_gManualNumberOff.TimeOvermS(100)) {
		OutManualNumber(ManualNumber);
	}
	//////////////////////////////////////////////////////////////////////////
	//if (bit.KeyStartPressed) {
	//	if (optmStartBtnResetOnTmOver.Run(tm_iKeyStart_On.TimeOvermS(500))) {
	//		KeyReset();
	//		//			pFileLog->LOG_MSG(LT_OPERATION,"RESET BUTTON PRESSED");
	//	}
	//	if (optmStartBtnStartOnTmOver.Run(tm_iKeyStart_On.TimeOvermS(1500))) {
	//		if (!bit.AutoRun) {
	//			AutoStart();
	//			bit.KeyStartPressed = 0;
	//			//				pFileLog->LOG_MSG(LT_OPERATION,"START BUTTON PRESSED");
	//		}
	//	}
	//}

	//if (optmStartBtnResetOnTmOver.Run(tm_iKeyStart_On.TimeOvermS(500))) {
	//	KeyReset();
	//	LOG_TRACE("RESET BUTTON PRESSED");
	//}

	if (optmStartBtnStartOnTmOver.Run(AINON(iKeyStart) && tm_iKeyStart_On.TimeOvermS(1*00))) {
		if (!bit.AutoRun) {
			AutoStart();
			bit.KeyStartPressed = 0;
			LOG_TRACE("START BUTTON PRESSED");
		}
	}

	if (optmStartBtnResetOnTmOver.Run(AINON(iKeyReset) && tm_iKeyReset_On.TimeOvermS(100))) {
		KeyReset();
		LOG_TRACE("RESET BUTTON PRESSED");
	}

	if (AINON(iKeyStop)) {
		AutoStop();
		LOG_TRACE("STOP BUTTON PRESSED");
	}


	/*if (bit.AllMotionDone &&
		optmDoorOpenBtnOnTmOver.Run(AINON(iKeyDoorOpen) && tm_iKeyDoorOpen_On.TimeOvermS(500))) {
		_ON(oDoorOpen);
		_ON(oEmptyDoorOpen);
	}*/

	if (dm.MmiButtonOperation == 1) {
		KeyReset();
		Sleep(500);
		AutoStart();
		dm.MmiButtonOperation = 0;
		LOG_TRACE("MMI Operation AutoStart()");
	}
	if (dm.MmiButtonOperation == 2) {
		AutoStop();
		dm.MmiButtonOperation = 0;
		LOG_TRACE("MMI Operation AutoStop()");
	}
	if (dm.MmiButtonOperation == 3) {
		KeyReset();
		dm.MmiButtonOperation = 0;
		LOG_TRACE("MMI Operation KeyReset()");
	}

	
	//////////////////////////////////////////////////////////////////////////
}

