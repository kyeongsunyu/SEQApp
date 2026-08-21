#include "..\pch.h"
#include "Define\DEFINE_MotorPosition.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"



//////////////////////////////////////////////////////////////////////////
void CSeqMain::AutoRun(void)
{
	if (bit.PAutoStop) {
		bit.AutoRun = 0;
		bit.PAutoStop = 1;
		return;
	}
}