#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <Windows.h>

#pragma once

#define BUFF_SIZE		4096

#define ASCII_LF		0x0a
#define ASCII_CR		0x0d
#define ASCII_XON		0x11
#define ASCII_XOFF		0x13

#define MAX_BUFF_SIZE 	100
#define INQUEUE			4096
#define OUTQUEUE		4096

#define PACKET_OK		0x00
#define TIME_OVER		0x01
#define PACKET_ERROR	0x02

class CSerial {
private:
	char buff[MAX_BUFF_SIZE];
	int Count;

	TCHAR* cPPortName;
	DWORD dwBaud;

	BOOL bIsOpen;

	HANDLE hCommHandle;
	OVERLAPPED m_osRead, m_osWrite;

protected:
	int iSerialStatus;
public:
	CSerial();

	CSerial(TCHAR* PortName, int Baud);
	~CSerial();

	BOOL Open(TCHAR* PortName, int Baud);
	void Close();

	inline HANDLE GetCommHandle() { return hCommHandle; }
	inline BOOL IsOpen() { return bIsOpen; }
	inline TCHAR* GetPortName() { return cPPortName; }

	DWORD WriteToComm(BYTE* pBuff, DWORD nToWrite);
	DWORD ReadFromComm(BYTE* pBuff, DWORD nToRead);
	inline int GetSerialStatus() { return iSerialStatus; }
};

#endif