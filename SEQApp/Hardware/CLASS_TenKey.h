#ifndef _TEN_KEY_H_
#define _TEN_KEY_H_

#include "..\Func\CLASS_TIMER.h"
#include "..\Func\CLASS_OnePulse.h"

#pragma once

//typedef enum {
//	KEYDIGITSTART = 0,
//	KEYDIGIT2,
//	KEYDIGIT3,
//	KEYDIGITEND
//} TKeyDigit;
enum class TKeyDigit
{
	KEYDIGITSTART = 0,
	KEYDIGIT2,
	KEYDIGIT3,
	KEYDIGITEND
};
enum {
	KC_0 = 0x0010,
	KC_1,   // 0x0011
	KC_2,   // 0x0012
	KC_3,   // 0x0013
	KC_4,   // 0x0014
	KC_5,   // 0x0015
	KC_6,   // 0x0016
	KC_7,   // 0x0017
	KC_8,   // 0x0018
	KC_9,   // 0x0019
	KC_CLR, // 0x001a
	KC_SET, // 0x001b
	KC_F1 = 0x0021,
	KC_F2,  // 0x0022
	KC_F3,  // 0x0023
	KC_F4,  // 0x0024
	KC_F5,  // 0x0025
	KC_F6,  // 0x0026
	KC_F7,  // 0x0027
	KC_F8,  // 0x0028
	KC_F9,  // 0x0029
	KC_F0,  // 0x002a
	KC_FUN, // 0x002b
	KC_10,  // 0x002c
	KC_START = 0x0030,
	KC_STOP,// 0x0031
	KC_RST, // 0x0032
	KC_LOTEND, // 0x0033
	KC_DRY,
	KC_END
};


class CTenKey
{
private:
	BOOL bKeyPressed;
	BOOL bKeyRescan;
	BOOL bKeyOn;

	TKeyDigit wKeyDigit;
	WORD wCurKeyVal, wPrevKeyVal, wKeyVal;
	WORD wKeyCode;

	COnePulse opProcessKey;
	CRtTimer t;

	WORD wManualNumber;

public:
	CTenKey() : wCurKeyVal(0), wPrevKeyVal(0), wKeyVal(0), wKeyCode(0), wManualNumber(0)
	{
		bKeyPressed = FALSE;
		bKeyRescan = FALSE;
		bKeyOn = FALSE;
		wKeyDigit = TKeyDigit::KEYDIGIT2;
	}

	~CTenKey()
	{
	}

	BOOL ReadKey(WORD inval);
	inline void SetKeyDigit(TKeyDigit kd)
	{
		if ((TKeyDigit::KEYDIGITSTART < kd) && (kd < TKeyDigit::KEYDIGITEND)) wKeyDigit = kd;
		else wKeyDigit = TKeyDigit::KEYDIGIT2;
	}
	inline TKeyDigit GetKeyDigit(void) { return wKeyDigit; }
	int MakeKeyCode(void);


	BOOL IsKeyOn() { return bKeyOn; }   // 2nd version machine
	BOOL IsKeyPressed() { return !bKeyRescan; }
	WORD GetKeyCode(void) { return wKeyCode; }

	inline void SetManualNumber(WORD num) { wManualNumber = num; }
	inline WORD GetManualNumber(void) { return wManualNumber; }

};

#endif