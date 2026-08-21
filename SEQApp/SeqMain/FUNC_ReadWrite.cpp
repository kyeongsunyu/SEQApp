#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"



//////////////////////////////////////////////////////////////////////////
void CSeqMain::Read_All(void)
{
	//for (int i = 0; i < AjinIO->uInputCount; i++) {
	//	uiobuf.wiobuf[i] = (unsigned short int)AjinIO->READINPUT(i);
	//}
	dm.MachineSpeed = MachineSpeed;
	uiobuf.wiobuf[0] = (WORD)AjinIO->READINPUT(0);		// EL1889	IN CH 00
	uiobuf.wiobuf[1] = (WORD)AjinIO->READINPUT(1);		// EL1889	IN CH 01
	
}

void CSeqMain::Write_All(void)
{
	int iAddress = 0;
	WORD wData = 0;

	//for (int i = 0; i < AjinIO->uOutputCount; i++) {
	//	iAddress = i + AjinIO->uOutputStartAddress;
	//	wData = uiobuf.wiobuf[iAddress];
	//	AjinIO->WRITE(iAddress, wData);
	//}

	wData = uiobuf.wiobuf[2];	// EL2889	OUT CH 00
	AjinIO->WRITE(2, wData);

	wData = uiobuf.wiobuf[3];	// EL2889	OUT CH 01
	AjinIO->WRITE(3, wData);
	
}

void CSeqMain::OffAllOutput(void)
{
	//int iAddress = 0;

	//for (int i = 0; i < AjinIO->uOutputCount; i++) {
	//	iAddress = i + AjinIO->uOutputStartAddress;
	//	uiobuf.wiobuf[iAddress] = 0;
	//	AjinIO->WRITE(i, 0);
	//}
	AjinIO->WRITE(2, 0);
	AjinIO->WRITE(3, 0);
}



