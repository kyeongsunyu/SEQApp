
#ifndef __AXT_AXDEV_H__
#define __AXT_AXDEV_H__

#include "AXHD.h"

#ifdef __cplusplus
extern "C" {
#endif    //__cplusplus


// Use Board Number and find Board Address
DWORD    __stdcall AxlGetBoardAddress(long lBoardNo, DWORD *upBoardAddress);
// Use Board Number and find Board ID
DWORD    __stdcall AxlGetBoardID(long lBoardNo, DWORD *upBoardID);
// Use Board Number and find Board Version
DWORD    __stdcall AxlGetBoardVersion(long lBoardNo, DWORD *upBoardVersion);
// Use Board Number/Module Position and find Module ID
DWORD    __stdcall AxlGetModuleID(long lBoardNo, long lModulePos, DWORD *upModuleID);
// Use Board Number/Module Position and find Module Version
DWORD    __stdcall AxlGetModuleVersion(long lBoardNo, long lModulePos, DWORD *upModuleVersion);

DWORD    __stdcall AxlGetModuleNodeInfo(long lBoardNo, long lModulePos, long *upNetNo, DWORD *upNodeAddr);


// Only for PCI-R1604[RTEX]
// Writing user data to embedded flash memory
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
// Note) Delay time is required for completing writing operation to Flash(Max. 17mSec)
DWORD    __stdcall AxlSetDataFlash(long lBoardNo, long lPageAddr, long lBytesNum, BYTE *bpSetData);



// ML3 Only, Use Board and Set the EStopInterLock Parameter
// dwInterLock    : (0) Not use(Default value)
//                  (1) Using function. When E-STOP signal is externally applied after setting function, E-STOP drive command is executed to the motion control node connected to the board.
// dwDigFilterVal : Setting range of input filter constant (1~40). Unit communication Cyclic time
// Set EstopInterLock function by using dwInterLock and dwDigFilterVal on Board
DWORD    __stdcall AxlSetEStopInterLock(long lBoardNo, DWORD dwInterLock, DWORD dwDigFilterVal);
// ML3 Only, Use Board and Get the EStopInterLock Parameter
DWORD    __stdcall AxlGetEStopInterLock(long lBoardNo, DWORD *dwInterLock, DWORD  *dwDigFilterVal);
// ML3 Only, Read the External ESTOP Signal status
DWORD    __stdcall AxlReadEStopInterLock(long lBoardNo, DWORD *dwInterLock);

// Reading datas from embedded flash memory
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
DWORD    __stdcall AxlGetDataFlash(long lBoardNo, long lPageAddr, long lBytesNum, BYTE *bpGetData);


// Use Board Number/Module Position and find AIO Module Number
DWORD    __stdcall AxaInfoGetModuleNo(long lBoardNo, long lModulePos, long *lpModuleNo);
// Use Board Number/Module Position and find DIO Module Number
DWORD    __stdcall AxdInfoGetModuleNo(long lBoardNo, long lModulePos, long *lpModuleNo);


// IPCOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommand(long lAxisNo, IPCOMMAND sCommand);
// 8bit IPCOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommandData08(long lAxisNo, IPCOMMAND sCommand, DWORD uData);
// Get 8bit IPCOMMAND at an appoint axis
DWORD    __stdcall AxmGetCommandData08(long lAxisNo, IPCOMMAND sCommand, DWORD *upData);
// 16bit IPCOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommandData16(long lAxisNo, IPCOMMAND sCommand, DWORD uData);
// Get 16bit IPCOMMAND at an appoint axis
DWORD    __stdcall AxmGetCommandData16(long lAxisNo, IPCOMMAND sCommand, DWORD *upData);
// 24bit IPCOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommandData24(long lAxisNo, IPCOMMAND sCommand, DWORD uData);
// Get 24bit IPCOMMAND at an appoint axis
DWORD    __stdcall AxmGetCommandData24(long lAxisNo, IPCOMMAND sCommand, DWORD *upData);
// 32bit IPCOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommandData32(long lAxisNo, IPCOMMAND sCommand, DWORD uData);
// Get 32bit IPCOMMAND at an appoint axis
DWORD    __stdcall AxmGetCommandData32(long lAxisNo, IPCOMMAND sCommand, DWORD *upData);


// QICOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommandQi(long lAxisNo, QICOMMAND sCommand);
// 8bit QICOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommandData08Qi(long lAxisNo, QICOMMAND sCommand, DWORD uData);
// Get 8bit QICOMMAND at an appoint axis
DWORD    __stdcall AxmGetCommandData08Qi(long lAxisNo, QICOMMAND sCommand, DWORD *upData);
// 16bit QICOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommandData16Qi(long lAxisNo, QICOMMAND sCommand, DWORD uData);
// Get 16bit QICOMMAND at an appoint axis
DWORD    __stdcall AxmGetCommandData16Qi(long lAxisNo, QICOMMAND sCommand, DWORD *upData);
// 24bit QICOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommandData24Qi(long lAxisNo, QICOMMAND sCommand, DWORD uData);
// Get 24bit QICOMMAND at an appoint axis
DWORD    __stdcall AxmGetCommandData24Qi(long lAxisNo, QICOMMAND sCommand, DWORD *upData);
// 32bit QICOMMAND Setting at an appoint axis
DWORD    __stdcall AxmSetCommandData32Qi(long lAxisNo, QICOMMAND sCommand, DWORD uData);
// Get 32bit QICOMMAND at an appoint axis
DWORD    __stdcall AxmGetCommandData32Qi(long lAxisNo, QICOMMAND sCommand, DWORD *upData);


// Get Port Data at an appoint axis - IP
DWORD    __stdcall AxmGetPortData(long lAxisNo,  WORD wOffset, DWORD *upData);
// Port Data Setting at an appoint axis - IP
DWORD    __stdcall AxmSetPortData(long lAxisNo, WORD wOffset, DWORD dwData);
// Get Port Data at an appoint axis - QI
DWORD    __stdcall AxmGetPortDataQi(long lAxisNo, WORD byOffset, WORD *wData);
// Port Data Setting at an appoint axis - QI
DWORD    __stdcall AxmSetPortDataQi(long lAxisNo, WORD byOffset, WORD wData);


// Set the script at an appoint axis.  - IP
// sc    : Script number (1 - 4)
// event : Define an event SCRCON to happen.
//         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
// cmd   : Define a selection SCRCMD however we change any content
// data  : Selection to change any Data.
DWORD    __stdcall AxmSetScriptCaptionIp(long lAxisNo, long sc, DWORD event, DWORD data);
// Return the script at an appoint axis.  - IP
DWORD    __stdcall AxmGetScriptCaptionIp(long lAxisNo, long sc, DWORD *event, DWORD *data);


// Set the script at an appoint axis.  - QI
// sc    : Script number (1 - 4)
// event : Define an event SCRCON to happen.
//         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
// cmd   : Define a selection SCRCMD however we change any content
// data  : Selection to change any Data.
DWORD    __stdcall AxmSetScriptCaptionQi(long lAxisNo, long sc, DWORD event, DWORD cmd, DWORD data);
// Return the script at an appoint axis. - QI
DWORD    __stdcall AxmGetScriptCaptionQi(long lAxisNo, long sc, DWORD *event, DWORD *cmd, DWORD *data);


// Clear orders a script inside Queue Index at an appoint axis
// uSelect IP.
// uSelect(0): Script Queue Index Clear.
//        (1): Caption Queue Index Clear.
// uSelect QI.
// uSelect(0): Script Queue 1 Index Clear.
//        (1): Script Queue 2 Index Clear.
DWORD    __stdcall AxmSetScriptCaptionQueueClear(long lAxisNo, DWORD uSelect);


// Return Index of a script inside Queue at an appoint axis.
// uSelect IP
// uSelect(0): Read Script Queue Index
//        (1): Read Caption Queue Index
// uSelect QI.
// uSelect(0): Read Script Queue 1 Index
//        (1): Read Script Queue 2 Index
DWORD    __stdcall AxmGetScriptCaptionQueueCount(long lAxisNo, DWORD *updata, DWORD uSelect);


// Return Data number of a script inside Queue at an appoint axis.
// uSelect IP
// uSelect(0): Read Script Queue Data
//        (1): Read Caption Queue Data
// uSelect QI.
// uSelect(0): Read Script Queue 1 Data
//        (1): Read Script Queue 2 Data
DWORD    __stdcall AxmGetScriptCaptionQueueDataCount(long lAxisNo, DWORD *updata, DWORD uSelect);


// Read an inside data.
//DWORD    __stdcall AxmGetOptimizeDriveData(long lAxisNo, double dMinVel, double dVel, double dAccel, double  dDecel,



// Setting up confirmes the register besides within the board by Byte.
DWORD    __stdcall AxmBoardWriteByte(long lBoardNo, WORD wOffset, BYTE byData);
DWORD    __stdcall AxmBoardReadByte(long lBoardNo, WORD wOffset, BYTE *byData);


// Setting up confirmes the register besides within the board by Word.
DWORD    __stdcall AxmBoardWriteWord(long lBoardNo, WORD wOffset, WORD wData);
DWORD    __stdcall AxmBoardReadWord(long lBoardNo, WORD wOffset, WORD *wData);


// Setting up confirmes the register besides within the board by DWord.
DWORD    __stdcall AxmBoardWriteDWord(long lBoardNo, WORD wOffset, DWORD dwData);
DWORD    __stdcall AxmBoardReadDWord(long lBoardNo, WORD wOffset, DWORD *dwData);


// Setting up confirmes the register besides within the Module by Byte.
DWORD    __stdcall AxmModuleWriteByte(long lBoardNo, long lModulePos, WORD wOffset, BYTE byData);
DWORD    __stdcall AxmModuleReadByte(long lBoardNo, long lModulePos, WORD wOffset, BYTE *byData);


// Setting up confirmes the register besides within the Module by Word.
DWORD    __stdcall AxmModuleWriteWord(long lBoardNo, long lModulePos, WORD wOffset, WORD wData);
DWORD    __stdcall AxmModuleReadWord(long lBoardNo, long lModulePos, WORD wOffset, WORD *wData);


// Setting up confirmes the register besides within the Module by DWord.
DWORD    __stdcall AxmModuleWriteDWord(long lBoardNo, long lModulePos, WORD wOffset, DWORD dwData);
DWORD    __stdcall AxmModuleReadDWord(long lBoardNo, long lModulePos, WORD wOffset, DWORD *dwData);


// Set EXCNT (Pos = Unit)
DWORD    __stdcall AxmStatusSetActComparatorPos(long lAxisNo, double dPos);
// Return EXCNT (Positon = Unit)
DWORD    __stdcall AxmStatusGetActComparatorPos(long lAxisNo, double *dpPos);


// Set INCNT (Pos = Unit)
DWORD    __stdcall AxmStatusSetCmdComparatorPos(long lAxisNo, double dPos);
// Return INCNT (Pos = Unit)
DWORD    __stdcall AxmStatusGetCmdComparatorPos(long lAxisNo, double *dpPos);


//=========== Append function. =========================================================================================================
// Increase a straight line interpolation at speed to the infinity.
// Must put the distance speed rate.
DWORD    __stdcall AxmLineMoveVel(long lCoord, double dVel, double dAccel, double dDecel);


//========= Sensor drive API( Read carefully: Available only PI , No function in QI) =========================================================================
// Set mark signal( used in sensor positioning drive)
DWORD    __stdcall AxmSensorSetSignal(long lAxisNo, DWORD uLevel);
// Verify mark signal( used in sensor positioning drive)
DWORD    __stdcall AxmSensorGetSignal(long lAxisNo, DWORD *upLevel);
// Verify mark signal( used in sensor positioning drive)state
DWORD    __stdcall AxmSensorReadSignal(long lAxisNo, DWORD *upStatus);


// Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop. Applied motion is started upon the start of API, and escapes from the API after the motion is completed.
DWORD    __stdcall AxmSensorMovePos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, long lMethod);


// Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop. Applied motion is started upon the start of API, then escapes from the API immediately without waiting until the motion is completed.
DWORD    __stdcall AxmSensorStartMovePos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, long lMethod);


// Return record of origin search progress step.
// *lpStepCount      : Number of step(Be recorded)
// *upMainStepNumber : Array point of 'MainStepNumber ' information(Be recorded)
// *upStepNumber     : Array point of 'StepNumber ' information(Be recorded)
// *upStepBranch     : Array point of branch information by step(Be recorded)
// ※ Caution : Number of array should be fixed 50.
DWORD    __stdcall AxmHomeGetStepTrace(long lAxisNo, long *lpStepCount, DWORD *upMainStepNumber, DWORD *upStepNumber, DWORD *upStepBranch);


//======= Additive home search (Applicable to PI-N804/404  only) =================================================================================

// Set home setting parameters of axis specified by user. (Use exclusive-use register for QI chip).
// uZphasCount : Z phase count after home completion. (0 - 15)
// lHomeMode   : Home setting mode( 0 - 12)
// lClearSet   : Select use of position clear and remaining pulse clear (0 - 3)
//               0: No use of position clear, no use of remaining pulse clear
//               1: use of position clear, no use of remaining pulse clear
//               2: No use of position clear, use of remaining pulse clear
//               3: use of position clear, use of remaining pulse clear
// dOrgVel : Set Org  Speed related home
// dLastVel: Set Last Speed related home
DWORD    __stdcall AxmHomeSetConfig(long lAxisNo, DWORD uZphasCount, long lHomeMode, long lClearSet, double dOrgVel, double dLastVel, double dLeavePos);
// Return home setting parameters of axis specified by user.
DWORD    __stdcall AxmHomeGetConfig(long lAxisNo, DWORD *upZphasCount, long *lpHomeMode, long *lpClearSet, double *dpOrgVel, double *dpLastVel, double *dpLeavePos); //KKJ(070215)


// Start home search of axis specified by user
// Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
// If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
// Move direction      : CW when Vel value is positive, CCW when negative.
DWORD    __stdcall AxmHomeSetMoveSearch(long lAxisNo, double dVel, double dAccel, double dDecel);


// Start home return of axis specified by user.
// Set when lHomeMode is used: set 0 - 12
// If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
// Move direction      : CW when Vel value is positive, CCW when negative.
DWORD    __stdcall AxmHomeSetMoveReturn(long lAxisNo, double dVel, double dAccel, double dDecel);


// Home separation of axis specified by user is started.
// Move direction      : CW when Vel value is positive, CCW when negative.
DWORD    __stdcall AxmHomeSetMoveLeave(long lAxisNo, double dVel, double dAccel, double dDecel);


// User start home search of multi-axis specified by user.
// Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
// If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
// Move direction      : CW when Vel value is positive, CCW when negative.
DWORD    __stdcall AxmHomeSetMultiMoveSearch(long lArraySize, long *lpAxesNo, double *dpVel, double *dpAccel, double *dpDecel);


//Set move velocity profile mode of specific coordinate system.
// (caution : Available to use only after axis mapping)
//ProfileMode : '0' - symmetry Trapezoid
//              '1' - asymmetric Trapezoid
//              '2' - symmetry Quasi-S Curve
//              '3' - symmetry S Curve
//              '4' - asymmetric S Curve
DWORD    __stdcall AxmContiSetProfileMode(long lCoord, DWORD uProfileMode);
// Return move velocity profile mode of specific coordinate system.
DWORD    __stdcall AxmContiGetProfileMode(long lCoord, DWORD *upProfileMode);


