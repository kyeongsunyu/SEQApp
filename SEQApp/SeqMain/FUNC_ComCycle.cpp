#include "..\pch.h"
#include "CLASS_Main.h"
#include <random>

//////////////////////////////////////////////////////////////////////////
void CSeqMain::CommonCycle(void)
{
	CommonTimer();

	LotEndProcess_Cycle();
	TowerLamp_CycleC();
	Buzzer_CycleC();
	AllHomeC();

#pragma region CYCLE
#pragma endregion
	
#pragma region HOME_CYCLE
	// Motor Homming..
#pragma endregion
}
