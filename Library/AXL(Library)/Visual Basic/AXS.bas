Attribute VB_Name = "AXS"
'****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ---------
'**
'** AXS.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Ajinextek Motion Library Header File
'**
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Source Change Indices
'** ---------------------
'**
'** (None)
'**
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Website
'** ---------------------
'**
'** http://www.ajinextek.com
'**
'*****************************************************************************
'*****************************************************************************
'*

'========== Board and module verification API(Info) - Information =================================================================================

' Return board number, module position and module ID of relevant axis.
Public Declare Function AxsInfoGetPort Lib "AXL.dll" (ByVal lPortNo As Long, ByRef lpBoardNo As Long, ByRef lpModulePos As Long, ByRef upModuleID As Long) As Long
'  Get the specified module board : Sub ID, module name, module description
' ===============================================/
'  support product      : EtherCAT
'  upModuleSubID        : EtherCAT SubID(for distinguish between EtherCAT modules)
'  szModuleName         : model name of module(50 Bytes)
'  szModuleDescription  : description of module(80 Bytes)
' ======================================================//  
Public Declare Function AxsInfoGetPortEx Lib "AXL.dll" (ByVal lPortNo As Long, ByRef upModuleSubID As Long, ByRef szModuleName As Byte, ByRef szModuleDescription As Byte) As Long
' Returns whether the serial module exists.
Public Declare Function AxsInfoIsSerialModule Lib "AXL.dll" (ByRef upStatus As Long) As Long
' Returns whether the port is valid.
Public Declare Function AxsInfoIsInvalidPortNo Lib "AXL.dll" (ByVal lPortNo As Long) As Long
' Returns whether the port is controllable.
Public Declare Function AxsInfoGetPortStatus Lib "AXL.dll" (ByVal lPortNo As Long) As Long
' Returns the number of valid communication ports in the system.
Public Declare Function AxsInfoGetPortCount Lib "AXL.dll" (ByRef lpPortCount As Long) As Long
' Returns the first axis number of the board / module.
Public Declare Function AxsInfoGetFirstPortNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpPortNo As Long) As Long
' Returns the first communication port number of the board.
Public Declare Function AxsInfoGetBoardFirstPortNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpPortNo As Long) As Long
' ========== Serial communication function(Port) =================================================================================
'  Open communication port. PortOpen can be used only by one application.
'  lBaudRate : 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
'  lDataBits : 7, 8 
'  lStopBits : 1, 2
'  lParity   : [0]None, [1]Even, [2]Odd
'  dwFlagsAndAttributes : Reserved
Public Declare Function AxsPortOpen Lib "AXL.dll" (ByVal lPortNo As Long, ByVal lBaudRate As Long, ByVal lDataBits As Long, ByVal lStopBits As Long, ByVal lParity As Long, ByVal dwFlagsAndAttributes As Long) As Long
' Close the communication port.
Public Declare Function AxsPortClose Lib "AXL.dll" (ByVal lPortNo As Long) As Long   
' Set communication port (communication buffer is not initialized)
' lpDCB->BaudRate  : 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200
' lpDCB->ByteSize  : 7, 8  
' lpDCB->StopBits  : 1, 2
' lpDCB->Parity    : [0]None, [1]Even, [2]Odd
Public Declare Function AxsPortSetCommState Lib "kernel32.dll" (ByVal lPortNo As Long, lpDCB As DCB) As Long
' Get the communication port setting value.
Public Declare Function AxsPortGetCommState Lib "kernel32.dll" (ByVal lPortNo As Long, lpDCB As DCB) As Long
' Set the communication port timeout value.
' lpCommTimeouts->ReadIntervalTimeout          : Set timeout time between strings after string input starts (milliseconds)
' lpCommTimeouts->ReadTotalTimeoutMultiplier;  : Timeout time setting for one character string at the communication speed set in the read operation (milliseconds)
' lpCommTimeouts->ReadTotalTimeoutConstant;    : Timeout time setting excluding the timeout for the number of characters to be input (milliseconds)
' lpCommTimeouts->WriteTotalTimeoutMultiplier; : Timeout time setting for one character string at the communication speed set in writing operation (milliseconds)
' lpCommTimeouts->WriteTotalTimeoutConstant;   : Timeout time setting excluding the timeout for the number of characters to be transferred (milliseconds)
Public Declare Function AxsPortSetCommTimeouts Lib "kernel32.dll" (ByVal lPortNo As Long, lpCommTimeouts As COMMTIMEOUTS) As Long
' Get the timeout value of the communication port.
Public Declare Function AxsPortGetCommTimeouts Lib "kernel32.dll" (ByVal lPortNo As Long, lpCommTimeouts As COMMTIMEOUTS) As Long
' Erase the device's error flag or check the number of data sent and received.
' lpErrors : 
'      [1]CE_RXOVER:       Receive buffer overflow
'      [2]CE_OVERRUN:      Receive Buffer Overrun Error
'      [4]CE_RXPARITY:     Receive data parity bit error
'      [8]CE_FRAME:        Receive framing error
' lpStat->cbInQue :        Number of data input to receive buffer
' lpStat->cbOutQue:        Number of data remaining in the transmit buffer
Public Declare Function AxsPortClearCommError Lib "kernel32.dll" (ByVal lPortNo As Long, lpErrors As Long, lpStat As COMSTAT) As Long
' Stop sending data
Public Declare Function AxsPortSetCommBreak Lib "AXL.dll" (ByVal lPortNo As Long) As Long
' Resume data transmission
Public Declare Function AxsPortClearCommBreak Lib "AXL.dll" (ByVal lPortNo As Long) As Long    
' Stop sending or receiving or clear buffer
' dwFlags: 
'      [1]PURGE_TXABORT:    Stop writing
'      [2]PURGE_RXABORT:    Stop Reading
'      [4]PURGE_TXCLEAR:    Clear if there is data in the transmit buffer
'      [8]PURGE_RXCLEAR:    Clear if there is data in the receive buffer
Public Declare Function AxsPortPurgeComm Lib "AXL.dll" (ByVal lPortNo As Long, ByVal dwFlags As Long) As Long
' Writes data to the serial port
' lpBuffer :                The pointer value of the buffer that holds the data to write to the device.
' nNumberOfBytesToWrite :   Number of bytes of actual data in lpBuffer
' lpNumberOfBytesWritten :  Returns the number of bytes actually written (in case of None Overrapped)
' lpOverlapped :            Point value of OVERLAPPED structure for asynchronous
Public Declare Function AxsPortWriteFile Lib "kernel32.dll" (ByVal lPortNo As Long, lpBuffer As Long, ByVal nNumberOfBytesToWrite As Long, lpNumberOfBytesWritten As Long, lpOverlapped As OVERLAPPED) As Long
' Read data from serial port
' lpBuffer :               The pointer value of the buffer that holds the data to write to the device.
' nNumberOfBytesToRead :   The size of the buffer pointed to by lpBuffer in bytes
' lpNumberOfBytesRead :    Returns the number of bytes actually read (in case of None Overrapped)
' lpOverlapped :           Point value of OVERLAPPED structure for asynchronous
Public Declare Function AxsPortReadFile Lib "kernel32.dll" (ByVal lPortNo As Long, lpBuffer As Long, ByVal nNumberOfBytesToRead As Long, lpNumberOfBytesRead As Long, lpOverlapped As OVERLAPPED) As Long
' Returns the result of the serial port overlapped operation
' lpOverlapped->hEvent :       The event handle to be signaled after the transfer is complete. Set this value before using the AxsPortWriteFile, AxsPortReadFile function.
' lpNumberOfBytesTransferred:  Variable pointer to get the actual byte size of the transfer
' bWait:                       Determines the processing when the I / O operation is not completed
'      [0]: Wait for I / O operation to finish
'      [1]: Returns even if the I / O operation is not completed
Public Declare Function AxsPortGetOverlappedResult Lib "AXL.dll" (ByVal lPortNo As Long, lpOverlapped As OVERLAPPED, lpNumberOfBytesTransferred As Long, ByVal bWait As Long) As Long
' Returns the last error code on the serial port
' [  0]ERROR_SUCCESS           No error
' [  2]ERROR_FILE_NOT_FOUND    Invalid communication port
' [  5]ERROR_ACCESS_DENIED     When the communication port is in use
' [995]ERROR_OPERATION_ABORTED The I/O operation has been aborted because of either a thread exit or an application request.
' [996]ERROR_IO_INCOMPLETE     In Overrapped mode, if the write operation is not completed or a timeout occurs
' [997]ERROR_IO_PENDING        I / O operation is in progress when in overrapped mode
Public Declare Function AxsPortGetLastError Lib "AXL.dll" (ByRef dwpErrCode As Long) As Long
Public Declare Function AxsPortSetLastError Lib "AXL.dll" (ByVal dwErrCode As Long) As Long