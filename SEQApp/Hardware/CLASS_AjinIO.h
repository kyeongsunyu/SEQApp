#ifndef _CLASS_DIO_H_
#define _CLASS_DIO_H_

#pragma once
#include "..\..\Library\AXL(Library)\C, C++\AXA.h"
#include "..\..\Library\AXL(Library)\C, C++\AXHS.h"
#include "..\..\Library\AXL(Library)\C, C++\AXM.h"
#include "..\..\Library\AXL(Library)\C, C++\AXDev.h"
#include "..\..\Library\AXL(Library)\C, C++\AXL.h"
#include "..\..\Library\AXL(Library)\C, C++\AXD.h"

//////////////////////////////////////////////////////////////////////////
class CAjinIO
{
private:
	unsigned short int    uAddress, uOffset, uct2dMode;
public:		//-- Decreare in valiable
//	unsigned short int    uIOValue;
	unsigned short int    uMaxBaseBoard, uOutputStartAddress, uInputCount, uOutputCount;
	long    uDioCardCount=0;

public:
	CAjinIO();
	virtual ~CAjinIO();
	unsigned short int	 Isct2dMode() { return uct2dMode; }
	void Setct2dMode(unsigned char uOnOff) { uct2dMode = uOnOff; }
	DWORD  READINPUT(unsigned short int CHNO);
	DWORD  READOUTPUT(unsigned short int CHNO);
	bool WRITE(unsigned short int CHNO, unsigned short int Value);
	void ReOpen();
};

class CAjinAIO
{
public:
	long	nCHList[2];
	double	d_thickres;
	CAjinAIO();
	virtual ~CAjinAIO();
	void	InitCard();
	void	SetTriggerMode();
	void	ExtTriggerStart();
	int 	GetFIFO_Status();
	double	ReadOneVolt(int nCH);
};

#endif