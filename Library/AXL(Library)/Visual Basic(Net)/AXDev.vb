Option Strict Off
Option Explicit On
Module AXDev



    Public Declare Function AxlGetBoardAddress Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef upBoardAddress As Integer) As Integer
    Public Declare Function AxlGetBoardID Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef upBoardID As Integer) As Integer
    Public Declare Function AxlGetBoardVersion Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef upBoardVersion As Integer) As Integer
    Public Declare Function AxlGetModuleID Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef upModuleID As Integer) As Integer
    Public Declare Function AxlGetModuleVersion Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef upModuleVersion As Integer) As Integer
    Public Declare Function AxlGetModuleNodeInfo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef upNetNo As Integer, ByRef upNodeAddr As Integer) As Integer

    Public Declare Function AxlSetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lPageAddr As Integer, ByVal lBytesNum As Integer, ByRef bpSetData As Byte) As Integer

    Public Declare Function AxlSetEStopInterLock Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwInterLock As Integer, ByVal dwDigFilterVal As Integer) As Integer
    Public Declare Function AxlGetEStopInterLock Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwInterLock As Integer, ByRef dwDigFilterVal As Integer) As Integer
    Public Declare Function AxlReadEStopInterLock Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwInterLock As Integer) As Integer

    Public Declare Function AxlGetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lPageAddr As Integer, ByVal lBytesNum As Integer, ByRef bpGetData As Byte) As Integer

    Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer
    Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer

    Public Declare Function AxmSetCommand Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte) As Integer
    Public Declare Function AxmSetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    Public Declare Function AxmGetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    Public Declare Function AxmSetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    Public Declare Function AxmGetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    Public Declare Function AxmSetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    Public Declare Function AxmGetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    Public Declare Function AxmSetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    Public Declare Function AxmGetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer

    Public Declare Function AxmSetCommandQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte) As Integer
    Public Declare Function AxmSetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    Public Declare Function AxmGetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    Public Declare Function AxmSetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    Public Declare Function AxmGetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    Public Declare Function AxmSetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    Public Declare Function AxmGetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    Public Declare Function AxmSetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    Public Declare Function AxmGetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer

    Public Declare Function AxmGetPortData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByRef upData As Integer) As Integer
    Public Declare Function AxmSetPortData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByVal dwData As Integer) As Integer
    Public Declare Function AxmGetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal byOffset As Integer, ByRef wData As Integer) As Integer
    Public Declare Function AxmSetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal byOffset As Integer, ByVal wData As Integer) As Integer

    Public Declare Function AxmSetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByVal event As Integer, ByVal data As Integer) As Integer
    Public Declare Function AxmGetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByRef event As Integer, ByRef data As Integer) As Integer

    Public Declare Function AxmSetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByVal event As Integer, ByVal cmd As Integer, ByVal data As Integer) As Integer
    Public Declare Function AxmGetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByRef event As Integer, ByRef cmd As Integer, ByRef data As Integer) As Integer

    Public Declare Function AxmSetScriptCaptionQueueClear Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uSelect As Integer) As Integer

    Public Declare Function AxmGetScriptCaptionQueueCount Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef updata As Integer, ByVal uSelect As Integer) As Integer

    Public Declare Function AxmGetScriptCaptionQueueDataCount Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef updata As Integer, ByVal uSelect As Integer) As Integer

    Public Declare Function AxmGetOptimizeDriveData Lib "AXL.dll" () As Integer


    Public Declare Function AxmBoardWriteByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal byData As Byte) As Integer
    Public Declare Function AxmBoardReadByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef byData As Byte) As Integer

    Public Declare Function AxmBoardWriteWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal wData As Integer) As Integer
    Public Declare Function AxmBoardReadWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef wData As Integer) As Integer

    Public Declare Function AxmBoardWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal dwData As Integer) As Integer
    Public Declare Function AxmBoardReadDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer

    Public Declare Function AxmModuleWriteByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByVal byData As Byte) As Integer
    Public Declare Function AxmModuleReadByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByRef byData As Byte) As Integer

    Public Declare Function AxmModuleWriteWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByVal wData As Integer) As Integer
    Public Declare Function AxmModuleReadWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByRef wData As Integer) As Integer

    Public Declare Function AxmModuleWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByVal dwData As Integer) As Integer
    Public Declare Function AxmModuleReadDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer

    Public Declare Function AxmStatusSetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double) As Integer
    Public Declare Function AxmStatusGetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dpPos As Double) As Integer

    Public Declare Function AxmStatusSetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double) As Integer
    Public Declare Function AxmStatusGetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dpPos As Double) As Integer

'========== Append function. =========================================================================================================
' Increase a straight line interpolation at speed to the infinity.
' Must put the distance speed rate.
Public Declare Function AxmLineMoveVel Lib "AXL.dll" (ByVal lCoord As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer


'========= Sensor drive API( Read carefully: Available only PI , No function in QI)=========================================================================
' Set mark signal( used in sensor positioning drive)
Public Declare Function AxmSensorSetSignal Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uLevel As Integer) As Integer
' Verify mark signal( used in sensor positioning drive)
Public Declare Function AxmSensorGetSignal Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upLevel As Integer) As Integer
' Verify mark signal( used in sensor positioning drive)state
Public Declare Function AxmSensorReadSignal Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upStatus As Integer) As Integer


' Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop.
' Applied motion is started upon the start of API, and escapes from the API after the motion is completed.
Public Declare Function AxmSensorMovePos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Integer) As Integer


' Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop.
' Applied motion is started upon the start of API, then escapes from the API immediately without waiting until the motion is completed.
Public Declare Function AxmSensorStartMovePos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Integer) As Integer


' Return record of origin search progress step.
' *lpStepCount      : Number of step(Be recorded)
' *upMainStepNumber : Array point of 'MainStepNumber ' information(Be recorded)
' *upStepNumber     : Array point of 'StepNumber ' information(Be recorded)
' *upStepBranch     : Array point of branch information by step(Be recorded)
' ※ Caution : Number of array should be fixed 50.
Public Declare Function AxmHomeGetStepTrace Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef lpStepCount As Integer, ByRef upMainStepNumber As Integer, ByRef upStepNumber As Integer, ByRef upStepBranch As Integer) As Integer


'=======Additive home search (Applicable to PI-N804/404  only)=================================================================================

' Set home setting parameters of axis specified by user. (Use exclusive-use register for QI chip).
' uZphasCount : Z phase count after home completion. (0 - 15)
' lHomeMode   : Home setting mode( 0 - 12)
' lClearSet   : Select use of position clear and remaining pulse clear (0 - 3)
'               0: No use of position clear, no use of remaining pulse clear
'               1: use of position clear, no use of remaining pulse clear
'               2: No use of position clear, use of remaining pulse clear
'               3: use of position clear, use of remaining pulse clear
' dOrgVel : Set Org  Speed related home
' dLastVel: Set Last Speed related home
Public Declare Function AxmHomeSetConfig Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uZphasCount As Integer, ByVal lHomeMode As Integer, ByVal lClearSet As Integer, ByVal dOrgVel As Double, ByVal dLastVel As Double, ByVal dLeavePos As Double) As Integer
' Return home setting parameters of axis specified by user.
Public Declare Function AxmHomeGetConfig Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upZphasCount As Integer, ByRef lpHomeMode As Integer, ByRef lpClearSet As Integer, ByRef dpOrgVel As Double, ByRef dpLastVel As Double, ByRef dpLeavePos As Double) As Integer


