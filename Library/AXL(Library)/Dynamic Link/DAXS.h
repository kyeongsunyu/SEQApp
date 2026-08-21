#ifndef __AXT_DAXS_H__
#define __AXT_DAXS_H__

//#include "AXHS.h"
#include "../../AXL(Library)/C, C++/AXHS.h"
typedef DWORD    PASCAL EXPORT funcAxsInfoGetPort(long lPortNo, long *lpBoardNo, long *lpModulePos, DWORD *upModuleID);
typedef DWORD    PASCAL EXPORT funcAxsInfoGetPortEx(long lPortNo, DWORD *upModuleSubID, char* szModuleName, char* szModuleDescription);
typedef DWORD    PASCAL EXPORT funcAxsInfoIsSerialModule(DWORD *upStatus);
typedef DWORD    PASCAL EXPORT funcAxsInfoIsInvalidPortNo(long lPortNo);
typedef DWORD    PASCAL EXPORT funcAxsInfoGetPortStatus(long lPortNo);
typedef DWORD    PASCAL EXPORT funcAxsInfoGetPortCount(long *lpPortCount);
typedef DWORD    PASCAL EXPORT funcAxsInfoGetFirstPortNo(long lBoardNo, long lModulePos, long *lpPortNo);
typedef DWORD    PASCAL EXPORT funcAxsInfoGetBoardFirstPortNo(long lBoardNo, long lModulePos, long *lpPortNo);
typedef DWORD    PASCAL EXPORT funcAxsPortOpen(long lPortNo, long lBaudRate, long lDataBits, long lStopBits, long lParity, DWORD dwFlagsAndAttributes);
typedef DWORD    PASCAL EXPORT funcAxsPortClose(long lPortNo); 
typedef DWORD    PASCAL EXPORT funcAxsPortSetCommState(long lPortNo, LPDCB lpDCB);
typedef DWORD    PASCAL EXPORT funcAxsPortGetCommState(long lPortNo, LPDCB lpDCB);
typedef DWORD    PASCAL EXPORT funcAxsPortSetCommTimeouts(long lPortNo, LPCOMMTIMEOUTS lpCommTimeouts);
typedef DWORD    PASCAL EXPORT funcAxsPortGetCommTimeouts(long lPortNo, LPCOMMTIMEOUTS lpCommTimeouts);
typedef DWORD    PASCAL EXPORT funcAxsPortClearCommError(long lPortNo, LPDWORD lpErrors, LPCOMSTAT lpStat);
typedef DWORD    PASCAL EXPORT funcAxsPortSetCommBreak(long lPortNo);
typedef DWORD    PASCAL EXPORT funcAxsPortClearCommBreak(long lPortNo);
typedef DWORD    PASCAL EXPORT funcAxsPortPurgeComm(long lPortNo, DWORD dwFlags);
typedef DWORD    PASCAL EXPORT funcAxsPortWriteFile(long lPortNo, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
typedef DWORD    PASCAL EXPORT funcAxsPortReadFile(long lPortNo, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
typedef DWORD    PASCAL EXPORT funcAxsPortGetOverlappedResult(long lPortNo, LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait);
typedef DWORD    PASCAL EXPORT funcAxsPortGetLastError(DWORD *dwpErrCode);
typedef DWORD    PASCAL EXPORT funcAxsPortSetLastError(DWORD dwErrCode);

extern funcAxsInfoGetPort                       *AxsInfoGetPort;
extern funcAxsInfoGetPortEx                     *AxsInfoGetPortEx;
extern funcAxsInfoIsSerialModule                *AxsInfoIsSerialModule;
extern funcAxsInfoIsInvalidPortNo               *AxsInfoIsInvalidPortNo;
extern funcAxsInfoGetPortStatus                 *AxsInfoGetPortStatus;
extern funcAxsInfoGetPortCount                  *AxsInfoGetPortCount;
extern funcAxsInfoGetFirstPortNo                *AxsInfoGetFirstPortNo;
extern funcAxsInfoGetBoardFirstPortNo           *AxsInfoGetBoardFirstPortNo;
extern funcAxsPortOpen                          *AxsPortOpen;
extern funcAxsPortClose                         *AxsPortClose;
extern funcAxsPortSetCommState                  *AxsPortSetCommState;
extern funcAxsPortGetCommState                  *AxsPortGetCommState;
extern funcAxsPortSetCommTimeouts               *AxsPortSetCommTimeouts;
extern funcAxsPortGetCommTimeouts               *AxsPortGetCommTimeouts;
extern funcAxsPortClearCommError                *AxsPortClearCommError;
extern funcAxsPortSetCommBreak                  *AxsPortSetCommBreak;
extern funcAxsPortClearCommBreak                *AxsPortClearCommBreak;
extern funcAxsPortPurgeComm                     *AxsPortPurgeComm;
extern funcAxsPortWriteFile                     *AxsPortWriteFile;
extern funcAxsPortReadFile                      *AxsPortReadFile;
extern funcAxsPortGetOverlappedResult           *AxsPortGetOverlappedResult;
extern funcAxsPortGetLastError                  *AxsPortGetLastError;
extern funcAxsPortSetLastError                  *AxsPortSetLastError;

BOOL LoadAXS();
BOOL FreeAXS();

#endif    __AXT_DAXS_H__
