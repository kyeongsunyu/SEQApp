#include "..\pch.h"
#include "CLASS_Main.h"

void CSeqMain::TowerLamp_CycleC(void)
{
	//if (EMERON())	return;

	bool error = false;
	for (int i = 0; i < 10; i++) {
		if (errorcode[i]) {
			errvalue[i] = errorcode[i];
			error = true;
		}
		else {
			errvalue[i] = 0;
		}
	}


	//////////////////////////////
	if (AINON(iKeyStop) || !bit.AutoRun && (errvalue[0] == 0)) 
	{
		_ON(oKeyStop);
		_OFF(oKeyReset);
		_OFF(oKeyStart);

		_ON(oTowerLampRed);
		_OFF(oTowerLampYellow);
		_OFF(oTowerLampGreen);
	}
	else if (error) 
	{
		if (errvalue[0]) 
		{
			/// TowerLamp RED Ctrl..
			switch (LampBuzzerType[errvalue[0] - 1][0]) {	// RED LAMP
			case 0:		// RED LAMP OFF	
				_OFF(oKeyStop);
				_OFF(oTowerLampRed);
				break;
			case 1:		// RED LAMP ON
				_ON(oKeyStop);
				_ON(oTowerLampRed);
				break;
			case 2:		// RED LAMP BLINK	
				if (tm_gStopBlink.TimeOvermS(500)) {
					tm_gStopBlink.SetTime();
					CPLBITMOVETOOUT(oKeyStop, OUTON(oKeyStop));
					CPLBITMOVETOOUT(oTowerLampRed, OUTON(oTowerLampRed));

				}
				break;
			default:
				_ON(oKeyStop);
				_ON(oTowerLampRed);
				break;
			}

			/// TowerLamp YELLOW Ctrl..
			switch (LampBuzzerType[errvalue[0] - 1][1]) {	// YELLOW LAMP
			case 0:		// YELLOW LAMP OFF
				_OFF(oKeyReset);
				_OFF(oTowerLampYellow);
				break;
			case 1:		// YELLOW LAMP ON
				_ON(oKeyReset);
				_ON(oTowerLampYellow);
				break;
			case 2:		// YELLOW LAMP BLINK
				if (tm_gResetBlink.TimeOvermS(500)) {
					tm_gResetBlink.SetTime();
					CPLBITMOVETOOUT(oKeyReset, OUTON(oKeyReset));
					CPLBITMOVETOOUT(oTowerLampYellow, OUTON(oTowerLampYellow));
				}
				break;
			default:
				break;
			}

			switch (LampBuzzerType[errvalue[0] - 1][2]) {	// GREEN LAMP
			case 0:		// GREEN LAMP OFF	
				_OFF(oKeyStart);
				_OFF(oTowerLampGreen);
				break;
			case 1:		// GREEN LAMP ON
				_ON(oKeyStart);
				_ON(oTowerLampGreen);
				break;
			case 2:		// GREEN LAMP BLINK
				if (tm_gStartBlink.TimeOvermS(500)) {
					tm_gStartBlink.SetTime();
					CPLBITMOVETOOUT(oKeyStart, OUTON(oKeyStart));
					CPLBITMOVETOOUT(oTowerLampGreen, OUTON(oTowerLampGreen));
				}
				break;
			default:
				break;
			}
		}
	}
	else 
	{
		_OFF(oKeyStop);
		_OFF(oKeyReset);

		_OFF(oTowerLampRed);
		_OFF(oTowerLampYellow);
	}

	BITMOVETOOUT(oKeyStart, bit.AutoRun);
	BITMOVETOOUT(oTowerLampGreen, bit.AutoRun);

//	BITMOVETOOUT(oKeyLotEnd, bit.ButtonLotEnd);
}

void CSeqMain::Buzzer_CycleC(void)
{
	BUZZERONTIME = LampBuzzerType[errorcode[0] - 1][4];
	BUZZEROFFTIME = LampBuzzerType[errorcode[0] - 1][5];

	if (BUZZERONTIME == 0) {
		BUZZERONTIME = 3500;
	}
	if (BUZZEROFFTIME == 0) {
		BUZZEROFFTIME = 1000;
	}

	//////////////////////////////
	if ((bit.BuzzerOn)) 
	{
		if (bit.NewBuzzer) {
			bit.NewBuzzer = 0;
			if (errorcode[0] == ERROR_LOTEND || errorcode[0] >= 0x0350) {
				if ((errorcode[0] >= 0x0350) && (errorcode[0] <= 0x03e5)) {
					if (errorcode[0] == 0x0355) {
						cntbuzzer = 20;
					}
					else {
						cntbuzzer = 5;
					}
				}
				else {
					cntbuzzer = LampBuzzerType[errorcode[0] - 1][3];//5;
				}
				if (!cntbuzzer) {
					cntbuzzer = 5;
				}
			}
			else {
				cntbuzzer = LampBuzzerType[errorcode[0] - 1][3];//10;
				if (!cntbuzzer) {
					cntbuzzer = 10;
				}
			}
			_ON(oBuzzer1);
			tm_gBuzzer1Blink.SetTime();
		}
		else {
			if (cntbuzzer) {
				if (OUTON(oBuzzer1)) {
					if (tm_gBuzzer1Blink.TimeOvermS(BUZZERONTIME)) {
						_OFF(oBuzzer1);
						tm_gBuzzer1Blink.SetTime();
						cntbuzzer--;
					}
				}
				else {
					if (tm_gBuzzer1Blink.TimeOvermS(BUZZEROFFTIME)) {
						_ON(oBuzzer1);
						tm_gBuzzer1Blink.SetTime();
					}
				}
			}
			else {
				bit.BuzzerOn = 0;
				_OFF(oBuzzer1);
			}
		}
	}
	else {
		_OFF(oBuzzer1);
	}
}