' Start home search of axis specified by user
' Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
' If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
' Move direction      : CW when Vel value is positive, CCW when negative.
Public Declare Function AxmHomeSetMoveSearch Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer


' Start home return of axis specified by user.
' Set when lHomeMode is used: set 0 - 12
' If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
' Move direction      : CW when Vel value is positive, CCW when negative.
Public Declare Function AxmHomeSetMoveReturn Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer


' Home separation of axis specified by user is started.
' Move direction      : CW when Vel value is positive, CCW when negative.
Public Declare Function AxmHomeSetMoveLeave Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer


' User start home search of multi-axis specified by user.
' Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
' If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
' Move direction      : CW when Vel value is positive, CCW when negative.
Public Declare Function AxmHomeSetMultiMoveSearch Lib "AXL.dll" (ByVal lArraySize As Integer, ByRef lpAxesNo As Integer, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Integer


'Set move velocity profile mode of specific coordinate system.
' (caution : Available to use only after axis mapping)
'ProfileMode : '0' - symmetry Trapezoid
'              '1' - asymmetric Trapezoid
'              '2' - symmetry Quasi-S Curve
'              '3' - symmetry S Curve
'              '4' - asymmetric S Curve
Public Declare Function AxmContiSetProfileMode Lib "AXL.dll" (ByVal lCoord As Integer, ByVal uProfileMode As Integer) As Integer
' Return move velocity profile mode of specific coordinate system.
Public Declare Function AxmContiGetProfileMode Lib "AXL.dll" (ByVal lCoord As Integer, ByRef upProfileMode As Integer) As Integer


'========== Reading group for input interrupt occurrence flag
' Reading the interrupt occurrence state by bit unit in specified input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagReadBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
' Reading the interrupt occurrence state by byte unit in specified input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagReadByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
' Reading the interrupt occurrence state by word unit in specified input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagReadWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
' Reading the interrupt occurrence state by double word unit in specified input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagReadDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
' Reading the interrupt occurrence state by bit unit in entire input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagRead Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer


'========= API related log ==========================================================================================
' This API sets or resets in order to monitor the API execution result of set axis in EzSpy.
' uUse : use or not use => DISABLE(0), ENABLE(1)
Public Declare Function AxmLogSetAxis Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uUse As Integer) As Integer


' This API verifies if the API execution result of set axis is monitored in EzSpy.
Public Declare Function AxmLogGetAxis Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upUse As Integer) As Integer


'==Log
' Set whether to log output to EzSpy of specified input channel
Public Declare Function AxaiLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uUse As Integer) As Integer
' Verify whether to log output to EzSpy of specified input channel
Public Declare Function AxaiLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUse As Integer) As Integer


' Set whether to log output in EzSpy of specified output channel
Public Declare Function AxaoLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uUse As Integer) As Integer
' Verify whether log output is done in EzSpy of specified output channel.
Public Declare Function AxaoLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUse As Integer) As Integer


' Set whether execute log output on EzSpy of specified module
Public Declare Function AxdLogSetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uUse As Integer) As Integer
' Verify whether execute log output on EzSpy of specified module
Public Declare Function AxdLogGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upUse As Integer) As Integer


' Verify whether to firmware version designated RTEX board.
Public Declare Function AxlGetFirmwareVersion Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal szVersion As String) As Integer
' Sent to firmware designated board.
Public Declare Function AxlSetFirmwareCopy Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef wData As Integer, ByRef wCmdData As Integer) As Integer
' Execute Firmware update to designated board.
Public Declare Function AxlSetFirmwareUpdate Lib "AXL.dll" (ByVal lBoardNo As Integer) As Integer
' Verify whether currently RTEX status Initialized.
Public Declare Function AxlCheckStatus Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwStatus As Integer) As Integer
' Execute universal command designated axis of board.
Public Declare Function AxlRtexUniversalCmd Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wCmd As Integer, ByVal wOffset As Integer, ByRef wData As Integer) As Integer
' Execute RTEX communication command designated axis.
Public Declare Function AxmRtexSlaveCmd Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwCmdCode As Integer, ByVal dwTypeCode As Integer, ByVal dwIndexCode As Integer, ByVal dwCmdConfigure As Integer, ByVal dwValue As Integer) As Integer
' Verify whether Result of RTEX communication command designated axis.
Public Declare Function AxmRtexGetSlaveCmdResult Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwIndex As Integer, ByRef dwValue As Integer) As Integer
' Check the result of the RTEX communication command executed on the specified axis. PCIE-Rxx04-RTEX only
Public Declare Function AxmRtexGetSlaveCmdResultEx Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpCommand As Integer, ByRef dwpType As Integer, ByRef dwpIndex As Integer, ByRef dwpValue As Integer) As Integer
' Verify whether RTEX status information designated axis.
Public Declare Function AxmRtexGetAxisStatus Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwStatus As Integer) As Integer
' Verify whether RTEX communication return information designated axis.(Actual position, Velocity, Torque)
Public Declare Function AxmRtexGetAxisReturnData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwReturn1 As Integer, ByRef dwReturn2 As Integer, ByRef dwReturn3 As Integer) As Integer
' Verify whether currently status information of RTEX slave axis.(mechanical, Inposition and etc)
Public Declare Function AxmRtexGetAxisSlaveStatus Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwStatus As Integer) As Integer


' Enter the universal network command of specified MLII slave axis.
Public Declare Function AxmSetAxisCmd Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef tagCommand As Integer) As Integer
' Verifying result of universal network command of specified MLII slave axis.
Public Declare Function AxmGetAxisCmdResult Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef tagCommand As Integer) As Integer


' The specified SID Write the result of the network command to the slave module and return it.
Public Declare Function AxdSetAndGetSlaveCmdResult Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef tagSetCommand As Integer, ByRef tagGetCommand As Integer) As Integer
Public Declare Function AxaSetAndGetSlaveCmdResult Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef tagSetCommand As Integer, ByRef tagGetCommand As Integer) As Integer
Public Declare Function AxcSetAndGetSlaveCmdResult Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef tagSetCommand As Integer, ByRef tagGetCommand As Integer) As Integer

' Verify DPRAM data
Public Declare Function AxlGetDpRamData Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wAddress As Integer, ByRef dwpRdData As Integer) As Integer
' Verify DPRAM data in Word unit.
Public Declare Function AxlBoardReadDpramWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef dwpRdData As Integer) As Integer
' Set DPRAM data in Word unit.
Public Declare Function AxlBoardWriteDpramWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal dwWrData As Integer) As Integer