//========== Reading group for input interrupt occurrence flag
// Reading the interrupt occurrence state by bit unit in specified input contact module and Offset position of Interrupt Flag Register
DWORD    __stdcall AxdiInterruptFlagReadBit(long lModuleNo, long lOffset, DWORD *upValue);
// Reading the interrupt occurrence state by byte unit in specified input contact module and Offset position of Interrupt Flag Register
DWORD    __stdcall AxdiInterruptFlagReadByte(long lModuleNo, long lOffset, DWORD *upValue);
// Reading the interrupt occurrence state by word unit in specified input contact module and Offset position of Interrupt Flag Register
DWORD    __stdcall AxdiInterruptFlagReadWord(long lModuleNo, long lOffset, DWORD *upValue);
// Reading the interrupt occurrence state by double word unit in specified input contact module and Offset position of Interrupt Flag Register
DWORD    __stdcall AxdiInterruptFlagReadDword(long lModuleNo, long lOffset, DWORD *upValue);
// Reading the interrupt occurrence state by bit unit in entire input contact module and Offset position of Interrupt Flag Register
DWORD    __stdcall AxdiInterruptFlagRead(long lOffset, DWORD *upValue);


//========= API related log ==========================================================================================
// This API sets or resets in order to monitor the API execution result of set axis in EzSpy.
// uUse : use or not use => DISABLE(0), ENABLE(1)
DWORD    __stdcall AxmLogSetAxis(long lAxisNo, DWORD uUse);


// This API verifies if the API execution result of set axis is monitored in EzSpy.
DWORD    __stdcall AxmLogGetAxis(long lAxisNo, DWORD *upUse);


//==Log

// Set whether to log output to EzSpy of specified input channel
DWORD    __stdcall AxaiLogSetChannel(long lChannelNo, DWORD uUse);
// Verify whether to log output to EzSpy of specified input channel
DWORD    __stdcall AxaiLogGetChannel(long lChannelNo, DWORD *upUse);


// Set whether to log output in EzSpy of specified output channel
DWORD    __stdcall AxaoLogSetChannel(long lChannelNo, DWORD uUse);
// Verify whether log output is done in EzSpy of specified output channel.
DWORD    __stdcall AxaoLogGetChannel(long lChannelNo, DWORD *upUse);


// Set whether execute log output on EzSpy of specified module
DWORD    __stdcall AxdLogSetModule(long lModuleNo, DWORD uUse);
// Verify whether execute log output on EzSpy of specified module
DWORD    __stdcall AxdLogGetModule(long lModuleNo, DWORD *upUse);

// Verify whether to firmware version designated RTEX board.
//DWORD    __stdcall AxlGetFirmwareVersion(long lBoardNo, PTCHAR szVersion);
// Sent to firmware designated board.
DWORD    __stdcall AxlSetFirmwareCopy(long lBoardNo, WORD *wData, WORD *wCmdData);
// Execute Firmware update to designated board.
DWORD    __stdcall AxlSetFirmwareUpdate(long lBoardNo);
// Verify whether currently RTEX status Initialized.
DWORD    __stdcall AxlCheckStatus(long lBoardNo, DWORD* dwStatus);
// Execute universal command designated axis of board.
DWORD    __stdcall AxlRtexUniversalCmd(long lBoardNo, WORD wCmd, WORD wOffset, WORD *wData);
// Execute RTEX communication command designated axis.
DWORD    __stdcall AxmRtexSlaveCmd(long lAxisNo, DWORD dwCmdCode, DWORD dwTypeCode, DWORD dwIndexCode, DWORD dwCmdConfigure, DWORD dwValue);
// Verify whether Result of RTEX communication command designated axis.
DWORD    __stdcall AxmRtexGetSlaveCmdResult(long lAxisNo, DWORD* dwIndex, DWORD *dwValue);
// Check the result of the RTEX communication command executed on the specified axis. PCIE-Rxx04-RTEX only
DWORD    __stdcall AxmRtexGetSlaveCmdResultEx(long lAxisNo, DWORD* dwpCommand, DWORD* dwpType, DWORD* dwpIndex, DWORD *dwpValue);
// Verify whether RTEX status information designated axis.
DWORD    __stdcall AxmRtexGetAxisStatus(long lAxisNo, DWORD *dwStatus);
// Verify whether RTEX communication return information designated axis.(Actual position, Velocity, Torque)
DWORD    __stdcall AxmRtexGetAxisReturnData(long lAxisNo,  DWORD *dwReturn1, DWORD *dwReturn2, DWORD *dwReturn3);
// Verify whether currently status information of RTEX slave axis.(mechanical, Inposition and etc)
DWORD    __stdcall AxmRtexGetAxisSlaveStatus(long lAxisNo,  DWORD *dwStatus);


// Enter the universal network command of specified MLII slave axis.
DWORD    __stdcall AxmSetAxisCmd(long lAxisNo, DWORD* tagCommand);
// Verifying result of universal network command of specified MLII slave axis.
DWORD    __stdcall AxmGetAxisCmdResult(long lAxisNo, DWORD* tagCommand);


// The specified SID Write the result of the network command to the slave module and return it.
DWORD   __stdcall AxdSetAndGetSlaveCmdResult(long lModuleNo, DWORD* tagSetCommand, DWORD* tagGetCommand);
DWORD   __stdcall AxaSetAndGetSlaveCmdResult(long lModuleNo, DWORD* tagSetCommand, DWORD* tagGetCommand);
DWORD   __stdcall AxcSetAndGetSlaveCmdResult(long lModuleNo, DWORD* tagSetCommand, DWORD* tagGetCommand);

// Verify DPRAM data.
DWORD    __stdcall AxlGetDpRamData(long lBoardNo, WORD wAddress, DWORD* dwpRdData);
// Verify DPRAM data in Word unit.
DWORD    __stdcall AxlBoardReadDpramWord(long lBoardNo, WORD wOffset, DWORD* dwpRdData);
// Set DPRAM data in Word unit.
DWORD   __stdcall AxlBoardWriteDpramWord(long lBoardNo, WORD wOffset, DWORD dwWrData);


// Transmit instructions of each slave of each board.
DWORD   __stdcall AxlSetSendBoardEachCommand(long lBoardNo, DWORD dwCommand, DWORD* dwpSendData, DWORD dwLength);
// Transmit instructions to each board.
DWORD    __stdcall AxlSetSendBoardCommand(long lBoardNo, DWORD dwCommand, DWORD* dwpSendData, DWORD dwLength);
// Verify the response of each board.
DWORD    __stdcall AxlGetResponseBoardCommand(long lBoardNo, DWORD* dwpReadData);

// Reading firmware version function of slaves in network type master board.
// Declare with array of ucaFirmwareVersion unsigned char type(Size : 4 or more)
DWORD    __stdcall AxmInfoGetFirmwareVersion(long lAxisNo, unsigned char* ucaFirmwareVersion);
DWORD    __stdcall AxaInfoGetFirmwareVersion(long lModuleNo, unsigned char* ucaFirmwareVersion);
DWORD    __stdcall AxdInfoGetFirmwareVersion(long lModuleNo, unsigned char* ucaFirmwareVersion);
DWORD    __stdcall AxcInfoGetFirmwareVersion(long lModuleNo, unsigned char* ucaFirmwareVersion);


//======== Only for PCI-R1604-MLII ===========================================================================
// Set the value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
// Default value : Max
// Setting value Range : 0 ~ 4000H
// If it is set to 4000H or higher, the setting is set higher than that, but the operation is applied to the value of 4000H.
DWORD    __stdcall AxmSetTorqFeedForward(long lAxisNo, DWORD dwTorqFeedForward);

// It is API that read value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
// Default value : Max
DWORD    __stdcall AxmGetTorqFeedForward(long lAxisNo, DWORD* dwpTorqFeedForward);

// It is API that set the value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
// Default value : 0
// Setting value Range : 0 ~ FFFFH
DWORD    __stdcall AxmSetVelocityFeedForward(long lAxisNo, DWORD dwVelocityFeedForward);

// It is API that read value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
DWORD    __stdcall AxmGetVelocityFeedForward(long lAxisNo, DWORD* dwpVelocityFeedForward);


// Set Encoder type.
// Default value : 0(TYPE_INCREMENTAL)
// Setting range : 0 ~ 1
// dwEncoderType : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
DWORD   __stdcall AxmSignalSetEncoderType(long lAxisNo, DWORD dwEncoderType);


