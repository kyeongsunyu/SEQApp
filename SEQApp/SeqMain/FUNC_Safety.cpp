#include "..\pch.h"
#include "CLASS_Main.h"


//////////////////////////////////////////////////////////////////////////
void CSeqMain::MotorSafetyFunction(void)
{
	if (/*EMERON() || */!bit.DeviceDataReceived)	return;

	//if (!SAFETYON()) {
	//	//if (!MTLdElev->fMotorPause) {
	//	//	Motor_Pause(MTLdElev, DECEL_STOP);
	//	//	if (!MTLdElev->IsStop)
	//	//		LOG_TRACE("DOOR OPENED : MTLdElev MOTOR PAUSE");
	//	//}

	//	bit.SafetyReset = 0;
	//}

	//if (bit.SafetyReset) {
	//	if (SAFETYON()) {
	//		//if (MTLdElev->fMotorPause) {
	//		//	if (MTLdElev->imrs) {
	//		//		Motor_Adjust(MTLdElev);
	//		//		LOG_TRACE("SAFETY CLOSED : MTLdElev MOTOR PAUSE RELEASED");
	//		//	}
	//		//}


	//		bit.SafetyReset = 0;
	//	}
	//}

//	if (bit.AutoRun) {
		//if (BINON(iLdLightCurtain)) {
		//	if (!MTLdElev->IsStop) {
		//		Motor_Pause(MTLdElev, DECEL_STOP);
		//	}
		//}
		//else if (BINOFF(iLdLightCurtain) && tm_iLdLightCurtain_Off.TimeOvermS(2000)) {
		//	if (MTLdElev->fMotorPause) {
		//		Motor_Adjust(MTLdElev);
		//	}
		//}

//	}
}