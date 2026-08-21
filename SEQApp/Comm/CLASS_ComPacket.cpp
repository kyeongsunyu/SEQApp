#include "..\pch.h"
#include "CLASS_ComPacket.h"



CCommPacket::CCommPacket(BOOL singleConnectionOnly) : CSerial()
{
	iStartIndex = 0;
	iEndIndex = 0;
	iInCount = 0;
	bIsPacketExist = FALSE;
	CommServer = NULL;
	bSingleConnectionOnly = singleConnectionOnly;
}

CCommPacket::CCommPacket(TCHAR* portName, int baud, BOOL singleConnectionOnly) :CSerial(portName, baud)
{
	iStartIndex = 0;
	iEndIndex = 0;
	iInCount = 0;
	bIsPacketExist = FALSE;
	CommServer = NULL;
	bSingleConnectionOnly = singleConnectionOnly;
}

CCommPacket::~CCommPacket()
{
}
int CCommPacket::WriteCommPacket(char packet[], int n_size)
{
	return WriteToComm((BYTE*)packet, n_size);
}
//남은 Queue 겟수를 리턴한다. 에러나면 -1을 리턴...
// 에러나는경우. -> Queue의 남은 겟수가 0일때 Read를 하면 -1을 리턴..

int CCommPacket::Thread()
{
	static int readsize = 0;
	static int retsize = 0;
	static BYTE buffer[256];

	retsize = ReadFromComm((BYTE*)&buffer[readsize], PACKETSIZE);
	if (retsize > 0) {
		CommServer((char*)&buffer[readsize], this);
	}
	return retsize;
}
