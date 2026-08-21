
Attribute VB_Name = "AXDev"



' Use Board Number and find Board Address
Public Declare Function AxlGetBoardAddress Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardAddress As Long) As Long
' Use Board Number and find Board ID
Public Declare Function AxlGetBoardID Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardID As Long) As Long
' Use Board Number and find Board Version
Public Declare Function AxlGetBoardVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardVersion As Long) As Long
' Use Board Number/Module Position and find Module ID
Public Declare Function AxlGetModuleID Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upModuleID As Long) As Long
' Use Board Number/Module Position and find Module Version
Public Declare Function AxlGetModuleVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upModuleVersion As Long) As Long

Public Declare Function AxlGetModuleNodeInfo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upNetNo As Long, ByRef upNodeAddr As Long) As Long


' Only for PCI-R1604[RTEX]
' Writing user data to embedded flash memory
' lPageAddr(0 ~ 199)
' lByteNum(1 ~ 120)
' Note) Delay time is required for completing writing operation to Flash(Max. 17mSec)
Public Declare Function AxlSetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lPageAddr As Long, ByVal lBytesNum As Long, ByRef bpSetData As Byte) As Long


'ML3 Only, Use Board and Set the EStopInterLock Parameter
' dwInterLock    : (0) Not use(Default value)
'                  (1) Using function. When E-STOP signal is externally applied after setting function, E-STOP drive command is executed to the motion control node connected to the board.
' dwDigFilterVal : Setting range of input filter constant (1~40). Unit communication Cyclic time
' Set EstopInterLock function by using dwInterLock and dwDigFilterVal on Board
Public Declare Function AxlSetEStopInterLock Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwInterLock As Long, ByVal dwDigFilterVal As Long) As Long
' ML3 Only, Use Board and Get the EStopInterLock Parameter
Public Declare Function AxlGetEStopInterLock Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwInterLock As Long, ByRef dwDigFilterVal As Long) As Long
' ML3 Only, Read the External ESTOP Signal status
Public Declare Function AxlReadEStopInterLock Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwInterLock As Long) As Long


' Reading datas from embedded flash memory
' lPageAddr(0 ~ 199)
' lByteNum(1 ~ 120)
Public Declare Function AxlGetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lPageAddr As Long, ByVal lBytesNum As Long, ByRef bpGetData As Byte) As Long

' Use Board Number/Module Position and find AIO Module Number
Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long
' Use Board Number/Module Position and find DIO Module Number
Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long


' IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommand Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte) As Long
' 8bit IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 8bit IPCOMMAND at an appoint axis
Public Declare Function AxmGetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 16bit IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 16bit IPCOMMAND at an appoint axis
Public Declare Function AxmGetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 24bit IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 24bit IPCOMMAND at an appoint axis
Public Declare Function AxmGetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 32bit IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 32bit IPCOMMAND at an appoint axis
Public Declare Function AxmGetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long


' QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte) As Long
' 8bit QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 8bit QICOMMAND at an appoint axis
Public Declare Function AxmGetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 16bit QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 16bit QICOMMAND at an appoint axis
Public Declare Function AxmGetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 24bit QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 24bit QICOMMAND at an appoint axis
Public Declare Function AxmGetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 32bit QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 32bit QICOMMAND at an appoint axis
Public Declare Function AxmGetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long


' Get Port Data at an appoint axis - IP
Public Declare Function AxmGetPortData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef upData As Long) As Long
' Port Data Setting at an appoint axis - IP
Public Declare Function AxmSetPortData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long
' Get Port Data at an appoint axis - QI
Public Declare Function AxmGetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef upData As Long) As Long
' Port Data Setting at an appoint axis - QI
Public Declare Function AxmSetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long

' Set the script at an appoint axis.  - IP
' sc    : Script number (1 - 4)
' event : Define an event SCRCON to happen.
'         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
' cmd   : Define a selection SCRCMD however we change any content
' data  : Selection to change any Data.
Public Declare Function AxmSetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByVal event1 As Long, ByVal data As Long) As Long
' Return the script at an appoint axis.  - IP
Public Declare Function AxmGetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByRef event1 As Long, ByRef data As Long) As Long

' Set the script at an appoint axis.  - QI
' sc    : Script number (1 - 4)
' event : Define an event SCRCON to happen.
'         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
' cmd   : Define a selection SCRCMD however we change any content
' data  : Selection to change any Data.
Public Declare Function AxmSetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByVal event1 As Long, ByVal cmd As Long, ByVal data As Long) As Long
' Return the script at an appoint axis. - QI
Public Declare Function AxmGetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByRef event1 As Long, ByRef cmd As Long, ByRef data As Long) As Long

' Clear orders a script inside Queue Index at an appoint axis
' uSelect IP.
' uSelect(0): Script Queue Index Clear.
'        (1): Caption Queue Index Clear.
' uSelect QI.
' uSelect(0): Script Queue 1 Index Clear.
'        (1): Script Queue 2 Index Clear.
Public Declare Function AxmSetScriptCaptionQueueClear Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelect As Long) As Long

' Return Index of a script inside Queue at an appoint axis.
' uSelect IP
' uSelect(0): Read Script Queue Index
'       (1): Read Caption Queue Index
' uSelect QI.
' uSelect(0): Read Script Queue 1 Index
'       (1): Read Script Queue 2 Index
Public Declare Function AxmGetScriptCaptionQueueCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long, ByVal uSelect As Long) As Long

' Return Data number of a script inside Queue at an appoint axis.
' uSelect IP
' uSelect(0): Read Script Queue Data
'       (1): Read Caption Queue Data
' uSelect QI.
' uSelect(0): Read Script Queue 1 Data
'        (1): Read Script Queue 2 Data
Public Declare Function AxmGetScriptCaptionQueueDataCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long, ByVal uSelect As Long) As Long

' Read an inside data.
Public Declare Function AxmGetOptimizeDriveData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dMinVel As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByRef wRangeData As Long, ByRef wStartStopSpeedData As Long, ByRef wObjectSpeedData As Long, ByRef wAccelRate As Long, ByRef wDecelRate As Long) As Long



' Setting up confirmes the register besides within the board by Byte.
Public Declare Function AxmBoardWriteByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal byData As Byte) As Long
Public Declare Function AxmBoardReadByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef byData As Byte) As Long

' Setting up confirmes the register besides within the board by Word.
Public Declare Function AxmBoardWriteWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal wData As Long) As Long
Public Declare Function AxmBoardReadWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef wData As Long) As Long

' Setting up confirmes the register besides within the board by DWord.
Public Declare Function AxmBoardWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal dwData As Long) As Long
Public Declare Function AxmBoardReadDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long


' Setting up confirmes the register besides within the Module by Byte.
Public Declare Function AxmModuleWriteByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal byData As Byte) As Long
Public Declare Function AxmModuleReadByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef byData As Byte) As Long


