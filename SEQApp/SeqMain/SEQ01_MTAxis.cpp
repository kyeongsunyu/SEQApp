#include "..\pch.h"
#include "CLASS_Main.h"

//////////////////////////////////////////////////////////////////////////
bool CSeqMain::bJogCondition(int axisno)
{
	if (axisno < 0 || axisno > totalAxisCnt) {
		printf("Invalid axis number\n");
		return false;
	}

	if (bit.AutoRun) {
		printf("Auto Running\n");
		return false;
	}

	//if (!SAFETYON()) {
	//	CSeqMain* seqMain = CSeqMain::GetInstance();
	//	assert(seqMain != nullptr);
	//	char strDoor[32]="";
	//	//if (AINOFF(iDoor1)) {
	//	//	strcpy(strDoor, "DOOR1");
	//	//}
	//	NOTIFY_MSG notify_msg;
	//	memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//	sprintf(notify_msg.strMsg,"%s %s",strDoor, "Door Opened");
	//	seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return false;
	//}

	/*if (MTAxis[axisno + 1] == MTLoadPkX) {
		if (!MTRDY(MTLoadPkZ)) {
			
			return false;
		}
	}*/

	

	return true;
}
bool CSeqMain::bJogIndexCondition(int axisno)
{
	if (axisno < 0 || axisno > totalAxisCnt) {
		printf("Invalid axis number\n");
		return false;
	}

	if (bit.AutoRun) {
		printf("Auto Running\n");
		return false;
	}

	//if (!SAFETYON()) {
	//	//CSeqMain* seqMain = CSeqMain::GetInstance();
	//	//assert(seqMain != nullptr);
	//	//char strDoor[32]="";
	//	//if (AINOFF(iDoor1)) {
	//	//	strcpy(strDoor, "DOOR1");
	//	//}
	//	//NOTIFY_MSG notify_msg;
	//	//memset(&notify_msg, 0x00, sizeof(NOTIFY_MSG));
	//	//sprintf(notify_msg.strMsg,"%s %s",strDoor, "Door가 열려있습니다");
	//	//seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_NOTIFY, sizeof(NOTIFY_MSG), (void*)&notify_msg);
	//	return false;
	//}

	//if (MTAxis[axisno + 1] == MTMZTrfY) {
	//	if (AINON(iMZPickerDown)) {
	//		// Notify message
	//		return false;
	//	}
	//}
	//else if (MTAxis[axisno + 1] == MTMZTrfZ) {
	//	// do condition check
	//}

	return true;
}


//////////////////////////////////////////////////////////////////////////
void CSeqMain::JogMoveContinious(int axisno, int JogVel, int dir)
{
	if (!bJogCondition(axisno)) {
		return;
	}
	double dVel = (double)JogVel * MTAxis[axisno + 1]->MMI_PulseRate;

	MTAxis[axisno + 1]->CurPos = 99;
	MTAxis[axisno + 1]->NxtPos = 99;
	MTAxis[axisno + 1]->imrs = 0;

	if (dir == 1) {		// PLUS DIR
		MTAxis[axisno + 1]->Direction = 1;
		MTAxis[axisno + 1]->Speed = dVel;// JogVel* MTAxis[axisno + 1]->MMI_PulseRate;
		MTAxis[axisno + 1]->Accel = MTAxis[axisno + 1]->Speed * 5;
		MTAxis[axisno + 1]->Decel = MTAxis[axisno + 1]->Accel;
	}
	else if (dir == 0) {	// MINUS DIR
		MTAxis[axisno + 1]->Direction = -1;
		MTAxis[axisno + 1]->Speed = -dVel;// (-JogVel)* MTAxis[axisno + 1]->MMI_PulseRate;
		MTAxis[axisno + 1]->Accel = abs(MTAxis[axisno + 1]->Speed * 5);
		MTAxis[axisno + 1]->Decel = abs(MTAxis[axisno + 1]->Accel);
	}
	MTAxis[axisno + 1]->MTSCMove();
}

