'*****************************************************************************
'/****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ----------
'**
'** AXL.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Ajinextek Library Header File
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
'*/
'

Attribute VB_Name = "AXL"




'========== Library initialization =================================================================================

' Library initialization
Public Declare Function AxlOpen Lib "AXL.dll" (ByVal lIrqNo As Long) As Long

' Do not reset to hardware chip when library is initialized.
Public Declare Function AxlOpenNoReset Lib "AXL.dll" (ByVal lIrqNo As Long) As Long

' Exit from library use
Public Declare Function AxlClose Lib "AXL.dll" () As Byte

' Verify if the library is initialized
Public Declare Function AxlIsOpened Lib "AXL.dll" () As Byte


' Use Interrupt
Public Declare Function AxlInterruptEnable Lib "AXL.dll" () As Long

' Not use Interrupt
Public Declare Function AxlInterruptDisable Lib "AXL.dll" () As Long


'========== library and base board information =================================================================================

' Verify the number of registered base board
Public Declare Function AxlGetBoardCount Lib "AXL.dll" (ByRef lpBoardCount As Long) As Long
' Verify the library version
Public Declare Function AxlGetLibVersion Lib "AXL.dll" (ByVal szVersion As Byte) As Long

' Verify Network models Module Status
Public Declare Function AxlGetModuleNodeStatus Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long) As Long

' Verify Board Status
Public Declare Function AxlGetBoardStatus Lib "AXL.dll" (ByVal lBoardNo As Long) As Long

' return Configuration Lock status of Network product.
' *wpLockMode  : DISABLE(0), ENABLE(1)
Public Declare Function AxlGetLockMode Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef wpLockMode As Long) As Long


' Function to check whether all slaves of specified network type are operational
' NETWORK_TYPE_ALL(0)
' NETWORK_TYPE_RTEX(1)
' NETWORK_TYPE_MLII(2)
' NETWORK_TYPE_MLIII(3)
' NETWORK_TYPE_SIIIH(4)
' NETWORK_TYPE_ECAT(5)
Public Declare Function AxlIsConnectedAllSlaves Lib "AXL.dll" (ByVal uNetworkType As Integer) As Long

    Public Declare Function AxlGetReturnCodeInfo Lib "AXL.dll" (ByVal dwReturnCode As Long, ByVal lReturnInfoSize As Long, ByRef lpRecivedSize As Long, ByRef szReturnInfo As char*) As Long
'========== Log level =================================================================================

' Set message level to be output to EzSpy
' uLevel : 0 - 3 Set
' LEVEL_NONE(0)    : ALL Message don't Output
' LEVEL_ERROR(1)   : Error Message Output
' LEVEL_RUNSTOP(2) : Run/Stop relative Message Output during Motion.
' LEVEL_FUNCTION(3): ALL Message don't Output
Public Declare Function AxlSetLogLevel Lib "AXL.dll" (ByVal uLevel As Long) As Long
' Verify message level to be output to EzSpy
Public Declare Function AxlGetLogLevel Lib "AXL.dll" (ByRef upLevel As Long) As Long


'========== MLIII =================================================================================
' The API for start searching each module of network product.
Public Declare Function AxlScanStart Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lNet As Long) As Long
' The API for connect all modules of each board.
Public Declare Function AxlBoardConnect Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lNet As Long) As Long
' The API for disconnect all modules of each board.
Public Declare Function AxlBoardDisconnect Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lNet As Long) As Long

    Public Declare Function AxlReadFanSpeed Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dpFanSpeed As Double) As Long

    Public Declare Function AxlEzSpyUserLog Lib "AXL.dll" (ByRef szUserLog As char*) As Long


