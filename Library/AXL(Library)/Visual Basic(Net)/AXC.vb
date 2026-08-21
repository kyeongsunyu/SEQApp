Option Strict Off
Option Explicit On
Module AXC

    '*****************************************************************************
    '/****************************************************************************
    '*****************************************************************************
    '**
    '** File Name
    '** ----------
    '**
    '** AXC.VB
    '**
    '** COPYRIGHT (c) AJINEXTEK Co., LTD
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Description
    '** -----------
    '** Ajinextek Counter Library Header File
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


'========== Board and verification API group of module information
'Verifying If CNT module exists
Public Declare Function AxcInfoIsCNTModule Lib "AXL.dll" (ByRef upStatus As Integer) As Integer


'Verifying CNT module number
Public Declare Function AxcInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer


'Verifying the number of CNT I/O module
Public Declare Function AxcInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Integer) As Integer


'Verifying the Number of counter input channels for specified module
Public Declare Function AxcInfoGetChannelCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer


' Verifying the total number of channels in system mounted counter.
Public Declare Function AxcInfoGetTotalChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Integer) As Integer


' Verifying base board number, module position and module ID with specified module number
Public Declare Function AxcInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpBoardNo As Integer, ByRef lpModulePos As Integer, ByRef upModuleID As Integer) As Integer


' Verifying specified module board : Sub ID, module name, module description
'======================================================/
' support product : EtherCAT
' upModuleSubID   : EtherCAT SubID(for distinguish between EtherCAT modules)
' szModuleName         : model name of module(50 Bytes)
' szModuleDescription  : description of module(80 Bytes)
'======================================================'
Public Declare Function AxcInfoGetModuleEx Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upModuleSubID As Integer, ByVal szNoduleName As String, ByVal szModuleDescription As String) As Integer



'Verifying Module status of specified module board
Public Declare Function AxcInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer


Public Declare Function AxcInfoGetFirstChannelNoOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpChannelNo As Integer) As Integer
    Public Declare Function AxcInfoGetModuleNoOfChannelNo Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpModuleNo As Integer) As Integer


' Setting encoder input method of counter module
' dwMethod --> 0x00 : Sign and pulse, x1 multiplication
' dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
' dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
' dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
' dwMethod --> 0x08 : Sign and pulse, x2 multiplication
' dwMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
' dwMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
' SIO-CN2CH/HPC4
' dwMethod --> 0x00 : Up/Down method, A phase : pulse, B phase : direction
' dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
' dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
' dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
Public Declare Function AxcSignalSetEncInputMethod Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwMethod As Integer) As Integer


' Verifying encoder input method of counter module
' *dwpUpMethod --> 0x00 : Sign and pulse, x1 multiplication
' *dwpUpMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
' *dwpUpMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
' *dwpUpMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
' *dwpUpMethod --> 0x08 : Sign and pulse, x2 multiplication
' *dwpUpMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
' *dwpUpMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
' SIO-CN2CH/HPC4
' dwMethod --> 0x00 : Up/Down method, A phase : pulse, B phase : direction
' dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
' dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
' dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
Public Declare Function AxcSignalGetEncInputMethod Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpUpMethod As Integer) As Integer


' Setting trigger of counter module
' dwMode -->  0x00 : Latch
' dwMode -->  0x01 : State
' dwMode -->  0x02 : Special State    --> SIO-CN2CH only
' SIO-CN2CH
' dwMode -->  0x00 : absolute position trigger or period position trigger.
' caution : Each product has different functions. So, it need to use distinctively.
' dwMode -->  0x01 : Time period trigger(Set to AxcTriggerSetFreq)
' In the case of SIO-HPC4
' dwMode -->  0x00 : absolute mode[with ram data].
' dwMode -->  0x01 : timer mode.
' dwMode -->  0x02 : absolute mode[with fifo].
' dwMode -->  0x03 : periodic mode.[Default]
Public Declare Function AxcTriggerSetFunction Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwMode As Integer) As Integer


