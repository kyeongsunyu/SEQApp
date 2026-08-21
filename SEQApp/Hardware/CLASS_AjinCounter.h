#ifndef _CLASS_COUNTER_H_
#define _CLASS_COUNTER_H_

#pragma once
#include <stddef.h>
#include "..\..\Library\AXL(Library)\C, C++\AXA.h"
#include "..\..\Library\AXL(Library)\C, C++\AXHS.h"
#include "..\..\Library\AXL(Library)\C, C++\AXM.h"
#include "..\..\Library\AXL(Library)\C, C++\AXC.h"
#include "..\..\Library\AXL(Library)\C, C++\AXL.h"
#include "..\..\Library\AXL(Library)\C, C++\AXD.h"
#include "..\..\Library\AXL(Library)\C, C++\AXDev.h"
class CAjinCounter
{

public:
	CAjinCounter();
	~CAjinCounter();

	void TriggerEnable(long chNum);
	void TriggerDisable(long chNum);
	void SetActualPos(long chNum, double pos);
	void TriggerOut(long chNum, BOOL OnOff);
	void SetTriggerPosition(long chNum, DWORD trigNum, double dPos[8], double dUpper);
};

#endif