#ifndef _COMPACKET_H_
#define _COMPACKET_H_

#include "CLASS_Serial.h"
#include "..\Func\CLASS_TIMER.h"



#pragma once

#define COMMANDBYTE     0
#define COM_STX         0x2
#define COM_ETX         0x3
#define COM_EOT         0x5
#define COM_ACK         0x6

#define PACKETSIZE          80
#define PARITYCHECKSIZE    (PACKETSIZE - 8)
#define PACKETDATASIZE      32

typedef union {
	char TransiveBuf[PACKETSIZE]; // Total Packet
	unsigned short TransiveWord[PACKETSIZE / 2]; // Total Packet
}TCommPacket;

class CCommPacket : public CSerial
{
private:
	int iStartIndex;
	int iEndIndex;
	int iInCount;

	BOOL bIsPacketExist;
	BOOL bSingleConnectionOnly;

	TCommPacket WrittenPacket;
	CRtTimer tmRecv;
public:
	CCommPacket(BOOL singleConnectionOnly = TRUE);
	CCommPacket(TCHAR* portName, int baud, BOOL singleConnectionOnly = TRUE);
	~CCommPacket();

	inline int GetInCount() { return iInCount; }

	inline BOOL IsPacketExist() { return bIsPacketExist; }

	int WriteCommPacket(char packet[], int n_size);

	int Thread();

	void(*CommServer)(char packet[], CCommPacket* Sender);
};

#endif
