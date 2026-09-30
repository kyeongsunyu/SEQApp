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

	// The scan cycle drives the stage and the trigger output, so an emergency
	// off has to end both. Aborted rather than just flagged down, because the
	// trigger keeps running on its own until the board is told to stop - in
	// timer mode it free runs off its own clock and does not need the stage to
	// be moving at all.
	//
	// The flag comes down either way. ScanTriggerSetRecipe() refuses a recipe
	// while it is up, so a cycle left flagged running makes SEQ ignore every
	// SET that follows - the scan panel then shows the previous recipe's
	// answers and looks, from the outside, exactly like a good reading.
	if (bit.ScanTriggerRun) {
		ScanTriggerAbort("emergency off");
	}
	bit.ScanTriggerRun = 0;

	MTEMEROFF(MTStageX);
	MTEMEROFF(MTStageY);

}
