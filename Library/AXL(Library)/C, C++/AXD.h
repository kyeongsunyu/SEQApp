/****************************************************************************
*****************************************************************************
**
** File Name
** ----------
**
** AXD.H
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Digital Library Header File
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


#ifndef __AXT_AXD_H__
#define __AXT_AXD_H__

#include "AXHS.h"

#ifdef __cplusplus
extern "C" {
#endif    //__cplusplus


//========== Board and module information
// Verify if DIO module exists
DWORD    __stdcall AxdInfoIsDIOModule(DWORD *upStatus);


// Verify DIO in/output module number
DWORD    __stdcall AxdInfoGetModuleNo(long lBoardNo, long lModulePos, long *lpModuleNo);


// Verify the number of DIO in/output module
DWORD    __stdcall AxdInfoGetModuleCount(long *lpModuleCount);


// Verify the number of input contacts of specified module
DWORD    __stdcall AxdInfoGetInputCount(long lModuleNo, long *lpCount);


// Verify the number of output contacts of specified module
DWORD    __stdcall AxdInfoGetOutputCount(long lModuleNo, long *lpCount);


// Verify the base board number, module position and module ID with specified module number
DWORD    __stdcall AxdInfoGetModule(long lModuleNo, long *lpBoardNo, long *lpModulePos, DWORD *upModuleID);


// Verify specified module board : Sub ID, module name, module description
//===============================================/
// support product : EtherCAT
// upModuleSubID   : EtherCAT SubID(for distinguish between EtherCAT modules)
// szModuleName         : model name of module(50 Bytes)
// szModuleDescription  : description of module(80 Bytes)
//======================================================//
DWORD    __stdcall AxdInfoGetModuleEx(long lModuleNo, DWORD *upModuleSubID, char* szModuleName, char* szModuleDescription);

//Verify Module status of specified module board
DWORD    __stdcall AxdInfoGetModuleStatus(long lModuleNo);


//========== Verification group for input interrupt setting
// Use window message, callback API or event method in order to get interrupt message into specified module
//========= Interrupt-related function ======================================================================================
//The callback function method has the advantage that the event can be notified very quickly because the callback function is called immediately at the time of the occurrence of the event.
//But, The main process is stalled until the callback function is completely terminated.
//In other words, Care must be taken when there is work load in the callback function.
//The event method is a method of continuously detecting and processing the occurrence of an interrupt by using a thread.
//The event method has the disadvantage that system resources are occupied by thread, but it has the advantage that interrupts can be detected and processed the fastest.
//This method is not commonly used. but it is used when quick interrupt handling is main concern.
//The event method uses a specific thread to monitor the occurrence of an event, and it works independently of the main process.
//So, This is the recommended method because it enables the most efficient use of resources in a multiprocessor system.
//Use a Window message or callback function to receive interrupt message.
//(Message handle, Message ID, Callback function, Interrupt event)
//    hWnd        : Used to receive window handles and window messages. If not, enter NULL.
//    uMessage    : Massage of window handle. To not use this or use the default value, enter 0.
//    proc        : Pointer of the function to be called when an interrupt occurs. To not use this, enter NULL.
//    pEvent      : Event handling when using event method.
// Ex)
// AxdiInterruptSetModule(0, Null, 0, AxtInterruptProc, NULL);
// void __stdcall AxtInterruptProc(long lActiveNo, DWORD uFlag){
//     ... ;
// }
DWORD    __stdcall AxdiInterruptSetModule(long lModuleNo, HWND hWnd, DWORD uMessage, AXT_INTERRUPT_PROC pProc, HANDLE *pEvent);


// Set whether to use interrupt of specified module
//======================================================//
// uUse    : DISABLE(0)    // Interrupt Disable
//         : ENABLE(1)        // Interrupt Enable
//======================================================//
DWORD    __stdcall AxdiInterruptSetModuleEnable(long lModuleNo, DWORD uUse);


// Verify whether to use interrupt of specified module
//======================================================//
// *upUse  : DISABLE(0)    // Interrupt Disable
//         : ENABLE(1)        // Interrupt Enable
//======================================================//
DWORD    __stdcall AxdiInterruptGetModuleEnable(long lModuleNo, DWORD *upUse);


// Verify the position interrupt occurred
DWORD    __stdcall AxdiInterruptRead(long *lpModuleNo, DWORD *upFlag);


//========== Input interrupt rising / Verification group for setting of interrupt occurrence in falling edge
// Set the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// uValue    : DISABLE(0)
//           : ENABLE(1)
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeSetBit(long lModuleNo, long lOffset, DWORD uMode, DWORD uValue);


// Set the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// uValue    : 0x00 ~ 0x0FF
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeSetByte(long lModuleNo, long lOffset, DWORD uMode, DWORD uValue);


// Set the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// uValue    : 0x00 ~ 0x0FFFF
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeSetWord(long lModuleNo, long lOffset, DWORD uMode, DWORD uValue);


// Set the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// uValue    : 0x00 ~ 0x0FFFFFFFF
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeSetDword(long lModuleNo, long lOffset, DWORD uMode, DWORD uValue);


// Verify the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// *upValue  : 0x00 ~ 0x0FF
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeGetBit(long lModuleNo, long lOffset, DWORD uMode, DWORD *upValue);


// Verify the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// *upValue  : 0x00 ~ 0x0FF
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeGetByte(long lModuleNo, long lOffset, DWORD uMode, DWORD *upValue);


// Verify the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// *upValue  : 0x00 ~ 0x0FFFF
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeGetWord(long lModuleNo, long lOffset, DWORD uMode, DWORD *upValue);


// Verify the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// *upValue  : 0x00 ~ 0x0FFFFFFFF
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeGetDword(long lModuleNo, long lOffset, DWORD uMode, DWORD *upValue);


// Set the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// uValue    : DISABLE(0)
//           : ENABLE(1)
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeSet(long lOffset, DWORD uMode, DWORD uValue);


// Verify the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
//===============================================================================================//
// lOffset   : Offset position for input contact
// uMode     : DOWN_EDGE(0)
//           : UP_EDGE(1)
// *upValue  : DISABLE(0)
//           : ENABLE(1)
//===============================================================================================//
DWORD    __stdcall AxdiInterruptEdgeGet(long lOffset, DWORD uMode, DWORD *upValue);


//========== Verification group of input / output signal level setting
//==Verification group of input signal level setting
// Set data level by bit unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdiLevelSetInportBit(long lModuleNo, long lOffset, DWORD uLevel);


// Set data level by byte unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// uLevel      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD    __stdcall AxdiLevelSetInportByte(long lModuleNo, long lOffset, DWORD uLevel);


// Set data level by word unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// uLevel      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD    __stdcall AxdiLevelSetInportWord(long lModuleNo, long lOffset, DWORD uLevel);


// Set data level by double word unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// uLevel      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD    __stdcall AxdiLevelSetInportDword(long lModuleNo, long lOffset, DWORD uLevel);


// Verify data level by bit unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdiLevelGetInportBit(long lModuleNo, long lOffset, DWORD *upLevel);


// Verify data level by byte unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdiLevelGetInportByte(long lModuleNo, long lOffset, DWORD *upLevel);


// Verify data level by word unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdiLevelGetInportWord(long lModuleNo, long lOffset, DWORD *upLevel);


// Verify data level by double word unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdiLevelGetInportDword(long lModuleNo, long lOffset, DWORD *upLevel);


// Set data level by bit unit in Offset position of entire input contact module
//===============================================================================================//
// lOffset     : Offset position for input contact
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdiLevelSetInport(long lOffset, DWORD uLevel);


// Verify data level by bit unit in Offset position of entire input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdiLevelGetInport(long lOffset, DWORD *upLevel);


//==Verification group of output signal level setting
// Set data level by bit unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdoLevelSetOutportBit(long lModuleNo, long lOffset, DWORD uLevel);


// Set data level by byte unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD    __stdcall AxdoLevelSetOutportByte(long lModuleNo, long lOffset, DWORD uLevel);


// Set data level by word unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD    __stdcall AxdoLevelSetOutportWord(long lModuleNo, long lOffset, DWORD uLevel);


// Set data level by double word unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD    __stdcall AxdoLevelSetOutportDword(long lModuleNo, long lOffset, DWORD uLevel);


// Verify data level by bit unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdoLevelGetOutportBit(long lModuleNo, long lOffset, DWORD *upLevel);


// Verify data level by byte unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdoLevelGetOutportByte(long lModuleNo, long lOffset, DWORD *upLevel);


// Verify data level by word unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdoLevelGetOutportWord(long lModuleNo, long lOffset, DWORD *upLevel);


// Verify data level by double word unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdoLevelGetOutportDword(long lModuleNo, long lOffset, DWORD *upLevel);


// Set data level by bit unit in Offset position of entire output contact module
//===============================================================================================//
// lOffset     : Offset position for output contact
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdoLevelSetOutport(long lOffset, DWORD uLevel);


// Verify data level by bit unit in Offset position of entire output contact module
//===============================================================================================//
// lOffset     : Offset position for output contact
// *upLevel    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdoLevelGetOutport(long lOffset, DWORD *upLevel);


//========== Input / Output signal reading / writing
//==Output signal writing
// Output data by bit unit in Offset position of entire output contact module
//===============================================================================================//
// lOffset     : Offset position for output contact
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdoWriteOutport(long lOffset, DWORD uValue);


// Output data by bit unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdoWriteOutportBit(long lModuleNo, long lOffset, DWORD uValue);


// Output data by byte unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uValue      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD    __stdcall AxdoWriteOutportByte(long lModuleNo, long lOffset, DWORD uValue);


// Output data by word unit in Offset position of specified output contact module
//===============================================================================================//
// uValue      : 0x00 ~ 0x0FFFF
// lOffset     : Offset position for output contact
// uValue      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD    __stdcall AxdoWriteOutportWord(long lModuleNo, long lOffset, DWORD uValue);


// Output data by double word unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uValue      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD    __stdcall AxdoWriteOutportDword(long lModuleNo, long lOffset, DWORD uValue);

//==Output signal reading
// Read data by bit unit in Offset position of entire output contact module
//===============================================================================================//
// lOffset     : Offset position for output contact
// *upLevel    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdoReadOutport(long lOffset, DWORD *upValue);


// Read data by bit unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdoReadOutportBit(long lModuleNo, long lOffset, DWORD *upValue);


// Read data by byte unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upValue    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdoReadOutportByte(long lModuleNo, long lOffset, DWORD *upValue);


// Read data by word unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upValue    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdoReadOutportWord(long lModuleNo, long lOffset, DWORD *upValue);


// Read data by double word unit in Offset position of specified output contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upValue    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdoReadOutportDword(long lModuleNo, long lOffset, DWORD *upValue);


//==Input signal reading
// Read data level by bit unit in Offset position of entire input contact module
//===============================================================================================//
// lOffset     : Offset position for input contact
// *upValue    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdiReadInport(long lOffset, DWORD *upValue);


// Read data level by bit unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upValue    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD    __stdcall AxdiReadInportBit(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by byte unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upValue    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdiReadInportByte(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by word unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upValue    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdiReadInportWord(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by double word unit in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upValue    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//===============================================================================================//
DWORD    __stdcall AxdiReadInportDword(long lModuleNo, long lOffset, DWORD *upValue);



//== Only for MLII, M-Systems DIO(R7 series)
// Read data level by bit unit in Offset position of specified extended input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between input index.(0~15)
// *upValue    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD   __stdcall AxdReadExtInportBit(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by byte unit in Offset position of specified extended input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : offset position by byte unit between input index.(0~1)
// *upValue    : 0x00 ~ 0x0FF
//===============================================================================================//
DWORD   __stdcall AxdReadExtInportByte(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by word unit in Offset position of specified extended input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : offset position by word unit between input index.(0)
// *upValue    : 0x00 ~ 0x0FFFF
//===============================================================================================//
DWORD   __stdcall AxdReadExtInportWord(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by double word unit in Offset position of specified extended input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : offset position by dword unit between input index.(0)
// *upValue    : 0x00 ~ 0x00000FFFF
//===============================================================================================//
DWORD   __stdcall AxdReadExtInportDword(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by bit unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between output index.(0~15)
// *upValue    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD   __stdcall AxdReadExtOutportBit(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by byte unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by byte unit between output index.(0~1)
// *upValue    : 0x00 ~ 0x0FF
//===============================================================================================//
DWORD   __stdcall AxdReadExtOutportByte(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by word unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by word unit between output index.(0)
// *upValue    : 0x00 ~ 0x0FFFF
//===============================================================================================//
DWORD   __stdcall AxdReadExtOutportWord(long lModuleNo, long lOffset, DWORD *upValue);


// Read data level by double word unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by dword unit between output index.(0)
// *upValue    : 0x00 ~ 0x0000FFFF
//===============================================================================================//
DWORD   __stdcall AxdReadExtOutportDword(long lModuleNo, long lOffset, DWORD *upValue);


// Output data by bit unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between output index.(0~15)
// uValue      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD   __stdcall AxdWriteExtOutportBit(long lModuleNo, long lOffset, DWORD uValue);


// Output data by byte unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by byte unit between output index.(0~1)
// uValue      : 0x00 ~ 0x0FF
//===============================================================================================//
DWORD   __stdcall AxdWriteExtOutportByte(long lModuleNo, long lOffset, DWORD uValue);


// Output data by word unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by word unit between output index.(0~1)
// uValue      : 0x00 ~ 0x0FFFF
//===============================================================================================//
DWORD   __stdcall AxdWriteExtOutportWord(long lModuleNo, long lOffset, DWORD uValue);


// Output data by dword unit in Offset position of specified extended output contact module
//==============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by dword unit between output index.(0)
// uValue      : 0x00 ~ 0x00000FFFF
//===============================================================================================//
DWORD   __stdcall AxdWriteExtOutportDword(long lModuleNo, long lOffset, DWORD uValue);


// Set data level by bit unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between input/output index.(0~15)
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD   __stdcall AxdLevelSetExtportBit(long lModuleNo, long lOffset, DWORD uLevel);


// Set data level by byte unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by byte unit between input/output index.(0~1)
// uLevel      : 0x00 ~ 0xFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD   __stdcall AxdLevelSetExtportByte(long lModuleNo, long lOffset, DWORD uLevel);


// Set data level by word unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by word unit between input/output index.(0)
// uLevel      : 0x00 ~ 0xFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD   __stdcall AxdLevelSetExtportWord(long lModuleNo, long lOffset, DWORD uLevel);


// Set data level by dword unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by dword unit between input/output index(0)
// uLevel      : 0x00 ~ 0x0000FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD   __stdcall AxdLevelSetExtportDword(long lModuleNo, long lOffset, DWORD uLevel);


// Verify data level by bit unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between input/output index(0~15)
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
DWORD   __stdcall AxdLevelGetExtportBit(long lModuleNo, long lOffset, DWORD *upLevel);


// Verify data level by byte unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by byte unit between input/output index(0~1)
// uLevel      : 0x00 ~ 0xFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD   __stdcall AxdLevelGetExtportByte(long lModuleNo, long lOffset, DWORD *upLevel);


// Verify data level by word unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by word unit between input/output index(0)
// uLevel      : 0x00 ~ 0xFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD   __stdcall AxdLevelGetExtportWord(long lModuleNo, long lOffset, DWORD *upLevel);


// Verify data level by dword unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by dword unit between input index(0)
// uLevel      : 0x00 ~ 0x0000FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD   __stdcall AxdLevelGetExtportDword(long lModuleNo, long lOffset, DWORD *upLevel);


//========== Advanced API
// Verify if the signal was switched from Off to On in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position for input contact
// *upValue    : FALSE(0)
//             : TRUE(1)
//===============================================================================================//
DWORD    __stdcall AxdiIsPulseOn(long lModuleNo, long lOffset, DWORD *upValue);


// Verify if the signal was switched from On to Off in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position for input contact
// *upValue    : FALSE(0)
//             : TRUE(1)
//===============================================================================================//
DWORD    __stdcall AxdiIsPulseOff(long lModuleNo, long lOffset, DWORD *upValue);


// Verify if the signal is maintained On state during the calling time as much as count in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position for input contact
// lCount      : 0 ~ 0x7FFFFFFF(2147483647)
// *upValue    : FALSE(0)
//             : TRUE(1)
// lStart      : 1
//             : 0
//===============================================================================================//
DWORD    __stdcall AxdiIsOn(long lModuleNo, long lOffset, long lCount, DWORD *upValue, long lStart);


// Verify if the signal is maintained Off state during the calling time as much as count in Offset position of specified input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position for input contact
// lCount      : 0 ~ 0x7FFFFFFF(2147483647)
// *upValue    : FALSE(0)
//             : TRUE(1)
// lStart      : 1(First call)
//             : 0(Repeat call)
//===============================================================================================//
DWORD    __stdcall AxdiIsOff(long lModuleNo, long lOffset, long lCount, DWORD *upValue, long lStart);


// Maintain On state during mSec set in Offset position of specified output contact module, then turns Off
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position for output contact
// lCount      : 0 ~ 0x7FFFFFFF(2147483647)
// lmSec       : 1 ~ 30000
//===============================================================================================//
DWORD    __stdcall AxdoOutPulseOn(long lModuleNo, long lOffset, long lmSec);


// Maintain Off state during mSec set in Offset position of specified output contact module, then turns On
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position for output contact
// lCount      : 0 ~ 0x7FFFFFFF(2147483647)
// lmSec       : 1 ~ 30000
//===============================================================================================//
DWORD    __stdcall AxdoOutPulseOff(long lModuleNo, long lOffset, long lmSec);


// Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position for output contact
// lInitState  : Off(0)
//             : On(1)
// lmSecOn     : 1 ~ 30000
// lmSecOff    : 1 ~ 30000
// lCount      : 1 ~ 0x7FFFFFFF(2147483647)
//             : -1
//===============================================================================================//
DWORD    __stdcall AxdoToggleStart(long lModuleNo, long lOffset, long lInitState, long lmSecOn, long lmSecOff, long lCount);


// Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position for output contact
// uOnOff      : Off(0)
//             : On(1)
//===============================================================================================//
DWORD    __stdcall AxdoToggleStop(long lModuleNo, long lOffset, DWORD uOnOff);


// In disconnect cases Set output status of specified module by byte.
//===============================================================================================//
// lModuleNo   : Module number
// dwSize      : Set Byte Number(ex. RTEX-DB32 : 2, RTEX-DO32 : 4)
// dwaSetValue : Set Value(Default : Status before Disconnect)
//             : 0 --> Disconnect before Status
//             : 1 --> On
//             : 2 --> Off
//             : 3 --> User Value, (Default user value : 'Off', Changeable from 'AxdoSetNetworkErrorUserValue()'). (SIII / ML3 / ECAT only)
//===============================================================================================//
DWORD   __stdcall AxdoSetNetworkErrorAct(long lModuleNo, DWORD dwSize, DWORD* dwaSetValue);


// API function for setting user defined output value in bytes when specified output module network is broken. (SIII / ML3 / ECAT only)
//===============================================================================================//
// lModuleNo   : Module number(Support dispersion type slaves only)
// dwOffset    : Offset position by dword unit between output index, Increasing unit of byte(Designation range:0, 1, 2, 3)
// dwValue     : Output contact value(00 ~ FFH)
//             : It must be set to 'User Value' for corresponding offset by 'AxdoSetNetworkErrorAct()'
//===============================================================================================//
DWORD   __stdcall AxdoSetNetworkErrorUserValue(long lModuleNo, DWORD dwOffset, DWORD dwValue);


// Setting connection number of specified module.
DWORD   __stdcall AxdSetContactNum(long lModuleNo, DWORD dwInputNum, DWORD dwOutputNum);


// Verifying connection number of specified module.
DWORD   __stdcall AxdGetContactNum(long lModuleNo, DWORD* dwpInputNum, DWORD* dwpOutputNum);




//== API for EtherCAT.
// Output data by bit length in Offset position of specified output module
//===============================================================================================//
// lModuleNo        : Module number
// dwBitOffset      : Bit offset position by dword unit between output index
// dwDataBitLength  : Bit length of output data
// pbyData          : The pointer of output data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD   __stdcall AxdoWriteOutportByBitOffset(long lModuleNo, DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);

// Read data by bit length in Offset position of specified input module
//===============================================================================================//
// lModuleNo        : Module number
// dwBitOffset      : Bit offset position by dword unit between input index
// dwDataBitLength  : Bit length of output data
// pbyData          : The pointer of input data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD   __stdcall AxdiReadInportByBitOffset(long lModuleNo, DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);

// Read data by bit length in Offset position of specified output module
//===============================================================================================//
// lModuleNo        : Module number
// dwBitOffset      : Bit offset position by dword unit between output index
// dwDataBitLength  : Bit length of input data
// pbyData          : The pointer of input data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
DWORD   __stdcall AxdoReadOutportByBitOffset(long lModuleNo, DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);

DWORD   __stdcall AxdoLinkSetOutport(long lLinkNo, long lDstModuleNo, DWORD uDstBitOffset, long lSrcModuleNo, DWORD uSrcBitOffset, DWORD uSrcDataBitLength, DWORD uSrcPortType);
DWORD   __stdcall AxdoLinkGetOutport(long lLinkNo, long *lpDstModuleNo, DWORD *upDstBitOffset, long *lpSrcModuleNo, DWORD *upSrcBitOffset, DWORD *upSrcDataBitLength, DWORD *upSrcPortType);
DWORD   __stdcall AxdoLinkResetOutport(long lLinkNo);

DWORD   __stdcall AxdoInterLockSetOutport(long lBoardNo, long lInterLockNo, long lDstModuleNo, DWORD uDstBitOffset, long lSrcModuleNo, DWORD uSrcBitOffset, DWORD uSrcPortType, DWORD uSrcCondition, DWORD uOutputMode, DWORD uOutputModeData);
DWORD   __stdcall AxdoInterLockGetOutport(long lBoardNo, long lInterLockNo, long *lpDstModuleNo, DWORD *upDstBitOffset, long *lpSrcModuleNo, DWORD *upSrcBitOffset, DWORD *upSrcPortType, DWORD *upSrcCondition, DWORD *upOutputMode, DWORD *upOutputModeData);
DWORD   __stdcall AxdoInterLockIsEnabled(long lBoardNo, long lInterLockNo, DWORD* upEnabled);
DWORD   __stdcall AxdoInterLockResetOutport(long lBoardNo, long lInterLockNo);


#ifdef __cplusplus
}
#endif    //__cplusplus

#endif    //__AXT_AXD_H__