' Transmit instructions of each slave of each board.
Public Declare Function AxlSetSendBoardEachCommand Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwCommand As Integer, ByRef dwpSendData As Integer, ByVal dwLength As Integer) As Integer
' Transmit instructions to each board.
Public Declare Function AxlSetSendBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwCommand As Integer, ByRef dwpSendData As Integer, ByVal dwLength As Integer) As Integer
' Verify the response of each board.
Public Declare Function AxlGetResponseBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwpReadData As Integer) As Integer

' Reading firmware version function of slaves in network type master board.
' Declare with array of ucaFirmwareVersion unsigned char type(Size : 4 or more)
Public Declare Function AxmInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef ucaFirmwareVersion As Integer) As Integer
Public Declare Function AxaInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef ucaFirmwareVersion As Integer) As Integer
Public Declare Function AxdInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef ucaFirmwareVersion As Integer) As Integer
Public Declare Function AxcInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal ucaFirmwareVersion As Integer) As Integer


'======== Only for PCI-R1604-MLII ===========================================================================
' Set the value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
' Default value : Max
' Setting value Range : 0 ~ 4000H
' If it is set to 4000H or higher, the setting is set higher than that, but the operation is applied to the value of 4000H.
Public Declare Function  AxmSetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwTorqFeedForward As Integer) As Integer

' It is API that read value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
' Default value : Max
Public Declare Function  AxmGetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpTorqFeedForward As Integer) As Integer

' It is API that set the value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
' Default value : 0
' Setting value Range : 0 ~ FFFFH
Public Declare Function  AxmSetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwVelocityFeedForward As Integer) As Integer

' It is API that read value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
Public Declare Function AxmGetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpVelocityFeedForward As Integer) As Integer


' Set Encoder type.
' Default value : 0(TYPE_INCREMENTAL)
' Setting range : 0 ~ 1
' dwEncoderType : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
Public Declare Function AxmSignalSetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwEncoderType As Integer) As Integer


' Verify Encoder type.
Public Declare Function AxmSignalGetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpEncoderType As Integer) As Integer



' For updating the slave firmware(only for RTEX-PM).
' Public Declare Function AxmSetSendAxisCommand Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wCommand As Integer, ByRef wpSendData As Integer, ByVal wLength As Integer) As Integer

'======== Only for PCI-R1604-RTEX, RTEX-PM==============================================================
' When Input Universal Input 2, 3, Set Jog move velocity
' Set only once execute after all drive setting (Ex, PulseOutMethod, MoveUnitPerPulse etc..)
Public Declare Function AxmMotSetUserMotion Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer


' When Input Universal Input 2, 3, Set Jog move usage
' Setting value :  0(DISABLE), 1(ENABLE)
Public Declare Function AxmMotSetUserMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwUsage As Integer) As Integer


' Set Load/UnLoad Position to Automatically move use MPGP Input.
Public Declare Function AxmMotSetUserPosMotion Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dLoadPos As Double, ByVal dUnLoadPos As Double, ByVal dwFilter As Integer, ByVal dwDelay As Integer) As Integer


' Set Usage Load/UnLoad Position to Automatically move use MPGP Input
' Setting value :  0(DISABLE), 1(Position function A), 2(Position function B).
Public Declare Function AxmMotSetUserPosMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwUsage As Integer) As Integer

'========================================================================================================

'======== SIO-CN2CH, Only for absolute position trigger module(B0) ================================================
' The API of writing memory data.
Public Declare Function AxcKeWriteRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByVal dwData As Integer) As Integer
' The API of reading memory data.
Public Declare Function AxcKeReadRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByRef dwpData As Integer) As Integer
' Memory initialization API.
Public Declare Function AxcKeResetRamDataAll Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwData As Integer) As Integer
' Trigger timeout setting API.
Public Declare Function AxcTriggerSetTimeout Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwTimeout As Integer) As Integer
' Trigger timeout checking API.
Public Declare Function AxcTriggerGetTimeout Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpTimeout As Integer) As Integer
' Trigger Waiting State checking API.
Public Declare Function AxcStatusGetWaitState Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpState As Integer) As Integer
' Trigger Waiting State setting API.
Public Declare Function AxcStatusSetWaitState Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwState As Integer) As Integer

' Write command to designated channel.
Public Declare Function AxcKeSetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCommand As Integer, ByVal dwData As Integer) As Integer
' Write command to designated channel.
Public Declare Function AxcKeSetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCommand As Integer, ByVal wData As Integer) As Integer
' Verify register of specified channel.
Public Declare Function AxcKeGetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCommand As Integer, ByRef dwpData As Integer) As Integer
' Verify register of specified channel.
Public Declare Function AxcKeGetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCommand As Integer, ByRef wpData As Integer) As Integer

'========================================================================================================

' ======== Only for PCI-N804/N404, Sequence Motion ===========================================================
' Set Axis Information of sequence Motion (min 1axis)
' lSeqMapNo : Sequence Motion Index Point
' lSeqMapSize : Number of axis
' long* LSeqAxesNo : Number of arrar
Public Declare Function AxmSeqSetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal lSeqMapSize As Integer, ByRef lSeqAxesNo As Integer) As Integer
Public Declare Function AxmSeqGetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef lSeqMapSize As Integer, ByRef lSeqAxesNo As Integer) As Integer


' Set Standard(Master)Axis of Sequence Motion.
' By all means Set in AxmSeqSetAxisMap setting axis.
Public Declare Function AxmSeqSetMasterAxisNo Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal lMasterAxisNo As Integer) As Integer


' Notifies the library node start loading of Sequence Motion.
Public Declare Function AxmSeqBeginNode Lib "AXL.dll" (ByVal lSeqMapNo As Integer) As Integer


' Notifies the library node end loading of Sequence Motion.
Public Declare Function AxmSeqEndNode Lib "AXL.dll" (ByVal lSeqMapNo As Integer) As Integer


' Start Sequence Motion Move.
Public Declare Function AxmSeqStart Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal dwStartOption As Integer) As Integer


' Set each profile node Information of Sequence Motion in Library.
' if used 1axis Sequence Motion, Must be Set *dPosition one Array.
Public Declare Function AxmSeqAddNode Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef dPosition As Double, ByVal dVelocity As Double, ByVal dAcceleration As Double, ByVal dDeceleration As Double, ByVal dNextVelocity As Double) As Integer


' Return Node Index number of Sequence Motion.
Public Declare Function AxmSeqGetNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef lCurNodeNo As Integer) As Integer


'  Return All node count of Sequence Motion.
Public Declare Function AxmSeqGetTotalNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef lTotalNodeCnt As Integer) As Integer


' Return Sequence Motion drive status  of specific SeqMap.
' dwInMotion : 0(Drive end), 1(In drive).
Public Declare Function AxmSeqIsMotion Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef dwInMotion As Integer) As Integer


