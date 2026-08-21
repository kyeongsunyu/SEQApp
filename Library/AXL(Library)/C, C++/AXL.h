/****************************************************************************
*****************************************************************************
**
** File Name
** ----------
**
** AXL.H
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Library Header File
** 
**
*****************************************************************************
*****************************************************************************
**
** Source Change Indices
** ---------------------
** 
** (None)
**
**
*****************************************************************************
*****************************************************************************
**
** Website
** ---------------------
**
** http://www.ajinextek.com
**
*****************************************************************************
*****************************************************************************
*/


#ifndef __AXT_AXL_H__
#define __AXT_AXL_H__

#include "AXHS.h"
//#include "AXA.h"
//#include "AXD.h"
//#include "AXM.h"

#ifdef __cplusplus
extern "C" {
#endif    //__cplusplus



//========== Library initialization =================================================================================

// Library initialization
DWORD   __stdcall AxlOpen(long lIrqNo);


// Do not reset to hardware chip when library is initialized.
DWORD   __stdcall AxlOpenNoReset(long lIrqNo);


// Exit from library use
BOOL    __stdcall AxlClose();


// Verify if the library is initialized
BOOL    __stdcall AxlIsOpened();


// Use Interrupt
DWORD   __stdcall AxlInterruptEnable();


// Not use Interrput
DWORD   __stdcall AxlInterruptDisable();



//========== library and base board information =================================================================================
// Verify the number of registered base board
DWORD   __stdcall AxlGetBoardCount(long *lpBoardCount);
// Verify the library version, szVersion[64]
DWORD   __stdcall AxlGetLibVersion(char *szVersion);

// Verify Network models Module Status
DWORD   __stdcall AxlGetModuleNodeStatus(long lBoardNo, long lModulePos);

// Verify Board Status
DWORD   __stdcall AxlGetBoardStatus(long lBoardNo);

// return Configuration Lock status of Network product.
// *wpLockMode  : DISABLE(0), ENABLE(1)
DWORD   __stdcall AxlGetLockMode(long lBoardNo, WORD* wpLockMode);


// Function to check whether all slaves of specified network type are operational
// NETWORK_TYPE_ALL(0)
// NETWORK_TYPE_RTEX(1)
// NETWORK_TYPE_MLII(2)
// NETWORK_TYPE_MLIII(3)
// NETWORK_TYPE_SIIIH(4)
// NETWORK_TYPE_ECAT(5)
DWORD   __stdcall AxlIsConnectedAllSlaves(DWORD uNetworkType);

DWORD   __stdcall AxlGetReturnCodeInfo(DWORD dwReturnCode, long lReturnInfoSize, long* lpRecivedSize, char* szReturnInfo);
//========== Log level =================================================================================
// Set message level to be output to EzSpy
// uLevel : 0 - 3 Set
// LEVEL_NONE(0)    : ALL Message don't Output
// LEVEL_ERROR(1)   : Error Message Output
// LEVEL_RUNSTOP(2) : Run/Stop relative Message Output during Motion.
// LEVEL_FUNCTION(3): ALL Message don't Output
DWORD   __stdcall AxlSetLogLevel(DWORD uLevel);
// Verify message level to be output to EzSpy
DWORD   __stdcall AxlGetLogLevel(DWORD *upLevel);


//========== MLIII =================================================================================
// The API for start searching each module of network product.
DWORD   __stdcall AxlScanStart(long lBoardNo, long lNet);
// The API for connect all modules of each board.
DWORD   __stdcall AxlBoardConnect(long lBoardNo, long lNet);
// The API for disconnect all modules of each board.
DWORD   __stdcall AxlBoardDisconnect(long lBoardNo, long lNet);

DWORD   __stdcall AxlReadFanSpeed(long lBoardNo, double *dpFanSpeed);


//========== EzSpy =================================================================================
// EzSpy User Log(Max length : 200 Bytes)
DWORD   __stdcall AxlEzSpyUserLog(char* szUserLog);


#ifdef __cplusplus
}
#endif    //__cplusplus

#endif    //__AXT_AXL_H__