// Verify Encoder type.
DWORD   __stdcall AxmSignalGetEncoderType(long lAxisNo, DWORD* dwpEncoderType);



// For updating the slave firmware(only for RTEX-PM).
//DWORD   __stdcall AxmSetSendAxisCommand(long lAxisNo, WORD wCommand, WORD* wpSendData, WORD wLength);

//======== Only for PCI-R1604-RTEX, RTEX-PM==============================================================
// When Input Universal Input 2, 3, Set Jog move velocity
// Set only once execute after all drive setting (Ex, PulseOutMethod, MoveUnitPerPulse etc..)
DWORD    __stdcall AxmMotSetUserMotion(long lAxisNo, double dVelocity, double dAccel, double dDecel);


// When Input Universal Input 2, 3, Set Jog move usage
// Setting value :  0(DISABLE), 1(ENABLE)
DWORD    __stdcall AxmMotSetUserMotionUsage(long lAxisNo, DWORD dwUsage);


// Set Load/UnLoad Position to Automatically move use MPGP Input
DWORD    __stdcall  AxmMotSetUserPosMotion(long lAxisNo, double dVelocity, double dAccel, double dDecel, double dLoadPos, double dUnLoadPos, DWORD dwFilter, DWORD dwDelay);


// Set Usage Load/UnLoad Position to Automatically move use MPGP Input
// Setting value :  0(DISABLE), 1(Position function A), 2(Position function B)
DWORD    __stdcall  AxmMotSetUserPosMotionUsage(long lAxisNo, DWORD dwUsage);

//========================================================================================================

//======== SIO-CN2CH, Only for absolute position trigger module(B0) =======================================
// The API of writing memory data.
DWORD  __stdcall AxcKeWriteRamDataAddr(long lChannelNo, DWORD dwAddr, DWORD dwData);
// The API of reading memory data.
DWORD  __stdcall AxcKeReadRamDataAddr(long lChannelNo, DWORD dwAddr, DWORD* dwpData);
// Memory initialization API.
DWORD  __stdcall AxcKeResetRamDataAll(long lModuleNo, DWORD dwData);
// Trigger timeout setting API.
DWORD  __stdcall AxcTriggerSetTimeout(long lChannelNo, DWORD dwTimeout);
// Trigger timeout checking API.
DWORD  __stdcall AxcTriggerGetTimeout(long lChannelNo, DWORD* dwpTimeout);
// Trigger Waiting State checking API.
DWORD  __stdcall AxcStatusGetWaitState(long lChannelNo, DWORD* dwpState);
// Trigger Waiting State setting API.
DWORD  __stdcall AxcStatusSetWaitState(long lChannelNo, DWORD dwState);

// Write command to designated channel.
DWORD  __stdcall AxcKeSetCommandData32(long lChannelNo, DWORD dwCommand, DWORD dwData);
// Write command to designated channel.
DWORD  __stdcall AxcKeSetCommandData16(long lChannelNo, DWORD dwCommand, WORD wData);
// Verify register of specified channel.
DWORD  __stdcall AxcKeGetCommandData32(long lChannelNo, DWORD dwCommand, DWORD *dwpData);
// Verify register of specified channel.
DWORD  __stdcall AxcKeGetCommandData16(long lChannelNo, DWORD dwCommand, WORD *wpData);

//========================================================================================================

//======== Only for PCI-N804/N404, Sequence Motion ===========================================================
// Set Axis Information of sequence Motion (min 1axis)
// lSeqMapNo : Sequence Motion Index Point
// lSeqMapSize : Number of axis
// long* LSeqAxesNo : Number of arrary
DWORD   __stdcall AxmSeqSetAxisMap(long lSeqMapNo, long lSeqMapSize, long* lSeqAxesNo);
DWORD   __stdcall AxmSeqGetAxisMap(long lSeqMapNo, long* lSeqMapSize, long* lSeqAxesNo);


// Set Standard(Master)Axis of Sequence Motion.
// By all means Set in AxmSeqSetAxisMap setting axis.
DWORD   __stdcall AxmSeqSetMasterAxisNo(long lSeqMapNo, long lMasterAxisNo);


// Notifies the library node start loading of Sequence Motion.
DWORD   __stdcall AxmSeqBeginNode(long lSeqMapNo);


// Notifies the library node end loading of Sequence Motion.
DWORD   __stdcall AxmSeqEndNode(long lSeqMapNo);


// Start Sequence Motion Move.
DWORD   __stdcall AxmSeqStart(long lSeqMapNo, DWORD dwStartOption);


// Set each profile node Information of Sequence Motion in Library.
// if used 1axis Sequence Motion, Must be Set *dPosition one Array.
DWORD   __stdcall AxmSeqAddNode(long lSeqMapNo, double* dPosition, double dVelocity, double dAcceleration, double dDeceleration, double dNextVelocity);


// Return Node Index number of Sequence Motion.
DWORD   __stdcall AxmSeqGetNodeNum(long lSeqMapNo, long* lCurNodeNo);


// Return All node count of Sequence Motion.
DWORD   __stdcall AxmSeqGetTotalNodeNum(long lSeqMapNo, long* lTotalNodeCnt);


// Return Sequence Motion drive status  of specific SeqMap.
// dwInMotion : 0(Drive end), 1(In drive)
DWORD   __stdcall AxmSeqIsMotion(long lSeqMapNo, DWORD* dwInMotion);


// Clear Sequence Motion Memory.
DWORD   __stdcall AxmSeqWriteClear(long lSeqMapNo);


// Stop sequence motion
// dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
DWORD   __stdcall AxmSeqStop(long lSeqMapNo, DWORD dwStopMode);


//========================================================================================================


//======== Only for PCIe-Rxx04-SIIIH ==========================================================================
// (SIIIH, MR_J4_xxB, Para : 0 ~ 8) ==
//     [0] : Command Position
//     [1] : Actual Position
//     [2] : Actual Velocity
//     [3] : Mechanical Signal
//     [4] : Regeneration load factor(%)
//     [5] : Effective load factor(%)
//     [6] : Peak load factor(%)
//     [7] : Current Feedback
//     [8] : Command Velocity
DWORD   __stdcall AxmStatusSetMon(long lAxisNo, DWORD dwParaNo1, DWORD dwParaNo2, DWORD dwParaNo3, DWORD dwParaNo4, DWORD dwUse);
DWORD   __stdcall AxmStatusGetMon(long lAxisNo, DWORD *dwpParaNo1, DWORD *dwpParaNo2, DWORD *dwpParaNo3, DWORD *dwpParaNo4, DWORD *dwpUse);
DWORD   __stdcall AxmStatusReadMon(long lAxisNo, DWORD *dwpParaNo1, DWORD *dwpParaNo2, DWORD *dwpParaNo3, DWORD *dwpParaNo4, DWORD *dwDataVaild);
DWORD   __stdcall AxmStatusReadMonEx(long lAxisNo, long *lpDataCnt, DWORD *dwpReadData);

//=============================================================================================================

//======== Only for PCI-R32IOEV-RTEX ===========================================================================
// The API for read or write HPI register which allocated as I/O port.
// I/O Registers for HOST interface.
// I/O 00h Host status register (HSR)
// I/O 04h Host-to-DSP control register (HDCR)
// I/O 08h DSP page register (DSPP)
// I/O 0Ch Reserved
DWORD   __stdcall AxlSetIoPort(long lBoardNo, DWORD dwAddr, DWORD dwData);
DWORD   __stdcall AxlGetIoPort(long lBoardNo, DWORD dwAddr, DWORD* dwpData);


//======== Only for PCI-R3200-MLIII ===========================================================================
// Basic information setting API for firmware update of M-III Master board.
DWORD   __stdcall AxlM3SetFWUpdateInit(long lBoardNo, DWORD dwTotalPacketSize, DWORD dwProcTotalStepNo);
// Verify setting value of 'AxlM3SetFWUpdateInit'.
DWORD   __stdcall AxlM3GetFWUpdateInit(long lBoardNo, DWORD *dwTotalPacketSize, DWORD *dwProcTotalStepNo);


