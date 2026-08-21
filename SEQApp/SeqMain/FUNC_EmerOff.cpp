#include "..\pch.h"
#include "CLASS_Main.h"

void CSeqMain::EmerOffProcess(void)
{
	OffAllOutput();
	ManualNumber = 0;
	Key10.SetManualNumber(0);

	bit.DryRun = 0;
	bit.AutoRun = 0;
	bit.AllHome = 0;
	bit.MotorTunning = 0;

	MTEMEROFF(MTStageX);
	MTEMEROFF(MTStageY);
	MTEMEROFF(MTStageZ);

}