' Setting up confirmes the register besides within the Module by Word.
Public Declare Function AxmModuleWriteWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal wData As Long) As Long
Public Declare Function AxmModuleReadWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef wData As Long) As Long


' Setting up confirmes the register besides within the Module by DWord.
Public Declare Function AxmModuleWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal dwData As Long) As Long
Public Declare Function AxmModuleReadDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long


' Set EXCNT (Pos = Unit)
Public Declare Function AxmStatusSetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' Return EXCNT (Positon = Unit)
Public Declare Function AxmStatusGetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long

' Set INCNT (Pos = Unit)
Public Declare Function AxmStatusSetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' Return INCNT (Pos = Unit)
Public Declare Function AxmStatusGetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long


'=========== Append function. =========================================================================================================
' 	Increase a straight line interpolation at speed to the infinity.
' 	Must put the distance speed rate.
Public Declare Function AxmLineMoveVel Lib "AXL.dll" (ByVal lCoord As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

'========= Sensor drive API( Read carefully: Available only PI , No function in QI) =========================================================================
'	 Set mark signal( used in sensor positioning drive)
Public Declare Function AxmSensorSetSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
'	 Verify mark signal( used in sensor positioning drive)
Public Declare Function AxmSensorGetSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long
'	Verify mark signal( used in sensor positioning drive)state
Public Declare Function AxmSensorReadSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

' Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop.
' Applied motion is started upon the start of API, and escapes from the API after the motion is completed.
Public Declare Function AxmSensorMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Long) As Long

' Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop.
' Applied motion is started upon the start of API, then escapes from the API immediately without waiting until the motion is completed.
Public Declare Function AxmSensorStartMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Long) As Long


' Return record of origin search progress step.
' *lpStepCount      : Number of step(Be recorded)
' *upMainStepNumber : Array point of 'MainStepNumber ' information(Be recorded)
' *upStepNumber     : Array point of 'StepNumber ' information(Be recorded)
' *upStepBranch     : Array point of branch information by step(Be recorded)
'  Caution : Number of array should be fixed 50.
Public Declare Function AxmHomeGetStepTrace Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpStepCount As Long, ByRef upMainStepNumber As Long, ByRef upStepNumber As Long, ByRef upStepBranch As Long) As Long

'======= Additive home search (Applicable to PI-N804/404  only) =================================================================================

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
Public Declare Function AxmHomeSetConfig Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uZphasCount As Long, ByVal lHomeMode As Long, ByVal lClearSet As Long, ByVal dOrgVel As Double, ByVal dLastVel As Double, ByVal dLeavePos As Double) As Long
' Return home setting parameters of axis specified by user.
Public Declare Function AxmHomeGetConfig Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upZphasCount As Long, ByRef lpHomeMode As Long, ByRef lpClearSet As Long, ByRef dpOrgVel As Double, ByRef dpLastVel As Double, ByRef dpLeavePos As Double) As Long

' Start home search of axis specified by user
' Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
' If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
' Move direction      : CW when Vel value is positive, CCW when negative.
Public Declare Function AxmHomeSetMoveSearch Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' Start home return of axis specified by user.
' Set when lHomeMode is used: set 0 - 12
' If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
' Move direction      : CW when Vel value is positive, CCW when negative.
Public Declare Function AxmHomeSetMoveReturn Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

'Home separation of axis specified by user is started.
'Move direction      : CW when Vel value is positive, CCW when negative.
Public Declare Function AxmHomeSetMoveLeave Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' User start home search of multi-axis specified by user.
' Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
' If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
' Move direction      : CW when Vel value is positive, CCW when negative.
Public Declare Function AxmHomeSetMultiMoveSearch Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Long


' Set move velocity profile mode of specific coordinate system.
'  (caution : Available to use only after axis mapping)
' ProfileMode : '0' - symmetry Trapezoid
'               '1' - asymmetric Trapezoid
'               '2' - symmetry Quasi-S Curve
'               '3' - symmetry S Curve
'               '4' - asymmetric S Curve
Public Declare Function AxmContiSetProfileMode Lib "AXL.dll" (ByVal lCoord As Long, ByVal uProfileMode As Long) As Long
' Return move velocity profile mode of specific coordinate system.
Public Declare Function AxmContiGetProfileMode Lib "AXL.dll" (ByVal lCoord As Long, ByRef upProfileMode As Long) As Long

' ========== Reading group for input interrupt occurrence flag
'  Reading the interrupt occurrence state by bit unit in specified input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagReadBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' Reading the interrupt occurrence state by byte unit in specified input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagReadByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' Reading the interrupt occurrence state by word unit in specified input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagReadWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' Reading the interrupt occurrence state by double word unit in specified input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagReadDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
' Reading the interrupt occurrence state by bit unit in entire input contact module and Offset position of Interrupt Flag Register
Public Declare Function AxdiInterruptFlagRead Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long


' ========= API related log ==========================================================================================
' This API sets or resets in order to monitor the API execution result of set axis in EzSpy.
' uUse : use or not use => DISABLE(0), ENABLE(1)
Public Declare Function AxmLogSetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long


' This API verifies if the API execution result of set axis is monitored in EzSpy.
Public Declare Function AxmLogGetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long

'==Log

' Set whether to log output to EzSpy of specified input channel
Public Declare Function AxaiLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long
' Verify whether to log output to EzSpy of specified input channel
Public Declare Function AxaiLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long


' Set whether to log output in EzSpy of specified output channel
Public Declare Function AxaoLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long
' Verify whether log output is done in EzSpy of specified output channel.
Public Declare Function AxaoLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long

' Set whether execute log output on EzSpy of specified module
Public Declare Function AxdLogSetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uUse As Long) As Long
' Verify whether execute log output on EzSpy of specified module
Public Declare Function AxdLogGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upUse As Long) As Long

' Verify whether to firmware version designated RTEX board.
Public Declare Function AxlGetFirmwareVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal szVersion As String) As Long
' Sent to firmware designated board.
Public Declare Function AxlSetFirmwareCopy Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef wData As Long, ByRef wCmdData As Long) As Long
'Execute Firmware update to designated board.
Public Declare Function AxlSetFirmwareUpdate Lib "AXL.dll" (ByVal lBoardNo As Long) As Long
' Verify whether currently RTEX status Initialized.
Public Declare Function AxlCheckStatus Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwStatus As Long) As Long
' Execute universal command designated axis of board.
Public Declare Function AxlRtexUniversalCmd Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wCmd As Long, ByVal wOffset As Long, ByRef wData As Long) As Long
' Execute RTEX communication command designated axis.
Public Declare Function AxmRtexSlaveCmd Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwCmdCode As Long, ByVal dwTypeCode As Long, ByVal dwIndexCode As Long, ByVal dwCmdConfigure As Long, ByVal dwValue As Long) As Long
' Verify whether Result of RTEX communication command designated axis.
Public Declare Function AxmRtexGetSlaveCmdResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwIndex As Long, ByRef dwValue As Long) As Long
' Check the result of the RTEX communication command executed on the specified axis. PCIE-Rxx04-RTEX only
Public Declare Function AxmRtexGetSlaveCmdResultEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpCommand As Long, ByRef dwpType As Long, ByRef dwpIndex As Long, ByRef dwpValue As Long) As Long
' Verify whether RTEX status information designated axis.
Public Declare Function AxmRtexGetAxisStatus Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwStatus As Long) As Long
' Verify whether RTEX communication return information designated axis.(Actual position, Velocity, Torque)
Public Declare Function AxmRtexGetAxisReturnData Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwReturn1 As Long, ByRef dwReturn2 As Long, ByRef dwReturn3 As Long) As Long
' Verify whether currently status information of RTEX slave axis.(mechanical, Inposition and etc)
Public Declare Function AxmRtexGetAxisSlaveStatus Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwStatus As Long) As Long