// M-III Master board firmware update data transfer API.
DWORD   __stdcall AxlM3SetFWUpdateCopy(long lBoardNo, DWORD *pdwPacketData, DWORD dwPacketSize);
// Verify setting value of 'AxlM3SetFWUpdateCopy'.
DWORD   __stdcall AxlM3GetFWUpdateCopy(long lBoardNo, DWORD *dwPacketSize);


// Execute firmware update of M-III Master Board.
DWORD   __stdcall AxlM3SetFWUpdate(long lBoardNo, DWORD dwFlashBurnStepNo);
// Verifying result of execute firmware update of M-III Master Board.
DWORD   __stdcall AxlM3GetFWUpdate(long lBoardNo, DWORD *dwFlashBurnStepNo, DWORD *dwIsFlashBurnDone);

// The API for setting EEPROM data of M-III Master board.
DWORD   __stdcall AxlM3SetCFGData(long lBoardNo, DWORD *pCmdData, DWORD CmdDataSize);
// The API for getting data from EEPROM of M-III Master board.
DWORD   __stdcall AxlM3GetCFGData(long lBoardNo, DWORD *pCmdData, DWORD CmdDataSize);

// The API for setting CONNECT PARAMETER information of M-III Master board.
DWORD   __stdcall AxlM3SetMCParaUpdateInit(long lBoardNo, WORD wCh0Slaves, WORD wCh1Slaves, DWORD dwCh0CycTime, DWORD dwCh1CycTime, DWORD dwChInfoMaxRetry);
// The API for verifying CONNECT PARAMETER information of M-III Master board.
DWORD   __stdcall AxlM3GetMCParaUpdateInit(long lBoardNo, WORD *wCh0Slaves, WORD *wCh1Slaves, DWORD *dwCh0CycTime, DWORD *dwCh1CycTime, DWORD *dwChInfoMaxRetry);
// The API for transmit CONNECT PARAMETER information of M-III Master board.
DWORD   __stdcall AxlM3SetMCParaUpdateCopy(long lBoardNo, WORD wIdx, WORD wChannel, WORD wSlaveAddr, DWORD dwProtoCalType, DWORD dwTransBytes, DWORD dwDeviceCode);
// The API for verifying transmit CONNECT PARAMETER information of M-III Master board.
DWORD   __stdcall AxlM3GetMCParaUpdateCopy(long lBoardNo, WORD wIdx, WORD *wChannel, WORD *wSlaveAddr, DWORD *dwProtoCalType, DWORD *dwTransBytes, DWORD *dwDeviceCode);

// The API for checking register as DWord unit within M-III Master board.
DWORD   __stdcall AxlBoardReadDWord(long lBoardNo, WORD wOffset, DWORD *dwData);
// The API for setting register as DWord unit within M-III Master board.
DWORD   __stdcall AxlBoardWriteDWord(long lBoardNo, WORD wOffset, DWORD dwData);

// Setting and verifying extension register as DWord unit within board.
DWORD    __stdcall AxlBoardReadDWordEx(long lBoardNo, DWORD dwOffset, DWORD *dwData);
DWORD    __stdcall AxlBoardWriteDWordEx(long lBoardNo, DWORD dwOffset, DWORD dwData);

// The API for setting servo to stop mode.
DWORD   __stdcall AxmM3ServoSetCtrlStopMode(long lAxisNo, BYTE bStopMode);
// The API for setting servo to Lt selection state.
DWORD   __stdcall AxmM3ServoSetCtrlLtSel(long lAxisNo, BYTE bLtSel1, BYTE bLtSel2);
// The API for verifying servo I/O input state.
DWORD   __stdcall AxmStatusReadServoCmdIOInput(long lAxisNo, DWORD *upStatus);
// Servo interpolation drive API.
DWORD   __stdcall AxmM3ServoExInterpolate(long lAxisNo, DWORD dwTPOS, DWORD dwVFF, DWORD dwTFF, DWORD dwTLIM, DWORD dwExSig1, DWORD dwExSig2);
// The API for setting bias of the servo actuator.
DWORD   __stdcall AxmM3ServoSetExpoAccBias(long lAxisNo, WORD wBias);
// The API for setting time of the servo actuator.
DWORD   __stdcall AxmM3ServoSetExpoAccTime(long lAxisNo, WORD wTime);
// The API for setting time of the servo move.
DWORD   __stdcall AxmM3ServoSetMoveAvrTime(long lAxisNo, WORD wTime);
// The API for setting acc filter of the servo.
DWORD   __stdcall AxmM3ServoSetAccFilter(long lAxisNo, BYTE bAccFil);
// The API for setting status monitor1 of the servo.
DWORD   __stdcall AxmM3ServoSetCprmMonitor1(long lAxisNo, BYTE bMonSel);
// The API for setting status monitor2 of the servo.
DWORD   __stdcall AxmM3ServoSetCprmMonitor2(long lAxisNo, BYTE bMonSel);
// The API for verifying status monitor1 of the servo.
DWORD   __stdcall AxmM3ServoStatusReadCprmMonitor1(long lAxisNo, DWORD *upStatus);
// The API for verifying status monitor2 of the servo.
DWORD   __stdcall AxmM3ServoStatusReadCprmMonitor2(long lAxisNo, DWORD *upStatus);
// The API for setting Dec of servo actuator.
DWORD   __stdcall AxmM3ServoSetAccDec(long lAxisNo, WORD wAcc1, WORD wAcc2, WORD wAccSW, WORD wDec1, WORD wDec2, WORD wDecSW);
// The API for servo stop.
DWORD   __stdcall AxmM3ServoSetStop(long lAxisNo, long lMaxDecel);

//========== Common commands of standard I/O dvices =========================================================================
// The API for return parameter setting value of each slave device.
DWORD   __stdcall AxlM3GetStationParameter(long lBoardNo, long lModuleNo, WORD wNo, BYTE bSize, BYTE bModuleType, BYTE *pbParam);
// The API for setting parameter value of each slave device.
DWORD   __stdcall AxlM3SetStationParameter(long lBoardNo, long lModuleNo, WORD wNo, BYTE bSize, BYTE bModuleType, BYTE *pbParam);
// The API for return ID value of each slave device.
DWORD   __stdcall AxlM3GetStationIdRd(long lBoardNo, long lModuleNo, BYTE bIdCode, BYTE bOffset, BYTE bSize, BYTE bModuleType, BYTE *pbParam);
// The API used as invalid command of each slave device.
DWORD   __stdcall AxlM3SetStationNop(long lBoardNo, long lModuleNo, BYTE bModuleType);
// The API for set up each slave device.
DWORD   __stdcall AxlM3SetStationConfig(long lBoardNo, long lModuleNo, BYTE bConfigMode, BYTE bModuleType);
// The API for return alarm and warning status value of each slave device.
DWORD   __stdcall AxlM3GetStationAlarm(long lBoardNo, long lModuleNo, WORD wAlarmRdMod, WORD wAlarmIndex, BYTE bModuleType, WORD *pwAlarmData);
// The API for clearing alarm and warning status value of each slave device.
DWORD   __stdcall AxlM3SetStationAlarmClear(long lBoardNo, long lModuleNo, WORD wAlarmClrMod, BYTE bModuleType);
// The API for setting establish synchronous communication with each slave device.
DWORD   __stdcall AxlM3SetStationSyncSet(long lBoardNo, long lModuleNo, BYTE bModuleType);
// The API for setting connection with each slave device.
DWORD   __stdcall AxlM3SetStationConnect(long lBoardNo, long lModuleNo, BYTE bVer, BYTE bComMode, BYTE bComTime, BYTE bProfileType, BYTE bModuleType);
// The API for setting disconnection with each slave device.
DWORD   __stdcall AxlM3SetStationDisConnect(long lBoardNo, long lModuleNo, BYTE bModuleType);
// The API for return of non-volatile parameter setting value.
DWORD   __stdcall AxlM3GetStationStoredParameter(long lBoardNo, long lModuleNo, WORD wNo, BYTE bSize, BYTE bModuleType, BYTE *pbParam);
// The API for setting non-volatile parameter value of each slave device.
DWORD   __stdcall AxlM3SetStationStoredParameter(long lBoardNo, long lModuleNo, WORD wNo, BYTE bSize, BYTE bModuleType, BYTE *pbParam);
// The API for return of memory setting value of each slave device.
DWORD   __stdcall AxlM3GetStationMemory(long lBoardNo, long lModuleNo, WORD wSize, DWORD dwAddress, BYTE bModuleType, BYTE bMode, BYTE bDataType, BYTE *pbData);
// The API for setting memory value of each slave device.
DWORD   __stdcall AxlM3SetStationMemory(long lBoardNo, long lModuleNo, WORD wSize, DWORD dwAddress, BYTE bModuleType, BYTE bMode, BYTE bDataType, BYTE *pbData);

