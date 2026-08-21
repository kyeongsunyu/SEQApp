#include "..\pch.h"
#include "CLASS_Serial.h"

CSerial::CSerial()
{
	cPPortName = NULL;
	dwBaud = 0;
	bIsOpen = FALSE;
}
CSerial::CSerial(TCHAR* PortName, int Baud)
{
	cPPortName = NULL;
	dwBaud = 0;
	bIsOpen = FALSE;

	Open(PortName, Baud);
}
CSerial::~CSerial()
{
	cPPortName = NULL;
	dwBaud = 0;
	bIsOpen = FALSE;
}
BOOL CSerial::Open(TCHAR* PortName, int Baud)
{
	COMMTIMEOUTS timeouts;
	DCB dcb;

	bIsOpen = FALSE;

	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	if (!(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) return FALSE;


	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	if (!(m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) return FALSE;


	cPPortName = PortName;
	hCommHandle = CreateFile(cPPortName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL);

	if (hCommHandle == (HANDLE)-1) return FALSE;

	SetCommMask(hCommHandle, EV_RXCHAR);
	SetupComm(hCommHandle, INQUEUE, OUTQUEUE);
	PurgeComm(hCommHandle, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	GetCommTimeouts(hCommHandle, &timeouts);
	dwBaud = Baud;
	timeouts.ReadIntervalTimeout = 100;// 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;//0;
	timeouts.ReadTotalTimeoutConstant = 0;//0;
	timeouts.WriteTotalTimeoutMultiplier = 2 * CBR_9600 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;//1000;//0;

	SetCommTimeouts(hCommHandle, &timeouts);

	dcb.DCBlength = sizeof(DCB);
	GetCommState(hCommHandle, &dcb);
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;
	dcb.Parity = 0;
	dcb.StopBits = 0;
	dcb.fInX = dcb.fOutX = 1;
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;

	dcb.fBinary = 0;
	dcb.fOutxCtsFlow = 0;
	dcb.fOutxDsrFlow = 0;
	dcb.fDtrControl = 0;
	dcb.fDsrSensitivity = 0;
	dcb.fTXContinueOnXoff = 0;
	dcb.fOutX = 0;
	dcb.fInX = 0;

	if (!SetCommState(hCommHandle, &dcb))	return FALSE;

	bIsOpen = true;

	return TRUE;
}
void CSerial::Close()
{
	bIsOpen = FALSE;
	SetCommMask(hCommHandle, 0);
	PurgeComm(hCommHandle, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
	CloseHandle(hCommHandle);
}
DWORD CSerial::WriteToComm(BYTE* pBuff, DWORD nToWrite)
{
	DWORD dwWritten;
	DWORD dwError, dwErrorFlags;
	COMSTAT comstat;

	if (bIsOpen == FALSE) { return -1; }

	if (!WriteFile(hCommHandle, pBuff, nToWrite, &dwWritten, &m_osWrite)) {
		if (GetLastError() == ERROR_IO_PENDING) {
			while (!GetOverlappedResult(hCommHandle, &m_osWrite, &dwWritten, TRUE)) {
				dwError = GetLastError();
				if (dwError != ERROR_IO_INCOMPLETE) {
					ClearCommError(hCommHandle, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else {
			dwWritten = 0;
			ClearCommError(hCommHandle, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}
DWORD CSerial::ReadFromComm(BYTE* pBuff, DWORD nToRead)
{
	DWORD dwRead = nToRead, dwError, dwErrorFlags;
	BOOL ret;
	COMSTAT comstat;

	if (bIsOpen == FALSE) { return -1; }

	ret = ClearCommError(hCommHandle, &dwErrorFlags, &comstat);

	dwRead = comstat.cbInQue;

	if (dwRead > 0) {
		if (!ReadFile(hCommHandle, pBuff, nToRead, &dwRead, &m_osRead)) {
			if (GetLastError() == ERROR_IO_PENDING) {
				while (!GetOverlappedResult(hCommHandle, &m_osRead, &dwRead, TRUE)) {
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE) {
						ClearCommError(hCommHandle, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else {
				dwRead = 0;
				ClearCommError(hCommHandle, &dwErrorFlags, &comstat);
			}
		}
	}
	return dwRead;
}