' Enter the universal network command of specified MLII slave axis.
Public Declare Function AxmSetAxisCmd Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef tagCommand As Long) As Long
' Verifying result of universal network command of specified MLII slave axis.
Public Declare Function AxmGetAxisCmdResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef tagCommand As Long) As Long


' The specified SID Write the result of the network command to the slave module and return it.
Public Declare Function AxdSetAndGetSlaveCmdResult Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef tagSetCommand As Long, ByRef tagGetCommand As Long) As Long
Public Declare Function AxaSetAndGetSlaveCmdResult Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef tagSetCommand As Long, ByRef tagGetCommand As Long) As Long
Public Declare Function AxcSetAndGetSlaveCmdResult Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef tagSetCommand As Long, ByRef tagGetCommand As Long) As Long

' Verify DPRAM data.
Public Declare Function AxlGetDpRamData Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wAddress As Long, ByRef dwpRdData As Long) As Long
' Verify DPRAM data in Word unit.
Public Declare Function AxlBoardReadDpramWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef dwpRdData As Long) As Long
' Set DPRAM data in Word unit.
Public Declare Function AxlBoardWriteDpramWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Integer, ByVal dwWrData As Long) As Long

' Transmit instructions of each slave of each board.
Public Declare Function AxlSetSendBoardEachCommand Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwCommand As Long, ByRef dwpSendData As Long, ByVal dwLength As Long) As Long
' Transmit instructions to each board.
Public Declare Function AxlSetSendBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwCommand As Long, ByRef dwpSendData As Long, ByVal dwLength As Long) As Long
' Verify the response of each board.
Public Declare Function AxlGetResponseBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwpReadData As Long) As Long

' Reading firmware version function of slaves in network type master board.
' Declare with array of ucaFirmwareVersion unsigned char type(Size : 4 or more)
Public Declare Function AxmInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function AxaInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function AxdInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function AxcInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal ucaFirmwareVersion As Long) As Long


'======== Only for PCI-R1604-MLII ===========================================================================
' Set the value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
' Default value : Max
' Setting value Range : 0 ~ 4000H
' If it is set to 4000H or higher, the setting is set higher than that, but the operation is applied to the value of 4000H.
Public Declare Function  AxmSetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTorqFeedForward As Long) As Long

' It is API that read value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
' Default value : Max
Public Declare Function  AxmGetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpTorqFeedForward As Long) As Long

' It is API that set the value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
' Default value : 0
' Setting value Range : 0 ~ FFFFH
Public Declare Function  AxmSetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwVelocityFeedForward As Long) As Long

' It is API that read value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
Public Declare Function AxmGetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpVelocityFeedForward As Long) As Long


' Set Encoder type.
' Default value : 0(TYPE_INCREMENTAL)
' Setting range : 0 ~ 1
' dwEncoderType : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
Public Declare Function AxmSignalSetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwEncoderType As Long) As Long


' Verify Encoder type.
Public Declare Function AxmSignalGetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpEncoderType As Long) As Long



' For updating the slave firmware(only for RTEX-PM).
' Public Declare Function AxmSetSendAxisCommand Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wCommand As Long, ByRef wpSendData As Long, ByVal wLength As Long) As Long

'======== Only for PCI-R1604-RTEX, RTEX-PM==============================================================
' When Input Universal Input 2, 3, Set Jog move velocity
' Set only once execute after all drive setting (Ex, PulseOutMethod, MoveUnitPerPulse etc..)
Public Declare Function AxmMotSetUserMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long


' When Input Universal Input 2, 3, Set Jog move usage
' Setting value :  0(DISABLE), 1(ENABLE)
Public Declare Function AxmMotSetUserMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long) As Long


' Set Load/UnLoad Position to Automatically move use MPGP Input.
Public Declare Function AxmMotSetUserPosMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dLoadPos As Double, ByVal dUnLoadPos As Double, ByVal dwFilter As Long, ByVal dwDelay As Long) As Long


' Set Usage Load/UnLoad Position to Automatically move use MPGP Input
' Setting value :  0(DISABLE), 1(Position function A), 2(Position function B).
Public Declare Function AxmMotSetUserPosMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long) As Long

'========================================================================================================

'======== SIO-CN2CH, Only for absolute position trigger module(B0) ================================================
' The API of writing memory data.
Public Declare Function AxcKeWriteRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByVal dwData As Long) As Long
' The API of reading memory data.
Public Declare Function AxcKeReadRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByRef dwpData As Long) As Long
' Memory initialization API.
Public Declare Function AxcKeResetRamDataAll Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwData As Long) As Long
' Trigger timeout setting API.
Public Declare Function AxcTriggerSetTimeout Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwTimeout As Long) As Long
' Trigger timeout checking API.
Public Declare Function AxcTriggerGetTimeout Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpTimeout As Long) As Long
' Trigger Waiting State checking API.
Public Declare Function AxcStatusGetWaitState Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpState As Long) As Long
' Trigger Waiting State setting API.
Public Declare Function AxcStatusSetWaitState Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwState As Long) As Long

' Write command to designated channel.
Public Declare Function AxcKeSetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByVal dwData As Long) As Long
' Write command to designated channel.
Public Declare Function AxcKeSetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByVal wData As Integer) As Long
' Verify register of specified channel.
Public Declare Function AxcKeGetCommandData32 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByRef dwpData As Long) As Long
' Verify register of specified channel.
Public Declare Function AxcKeGetCommandData16 Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwCommand As Long, ByRef wpData As Integer) As Long

'========================================================================================================

' ======== Only for PCI-N804/N404, Sequence Motion ===========================================================
' Set Axis Information of sequence Motion (min 1axis)
' lSeqMapNo : Sequence Motion Index Point
' lSeqMapSize : Number of axis
' long* LSeqAxesNo : Number of arrar
Public Declare Function AxmSeqSetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal lSeqMapSize As Long, ByRef lSeqAxesNo As Long) As Long
Public Declare Function AxmSeqGetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lSeqMapSize As Long, ByRef lSeqAxesNo As Long) As Long