' Verifying trigger setting of counter module
' *dwMode -->  0x00 : Latch
' *dwMode -->  0x01 : State
' *dwMode -->  0x02 : Special State
' dwMode -->  0x00 : absolute position trigger or period position trigger.
' caution : Each product has different functions. So, it need to use distinctively.
' dwMode -->  0x01 : Time period trigger(Set to AxcTriggerSetFreq)
' In the case of SIO-HPC4
' dwMode -->  0x00 : absolute mode[with ram data].
' dwMode -->  0x01 : timer mode.
' dwMode -->  0x02 : absolute mode[with fifo].
' dwMode -->  0x03 : periodic mode.[Default]
Public Declare Function AxcTriggerGetFunction Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpMode As Integer) As Integer


' dwUsage --> 0x00 : Trigger Not use
' dwUsage --> 0x01 : Trigger use
Public Declare Function AxcTriggerSetNotchEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwUsage As Integer) As Integer


' *dwUsage --> 0x00 : Trigger Not use
' *dwUsage --> 0x01 : Trigger use
Public Declare Function AxcTriggerGetNotchEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpUsage As Integer) As Integer




' Setting capture polarity of counter module.(External latch input polarity)
' dwCapturePol --> 0x00 : Signal OFF -> ON
' dwCapturePol --> 0x01 : Signal ON -> OFF
Public Declare Function AxcSignalSetCaptureFunction Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwCapturePol As Integer) As Integer


' Verifying capture polarity setting of counter module.(External latch input polarity)
' *dwCapturePol --> 0x00 : Signal OFF -> ON
' *dwCapturePol --> 0x01 : Signal ON -> OFF
Public Declare Function AxcSignalGetCaptureFunction Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpCapturePol As Integer) As Integer


' Verifying capture position of counter module.(External latch)
' *dbpCapturePos --> Location of Capture position
Public Declare Function AxcSignalGetCapturePos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dbpCapturePos As Double) As Integer


' Verifying counter value of counter module.
' *dbpActPos --> Counter value
Public Declare Function AxcStatusGetActPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dbpActPos As Double) As Integer


' Setting counter value to dbActPos of counter module.
Public Declare Function AxcStatusSetActPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dbActPos As Double) As Integer


' Setting trigger position of counter module.
' Trigger position of counter module can be set up to two.
Public Declare Function AxcTriggerSetNotchPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dbLowerPos As Double, ByVal dbUpperPos As Double) As Integer


' Verifying trigger position of counter module.
Public Declare Function AxcTriggerGetNotchPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dbpLowerPos As Double, ByRef dbpUpperPos As Double) As Integer


' Forced trigger output of counter module.
' dwOutVal --> 0x00 : Trigger output '0'
' dwOutVal --> 0x01 : Trigger output '1'
Public Declare Function AxcTriggerSetOutput Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwOutVal As Integer) As Integer


' Verifying status of counter module.
' Bit '0' : Carry (Only 1scan turns 'ON' When current counter value is changed to '0' over the upper limit by additional pulse)
' Bit '1' : Borrow (Only 1scan turns 'ON' When current counter value is changed to lower limit under the '0' by subtraction pulse)
' Bit '2' : Trigger output status
' Bit '3' : Latch input status
Public Declare Function AxcStatusGetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpChannelStatus As Integer) As Integer




' API for SIO-CN2CH only
'
' Setting position unit of counter module
' ex) If you need 1000pulse for move 1mm distance, Setting like -> dMoveUnitPerPulse = 0.001
'     And then, setting location-related values of all functions to 'mm' unit.
Public Declare Function AxcMotSetMoveUnitPerPulse Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dMoveUnitPerPulse As Double) As Integer


' Verifying position unit of counter module.
Public Declare Function AxcMotGetMoveUnitPerPulse Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpMoveUnitPerPuls As Double) As Integer


