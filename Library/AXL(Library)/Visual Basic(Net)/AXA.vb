Option Strict Off
Option Explicit On
Module AXA

    '*****************************************************************************
    '/****************************************************************************
    '*****************************************************************************
    '**
    '** File Name
    '** ----------
    '**
    '** AXA.VB
    '**
    '** COPYRIGHT (c) AJINEXTEK Co., LTD
    '**
    '*****************************************************************************
    '*****************************************************************************
    '**
    '** Description
    '** -----------
    '** Ajinextek Analog Library Header File
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

'========== Board and verification API group of module information =================================================================================
'Verify if AIO module exists
Public Declare Function AxaInfoIsAIOModule Lib "AXL.dll" (ByRef upStatus As Integer) As Integer


'Verify AIO module number
Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer


'Verify the number of AIO module
Public Declare Function AxaInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Integer) As Integer


'Verify the number of input channels of specified module
Public Declare Function AxaInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer


'Verify the number of output channels of specified module
Public Declare Function AxaInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer


'Verify the first channel number of specified module
Public Declare Function AxaInfoGetChannelNoOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpChannelNo As Integer) As Integer


'Verify the first Input channel number of specified module (Inputmodule, Integration for input/output Module)
Public Declare Function AxaInfoGetChannelNoAdcOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpChannelNo As Integer) As Integer


'Verify the first output channel number of specified module (Inputmodule, Integration for input/output Module)
Public Declare Function AxaInfoGetChannelNoDacOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpChannelNo As Integer) As Integer


'Verify base board number, module position and module ID with specified module number
Public Declare Function AxaInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpBoardNo As Integer, ByRef lpModulePos As Integer, ByRef upModuleID As Integer) As Integer


'Verify specified module board : Sub ID, module name, module description                                                                   <<<<<
'======================================================'
' support product : EtherCAT
' upModuleSubID        : EtherCAT SubID(for distinguish between EtherCAT modules)
' szModuleName            : model name of module(50 Bytes)
' szModuleDescription  : description of module(80 Bytes)
'======================================================'
Public Declare Function AxaInfoGetModuleEx Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upModuleSubID As Integer, ByVal szModuleName As String, ByVal szModuleDescription As String) As Integer


'Verify Module status of specified module board
Public Declare Function AxaInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer


'========== API group of input module information search ====================================================================================
'Verify module number with specified input channel number
Public Declare Function AxaiInfoGetModuleNoOfChannelNo Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpModuleNo As Integer) As Integer


'Verify the number of entire channels of analog input module
Public Declare Function AxaiInfoGetChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Integer) As Integer


'========== API group for setting and verifying of input module interrupt ============================================================
'Use window message, callback API or event method in order to get event message into specified channel. Use for the time of collection action( refer AxaStartMultiChannelAdc ) of continuous data by H/W timer
'(Timer Trigger Mode, External Trigger Mode)
'Use Windows message and callback function or event method to receive an interrupt message to the specified module.
'========= Interrupt-related function ======================================================================================
'The callback function method has the advantage that the event can be notified very quickly because the callback function is called immediately at the time of the occurrence of the event.
'But, The main process is stalled until the callback function is completely terminated.
'In other words, Care must be taken when there is work load in the callback function.
'The event method is a method of continuously detecting and processing the occurrence of an interrupt by using a thread.
'The event method has the disadvantage that system resources are occupied by thread, but it has the advantage that interrupts can be detected and processed the fastest.
'This method is not commonly used. but it is used when quick interrupt handling is main concern.
'The event method uses a specific thread to monitor the occurrence of an event, and it works independently of the main process.
'So, This is the recommended method because it enables the most efficient use of resources in a multiprocessor system.
'Use a Window message or callback function to receive interrupt message.
'(Message handle, Message ID, Callback function, Interrupt event)
'    hWnd        : Used to receive window handles and window messages. If not, enter NULL.
'    uMessage    : Massage of window handle. To not use this or use the default value, enter 0.
'    proc        : Pointer of the function to be called when an interrupt occurs. To not use this, enter NULL.
'    pEvent      : Event handling when using event method.
Public Declare Function AxaiEventSetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal hWnd As Integer, ByVal uMesssage As Integer, ByVal pProc As Integer, ByRef pEvent As Integer) As Integer


'Set whether to use event in specified input channel
'======================================================'
' uUse       : DISABLE(0)   ' Event Disable
'            : ENABLE(1)    ' Event Enable
'======================================================'
Public Declare Function AxaiEventSetChannelEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uUse As Integer) As Integer