' Set Standard(Master)Axis of Sequence Motion.
' By all means Set in AxmSeqSetAxisMap setting axis.
Public Declare Function AxmSeqSetMasterAxisNo Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal lMasterAxisNo As Long) As Long


' Notifies the library node start loading of Sequence Motion.
Public Declare Function AxmSeqBeginNode Lib "AXL.dll" (ByVal lSeqMapNo) As Long


' Notifies the library node end loading of Sequence Motion.
Public Declare Function AxmSeqEndNode Lib "AXL.dll" (ByVal lSeqMapNo) As Long


' Start Sequence Motion Move.
Public Declare Function AxmSeqStart Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal dwStartOption As Long) As Long


' Set each profile node Information of Sequence Motion in Library.
' if used 1axis Sequence Motion, Must be Set *dPosition one Array.
Public Declare Function AxmSeqAddNode Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef dPosition As Double, ByVal dVelocity As Double, ByVal dAcceleration As Double, ByVal dDeceleration As Double, ByVal dNextVelocity As Double) As Long


' Return Node Index number of Sequence Motion.
Public Declare Function AxmSeqGetNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lCurNodeNo As Long) As Long


'  Return All node count of Sequence Motion.
Public Declare Function AxmSeqGetTotalNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lTotalNodeCnt As Long) As Long


' Return Sequence Motion drive status  of specific SeqMap.
' dwInMotion : 0(Drive end), 1(In drive).
Public Declare Function AxmSeqIsMotion Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef dwInMotion As Long) As Long


' Clear Sequence Motion Memory
Public Declare Function AxmSeqWriteClear Lib "AXL.dll" (ByVal lSeqMapNo) As Long


' Stop sequence motion
' dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
Public Declare Function AxmSeqStop Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal dwStopMode As Long) As Long


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
Public Declare Function AxmStatusSetMon Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwParaNo1 As Long, ByVal dwParaNo2 As Long, ByVal dwParaNo3 As Long, ByVal dwParaNo4 As Long, ByVal dwUse As Long) As Long
Public Declare Function AxmStatusGetMon Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpParaNo1 As Long, ByRef dwpParaNo2 As Long, ByRef dwpParaNo3 As Long, ByRef dwpParaNo4 As Long, ByRef dwpUse As Long) As Long
Public Declare Function AxmStatusReadMon Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpParaNo1 As Long, ByRef dwpParaNo2 As Long, ByRef dwpParaNo3 As Long, ByRef dwpParaNo4 As Long, ByRef dwDataValid As Long) As Long
Public Declare Function AxmStatusReadMonEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpDataCnt As Long, ByRef dwpReadData As Long) As Long

'=============================================================================================================

'======== Only for PCI-R32IOEV-RTEX ===========================================================================
' The API for read or write HPI register which allocated as I/O port.
' I/O Registers for HOST interface.
' I/O 00h Host status register (HSR)
' I/O 04h Host-to-DSP control register (HDCR)
' I/O 08h DSP page register (DSPP)
' I/O 0Ch Reserved
Public Declare Function AxlSetIoPort Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwAddr As Long, ByVal dwData As Long) As Long
Public Declare Function AxlGetIoPort Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwAddr As Long, ByRef dwpData As Long) As Long


'======= Only for PCI-R3200-MLIII ===========================================================================
' Basic information setting API for firmware update of M-III Master board.
Public Declare Function AxlM3SetFWUpdateInit Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwTotalPacketSize As Long, ByVal dwProcTotalStepNo As Long) As Long
' Verify setting value of 'AxlM3SetFWUpdateInit'.
Public Declare Function AxlM3GetFWUpdateInit Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwTotalPacketSize As Long, ByRef dwProcTotalStepNo As Long) As Long

' M-III Master board firmware update data transfer API.
Public Declare Function AxlM3SetFWUpdateCopy Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef pdwPacketData As Long, ByVal dwPacketSize As Long) As Long
' Verify setting value of 'AxlM3SetFWUpdateCopy'.
Public Declare Function AxlM3GetFWUpdateCopy Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwPacketSize As Long) As Long

' Execute firmware update of M-III Master Board.
Public Declare Function AxlM3SetFWUpdate Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwFlashBurnStepNo As Long) As Long
' Verifying result of execute firmware update of M-III Master Board.
Public Declare Function AxlM3GetFWUpdate Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwFlashBurnStepNo As Long, ByRef dwIsFlashBurnDone As Long) As Long

' The API for setting EEPROM data of M-III Master board.
Public Declare Function AxlM3SetCFGData Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef pCmdData As Integer, ByVal CmdDataSize As Integer) As Long
' The API for getting data from EEPROM of M-III Master board.
Public Declare Function AxlM3GetCFGData Lib "AXL.dll" (ByVal lBoradNo As Long, ByRef pCmdData As Integer, ByVal CmdDataSize As Integer) As Long

' The API for setting CONNECT PARAMETER information of M-III Master board.
Public Declare Function AxlM3SetMCParaUpdateInit Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wCh0Slaves As Integer, ByVal wCh1Slaves As Integer, ByVal dwCh0CycTime As Long, ByVal dwCh1CycTime As Long, ByVal dwChInfoMaxRetry As Long) As Long
' The API for verifying CONNECT PARAMETER information of M-III Master board.
Public Declare Function AxlM3GetMCParaUpdateInit Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef wCh0Slaves As Integer, ByVal wCh1Slaves As Integer, ByRef dwCh0CycTime As Long, ByRef dwCh1CycTime As Long, ByRef dwChInfoMaxRetry As Long) As Long
' The API for transmit CONNECT PARAMETER information of M-III Master board.
Public Declare Function AxlM3SetMCParaUpdateCopy Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wIdx As Integer, ByVal wSlaveAddr As Integer, ByVal dwProtoCalType As Long, ByVal dwTransBytes As Long, ByVal dwDeviceCode As Long) As Long
' The API for verifying transmit CONNECT PARAMETER information of M-III Master board.
Public Declare Function AxlM3GetMCParaUpdateCopy Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wIdx As Integer, ByRef wChannel As Integer, ByRef wSlaveAddr As Integer, ByRef dwProtoCalType As Long, ByRef dwTransBytes As Long, ByRef dwDeviceCode As Long) As Long

' The API for checking register as DWord unit within M-III Master board.
Public Declare Function AxlBoardReadDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Integer, ByRef dwData As Long) As Long
' The API for setting register as DWord unit within M-III Master board
Public Declare Function AxlBoardWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Integer, ByVal dwData As Long) As Long

' Setting and verifying extension register as DWord unit within board.
Public Declare Function AxlBoardReadDWordEx Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwOffset As Long, ByRef dwData As Long) As Long
Public Declare Function AxlBoardWriteDWordEx Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwOffset As Long, ByVal dwData As Long) As Long