' Clear Sequence Motion Memory
Public Declare Function AxmSeqWriteClear Lib "AXL.dll" (ByVal lSeqMapNo As Integer) As Integer


' Stop sequence motion
' dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
Public Declare Function AxmSeqStop Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal dwStopMode As Integer) As Integer


'========================================================================================================

'======== Only for PCIe-Rxx04-SIIIH ==========================================================================
' (SIIIH, MR_J4_xxB, Para : 0 ~ 8) ==
'     [0] : Command Position
'     [1] : Actual Position
'     [2] : Actual Velocity
'     [3] : Mechanical Signal
'     [4] : Regeneration load factor(%)
'     [5] : Effective load factor(%)
'     [6] : Peak load factor(%)
'     [7] : Current Feedback
'     [8] : Command Velocity
Public Declare Function AxmStatusSetMon Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwParaNo1 As Integer, ByVal dwParaNo2 As Integer, ByVal dwParaNo3 As Integer, ByVal dwParaNo4 As Integer, ByVal dwUse As Integer) As Integer
Public Declare Function AxmStatusGetMon Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpParaNo1 As Integer, ByRef dwpParaNo2 As Integer, ByRef dwpParaNo3 As Integer, ByRef dwpParaNo4 As Integer, ByRef dwpUse As Integer) As Integer
Public Declare Function AxmStatusReadMon Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpParaNo1 As Integer, ByRef dwpParaNo2 As Integer, ByRef dwpParaNo3 As Integer, ByRef dwpParaNo4 As Integer, ByRef dwDataValid As Integer) As Integer
Public Declare Function AxmStatusReadMonEx Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef lpDataCnt As Integer, ByRef dwpReadData As Integer) As Integer

'=============================================================================================================

'======== Only for PCI-R32IOEV-RTEX ===========================================================================
' The API for read or write HPI register which allocated as I/O port.
' I/O Registers for HOST interface.
' I/O 00h Host status register (HSR)
' I/O 04h Host-to-DSP control register (HDCR)
' I/O 08h DSP page register (DSPP)
' I/O 0Ch Reserved
Public Declare Function AxlSetIoPort Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwAddr As Integer, ByVal dwData As Integer) As Integer
Public Declare Function AxlGetIoPort Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwAddr As Integer, ByRef dwpData As Integer) As Integer


'======= Only for PCI-R3200-MLIII ===========================================================================

' Basic information setting API for firmware update of M-III Master board.
Public Declare Function AxlM3SetFWUpdateInit Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwTotalPacketSize As Integer, ByVal dwProcTotalStepNo As Integer) As Integer
' Verify setting value of 'AxlM3SetFWUpdateInit'.
Public Declare Function AxlM3GetFWUpdateInit Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwTotalPacketSize As Integer, ByRef dwProcTotalStepNo As Integer) As Integer

' M-III Master board firmware update data transfer API.
Public Declare Function AxlM3SetFWUpdateCopy Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef pdwPacketData As Integer, ByVal dwPacketSize As Integer) As Integer
' Verify setting value of 'AxlM3SetFWUpdateCopy'.
Public Declare Function AxlM3GetFWUpdateCopy Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwPacketSize As Integer) As Integer

' Execute firmware update of M-III Master Board.
Public Declare Function AxlM3SetFWUpdate Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwFlashBurnStepNo As Integer) As Integer
' Verifying result of execute firmware update of M-III Master Board.
Public Declare Function AxlM3GetFWUpdate Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwFlashBurnStepNo As Integer, ByRef dwIsFlashBurnDone As Integer) As Integer

' The API for setting EEPROM data of M-III Master board.
Public Declare Function AxlM3SetCFGData Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef pCmdData As Integer, ByVal CmdDataSize As Integer) As Integer
' The API for getting data from EEPROM of M-III Master board.
Public Declare Function AxlM3GetCFGData Lib "AXL.dll" (ByVal lBoradNo As Integer, ByRef pCmdData As Integer, ByVal CmdDataSize As Integer) As Integer

' The API for setting CONNECT PARAMETER information of M-III Master board.
Public Declare Function AxlM3SetMCParaUpdateInit Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wCh0Slaves As Integer, ByVal wCh1Slaves As Integer, ByVal dwCh0CycTime As Integer, ByVal dwCh1CycTime As Integer, ByVal dwChInfoMaxRetry As Integer) As Integer
' The API for verifying CONNECT PARAMETER information of M-III Master board.
Public Declare Function AxlM3GetMCParaUpdateInit Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef wCh0Slaves As Integer, ByVal wCh1Slaves As Integer, ByRef dwCh0CycTime As Integer, ByRef dwCh1CycTime As Integer, ByRef dwChInfoMaxRetry As Integer) As Integer
' The API for transmit CONNECT PARAMETER information of M-III Master board.
Public Declare Function AxlM3SetMCParaUpdateCopy Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wIdx As Integer, ByVal wSlaveAddr As Integer, ByVal dwProtoCalType As Integer, ByVal dwTransBytes As Integer, ByVal dwDeviceCode As Integer) As Integer
' The API for verifying transmit CONNECT PARAMETER information of M-III Master board.
Public Declare Function AxlM3GetMCParaUpdateCopy Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wIdx As Integer, ByRef wChannel As Integer, ByRef wSlaveAddr As Integer, ByRef dwProtoCalType As Integer, ByRef dwTransBytes As Integer, ByRef dwDeviceCode As Integer) As Integer

' The API for checking register as DWord unit within M-III Master board.
Public Declare Function AxlBoardReadDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer
' The API for setting register as DWord unit within M-III Master board
Public Declare Function AxlBoardWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal dwData As Integer) As Integer

' Setting and verifying extension register as DWord unit within board.
Public Declare Function AxlBoardReadDWordEx Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwOffset As Integer, ByRef dwData As Integer) As Integer
Public Declare Function AxlBoardWriteDWordEx Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwOffset As Integer, ByVal dwData As Integer) As Integer


