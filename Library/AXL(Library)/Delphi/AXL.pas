//****************************************************************************
///****************************************************************************
//*****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXL.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Library Header File
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

unit AXL;

interface

uses Windows, Messages, AXHS, AXA, AXD, AXM;



//========== Library initialization =================================================================================

// Library initialization
function AxlOpen (lIrqNo : LongInt) : DWord; stdcall;

// Do not reset to hardware chip when library is initialized.
function AxlOpenNoReset (lIrqNo : LongInt) : DWord; stdcall;

// Exit from library use
function AxlClose () : Boolean; stdcall;

// Verify if the library is initialized
function AxlIsOpened () : Boolean; stdcall;


// Use Interrupt
function AxlInterruptEnable () : DWord; stdcall;

// Not use Interrput
function AxlInterruptDisable () : DWord; stdcall;


//========== library and base board information =================================================================================

// Verify the number of registered base board
function AxlGetBoardCount (lpBoardCount : PLongInt) : DWord; stdcall;
// Verify the library version
function AxlGetLibVersion (szVersion : PChar) : DWord; stdcall;

// Verify Network models Module Status
function AxlGetModuleNodeStatus(lBoardNo : LongInt; lModulePos : LongInt) : DWord; stdcall;

// Verify Board Status
function AxlGetBoardStatus(lBoardNo : LongInt) : DWord; stdcall;

// return Configuration Lock status of Network product.
// *wpLockMode  : DISABLE(0), ENABLE(1)
function AxlGetLockMode(lBoardNo : LongInt; wpLockMode : PWord) : DWord; stdcall;


// Function to check whether all slaves of specified network type are operational
// NETWORK_TYPE_ALL(0)
// NETWORK_TYPE_RTEX(1)
// NETWORK_TYPE_MLII(2)
// NETWORK_TYPE_MLIII(3)
// NETWORK_TYPE_SIIIH(4)
// NETWORK_TYPE_ECAT(5)
function AxlIsConnectedAllSlaves(uNetworkType : DWord) : DWord; stdcall;

    function AxlGetReturnCodeInfo (dwReturnCode : DWord; lReturnInfoSize : LongInt; lpRecivedSize : PLongInt; szReturnInfo : char*) : DWord; stdcall;
//========== Log level =================================================================================
// Set message level to be output to EzSpy
// uLevel : 0 - 3 Set
// LEVEL_NONE(0)    : ALL Message don't Output
// LEVEL_ERROR(1)   : Error Message Output
// LEVEL_RUNSTOP(2) : Run/Stop relative Message Output during Motion.
// LEVEL_FUNCTION(3): ALL Message don't Output
function AxlSetLogLevel (uLevel : DWord) : DWord; stdcall;
// Verify message level to be output to EzSpy
function AxlGetLogLevel (upLevel : PDWord) : DWord; stdcall;


//========== MLIII =================================================================================
function AxlScanStart(lBoardNo : LongInt; lNet : LongInt) : DWord; stdcall;
function AxlBoardConnect(lBoardNo : LongInt; lNet : LongInt) : DWord; stdcall;
function AxlBoardDisconnect(lBoardNo : LongInt; lNet : LongInt) : DWord; stdcall;

    function AxlReadFanSpeed (lBoardNo : LongInt; dpFanSpeed : PDouble) : DWord; stdcall;

    function AxlEzSpyUserLog (szUserLog : char*) : DWord; stdcall;


implementation