' The API for setting servo to stop mode.
Public Declare Function AxmM3ServoSetCtrlStopMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal bStopMode As Byte) As Long
' The API for setting servo to Lt selection state.
Public Declare Function AxmM3ServoSetCtrlLtSel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal bLtSell As Byte, ByVal bLtSel2 As Byte) As Long
' The API for verifying servo I/O input state.
Public Declare Function AxmStatusReadServoCmdIOInput Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long
' Servo interpolation drive API.
Public Declare Function AxmM3ServoExInterpolate Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTPOS As Long, ByVal dwVFF As Long, ByVal dwTFF As Long, ByVal dwTLIM As Long, ByVal dwExSig1 As Long, ByVal dwExSig2 As Long) As Long
' The API for setting bias of the servo actuator.
Public Declare Function AxmM3ServoSetExpoAccBias Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wBias As Integer) As Long
' The API for setting time of the servo actuator.
Public Declare Function AxmM3ServoSetExpoAccTime Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wTime As Integer) As Long
' The API for setting time of the servo move.
Public Declare Function AxmM3ServoSetMoveAvrTime Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wTime As Integer) As Long
' The API for setting acc filter of the servo.
Public Declare Function AxmM3ServoSetAccFilter Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal bAccFil As Byte) As Long
' The API for setting status monitor1 of the servo.
Public Declare Function AxmM3ServoSetCprmMonitor1 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal bMonSel As Byte) As Long
' The API for setting status monitor2 of the servo.
Public Declare Function AxmM3ServoSetCprmMonitor2 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal bMonSel As Byte) As Long
' The API for verifying status monitor1 of the servo.
Public Declare Function AxmM3ServoStatusReadCprmMonitor1 Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long
' The API for verifying status monitor2 of the servo.
Public Declare Function AxmM3ServoStatusReadCprmMonitor2 Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long
' The API for setting Dec of servo actuator.
Public Declare Function AxmM3ServoSetAccDec Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wAccl As Integer, ByVal wAcc2 As Integer, ByVal wAccSW As Integer, ByVal wDec1 As Integer, ByVal wDec2 As Integer, ByVal wDecSW As Integer) As Long
' The API for servo stop.
Public Declare Function AxmM3ServoSetStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lMaxDecel As Long) As Long


'========== Common commands of standard I/O dvices =========================================================================
' The API for return parameter setting value of each slave device.
Public Declare Function AxlM3GetStationParameter Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal wNo As Integer, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Long
' The API for setting parameter value of each slave device.
Public Declare Function AxlM3SetStationParameter Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal wNo As Integer, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Long
' The API for return ID value of each slave device.
Public Declare Function AxlM3GetStationIdRd Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bIdCode As Byte, ByVal bOffset As Byte, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Long
' The API used as invalid command of each slave device.
Public Declare Function AxlM3SetStationNop Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte) As Long
' The API for set up each slave device.
Public Declare Function AxlM3SetStationConfig Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bConfigMode As Byte, ByVal bModuleType As Byte) As Long
' The API for return alarm and warning status value of each slave device.
Public Declare Function AxlM3GetStationAlarm Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal wAlarmRdMod As Integer, ByVal wAlarmIndex As Integer, ByVal bModuleType As Byte, ByRef pwAlarmData As Integer) As Long
' The API for clearing alarm and warning status value of each slave device.
Public Declare Function AxlM3SetStationAlarmClear Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal wAlarmClrMod As Integer, ByVal bModuleType As Byte) As Long
' The API for setting establish synchronous communication with each slave device.
Public Declare Function AxlM3SetStationSyncSet Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Integer) As Long
' The API for setting connection with each slave device.
Public Declare Function AxlM3SetStationConnect Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bVer As Byte, ByVal bComMode As Byte, ByVal bComTime As Byte, ByVal bProfileType As Byte, ByVal bModuleType As Byte) As Long
' The API for setting disconnection with each slave device.
Public Declare Function AxlM3SetStationDisConnect Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte) As Long
' The API for return of non-volatile parameter setting value.
Public Declare Function AxlM3GetStationStoredParameter Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal wNo As Integer, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Long
' The API for setting non-volatile parameter value of each slave device.
Public Declare Function AxlM3SetStationStoredParameter Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal wNo As Integer, ByVal bSize As Byte, ByVal bModuleType As Byte, ByRef pbParam As Byte) As Long
' The API for return of memory setting value of each slave device.
Public Declare Function AxlM3GetStationMemory Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal wSize As Integer, ByVal dwAddress As Long, ByVal bModuleType As Byte, ByVal bMode As Byte, ByVal bDataType As Byte, ByRef pbData As Byte) As Long
' The API for setting memory value of each slave device.
Public Declare Function AxlM3SetStationMemory Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal wSize As Integer, ByVal dwAddress As Long, ByVal bModuleType As Byte, ByVal bMode As Byte, ByVal bDataType As Byte, ByRef pbData As Byte) As Long


'========== Connection commands of standard I/O dvices =========================================================================
' The API for setting value of automatic access mode of each re-ordered slave device.
Public Declare Function AxlM3SetStationAccessMode Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte, ByVal bRWSMode As Byte) As Long
' The API for return of automatic access mode setting value of each re-ordered slave device.
Public Declare Function AxlM3GetStationAccessMode Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte, ByRef bRWSMode As Byte) As Long
' The API for set synchronous auto connect mode of each slave device.
Public Declare Function AxlM3SetAutoSyncConnectMode Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte, ByVal dwAutoSyncConnectMode As Long) As Long
' The API for return of synchronous auto connect mode setting value of each slave device.
Public Declare Function AxlM3GetAutoSyncConnectMode Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte, ByRef dwpAutoSyncConnectMode As Long) As Long
' The API for establish a single synchronization connection to each slave device.
Public Declare Function AxlM3SyncConnectSingle Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte) As Long
' The API for establish a single synchronization disconnection to each slave device.
Public Declare Function AxlM3SyncDisconnectSingle Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte) As Long
' The API for verifying connection status with slave device.
Public Declare Function AxlM3IsOnLine Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByRef dwData As Long) As Long


'========== Profile commands of standard I/O =========================================================================
' The API for return of data setting value for each synchronous I/O slave device.
Public Declare Function AxlM3GetStationRWS Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte, ByRef pdwParam As Long, ByVal bSize As Byte) As Long
' The API for setting data value for each synchronous I/O slave device.
Public Declare Function AxlM3SetStationRWS Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte, ByRef pdwParam As Long, ByVal bSize As Byte) As Long
' The API for return of data setting value for each asynchronous I/O slave device.
Public Declare Function AxlM3GetStationRWA Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte, ByRef pdwParam As Long, ByVal bSize As Byte) As Long
' The API for setting data value for each asynchronous I/O slave device.
Public Declare Function AxlM3SetStationRWA Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModuleNo As Long, ByVal bModuleType As Byte, ByRef pdwParam As Long, ByVal bSize As Byte) As Long


' Set the MLIII adjustment operation
' dwReqCode == 0x1005 : parameter initialization : 20sec
' dwReqCode == 0x1008 : absolute encoder reset   : 5sec
' dwReqCode == 0x100E : automatic offset adjustment of motor current detection signals  : 5sec
' dwReqCode == 0x1013 : Multiturn limit setting  : 5sec
Public Declare Function AxmM3AdjustmentOperation Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwReqCode As Long) As Long