//========== Connection commands of standard I/O dvices =========================================================================
// The API for setting value of automatic access mode of each re-ordered slave device.
DWORD   __stdcall AxlM3SetStationAccessMode(long lBoardNo, long lModuleNo, BYTE bModuleType, BYTE bRWSMode);
// The API for return of automatic access mode setting value of each re-ordered slave device.
DWORD   __stdcall AxlM3GetStationAccessMode(long lBoardNo, long lModuleNo, BYTE bModuleType, BYTE *bRWSMode);
// The API for set synchronous auto connect mode of each slave device.
DWORD   __stdcall AxlM3SetAutoSyncConnectMode(long lBoardNo, long lModuleNo, BYTE bModuleType, DWORD dwAutoSyncConnectMode);
// The API for return of synchronous auto connect mode setting value of each slave device.
DWORD   __stdcall AxlM3GetAutoSyncConnectMode(long lBoardNo, long lModuleNo, BYTE bModuleType, DWORD *dwpAutoSyncConnectMode);
// The API for establish a single synchronization connection to each slave device.
DWORD   __stdcall AxlM3SyncConnectSingle(long lBoardNo, long lModuleNo, BYTE bModuleType);
// The API for establish a single synchronization disconnection to each slave device.
DWORD   __stdcall AxlM3SyncDisconnectSingle(long lBoardNo, long lModuleNo, BYTE bModuleType);
// The API for verifying connection status with slave device.
DWORD   __stdcall AxlM3IsOnLine(long lBoardNo, long lModuleNo, DWORD *dwData);

//========== Profile commands of standard I/O =========================================================================
// The API for return of data setting value for each synchronous I/O slave device.
DWORD   __stdcall AxlM3GetStationRWS(long lBoardNo, long lModuleNo, BYTE bModuleType, DWORD *pdwParam, BYTE bSize);
// The API for setting data value for each synchronous I/O slave device.
DWORD   __stdcall AxlM3SetStationRWS(long lBoardNo, long lModuleNo, BYTE bModuleType, DWORD *pdwParam, BYTE bSize);
// The API for return of data setting value for each asynchronous I/O slave device.
DWORD   __stdcall AxlM3GetStationRWA(long lBoardNo, long lModuleNo, BYTE bModuleType, DWORD *pdwParam, BYTE bSize);
// The API for setting data value for each asynchronous I/O slave device.
DWORD   __stdcall AxlM3SetStationRWA(long lBoardNo, long lModuleNo, BYTE bModuleType, DWORD *pdwParam, BYTE bSize);

// Set the MLIII adjustment operation
// dwReqCode == 0x1005 : parameter initialization : 20sec
// dwReqCode == 0x1008 : absolute encoder reset   : 5sec
// dwReqCode == 0x100E : automatic offset adjustment of motor current detection signals  : 5sec
// dwReqCode == 0x1013 : Multiturn limit setting  : 5sec
DWORD   __stdcall AxmM3AdjustmentOperation(long lAxisNo, DWORD dwReqCode);

// API for diagnosing home search progress.(Only for M3)
DWORD    __stdcall AxmHomeGetM3FWRealRate(long lAxisNo, DWORD *upHomeMainStepNumber, DWORD *upHomeSubStepNumber, DWORD *upHomeLastMainStepNumber, DWORD *upHomeLastSubStepNumber);
// Return adjusted position value when escaping sensor zone from origin search.(Only for M3)
DWORD   __stdcall AxmHomeGetM3OffsetAvoideSenArea(long lAxisNo, double *dPos);
// The API for Setting adjusted position value when escaping sensor zone from origin search.(Only for M3)
// If dPos setting value is '0', adjusted position value will be set automatically when automatically escaping.
// 'dPos' should be a positive number.
DWORD   __stdcall AxmHomeSetM3OffsetAvoideSenArea(long lAxisNo, double dPos);


// Setting usage criterion of absolute encoder. Set whether to CMD/ACT POS initialize after origin search.(Only for M3)
// dwSel: 0, CMD/ACTPOS will be set '0' after origin search.(Default)
// dwSel: 1, CMD/ACTPOS will be not set after origin search.
DWORD   __stdcall AxmM3SetAbsEncOrgResetDisable(long lAxisNo, DWORD dwSel);

// Get 'AxmM3SetAbsEncOrgResetDisable' setting value.(Only for M3)
// upSel: 0, CMD / ACTPOS set to 0 after home search. (Default)
// upSel: 1, CMD / ACTPOS value is not set after home search.
DWORD   __stdcall AxmM3GetAbsEncOrgResetDisable(long lAxisNo, DWORD *upSel);


// Setting whether using alarm maintenance function when switch to slave offline mode.(Only for M3)
// dwSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
// dwSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
DWORD   __stdcall AxmM3SetOfflineAlarmEnable(long lAxisNo, DWORD dwSel);

// Get 'AxmM3SetOfflineAlarmEnable' setting value.(Only for M3)
// upSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
// upSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
DWORD   __stdcall AxmM3GetOfflineAlarmEnable(long lAxisNo, DWORD *upSel);

// Read value of slave online or offline status. (Only for M3)
// upSel: 0, ONLINE->OFFLINE Not converted
// upSel: 1, ONLINE->OFFLINE converted
DWORD   __stdcall AxmM3ReadOnlineToOfflineStatus(long lAxisNo, DWORD *upStatus);

DWORD   __stdcall AxlSetLockMode(long lBoardNo, WORD wLockMode);
DWORD   __stdcall AxlSetLockData(long lBoardNo, DWORD dwTotalNodeNum, DWORD *dwpNodeNo, DWORD *dwpNodeID, DWORD *dwpLockData);
DWORD   __stdcall AxmMoveStartPosWithAVC(long lAxisNo, double dPosition, double dMaxVelocity, double dMaxAccel, double dMinJerk, double *dpMoveVelocity, double *dpMoveAccel, double *dpMoveJerk);
//======== API for EtherCAT only =============================================================================
// The API for read VendorID, ProductCode and RevisionNo of EtherCat slave product by using StationAddress.
DWORD  __stdcall AxlECatGetProductInfo(DWORD dwStationAddress, DWORD* pdwVendorID, DWORD* pdwProductCode, DWORD* pdwRevisionNo);
DWORD  __stdcall AxlECatGetProductInfoEx(long lBoardNo, DWORD dwStationAddress, DWORD* pdwVendorID, DWORD* pdwProductCode, DWORD* pdwRevisionNo);

// The API for verifying network status of EtherCAT slave product by using StationAddress.
DWORD  __stdcall AxlECatGetModuleStatus(DWORD dwStationAddress);

// Read input PDO(Process Data Objects)
// dwBitOffset     : ProcessImage inputs bit offset value.
// dwDataBitLength : bit size of input pdo data.
// pbyData         : The Buffer for inserting read data.
DWORD  __stdcall AxlECatReadPdoInput(DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);
DWORD  __stdcall AxlECatReadPdoInputEx(long lBoardNo, DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);