' Setting inversion function of encoder input counter of counter module.
' dwReverse --> 0x00 : No reversal.
' dwReverse --> 0x01 : Reversal.
Public Declare Function AxcSignalSetEncReverse Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwReverse As Integer) As Integer


' Returns whether the function of inverting the encoder input counter of the counter module is set.
Public Declare Function AxcSignalGetEncReverse Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpReverse As Integer) As Integer


' Selecting encoder input signal of counter module.
' dwSource -->  0x00 : 2(A/B)-Phase signal.
' dwSource -->  0x01 : Z-Phase signal.(No directionality.)
Public Declare Function AxcSignalSetEncSource Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwSource As Integer) As Integer


' Verifying encoder input signal selection setting of counter module.
Public Declare Function AxcSignalGetEncSource Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpSource As Integer) As Integer


' Setting lower limit value of trigger output range of counter module.
' Setting lower limit value of range to generate trigger output with position period.(In the case of position period trigger product)
' Setting standard position application of trigger information of start address of ram.(In the case of absolute location product)
' Unit : Set by 'AxcMotSetMoveUnitPerPulse'.
' Note : Lower limit value should be set smaller than upper limit value.
Public Declare Function AxcTriggerSetBlockLowerPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dLowerPosition As Double) As Integer


' Verifying lower limit value of trigger output range of counter module.
Public Declare Function AxcTriggerGetBlockLowerPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpLowerPosition As Double) As Integer


' Verifying upper limit value of trigger output range of counter module.
' Setting upper limit value of range to generate trigger output with position period.(In the case of position period trigger product).
' In the case of the product of absolute position trigger, used as location where trigger information is applied of last address of RAM(Trigger information was set).
' Unit : Setting from 'AxcMotSetMoveUnitPerPulse'
' Note : Upper limit value should be set bigger than lower limit value.
Public Declare Function AxcTriggerSetBlockUpperPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dUpperPosition As Double) As Integer
' Setting lower limit value of trigger output range of counter module.
Public Declare Function AxcTriggerGetBlockUpperPos Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpUpperrPosition As Double) As Integer


' Setting position period used for position peroid mode trigger of counter module.
' Unit : Sets from 'AxcMotSetMoveUnitPerPulse'.
Public Declare Function AxcTriggerSetPosPeriod Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dPeriod As Double) As Integer


' Verifying position period used for position peroid mode trigger of counter module.
Public Declare Function AxcTriggerGetPosPeriod Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpPeriod As Double) As Integer


' Setting a valid function about position increase/decrease when using trigger of position period mode of counter module.
' dwDirection -->  0x00 : Output every trigger period.(About counter increase/decrease)
' dwDirection -->  0x01 : Output every trigger period.(About counter increase)
' dwDirection -->  0x01 : Output every trigger period.(About counter decrease)
Public Declare Function AxcTriggerSetDirectionCheck Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwDirection As Integer) As Integer
' Verifying setting value of 'AxcTriggerSetDirectionCheck'.
Public Declare Function AxcTriggerGetDirectionCheck Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpDirection As Integer) As Integer


' Setting position period and range at once.(About trigger function of position period mode)
'Positioning unit : Set by 'AxcMotSetMoveUnitPerPulse'.
Public Declare Function AxcTriggerSetBlock Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dLower As Double, ByVal dUpper As Double, ByVal dABSod As Double) As Integer


' Verifying setting value of 'AxcTriggerSetBlock'.
Public Declare Function AxcTriggerGetBlock Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpLower As Double, ByRef dpUpper As Double, ByRef dpABSod As Double) As Integer


' Setting pulse width of trigger output of counter module.
' Unit : uSec
Public Declare Function AxcTriggerSetTime Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dTrigTime As Double) As Integer


' Verifying setting value of 'AxcTriggerSetTime'.
Public Declare Function AxcTriggerGetTime Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpTrigTime As Double) As Integer


