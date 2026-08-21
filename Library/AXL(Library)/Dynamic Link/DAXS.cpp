#include "stdafx.h"
#include "DAXS.h"

HINSTANCE    g_hAXS = NULL;
funcAxsInfoGetPort                       *AxsInfoGetPort;
funcAxsInfoGetPortEx                     *AxsInfoGetPortEx;
funcAxsInfoIsSerialModule                *AxsInfoIsSerialModule;
funcAxsInfoIsInvalidPortNo               *AxsInfoIsInvalidPortNo;
funcAxsInfoGetPortStatus                 *AxsInfoGetPortStatus;
funcAxsInfoGetPortCount                  *AxsInfoGetPortCount;
funcAxsInfoGetFirstPortNo                *AxsInfoGetFirstPortNo;
funcAxsInfoGetBoardFirstPortNo           *AxsInfoGetBoardFirstPortNo;
funcAxsPortOpen                          *AxsPortOpen;
funcAxsPortClose                         *AxsPortClose;
funcAxsPortSetCommState                  *AxsPortSetCommState;
funcAxsPortGetCommState                  *AxsPortGetCommState;
funcAxsPortSetCommTimeouts               *AxsPortSetCommTimeouts;
funcAxsPortGetCommTimeouts               *AxsPortGetCommTimeouts;
funcAxsPortClearCommError                *AxsPortClearCommError;
funcAxsPortSetCommBreak                  *AxsPortSetCommBreak;
funcAxsPortClearCommBreak                *AxsPortClearCommBreak;
funcAxsPortPurgeComm                     *AxsPortPurgeComm;
funcAxsPortWriteFile                     *AxsPortWriteFile;
funcAxsPortReadFile                      *AxsPortReadFile;
funcAxsPortGetOverlappedResult           *AxsPortGetOverlappedResult;
funcAxsPortGetLastError                  *AxsPortGetLastError;
funcAxsPortSetLastError                  *AxsPortSetLastError;


BOOL LoadAXS()
{
    g_hAXS    = LoadLibrary("Axl.dll");
    if (g_hAXS)
    {
        AxsInfoGetPort                      = (funcAxsInfoGetPort *)GetProcAddress(g_hAXS, "AxsInfoGetPort");
	    AxsInfoGetPortEx                    = (funcfuncAxsInfoGetPortEx *)GetProcAddress(g_hAXS, "funcAxsInfoGetPortEx");
	    AxsInfoIsSerialModule               = (funcAxsInfoIsSerialModule *)GetProcAddress(g_hAXS, "AxsInfoIsSerialModule");
	    AxsInfoIsInvalidPortNo              = (funcAxsInfoIsInvalidPortNo *)GetProcAddress(g_hAXS, "AxsInfoIsInvalidPortNo");
	    AxsInfoGetPortStatus                = (funcAxsInfoGetPortStatus *)GetProcAddress(g_hAXS, "AxsInfoGetPortStatus");
	    AxsInfoGetPortCount                 = (funcAxsInfoGetPortCount *)GetProcAddress(g_hAXS, "AxsInfoGetPortCount");
	    AxsInfoGetFirstPortNo               = (funcAxsInfoGetFirstPortNo *)GetProcAddress(g_hAXS, "AxsInfoGetFirstPortNo");
	    AxsPortOpen                         = (funcAxsPortOpen *)GetProcAddress(g_hAXS, "AxsPortOpen");
	    AxsPortClose                        = (funcAxsPortClose *)GetProcAddress(g_hAXS, "AxsPortClose");
	    AxsPortSetCommState                 = (funcAxsPortSetCommState *)GetProcAddress(g_hAXS, "AxsPortSetCommState");
	    AxsPortGetCommState                 = (funcAxsPortGetCommState *)GetProcAddress(g_hAXS, "AxsPortGetCommState");
	    AxsPortSetCommTimeouts              = (funcAxsPortSetCommTimeouts *)GetProcAddress(g_hAXS, "AxsPortSetCommTimeouts");
	    AxsPortGetCommTimeouts              = (funcAxsPortGetCommTimeouts *)GetProcAddress(g_hAXS, "AxsPortGetCommTimeouts");
	    AxsPortClearCommError               = (funcAxsPortClearCommError *)GetProcAddress(g_hAXS, "AxsPortClearCommError");
	    AxsPortSetCommBreak                 = (funcAxsPortSetCommBreak *)GetProcAddress(g_hAXS, "AxsPortSetCommBreak");
	    AxsPortClearCommBreak               = (funcAxsPortClearCommBreak *)GetProcAddress(g_hAXS, "AxsPortClearCommBreak");
	    AxsPortPurgeComm                    = (funcAxsPortPurgeComm *)GetProcAddress(g_hAXS, "AxsPortPurgeComm");
	    AxsPortWriteFile                    = (funcAxsPortWriteFile *)GetProcAddress(g_hAXS, "AxsPortWriteFile");
	    AxsPortReadFile                     = (funcAxsPortReadFile *)GetProcAddress(g_hAXS, "AxsPortReadFile");
	    AxsPortGetOverlappedResult          = (funcAxsPortGetOverlappedResult *)GetProcAddress(g_hAXS, "AxsPortGetOverlappedResult");
	    AxsPortGetLastError                 = (funcAxsPortGetLastError *)GetProcAddress(g_hAXS, "AxsPortGetLastError");
	    AxsPortSetLastError                 = (funcAxsPortSetLastError *)GetProcAddress(g_hAXS, "AxsPortSetLastError");
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL FreeAXS()
{
    if (g_hAXS)
    {
        FreeLibrary(g_hAXS);
        g_hAXS = NULL;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