// Read output PDO(Process Data Objects)
// dwBitOffset     : ProcessImage outputs bit offset value.
// dwDataBitLength : bit size of input pdo data.(for read)
// pbyData         : The Buffer for inserting read data.
DWORD  __stdcall AxlECatReadPdoOutput(DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);
DWORD  __stdcall AxlECatReadPdoOutputEx(long lBoardNo, DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);

// Write value to output process data.
// dwBitOffset     : ProcessImage outputs bit offset value.
// dwDataBitLength : bit size of output pdo data.(for write)
// pbyData         : The Buffer for inserting write data.
DWORD  __stdcall AxlECatWritePdoOutput(DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);

// Read SDO(Service Data Objects) by using COE.
DWORD  __stdcall AxlECatReadSdo(DWORD dwStationAddress, WORD wObjectIndex, BYTE byObjectSubIndex, BYTE* pbyData, DWORD dwDataLength, DWORD *pdwReadDataLength);
DWORD  __stdcall AxlECatReadSdoEx(long lBoardNo, DWORD dwStationAddress, WORD wObjectIndex, BYTE byObjectSubIndex, BYTE* pbyData, DWORD dwDataLength, DWORD *pdwReadDataLength);

// Store values in SDO by using COE.
DWORD  __stdcall AxlECatWriteSdo(DWORD dwStationAddress, WORD wObjectIndex, BYTE byObjectSubIndex, BYTE* pbyData, DWORD dwDataLength);
DWORD  __stdcall AxlECatWriteSdoEx(long lBoardNo, DWORD dwStationAddress, WORD wObjectIndex, BYTE byObjectSubIndex, BYTE* pbyData, DWORD dwDataLength);

DWORD  __stdcall AxlECatReadSdoFromAxisDouble(long  lAxisNo, WORD wObjectIndex, BYTE byObjectSubIndex, double* pdData);

DWORD  __stdcall AxlECatWriteSdoFromAxisDouble(long  lAxisNo, WORD wObjectIndex, BYTE byObjectSubIndex, double* pdData);
// Read SDO(DWORD type) through the axis number.
DWORD  __stdcall AxlECatReadSdoFromAxisDword(long  lAxisNo, WORD wObjectIndex, BYTE byObjectSubIndex, DWORD* pdwData);

// Store values in SDO(DWORD type) through the axis number.
DWORD  __stdcall AxlECatWriteSdoFromAxisDword(long  lAxisNo, WORD wObjectIndex, BYTE byObjectSubIndex, DWORD* pdwData);

// Read SDO(WORD type) through the axis number.
DWORD  __stdcall AxlECatReadSdoFromAxisWord(long  lAxisNo, WORD wObjectIndex, BYTE byObjectSubIndex, WORD* pwData);

// Store values in SDO(WORD type) through the axis number.
DWORD  __stdcall AxlECatWriteSdoFromAxisWord(long  lAxisNo, WORD wObjectIndex, BYTE byObjectSubIndex, WORD* pwData);

// Read SDO(BYTE type) through the axis number.
DWORD  __stdcall AxlECatReadSdoFromAxisByte(long  lAxisNo, WORD wObjectIndex, BYTE byObjectSubIndex, BYTE* pbyData);

// Store values in SDO(BYTE type) through the axis number.
DWORD  __stdcall AxlECatWriteSdoFromAxisByte(long  lAxisNo, WORD wObjectIndex, BYTE byObjectSubIndex, BYTE* pbyData);

// Read value of EEPROM.
DWORD  __stdcall AxlECatReadEEPRom(DWORD dwStationAddress, WORD wEEPRomStartOffset, WORD* pwData, DWORD dwDataLength);

// Write value to EEPROM.
DWORD  __stdcall AxlECatWriteEEPRom(DWORD dwStationAddress, WORD wEEPRomStartOffset, WORD* pwData, DWORD dwDataLength);
DWORD  __stdcall AxlECatReadEEPRomEx(long lBoardNo, DWORD dwStationAddress, WORD wEEPRomStartOffset, WORD* pwData, DWORD dwDataLength);

DWORD  __stdcall AxlECatWriteEEPRomEx(long lBoardNo, DWORD dwStationAddress, WORD wEEPRomStartOffset, WORD* pwData, DWORD dwDataLength);

// Read value of a register.
//DWORD  __stdcall AxlECatReadRegister(DWORD dwStationAddress, WORD wRegisterOffset, VOID *pvData, WORD wLen);

// Write value of a register.
//DWORD  __stdcall AxlECatWriteRegister(DWORD dwStationAddress, WORD wRegisterOffset, VOID *pvData, WORD wLen);

// Save BackupData as a file from among the object dictionary of EtherCat slave.
DWORD  __stdcall AxlECatSaveHotSwapData(DWORD dwStationAddress);

// Load BackupData which saved as a file from corresponding EtherCat salve.
DWORD  __stdcall AxlECatLoadHotSwapData(DWORD dwStationAddress);


// When using the HotSwapStart API(Function to advance HotSwap only for registered StationAddresses),
//       it stores the StationAddress in HotSwapConfig, confirms existence and deletes it.
DWORD  __stdcall AxlECatSetHotSwap(DWORD dwStationAddress);
DWORD  __stdcall AxlECatIsSetHotSwap(DWORD dwStationAddress);
DWORD  __stdcall AxlECatReSetHotSwap(DWORD dwStationAddress);

// Set EtherCat master mode (configure = 0, RumMode = 1)
DWORD  __stdcall AxlECatSetMasterMode(DWORD dwMasterMode);

// Get mode status of EtherCat master.
DWORD  __stdcall AxlECatGetMasterMode(DWORD* pdwMasterMode);

// Set MasterOperationMode of EtherCat master.
DWORD  __stdcall AxlECatSetMasterOperationMode(DWORD dwOperationMode);

// Get MasterOperationMode of EtherCat master.
DWORD  __stdcall AxlECatGetMasterOperationMode(DWORD* pdwOperationMode);

// Requesting scan command to EtherCat master, and then command to save scaned data to SHM.
DWORD  __stdcall AxlECatRequestScanData();


// Get total number of scanned slaves.
DWORD  __stdcall AxlECatGetScanSlaveCount(DWORD* pdwSlaveCount);

// Get current status information of EtherCat master.
DWORD  __stdcall AxlECatGetStatus(int* pnECMasterStatus, int* pnECSlaveStatus, int* pnECConnectedSlave, int* pnECConfiguredSlave, int* pnJobTaskCycleCnt, DWORD* pdwECMasterNotification);

// Reconnecting failed network.
DWORD  __stdcall AxlEcatReConnect();

// Get address information of slave which be set.
DWORD  __stdcall AxmECatReadAddress(long lAxisNo, DWORD* dwpStationAddress, long* lpAutoIncAddress, DWORD* dwpAliasAddress);
DWORD  __stdcall AxdECatReadAddress(long lModuleNo, DWORD* dwpStationAddress, long* lpAutoIncAddress, DWORD* dwpAliasAddress);
DWORD  __stdcall AxaECatReadAddress(long lModuleNo, DWORD* dwpStationAddress, long* lpAutoIncAddress, DWORD* dwpAliasAddress);
DWORD  __stdcall AxsECatReadAddress(long lPortNo, DWORD* dwpStationAddress, long* lpAutoIncAddress, DWORD* dwpAliasAddress);


// Monitor
// Add an item to proceed with data collection.
DWORD  __stdcall AxlMonitorSetItem(long lItemIndex, DWORD dwSignalType, long lSignalNo, long lSubSignalNo);

// Get information about items to be collected.
DWORD  __stdcall AxlMonitorGetIndexInfo(long* lpItemSize, long* lpItemIndex);

// Get detailed settings of each items for data collection progress.
DWORD  __stdcall AxlMonitorGetItemInfo(long lItemIndex, DWORD* dwpSignalType, long* lpSignalNo, long* lpSubSignalNo);

// Reset settings of all data collection items.
DWORD  __stdcall AxlMonitorResetAllItem();