' API for diagnosing home search progress.(Only for M3)
Public Declare Function AxmHomeGetM3FWRealRate Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upHomeMainStepNumber As Long, ByRef upHomeSubStepNumber As Long, ByRef upHomeLastMainStepNumber As Long, ByRef upHomeLastSubStepNumber As Long) As Long
' Return adjusted position value when escaping sensor zone from origin search.(Only for M3)
Public Declare Function AxmHomeGetM3OffsetAvoideSenArea Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dPos As Double) As Long
' The API for Setting adjusted position value when escaping sensor zone from origin search.(Only for M3)
' If dPos setting value is '0', adjusted position value will be set automatically when automatically escaping.
' 'dPos' should be a positive number.
Public Declare Function AxmHomeSetM3OffsetAvoideSenArea Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long


' Setting usage criterion of absolute encoder. Set whether to CMD/ACT POS initialize after origin search.(Only for M3)
' dwSel: 0, CMD/ACTPOS will be set '0' after origin search.(Default)
' dwSel: 1, CMD/ACTPOS will be not set after origin search.
Public Declare Function AxmM3SetAbsEncOrgResetDisable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwSel As Long) As Long

' Get 'AxmM3SetAbsEncOrgResetDisable' setting value.(Only for M3)
' upSel: 0, CMD / ACTPOS set to 0 after home search. (Default)
' upSel: 1, CMD / ACTPOS value is not set after home search.
Public Declare Function AxmM3GetAbsEncOrgResetDisable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upSel As Long) As Long


' Setting whether using alarm maintenance function when switch to slave offline mode.(Only for M3)
' dwSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
' dwSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
Public Declare Function AxmM3SetOfflineAlarmEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwSel As Long) As Long

' Get 'AxmM3SetOfflineAlarmEnable' setting value.(Only for M3)
' upSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
' upSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
Public Declare Function AxmM3GetOfflineAlarmEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upSel As Long) As Long

' Read value of slave online or offline status. (Only for M3)
' upSel: 0, ONLINE->OFFLINE Not converted
' upSel: 1, ONLINE->OFFLINE converted
Public Declare Function AxmM3ReadOnlineToOfflineStatus Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

    Public Declare Function AxlSetLockMode Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wLockMode As Long) As Long
    Public Declare Function AxlSetLockData Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwTotalNodeNum As Long, ByRef dwpNodeNo As Long, ByRef dwpNodeID As Long, ByRef dwpLockData As Long) As Long
    Public Declare Function AxmMoveStartPosWithAVC Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPosition As Double, ByVal dMaxVelocity As Double, ByVal dMaxAccel As Double, ByVal dMinJerk As Double, ByRef dpMoveVelocity As Double, ByRef dpMoveAccel As Double, ByRef dpMoveJerk As Double) As Long

'======== API for EtherCAT only =============================================================================
' The API for read VendorID, ProductCode and RevisionNo of EtherCat slave product by using StationAddress.
Public Declare Function AxlECatGetProductInfo Lib "AXL.dll" (ByVal dwStationAddress As Long, ByRef pdwVendorID As Long, ByRef pdwProductCode As Long, ByRef pdwRevisionNo As Long) As Long
    Public Declare Function AxlECatGetProductInfoEx Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwStationAddress As Long, ByRef pdwVendorID As Long, ByRef pdwProductCode As Long, ByRef pdwRevisionNo As Long) As Long

' The API for verifying network status of EtherCAT slave product by using StationAddress.
Public Declare Function AxlECatGetModuleStatus Lib "AXL.dll" (ByVal dwStationAddress As Long) As Long


' Read input PDO(Process Data Objects)
' dwBitOffset     : ProcessImage inputs bit offset value.
' dwDataBitLength : bit size of input pdo data.
' pbyData         : The Buffer for inserting read data.
Public Declare Function AxlECatReadPdoInput Lib "AXL.dll" (ByVal dwBitOffset As Long, ByVal dwDataBitLength As Long, ByRef pbyData As Byte) As Long
    Public Declare Function AxlECatReadPdoInputEx Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwBitOffset As Long, ByVal dwDataBitLength As Long, ByRef pbyData As Byte) As Long


' Read output PDO(Process Data Objects)
' dwBitOffset     : ProcessImage outputs bit offset value.
' dwDataBitLength : bit size of input pdo data.(for read)
' pbyData         : The Buffer for inserting read data.
Public Declare Function AxlECatReadPdoOutput Lib "AXL.dll" (ByVal dwBitOffset As Long, ByVal dwDataBitLength As Long, ByRef pbyData As Byte) As Long
    Public Declare Function AxlECatReadPdoOutputEx Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwBitOffset As Long, ByVal dwDataBitLength As Long, ByRef pbyData As Byte) As Long

' Write value to output process data.
' dwBitOffset     : ProcessImage outputs bit offset value.
' dwDataBitLength : bit size of output pdo data.(for write)
' pbyData         : The Buffer for inserting write data.
Public Declare Function AxlECatWritePdoOutput Lib "AXL.dll" (ByVal dwBitOffset As Long, ByVal dwDataBitLength As Long, ByRef pbyData As Byte) As Long


' Read SDO(Service Data Objects) by using COE.
Public Declare Function AxlECatReadSdo Lib "AXL.dll" (ByVal dwStationAddress As Long, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte, ByVal dwDataLength As Long, ByRef pdwReadDataLength As Long) As Long
    Public Declare Function AxlECatReadSdoEx Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwStationAddress As Long, ByVal wObjectIndex As Long, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte, ByVal dwDataLength As Long, ByRef pdwReadDataLength As Long) As Long

' Store values in SDO by using COE.
Public Declare Function AxlECatWriteSdo Lib "AXL.dll" (ByVal dwStationAddress As Long, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte, ByVal dwDataLength As Long) As Long
    Public Declare Function AxlECatWriteSdoEx Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwStationAddress As Long, ByVal wObjectIndex As Long, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte, ByVal dwDataLength As Long) As Long

    Public Declare Function AxlECatReadSdoFromAxisDouble Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wObjectIndex As Long, ByVal byObjectSubIndex As Byte, ByRef pdData As Double) As Long

    Public Declare Function AxlECatWriteSdoFromAxisDouble Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wObjectIndex As Long, ByVal byObjectSubIndex As Byte, ByRef pdData As Double) As Long
' Read SDO(DWORD type) through the axis number.
Public Declare Function AxlECatReadSdoFromAxisDword Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pdwData As Long) As Long

' Store values in SDO(DWORD type) through the axis number.
Public Declare Function AxlECatWriteSdoFromAxisDword Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pdwData As Long) As Long

' Read SDO(WORD type) through the axis number.
Public Declare Function AxlECatReadSdoFromAxisWord Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pwData As Integer) As Long

' Store values in SDO(WORD type) through the axis number.
Public Declare Function AxlECatWriteSdoFromAxisWord Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pwData As Integer) As Long