'Verify whether to use event in specified input channel
'======================================================'
' *upUse     : DISABLE(0)   ' Event Disable
'            : ENABLE(1)    ' Event Enable
'======================================================'
Public Declare Function AxaiEventGetChannelEnable Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUse As Integer) As Integer


'Set whether to use event in specified multiple input channels
'======================================================'
'lSize       : Number of input channel
' uUse       : DISABLE(0)' Event Disable
'            : ENABLE(1)    ' Event Enable
'======================================================'
Public Declare Function AxaiEventSetMultiChannelEnable Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal uUse As Integer) As Integer


'Set kind of event in specified input channel
'======================================================'
' uMask      : DATA_EMPTY(1)
'            : DATA_MANY(2)
'            : DATA_SMALL(3)
'            : DATA_FULL(4)
'======================================================'
Public Declare Function AxaiEventSetChannelMask Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uMask As Integer) As Integer


'Verify kind of event in specified input channel
'======================================================'
' *upMask    : DATA_EMPTY(1)
'            : DATA_MANY(2)
'            : DATA_SMALL(3)
'            : DATA_FULL(4)
'======================================================'
Public Declare Function AxaiEventGetChannelMask Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upMask As Integer) As Integer


'Set kind of event in specified multiple input channels
'=============================================================================='
' uMask      : DATA_EMPTY(1)
'            : DATA_MANY(2)
'            : DATA_SMALL(3)
'            : DATA_FULL(4)
'=============================================================================='
Public Declare Function AxaiEventSetMultiChannelMask Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal uMask As Integer) As Integer


'Verify event occurrence position
'=============================================================================='
' *upMode    : AIO_EVENT_DATA_UPPER(1)
'            : AIO_EVENT_DATA_LOWER(2)
'            : AIO_EVENT_DATA_FULL(3)
'            : AIO_EVENT_DATA_EMPTY(4)
'=============================================================================='
Public Declare Function AxaiEventRead Lib "AXL.dll" (ByRef lpChannelNo As Integer, ByRef upMode As Integer) As Integer


'Set interrupt mask of specified module. (SIO-AI4RB is not supportive.)
'=================================================================================================='
' uMask      : SCAN_END(1)
'            : FIFO_HALF_FULL(2)
'=================================================================================================='
Public Declare Function AxaiInterruptSetModuleMask Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uMask As Integer) As Integer


'Verify interrupt mask of specified module
'=================================================================================================='
' *upMask    : SCAN_END(1)
'            : FIFO_HALF_FULL(2)
'=================================================================================================='
Public Declare Function AxaiInterruptGetModuleMask Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upMask As Integer) As Integer


'========== API group for setting and verifying of input module parameter ========================================================================
'Set the input voltage range in specified input channel
'=================================================================================================='
' AI4RB
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AI16Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaiSetRange Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Integer


'Verify the input voltage range in specified input channel
'=================================================================================================='
' AI4RB
' *dpMinVolt  : -10V/-5V/0V
' *dpMaxVolt  : 10V/5V/
'
' AI16Hx
' *dpMaxVolt  : -10V Fix
' *dpMaxVolt  : 10V Fix
'=================================================================================================='
Public Declare Function AxaiGetRange Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpMinVolt As Double, ByRef dpMaxVolt As Double) As Integer


'Set the allowed input voltage range in specified multiple input Modules
'==================================================================================================//
' lModuleNo   : Analog Module Number
'
' RTEX AI16F
' Mode -5~+5  : dMinVolt = -5, dMaxVolt = +5
' Mode -10~+10: dMinVolt = -10, dMaxVolt = +10
'==================================================================================================//
Public Declare Function AxaiSetRangeModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long


'Verify the input voltage range in specified input Module
'==================================================================================================//
' lModuleNo   : Analog Module Number
'
' RTEX AI16F
' *dMinVolt   : -5V, -10V
' *dMaxVolt   : +5V, +10V
'==================================================================================================//
Public Declare Function AxaiGetRangeModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dMinVolt As Double, ByRef dMaxVolt As Double) As Long



'Set the allowed input voltage range in specified multiple input channels
'=================================================================================================='
' AI4RB
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AI16Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaiSetMultiRange Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Integer


'Set trigger mode in the specified input module
'=================================================================================================='
' uTriggerMode: NORMAL_MODE(1)
'             : TIMER_MODE(2)
'             : EXTERNAL_MODE(3)
'=================================================================================================='
Public Declare Function AxaiSetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uTriggerMode As Integer) As Integer


