#ifndef _IO_ERROR_H_
#define _IO_ERROR_H_

#include "CLASS_TIMER.h"

#pragma once
enum {
	eNoError = 0,
	eCountStart,
	eCounting,
	eNewError,
	eAlreadyError,
	eErrorEnd
};

class CIOError
{
private:
	bool bInput1;
	bool bInput2;
	bool bOutput1;
	bool bOutput2;

	bool bIsTimerOn;
	bool bIsError;

	CRtTimer cTimer;

	DWORD dwTimerLimit;
	WORD wErrorCode;

public:
	CIOError():bInput1(false),bInput2(false),bOutput1(false),bOutput2(false),dwTimerLimit(0),wErrorCode(0)
	{
		bIsTimerOn = FALSE;
		bIsError = FALSE;
	}

	CIOError(WORD ErrorCode, DWORD TimerLimit):bInput1(false), bInput2(false), bOutput1(false), bOutput2(false), dwTimerLimit(0), wErrorCode(0)
	{
		wErrorCode = ErrorCode;
		dwTimerLimit = TimerLimit;
		bIsTimerOn = FALSE;
		bIsError = FALSE;
	}

	void* (ErrorCheckFunc)(...);
	bool GetInput1(void);
	void SetInput1(bool in);
	bool GetInput2(void);
	void SetInput2(bool in);
	void SetInput(bool f, bool s);
	
	bool GetOutput1(void);
	void SetOutput1(bool in);
	bool GetOutput2(void);
	void SetOutput2(bool in);
	void SetOutput(bool f, bool s);

	bool IsError(void);
	bool IsTimerOn(void);

	WORD GetErrorCode();
	void SetErrorCode(WORD ec);

	WORD ErrorCheck(bool i1, bool i2, bool o1, bool o2);
	WORD ErrorCheck(bool i1, bool o1);

	void Reset(void);
};
#endif