' Read SDO(BYTE type) through the axis number.
Public Declare Function AxlECatReadSdoFromAxisByte Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte) As Long

' Store values in SDO(BYTE type) through the axis number.
Public Declare Function AxlECatWriteSdoFromAxisByte Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wObjectIndex As Integer, ByVal byObjectSubIndex As Byte, ByRef pbyData As Byte) As Long

' Read value of EEPROM.
Public Declare Function AxlECatReadEEPRom Lib "AXL.dll" (ByVal dwStationAddress As Long, ByVal wEEPRomStartOffset As Integer, ByRef pwData As Integer, ByVal dwDataLength As Long) As Long

' Write value to EEPROM.
Public Declare Function AxlECatWriteEEPRom Lib "AXL.dll" (ByVal dwStationAddress As Long, ByVal wEEPRomStartOffset As Integer, ByRef pwData As Integer, ByVal dwDataLength As Long) As Long
    Public Declare Function AxlECatReadEEPRomEx Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwStationAddress As Long, ByVal wEEPRomStartOffset As Long, ByRef pwData As Long, ByVal dwDataLength As Long) As Long

    Public Declare Function AxlECatWriteEEPRomEx Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwStationAddress As Long, ByVal wEEPRomStartOffset As Long, ByRef pwData As Long, ByVal dwDataLength As Long) As Long

' Read value of a register.
Public Declare Function AxlECatReadRegister Lib "AXL.dll" (ByVal dwStationAddress As Long, ByVal wRegisterOffset As Integer, ByRef pvData As Object, ByVal wLen As Integer) As Long

' Write value of a register.
Public Declare Function AxlECatWriteRegister Lib "AXL.dll" (ByVal dwStationAddress As Long, ByVal wRegisterOffset As Integer, ByRef pvData As Object, ByVal wLen As Integer) As Long

' Save BackupData as a file from among the object dictionary of EtherCat slave.
Public Declare Function AxlECatSaveHotSwapData Lib "AXL.dll" (ByVal dwStationAddress As Long) As Long

' Load BackupData which saved as a file from corresponding EtherCat salve.
Public Declare Function AxlECatLoadHotSwapData Lib "AXL.dll" (ByVal dwStationAddress As Long) As Long

' When using the HotSwapStart API(Function to advance HotSwap only for registered StationAddresses),
'       it stores the StationAddress in HotSwapConfig, confirms existence and deletes it.
Public Declare Function AxlECatSetHotSwap Lib "AXL.dll" (ByVal dwStationAddress As Long) As Long
Public Declare Function AxlECatIsSetHotSwap Lib "AXL.dll" (ByVal dwStationAddress As Long) As Long
Public Declare Function AxlECatReSetHotSwap Lib "AXL.dll" (ByVal dwStationAddress As Long) As Long


' Set EtherCat master mode (configure = 0, RumMode = 1)
Public Declare Function AxlECatSetMasterMode Lib "AXL.dll" (ByVal dwMasterMode As Long) As Long

' Get mode status of EtherCat master.
Public Declare Function AxlECatGetMasterMode Lib "AXL.dll" (ByRef pdwMasterMode As Long) As Long


' Set MasterOperationMode of EtherCat master.
Public Declare Function AxlECatSetMasterOperationMode Lib "AXL.dll" (ByVal dwOperationMode As Long) As Long


' Get MasterOperationMode of EtherCat master.
Public Declare Function AxlECatGetMasterOperationMode Lib "AXL.dll" (ByRef pdwOperationMode As Long) As Long

' Requesting scan command to EtherCat master, and then command to save scaned data to SHM.
Public Declare Function AxlECatRequestScanData Lib "AXL.dll" () As Long



' Get total number of scanned slaves.
Public Declare Function AxlECatGetScanSlaveCount Lib "AXL.dll" (ByRef pdwSlaveCount As Long) As Long


' Get current status information of EtherCat master.
Public Declare Function AxlECatGetStatus Lib "AXL.dll" (ByRef pnECMasterStatus As Integer, ByRef pnECSlaveStatus As Integer, ByRef pnECConnectedSlave As Integer, ByRef pnECConfiguredSlave As Integer, ByRef pnJobTaskCycleCnt As Integer, ByRef pdwECMasterNotification As Long) As Long


' Reconnecting failed network.
Public Declare Function AxlEcatReConnect Lib "AXL.dll" () As Long


' Get address information of slave which be set.
Public Declare Function AxmECatReadAddress Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpStationAddress As Long, ByRef lpAutoIncAddress As Long, ByRef dwpAliasAddress As Long) As Long
Public Declare Function AxdECatReadAddress Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dwpStationAddress As Long, ByRef lpAutoIncAddress As Long, ByRef dwpAliasAddress As Long) As Long
Public Declare Function AxaECatReadAddress Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dwpStationAddress As Long, ByRef lpAutoIncAddress As Long, ByRef dwpAliasAddress As Long) As Long
Public Declare Function AxsECatReadAddress Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dwpStationAddress As Long, ByRef lpAutoIncAddress As Long, ByRef dwpAliasAddress As Long) As Long


' Monitor
' Add an item to proceed with data collection.
Public Declare Function AxlMonitorSetItem Lib "AXL.dll" (ByVal lItemIndex As Long, ByVal dwSignalType As Long, ByVal lSignalNo As Long, ByVal lSubSignalNo As Long) As Long


' Get information about items to be collected.
Public Declare Function AxlMonitorGetIndexInfo Lib "AXL.dll" (ByRef lpItemSize As Long, ByRef lpItemIndex As Long) As Long


' Get detailed settings of each items for data collection progress.
Public Declare Function AxlMonitorGetItemInfo Lib "AXL.dll" (ByVal lItemIndex As Long, ByRef dwpSignalType As Long, ByRef lSignalNo As Long, ByRef lpSubSignalNo As Long) As Long


' Reset settings of all data collection items.
Public Declare Function AxlMonitorResetAllItem Lib "AXL.dll" () As Long


' Reset settings of selected data collection items.
Public Declare Function AxlMonitorResetItem Lib "AXL.dll" (ByVal lItemIndex As Long) As Long


' Set the trigger condition of data collection.
Public Declare Function AxlMonitorSetTriggerOption Lib "AXL.dll" (ByVal dwSignalType As Long, ByVal lSignalNo As Long, ByVal lSubSignalNo As Long, ByVal dwOperatorType As Long, ByVal dValue1 As Double, ByVal dValue2 As Double) As Long



' Get the trigger condition of data collection.
' DWORD  __stdcall AxlMonitorGetTriggerOption(DWORD* dwpSignalType, long* lpSignalNo, long* lpSubSignalNo, DWORD* dwpOperatorType, double* dpValue1, double* dpValue2);

' Reset trigger condition of data collection.
Public Declare Function AxlMonitorResetTriggerOption Lib "AXL.dll" () As Long


' Start collecting data.
Public Declare Function AxlMonitorStart Lib "AXL.dll" (ByVal dwStartOption As Long, ByVal dwOverflowOption As Long) As Long


