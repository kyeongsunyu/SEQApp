#include "..\pch.h"
#include "CLASS_IOError.h"


bool CIOError::GetInput1(void)
{
	return bInput1;
}
void CIOError::SetInput1(bool in)
{
	bInput1 = in;
}
bool CIOError::GetInput2(void)
{
	return bInput2;
}
void CIOError::SetInput2(bool in)
{
	bInput2 = in;
}
void CIOError::SetInput(bool f, bool s)
{
	bInput1 = f;
	bInput2 = s;
}
bool CIOError::GetOutput1(void) 
{
	return bOutput1; 
}
void CIOError::SetOutput1(bool in)
{
	bOutput1 = in; 
}
bool CIOError::GetOutput2(void)
{
	return bOutput2;
}
void CIOError::SetOutput2(bool in)
{
	bOutput2 = in;
}
void CIOError::SetOutput(bool f, bool s)
{
	bOutput1 = f;
	bOutput2 = s;
}
bool CIOError::IsError(void)
{ 
	return bIsError;
}
bool CIOError::IsTimerOn(void)
{
	return bIsTimerOn;
}
WORD CIOError::GetErrorCode()
{ 
	return wErrorCode; 
}
void CIOError::SetErrorCode(WORD ec)
{
	wErrorCode = ec; 
}
WORD CIOError::ErrorCheck(bool i1, bool i2, bool o1, bool o2)
{
	if (((o1 || (!i2)) && (o2 || (!i1))) || (i1 && i2)) {
		if (bIsTimerOn) {
			// Timer Over Check..
			if (bIsError) {
				return eAlreadyError;
			}
			else if (cTimer.TimeOvermS(dwTimerLimit)) {
				bIsError = TRUE;
				return eNewError;
			}
			else {
				return eCounting;
			}
		}
		else {
			// Timer Set
			cTimer.SetTime();
			bIsTimerOn = TRUE;
			return eCountStart;
		}
	}
	else {
		bIsTimerOn = FALSE;
		return eNoError;
	}
	//		return bIsError;
}

WORD CIOError::ErrorCheck(bool i1, bool o1)	// added by s.c.k
{											// for 1 sensor, single sole
	if ((o1 && (!i1)) || ((!o1) && i1)) {
		if (bIsTimerOn) {
			// Timer Over Check..
			if (bIsError) {
				return eAlreadyError;
			}
			else if (cTimer.TimeOvermS(dwTimerLimit)) {
				bIsError = TRUE;
				return eNewError;
			}
			else {
				return eCounting;
			}
		}
		else {
			// Timer Set
			cTimer.SetTime();
			bIsTimerOn = TRUE;
			return eCountStart;
		}
	}
	else {
		bIsTimerOn = FALSE;
		return eNoError;
	}
	//		return bIsError;
}
void CIOError::Reset(void)
{
	bIsError = FALSE;
	bIsTimerOn = FALSE;
}