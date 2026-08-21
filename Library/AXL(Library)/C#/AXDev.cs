
using System;
using System.Runtime.InteropServices;

public class CAXDev
{

// Use Board Number and find Board Address
[DllImport("AXL.dll")] public static extern uint AxlGetBoardAddress(int nBoardNo, ref uint upBoardAddress);
// Use Board Number and find Board ID
[DllImport("AXL.dll")] public static extern uint AxlGetBoardID(int nBoardNo, ref uint upBoardID);
// Use Board Number and find Board Version
[DllImport("AXL.dll")] public static extern uint AxlGetBoardVersion(int nBoardNo, ref uint upBoardVersion);
// Use Board Number/Module Position and find Module ID
[DllImport("AXL.dll")] public static extern uint AxlGetModuleID(int nBoardNo, int nModulePos, ref uint upModuleID);
// Use Board Number/Module Position and find Module Version
[DllImport("AXL.dll")] public static extern uint AxlGetModuleVersion(int nBoardNo, int nModulePos, ref uint upModuleVersion);

[DllImport("AXL.dll")] public static extern uint AxlGetModuleNodeInfo(int nBoardNo, int nModulePos, ref uint upNetNo, ref uint upNodeAddr);


// Only for PCI-R1604[RTEX]
// Writing user data to embedded flash memory
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
// Note) Delay time is required for completing writing operation to Flash(Max. 17mSec)
[DllImport("AXL.dll")] public static extern uint AxlSetDataFlash(int nBoardNo, int nPageAddr, int nBytesNum, ref byte upSetData);


// ML3 Only, Use Board and Set the EStopInterLock Parameter
// dwInterLock    : (0) Not use(Default value)
//                  (1) Using function. When E-STOP signal is externally applied after setting function, E-STOP drive command is executed to the motion control node connected to the board.
// dwDigFilterVal : Setting range of input filter constant (1~40). Unit communication Cyclic time
// Set EstopInterLock function by using dwInterLock and dwDigFilterVal on Board
[DllImport("AXL.dll")] public static extern uint AxlSetEStopInterLock(int nBoardNo, uint dwInterLock, uint dwDigFilterVal);
// ML3 Only, Use Board and Get the EStopInterLock Parameter
[DllImport("AXL.dll")] public static extern uint AxlGetEStopInterLock(int nBoardNo, ref uint dwInterLock, ref uint dwDigFilterVal);
// ML3 Only, Read the External ESTOP Signal status
[DllImport("AXL.dll")] public static extern uint AxlReadEStopInterLock(int nBoardNo, ref uint dwInterLock);


// Reading datas from embedded flash memory(PCI-R1604[RTEX master board] only)
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
[DllImport("AXL.dll")] public static extern uint AxlGetDataFlash(int nBoardNo, int nPageAddr, int nBytesNum, ref uint upGetData);


// Use Board Number/Module Position and find AIO Module Number
[DllImport("AXL.dll")] public static extern uint AxaInfoGetModuleNo(int nBoardNo, int nModulePos, ref int npModuleNo);
// Use Board Number/Module Position and find DIO Module Number
[DllImport("AXL.dll")] public static extern uint AxdInfoGetModuleNo(int nBoardNo, int nModulePos, ref int npModuleNo);


// IPCOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommand(int nAxisNo, byte sCommand);
// 8bit IPCOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommandData08(int nAxisNo, byte sCommand, uint uData);
// Get 8bit IPCOMMAND at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmGetCommandData08(int nAxisNo, byte sCommand, ref uint upData);
// 16bit IPCOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommandData16(int nAxisNo, byte sCommand, uint uData);
// Get 16bit IPCOMMAND at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmGetCommandData16(int nAxisNo, byte sCommand, ref uint upData);
// 24bit IPCOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommandData24(int nAxisNo, byte sCommand, uint uData);
// Get 24bit IPCOMMAND at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmGetCommandData24(int nAxisNo, byte sCommand, ref uint upData);
// 32bit IPCOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommandData32(int nAxisNo, byte sCommand, uint uData);
// Get 32bit IPCOMMAND at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmGetCommandData32(int nAxisNo, byte sCommand, ref uint upData);


// QICOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommandQi(int nAxisNo, byte sCommand);
// 8bit QICOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommandData08Qi(int nAxisNo, byte sCommand, uint uData);
// Get 8bit QICOMMAND at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmGetCommandData08Qi(int nAxisNo, byte sCommand, ref uint upData);
// 16bit QICOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommandData16Qi(int nAxisNo, byte sCommand, uint uData);
// Get 16bit QICOMMAND at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmGetCommandData16Qi(int nAxisNo, byte sCommand, ref uint upData);
// 24bit QICOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommandData24Qi(int nAxisNo, byte sCommand, uint uData);
// Get 24bit QICOMMAND at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmGetCommandData24Qi(int nAxisNo, byte sCommand, ref uint upData);
// 32bit QICOMMAND Setting at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmSetCommandData32Qi(int nAxisNo, byte sCommand, uint uData);
// Get 32bit QICOMMAND at an appoint axis
[DllImport("AXL.dll")] public static extern uint AxmGetCommandData32Qi(int nAxisNo, byte sCommand, ref uint upData);


// Get Port Data at an appoint axis - IP
[DllImport("AXL.dll")] public static extern uint AxmGetPortData(int nAxisNo,  uint wOffset, ref uint upData);
// Port Data Setting at an appoint axis - IP
[DllImport("AXL.dll")] public static extern uint AxmSetPortData(int nAxisNo, uint wOffset, uint dwData);
// Get Port Data at an appoint axis - QI
[DllImport("AXL.dll")] public static extern uint AxmGetPortDataQi(int nAxisNo, uint byOffset, ref uint wData);
// Port Data Setting at an appoint axis - QI
[DllImport("AXL.dll")] public static extern uint AxmSetPortDataQi(int nAxisNo, uint byOffset, uint wData);


// Set the script at an appoint axis.  - IP
// sc    : Script number (1 - 4)
// event : Define an event SCRCON to happen.
//         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
// cmd   : Define a selection SCRCMD however we change any content
// data  : Selection to change any Data.
[DllImport("AXL.dll")] public static extern uint AxmSetScriptCaptionIp(int nAxisNo, int sc, uint uEvent, uint data);
// Return the script at an appoint axis.  - IP
[DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionIp(int nAxisNo, int sc, ref uint uEvent, ref uint data);


// Set the script at an appoint axis.  - QI
// sc    : Script number (1 - 4)
// event : Define an event SCRCON to happen.
//         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
// cmd   : Define a selection SCRCMD however we change any content
// data  : Selection to change any Data.
[DllImport("AXL.dll")] public static extern uint AxmSetScriptCaptionQi(int nAxisNo, int sc, uint uEvent, uint cmd, uint data);
// Return the script at an appoint axis. - QI
[DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionQi(int nAxisNo, int sc, ref uint uEvent, ref uint cmd, ref uint data);


// Clear orders a script inside Queue Index at an appoint axis
// uSelect IP.
// uSelect(0): Script Queue Index Clear.
//        (1): Caption Queue Index Clear.
// uSelect QI.
// uSelect(0): Script Queue 1 Index Clear.
//        (1): Script Queue 2 Index Clear.
[DllImport("AXL.dll")] public static extern uint AxmSetScriptCaptionQueueClear(int nAxisNo, uint uSelect);


// Return Index of a script inside Queue at an appoint axis.
// uSelect IP
// uSelect(0): Read Script Queue Index
//        (1): Read Caption Queue Index
// uSelect QI.
// uSelect(0): Read Script Queue 1 Index
//        (1): Read Script Queue 2 Index
[DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionQueueCount(int nAxisNo, ref uint updata, uint uSelect);


// Return Data number of a script inside Queue at an appoint axis.
// uSelect IP
// uSelect(0): Read Script Queue Data
//        (1): Read Caption Queue Data
// uSelect QI.
// uSelect(0): Read Script Queue 1 Data
//        (1): Read Script Queue 2 Data
[DllImport("AXL.dll")] public static extern uint AxmGetScriptCaptionQueueDataCount(int nAxisNo, ref uint updata, uint uSelect);


// Read an inside data.
[DllImport("AXL.dll")] public static extern uint AxmGetOptimizeDriveData(int nAxisNo, double dMinVel, double dVel, double dAccel, double  dDecel,



// Setting up confirmes the register besides within the board by Byte.
[DllImport("AXL.dll")] public static extern uint AxmBoardWriteByte(int nBoardNo, uint wOffset, byte byData);
[DllImport("AXL.dll")] public static extern uint AxmBoardReadByte(int nBoardNo, uint wOffset, ref byte byData);


// Setting up confirmes the register besides within the board by Word.
[DllImport("AXL.dll")] public static extern uint AxmBoardWriteWord(int nBoardNo, uint wOffset, uint wData);
[DllImport("AXL.dll")] public static extern uint AxmBoardReadWord(int nBoardNo, uint wOffset, ref ushort wData);


// Setting up confirmes the register besides within the board by DWord.
[DllImport("AXL.dll")] public static extern uint AxmBoardWriteDWord(int nBoardNo, uint wOffset, uint dwData);
[DllImport("AXL.dll")] public static extern uint AxmBoardReadDWord(int nBoardNo, uint wOffset, ref uint dwData);


// Setting up confirmes the register besides within the Module by Byte.
[DllImport("AXL.dll")] public static extern uint AxmModuleWriteByte(int nBoardNo, int nModulePos, uint wOffset, byte byData);
[DllImport("AXL.dll")] public static extern uint AxmModuleReadByte(int nBoardNo, int nModulePos, uint wOffset, ref byte byData);


// Setting up confirmes the register besides within the Module by Word.
[DllImport("AXL.dll")] public static extern uint AxmModuleWriteWord(int nBoardNo, int nModulePos, uint wOffset, uint wData);
[DllImport("AXL.dll")] public static extern uint AxmModuleReadWord(int nBoardNo, int nModulePos, uint wOffset, ref ushort wData);


// Setting up confirmes the register besides within the Module by DWord.
[DllImport("AXL.dll")] public static extern uint AxmModuleWriteDWord(int nBoardNo, int nModulePos, uint wOffset, uint dwData);
[DllImport("AXL.dll")] public static extern uint AxmModuleReadDWord(int nBoardNo, int nModulePos, uint wOffset, ref uint dwData);


// Set EXCNT (Pos = Unit)
[DllImport("AXL.dll")] public static extern uint AxmStatusSetActComparatorPos(int nAxisNo, double dPos);
// Return EXCNT (Positon = Unit)
[DllImport("AXL.dll")] public static extern uint AxmStatusGetActComparatorPos(int nAxisNo, ref double dpPos);


// Set INCNT (Pos = Unit)
[DllImport("AXL.dll")] public static extern uint AxmStatusSetCmdComparatorPos(int nAxisNo, double dPos);
// Return INCNT (Pos = Unit)
[DllImport("AXL.dll")] public static extern uint AxmStatusGetCmdComparatorPos(int nAxisNo, ref double dpPos);


//=========== Append function. =========================================================================================================
// Increase a straight line interpolation at speed to the infinity.
// Must put the distance speed rate.
[DllImport("AXL.dll")] public static extern uint AxmLineMoveVel(int nCoord, double dVel, double dAccel, double dDecel);


//========= Sensor drive API( Read carefully: Available only PI , No function in QI) =========================================================================
// Set mark signal( used in sensor positioning drive)
[DllImport("AXL.dll")] public static extern uint AxmSensorSetSignal(int nAxisNo, uint uLevel);
// Verify mark signal( used in sensor positioning drive)
[DllImport("AXL.dll")] public static extern uint AxmSensorGetSignal(int nAxisNo, ref uint upLevel);
// Verify mark signal( used in sensor positioning drive)state
[DllImport("AXL.dll")] public static extern uint AxmSensorReadSignal(int nAxisNo, ref uint upStatus);


// Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop. Applied motion is started upon the start of API, and escapes from the API after the motion is completed.
[DllImport("AXL.dll")] public static extern uint AxmSensorMovePos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nMethod);


// Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop. Applied motion is started upon the start of API, then escapes from the API immediately without waiting until the motion is completed.
[DllImport("AXL.dll")] public static extern uint AxmSensorStartMovePos(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nMethod);


// Return record of origin search progress step.
// *lpStepCount      : Number of step(Be recorded)
// *upMainStepNumber : Array point of 'MainStepNumber ' information(Be recorded)
// *upStepNumber     : Array point of 'StepNumber ' information(Be recorded)
// *upStepBranch     : Array point of branch information by step(Be recorded)
//  Caution : Number of array should be fixed 50.
[DllImport("AXL.dll")] public static extern uint AxmHomeGetStepTrace(int nAxisNo, ref uint upStepCount, ref uint upMainStepNumber, ref uint upStepNumber, ref uint upStepBranch);

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
[DllImport("AXL.dll")] public static extern uint AxmHomeSetConfig(int nAxisNo, uint uZphasCount, int nHomeMode, int nClearSet, double dOrgVel, double dLastVel, double dLeavePos);
// Return home setting parameters of axis specified by user.
[DllImport("AXL.dll")] public static extern uint AxmHomeGetConfig(int nAxisNo, ref uint upZphasCount, ref int npHomeMode, ref int npClearSet, ref double dpOrgVel, ref double dpLastVel, ref double dpLeavePos); //KKJ(070215)


// Start home search of axis specified by user
// Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
// If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
// Move direction      : CW when Vel value is positive, CCW when negative.
[DllImport("AXL.dll")] public static extern uint AxmHomeSetMoveSearch(int nAxisNo, double dVel, double dAccel, double dDecel);


// Start home return of axis specified by user.
// Set when lHomeMode is used: set 0 - 12
// If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
// Move direction      : CW when Vel value is positive, CCW when negative.
[DllImport("AXL.dll")] public static extern uint AxmHomeSetMoveReturn(int nAxisNo, double dVel, double dAccel, double dDecel);


// Home separation of axis specified by user is started.
// Move direction      : CW when Vel value is positive, CCW when negative.
[DllImport("AXL.dll")] public static extern uint AxmHomeSetMoveLeave(int nAxisNo, double dVel, double dAccel, double dDecel);


// User start home search of multi-axis specified by user.
// Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
// If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
// Move direction      : CW when Vel value is positive, CCW when negative.
[DllImport("AXL.dll")] public static extern uint AxmHomeSetMultiMoveSearch(int nArraySize, ref int npAxesNo, ref double dpVel, ref double dpAccel, ref double dpDecel);


//Set move velocity profile mode of specific coordinate system.
// (caution : Available to use only after axis mapping)
//ProfileMode : '0' - symmetry Trapezoid
//              '1' - asymmetric Trapezoid
//              '2' - symmetry Quasi-S Curve
//              '3' - symmetry S Curve
//              '4' - asymmetric S Curve
[DllImport("AXL.dll")] public static extern uint AxmContiSetProfileMode(int nCoord, uint uProfileMode);
// Return move velocity profile mode of specific coordinate system.
[DllImport("AXL.dll")] public static extern uint AxmContiGetProfileMode(int nCoord, ref uint upProfileMode);


//========== Reading group for input interrupt occurrence flag
// Reading the interrupt occurrence state by bit unit in specified input contact module and Offset position of Interrupt Flag Register
[DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadBit(int nModuleNo, int nOffset, ref uint upValue);
// Reading the interrupt occurrence state by byte unit in specified input contact module and Offset position of Interrupt Flag Register
[DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadByte(int nModuleNo, int nOffset, ref uint upValue);
// Reading the interrupt occurrence state by word unit in specified input contact module and Offset position of Interrupt Flag Register
[DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadWord(int nModuleNo, int nOffset, ref uint upValue);
// Reading the interrupt occurrence state by double word unit in specified input contact module and Offset position of Interrupt Flag Register
[DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagReadDword(int nModuleNo, int nOffset, ref uint upValue);
// Reading the interrupt occurrence state by bit unit in entire input contact module and Offset position of Interrupt Flag Register
[DllImport("AXL.dll")] public static extern uint AxdiInterruptFlagRead(int nOffset, ref uint upValue);


//========= API related log ==========================================================================================
// This API sets or resets in order to monitor the API execution result of set axis in EzSpy.
// uUse : use or not use => DISABLE(0), ENABLE(1)
[DllImport("AXL.dll")] public static extern uint AxmLogSetAxis(int nAxisNo, uint uUse);


// This API verifies if the API execution result of set axis is monitored in EzSpy.
[DllImport("AXL.dll")] public static extern uint AxmLogGetAxis(int nAxisNo, ref uint upUse);


//==Log
//Set whether to log output to EzSpy of specified input channel
[DllImport("AXL.dll")] public static extern uint AxaiLogSetChannel(int nChannelNo, uint uUse);
//Verify whether to log output to EzSpy of specified input channel
[DllImport("AXL.dll")] public static extern uint AxaiLogGetChannel(int nChannelNo, ref uint upUse);


//Set whether to log output in EzSpy of specified output channel
[DllImport("AXL.dll")] public static extern uint AxaoLogSetChannel(int nChannelNo, uint uUse);
//Verify whether log output is done in EzSpy of specified output channel.
[DllImport("AXL.dll")] public static extern uint AxaoLogGetChannel(int nChannelNo, ref uint upUse);


// Set whether execute log output on EzSpy of specified module
[DllImport("AXL.dll")] public static extern uint AxdLogSetModule(int nModuleNo, uint uUse);
// Verify whether execute log output on EzSpy of specified module
[DllImport("AXL.dll")] public static extern uint AxdLogGetModule(int nModuleNo, ref uint upUse);


// Verify whether to firmware version designated RTEX board.
[DllImport("AXL.dll")] public static extern uint AxlGetFirmwareVersion(int nBoardNo, ref byte szVersion);
// Sent to firmware designated board.
[DllImport("AXL.dll")] public static extern uint  AxlSetFirmwareCopy(int nBoardNo, ref ushort wData, ref ushort wCmdData);
// Execute Firmware update to designated board.
[DllImport("AXL.dll")] public static extern uint AxlSetFirmwareUpdate(int nBoardNo);
// Verify whether currently RTEX status Initialized.
[DllImport("AXL.dll")] public static extern uint AxlCheckStatus(int nBoardNo, ref uint dwStatus);
// Execute universal command designated axis of board.
[DllImport("AXL.dll")] public static extern uint AxlRtexUniversalCmd(int nBoardNo, ushort wCmd, ushort wOffset, ref ushort wData);
// Execute RTEX communication command designated axis.
[DllImport("AXL.dll")] public static extern uint AxmRtexSlaveCmd(int nAxisNo, uint dwCmdCode, uint dwTypeCode, uint dwIndexCode, uint dwCmdConfigure, uint dwValue);
// Verify whether Result of RTEX communication command designated axis.
[DllImport("AXL.dll")] public static extern uint AxmRtexGetSlaveCmdResult(int nAxisNo, ref uint dwIndex, ref uint dwValue);
[DllImport("AXL.dll")] public static extern uint AxmRtexGetSlaveCmdResultEx(int nAxisNo, ref uint dwpCommand, ref uint dwpType, ref uint dwpIndex, ref uint dwpValue);
// Verify whether RTEX status information designated axis.
[DllImport("AXL.dll")] public static extern uint AxmRtexGetAxisStatus(int nAxisNo, ref uint dwStatus);
// Verify whether RTEX communication return information designated axis.(Actual position, Velocity, Torque)
[DllImport("AXL.dll")] public static extern uint AxmRtexGetAxisReturnData(int nAxisNo,  ref uint dwReturn1, ref uint dwReturn2, ref uint dwReturn3);
// Verify whether currently status information of RTEX slave axis.(mechanical, Inposition and etc)
[DllImport("AXL.dll")] public static extern uint AxmRtexGetAxisSlaveStatus(int nAxisNo,  ref uint dwStatus);


// Enter the universal network command of specified MLII slave axis.
[DllImport("AXL.dll")] public static extern uint AxmSetAxisCmd(int nAxisNo, ref uint tagCommand);
// Verifying result of universal network command of specified MLII slave axis.
[DllImport("AXL.dll")] public static extern uint AxmGetAxisCmdResult(int nAxisNo, ref uint tagCommand);


// The specified SID Write the result of the network command to the slave module and return it.
[DllImport("AXL.dll")] public static extern uint AxdSetAndGetSlaveCmdResult(int nModuleNo, ref uint tagSetCommand, ref uint tagGetCommand);
[DllImport("AXL.dll")] public static extern uint AxaSetAndGetSlaveCmdResult(int nModuleNo, ref uint tagSetCommand, ref uint tagGetCommand);
[DllImport("AXL.dll")] public static extern uint AxcSetAndGetSlaveCmdResult(int nModuleNo, ref uint tagSetCommand, ref uint tagGetCommand);

// Verify DPRAM data.
[DllImport("AXL.dll")] public static extern uint AxlGetDpRamData(int nBoardNo, ushort uAddress, ref uint upRdData);
// Verify DPRAM data in Word unit.
[DllImport("AXL.dll")] public static extern uint AxlBoardReadDpramWord(int nBoardNo, ushort uOffset, ref uint upRdData);
// Set DPRAM data in Word unit.
[DllImport("AXL.dll")] public static extern uint AxlBoardWriteDpramWord(int nBoardNo, ushort uOffset, uint uWrData);

// Transmit instructions of each slave of each board.
[DllImport("AXL.dll")] public static extern uint AxlSetSendBoardEachCommand(int nBoardNo, uint uCommand, ref uint upSendData, uint uLength);
// Transmit instructions to each board.
[DllImport("AXL.dll")] public static extern uint AxlSetSendBoardCommand(int nBoardNo, uint uCommand, ref uint upSendData, uint uLength);
// Verify the response of each board.
[DllImport("AXL.dll")] public static extern uint AxlGetResponseBoardCommand(int nBoardNo, ref uint upReadData);

// Reading firmware version function of slaves in network type master board.
// Declare with array of ucaFirmwareVersion byte type(Size : 4 or more)
[DllImport("AXL.dll")] public static extern uint AxmInfoGetFirmwareVersion(int nAxisNo, ref byte ucaFirmwareVersion);
[DllImport("AXL.dll")] public static extern uint AxaInfoGetFirmwareVersion(int nModuleNo, ref byte ucaFirmwareVersion);
[DllImport("AXL.dll")] public static extern uint AxdInfoGetFirmwareVersion(int nModuleNo, ref byte ucaFirmwareVersion);
[DllImport("AXL.dll")] public static extern uint AxcInfoGetFirmwareVersion(int nModuleNo, ref byte ucaFirmwareVersion);


//======== Only for PCI-R1604-MLII ===========================================================================
// Set the value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
// Default value : Max
// Setting value Range : 0 ~ 4000H
// If it is set to 4000H or higher, the setting is set higher than that, but the operation is applied to the value of 4000H.
[DllImport("AXL.dll")] public static extern uint AxmSetTorqFeedForward(int nAxisNo, uint uTorqFeedForward);

// It is API that read value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
// Default value : Max
[DllImport("AXL.dll")] public static extern uint AxmGetTorqFeedForward(int nAxisNo, ref uint upTorqFeedForward);

// It is API that set the value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
// Default value : 0
// Setting value Range : 0 ~ FFFFH
[DllImport("AXL.dll")] public static extern uint AxmSetVelocityFeedForward(int nAxisNo, uint uVelocityFeedForward);

// It is API that read value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
[DllImport("AXL.dll")] public static extern uint  AxmGetVelocityFeedForward(int nAxisNo, ref uint upVelocityFeedForward);


// Set Encoder type.
// Default value : 0(TYPE_INCREMENTAL)
// Setting range : 0 ~ 1
// dwEncoderType : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
[DllImport("AXL.dll")] public static extern uint AxmSignalSetEncoderType(int nAxisNo, uint uEncoderType);


// Verify Encoder type.
[DllImport("AXL.dll")] public static extern uint AxmSignalGetEncoderType(int nAxisNo, ref uint upEncoderType);



// For updating the slave firmware(only for RTEX-PM).
//DWORD   __stdcall AxmSetSendAxisCommand(long lAxisNo, WORD wCommand, WORD* wpSendData, WORD wLength);

//======== Only for PCI-R1604-RTEX, RTEX-PM==============================================================
// When Input Universal Input 2, 3, Set Jog move velocity
// Set only once execute after all drive setting (Ex, PulseOutMethod, MoveUnitPerPulse etc..)
[DllImport("AXL.dll")] public static extern uint AxmMotSetUserMotion(int nAxisNo, double dVelocity, double dAccel, double dDecel);


// When Input Universal Input 2, 3, Set Jog move usage
// Setting value :  0(DISABLE), 1(ENABLE)
[DllImport("AXL.dll")] public static extern uint AxmMotSetUserMotionUsage(int nAxisNo, uint dwUsage);


// Set Load/UnLoad Position to Automatically move use MPGP Input
[DllImport("AXL.dll")] public static extern uint AxmMotSetUserPosMotion(int nAxisNo, double dVelocity, double dAccel, double dDecel, double dLoadPos, double dUnLoadPos, uint dwFilter, uint dwDelay);


// Set Usage Load/UnLoad Position to Automatically move use MPGP Input
// Setting value :  0(DISABLE), 1(Position function A), 2(Position function B)
[DllImport("AXL.dll")] public static extern uint AxmMotSetUserPosMotionUsage(int nAxisNo, uint dwUsage);

//========================================================================================================

//======== SIO-CN2CH, Only for absolute position trigger module(B0) =======================================
// The API of writing memory data.
[DllImport("AXL.dll")] public static extern uint AxcKeWriteRamDataAddr(int nChannelNo, uint dwAddr, uint dwData);
// The API of reading memory data.
[DllImport("AXL.dll")] public static extern uint AxcKeReadRamDataAddr(int nChannelNo, uint dwAddr, ref uint dwpData);
// Memory initialization API.
[DllImport("AXL.dll")] public static extern uint AxcKeResetRamDataAll(int nModuleNo, uint dwData);
// Trigger timeout setting API.
[DllImport("AXL.dll")] public static extern uint AxcTriggerSetTimeout(int nChannelNo, uint dwTimeout);
// Trigger timeout checking API.
[DllImport("AXL.dll")] public static extern uint AxcTriggerGetTimeout(int nChannelNo, ref uint dwpTimeout);
// Trigger Waiting State checking API.
[DllImport("AXL.dll")] public static extern uint AxcStatusGetWaitState(int nChannelNo, ref uint dwpState);
// Trigger Waiting State setting API.
[DllImport("AXL.dll")] public static extern uint AxcStatusSetWaitState(int nChannelNo, uint dwState);

// Write command to designated channel.
[DllImport("AXL.dll")] public static extern uint AxcKeSetCommandData32(int nChannelNo, uint dwCommand, uint dwData);
// Write command to designated channel.
[DllImport("AXL.dll")] public static extern uint AxcKeSetCommandData16(int nChannelNo, uint dwCommand, uint wData);
// Verify register of specified channel.
[DllImport("AXL.dll")] public static extern uint AxcKeGetCommandData32(int nChannelNo, uint dwCommand, ref uint dwpData);
// Verify register of specified channel.
[DllImport("AXL.dll")] public static extern uint AxcKeGetCommandData16(int nChannelNo, uint dwCommand, ref uint wpData);

//========================================================================================================

//======== Only for PCI-N804/N404, Sequence Motion ===========================================================
// Set Axis Information of sequence Motion (min 1axis)
// lSeqMapNo : Sequence Motion Index Point
// lSeqMapSize : Number of axis
// long* LSeqAxesNo : Number of arrary
[DllImport("AXL.dll")] public static extern uint AxmSeqSetAxisMap(int nSeqMapNo, int nSeqMapSize, ref int nSeqAxesNo);
[DllImport("AXL.dll")] public static extern uint AxmSeqGetAxisMap(int nSeqMapNo, ref int nSeqMapSize, ref int nSeqAxesNo);


// Set Standard(Master)Axis of Sequence Motion.
// By all means Set in AxmSeqSetAxisMap setting axis.
[DllImport("AXL.dll")] public static extern uint AxmSeqSetMasterAxisNo(int nSeqMapNo, int nMasterAxisNo);



// Notifies the library node start loading of Sequence Motion.
[DllImport("AXL.dll")] public static extern uint AxmSeqBeginNode(int nSeqMapNo);



// Notifies the library node end loading of Sequence Motion.
[DllImport("AXL.dll")] public static extern uint AxmSeqEndNode(int nSeqMapNo);



// Start Sequence Motion Move.
[DllImport("AXL.dll")] public static extern uint AxmSeqStart(int nSeqMapNo, ref uint dwStartOption);



// Set each profile node Information of Sequence Motion in Library.
// if used 1axis Sequence Motion, Must be Set *dPosition one Array.
[DllImport("AXL.dll")] public static extern uint AxmSeqAddNode(int nSeqMapNo, ref double dPosition, double dVelocity, double dAcceleration, double dDeceleration, double dNextVelocity);



// Return Node Index number of Sequence Motion.
[DllImport("AXL.dll")] public static extern uint AxmSeqGetNodeNum(int nSeqMapNo, ref int nCurNodeNo);


// Return All node count of Sequence Motion.
[DllImport("AXL.dll")] public static extern uint AxmSeqGetTotalNodeNum(int nSeqMapNo, ref int nTotalNodeCnt);


// Return Sequence Motion drive status  of specific SeqMap.
// dwInMotion : 0(Drive end), 1(In drive)
[DllImport("AXL.dll")] public static extern uint AxmSeqIsMotion(int nSeqMapNo, ref uint dwInMotion);


// Clear Sequence Motion Memory.
[DllImport("AXL.dll")] public static extern uint AxmSeqWriteClear(int nSeqMapNo);


// Stop sequence motion
// dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
[DllImport("AXL.dll")] public static extern uint AxmSeqStop(int nSeqMapNo, uint dwStopMode);


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
[DllImport("AXL.dll")] public static extern uint AxmStatusSetMon(int nAxisNo, uint dwParaNo1, uint dwParaNo2, uint dwParaNo3, uint dwParaNo4, uint dwUse);
[DllImport("AXL.dll")] public static extern uint AxmStatusGetMon(int nAxisNo, ref uint dwpParaNo1, ref uint dwpParaNo2, ref uint dwpParaNo3, ref uint dwpParaNo4, ref uint dwpUse);
[DllImport("AXL.dll")] public static extern uint AxmStatusReadMon(int nAxisNo, ref uint dwpParaNo1, ref uint dwpParaNo2, ref uint dwpParaNo3, ref uint dwpParaNo4, ref uint dwDataValid);
[DllImport("AXL.dll")] public static extern uint AxmStatusReadMonEx(int nAxisNo, ref int npDataCnt, ref uint dwpReadData);

//=============================================================================================================

//======== Only for PCI-R32IOEV-RTEX ===========================================================================
// The API for read or write HPI register which allocated as I/O port.
// I/O Registers for HOST interface.
// I/O 00h Host status register (HSR)
// I/O 04h Host-to-DSP control register (HDCR)
// I/O 08h DSP page register (DSPP)
// I/O 0Ch Reserved
[DllImport("AXL.dll")] public static extern uint AxlSetIoPort(int nBoardNo, uint dwAddr, uint dwData);
[DllImport("AXL.dll")] public static extern uint AxlGetIoPort(int nBoardNo, uint dwAddr, ref uint dwpData);

//======== Only for PCI-R3200-MLIII ===========================================================================
// Basic information setting API for firmware update of M-III Master board.
[DllImport("AXL.dll")] public static extern uint AxlM3SetFWUpdateInit(int nBoardNo, uint dwTotalPacketSize, uint dwProcTotalStepNo);
// Verify setting value of 'AxlM3SetFWUpdateInit'.
[DllImport("AXL.dll")] public static extern uint AxlM3GetFWUpdateInit(int nBoardNo, ref uint dwTotalPacketSize, ref uint dwProcTotalStepNo);

// M-III Master board firmware update data transfer API.
[DllImport("AXL.dll")] public static extern uint AxlM3SetFWUpdateCopy(int nBoardNo, ref uint pdwPacketData, uint dwPacketSize);
// Verify setting value of 'AxlM3SetFWUpdateCopy'.
[DllImport("AXL.dll")] public static extern uint AxlM3GetFWUpdateCopy(int nBoardNo, ref uint dwPacketSize);

// Execute firmware update of M-III Master Board.
[DllImport("AXL.dll")] public static extern uint AxlM3SetFWUpdate(int nBoardNo, uint dwFlashBurnStepNo);
// Verifying result of execute firmware update of M-III Master Board.
[DllImport("AXL.dll")] public static extern uint AxlM3GetFWUpdate(int nBoardNo, ref uint dwFlashBurnStepNo, ref uint dwIsFlashBurnDone);

// The API for setting EEPROM data of M-III Master board.
[DllImport("AXL.dll")] public static extern uint AxlM3SetCFGData(int nBoardNo, ref uint pCmdData, uint CmdDataSize);
// The API for getting data from EEPROM of M-III Master board.
[DllImport("AXL.dll")] public static extern uint AxlM3GetCFGData(int nBoardNo, ref uint pCmdData, uint CmdDataSize);

// The API for setting CONNECT PARAMETER information of M-III Master board.
[DllImport("AXL.dll")] public static extern uint AxlM3SetMCParaUpdateInit(int nBoardNo, ushort wCh0Slaves, ushort wCh1Slaves, uint dwCh0CycTime, uint dwCh1CycTime, uint dwChInfoMaxRetry);
// The API for verifying CONNECT PARAMETER information of M-III Master board.
[DllImport("AXL.dll")] public static extern uint AxlM3GetMCParaUpdateInit(int nBoardNo, ref ushort wCh0Slaves, ref ushort wCh1Slaves, ref uint dwCh0CycTime, ref uint dwCh1CycTime, ref uint dwChInfoMaxRetry);
// The API for transmit CONNECT PARAMETER information of M-III Master board.
[DllImport("AXL.dll")] public static extern uint AxlM3SetMCParaUpdateCopy(int nBoardNo, ushort wIdx, ushort wChannel, ushort wSlaveAddr, uint dwProtoCalType, uint dwTransBytes, uint dwDeviceCode);
// The API for verifying transmit CONNECT PARAMETER information of M-III Master board.
[DllImport("AXL.dll")] public static extern uint AxlM3GetMCParaUpdateCopy(int nBoardNo, ushort wIdx, ref ushort wChannel, ref ushort wSlaveAddr, ref uint dwProtoCalType, ref uint dwTransBytes, ref uint dwDeviceCode);

// The API for checking register as DWord unit within M-III Master board.
[DllImport("AXL.dll")] public static extern uint AxlBoardReadDWord(int nBoardNo, ushort wOffset, ref uint dwData);
// The API for setting register as DWord unit within M-III Master board.
[DllImport("AXL.dll")] public static extern uint AxlBoardWriteDWord(int nBoardNo, ushort wOffset, uint dwData);

// Setting and verifying extension register as DWord unit within board.
[DllImport("AXL.dll")] public static extern uint AxlBoardReadDWordEx(int nBoardNo, uint dwOffset, ref uint dwData);
[DllImport("AXL.dll")] public static extern uint AxlBoardWriteDWordEx(int nBoardNo, uint dwOffset, uint dwData);


// The API for setting servo to stop mode.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetCtrlStopMode(int nAxisNo, byte bStopMode);
// The API for setting servo to Lt selection state.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetCtrlLtSel(int nAxisNo, byte bLtSel1, byte bLtSel2);
// The API for verifying servo I/O input state.
[DllImport("AXL.dll")] public static extern uint AxmStatusReadServoCmdIOInput(int nAxisNo, ref uint upStatus);
// Servo interpolation drive API.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoExInterpolate(int nAxisNo, uint dwTPOS, uint dwVFF, uint dwTFF, uint dwTLIM, uint dwExSig1, uint dwExSig2);
// The API for setting bias of the servo actuator.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetExpoAccBias(int nAxisNo, ushort wBias);
// The API for setting time of the servo actuator.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetExpoAccTime(int nAxisNo, ushort wTime);
// The API for setting time of the servo move.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetMoveAvrTime(int nAxisNo, ushort wTime);
// The API for setting acc filter of the servo.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetAccFilter(int nAxisNo, byte bAccFil);
// The API for setting status monitor1 of the servo.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetCprmMonitor1(int nAxisNo, byte bMonSel);
// The API for setting status monitor2 of the servo.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetCprmMonitor2(int nAxisNo, byte bMonSel);
// The API for verifying status monitor1 of the servo.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoStatusReadCprmMonitor1(int nAxisNo, ref uint upStatus);
// The API for verifying status monitor2 of the servo.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoStatusReadCprmMonitor2(int nAxisNo, ref uint upStatus);
// The API for setting Dec of servo actuator.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetAccDec(int nAxisNo, ushort wAcc1, ushort wAcc2, ushort wAccSW, ushort wDec1, ushort wDec2, ushort wDecSW);
// The API for servo stop.
[DllImport("AXL.dll")] public static extern uint AxmM3ServoSetStop(int nAxisNo, int nMaxDecel);

//========== Common commands of standard I/O dvices =========================================================================
// The API for return parameter setting value of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3GetStationParameter(int nBoardNo, int nModuleNo, ushort wNo, byte bSize, byte bModuleType, ref byte pbParam);
// The API for setting parameter value of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationParameter(int nBoardNo, int nModuleNo, ushort wNo, byte bSize, byte bModuleType, ref byte pbParam);
// The API for return ID value of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3GetStationIdRd(int nBoardNo, int nModuleNo, byte bIdCode, byte bOffset, byte bSize, byte bModuleType, ref byte pbParam);
// The API used as invalid command of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationNop(int nBoardNo, int nModuleNo, byte bModuleType);
// The API for set up each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationConfig(int nBoardNo, int nModuleNo, byte bConfigMode, byte bModuleType);
// The API for return alarm and warning status value of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3GetStationAlarm(int nBoardNo, int nModuleNo, ushort wAlarmRdMod, ushort wAlarmIndex, byte bModuleType, ref ushort pwAlarmData);
// The API for clearing alarm and warning status value of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationAlarmClear(int nBoardNo, int nModuleNo, ushort wAlarmClrMod, byte bModuleType);
// The API for setting establish synchronous communication with each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationSyncSet(int nBoardNo, int nModuleNo, byte bModuleType);
// The API for setting connection with each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationConnect(int nBoardNo, int nModuleNo, byte bVer, byte bComMode, byte bComTime, byte bProfileType, byte bModuleType);
// The API for setting disconnection with each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationDisConnect(int nBoardNo, int nModuleNo, byte bModuleType);
// The API for return of non-volatile parameter setting value.
[DllImport("AXL.dll")] public static extern uint AxlM3GetStationStoredParameter(int nBoardNo, int nModuleNo, ushort wNo, byte bSize, byte bModuleType, ref byte pbParam);
// The API for setting non-volatile parameter value of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationStoredParameter(int nBoardNo, int nModuleNo, ushort wNo, byte bSize, byte bModuleType, ref byte pbParam);
// The API for return of memory setting value of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3GetStationMemory(int nBoardNo, int nModuleNo, ushort wSize, uint dwAddress, byte bModuleType, byte bMode, byte bDataType, ref byte pbData);
// The API for setting memory value of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationMemory(int nBoardNo, int nModuleNo, ushort wSize, uint dwAddress, byte bModuleType, byte bMode, byte bDataType, ref byte pbData);

//========== Connection commands of standard I/O dvices =========================================================================
// The API for setting value of automatic access mode of each re-ordered slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationAccessMode(int nBoardNo, int nModuleNo, byte bModuleType, byte bRWSMode);
// The API for return of automatic access mode setting value of each re-ordered slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3GetStationAccessMode(int nBoardNo, int nModuleNo, byte bModuleType, ref byte bRWSMode);
// The API for set synchronous auto connect mode of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetAutoSyncConnectMode(int nBoardNo, int nModuleNo, byte bModuleType, uint dwAutoSyncConnectMode);
// The API for return of synchronous auto connect mode setting value of each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3GetAutoSyncConnectMode(int nBoardNo, int nModuleNo, byte bModuleType, ref uint dwpAutoSyncConnectMode);
// The API for establish a single synchronization connection to each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SyncConnectSingle(int nBoardNo, int nModuleNo, byte bModuleType);
// The API for establish a single synchronization disconnection to each slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SyncDisconnectSingle(int nBoardNo, int nModuleNo, byte bModuleType);
// The API for verifying connection status with slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3IsOnLine(int nBoardNo, int nModuleNo, ref uint dwData);

//========== Profile commands of standard I/O =========================================================================
// The API for return of data setting value for each synchronous I/O slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3GetStationRWS(int nBoardNo, int nModuleNo, byte bModuleType, ref uint pdwParam, byte bSize);
// The API for setting data value for each synchronous I/O slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationRWS(int nBoardNo, int nModuleNo, byte bModuleType, ref uint pdwParam, byte bSize);
// The API for return of data setting value for each asynchronous I/O slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3GetStationRWA(int nBoardNo, int nModuleNo, byte bModuleType, ref uint pdwParam, byte bSize);
// The API for setting data value for each asynchronous I/O slave device.
[DllImport("AXL.dll")] public static extern uint AxlM3SetStationRWA(int nBoardNo, int nModuleNo, byte bModuleType, ref uint pdwParam, byte bSize);

// Set the MLIII adjustment operation
// dwReqCode == 0x1005 : parameter initialization : 20sec
// dwReqCode == 0x1008 : absolute encoder reset   : 5sec
// dwReqCode == 0x100E : automatic offset adjustment of motor current detection signals  : 5sec
// dwReqCode == 0x1013 : Multiturn limit setting  : 5sec
[DllImport("AXL.dll")] public static extern uint AxmM3AdjustmentOperation(int nAxisNo, uint dwReqCode);

// API for diagnosing home search progress.(Only for M3)
[DllImport("AXL.dll")] public static extern uint AxmHomeGetM3FWRealRate(int nAxisNo, ref uint upHomeMainStepNumber, ref uint upHomeSubStepNumber, ref uint upHomeLastMainStepNumber, ref uint upHomeLastSubStepNumber);
// Return adjusted position value when escaping sensor zone from origin search.(Only for M3)
[DllImport("AXL.dll")] public static extern uint AxmHomeGetM3OffsetAvoideSenArea(int nAxisNo, ref double dPos);
// The API for Setting adjusted position value when escaping sensor zone from origin search.(Only for M3)
// If dPos setting value is '0', adjusted position value will be set automatically when automatically escaping.
// 'dPos' should be a positive number.
[DllImport("AXL.dll")] public static extern uint AxmHomeSetM3OffsetAvoideSenArea(int nAxisNo, double dPos);


// Setting usage criterion of absolute encoder. Set whether to CMD/ACT POS initialize after origin search.(Only for M3)
// dwSel: 0, CMD/ACTPOS will be set '0' after origin search.(Default)
// dwSel: 1, CMD/ACTPOS will be not set after origin search.
[DllImport("AXL.dll")] public static extern uint AxmM3SetAbsEncOrgResetDisable(int nAxisNo, uint dwSel);

// Get 'AxmM3SetAbsEncOrgResetDisable' setting value.(Only for M3)
// upSel: 0, CMD / ACTPOS set to 0 after home search. (Default)
// upSel: 1, CMD / ACTPOS value is not set after home search.
[DllImport("AXL.dll")] public static extern uint AxmM3GetAbsEncOrgResetDisable(int nAxisNo, ref uint upSel);


// Setting whether using alarm maintenance function when switch to slave offline mode.(Only for M3)
// dwSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
// dwSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
[DllImport("AXL.dll")] public static extern uint AxmM3SetOfflineAlarmEnable(int nAxisNo, uint dwSel);

// Get 'AxmM3SetOfflineAlarmEnable' setting value.(Only for M3)
// upSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
// upSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
[DllImport("AXL.dll")] public static extern uint AxmM3GetOfflineAlarmEnable(int nAxisNo, ref uint upSel);

// Read value of slave online or offline status. (Only for M3)
// upSel: 0, ONLINE->OFFLINE Not converted
// upSel: 1, ONLINE->OFFLINE converted
[DllImport("AXL.dll")] public static extern uint AxmM3ReadOnlineToOfflineStatus(int nAxisNo, ref uint upStatus);

    [DllImport("AXL.dll")] public static extern uint AxlSetLockMode(int lBoardNo, uint wLockMode);
    [DllImport("AXL.dll")] public static extern uint AxlSetLockData(int lBoardNo, uint dwTotalNodeNum, ref uint dwpNodeNo, ref uint dwpNodeID, ref uint dwpLockData);
    [DllImport("AXL.dll")] public static extern uint AxmMoveStartPosWithAVC(int lAxisNo, double dPosition, double dMaxVelocity, double dMaxAccel, double dMinJerk, ref double dpMoveVelocity, ref double dpMoveAccel, ref double dpMoveJerk);
//======== API for EtherCAT only =============================================================================
// The API for read VendorID, ProductCode and RevisionNo of EtherCat slave product by using StationAddress.
[DllImport("AXL.dll")] public static extern uint AxlECatGetProductInfo(uint dwStationAddress, ref uint upVendorID, ref uint upProductCode, ref uint upRevisionNo);
    [DllImport("AXL.dll")] public static extern uint AxlECatGetProductInfoEx(int lBoardNo, uint dwStationAddress, ref uint pdwVendorID, ref uint pdwProductCode, ref uint pdwRevisionNo);

// The API for verifying network status of EtherCAT slave product by using StationAddress.
[DllImport("AXL.dll")] public static extern uint AxlECatGetModuleStatus(uint dwStationAddress);

// Read input PDO(Process Data Objects)
// dwBitOffset     : ProcessImage inputs bit offset value.
// dwDataBitLength : bit size of input pdo data.
// pbyData         : The Buffer for inserting read data.
[DllImport("AXL.dll")] public static extern uint AxlECatReadPdoInput(uint dwBitOffset, uint dwDataBitLength, ref byte bpData);
    [DllImport("AXL.dll")] public static extern uint AxlECatReadPdoInputEx(int lBoardNo, uint dwBitOffset, uint dwDataBitLength, ref byte pbyData);

// Read output PDO(Process Data Objects)
// dwBitOffset     : ProcessImage outputs bit offset value.
// dwDataBitLength : bit size of input pdo data.(for read)
// pbyData         : The Buffer for inserting read data.
[DllImport("AXL.dll")] public static extern uint AxlECatReadPdoOutput(uint dwBitOffset, uint dwDataBitLength, ref byte bpData);
    [DllImport("AXL.dll")] public static extern uint AxlECatReadPdoOutputEx(int lBoardNo, uint dwBitOffset, uint dwDataBitLength, ref byte pbyData);

// Write value to output process data.
// dwBitOffset     : ProcessImage outputs bit offset value.
// dwDataBitLength : bit size of output pdo data.(for write)
// pbyData         : The Buffer for inserting write data.
[DllImport("AXL.dll")] public static extern uint AxlECatWritePdoOutput(uint dwBitOffset, uint dwDataBitLength, ref byte pbyData);

// Read SDO(Service Data Objects) by using COE.
[DllImport("AXL.dll")] public static extern uint AxlECatReadSdo(uint dwStationAddress, ushort wObjectIndex, byte byObjectSubIndex, ref byte pbyData, uint dwDataLength, ref uint pdwReadDataLength);
    [DllImport("AXL.dll")] public static extern uint AxlECatReadSdoEx(int lBoardNo, uint dwStationAddress, uint wObjectIndex, byte byObjectSubIndex, ref byte pbyData, uint dwDataLength, ref uint pdwReadDataLength);

// Store values in SDO by using COE.
[DllImport("AXL.dll")] public static extern uint AxlECatWriteSdo(uint dwStationAddress, ushort wObjectIndex, byte byObjectSubIndex, ref byte pbyData, uint dwDataLength);
    [DllImport("AXL.dll")] public static extern uint AxlECatWriteSdoEx(int lBoardNo, uint dwStationAddress, uint wObjectIndex, byte byObjectSubIndex, ref byte pbyData, uint dwDataLength);

    [DllImport("AXL.dll")] public static extern uint AxlECatReadSdoFromAxisDouble(int lAxisNo, uint wObjectIndex, byte byObjectSubIndex, ref double pdData);

    [DllImport("AXL.dll")] public static extern uint AxlECatWriteSdoFromAxisDouble(int lAxisNo, uint wObjectIndex, byte byObjectSubIndex, ref double pdData);
// Read SDO(DWORD type) through the axis number.
[DllImport("AXL.dll")] public static extern uint AxlECatReadSdoFromAxisDword(int  lAxisNo, ushort wObjectIndex, byte byObjectSubIndex, ref uint pdwData);

// Store values in SDO(DWORD type) through the axis number.
[DllImport("AXL.dll")] public static extern uint AxlECatWriteSdoFromAxisDword(int  lAxisNo, ushort wObjectIndex, byte byObjectSubIndex, ref uint pdwData);

// Read SDO(WORD type) through the axis number.
[DllImport("AXL.dll")] public static extern uint AxlECatReadSdoFromAxisWord(int  lAxisNo, ushort wObjectIndex, byte byObjectSubIndex, ref ushort pwData);

// Store values in SDO(WORD type) through the axis number.
[DllImport("AXL.dll")] public static extern uint AxlECatWriteSdoFromAxisWord(int  lAxisNo, ushort wObjectIndex, byte byObjectSubIndex, ref ushort pwData);

// Read SDO(BYTE type) through the axis number.
[DllImport("AXL.dll")] public static extern uint AxlECatReadSdoFromAxisByte(int  lAxisNo, ushort wObjectIndex, byte byObjectSubIndex, ref byte pbyData);

// Store values in SDO(BYTE type) through the axis number.
[DllImport("AXL.dll")] public static extern uint AxlECatWriteSdoFromAxisByte(int  lAxisNo, ushort wObjectIndex, byte byObjectSubIndex, ref byte pbyData);

// Read value of EEPROM.
[DllImport("AXL.dll")] public static extern uint AxlECatReadEEPRom(uint dwStationAddress, ushort wEEPRomStartOffset, ref ushort pwData, uint dwDataLength);

// Write value to EEPROM.
[DllImport("AXL.dll")] public static extern uint AxlECatWriteEEPRom(uint dwStationAddress, ushort wEEPRomStartOffset, ref ushort pwData, uint dwDataLength);
    [DllImport("AXL.dll")] public static extern uint AxlECatReadEEPRomEx(int lBoardNo, uint dwStationAddress, uint wEEPRomStartOffset, ref uint pwData, uint dwDataLength);

    [DllImport("AXL.dll")] public static extern uint AxlECatWriteEEPRomEx(int lBoardNo, uint dwStationAddress, uint wEEPRomStartOffset, ref uint pwData, uint dwDataLength);

// Read value of a register.
[DllImport("AXL.dll")] public static extern uint AxlECatReadRegister(uint dwStationAddress, ushort wRegisterOffset, object pvData, ushort wLen); // Intptr?

// Write value of a register.
[DllImport("AXL.dll")] public static extern uint AxlECatWriteRegister(uint dwStationAddress, ushort wRegisterOffset, object pvData, ushort wLen); // Intptr?

// Save BackupData as a file from among the object dictionary of EtherCat slave.
[DllImport("AXL.dll")] public static extern uint AxlECatSaveHotSwapData(uint dwStationAddress);

// Load BackupData which saved as a file from corresponding EtherCat salve.
[DllImport("AXL.dll")] public static extern uint AxlECatLoadHotSwapData(uint dwStationAddress);


// When using the HotSwapStart API(Function to advance HotSwap only for registered StationAddresses),
//       it stores the StationAddress in HotSwapConfig, confirms existence and deletes it.
[DllImport("AXL.dll")] public static extern uint AxlECatSetHotSwap(uint dwStationAddress);
[DllImport("AXL.dll")] public static extern uint AxlECatIsSetHotSwap(uint dwStationAddress);
[DllImport("AXL.dll")] public static extern uint AxlECatReSetHotSwap(uint dwStationAddress);

// Set EtherCat master mode (configure = 0, RumMode = 1)
[DllImport("AXL.dll")] public static extern uint AxlECatSetMasterMode(uint dwMasterMode);

// Get mode status of EtherCat master.
[DllImport("AXL.dll")] public static extern uint AxlECatGetMasterMode(ref uint pdMasterMode);

// Set MasterOperationMode of EtherCat master.
[DllImport("AXL.dll")] public static extern uint AxlECatSetMasterOperationMode(uint dwOperationMode);

// Get MasterOperationMode of EtherCat master.
[DllImport("AXL.dll")] public static extern uint AxlECatGetMasterOperationMode(ref uint pdwOperationMode);

// Requesting scan command to EtherCat master, and then command to save scaned data to SHM.
[DllImport("AXL.dll")] public static extern uint AxlECatRequestScanData();


// Get total number of scanned slaves.
[DllImport("AXL.dll")] public static extern uint AxlECatGetScanSlaveCount(ref uint pdwSlaveCount);

// Get current status information of EtherCat master.
[DllImport("AXL.dll")] public static extern uint AxlECatGetStatus(ref int pnECMasterStatus, ref int pnECSlaveStatus, ref int pnECConnectedSlave, ref int pnECConfiguredSlave, ref int pnJobTaskCycleCnt, ref uint pdwECMasterNotification);

// Reconnecting failed network.
[DllImport("AXL.dll")] public static extern uint AxlEcatReConnect();


[DllImport("AXL.dll")] public static extern uint AxmECatReadAddress(int nAxisNo, ref uint dwpStationAddress, ref int npAutoIncAddress, ref uint dwpAliasAddress);
[DllImport("AXL.dll")] public static extern uint AxdECatReadAddress(int nModuleNo, ref uint dwpStationAddress, ref int npAutoIncAddress, ref uint dwpAliasAddress);
// Get address information of slave which be set.
[DllImport("AXL.dll")] public static extern uint AxaECatReadAddress(int nModuleNo, ref uint dwpStationAddress, ref int npAutoIncAddress, ref uint dwpAliasAddress);
    [DllImport("AXL.dll")] public static extern uint AxsECatReadAddress(int lPortNo, ref uint dwpStationAddress, ref int lpAutoIncAddress, ref uint dwpAliasAddress);


// Monitor
// Add an item to proceed with data collection.
[DllImport("AXL.dll")] public static extern uint AxlMonitorSetItem(int nItemIndex, uint dwSignalType, int nSignalNo, int nSubSignalNo);

// Get information about items to be collected.
[DllImport("AXL.dll")] public static extern uint AxlMonitorGetIndexInfo(ref int npItemSize, ref int npItemIndex);

// Get detailed settings of each items for data collection progress.
[DllImport("AXL.dll")] public static extern uint AxlMonitorGetItemInfo(int nItemIndex, ref uint dwpSignalType, ref int npSignalNo, ref int npSubSignalNo);

// Reset settings of all data collection items.
[DllImport("AXL.dll")] public static extern uint AxlMonitorResetAllItem();

// Reset settings of selected data collection items.
[DllImport("AXL.dll")] public static extern uint AxlMonitorResetItem(int nItemIndex);

// Set the trigger condition of data collection.
[DllImport("AXL.dll")] public static extern uint AxlMonitorSetTriggerOption(uint dwSignalType, int nSignalNo, int nSubSignalNo, uint dwOperatorType, double dValue1, double dValue2);


// Get the trigger condition of data collection.
//DWORD  __stdcall AxlMonitorGetTriggerOption(DWORD* dwpSignalType, long* lpSignalNo, long* lpSubSignalNo, DWORD* dwpOperatorType, double* dpValue1, double* dpValue2);
// Reset trigger condition of data collection.
[DllImport("AXL.dll")] public static extern uint AxlMonitorResetTriggerOption();

// Start collecting data.
[DllImport("AXL.dll")] public static extern uint AxlMonitorStart(uint dwStartOption, uint dwOverflowOption);

// Stop collecting data.
[DllImport("AXL.dll")] public static extern uint AxlMonitorStop();

// Read collected data.
[DllImport("AXL.dll")] public static extern uint AxlMonitorReadData(ref int npItemSize, ref int npDataCount, ref double dpReadData);


// Read period of data collection.
[DllImport("AXL.dll")] public static extern uint AxlMonitorReadPeriod(ref uint dwpPeriod);



//////////////////////////////////////////////////////////////////////////
// MonitorEx
// Add an item to proceed with data collection.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExSetItem(int nItemIndex, uint dwSignalType, int nSignalNo, int nSubSignalNo);


// Gets information about the items to be collected.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExGetIndexInfo(ref int npItemSize, ref int npItemIndex);


// Gets the detailed settings for each item to proceed with data collection.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExGetItemInfo(int nItemIndex, ref uint dwpSignalType, ref int npSignalNo, ref int npSubSignalNo);


// Reset the settings for all data collection items.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExResetAllItem();


// Reset the settings of the selected data collection item.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExResetItem(int nItemIndex);


// Sets the trigger condition for data collection.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExSetTriggerOption(uint dwSignalType, int nSignalNo, int nSubSignalNo, uint dwOperatorType, double dValue1, double dValue2);



// Reset trigger conditions for data collection.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExResetTriggerOption();


// Start collecting data.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExStart(uint dwStartOption, uint dwOverflowOption);


// Stop collecting data.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExStop();


// Gets collected data.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExReadData(ref long lpItemSize, ref long lpDataCount, ref double dpReadData);


// Gets the period of data collection.
[DllImport("AXL.dll")] public static extern uint AxlMonitorExReadPeriod(ref uint dwpPeriod);



//////////////////////////////////////////////////////////////////////////

// Linear interpolation about 2 axis including information of offset position for X2, Y2 axis.
[DllImport("AXL.dll")] public static extern uint AxmLineMoveDual01(int nCoordNo, ref double dpEndPosition, double dVelocity, double dAccel, double dDecel, double dOffsetLength, double dTotalLength, ref double dpStartOffsetPosition, ref double dpEndOffsetPosition);
// Arc interpolation about 2 axis including information of offset position for X2, Y2 axis.
[DllImport("AXL.dll")] public static extern uint AxmCircleCenterMoveDual01(int nCoordNo, ref int npAxes, ref double dpCenterPosition, ref double dpEndPosition, double dVelocity, double dAccel, double dDecel, uint dwCWDir, double dTotalLength, ref double dpStartOffsetPosition, ref double dpEndOffsetPosition);

// About ECAT Foe
[DllImport("AXL.dll")] public static extern uint AxdSetFirmwareUpdateInfo(int nModuleNo, uint dwTotalDataSize, uint dwTotalPacketSize);
[DllImport("AXL.dll")] public static extern uint AxdSetFirmwareDataTrans(int nModuleNo, uint dwPacketIndex, ref uint dwaPacketData);
[DllImport("AXL.dll")] public static extern uint AxdSetFirmwareUpdate(int nModuleNo, char[] szFileName, uint dwFileNameLen, uint dwPassWord);
[DllImport("AXL.dll")] public static extern uint AxdSetFirmwareUpdate(int nModuleNo, string szFileName, uint dwFileNameLen, uint dwPassWord);


[DllImport("AXL.dll")] public static extern uint AxaSetFirmwareUpdateInfo(int nModuleNo, uint dwTotalDataSize, uint dwTotalPacketSize);
[DllImport("AXL.dll")] public static extern uint AxaSetFirmwareDataTrans(int nModuleNo, uint dwPacketIndex, ref uint dwaPacketData);
[DllImport("AXL.dll")] public static extern uint AxaSetFirmwareUpdate(int nModuleNo, char[] szFileName, uint dwFileNameLen, uint dwPassWord);
[DllImport("AXL.dll")] public static extern uint AxaSetFirmwareUpdate(int nModuleNo, string szFileName, uint dwFileNameLen, uint dwPassWord);


[DllImport("AXL.dll")] public static extern uint AxmSetFirmwareUpdateInfo(int nAxisNo, uint dwTotalDataSize, uint dwTotalPacketSize);
[DllImport("AXL.dll")] public static extern uint AxmSetFirmwareDataTrans(int nAxisNo, uint dwPacketIndex, ref uint dwaPacketData);
[DllImport("AXL.dll")] public static extern uint AxmSetFirmwareUpdate(int nAxisNo, char[] szFileName, uint dwFileNameLen, uint dwPassWord);
[DllImport("AXL.dll")] public static extern uint AxmSetFirmwareUpdate(int nAxisNo, string szFileName, uint dwFileNameLen, uint dwPassWord);
[DllImport("AXL.dll")] public static extern uint AxmSetFoeUploadInfo(int lAxisNo, uint dwTotalDataSize, uint dwTotalPacketSize);
[DllImport("AXL.dll")] public static extern uint AxmGetFoeUploadData(int lAxisNo, uint dwPacketIndex, ref uint dwaPacketData);
[DllImport("AXL.dll")] public static extern uint AxmSetFoeUpload(int lAxisNo, char[] szFileName, uint dwFileNameLen, uint dwPassWord);
[DllImport("AXL.dll")] public static extern uint AxmSetFoeUpload(int lAxisNo, string szFileName, uint dwFileNameLen, uint dwPassWord);


[DllImport("AXL.dll")] public static extern uint AxmMotSetOperationMode(int nAxisNo, uint dwOperationMode);
[DllImport("AXL.dll")] public static extern uint AxmMotGetOperationMode(int nAxisNo, ref uint pdwOperationMode);



[DllImport("AXL.dll")] public static extern uint AxcTriggerSetPatternData(int lChannelNo, int nDataCnt, uint dwOption, double[] dpPatternData);
[DllImport("AXL.dll")] public static extern uint AxcTriggerGetPatternData(int lChannelNo, ref int npDataCnt, ref uint dwpOption, double[] dpPatternData);

[DllImport("AXL.dll")] public static extern uint AxmSpiralMoveEx(int lCoordNo, double dSpiralPitch, double dTurningCount, double dAngleOfPose, uint dwIsInnerDirection, double dVelocity, double dAcceleration, double dDeceleration);
[DllImport("AXL.dll")] public static extern uint AxmFilletMove(int lCoordinate, ref double dPosition, ref double dFirstVector, ref double dSecondVector, double dMaxVelocity, double dMaxAccel, double dMaxDecel, double dRadius);

[DllImport("AXL.dll")] public static extern uint AxmSignalIsServoOnSingleAxis(int lAxisNo, ref uint upOnOff);

[DllImport("AXL.dll")] public static extern uint AxmMotSetTorqueConnection(int lAxisNo, int lSourceAxisNo, uint dwEnable);
[DllImport("AXL.dll")] public static extern uint AxmMotGetTorqueConnection(int lAxisNo, ref int plSourceAxisNo, ref uint pdwEnable);


}