' Setting output level of trigger output pulse of counter module.
' dwLevel -->  0x00 : Low level output.(When trigger is output)
' dwLevel -->  0x01 : High level output.(When trigger is output)
Public Declare Function AxcTriggerSetLevel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwLevel As Integer) As Integer
' Verifying setting value of 'AxcTriggerSetLevel'.
Public Declare Function AxcTriggerGetLevel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpLevel As Integer) As Integer


' Setting frequency for Frequency trigger output function of counter module.
' Unit : Hz, Range : 1Hz ~ 500 kHz
Public Declare Function AxcTriggerSetFreq Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwFreqency As Integer) As Integer
' Verifying setting value of 'AxcTriggerSetFreq'.
Public Declare Function AxcTriggerGetFreq Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpFreqency As Integer) As Integer


    Public Declare Function AxcTriggerGetTriggerOutCount Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpTriggerOutCount As Integer) As Integer
    Public Declare Function AxcTriggerSetTriggerOutCount Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwTriggerOutCount As Integer) As Integer



' Setting the value of universal output about appoint channel of counter module.
' dwOutput range : 0x00 ~ 0x0F, Four universal outputs for each channel.
Public Declare Function AxcSignalWriteOutput Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwOutput As Integer) As Integer


' Verifying the value of universal output about appoint channel of counter module.
Public Declare Function AxcSignalReadOutput Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpOutput As Integer) As Integer


' Setting the value by bit of universal output about appoint channel of counter module.
' lBitNo range : 0 ~ 3, Four universal outputs for each channel.
Public Declare Function AxcSignalWriteOutputBit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lBitNo As Integer, ByVal uOnOff As Integer) As Integer
' Verifying the value by bit of universal output about appoint channel of counter module.
' lBitNo range : 0 ~ 3
Public Declare Function AxcSignalReadOutputBit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lBitNo As Integer, ByRef upOnOff As Integer) As Integer


' Check the general-purpose input value for the designated channel of the counter module.
Public Declare Function AxcSignalReadInput Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpInput As Integer) As Integer


' Verifying the value by bit of universal input about appoint channel of counter module.
' lBitNo range : 0 ~ 3
Public Declare Function AxcSignalReadInputBit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lBitNo As Integer, ByRef upOnOff As Integer) As Integer


' Activating trigger output of counter module.
' Sets whether the trigger output will be finally output according to the currently set function.
Public Declare Function AxcTriggerSetEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwUsage As Integer) As Integer


' Verifying setting value of 'AxcTriggerSetEnable'.
Public Declare Function AxcTriggerGetEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpUsage As Integer) As Integer


' Verifying RAM contents for absolute trigger function of counter module.
' dwAddr range : 0x0000 ~ 0x1FFFF;
Public Declare Function AxcTriggerReadAbsRamData Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByRef dwpData As Integer) As Integer


' Setting RAM contents for absolute trigger function of counter module.
' dwAddr range : 0x0000 ~ 0x1FFFF;
Public Declare Function AxcTriggerWriteAbsRamData Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByVal dwData As Integer) As Integer


' Setting RAM contents at once for absolute trigger function of counter module.
' dwTrigNum range : ~ 0x20000  In the case of *RTEX CNT2  0x200*
' dwDirection --> 0x0 : Input trigger information first about lower limit trigger position. Used for trigger output(In direction of increasing position).
' dwDirection --> 0x1 : Input trigger information first about upper limit trigger position. Used for trigger output(In direction of decreasing position).
Public Declare Function AxcTriggerSetAbs Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwTrigNum As Integer, ByRef dwTrigPos As Integer, ByVal dwDirection As Integer) As Integer


