#ifndef _ONEPULSE_H_
#define _ONEPULSE_H_
#include <Windows.h>

#pragma once

typedef enum {
	pmRising = 0,
	pmFalling,
	pmRisingFalling,
	pmDisabled,
	pmEnd
} OnePulseMode;

class COnePulse {
private:
	bool bOneScanPassed;
	bool bPrevCondition;
	bool bPulseValue;
	WORD wMode;

public:
	inline COnePulse()
	{
		bOneScanPassed = false;
		bPrevCondition = false;
		bPulseValue = false;
		wMode = pmRising;
	}
	inline bool Run(bool condition)
	{
		if (bOneScanPassed) {
			if (bPrevCondition != condition) {
				bPulseValue = false;
				if (wMode == pmRising) {
					if (condition) bPulseValue = true;
				}
				else if (wMode == pmFalling) {
					if (!condition) bPulseValue = true;
				}
				else if (wMode == pmRisingFalling) {
					bPulseValue = true;
				}
				else {
					bOneScanPassed = false;
					bPulseValue = false;
					wMode = pmRising;
				}
			}
			else {
				bPulseValue = false;
			}
		}
		bPrevCondition = condition;
		bOneScanPassed = true;

		return bPulseValue;
	}

	inline void SetMode(WORD m)
	{
		wMode = m;
	}

	inline WORD GetMode(void)
	{
		return wMode;
	}

	inline bool GetValue(void)
	{
		return bPulseValue;
	}
};

#endif