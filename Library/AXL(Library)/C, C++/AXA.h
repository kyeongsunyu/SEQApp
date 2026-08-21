/****************************************************************************
*****************************************************************************
**
** File Name
** ----------
**
** AXA.H
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Analog Library Header File
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


#ifndef __AXT_AXA_H__
#define __AXT_AXA_H__

#include "AXHS.h"

#ifdef __cplusplus
extern "C" {

#endif    //__cplusplus
//========== Board and verification API group of module information
//Verify if AIO module exists
DWORD    __stdcall AxaInfoIsAIOModule(DWORD *upStatus);


//Verify AIO module number
DWORD    __stdcall AxaInfoGetModuleNo(long lBoardNo, long lModulePos, long *lpModuleNo);


//Verify the number of AIO module
DWORD    __stdcall AxaInfoGetModuleCount(long *lpModuleCount);


//Verify the number of input channels of specified module
DWORD    __stdcall AxaInfoGetInputCount(long lModuleNo, long *lpCount);


//Verify the number of output channels of specified module
DWORD    __stdcall AxaInfoGetOutputCount(long lModuleNo, long *lpCount);


//Verify the first channel number of specified module
DWORD    __stdcall AxaInfoGetChannelNoOfModuleNo(long lModuleNo, long *lpChannelNo);


// Verify the first Input channel number of specified module (Inputmodule, Integration for input/output Module)
DWORD    __stdcall AxaInfoGetChannelNoAdcOfModuleNo(long lModuleNo, long *lpChannelNo);


// Verify the first output channel number of specified module (Inputmodule, Integration for input/output Module)
DWORD    __stdcall AxaInfoGetChannelNoDacOfModuleNo(long lModuleNo, long *lpChannelNo);


//Verify base board number, module position and module ID with specified module number
DWORD    __stdcall AxaInfoGetModule (long lModuleNo, long *lpBoardNo, long *lpModulePos, DWORD *upModuleID);


// Verify specified module board : Sub ID, module name, module description
//===============================================/
// support product : EtherCAT
// upModuleSubID   : EtherCAT SubID(for distinguish between EtherCAT modules)
// szModuleName         : model name of module(50 Bytes)
// szModuleDescription  : description of module(80 Bytes)
//======================================================//
DWORD    __stdcall AxaInfoGetModuleEx(long lModuleNo, DWORD *upModuleSubID, char* szModuleName, char* szModuleDescription);


//Verify Module status of specified module board
DWORD    __stdcall AxaInfoGetModuleStatus(long lModuleNo);


//========== API group of input module information search
//Verify module number with specified input channel number
DWORD    __stdcall AxaiInfoGetModuleNoOfChannelNo(long lChannelNo, long *lpModuleNo);


//Verify the number of entire channels of analog input module
DWORD    __stdcall AxaiInfoGetChannelCount(long *lpChannelCount);


//========== API group for setting and verifying of input module interrupt
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
DWORD    __stdcall AxaiEventSetChannel(long lChannelNo, HWND hWnd, DWORD uMesssage, AXT_EVENT_PROC pProc, HANDLE *pEvent);


//Set whether to use event in specified input channel
//======================================================//
// uUse       : DISABLE(0)    // Event Disable
//            : ENABLE(1)     // Event Enable
//======================================================//
DWORD    __stdcall AxaiEventSetChannelEnable(long lChannelNo, DWORD uUse);


//Verify whether to use event in specified input channel
//======================================================//
// *upUse     : DISABLE(0)    // Event Disable
//            : ENABLE(1)     // Event Enable
//======================================================//
DWORD    __stdcall AxaiEventGetChannelEnable(long lChannelNo, DWORD *upUse);


//Set whether to use event in specified multiple input channels
//======================================================//
//lSize       : Number of input channel
// uUse       : DISABLE(0)    // Event Disable
//            : ENABLE(1)     // Event Enable
//======================================================//
DWORD    __stdcall AxaiEventSetMultiChannelEnable(long lSize, long *lpChannelNo, DWORD uUse);


//Set kind of event in specified input channel
//======================================================//
// uMask      : DATA_EMPTY(1)
//            : DATA_MANY(2)
//            : DATA_SMALL(3)
//            : DATA_FULL(4)
//======================================================//
DWORD    __stdcall AxaiEventSetChannelMask(long lChannelNo, DWORD uMask);


//Verify kind of event in specified input channel
//======================================================//
// *upMask    : DATA_EMPTY(1)
//            : DATA_MANY(2)
//            : DATA_SMALL(3)
//            : DATA_FULL(4)
//======================================================//
DWORD    __stdcall AxaiEventGetChannelMask(long lChannelNo, DWORD *upMask);


//Set kind of event in specified multiple input channels
//==============================================================================//
// uMask      : DATA_EMPTY(1)
//            : DATA_MANY(2)
//            : DATA_SMALL(3)
//            : DATA_FULL(4)
//==============================================================================//
DWORD    __stdcall AxaiEventSetMultiChannelMask(long lSize, long *lpChannelNo, DWORD uMask);


//Verify event occurrence position
//==============================================================================//
// *upMode    : AIO_EVENT_DATA_UPPER(1)
//            : AIO_EVENT_DATA_LOWER(2)
//            : AIO_EVENT_DATA_FULL(3)
//            : AIO_EVENT_DATA_EMPTY(4)
//==============================================================================//
DWORD    __stdcall AxaiEventRead(long *lpChannelNo, DWORD *upMode);


//Set interrupt mask of specified module. (SIO-AI4RB is not supportive.)
//==================================================================================================//
// uMask      : SCAN_END(1)
//            : FIFO_HALF_FULL(2)
//==================================================================================================//
DWORD    __stdcall AxaiInterruptSetModuleMask(long lModuleNo, DWORD uMask);


//Verify interrupt mask of specified module
//==================================================================================================//
// *upMask    : SCAN_END(1)
//            : FIFO_HALF_FULL(2)
//==================================================================================================//
DWORD    __stdcall AxaiInterruptGetModuleMask(long lModuleNo, DWORD *upMask);


//========== API group for setting and verifying of input module parameter
//Set the input voltage range in specified input channel
//==================================================================================================//
// AI4RB
// dMinVolt    : -10V/-5V/0V
// dMaxVolt    : 10V/5V/
//
// AI16Hx
// dMinVolt    : -10V Fix
// dMaxVolt    : 10V Fix
//==================================================================================================//
DWORD    __stdcall AxaiSetRange(long lChannelNo, double dMinVolt, double dMaxVolt);


//Verify the input voltage range in specified input channel
//==================================================================================================//
// AI4RB
// *dpMinVolt    : -10V/-5V/0V
// *dpMaxVolt    : 10V/5V/
//
// AI16Hx
// *dpMaxVolt    : -10V Fix
// *dpMaxVolt    : 10V Fix
//==================================================================================================//
DWORD    __stdcall AxaiGetRange(long lChannelNo, double *dpMinVolt, double *dpMaxVolt);


//Set the allowed input voltage range in specified multiple input Modules
//==================================================================================================//
// lModuleNo   : Analog Module Number
//
// RTEX AI16F
// Mode -5~+5  : dMinVolt = -5, dMaxVolt = +5
// Mode -10~+10: dMinVolt = -10, dMaxVolt = +10
//==================================================================================================//
DWORD    __stdcall AxaiSetRangeModule(long lModuleNo, double dMinVolt, double dMaxVolt);


//Verify the input voltage range in specified input Module
//==================================================================================================//
// lModuleNo   : Analog Module Number
//
// RTEX AI16F
// *dMinVolt   : -5V, -10V
// *dMaxVolt   : +5V, +10V
//==================================================================================================//
DWORD    __stdcall AxaiGetRangeModule(long lModuleNo, double *dMinVolt, double *dMaxVolt);



//Set the allowed input voltage range in specified multiple input channels
//==================================================================================================//
// AI4RB
// dMinVolt    : -10V/-5V/0V
// dMaxVolt    : 10V/5V/
//
// AI16Hx
// dMinVolt    : -10V Fix
// dMaxVolt    : 10V Fix
//==================================================================================================//
DWORD    __stdcall AxaiSetMultiRange(long lSize, long *lpChannelNo, double dMinVolt, double dMaxVolt);


//Set trigger mode in the specified input module
//==================================================================================================//
// uTriggerMode : NORMAL_MODE(1)
//              : TIMER_MODE(2)
//              : EXTERNAL_MODE(3)
//==================================================================================================//
DWORD    __stdcall AxaiSetTriggerMode(long lModuleNo, DWORD uTriggerMode);


//Verify trigger mode in the specified input module
//==================================================================================================//
// *upTriggerMode : NORMAL_MODE(1)
//                : TIMER_MODE(2)
//                : EXTERNAL_MODE(3)
//==================================================================================================//
DWORD    __stdcall AxaiGetTriggerMode(long lModuleNo, DWORD *upTriggerMode);


//Set offset of specified input module by mVolt (mV) unit. Max -100~100mVolt
//==================================================================================================//
// dMiliVolt    : -100 ~ 100
//==================================================================================================//
DWORD    __stdcall AxaiSetModuleOffsetValue(long lModuleNo, double dMiliVolt);


//Verify offset value of specified input module. mVolt unit(mV)
//==================================================================================================//
// *dpMiliVolt    : -100 ~ 100
//==================================================================================================//
DWORD    __stdcall AxaiGetModuleOffsetValue(long lModuleNo, double *dpMiliVolt);


//==Software Timer (Normal Trigger Mode) group
//Software Trigger Mode API, Convert analog input value to A/D in the specified input channel by user , then return it in voltage value
DWORD    __stdcall AxaiSwReadVoltage(long lChannelNo, double *dpVolt);


//Software Trigger Mode API, Return analog input value in digit value to specified input channel
DWORD    __stdcall AxaiSwReadDigit(long lChannelNo, DWORD *upDigit);


//Software Trigger Mode API, Return analog input value in voltage value to specified multiple input channels
DWORD    __stdcall AxaiSwReadMultiVoltage(long lSize, long *lpChannelNo, double *dpVolt);


//Software Trigger Mode API, Return analog input value in digit value to specified multiple input channels
DWORD    __stdcall AxaiSwReadMultiDigit(long lSize, long *lpChannelNo, DWORD *upDigit);


//==Hardware Timer (Timer Trigger Mode + External Trigger Mode) group
//Hardware Trigger Mode API, Set setting value in order to use immediate mode in specified multiple channels
DWORD    __stdcall AxaiHwSetMultiAccess(long lSize, long *lpChannelNo, long *lpWordSize);


//Hardware Trigger Mode API, Convert A/D as much as number of specified, then return the voltage value
DWORD    __stdcall AxaiHwStartMultiAccess(double *dpBuffer);


//Set sampling interval to specified module by frequency unit(Hz)
//==================================================================================================//
// dSampleFreq    : 10 ~ 100000
//==================================================================================================//
DWORD    __stdcall AxaiHwSetSampleFreq(long lModuleNo, double dSampleFreq);


//Verify the setting value of sampling interval to specified module by frequency unit(Hz)
//==================================================================================================//
// *dpSampleFreq  : 10 ~ 100000
//==================================================================================================//
DWORD    __stdcall AxaiHwGetSampleFreq(long lModuleNo, double *dpSampleFreq);


//Set sampling interval to specified module by time unit (uSec)
//==================================================================================================//
// dSamplePeriod  : 100000 ~ 1000000000
//==================================================================================================//
DWORD    __stdcall AxaiHwSetSamplePeriod(long lModuleNo, double dSamplePeriod);


//Verify setting value of sampling interval to specified module by time unit(uSec)
//==================================================================================================//
// *dpSamplePeriod: 100000 ~ 1000000000
//==================================================================================================//
DWORD    __stdcall AxaiHwGetSamplePeriod(long lModuleNo, double *dpSamplePeriod);


//Set control method when the buffer is full in specified input channel
//==================================================================================================//
// uFullMode      : NEW_DATA_KEEP(0)
//                : CURR_DATA_KEEP(1)
//==================================================================================================//
DWORD    __stdcall AxaiHwSetBufferOverflowMode(long lChannelNo, DWORD uFullMode);


//Verify control method when the buffer is full in specified input channel
//==================================================================================================//
// *upFullMode    : NEW_DATA_KEEP(0)
//                : CURR_DATA_KEEP(1)
//==================================================================================================//
DWORD    __stdcall AxaiHwGetBufferOverflowMode(long lChannelNo, DWORD *upFullMode);


//control method when the buffer is full in specified multiple input channels
//==================================================================================================//
// uFullMode      : NEW_DATA_KEEP(0)
//                : CURR_DATA_KEEP(1)
//==================================================================================================//
DWORD    __stdcall AxaiHwSetMultiBufferOverflowMode(long lSize, long *lpChannelNo, DWORD uFullMode);


//Set the upper limit and lower limit of buffer in specified input channel
DWORD    __stdcall AxaiHwSetLimit(long lChannelNo, long lLowLimit, long lUpLimit);


//Verify the upper limit and lower limit of buffer in specified input channel
DWORD    __stdcall AxaiHwGetLimit(long lChannelNo, long *lpLowLimit, long *lpUpLimit);


//Set the upper limit and lower limit of buffer in multiple input channels
DWORD    __stdcall AxaiHwSetMultiLimit(long lSize, long *lpChannelNo, long lLowLimit, long lUpLimit);


//Start A/D conversion using H/W timer in specified multiple channels
DWORD    __stdcall AxaiHwStartMultiChannel(long lSize, long *lpChannelNo, long lBuffSize);


//Start A/D conversion using H/W timer in specified single channels
DWORD    __stdcall AxaiHwStartSingleChannelAdc(long lChannelNo, long lBuffSize);


//Stop continuous signal A/D conversion used H/W timer.
DWORD    __stdcall AxaiHwStopSingleChannelAdc(long lChannelNo);


//After starting of A/D conversion in specified multiple channels, manage filtering as much as specified and return into voltage
//==================================================================================================//
// lSize           : Number of input channels to use
// *lpChannelNo    : An array of channel numbers to use
// lFilterCount    : Number of data for filtering
// lBuffSize       : Number of buffers which are assigned to each channel
//==================================================================================================//
DWORD    __stdcall AxaiHwStartMultiFilter(long lSize, long *lpChannelNo, long lFilterCount, long lBuffSize);


//Stop continuous signal A/D conversion used H/W timer
DWORD    __stdcall AxaiHwStopMultiChannel(long lModuleNo);


//Inspect the numbers of data in memory buffer of specified input channel
DWORD    __stdcall AxaiHwReadDataLength(long lChannelNo, long *lpDataLength);


//Read A/D conversion data used H/W timer in specified input channel by voltage value
DWORD    __stdcall AxaiHwReadSampleVoltage(long lChannelNo, long *lpSize, double *dpVolt);


//Read A/D conversion data used H/W timer in specified input channel by digit value
DWORD    __stdcall AxaiHwReadSampleDigit(long lChannelNo, long *lpsize, DWORD *upDigit);


//========== API group of input module state check
//Inspect if there is no data in memory buffer of specified input channel
//==================================================================================================//
// *upEmpty   : FALSE(0)
//            : TRUE(1)
//==================================================================================================//
DWORD    __stdcall AxaiHwIsBufferEmpty(long lChannelNo, DWORD *upEmpty);


//Inspect if the data is more than the upper limit specified in memory buffer of specified input channel
//==================================================================================================//
// *upUpper   : FALSE(0)
//            : TRUE(1)
//==================================================================================================//
DWORD    __stdcall AxaiHwIsBufferUpper(long lChannelNo, DWORD *upUpper);


//Inspect if the data is less than the upper limit specified in memory buffer of specified input channel
//==================================================================================================//
// *upLower   : FALSE(0)
//            : TRUE(1)
//==================================================================================================//
DWORD    __stdcall AxaiHwIsBufferLower(long lChannelNo, DWORD *upLower);


//==External Trigger Mode function
//Start external trigger mode of the selected channels of specified input module.
//==================================================================================================//
// lSize           : Number of channels to use external trigger on specified input module
// *lpChannelPos   : Index of channels to use external trigger on specified input module
DWORD   __stdcall AxaiExternalStartADC(long lModuleNo, long lSize, long *lpChannelPos);
//Stop external trigger mode of specified input module.
DWORD   __stdcall AxaiExternalStopADC(long lModuleNo);
//Return FIFO status of specified input module
//==================================================================================================//
// *dwpStatus      : FIFO_DATA_EXIST(0)
//                 : FIFO_DATA_EMPTY(1)
//                 : FIFO_DATA_HALF(2)
//                 : FIFO_DATA_FULL(6)
//==================================================================================================//
DWORD   __stdcall AxaiExternalReadFifoStatus(long lModuleNo, DWORD *dwpStatus);
//Read converted A/D value from external signal of specified input module.
// lSize           : Number of channels to read converted A/D value in specified input module
// *lpChannelPos   : Index of channels to read converted A/D value in specified input module
// lDataSize       : Number of maximum data to read converted A/D value by external trigger
// lBuffSize       : Size of externally allocated data buffer
// lStartDataPos   : Starting location of data buffer saving
// *dpVolt         : Two-demensional array pointer(for receiving value of converted to A/D)
// *lpRetDataSize  : Actually assigned number to data buffer(converted A/D value)
// *dwpStatus      : Return FIFO status when read converted A/D value from Fifo(H/W Buffer)
DWORD   __stdcall AxaiExternalReadVoltage(long lModuleNo, long lSize, long *lpChannelPos, long lDataSize, long lBuffSize, long lStartDataPos, double *dpVolt, long *lpRetDataSize, DWORD *dwpStatus);

//== API group of output module information search
//Verify module number with specified output channel number
DWORD    __stdcall AxaoInfoGetModuleNoOfChannelNo(long lChannelNo, long *lpModuleNo);


//Verify entire number of channel of analog output module
DWORD    __stdcall AxaoInfoGetChannelCount(long *lpChannelCount);


//========== API group for output module setting and verification
//Set output voltage range in specified output channel
//==================================================================================================//
// AO4R
// dMinVolt    : -10V/-5V/0V
// dMaxVolt    : 10V/5V/
//
// AO2Hx
// dMinVolt    : -10V Fix
// dMaxVolt    : 10V Fix
//==================================================================================================//
DWORD    __stdcall AxaoSetRange(long lChannelNo, double dMinVolt, double dMaxVolt);


//Verify output voltage range in specified output channel
//==================================================================================================//
// AO4R
// dMinVolt    : -10V/-5V/0V
// dMaxVolt    : 10V/5V/
//
// AO2Hx
// dMinVolt    : -10V Fix
// dMaxVolt    : 10V Fix
//==================================================================================================//
DWORD    __stdcall AxaoGetRange(long lChannelNo, double *dpMinVolt, double *dpMaxVolt);


//Set output voltage range in specified multiple output channels
//==================================================================================================//
// AO4R
// dMinVolt    : -10V/-5V/0V
// dMaxVolt    : 10V/5V/
//
// AO2Hx
// dMinVolt    : -10V Fix
// dMaxVolt    : 10V Fix
//==================================================================================================//
DWORD    __stdcall AxaoSetMultiRange(long lSize, long *lpChannelNo, double dMinVolt, double dMaxVolt);


//The Input voltage is output in specified output channel
DWORD    __stdcall AxaoWriteVoltage(long lChannelNo, double dVolt);


//The Input voltage is output in specified multiple output channel
DWORD    __stdcall AxaoWriteMultiVoltage(long lSize, long *lpChannelNo, double *dpVolt);


//Verify voltage which is output in specified output channel
DWORD    __stdcall AxaoReadVoltage(long lChannelNo, double *dpVolt);


//Verify voltage which is output in specified multiple output channels
DWORD    __stdcall AxaoReadMultiVoltage(long lSize, long *lpChannelNo, double *dpVolt);

//============================ AXA User Define Pattern Generator ============================
// API function for setting 'Channel User Define Pattern Generator'
// Outputting pattern every time depending on AxaoPgSetUserInterval setting
// lLoopCnt       : '0'(Repeat input pattern infinitely), 'value' : Keep last pattern, After outputting input pattern for specified number of times
//                : (MAX : 60000)
// lPatternSize   : Number of input pattern(MAX : 8192)
DWORD   __stdcall AxaoPgSetUserPatternGenerator(long lChannelNo, long lLoopCnt, long lPatternSize, double *dpPattern);

// API function for getting 'user define pattern generator'
DWORD   __stdcall AxaoPgGetUserPatternGenerator(long lChannelNo, long *lpLoopCnt, long *lpPatternSize, double *dpPattern);

// API function for setting 'pattern generator interval' of corresponding channel
// Unit : us(Default resolution : 500uSec)
DWORD   __stdcall AxaoPgSetUserInterval(long lChannelNo, double dInterval);

// API function for getting 'pattern generator interval' of corresponding channel
DWORD   __stdcall AxaoPgGetUserInterval(long lChannelNo, double *dpInterval);

// API function for getting 'Pattern Index / Loop Cnt' of corresponding channel
// In the case of status, following status can be included.
// lpIndexNum : The index of current user pattern
// lpLoopCnt : Number of currently running loop
// dwpInBusy : Driving status of Pattern Generator
DWORD   __stdcall AxaoPgGetStatus(long lChannelNo, long *lpIndexNum, long *lpLoopCnt, DWORD *dwpInBusy);


// API function for start 'User Define Pattern Generator' of corresponding channel ('AO' output start)
// Inputting start channel number as an array
// Start pattern generator function simultaneously for input channel.
DWORD   __stdcall AxaoPgSetUserStart(long *lpChannelNo, long lSize);


// API function for stopping 'User Define Pattern Generator' of corresponding channel ('AO' output stop)
// Output value is switched to 0 volt when output is stopped
DWORD   __stdcall AxaoPgSetUserStop(long *lpChannelNo, long lSize);


// API function for clearing Pattern Data(Reset all areas to 0x00)
DWORD   __stdcall AxaPgSetUserDataReset(long lChannelNo);


// API function for setting output status by each channel when specified output module network is broken
//===============================================================================================//
// lChannelNo  : Channel number(Distributed slave products only)
// dwSetValue  : Setting value
//             : 1 --> Analog Max
//             : 2 --> Analog MIN
//             : 3 --> User Vaule(Default user value : 0V, You can change this value by 'AxaoSetNetworkErrorUserValue()')
//             : 4 --> Analog 0 V
//===============================================================================================//
DWORD   __stdcall AxaoSetNetworkErrorAct(long lChannelNo, DWORD dwSetValue);

// API function for setting output status in bytes when specified output module network is broken
//===============================================================================================//
// lChannelNo  : Channel number(Distributed slave products only)
// dVolt       : Analog output voltage(User defined value)
//===============================================================================================//
DWORD   __stdcall AxaoSetNetworkErrorUserValue(long lChannelNo, double dVolt);


#ifdef __cplusplus

}
#endif    //__cplusplus

#endif    //__AXT_AXA_H__