' The API for setting servo to stop mode.
Public Declare Function AxmM3ServoSetCtrlStopMode Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal bStopMode As Byte) As Integer
' The API for setting servo to Lt selection state.
Public Declare Function AxmM3ServoSetCtrlLtSel Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal bLtSell As Byte, ByVal bLtSel2 As Byte) As Integer
' The API for verifying servo I/O input state.
Public Declare Function AxmStatusReadServoCmdIOInput Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upStatus As Integer) As Integer
' Servo interpolation drive API.
Public Declare Function AxmM3ServoExInterpolate Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwTPOS As Integer, ByVal dwVFF As Integer, ByVal dwTFF As Integer, ByVal dwTLIM As Integer, ByVal dwExSig1 As Integer, ByVal dwExSig2 As Integer) As Integer
' The API for setting bias of the servo actuator.
Public Declare Function AxmM3ServoSetExpoAccBias Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wBias As Integer) As Integer
' The API for setting time of the servo actuator.
Public Declare Function AxmM3ServoSetExpoAccTime Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wTime As Integer) As Integer
' The API for setting time of the servo move.
Public Declare Function AxmM3ServoSetMoveAvrTime Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wTime As Integer) As Integer
' The API for setting acc filter of the servo.
Public Declare Function AxmM3ServoSetAccFilter Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal bAccFil As Byte) As Integer
' The API for setting status monitor1 of the servo.
Public Declare Function AxmM3ServoSetCprmMonitor1 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal bMonSel As Byte) As Integer
' The API for setting status monitor2 of the servo.
Public Declare Function AxmM3ServoSetCprmMonitor2 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal bMonSel As Byte) As Integer
' The API for verifying status monitor1 of the servo.
Public Declare Function AxmM3ServoStatusReadCprmMonitor1 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upStatus As Integer) As Integer
' The API for verifying status monitor2 of the servo.
Public Declare Function AxmM3ServoStatusReadCprmMonitor2 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upStatus As Integer) As Integer
' The API for setting Dec of servo actuator.
Public Declare Function AxmM3ServoSetAccDec Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wAccl As Integer, ByVal wAcc2 As Integer, ByVal wAccSW As Integer, ByVal wDec1 As Integer, ByVal wDec2 As Integer, ByVal wDecSW As Integer) As Integer
' The API for servo stop.
Public Declare Function AxmM3ServoSetStop Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal lMaxDecel As Integer) As Integer


'========== Common commands of standard I/O dvices =========================================================================
' The API for return parameter setting value of each slave device.
Public Declare Function AxlM3GetStationParameter Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal wNo As Integer, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Integer
' The API for setting parameter value of each slave device.
Public Declare Function AxlM3SetStationParameter Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal wNo As Integer, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Integer
' The API for return ID value of each slave device.
Public Declare Function AxlM3GetStationIdRd Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bIdCode As Byte, ByVal bOffset As Byte, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Integer
' The API used as invalid command of each slave device.
Public Declare Function AxlM3SetStationNop Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte) As Integer
' The API for set up each slave device.
Public Declare Function AxlM3SetStationConfig Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bConfigMode As Byte, ByVal bModuleType As Byte) As Integer
' The API for return alarm and warning status value of each slave device.
Public Declare Function AxlM3GetStationAlarm Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal wAlarmRdMod As Integer, ByVal wAlarmIndex As Integer, ByVal bModuleType As Byte, ByRef pwAlarmData As Integer) As Integer
' The API for clearing alarm and warning status value of each slave device.
Public Declare Function AxlM3SetStationAlarmClear Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal wAlarmClrMod As Integer, ByVal bModuleType As Byte) As Integer
' The API for setting establish synchronous communication with each slave device.
Public Declare Function AxlM3SetStationSyncSet Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Integer) As Integer
' The API for setting connection with each slave device.
Public Declare Function AxlM3SetStationConnect Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bVer As Byte, ByVal bComMode As Byte, ByVal bComTime As Byte, ByVal bProfileType As Byte, ByVal bModuleType As Byte) As Integer
' The API for setting disconnection with each slave device.
Public Declare Function AxlM3SetStationDisConnect Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte) As Integer
' The API for return of non-volatile parameter setting value.
Public Declare Function AxlM3GetStationStoredParameter Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal wNo As Integer, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Integer
' The API for setting non-volatile parameter value of each slave device.
Public Declare Function AxlM3SetStationStoredParameter Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal wNo As Integer, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Integer
' The API for return of memory setting value of each slave device.
Public Declare Function AxlM3GetStationMemory Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal wSize As Integer, ByVal dwAddress As Integer, ByVal bModuleType As Byte, ByVal bMode As Byte, ByVal bDataType As Byte, ByRef pbData As Byte) As Integer
' The API for setting memory value of each slave device.
Public Declare Function AxlM3SetStationMemory Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal wSize As Integer, ByVal dwAddress As Integer, ByVal bModuleType As Byte, ByVal bMode As Byte, ByVal bDataType As Byte, ByRef pbData As Byte) As Integer


'========== Connection commands of standard I/O dvices =========================================================================
' The API for setting value of automatic access mode of each re-ordered slave device.
Public Declare Function AxlM3SetStationAccessMode Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte, ByVal bRWSMode As Byte) As Integer
' The API for return of automatic access mode setting value of each re-ordered slave device.
Public Declare Function AxlM3GetStationAccessMode Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte, ByRef bRWSMode As Byte) As Integer
' The API for set synchronous auto connect mode of each slave device.
Public Declare Function AxlM3SetAutoSyncConnectMode Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte, ByVal dwAutoSyncConnectMode As Integer) As Integer
' The API for return of synchronous auto connect mode setting value of each slave device.
Public Declare Function AxlM3GetAutoSyncConnectMode Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte, ByRef dwpAutoSyncConnectMode As Integer) As Integer
' The API for establish a single synchronization connection to each slave device.
Public Declare Function AxlM3SyncConnectSingle Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte) As Integer
' The API for establish a single synchronization disconnection to each slave device.
Public Declare Function AxlM3SyncDisconnectSingle Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte) As Integer
' The API for verifying connection status with slave device.
Public Declare Function AxlM3IsOnLine Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByRef dwData As Integer) As Integer


'========== Profile commands of standard I/O =========================================================================
' The API for return of data setting value for each synchronous I/O slave device.
Public Declare Function AxlM3GetStationRWS Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte, ByRef pdwParam As Integer, ByVal bSize As Byte) As Integer
' The API for setting data value for each synchronous I/O slave device.
Public Declare Function AxlM3SetStationRWS Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte, ByRef pdwParam As Integer, ByVal bSize As Byte) As Integer
' The API for return of data setting value for each asynchronous I/O slave device.
Public Declare Function AxlM3GetStationRWA Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte, ByRef pdwParam As Integer, ByVal bSize As Byte) As Integer
' The API for setting data value for each asynchronous I/O slave device.
Public Declare Function AxlM3SetStationRWA Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModuleNo As Integer, ByVal bModuleType As Byte, ByRef pdwParam As Integer, ByVal bSize As Byte) As Integer


' Set the MLIII adjustment operation
' dwReqCode == 0x1005 : parameter initialization : 20sec
' dwReqCode == 0x1008 : absolute encoder reset   : 5sec
' dwReqCode == 0x100E : automatic offset adjustment of motor current detection signals  : 5sec
' dwReqCode == 0x1013 : Multiturn limit setting  : 5sec
Public Declare Function AxmM3AdjustmentOperation Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwReqCode As Integer) As Integer


' API for diagnosing home search progress.(Only for M3)
Public Declare Function AxmHomeGetM3FWRealRate Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upHomeMainStepNumber As Integer, ByRef upHomeSubStepNumber As Integer, ByRef upHomeLastMainStepNumber As Integer, ByRef upHomeLastSubStepNumber As Integer) As Integer
' Return adjusted position value when escaping sensor zone from origin search.(Only for M3)
Public Declare Function AxmHomeGetM3OffsetAvoideSenArea Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dPos As Double) As Integer
' The API for Setting adjusted position value when escaping sensor zone from origin search.(Only for M3)
' If dPos setting value is '0', adjusted position value will be set automatically when automatically escaping.
' 'dPos' should be a positive number.
Public Declare Function AxmHomeSetM3OffsetAvoideSenArea Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double) As Integer