const

    dll_name    = 'AXL.dll';
    function AxlOpen; external dll_name name 'AxlOpen';
    function AxlOpenNoReset; external dll_name name 'AxlOpenNoReset';
    function AxlClose; external dll_name name 'AxlClose';
    function AxlIsOpened; external dll_name name 'AxlIsOpened';
    function AxlInterruptEnable; external dll_name name 'AxlInterruptEnable';
    function AxlInterruptDisable; external dll_name name 'AxlInterruptDisable';
    function AxlGetBoardCount; external dll_name name 'AxlGetBoardCount';
    function AxlGetLibVersion; external dll_name name 'AxlGetLibVersion';
    function AxlGetModuleNodeStatus; external dll_name name 'AxlGetModuleNodeStatus';
    function AxlGetBoardStatus; external dll_name name 'AxlGetBoardStatus';
    function AxlGetLockMode; external dll_name name 'AxlGetLockMode';
    function AxlIsConnectedAllSlaves; external dll_name name 'AxlIsConnectedAllSlaves';
    function AxlSetLogLevel; external dll_name name 'AxlSetLogLevel';
    function AxlGetLogLevel; external dll_name name 'AxlGetLogLevel';
    function AxlScanStart; external dll_name name 'AxlScanStart';
    function AxlBoardConnect; external dll_name name 'AxlBoardConnect';
    function AxlBoardDisconnect; external dll_name name 'AxlBoardDisconnect';
    function AxlEzSpyUserLog; external dll_name name 'AxlEzSpyUserLog';
    function AxlOpen; external dll_name name 'AxlOpen';
    function AxlOpenNoReset; external dll_name name 'AxlOpenNoReset';
    function AxlClose; external dll_name name 'AxlClose';
    function AxlIsOpened; external dll_name name 'AxlIsOpened';
    function AxlInterruptEnable; external dll_name name 'AxlInterruptEnable';
    function AxlInterruptDisable; external dll_name name 'AxlInterruptDisable';
    function AxlGetBoardCount; external dll_name name 'AxlGetBoardCount';
    function AxlGetLibVersion; external dll_name name 'AxlGetLibVersion';
    function AxlGetModuleNodeStatus; external dll_name name 'AxlGetModuleNodeStatus';
    function AxlGetBoardStatus; external dll_name name 'AxlGetBoardStatus';
    function AxlGetLockMode; external dll_name name 'AxlGetLockMode';
    function AxlIsConnectedAllSlaves; external dll_name name 'AxlIsConnectedAllSlaves';
    function AxlSetLogLevel; external dll_name name 'AxlSetLogLevel';
    function AxlGetLogLevel; external dll_name name 'AxlGetLogLevel';
    function AxlScanStart; external dll_name name 'AxlScanStart';
    function AxlBoardConnect; external dll_name name 'AxlBoardConnect';
    function AxlBoardDisconnect; external dll_name name 'AxlBoardDisconnect';
    function AxlOpen; external dll_name name 'AxlOpen';
    function AxlOpenNoReset; external dll_name name 'AxlOpenNoReset';
    function AxlClose; external dll_name name 'AxlClose';
    function AxlIsOpened; external dll_name name 'AxlIsOpened';
    function AxlInterruptEnable; external dll_name name 'AxlInterruptEnable';
    function AxlInterruptDisable; external dll_name name 'AxlInterruptDisable';
    function AxlGetBoardCount; external dll_name name 'AxlGetBoardCount';
    function AxlGetLibVersion; external dll_name name 'AxlGetLibVersion';
    function AxlGetModuleNodeStatus; external dll_name name 'AxlGetModuleNodeStatus';
    function AxlGetBoardStatus; external dll_name name 'AxlGetBoardStatus';
    function AxlGetLockMode; external dll_name name 'AxlGetLockMode';
    function AxlIsConnectedAllSlaves; external dll_name name 'AxlIsConnectedAllSlaves';
    function AxlSetLogLevel; external dll_name name 'AxlSetLogLevel';
    function AxlGetLogLevel; external dll_name name 'AxlGetLogLevel';
    function AxlScanStart; external dll_name name 'AxlScanStart';
    function AxlBoardConnect; external dll_name name 'AxlBoardConnect';
    function AxlBoardDisconnect; external dll_name name 'AxlBoardDisconnect';
    function AxlOpen; external dll_name name 'AxlOpen';
    function AxlOpenNoReset; external dll_name name 'AxlOpenNoReset';
    function AxlClose; external dll_name name 'AxlClose';
    function AxlIsOpened; external dll_name name 'AxlIsOpened';
    function AxlInterruptEnable; external dll_name name 'AxlInterruptEnable';
    function AxlInterruptDisable; external dll_name name 'AxlInterruptDisable';
    function AxlGetBoardCount; external dll_name name 'AxlGetBoardCount';
    function AxlGetLibVersion; external dll_name name 'AxlGetLibVersion';
    function AxlGetModuleNodeStatus; external dll_name name 'AxlGetModuleNodeStatus';
    function AxlGetBoardStatus; external dll_name name 'AxlGetBoardStatus';
    function AxlGetLockMode; external dll_name name 'AxlGetLockMode';
    function AxlIsConnectedAllSlaves; external dll_name name 'AxlIsConnectedAllSlaves';
    function AxlSetLogLevel; external dll_name name 'AxlSetLogLevel';
    function AxlGetLogLevel; external dll_name name 'AxlGetLogLevel';
    function AxlScanStart; external dll_name name 'AxlScanStart';
    function AxlBoardConnect; external dll_name name 'AxlBoardConnect';
    function AxlBoardDisconnect; external dll_name name 'AxlBoardDisconnect';
    function AxlOpen; external dll_name name 'AxlOpen';
    function AxlOpenNoReset; external dll_name name 'AxlOpenNoReset';
    function AxlClose; external dll_name name 'AxlClose';
    function AxlIsOpened; external dll_name name 'AxlIsOpened';
    function AxlInterruptEnable; external dll_name name 'AxlInterruptEnable';
    function AxlInterruptDisable; external dll_name name 'AxlInterruptDisable';
    function AxlGetBoardCount; external dll_name name 'AxlGetBoardCount';
    function AxlGetLibVersion; external dll_name name 'AxlGetLibVersion';
    function AxlGetModuleNodeStatus; external dll_name name 'AxlGetModuleNodeStatus';
    function AxlGetBoardStatus; external dll_name name 'AxlGetBoardStatus';
    function AxlGetLockMode; external dll_name name 'AxlGetLockMode';
    function AxlIsConnectedAllSlaves; external dll_name name 'AxlIsConnectedAllSlaves';
    function AxlGetReturnCodeInfo; external dll_name name 'AxlGetReturnCodeInfo';
    function AxlSetLogLevel; external dll_name name 'AxlSetLogLevel';
    function AxlGetLogLevel; external dll_name name 'AxlGetLogLevel';
    function AxlScanStart; external dll_name name 'AxlScanStart';
    function AxlBoardConnect; external dll_name name 'AxlBoardConnect';
    function AxlBoardDisconnect; external dll_name name 'AxlBoardDisconnect';
    function AxlReadFanSpeed; external dll_name name 'AxlReadFanSpeed';
    function AxlEzSpyUserLog; external dll_name name 'AxlEzSpyUserLog';