' Stop collecting data.
Public Declare Function AxlMonitorStop Lib "AXL.dll" () As Long


' Gets collected data.
Public Declare Function AxlMonitorReadData Lib "AXL.dll" (ByRef lpItemSize As Long, ByRef lpDataCount As Long, ByRef dpReadData As Double) As Long


' Gets the period of data collection.
Public Declare Function AxlMonitorReadPeriod Lib "AXL.dll" (ByRef dwpPeriod As Long) As Long


' MonitorEX
' Add an item to proceed with data collection.
Public Declare Function AxlMonitorExSetItem Lib "AXL.dll" (ByVal lItemIndex As Long, ByVal dwSignalType As Long, ByVal lSignalNo As Long, ByVal lSubSignalNo As Long) As Long


' Gets information about the items to be collected.
Public Declare Function AxlMonitorExGetIndexInfo Lib "AXL.dll" (ByRef lpItemSize As Long, ByRef lpItemIndex As Long) As Long


' Gets the detailed settings for each item to proceed with data collection.
Public Declare Function AxlMonitorExGetItemInfo Lib "AXL.dll" (ByVal lItemIndex As Long, ByRef dwpSignalType As Long, ByRef lpSignalNo As Long, ByRef lpSubSignalNo As Long) As Long


' Reset settings of all data collection items.
Public Declare Function AxlMonitorExResetAllItem Lib "AXL.dll" () As Long


' Reset settings of selected data collection items.
Public Declare Function AxlMonitorExResetItem Lib "AXL.dll" (ByVal lItemIndex As Long) As Long


' Set the trigger condition of data collection.
Public Declare Function AxlMonitorExSetTriggerOption Lib "AXL.dll" (ByVal dwSignalType As Long, ByVal lSignalNo As Long, ByVal lSubSignalNo As Long, ByVal dwOperatorType As Long, ByVal dValue1 As Double, ByVal dValue2 As Double) As Long



' Get the trigger condition of data collection.
' DWORD  __stdcall AxlMonitorGetTriggerOption(DWORD* dwpSignalType, long* lpSignalNo, long* lpSubSignalNo, DWORD* dwpOperatorType, double* dpValue1, double* dpValue2);

' Reset trigger condition of data collection.
Public Declare Function AxlMonitorExResetTriggerOption Lib "AXL.dll" () As Long


' Start collecting data.
Public Declare Function AxlMonitorExStart Lib "AXL.dll" (ByVal dwStartOption As Long, ByVal dwOverflowOption As Long) As Long


' Stop collecting data.
Public Declare Function AxlMonitorExStop Lib "AXL.dll" () As Long


' Gets collected data.
Public Declare Function AxlMonitorExReadData Lib "AXL.dll" (ByRef lpItemSize As Long, ByRef lpDataCount As Long, ByRef dpReadData As Double) As Long


' Gets the period of data collection.
Public Declare Function AxlMonitorExReadPeriod Lib "AXL.dll" (ByRef dwpPeriod As Long) As Long



' Linear interpolation about 2 axis including information of offset position for X2, Y2 axis.
Public Declare Function AxmLineMoveDual01 Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dpEndPosition As Double, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dOffsetLength As Double, ByVal dTotalLength As Double, ByRef dpStartOffsetPosition As Double, ByRef dpEndOffsetPosition As Double) As Long
' Arc interpolation about 2 axis including information of offset position for X2, Y2 axis.
Public Declare Function AxmCircleCenterMoveDual01 Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef lpAxes As Long, ByRef dpCenterPosition As Double, ByRef dpEndPosition As Double, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dwCWDir As Long, ByVal dOffsetLength As Double, ByVal dTotalLength As Double, ByRef dpStartOffsetPosition As Double, ByRef dpEndOffsetPosition As Double) As Long

' About ECAT Foe
Public Declare Function AxdSetFirmwareUpdateInfo Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwTotalDataSize As Long, ByVal dwTotalPacketSize As Long) As Long
Public Declare Function AxdSetFirmwareDataTrans Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwPacketIndex As Long, ByRef dwaPacketData As Long) As Long
Public Declare Function AxdSetFirmwareUpdate Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef szFileName As Byte, ByVal dwFileNameLen As Long, ByVal dwPassWord As Long) As Long


Public Declare Function AxaSetFirmwareUpdateInfo Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwTotalDataSize As Long, ByVal dwTotalPacketSize As Long) As Long
Public Declare Function AxaSetFirmwareDataTrans Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwPacketIndex As Long, ByRef dwaPacketData As Long) As Long
Public Declare Function AxaSetFirmwareUpdate Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef szFileName As Byte, ByVal dwFileNameLen As Long, ByVal dwPassWord As Long) As Long


Public Declare Function AxmSetFirmwareUpdateInfo Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTotalDataSize As Long, ByVal dwTotalPacketSize As Long) As Long
Public Declare Function AxmSetFirmwareDataTrans Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwPacketIndex As Long, ByRef dwaPacketData As Long) As Long
Public Declare Function AxmSetFirmwareUpdate Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef szFileName As Byte, ByVal dwFileNameLen As Long, ByVal dwPassWord As Long) As Long
    Public Declare Function AxmSetFoeUploadInfo Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTotalDataSize As Long, ByVal dwTotalPacketSize As Long) As Long
    Public Declare Function AxmGetFoeUploadData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwPacketIndex As Long, ByRef dwaPacketData As Long) As Long
    Public Declare Function AxmSetFoeUpload Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef szFileName As char*, ByVal dwFileNameLen As Long, ByVal dwPassWord As Long) As Long


Public Declare Function AxmMotSetOperationMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwOperationMode As Long) As Long
Public Declare Function AxmMotGetOperationMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef pdwOperationMode As Long) As Long



    Public Declare Function AxcTriggerSetPatternData Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal nDataCnt As Long, ByVal dwOption As Long, ByRef dpPatternData As Double) As Long
    Public Declare Function AxcTriggerGetPatternData Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef npDataCnt As Long, ByRef dwpOption As Long, ByRef dpPatternData As Double) As Long

    Public Declare Function AxmSpiralMoveEx Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dSpiralPitch As Double, ByVal dTurningCount As Double, ByVal dAngleOfPose As Double, ByVal dwIsInnerDirection As Long, ByVal dVelocity As Double, ByVal dAcceleration As Double, ByVal dDeceleration As Double) As Long
    Public Declare Function AxmFilletMove Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef dPosition As Double, ByRef dFirstVector As Double, ByRef dSecondVector As Double, ByVal dMaxVelocity As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double, ByVal dRadius As Double) As Long

    Public Declare Function AxmSignalIsServoOnSingleAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upOnOff As Long) As Long

    Public Declare Function AxmMotSetTorqueConnection Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lSourceAxisNo As Long, ByVal dwEnable As Long) As Long
    Public Declare Function AxmMotGetTorqueConnection Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef plSourceAxisNo As Long, ByRef pdwEnable As Long) As Long