' Setting usage criterion of absolute encoder. Set whether to CMD/ACT POS initialize after origin search.(Only for M3)
' dwSel: 0, CMD/ACTPOS will be set '0' after origin search.(Default)
' dwSel: 1, CMD/ACTPOS will be not set after origin search.
Public Declare Function AxmM3SetAbsEncOrgResetDisable Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwSel As Integer) As Integer

' Get 'AxmM3SetAbsEncOrgResetDisable' setting value.(Only for M3)
' upSel: 0, CMD / ACTPOS set to 0 after home search. (Default)
' upSel: 1, CMD / ACTPOS value is not set after home search.
Public Declare Function AxmM3GetAbsEncOrgResetDisable Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upSel As Integer) As Integer


' Setting whether using alarm maintenance function when switch to slave offline mode.(Only for M3)
' dwSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
' dwSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
Public Declare Function AxmM3SetOfflineAlarmEnable Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwSel As Integer) As Integer

' Get 'AxmM3SetOfflineAlarmEnable' setting value.(Only for M3)
' upSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
' upSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
Public Declare Function AxmM3GetOfflineAlarmEnable Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upSel As Integer) As Integer

' Read value of slave online or offline status. (Only for M3)
' upSel: 0, ONLINE->OFFLINE Not converted
' upSel: 1, ONLINE->OFFLINE converted
Public Declare Function AxmM3ReadOnlineToOfflineStatus Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upStatus As Integer) As Integer

    Public Declare Function AxlSetLockMode Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wLockMode As Integer) As Integer
    Public Declare Function AxlSetLockData Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwTotalNodeNum As Integer, ByRef dwpNodeNo As Integer, ByRef dwpNodeID As Integer, ByRef dwpLockData As Integer) As Integer
    Public Declare Function AxmMoveStartPosWithAVC Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPosition As Double, ByVal dMaxVelocity As Double, ByVal dMaxAccel As Double, ByVal dMinJerk As Double, ByRef dpMoveVelocity As Double, ByRef dpMoveAccel As Double, ByRef dpMoveJerk As Double) As Integer

'======== API for EtherCAT only =============================================================================
' The API for read VendorID, ProductCode and RevisionNo of EtherCat slave product by using StationAddress.
Public Declare Function AxlECatGetProductInfo Lib "AXL.dll" (ByVal dwStationAddress As Integer, ByRef pdwVendorID As Integer, ByRef pdwProductCode As Integer, ByRef pdwRevisionNo As Integer) As Integer
    Public Declare Function AxlECatGetProductInfoEx Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwStationAddress As Integer, ByRef pdwVendorID As Integer, ByRef pdwProductCode As Integer, ByRef pdwRevisionNo As Integer) As Integer

' The API for verifying network status of EtherCAT slave product by using StationAddress.
Public Declare Function AxlECatGetModuleStatus Lib "AXL.dll" (ByVal dwStationAddress As Integer) As Integer


' Read input PDO(Process Data Objects)
' dwBitOffset     : ProcessImage inputs bit offset value.
' dwDataBitLength : bit size of input pdo data.
' pbyData         : The Buffer for inserting read data.
Public Declare Function AxlECatReadPdoInput Lib "AXL.dll" (ByVal dwBitOffset As Integer, ByVal dwDataBitLength As Integer, ByRef pbyData As Byte) As Integer
    Public Declare Function AxlECatReadPdoInputEx Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwBitOffset As Integer, ByVal dwDataBitLength As Integer, ByRef pbyData As Byte) As Integer


' Read output PDO(Process Data Objects)
' dwBitOffset     : ProcessImage outputs bit offset value.
' dwDataBitLength : bit size of input pdo data.(for read)
' pbyData         : The Buffer for inserting read data.
Public Declare Function AxlECatReadPdoOutput Lib "AXL.dll" (ByVal dwBitOffset As Integer, ByVal dwDataBitLength As Integer, ByRef pbyData As Byte) As Integer
    Public Declare Function AxlECatReadPdoOutputEx Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwBitOffset As Integer, ByVal dwDataBitLength As Integer, ByRef pbyData As Byte) As Integer

' Write value to output process data.
' dwBitOffset     : ProcessImage outputs bit offset value.
' dwDataBitLength : bit size of output pdo data.(for write)
' pbyData         : The Buffer for inserting write data.
Public Declare Function AxlECatWritePdoOutput Lib "AXL.dll" (ByVal dwBitOffset As Integer, ByVal dwDataBitLength As Integer, ByRef pbyData As Byte) As Integer


' Read SDO(Service Data Objects) by using COE.
Public Declare Function AxlECatReadSdo Lib "AXL.dll" (ByVal dwStationAddress As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte, ByVal dwDataLength As Integer, ByRef pdwReadDataLength As Integer) As Integer
    Public Declare Function AxlECatReadSdoEx Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwStationAddress As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte, ByVal dwDataLength As Integer, ByRef pdwReadDataLength As Integer) As Integer

' Store values in SDO by using COE.
Public Declare Function AxlECatWriteSdo Lib "AXL.dll" (ByVal dwStationAddress As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte, ByVal dwDataLength As Integer) As Integer
    Public Declare Function AxlECatWriteSdoEx Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwStationAddress As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte, ByVal dwDataLength As Integer) As Integer

    Public Declare Function AxlECatReadSdoFromAxisDouble Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pdData As Double) As Integer

    Public Declare Function AxlECatWriteSdoFromAxisDouble Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pdData As Double) As Integer
' Read SDO(DWORD type) through the axis number.
Public Declare Function AxlECatReadSdoFromAxisDword Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pdwData As Integer) As Integer

' Store values in SDO(DWORD type) through the axis number.
Public Declare Function AxlECatWriteSdoFromAxisDword Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pdwData As Integer) As Integer

' Read SDO(WORD type) through the axis number.
Public Declare Function AxlECatReadSdoFromAxisWord Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pwData As Integer) As Integer

' Store values in SDO(WORD type) through the axis number.
Public Declare Function AxlECatWriteSdoFromAxisWord Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pwData As Integer) As Integer

' Read SDO(BYTE type) through the axis number.
Public Declare Function AxlECatReadSdoFromAxisByte Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte) As Integer

' Store values in SDO(BYTE type) through the axis number.
Public Declare Function AxlECatWriteSdoFromAxisByte Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte) As Integer

' Read value of EEPROM.
Public Declare Function AxlECatReadEEPRom Lib "AXL.dll" (ByVal dwStationAddress As Integer, ByVal wEEPRomStartOffset As Integer, ByRef pwData As Integer, ByVal dwDataLength As Integer) As Integer