'Verify trigger mode in the specified input module
'=================================================================================================='
' *upTriggerMode : NORMAL_MODE(1)
'                : TIMER_MODE(2)
'                : EXTERNAL_MODE(3)
'=================================================================================================='
Public Declare Function AxaiGetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upTriggerMode As Integer) As Integer


'Set offset of specified input module by mVolt (mV) unit. Max -100~100mVolt
'=================================================================================================='
' dMiliVolt      : -100 ~ 100
'=================================================================================================='
Public Declare Function AxaiSetModuleOffsetValue Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dMiliVolt As Double) As Integer


'Verify offset value of specified input module. mVolt unit(mV)
'=================================================================================================='
' *dpMiliVolt    : -100 ~ 100
'=================================================================================================='
Public Declare Function AxaiGetModuleOffsetValue Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dpMiliVolt As Double) As Integer


'========== Software Timer (Normal Trigger Mode) group =======================================================================================
'Software Trigger Mode API, Convert analog input value to A/D in the specified input channel by user , then return it in voltage value
Public Declare Function AxaiSwReadVoltage Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpVolt As Double) As Integer


'Software Trigger Mode API, Return analog input value in digit value to specified input channel
Public Declare Function AxaiSwReadDigit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upDigit As Integer) As Integer


'Software Trigger Mode API, Return analog input value in voltage value to specified multiple input channels
Public Declare Function AxaiSwReadMultiVoltage Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef dpVolt As Double) As Integer


'Software Trigger Mode API, Return analog input value in digit value to specified multiple input channels
Public Declare Function AxaiSwReadMultiDigit Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef upDigit As Integer) As Integer


'========== Hardware Timer (Timer Trigger Mode + External Trigger Mode) group =======================================================================================
'Hardware Trigger Mode API, Set setting value in order to use immediate mode in specified multiple channels
Public Declare Function AxaiHwSetMultiAccess Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef lpWordSize As Integer) As Integer


'Hardware Trigger Mode API, Convert A/D as much as number of specified, then return the voltage value
Public Declare Function AxaiHwStartMultiAccess Lib "AXL.dll" (ByRef dpBuffer As Double) As Integer


'Set sampling interval to specified module by frequency unit(Hz)
'=================================================================================================='
' dSampleFreq    : 10 ~ 100000
'=================================================================================================='
Public Declare Function AxaiHwSetSampleFreq Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dSampleFreq As Double) As Integer


'Verify the setting value of sampling interval to specified module by frequency unit(Hz)
'=================================================================================================='
' *dpSampleFreq  : 10 ~ 100000
'=================================================================================================='
Public Declare Function AxaiHwGetSampleFreq Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dpSampleFreq As Double) As Integer


'Set sampling interval to specified module by time unit (uSec)
'=================================================================================================='
' dSamplePeriod  : 100000 ~ 1000000000
'=================================================================================================='
Public Declare Function AxaiHwSetSamplePeriod Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dSamplePeriod As Double) As Integer


'Verify setting value of sampling interval to specified module by time unit(uSec)
'=================================================================================================='
' *dpSamplePeriod : 100000 ~ 1000000000
'=================================================================================================='
Public Declare Function AxaiHwGetSamplePeriod Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dpSamplePeriod As Double) As Integer


'Set control method when the buffer is full in specified input channel
'=================================================================================================='
' uFullMode    : NEW_DATA_KEEP(0)
'              : CURR_DATA_KEEP(1)
'=================================================================================================='
Public Declare Function AxaiHwSetBufferOverflowMode Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uFullMode As Integer) As Integer


'Verify control method when the buffer is full in specified input channel
'=================================================================================================='
' *upFullMode  : NEW_DATA_KEEP(0)
'              : CURR_DATA_KEEP(1)
'=================================================================================================='
Public Declare Function AxaiHwGetBufferOverflowMode Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upFullMode As Integer) As Integer


'control method when the buffer is full in specified multiple input channels
'=================================================================================================='
' uFullMode    : NEW_DATA_KEEP(0)
'              : CURR_DATA_KEEP(1)
'=================================================================================================='
Public Declare Function AxaiHwSetMultiBufferOverflowMode Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal uFullMode As Integer) As Integer


'Set the upper limit and lower limit of buffer in specified input channel
Public Declare Function AxaiHwSetLimit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lLowLimit As Integer, ByVal lUpLimit As Integer) As Integer


'Verify the upper limit and lower limit of buffer in specified input channel
Public Declare Function AxaiHwGetLimit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpLowLimit As Integer, ByRef lpUpLimit As Integer) As Integer


'Set the upper limit and lower limit of buffer in multiple input channels
Public Declare Function AxaiHwSetMultiLimit Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal lLowLimit As Integer, ByVal lUpLimit As Integer) As Integer