void CSeqMain::JogMoveRelative(int axisno, int pos, int JogVel)
{
	if (!bJogCondition(axisno)) {
		return;
	}

	MTAxis[axisno + 1]->NxtArrpos = pos;
	MTAxis[axisno + 1]->NxtPos = 99;
	MTAxis[axisno + 1]->imrs = 0;

	MTAxis[axisno + 1]->Speed = (double)JogVel * MTAxis[axisno + 1]->MMI_PulseRate;
	MTAxis[axisno + 1]->Accel = MTAxis[axisno + 1]->Speed * 5;
	MTAxis[axisno + 1]->Decel = MTAxis[axisno + 1]->Accel;

	MTAxis[axisno + 1]->MTSRMove(pos);
}

void CSeqMain::JogMoveIndex(int axisno, int idx)
{
	// index move 사용시 주의 필요, 반드시 condition check
	if (!bJogIndexCondition(axisno)) {
		return;
	}

	MTMOVE(MTAxis[axisno + 1], idx, MIDDLE);
}

//////////////////////////////////////////////////////////////////////////
#pragma region AXIS01 MTStageZ
void CSeqMain::MTStageXHomeM(void)
{

	if (MTRDY(MTStageZ)) {
		if (MTRDY(MTStageX)) {
			MTStageX->imrs = 0;
			MTStageX->NxtPos = 0;
			MTStageX->omove = 1;

		}
	}
}
void CSeqMain::MTStageYHomeM(void)
{
	if (MTRDY(MTStageZ)) {
		if (MTRDY(MTStageY)) {
			MTStageY->imrs = 0;
			MTStageY->NxtPos = 0;
			MTStageY->omove = 1;
		}
	}
}

void CSeqMain::MTStageZHomeM(void)
{

	if (MTRDY(MTStageZ)) {
		MTStageZ->imrs = 0;
		MTStageZ->NxtPos = 0;
		MTStageZ->omove = 1;
	}
}


void CSeqMain::MTStageXMoveM(void)
{
	if(MTRDY(MTStageZ)){
		if (MTRDY(MTStageX)) {
			if (MTCEP(MTStageX, STAGE_X_WAIT)) {
				MTMOVE(MTStageX, STAGE_X_PRE_WORK, AUTOSPEED);
			}
			else if (MTCEP(MTStageX, STAGE_X_PRE_WORK)) {
				MTMOVE(MTStageX, STAGE_X_WORK, AUTOSPEED);
			}
			else if (MTCEP(MTStageX, STAGE_X_WORK)) {
				MTMOVE(MTStageX, STAGE_X_WAIT, AUTOSPEED);
			}
		}
	}
}
void CSeqMain::MTStageYMoveM(void)
{
	if (MTRDY(MTStageZ)) {
		if (MTRDY(MTStageY)) {
			if (MTCEP(MTStageY, STAGE_Y_WAIT)) {
				MTMOVE(MTStageY, STAGE_Y_PRE_WORK, AUTOSPEED);
			}
			else if (MTCEP(MTStageY, STAGE_Y_PRE_WORK)) {
				MTMOVE(MTStageY, STAGE_Y_WORK, AUTOSPEED);
			}
			else if (MTCEP(MTStageY, STAGE_Y_WORK)) {
				MTMOVE(MTStageY, STAGE_Y_WAIT, AUTOSPEED);
			}
		}
	}
}
void CSeqMain::MTStageZMoveM(void)
{
	if (MTRDY(MTStageZ)) {
		if (MTCEP(MTStageZ, STAGE_Z_UP)) {
			MTMOVE(MTStageZ, STAGE_Z_PRE_AUTOFOCUS, AUTOSPEED);
		}
		else if (MTCEP(MTStageZ, STAGE_Z_PRE_AUTOFOCUS)) {
			MTMOVE(MTStageZ, STAGE_Z_AUTOFOCUS, AUTOSPEED);
		}
		else if (MTCEP(MTStageZ, STAGE_Z_AUTOFOCUS)) {
			MTMOVE(MTStageZ, STAGE_Z_UP, AUTOSPEED);
		}
	}
}
#pragma endregion