' Write value to EEPROM.
Public Declare Function AxlECatWriteEEPRom Lib "AXL.dll" (ByVal dwStationAddress As Integer, ByVal wEEPRomStartOffset As Integer, ByRef pwData As Integer, ByVal dwDataLength As Integer) As Integer
    Public Declare Function AxlECatReadEEPRomEx Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwStationAddress As Integer, ByVal wEEPRomStartOffset As Integer, ByRef pwData As Integer, ByVal dwDataLength As Integer) As Integer

    Public Declare Function AxlECatWriteEEPRomEx Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwStationAddress As Integer, ByVal wEEPRomStartOffset As Integer, ByRef pwData As Integer, ByVal dwDataLength As Integer) As Integer

' Read value of a register.
Public Declare Function AxlECatReadRegister Lib "AXL.dll" (ByVal dwStationAddress As Integer, ByVal wRegisterOffset As Integer, ByRef pvData As Object, ByVal wLen As Integer) As Integer

' Write value of a register.
Public Declare Function AxlECatWriteRegister Lib "AXL.dll" (ByVal dwStationAddress As Integer, ByVal wRegisterOffset As Integer, ByRef pvData As Object, ByVal wLen As Integer) As Integer

' Save BackupData as a file from among the object dictionary of EtherCat slave.
Public Declare Function AxlECatSaveHotSwapData Lib "AXL.dll" (ByVal dwStationAddress As Integer) As Integer

' Load BackupData which saved as a file from corresponding EtherCat salve.
Public Declare Function AxlECatLoadHotSwapData Lib "AXL.dll" (ByVal dwStationAddress As Integer) As Integer

' When using the HotSwapStart API(Function to advance HotSwap only for registered StationAddresses),
'       it stores the StationAddress in HotSwapConfig, confirms existence and deletes it.
Public Declare Function AxlECatSetHotSwap Lib "AXL.dll" (ByVal dwStationAddress As Integer) As Integer
Public Declare Function AxlECatIsSetHotSwap Lib "AXL.dll" (ByVal dwStationAddress As Integer) As Integer
Public Declare Function AxlECatReSetHotSwap Lib "AXL.dll" (ByVal dwStationAddress As Integer) As Integer


' Set EtherCat master mode (configure = 0, RumMode = 1)
Public Declare Function AxlECatSetMasterMode Lib "AXL.dll" (ByVal dwMasterMode As Integer) As Integer

' Get mode status of EtherCat master.
Public Declare Function AxlECatGetMasterMode Lib "AXL.dll" (ByRef pdwMasterMode As Integer) As Integer


' Set MasterOperationMode of EtherCat master.
Public Declare Function AxlECatSetMasterOperationMode Lib "AXL.dll" (ByVal dwOperationMode As Integer) As Integer


' Get MasterOperationMode of EtherCat master.
Public Declare Function AxlECatGetMasterOperationMode Lib "AXL.dll" (ByRef pdwOperationMode As Integer) As Integer

' Requesting scan command to EtherCat master, and then command to save scaned data to SHM.
Public Declare Function AxlECatRequestScanData Lib "AXL.dll" () As Integer



' Get total number of scanned slaves.
Public Declare Function AxlECatGetScanSlaveCount Lib "AXL.dll" (ByRef pdwSlaveCount As Integer) As Integer


' Get current status information of EtherCat master.
Public Declare Function AxlECatGetStatus Lib "AXL.dll" (ByRef pnECMasterStatus As Integer, ByRef pnECSlaveStatus As Integer, ByRef pnECConnectedSlave As Integer, ByRef pnECConfiguredSlave As Integer, ByRef pnJobTaskCycleCnt As Integer, ByRef pdwECMasterNotification As Integer) As Integer


' Reconnecting failed network.
Public Declare Function AxlEcatReConnect Lib "AXL.dll" () As Integer


' Get address information of slave which be set.
Public Declare Function AxmECatReadAddress Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpStationAddress As Integer, ByRef lpAutoIncAddress As Integer, ByRef dwpAliasAddress As Integer) As Integer
Public Declare Function AxdECatReadAddress Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dwpStationAddress As Integer, ByRef lpAutoIncAddress As Integer, ByRef dwpAliasAddress As Integer) As Integer
Public Declare Function AxaECatReadAddress Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dwpStationAddress As Integer, ByRef lpAutoIncAddress As Integer, ByRef dwpAliasAddress As Integer) As Integer
Public Declare Function AxsECatReadAddress Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dwpStationAddress As Integer, ByRef lpAutoIncAddress As Integer, ByRef dwpAliasAddress As Integer) As Integer


' Monitor
' Add an item to proceed with data collection.
Public Declare Function AxlMonitorSetItem Lib "AXL.dll" (ByVal lItemIndex As Integer, ByVal dwSignalType As Integer, ByVal lSignalNo As Integer, ByVal lSubSignalNo As Integer) As Integer


' Get information about items to be collected.
Public Declare Function AxlMonitorGetIndexInfo Lib "AXL.dll" (ByRef lpItemSize As Integer, ByRef lpItemIndex As Integer) As Integer


' Get detailed settings of each items for data collection progress.
Public Declare Function AxlMonitorGetItemInfo Lib "AXL.dll" (ByVal lItemIndex As Integer, ByRef dwpSignalType As Integer, ByRef lSignalNo As Integer, ByRef lpSubSignalNo As Integer) As Integer


' Reset settings of all data collection items.
Public Declare Function AxlMonitorResetAllItem Lib "AXL.dll" () As Integer


' Reset settings of selected data collection items.
Public Declare Function AxlMonitorResetItem Lib "AXL.dll" (ByVal lItemIndex As Integer) As Integer


' Set the trigger condition of data collection.
Public Declare Function AxlMonitorSetTriggerOption Lib "AXL.dll" (ByVal dwSignalType As Integer, ByVal lSignalNo As Integer, ByVal lSubSignalNo As Integer, ByVal dwOperatorType As Integer, ByVal dValue1 As Double, ByVal dValue2 As Double) As Integer



' Get the trigger condition of data collection.
' DWORD  __stdcall AxlMonitorGetTriggerOption(DWORD* dwpSignalType, long* lpSignalNo, long* lpSubSignalNo, DWORD* dwpOperatorType, double* dpValue1, double* dpValue2);

' Reset trigger condition of data collection.
Public Declare Function AxlMonitorResetTriggerOption Lib "AXL.dll" () As Integer


' Start collecting data.
Public Declare Function AxlMonitorStart Lib "AXL.dll" (ByVal dwStartOption As Integer, ByVal dwOverflowOption As Integer) As Integer


' Stop collecting data.
Public Declare Function AxlMonitorStop Lib "AXL.dll" () As Integer


' Gets collected data.
Public Declare Function AxlMonitorReadData Lib "AXL.dll" (ByRef lpItemSize As Integer, ByRef lpDataCount As Integer, ByRef dpReadData As Double) As Integer


' Gets the period of data collection.
Public Declare Function AxlMonitorReadPeriod Lib "AXL.dll" (ByRef dwpPeriod As Integer) As Integer