'Start A/D conversion using H/W timer in specified multiple channels
Public Declare Function AxaiHwStartMultiChannel Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal lBuffSize As Integer) As Integer


'Start A/D conversion using H/W timer in specified single channels                                                                        <<<<<
Public Declare Function AxaiHwStartSingleChannelAdc Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lBuffSize As Integer) As Integer


'Stop continuous signal A/D conversion used H/W timer.
Public Declare Function AxaiHwStopSingleChannelAdc Lib "AXL.dll" (ByVal lChannelNo As Integer) As Integer


'After starting of A/D conversion in specified multiple channels, manage filtering as much as specified and return into voltage
'==================================================================================================//
'lSize           : Number of input channels to use
' *lpChannelNo    : An array of channel numbers to use
' lFilterCount    : Number of data for filtering
' lBuffSize       : Number of buffers which are assigned to each channel
'==================================================================================================//
Public Declare Function AxaiHwStartMultiFilter Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal lFilterCount As Integer, ByVal lBuffSize As Integer) As Integer


'Stop continuous signal A/D conversion used H/W timer
Public Declare Function AxaiHwStopMultiChannel Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer


'Inspect the numbers of data in memory buffer of specified input channel
Public Declare Function AxaiHwReadDataLength Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpDataLength As Integer) As Integer


'Read A/D conversion data used H/W timer in specified input channel by voltage value
Public Declare Function AxaiHwReadSampleVoltage Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpCount As Integer, ByRef dpVolt As Double) As Integer


'Read A/D conversion data used H/W timer in specified input channel by digit value
Public Declare Function AxaiHwReadSampleDigit Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpCount As Integer, ByRef upDigit As Integer) As Integer


'========== API group of input module state check ===================================================================================
'Inspect if there is no data in memory buffer of specified input channel
'=================================================================================================='
' *upEmpty     : FALSE(0)
'              : TRUE(1)
'=================================================================================================='
Public Declare Function AxaiHwIsBufferEmpty Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upEmpty As Integer) As Integer


'Inspect if the data is more than the upper limit specified in memory buffer of specified input channel
'=================================================================================================='
' *upUpper     : FALSE(0)
'              : TRUE(1)
'=================================================================================================='
Public Declare Function AxaiHwIsBufferUpper Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUpper As Integer) As Integer


'Inspect if the data is less than the upper limit specified in memory buffer of specified input channel
'=================================================================================================='
' *upLower     : FALSE(0)
'              : TRUE(1)
'=================================================================================================='
Public Declare Function AxaiHwIsBufferLower Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upLower As Integer) As Integer


'==External Trigger Mode Function
'Start external trigger mode of the selected channels of specified input module.
'==================================================================================================//
' lSize           : Number of channels to use external trigger on specified input module
' *lpChannelPos   : Index of channels to use external trigger on specified input module
Public Declare Function AxaiExternalStartADC Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lSize As Integer, ByRef lpChannelPos As Integer) As Integer
'Stop external trigger mode of specified input module.
Public Declare Function AxaiExternalStopADC Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer
'Return FIFO status of specified input module
'=================================================================================================='
' upStatus         : FIFO_DATA_EXIST(0)
'                  : FIFO_DATA_EMPTY(1)
'                  : FIFO_DATA_HALF(2)
'                  : FIFO_DATA_FULL(6)
'=================================================================================================='
Public Declare Function AxaiExternalReadFifoStatus Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upStatus As Integer) As Integer
'Read converted A/D value from external signal of specified input module.
' lSize           : Number of channels to read converted A/D value in specified input module
' *lpChannelPos   : Index of channels to read converted A/D value in specified input module
' lDataSize       : Number of maximum data to read converted A/D value by external trigger
' lBuffSize       : Size of externally allocated data buffer
' lStartDataPos   : Starting location of data buffer saving
' *dpVolt         : Two-demensional array pointer(for receiving value of converted to A/D)
' *lpRetDataSize  : Actually assigned number to data buffer(converted A/D value)
' *dwpStatus      : Return FIFO status when read converted A/D value from Fifo(H/W Buffer)
Public Declare Function AxaiExternalReadVoltage Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lSize As Integer, ByRef lpChannelPos As Integer, ByVal lDataSize As Integer, ByVal lBuffSize As Integer, ByVal lStartDataPos As Integer, ByRef dpVolt As Double, ByRef lpRetDataSize As Integer, ByRef upStatus As Integer) As Integer


'========== API group of output module information search ========================================================================================
'Verify module number with specified output channel number
Public Declare Function AxaoInfoGetModuleNoOfChannelNo Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpModuleNo As Integer) As Integer


