#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include <Windows.h>
#include <stdio.h>
#include "..\..\Library\AXL(Library)\C, C++\AXL.h"
#include "..\..\Library\AXL(Library)\C, C++\AXC.h"
#include "..\..\Library\AXL(Library)\C, C++\AXHS.h"


#pragma once
class CAjinTrigger
{
private:
	long lCntChannelCounts;

public:
	CAjinTrigger();
	~CAjinTrigger();

	bool SetTriggerActPos(int nTableNo, double fActPos , double fUPP);
	bool SetTriggerEncReverse(int nTableNo, bool bRevers);

	bool SetTriggerOnOff(int nModNo, int nTableNo, bool bEnable);
	bool SetTriggerOutPort(int nModNo, int nTableNo, int nTrigOutPortNo);
	bool SetTriggerConfig(int nModNo, int nTableNo, int nEncoderPortNo, int nTrigOutPortNo, double fPulsWidthUS);
	bool StartTrigger(int nModNo, int nTableNo, int nTrigCount, double fTrigStartPos, double fTrigDistance);

};

#endif