' Set the contents of the RAM required for the absolute position trigger function of the counter module at once.
' dwTrigNum range : 0 ~ 0x20000 (RTEX CNT2 : 0 ~ 0x200)
' dwDirection     : (0) Enter the trigger information for the lower limit trigger position. Used for trigger output in the direction of increasing position.
'                   (1) Enter the trigger information for the upper limit trigger position. Used for trigger output in the direction of decreasing position.
' dTrigPos        : Use trigger position of counter module as double type
Public Declare Function AxcTriggerSetAbsDouble Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwTrigNum As Integer, ByRef dTrigPos As Double, ByVal dwDirection As Integer) As Integer

    Public Declare Function AxcTriggerSetEncoderInput Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwEncoderInput1 As Integer, ByVal dwEncoderInput2 As Integer) As Integer
    Public Declare Function AxcTriggerGetEncoderInput Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dwpEncoderInput1 As Integer, ByRef dwpEncoderInput2 As Integer) As Integer

    Public Declare Function AxcTableSetTriggerLevel Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal uLevel As Integer) As Integer
    Public Declare Function AxcTableGetTriggerLevel Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef upLevel As Integer) As Integer

    Public Declare Function AxcTableSetTriggerTime Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal dTriggerTimeUSec As Double) As Integer
    Public Declare Function AxcTableGetTriggerTime Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef dpTriggerTimeUSec As Double) As Integer

    Public Declare Function AxcTableSetEncoderInput Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal uEncoderInput1 As Integer, ByVal uEncoderInput2 As Integer) As Integer
    Public Declare Function AxcTableGetEncoderInput Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef upEncoderInput1 As Integer, ByRef upEncoderInput2 As Integer) As Integer


    Public Declare Function AxcTableSetTriggerOutport Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal uTriggerOutport As Integer) As Integer
    Public Declare Function AxcTableGetTriggerOutport Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef upTriggerOutport As Integer) As Integer

    Public Declare Function AxcTableSetErrorRange Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal dErrorRange As Double) As Integer
    Public Declare Function AxcTableGetErrorRange Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef dpErrorRange As Double) As Integer

    Public Declare Function AxcTableTriggerOneShot Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer) As Integer

    Public Declare Function AxcTableTriggerPatternShot Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal lTriggerCount As Integer, ByVal uTriggerFrequency As Integer) As Integer
    Public Declare Function AxcTableGetPatternShotData Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef lpTriggerCount As Integer, ByRef upTriggerFrequency As Integer) As Integer

    Public Declare Function AxcTableSetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal uTrigMode As Integer) As Integer
    Public Declare Function AxcTableGetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef upTrigMode As Integer) As Integer
    Public Declare Function AxcTableSetTriggerCountClear Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer) As Integer

    Public Declare Function AxcTableSetTriggerData Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal lTriggerDataCount As Integer, ByRef dpTriggerData As Double, ByRef lpTriggerCount As Integer, ByRef dpTriggerInterval As Double) As Integer
    Public Declare Function AxcTableGetTriggerData Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef lpTriggerDataCount As Integer, ByRef dpTriggerData As Double, ByRef lpTriggerCount As Integer, ByRef dpTriggerInterval As Double) As Integer

    Public Declare Function AxcTableSetTriggerDataEx Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal lTriggerDataCount As Integer, ByVal uOption As Integer, ByRef dpTriggerData As Double) As Integer
    Public Declare Function AxcTableGetTriggerDataEx Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef lpTriggerDataCount As Integer, ByRef upOption As Integer, ByRef dpTriggerData As Double) As Integer

    Public Declare Function AxcTableSetTriggerDataClear Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer) As Integer

    Public Declare Function AxcTableSetEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByVal uEnable As Integer) As Integer
    Public Declare Function AxcTableGetEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef upEnable As Integer) As Integer

    Public Declare Function AxcTableReadTriggerCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef lpTriggerCount As Integer) As Integer

    Public Declare Function AxcTableReadFifoStatus Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef lpCount1 As Integer, ByRef upStatus1 As Integer, ByRef lpCount2 As Integer, ByRef upStatus2 As Integer) As Integer

    Public Declare Function AxcTableReadFifoData Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lTablePos As Integer, ByRef dpTopData1 As Double, ByRef dpTopData2 As Double) As Integer

End Module
