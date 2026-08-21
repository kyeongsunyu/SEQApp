//****************************************************************************
///****************************************************************************
//*****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXD.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Digital Library Header File
//** 
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Source Change Indices
//** ---------------------
//** 
//** (None)
//**
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Website
//** ---------------------
//**
//** http://www.ajinextek.com
//**
//*****************************************************************************
//*****************************************************************************
//*/
//

unit AXD;

interface

uses Windows, Messages, AXHS;



//========== Board and module information ======================================
// Verify if DIO module exists
function AxdInfoIsDIOModule (upStatus : PDWord) : DWord; stdcall;


// Verify DIO in/output module number
function AxdInfoGetModuleNo (lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;


// Verify the number of DIO in/output module
function AxdInfoGetModuleCount (lpModuleCount : PLongInt) : DWord; stdcall;


// Verify the number of input contacts of specified module
function AxdInfoGetInputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;


// Verify the number of output contacts of specified module
function AxdInfoGetOutputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;


// Verify the base board number, module position and module ID with specified module number
function AxdInfoGetModule (lModuleNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;


// Verify specified module board : Sub ID, module name, module description
//===============================================/
// support product : EtherCAT
// upModuleSubID   : EtherCAT SubID(for distinguish between EtherCAT modules)
// szModuleName         : model name of module(50 Bytes)
// szModuleDescription  : description of module(80 Bytes)
//======================================================//
function AxdInfoGetModuleEx (lModuleNo : LongInt; upModuleSubID : PDWord; szModuleName : PChar; szModuleDescription : PChar) : DWord; stdcall;

//Verify Module status of specified module board
function AxdInfoGetModuleStatus(lModuleNo : LongInt) : DWord; stdcall;


//========== Verification group for input interrupt setting ====================
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
function AxdiInterruptSetModule (lModuleNo : LongInt; hWnd : HWND; uMessage : DWord; pProc : AXT_INTERRUPT_PROC; pEvent : PDWord) : DWord; stdcall;


// Set whether to use interrupt of specified module
//======================================================
// uUse   : DISABLE(0)   // Interrupt Disable
//        : ENABLE(1)    // Interrupt Enable
//======================================================
function AxdiInterruptSetModuleEnable (lModuleNo : LongInt; uUse : DWord) : DWord; stdcall;


// Verify whether to use interrupt of specified module
//======================================================
// *upUse : DISABLE(0)   // Interrupt Disable
//        : ENABLE(1)    // Interrupt Enable
//======================================================
function AxdiInterruptGetModuleEnable (lModuleNo : LongInt; upUse : PDWord) : DWord; stdcall;


// Verify the position interrupt occurred
function AxdiInterruptRead (lpModuleNo : PLongInt; upFlag : PDWord) : DWord; stdcall;


//========== Input interrupt rising / Verification group for setting of interrupt occurrence in falling edge

// Set the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode  : DOWN_EDGE(0)
//        : UP_EDGE(1)
// uValue : DISABLE(0)
//        : ENABLE(1)
//======================================================
function AxdiInterruptEdgeSetBit (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;


// Set the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode  : DOWN_EDGE(0)
//        : UP_EDGE(1)
// uValue : 0x00 ~ 0x0FF
//======================================================
function AxdiInterruptEdgeSetByte (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;


// Set the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode  : DOWN_EDGE(0)
//        : UP_EDGE(1)
// uValue : 0x00 ~ 0x0FFFF
//======================================================
function AxdiInterruptEdgeSetWord (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;


// Set the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode  : DOWN_EDGE(0)
//        : UP_EDGE(1)
// uValue : 0x00 ~ 0x0FFFFFFFF
//======================================================
function AxdiInterruptEdgeSetDword (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;


// Verify the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode    : DOWN_EDGE(0)
//          : UP_EDGE(1)
// *upValue : 0x00 ~ 0x0FF
//======================================================
function AxdiInterruptEdgeGetBit (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;


// Verify the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode    : DOWN_EDGE(0)
//          : UP_EDGE(1)
// *upValue : 0x00 ~ 0x0FF
//======================================================
function AxdiInterruptEdgeGetByte (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;


// Verify the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode    : DOWN_EDGE(0)
//          : UP_EDGE(1)
// *upValue : 0x00 ~ 0x0FFFFFFFF
//======================================================
function AxdiInterruptEdgeGetWord (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;


// Verify the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lModuleNo : Number of module
// lOffset   : Offset position for input contact
// uMode    : DOWN_EDGE(0)
//          : UP_EDGE(1)
// *upValue : 0x00 ~ 0x0FFFFFFFF
//======================================================
function AxdiInterruptEdgeGetDword (lModuleNo : LongInt; lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;


// Set the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lOffset   : Offset position for input contact
// uMode    : DOWN_EDGE(0)
//          : UP_EDGE(1)
// uValue   : DISABLE(0)
//          : ENABLE(1)
//======================================================
function AxdiInterruptEdgeSet (lOffset : LongInt; uMode : DWord; uValue : DWord) : DWord; stdcall;


// Verify the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
//======================================================
// lOffset   : Offset position for input contact
// uMode    : DOWN_EDGE(0)
//          : UP_EDGE(1)
// *upValue : DISABLE(0)
//          : ENABLE(1)
//======================================================
function AxdiInterruptEdgeGet (lOffset : LongInt; uMode : DWord; upValue : PDWord) : DWord; stdcall;


//========== Verification group of input / output signal level setting =========
//==Verification group of input signal level setting
// Set data level by bit unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// uLevel   : LOW(0)
//          : HIGH(1)
//======================================================
function AxdiLevelSetInportBit (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Set data level by byte unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// uLevel      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//======================================================
function AxdiLevelSetInportByte (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Set data level by word unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// uLevel      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//======================================================
function AxdiLevelSetInportWord (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Set data level by double word unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// uLevel      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//======================================================
function AxdiLevelSetInportDword (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Verify data level by bit unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel : LOW(0)
//          : HIGH(1)
//======================================================
function AxdiLevelGetInportBit (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Verify data level by byte unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdiLevelGetInportByte (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Verify data level by word unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdiLevelGetInportWord (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Verify data level by double word unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdiLevelGetInportDword (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Set data level by bit unit in Offset position of entire input contact module
//======================================================
// lOffset     : Offset position for input contact
// uLevel   : LOW(0)
//          : HIGH(1)
//======================================================
function AxdiLevelSetInport (lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Verify data level by bit unit in Offset position of entire input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upLevel : LOW(0)
//          : HIGH(1)
//======================================================
function AxdiLevelGetInport (lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


//==Verification group of output signal level setting ==========================
// Set data level by bit unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel   : LOW(0)
//          : HIGH(1)
//======================================================
function AxdoLevelSetOutportBit (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Set data level by byte unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//======================================================
function AxdoLevelSetOutportByte (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Set data level by word unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//======================================================
function AxdoLevelSetOutportWord (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Set data level by double word unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//======================================================
function AxdoLevelSetOutportDword (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Verify data level by bit unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel : LOW(0)
//          : HIGH(1)
//======================================================
function AxdoLevelGetOutportBit (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Verify data level by byte unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdoLevelGetOutportByte (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Verify data level by word unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdoLevelGetOutportWord (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Verify data level by double word unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdoLevelGetOutportDword (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Set data level by bit unit in Offset position of entire output contact module
//======================================================
// lOffset     : Offset position for output contact
// uLevel   : LOW(0)
//          : HIGH(1)
//======================================================
function AxdoLevelSetOutport (lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Verify data level by bit unit in Offset position of entire output contact module
//======================================================
// lOffset     : Offset position for output contact
// *upLevel : LOW(0)
//          : HIGH(1)
//======================================================
function AxdoLevelGetOutport (lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


//========== Input / Output signal reading / writing ===========================
//==Output signal writing
// Output data by bit unit in Offset position of entire output contact module
//======================================================
// lOffset     : Offset position for output contact
// uLevel   : LOW(0)
//          : HIGH(1)
//======================================================
function AxdoWriteOutport (lOffset : LongInt; uValue : DWord) : DWord; stdcall;


// Output data by bit unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uLevel      : LOW(0)
//             : HIGH(1)
//======================================================
function AxdoWriteOutportBit (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;


// Output data by byte unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uValue      : 0x00 ~ 0x0FF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//======================================================
function AxdoWriteOutportByte (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;


// Output data by word unit in Offset position of specified output contact module
//======================================================
// uValue      : 0x00 ~ 0x0FFFF
// lOffset     : Offset position for output contact
// uValue      : 0x00 ~ 0x0FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//======================================================
function AxdoWriteOutportWord (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;


// Output data by double word unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// uValue      : 0x00 ~ 0x0FFFFFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//======================================================
function AxdoWriteOutportDword (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;


//==Output signal reading ======================================================
// Read data by bit unit in Offset position of entire output contact module
//======================================================
// lOffset     : Offset position for output contact
// *upLevel : LOW(0)
//          : HIGH(1)
//======================================================
function AxdoReadOutport (lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data by bit unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upLevel    : LOW(0)
//             : HIGH(1)
//======================================================
function AxdoReadOutportBit (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data by byte unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upValue    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdoReadOutportByte (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data by word unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upValue    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdoReadOutportWord (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data by double word unit in Offset position of specified output contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for output contact
// *upValue    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdoReadOutportDword (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


//==Input signal reading =======================================================
// Read data level by bit unit in Offset position of entire input contact module
//======================================================
// lOffset     : Offset position for input contact
// *upValue  : LOW(0)
//           : HIGH(1)
//======================================================
function AxdiReadInport (lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by bit unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upValue   : LOW(0)
//            : HIGH(1)
//======================================================
function AxdiReadInportBit (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by byte unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upValue    : 0x00 ~ 0x0FF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdiReadInportByte (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by wordt unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upValue    : 0x00 ~ 0x0FFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdiReadInportWord (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by double word unit in Offset position of specified input contact module
//======================================================
// lModuleNo   : Number of module
// lOffset     : Offset position for input contact
// *upValue    : 0x00 ~ 0x0FFFFFFFF(Read bit '1' means 'HIGH', Read bit '0' means 'LOW')
//======================================================
function AxdiReadInportDword (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;



//== Only for MLII, M-Systems DIO(R7 series)
// Read data level by bit unit in Offset position of specified extended input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between input index.(0~15)
// *upValue    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
function AxdReadExtInportBit (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by byte unit in Offset position of specified extended input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : offset position by byte unit between input index.(0~1)
// *upValue    : 0x00 ~ 0x0FF
//===============================================================================================//
function AxdReadExtInportByte (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by word unit in Offset position of specified extended input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : offset position by word unit between input index.(0)
// *upValue    : 0x00 ~ 0x0FFFF
//===============================================================================================//
function AxdReadExtInportWord (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by double word unit in Offset position of specified extended input contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : offset position by dword unit between input index.(0)
// *upValue    : 0x00 ~ 0x00000FFFF
//===============================================================================================//
function AxdReadExtInportDword (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by bit unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between output index.(0~15)
// *upValue    : LOW(0)
//             : HIGH(1)
//===============================================================================================//
function AxdReadExtOutportBit (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by byte unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by byte unit between output index.(0~1)
// *upValue    : 0x00 ~ 0x0FF
//===============================================================================================//
function AxdReadExtOutportByte (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by word unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by word unit between output index.(0)
// *upValue    : 0x00 ~ 0x0FFFF
//===============================================================================================//
function AxdReadExtOutportWord (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Read data level by double word unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by dword unit between output index.(0)
// *upValue    : 0x00 ~ 0x0000FFFF
//===============================================================================================//
function AxdReadExtOutportDword (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Output data by bit unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between output index.(0~15)
// uValue      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
function AxdWriteExtOutportBit (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;


// Output data by byte unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by byte unit between output index.(0~1)
// uValue      : 0x00 ~ 0x0FF
//===============================================================================================//
function AxdWriteExtOutportByte (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;


// Output data by word unit in Offset position of specified extended output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by word unit between output index.(0~1)
// uValue      : 0x00 ~ 0x0FFFF
//===============================================================================================//
function AxdWriteExtOutportWord (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;


// Output data by dword unit in Offset position of specified extended output contact module
//==============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by dword unit between output index.(0)
// uValue    : 0x00 ~ 0x00000FFFF
//===============================================================================================//
function AxdWriteExtOutportDword (lModuleNo : LongInt; lOffset : LongInt; uValue : DWord) : DWord; stdcall;


// Set data level by bit unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between input/output index.(0~15)
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
function AxdLevelSetExtportBit (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Set data level by byte unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by byte unit between input/output index.(0~1)
// uLevel      : 0x00 ~ 0xFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
function AxdLevelSetExtportByte (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Set data level by word unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by word unit between input/output index.(0)
// uLevel      : 0x00 ~ 0xFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
function AxdLevelSetExtportWord (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Set data level by dword unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by dword unit between input/output index.(0)
// uLevel      : 0x00 ~ 0x0000FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
function AxdLevelSetExtportDword (lModuleNo : LongInt; lOffset : LongInt; uLevel : DWord) : DWord; stdcall;


// Verify data level by bit unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by bit unit between input/output index.(0~15)
// uLevel      : LOW(0)
//             : HIGH(1)
//===============================================================================================//
function AxdLevelGetExtportBit (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Verify data level by byte unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by byte unit between input/output index.(0~1)
// uLevel      : 0x00 ~ 0xFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
function AxdLevelGetExtportByte (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Verify data level by word unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by word unit between input/output index.(0)
// uLevel      : 0x00 ~ 0xFFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
function AxdLevelGetExtportWord (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


// Verify data level by dword unit in Offset position of specified extended input/output contact module
//===============================================================================================//
// lModuleNo   : Module number
// lOffset     : Offset position by dword unit between input/output index.(0)
// uLevel      : 0x00 ~ 0x0000FFFF(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
function AxdLevelGetExtportDword (lModuleNo : LongInt; lOffset : LongInt; upLevel : PDWord) : DWord; stdcall;


//========== Advanced API ======================================================
// Verify if the signal was switched from Off to On in Offset position of specified input contact module
//======================================================
// lModuleNo   : Module number
// lOffset     : Offset position for input contact
// *upValue   : FALSE(0)
//            : TRUE(1)
//======================================================
function AxdiIsPulseOn (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Verify if the signal was switched from On to Off in Offset position of specified input contact module
//======================================================
// lModuleNo   : Module number
// lOffset     : Offset position for input contact
// *upValue   : FALSE(0)
//            : TRUE(1)
//======================================================
function AxdiIsPulseOff (lModuleNo : LongInt; lOffset : LongInt; upValue : PDWord) : DWord; stdcall;


// Verify if the signal is maintained On state during the calling time as much as count in Offset position of specified input contact module
//======================================================
// lModuleNo   : Module number
// lOffset     : Offset position for input contact
// lCount     : 0 ~ 0x7FFFFFFF(2147483647)
// *upValue   : FALSE(0)
//            : TRUE(1)
// lStart     : 1
//            : 0
//======================================================
function AxdiIsOn (lModuleNo : LongInt; lOffset : LongInt; lCount : LongInt; upValue : PDWord; lStart : LongInt) : DWord; stdcall;


// Verify if the signal is maintained Off state during the calling time as much as count in Offset position of specified input contact module
//======================================================
// lModuleNo   : Module number
// lOffset     : Offset position for input contact
// lCount     : 0 ~ 0x7FFFFFFF(2147483647)
// *upValue   : FALSE(0)
//            : TRUE(1)
// lStart     : 1(First call)
//            : 0(Repeat call)
//======================================================
function AxdiIsOff (lModuleNo : LongInt; lOffset : LongInt; lCount : LongInt; upValue : PDWord; lStart : LongInt) : DWord; stdcall;


// Maintain On state during mSec set in Offset position of specified output contact module, then turns Off
//======================================================
// lModuleNo   : Module number
// lOffset     : Offset position for output contact
// lCount     : 0 ~ 0x7FFFFFFF(2147483647)
// lmSec      : 1 ~ 30000
//======================================================
function AxdoOutPulseOn (lModuleNo : LongInt; lOffset : LongInt; lmSec : LongInt) : DWord; stdcall;


// Maintain Off state during mSec set in Offset position of specified output contact module, then turns On
//======================================================
// lModuleNo   : Module number
// lOffset     : Offset position for output contact
// lCount     : 0 ~ 0x7FFFFFFF(2147483647)
// lmSec      : 1 ~ 30000
//======================================================
function AxdoOutPulseOff (lModuleNo : LongInt; lOffset : LongInt; lmSec : LongInt) : DWord; stdcall;


// Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
//======================================================
// lModuleNo   : Module number
// lOffset     : Offset position for output contact
// lInitState : Off(0)
//            : On(1)
// lmSecOn    : 1 ~ 30000
// lmSecOff   : 1 ~ 30000
// lCount     : 1 ~ 0x7FFFFFFF(2147483647)
//            : -1
//======================================================
function AxdoToggleStart (lModuleNo : LongInt; lOffset : LongInt; lInitState : LongInt; lmSecOn : LongInt; lmSecOff : LongInt; lCount : LongInt) : DWord; stdcall;


// Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
//======================================================
// lModuleNo   : Module number
// lOffset     : Offset position for output contact
// uOnOff     : Off(0)
//            : On(1)
//======================================================
function AxdoToggleStop (lModuleNo : LongInt; lOffset : LongInt; uOnOff : DWord) : DWord; stdcall;


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
function AxdoSetNetworkErrorAct(lModuleNo: LongInt; dwSize : DWord; dwaSetValue : PDWord) : DWord; stdcall;


// API function for setting user defined output value in bytes when specified output module network is broken. (SIII / ML3 / ECAT only)
//===============================================================================================//
// lModuleNo   : Module number(Support dispersion type slaves only)
// dwOffset    : Offset position by dword unit between output index, Increasing unit of byte(Designation range:0, 1, 2, 3)
// dwValue     : Output contact value(00 ~ FFH)
//             : It must be set to 'User Value' for corresponding offset by 'AxdoSetNetworkErrorAct()'
//===============================================================================================//
function AxdoSetNetworkErrorUserValue(lModuleNo: LongInt; uOffset : DWord; uValue : DWord) : DWord; stdcall;


// Setting connection number of specified module.
function AxdSetContactNum(lModuleNo : LongInt; dwInputNum : DWord; dwOutputNum : DWord) : DWord; stdcall;


// Verifying connection number of specified module.
function AxdGetContactNum(lModuleNo : LongInt; dwpInputNum : PDWord; dwpOutputNum : PDWord) : DWord; stdcall;




//== For EtherCAT Only
// Output data by bit length in Offset position of specified output module
//===============================================================================================//
// lModuleNo        : Module number
// dwBitOffset      : Bit offset position by dword unit between output index
// dwDataBitLength  : Bit length of output data
// pbyData          : The pointer of output data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
function AxdoWriteOutportByBitOffset(lModuleNo : LongInt; uBitOffset : DWord; uDataBitLength : DWord; bpData : PByte) : DWord; stdcall;

// Read data by bit length in Offset position of specified input module
//===============================================================================================//
// lModuleNo        : Module number
// dwBitOffset      : Bit offset position by dword unit between input index
// dwDataBitLength  : Bit length of output data
// pbyData          : The pointer of input data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
function AxdiReadInportByBitOffset(lModuleNo : LongInt; uBitOffset : DWord; uDataBitLength : DWord; bpData : PByte) : DWord; stdcall;

// Read data by bit length in Offset position of specified output module
//===============================================================================================//
// lModuleNo        : Module number
// dwBitOffset      : Bit offset position by dword unit between output index
// dwDataBitLength  : Bit length of input data
// pbyData          : The pointer of input data(If set bit is '1', It means HIGH, If set bit is '0', It means LOW)
//===============================================================================================//
function AxdoReadOutportByBitOffset(lModuleNo : LongInt; uBitOffset : DWord; uDataBitLength : DWord; bpData : PByte) : DWord; stdcall;

    function AxdoLinkSetOutport (lLinkNo : LongInt; lDstModuleNo : LongInt; uDstBitOffset : DWord; lSrcModuleNo : LongInt; uSrcBitOffset : DWord; uSrcDataBitLength : DWord; uSrcPortType : DWord) : DWord; stdcall;
    function AxdoLinkGetOutport (lLinkNo : LongInt; lpDstModuleNo : PLongInt; upDstBitOffset : PDWord; lpSrcModuleNo : PLongInt; upSrcBitOffset : PDWord; upSrcDataBitLength : PDWord; upSrcPortType : PDWord) : DWord; stdcall;
    function AxdoLinkResetOutport (lLinkNo : LongInt) : DWord; stdcall;

    function AxdoInterLockSetOutport (lBoardNo : LongInt; lInterLockNo : LongInt; lDstModuleNo : LongInt; uDstBitOffset : DWord; lSrcModuleNo : LongInt; uSrcBitOffset : DWord; uSrcPortType : DWord; uSrcCondition : DWord; uOutputMode : DWord; uOutputModeData : DWord) : DWord; stdcall;
    function AxdoInterLockGetOutport (lBoardNo : LongInt; lInterLockNo : LongInt; lpDstModuleNo : PLongInt; upDstBitOffset : PDWord; lpSrcModuleNo : PLongInt; upSrcBitOffset : PDWord; upSrcPortType : PDWord; upSrcCondition : PDWord; upOutputMode : PDWord; upOutputModeData : PDWord) : DWord; stdcall;
    function AxdoInterLockIsEnabled (lBoardNo : LongInt; lInterLockNo : LongInt; upEnabled : PDWord) : DWord; stdcall;
    function AxdoInterLockResetOutport (lBoardNo : LongInt; lInterLockNo : LongInt) : DWord; stdcall;


implementation

const

    dll_name    = 'AXL.dll';
    function AxdInfoIsDIOModule; external dll_name name 'AxdInfoIsDIOModule';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxdInfoGetModuleCount; external dll_name name 'AxdInfoGetModuleCount';
    function AxdInfoGetInputCount; external dll_name name 'AxdInfoGetInputCount';
    function AxdInfoGetOutputCount; external dll_name name 'AxdInfoGetOutputCount';
    function AxdInfoGetModule; external dll_name name 'AxdInfoGetModule';
    function AxdInfoGetModuleEx; external dll_name name 'AxdInfoGetModuleEx';
    function AxdInfoGetModuleStatus; external dll_name name 'AxdInfoGetModuleStatus';
    function AxdiInterruptSetModule; external dll_name name 'AxdiInterruptSetModule';
    function AxdiInterruptSetModuleEnable; external dll_name name 'AxdiInterruptSetModuleEnable';
    function AxdiInterruptGetModuleEnable; external dll_name name 'AxdiInterruptGetModuleEnable';
    function AxdiInterruptRead; external dll_name name 'AxdiInterruptRead';
    function AxdiInterruptEdgeSetBit; external dll_name name 'AxdiInterruptEdgeSetBit';
    function AxdiInterruptEdgeSetByte; external dll_name name 'AxdiInterruptEdgeSetByte';
    function AxdiInterruptEdgeSetWord; external dll_name name 'AxdiInterruptEdgeSetWord';
    function AxdiInterruptEdgeSetDword; external dll_name name 'AxdiInterruptEdgeSetDword';
    function AxdiInterruptEdgeGetBit; external dll_name name 'AxdiInterruptEdgeGetBit';
    function AxdiInterruptEdgeGetByte; external dll_name name 'AxdiInterruptEdgeGetByte';
    function AxdiInterruptEdgeGetWord; external dll_name name 'AxdiInterruptEdgeGetWord';
    function AxdiInterruptEdgeGetDword; external dll_name name 'AxdiInterruptEdgeGetDword';
    function AxdiInterruptEdgeSet; external dll_name name 'AxdiInterruptEdgeSet';
    function AxdiInterruptEdgeGet; external dll_name name 'AxdiInterruptEdgeGet';
    function AxdiLevelSetInportBit; external dll_name name 'AxdiLevelSetInportBit';
    function AxdiLevelSetInportByte; external dll_name name 'AxdiLevelSetInportByte';
    function AxdiLevelSetInportWord; external dll_name name 'AxdiLevelSetInportWord';
    function AxdiLevelSetInportDword; external dll_name name 'AxdiLevelSetInportDword';
    function AxdiLevelGetInportBit; external dll_name name 'AxdiLevelGetInportBit';
    function AxdiLevelGetInportByte; external dll_name name 'AxdiLevelGetInportByte';
    function AxdiLevelGetInportWord; external dll_name name 'AxdiLevelGetInportWord';
    function AxdiLevelGetInportDword; external dll_name name 'AxdiLevelGetInportDword';
    function AxdiLevelSetInport; external dll_name name 'AxdiLevelSetInport';
    function AxdiLevelGetInport; external dll_name name 'AxdiLevelGetInport';
    function AxdoLevelSetOutportBit; external dll_name name 'AxdoLevelSetOutportBit';
    function AxdoLevelSetOutportByte; external dll_name name 'AxdoLevelSetOutportByte';
    function AxdoLevelSetOutportWord; external dll_name name 'AxdoLevelSetOutportWord';
    function AxdoLevelSetOutportDword; external dll_name name 'AxdoLevelSetOutportDword';
    function AxdoLevelGetOutportBit; external dll_name name 'AxdoLevelGetOutportBit';
    function AxdoLevelGetOutportByte; external dll_name name 'AxdoLevelGetOutportByte';
    function AxdoLevelGetOutportWord; external dll_name name 'AxdoLevelGetOutportWord';
    function AxdoLevelGetOutportDword; external dll_name name 'AxdoLevelGetOutportDword';
    function AxdoLevelSetOutport; external dll_name name 'AxdoLevelSetOutport';
    function AxdoLevelGetOutport; external dll_name name 'AxdoLevelGetOutport';
    function AxdoWriteOutport; external dll_name name 'AxdoWriteOutport';
    function AxdoWriteOutportBit; external dll_name name 'AxdoWriteOutportBit';
    function AxdoWriteOutportByte; external dll_name name 'AxdoWriteOutportByte';
    function AxdoWriteOutportWord; external dll_name name 'AxdoWriteOutportWord';
    function AxdoWriteOutportDword; external dll_name name 'AxdoWriteOutportDword';
    function AxdoReadOutport; external dll_name name 'AxdoReadOutport';
    function AxdoReadOutportBit; external dll_name name 'AxdoReadOutportBit';
    function AxdoReadOutportByte; external dll_name name 'AxdoReadOutportByte';
    function AxdoReadOutportWord; external dll_name name 'AxdoReadOutportWord';
    function AxdoReadOutportDword; external dll_name name 'AxdoReadOutportDword';
    function AxdiReadInport; external dll_name name 'AxdiReadInport';
    function AxdiReadInportBit; external dll_name name 'AxdiReadInportBit';
    function AxdiReadInportByte; external dll_name name 'AxdiReadInportByte';
    function AxdiReadInportWord; external dll_name name 'AxdiReadInportWord';
    function AxdiReadInportDword; external dll_name name 'AxdiReadInportDword';
    function AxdReadExtInportBit; external dll_name name 'AxdReadExtInportBit';
    function AxdReadExtInportByte; external dll_name name 'AxdReadExtInportByte';
    function AxdReadExtInportWord; external dll_name name 'AxdReadExtInportWord';
    function AxdReadExtInportDword; external dll_name name 'AxdReadExtInportDword';
    function AxdReadExtOutportBit; external dll_name name 'AxdReadExtOutportBit';
    function AxdReadExtOutportByte; external dll_name name 'AxdReadExtOutportByte';
    function AxdReadExtOutportWord; external dll_name name 'AxdReadExtOutportWord';
    function AxdReadExtOutportDword; external dll_name name 'AxdReadExtOutportDword';
    function AxdWriteExtOutportBit; external dll_name name 'AxdWriteExtOutportBit';
    function AxdWriteExtOutportByte; external dll_name name 'AxdWriteExtOutportByte';
    function AxdWriteExtOutportWord; external dll_name name 'AxdWriteExtOutportWord';
    function AxdWriteExtOutportDword; external dll_name name 'AxdWriteExtOutportDword';
    function AxdLevelSetExtportBit; external dll_name name 'AxdLevelSetExtportBit';
    function AxdLevelSetExtportByte; external dll_name name 'AxdLevelSetExtportByte';
    function AxdLevelSetExtportWord; external dll_name name 'AxdLevelSetExtportWord';
    function AxdLevelSetExtportDword; external dll_name name 'AxdLevelSetExtportDword';
    function AxdLevelGetExtportBit; external dll_name name 'AxdLevelGetExtportBit';
    function AxdLevelGetExtportByte; external dll_name name 'AxdLevelGetExtportByte';
    function AxdLevelGetExtportWord; external dll_name name 'AxdLevelGetExtportWord';
    function AxdLevelGetExtportDword; external dll_name name 'AxdLevelGetExtportDword';
    function AxdiIsPulseOn; external dll_name name 'AxdiIsPulseOn';
    function AxdiIsPulseOff; external dll_name name 'AxdiIsPulseOff';
    function AxdiIsOn; external dll_name name 'AxdiIsOn';
    function AxdiIsOff; external dll_name name 'AxdiIsOff';
    function AxdoOutPulseOn; external dll_name name 'AxdoOutPulseOn';
    function AxdoOutPulseOff; external dll_name name 'AxdoOutPulseOff';
    function AxdoToggleStart; external dll_name name 'AxdoToggleStart';
    function AxdoToggleStop; external dll_name name 'AxdoToggleStop';
    function AxdoSetNetworkErrorAct; external dll_name name 'AxdoSetNetworkErrorAct';
    function AxdoSetNetworkErrorUserValue; external dll_name name 'AxdoSetNetworkErrorUserValue';
    function AxdSetContactNum; external dll_name name 'AxdSetContactNum';
    function AxdGetContactNum; external dll_name name 'AxdGetContactNum';
    function AxdoWriteOutportByBitOffset; external dll_name name 'AxdoWriteOutportByBitOffset';
    function AxdiReadInportByBitOffset; external dll_name name 'AxdiReadInportByBitOffset';
    function AxdoReadOutportByBitOffset; external dll_name name 'AxdoReadOutportByBitOffset';
    function AxdInfoIsDIOModule; external dll_name name 'AxdInfoIsDIOModule';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxdInfoGetModuleCount; external dll_name name 'AxdInfoGetModuleCount';
    function AxdInfoGetInputCount; external dll_name name 'AxdInfoGetInputCount';
    function AxdInfoGetOutputCount; external dll_name name 'AxdInfoGetOutputCount';
    function AxdInfoGetModule; external dll_name name 'AxdInfoGetModule';
    function AxdInfoGetModuleEx; external dll_name name 'AxdInfoGetModuleEx';
    function AxdInfoGetModuleStatus; external dll_name name 'AxdInfoGetModuleStatus';
    function AxdiInterruptSetModule; external dll_name name 'AxdiInterruptSetModule';
    function AxdiInterruptSetModuleEnable; external dll_name name 'AxdiInterruptSetModuleEnable';
    function AxdiInterruptGetModuleEnable; external dll_name name 'AxdiInterruptGetModuleEnable';
    function AxdiInterruptRead; external dll_name name 'AxdiInterruptRead';
    function AxdiInterruptEdgeSetBit; external dll_name name 'AxdiInterruptEdgeSetBit';
    function AxdiInterruptEdgeSetByte; external dll_name name 'AxdiInterruptEdgeSetByte';
    function AxdiInterruptEdgeSetWord; external dll_name name 'AxdiInterruptEdgeSetWord';
    function AxdiInterruptEdgeSetDword; external dll_name name 'AxdiInterruptEdgeSetDword';
    function AxdiInterruptEdgeGetBit; external dll_name name 'AxdiInterruptEdgeGetBit';
    function AxdiInterruptEdgeGetByte; external dll_name name 'AxdiInterruptEdgeGetByte';
    function AxdiInterruptEdgeGetWord; external dll_name name 'AxdiInterruptEdgeGetWord';
    function AxdiInterruptEdgeGetDword; external dll_name name 'AxdiInterruptEdgeGetDword';
    function AxdiInterruptEdgeSet; external dll_name name 'AxdiInterruptEdgeSet';
    function AxdiInterruptEdgeGet; external dll_name name 'AxdiInterruptEdgeGet';
    function AxdiLevelSetInportBit; external dll_name name 'AxdiLevelSetInportBit';
    function AxdiLevelSetInportByte; external dll_name name 'AxdiLevelSetInportByte';
    function AxdiLevelSetInportWord; external dll_name name 'AxdiLevelSetInportWord';
    function AxdiLevelSetInportDword; external dll_name name 'AxdiLevelSetInportDword';
    function AxdiLevelGetInportBit; external dll_name name 'AxdiLevelGetInportBit';
    function AxdiLevelGetInportByte; external dll_name name 'AxdiLevelGetInportByte';
    function AxdiLevelGetInportWord; external dll_name name 'AxdiLevelGetInportWord';
    function AxdiLevelGetInportDword; external dll_name name 'AxdiLevelGetInportDword';
    function AxdiLevelSetInport; external dll_name name 'AxdiLevelSetInport';
    function AxdiLevelGetInport; external dll_name name 'AxdiLevelGetInport';
    function AxdoLevelSetOutportBit; external dll_name name 'AxdoLevelSetOutportBit';
    function AxdoLevelSetOutportByte; external dll_name name 'AxdoLevelSetOutportByte';
    function AxdoLevelSetOutportWord; external dll_name name 'AxdoLevelSetOutportWord';
    function AxdoLevelSetOutportDword; external dll_name name 'AxdoLevelSetOutportDword';
    function AxdoLevelGetOutportBit; external dll_name name 'AxdoLevelGetOutportBit';
    function AxdoLevelGetOutportByte; external dll_name name 'AxdoLevelGetOutportByte';
    function AxdoLevelGetOutportWord; external dll_name name 'AxdoLevelGetOutportWord';
    function AxdoLevelGetOutportDword; external dll_name name 'AxdoLevelGetOutportDword';
    function AxdoLevelSetOutport; external dll_name name 'AxdoLevelSetOutport';
    function AxdoLevelGetOutport; external dll_name name 'AxdoLevelGetOutport';
    function AxdoWriteOutport; external dll_name name 'AxdoWriteOutport';
    function AxdoWriteOutportBit; external dll_name name 'AxdoWriteOutportBit';
    function AxdoWriteOutportByte; external dll_name name 'AxdoWriteOutportByte';
    function AxdoWriteOutportWord; external dll_name name 'AxdoWriteOutportWord';
    function AxdoWriteOutportDword; external dll_name name 'AxdoWriteOutportDword';
    function AxdoReadOutport; external dll_name name 'AxdoReadOutport';
    function AxdoReadOutportBit; external dll_name name 'AxdoReadOutportBit';
    function AxdoReadOutportByte; external dll_name name 'AxdoReadOutportByte';
    function AxdoReadOutportWord; external dll_name name 'AxdoReadOutportWord';
    function AxdoReadOutportDword; external dll_name name 'AxdoReadOutportDword';
    function AxdiReadInport; external dll_name name 'AxdiReadInport';
    function AxdiReadInportBit; external dll_name name 'AxdiReadInportBit';
    function AxdiReadInportByte; external dll_name name 'AxdiReadInportByte';
    function AxdiReadInportWord; external dll_name name 'AxdiReadInportWord';
    function AxdiReadInportDword; external dll_name name 'AxdiReadInportDword';
    function AxdReadExtInportBit; external dll_name name 'AxdReadExtInportBit';
    function AxdReadExtInportByte; external dll_name name 'AxdReadExtInportByte';
    function AxdReadExtInportWord; external dll_name name 'AxdReadExtInportWord';
    function AxdReadExtInportDword; external dll_name name 'AxdReadExtInportDword';
    function AxdReadExtOutportBit; external dll_name name 'AxdReadExtOutportBit';
    function AxdReadExtOutportByte; external dll_name name 'AxdReadExtOutportByte';
    function AxdReadExtOutportWord; external dll_name name 'AxdReadExtOutportWord';
    function AxdReadExtOutportDword; external dll_name name 'AxdReadExtOutportDword';
    function AxdWriteExtOutportBit; external dll_name name 'AxdWriteExtOutportBit';
    function AxdWriteExtOutportByte; external dll_name name 'AxdWriteExtOutportByte';
    function AxdWriteExtOutportWord; external dll_name name 'AxdWriteExtOutportWord';
    function AxdWriteExtOutportDword; external dll_name name 'AxdWriteExtOutportDword';
    function AxdLevelSetExtportBit; external dll_name name 'AxdLevelSetExtportBit';
    function AxdLevelSetExtportByte; external dll_name name 'AxdLevelSetExtportByte';
    function AxdLevelSetExtportWord; external dll_name name 'AxdLevelSetExtportWord';
    function AxdLevelSetExtportDword; external dll_name name 'AxdLevelSetExtportDword';
    function AxdLevelGetExtportBit; external dll_name name 'AxdLevelGetExtportBit';
    function AxdLevelGetExtportByte; external dll_name name 'AxdLevelGetExtportByte';
    function AxdLevelGetExtportWord; external dll_name name 'AxdLevelGetExtportWord';
    function AxdLevelGetExtportDword; external dll_name name 'AxdLevelGetExtportDword';
    function AxdiIsPulseOn; external dll_name name 'AxdiIsPulseOn';
    function AxdiIsPulseOff; external dll_name name 'AxdiIsPulseOff';
    function AxdiIsOn; external dll_name name 'AxdiIsOn';
    function AxdiIsOff; external dll_name name 'AxdiIsOff';
    function AxdoOutPulseOn; external dll_name name 'AxdoOutPulseOn';
    function AxdoOutPulseOff; external dll_name name 'AxdoOutPulseOff';
    function AxdoToggleStart; external dll_name name 'AxdoToggleStart';
    function AxdoToggleStop; external dll_name name 'AxdoToggleStop';
    function AxdoSetNetworkErrorAct; external dll_name name 'AxdoSetNetworkErrorAct';
    function AxdoSetNetworkErrorUserValue; external dll_name name 'AxdoSetNetworkErrorUserValue';
    function AxdSetContactNum; external dll_name name 'AxdSetContactNum';
    function AxdGetContactNum; external dll_name name 'AxdGetContactNum';
    function AxdoWriteOutportByBitOffset; external dll_name name 'AxdoWriteOutportByBitOffset';
    function AxdiReadInportByBitOffset; external dll_name name 'AxdiReadInportByBitOffset';
    function AxdoReadOutportByBitOffset; external dll_name name 'AxdoReadOutportByBitOffset';
    function AxdInfoIsDIOModule; external dll_name name 'AxdInfoIsDIOModule';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxdInfoGetModuleCount; external dll_name name 'AxdInfoGetModuleCount';
    function AxdInfoGetInputCount; external dll_name name 'AxdInfoGetInputCount';
    function AxdInfoGetOutputCount; external dll_name name 'AxdInfoGetOutputCount';
    function AxdInfoGetModule; external dll_name name 'AxdInfoGetModule';
    function AxdInfoGetModuleEx; external dll_name name 'AxdInfoGetModuleEx';
    function AxdInfoGetModuleStatus; external dll_name name 'AxdInfoGetModuleStatus';
    function AxdiInterruptSetModule; external dll_name name 'AxdiInterruptSetModule';
    function AxdiInterruptSetModuleEnable; external dll_name name 'AxdiInterruptSetModuleEnable';
    function AxdiInterruptGetModuleEnable; external dll_name name 'AxdiInterruptGetModuleEnable';
    function AxdiInterruptRead; external dll_name name 'AxdiInterruptRead';
    function AxdiInterruptEdgeSetBit; external dll_name name 'AxdiInterruptEdgeSetBit';
    function AxdiInterruptEdgeSetByte; external dll_name name 'AxdiInterruptEdgeSetByte';
    function AxdiInterruptEdgeSetWord; external dll_name name 'AxdiInterruptEdgeSetWord';
    function AxdiInterruptEdgeSetDword; external dll_name name 'AxdiInterruptEdgeSetDword';
    function AxdiInterruptEdgeGetBit; external dll_name name 'AxdiInterruptEdgeGetBit';
    function AxdiInterruptEdgeGetByte; external dll_name name 'AxdiInterruptEdgeGetByte';
    function AxdiInterruptEdgeGetWord; external dll_name name 'AxdiInterruptEdgeGetWord';
    function AxdiInterruptEdgeGetDword; external dll_name name 'AxdiInterruptEdgeGetDword';
    function AxdiInterruptEdgeSet; external dll_name name 'AxdiInterruptEdgeSet';
    function AxdiInterruptEdgeGet; external dll_name name 'AxdiInterruptEdgeGet';
    function AxdiLevelSetInportBit; external dll_name name 'AxdiLevelSetInportBit';
    function AxdiLevelSetInportByte; external dll_name name 'AxdiLevelSetInportByte';
    function AxdiLevelSetInportWord; external dll_name name 'AxdiLevelSetInportWord';
    function AxdiLevelSetInportDword; external dll_name name 'AxdiLevelSetInportDword';
    function AxdiLevelGetInportBit; external dll_name name 'AxdiLevelGetInportBit';
    function AxdiLevelGetInportByte; external dll_name name 'AxdiLevelGetInportByte';
    function AxdiLevelGetInportWord; external dll_name name 'AxdiLevelGetInportWord';
    function AxdiLevelGetInportDword; external dll_name name 'AxdiLevelGetInportDword';
    function AxdiLevelSetInport; external dll_name name 'AxdiLevelSetInport';
    function AxdiLevelGetInport; external dll_name name 'AxdiLevelGetInport';
    function AxdoLevelSetOutportBit; external dll_name name 'AxdoLevelSetOutportBit';
    function AxdoLevelSetOutportByte; external dll_name name 'AxdoLevelSetOutportByte';
    function AxdoLevelSetOutportWord; external dll_name name 'AxdoLevelSetOutportWord';
    function AxdoLevelSetOutportDword; external dll_name name 'AxdoLevelSetOutportDword';
    function AxdoLevelGetOutportBit; external dll_name name 'AxdoLevelGetOutportBit';
    function AxdoLevelGetOutportByte; external dll_name name 'AxdoLevelGetOutportByte';
    function AxdoLevelGetOutportWord; external dll_name name 'AxdoLevelGetOutportWord';
    function AxdoLevelGetOutportDword; external dll_name name 'AxdoLevelGetOutportDword';
    function AxdoLevelSetOutport; external dll_name name 'AxdoLevelSetOutport';
    function AxdoLevelGetOutport; external dll_name name 'AxdoLevelGetOutport';
    function AxdoWriteOutport; external dll_name name 'AxdoWriteOutport';
    function AxdoWriteOutportBit; external dll_name name 'AxdoWriteOutportBit';
    function AxdoWriteOutportByte; external dll_name name 'AxdoWriteOutportByte';
    function AxdoWriteOutportWord; external dll_name name 'AxdoWriteOutportWord';
    function AxdoWriteOutportDword; external dll_name name 'AxdoWriteOutportDword';
    function AxdoReadOutport; external dll_name name 'AxdoReadOutport';
    function AxdoReadOutportBit; external dll_name name 'AxdoReadOutportBit';
    function AxdoReadOutportByte; external dll_name name 'AxdoReadOutportByte';
    function AxdoReadOutportWord; external dll_name name 'AxdoReadOutportWord';
    function AxdoReadOutportDword; external dll_name name 'AxdoReadOutportDword';
    function AxdiReadInport; external dll_name name 'AxdiReadInport';
    function AxdiReadInportBit; external dll_name name 'AxdiReadInportBit';
    function AxdiReadInportByte; external dll_name name 'AxdiReadInportByte';
    function AxdiReadInportWord; external dll_name name 'AxdiReadInportWord';
    function AxdiReadInportDword; external dll_name name 'AxdiReadInportDword';
    function AxdReadExtInportBit; external dll_name name 'AxdReadExtInportBit';
    function AxdReadExtInportByte; external dll_name name 'AxdReadExtInportByte';
    function AxdReadExtInportWord; external dll_name name 'AxdReadExtInportWord';
    function AxdReadExtInportDword; external dll_name name 'AxdReadExtInportDword';
    function AxdReadExtOutportBit; external dll_name name 'AxdReadExtOutportBit';
    function AxdReadExtOutportByte; external dll_name name 'AxdReadExtOutportByte';
    function AxdReadExtOutportWord; external dll_name name 'AxdReadExtOutportWord';
    function AxdReadExtOutportDword; external dll_name name 'AxdReadExtOutportDword';
    function AxdWriteExtOutportBit; external dll_name name 'AxdWriteExtOutportBit';
    function AxdWriteExtOutportByte; external dll_name name 'AxdWriteExtOutportByte';
    function AxdWriteExtOutportWord; external dll_name name 'AxdWriteExtOutportWord';
    function AxdWriteExtOutportDword; external dll_name name 'AxdWriteExtOutportDword';
    function AxdLevelSetExtportBit; external dll_name name 'AxdLevelSetExtportBit';
    function AxdLevelSetExtportByte; external dll_name name 'AxdLevelSetExtportByte';
    function AxdLevelSetExtportWord; external dll_name name 'AxdLevelSetExtportWord';
    function AxdLevelSetExtportDword; external dll_name name 'AxdLevelSetExtportDword';
    function AxdLevelGetExtportBit; external dll_name name 'AxdLevelGetExtportBit';
    function AxdLevelGetExtportByte; external dll_name name 'AxdLevelGetExtportByte';
    function AxdLevelGetExtportWord; external dll_name name 'AxdLevelGetExtportWord';
    function AxdLevelGetExtportDword; external dll_name name 'AxdLevelGetExtportDword';
    function AxdiIsPulseOn; external dll_name name 'AxdiIsPulseOn';
    function AxdiIsPulseOff; external dll_name name 'AxdiIsPulseOff';
    function AxdiIsOn; external dll_name name 'AxdiIsOn';
    function AxdiIsOff; external dll_name name 'AxdiIsOff';
    function AxdoOutPulseOn; external dll_name name 'AxdoOutPulseOn';
    function AxdoOutPulseOff; external dll_name name 'AxdoOutPulseOff';
    function AxdoToggleStart; external dll_name name 'AxdoToggleStart';
    function AxdoToggleStop; external dll_name name 'AxdoToggleStop';
    function AxdoSetNetworkErrorAct; external dll_name name 'AxdoSetNetworkErrorAct';
    function AxdoSetNetworkErrorUserValue; external dll_name name 'AxdoSetNetworkErrorUserValue';
    function AxdSetContactNum; external dll_name name 'AxdSetContactNum';
    function AxdGetContactNum; external dll_name name 'AxdGetContactNum';
    function AxdoWriteOutportByBitOffset; external dll_name name 'AxdoWriteOutportByBitOffset';
    function AxdiReadInportByBitOffset; external dll_name name 'AxdiReadInportByBitOffset';
    function AxdoReadOutportByBitOffset; external dll_name name 'AxdoReadOutportByBitOffset';
    function AxdInfoIsDIOModule; external dll_name name 'AxdInfoIsDIOModule';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxdInfoGetModuleCount; external dll_name name 'AxdInfoGetModuleCount';
    function AxdInfoGetInputCount; external dll_name name 'AxdInfoGetInputCount';
    function AxdInfoGetOutputCount; external dll_name name 'AxdInfoGetOutputCount';
    function AxdInfoGetModule; external dll_name name 'AxdInfoGetModule';
    function AxdInfoGetModuleEx; external dll_name name 'AxdInfoGetModuleEx';
    function AxdInfoGetModuleStatus; external dll_name name 'AxdInfoGetModuleStatus';
    function AxdiInterruptSetModule; external dll_name name 'AxdiInterruptSetModule';
    function AxdiInterruptSetModuleEnable; external dll_name name 'AxdiInterruptSetModuleEnable';
    function AxdiInterruptGetModuleEnable; external dll_name name 'AxdiInterruptGetModuleEnable';
    function AxdiInterruptRead; external dll_name name 'AxdiInterruptRead';
    function AxdiInterruptEdgeSetBit; external dll_name name 'AxdiInterruptEdgeSetBit';
    function AxdiInterruptEdgeSetByte; external dll_name name 'AxdiInterruptEdgeSetByte';
    function AxdiInterruptEdgeSetWord; external dll_name name 'AxdiInterruptEdgeSetWord';
    function AxdiInterruptEdgeSetDword; external dll_name name 'AxdiInterruptEdgeSetDword';
    function AxdiInterruptEdgeGetBit; external dll_name name 'AxdiInterruptEdgeGetBit';
    function AxdiInterruptEdgeGetByte; external dll_name name 'AxdiInterruptEdgeGetByte';
    function AxdiInterruptEdgeGetWord; external dll_name name 'AxdiInterruptEdgeGetWord';
    function AxdiInterruptEdgeGetDword; external dll_name name 'AxdiInterruptEdgeGetDword';
    function AxdiInterruptEdgeSet; external dll_name name 'AxdiInterruptEdgeSet';
    function AxdiInterruptEdgeGet; external dll_name name 'AxdiInterruptEdgeGet';
    function AxdiLevelSetInportBit; external dll_name name 'AxdiLevelSetInportBit';
    function AxdiLevelSetInportByte; external dll_name name 'AxdiLevelSetInportByte';
    function AxdiLevelSetInportWord; external dll_name name 'AxdiLevelSetInportWord';
    function AxdiLevelSetInportDword; external dll_name name 'AxdiLevelSetInportDword';
    function AxdiLevelGetInportBit; external dll_name name 'AxdiLevelGetInportBit';
    function AxdiLevelGetInportByte; external dll_name name 'AxdiLevelGetInportByte';
    function AxdiLevelGetInportWord; external dll_name name 'AxdiLevelGetInportWord';
    function AxdiLevelGetInportDword; external dll_name name 'AxdiLevelGetInportDword';
    function AxdiLevelSetInport; external dll_name name 'AxdiLevelSetInport';
    function AxdiLevelGetInport; external dll_name name 'AxdiLevelGetInport';
    function AxdoLevelSetOutportBit; external dll_name name 'AxdoLevelSetOutportBit';
    function AxdoLevelSetOutportByte; external dll_name name 'AxdoLevelSetOutportByte';
    function AxdoLevelSetOutportWord; external dll_name name 'AxdoLevelSetOutportWord';
    function AxdoLevelSetOutportDword; external dll_name name 'AxdoLevelSetOutportDword';
    function AxdoLevelGetOutportBit; external dll_name name 'AxdoLevelGetOutportBit';
    function AxdoLevelGetOutportByte; external dll_name name 'AxdoLevelGetOutportByte';
    function AxdoLevelGetOutportWord; external dll_name name 'AxdoLevelGetOutportWord';
    function AxdoLevelGetOutportDword; external dll_name name 'AxdoLevelGetOutportDword';
    function AxdoLevelSetOutport; external dll_name name 'AxdoLevelSetOutport';
    function AxdoLevelGetOutport; external dll_name name 'AxdoLevelGetOutport';
    function AxdoWriteOutport; external dll_name name 'AxdoWriteOutport';
    function AxdoWriteOutportBit; external dll_name name 'AxdoWriteOutportBit';
    function AxdoWriteOutportByte; external dll_name name 'AxdoWriteOutportByte';
    function AxdoWriteOutportWord; external dll_name name 'AxdoWriteOutportWord';
    function AxdoWriteOutportDword; external dll_name name 'AxdoWriteOutportDword';
    function AxdoReadOutport; external dll_name name 'AxdoReadOutport';
    function AxdoReadOutportBit; external dll_name name 'AxdoReadOutportBit';
    function AxdoReadOutportByte; external dll_name name 'AxdoReadOutportByte';
    function AxdoReadOutportWord; external dll_name name 'AxdoReadOutportWord';
    function AxdoReadOutportDword; external dll_name name 'AxdoReadOutportDword';
    function AxdiReadInport; external dll_name name 'AxdiReadInport';
    function AxdiReadInportBit; external dll_name name 'AxdiReadInportBit';
    function AxdiReadInportByte; external dll_name name 'AxdiReadInportByte';
    function AxdiReadInportWord; external dll_name name 'AxdiReadInportWord';
    function AxdiReadInportDword; external dll_name name 'AxdiReadInportDword';
    function AxdReadExtInportBit; external dll_name name 'AxdReadExtInportBit';
    function AxdReadExtInportByte; external dll_name name 'AxdReadExtInportByte';
    function AxdReadExtInportWord; external dll_name name 'AxdReadExtInportWord';
    function AxdReadExtInportDword; external dll_name name 'AxdReadExtInportDword';
    function AxdReadExtOutportBit; external dll_name name 'AxdReadExtOutportBit';
    function AxdReadExtOutportByte; external dll_name name 'AxdReadExtOutportByte';
    function AxdReadExtOutportWord; external dll_name name 'AxdReadExtOutportWord';
    function AxdReadExtOutportDword; external dll_name name 'AxdReadExtOutportDword';
    function AxdWriteExtOutportBit; external dll_name name 'AxdWriteExtOutportBit';
    function AxdWriteExtOutportByte; external dll_name name 'AxdWriteExtOutportByte';
    function AxdWriteExtOutportWord; external dll_name name 'AxdWriteExtOutportWord';
    function AxdWriteExtOutportDword; external dll_name name 'AxdWriteExtOutportDword';
    function AxdLevelSetExtportBit; external dll_name name 'AxdLevelSetExtportBit';
    function AxdLevelSetExtportByte; external dll_name name 'AxdLevelSetExtportByte';
    function AxdLevelSetExtportWord; external dll_name name 'AxdLevelSetExtportWord';
    function AxdLevelSetExtportDword; external dll_name name 'AxdLevelSetExtportDword';
    function AxdLevelGetExtportBit; external dll_name name 'AxdLevelGetExtportBit';
    function AxdLevelGetExtportByte; external dll_name name 'AxdLevelGetExtportByte';
    function AxdLevelGetExtportWord; external dll_name name 'AxdLevelGetExtportWord';
    function AxdLevelGetExtportDword; external dll_name name 'AxdLevelGetExtportDword';
    function AxdiIsPulseOn; external dll_name name 'AxdiIsPulseOn';
    function AxdiIsPulseOff; external dll_name name 'AxdiIsPulseOff';
    function AxdiIsOn; external dll_name name 'AxdiIsOn';
    function AxdiIsOff; external dll_name name 'AxdiIsOff';
    function AxdoOutPulseOn; external dll_name name 'AxdoOutPulseOn';
    function AxdoOutPulseOff; external dll_name name 'AxdoOutPulseOff';
    function AxdoToggleStart; external dll_name name 'AxdoToggleStart';
    function AxdoToggleStop; external dll_name name 'AxdoToggleStop';
    function AxdoSetNetworkErrorAct; external dll_name name 'AxdoSetNetworkErrorAct';
    function AxdoSetNetworkErrorUserValue; external dll_name name 'AxdoSetNetworkErrorUserValue';
    function AxdSetContactNum; external dll_name name 'AxdSetContactNum';
    function AxdGetContactNum; external dll_name name 'AxdGetContactNum';
    function AxdoWriteOutportByBitOffset; external dll_name name 'AxdoWriteOutportByBitOffset';
    function AxdiReadInportByBitOffset; external dll_name name 'AxdiReadInportByBitOffset';
    function AxdoReadOutportByBitOffset; external dll_name name 'AxdoReadOutportByBitOffset';
    function AxdInfoIsDIOModule; external dll_name name 'AxdInfoIsDIOModule';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxdInfoGetModuleCount; external dll_name name 'AxdInfoGetModuleCount';
    function AxdInfoGetInputCount; external dll_name name 'AxdInfoGetInputCount';
    function AxdInfoGetOutputCount; external dll_name name 'AxdInfoGetOutputCount';
    function AxdInfoGetModule; external dll_name name 'AxdInfoGetModule';
    function AxdInfoGetModuleEx; external dll_name name 'AxdInfoGetModuleEx';
    function AxdInfoGetModuleStatus; external dll_name name 'AxdInfoGetModuleStatus';
    function AxdiInterruptSetModule; external dll_name name 'AxdiInterruptSetModule';
    function AxdiInterruptSetModuleEnable; external dll_name name 'AxdiInterruptSetModuleEnable';
    function AxdiInterruptGetModuleEnable; external dll_name name 'AxdiInterruptGetModuleEnable';
    function AxdiInterruptRead; external dll_name name 'AxdiInterruptRead';
    function AxdiInterruptEdgeSetBit; external dll_name name 'AxdiInterruptEdgeSetBit';
    function AxdiInterruptEdgeSetByte; external dll_name name 'AxdiInterruptEdgeSetByte';
    function AxdiInterruptEdgeSetWord; external dll_name name 'AxdiInterruptEdgeSetWord';
    function AxdiInterruptEdgeSetDword; external dll_name name 'AxdiInterruptEdgeSetDword';
    function AxdiInterruptEdgeGetBit; external dll_name name 'AxdiInterruptEdgeGetBit';
    function AxdiInterruptEdgeGetByte; external dll_name name 'AxdiInterruptEdgeGetByte';
    function AxdiInterruptEdgeGetWord; external dll_name name 'AxdiInterruptEdgeGetWord';
    function AxdiInterruptEdgeGetDword; external dll_name name 'AxdiInterruptEdgeGetDword';
    function AxdiInterruptEdgeSet; external dll_name name 'AxdiInterruptEdgeSet';
    function AxdiInterruptEdgeGet; external dll_name name 'AxdiInterruptEdgeGet';
    function AxdiLevelSetInportBit; external dll_name name 'AxdiLevelSetInportBit';
    function AxdiLevelSetInportByte; external dll_name name 'AxdiLevelSetInportByte';
    function AxdiLevelSetInportWord; external dll_name name 'AxdiLevelSetInportWord';
    function AxdiLevelSetInportDword; external dll_name name 'AxdiLevelSetInportDword';
    function AxdiLevelGetInportBit; external dll_name name 'AxdiLevelGetInportBit';
    function AxdiLevelGetInportByte; external dll_name name 'AxdiLevelGetInportByte';
    function AxdiLevelGetInportWord; external dll_name name 'AxdiLevelGetInportWord';
    function AxdiLevelGetInportDword; external dll_name name 'AxdiLevelGetInportDword';
    function AxdiLevelSetInport; external dll_name name 'AxdiLevelSetInport';
    function AxdiLevelGetInport; external dll_name name 'AxdiLevelGetInport';
    function AxdoLevelSetOutportBit; external dll_name name 'AxdoLevelSetOutportBit';
    function AxdoLevelSetOutportByte; external dll_name name 'AxdoLevelSetOutportByte';
    function AxdoLevelSetOutportWord; external dll_name name 'AxdoLevelSetOutportWord';
    function AxdoLevelSetOutportDword; external dll_name name 'AxdoLevelSetOutportDword';
    function AxdoLevelGetOutportBit; external dll_name name 'AxdoLevelGetOutportBit';
    function AxdoLevelGetOutportByte; external dll_name name 'AxdoLevelGetOutportByte';
    function AxdoLevelGetOutportWord; external dll_name name 'AxdoLevelGetOutportWord';
    function AxdoLevelGetOutportDword; external dll_name name 'AxdoLevelGetOutportDword';
    function AxdoLevelSetOutport; external dll_name name 'AxdoLevelSetOutport';
    function AxdoLevelGetOutport; external dll_name name 'AxdoLevelGetOutport';
    function AxdoWriteOutport; external dll_name name 'AxdoWriteOutport';
    function AxdoWriteOutportBit; external dll_name name 'AxdoWriteOutportBit';
    function AxdoWriteOutportByte; external dll_name name 'AxdoWriteOutportByte';
    function AxdoWriteOutportWord; external dll_name name 'AxdoWriteOutportWord';
    function AxdoWriteOutportDword; external dll_name name 'AxdoWriteOutportDword';
    function AxdoReadOutport; external dll_name name 'AxdoReadOutport';
    function AxdoReadOutportBit; external dll_name name 'AxdoReadOutportBit';
    function AxdoReadOutportByte; external dll_name name 'AxdoReadOutportByte';
    function AxdoReadOutportWord; external dll_name name 'AxdoReadOutportWord';
    function AxdoReadOutportDword; external dll_name name 'AxdoReadOutportDword';
    function AxdiReadInport; external dll_name name 'AxdiReadInport';
    function AxdiReadInportBit; external dll_name name 'AxdiReadInportBit';
    function AxdiReadInportByte; external dll_name name 'AxdiReadInportByte';
    function AxdiReadInportWord; external dll_name name 'AxdiReadInportWord';
    function AxdiReadInportDword; external dll_name name 'AxdiReadInportDword';
    function AxdReadExtInportBit; external dll_name name 'AxdReadExtInportBit';
    function AxdReadExtInportByte; external dll_name name 'AxdReadExtInportByte';
    function AxdReadExtInportWord; external dll_name name 'AxdReadExtInportWord';
    function AxdReadExtInportDword; external dll_name name 'AxdReadExtInportDword';
    function AxdReadExtOutportBit; external dll_name name 'AxdReadExtOutportBit';
    function AxdReadExtOutportByte; external dll_name name 'AxdReadExtOutportByte';
    function AxdReadExtOutportWord; external dll_name name 'AxdReadExtOutportWord';
    function AxdReadExtOutportDword; external dll_name name 'AxdReadExtOutportDword';
    function AxdWriteExtOutportBit; external dll_name name 'AxdWriteExtOutportBit';
    function AxdWriteExtOutportByte; external dll_name name 'AxdWriteExtOutportByte';
    function AxdWriteExtOutportWord; external dll_name name 'AxdWriteExtOutportWord';
    function AxdWriteExtOutportDword; external dll_name name 'AxdWriteExtOutportDword';
    function AxdLevelSetExtportBit; external dll_name name 'AxdLevelSetExtportBit';
    function AxdLevelSetExtportByte; external dll_name name 'AxdLevelSetExtportByte';
    function AxdLevelSetExtportWord; external dll_name name 'AxdLevelSetExtportWord';
    function AxdLevelSetExtportDword; external dll_name name 'AxdLevelSetExtportDword';
    function AxdLevelGetExtportBit; external dll_name name 'AxdLevelGetExtportBit';
    function AxdLevelGetExtportByte; external dll_name name 'AxdLevelGetExtportByte';
    function AxdLevelGetExtportWord; external dll_name name 'AxdLevelGetExtportWord';
    function AxdLevelGetExtportDword; external dll_name name 'AxdLevelGetExtportDword';
    function AxdiIsPulseOn; external dll_name name 'AxdiIsPulseOn';
    function AxdiIsPulseOff; external dll_name name 'AxdiIsPulseOff';
    function AxdiIsOn; external dll_name name 'AxdiIsOn';
    function AxdiIsOff; external dll_name name 'AxdiIsOff';
    function AxdoOutPulseOn; external dll_name name 'AxdoOutPulseOn';
    function AxdoOutPulseOff; external dll_name name 'AxdoOutPulseOff';
    function AxdoToggleStart; external dll_name name 'AxdoToggleStart';
    function AxdoToggleStop; external dll_name name 'AxdoToggleStop';
    function AxdoSetNetworkErrorAct; external dll_name name 'AxdoSetNetworkErrorAct';
    function AxdoSetNetworkErrorUserValue; external dll_name name 'AxdoSetNetworkErrorUserValue';
    function AxdSetContactNum; external dll_name name 'AxdSetContactNum';
    function AxdGetContactNum; external dll_name name 'AxdGetContactNum';
    function AxdoWriteOutportByBitOffset; external dll_name name 'AxdoWriteOutportByBitOffset';
    function AxdiReadInportByBitOffset; external dll_name name 'AxdiReadInportByBitOffset';
    function AxdoReadOutportByBitOffset; external dll_name name 'AxdoReadOutportByBitOffset';
    function AxdoLinkSetOutport; external dll_name name 'AxdoLinkSetOutport';
    function AxdoLinkGetOutport; external dll_name name 'AxdoLinkGetOutport';
    function AxdoLinkResetOutport; external dll_name name 'AxdoLinkResetOutport';
    function AxdoInterLockSetOutport; external dll_name name 'AxdoInterLockSetOutport';
    function AxdoInterLockGetOutport; external dll_name name 'AxdoInterLockGetOutport';
    function AxdoInterLockIsEnabled; external dll_name name 'AxdoInterLockIsEnabled';
    function AxdoInterLockResetOutport; external dll_name name 'AxdoInterLockResetOutport';
