/****************************************************************************
*****************************************************************************
**
** File Name
** ----------
**
** AXC.H
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Counter Library Header File
** 
**
*****************************************************************************
*****************************************************************************
**
** Source Change Indices
** ---------------------
** 
** (None)
**
**
*****************************************************************************
*****************************************************************************
**
** Website
** ---------------------
**
** http://www.ajinextek.com
**
*****************************************************************************
*****************************************************************************
*/


#ifndef __AXT_AXC_H__
#define __AXT_AXC_H__

#include "AXHS.h"
#include "AXHD.h"

#ifdef __cplusplus
extern "C" {
#endif    //__cplusplus


//========== Board and verification API group of module information
// Verifying If AIO module exists
DWORD __stdcall AxcInfoIsCNTModule(DWORD *upStatus);


// Verifying CNT module number
DWORD __stdcall AxcInfoGetModuleNo(long lBoardNo, long lModulePos, long *lpModuleNo);


// Verifying the number of CNT I/O module
DWORD __stdcall AxcInfoGetModuleCount(long *lpModuleCount);


// Verifying the Number of counter input channels for specified module
DWORD __stdcall AxcInfoGetChannelCount(long lModuleNo, long *lpCount);


// Verifying the total number of channels in system mounted counter.
DWORD __stdcall AxcInfoGetTotalChannelCount(long *lpChannelCount);


// Verifying base board number, module position and module ID with specified module number
DWORD __stdcall AxcInfoGetModule(long lModuleNo, long *lpBoardNo, long *lpModulePos, DWORD *upModuleID);


// Verifying specified module board : Sub ID, module name, module description
//======================================================/
// support product : EtherCAT
// upModuleSubID   : EtherCAT SubID(for distinguish between EtherCAT modules)
// szModuleName         : model name of module(50 Bytes)
// szModuleDescription  : description of module(80 Bytes)
//======================================================//
DWORD __stdcall AxcInfoGetModuleEx(long lModuleNo, DWORD *upModuleSubID, char* szModuleName, char* szModuleDescription);

// Verifying Module status of specified module board
DWORD __stdcall AxcInfoGetModuleStatus(long lModuleNo);


DWORD __stdcall AxcInfoGetFirstChannelNoOfModuleNo(long lModuleNo, long *lpChannelNo);
DWORD __stdcall AxcInfoGetModuleNoOfChannelNo(long lChannelNo, long *lpModuleNo);


// Setting encoder input method of counter module
// dwMethod --> 0x00 : Sign and pulse, x1 multiplication
// dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
// dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
// dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
// dwMethod --> 0x08 : Sign and pulse, x2 multiplication
// dwMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
// dwMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
// SIO-CN2CH/HPC4
// dwMethod --> 0x00 : Up/Down method, A phase : pulse, B phase : direction
// dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
// dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
// dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
DWORD __stdcall AxcSignalSetEncInputMethod(long lChannelNo, DWORD dwMethod);


// Verifying encoder input method of counter module
// *dwpUpMethod --> 0x00 : Sign and pulse, x1 multiplication
// *dwpUpMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
// *dwpUpMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
// *dwpUpMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
// *dwpUpMethod --> 0x08 : Sign and pulse, x2 multiplication
// *dwpUpMethod --> 0x09 : Increment and decrement pulses, x1 multiplication
// *dwpUpMethod --> 0x0A : Increment and decrement pulses, x2 multiplication
// SIO-CN2CH/HPC4
// dwMethod --> 0x00 : Up/Down method, A phase : pulse, B phase : direction
// dwMethod --> 0x01 : Phase-A and phase-B pulses, x1 multiplication
// dwMethod --> 0x02 : Phase-A and phase-B pulses, x2 multiplication
// dwMethod --> 0x03 : Phase-A and phase-B pulses, x4 multiplication
DWORD __stdcall AxcSignalGetEncInputMethod(long lChannelNo, DWORD* dwpUpMethod);


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

// For CNT_RECAT_SC_10
// Setting the value of Trigger Mode for each table int the counter module.
// uTrigMode : Trigger Mode 
//	 [0] CCGC_CNT_RANGE_TRIGGER   : Trigger Output when it is within the acceptable range set at the specified trigger position
//	 [2] CCGC_CNT_DISTANCE_PERIODIC_TRIGGER : The mode in which a trigger is output to a position equally spaced within the acceptable range set at the specified trigger position.
//	 [3] CCGC_CNT_PATTERN_TRIGGER : Regardless of where the specified number of outputs a frequency set trigger mode.
//	 [4] CCGC_CNT_POSITION_ON_OFF_TRIGGER : Hold the trigger output at the specified trigger position (Set in the same way as CCGC_CNT_RANGE_TRIGGER.
//											Output starts at odd number of TargerPosition and turns off at even number of positions.) 
//	 [5] CCGC_CNT_AREA_ON_OFF_TRIGGER : Specified low from position upper position to trigger to maintain output mode.

DWORD __stdcall AxcTriggerSetFunction(long lChannelNo, DWORD dwMode);


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

// For CNT_RECAT_SC_10
// Setting the value of Trigger Mode for each table int the counter module.
// uTrigMode : Trigger Mode 
//	 [0] CCGC_CNT_RANGE_TRIGGER   : Trigger Output when it is within the acceptable range set at the specified trigger position
//	 [2] CCGC_CNT_DISTANCE_PERIODIC_TRIGGER : The mode in which a trigger is output to a position equally spaced within the acceptable range set at the specified trigger position.
//	 [3] CCGC_CNT_PATTERN_TRIGGER : Regardless of where the specified number of outputs a frequency set trigger mode.
//	 [4] CCGC_CNT_POSITION_ON_OFF_TRIGGER : Hold the trigger output at the specified trigger position (Set in the same way as CCGC_CNT_RANGE_TRIGGER.
//											Output starts at odd number of TargerPosition and turns off at even number of positions.) 
//	 [5] CCGC_CNT_AREA_ON_OFF_TRIGGER : Specified low from position upper position to trigger to maintain output mode.

DWORD __stdcall AxcTriggerGetFunction(long lChannelNo, DWORD* dwpMode);


// dwUsage --> 0x00 : Trigger Not use
// dwUsage --> 0x01 : Trigger use
DWORD __stdcall AxcTriggerSetNotchEnable(long lChannelNo, DWORD dwUsage);


// *dwUsage --> 0x00 : Trigger Not use
// *dwUsage --> 0x01 : Trigger use
DWORD __stdcall AxcTriggerGetNotchEnable(long lChannelNo, DWORD* dwpUsage);




// Setting capture polarity of counter module.(External latch input polarity)
// dwCapturePol --> 0x00 : Signal OFF -> ON
// dwCapturePol --> 0x01 : Signal ON -> OFF
DWORD __stdcall AxcSignalSetCaptureFunction(long lChannelNo, DWORD dwCapturePol);


// Verifying capture polarity setting of counter module.(External latch input polarity)
// *dwCapturePol --> 0x00 : Signal OFF -> ON
// *dwCapturePol --> 0x01 : Signal ON -> OFF
DWORD __stdcall AxcSignalGetCaptureFunction(long lChannelNo, DWORD* dwpCapturePol);


// Verifying capture position of counter module.(External latch)
// *dbpCapturePos --> Location of Capture position
DWORD __stdcall AxcSignalGetCapturePos(long lChannelNo, double* dbpCapturePos);


// Verifying counter value of counter module.
// *dbpActPos --> Counter value
DWORD __stdcall AxcStatusGetActPos(long lChannelNo, double* dbpActPos);


// Setting counter value to dbActPos of counter module.
DWORD __stdcall AxcStatusSetActPos(long lChannelNo, double dbActPos);


// Setting trigger position of counter module.
// Trigger position of counter module can be set up to two.
DWORD __stdcall AxcTriggerSetNotchPos(long lChannelNo, double dbLowerPos, double dbUpperPos);


// Verifying trigger position of counter module.
DWORD __stdcall AxcTriggerGetNotchPos(long lChannelNo, double* dbpLowerPos, double* dbpUpperPos);


// Forced trigger output of counter module.
// dwOutVal --> 0x00 : Trigger output '0'
// dwOutVal --> 0x01 : Trigger output '1'
DWORD __stdcall AxcTriggerSetOutput(long lChannelNo, DWORD dwOutVal);


// Verifying status of counter module.
// Bit '0' : Carry (Only 1scan turns 'ON' When current counter value is changed to '0' over the upper limit by additional pulse)
// Bit '1' : Borrow (Only 1scan turns 'ON' When current counter value is changed to lower limit under the '0' by subtraction pulse)
// Bit '2' : Trigger output status
// Bit '3' : Latch input status
DWORD __stdcall AxcStatusGetChannel(long lChannelNo, DWORD* dwpChannelStatus);




// API for SIO-CN2CH only
//
// Setting position unit of counter module
// ex) If you need 1000pulse for move 1mm distance, Setting like -> dMoveUnitPerPulse = 0.001
//     And then, setting location-related values of all functions to 'mm' unit.
DWORD __stdcall AxcMotSetMoveUnitPerPulse(long lChannelNo, double dMoveUnitPerPulse);


// Verifying position unit of counter module.
DWORD __stdcall AxcMotGetMoveUnitPerPulse(long lChannelNo, double* dpMoveUnitPerPuls);


// Setting inversion function of encoder input counter of counter module.
// dwReverse --> 0x00 : No reversal.
// dwReverse --> 0x01 : Reversal.
DWORD __stdcall AxcSignalSetEncReverse(long lChannelNo, DWORD dwReverse);


// Returns whether the function of inverting the encoder input counter of the counter module is set.
DWORD __stdcall AxcSignalGetEncReverse(long lChannelNo, DWORD* dwpReverse);


// Selecting encoder input signal of counter module.
// dwSource -->  0x00 : 2(A/B)-Phase signal.
// dwSource -->  0x01 : Z-Phase signal.(No directionality.)
DWORD  __stdcall AxcSignalSetEncSource(long lChannelNo, DWORD dwSource);


// Verifying encoder input signal selection setting of counter module.
DWORD  __stdcall AxcSignalGetEncSource(long lChannelNo, DWORD* dwpSource);


// Setting lower limit value of trigger output range of counter module.
// Setting lower limit value of range to generate trigger output with position period.(In the case of position period trigger product)
// Setting standard position application of trigger information of start address of ram.(In the case of absolute location product)
// Unit : Set by 'AxcMotSetMoveUnitPerPulse'.
// Note : Lower limit value should be set smaller than upper limit value.
DWORD  __stdcall AxcTriggerSetBlockLowerPos(long lChannelNo, double dLowerPosition);


// Verifying lower limit value of trigger output range of counter module.
DWORD  __stdcall AxcTriggerGetBlockLowerPos(long lChannelNo, double* dpLowerPosition);


// Verifying upper limit value of trigger output range of counter module.
// Setting upper limit value of range to generate trigger output with position period.(In the case of position period trigger product).
// In the case of the product of absolute position trigger, used as location where trigger information is applied of last address of RAM(Trigger information was set).
// Unit : Setting from 'AxcMotSetMoveUnitPerPulse'
// Note : Upper limit value should be set bigger than lower limit value.
DWORD  __stdcall AxcTriggerSetBlockUpperPos(long lChannelNo, double dUpperPosition);
// Setting lower limit value of trigger output range of counter module.
DWORD  __stdcall AxcTriggerGetBlockUpperPos(long lChannelNo, double* dpUpperrPosition);


// Setting position period used for position peroid mode trigger of counter module.
// Unit : Sets from 'AxcMotSetMoveUnitPerPulse'.
DWORD  __stdcall AxcTriggerSetPosPeriod(long lChannelNo, double dPeriod);


// Verifying position period used for position peroid mode trigger of counter module.
DWORD  __stdcall AxcTriggerGetPosPeriod(long lChannelNo, double* dpPeriod);


// Setting a valid function about position increase/decrease when using trigger of position period mode of counter module.
// dwDirection -->  0x00 : Output every trigger period.(About counter increase/decrease)
// dwDirection -->  0x01 : Output every trigger period.(About counter increase)
// dwDirection -->  0x01 : Output every trigger period.(About counter decrease)
DWORD  __stdcall AxcTriggerSetDirectionCheck(long lChannelNo, DWORD dwDirection);
// Verifying setting value of 'AxcTriggerSetDirectionCheck'.
DWORD  __stdcall AxcTriggerGetDirectionCheck(long lChannelNo, DWORD* dwpDirection);


// Setting position period and range at once.(About trigger function of position period mode)
// Positioning unit : Set by 'AxcMotSetMoveUnitPerPulse'.
DWORD  __stdcall AxcTriggerSetBlock(long lChannelNo, double dLower, double dUpper, double dABSod);


// Verifying setting value of 'AxcTriggerSetBlock'.
DWORD  __stdcall AxcTriggerGetBlock(long lChannelNo, double *dpLower, double *dpUpper, double *dpABSod);


// Setting pulse width of trigger output of counter module.
// Unit : uSec
DWORD  __stdcall AxcTriggerSetTime(long lChannelNo, double dTrigTime);


// Verifying setting value of 'AxcTriggerSetTime'.
DWORD  __stdcall AxcTriggerGetTime(long lChannelNo, double* dpTrigTime);


// Setting output level of trigger output pulse of counter module.
// dwLevel -->  0x00 : Low level output.(When trigger is output)
// dwLevel -->  0x01 : High level output.(When trigger is output)
DWORD  __stdcall AxcTriggerSetLevel(long lChannelNo, DWORD dwLevel);
// Verifying setting value of 'AxcTriggerSetLevel'.
DWORD  __stdcall AxcTriggerGetLevel(long lChannelNo, DWORD* dwpLevel);


// Setting frequency for Frequency trigger output function of counter module.
// Unit : Hz, Range : 1Hz ~ 500 kHz
DWORD  __stdcall AxcTriggerSetFreq(long lChannelNo, DWORD dwFreqency);
// Verifying setting value of 'AxcTriggerSetFreq'.
DWORD  __stdcall AxcTriggerGetFreq(long lChannelNo, DWORD* dwpFreqency);


DWORD  __stdcall AxcTriggerGetTriggerOutCount(long lChannelNo, DWORD* dwpTriggerOutCount);
DWORD  __stdcall AxcTriggerSetTriggerOutCount(long lChannelNo, DWORD dwTriggerOutCount);



// Setting the value of universal output about appoint channel of counter module.
// dwOutput range : 0x00 ~ 0x0F, Four universal outputs for each channel.
DWORD  __stdcall AxcSignalWriteOutput(long lChannelNo, DWORD dwOutput);


// Verifying the value of universal output about appoint channel of counter module.
DWORD  __stdcall AxcSignalReadOutput(long lChannelNo, DWORD* dwpOutput);


// Setting the value by bit of universal output about appoint channel of counter module.
// lBitNo range : 0 ~ 3, Four universal outputs for each channel.
DWORD  __stdcall AxcSignalWriteOutputBit(long lChannelNo, long lBitNo, DWORD uOnOff);
// Verifying the value by bit of universal output about appoint channel of counter module.
// lBitNo range : 0 ~ 3
DWORD  __stdcall AxcSignalReadOutputBit(long lChannelNo,long lBitNo, DWORD *upOnOff);


// Check the general-purpose input value for the designated channel of the counter module.
DWORD  __stdcall AxcSignalReadInput(long lChannelNo, DWORD* dwpInput);


// Verifying the value by bit of universal input about appoint channel of counter module.
// lBitNo range : 0 ~ 3
DWORD  __stdcall AxcSignalReadInputBit(long lChannelNo, long lBitNo, DWORD *upOnOff);


// Activating trigger output of counter module.
// Sets whether the trigger output will be finally output according to the currently set function.
DWORD  __stdcall AxcTriggerSetEnable(long lChannelNo, DWORD dwUsage);


// Verifying setting value of 'AxcTriggerSetEnable'.
DWORD  __stdcall AxcTriggerGetEnable(long lChannelNo, DWORD* dwpUsage);


// Verifying RAM contents for absolute trigger function of counter module.
// dwAddr range : 0x0000 ~ 0x1FFFF;
DWORD  __stdcall AxcTriggerReadAbsRamData(long lChannelNo, DWORD dwAddr, DWORD* dwpData);


// Setting RAM contents for absolute trigger function of counter module.
// dwAddr range : 0x0000 ~ 0x1FFFF;
DWORD  __stdcall AxcTriggerWriteAbsRamData(long lChannelNo, DWORD dwAddr, DWORD dwData);


// Setting RAM contents at once for absolute trigger function of counter module.
// dwTrigNum range : ~ 0x20000  In the case of *RTEX CNT2  0x200*
// dwDirection --> 0x0 : Input trigger information first about lower limit trigger position. Used for trigger output(In direction of increasing position).
// dwDirection --> 0x1 : Input trigger information first about upper limit trigger position. Used for trigger output(In direction of decreasing position).
DWORD  __stdcall AxcTriggerSetAbs(long lChannelNo, DWORD dwTrigNum, DWORD* dwTrigPos, DWORD dwDirection);


// Set the contents of the RAM required for the absolute position trigger function of the counter module at once.
// dwTrigNum range : 0 ~ 0x20000 (RTEX CNT2 : 0 ~ 0x200)
// dwDirection     : (0) Enter the trigger information for the lower limit trigger position. Used for trigger output in the direction of increasing position.
//                   (1) Enter the trigger information for the upper limit trigger position. Used for trigger output in the direction of decreasing position.
// dTrigPos        : Use trigger position of counter module as double type
DWORD  __stdcall AxcTriggerSetAbsDouble(long lChannelNo, DWORD dwTrigNum, double* dTrigPos, DWORD dwDirection);

// Setting the value of Encoder Input signal to be assigned to the counter module.
// dwEncoderInput [0-3]: One of the four encoder signals entered into the counter module.
DWORD __stdcall AxcTriggerSetEncoderInput(long lChannelNo, DWORD dwEncoderInput);
// Verifying the value of assigned encoder input signal from the counter module
DWORD __stdcall AxcTriggerGetEncoderInput(long lChannelNo, DWORD* dwpEncoderInput);


// Setting the value of Level of the trigger output assigned to each table in the counter module
// uLevel : Active Level of Trigger Output Signal
//	 [0]  : 'Low' level output at trigger output.
//	 [1]  : 'High' level output at trigger output.
DWORD  __stdcall AxcTableSetTriggerLevel(long lModuleNo, long lTablePos, DWORD uLevel);
// Verifying the value of Level of the trigger output specified in each table in the counter module
DWORD  __stdcall AxcTableGetTriggerLevel(long lModuleNo, long lTablePos, DWORD* upLevel);

// Setting the value of Level of the Pulse width assigned to each table in the counter module
// dTriggerTimeUSec : [Default 500ms], Specify in us units
DWORD  __stdcall AxcTableSetTriggerTime(long lModuleNo, long lTablePos, double dTriggerTimeUSec);
// Verifying the value of Pulse width of the trigger output specified in each table in the counter module
DWORD  __stdcall AxcTableGetTriggerTime(long lModuleNo, long lTablePos, double* dpTriggerTimeUSec);

// Setting the value of Encoder Input signal to be assigned to the counter module.
// uEncoderInput1 [0-3]:  One of the four encoder signals entered into the counter module.
// uEncoderInput2 [0-3]:  One of the four encoder signals entered into the counter module.
DWORD  __stdcall AxcTableSetEncoderInput(long lModuleNo, long lTablePos, DWORD uEncoderInput1, DWORD uEncoderInput2);
// Verifying the value of assigned encoder input signal from the counter module
DWORD  __stdcall AxcTableGetEncoderInput(long lModuleNo, long lTablePos, DWORD* upEncoderInput1, DWORD* upEncoderInput2);


// Setting the value of Trigger output port to be assigned to each table in the couynter module.
// uTriggerOutport [0x0-0xF]: Bit0: Trigger Output 0, Bit1: Trigger Output 1, Bit2: Trigger Output, Bit3: Trigger Output 
// Ex) 0x3(3)	: Output a trigger signal to output 0,1
//	   0xF(255) : Output a trigger signal to output 0,1,2,3
DWORD  __stdcall AxcTableSetTriggerOutport(long lModuleNo, long lTablePos, DWORD uTriggerOutport);
// Verifying the value of Trigger output port from the counter module
DWORD  __stdcall AxcTableGetTriggerOutport(long lModuleNo, long lTablePos, DWORD* upTriggerOutport);


//Setting the value of Error Range for the trigger position set for each table int the counter module.
// dErrorRange	: Error Range for the position of the trigger
DWORD  __stdcall AxcTableSetErrorRange(long lModuleNo, long lTablePos, double dErrorRange);
// Verifying the value of Error Range for the trigger position set for each table int the counter module.
DWORD  __stdcall AxcTableGetErrorRange(long lModuleNo, long lTablePos, double* dpErrorRange);

// Generate one shot trigger with the information set on each table in the counter module(trigger output port, trigger pulse width)
// �� Note : 1) If the trigger is disabled, this function automatically make enable
//			 2) Incase of Trigger Mode (HPC4_PATTERN_TRIGGER), thie function automatically change trigger mode to HPC4_RANGE_TRIGGER
//			 2) Incase of Trigger Mode (CCGC_CNT_PATTERN_TRIGGER), thie function automatically change trigger mode to CCGC_CNT_RANGE_TRIGGER
DWORD  __stdcall AxcTableTriggerOneShot(long lModuleNo, long lTablePos);

// Trigger with the Information set on each table in the counter module (Trigger output port, trigger pulse width), at the frequency set by the specified number.
// lTriggerCount	 : Number of trigger outputs to generate at the specified frequency
// uTriggerFrequency : Frequency Value
// �� ���� :  1) If the trigger is disabled, this function automatically make enable 
//			 2) Incase of Trigger Mode (Not HPC4_PATTERN_TRIGGER), thie function automatically change trigger mode to HPC4_PATTERN_TRIGGER
//			 3) Incase of Trigger Mode (Not CCGC_CNT_PATTERN_TRIGGER), thie function automatically change trigger mode to CCGC_CNT_PATTERN_TRIGGER
DWORD  __stdcall AxcTableTriggerPatternShot(long lModuleNo, long lTablePos, long lTriggerCount, DWORD uTriggerFrequency);
// Return the value of trigger setup information(frequency, counter) set for each table in the counter module.
DWORD  __stdcall AxcTableGetPatternShotData(long lModuleNo, long lTablePos, long* lpTriggerCount, DWORD* upTriggerFrequency);

// For SIO-HPC4
// Setting the value of Trigger Mode for each table int the counter module.
// uTrigMode : Trigger Mode 
//	 [0] HPC4_RANGE_TRIGGER   : Trigger Output when it is within the acceptable range set at the specified trigger position
//	 [1] HPC4_VECTOR_TRIGGER  : The mode in which a trigger is output when the vector direction matches the allowable range set at the specified trigger position.
//	 [3] HPC4_PATTERN_TRIGGER : Regardless of where the specified number of outputs a frequency set trigger mode.

// For CNT_RECAT_SC_10
// Setting the value of Trigger Mode for each table int the counter module.
// uTrigMode : Trigger Mode 
//	 [0] CCGC_CNT_RANGE_TRIGGER   : Trigger Output when it is within the acceptable range set at the specified trigger position
//	 [1] CCGC_CNT_VECTOR_TRIGGER  : The mode in which a trigger is output when the vector direction matches the allowable range set at the specified trigger position.
//	 [2] CCGC_CNT_DISTANCE_PERIODIC_TRIGGER : The mode in which a trigger is output to a position equally spaced within the acceptable range set at the specified trigger position.
//	 [3] CCGC_CNT_PATTERN_TRIGGER : Regardless of where the specified number of outputs a frequency set trigger mode.
//	 [4] CCGC_CNT_POSITION_ON_OFF_TRIGGER : Hold the trigger output at the specified trigger position (Set in the same way as CCGC_CNT_RANGE_TRIGGER.
//											Output starts at odd number of TargerPosition and turns off at even number of positions.) 
//	 [5] CCGC_CNT_AREA_ON_OFF_TRIGGER : Specified low from position upper position to trigger to maintain output mode.
DWORD  __stdcall AxcTableSetTriggerMode(long lModuleNo, long lTablePos, DWORD uTrigMode);
// Verifying the value of Trigger Mode for each table int the counter module.
DWORD  __stdcall AxcTableGetTriggerMode(long lModuleNo, long lTablePos, DWORD* upTrigMode); 	
// Initialize the cumulative number of triggers output for each table in the counter module.
DWORD  __stdcall AxcTableSetTriggerCountClear(long lModuleNo, long lTablePos);

// Setting the information to set the trigger signal in the absolute Position (For 2D)
// lTriggerDataCount : Total number of trigger information to set
//	 [-1, 0]		 : Initializing registered trigger information data
// dpTriggerData	 : Absolute position trigger information (number of corresponding arrays should be lTriggerDataCount * 2)
//	 *[0, 1]		 : X[0], Y[0] 
// lpTriggerCount	 : Set the number of triggers to be generated when the trigger condition is satisfied to the array
// dpTriggerInterval : Set the interval in frequency to be maintained when triggering a trigger as continuously as TriggerCount
// ��Note : 
//	  1) The number of arrays for each transfer factor should be used with caution. Specifying an array that is less than the factors used internally may result in memory errors.
//	  2) Trigger Mode automatically changed to HPC4_RANGE_TRIGGER
//	  3) Disable Trigger inside the function, proceed to all settings, and enable it again after completion
DWORD  __stdcall AxcTableSetTriggerData(long lModuleNo, long lTablePos, long lTriggerDataCount, double* dpTriggerData, long* lpTriggerCount, double* dpTriggerInterval);
// Set triggers set to output a trigger signal to each table of the counter module information.
// �� Note : For each registered up to trigger the number of data on the table below when you don't know ahead of the number of triggers, such as data and use.
// Ex)		1) AxcTableGetTriggerData(lModuleNo, lTablePos, &lTriggerDataCount, NULL, NULL, NULL);
//			2) dpTriggerData	 = new double[lTriggerDataCount * 2];
//			3) lpTriggerCount	 = new long[lTriggerDataCount];
//			4) dpTriggerInterval = new double[lTriggerDataCount];  
DWORD  __stdcall AxcTableGetTriggerData(long lModuleNo, long lTablePos, long* lpTriggerDataCount, double* dpTriggerData, long* lpTriggerCount, double* dpTriggerInterval);


// For SIO-HPC4 ///////////////////////////
// Setting the information required to output the trigger signal at each table in the counter module in a different way than the AxcTableSetTriggerData function.
// lTriggerDataCount : Total number of trigger information to set
// uOption : specify the data entry method for the dpTriggerData array
//	 [0]   : Enter the order X Pos[0], Y Pos[0], X Pos[1], and Y Pos[1] into the dpTriggerData array.
//	 [1]   : Enter X Pos[0], Y Pos[0], Count, Inteval, X Pos[1], Y Pos[1], Count, and Inteval in order of dpTriggerData array.
// ��Note : 
//	  1) The number of arrays for each transfer factor should be used with caution. Specifying an array that is less than the factors used internally may result in memory errors.
//	  2) Trigger Mode automatically changed to HPC4_RANGE_TRIGGER
//	  3) Disable Trigger inside the function, proceed to all settings, and enable it again after completion
// For CNT_RECAT_SC_10/////////////////////////// 
// Setting the information required to output the trigger signal at each table in the counter module in a different way than the AxcTableSetTriggerData function.
// lTriggerDataCount : Total number of trigger information to set
// uOption : Reserved
// dpTriggerData : Trigger Data
//	Case : CCGC_CNT_RANGE_TRIGGER 
//		Enter the order X Pos[0], Y Pos[0], X Pos[1], and Y Pos[1] into the dpTriggerData array.
//	Case : CCGC_CNT_VECTOR_TRIGGER 
//		In an array dptriggerdata x pos [0], y pos [0], x unitvector y and [0] unitvector [0] x pos y and [1] pos x, [1], unitvector y, [1], unitvector [1] Enter in the order.
//	Case : CCGC_CNT_POSITION_ON_OFF_TRIGGER 
//		Enter the order X Pos[0], Y Pos[0], X Pos[1], and Y Pos[1] into the dpTriggerData array.	
// ��Note : 
//	  1) The number of arrays for each transfer factor should be used with caution. Specifying an array that is less than the factors used internally may result in memory errors.

DWORD  __stdcall AxcTableSetTriggerDataEx(long lModuleNo, long lTablePos, long lTriggerDataCount, DWORD uOption, double* dpTriggerData);
// For SIO-HPC4  ///////////////////////////
// Set triggers set to output a trigger signal to each table of the counter module information.
// �� Note : For each registered up to trigger the number of data on the table below when you don't know ahead of the number of triggers, such as data and use.
// Ex)		1) AxcTableGetTriggerDataEx(lModuleNo, lTablePos, &lTriggerDataCount, &uOption, NULL);
//			2) if(uOption == 0) : dpTriggerData 	= new double[lTriggerDataCount * 2];
//			3) if(uOption == 1) : dpTriggerData 	= new double[lTriggerDataCount * 4];
// For CNT_RECAT_SC_10/////////////////////////// 
// Set triggers set to output a trigger signal to each table of the counter module information.
// �� Note : For each registered up to trigger the number of data on the table below when you don't know ahead of the number of triggers, such as data and use.
// uOption : Reserved
// Ex)		1) AxcTableGetTriggerDataEx(lModuleNo, lTablePos, &lTriggerDataCount, &uOption, NULL);
//	Case : CCGC_CNT_RANGE_TRIGGER 
//		dpTriggerData	  = new double[lTriggerDataCount * 2];
//	Case : CCGC_CNT_VECTOR_TRIGGER 
//		dpTriggerData	  = new double[lTriggerDataCount * 4];
//	Case : CCGC_CNT_POSITION_ON_OFF_TRIGGER 
//		dpTriggerData	  = new double[lTriggerDataCount * 2];
DWORD  __stdcall AxcTableGetTriggerDataEx(long lModuleNo, long lTablePos, long* lpTriggerDataCount,  DWORD* upOption, double* dpTriggerData);

// Deletes all trigger data set in the specified table in the counter module and all data in the H/W FIFO.
DWORD  __stdcall AxcTableSetTriggerDataClear(long lModuleNo, long lTablePos);

// Enables the trigger output function of the specified table on the counter module.
// uEnable : Whether or not to use the feature output a trigger settings.
// �� Note : 1) DISABLE during trigger output causes the output to stop immediately
//			 2) AxcTableTriggerOneShot, AxcTableGetPatternShotData,AxcTableSetTriggerData, AxcTableGetTriggerDataEx functions automatically call ENABLE
DWORD  __stdcall AxcTableSetEnable(long lModuleNo, long lTablePos, DWORD uEnable);
// Trigger of the table specified by the module output function is to verify whether the operation of the counter.
DWORD  __stdcall AxcTableGetEnable(long lModuleNo, long lTablePos, DWORD* upEnable);		

// Check the number generated using a table specifying the module's counter trigger.
// lpTriggerCount : eturns the number of trigger outputs that have been output to date, initializes to the AxcTableSetTriggerCountClear function
DWORD  __stdcall AxcTableReadTriggerCount(long lModuleNo, long lTablePos, long* lpTriggerCount);	

// Check the status of the H/W trigger data FIFO assigned to the specified table in the counter module.
// lpCount1[0~500] :Number of data entered in H/W FIFO where the first (X) position of the 2D trigger position data is being held
// upStatus1 : Status of H/W FIFO with the first (X) position of the 2D trigger position data at rest
//	 [Bit 0] : Data Empty
//	 [Bit 1] : Data Full
//	 [Bit 2] : Data Valid
// lpCount2[0~500] : Number of data entered in H/W FIFO where the second (Y) position of the 2D trigger position data 
// upStatus2 : Status of H/W FIFO with the second (y) position of the 2D trigger position data at rest
//	 [Bit 0] : Data Empty
//	 [Bit 1] : Data Full
//	 [Bit 2] : Data Valid
DWORD  __stdcall AxcTableReadFifoStatus(long lModuleNo, long lTablePos, long* lpCount1, DWORD* upStatus1, long* lpCount2, DWORD* upStatus2);

// Check the current position data value of the H/W trigger data FIFO assigned to the specified table in the counter module.
// dpTopData1 : 2D H/W First(X) Position Top Data.
// dpTopData1 : 2D H/W Second(Y) Position Top Data
DWORD  __stdcall AxcTableReadFifoData(long lModuleNo, long lTablePos, double* dpTopData1, double* dpTopData2);

// Setting the value of dimension of counter module.
// dwDimension : 1D/2D Value
//	[0] : 1D
//	[1] : 2D
DWORD  __stdcall AxcTableSetDimension(long lModuleNo, long lTablePos, DWORD dwDimension);
// Verifying the value of dimension of counter module.
// dwpDimension : 1D/2D Value
//	[0] : 1D
//	[1] : 2D
DWORD  __stdcall AxcTableGetDimension(long lModuleNo, long lTablePos, DWORD* dwpDimension);

// Setting lower limit value of trigger output range of counter module.
// Setting lower limit value of range to generate trigger output with position period.(In the case of position period trigger product)
// Setting standard position application of trigger information of start address of ram.(In the case of absolute location product)
// Unit : Set by 'AxcMotSetMoveUnitPerPulse'.
// Note : Lower limit value should be set smaller than upper limit value.
DWORD  __stdcall AxcTableSetBlockLowerPos(long lModuleNo, long lTablePos, double dLowerPosition1, double dLowerPosition2);

// Verifying lower limit value of trigger output range of counter module.
DWORD  __stdcall AxcTableGetBlockLowerPos(long lModuleNo, long lTablePos, double* dpLowerPosition1, double* dpLowerPosition2);

// Setting upper limit value of trigger output range of counter module.
// Setting upper limit value of range to generate trigger output with position period.(In the case of position period trigger product).
// In the case of the product of absolute position trigger, used as location where trigger information is applied of last address of RAM(Trigger information was set).
// Unit : Setting from 'AxcMotSetMoveUnitPerPulse'
// Note : Upper limit value should be set bigger than lower limit value.
DWORD  __stdcall AxcTableSetBlockUpperPos(long lModuleNo, long lTablePos, double dUpperPosition1, double dUpperPosition2);

// Verifying upper limit value of trigger output range of counter module.
DWORD  __stdcall AxcTableGetBlockUpperPos(long lModuleNo, long lTablePos, double* dpUpperPosition1, double* dpUpperPosition2);

// Generates a trigger with the information set on each table in the counter module(trigger output port, trigger pulse width), equal spacing to the specified position within the allowable range.
// dDistance     : position interval of trigger made
// �� Note : 1) If Trigger is disabled, this function is automatically causes the trigger with patterns through enable. 
//           2) If Trigger mode is not in CCGC_CNT_DISTANCE_PERIODIC_TRIGGER mode, this tunction automatically changes the trigger mode CCGC_CNT_DISTANCE_PERIODIC_TRIGGER
DWORD  __stdcall AxcTableTriggerDistancePatternShot(long lModuleNo, long lTablePos, double dDistance);

// Check the trigger setup information(interal between Trigger)set on each table in the counter module.
DWORD  __stdcall AxcTableGetDistancePatternShotData(long lModuleNo, long lTablePos, double* dpDistance);

// For CNT_RECAT_SC_10/////////////////////////// 
// Set triggers set to output a trigger signal to each channel of the counter module information.
// �� Note : For each registered up to trigger the number of data on the channel below when you don't know ahead of the number of triggers, such as data and use.
// Ex)      1) AxcTriggerGetAbs(long lChannelNo, DWORD* dwpTrigNum, DWORD* dwTrigPos, DWORD dwDirection);
//          2) dwpTrigPos     = new uint[dwpTrigPos];  
DWORD __stdcall AxcTriggerGetAbs(long lChannelNo, DWORD* dwpTrigNum, DWORD* dwpTrigPos);
// Check the status of the H/W trigger data FIFO assigned to the specified channel in the counter module.
// lpCount[0~500] :Number of data entered in H/W FIFO where the first position of the trigger position data is being held
// upStatus : Status of H/W FIFO with the first position of the trigger position data at rest
//	 [Bit 0] : Data Empty
//	 [Bit 1] : Data Full
//	 [Bit 2] : Data Valid
DWORD  __stdcall AxcTriggerReadFifoStatus(long lChannelNo, long* lpCount, DWORD* upStatus);
// Check the current position data value of the H/W trigger data FIFO assigned to the specified channel in the counter module.
// dpTopData : First Position Top Data.
DWORD  __stdcall AxcTriggerReadFifoData(long lChannelNo, double* dpTopData);	

// Trigger with the Information set on each channel in the counter module (Trigger output port, trigger pulse width), at the frequency set by the specified number.
// lTriggerCount	 : Number of trigger outputs to generate at the specified frequency
// uTriggerFrequency : Frequency Value
// �� ���� :  1) If the trigger is disabled, this function automatically make enable 
//			 2) Incase of Trigger Mode (Not HPC4_PATTERN_TRIGGER), thie function automatically change trigger mode to HPC4_PATTERN_TRIGGER
//			 3) Incase of Trigger Mode (Not CCGC_CNT_PATTERN_TRIGGER), thie function automatically change trigger mode to CCGC_CNT_PATTERN_TRIGGER
DWORD  __stdcall AxcTriggerPatternShot(long lChannelNo, long lTriggerCount, DWORD uTriggerFrequency);

// Return the value of trigger setup information(frequency, counter) set for each table in the counter module.
DWORD  __stdcall AxcTriggerGetPatternShotData(long lChannelNo, long* lpTriggerCount, DWORD* upTriggerFrequency);
// Initialize the cumulative number of triggers output for each channel in the counter module.
DWORD  __stdcall AxcTriggerSetTriggerCountClear(long lChannelNo);
// Check the number generated using a channel specifying the module's counter trigger.
// lpTriggerCount : eturns the number of trigger outputs that have been output to date, initializes to the AxcTriggerSetTriggerCountClear function
DWORD  __stdcall AxcTriggerReadTriggerCount(long lChannelNo, long* lpTriggerCount);
// Generates a trigger with the information set on each channel in the counter module(trigger output port, trigger pulse width), equal spacing to the specified position within the allowable range.
// dDistance	 : position interval of trigger made
// �� Note : 1) If Trigger is disabled, this function is automatically causes the trigger with patterns through enable. 
//			 2) If Trigger mode is not in CCGC_CNT_DISTANCE_PERIODIC_TRIGGER mode, this tunction automatically changes the trigger mode CCGC_CNT_DISTANCE_PERIODIC_TRIGGER
DWORD  __stdcall AxcTriggerDistancePatternShot(long lChannelNo,double dDistance);
// Check the trigger setup information(interal between Trigger)set on each channel in the counter module.
DWORD  __stdcall AxcTriggerGetDistancePatternShotData(long lChannelNo,double* dpDistance);

// Setting the value of Trigger output port to be assigned to each channel in the couynter module.
// uTriggerOutport [0x0-0xF]: Bit0: Trigger Output 0, Bit1: Trigger Output 1, Bit2: Trigger Output, Bit3: Trigger Output 
// Ex) 0x3(3)	: Output a trigger signal to output 0,1
//	   0xF(255) : Output a trigger signal to output 0,1,2,3
DWORD __stdcall AxcTriggerSetTriggerOutport(long lChannelNo, DWORD dwTriggerOutPort);
// Verifying the value of Trigger output port from the counter module
DWORD __stdcall AxcTriggerGetTriggerOutport(long lChannelNo, DWORD* dwpTriggerOutPort);

DWORD __stdcall AxcTriggerOneShot(long lChannelNo);

#ifdef __cplusplus
}
#endif    //__cplusplus

#endif    //__AXT_AXC_H__
