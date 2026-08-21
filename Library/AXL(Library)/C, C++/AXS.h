
#pragma once

#ifdef __cplusplus
extern "C" {

#endif    //__cplusplus

    //========== Board and module verification functions(Info) - Infomation ===============================================================
    // Returns the board number, module location, and module ID of the corresponding port.
    DWORD    __stdcall AxsInfoGetPort(long lPortNo, long *lpBoardNo, long *lpModulePos, DWORD *upModuleID);

    // Get the specified module board : Sub ID, module name, module description
    //===============================================/
    // support product      : EtherCAT
    // upModuleSubID        : EtherCAT SubID(for distinguish between EtherCAT modules)
    // szModuleName         : model name of module(50 Bytes)
    // szModuleDescription  : description of module(80 Bytes)
    //======================================================//  
    DWORD    __stdcall AxsInfoGetPortEx(long lPortNo, DWORD *upModuleSubID, char* szModuleName, char* szModuleDescription);

    // Returns whether the serial module exists.
    DWORD    __stdcall AxsInfoIsSerialModule(DWORD *upStatus);
    // Returns whether the port is valid.
    DWORD    __stdcall AxsInfoIsInvalidPortNo(long lPortNo);
    // Returns whether the port is controllable.
    DWORD    __stdcall AxsInfoGetPortStatus(long lPortNo);
    // Returns the number of valid communication ports in the system.
    DWORD    __stdcall AxsInfoGetPortCount(long *lpPortCount);
    // Returns the first axis number of the board / module.
    DWORD    __stdcall AxsInfoGetFirstPortNo(long lBoardNo, long lModulePos, long *lpPortNo);
    // Returns the first communication port number of the board.
    DWORD    __stdcall AxsInfoGetBoardFirstPortNo(long lBoardNo, long lModulePos, long *lpPortNo);

    //========== Serial communication function(Port) =================================================================================
    // Open communication port. PortOpen can be used only by one application.
    // lBaudRate : 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
    // lDataBits : 7, 8 
    // lStopBits : 1, 2
    // lParity   : [0]None, [1]Even, [2]Odd
    // dwFlagsAndAttributes : Reserved
    DWORD    __stdcall AxsPortOpen(long lPortNo, long lBaudRate, long lDataBits, long lStopBits, long lParity, DWORD dwFlagsAndAttributes);
    // Close the communication port.
    DWORD    __stdcall AxsPortClose(long lPortNo);
    // Set communication port (communication buffer is not initialized)
    // lpDCB->BaudRate  : 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
    // lpDCB->ByteSize  : 7, 8  
    // lpDCB->StopBits  : 1, 2
    // lpDCB->Parity    : [0]None, [1]Even, [2]Odd
    DWORD    __stdcall AxsPortSetCommState(long lPortNo, LPDCB lpDCB);
    // Get the communication port setting value.
    DWORD    __stdcall AxsPortGetCommState(long lPortNo, LPDCB lpDCB);
    // Set the communication port timeout value.
    // lpCommTimeouts->ReadIntervalTimeout          : Set timeout time between strings after string input starts (milliseconds)
    // lpCommTimeouts->ReadTotalTimeoutMultiplier;  : Timeout time setting for one character string at the communication speed set in the read operation (milliseconds)
    // lpCommTimeouts->ReadTotalTimeoutConstant;    : Timeout time setting excluding the timeout for the number of characters to be input (milliseconds)
    // lpCommTimeouts->WriteTotalTimeoutMultiplier; : Timeout time setting for one character string at the communication speed set in writing operation (milliseconds)
    // lpCommTimeouts->WriteTotalTimeoutConstant;   : Timeout time setting excluding the timeout for the number of characters to be transferred (milliseconds)
    DWORD    __stdcall AxsPortSetCommTimeouts(long lPortNo, LPCOMMTIMEOUTS lpCommTimeouts);
    // Get the timeout value of the communication port.
    DWORD    __stdcall AxsPortGetCommTimeouts(long lPortNo, LPCOMMTIMEOUTS lpCommTimeouts);
    // Erase the device's error flag or check the number of data sent and received.
    // lpErrors : 
    //      [1]CE_RXOVER:       Receive buffer overflow
    //      [2]CE_OVERRUN:      Receive Buffer Overrun Error
    //      [4]CE_RXPARITY:     Receive data parity bit error
    //      [8]CE_FRAME:        Receive framing error
    // lpStat->cbInQue :        Number of data input to receive buffer
    // lpStat->cbOutQue:        Number of data remaining in the transmit buffer
    DWORD    __stdcall AxsPortClearCommError(long lPortNo, LPDWORD lpErrors, LPCOMSTAT lpStat);
    // Stop sending data
    DWORD    __stdcall AxsPortSetCommBreak(long lPortNo);
    // Resume data transmission
    DWORD    __stdcall AxsPortClearCommBreak(long lPortNo);    
    // Stop sending or receiving or clear buffer
    // dwFlags: 
    //      [1]PURGE_TXABORT:    Stop writing
    //      [2]PURGE_RXABORT:    Stop Reading
    //      [4]PURGE_TXCLEAR:    Clear if there is data in the transmit buffer
    //      [8]PURGE_RXCLEAR:    Clear if there is data in the receive buffer
    DWORD    __stdcall AxsPortPurgeComm(long lPortNo, DWORD dwFlags);
    // Writes data to the serial port
    // lpBuffer :                The pointer value of the buffer that holds the data to write to the device.
    // nNumberOfBytesToWrite :   Number of bytes of actual data in lpBuffer
    // lpNumberOfBytesWritten :  Returns the number of bytes actually written (in case of None Overrapped)
    // lpOverlapped :            Point value of OVERLAPPED structure for asynchronous
    DWORD    __stdcall AxsPortWriteFile(long lPortNo, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
    // Read data from serial port
    // lpBuffer :               The pointer value of the buffer that holds the data to write to the device.
    // nNumberOfBytesToRead :   The size of the buffer pointed to by lpBuffer in bytes
    // lpNumberOfBytesRead :    Returns the number of bytes actually read (in case of None Overrapped)
    // lpOverlapped :           Point value of OVERLAPPED structure for asynchronous
    DWORD    __stdcall AxsPortReadFile(long lPortNo, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

    // Returns the result of the serial port overlapped operation
    // lpOverlapped->hEvent :       The event handle to be signaled after the transfer is complete. Set this value before using the AxsPortWriteFile, AxsPortReadFile function.
    // lpNumberOfBytesTransferred:  Variable pointer to get the actual byte size of the transfer
    // bWait:                       Determines the processing when the I / O operation is not completed
    //      [0]: Wait for I / O operation to finish
    //      [1]: Returns even if the I / O operation is not completed
    DWORD    __stdcall AxsPortGetOverlappedResult(long lPortNo, LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait);
    
    // Returns the last error code on the serial port
    // [  0]ERROR_SUCCESS           No error
    // [  2]ERROR_FILE_NOT_FOUND    Invalid communication port
    // [  5]ERROR_ACCESS_DENIED     When the communication port is in use
    // [995]ERROR_OPERATION_ABORTED The I/O operation has been aborted because of either a thread exit or an application request.
    // [996]ERROR_IO_INCOMPLETE     In Overrapped mode, if the write operation is not completed or a timeout occurs
    // [997]ERROR_IO_PENDING        I / O operation is in progress when in overrapped mode
    DWORD    __stdcall AxsPortGetLastError(long lPortNo, DWORD *dwpErrCode);
    DWORD    __stdcall AxsPortSetLastError(long lPortNo, DWORD dwErrCode);

#ifdef __cplusplus

}
#endif    //__cplusplus