'Verify entire number of channel of analog output module
Public Declare Function AxaoInfoGetChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Integer) As Integer


'========== API group for output module setting and verification ========================================================================================
'Set output voltage range in specified output channel
'=================================================================================================='
' AO4R
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AO2Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaoSetRange Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Integer


'Verify output voltage range in specified output channel
'=================================================================================================='
' AO4R
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AO2Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaoGetRange Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpMinVolt As Double, ByRef dpMaxVolt As Double) As Integer


'Set output voltage range in specified multiple output channels
'=================================================================================================='
' AO4R
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AO2Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaoSetMultiRange Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Integer


'The Input voltage is output in specified output channel
Public Declare Function AxaoWriteVoltage Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dVolt As Double) As Integer


'The Input voltage is output in specified multiple output channel
Public Declare Function AxaoWriteMultiVoltage Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef dpVolt As Double) As Integer


'Verify voltage which is output in specified output channel
Public Declare Function AxaoReadVoltage Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpVolt As Double) As Integer


'Verify voltage which is output in specified multiple output channels
Public Declare Function AxaoReadMultiVoltage Lib "AXL.dll" (ByVal lSize As Integer, ByRef lpChannelNo As Integer, ByRef dpVolt As Double) As Integer


'============================ AXA User Define Pattern Generator ============================
' API function for setting 'Channel User Define Pattern Generator'
' Outputting pattern every time depending on AxaoPgSetUserInterval setting
' lLoopCnt       : '0'(Repeat input pattern infinitely), 'value' : Keep last pattern, After outputting input pattern for specified number of times
'                : (MAX : 60000)
' lPatternSize   : Number of input pattern(MAX : 8192)
Public Declare Function AxaoPgSetUserPatternGenerator Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal lLoopCnt As Integer, ByVal lPatternSize As Integer, ByRef dpPattern As Double) As Integer

' API function for getting 'user define pattern generator'
Public Declare Function AxaoPgGetUserPatternGenerator Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpLoopCnt As Integer, ByRef lpPatternSize As Integer, ByRef dpPattern As Double) As Integer

' API function for setting 'pattern generator interval' of corresponding channel
' Unit : us(Default resolution : 500uSec)
Public Declare Function AxaoPgSetUserInterval Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dInterval As Double) As Integer

' API function for getting 'pattern generator interval' of corresponding channel
Public Declare Function AxaoPgGetUserInterval Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dpInterval As Double) As Integer

' API function for getting 'Pattern Index / Loop Cnt' of corresponding channel
' In the case of status, following status can be included.
' lpIndexNum : The index of current user pattern
' lpLoopCnt : Number of currently running loop
' dwpInBusy : Driving status of Pattern Generator
Public Declare Function AxaoPgGetStatus Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef lpIndexNum As Integer, ByRef lpLoopCnt As Integer, ByRef dwpInBusy As Integer) As Integer


' API function for start 'User Define Pattern Generator' of corresponding channel ('AO' output start)
' Inputting start channel number as an array
' Start pattern generator function simultaneously for input channel.
Public Declare Function AxaoPgSetUserStart Lib "AXL.dll" (ByVal lpChannelNo As Integer, ByVal lSize As Integer) As Integer


' API function for stopping 'User Define Pattern Generator' of corresponding channel ('AO' output stop)
' Output value is switched to 0 volt when output is stopped
Public Declare Function AxaoPgSetUserStop Lib "AXL.dll" (ByRef lpChannelNo As Integer, ByVal lSize As Integer) As Integer


' API function for clearing Pattern Data(Reset all areas to 0x00)
Public Declare Function AxaPgSetUserDataReset Lib "AXL.dll" (ByVal lChannelNo As Integer) As Integer


' API function for setting output status by each channel when specified output module network is broken
'===============================================================================================//
' lChannelNo  : Channel number(Distributed slave products only)
' dwSetValue  : Setting value
'             : 1 --> Analog Max
'             : 2 --> Analog MIN
'             : 3 --> User Vaule(Default user value : 0V, You can change this value by 'AxaoSetNetworkErrorUserValue()')
'             : 4 --> Analog 0 V
'==============================================================================================='
Public Declare Function AxaoSetNetworkErrorAct Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwSetValue As Integer) As Integer

' API function for setting output status in bytes when specified output module network is broken
'==============================================================================================='
' lChannelNo  : Channel number(Distributed slave products only)
' dVolt       : Analog output voltage(User defined value)
'==============================================================================================='
Public Declare Function AxaoSetNetworkErrorUserValue Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dVolt As Double) As Integer


End Module