// Reset settings of selected data collection items.
DWORD  __stdcall AxlMonitorResetItem(long lItemIndex);

// Set the trigger condition of data collection.
DWORD  __stdcall AxlMonitorSetTriggerOption(DWORD dwSignalType, long lSignalNo, long lSubSignalNo, DWORD dwOperatorType, double dValue1, double dValue2);


// Get the trigger condition of data collection.
//DWORD  __stdcall AxlMonitorGetTriggerOption(DWORD* dwpSignalType, long* lpSignalNo, long* lpSubSignalNo, DWORD* dwpOperatorType, double* dpValue1, double* dpValue2);
// Reset trigger condition of data collection.
DWORD  __stdcall AxlMonitorResetTriggerOption();

// Start collecting data.
DWORD  __stdcall AxlMonitorStart(DWORD dwStartOption, DWORD dwOverflowOption);

// Stop collecting data.
DWORD  __stdcall AxlMonitorStop();

// Read collected data.
DWORD  __stdcall AxlMonitorReadData(long* lpItemSize, long* lpDataCount, double* dpReadData);

// Read period of data collection.
DWORD  __stdcall AxlMonitorReadPeriod(DWORD* dwpPeriod);



//////////////////////////////////////////////////////////////////////////
// MonitorEx
// Add an item to proceed with data collection.
DWORD  __stdcall AxlMonitorExSetItem(long lItemIndex, DWORD dwSignalType, long lSignalNo, long lSubSignalNo);


// Gets information about the items to be collected.
DWORD  __stdcall AxlMonitorExGetIndexInfo(long* lpItemSize, long* lpItemIndex);


// Gets the detailed settings for each item to proceed with data collection.
DWORD  __stdcall AxlMonitorExGetItemInfo(long lItemIndex, DWORD* dwpSignalType, long* lpSignalNo, long* lpSubSignalNo);


// Reset the settings for all data collection items.
DWORD  __stdcall AxlMonitorExResetAllItem();


// Reset the settings of the selected data collection item.
DWORD  __stdcall AxlMonitorExResetItem(long lItemIndex);


// Sets the trigger condition for data collection.
DWORD  __stdcall AxlMonitorExSetTriggerOption(DWORD dwSignalType, long lSignalNo, long lSubSignalNo, DWORD dwOperatorType, double dValue1, double dValue2);



// Gets the trigger condition for data collection.
//DWORD  __stdcall AxlMonitorExGetTriggerOption(DWORD* dwpSignalType, long* lpSignalNo, long* lpSubSignalNo, DWORD* dwpOperatorType, double* dpValue1, double* dpValue2);

// Reset trigger conditions for data collection.
DWORD  __stdcall AxlMonitorExResetTriggerOption();


// Start collecting data.
DWORD  __stdcall AxlMonitorExStart(DWORD dwStartOption, DWORD dwOverflowOption);


// Stop collecting data.
DWORD  __stdcall AxlMonitorExStop();


// Gets collected data.
DWORD  __stdcall AxlMonitorExReadData(long* lpItemSize, long* lpDataCount, double* dpReadData);


// Gets the period of data collection.
DWORD  __stdcall AxlMonitorExReadPeriod(DWORD* dwpPeriod);


//////////////////////////////////////////////////////////////////////////

// Linear interpolation about 2 axis including information of offset position for X2, Y2 axis.
DWORD  __stdcall AxmLineMoveDual01(long lCoordNo, double* dpEndPosition, double dVelocity, double dAccel, double dDecel, double dOffsetLength, double dTotalLength, double* dpStartOffsetPosition, double* dpEndOffsetPosition);
// Arc interpolation about 2 axis including information of offset position for X2, Y2 axis.
DWORD  __stdcall AxmCircleCenterMoveDual01(long lCoordNo, long* lpAxes, double* dpCenterPosition, double* dpEndPosition, double dVelocity, double dAccel, double dDecel, DWORD dwCWDir, double dOffsetLength, double dTotalLength, double* dpStartOffsetPosition, double* dpEndOffsetPosition);

// About ECAT Foe
DWORD __stdcall AxdSetFirmwareUpdateInfo(long lModuleNo, DWORD dwTotalDataSize, DWORD dwTotalPacketSize);
DWORD __stdcall AxdSetFirmwareDataTrans(long lModuleNo, DWORD dwPacketIndex, DWORD* dwaPacketData);
DWORD __stdcall AxdSetFirmwareUpdate(long lModuleNo, char* szFileName, DWORD dwFileNameLen, DWORD dwPassWord);


DWORD __stdcall AxaSetFirmwareUpdateInfo(long lModuleNo, DWORD dwTotalDataSize, DWORD dwTotalPacketSize);
DWORD __stdcall AxaSetFirmwareDataTrans(long lModuleNo, DWORD dwPacketIndex, DWORD* dwaPacketData);
DWORD __stdcall AxaSetFirmwareUpdate(long lModuleNo, char* szFileName, DWORD dwFileNameLen, DWORD dwPassWord);


DWORD __stdcall AxmSetFirmwareUpdateInfo(long lAxisNo, DWORD dwTotalDataSize, DWORD dwTotalPacketSize);
DWORD __stdcall AxmSetFirmwareDataTrans(long lAxisNo, DWORD dwPacketIndex, DWORD* dwaPacketData);
DWORD __stdcall AxmSetFirmwareUpdate(long lAxisNo, char* szFileName, DWORD dwFileNameLen, DWORD dwPassWord);
DWORD __stdcall AxmSetFoeUploadInfo(long lAxisNo, DWORD dwTotalDataSize, DWORD dwTotalPacketSize);
DWORD __stdcall AxmGetFoeUploadData(long lAxisNo, DWORD dwPacketIndex, DWORD* dwaPacketData);
DWORD __stdcall AxmSetFoeUpload(long lAxisNo, char* szFileName, DWORD dwFileNameLen, DWORD dwPassWord);


//ProfilePosition Mode          = 1,
//Velocity Mode                 = 2,
//ProfileVelocity Mode          = 3,
//ProfileTorque Mode            = 4,
//Homing Mode                   = 6,
//InterpolatedPosition Mode     = 7,
//CyclicSyncPosition Mode       = 8,
//CyclicSyncVelocity Mode       = 9,
//CyclicSyncTorque Mode         = 10,
DWORD __stdcall AxmMotSetOperationMode(long lAxisNo, DWORD dwOperationMode);
DWORD __stdcall AxmMotGetOperationMode(long lAxisNo, DWORD* pdwOperationMode);



// lChannelNo : [0,1] = 0, [2,3] = 2
// nDataCnt :
//  nDataCnt > 0 : Add Data, nDataCnt <= 0 : Initialize Data
// dwOption : Reserved.
// dpPatternData : (X1, Y1)
DWORD  __stdcall AxcTriggerSetPatternData(long lChannelNo, long nDataCnt,  DWORD dwOption, double* dpPatternData);
DWORD  __stdcall AxcTriggerGetPatternData(long lChannelNo, long* npDataCnt,  DWORD* dwpOption, double* dpPatternData);

DWORD __stdcall AxmSpiralMoveEx(long lCoordNo, double dSpiralPitch, double dTurningCount, double dAngleOfPose, DWORD dwIsInnerDirection, double dVelocity, double dAcceleration, double dDeceleration);
DWORD    __stdcall AxmFilletMove(long lCoordinate, double* dPosition, double* dFirstVector, double* dSecondVector, double dMaxVelocity, double dMaxAccel, double dMaxDecel, double dRadius);

DWORD  __stdcall AxmSignalIsServoOnSingleAxis(long lAxisNo, DWORD *upOnOff);

DWORD  __stdcall AxmMotSetTorqueConnection(long lAxisNo, long lSourceAxisNo, DWORD dwEnable);
DWORD  __stdcall AxmMotGetTorqueConnection(long lAxisNo, long* plSourceAxisNo, DWORD* pdwEnable);


#ifdef __cplusplus
}
#endif    //__cplusplus

#endif    //__AXT_AXDEV_H__
