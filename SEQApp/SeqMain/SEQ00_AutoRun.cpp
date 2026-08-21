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
		bit.PreStartInit = 0;
		return;
	}

	if (!bit.PreStartInit) return;


//	LotEndCheck();
}