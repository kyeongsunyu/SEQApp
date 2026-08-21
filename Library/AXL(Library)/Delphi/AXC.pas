//****************************************************************************
///****************************************************************************
//*****************************************************************************
//**
//** File Name
//** ----------
//**
//** AXC.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Counter Library Header File
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

unit AXC;

interface

uses Windows, Messages, AXHS;



//========== Board & Module Info
// Verifying If AIO module exists
function AxcInfoIsCNTModule(upStatus : PDWord) : DWord; stdcall;


// Verifying CNT module number
function AxcInfoGetModuleNo(lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;


// Verifying the number of CNT I/O module
function AxcInfoGetModuleCount(lpModuleCount : PLongInt) : DWord; stdcall;


// Verifying the Number of counter input channels for specified module
function AxcInfoGetChannelCount(lModuleNo : LongInt; lpCount : PLongInt) : DWord; stdcall;


// Verifying the total number of channels in system mounted counter.
function AxcInfoGetTotalChannelCount(lpChannelCount : PLongInt) : DWord; stdcall;


// Verifying base board number, module position and module ID with specified module number
function AxcInfoGetModule(lModuleNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;


// Verifying specified module board : Sub ID, module name, module description
//======================================================/
// support product : EtherCAT
// upModuleSubID   : EtherCAT SubID(for distinguish between EtherCAT modules)
// szModuleName         : model name of module(50 Bytes)
// szModuleDescription  : description of module(80 Bytes)
//======================================================//
function AxcInfoGetModuleEx (lAxisNo : LongInt; upModuleSubID : PDWord; szModuleName : PChar; szModuleDescription : PChar) : DWord; stdcall;

// Verifying Module status of specified module board
function AxcInfoGetModuleStatus(lModuleNo : LongInt) : DWord; stdcall;


function AxcInfoGetFirstChannelNoOfModuleNo(lModuleNo : LongInt; lpChannelNo : PLongInt) : DWord; stdcall;
    function AxcInfoGetModuleNoOfChannelNo (lChannelNo : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;


// Set the Encoder input method for counter module
// dwMethod --> 0x00 : Sign and pulse, x1 multiplication
// dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
// dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
// dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
// dwMethod --> 0x08 : Sign and pulse, x2 multiplication
// dwMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
// dwMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
// For SIO-CN2CH/HPC4
// dwMethod --> 0x00 : Up/Down, A phase, B phase
// dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
// dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
// dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
function AxcSignalSetEncInputMethod(lChannelNo : LongInt; dwMethod : DWord) : DWord; stdcall;


// Get the Encoder input method for counter module
// *dwpUpMethod --> 0x00 : Sign and pulse, x1 multiplication
// *dwpUpMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
// *dwpUpMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
// *dwpUpMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
// *dwpUpMethod --> 0x08 : Sign and pulse, x2 multiplication
// *dwpUpMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
// *dwpUpMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
// For SIO-CN2CH/HPC4
// dwMethod --> 0x00 : Up/Down, A phase, B phase
// dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
// dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
// dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
function AxcSignalGetEncInputMethod(lChannelNo : LongInt; dwpUpMethod : PDWord) : DWord; stdcall;


// Setting trigger of counter module
// dwMode -->  0x00 : Latch
// dwMode -->  0x01 : State
// dwMode -->  0x02 : Special State    --> SIO-CN2CH only
// SIO-CN2CH
// dwMode -->  0x00 : absolute position trigger or period position trigger.
// caution : Each product has different functions. So, it need to use distinctively.
// dwMode -->  0x01 : Time period trigger(Set to AxcTriggerSetFreq)
// In the case of SIO-HPC4
// dwMode -->  0x00 : absolute mode[with ram data].
// dwMode -->  0x01 : timer mode.
// dwMode -->  0x02 : absolute mode[with fifo].
// dwMode -->  0x03 : periodic mode.[Default]
function AxcTriggerSetFunction(lChannelNo : LongInt; dwMode : DWord) : DWord; stdcall;


// Verifying trigger setting of counter module
// *dwMode -->  0x00 : Latch
// *dwMode -->  0x01 : State
// *dwMode -->  0x02 : Special State
// dwMode -->  0x00 : absolute position trigger or period position trigger.
// caution : Each product has different functions. So, it need to use distinctively.
// dwMode -->  0x01 : Time period trigger(Set to AxcTriggerSetFreq)
// In the case of SIO-HPC4
// dwMode -->  0x00 : absolute mode[with ram data].
// dwMode -->  0x01 : timer mode.
// dwMode -->  0x02 : absolute mode[with fifo].
// dwMode -->  0x03 : periodic mode.[Default]
function AxcTriggerGetFunction(lChannelNo : LongInt; dwpMode : PDWord) : DWord; stdcall;


// dwUsage --> 0x00 : Trigger Not use
// dwUsage --> 0x01 : Trigger use
function AxcTriggerSetNotchEnable(lChannelNo : LongInt; dwUsage : DWord) : DWord; stdcall;


// *dwUsage --> 0x00 : Trigger Not use
// *dwUsage --> 0x01 : Trigger use
function AxcTriggerGetNotchEnable(lChannelNo : LongInt; dwpUsage : PDWord) : DWord; stdcall;




// Setting capture polarity of counter module.(External latch input polarity)
// dwCapturePol --> 0x00 : Signal OFF -> ON
// dwCapturePol --> 0x01 : Signal ON -> OFF
function AxcSignalSetCaptureFunction(lChannelNo : LongInt; dwCapturePol : DWord) : DWord; stdcall;


// Verifying capture polarity setting of counter module.(External latch input polarity)
// *dwCapturePol --> 0x00 : Signal OFF -> ON
// *dwCapturePol --> 0x01 : Signal ON -> OFF
function AxcSignalGetCaptureFunction(lChannelNo : LongInt; dwpCapturePol : PDWord) : DWord; stdcall;


// Verifying capture position of counter module.(External latch)
// *dbpCapturePos --> Location of Capture position
function AxcSignalGetCapturePos(lChannelNo : LongInt; dbpCapturePos : PDouble) : DWord; stdcall;


// Verifying counter value of counter module.
// *dbpActPos --> Counter value
function AxcStatusGetActPos(lChannelNo : LongInt; dbpActPos : PDouble) : DWord; stdcall;


// Setting counter value to dbActPos of counter module.
function AxcStatusSetActPos(lChannelNo : LongInt; dbActPos : Double) : DWord; stdcall;


// Setting trigger position of counter module.
// Trigger position of counter module can be set up to two.
function AxcTriggerSetNotchPos(lChannelNo : LongInt; dbLowerPos : Double; dbUpperPos : Double) : DWord; stdcall;


function AxcTriggerGetNotchPos(lChannelNo : LongInt; dbpLowerPos : PDouble; dbpUpperPos : PDouble) : DWord; stdcall;


// Forced trigger output of counter module.
// dwOutVal --> 0x00 : Trigger output '0'
// dwOutVal --> 0x01 : Trigger output '1'
function AxcTriggerSetOutput(lChannelNo : LongInt; dwOutVal : DWord) : DWord; stdcall;


// Verifying status of counter module.
// Bit '0' : Carry (Only 1scan turns 'ON' When current counter value is changed to '0' over the upper limit by additional pulse)
// Bit '1' : Borrow (Only 1scan turns 'ON' When current counter value is changed to lower limit under the '0' by subtraction pulse)
// Bit '2' : Trigger output status
// Bit '3' : Latch input status
function AxcStatusGetChannel(lChannelNo : LongInt; dwpChannelStatus : DWord) : DWord; stdcall;




// API for SIO-CN2CH only
//
// Setting position unit of counter module
// ex) If you need 1000pulse for move 1mm distance, Setting like -> dMoveUnitPerPulse = 0.001
//     And then, setting location-related values of all functions to 'mm' unit.
function AxcMotSetMoveUnitPerPulse(lChannelNo : LongInt; dMoveUnitPerPulse : Double) : DWord; stdcall;


// Verifying position unit of counter module.
function AxcMotGetMoveUnitPerPulse(lChannelNo : LongInt;  dpMoveUnitPerPuls : PDouble) : DWord; stdcall;


// Setting inversion function of encoder input counter of counter module.
// dwReverse --> 0x00 : No reversal.
// dwReverse --> 0x01 : Reversal.
function AxcSignalSetEncReverse(lChannelNo : LongInt; dwReverse : DWord) : DWord; stdcall;


// Returns whether the function of inverting the encoder input counter of the counter module is set.
function AxcSignalGetEncReverse(lChannelNo : LongInt; dwpReverse : PDWord) : DWord; stdcall;


// Selecting encoder input signal of counter module.
// dwSource -->  0x00 : 2(A/B)-Phase signal.
// dwSource -->  0x01 : Z-Phase signal.(No directionality.)
function AxcSignalSetEncSource(lChannelNo : LongInt; dwSource : DWord) : DWord; stdcall;


// Verifying encoder input signal selection setting of counter module.
function AxcSignalGetEncSource(lChannelNo : LongInt; dwpSource : PDWord) : DWord; stdcall;


// Setting lower limit value of trigger output range of counter module.
// Setting lower limit value of range to generate trigger output with position period.(In the case of position period trigger product)
// Setting standard position application of trigger information of start address of ram.(In the case of absolute location product)
// Unit : Set by 'AxcMotSetMoveUnitPerPulse'.
// Note : Lower limit value should be set smaller than upper limit value.
function AxcTriggerSetBlockLowerPos(lChannelNo : LongInt; dLowerPosition : Double) : DWord; stdcall;


// Verifying lower limit value of trigger output range of counter module.
function AxcTriggerGetBlockLowerPos(lChannelNo : LongInt; dpLowerPosition : PDouble) : DWord; stdcall;


// Verifying upper limit value of trigger output range of counter module.
// Setting upper limit value of range to generate trigger output with position period.(In the case of position period trigger product).
// In the case of the product of absolute position trigger, used as location where trigger information is applied of last address of RAM(Trigger information was set).
// Unit : Setting from 'AxcMotSetMoveUnitPerPulse'
// Note : Upper limit value should be set bigger than lower limit value.
function AxcTriggerSetBlockUpperPos(lChannelNo : LongInt; dUpperPosition : Double) : DWord; stdcall;
// Setting lower limit value of trigger output range of counter module.
function AxcTriggerGetBlockUpperPos(lChannelNo : LongInt; dpUpperrPosition : PDouble) : DWord; stdcall;


// Setting position period used for position peroid mode trigger of counter module.
// Unit : Sets from 'AxcMotSetMoveUnitPerPulse'.
function AxcTriggerSetPosPeriod(lChannelNo : LongInt; dPeriod : Double) : DWord; stdcall;


// Verifying position period used for position peroid mode trigger of counter module.
function AxcTriggerGetPosPeriod(lChannelNo : LongInt; dpPeriod : PDouble) : DWord; stdcall;


// Setting a valid function about position increase/decrease when using trigger of position period mode of counter module.
// dwDirection -->  0x00 : Output every trigger period.(About counter increase/decrease)
// dwDirection -->  0x01 : Output every trigger period.(About counter increase)
// dwDirection -->  0x01 : Output every trigger period.(About counter decrease)
function AxcTriggerSetDirectionCheck(lChannelNo : LongInt; dwDirection : DWord) : DWord; stdcall;
// Verifying setting value of 'AxcTriggerSetDirectionCheck'.
function AxcTriggerGetDirectionCheck(lChannelNo : LongInt; dwpDirection : PDWord) : DWord; stdcall;


// Setting position period and range at once.(About trigger function of position period mode)
// Positioning unit : Set by 'AxcMotSetMoveUnitPerPulse'.
function AxcTriggerSetBlock(lChannelNo : LongInt; dLower : Double; dUpper : Double; dABSod : Double) : DWord; stdcall;


// Verifying setting value of 'AxcTriggerSetBlock'.
function AxcTriggerGetBlock(lChannelNo : LongInt; dpLower : PDouble; dpUpper : PDouble; dpABSod : PDouble) : DWord; stdcall;


// Setting pulse width of trigger output of counter module.
// Unit : uSec
function AxcTriggerSetTime(lChannelNo : LongInt; dTrigTime : Double) : DWord; stdcall;


// Verifying setting value of 'AxcTriggerSetTime'.
function AxcTriggerGetTime(lChannelNo : LongInt; dpTrigTime : PDouble) : DWord; stdcall;


// Setting output level of trigger output pulse of counter module.
// dwLevel -->  0x00 : Low level output.(When trigger is output)
// dwLevel -->  0x01 : High level output.(When trigger is output)
function AxcTriggerSetLevel(lChannelNo : LongInt; dwLevel : DWord) : DWord; stdcall;
// Verifying setting value of 'AxcTriggerSetLevel'.
function AxcTriggerGetLevel(lChannelNo : LongInt; dwpLevel : PDWord) : DWord; stdcall;


// Setting frequency for Frequency trigger output function of counter module.
// Unit : Hz, Range : 1Hz ~ 500 kHz
function AxcTriggerSetFreq(lChannelNo : LongInt; dwFreqency : DWord) : DWord; stdcall;
// Verifying setting value of 'AxcTriggerSetFreq'.
function AxcTriggerGetFreq(lChannelNo : LongInt; dwpFreqency : PDWord) : DWord; stdcall;


    function AxcTriggerGetTriggerOutCount (lChannelNo : LongInt; dwpTriggerOutCount : PDWord) : DWord; stdcall;
    function AxcTriggerSetTriggerOutCount (lChannelNo : LongInt; dwTriggerOutCount : DWord) : DWord; stdcall;



// Setting the value of universal output about appoint channel of counter module.
// dwOutput range : 0x00 ~ 0x0F, Four universal outputs for each channel.
function AxcSignalWriteOutput(lChannelNo : LongInt; dwOutput : DWord) : DWord; stdcall;


// Verifying the value of universal output about appoint channel of counter module.
function AxcSignalReadOutput(lChannelNo : LongInt; dwpOutput : PDWord) : DWord; stdcall;


// Setting the value by bit of universal output about appoint channel of counter module.
// lBitNo range : 0 ~ 3, Four universal outputs for each channel.
function AxcSignalWriteOutputBit(lChannelNo : LongInt; lBitNo : LongInt; uOnOff : DWord) : DWord; stdcall;
// Verifying the value by bit of universal output about appoint channel of counter module.
// lBitNo range : 0 ~ 3
function AxcSignalReadOutputBit(lChannelNo : LongInt; lBitNo : LongInt; upOnOff : PDWord) : DWord; stdcall;


// Check the general-purpose input value for the designated channel of the counter module.
function AxcSignalReadInput(lChannelNo : LongInt; dwpInput : PDWord) : DWord; stdcall;


// Verifying the value by bit of universal input about appoint channel of counter module.
// lBitNo range : 0 ~ 3
function AxcSignalReadInputBit(lChannelNo : LongInt; lBitNo : LongInt; upOnOff : PDWord) : DWord; stdcall;


// Activating trigger output of counter module.
// Sets whether the trigger output will be finally output according to the currently set function.
function AxcTriggerSetEnable(lChannelNo : LongInt; dwUsage : DWord) : DWord; stdcall;


// Verifying setting value of 'AxcTriggerSetEnable'.
function AxcTriggerGetEnable(lChannelNo : LongInt; dwpUsage : PDWord) : DWord; stdcall;


// Verifying RAM contents for absolute trigger function of counter module.
// dwAddr range : 0x0000 ~ 0x1FFFF;
function AxcTriggerReadAbsRamData(lChannelNo : LongInt; dwAddr : DWord; dwpData : PDWord) : DWord; stdcall;


// Setting RAM contents for absolute trigger function of counter module.
// dwAddr range : 0x0000 ~ 0x1FFFF;
function AxcTriggerWriteAbsRamData(lChannelNo : LongInt; dwAddr : DWord; dwData : DWord) : DWord; stdcall;


// Setting RAM contents at once for absolute trigger function of counter module.
// dwTrigNum range : ~ 0x20000  In the case of *RTEX CNT2  0x200*
// dwDirection --> 0x0 : Input trigger information first about lower limit trigger position. Used for trigger output(In direction of increasing position).
// dwDirection --> 0x1 : Input trigger information first about upper limit trigger position. Used for trigger output(In direction of decreasing position).
function AxcTriggerSetAbs(lChannelNo : LongInt; dwTrigNum : DWord; dwTrigPos : PDWord; dwDirection : DWord) : DWord; stdcall;


// Set the contents of the RAM required for the absolute position trigger function of the counter module at once.
// dwTrigNum range : 0 ~ 0x20000 (RTEX CNT2 : 0 ~ 0x200)
// dwDirection     : (0) Enter the trigger information for the lower limit trigger position. Used for trigger output in the direction of increasing position.
//                   (1) Enter the trigger information for the upper limit trigger position. Used for trigger output in the direction of decreasing position.
// dTrigPos        : Use trigger position of counter module as double type
function AxcTriggerSetAbsDouble(lChannelNo : LongInt; dwTrigNum : DWord; dTrigPos : PDouble; dwDirection : DWord) : DWord; stdcall;

    function AxcTriggerSetEncoderInput (lModuleNo : LongInt; dwEncoderInput1 : DWord; dwEncoderInput2 : DWord) : DWord; stdcall;
    function AxcTriggerGetEncoderInput (lModuleNo : LongInt; dwpEncoderInput1 : PDWord; dwpEncoderInput2 : PDWord) : DWord; stdcall;

    function AxcTableSetTriggerLevel (lModuleNo : LongInt; lTablePos : LongInt; uLevel : DWord) : DWord; stdcall;
    function AxcTableGetTriggerLevel (lModuleNo : LongInt; lTablePos : LongInt; upLevel : PDWord) : DWord; stdcall;

    function AxcTableSetTriggerTime (lModuleNo : LongInt; lTablePos : LongInt; dTriggerTimeUSec : Double) : DWord; stdcall;
    function AxcTableGetTriggerTime (lModuleNo : LongInt; lTablePos : LongInt; dpTriggerTimeUSec : PDouble) : DWord; stdcall;

    function AxcTableSetEncoderInput (lModuleNo : LongInt; lTablePos : LongInt; uEncoderInput1 : DWord; uEncoderInput2 : DWord) : DWord; stdcall;
    function AxcTableGetEncoderInput (lModuleNo : LongInt; lTablePos : LongInt; upEncoderInput1 : PDWord; upEncoderInput2 : PDWord) : DWord; stdcall;


    function AxcTableSetTriggerOutport (lModuleNo : LongInt; lTablePos : LongInt; uTriggerOutport : DWord) : DWord; stdcall;
    function AxcTableGetTriggerOutport (lModuleNo : LongInt; lTablePos : LongInt; upTriggerOutport : PDWord) : DWord; stdcall;

    function AxcTableSetErrorRange (lModuleNo : LongInt; lTablePos : LongInt; dErrorRange : Double) : DWord; stdcall;
    function AxcTableGetErrorRange (lModuleNo : LongInt; lTablePos : LongInt; dpErrorRange : PDouble) : DWord; stdcall;

    function AxcTableTriggerOneShot (lModuleNo : LongInt; lTablePos : LongInt) : DWord; stdcall;

    function AxcTableTriggerPatternShot (lModuleNo : LongInt; lTablePos : LongInt; lTriggerCount : LongInt; uTriggerFrequency : DWord) : DWord; stdcall;
    function AxcTableGetPatternShotData (lModuleNo : LongInt; lTablePos : LongInt; lpTriggerCount : PLongInt; upTriggerFrequency : PDWord) : DWord; stdcall;

    function AxcTableSetTriggerMode (lModuleNo : LongInt; lTablePos : LongInt; uTrigMode : DWord) : DWord; stdcall;
    function AxcTableGetTriggerMode (lModuleNo : LongInt; lTablePos : LongInt; upTrigMode : PDWord) : DWord; stdcall;
    function AxcTableSetTriggerCountClear (lModuleNo : LongInt; lTablePos : LongInt) : DWord; stdcall;

    function AxcTableSetTriggerData (lModuleNo : LongInt; lTablePos : LongInt; lTriggerDataCount : LongInt; dpTriggerData : PDouble; lpTriggerCount : PLongInt; dpTriggerInterval : PDouble) : DWord; stdcall;
    function AxcTableGetTriggerData (lModuleNo : LongInt; lTablePos : LongInt; lpTriggerDataCount : PLongInt; dpTriggerData : PDouble; lpTriggerCount : PLongInt; dpTriggerInterval : PDouble) : DWord; stdcall;

    function AxcTableSetTriggerDataEx (lModuleNo : LongInt; lTablePos : LongInt; lTriggerDataCount : LongInt; uOption : DWord; dpTriggerData : PDouble) : DWord; stdcall;
    function AxcTableGetTriggerDataEx (lModuleNo : LongInt; lTablePos : LongInt; lpTriggerDataCount : PLongInt; upOption : PDWord; dpTriggerData : PDouble) : DWord; stdcall;

    function AxcTableSetTriggerDataClear (lModuleNo : LongInt; lTablePos : LongInt) : DWord; stdcall;

    function AxcTableSetEnable (lModuleNo : LongInt; lTablePos : LongInt; uEnable : DWord) : DWord; stdcall;
    function AxcTableGetEnable (lModuleNo : LongInt; lTablePos : LongInt; upEnable : PDWord) : DWord; stdcall;

    function AxcTableReadTriggerCount (lModuleNo : LongInt; lTablePos : LongInt; lpTriggerCount : PLongInt) : DWord; stdcall;

    function AxcTableReadFifoStatus (lModuleNo : LongInt; lTablePos : LongInt; lpCount1 : PLongInt; upStatus1 : PDWord; lpCount2 : PLongInt; upStatus2 : PDWord) : DWord; stdcall;

    function AxcTableReadFifoData (lModuleNo : LongInt; lTablePos : LongInt; dpTopData1 : PDouble; dpTopData2 : PDouble) : DWord; stdcall;

implementation

const

    dll_name    = 'AXL.dll';
    function AxcInfoIsCNTModule; external dll_name name 'AxcInfoIsCNTModule';
    function AxcInfoGetModuleNo; external dll_name name 'AxcInfoGetModuleNo';
    function AxcInfoGetModuleCount; external dll_name name 'AxcInfoGetModuleCount';
    function AxcInfoGetChannelCount; external dll_name name 'AxcInfoGetChannelCount';
    function AxcInfoGetTotalChannelCount; external dll_name name 'AxcInfoGetTotalChannelCount';
    function AxcInfoGetModule; external dll_name name 'AxcInfoGetModule';
    function AxcInfoGetModuleEx; external dll_name name 'AxcInfoGetModuleEx';
    function AxcInfoGetModuleStatus; external dll_name name 'AxcInfoGetModuleStatus';
    function AxcInfoGetFirstChannelNoOfModuleNo; external dll_name name 'AxcInfoGetFirstChannelNoOfModuleNo';
    function AxcSignalSetEncInputMethod; external dll_name name 'AxcSignalSetEncInputMethod';
    function AxcSignalGetEncInputMethod; external dll_name name 'AxcSignalGetEncInputMethod';
    function AxcTriggerSetFunction; external dll_name name 'AxcTriggerSetFunction';
    function AxcTriggerGetFunction; external dll_name name 'AxcTriggerGetFunction';
    function AxcTriggerSetNotchEnable; external dll_name name 'AxcTriggerSetNotchEnable';
    function AxcTriggerGetNotchEnable; external dll_name name 'AxcTriggerGetNotchEnable';
    function AxcSignalSetCaptureFunction; external dll_name name 'AxcSignalSetCaptureFunction';
    function AxcSignalGetCaptureFunction; external dll_name name 'AxcSignalGetCaptureFunction';
    function AxcSignalGetCapturePos; external dll_name name 'AxcSignalGetCapturePos';
    function AxcStatusGetActPos; external dll_name name 'AxcStatusGetActPos';
    function AxcStatusSetActPos; external dll_name name 'AxcStatusSetActPos';
    function AxcTriggerSetNotchPos; external dll_name name 'AxcTriggerSetNotchPos';
    function AxcTriggerGetNotchPos; external dll_name name 'AxcTriggerGetNotchPos';
    function AxcTriggerSetOutput; external dll_name name 'AxcTriggerSetOutput';
    function AxcStatusGetChannel; external dll_name name 'AxcStatusGetChannel';
    function AxcMotSetMoveUnitPerPulse; external dll_name name 'AxcMotSetMoveUnitPerPulse';
    function AxcMotGetMoveUnitPerPulse; external dll_name name 'AxcMotGetMoveUnitPerPulse';
    function AxcSignalSetEncReverse; external dll_name name 'AxcSignalSetEncReverse';
    function AxcSignalGetEncReverse; external dll_name name 'AxcSignalGetEncReverse';
    function AxcSignalSetEncSource; external dll_name name 'AxcSignalSetEncSource';
    function AxcSignalGetEncSource; external dll_name name 'AxcSignalGetEncSource';
    function AxcTriggerSetBlockLowerPos; external dll_name name 'AxcTriggerSetBlockLowerPos';
    function AxcTriggerGetBlockLowerPos; external dll_name name 'AxcTriggerGetBlockLowerPos';
    function AxcTriggerSetBlockUpperPos; external dll_name name 'AxcTriggerSetBlockUpperPos';
    function AxcTriggerGetBlockUpperPos; external dll_name name 'AxcTriggerGetBlockUpperPos';
    function AxcTriggerSetPosPeriod; external dll_name name 'AxcTriggerSetPosPeriod';
    function AxcTriggerGetPosPeriod; external dll_name name 'AxcTriggerGetPosPeriod';
    function AxcTriggerSetDirectionCheck; external dll_name name 'AxcTriggerSetDirectionCheck';
    function AxcTriggerGetDirectionCheck; external dll_name name 'AxcTriggerGetDirectionCheck';
    function AxcTriggerSetBlock; external dll_name name 'AxcTriggerSetBlock';
    function AxcTriggerGetBlock; external dll_name name 'AxcTriggerGetBlock';
    function AxcTriggerSetTime; external dll_name name 'AxcTriggerSetTime';
    function AxcTriggerGetTime; external dll_name name 'AxcTriggerGetTime';
    function AxcTriggerSetLevel; external dll_name name 'AxcTriggerSetLevel';
    function AxcTriggerGetLevel; external dll_name name 'AxcTriggerGetLevel';
    function AxcTriggerSetFreq; external dll_name name 'AxcTriggerSetFreq';
    function AxcTriggerGetFreq; external dll_name name 'AxcTriggerGetFreq';
    function AxcSignalWriteOutput; external dll_name name 'AxcSignalWriteOutput';
    function AxcSignalReadOutput; external dll_name name 'AxcSignalReadOutput';
    function AxcSignalWriteOutputBit; external dll_name name 'AxcSignalWriteOutputBit';
    function AxcSignalReadOutputBit; external dll_name name 'AxcSignalReadOutputBit';
    function AxcSignalReadInput; external dll_name name 'AxcSignalReadInput';
    function AxcSignalReadInputBit; external dll_name name 'AxcSignalReadInputBit';
    function AxcTriggerSetEnable; external dll_name name 'AxcTriggerSetEnable';
    function AxcTriggerGetEnable; external dll_name name 'AxcTriggerGetEnable';
    function AxcTriggerReadAbsRamData; external dll_name name 'AxcTriggerReadAbsRamData';
    function AxcTriggerWriteAbsRamData; external dll_name name 'AxcTriggerWriteAbsRamData';
    function AxcTriggerSetAbs; external dll_name name 'AxcTriggerSetAbs';
    function AxcTriggerSetAbsDouble; external dll_name name 'AxcTriggerSetAbsDouble';
    function AxcInfoIsCNTModule; external dll_name name 'AxcInfoIsCNTModule';
    function AxcInfoGetModuleNo; external dll_name name 'AxcInfoGetModuleNo';
    function AxcInfoGetModuleCount; external dll_name name 'AxcInfoGetModuleCount';
    function AxcInfoGetChannelCount; external dll_name name 'AxcInfoGetChannelCount';
    function AxcInfoGetTotalChannelCount; external dll_name name 'AxcInfoGetTotalChannelCount';
    function AxcInfoGetModule; external dll_name name 'AxcInfoGetModule';
    function AxcInfoGetModuleEx; external dll_name name 'AxcInfoGetModuleEx';
    function AxcInfoGetModuleStatus; external dll_name name 'AxcInfoGetModuleStatus';
    function AxcInfoGetFirstChannelNoOfModuleNo; external dll_name name 'AxcInfoGetFirstChannelNoOfModuleNo';
    function AxcSignalSetEncInputMethod; external dll_name name 'AxcSignalSetEncInputMethod';
    function AxcSignalGetEncInputMethod; external dll_name name 'AxcSignalGetEncInputMethod';
    function AxcTriggerSetFunction; external dll_name name 'AxcTriggerSetFunction';
    function AxcTriggerGetFunction; external dll_name name 'AxcTriggerGetFunction';
    function AxcTriggerSetNotchEnable; external dll_name name 'AxcTriggerSetNotchEnable';
    function AxcTriggerGetNotchEnable; external dll_name name 'AxcTriggerGetNotchEnable';
    function AxcSignalSetCaptureFunction; external dll_name name 'AxcSignalSetCaptureFunction';
    function AxcSignalGetCaptureFunction; external dll_name name 'AxcSignalGetCaptureFunction';
    function AxcSignalGetCapturePos; external dll_name name 'AxcSignalGetCapturePos';
    function AxcStatusGetActPos; external dll_name name 'AxcStatusGetActPos';
    function AxcStatusSetActPos; external dll_name name 'AxcStatusSetActPos';
    function AxcTriggerSetNotchPos; external dll_name name 'AxcTriggerSetNotchPos';
    function AxcTriggerGetNotchPos; external dll_name name 'AxcTriggerGetNotchPos';
    function AxcTriggerSetOutput; external dll_name name 'AxcTriggerSetOutput';
    function AxcStatusGetChannel; external dll_name name 'AxcStatusGetChannel';
    function AxcMotSetMoveUnitPerPulse; external dll_name name 'AxcMotSetMoveUnitPerPulse';
    function AxcMotGetMoveUnitPerPulse; external dll_name name 'AxcMotGetMoveUnitPerPulse';
    function AxcSignalSetEncReverse; external dll_name name 'AxcSignalSetEncReverse';
    function AxcSignalGetEncReverse; external dll_name name 'AxcSignalGetEncReverse';
    function AxcSignalSetEncSource; external dll_name name 'AxcSignalSetEncSource';
    function AxcSignalGetEncSource; external dll_name name 'AxcSignalGetEncSource';
    function AxcTriggerSetBlockLowerPos; external dll_name name 'AxcTriggerSetBlockLowerPos';
    function AxcTriggerGetBlockLowerPos; external dll_name name 'AxcTriggerGetBlockLowerPos';
    function AxcTriggerSetBlockUpperPos; external dll_name name 'AxcTriggerSetBlockUpperPos';
    function AxcTriggerGetBlockUpperPos; external dll_name name 'AxcTriggerGetBlockUpperPos';
    function AxcTriggerSetPosPeriod; external dll_name name 'AxcTriggerSetPosPeriod';
    function AxcTriggerGetPosPeriod; external dll_name name 'AxcTriggerGetPosPeriod';
    function AxcTriggerSetDirectionCheck; external dll_name name 'AxcTriggerSetDirectionCheck';
    function AxcTriggerGetDirectionCheck; external dll_name name 'AxcTriggerGetDirectionCheck';
    function AxcTriggerSetBlock; external dll_name name 'AxcTriggerSetBlock';
    function AxcTriggerGetBlock; external dll_name name 'AxcTriggerGetBlock';
    function AxcTriggerSetTime; external dll_name name 'AxcTriggerSetTime';
    function AxcTriggerGetTime; external dll_name name 'AxcTriggerGetTime';
    function AxcTriggerSetLevel; external dll_name name 'AxcTriggerSetLevel';
    function AxcTriggerGetLevel; external dll_name name 'AxcTriggerGetLevel';
    function AxcTriggerSetFreq; external dll_name name 'AxcTriggerSetFreq';
    function AxcTriggerGetFreq; external dll_name name 'AxcTriggerGetFreq';
    function AxcSignalWriteOutput; external dll_name name 'AxcSignalWriteOutput';
    function AxcSignalReadOutput; external dll_name name 'AxcSignalReadOutput';
    function AxcSignalWriteOutputBit; external dll_name name 'AxcSignalWriteOutputBit';
    function AxcSignalReadOutputBit; external dll_name name 'AxcSignalReadOutputBit';
    function AxcSignalReadInput; external dll_name name 'AxcSignalReadInput';
    function AxcSignalReadInputBit; external dll_name name 'AxcSignalReadInputBit';
    function AxcTriggerSetEnable; external dll_name name 'AxcTriggerSetEnable';
    function AxcTriggerGetEnable; external dll_name name 'AxcTriggerGetEnable';
    function AxcTriggerReadAbsRamData; external dll_name name 'AxcTriggerReadAbsRamData';
    function AxcTriggerWriteAbsRamData; external dll_name name 'AxcTriggerWriteAbsRamData';
    function AxcTriggerSetAbs; external dll_name name 'AxcTriggerSetAbs';
    function AxcTriggerSetAbsDouble; external dll_name name 'AxcTriggerSetAbsDouble';
    function AxcInfoIsCNTModule; external dll_name name 'AxcInfoIsCNTModule';
    function AxcInfoGetModuleNo; external dll_name name 'AxcInfoGetModuleNo';
    function AxcInfoGetModuleCount; external dll_name name 'AxcInfoGetModuleCount';
    function AxcInfoGetChannelCount; external dll_name name 'AxcInfoGetChannelCount';
    function AxcInfoGetTotalChannelCount; external dll_name name 'AxcInfoGetTotalChannelCount';
    function AxcInfoGetModule; external dll_name name 'AxcInfoGetModule';
    function AxcInfoGetModuleEx; external dll_name name 'AxcInfoGetModuleEx';
    function AxcInfoGetModuleStatus; external dll_name name 'AxcInfoGetModuleStatus';
    function AxcInfoGetFirstChannelNoOfModuleNo; external dll_name name 'AxcInfoGetFirstChannelNoOfModuleNo';
    function AxcSignalSetEncInputMethod; external dll_name name 'AxcSignalSetEncInputMethod';
    function AxcSignalGetEncInputMethod; external dll_name name 'AxcSignalGetEncInputMethod';
    function AxcTriggerSetFunction; external dll_name name 'AxcTriggerSetFunction';
    function AxcTriggerGetFunction; external dll_name name 'AxcTriggerGetFunction';
    function AxcTriggerSetNotchEnable; external dll_name name 'AxcTriggerSetNotchEnable';
    function AxcTriggerGetNotchEnable; external dll_name name 'AxcTriggerGetNotchEnable';
    function AxcSignalSetCaptureFunction; external dll_name name 'AxcSignalSetCaptureFunction';
    function AxcSignalGetCaptureFunction; external dll_name name 'AxcSignalGetCaptureFunction';
    function AxcSignalGetCapturePos; external dll_name name 'AxcSignalGetCapturePos';
    function AxcStatusGetActPos; external dll_name name 'AxcStatusGetActPos';
    function AxcStatusSetActPos; external dll_name name 'AxcStatusSetActPos';
    function AxcTriggerSetNotchPos; external dll_name name 'AxcTriggerSetNotchPos';
    function AxcTriggerGetNotchPos; external dll_name name 'AxcTriggerGetNotchPos';
    function AxcTriggerSetOutput; external dll_name name 'AxcTriggerSetOutput';
    function AxcStatusGetChannel; external dll_name name 'AxcStatusGetChannel';
    function AxcMotSetMoveUnitPerPulse; external dll_name name 'AxcMotSetMoveUnitPerPulse';
    function AxcMotGetMoveUnitPerPulse; external dll_name name 'AxcMotGetMoveUnitPerPulse';
    function AxcSignalSetEncReverse; external dll_name name 'AxcSignalSetEncReverse';
    function AxcSignalGetEncReverse; external dll_name name 'AxcSignalGetEncReverse';
    function AxcSignalSetEncSource; external dll_name name 'AxcSignalSetEncSource';
    function AxcSignalGetEncSource; external dll_name name 'AxcSignalGetEncSource';
    function AxcTriggerSetBlockLowerPos; external dll_name name 'AxcTriggerSetBlockLowerPos';
    function AxcTriggerGetBlockLowerPos; external dll_name name 'AxcTriggerGetBlockLowerPos';
    function AxcTriggerSetBlockUpperPos; external dll_name name 'AxcTriggerSetBlockUpperPos';
    function AxcTriggerGetBlockUpperPos; external dll_name name 'AxcTriggerGetBlockUpperPos';
    function AxcTriggerSetPosPeriod; external dll_name name 'AxcTriggerSetPosPeriod';
    function AxcTriggerGetPosPeriod; external dll_name name 'AxcTriggerGetPosPeriod';
    function AxcTriggerSetDirectionCheck; external dll_name name 'AxcTriggerSetDirectionCheck';
    function AxcTriggerGetDirectionCheck; external dll_name name 'AxcTriggerGetDirectionCheck';
    function AxcTriggerSetBlock; external dll_name name 'AxcTriggerSetBlock';
    function AxcTriggerGetBlock; external dll_name name 'AxcTriggerGetBlock';
    function AxcTriggerSetTime; external dll_name name 'AxcTriggerSetTime';
    function AxcTriggerGetTime; external dll_name name 'AxcTriggerGetTime';
    function AxcTriggerSetLevel; external dll_name name 'AxcTriggerSetLevel';
    function AxcTriggerGetLevel; external dll_name name 'AxcTriggerGetLevel';
    function AxcTriggerSetFreq; external dll_name name 'AxcTriggerSetFreq';
    function AxcTriggerGetFreq; external dll_name name 'AxcTriggerGetFreq';
    function AxcSignalWriteOutput; external dll_name name 'AxcSignalWriteOutput';
    function AxcSignalReadOutput; external dll_name name 'AxcSignalReadOutput';
    function AxcSignalWriteOutputBit; external dll_name name 'AxcSignalWriteOutputBit';
    function AxcSignalReadOutputBit; external dll_name name 'AxcSignalReadOutputBit';
    function AxcSignalReadInput; external dll_name name 'AxcSignalReadInput';
    function AxcSignalReadInputBit; external dll_name name 'AxcSignalReadInputBit';
    function AxcTriggerSetEnable; external dll_name name 'AxcTriggerSetEnable';
    function AxcTriggerGetEnable; external dll_name name 'AxcTriggerGetEnable';
    function AxcTriggerReadAbsRamData; external dll_name name 'AxcTriggerReadAbsRamData';
    function AxcTriggerWriteAbsRamData; external dll_name name 'AxcTriggerWriteAbsRamData';
    function AxcTriggerSetAbs; external dll_name name 'AxcTriggerSetAbs';
    function AxcTriggerSetAbsDouble; external dll_name name 'AxcTriggerSetAbsDouble';
    function AxcInfoIsCNTModule; external dll_name name 'AxcInfoIsCNTModule';
    function AxcInfoGetModuleNo; external dll_name name 'AxcInfoGetModuleNo';
    function AxcInfoGetModuleCount; external dll_name name 'AxcInfoGetModuleCount';
    function AxcInfoGetChannelCount; external dll_name name 'AxcInfoGetChannelCount';
    function AxcInfoGetTotalChannelCount; external dll_name name 'AxcInfoGetTotalChannelCount';
    function AxcInfoGetModule; external dll_name name 'AxcInfoGetModule';
    function AxcInfoGetModuleEx; external dll_name name 'AxcInfoGetModuleEx';
    function AxcInfoGetModuleStatus; external dll_name name 'AxcInfoGetModuleStatus';
    function AxcInfoGetFirstChannelNoOfModuleNo; external dll_name name 'AxcInfoGetFirstChannelNoOfModuleNo';
    function AxcSignalSetEncInputMethod; external dll_name name 'AxcSignalSetEncInputMethod';
    function AxcSignalGetEncInputMethod; external dll_name name 'AxcSignalGetEncInputMethod';
    function AxcTriggerSetFunction; external dll_name name 'AxcTriggerSetFunction';
    function AxcTriggerGetFunction; external dll_name name 'AxcTriggerGetFunction';
    function AxcTriggerSetNotchEnable; external dll_name name 'AxcTriggerSetNotchEnable';
    function AxcTriggerGetNotchEnable; external dll_name name 'AxcTriggerGetNotchEnable';
    function AxcSignalSetCaptureFunction; external dll_name name 'AxcSignalSetCaptureFunction';
    function AxcSignalGetCaptureFunction; external dll_name name 'AxcSignalGetCaptureFunction';
    function AxcSignalGetCapturePos; external dll_name name 'AxcSignalGetCapturePos';
    function AxcStatusGetActPos; external dll_name name 'AxcStatusGetActPos';
    function AxcStatusSetActPos; external dll_name name 'AxcStatusSetActPos';
    function AxcTriggerSetNotchPos; external dll_name name 'AxcTriggerSetNotchPos';
    function AxcTriggerGetNotchPos; external dll_name name 'AxcTriggerGetNotchPos';
    function AxcTriggerSetOutput; external dll_name name 'AxcTriggerSetOutput';
    function AxcStatusGetChannel; external dll_name name 'AxcStatusGetChannel';
    function AxcMotSetMoveUnitPerPulse; external dll_name name 'AxcMotSetMoveUnitPerPulse';
    function AxcMotGetMoveUnitPerPulse; external dll_name name 'AxcMotGetMoveUnitPerPulse';
    function AxcSignalSetEncReverse; external dll_name name 'AxcSignalSetEncReverse';
    function AxcSignalGetEncReverse; external dll_name name 'AxcSignalGetEncReverse';
    function AxcSignalSetEncSource; external dll_name name 'AxcSignalSetEncSource';
    function AxcSignalGetEncSource; external dll_name name 'AxcSignalGetEncSource';
    function AxcTriggerSetBlockLowerPos; external dll_name name 'AxcTriggerSetBlockLowerPos';
    function AxcTriggerGetBlockLowerPos; external dll_name name 'AxcTriggerGetBlockLowerPos';
    function AxcTriggerSetBlockUpperPos; external dll_name name 'AxcTriggerSetBlockUpperPos';
    function AxcTriggerGetBlockUpperPos; external dll_name name 'AxcTriggerGetBlockUpperPos';
    function AxcTriggerSetPosPeriod; external dll_name name 'AxcTriggerSetPosPeriod';
    function AxcTriggerGetPosPeriod; external dll_name name 'AxcTriggerGetPosPeriod';
    function AxcTriggerSetDirectionCheck; external dll_name name 'AxcTriggerSetDirectionCheck';
    function AxcTriggerGetDirectionCheck; external dll_name name 'AxcTriggerGetDirectionCheck';
    function AxcTriggerSetBlock; external dll_name name 'AxcTriggerSetBlock';
    function AxcTriggerGetBlock; external dll_name name 'AxcTriggerGetBlock';
    function AxcTriggerSetTime; external dll_name name 'AxcTriggerSetTime';
    function AxcTriggerGetTime; external dll_name name 'AxcTriggerGetTime';
    function AxcTriggerSetLevel; external dll_name name 'AxcTriggerSetLevel';
    function AxcTriggerGetLevel; external dll_name name 'AxcTriggerGetLevel';
    function AxcTriggerSetFreq; external dll_name name 'AxcTriggerSetFreq';
    function AxcTriggerGetFreq; external dll_name name 'AxcTriggerGetFreq';
    function AxcSignalWriteOutput; external dll_name name 'AxcSignalWriteOutput';
    function AxcSignalReadOutput; external dll_name name 'AxcSignalReadOutput';
    function AxcSignalWriteOutputBit; external dll_name name 'AxcSignalWriteOutputBit';
    function AxcSignalReadOutputBit; external dll_name name 'AxcSignalReadOutputBit';
    function AxcSignalReadInput; external dll_name name 'AxcSignalReadInput';
    function AxcSignalReadInputBit; external dll_name name 'AxcSignalReadInputBit';
    function AxcTriggerSetEnable; external dll_name name 'AxcTriggerSetEnable';
    function AxcTriggerGetEnable; external dll_name name 'AxcTriggerGetEnable';
    function AxcTriggerReadAbsRamData; external dll_name name 'AxcTriggerReadAbsRamData';
    function AxcTriggerWriteAbsRamData; external dll_name name 'AxcTriggerWriteAbsRamData';
    function AxcTriggerSetAbs; external dll_name name 'AxcTriggerSetAbs';
    function AxcTriggerSetAbsDouble; external dll_name name 'AxcTriggerSetAbsDouble';
    function AxcInfoIsCNTModule; external dll_name name 'AxcInfoIsCNTModule';
    function AxcInfoGetModuleNo; external dll_name name 'AxcInfoGetModuleNo';
    function AxcInfoGetModuleCount; external dll_name name 'AxcInfoGetModuleCount';
    function AxcInfoGetChannelCount; external dll_name name 'AxcInfoGetChannelCount';
    function AxcInfoGetTotalChannelCount; external dll_name name 'AxcInfoGetTotalChannelCount';
    function AxcInfoGetModule; external dll_name name 'AxcInfoGetModule';
    function AxcInfoGetModuleEx; external dll_name name 'AxcInfoGetModuleEx';
    function AxcInfoGetModuleStatus; external dll_name name 'AxcInfoGetModuleStatus';
    function AxcInfoGetFirstChannelNoOfModuleNo; external dll_name name 'AxcInfoGetFirstChannelNoOfModuleNo';
    function AxcInfoGetModuleNoOfChannelNo; external dll_name name 'AxcInfoGetModuleNoOfChannelNo';
    function AxcSignalSetEncInputMethod; external dll_name name 'AxcSignalSetEncInputMethod';
    function AxcSignalGetEncInputMethod; external dll_name name 'AxcSignalGetEncInputMethod';
    function AxcTriggerSetFunction; external dll_name name 'AxcTriggerSetFunction';
    function AxcTriggerGetFunction; external dll_name name 'AxcTriggerGetFunction';
    function AxcTriggerSetNotchEnable; external dll_name name 'AxcTriggerSetNotchEnable';
    function AxcTriggerGetNotchEnable; external dll_name name 'AxcTriggerGetNotchEnable';
    function AxcSignalSetCaptureFunction; external dll_name name 'AxcSignalSetCaptureFunction';
    function AxcSignalGetCaptureFunction; external dll_name name 'AxcSignalGetCaptureFunction';
    function AxcSignalGetCapturePos; external dll_name name 'AxcSignalGetCapturePos';
    function AxcStatusGetActPos; external dll_name name 'AxcStatusGetActPos';
    function AxcStatusSetActPos; external dll_name name 'AxcStatusSetActPos';
    function AxcTriggerSetNotchPos; external dll_name name 'AxcTriggerSetNotchPos';
    function AxcTriggerGetNotchPos; external dll_name name 'AxcTriggerGetNotchPos';
    function AxcTriggerSetOutput; external dll_name name 'AxcTriggerSetOutput';
    function AxcStatusGetChannel; external dll_name name 'AxcStatusGetChannel';
    function AxcMotSetMoveUnitPerPulse; external dll_name name 'AxcMotSetMoveUnitPerPulse';
    function AxcMotGetMoveUnitPerPulse; external dll_name name 'AxcMotGetMoveUnitPerPulse';
    function AxcSignalSetEncReverse; external dll_name name 'AxcSignalSetEncReverse';
    function AxcSignalGetEncReverse; external dll_name name 'AxcSignalGetEncReverse';
    function AxcSignalSetEncSource; external dll_name name 'AxcSignalSetEncSource';
    function AxcSignalGetEncSource; external dll_name name 'AxcSignalGetEncSource';
    function AxcTriggerSetBlockLowerPos; external dll_name name 'AxcTriggerSetBlockLowerPos';
    function AxcTriggerGetBlockLowerPos; external dll_name name 'AxcTriggerGetBlockLowerPos';
    function AxcTriggerSetBlockUpperPos; external dll_name name 'AxcTriggerSetBlockUpperPos';
    function AxcTriggerGetBlockUpperPos; external dll_name name 'AxcTriggerGetBlockUpperPos';
    function AxcTriggerSetPosPeriod; external dll_name name 'AxcTriggerSetPosPeriod';
    function AxcTriggerGetPosPeriod; external dll_name name 'AxcTriggerGetPosPeriod';
    function AxcTriggerSetDirectionCheck; external dll_name name 'AxcTriggerSetDirectionCheck';
    function AxcTriggerGetDirectionCheck; external dll_name name 'AxcTriggerGetDirectionCheck';
    function AxcTriggerSetBlock; external dll_name name 'AxcTriggerSetBlock';
    function AxcTriggerGetBlock; external dll_name name 'AxcTriggerGetBlock';
    function AxcTriggerSetTime; external dll_name name 'AxcTriggerSetTime';
    function AxcTriggerGetTime; external dll_name name 'AxcTriggerGetTime';
    function AxcTriggerSetLevel; external dll_name name 'AxcTriggerSetLevel';
    function AxcTriggerGetLevel; external dll_name name 'AxcTriggerGetLevel';
    function AxcTriggerSetFreq; external dll_name name 'AxcTriggerSetFreq';
    function AxcTriggerGetFreq; external dll_name name 'AxcTriggerGetFreq';
    function AxcTriggerGetTriggerOutCount; external dll_name name 'AxcTriggerGetTriggerOutCount';
    function AxcTriggerSetTriggerOutCount; external dll_name name 'AxcTriggerSetTriggerOutCount';
    function AxcSignalWriteOutput; external dll_name name 'AxcSignalWriteOutput';
    function AxcSignalReadOutput; external dll_name name 'AxcSignalReadOutput';
    function AxcSignalWriteOutputBit; external dll_name name 'AxcSignalWriteOutputBit';
    function AxcSignalReadOutputBit; external dll_name name 'AxcSignalReadOutputBit';
    function AxcSignalReadInput; external dll_name name 'AxcSignalReadInput';
    function AxcSignalReadInputBit; external dll_name name 'AxcSignalReadInputBit';
    function AxcTriggerSetEnable; external dll_name name 'AxcTriggerSetEnable';
    function AxcTriggerGetEnable; external dll_name name 'AxcTriggerGetEnable';
    function AxcTriggerReadAbsRamData; external dll_name name 'AxcTriggerReadAbsRamData';
    function AxcTriggerWriteAbsRamData; external dll_name name 'AxcTriggerWriteAbsRamData';
    function AxcTriggerSetAbs; external dll_name name 'AxcTriggerSetAbs';
    function AxcTriggerSetAbsDouble; external dll_name name 'AxcTriggerSetAbsDouble';
    function AxcTriggerSetEncoderInput; external dll_name name 'AxcTriggerSetEncoderInput';
    function AxcTriggerGetEncoderInput; external dll_name name 'AxcTriggerGetEncoderInput';
    function AxcTableSetTriggerLevel; external dll_name name 'AxcTableSetTriggerLevel';
    function AxcTableGetTriggerLevel; external dll_name name 'AxcTableGetTriggerLevel';
    function AxcTableSetTriggerTime; external dll_name name 'AxcTableSetTriggerTime';
    function AxcTableGetTriggerTime; external dll_name name 'AxcTableGetTriggerTime';
    function AxcTableSetEncoderInput; external dll_name name 'AxcTableSetEncoderInput';
    function AxcTableGetEncoderInput; external dll_name name 'AxcTableGetEncoderInput';
    function AxcTableSetTriggerOutport; external dll_name name 'AxcTableSetTriggerOutport';
    function AxcTableGetTriggerOutport; external dll_name name 'AxcTableGetTriggerOutport';
    function AxcTableSetErrorRange; external dll_name name 'AxcTableSetErrorRange';
    function AxcTableGetErrorRange; external dll_name name 'AxcTableGetErrorRange';
    function AxcTableTriggerOneShot; external dll_name name 'AxcTableTriggerOneShot';
    function AxcTableTriggerPatternShot; external dll_name name 'AxcTableTriggerPatternShot';
    function AxcTableGetPatternShotData; external dll_name name 'AxcTableGetPatternShotData';
    function AxcTableSetTriggerMode; external dll_name name 'AxcTableSetTriggerMode';
    function AxcTableGetTriggerMode; external dll_name name 'AxcTableGetTriggerMode';
    function AxcTableSetTriggerCountClear; external dll_name name 'AxcTableSetTriggerCountClear';
    function AxcTableSetTriggerData; external dll_name name 'AxcTableSetTriggerData';
    function AxcTableGetTriggerData; external dll_name name 'AxcTableGetTriggerData';
    function AxcTableSetTriggerDataEx; external dll_name name 'AxcTableSetTriggerDataEx';
    function AxcTableGetTriggerDataEx; external dll_name name 'AxcTableGetTriggerDataEx';
    function AxcTableSetTriggerDataClear; external dll_name name 'AxcTableSetTriggerDataClear';
    function AxcTableSetEnable; external dll_name name 'AxcTableSetEnable';
    function AxcTableGetEnable; external dll_name name 'AxcTableGetEnable';
    function AxcTableReadTriggerCount; external dll_name name 'AxcTableReadTriggerCount';
    function AxcTableReadFifoStatus; external dll_name name 'AxcTableReadFifoStatus';
    function AxcTableReadFifoData; external dll_name name 'AxcTableReadFifoData';
