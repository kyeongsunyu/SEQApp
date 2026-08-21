//*****************************************************************************
//*****************************************************************************
//**
//** File Name
//** ---------
//**
//** AXS.PAS
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

unit AXS;

interface

uses Windows, Messages, AXHS;

//========== Board and module verification API(Info) - Information =================================================================================

// Return board number, module position and module ID of relevant axis. 
function AxsInfoGetPort(lPortNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;

// Get the specified module board : Sub ID, module name, module description
//===============================================/
// support product      : EtherCAT
// upModuleSubID        : EtherCAT SubID(for distinguish between EtherCAT modules)
// szModuleName         : model name of module(50 Bytes)
// szModuleDescription  : description of module(80 Bytes)
//======================================================//
function AxsInfoGetPortEx(lPortNo : LongInt; upModuleSubID : PLongInt; szModuleName : PChar; szModuleDescription : PChar) : DWord; stdcall;
// Returns whether the serial module exists.
function AxsInfoIsSerialModule(upStatus : PDWord) :DWord; stdcall;
// Returns whether the port is valid.
function AxsInfoIsInvalidPortNo(lPortNo : LongInt) : DWord; stdcall;
// Returns whether the port is controllable.
function AxsInfoGetPortStatus(lPortNo : LongInt) : DWord; stdcall;
// Returns the number of valid communication ports in the system.
function AxsInfoGetPortCount(lpPortCount : PLongInt) : DWord; stdcall;
// Returns the first axis number of the board / module.
function AxsInfoGetFirstPortNo(lBoardNo : LongInt; lModulePos : LongInt; lpPortNo : PLongInt) : DWord; stdcall;
// Returns the first communication port number of the board.
function AxsInfoGetBoardFirstPortNo(lBoardNo : LongInt; lModulePos : LongInt; lpPortNo : PLongInt) : DWord; stdcall;
//========== Serial communication function(Port) =================================================================================
// Open communication port. PortOpen can be used only by one application.
// lBaudRate : 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
// lDataBits : 7, 8 
// lStopBits : 1, 2
// lParity   : [0]None, [1]Even, [2]Odd
// dwFlagsAndAttributes : Reserved
function AxsPortOpen(lPortNo : LongInt; lBaudRate : LongInt; lDataBits : LongInt; lStopBits : LongInt; lParity : LongInt; dwFlagsAndAttributes : DWord) : DWord; stdcall;
// Close the communication port.
function AxsPortClose(lPortNo : LongInt) : DWord; stdcall;   
// Set communication port (communication buffer is not initialized)
// lpDCB->BaudRate  : 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
// lpDCB->ByteSize  : 7, 8  
// lpDCB->StopBits  : 1, 2
// lpDCB->Parity    : [0]None, [1]Even, [2]Odd
function AxsPortSetCommState(lPortNo : LongInt; var lpDCB : DCB) : DWord; stdcall;
// Get the communication port setting value.
function AxsPortGetCommState(lPortNo : LongInt; var lpDCB : DCB) : DWord; stdcall;
// Set the communication port timeout value.
// lpCommTimeouts->ReadIntervalTimeout          : Set timeout time between strings after string input starts (milliseconds)
// lpCommTimeouts->ReadTotalTimeoutMultiplier;  : Timeout time setting for one character string at the communication speed set in the read operation (milliseconds)
// lpCommTimeouts->ReadTotalTimeoutConstant;    : Timeout time setting excluding the timeout for the number of characters to be input (milliseconds)
// lpCommTimeouts->WriteTotalTimeoutMultiplier; : Timeout time setting for one character string at the communication speed set in writing operation (milliseconds)
// lpCommTimeouts->WriteTotalTimeoutConstant;   : Timeout time setting excluding the timeout for the number of characters to be transferred (milliseconds)
function AxsPortSetCommTimeouts(lPortNo : LongInt; var lpCommTimeouts : COMMTIMEOUTS) : DWord; stdcall;
// Get the timeout value of the communication port.
function AxsPortGetCommTimeouts(lPortNo : LongInt; var lpCommTimeouts : COMMTIMEOUTS) : DWord; stdcall;
// Erase the device's error flag or check the number of data sent and received.
// lpErrors : 
//      [1]CE_RXOVER:       Receive buffer overflow
//      [2]CE_OVERRUN:      Receive Buffer Overrun Error
//      [4]CE_RXPARITY:     Receive data parity bit error
//      [8]CE_FRAME:        Receive framing error
// lpStat->cbInQue :        Number of data input to receive buffer
// lpStat->cbOutQue:        Number of data remaining in the transmit buffer
function AxsPortClearCommError(lPortNo : LongInt; lpErrors : LPDWORD; lpStat : COMSTAT) : DWord; stdcall;
// Stop sending data
function AxsPortSetCommBreak(lPortNo : LongInt) : DWord; stdcall;
// Resume data transmission
function AxsPortClearCommBreak(lPortNo : LongInt) : DWord; stdcall;    
// Stop sending or receiving or clear buffer
// dwFlags: 
//      [1]PURGE_TXABORT:    Stop writing
//      [2]PURGE_RXABORT:    Stop Reading
//      [4]PURGE_TXCLEAR:    Clear if there is data in the transmit buffer
//      [8]PURGE_RXCLEAR:    Clear if there is data in the receive buffer
function AxsPortPurgeComm(lPortNo : LongInt; dwFlags : DWord) : DWord; stdcall;
// Writes data to the serial port
// lpBuffer :                The pointer value of the buffer that holds the data to write to the device.
// nNumberOfBytesToWrite :   Number of bytes of actual data in lpBuffer
// lpNumberOfBytesWritten :  Returns the number of bytes actually written (in case of None Overrapped)
// lpOverlapped :            Point value of OVERLAPPED structure for asynchronous
function AxsPortWriteFile(lPortNo : LongInt; lpBuffer : Pointer; nNumberOfBytesToWrite : DWord; lpNumberOfBytesWritten : LPDWORD; lpOverlapped : POVERLAPPED) : DWord; stdcall
// Read data from serial port
// lpBuffer :               The pointer value of the buffer that holds the data to write to the device.
// nNumberOfBytesToRead :   The size of the buffer pointed to by lpBuffer in bytes
// lpNumberOfBytesRead :    Returns the number of bytes actually read (in case of None Overrapped)
// lpOverlapped :           Point value of OVERLAPPED structure for asynchronous
function AxsPortReadFile(lPortNo : LongInt; lpBuffer : Pointer; nNumberOfBytesToRead : DWord; lpNumberOfBytesRead : LPDWORD; lpOverlapped : POVERLAPPED) : DWord; stdcall;

// Returns the result of the serial port overlapped operation
// lpOverlapped->hEvent :       The event handle to be signaled after the transfer is complete. Set this value before using the AxsPortWriteFile, AxsPortReadFile function.
// lpNumberOfBytesTransferred:  Variable pointer to get the actual byte size of the transfer
// bWait:                       Determines the processing when the I / O operation is not completed
//      [0]: Wait for I / O operation to finish
//      [1]: Returns even if the I / O operation is not completed
function AxsPortGetOverlappedResult(lPortNo : LongInt; lpOverlapped : POVERLAPPED; lpNumberOfBytesTransferred : LPDWORD; bWait : LongBool) : DWord; stdcall;
    
// Returns the last error code on the serial port
// [  0]ERROR_SUCCESS           No error
// [  2]ERROR_FILE_NOT_FOUND    Invalid communication port
// [  5]ERROR_ACCESS_DENIED     When the communication port is in use
// [995]ERROR_OPERATION_ABORTED The I/O operation has been aborted because of either a thread exit or an application request.
// [996]ERROR_IO_INCOMPLETE     In Overrapped mode, if the write operation is not completed or a timeout occurs
// [997]ERROR_IO_PENDING        I / O operation is in progress when in overrapped mode
function AxsPortGetLastError(dwpErrCode : PDWord) : DWord; stdcall;
function AxsPortSetLastError(dwErrCode : DWord) : DWord; stdcall;


//------------------------------------------------------------------------------------------------------------------

implementation

const

    dll_name    = 'Axl.dll';
    function AxsInfoGetPort; external dll_name name 'AxsInfoGetPort';
    function AxsInfoGetPortEx; external dll_name name 'AxsInfoGetPortEx';
    function AxsInfoIsSerialModule; external dll_name name 'AxsInfoIsSerialModule';
    function AxsInfoIsInvalidPortNo; external dll_name name 'AxsInfoIsInvalidPortNo';
    function AxsInfoGetPortStatus; external dll_name name 'AxsInfoGetPortStatus';
    function AxsInfoGetPortCount; external dll_name name 'AxsInfoGetPortCount';
    function AxsInfoGetFirstPortNo; external dll_name name 'AxsInfoGetFirstPortNo';
    function AxsInfoGetBoardFirstPortNo; external dll_name name 'AxsInfoGetBoardFirstPortNo';
    function AxsPortOpen; external dll_name name 'AxsPortOpen';
    function AxsPortClose; external dll_name name 'AxsPortClose';
    function AxsPortSetCommState; external dll_name name 'AxsPortSetCommState';
    function AxsPortGetCommState; external dll_name name 'AxsPortGetCommState';
    function AxsPortSetCommTimeouts; external dll_name name 'AxsPortSetCommTimeouts';
    function AxsPortGetCommTimeouts; external dll_name name 'AxsPortGetCommTimeouts';
    function AxsPortClearCommError; external dll_name name 'AxsPortClearCommError';
    function AxsPortSetCommBreak; external dll_name name 'AxsPortSetCommBreak';
    function AxsPortClearCommBreak; external dll_name name 'AxsPortClearCommBreak';
    function AxsPortPurgeComm; external dll_name name 'AxsPortPurgeComm';
    function AxsPortWriteFile; external dll_name name 'AxsPortWriteFile';
    function AxsPortReadFile; external dll_name name 'AxsPortReadFile';
    function AxsPortGetOverlappedResult; external dll_name name 'AxsPortGetOverlappedResult';
    function AxsPortGetLastError; external dll_name name 'AxsPortGetLastError';
    function AxsPortSetLastError; external dll_name name 'AxsPortSetLastError';
end.