' MonitorEX
' Add an item to proceed with data collection.
Public Declare Function AxlMonitorExSetItem Lib "AXL.dll" (ByVal lItemIndex As Integer, ByVal dwSignalType As Integer, ByVal lSignalNo As Integer, ByVal lSubSignalNo As Integer) As Integer


' Gets information about the items to be collected.
Public Declare Function AxlMonitorExGetIndexInfo Lib "AXL.dll" (ByRef lpItemSize As Integer, ByRef lpItemIndex As Integer) As Integer


' Gets the detailed settings for each item to proceed with data collection.
Public Declare Function AxlMonitorExGetItemInfo Lib "AXL.dll" (ByVal lItemIndex As Integer, ByRef dwpSignalType As Integer, ByRef lpSignalNo As Integer, ByRef lpSubSignalNo As Integer) As Integer


' Reset settings of all data collection items.
Public Declare Function AxlMonitorExResetAllItem Lib "AXL.dll" () As Integer


' Reset settings of selected data collection items.
Public Declare Function AxlMonitorExResetItem Lib "AXL.dll" (ByVal lItemIndex As Integer) As Integer


' Set the trigger condition of data collection.
Public Declare Function AxlMonitorExSetTriggerOption Lib "AXL.dll" (ByVal dwSignalType As Integer, ByVal lSignalNo As Integer, ByVal lSubSignalNo As Integer, ByVal dwOperatorType As Integer, ByVal dValue1 As Double, ByVal dValue2 As Double) As Integer



' Get the trigger condition of data collection.
' DWORD  __stdcall AxlMonitorGetTriggerOption(DWORD* dwpSignalType, long* lpSignalNo, long* lpSubSignalNo, DWORD* dwpOperatorType, double* dpValue1, double* dpValue2);

' Reset trigger condition of data collection.
Public Declare Function AxlMonitorExResetTriggerOption Lib "AXL.dll" () As Integer


' Start collecting data.
Public Declare Function AxlMonitorExStart Lib "AXL.dll" (ByVal dwStartOption As Integer, ByVal dwOverflowOption As Integer) As Integer


' Stop collecting data.
Public Declare Function AxlMonitorExStop Lib "AXL.dll" () As Integer


' Gets collected data.
Public Declare Function AxlMonitorExReadData Lib "AXL.dll" (ByRef lpItemSize As Integer, ByRef lpDataCount As Integer, ByRef dpReadData As Double) As Integer


' Gets the period of data collection.
Public Declare Function AxlMonitorExReadPeriod Lib "AXL.dll" (ByRef dwpPeriod As Integer) As Integer



' Linear interpolation about 2 axis including information of offset position for X2, Y2 axis.
Public Declare Function AxmLineMoveDual01 Lib "AXL.dll" (ByVal lCoordNo As Integer, ByRef dpEndPosition As Double, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dOffsetLength As Double, ByVal dTotalLength As Double, ByRef dpStartOffsetPosition As Double, ByRef dpEndOffsetPosition As Double) As Integer
' Arc interpolation about 2 axis including information of offset position for X2, Y2 axis.
Public Declare Function AxmCircleCenterMoveDual01 Lib "AXL.dll" (ByVal lCoordNo As Integer, ByRef lpAxes As Integer, ByRef dpCenterPosition As Double, ByRef dpEndPosition As Double, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dwCWDir As Integer, ByVal dOffsetLength As Double, ByVal dTotalLength As Double, ByRef dpStartOffsetPosition As Double, ByRef dpEndOffsetPosition As Double) As Integer

' About ECAT Foe
Public Declare Function AxdSetFirmwareUpdateInfo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwTotalDataSize As Integer, ByVal dwTotalPacketSize As Integer) As Integer
Public Declare Function AxdSetFirmwareDataTrans Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwPacketIndex As Integer, ByRef dwaPacketData As Integer) As Integer
Public Declare Function AxdSetFirmwareUpdate Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef szFileName As Byte, ByVal dwFileNameLen As Integer, ByVal dwPassWord As Integer) As Integer


Public Declare Function AxaSetFirmwareUpdateInfo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwTotalDataSize As Integer, ByVal dwTotalPacketSize As Integer) As Integer
Public Declare Function AxaSetFirmwareDataTrans Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwPacketIndex As Integer, ByRef dwaPacketData As Integer) As Integer
Public Declare Function AxaSetFirmwareUpdate Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef szFileName As Byte, ByVal dwFileNameLen As Integer, ByVal dwPassWord As Integer) As Integer


Public Declare Function AxmSetFirmwareUpdateInfo Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwTotalDataSize As Integer, ByVal dwTotalPacketSize As Integer) As Integer
Public Declare Function AxmSetFirmwareDataTrans Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwPacketIndex As Integer, ByRef dwaPacketData As Integer) As Integer
Public Declare Function AxmSetFirmwareUpdate Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef szFileName As Byte, ByVal dwFileNameLen As Integer, ByVal dwPassWord As Integer) As Integer
    Public Declare Function AxmSetFoeUploadInfo Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwTotalDataSize As Integer, ByVal dwTotalPacketSize As Integer) As Integer
    Public Declare Function AxmGetFoeUploadData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwPacketIndex As Integer, ByRef dwaPacketData As Integer) As Integer
    Public Declare Function AxmSetFoeUpload Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef szFileName As char*, ByVal dwFileNameLen As Integer, ByVal dwPassWord As Integer) As Integer


Public Declare Function AxmMotSetOperationMode Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwOperationMode As Integer) As Integer
Public Declare Function AxmMotGetOperationMode Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef pdwOperationMode As Integer) As Integer



    Public Declare Function AxcTriggerSetPatternData Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal nDataCnt As Integer, ByVal dwOption As Integer, ByRef dpPatternData As Double) As Integer
    Public Declare Function AxcTriggerGetPatternData Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef npDataCnt As Integer, ByRef dwpOption As Integer, ByRef dpPatternData As Double) As Integer

    Public Declare Function AxmSpiralMoveEx Lib "AXL.dll" (ByVal lCoordNo As Integer, ByVal dSpiralPitch As Double, ByVal dTurningCount As Double, ByVal dAngleOfPose As Double, ByVal dwIsInnerDirection As Integer, ByVal dVelocity As Double, ByVal dAcceleration As Double, ByVal dDeceleration As Double) As Integer
    Public Declare Function AxmFilletMove Lib "AXL.dll" (ByVal lCoordinate As Integer, ByRef dPosition As Double, ByRef dFirstVector As Double, ByRef dSecondVector As Double, ByVal dMaxVelocity As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double, ByVal dRadius As Double) As Integer

    Public Declare Function AxmSignalIsServoOnSingleAxis Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upOnOff As Integer) As Integer

    Public Declare Function AxmMotSetTorqueConnection Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal lSourceAxisNo As Integer, ByVal dwEnable As Integer) As Integer
    Public Declare Function AxmMotGetTorqueConnection Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef plSourceAxisNo As Integer, ByRef pdwEnable As Integer) As Integer


End Module
