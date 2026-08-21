//****************************************************************************
///****************************************************************************
//*****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXA.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Analog Library Header File
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

unit AXA;

interface

uses Windows, Messages, AXHS;

//========== Board and verification API group of module information ============
//Verify if AIO module exists
function AxaInfoIsAIOModule (upStatus : PDWord) : DWord; stdcall;


//Verify AIO module number
function AxaInfoGetModuleNo (lBoardNo: LongInt; lModulePos :  LongInt; lpModuleNo :  PLongInt) : DWord; stdcall;


//Verify the number of AIO module
function AxaInfoGetModuleCount (lpModuleCount : PLongInt) : DWord; stdcall;


//Verify the number of input channels of specified module
function AxaInfoGetInputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;


//Verify the number of output channels of specified module
function AxaInfoGetOutputCount (lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;


//Verify the first channel number of specified module
function AxaInfoGetChannelNoOfModuleNo (lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;


// Verify the first Input channel number of specified module (Inputmodule, Integration for input/output Module)
function AxaInfoGetChannelNoAdcOfModuleNo (lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;


// Verify the first output channel number of specified module (Inputmodule, Integration for input/output Module)
function AxaInfoGetChannelNoDacOfModuleNo (lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;


//Verify base board number, module position and module ID with specified module number
function AxaInfoGetModule (lModuleNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;


// Verify specified module board : Sub ID, module name, module description
//===============================================/
// support product : EtherCAT
// upModuleSubID   : EtherCAT SubID(for distinguish between EtherCAT modules)
// szModuleName         : model name of module(50 Bytes)
// szModuleDescription  : description of module(80 Bytes)
//======================================================//
function AxaInfoGetModuleEx (lModuleNo : LongInt; upModuleSubID : PDWord; szModuleName : PChar; szModuleDescription : PChar) : DWord; stdcall;

//Verify Module status of specified module board
function AxaInfoGetModuleStatus(lModuleNo : LongInt) : DWord; stdcall;


//========== API group of input module information search ======================
//Verify module number with specified input channel number
function AxaiInfoGetModuleNoOfChannelNo (lChannelNo : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;


//Verify the number of entire channels of analog input module
function AxaiInfoGetChannelCount (lpChannelCount : PLongInt) : DWord; stdcall;


//========== API group for setting and verifying of input module interrupt =====
//Use window message, callback API or event method in order to get event message into specified channel. Use for the time of collection action( refer AxaStartMultiChannelAdc ) of continuous data by H/W timer
//(Timer Trigger Mode, External Trigger Mode)
//Use Windows message and callback function or event method to receive an interrupt message to the specified module.
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
function AxaiEventSetChannel (lChannelNo : LongInt; hWnd : HWND; uMesssage : DWord; pProc : AXT_EVENT_PROC; pEvent : PDWord) : DWord; stdcall;


//Set whether to use event in specified input channel
//======================================================
// uUse   : DISABLE(0)    // Event Disable
//        : ENABLE(1)     // Event Enable
//==================================================
function AxaiEventSetChannelEnable (lChannelNo : LongInt; uUse : DWord) : DWord; stdcall;


//Verify whether to use event in specified input channel
//======================================================
// *upUse : DISABLE(0)    // Event Disable
//        : ENABLE(1)     // Event Enable
//==================================================
function AxaiEventGetChannelEnable (lChannelNo : LongInt; upUse : PDWord) : DWord; stdcall;


//Set whether to use event in specified multiple input channels
//======================================================
// lSize       : Number of input channel
// uUse   : DISABLE(0)    // Event Disable
//        : ENABLE(1)     // Event Enable
//==================================================
function AxaiEventSetMultiChannelEnable (lSize : LongInt; lpChannelNo : PLongInt; uUse : DWord) : DWord; stdcall;


//Set kind of event in specified input channel
//======================================================
// uMask  : DATA_EMPTY(1)
//        : DATA_MANY(2)
//        : DATA_SMALL(3)
//        : DATA_FULL(4)
//==================================================
function AxaiEventSetChannelMask (lChannelNo : LongInt; uMask : DWord) : DWord; stdcall;


//Verify kind of event in specified input channel
//======================================================
// *upMask: DATA_EMPTY(1)
//        : DATA_MANY(2)
//        : DATA_SMALL(3)
//        : DATA_FULL(4)
//==================================================
function AxaiEventGetChannelMask (lChannelNo : LongInt; upMask : PDWord) : DWord; stdcall;


//Set kind of event in specified multiple input channels
//======================================================
// uMask  : DATA_EMPTY(1)
//        : DATA_MANY(2)
//        : DATA_SMALL(3)
//        : DATA_FULL(4)
//==================================================
function AxaiEventSetMultiChannelMask (lSize : LongInt; lpChannelNo : PLongInt; uMask : DWord) : DWord; stdcall;


//Verify event occurrence position
//======================================================
// *upMode: AIO_EVENT_DATA_UPPER(1)
//        : AIO_EVENT_DATA_LOWER(2)
//        : AIO_EVENT_DATA_FULL(3)
//        : AIO_EVENT_DATA_EMPTY(4)
//==================================================
function AxaiEventRead (lpChannelNo : PLongInt; upMode : PDWord) : DWord; stdcall;


//Set interrupt mask of specified module. (SIO-AI4RB is not supportive.)
//======================================================
// uMask  : SCAN_END(1)
//        : FIFO_HALF_FULL(2)
//==================================================
function AxaiInterruptSetModuleMask(lpChannelNo : PLongInt; uMask : Dword) : DWord; stdcall;


//Verify interrupt mask of specified module
//======================================================
// *upMask: SCAN_END(1)
//        : FIFO_HALF_FULL(2)
//==================================================
function  AxaiInterruptGetModuleMask(lpChannelNo : PLongInt; upMask : PDWord) : DWord; stdcall;


//========== API group for setting and verifying of input module parameter =====
//Set the input voltage range in specified input channel
//======================================================
// AI4RB
// dMinVolt    : -10V/-5V/0V
// dMaxVolt    : 10V/5V/
//
// AI16Hx
// dMinVolt    : -10V Fix
// dMaxVolt    : 10V Fix
//==================================================
function AxaiSetRange (lChannelNo : LongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;


//Verify the input voltage range in specified input channel
//======================================================
// AI4RB
// *dpMinVolt    : -10V/-5V/0V
// *dpMaxVolt    : 10V/5V/
//
// AI16Hx
// *dpMaxVolt    : -10V Fix
// *dpMaxVolt    : 10V Fix
//==================================================
function AxaiGetRange (lChannelNo : LongInt; dpMinVolt : PDouble; dpMaxVolt : PDouble) : DWord; stdcall;


//Set the allowed input voltage range in specified multiple input Modules
//==================================================================================================//
// lModuleNo   : Analog Module Number
//
// RTEX AI16F
// Mode -5~+5  : dMinVolt = -5, dMaxVolt = +5
// Mode -10~+10: dMinVolt = -10, dMaxVolt = +10
//==================================================================================================//
function  AxaiSetRangeModule(lModuleNo : LongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;


//Verify the input voltage range in specified input Module
//==================================================================================================//
// lModuleNo   : Analog Module Number
//
// RTEX AI16F
// *dMinVolt   : -5V, -10V
// *dMaxVolt   : +5V, +10V
//==================================================================================================//
function  AxaiGetRangeModule(lModuleNo : LongInt; dpMinVolt : PDouble; dpMaxVolt : PDouble) : DWord; stdcall;



//Set the allowed input voltage range in specified multiple input channels
//======================================================
// AI4RB
// dMinVolt      : -10V/-5V/0V
// dMaxVolt      : 10V/5V/
//
// AI16Hx
// dMinVolt      : -10V Fix
// dMaxVolt      : 10V Fix
//==================================================
function AxaiSetMultiRange (lSize : LongInt; lpChannelNo : PLongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;


//Set trigger mode in the specified input module
//======================================================
// uTriggerMode  : NORMAL_MODE(1)
//               : TIMER_MODE(2)
//               : EXTERNAL_MODE(3)
//==================================================
function AxaiSetTriggerMode (lModuleNo : LongInt; uTriggerMode : DWord) : DWord; stdcall;


//Verify trigger mode in the specified input module
//======================================================
// *upTriggerMode: NORMAL_MODE(1)
//               : TIMER_MODE(2)
//               : EXTERNAL_MODE(3)
//==================================================
function AxaiGetTriggerMode (lModuleNo : LongInt; upTriggerMode : PDWord) : DWord; stdcall;


//Set offset of specified input module by mVolt (mV) unit. Max -100~100mVolt
//======================================================
// dMiliVolt    : -100 ~ 100
//==================================================
function AxaiSetModuleOffsetValue(lModuleNo : LongInt; dMiliVolt : Double) : DWord; stdcall;


//Verify offset value of specified input module. mVolt unit(mV)
//======================================================
// *dpMiliVolt  : -100 ~ 100
//==================================================
function AxaiGetModuleOffsetValue(lModuleNo : LongInt; dpMiliVolt : PDouble) : DWord; stdcall;


//========== Software Timer (Normal Trigger Mode) group ========================
//Software Trigger Mode API, Convert analog input value to A/D in the specified input channel by user , then return it in voltage value
function AxaiSwReadVoltage (lChannelNo : LongInt; dpVolt : PDouble) : DWord; stdcall;


//Software Trigger Mode API, Return analog input value in digit value to specified input channel
function AxaiSwReadDigit (lChannelNo : LongInt; upDigit : PDWord) : DWord; stdcall;


//Software Trigger Mode API, Return analog input value in voltage value to specified multiple input channels
function AxaiSwReadMultiVoltage (lSize : LongInt; lpChannelNo : PLongInt; dpVolt : PDouble) : DWord; stdcall;


//Software Trigger Mode API, Return analog input value in digit value to specified multiple input channels
function AxaiSwReadMultiDigit (lSize : LongInt; lpChannelNo : PLongInt; upDigit : PDWord) : DWord; stdcall;


//========== Hardware Timer (Timer Trigger Mode + External Trigger Mode) group =
//Hardware Trigger Mode API, Set setting value in order to use immediate mode in specified multiple channels
function AxaiHwSetMultiAccess (lSize : LongInt; lpChannelNo : PLongInt; lpWordSize : PLongInt) : DWord; stdcall;


//Hardware Trigger Mode API, Convert A/D as much as number of specified, then return the voltage value
function AxaiHwStartMultiAccess (dpBuffer : PDouble) : DWord; stdcall;


//Set sampling interval to specified module by frequency unit(Hz)
//==================================================================================================//
// dSampleFreq    : 10 ~ 100000
//==================================================================================================//
function AxaiHwSetSampleFreq (lModuleNo : LongInt; dSampleFreq : Double) : DWord; stdcall;


//Verify the setting value of sampling interval to specified module by frequency unit(Hz)
//==================================================================================================//
// *dpSampleFreq  : 10 ~ 100000
//==================================================================================================//
function AxaiHwGetSampleFreq (lModuleNo : LongInt; dpSampleFreq : PDouble) : DWord; stdcall;


//Set sampling interval to specified module by time unit (uSec)
//==================================================================================================//
// dSamplePeriod  : 100000 ~ 1000000000
//==================================================================================================//
function AxaiHwSetSamplePeriod (lModuleNo : LongInt; dSamplePeriod : Double) : DWord; stdcall;


//Verify setting value of sampling interval to specified module by time unit(uSec)
//==================================================================================================//
// *dpSamplePeriod: 100000 ~ 1000000000
//==================================================================================================//
function AxaiHwGetSamplePeriod (lModuleNo : LongInt; dpSamplePeriod : PDouble) : DWord; stdcall;


//Set control method when the buffer is full in specified input channel
//==================================================================================================//
// uFullMode      : NEW_DATA_KEEP(0)
//                : CURR_DATA_KEEP(1)
//==================================================================================================//
function AxaiHwSetBufferOverflowMode (lChannelNo : LongInt; uFullMode : DWord) : DWord; stdcall;


//Verify control method when the buffer is full in specified input channel
//==================================================================================================//
// *upFullMode    : NEW_DATA_KEEP(0)
//                : CURR_DATA_KEEP(1)
//==================================================================================================//
function AxaiHwGetBufferOverflowMode (lChannelNo : LongInt; upFullMode : PDWord) : DWord; stdcall;


//control method when the buffer is full in specified multiple input channels
//==================================================================================================//
// uFullMode      : NEW_DATA_KEEP(0)
//                : CURR_DATA_KEEP(1)
//==================================================================================================//
function AxaiHwSetMultiBufferOverflowMode (lSize : LongInt; lpChannelNo : PLongInt; uFullMode : DWord) : DWord; stdcall;


//Set the upper limit and lower limit of buffer in specified input channel
function AxaiHwSetLimit (lChannelNo : LongInt; lLowLimit : LongInt; lUpLimit : LongInt) : DWord; stdcall;


//Verify the upper limit and lower limit of buffer in specified input channel
function AxaiHwGetLimit (lChannelNo : LongInt; lpLowLimit : PLongInt; lpUpLimit : PLongInt) : DWord; stdcall;


//Set the upper limit and lower limit of buffer in multiple input channels
function AxaiHwSetMultiLimit (lSize : LongInt; lpChannelNo : PLongInt; lLowLimit : LongInt; lUpLimit : LongInt) : DWord; stdcall;


//Start A/D conversion using H/W timer in specified multiple channels
function AxaiHwStartMultiChannel (lSize : LongInt; lpChannelNo : PLongInt; lBuffSize : LongInt) : DWord; stdcall;


//Start A/D conversion using H/W timer in specified single channels
function AxaiHwStartSingleChannelAdc (lChannelNo : LongInt; lBuffSize : LongInt) : DWord; stdcall;


//Stop continuous signal A/D conversion used H/W timer.
function AxaiHwStopSingleChannelAdc (lChannelNo : LongInt) : DWord; stdcall;


//After starting of A/D conversion in specified multiple channels, manage filtering as much as specified and return into voltage
//==================================================================================================//
// lSize           : Number of input channels to use
// *lpChannelNo    : An array of channel numbers to use
// lFilterCount    : Number of data for filtering
// lBuffSize       : Number of buffers which are assigned to each channel
//==================================================================================================//
function AxaiHwStartMultiFilter (lSize : LongInt; lpChannelNo : PLongInt; lFilterCount : LongInt; lBuffSize : LongInt) : DWord; stdcall;


//Stop continuous signal A/D conversion used H/W timer
function AxaiHwStopMultiChannel (lModuleNo : LongInt) : DWord; stdcall;


//Inspect the numbers of data in memory buffer of specified input channel
function AxaiHwReadDataLength (lChannelNo : LongInt; lpDataLength : PLongInt) : DWord; stdcall;


//Read A/D conversion data used H/W timer in specified input channel by voltage value
function AxaiHwReadSampleVoltage (lChannelNo : LongInt; lSize : PLongInt; dpVolt : PDouble) : DWord; stdcall;


//Read A/D conversion data used H/W timer in specified input channel by digit value
function AxaiHwReadSampleDigit (lChannelNo : LongInt; lSize : PLongInt; upDigit : PDWord) : DWord; stdcall;


//========== API group of input module state check
//Inspect if there is no data in memory buffer of specified input channel
//==================================================================================================//
// *upEmpty   : FALSE(0)
//            : TRUE(1)
//==================================================================================================//
function AxaiHwIsBufferEmpty (lChannelNo : LongInt; upEmpty : PDWord) : DWord; stdcall;


//Inspect if the data is more than the upper limit specified in memory buffer of specified input channel
//==================================================================================================//
// *upUpper   : FALSE(0)
//            : TRUE(1)
//==================================================================================================//
function AxaiHwIsBufferUpper (lChannelNo : LongInt; upUpper : PDWord) : DWord; stdcall;


//Inspect if the data is less than the upper limit specified in memory buffer of specified input channel
//==================================================================================================//
// *upLower   : FALSE(0)
//            : TRUE(1)
//==================================================================================================//
function AxaiHwIsBufferLower (lChannelNo : LongInt; upLower : PDWord) : DWord; stdcall;

//==External Trigger Mode Funtion
//Start external trigger mode of the selected channels of specified input module.
//==================================================================================================//
// lSize           : Number of channels to use external trigger on specified input module
// *lpChannelPos   : Index of channels to use external trigger on specified input module
function AxaiExternalStartADC(lModuleNo : LongInt; lSize : LongInt; lpChannelPos : PLongInt) : DWord; stdcall;
//Stop external trigger mode of specified input module.
function AxaiExternalStopADC(lModuleNo : LongInt) : DWord; stdcall;
//Return FIFO status of specified input module
//==================================================================================================//
// *dwpStatus      : FIFO_DATA_EXIST(0)
//                 : FIFO_DATA_EMPTY(1)
//                 : FIFO_DATA_HALF(2)
//                 : FIFO_DATA_FULL(6)
//==================================================================================================//
function AxaiExternalReadFifoStatus(lModuleNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
//Read converted A/D value from external signal of specified input module.
// lSize           : Number of channels to read converted A/D value in specified input module
// *lpChannelPos   : Index of channels to read converted A/D value in specified input module
// lDataSize       : Number of maximum data to read converted A/D value by external trigger
// lBuffSize       : Size of externally allocated data buffer
// lStartDataPos   : Starting location of data buffer saving
// *dpVolt         : Two-demensional array pointer(for receiving value of converted to A/D)
// *lpRetDataSize  : Actually assigned number to data buffer(converted A/D value)
// *dwpStatus      : Return FIFO status when read converted A/D value from Fifo(H/W Buffer)
function AxaiExternalReadVoltage(lModuleNo : LongInt; lSize : LongInt; lpChannelPos : PLongInt; lDataSize : LongInt; lBuffSize : LongInt; lStartDataPos : LongInt; dpVolt : PDouble; lpRetDataSize : PLongInt; dwpStatus : PLongInt) : DWord; stdcall;



//========== API group of output module information search =====================
//Verify module number with specified output channel number
function AxaoInfoGetModuleNoOfChannelNo (lChannelNo : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;


//Verify entire number of channel of analog output module
function AxaoInfoGetChannelCount (lpChannelCount : PLongInt) : DWord; stdcall;


//========== API group for output module setting and verification ==============
//Set output voltage range in specified output channel
//======================================================
// AO4R
// dMinVolt : -10V/-5V/0V
// dMaxVolt : 10V/5V/
//
// AO2Hx
// dMinVolt : -10V Fix
// dMaxVolt : 10V Fix
//==================================================
function AxaoSetRange (lChannelNo : LongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;


//Verify output voltage range in specified output channel
//======================================================
// AO4R
// dMinVolt : -10V/-5V/0V
// dMaxVolt : 10V/5V/
//
// AO2Hx
// dMinVolt : -10V Fix
// dMaxVolt : 10V Fix
//==================================================
function AxaoGetRange (lChannelNo : LongInt; dpMinVolt : PDouble; dpMaxVolt : PDouble) : DWord; stdcall;


//Set output voltage range in specified multiple output channels
//======================================================
// AO4R
// dMinVolt : -10V/-5V/0V
// dMaxVolt : 10V/5V/
//
// AO2Hx
// dMinVolt : -10V Fix
// dMaxVolt : 10V Fix
//==================================================
function AxaoSetMultiRange (lSize : LongInt; lpChannelNo : PLongInt; dMinVolt : Double; dMaxVolt : Double) : DWord; stdcall;


//The Input voltage is output in specified output channel
function AxaoWriteVoltage (lChannelNo : LongInt; dVolt : Double) : DWord; stdcall;


//The Input voltage is output in specified multiple output channel
function AxaoWriteMultiVoltage (lSize : LongInt; lpChannelNo : PLongInt; dpVolt : PDouble) : DWord; stdcall;


//Verify voltage which is output in specified output channel
function AxaoReadVoltage (lChannelNo : LongInt; dpVolt : PDouble) : DWord; stdcall;


//Verify voltage which is output in specified multiple output channels
function AxaoReadMultiVoltage (lSize : LongInt; lpChannelNo : PLongInt; dpVolt : PDouble) : DWord; stdcall;

//============================ AXA User Define Pattern Generator ============================
// API function for setting 'Channel User Define Pattern Generator'
// Outputting pattern every time depending on AxaoPgSetUserInterval setting
// lLoopCnt       : '0'(Repeat input pattern infinitely), 'value' : Keep last pattern, After outputting input pattern for specified number of times
//                : (MAX : 60000)
// lPatternSize   : Number of input pattern(MAX : 8192)
function AxaoPgSetUserPatternGenerator (lChannelNo : LongInt; lLoopCnt : LongInt; lPatternSize : LongInt; dpPettern : PDouble) : DWord; stdcall;

// API function for getting 'user define pattern generator'
function AxaoPgGetUserPatternGenerator (lChannelNo : LongInt; lpLoopCnt : PLongInt; lpPatternSize : PLongInt; dpPettern : PDouble) : DWord; stdcall;

// API function for setting 'pattern generator interval' of corresponding channel
// Unit : us(Default resolution : 500uSec)
function AxaoPgSetUserInterval (lChannelNo : LongInt; dInterval : Double) : DWord; stdcall;

// API function for getting 'pattern generator interval' of corresponding channel
function AxaoPgGetUserInterval (lChannelNo : LongInt; dpInterval : PDouble) : DWord; stdcall;

// API function for getting 'Pattern Index / Loop Cnt' of corresponding channel
// In the case of status, following status can be included.
// lpIndexNum : The index of current user pattern
// lpLoopCnt : Number of currently running loop
// dwpInBusy : Driving status of Pattern Generator
function AxaoPgGetStatus (lChannelNo : LongInt; lpIndexNum : PLongInt; lpLoopCnt : PLongInt; upInBusy : PDWord) : DWord; stdcall;


// API function for start 'User Define Pattern Generator' of corresponding channel ('AO' output start)
// Inputting start channel number as an array
// Start pattern generator function simultaneously for input channel.
function AxaoPgSetUserStart (lpChannelNo : PLongInt; lSize : LongInt) : DWord; stdcall;


// API function for stopping 'User Define Pattern Generator' of corresponding channel ('AO' output stop)
// Output value is switched to 0 volt when output is stopped
function AxaoPgSetUserStop (lpChannelNo : PLongInt; lSize : LongInt) : DWord; stdcall;


// API function for clearing Pattern Data(Reset all areas to 0x00)
function AxaPgSetUserDataReset (lChannelNo : LongInt) : DWord; stdcall;


// API function for setting output status by each channel when specified output module network is broken
//===============================================================================================//
// lChannelNo  : Channel number(Distributed slave products only)
// dwSetValue  : Setting value
//             : 1 --> Analog Max
//             : 2 --> Analog MIN
//             : 3 --> User Vaule(Default user value : 0V, You can change this value by 'AxaoSetNetworkErrorUserValue()')
//             : 4 --> Analog 0 V
//===============================================================================================//
function AxaoSetNetworkErrorAct (lChannelNo : LongInt; uSetValue : DWord) : DWord; stdcall;

// API function for setting output status in bytes when specified output module network is broken
//===============================================================================================//
// lChannelNo  : Channel number(Distributed slave products only)
// dVolt       : Analog output voltage(User defined value)
//===============================================================================================//
function AxaoSetNetworkErrorUserValue (lChannelNo : LongInt; dVolt : Double) : DWord; stdcall;


implementation

const

    dll_name    = 'AXL.dll';
    function AxaInfoIsAIOModule; external dll_name name 'AxaInfoIsAIOModule';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxaInfoGetModuleCount; external dll_name name 'AxaInfoGetModuleCount';
    function AxaInfoGetInputCount; external dll_name name 'AxaInfoGetInputCount';
    function AxaInfoGetOutputCount; external dll_name name 'AxaInfoGetOutputCount';
    function AxaInfoGetChannelNoOfModuleNo; external dll_name name 'AxaInfoGetChannelNoOfModuleNo';
    function AxaInfoGetChannelNoAdcOfModuleNo; external dll_name name 'AxaInfoGetChannelNoAdcOfModuleNo';
    function AxaInfoGetChannelNoDacOfModuleNo; external dll_name name 'AxaInfoGetChannelNoDacOfModuleNo';
    function AxaInfoGetModule; external dll_name name 'AxaInfoGetModule';
    function AxaInfoGetModuleEx; external dll_name name 'AxaInfoGetModuleEx';
    function AxaInfoGetModuleStatus; external dll_name name 'AxaInfoGetModuleStatus';
    function AxaiInfoGetModuleNoOfChannelNo; external dll_name name 'AxaiInfoGetModuleNoOfChannelNo';
    function AxaiInfoGetChannelCount; external dll_name name 'AxaiInfoGetChannelCount';
    function AxaiEventSetChannel; external dll_name name 'AxaiEventSetChannel';
    function AxaiEventSetChannelEnable; external dll_name name 'AxaiEventSetChannelEnable';
    function AxaiEventGetChannelEnable; external dll_name name 'AxaiEventGetChannelEnable';
    function AxaiEventSetMultiChannelEnable; external dll_name name 'AxaiEventSetMultiChannelEnable';
    function AxaiEventSetChannelMask; external dll_name name 'AxaiEventSetChannelMask';
    function AxaiEventGetChannelMask; external dll_name name 'AxaiEventGetChannelMask';
    function AxaiEventSetMultiChannelMask; external dll_name name 'AxaiEventSetMultiChannelMask';
    function AxaiEventRead; external dll_name name 'AxaiEventRead';
    function AxaiInterruptSetModuleMask; external dll_name name 'AxaiInterruptSetModuleMask';
    function AxaiInterruptGetModuleMask; external dll_name name 'AxaiInterruptGetModuleMask';
    function AxaiSetRange; external dll_name name 'AxaiSetRange';
    function AxaiGetRange; external dll_name name 'AxaiGetRange';
    function AxaiSetRangeModule; external dll_name name 'AxaiSetRangeModule';
    function AxaiGetRangeModule; external dll_name name 'AxaiGetRangeModule';
    function AxaiSetMultiRange; external dll_name name 'AxaiSetMultiRange';
    function AxaiSetTriggerMode; external dll_name name 'AxaiSetTriggerMode';
    function AxaiGetTriggerMode; external dll_name name 'AxaiGetTriggerMode';
    function AxaiSetModuleOffsetValue; external dll_name name 'AxaiSetModuleOffsetValue';
    function AxaiGetModuleOffsetValue; external dll_name name 'AxaiGetModuleOffsetValue';
    function AxaiSwReadVoltage; external dll_name name 'AxaiSwReadVoltage';
    function AxaiSwReadDigit; external dll_name name 'AxaiSwReadDigit';
    function AxaiSwReadMultiVoltage; external dll_name name 'AxaiSwReadMultiVoltage';
    function AxaiSwReadMultiDigit; external dll_name name 'AxaiSwReadMultiDigit';
    function AxaiHwSetMultiAccess; external dll_name name 'AxaiHwSetMultiAccess';
    function AxaiHwStartMultiAccess; external dll_name name 'AxaiHwStartMultiAccess';
    function AxaiHwSetSampleFreq; external dll_name name 'AxaiHwSetSampleFreq';
    function AxaiHwGetSampleFreq; external dll_name name 'AxaiHwGetSampleFreq';
    function AxaiHwSetSamplePeriod; external dll_name name 'AxaiHwSetSamplePeriod';
    function AxaiHwGetSamplePeriod; external dll_name name 'AxaiHwGetSamplePeriod';
    function AxaiHwSetBufferOverflowMode; external dll_name name 'AxaiHwSetBufferOverflowMode';
    function AxaiHwGetBufferOverflowMode; external dll_name name 'AxaiHwGetBufferOverflowMode';
    function AxaiHwSetMultiBufferOverflowMode; external dll_name name 'AxaiHwSetMultiBufferOverflowMode';
    function AxaiHwSetLimit; external dll_name name 'AxaiHwSetLimit';
    function AxaiHwGetLimit; external dll_name name 'AxaiHwGetLimit';
    function AxaiHwSetMultiLimit; external dll_name name 'AxaiHwSetMultiLimit';
    function AxaiHwStartMultiChannel; external dll_name name 'AxaiHwStartMultiChannel';
    function AxaiHwStartSingleChannelAdc; external dll_name name 'AxaiHwStartSingleChannelAdc';
    function AxaiHwStopSingleChannelAdc; external dll_name name 'AxaiHwStopSingleChannelAdc';
    function AxaiHwStartMultiFilter; external dll_name name 'AxaiHwStartMultiFilter';
    function AxaiHwStopMultiChannel; external dll_name name 'AxaiHwStopMultiChannel';
    function AxaiHwReadDataLength; external dll_name name 'AxaiHwReadDataLength';
    function AxaiHwReadSampleVoltage; external dll_name name 'AxaiHwReadSampleVoltage';
    function AxaiHwReadSampleDigit; external dll_name name 'AxaiHwReadSampleDigit';
    function AxaiHwIsBufferEmpty; external dll_name name 'AxaiHwIsBufferEmpty';
    function AxaiHwIsBufferUpper; external dll_name name 'AxaiHwIsBufferUpper';
    function AxaiHwIsBufferLower; external dll_name name 'AxaiHwIsBufferLower';
    function AxaiExternalStartADC; external dll_name name 'AxaiExternalStartADC';
    function AxaiExternalStopADC; external dll_name name 'AxaiExternalStopADC';
    function AxaiExternalReadFifoStatus; external dll_name name 'AxaiExternalReadFifoStatus';
    function AxaiExternalReadVoltage; external dll_name name 'AxaiExternalReadVoltage';
    function AxaoInfoGetModuleNoOfChannelNo; external dll_name name 'AxaoInfoGetModuleNoOfChannelNo';
    function AxaoInfoGetChannelCount; external dll_name name 'AxaoInfoGetChannelCount';
    function AxaoSetRange; external dll_name name 'AxaoSetRange';
    function AxaoGetRange; external dll_name name 'AxaoGetRange';
    function AxaoSetMultiRange; external dll_name name 'AxaoSetMultiRange';
    function AxaoWriteVoltage; external dll_name name 'AxaoWriteVoltage';
    function AxaoWriteMultiVoltage; external dll_name name 'AxaoWriteMultiVoltage';
    function AxaoReadVoltage; external dll_name name 'AxaoReadVoltage';
    function AxaoReadMultiVoltage; external dll_name name 'AxaoReadMultiVoltage';
    function AxaoPgSetUserPatternGenerator; external dll_name name 'AxaoPgSetUserPatternGenerator';
    function AxaoPgGetUserPatternGenerator; external dll_name name 'AxaoPgGetUserPatternGenerator';
    function AxaoPgSetUserInterval; external dll_name name 'AxaoPgSetUserInterval';
    function AxaoPgGetUserInterval; external dll_name name 'AxaoPgGetUserInterval';
    function AxaoPgGetStatus; external dll_name name 'AxaoPgGetStatus';
    function AxaoPgSetUserStart; external dll_name name 'AxaoPgSetUserStart';
    function AxaoPgSetUserStop; external dll_name name 'AxaoPgSetUserStop';
    function AxaPgSetUserDataReset; external dll_name name 'AxaPgSetUserDataReset';
    function AxaoSetNetworkErrorAct; external dll_name name 'AxaoSetNetworkErrorAct';
    function AxaoSetNetworkErrorUserValue; external dll_name name 'AxaoSetNetworkErrorUserValue';
    function AxaInfoIsAIOModule; external dll_name name 'AxaInfoIsAIOModule';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxaInfoGetModuleCount; external dll_name name 'AxaInfoGetModuleCount';
    function AxaInfoGetInputCount; external dll_name name 'AxaInfoGetInputCount';
    function AxaInfoGetOutputCount; external dll_name name 'AxaInfoGetOutputCount';
    function AxaInfoGetChannelNoOfModuleNo; external dll_name name 'AxaInfoGetChannelNoOfModuleNo';
    function AxaInfoGetChannelNoAdcOfModuleNo; external dll_name name 'AxaInfoGetChannelNoAdcOfModuleNo';
    function AxaInfoGetChannelNoDacOfModuleNo; external dll_name name 'AxaInfoGetChannelNoDacOfModuleNo';
    function AxaInfoGetModule; external dll_name name 'AxaInfoGetModule';
    function AxaInfoGetModuleEx; external dll_name name 'AxaInfoGetModuleEx';
    function AxaInfoGetModuleStatus; external dll_name name 'AxaInfoGetModuleStatus';
    function AxaiInfoGetModuleNoOfChannelNo; external dll_name name 'AxaiInfoGetModuleNoOfChannelNo';
    function AxaiInfoGetChannelCount; external dll_name name 'AxaiInfoGetChannelCount';
    function AxaiEventSetChannel; external dll_name name 'AxaiEventSetChannel';
    function AxaiEventSetChannelEnable; external dll_name name 'AxaiEventSetChannelEnable';
    function AxaiEventGetChannelEnable; external dll_name name 'AxaiEventGetChannelEnable';
    function AxaiEventSetMultiChannelEnable; external dll_name name 'AxaiEventSetMultiChannelEnable';
    function AxaiEventSetChannelMask; external dll_name name 'AxaiEventSetChannelMask';
    function AxaiEventGetChannelMask; external dll_name name 'AxaiEventGetChannelMask';
    function AxaiEventSetMultiChannelMask; external dll_name name 'AxaiEventSetMultiChannelMask';
    function AxaiEventRead; external dll_name name 'AxaiEventRead';
    function AxaiInterruptSetModuleMask; external dll_name name 'AxaiInterruptSetModuleMask';
    function AxaiInterruptGetModuleMask; external dll_name name 'AxaiInterruptGetModuleMask';
    function AxaiSetRange; external dll_name name 'AxaiSetRange';
    function AxaiGetRange; external dll_name name 'AxaiGetRange';
    function AxaiSetRangeModule; external dll_name name 'AxaiSetRangeModule';
    function AxaiGetRangeModule; external dll_name name 'AxaiGetRangeModule';
    function AxaiSetMultiRange; external dll_name name 'AxaiSetMultiRange';
    function AxaiSetTriggerMode; external dll_name name 'AxaiSetTriggerMode';
    function AxaiGetTriggerMode; external dll_name name 'AxaiGetTriggerMode';
    function AxaiSetModuleOffsetValue; external dll_name name 'AxaiSetModuleOffsetValue';
    function AxaiGetModuleOffsetValue; external dll_name name 'AxaiGetModuleOffsetValue';
    function AxaiSwReadVoltage; external dll_name name 'AxaiSwReadVoltage';
    function AxaiSwReadDigit; external dll_name name 'AxaiSwReadDigit';
    function AxaiSwReadMultiVoltage; external dll_name name 'AxaiSwReadMultiVoltage';
    function AxaiSwReadMultiDigit; external dll_name name 'AxaiSwReadMultiDigit';
    function AxaiHwSetMultiAccess; external dll_name name 'AxaiHwSetMultiAccess';
    function AxaiHwStartMultiAccess; external dll_name name 'AxaiHwStartMultiAccess';
    function AxaiHwSetSampleFreq; external dll_name name 'AxaiHwSetSampleFreq';
    function AxaiHwGetSampleFreq; external dll_name name 'AxaiHwGetSampleFreq';
    function AxaiHwSetSamplePeriod; external dll_name name 'AxaiHwSetSamplePeriod';
    function AxaiHwGetSamplePeriod; external dll_name name 'AxaiHwGetSamplePeriod';
    function AxaiHwSetBufferOverflowMode; external dll_name name 'AxaiHwSetBufferOverflowMode';
    function AxaiHwGetBufferOverflowMode; external dll_name name 'AxaiHwGetBufferOverflowMode';
    function AxaiHwSetMultiBufferOverflowMode; external dll_name name 'AxaiHwSetMultiBufferOverflowMode';
    function AxaiHwSetLimit; external dll_name name 'AxaiHwSetLimit';
    function AxaiHwGetLimit; external dll_name name 'AxaiHwGetLimit';
    function AxaiHwSetMultiLimit; external dll_name name 'AxaiHwSetMultiLimit';
    function AxaiHwStartMultiChannel; external dll_name name 'AxaiHwStartMultiChannel';
    function AxaiHwStartSingleChannelAdc; external dll_name name 'AxaiHwStartSingleChannelAdc';
    function AxaiHwStopSingleChannelAdc; external dll_name name 'AxaiHwStopSingleChannelAdc';
    function AxaiHwStartMultiFilter; external dll_name name 'AxaiHwStartMultiFilter';
    function AxaiHwStopMultiChannel; external dll_name name 'AxaiHwStopMultiChannel';
    function AxaiHwReadDataLength; external dll_name name 'AxaiHwReadDataLength';
    function AxaiHwReadSampleVoltage; external dll_name name 'AxaiHwReadSampleVoltage';
    function AxaiHwReadSampleDigit; external dll_name name 'AxaiHwReadSampleDigit';
    function AxaiHwIsBufferEmpty; external dll_name name 'AxaiHwIsBufferEmpty';
    function AxaiHwIsBufferUpper; external dll_name name 'AxaiHwIsBufferUpper';
    function AxaiHwIsBufferLower; external dll_name name 'AxaiHwIsBufferLower';
    function AxaiExternalStartADC; external dll_name name 'AxaiExternalStartADC';
    function AxaiExternalStopADC; external dll_name name 'AxaiExternalStopADC';
    function AxaiExternalReadFifoStatus; external dll_name name 'AxaiExternalReadFifoStatus';
    function AxaiExternalReadVoltage; external dll_name name 'AxaiExternalReadVoltage';
    function AxaoInfoGetModuleNoOfChannelNo; external dll_name name 'AxaoInfoGetModuleNoOfChannelNo';
    function AxaoInfoGetChannelCount; external dll_name name 'AxaoInfoGetChannelCount';
    function AxaoSetRange; external dll_name name 'AxaoSetRange';
    function AxaoGetRange; external dll_name name 'AxaoGetRange';
    function AxaoSetMultiRange; external dll_name name 'AxaoSetMultiRange';
    function AxaoWriteVoltage; external dll_name name 'AxaoWriteVoltage';
    function AxaoWriteMultiVoltage; external dll_name name 'AxaoWriteMultiVoltage';
    function AxaoReadVoltage; external dll_name name 'AxaoReadVoltage';
    function AxaoReadMultiVoltage; external dll_name name 'AxaoReadMultiVoltage';
    function AxaoPgSetUserPatternGenerator; external dll_name name 'AxaoPgSetUserPatternGenerator';
    function AxaoPgGetUserPatternGenerator; external dll_name name 'AxaoPgGetUserPatternGenerator';
    function AxaoPgSetUserInterval; external dll_name name 'AxaoPgSetUserInterval';
    function AxaoPgGetUserInterval; external dll_name name 'AxaoPgGetUserInterval';
    function AxaoPgGetStatus; external dll_name name 'AxaoPgGetStatus';
    function AxaoPgSetUserStart; external dll_name name 'AxaoPgSetUserStart';
    function AxaoPgSetUserStop; external dll_name name 'AxaoPgSetUserStop';
    function AxaPgSetUserDataReset; external dll_name name 'AxaPgSetUserDataReset';
    function AxaoSetNetworkErrorAct; external dll_name name 'AxaoSetNetworkErrorAct';
    function AxaoSetNetworkErrorUserValue; external dll_name name 'AxaoSetNetworkErrorUserValue';
    function AxaInfoIsAIOModule; external dll_name name 'AxaInfoIsAIOModule';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxaInfoGetModuleCount; external dll_name name 'AxaInfoGetModuleCount';
    function AxaInfoGetInputCount; external dll_name name 'AxaInfoGetInputCount';
    function AxaInfoGetOutputCount; external dll_name name 'AxaInfoGetOutputCount';
    function AxaInfoGetChannelNoOfModuleNo; external dll_name name 'AxaInfoGetChannelNoOfModuleNo';
    function AxaInfoGetChannelNoAdcOfModuleNo; external dll_name name 'AxaInfoGetChannelNoAdcOfModuleNo';
    function AxaInfoGetChannelNoDacOfModuleNo; external dll_name name 'AxaInfoGetChannelNoDacOfModuleNo';
    function AxaInfoGetModule; external dll_name name 'AxaInfoGetModule';
    function AxaInfoGetModuleEx; external dll_name name 'AxaInfoGetModuleEx';
    function AxaInfoGetModuleStatus; external dll_name name 'AxaInfoGetModuleStatus';
    function AxaiInfoGetModuleNoOfChannelNo; external dll_name name 'AxaiInfoGetModuleNoOfChannelNo';
    function AxaiInfoGetChannelCount; external dll_name name 'AxaiInfoGetChannelCount';
    function AxaiEventSetChannel; external dll_name name 'AxaiEventSetChannel';
    function AxaiEventSetChannelEnable; external dll_name name 'AxaiEventSetChannelEnable';
    function AxaiEventGetChannelEnable; external dll_name name 'AxaiEventGetChannelEnable';
    function AxaiEventSetMultiChannelEnable; external dll_name name 'AxaiEventSetMultiChannelEnable';
    function AxaiEventSetChannelMask; external dll_name name 'AxaiEventSetChannelMask';
    function AxaiEventGetChannelMask; external dll_name name 'AxaiEventGetChannelMask';
    function AxaiEventSetMultiChannelMask; external dll_name name 'AxaiEventSetMultiChannelMask';
    function AxaiEventRead; external dll_name name 'AxaiEventRead';
    function AxaiInterruptSetModuleMask; external dll_name name 'AxaiInterruptSetModuleMask';
    function AxaiInterruptGetModuleMask; external dll_name name 'AxaiInterruptGetModuleMask';
    function AxaiSetRange; external dll_name name 'AxaiSetRange';
    function AxaiGetRange; external dll_name name 'AxaiGetRange';
    function AxaiSetRangeModule; external dll_name name 'AxaiSetRangeModule';
    function AxaiGetRangeModule; external dll_name name 'AxaiGetRangeModule';
    function AxaiSetMultiRange; external dll_name name 'AxaiSetMultiRange';
    function AxaiSetTriggerMode; external dll_name name 'AxaiSetTriggerMode';
    function AxaiGetTriggerMode; external dll_name name 'AxaiGetTriggerMode';
    function AxaiSetModuleOffsetValue; external dll_name name 'AxaiSetModuleOffsetValue';
    function AxaiGetModuleOffsetValue; external dll_name name 'AxaiGetModuleOffsetValue';
    function AxaiSwReadVoltage; external dll_name name 'AxaiSwReadVoltage';
    function AxaiSwReadDigit; external dll_name name 'AxaiSwReadDigit';
    function AxaiSwReadMultiVoltage; external dll_name name 'AxaiSwReadMultiVoltage';
    function AxaiSwReadMultiDigit; external dll_name name 'AxaiSwReadMultiDigit';
    function AxaiHwSetMultiAccess; external dll_name name 'AxaiHwSetMultiAccess';
    function AxaiHwStartMultiAccess; external dll_name name 'AxaiHwStartMultiAccess';
    function AxaiHwSetSampleFreq; external dll_name name 'AxaiHwSetSampleFreq';
    function AxaiHwGetSampleFreq; external dll_name name 'AxaiHwGetSampleFreq';
    function AxaiHwSetSamplePeriod; external dll_name name 'AxaiHwSetSamplePeriod';
    function AxaiHwGetSamplePeriod; external dll_name name 'AxaiHwGetSamplePeriod';
    function AxaiHwSetBufferOverflowMode; external dll_name name 'AxaiHwSetBufferOverflowMode';
    function AxaiHwGetBufferOverflowMode; external dll_name name 'AxaiHwGetBufferOverflowMode';
    function AxaiHwSetMultiBufferOverflowMode; external dll_name name 'AxaiHwSetMultiBufferOverflowMode';
    function AxaiHwSetLimit; external dll_name name 'AxaiHwSetLimit';
    function AxaiHwGetLimit; external dll_name name 'AxaiHwGetLimit';
    function AxaiHwSetMultiLimit; external dll_name name 'AxaiHwSetMultiLimit';
    function AxaiHwStartMultiChannel; external dll_name name 'AxaiHwStartMultiChannel';
    function AxaiHwStartSingleChannelAdc; external dll_name name 'AxaiHwStartSingleChannelAdc';
    function AxaiHwStopSingleChannelAdc; external dll_name name 'AxaiHwStopSingleChannelAdc';
    function AxaiHwStartMultiFilter; external dll_name name 'AxaiHwStartMultiFilter';
    function AxaiHwStopMultiChannel; external dll_name name 'AxaiHwStopMultiChannel';
    function AxaiHwReadDataLength; external dll_name name 'AxaiHwReadDataLength';
    function AxaiHwReadSampleVoltage; external dll_name name 'AxaiHwReadSampleVoltage';
    function AxaiHwReadSampleDigit; external dll_name name 'AxaiHwReadSampleDigit';
    function AxaiHwIsBufferEmpty; external dll_name name 'AxaiHwIsBufferEmpty';
    function AxaiHwIsBufferUpper; external dll_name name 'AxaiHwIsBufferUpper';
    function AxaiHwIsBufferLower; external dll_name name 'AxaiHwIsBufferLower';
    function AxaiExternalStartADC; external dll_name name 'AxaiExternalStartADC';
    function AxaiExternalStopADC; external dll_name name 'AxaiExternalStopADC';
    function AxaiExternalReadFifoStatus; external dll_name name 'AxaiExternalReadFifoStatus';
    function AxaiExternalReadVoltage; external dll_name name 'AxaiExternalReadVoltage';
    function AxaoInfoGetModuleNoOfChannelNo; external dll_name name 'AxaoInfoGetModuleNoOfChannelNo';
    function AxaoInfoGetChannelCount; external dll_name name 'AxaoInfoGetChannelCount';
    function AxaoSetRange; external dll_name name 'AxaoSetRange';
    function AxaoGetRange; external dll_name name 'AxaoGetRange';
    function AxaoSetMultiRange; external dll_name name 'AxaoSetMultiRange';
    function AxaoWriteVoltage; external dll_name name 'AxaoWriteVoltage';
    function AxaoWriteMultiVoltage; external dll_name name 'AxaoWriteMultiVoltage';
    function AxaoReadVoltage; external dll_name name 'AxaoReadVoltage';
    function AxaoReadMultiVoltage; external dll_name name 'AxaoReadMultiVoltage';
    function AxaoPgSetUserPatternGenerator; external dll_name name 'AxaoPgSetUserPatternGenerator';
    function AxaoPgGetUserPatternGenerator; external dll_name name 'AxaoPgGetUserPatternGenerator';
    function AxaoPgSetUserInterval; external dll_name name 'AxaoPgSetUserInterval';
    function AxaoPgGetUserInterval; external dll_name name 'AxaoPgGetUserInterval';
    function AxaoPgGetStatus; external dll_name name 'AxaoPgGetStatus';
    function AxaoPgSetUserStart; external dll_name name 'AxaoPgSetUserStart';
    function AxaoPgSetUserStop; external dll_name name 'AxaoPgSetUserStop';
    function AxaPgSetUserDataReset; external dll_name name 'AxaPgSetUserDataReset';
    function AxaoSetNetworkErrorAct; external dll_name name 'AxaoSetNetworkErrorAct';
    function AxaoSetNetworkErrorUserValue; external dll_name name 'AxaoSetNetworkErrorUserValue';
    function AxaInfoIsAIOModule; external dll_name name 'AxaInfoIsAIOModule';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxaInfoGetModuleCount; external dll_name name 'AxaInfoGetModuleCount';
    function AxaInfoGetInputCount; external dll_name name 'AxaInfoGetInputCount';
    function AxaInfoGetOutputCount; external dll_name name 'AxaInfoGetOutputCount';
    function AxaInfoGetChannelNoOfModuleNo; external dll_name name 'AxaInfoGetChannelNoOfModuleNo';
    function AxaInfoGetChannelNoAdcOfModuleNo; external dll_name name 'AxaInfoGetChannelNoAdcOfModuleNo';
    function AxaInfoGetChannelNoDacOfModuleNo; external dll_name name 'AxaInfoGetChannelNoDacOfModuleNo';
    function AxaInfoGetModule; external dll_name name 'AxaInfoGetModule';
    function AxaInfoGetModuleEx; external dll_name name 'AxaInfoGetModuleEx';
    function AxaInfoGetModuleStatus; external dll_name name 'AxaInfoGetModuleStatus';
    function AxaiInfoGetModuleNoOfChannelNo; external dll_name name 'AxaiInfoGetModuleNoOfChannelNo';
    function AxaiInfoGetChannelCount; external dll_name name 'AxaiInfoGetChannelCount';
    function AxaiEventSetChannel; external dll_name name 'AxaiEventSetChannel';
    function AxaiEventSetChannelEnable; external dll_name name 'AxaiEventSetChannelEnable';
    function AxaiEventGetChannelEnable; external dll_name name 'AxaiEventGetChannelEnable';
    function AxaiEventSetMultiChannelEnable; external dll_name name 'AxaiEventSetMultiChannelEnable';
    function AxaiEventSetChannelMask; external dll_name name 'AxaiEventSetChannelMask';
    function AxaiEventGetChannelMask; external dll_name name 'AxaiEventGetChannelMask';
    function AxaiEventSetMultiChannelMask; external dll_name name 'AxaiEventSetMultiChannelMask';
    function AxaiEventRead; external dll_name name 'AxaiEventRead';
    function AxaiInterruptSetModuleMask; external dll_name name 'AxaiInterruptSetModuleMask';
    function AxaiInterruptGetModuleMask; external dll_name name 'AxaiInterruptGetModuleMask';
    function AxaiSetRange; external dll_name name 'AxaiSetRange';
    function AxaiGetRange; external dll_name name 'AxaiGetRange';
    function AxaiSetRangeModule; external dll_name name 'AxaiSetRangeModule';
    function AxaiGetRangeModule; external dll_name name 'AxaiGetRangeModule';
    function AxaiSetMultiRange; external dll_name name 'AxaiSetMultiRange';
    function AxaiSetTriggerMode; external dll_name name 'AxaiSetTriggerMode';
    function AxaiGetTriggerMode; external dll_name name 'AxaiGetTriggerMode';
    function AxaiSetModuleOffsetValue; external dll_name name 'AxaiSetModuleOffsetValue';
    function AxaiGetModuleOffsetValue; external dll_name name 'AxaiGetModuleOffsetValue';
    function AxaiSwReadVoltage; external dll_name name 'AxaiSwReadVoltage';
    function AxaiSwReadDigit; external dll_name name 'AxaiSwReadDigit';
    function AxaiSwReadMultiVoltage; external dll_name name 'AxaiSwReadMultiVoltage';
    function AxaiSwReadMultiDigit; external dll_name name 'AxaiSwReadMultiDigit';
    function AxaiHwSetMultiAccess; external dll_name name 'AxaiHwSetMultiAccess';
    function AxaiHwStartMultiAccess; external dll_name name 'AxaiHwStartMultiAccess';
    function AxaiHwSetSampleFreq; external dll_name name 'AxaiHwSetSampleFreq';
    function AxaiHwGetSampleFreq; external dll_name name 'AxaiHwGetSampleFreq';
    function AxaiHwSetSamplePeriod; external dll_name name 'AxaiHwSetSamplePeriod';
    function AxaiHwGetSamplePeriod; external dll_name name 'AxaiHwGetSamplePeriod';
    function AxaiHwSetBufferOverflowMode; external dll_name name 'AxaiHwSetBufferOverflowMode';
    function AxaiHwGetBufferOverflowMode; external dll_name name 'AxaiHwGetBufferOverflowMode';
    function AxaiHwSetMultiBufferOverflowMode; external dll_name name 'AxaiHwSetMultiBufferOverflowMode';
    function AxaiHwSetLimit; external dll_name name 'AxaiHwSetLimit';
    function AxaiHwGetLimit; external dll_name name 'AxaiHwGetLimit';
    function AxaiHwSetMultiLimit; external dll_name name 'AxaiHwSetMultiLimit';
    function AxaiHwStartMultiChannel; external dll_name name 'AxaiHwStartMultiChannel';
    function AxaiHwStartSingleChannelAdc; external dll_name name 'AxaiHwStartSingleChannelAdc';
    function AxaiHwStopSingleChannelAdc; external dll_name name 'AxaiHwStopSingleChannelAdc';
    function AxaiHwStartMultiFilter; external dll_name name 'AxaiHwStartMultiFilter';
    function AxaiHwStopMultiChannel; external dll_name name 'AxaiHwStopMultiChannel';
    function AxaiHwReadDataLength; external dll_name name 'AxaiHwReadDataLength';
    function AxaiHwReadSampleVoltage; external dll_name name 'AxaiHwReadSampleVoltage';
    function AxaiHwReadSampleDigit; external dll_name name 'AxaiHwReadSampleDigit';
    function AxaiHwIsBufferEmpty; external dll_name name 'AxaiHwIsBufferEmpty';
    function AxaiHwIsBufferUpper; external dll_name name 'AxaiHwIsBufferUpper';
    function AxaiHwIsBufferLower; external dll_name name 'AxaiHwIsBufferLower';
    function AxaiExternalStartADC; external dll_name name 'AxaiExternalStartADC';
    function AxaiExternalStopADC; external dll_name name 'AxaiExternalStopADC';
    function AxaiExternalReadFifoStatus; external dll_name name 'AxaiExternalReadFifoStatus';
    function AxaiExternalReadVoltage; external dll_name name 'AxaiExternalReadVoltage';
    function AxaoInfoGetModuleNoOfChannelNo; external dll_name name 'AxaoInfoGetModuleNoOfChannelNo';
    function AxaoInfoGetChannelCount; external dll_name name 'AxaoInfoGetChannelCount';
    function AxaoSetRange; external dll_name name 'AxaoSetRange';
    function AxaoGetRange; external dll_name name 'AxaoGetRange';
    function AxaoSetMultiRange; external dll_name name 'AxaoSetMultiRange';
    function AxaoWriteVoltage; external dll_name name 'AxaoWriteVoltage';
    function AxaoWriteMultiVoltage; external dll_name name 'AxaoWriteMultiVoltage';
    function AxaoReadVoltage; external dll_name name 'AxaoReadVoltage';
    function AxaoReadMultiVoltage; external dll_name name 'AxaoReadMultiVoltage';
    function AxaoPgSetUserPatternGenerator; external dll_name name 'AxaoPgSetUserPatternGenerator';
    function AxaoPgGetUserPatternGenerator; external dll_name name 'AxaoPgGetUserPatternGenerator';
    function AxaoPgSetUserInterval; external dll_name name 'AxaoPgSetUserInterval';
    function AxaoPgGetUserInterval; external dll_name name 'AxaoPgGetUserInterval';
    function AxaoPgGetStatus; external dll_name name 'AxaoPgGetStatus';
    function AxaoPgSetUserStart; external dll_name name 'AxaoPgSetUserStart';
    function AxaoPgSetUserStop; external dll_name name 'AxaoPgSetUserStop';
    function AxaPgSetUserDataReset; external dll_name name 'AxaPgSetUserDataReset';
    function AxaoSetNetworkErrorAct; external dll_name name 'AxaoSetNetworkErrorAct';
    function AxaoSetNetworkErrorUserValue; external dll_name name 'AxaoSetNetworkErrorUserValue';
    function AxaInfoIsAIOModule; external dll_name name 'AxaInfoIsAIOModule';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxaInfoGetModuleCount; external dll_name name 'AxaInfoGetModuleCount';
    function AxaInfoGetInputCount; external dll_name name 'AxaInfoGetInputCount';
    function AxaInfoGetOutputCount; external dll_name name 'AxaInfoGetOutputCount';
    function AxaInfoGetChannelNoOfModuleNo; external dll_name name 'AxaInfoGetChannelNoOfModuleNo';
    function AxaInfoGetChannelNoAdcOfModuleNo; external dll_name name 'AxaInfoGetChannelNoAdcOfModuleNo';
    function AxaInfoGetChannelNoDacOfModuleNo; external dll_name name 'AxaInfoGetChannelNoDacOfModuleNo';
    function AxaInfoGetModule; external dll_name name 'AxaInfoGetModule';
    function AxaInfoGetModuleEx; external dll_name name 'AxaInfoGetModuleEx';
    function AxaInfoGetModuleStatus; external dll_name name 'AxaInfoGetModuleStatus';
    function AxaiInfoGetModuleNoOfChannelNo; external dll_name name 'AxaiInfoGetModuleNoOfChannelNo';
    function AxaiInfoGetChannelCount; external dll_name name 'AxaiInfoGetChannelCount';
    function AxaiEventSetChannel; external dll_name name 'AxaiEventSetChannel';
    function AxaiEventSetChannelEnable; external dll_name name 'AxaiEventSetChannelEnable';
    function AxaiEventGetChannelEnable; external dll_name name 'AxaiEventGetChannelEnable';
    function AxaiEventSetMultiChannelEnable; external dll_name name 'AxaiEventSetMultiChannelEnable';
    function AxaiEventSetChannelMask; external dll_name name 'AxaiEventSetChannelMask';
    function AxaiEventGetChannelMask; external dll_name name 'AxaiEventGetChannelMask';
    function AxaiEventSetMultiChannelMask; external dll_name name 'AxaiEventSetMultiChannelMask';
    function AxaiEventRead; external dll_name name 'AxaiEventRead';
    function AxaiInterruptSetModuleMask; external dll_name name 'AxaiInterruptSetModuleMask';
    function AxaiInterruptGetModuleMask; external dll_name name 'AxaiInterruptGetModuleMask';
    function AxaiSetRange; external dll_name name 'AxaiSetRange';
    function AxaiGetRange; external dll_name name 'AxaiGetRange';
    function AxaiSetRangeModule; external dll_name name 'AxaiSetRangeModule';
    function AxaiGetRangeModule; external dll_name name 'AxaiGetRangeModule';
    function AxaiSetMultiRange; external dll_name name 'AxaiSetMultiRange';
    function AxaiSetTriggerMode; external dll_name name 'AxaiSetTriggerMode';
    function AxaiGetTriggerMode; external dll_name name 'AxaiGetTriggerMode';
    function AxaiSetModuleOffsetValue; external dll_name name 'AxaiSetModuleOffsetValue';
    function AxaiGetModuleOffsetValue; external dll_name name 'AxaiGetModuleOffsetValue';
    function AxaiSwReadVoltage; external dll_name name 'AxaiSwReadVoltage';
    function AxaiSwReadDigit; external dll_name name 'AxaiSwReadDigit';
    function AxaiSwReadMultiVoltage; external dll_name name 'AxaiSwReadMultiVoltage';
    function AxaiSwReadMultiDigit; external dll_name name 'AxaiSwReadMultiDigit';
    function AxaiHwSetMultiAccess; external dll_name name 'AxaiHwSetMultiAccess';
    function AxaiHwStartMultiAccess; external dll_name name 'AxaiHwStartMultiAccess';
    function AxaiHwSetSampleFreq; external dll_name name 'AxaiHwSetSampleFreq';
    function AxaiHwGetSampleFreq; external dll_name name 'AxaiHwGetSampleFreq';
    function AxaiHwSetSamplePeriod; external dll_name name 'AxaiHwSetSamplePeriod';
    function AxaiHwGetSamplePeriod; external dll_name name 'AxaiHwGetSamplePeriod';
    function AxaiHwSetBufferOverflowMode; external dll_name name 'AxaiHwSetBufferOverflowMode';
    function AxaiHwGetBufferOverflowMode; external dll_name name 'AxaiHwGetBufferOverflowMode';
    function AxaiHwSetMultiBufferOverflowMode; external dll_name name 'AxaiHwSetMultiBufferOverflowMode';
    function AxaiHwSetLimit; external dll_name name 'AxaiHwSetLimit';
    function AxaiHwGetLimit; external dll_name name 'AxaiHwGetLimit';
    function AxaiHwSetMultiLimit; external dll_name name 'AxaiHwSetMultiLimit';
    function AxaiHwStartMultiChannel; external dll_name name 'AxaiHwStartMultiChannel';
    function AxaiHwStartSingleChannelAdc; external dll_name name 'AxaiHwStartSingleChannelAdc';
    function AxaiHwStopSingleChannelAdc; external dll_name name 'AxaiHwStopSingleChannelAdc';
    function AxaiHwStartMultiFilter; external dll_name name 'AxaiHwStartMultiFilter';
    function AxaiHwStopMultiChannel; external dll_name name 'AxaiHwStopMultiChannel';
    function AxaiHwReadDataLength; external dll_name name 'AxaiHwReadDataLength';
    function AxaiHwReadSampleVoltage; external dll_name name 'AxaiHwReadSampleVoltage';
    function AxaiHwReadSampleDigit; external dll_name name 'AxaiHwReadSampleDigit';
    function AxaiHwIsBufferEmpty; external dll_name name 'AxaiHwIsBufferEmpty';
    function AxaiHwIsBufferUpper; external dll_name name 'AxaiHwIsBufferUpper';
    function AxaiHwIsBufferLower; external dll_name name 'AxaiHwIsBufferLower';
    function AxaiExternalStartADC; external dll_name name 'AxaiExternalStartADC';
    function AxaiExternalStopADC; external dll_name name 'AxaiExternalStopADC';
    function AxaiExternalReadFifoStatus; external dll_name name 'AxaiExternalReadFifoStatus';
    function AxaiExternalReadVoltage; external dll_name name 'AxaiExternalReadVoltage';
    function AxaoInfoGetModuleNoOfChannelNo; external dll_name name 'AxaoInfoGetModuleNoOfChannelNo';
    function AxaoInfoGetChannelCount; external dll_name name 'AxaoInfoGetChannelCount';
    function AxaoSetRange; external dll_name name 'AxaoSetRange';
    function AxaoGetRange; external dll_name name 'AxaoGetRange';
    function AxaoSetMultiRange; external dll_name name 'AxaoSetMultiRange';
    function AxaoWriteVoltage; external dll_name name 'AxaoWriteVoltage';
    function AxaoWriteMultiVoltage; external dll_name name 'AxaoWriteMultiVoltage';
    function AxaoReadVoltage; external dll_name name 'AxaoReadVoltage';
    function AxaoReadMultiVoltage; external dll_name name 'AxaoReadMultiVoltage';
    function AxaoPgSetUserPatternGenerator; external dll_name name 'AxaoPgSetUserPatternGenerator';
    function AxaoPgGetUserPatternGenerator; external dll_name name 'AxaoPgGetUserPatternGenerator';
    function AxaoPgSetUserInterval; external dll_name name 'AxaoPgSetUserInterval';
    function AxaoPgGetUserInterval; external dll_name name 'AxaoPgGetUserInterval';
    function AxaoPgGetStatus; external dll_name name 'AxaoPgGetStatus';
    function AxaoPgSetUserStart; external dll_name name 'AxaoPgSetUserStart';
    function AxaoPgSetUserStop; external dll_name name 'AxaoPgSetUserStop';
    function AxaPgSetUserDataReset; external dll_name name 'AxaPgSetUserDataReset';
    function AxaoSetNetworkErrorAct; external dll_name name 'AxaoSetNetworkErrorAct';
    function AxaoSetNetworkErrorUserValue; external dll_name name 'AxaoSetNetworkErrorUserValue';
