
unit AXDev;

interface

uses Windows, Messages, AXHS;



// Use Board Number and find Board Address
function AxlGetBoardAddress (lBoardNo : LongInt; upBoardAddress : PDWord) : DWord; stdcall;
// Use Board Number and find Board ID
function AxlGetBoardID (lBoardNo : LongInt; dwpBoardID : PDWord) : DWord; stdcall;
// Use Board Number and find Board Version
function AxlGetBoardVersion (lBoardNo : LongInt; dwpBoardVersion : PDWord) : DWord; stdcall;
// Use Board Number/Module Position and find Module ID
function AxlGetModuleID (lBoardNo : LongInt; lModulePos : LongInt; dwpModuleID : PDWord) : DWord; stdcall;
// Use Board Number/Module Position and find Module Version
function AxlGetModuleVersion (lBoardNo : LongInt; lModulePos : LongInt; dwpModuleVersion : PDWord) : DWord; stdcall;

function AxlGetModuleNodeInfo(lBoardNo : LongInt; lModulePos : LongInt; lpNetNo : PLongInt; dwpNodeAddr : PDWord) : DWord; stdcall;


// Only for PCI-R1604[RTEX]
// Writing user data to embedded flash memory
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
// Note) Delay time is required for completing writing operation to Flash(Max. 17mSec)
function AxlSetDataFlash (lBoardNo : LongInt; lPageAddr : LongInt; lBytesNum : LongInt; bpSetData : PByte) : DWord; stdcall;



// ML3 Only, Use Board and Set the EStopInterLock Parameter
// dwInterLock    : (0) Not use(Default value)
//                  (1) Using function. When E-STOP signal is externally applied after setting function, E-STOP drive command is executed to the motion control node connected to the board.
// dwDigFilterVal : Setting range of input filter constant (1~40). Unit communication Cyclic time
// Set EstopInterLock function by using dwInterLock and dwDigFilterVal on Board
function AxlSetEStopInterLock (lBoardNo : LongInt; dwInterLock : DWord; dwDigFilterVal : DWord) : DWord; stdcall;
// ML3 Only, Use Board and Get the EStopInterLock Parameter
function AxlGetEStopInterLock (lBoardNo : LongInt; dwpInterLock : PDWord; dwpDigFilterVal : PDWord) : DWord; stdcall;
// ML3 Only, Read the External ESTOP Signal status
function AxlReadEStopInterLock (lBoardNo : LongInt; dwpInterLock : PDWord) : DWord; stdcall;


// Reading datas from embedded flash memory
// lPageAddr(0 ~ 199)
// lByteNum(1 ~ 120)
function AxlGetDataFlash (lBoardNo : LongInt; lPageAddr : LongInt; lBytesNum : LongInt; bpSetData : PByte) : DWord; stdcall;


// Use Board Number/Module Position and find AIO Module Number
function AxaInfoGetModuleNo (lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;
// Use Board Number/Module Position and find DIO Module Number
function AxdInfoGetModuleNo (lBoardNo : LongInt; lModulePos : LongInt; lpModuleNo : PLongInt) : DWord; stdcall;


// IPCOMMAND Setting at an appoint axis
function AxmSetCommand (lAxisNo : LongInt; sCommand : Byte) : DWord; stdcall;
// 8bit IPCOMMAND Setting at an appoint axis
function AxmSetCommandData08 (lAxisNo : LongInt; sCommand : Byte; dwData : DWord) : DWord; stdcall;
// Get 8bit IPCOMMAND at an appoint axis
function AxmGetCommandData08 (lAxisNo : LongInt; sCommand : Byte; dwpData : PDWord) : DWord; stdcall;
// 16bit IPCOMMAND Setting at an appoint axis
function AxmSetCommandData16 (lAxisNo : LongInt; sCommand : Byte; dwData : DWord) : DWord; stdcall;
// Get 16bit IPCOMMAND at an appoint axis
function AxmGetCommandData16 (lAxisNo : LongInt; sCommand : Byte; dwpData : PDWord) : DWord; stdcall;
// 24bit IPCOMMAND Setting at an appoint axis
function AxmSetCommandData24 (lAxisNo : LongInt; sCommand : Byte; dwData : DWord) : DWord; stdcall;
// Get 24bit IPCOMMAND at an appoint axis
function AxmGetCommandData24 (lAxisNo : LongInt; sCommand : Byte; dwpData : PDWord) : DWord; stdcall;
// 32bit IPCOMMAND Setting at an appoint axis
function AxmSetCommandData32 (lAxisNo : LongInt; sCommand : Byte; dwData : DWord) : DWord; stdcall;
// Get 32bit IPCOMMAND at an appoint axis
function AxmGetCommandData32 (lAxisNo : LongInt; sCommand : Byte; dwpData : PDWord) : DWord; stdcall;


// QICOMMAND Setting at an appoint axis
function AxmSetCommandQi (lAxisNo : LongInt; sCommand : Byte) : DWord; stdcall;
// 8bit QICOMMAND Setting at an appoint axis
function AxmSetCommandData08Qi (lAxisNo : LongInt; sCommand : Byte; dwData : DWord) : DWord; stdcall;
// Get 8bit QICOMMAND at an appoint axis
function AxmGetCommandData08Qi (lAxisNo : LongInt; sCommand : Byte; dwpData : PDWord) : DWord; stdcall;
// 16bit QICOMMAND Setting at an appoint axis
function AxmSetCommandData16Qi (lAxisNo : LongInt; sCommand : Byte; dwData : DWord) : DWord; stdcall;
// Get 16bit QICOMMAND at an appoint axis
function AxmGetCommandData16Qi (lAxisNo : LongInt; sCommand : Byte; dwpData : PDWord) : DWord; stdcall;
// 24bit QICOMMAND Setting at an appoint axis
function AxmSetCommandData24Qi (lAxisNo : LongInt; sCommand : Byte; dwData : DWord) : DWord; stdcall;
// Get 24bit QICOMMAND at an appoint axis
function AxmGetCommandData24Qi (lAxisNo : LongInt; sCommand : Byte; dwpData : PDWord) : DWord; stdcall;
// 32bit QICOMMAND Setting at an appoint axis
function AxmSetCommandData32Qi (lAxisNo : LongInt; sCommand : Byte; dwData : DWord) : DWord; stdcall;
// Get 32bit QICOMMAND at an appoint axis
function AxmGetCommandData32Qi (lAxisNo : LongInt; sCommand : Byte; dwpData : PDWord) : DWord; stdcall;


// Get Port Data at an appoint axis - IP
function AxmGetPortData(lAxisNo : LongInt; wOffset : WORD; dwpData : PDWord) : DWord; stdcall;
// Port Data Setting at an appoint axis - IP
function AxmSetPortData(lAxisNo : LongInt; wOffset : WORD; dwData : DWord) : DWord; stdcall;

// Get Port Data at an appoint axis - QI
function AxmGetPortDataQi(lAxisNo : LongInt; wOffset : WORD; dwpData : PDWord) : DWord; stdcall;
// Port Data Setting at an appoint axis - QI
function AxmSetPortDataQi(lAxisNo : LongInt; wOffset : WORD; dwData : DWord) : DWord; stdcall;


// Set the script at an appoint axis.  - IP
// sc    : Script number (1 - 4)
// event : Define an event SCRCON to happen.
//         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
// cmd   : Define a selection SCRCMD however we change any content
// data  : Selection to change any Data.
function AxmSetScriptCaptionIp(lAxisNo : LongInt; lScriptNo : LongInt; dwEvent : DWord; dwData : DWord) : DWord; stdcall;
// Return the script at an appoint axis.  - IP
function AxmGetScriptCaptionIp(lAxisNo : LongInt; lScriptNo : LongInt; dwEvent : PDWord; dwpData : PDWord) : DWord; stdcall;

// Set the script at an appoint axis.  - QI
// sc    : Script number (1 - 4)
// event : Define an event SCRCON to happen.
//         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
// cmd   : Define a selection SCRCMD however we change any content
// data  : Selection to change any Data.
function AxmSetScriptCaptionQi(lAxisNo : LongInt; lScriptNo : LongInt; dwEvent : DWord; dwCmd : DWord; dwData : DWord) : DWord; stdcall;
// Return the script at an appoint axis. - QI
function AxmGetScriptCaptionQi(lAxisNo : LongInt; lScriptNo : LongInt; dwpEvent : PDWord; dwpCmd : PDWord; dwpData : PDWord) : DWord; stdcall;

// Clear orders a script inside Queue Index at an appoint axis
// uSelect IP.
// uSelect(0): Script Queue Index Clear.
//        (1): Caption Queue Index Clear.
// uSelect QI.
// uSelect(0): Script Queue 1 Index Clear.
//        (1): Script Queue 2 Index Clear.
function AxmSetScriptCaptionQueueClear(lAxisNo : LongInt; dwSelect : DWord) : DWord; stdcall;

// Return Index of a script inside Queue at an appoint axis.
// dwSelect IP
// dwSelect(0): Read Script Queue Index
//        (1): Read Caption Queue Index
// dwSelect QI.
// dwSelect(0): Read Script Queue 1 Index
//        (1): Read Script Queue 2 Index
function AxmGetScriptCaptionQueueCount(lAxisNo : LongInt; dwpData : PDWord; dwSelect : DWord) : DWord; stdcall;

// Return Data number of a script inside Queue at an appoint axis.
// dwSelect IP
// dwSelect(0): Read Script Queue Data
//        (1): Read Caption Queue Data
// dwSelect QI.
// dwSelect(0): Read Script Queue 1 Data
//        (1): Read Script Queue 2 Data
function AxmGetScriptCaptionQueueDataCount(lAxisNo : LongInt; dwpData : PDWord; dwSelect : DWord) : DWord; stdcall;

// Read an inside data.
function AxmGetOptimizeDriveData(lAxisNo : LongInt; dMinVel : Double; dVel : Double; dAccel : Double; dDecel : Double;


// Setting up confirmes the register besides within the board by Byte.
function AxmBoardWriteByte(lBoardNo : LongInt; wOffset : Word; byData : Byte) : DWord; stdcall;
function AxmBoardReadByte(lBoardNo : LongInt; wOffset : Word; bypData : PByte) : DWord; stdcall;

// Setting up confirmes the register besides within the board by Word.
function AxmBoardWriteWord(lBoardNo : LongInt; wOffset : Word; wData : Word) : DWord; stdcall;
function AxmBoardReadWord(lBoardNo : LongInt; wOffset : Word; wpData : PWord) : DWord; stdcall;

// Setting up confirmes the register besides within the board by DWord.
function AxmBoardWriteDWord(lBoardNo : LongInt; wOffset : Word; dwData : DWord) : DWord; stdcall;
function AxmBoardReadDWord(lBoardNo : LongInt; wOffset : Word; dwpData : PDWord) : DWord; stdcall;

// Setting up confirmes the register besides within the Module by Byte.
function AxmModuleWriteByte(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; byData : Byte) : DWord; stdcall;
function AxmModuleReadByte(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; bypData : PByte) : DWord; stdcall;

// Setting up confirmes the register besides within the Module by Word.
function AxmModuleWriteWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; wData : Word) : DWord; stdcall;
function AxmModuleReadWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; wpData : PWord) : DWord; stdcall;

// Setting up confirmes the register besides within the Module by DWord.
function AxmModuleWriteDWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; dwData : DWord) : DWord; stdcall;
function AxmModuleReadDWord(lBoardNo : LongInt; lModulePos : LongInt; wOffset : Word; dwpData : PDWord) : DWord; stdcall;

// Set EXCNT (Pos = Unit)
function AxmStatusSetActComparatorPos(lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// Return EXCNT (Positon = Unit)
function AxmStatusGetActComparatorPos(lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;

// Set INCNT (Pos = Unit)
function AxmStatusSetCmdComparatorPos(lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// Return INCNT (Pos = Unit)
function AxmStatusGetCmdComparatorPos(lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;

//=========== Append function. =================================================
// Increase a straight line interpolation at speed to the infinity.
// Must put the distance speed rate.
function AxmLineMoveVel(lCoord : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

//========= Sensor drive API( Read carefully: Available only PI , No function in QI)
// Set mark signal( used in sensor positioning drive)
function AxmSensorSetSignal(lAxisNo : LongInt; dwLevel : DWord) : DWord; stdcall;
// Verify mark signal( used in sensor positioning drive)
function AxmSensorGetSignal(lAxisNo : LongInt; dwpLevel : PDWord) : DWord; stdcall;
// Verify mark signal( used in sensor positioning drive)state
function AxmSensorReadSignal(lAxisNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;

// Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop. Applied motion is started upon the start of API, and escapes from the API after the motion is completed.
function AxmSensorMovePos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lMethod : LongInt) : DWord; stdcall;

// Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop. Applied motion is started upon the start of API, then escapes from the API immediately without waiting until the motion is completed.
function AxmSensorStartMovePos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lMethod : LongInt) : DWord; stdcall;


// Return record of origin search progress step.
// *lpStepCount      : Number of step(Be recorded)
// *upMainStepNumber : Array point of 'MainStepNumber ' information(Be recorded)
// *upStepNumber     : Array point of 'StepNumber ' information(Be recorded)
// *upStepBranch     : Array point of branch information by step(Be recorded)
// ¡Ø Caution : Number of array should be fixed 50.
function AxmHomeGetStepTrace(lAxisNo : LongInt; lpStepCount : PLongInt; dwpMainStepNumber : PDWord; dwpStepNumber : PDWord; dwpStepBranch : PDWord) : DWord; stdcall;


//======= Additive home search (Applicable to PI-N804/404  only) ===============

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
function AxmHomeSetConfig(lAxisNo : LongInt; dwZphasCount : DWord; lHomeMode : LongInt; lClearSet : LongInt; dOrgVel : Double; dLastVel : Double; dLeavePos : Double) : DWord; stdcall;
// Return home setting parameters of axis specified by user.
function AxmHomeGetConfig(lAxisNo : LongInt; dwpZphasCount : PDword; lpHomeMode : PLongInt; lpClearSet : PLongInt; dpOrgVel : PDouble; dpLastVel : PDouble; dpLeavePos : PDouble) : DWord; stdcall;

// Start home search of axis specified by user
// Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
// If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
// Move direction      : CW when Vel value is positive, CCW when negative.
function AxmHomeSetMoveSearch(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// Start home return of axis specified by user.
// Set when lHomeMode is used: set 0 - 12
// If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
// Move direction      : CW when Vel value is positive, CCW when negative.
function AxmHomeSetMoveReturn(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// Home separation of axis specified by user is started.
// Move direction      : CW when Vel value is positive, CCW when negative.
function AxmHomeSetMoveLeave(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

// User start home search of multi-axis specified by user.
// Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
// If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
// Move direction      : CW when Vel value is positive, CCW when negative.
function AxmHomeSetMultiMoveSearch(lArraySize : LongInt; lpAxesNo : PLongInt; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble) : DWord; stdcall;

//Set move velocity profile mode of specific coordinate system.
// (caution : Available to use only after axis mapping)
//ProfileMode : '0' - symmetry Trapezoid
//              '1' - asymmetric Trapezoid
//              '2' - symmetry Quasi-S Curve
//              '3' - symmetry S Curve
//              '4' - asymmetric S Curve
function AxmContiSetProfileMode(lCoord : LongInt; dwProfileMode : DWord) : DWord; stdcall;
// Return move velocity profile mode of specific coordinate system.
function AxmContiGetProfileMode(lCoord : LongInt; dwpProfileMode : PDWord) : DWord; stdcall;


//========== Reading group for input interrupt occurrence flag =================
// Reading the interrupt occurrence state by bit unit in specified input contact module and Offset position of Interrupt Flag Register
function AxdiInterruptFlagReadBit(lModuleNo : LongInt; lOffset : LongInt; dwpValue : PDWord) : DWord; stdcall;
// Reading the interrupt occurrence state by byte unit in specified input contact module and Offset position of Interrupt Flag Register
function AxdiInterruptFlagReadByte(lModuleNo : LongInt; lOffset : LongInt; dwpValue : PDWord) : DWord; stdcall;
// Reading the interrupt occurrence state by word unit in specified input contact module and Offset position of Interrupt Flag Register
function AxdiInterruptFlagReadWord(lModuleNo : LongInt; lOffset : LongInt; dwpValue : PDWord) : DWord; stdcall;
// Reading the interrupt occurrence state by double word unit in specified input contact module and Offset position of Interrupt Flag Register
function AxdiInterruptFlagReadDword(lModuleNo : LongInt; lOffset : LongInt; dwpValue : PDWord) : DWord; stdcall;
// Reading the interrupt occurrence state by bit unit in entire input contact module and Offset position of Interrupt Flag Register
function AxdiInterruptFlagRead(lOffset : LongInt; dwpValue : PDWord) : DWord; stdcall;

//========= API related log ====================================================
// This API sets or resets in order to monitor the API execution result of set axis in EzSpy.
// uUse : use or not use => DISABLE(0), ENABLE(1)
function AxmLogSetAxis(lAxisNo : LongInt; dwUse : DWord) : DWord; stdcall;

// This API verifies if the API execution result of set axis is monitored in EzSpy.
function AxmLogGetAxis(lAxisNo : LongInt; dwpUse : PDWord) : DWord; stdcall;

//==Log
//Set whether to log output to EzSpy of specified input channel
function AxaiLogSetChannel(lChannelNo : LongInt; dwUse : DWord) : DWord; stdcall;
//Verify whether to log output to EzSpy of specified input channel
function AxaiLogGetChannel(lChannelNo : LongInt; dwpUse : PDWord) : DWord; stdcall;

//Set whether to log output in EzSpy of specified output channel
function AxaoLogSetChannel(lChannelNo : LongInt; dwUse : DWord) : DWord; stdcall;
//Verify whether log output is done in EzSpy of specified output channel.
function AxaoLogGetChannel(lChannelNo : LongInt; dwpUse : PDWord) : DWord; stdcall;

// Set whether execute log output on EzSpy of specified module
function AxdLogSetModule(lModuleNo : LongInt; dwUse : DWord) : DWord; stdcall;
// Verify whether execute log output on EzSpy of specified module
function AxdLogGetModule(lModuleNo : LongInt; dwpUse : PDWord) : DWord; stdcall;




//Verify whether to firmware version designated RTEX board.
function AxlGetFirmwareVersion(lBoardNo : LongInt; szVersion : PChar) : DWord; stdcall;
//Sent to firmware designated board.
function AxlSetFirmwareCopy(lBoardNo : LongInt; wpData : PWord; wpCmdData : PWord) : DWord; stdcall;
//Execute Firmware update to designated board.
function AxlSetFirmwareUpdate(lBoardNo : LongInt) : DWord; stdcall;
//Verify whether currently RTEX status Initialized.
function AxlCheckStatus(lBoardNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
//Execute universal command designated axis of board.
function AxlRtexUniversalCmd(lBoardNo : LongInt; wCmd : Word; wOffset : Word; wpData : PWord) : DWord; stdcall;
//Execute RTEX communication command designated axis.
function AxmRtexSlaveCmd(lAxisNo : LongInt; dwCmdCode : DWord; dwTypeCode : DWord; dwIndexCode : DWord; dwCmdConfigure : DWord; dwValue : DWord) : DWord; stdcall;
//Verify whether Result of RTEX communication command designated axis.
function AxmRtexGetSlaveCmdResult(lAxisNo : LongInt; dwpIndex : PDWord; dwpValue : PDWord) : DWord; stdcall;
// Check the result of the RTEX communication command executed on the specified axis. PCIE-Rxx04-RTEX only
function AxmRtexGetSlaveCmdResultEx(lAxisNo : LongInt; dwpCommand : PDWord; dwpType : PDWord; dwpIndex : PDWord; dwpValue : PDWord) : DWord; stdcall;
//Verify whether RTEX status information designated axis.
function AxmRtexGetAxisStatus(lAxisNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
//Verify whether RTEX communication return information designated axis.(Actual position, Velocity, Torque)
function AxmRtexGetAxisReturnData(lAxisNo : LongInt;  dwpReturn1 : PDWord; dwpReturn2 : PDWord; dwpReturn3 : PDWord) : DWord; stdcall;
//Verify whether currently status information of RTEX slave axis.(mechanical, Inposition and etc)
function AxmRtexGetAxisSlaveStatus(lAxisNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;


// Enter the universal network command of specified MLII slave axis.
function AxmSetAxisCmd(lAxisNo : LongInt; dwpTagCommand : PDWord) : DWord; stdcall;
// Verifying result of universal network command of specified MLII slave axis.
function AxmGetAxisCmdResult(lAxisNo : LongInt; dwpTagCommand : PDWORD) : DWord; stdcall;


// The specified SID Write the result of the network command to the slave module and return it.
function AxdSetAndGetSlaveCmdResult(lModuleNo : LongInt; dwptagSetCommand : PDWord; dwptagGetCommand : PDWord) : DWord; stdcall;
function AxaSetAndGetSlaveCmdResult(lModuleNo : LongInt; dwptagSetCommand : PDWord; dwptagGetCommand : PDWord) : DWord; stdcall;
function AxcSetAndGetSlaveCmdResult(lModuleNo : LongInt; dwptagSetCommand : PDWord; dwptagGetCommand : PDWord) : DWord; stdcall;

// Verify DPRAM data.
function AxlGetDpRamData(lBoardNo : LongInt; wAddress : Word; dwpRdData : PDWord) : DWord; stdcall;
// Verify DPRAM data in Word unit.
function AxlBoardReadDpramWord(lBoardNo : LongInt; wOffset : Word; dwpRdData : PDWord) : DWord; stdcall;
// Set DPRAM data in Word unit.
function AxlBoardWriteDpramWord(lBoardNo : LongInt; wOffset : Word; dwWrData : DWord) : DWord; stdcall;


// Transmit instructions of each slave of each board.
function AxlSetSendBoardEachCommand(lBoardNo : LongInt; dwCommand : DWord; dwpSendData : PDWord; dwLength : DWord) : DWord; stdcall;
// Transmit instructions to each board.
function AxlSetSendBoardCommand(lBoardNo : LongInt; dwCommand : DWord; dwpSendData : PDWord; dwLength : DWord) : DWord; stdcall;
// Verify the response of each board.
function AxlGetResponseBoardCommand(lBoardNo : LongInt; dwpReadData : PDWord) : DWord; stdcall;

// Reading firmware version function of slaves in network type master board.
// Declare with array of ucaFirmwareVersion unsigned char type(Size : 4 or more)
function AxmInfoGetFirmwareVersion(lAxisNo : LongInt;  dwcaFirmwareVersion : PWord) : DWord; stdcall;
function AxaInfoGetFirmwareVersion(lModuleNo : LongInt; dwcaFirmwareVersion : PWord) : DWord; stdcall;
function AxdInfoGetFirmwareVersion(lModuleN : LongInt; dwcaFirmwareVersion : PWord) : DWord; stdcall;
function AxcInfoGetFirmwareVersion(lModuleN : LongInt; dwcaFirmwareVersion : PWord) : DWord; stdcall;


//======== Only for PCI-R1604-MLII ===========================================================================
// Set the value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
// Default value : Max
// Setting value Range : 0 ~ 4000H
// If it is set to 4000H or higher, the setting is set higher than that, but the operation is applied to the value of 4000H.
function AxmSetTorqFeedForward(lAxisNo : LongInt; dwTorqFeedForward : DWord) : DWord; stdcall;

// It is API that read value of Torq Feed Forward of Option Field of INTERPOLATE and LATCH Command.
// Default value : Max
function AxmGetTorqFeedForward(lAxisNo : LongInt; dwpTorqFeedForward : PDWord) : DWord; stdcall;

// It is API that set the value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
// Default value : 0
// Setting value Range : 0 ~ FFFFH
function AxmSetVelocityFeedForward(lAxisNo : LongInt; dwVelocityFeedForward : DWord) : DWord; stdcall;

// It is API that read value of Velocity Feed Forward of VFF Field of INTERPOLATE and LATCH Command.
function AxmGetVelocityFeedForward(lAxisNo : LongInt; dwpVelocityFeedForward : PDWord) : DWord; stdcall;


// Set Encoder type.
// Default value : 0(TYPE_INCREMENTAL)
// Setting range : 0 ~ 1
// dwEncoderType : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
function AxmSignalSetEncoderType(lAxisNo : LongInt; dwEncoderType : DWord) : DWord; stdcall;


// Verify Encoder type.
function AxmSignalGetEncoderType(lAxisNo : LongInt; dwpEncoderType : PDWord) : DWord; stdcall;



// For updating the slave firmware(only for RTEX-PM).
//function AxmSetSendAxisCommand(lAxisNo : LongInt; wCommand : Word; wpSendData : PDWord; wLength : Word) : DWord; stdcall;

//======== Only for PCI-R1604-RTEX, RTEX-PM==============================================================
// When Input Universal Input 2, 3, Set Jog move velocity
// Set only once execute after all drive setting (Ex, PulseOutMethod, MoveUnitPerPulse etc..)
function AxmMotSetUserMotion(lAxisNo : LongInt; dVelocity : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;


// When Input Universal Input 2, 3, Set Jog move usage
// Setting value :  0(DISABLE), 1(ENABLE)
function AxmMotSetUserMotionUsage(lAxisNo: LongInt; dwUsage : DWord) : DWord; stdcall;


// Set Load/UnLoad Position to Automatically move use MPGP Input
function  AxmMotSetUserPosMotion(lAxisNo : LongInt; dVelocity : Double; dAccel : Double; dDecel : Double; dLoadPos : Double; dUnLoadPos : Double; dwFilter : DWord; dwDelay : DWord) : DWord; stdcall;


// Set Usage Load/UnLoad Position to Automatically move use MPGP Input
// Setting value :  0(DISABLE), 1(Position function A), 2(Position function B)
function  AxmMotSetUserPosMotionUsage(lAxisNo : LongInt; dwUsage : DWord) : DWord; stdcall;

//========================================================================================================

//======== SIO-CN2CH, Only for absolute position trigger module(B0) ================================================
// The API of writing memory data.
function AxcKeWriteRamDataAddr(lChannelNo : LongInt; dwAddr : DWord; dwData : DWord) : DWord; stdcall;
// The API of reading memory data.
function AxcKeReadRamDataAddr(lChannelNo : LongInt; dwAddr : DWord; dwpData : PDWord) : DWord; stdcall;
// Memory initialization API.
function AxcKeResetRamDataAll(lModuleNo : LongInt; dwData : DWord) : DWord; stdcall;
// Trigger timeout setting API.
function AxcTriggerSetTimeout(lChannelNo : LongInt; dwTimeout : DWord) : DWord; stdcall;
// Trigger timeout checking API.
function AxcTriggerGetTimeout(lChannelNo : LongInt; dwpTimeout : PDWord) : DWord; stdcall;
// Trigger Waiting State checking API.
function AxcStatusGetWaitState(lChannelNo : LongInt; dwpState : PDWord) : DWord; stdcall;
// Trigger Waiting State setting API.
function AxcStatusSetWaitState(lChannelNo : LongInt; dwState : DWord) : DWord; stdcall;

// Write command to designated channel.
function AxcKeSetCommandData32(lChannelNo : LongInt; dwCommand : DWord ; dwData : DWord) : DWord; stdcall;
// Write command to designated channel.
function AxcKeSetCommandData16(lChannelNo : LongInt; dwCommand : DWord ; wData : Word) : DWord; stdcall;
// Verify register of specified channel.
function AxcKeGetCommandData32(lChannelNo : LongInt; dwCommand : DWord ; dwpData : PDWord) : DWord; stdcall;
// Verify register of specified channel.
function AxcKeGetCommandData16(lChannelNo : LongInt; dwCommand : DWord ; wpData : PWord) : DWord; stdcall;

//========================================================================================================

//======== Only for PCI-N804/N404, Sequence Motion ===========================================================
// Set Axis Information of sequence Motion (min 1axis)
// lSeqMapNo : Sequence Motion Index Point
// lSeqMapSize : Number of axis
// long* LSeqAxesNo : Number of arrary
function AxmSeqSetAxisMap(lSeqMapNo : LongInt; lSeqMapSize : LongInt; lpSeqAxesNo : PLongInt) : DWord; stdcall;
function AxmSeqGetAxisMap(lSeqMapNo : LongInt; lSeqMapSize : PLongInt; lpSeqAxesNo : PLongInt) : DWord; stdcall;


// Set Standard(Master)Axis of Sequence Motion.
// By all means Set in AxmSeqSetAxisMap setting axis.
function AxmSeqSetMasterAxisNo(lSeqMapNo : LongInt; lMasterAxisNo : LongInt) : DWord; stdcall;


// Notifies the library node start loading of Sequence Motion.
function AxmSeqBeginNode(lSeqMapNo : LongInt) : DWord; stdcall;


// Notifies the library node end loading of Sequence Motion.
function AxmSeqEndNode(lSeqMapNo : LongInt) : DWord; stdcall;


// Start Sequence Motion Move.
function AxmSeqStart(lSeqMapNo : LongInt; dwStartOption : DWord) : DWord; stdcall;


// Set each profile node Information of Sequence Motion in Library.
// if used 1axis Sequence Motion, Must be Set *dPosition one Array.
function AxmSeqAddNode(lSeqMapNo : LongInt; dpPosition : PDouble; dVelocity : Double; dAcceleration : Double; dDeceleration : Double; dNextVelocity : Double) : DWord; stdcall;


// Return Node Index number of Sequence Motion.
function AxmSeqGetNodeNum(lSeqMapNo : LongInt; lpCurNodeNo : PLongInt) : DWord; stdcall;


// Return All node count of Sequence Motion.
function AxmSeqGetTotalNodeNum(lSeqMapNo : LongInt; lpTotalNodeCnt : PLongInt) : DWord; stdcall;


// Return Sequence Motion drive status  of specific SeqMap.
// dwInMotion : 0(Drive end), 1(In drive)
function AxmSeqIsMotion(lSeqMapNo : LongInt; dwpInMotion : PDWord) : DWord; stdcall;


// Clear Sequence Motion Memory.
function AxmSeqWriteClear(lSeqMapNo : LongInt) : DWord; stdcall;


// Stop sequence motion
// dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
function AxmSeqStop(lSeqMapNo : LongInt; dwStopMode : DWord) : DWord; stdcall;


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
function AxmStatusSetMon(lAxisNo : LongInt; dwParaNo1 : DWord; dwParaNo2 : DWord; dwParaNo3 : DWord; dwParaNo4 : DWord; dwUse : DWord) : DWord; stdcall;
function AxmStatusGetMon(lAxisNo : LongInt; dwpParaNo1 : PDWord; dwpParaNo2 : PDWord; dwpParaNo3 : PDWord; dwpParaNo4 : PDWord; dwpUse : PDWord) : DWord; stdcall;
function AxmStatusReadMon(lAxisNo : LongInt; dwpParaNo1 : PDWord; dwpParaNo2 : PDWord; dwpParaNo3 : PDWord; dwpParaNo4 : PDWord; dwpDataValid : PDWord) : DWord; stdcall;
function AxmStatusReadMonEx(lAxisNo : LongInt; lpDataCnt : PLongInt; dwpReadData : PDWord) : DWord; stdcall;

//=============================================================================================================

//======== Only for PCI-R32IOEV-RTEX ===========================================================================
// The API for read or write HPI register which allocated as I/O port.
// I/O Registers for HOST interface.
// I/O 00h Host status register (HSR)
// I/O 04h Host-to-DSP control register (HDCR)
// I/O 08h DSP page register (DSPP)
// I/O 0Ch Reserved
function AxlSetIoPort(lBoardNo : LongInt; dwAddr : DWord; dwData : DWord) : DWord; stdcall;
function AxlGetIoPort(lBoardNo : LongInt; dwAddr : DWord; dwpData : PDWord) : DWord; stdcall;

//======== Only for PCI-R3200-MLIII ===========================================================================
// Basic information setting API for firmware update of M-III Master board.
function AxlM3SetFWUpdateInit(lBoardNo : LongInt; dwTotalPacketSize : DWord; dwProcTotalStepNo : DWord) : DWord; stdcall;
// Verify setting value of 'AxlM3SetFWUpdateInit'.
function AxlM3GetFWUpdateInit(lBoardNo : LongInt; dwpTotalPacketSize : PDWord; dwpProcTotalStepNo : PDWord) : DWord; stdcall;


// M-III Master board firmware update data transfer API.
function AxlM3SetFWUpdateCopy(lBoardNo : LongInt; dwpPacketData : PDWord; dwPacketSize : DWord) : DWord; stdcall;
// Verify setting value of 'AxlM3SetFWUpdateCopy'.
function AxlM3GetFWUpdateCopy(lBoardNo : LongInt; dwpPacketSize : PDWord) : DWord; stdcall;


// Execute firmware update of M-III Master Board.
function AxlM3SetFWUpdate(lBoardNo : LongInt; dwFlashBurnStepNo : DWord) : DWord; stdcall;
// Verifying result of execute firmware update of M-III Master Board.
function AxlM3GetFWUpdate(lBoardNo : LongInt; dwpFlashBurnStepNo : PDWord; dwpIsFlashBurnDone : PDWord) : DWord; stdcall;

// The API for setting EEPROM data of M-III Master board.
function AxlM3SetCFGData(lBoardNo : LongInt; dwpCmdData : PDWord; dwCmdDataSize : DWord) : DWord; stdcall;
// The API for getting data from EEPROM of M-III Master board.
function AxlM3GetCFGData(lBoardNo : LongInt; dwpCmdData : PDWord; dwCmdDataSize : DWord) : DWord; stdcall;

// The API for setting CONNECT PARAMETER information of M-III Master board.
function AxlM3SetMCParaUpdateInit(lBoardNo : LongInt; wCh0Slaves : Word; wCh1Slaves : Word; dwCh0CycTime : DWord; dwCh1CycTime : DWord; dwChInfoMaxRetry : DWord) : DWord; stdcall;
// The API for verifying CONNECT PARAMETER information of M-III Master board.
function AxlM3GetMCParaUpdateInit(lBoardNo : LongInt; wpCh0Slaves : PWord; wpCh1Slaves : PWord; dwpCh0CycTime : PDWord; dwpCh1CycTime : PDWord; dwpChInfoMaxRetry : PDWord) : DWord; stdcall;
// The API for transmit CONNECT PARAMETER information of M-III Master board.
function AxlM3SetMCParaUpdateCopy(lBoardNo : LongInt; wIdx : Word; wChannel : Word; wSlaveAddr : Word; dwProtoCalType : DWord; dwTransBytes : DWord; dwDeviceCode : DWord) : DWord; stdcall;
// The API for verifying transmit CONNECT PARAMETER information of M-III Master board.
function AxlM3GetMCParaUpdateCopy(lBoardNo : LongInt; wIdx : Word; wpChannel : PWord; wpSlaveAddr : PWord; dwpProtoCalType : PDWord; dwpTransBytes : PDWord; dwpDeviceCode : PDWord) : DWord; stdcall;

// The API for checking register as DWord unit within M-III Master board.
function AxlBoardReadDWord(lBoardNo : LongInt; wOffset : Word; dwpData : PDWord) : DWord; stdcall;
// The API for setting register as DWord unit within M-III Master board.
function AxlBoardWriteDWord(lBoardNo : LongInt; wOffset : Word; dwData : DWord) : DWord; stdcall;

// Setting and verifying extension register as DWord unit within board.
function AxlBoardReadDWordEx(lBoardNo : LongInt; dwOffset : DWord; dwpData : PDWord) : DWord; stdcall;
function AxlBoardWriteDWordEx(lBoardNo : LongInt; dwOffset : DWord; dwData : DWord) : DWord; stdcall;

// The API for setting servo to stop mode.
function AxmM3ServoSetCtrlStopMode(lAxisNo : LongInt; byStopMode : Byte) : DWord; stdcall;
// The API for setting servo to Lt selection state.
function AxmM3ServoSetCtrlLtSel(lAxisNo : LongInt; byLtSel1 : Byte; byLtSel2 : Byte) : DWord; stdcall;
// The API for verifying servo I/O input state.
function AxmStatusReadServoCmdIOInput(lAxisNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
// Servo interpolation drive API.
function AxmM3ServoExInterpolate(lAxisNo : LongInt; dwTPOS : DWord; dwVFF : DWord; dwTLIM : DWord; dwExSig1 : DWord; dwExSig2 : DWord) : DWord; stdcall;
// The API for setting bias of the servo actuator.
function AxmM3ServoSetExpoAccBias(lAxisNo : LongInt; wBias : Word) : DWord; stdcall;
// The API for setting time of the servo actuator.
function AxmM3ServoSetExpoAccTime(lAxisNo : LongInt; wTime : Word) : DWord; stdcall;
// The API for setting time of the servo move.
function AxmM3ServoSetMoveAvrTime(lAxisNo : LongInt; wTime : Word) : DWord; stdcall;
// The API for setting acc filter of the servo.
function AxmM3ServoSetAccFilter(lAxisNo : LongInt; byAccFil : Byte) : DWord; stdcall;
// The API for setting status monitor1 of the servo.
function AxmM3ServoSetCprmMonitor1(lAxisNo : LongInt; byMonSel : Byte) : DWord; stdcall;
// The API for setting status monitor2 of the servo.
function AxmM3ServoSetCprmMonitor2(lAxisNo : LongInt; byMonSel : Byte) : DWord; stdcall;
// The API for verifying status monitor1 of the servo.
function AxmM3ServoStatusReadCprmMonitor1(lAxisNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
// The API for verifying status monitor2 of the servo.
function AxmM3ServoStatusReadCprmMonitor2(lAxisNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
// The API for setting Dec of servo actuator.
function AxmM3ServoSetAccDec(lAxisNo : LongInt; wAcc1 : Word; wAcc2 : Word; wAccSW : Word; wDec1 : Word; wDec2 : Word; wDecSW : Word) : DWord; stdcall;
// The API for servo stop.
function AxmM3ServoSetStop(lAxisNo : LongInt; lMaxDecel : LongInt) : DWord; stdcall;

//========== Common commands of standard I/O dvices =========================================================================
// The API for return parameter setting value of each slave device.
function AxlM3GetStationParameter(lBoardNo : LongInt; lModuleNo : LongInt; wNo : Word; bySize : Byte; byModuleType : Byte; bypParam : PByte) : DWord; stdcall;
// The API for setting parameter value of each slave device.
function AxlM3SetStationParameter(lBoardNo : LongInt; lModuleNo : LongInt; wNo : Word; bySize : Byte; byModuleType : Byte; bypParam : PByte) : DWord; stdcall;
// The API for return ID value of each slave device.
function AxlM3GetStationIdRd(lBoardNo : LongInt; lModuleNo : LongInt; byIdCode : Byte; byOffset : Byte; bySize : Byte; bModuleType : Byte; bypParam : PByte) : DWord; stdcall;
// The API used as invalid command of each slave device.
function AxlM3SetStationNop(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte) : DWord; stdcall;
// The API for set up each slave device.
function AxlM3SetStationConfig(lBoardNo : LongInt; lModuleNo : LongInt; byConfigMode : Byte; byModuleType : Byte) : DWord; stdcall;
// The API for return alarm and warning status value of each slave device.
function AxlM3GetStationAlarm(lBoardNo : LongInt; lModuleNo : LongInt; wAlarmRdMod : Word; wAlarmIndex : Word; byModuleType : Byte; wpAlarmData : PWord) : DWord; stdcall;
// The API for clearing alarm and warning status value of each slave device.
function AxlM3SetStationAlarmClear(lBoardNo : LongInt; lModuleNo : LongInt; wAlarmClrMod : Word; byModuleType : Byte) : DWord; stdcall;
// The API for setting establish synchronous communication with each slave device.
function AxlM3SetStationSyncSet(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte) : DWord; stdcall;
// The API for setting connection with each slave device.
function AxlM3SetStationConnect(lBoardNo : LongInt; lModuleNo : LongInt; byVer : Byte; byComMode : Byte; byComTime : Byte; byProfileType : Byte; byModuleType : Byte) : DWord; stdcall;
// The API for setting disconnection with each slave device.
function AxlM3SetStationDisConnect(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte) : DWord; stdcall;
// The API for return of non-volatile parameter setting value.
function AxlM3GetStationStoredParameter(lBoardNo : LongInt; lModuleNo : LongInt; wNo : Word; bySize : Byte; byModuleType : Byte; bypParam : PByte) : DWord; stdcall;
// The API for setting non-volatile parameter value of each slave device.
function AxlM3SetStationStoredParameter(lBoardNo : LongInt; lModuleNo : LongInt; wNo : Word; bySize : Byte; byModuleType : Byte; bypParam : PByte) : DWord; stdcall;
// The API for return of memory setting value of each slave device.
function AxlM3GetStationMemory(lBoardNo : LongInt; lModuleNo : LongInt; wSize : Word; dwAddress : DWord; byModuleType : Byte; byMode : Byte; byDataType : Byte; bypData : PByte) : DWord; stdcall;
// The API for setting memory value of each slave device.
function AxlM3SetStationMemory(lBoardNo : LongInt; lModuleNo : LongInt; wSize : Word; dwAddress : DWord; byModuleType : Byte; byMode : Byte; byDataType : Byte; bypData : PByte) : DWord; stdcall;

//========== Connection commands of standard I/O dvices =========================================================================
// The API for setting value of automatic access mode of each re-ordered slave device.
function AxlM3SetStationAccessMode(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte; byRWSMode : Byte) : DWord; stdcall;
// The API for return of automatic access mode setting value of each re-ordered slave device.
function AxlM3GetStationAccessMode(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte; bypRWSMode : PByte) : DWord; stdcall;
// The API for set synchronous auto connect mode of each slave device.
function AxlM3SetAutoSyncConnectMode(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte; dwAutoSyncConnectMode : DWord) : DWord; stdcall;
// The API for return of synchronous auto connect mode setting value of each slave device.
function AxlM3GetAutoSyncConnectMode(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte; dwpAutoSyncConnectMode : PDWord) : DWord; stdcall;
// The API for establish a single synchronization connection to each slave device.
function AxlM3SyncConnectSingle(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte) : DWord; stdcall;
// The API for establish a single synchronization disconnection to each slave device.
function AxlM3SyncDisconnectSingle(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte) : DWord; stdcall;
// The API for verifying connection status with slave device.
function AxlM3IsOnLine(lBoardNo : LongInt; lModuleNo : LongInt; dwpData : PDWord) : DWord; stdcall;

//========== Profile commands of standard I/O =========================================================================
// The API for return of data setting value for each synchronous I/O slave device.
function AxlM3GetStationRWS(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte; dwpParam : PDWord; bySize : Byte) : DWord; stdcall;
// The API for setting data value for each synchronous I/O slave device.
function AxlM3SetStationRWS(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte; dwpParam : PDWord; bySize : Byte) : DWord; stdcall;
// The API for return of data setting value for each asynchronous I/O slave device.
function AxlM3GetStationRWA(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte; dwpParam : PDWord; bySize : Byte) : DWord; stdcall;
// The API for setting data value for each asynchronous I/O slave device.
function AxlM3SetStationRWA(lBoardNo : LongInt; lModuleNo : LongInt; byModuleType : Byte; dwpParam : PDWord; bySize : Byte) : DWord; stdcall;

// Set the MLIII adjustment operation
// dwReqCode == 0x1005 : parameter initialization : 20sec
// dwReqCode == 0x1008 : absolute encoder reset   : 5sec
// dwReqCode == 0x100E : automatic offset adjustment of motor current detection signals  : 5sec
// dwReqCode == 0x1013 : Multiturn limit setting  : 5sec
function AxmM3AdjustmentOperation(lAxisNo : LongInt; dwReqCode : DWord) : DWord; stdcall;

// API for diagnosing home search progress.(Only for M3)
function AxmHomeGetM3FWRealRate(lAxisNo : LongInt; dwpHomeMainStepNumber : PDWord; dwpHomeSubStepNumber : PDWord; dwpHomeLastMainStepNumber : PDWord; dwpHomeLastSubStepNumber : PDWord) : DWord; stdcall;
// Return adjusted position value when escaping sensor zone from origin search.(Only for M3)
function AxmHomeGetM3OffsetAvoideSenArea(lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;
// The API for Setting adjusted position value when escaping sensor zone from origin search.(Only for M3)
// If dPos setting value is '0', adjusted position value will be set automatically when automatically escaping.
// 'dPos' should be a positive number.
function AxmHomeSetM3OffsetAvoideSenArea(lAxisNo : LongInt; dPos : Double) : DWord; stdcall;


// Setting usage criterion of absolute encoder. Set whether to CMD/ACT POS initialize after origin search.(Only for M3)
// dwSel: 0, CMD/ACTPOS will be set '0' after origin search.(Default)
// dwSel: 1, CMD/ACTPOS will be not set after origin search.
function AxmM3SetAbsEncOrgResetDisable(lAxisNo : LongInt; dwSel : DWord) : DWord; stdcall;

// Get 'AxmM3SetAbsEncOrgResetDisable' setting value.(Only for M3)
// upSel: 0, CMD / ACTPOS set to 0 after home search. (Default)
// upSel: 1, CMD / ACTPOS value is not set after home search.
function AxmM3GetAbsEncOrgResetDisable(lAxisNo : LongInt; dwpSel : PDWord) : DWord; stdcall;


// Setting whether using alarm maintenance function when switch to slave offline mode.(Only for M3)
// dwSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
// dwSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
function AxmM3SetOfflineAlarmEnable(lAxisNo : LongInt; dwSel : DWord) : DWord; stdcall;

// Get 'AxmM3SetOfflineAlarmEnable' setting value.(Only for M3)
// upSel: 0, ML3 Slave ONLINE-> OFFLINE Alarm handling disabled. (Default)
// upSel: 1, ML3 Slave ONLINE-> OFFLINE Alarm handling enabled.
function AxmM3GetOfflineAlarmEnable(lAxisNo : LongInt; dwpSel : PDWord) : DWord; stdcall;

// Read value of slave online or offline status. (Only for M3)
// upSel: 0, ONLINE->OFFLINE Not converted
// upSel: 1, ONLINE->OFFLINE converted
function AxmM3ReadOnlineToOfflineStatus(lAxisNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;

    function AxlSetLockMode (lBoardNo : LongInt; wLockMode : Word) : DWord; stdcall;
function AxlSetLockData(lBoardNo : LongInt; dwTotalNodeNum : DWord; dwpNodeNo : PDWord; dwpNodeID : PDWord; dwpLockData : PDWord) : DWord; stdcall;
    function AxmMoveStartPosWithAVC (lAxisNo : LongInt; dPosition : Double; dMaxVelocity : Double; dMaxAccel : Double; dMinJerk : Double; dpMoveVelocity : PDouble; dpMoveAccel : PDouble; dpMoveJerk : PDouble) : DWord; stdcall;
//======== For EtherCAT Only =============================================================================
// The API for read VendorID, ProductCode and RevisionNo of EtherCat slave product by using StationAddress.
function AxlECatGetProductInfo(dwStationAddress : DWord; dwpVendorID : PDWord; dwpProductCode : PDWord; dwpRevisionNo : PDWord) : DWord; stdcall;
    function AxlECatGetProductInfoEx (lBoardNo : LongInt; dwStationAddress : DWord; pdwVendorID : PDWord; pdwProductCode : PDWord; pdwRevisionNo : PDWord) : DWord; stdcall;

// The API for verifying network status of EtherCAT slave product by using StationAddress.
function AxlECatGetModuleStatus(dwStationAddress : DWord) : DWord; stdcall;

// Read input PDO(Process Data Objects)
// dwBitOffset     : ProcessImage inputs bit offset value.
// dwDataBitLength : bit size of input pdo data.
// pbyData         : The Buffer for inserting read data.
function AxlECatReadPdoInput(dwBitOffset : DWord; dwDataBitLength : DWord; bypData : PByte) : DWord; stdcall;
    function AxlECatReadPdoInputEx (lBoardNo : LongInt; dwBitOffset : DWord; dwDataBitLength : DWord; pbyData : PByte) : DWord; stdcall;

// Read output PDO(Process Data Objects)
// dwBitOffset     : ProcessImage outputs bit offset value.
// dwDataBitLength : bit size of input pdo data.(for read)
// pbyData         : The Buffer for inserting read data.
function AxlECatReadPdoOutput(dwBitOffset : DWord; dwDataBitLength : DWord; bypData : PByte) : DWord; stdcall;
    function AxlECatReadPdoOutputEx (lBoardNo : LongInt; dwBitOffset : DWord; dwDataBitLength : DWord; pbyData : PByte) : DWord; stdcall;

// Write value to output process data.
// dwBitOffset     : ProcessImage outputs bit offset value.
// dwDataBitLength : bit size of output pdo data.(for write)
// pbyData         : The Buffer for inserting write data.
function AxlECatWritePdoOutput(dwBitOffset : DWord; dwDataBitLength : DWord; bypData : PByte) : DWord; stdcall;

// Read SDO(Service Data Objects) by using COE.
function AxlECatReadSdo(dwStationAddress : DWord; wObjectIndex : Word; byObjectSubIndex : Byte; bypData : PByte; dwDataLength : DWord; dwpReadDataLength : PDWord) : DWord; stdcall;
    function AxlECatReadSdoEx (lBoardNo : LongInt; dwStationAddress : DWord; wObjectIndex : Word; byObjectSubIndex : Byte; pbyData : PByte; dwDataLength : DWord; pdwReadDataLength : PDWord) : DWord; stdcall;

// Store values in SDO by using COE.
function AxlECatWriteSdo(dwStationAddress : DWord; wObjectIndex : Word; byObjectSubIndex : Byte; bypData : PByte; dwDataLength : DWord) : DWord; stdcall;
    function AxlECatWriteSdoEx (lBoardNo : LongInt; dwStationAddress : DWord; wObjectIndex : Word; byObjectSubIndex : Byte; pbyData : PByte; dwDataLength : DWord) : DWord; stdcall;

    function AxlECatReadSdoFromAxisDouble (lAxisNo : LongInt; wObjectIndex : Word; byObjectSubIndex : Byte; pdData : PDouble) : DWord; stdcall;

    function AxlECatWriteSdoFromAxisDouble (lAxisNo : LongInt; wObjectIndex : Word; byObjectSubIndex : Byte; pdData : PDouble) : DWord; stdcall;
// Read SDO(DWORD type) through the axis number.
function AxlECatReadSdoFromAxisDword(lAxisNo : LongInt; wObjectIndex : Word; byObjectSubIndex : Byte; dwpData : PDWord) : DWord; stdcall;

// Store values in SDO(DWORD type) through the axis number.
function AxlECatWriteSdoFromAxisDword(lAxisNo : LongInt; wObjectIndex : Word; byObjectSubIndex : Byte; dwpData : PDWord) : DWord; stdcall;

// Read SDO(WORD type) through the axis number.
function AxlECatReadSdoFromAxisWord(lAxisNo : LongInt; wObjectIndex : Word; byObjectSubIndex : Byte; wpData : PWord) : DWord; stdcall;

// Store values in SDO(WORD type) through the axis number.
function AxlECatWriteSdoFromAxisWord(lAxisNo : LongInt; wObjectIndex : Word; byObjectSubIndex : Byte; wpData : PWord) : DWord; stdcall;

// Read SDO(BYTE type) through the axis number.
function AxlECatReadSdoFromAxisByte(lAxisNo : LongInt; wObjectIndex : Word; byObjectSubIndex : Byte; bypData : PByte) : DWord; stdcall;

// Store values in SDO(BYTE type) through the axis number.
function AxlECatWriteSdoFromAxisByte(lAxisNo : LongInt; wObjectIndex : Word; byObjectSubIndex : Byte; bypData : PByte) : DWord; stdcall;

// Read value of EEPROM.
function AxlECatReadEEPRom(dwStationAddress : DWord; wEEPRomStartOffset : Word; wpData : PWord; dwDataLength : DWord) : DWord; stdcall;

// Write value to EEPROM.
function AxlECatWriteEEPRom(dwStationAddress : DWord; wEEPRomStartOffset : Word; wpData : PWord; dwDataLength : DWord) : DWord; stdcall;
    function AxlECatReadEEPRomEx (lBoardNo : LongInt; dwStationAddress : DWord; wEEPRomStartOffset : Word; pwData : PWord; dwDataLength : DWord) : DWord; stdcall;

    function AxlECatWriteEEPRomEx (lBoardNo : LongInt; dwStationAddress : DWord; wEEPRomStartOffset : Word; pwData : PWord; dwDataLength : DWord) : DWord; stdcall;

// Read value of a register.
function AxlECatReadRegister(dwStationAddress : DWord; wRegisterOffset : Word; vpData : Pointer; wLen : Word) : DWord; stdcall;

// Write value of a register.
function AxlECatWriteRegister(dwStationAddress : DWord; wRegisterOffset : Word; vpData : Pointer; wLen : Word) : DWord; stdcall;

// Save BackupData as a file from among the object dictionary of EtherCat slave.
function AxlECatSaveHotSwapData(dwStationAddress : DWord) : DWord; stdcall;

// Load BackupData which saved as a file from corresponding EtherCat salve.
function AxlECatLoadHotSwapData(dwStationAddress : DWord) : DWord; stdcall;


// When using the HotSwapStart API(Function to advance HotSwap only for registered StationAddresses),
//       it stores the StationAddress in HotSwapConfig, confirms existence and deletes it.
function AxlECatSetHotSwap(dwStationAddress : DWord) : DWord; stdcall;
function AxlECatIsSetHotSwap(dwStationAddress : DWord) : DWord; stdcall;
function AxlECatReSetHotSwap(dwStationAddress : DWord) : DWord; stdcall;

// Set EtherCat master mode (configure = 0, RumMode = 1)
function AxlECatSetMasterMode(dwMasterMode : DWord) : DWord; stdcall;

// Get mode status of EtherCat master.
function AxlECatGetMasterMode(dwpMasterMode : PDWord) : DWord; stdcall;

// Set MasterOperationMode of EtherCat master.
function AxlECatSetMasterOperationMode(dwOperationMode : DWord) : DWord; stdcall;

// Get MasterOperationMode of EtherCat master.
function AxlECatGetMasterOperationMode(dwpOperationMode : PDWord) : DWord; stdcall;

// Requesting scan command to EtherCat master, and then command to save scaned data to SHM.
function AxlECatRequestScanData() : DWord; stdcall;


// Get total number of scanned slaves.
function AxlECatGetScanSlaveCount(dwpSlaveCount : PDWord) : DWord; stdcall;

// Get current status information of EtherCat master.
function AxlECatGetStatus(npECMasterStatus : PInteger; npECSlaveStatus : PInteger; npECConnectedSlave : PInteger; npECConfiguredSlave : PInteger; npJobTaskCycleCnt : PInteger; dwpECMasterNotification : PDWord) : DWord; stdcall;

// Reconnecting failed network.
function AxlEcatReConnect() : DWord; stdcall;

// Get address information of slave which be set.
function AxmECatReadAddress(lAxisNo : LongInt; dwpStationAddress : PDWord; lpAutoIncAddress : PLongInt; dwpAliasAddress : PDWord) : DWord; stdcall;
function AxdECatReadAddress(lModuleNo : LongInt; dwpStationAddress : PDWord; lpAutoIncAddress : PLongInt; dwpAliasAddress : PDWord) : DWord; stdcall;
function AxaECatReadAddress(lModuleNo : LongInt; dwpStationAddress : PDWord; lpAutoIncAddress : PLongInt; dwpAliasAddress : PDWord) : DWord; stdcall;
function AxsECatReadAddress(lPortNo : LongInt; dwpStationAddress : PDWord; lpAutoIncAddress : PLongInt; dwpAliasAddress : PDWord) : DWord; stdcall;


// Monitor
// Add an item to proceed with data collection.
function AxlMonitorSetItem(lItemIndex : LongInt; dwSignalType : DWord; lSignalNo : LongInt; lSubSignalNo : LongInt) : DWord; stdcall;

// Get information about items to be collected.
function AxlMonitorGetIndexInfo(lpItemSize : PLongInt; lpItemIndex : PLongInt) : DWord; stdcall;

// Get detailed settings of each items for data collection progress.
function AxlMonitorGetItemInfo(lItemSize : LongInt; dwpSignalType : PDWord; lpSignalNo : PLongInt; lpSubSignalNo : PLongInt) : DWord; stdcall;

// Reset settings of all data collection items.
function AxlMonitorResetAllItem() : DWord; stdcall;

// Reset settings of selected data collection items.
function AxlMonitorResetItem(lItemIndex : LongInt) : DWord; stdcall;

// Set the trigger condition of data collection.
function AxlMonitorSetTriggerOption(dwSignalType : DWord; lSignalNo : LongInt; lSubSignalNo : LongInt; dwOperatorType : DWord; dValue1 : Double; dValue2 : Double) : DWord; stdcall;


// Reset trigger condition of data collection.
function AxlMonitorResetTriggerOption() : DWord; stdcall;

// Start collecting data.
function AxlMonitorStart(dwStartOption : DWord; dwOverflowOption : DWord) : DWord; stdcall;

// Stop collecting data.
function AxlMonitorStop() : DWord; stdcall;

// Read collected data.
function AxlMonitorReadData(lpItemSize : PLongInt; lpDataCount : PLongInt; dpReadData : PDouble) : DWord; stdcall;

// Read period of data collection.
function AxlMonitorReadPeriod(dwpPeriod : PDWord) : DWord; stdcall;



//////////////////////////////////////////////////////////////////////////
// MonitorEx
// Add an item to proceed with data collection.
function AxlMonitorExSetItem(lItemIndex : LongInt; dwSignalType : DWord; lSignalNo : LongInt; lSubSignalNo : LongInt) : DWord; stdcall;

// Gets information about the items to be collected.
function AxlMonitorExGetIndexInfo(lpItemSize : PLongInt; lpItemIndex : PLongInt) : DWord; stdcall;

// Gets the detailed settings for each item to proceed with data collection.
function AxlMonitorExGetItemInfo(lItemIndex : LongInt; dwpSignalType : PDWord; lpSignalNo : PLongInt; lpSubSignalNo : PLongInt) : DWord; stdcall;

// Reset the settings for all data collection items.
function AxlMonitorExResetAllItem() : DWord; stdcall;

// Reset the settings of the selected data collection item.
function AxlMonitorExResetItem(lItemIndex : LongInt) : DWord; stdcall;

// Sets the trigger condition for data collection.
function AxlMonitorExSetTriggerOption(dwSignalType : DWord; lSignalNo : LongInt; lSubSignalNo : LongInt; dwOperatorType : DWord; dValue1 : Double; dValue2 : Double) : DWord; stdcall;


// Reset trigger conditions for data collection.
function AxlMonitorExResetTriggerOption() : DWord; stdcall;

// Start collecting data.
function AxlMonitorExStart(dwStartOption : DWord; dwOverflowOption : DWord) : DWord; stdcall;

// Stop collecting data.
function AxlMonitorExStop() : DWord; stdcall;

// Gets collected data.
function AxlMonitorExReadData(lpItemSize : PLongInt; lpDataCount : PLongInt; dpReadData : PDouble) : DWord; stdcall;

// Gets the period of data collection.
function AxlMonitorExReadPeriod(dwpPeriod : PDWord) : DWord; stdcall;


//////////////////////////////////////////////////////////////////////////

// Linear interpolation about 2 axis including information of offset position for X2, Y2 axis.
function AxmLineMoveDual01(lCoordNo : LongInt; dpEndPosition : PDouble; dVelocity : Double; dAccel : Double; dDecel : Double; dOffsetLength : Double; dTotalLength : Double; dpStartOffsetPosition : PDouble; dpEndOffsetPosition : PDouble) : DWord; stdcall;
// Arc interpolation about 2 axis including information of offset position for X2, Y2 axis.
function AxmCircleCenterMoveDual01(lCoordNo : LongInt; lpAxes : PLongInt; dpCenterPosition : PDouble; dpEndPosition : PDouble; dVelocity : Double; dAccel : Double; dDecel : Double; dwCWDir : DWord; dOffsetLength : Double; dTotalLength : Double; dpStartOffsetPosition : PDouble; dpEndOffsetPosition : PDouble) : DWord; stdcall;

// About ECAT Foe
function AxdSetFirmwareUpdateInfo(lModuleNo : LongInt; dwTotalDataSize : DWord; dwTotalPacketSize : DWord) : DWord; stdcall;
function AxdSetFirmwareDataTrans(lModuleNo : LongInt; dwPacketIndex : DWord; dwpaPacketData : PDWord) : DWord; stdcall;
function AxdSetFirmwareUpdate(lModuleNo : LongInt; szFileName : PChar; dwFileNameLen : DWord; dwPassWord : DWord) : DWord; stdcall;


function AxaSetFirmwareUpdateInfo(lModuleNo : LongInt; dwTotalDataSize : DWord; dwTotalPacketSize : DWord) : DWord; stdcall;
function AxaSetFirmwareDataTrans(lModuleNo : LongInt; dwPacketIndex : DWord; dwpaPacketData : PDWord) : DWord; stdcall;
function AxaSetFirmwareUpdate(lModuleNo : LongInt; szFileName : PChar; dwFileNameLen : DWord; dwPassWord : DWord) : DWord; stdcall;


function AxmSetFirmwareUpdateInfo(lAxisNo : LongInt; dwTotalDataSize : DWord; dwTotalPacketSize : DWord) : DWord; stdcall;
function AxmSetFirmwareDataTrans(lAxisNo : LongInt; dwPacketIndex : DWord; dwpaPacketData : PDWord) : DWord; stdcall;

function AxmSetFirmwareUpdate(lAxisNo : LongInt; szFileName : PChar; dwFileNameLen : DWord; dwPassWord : DWord) : DWord; stdcall;
    function AxmSetFoeUploadInfo (lAxisNo : LongInt; dwTotalDataSize : DWord; dwTotalPacketSize : DWord) : DWord; stdcall;
    function AxmGetFoeUploadData (lAxisNo : LongInt; dwPacketIndex : DWord; dwaPacketData : PDWord) : DWord; stdcall;
    function AxmSetFoeUpload (lAxisNo : LongInt; szFileName : char*; dwFileNameLen : DWord; dwPassWord : DWord) : DWord; stdcall;


function AxmMotSetOperationMode(lAxisNo : LongInt; dwOperationMode : DWord) : DWord; stdcall;

function AxmMotGetOperationMode(lAxisNo : LongInt; pdwOperationMode : PDWord) : DWord; stdcall;



    function AxcTriggerSetPatternData (lChannelNo : LongInt; nDataCnt : LongInt; dwOption : DWord; dpPatternData : PDouble) : DWord; stdcall;
    function AxcTriggerGetPatternData (lChannelNo : LongInt; npDataCnt : PLongInt; dwpOption : PDWord; dpPatternData : PDouble) : DWord; stdcall;

    function AxmSpiralMoveEx (lCoordNo : LongInt; dSpiralPitch : Double; dTurningCount : Double; dAngleOfPose : Double; dwIsInnerDirection : DWord; dVelocity : Double; dAcceleration : Double; dDeceleration : Double) : DWord; stdcall;
    function AxmFilletMove (lCoordinate : LongInt; dPosition : PDouble; dFirstVector : PDouble; dSecondVector : PDouble; dMaxVelocity : Double; dMaxAccel : Double; dMaxDecel : Double; dRadius : Double) : DWord; stdcall;

    function AxmSignalIsServoOnSingleAxis (lAxisNo : LongInt; upOnOff : PDWord) : DWord; stdcall;

    function AxmMotSetTorqueConnection (lAxisNo : LongInt; lSourceAxisNo : LongInt; dwEnable : DWord) : DWord; stdcall;
    function AxmMotGetTorqueConnection (lAxisNo : LongInt; plSourceAxisNo : PLongInt; pdwEnable : PDWord) : DWord; stdcall;


implementation

const

    dll_name    = 'AXL.dll';
    function AxlGetBoardAddress; external dll_name name 'AxlGetBoardAddress';
    function AxlGetBoardID; external dll_name name 'AxlGetBoardID';
    function AxlGetBoardVersion; external dll_name name 'AxlGetBoardVersion';
    function AxlGetModuleID; external dll_name name 'AxlGetModuleID';
    function AxlGetModuleVersion; external dll_name name 'AxlGetModuleVersion';
    function AxlGetModuleNodeInfo; external dll_name name 'AxlGetModuleNodeInfo';
    function AxlSetDataFlash; external dll_name name 'AxlSetDataFlash';
    function AxlSetEStopInterLock; external dll_name name 'AxlSetEStopInterLock';
    function AxlGetEStopInterLock; external dll_name name 'AxlGetEStopInterLock';
    function AxlReadEStopInterLock; external dll_name name 'AxlReadEStopInterLock';
    function AxlGetDataFlash; external dll_name name 'AxlGetDataFlash';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxmSetCommand; external dll_name name 'AxmSetCommand';
    function AxmSetCommandData08; external dll_name name 'AxmSetCommandData08';
    function AxmGetCommandData08; external dll_name name 'AxmGetCommandData08';
    function AxmSetCommandData16; external dll_name name 'AxmSetCommandData16';
    function AxmGetCommandData16; external dll_name name 'AxmGetCommandData16';
    function AxmSetCommandData24; external dll_name name 'AxmSetCommandData24';
    function AxmGetCommandData24; external dll_name name 'AxmGetCommandData24';
    function AxmSetCommandData32; external dll_name name 'AxmSetCommandData32';
    function AxmGetCommandData32; external dll_name name 'AxmGetCommandData32';
    function AxmSetCommandQi; external dll_name name 'AxmSetCommandQi';
    function AxmSetCommandData08Qi; external dll_name name 'AxmSetCommandData08Qi';
    function AxmGetCommandData08Qi; external dll_name name 'AxmGetCommandData08Qi';
    function AxmSetCommandData16Qi; external dll_name name 'AxmSetCommandData16Qi';
    function AxmGetCommandData16Qi; external dll_name name 'AxmGetCommandData16Qi';
    function AxmSetCommandData24Qi; external dll_name name 'AxmSetCommandData24Qi';
    function AxmGetCommandData24Qi; external dll_name name 'AxmGetCommandData24Qi';
    function AxmSetCommandData32Qi; external dll_name name 'AxmSetCommandData32Qi';
    function AxmGetCommandData32Qi; external dll_name name 'AxmGetCommandData32Qi';
    function AxmGetPortData; external dll_name name 'AxmGetPortData';
    function AxmSetPortData; external dll_name name 'AxmSetPortData';
    function AxmGetPortDataQi; external dll_name name 'AxmGetPortDataQi';
    function AxmSetPortDataQi; external dll_name name 'AxmSetPortDataQi';
    function AxmSetScriptCaptionIp; external dll_name name 'AxmSetScriptCaptionIp';
    function AxmGetScriptCaptionIp; external dll_name name 'AxmGetScriptCaptionIp';
    function AxmSetScriptCaptionQi; external dll_name name 'AxmSetScriptCaptionQi';
    function AxmGetScriptCaptionQi; external dll_name name 'AxmGetScriptCaptionQi';
    function AxmSetScriptCaptionQueueClear; external dll_name name 'AxmSetScriptCaptionQueueClear';
    function AxmGetScriptCaptionQueueCount; external dll_name name 'AxmGetScriptCaptionQueueCount';
    function AxmGetScriptCaptionQueueDataCount; external dll_name name 'AxmGetScriptCaptionQueueDataCount';
    function AxmGetOptimizeDriveData; external dll_name name 'AxmGetOptimizeDriveData';
    function AxmBoardWriteByte; external dll_name name 'AxmBoardWriteByte';
    function AxmBoardReadByte; external dll_name name 'AxmBoardReadByte';
    function AxmBoardWriteWord; external dll_name name 'AxmBoardWriteWord';
    function AxmBoardReadWord; external dll_name name 'AxmBoardReadWord';
    function AxmBoardWriteDWord; external dll_name name 'AxmBoardWriteDWord';
    function AxmBoardReadDWord; external dll_name name 'AxmBoardReadDWord';
    function AxmModuleWriteByte; external dll_name name 'AxmModuleWriteByte';
    function AxmModuleReadByte; external dll_name name 'AxmModuleReadByte';
    function AxmModuleWriteWord; external dll_name name 'AxmModuleWriteWord';
    function AxmModuleReadWord; external dll_name name 'AxmModuleReadWord';
    function AxmModuleWriteDWord; external dll_name name 'AxmModuleWriteDWord';
    function AxmModuleReadDWord; external dll_name name 'AxmModuleReadDWord';
    function AxmStatusSetActComparatorPos; external dll_name name 'AxmStatusSetActComparatorPos';
    function AxmStatusGetActComparatorPos; external dll_name name 'AxmStatusGetActComparatorPos';
    function AxmStatusSetCmdComparatorPos; external dll_name name 'AxmStatusSetCmdComparatorPos';
    function AxmStatusGetCmdComparatorPos; external dll_name name 'AxmStatusGetCmdComparatorPos';
    function AxmLineMoveVel; external dll_name name 'AxmLineMoveVel';
    function AxmSensorSetSignal; external dll_name name 'AxmSensorSetSignal';
    function AxmSensorGetSignal; external dll_name name 'AxmSensorGetSignal';
    function AxmSensorReadSignal; external dll_name name 'AxmSensorReadSignal';
    function AxmSensorMovePos; external dll_name name 'AxmSensorMovePos';
    function AxmSensorStartMovePos; external dll_name name 'AxmSensorStartMovePos';
    function AxmHomeGetStepTrace; external dll_name name 'AxmHomeGetStepTrace';
    function AxmHomeSetConfig; external dll_name name 'AxmHomeSetConfig';
    function AxmHomeGetConfig; external dll_name name 'AxmHomeGetConfig';
    function AxmHomeSetMoveSearch; external dll_name name 'AxmHomeSetMoveSearch';
    function AxmHomeSetMoveReturn; external dll_name name 'AxmHomeSetMoveReturn';
    function AxmHomeSetMoveLeave; external dll_name name 'AxmHomeSetMoveLeave';
    function AxmHomeSetMultiMoveSearch; external dll_name name 'AxmHomeSetMultiMoveSearch';
    function AxmContiSetProfileMode; external dll_name name 'AxmContiSetProfileMode';
    function AxmContiGetProfileMode; external dll_name name 'AxmContiGetProfileMode';
    function AxdiInterruptFlagReadBit; external dll_name name 'AxdiInterruptFlagReadBit';
    function AxdiInterruptFlagReadByte; external dll_name name 'AxdiInterruptFlagReadByte';
    function AxdiInterruptFlagReadWord; external dll_name name 'AxdiInterruptFlagReadWord';
    function AxdiInterruptFlagReadDword; external dll_name name 'AxdiInterruptFlagReadDword';
    function AxdiInterruptFlagRead; external dll_name name 'AxdiInterruptFlagRead';
    function AxmLogSetAxis; external dll_name name 'AxmLogSetAxis';
    function AxmLogGetAxis; external dll_name name 'AxmLogGetAxis';
    function AxaiLogSetChannel; external dll_name name 'AxaiLogSetChannel';
    function AxaiLogGetChannel; external dll_name name 'AxaiLogGetChannel';
    function AxaoLogSetChannel; external dll_name name 'AxaoLogSetChannel';
    function AxaoLogGetChannel; external dll_name name 'AxaoLogGetChannel';
    function AxdLogSetModule; external dll_name name 'AxdLogSetModule';
    function AxdLogGetModule; external dll_name name 'AxdLogGetModule';
    function AxlGetFirmwareVersion; external dll_name name 'AxlGetFirmwareVersion';
    function AxlSetFirmwareCopy; external dll_name name 'AxlSetFirmwareCopy';
    function AxlSetFirmwareUpdate; external dll_name name 'AxlSetFirmwareUpdate';
    function AxlCheckStatus; external dll_name name 'AxlCheckStatus';
    function AxlRtexUniversalCmd; external dll_name name 'AxlRtexUniversalCmd';
    function AxmRtexSlaveCmd; external dll_name name 'AxmRtexSlaveCmd';
    function AxmRtexGetSlaveCmdResult; external dll_name name 'AxmRtexGetSlaveCmdResult';
    function AxmRtexGetSlaveCmdResultEx; external dll_name name 'AxmRtexGetSlaveCmdResultEx';
    function AxmRtexGetAxisStatus; external dll_name name 'AxmRtexGetAxisStatus';
    function AxmRtexGetAxisReturnData; external dll_name name 'AxmRtexGetAxisReturnData';
    function AxmRtexGetAxisSlaveStatus; external dll_name name 'AxmRtexGetAxisSlaveStatus';
    function AxmSetAxisCmd; external dll_name name 'AxmSetAxisCmd';
    function AxmGetAxisCmdResult; external dll_name name 'AxmGetAxisCmdResult';
    function AxdSetAndGetSlaveCmdResult; external dll_name name 'AxdSetAndGetSlaveCmdResult';
    function AxaSetAndGetSlaveCmdResult; external dll_name name 'AxaSetAndGetSlaveCmdResult';
    function AxcSetAndGetSlaveCmdResult; external dll_name name 'AxcSetAndGetSlaveCmdResult';
    function AxlGetDpRamData; external dll_name name 'AxlGetDpRamData';
    function AxlBoardReadDpramWord; external dll_name name 'AxlBoardReadDpramWord';
    function AxlBoardWriteDpramWord; external dll_name name 'AxlBoardWriteDpramWord';
    function AxlSetSendBoardEachCommand; external dll_name name 'AxlSetSendBoardEachCommand';
    function AxlSetSendBoardCommand; external dll_name name 'AxlSetSendBoardCommand';
    function AxlGetResponseBoardCommand; external dll_name name 'AxlGetResponseBoardCommand';
    function AxmInfoGetFirmwareVersion; external dll_name name 'AxmInfoGetFirmwareVersion';
    function AxaInfoGetFirmwareVersion; external dll_name name 'AxaInfoGetFirmwareVersion';
    function AxdInfoGetFirmwareVersion; external dll_name name 'AxdInfoGetFirmwareVersion';
    function AxcInfoGetFirmwareVersion; external dll_name name 'AxcInfoGetFirmwareVersion';
    function AxmSetTorqFeedForward; external dll_name name 'AxmSetTorqFeedForward';
    function AxmGetTorqFeedForward; external dll_name name 'AxmGetTorqFeedForward';
    function AxmSetVelocityFeedForward; external dll_name name 'AxmSetVelocityFeedForward';
    function AxmGetVelocityFeedForward; external dll_name name 'AxmGetVelocityFeedForward';
    function AxmSignalSetEncoderType; external dll_name name 'AxmSignalSetEncoderType';
    function AxmSignalGetEncoderType; external dll_name name 'AxmSignalGetEncoderType';
    function AxmMotSetUserMotion; external dll_name name 'AxmMotSetUserMotion';
    function AxmMotSetUserMotionUsage; external dll_name name 'AxmMotSetUserMotionUsage';
    function AxmMotSetUserPosMotion; external dll_name name 'AxmMotSetUserPosMotion';
    function AxmMotSetUserPosMotionUsage; external dll_name name 'AxmMotSetUserPosMotionUsage';
    function AxcKeWriteRamDataAddr; external dll_name name 'AxcKeWriteRamDataAddr';
    function AxcKeReadRamDataAddr; external dll_name name 'AxcKeReadRamDataAddr';
    function AxcKeResetRamDataAll; external dll_name name 'AxcKeResetRamDataAll';
    function AxcTriggerSetTimeout; external dll_name name 'AxcTriggerSetTimeout';
    function AxcTriggerGetTimeout; external dll_name name 'AxcTriggerGetTimeout';
    function AxcStatusGetWaitState; external dll_name name 'AxcStatusGetWaitState';
    function AxcStatusSetWaitState; external dll_name name 'AxcStatusSetWaitState';
    function AxcKeSetCommandData32; external dll_name name 'AxcKeSetCommandData32';
    function AxcKeSetCommandData16; external dll_name name 'AxcKeSetCommandData16';
    function AxcKeGetCommandData32; external dll_name name 'AxcKeGetCommandData32';
    function AxcKeGetCommandData16; external dll_name name 'AxcKeGetCommandData16';
    function AxmSeqSetAxisMap; external dll_name name 'AxmSeqSetAxisMap';
    function AxmSeqGetAxisMap; external dll_name name 'AxmSeqGetAxisMap';
    function AxmSeqSetMasterAxisNo; external dll_name name 'AxmSeqSetMasterAxisNo';
    function AxmSeqBeginNode; external dll_name name 'AxmSeqBeginNode';
    function AxmSeqEndNode; external dll_name name 'AxmSeqEndNode';
    function AxmSeqStart; external dll_name name 'AxmSeqStart';
    function AxmSeqAddNode; external dll_name name 'AxmSeqAddNode';
    function AxmSeqGetNodeNum; external dll_name name 'AxmSeqGetNodeNum';
    function AxmSeqGetTotalNodeNum; external dll_name name 'AxmSeqGetTotalNodeNum';
    function AxmSeqIsMotion; external dll_name name 'AxmSeqIsMotion';
    function AxmSeqWriteClear; external dll_name name 'AxmSeqWriteClear';
    function AxmSeqStop; external dll_name name 'AxmSeqStop';
    function AxmStatusSetMon; external dll_name name 'AxmStatusSetMon';
    function AxmStatusGetMon; external dll_name name 'AxmStatusGetMon';
    function AxmStatusReadMon; external dll_name name 'AxmStatusReadMon';
    function AxmStatusReadMonEx; external dll_name name 'AxmStatusReadMonEx';
    function AxlSetIoPort; external dll_name name 'AxlSetIoPort';
    function AxlGetIoPort; external dll_name name 'AxlGetIoPort';
    function AxlM3SetFWUpdateInit; external dll_name name 'AxlM3SetFWUpdateInit';
    function AxlM3GetFWUpdateInit; external dll_name name 'AxlM3GetFWUpdateInit';
    function AxlM3SetFWUpdateCopy; external dll_name name 'AxlM3SetFWUpdateCopy';
    function AxlM3GetFWUpdateCopy; external dll_name name 'AxlM3GetFWUpdateCopy';
    function AxlM3SetFWUpdate; external dll_name name 'AxlM3SetFWUpdate';
    function AxlM3GetFWUpdate; external dll_name name 'AxlM3GetFWUpdate';
    function AxlM3SetCFGData; external dll_name name 'AxlM3SetCFGData';
    function AxlM3GetCFGData; external dll_name name 'AxlM3GetCFGData';
    function AxlM3SetMCParaUpdateInit; external dll_name name 'AxlM3SetMCParaUpdateInit';
    function AxlM3GetMCParaUpdateInit; external dll_name name 'AxlM3GetMCParaUpdateInit';
    function AxlM3SetMCParaUpdateCopy; external dll_name name 'AxlM3SetMCParaUpdateCopy';
    function AxlM3GetMCParaUpdateCopy; external dll_name name 'AxlM3GetMCParaUpdateCopy';
    function AxlBoardReadDWord; external dll_name name 'AxlBoardReadDWord';
    function AxlBoardWriteDWord; external dll_name name 'AxlBoardWriteDWord';
    function AxlBoardReadDWordEx; external dll_name name 'AxlBoardReadDWordEx';
    function AxlBoardWriteDWordEx; external dll_name name 'AxlBoardWriteDWordEx';
    function AxmM3ServoSetCtrlStopMode; external dll_name name 'AxmM3ServoSetCtrlStopMode';
    function AxmM3ServoSetCtrlLtSel; external dll_name name 'AxmM3ServoSetCtrlLtSel';
    function AxmStatusReadServoCmdIOInput; external dll_name name 'AxmStatusReadServoCmdIOInput';
    function AxmM3ServoExInterpolate; external dll_name name 'AxmM3ServoExInterpolate';
    function AxmM3ServoSetExpoAccBias; external dll_name name 'AxmM3ServoSetExpoAccBias';
    function AxmM3ServoSetExpoAccTime; external dll_name name 'AxmM3ServoSetExpoAccTime';
    function AxmM3ServoSetMoveAvrTime; external dll_name name 'AxmM3ServoSetMoveAvrTime';
    function AxmM3ServoSetAccFilter; external dll_name name 'AxmM3ServoSetAccFilter';
    function AxmM3ServoSetCprmMonitor1; external dll_name name 'AxmM3ServoSetCprmMonitor1';
    function AxmM3ServoSetCprmMonitor2; external dll_name name 'AxmM3ServoSetCprmMonitor2';
    function AxmM3ServoStatusReadCprmMonitor1; external dll_name name 'AxmM3ServoStatusReadCprmMonitor1';
    function AxmM3ServoStatusReadCprmMonitor2; external dll_name name 'AxmM3ServoStatusReadCprmMonitor2';
    function AxmM3ServoSetAccDec; external dll_name name 'AxmM3ServoSetAccDec';
    function AxmM3ServoSetStop; external dll_name name 'AxmM3ServoSetStop';
    function AxlM3GetStationParameter; external dll_name name 'AxlM3GetStationParameter';
    function AxlM3SetStationParameter; external dll_name name 'AxlM3SetStationParameter';
    function AxlM3GetStationIdRd; external dll_name name 'AxlM3GetStationIdRd';
    function AxlM3SetStationNop; external dll_name name 'AxlM3SetStationNop';
    function AxlM3SetStationConfig; external dll_name name 'AxlM3SetStationConfig';
    function AxlM3GetStationAlarm; external dll_name name 'AxlM3GetStationAlarm';
    function AxlM3SetStationAlarmClear; external dll_name name 'AxlM3SetStationAlarmClear';
    function AxlM3SetStationSyncSet; external dll_name name 'AxlM3SetStationSyncSet';
    function AxlM3SetStationConnect; external dll_name name 'AxlM3SetStationConnect';
    function AxlM3SetStationDisConnect; external dll_name name 'AxlM3SetStationDisConnect';
    function AxlM3GetStationStoredParameter; external dll_name name 'AxlM3GetStationStoredParameter';
    function AxlM3SetStationStoredParameter; external dll_name name 'AxlM3SetStationStoredParameter';
    function AxlM3GetStationMemory; external dll_name name 'AxlM3GetStationMemory';
    function AxlM3SetStationMemory; external dll_name name 'AxlM3SetStationMemory';
    function AxlM3SetStationAccessMode; external dll_name name 'AxlM3SetStationAccessMode';
    function AxlM3GetStationAccessMode; external dll_name name 'AxlM3GetStationAccessMode';
    function AxlM3SetAutoSyncConnectMode; external dll_name name 'AxlM3SetAutoSyncConnectMode';
    function AxlM3GetAutoSyncConnectMode; external dll_name name 'AxlM3GetAutoSyncConnectMode';
    function AxlM3SyncConnectSingle; external dll_name name 'AxlM3SyncConnectSingle';
    function AxlM3SyncDisconnectSingle; external dll_name name 'AxlM3SyncDisconnectSingle';
    function AxlM3IsOnLine; external dll_name name 'AxlM3IsOnLine';
    function AxlM3GetStationRWS; external dll_name name 'AxlM3GetStationRWS';
    function AxlM3SetStationRWS; external dll_name name 'AxlM3SetStationRWS';
    function AxlM3GetStationRWA; external dll_name name 'AxlM3GetStationRWA';
    function AxlM3SetStationRWA; external dll_name name 'AxlM3SetStationRWA';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmHomeGetM3FWRealRate; external dll_name name 'AxmHomeGetM3FWRealRate';
    function AxmHomeGetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeGetM3OffsetAvoideSenArea';
    function AxmHomeSetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeSetM3OffsetAvoideSenArea';
    function AxmM3SetAbsEncOrgResetDisable; external dll_name name 'AxmM3SetAbsEncOrgResetDisable';
    function AxmM3GetAbsEncOrgResetDisable; external dll_name name 'AxmM3GetAbsEncOrgResetDisable';
    function AxmM3SetOfflineAlarmEnable; external dll_name name 'AxmM3SetOfflineAlarmEnable';
    function AxmM3GetOfflineAlarmEnable; external dll_name name 'AxmM3GetOfflineAlarmEnable';
    function AxmM3ReadOnlineToOfflineStatus; external dll_name name 'AxmM3ReadOnlineToOfflineStatus';
    function AxlSetLockData; external dll_name name 'AxlSetLockData';
    function AxlECatGetProductInfo; external dll_name name 'AxlECatGetProductInfo';
    function AxlECatGetModuleStatus; external dll_name name 'AxlECatGetModuleStatus';
    function AxlECatReadPdoInput; external dll_name name 'AxlECatReadPdoInput';
    function AxlECatReadPdoOutput; external dll_name name 'AxlECatReadPdoOutput';
    function AxlECatWritePdoOutput; external dll_name name 'AxlECatWritePdoOutput';
    function AxlECatReadSdo; external dll_name name 'AxlECatReadSdo';
    function AxlECatWriteSdo; external dll_name name 'AxlECatWriteSdo';
    function AxlECatReadSdoFromAxisDword; external dll_name name 'AxlECatReadSdoFromAxisDword';
    function AxlECatWriteSdoFromAxisDword; external dll_name name 'AxlECatWriteSdoFromAxisDword';
    function AxlECatReadSdoFromAxisWord; external dll_name name 'AxlECatReadSdoFromAxisWord';
    function AxlECatWriteSdoFromAxisWord; external dll_name name 'AxlECatWriteSdoFromAxisWord';
    function AxlECatReadSdoFromAxisByte; external dll_name name 'AxlECatReadSdoFromAxisByte';
    function AxlECatWriteSdoFromAxisByte; external dll_name name 'AxlECatWriteSdoFromAxisByte';
    function AxlECatReadEEPRom; external dll_name name 'AxlECatReadEEPRom';
    function AxlECatWriteEEPRom; external dll_name name 'AxlECatWriteEEPRom';
    function AxlECatReadRegister; external dll_name name 'AxlECatReadRegister';
    function AxlECatWriteRegister; external dll_name name 'AxlECatWriteRegister';
    function AxlECatSaveHotSwapData; external dll_name name 'AxlECatSaveHotSwapData';
    function AxlECatLoadHotSwapData; external dll_name name 'AxlECatLoadHotSwapData';
    function AxlECatSetHotSwap; external dll_name name 'AxlECatSetHotSwap';
    function AxlECatIsSetHotSwap; external dll_name name 'AxlECatIsSetHotSwap';
    function AxlECatReSetHotSwap; external dll_name name 'AxlECatReSetHotSwap';
    function AxlECatSetMasterMode; external dll_name name 'AxlECatSetMasterMode';
    function AxlECatGetMasterMode; external dll_name name 'AxlECatGetMasterMode';
    function AxlECatSetMasterOperationMode; external dll_name name 'AxlECatSetMasterOperationMode';
    function AxlECatGetMasterOperationMode; external dll_name name 'AxlECatGetMasterOperationMode';
    function AxlECatRequestScanData; external dll_name name 'AxlECatRequestScanData';
    function AxlECatGetScanSlaveCount; external dll_name name 'AxlECatGetScanSlaveCount';
    function AxlECatGetStatus; external dll_name name 'AxlECatGetStatus';
    function AxlEcatReConnect; external dll_name name 'AxlEcatReConnect';
    function AxmECatReadAddress; external dll_name name 'AxmECatReadAddress';
    function AxdECatReadAddress; external dll_name name 'AxdECatReadAddress';
    function AxaECatReadAddress; external dll_name name 'AxaECatReadAddress';
    function AxsECatReadAddress; external dll_name name 'AxsECatReadAddress';
    function AxlMonitorSetItem; external dll_name name 'AxlMonitorSetItem';
    function AxlMonitorGetIndexInfo; external dll_name name 'AxlMonitorGetIndexInfo';
    function AxlMonitorGetItemInfo; external dll_name name 'AxlMonitorGetItemInfo';
    function AxlMonitorResetAllItem; external dll_name name 'AxlMonitorResetAllItem';
    function AxlMonitorResetItem; external dll_name name 'AxlMonitorResetItem';
    function AxlMonitorSetTriggerOption; external dll_name name 'AxlMonitorSetTriggerOption';
    function AxlMonitorResetTriggerOption; external dll_name name 'AxlMonitorResetTriggerOption';
    function AxlMonitorStart; external dll_name name 'AxlMonitorStart';
    function AxlMonitorStop; external dll_name name 'AxlMonitorStop';
    function AxlMonitorReadData; external dll_name name 'AxlMonitorReadData';
    function AxlMonitorReadPeriod; external dll_name name 'AxlMonitorReadPeriod';
    function AxlMonitorExSetItem; external dll_name name 'AxlMonitorExSetItem';
    function AxlMonitorExGetIndexInfo; external dll_name name 'AxlMonitorExGetIndexInfo';
    function AxlMonitorExGetItemInfo; external dll_name name 'AxlMonitorExGetItemInfo';
    function AxlMonitorExResetAllItem; external dll_name name 'AxlMonitorExResetAllItem';
    function AxlMonitorExResetItem; external dll_name name 'AxlMonitorExResetItem';
    function AxlMonitorExSetTriggerOption; external dll_name name 'AxlMonitorExSetTriggerOption';
    function AxlMonitorExResetTriggerOption; external dll_name name 'AxlMonitorExResetTriggerOption';
    function AxlMonitorExStart; external dll_name name 'AxlMonitorExStart';
    function AxlMonitorExStop; external dll_name name 'AxlMonitorExStop';
    function AxlMonitorExReadData; external dll_name name 'AxlMonitorExReadData';
    function AxlMonitorExReadPeriod; external dll_name name 'AxlMonitorExReadPeriod';
    function AxmLineMoveDual01; external dll_name name 'AxmLineMoveDual01';
    function AxmCircleCenterMoveDual01; external dll_name name 'AxmCircleCenterMoveDual01';
    function AxdSetFirmwareUpdateInfo; external dll_name name 'AxdSetFirmwareUpdateInfo';
    function AxdSetFirmwareDataTrans; external dll_name name 'AxdSetFirmwareDataTrans';
    function AxdSetFirmwareUpdate; external dll_name name 'AxdSetFirmwareUpdate';
    function AxaSetFirmwareUpdateInfo; external dll_name name 'AxaSetFirmwareUpdateInfo';
    function AxaSetFirmwareDataTrans; external dll_name name 'AxaSetFirmwareDataTrans';
    function AxaSetFirmwareUpdate; external dll_name name 'AxaSetFirmwareUpdate';
    function AxmSetFirmwareUpdateInfo; external dll_name name 'AxmSetFirmwareUpdateInfo';
    function AxmSetFirmwareDataTrans; external dll_name name 'AxmSetFirmwareDataTrans';
    function AxmSetFirmwareUpdate; external dll_name name 'AxmSetFirmwareUpdate';
    function AxmMotSetOperationMode; external dll_name name 'AxmMotSetOperationMode';
    function AxmMotGetOperationMode; external dll_name name 'AxmMotGetOperationMode';
    function AxcTriggerSetPatternData; external dll_name name 'AxcTriggerSetPatternData';
    function AxcTriggerGetPatternData; external dll_name name 'AxcTriggerGetPatternData';
    function AxlGetBoardAddress; external dll_name name 'AxlGetBoardAddress';
    function AxlGetBoardID; external dll_name name 'AxlGetBoardID';
    function AxlGetBoardVersion; external dll_name name 'AxlGetBoardVersion';
    function AxlGetModuleID; external dll_name name 'AxlGetModuleID';
    function AxlGetModuleVersion; external dll_name name 'AxlGetModuleVersion';
    function AxlGetModuleNodeInfo; external dll_name name 'AxlGetModuleNodeInfo';
    function AxlSetDataFlash; external dll_name name 'AxlSetDataFlash';
    function AxlSetEStopInterLock; external dll_name name 'AxlSetEStopInterLock';
    function AxlGetEStopInterLock; external dll_name name 'AxlGetEStopInterLock';
    function AxlReadEStopInterLock; external dll_name name 'AxlReadEStopInterLock';
    function AxlGetDataFlash; external dll_name name 'AxlGetDataFlash';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxmSetCommand; external dll_name name 'AxmSetCommand';
    function AxmSetCommandData08; external dll_name name 'AxmSetCommandData08';
    function AxmGetCommandData08; external dll_name name 'AxmGetCommandData08';
    function AxmSetCommandData16; external dll_name name 'AxmSetCommandData16';
    function AxmGetCommandData16; external dll_name name 'AxmGetCommandData16';
    function AxmSetCommandData24; external dll_name name 'AxmSetCommandData24';
    function AxmGetCommandData24; external dll_name name 'AxmGetCommandData24';
    function AxmSetCommandData32; external dll_name name 'AxmSetCommandData32';
    function AxmGetCommandData32; external dll_name name 'AxmGetCommandData32';
    function AxmSetCommandQi; external dll_name name 'AxmSetCommandQi';
    function AxmSetCommandData08Qi; external dll_name name 'AxmSetCommandData08Qi';
    function AxmGetCommandData08Qi; external dll_name name 'AxmGetCommandData08Qi';
    function AxmSetCommandData16Qi; external dll_name name 'AxmSetCommandData16Qi';
    function AxmGetCommandData16Qi; external dll_name name 'AxmGetCommandData16Qi';
    function AxmSetCommandData24Qi; external dll_name name 'AxmSetCommandData24Qi';
    function AxmGetCommandData24Qi; external dll_name name 'AxmGetCommandData24Qi';
    function AxmSetCommandData32Qi; external dll_name name 'AxmSetCommandData32Qi';
    function AxmGetCommandData32Qi; external dll_name name 'AxmGetCommandData32Qi';
    function AxmGetPortData; external dll_name name 'AxmGetPortData';
    function AxmSetPortData; external dll_name name 'AxmSetPortData';
    function AxmGetPortDataQi; external dll_name name 'AxmGetPortDataQi';
    function AxmSetPortDataQi; external dll_name name 'AxmSetPortDataQi';
    function AxmSetScriptCaptionIp; external dll_name name 'AxmSetScriptCaptionIp';
    function AxmGetScriptCaptionIp; external dll_name name 'AxmGetScriptCaptionIp';
    function AxmSetScriptCaptionQi; external dll_name name 'AxmSetScriptCaptionQi';
    function AxmGetScriptCaptionQi; external dll_name name 'AxmGetScriptCaptionQi';
    function AxmSetScriptCaptionQueueClear; external dll_name name 'AxmSetScriptCaptionQueueClear';
    function AxmGetScriptCaptionQueueCount; external dll_name name 'AxmGetScriptCaptionQueueCount';
    function AxmGetScriptCaptionQueueDataCount; external dll_name name 'AxmGetScriptCaptionQueueDataCount';
    function AxmGetOptimizeDriveData; external dll_name name 'AxmGetOptimizeDriveData';
    function AxmBoardWriteByte; external dll_name name 'AxmBoardWriteByte';
    function AxmBoardReadByte; external dll_name name 'AxmBoardReadByte';
    function AxmBoardWriteWord; external dll_name name 'AxmBoardWriteWord';
    function AxmBoardReadWord; external dll_name name 'AxmBoardReadWord';
    function AxmBoardWriteDWord; external dll_name name 'AxmBoardWriteDWord';
    function AxmBoardReadDWord; external dll_name name 'AxmBoardReadDWord';
    function AxmModuleWriteByte; external dll_name name 'AxmModuleWriteByte';
    function AxmModuleReadByte; external dll_name name 'AxmModuleReadByte';
    function AxmModuleWriteWord; external dll_name name 'AxmModuleWriteWord';
    function AxmModuleReadWord; external dll_name name 'AxmModuleReadWord';
    function AxmModuleWriteDWord; external dll_name name 'AxmModuleWriteDWord';
    function AxmModuleReadDWord; external dll_name name 'AxmModuleReadDWord';
    function AxmStatusSetActComparatorPos; external dll_name name 'AxmStatusSetActComparatorPos';
    function AxmStatusGetActComparatorPos; external dll_name name 'AxmStatusGetActComparatorPos';
    function AxmStatusSetCmdComparatorPos; external dll_name name 'AxmStatusSetCmdComparatorPos';
    function AxmStatusGetCmdComparatorPos; external dll_name name 'AxmStatusGetCmdComparatorPos';
    function AxmLineMoveVel; external dll_name name 'AxmLineMoveVel';
    function AxmSensorSetSignal; external dll_name name 'AxmSensorSetSignal';
    function AxmSensorGetSignal; external dll_name name 'AxmSensorGetSignal';
    function AxmSensorReadSignal; external dll_name name 'AxmSensorReadSignal';
    function AxmSensorMovePos; external dll_name name 'AxmSensorMovePos';
    function AxmSensorStartMovePos; external dll_name name 'AxmSensorStartMovePos';
    function AxmHomeGetStepTrace; external dll_name name 'AxmHomeGetStepTrace';
    function AxmHomeSetConfig; external dll_name name 'AxmHomeSetConfig';
    function AxmHomeGetConfig; external dll_name name 'AxmHomeGetConfig';
    function AxmHomeSetMoveSearch; external dll_name name 'AxmHomeSetMoveSearch';
    function AxmHomeSetMoveReturn; external dll_name name 'AxmHomeSetMoveReturn';
    function AxmHomeSetMoveLeave; external dll_name name 'AxmHomeSetMoveLeave';
    function AxmHomeSetMultiMoveSearch; external dll_name name 'AxmHomeSetMultiMoveSearch';
    function AxmContiSetProfileMode; external dll_name name 'AxmContiSetProfileMode';
    function AxmContiGetProfileMode; external dll_name name 'AxmContiGetProfileMode';
    function AxdiInterruptFlagReadBit; external dll_name name 'AxdiInterruptFlagReadBit';
    function AxdiInterruptFlagReadByte; external dll_name name 'AxdiInterruptFlagReadByte';
    function AxdiInterruptFlagReadWord; external dll_name name 'AxdiInterruptFlagReadWord';
    function AxdiInterruptFlagReadDword; external dll_name name 'AxdiInterruptFlagReadDword';
    function AxdiInterruptFlagRead; external dll_name name 'AxdiInterruptFlagRead';
    function AxmLogSetAxis; external dll_name name 'AxmLogSetAxis';
    function AxmLogGetAxis; external dll_name name 'AxmLogGetAxis';
    function AxaiLogSetChannel; external dll_name name 'AxaiLogSetChannel';
    function AxaiLogGetChannel; external dll_name name 'AxaiLogGetChannel';
    function AxaoLogSetChannel; external dll_name name 'AxaoLogSetChannel';
    function AxaoLogGetChannel; external dll_name name 'AxaoLogGetChannel';
    function AxdLogSetModule; external dll_name name 'AxdLogSetModule';
    function AxdLogGetModule; external dll_name name 'AxdLogGetModule';
    function AxlGetFirmwareVersion; external dll_name name 'AxlGetFirmwareVersion';
    function AxlSetFirmwareCopy; external dll_name name 'AxlSetFirmwareCopy';
    function AxlSetFirmwareUpdate; external dll_name name 'AxlSetFirmwareUpdate';
    function AxlCheckStatus; external dll_name name 'AxlCheckStatus';
    function AxlRtexUniversalCmd; external dll_name name 'AxlRtexUniversalCmd';
    function AxmRtexSlaveCmd; external dll_name name 'AxmRtexSlaveCmd';
    function AxmRtexGetSlaveCmdResult; external dll_name name 'AxmRtexGetSlaveCmdResult';
    function AxmRtexGetSlaveCmdResultEx; external dll_name name 'AxmRtexGetSlaveCmdResultEx';
    function AxmRtexGetAxisStatus; external dll_name name 'AxmRtexGetAxisStatus';
    function AxmRtexGetAxisReturnData; external dll_name name 'AxmRtexGetAxisReturnData';
    function AxmRtexGetAxisSlaveStatus; external dll_name name 'AxmRtexGetAxisSlaveStatus';
    function AxmSetAxisCmd; external dll_name name 'AxmSetAxisCmd';
    function AxmGetAxisCmdResult; external dll_name name 'AxmGetAxisCmdResult';
    function AxdSetAndGetSlaveCmdResult; external dll_name name 'AxdSetAndGetSlaveCmdResult';
    function AxaSetAndGetSlaveCmdResult; external dll_name name 'AxaSetAndGetSlaveCmdResult';
    function AxcSetAndGetSlaveCmdResult; external dll_name name 'AxcSetAndGetSlaveCmdResult';
    function AxlGetDpRamData; external dll_name name 'AxlGetDpRamData';
    function AxlBoardReadDpramWord; external dll_name name 'AxlBoardReadDpramWord';
    function AxlBoardWriteDpramWord; external dll_name name 'AxlBoardWriteDpramWord';
    function AxlSetSendBoardEachCommand; external dll_name name 'AxlSetSendBoardEachCommand';
    function AxlSetSendBoardCommand; external dll_name name 'AxlSetSendBoardCommand';
    function AxlGetResponseBoardCommand; external dll_name name 'AxlGetResponseBoardCommand';
    function AxmInfoGetFirmwareVersion; external dll_name name 'AxmInfoGetFirmwareVersion';
    function AxaInfoGetFirmwareVersion; external dll_name name 'AxaInfoGetFirmwareVersion';
    function AxdInfoGetFirmwareVersion; external dll_name name 'AxdInfoGetFirmwareVersion';
    function AxcInfoGetFirmwareVersion; external dll_name name 'AxcInfoGetFirmwareVersion';
    function AxmSetTorqFeedForward; external dll_name name 'AxmSetTorqFeedForward';
    function AxmGetTorqFeedForward; external dll_name name 'AxmGetTorqFeedForward';
    function AxmSetVelocityFeedForward; external dll_name name 'AxmSetVelocityFeedForward';
    function AxmGetVelocityFeedForward; external dll_name name 'AxmGetVelocityFeedForward';
    function AxmSignalSetEncoderType; external dll_name name 'AxmSignalSetEncoderType';
    function AxmSignalGetEncoderType; external dll_name name 'AxmSignalGetEncoderType';
    function AxmMotSetUserMotion; external dll_name name 'AxmMotSetUserMotion';
    function AxmMotSetUserMotionUsage; external dll_name name 'AxmMotSetUserMotionUsage';
    function AxmMotSetUserPosMotion; external dll_name name 'AxmMotSetUserPosMotion';
    function AxmMotSetUserPosMotionUsage; external dll_name name 'AxmMotSetUserPosMotionUsage';
    function AxcKeWriteRamDataAddr; external dll_name name 'AxcKeWriteRamDataAddr';
    function AxcKeReadRamDataAddr; external dll_name name 'AxcKeReadRamDataAddr';
    function AxcKeResetRamDataAll; external dll_name name 'AxcKeResetRamDataAll';
    function AxcTriggerSetTimeout; external dll_name name 'AxcTriggerSetTimeout';
    function AxcTriggerGetTimeout; external dll_name name 'AxcTriggerGetTimeout';
    function AxcStatusGetWaitState; external dll_name name 'AxcStatusGetWaitState';
    function AxcStatusSetWaitState; external dll_name name 'AxcStatusSetWaitState';
    function AxcKeSetCommandData32; external dll_name name 'AxcKeSetCommandData32';
    function AxcKeSetCommandData16; external dll_name name 'AxcKeSetCommandData16';
    function AxcKeGetCommandData32; external dll_name name 'AxcKeGetCommandData32';
    function AxcKeGetCommandData16; external dll_name name 'AxcKeGetCommandData16';
    function AxmSeqSetAxisMap; external dll_name name 'AxmSeqSetAxisMap';
    function AxmSeqGetAxisMap; external dll_name name 'AxmSeqGetAxisMap';
    function AxmSeqSetMasterAxisNo; external dll_name name 'AxmSeqSetMasterAxisNo';
    function AxmSeqBeginNode; external dll_name name 'AxmSeqBeginNode';
    function AxmSeqEndNode; external dll_name name 'AxmSeqEndNode';
    function AxmSeqStart; external dll_name name 'AxmSeqStart';
    function AxmSeqAddNode; external dll_name name 'AxmSeqAddNode';
    function AxmSeqGetNodeNum; external dll_name name 'AxmSeqGetNodeNum';
    function AxmSeqGetTotalNodeNum; external dll_name name 'AxmSeqGetTotalNodeNum';
    function AxmSeqIsMotion; external dll_name name 'AxmSeqIsMotion';
    function AxmSeqWriteClear; external dll_name name 'AxmSeqWriteClear';
    function AxmSeqStop; external dll_name name 'AxmSeqStop';
    function AxmStatusSetMon; external dll_name name 'AxmStatusSetMon';
    function AxmStatusGetMon; external dll_name name 'AxmStatusGetMon';
    function AxmStatusReadMon; external dll_name name 'AxmStatusReadMon';
    function AxmStatusReadMonEx; external dll_name name 'AxmStatusReadMonEx';
    function AxlSetIoPort; external dll_name name 'AxlSetIoPort';
    function AxlGetIoPort; external dll_name name 'AxlGetIoPort';
    function AxlM3SetFWUpdateInit; external dll_name name 'AxlM3SetFWUpdateInit';
    function AxlM3GetFWUpdateInit; external dll_name name 'AxlM3GetFWUpdateInit';
    function AxlM3SetFWUpdateCopy; external dll_name name 'AxlM3SetFWUpdateCopy';
    function AxlM3GetFWUpdateCopy; external dll_name name 'AxlM3GetFWUpdateCopy';
    function AxlM3SetFWUpdate; external dll_name name 'AxlM3SetFWUpdate';
    function AxlM3GetFWUpdate; external dll_name name 'AxlM3GetFWUpdate';
    function AxlM3SetCFGData; external dll_name name 'AxlM3SetCFGData';
    function AxlM3GetCFGData; external dll_name name 'AxlM3GetCFGData';
    function AxlM3SetMCParaUpdateInit; external dll_name name 'AxlM3SetMCParaUpdateInit';
    function AxlM3GetMCParaUpdateInit; external dll_name name 'AxlM3GetMCParaUpdateInit';
    function AxlM3SetMCParaUpdateCopy; external dll_name name 'AxlM3SetMCParaUpdateCopy';
    function AxlM3GetMCParaUpdateCopy; external dll_name name 'AxlM3GetMCParaUpdateCopy';
    function AxlBoardReadDWord; external dll_name name 'AxlBoardReadDWord';
    function AxlBoardWriteDWord; external dll_name name 'AxlBoardWriteDWord';
    function AxlBoardReadDWordEx; external dll_name name 'AxlBoardReadDWordEx';
    function AxlBoardWriteDWordEx; external dll_name name 'AxlBoardWriteDWordEx';
    function AxmM3ServoSetCtrlStopMode; external dll_name name 'AxmM3ServoSetCtrlStopMode';
    function AxmM3ServoSetCtrlLtSel; external dll_name name 'AxmM3ServoSetCtrlLtSel';
    function AxmStatusReadServoCmdIOInput; external dll_name name 'AxmStatusReadServoCmdIOInput';
    function AxmM3ServoExInterpolate; external dll_name name 'AxmM3ServoExInterpolate';
    function AxmM3ServoSetExpoAccBias; external dll_name name 'AxmM3ServoSetExpoAccBias';
    function AxmM3ServoSetExpoAccTime; external dll_name name 'AxmM3ServoSetExpoAccTime';
    function AxmM3ServoSetMoveAvrTime; external dll_name name 'AxmM3ServoSetMoveAvrTime';
    function AxmM3ServoSetAccFilter; external dll_name name 'AxmM3ServoSetAccFilter';
    function AxmM3ServoSetCprmMonitor1; external dll_name name 'AxmM3ServoSetCprmMonitor1';
    function AxmM3ServoSetCprmMonitor2; external dll_name name 'AxmM3ServoSetCprmMonitor2';
    function AxmM3ServoStatusReadCprmMonitor1; external dll_name name 'AxmM3ServoStatusReadCprmMonitor1';
    function AxmM3ServoStatusReadCprmMonitor2; external dll_name name 'AxmM3ServoStatusReadCprmMonitor2';
    function AxmM3ServoSetAccDec; external dll_name name 'AxmM3ServoSetAccDec';
    function AxmM3ServoSetStop; external dll_name name 'AxmM3ServoSetStop';
    function AxlM3GetStationParameter; external dll_name name 'AxlM3GetStationParameter';
    function AxlM3SetStationParameter; external dll_name name 'AxlM3SetStationParameter';
    function AxlM3GetStationIdRd; external dll_name name 'AxlM3GetStationIdRd';
    function AxlM3SetStationNop; external dll_name name 'AxlM3SetStationNop';
    function AxlM3SetStationConfig; external dll_name name 'AxlM3SetStationConfig';
    function AxlM3GetStationAlarm; external dll_name name 'AxlM3GetStationAlarm';
    function AxlM3SetStationAlarmClear; external dll_name name 'AxlM3SetStationAlarmClear';
    function AxlM3SetStationSyncSet; external dll_name name 'AxlM3SetStationSyncSet';
    function AxlM3SetStationConnect; external dll_name name 'AxlM3SetStationConnect';
    function AxlM3SetStationDisConnect; external dll_name name 'AxlM3SetStationDisConnect';
    function AxlM3GetStationStoredParameter; external dll_name name 'AxlM3GetStationStoredParameter';
    function AxlM3SetStationStoredParameter; external dll_name name 'AxlM3SetStationStoredParameter';
    function AxlM3GetStationMemory; external dll_name name 'AxlM3GetStationMemory';
    function AxlM3SetStationMemory; external dll_name name 'AxlM3SetStationMemory';
    function AxlM3SetStationAccessMode; external dll_name name 'AxlM3SetStationAccessMode';
    function AxlM3GetStationAccessMode; external dll_name name 'AxlM3GetStationAccessMode';
    function AxlM3SetAutoSyncConnectMode; external dll_name name 'AxlM3SetAutoSyncConnectMode';
    function AxlM3GetAutoSyncConnectMode; external dll_name name 'AxlM3GetAutoSyncConnectMode';
    function AxlM3SyncConnectSingle; external dll_name name 'AxlM3SyncConnectSingle';
    function AxlM3SyncDisconnectSingle; external dll_name name 'AxlM3SyncDisconnectSingle';
    function AxlM3IsOnLine; external dll_name name 'AxlM3IsOnLine';
    function AxlM3GetStationRWS; external dll_name name 'AxlM3GetStationRWS';
    function AxlM3SetStationRWS; external dll_name name 'AxlM3SetStationRWS';
    function AxlM3GetStationRWA; external dll_name name 'AxlM3GetStationRWA';
    function AxlM3SetStationRWA; external dll_name name 'AxlM3SetStationRWA';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmHomeGetM3FWRealRate; external dll_name name 'AxmHomeGetM3FWRealRate';
    function AxmHomeGetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeGetM3OffsetAvoideSenArea';
    function AxmHomeSetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeSetM3OffsetAvoideSenArea';
    function AxmM3SetAbsEncOrgResetDisable; external dll_name name 'AxmM3SetAbsEncOrgResetDisable';
    function AxmM3GetAbsEncOrgResetDisable; external dll_name name 'AxmM3GetAbsEncOrgResetDisable';
    function AxmM3SetOfflineAlarmEnable; external dll_name name 'AxmM3SetOfflineAlarmEnable';
    function AxmM3GetOfflineAlarmEnable; external dll_name name 'AxmM3GetOfflineAlarmEnable';
    function AxmM3ReadOnlineToOfflineStatus; external dll_name name 'AxmM3ReadOnlineToOfflineStatus';
    function AxlECatGetProductInfo; external dll_name name 'AxlECatGetProductInfo';
    function AxlECatGetModuleStatus; external dll_name name 'AxlECatGetModuleStatus';
    function AxlECatReadPdoInput; external dll_name name 'AxlECatReadPdoInput';
    function AxlECatReadPdoOutput; external dll_name name 'AxlECatReadPdoOutput';
    function AxlECatWritePdoOutput; external dll_name name 'AxlECatWritePdoOutput';
    function AxlECatReadSdo; external dll_name name 'AxlECatReadSdo';
    function AxlECatWriteSdo; external dll_name name 'AxlECatWriteSdo';
    function AxlECatReadSdoFromAxisDword; external dll_name name 'AxlECatReadSdoFromAxisDword';
    function AxlECatWriteSdoFromAxisDword; external dll_name name 'AxlECatWriteSdoFromAxisDword';
    function AxlECatReadSdoFromAxisWord; external dll_name name 'AxlECatReadSdoFromAxisWord';
    function AxlECatWriteSdoFromAxisWord; external dll_name name 'AxlECatWriteSdoFromAxisWord';
    function AxlECatReadSdoFromAxisByte; external dll_name name 'AxlECatReadSdoFromAxisByte';
    function AxlECatWriteSdoFromAxisByte; external dll_name name 'AxlECatWriteSdoFromAxisByte';
    function AxlECatReadEEPRom; external dll_name name 'AxlECatReadEEPRom';
    function AxlECatWriteEEPRom; external dll_name name 'AxlECatWriteEEPRom';
    function AxlECatReadRegister; external dll_name name 'AxlECatReadRegister';
    function AxlECatWriteRegister; external dll_name name 'AxlECatWriteRegister';
    function AxlECatSaveHotSwapData; external dll_name name 'AxlECatSaveHotSwapData';
    function AxlECatLoadHotSwapData; external dll_name name 'AxlECatLoadHotSwapData';
    function AxlECatSetHotSwap; external dll_name name 'AxlECatSetHotSwap';
    function AxlECatIsSetHotSwap; external dll_name name 'AxlECatIsSetHotSwap';
    function AxlECatReSetHotSwap; external dll_name name 'AxlECatReSetHotSwap';
    function AxlECatSetMasterMode; external dll_name name 'AxlECatSetMasterMode';
    function AxlECatGetMasterMode; external dll_name name 'AxlECatGetMasterMode';
    function AxlECatSetMasterOperationMode; external dll_name name 'AxlECatSetMasterOperationMode';
    function AxlECatGetMasterOperationMode; external dll_name name 'AxlECatGetMasterOperationMode';
    function AxlECatRequestScanData; external dll_name name 'AxlECatRequestScanData';
    function AxlECatGetScanSlaveCount; external dll_name name 'AxlECatGetScanSlaveCount';
    function AxlECatGetStatus; external dll_name name 'AxlECatGetStatus';
    function AxlEcatReConnect; external dll_name name 'AxlEcatReConnect';
    function AxmECatReadAddress; external dll_name name 'AxmECatReadAddress';
    function AxdECatReadAddress; external dll_name name 'AxdECatReadAddress';
    function AxaECatReadAddress; external dll_name name 'AxaECatReadAddress';
    function AxlMonitorSetItem; external dll_name name 'AxlMonitorSetItem';
    function AxlMonitorGetIndexInfo; external dll_name name 'AxlMonitorGetIndexInfo';
    function AxlMonitorGetItemInfo; external dll_name name 'AxlMonitorGetItemInfo';
    function AxlMonitorResetAllItem; external dll_name name 'AxlMonitorResetAllItem';
    function AxlMonitorResetItem; external dll_name name 'AxlMonitorResetItem';
    function AxlMonitorSetTriggerOption; external dll_name name 'AxlMonitorSetTriggerOption';
    function AxlMonitorResetTriggerOption; external dll_name name 'AxlMonitorResetTriggerOption';
    function AxlMonitorStart; external dll_name name 'AxlMonitorStart';
    function AxlMonitorStop; external dll_name name 'AxlMonitorStop';
    function AxlMonitorReadData; external dll_name name 'AxlMonitorReadData';
    function AxlMonitorReadPeriod; external dll_name name 'AxlMonitorReadPeriod';
    function AxlMonitorExSetItem; external dll_name name 'AxlMonitorExSetItem';
    function AxlMonitorExGetIndexInfo; external dll_name name 'AxlMonitorExGetIndexInfo';
    function AxlMonitorExGetItemInfo; external dll_name name 'AxlMonitorExGetItemInfo';
    function AxlMonitorExResetAllItem; external dll_name name 'AxlMonitorExResetAllItem';
    function AxlMonitorExResetItem; external dll_name name 'AxlMonitorExResetItem';
    function AxlMonitorExSetTriggerOption; external dll_name name 'AxlMonitorExSetTriggerOption';
    function AxlMonitorExResetTriggerOption; external dll_name name 'AxlMonitorExResetTriggerOption';
    function AxlMonitorExStart; external dll_name name 'AxlMonitorExStart';
    function AxlMonitorExStop; external dll_name name 'AxlMonitorExStop';
    function AxlMonitorExReadData; external dll_name name 'AxlMonitorExReadData';
    function AxlMonitorExReadPeriod; external dll_name name 'AxlMonitorExReadPeriod';
    function AxmLineMoveDual01; external dll_name name 'AxmLineMoveDual01';
    function AxmCircleCenterMoveDual01; external dll_name name 'AxmCircleCenterMoveDual01';
    function AxdSetFirmwareUpdateInfo; external dll_name name 'AxdSetFirmwareUpdateInfo';
    function AxdSetFirmwareDataTrans; external dll_name name 'AxdSetFirmwareDataTrans';
    function AxdSetFirmwareUpdate; external dll_name name 'AxdSetFirmwareUpdate';
    function AxaSetFirmwareUpdateInfo; external dll_name name 'AxaSetFirmwareUpdateInfo';
    function AxaSetFirmwareDataTrans; external dll_name name 'AxaSetFirmwareDataTrans';
    function AxaSetFirmwareUpdate; external dll_name name 'AxaSetFirmwareUpdate';
    function AxmSetFirmwareUpdateInfo; external dll_name name 'AxmSetFirmwareUpdateInfo';
    function AxmSetFirmwareDataTrans; external dll_name name 'AxmSetFirmwareDataTrans';
    function AxmSetFirmwareUpdate; external dll_name name 'AxmSetFirmwareUpdate';
    function AxmMotSetOperationMode; external dll_name name 'AxmMotSetOperationMode';
    function AxmMotGetOperationMode; external dll_name name 'AxmMotGetOperationMode';
    function AxmLineMoveVel; external dll_name name 'AxmLineMoveVel';
    function AxmSensorSetSignal; external dll_name name 'AxmSensorSetSignal';
    function AxmSensorGetSignal; external dll_name name 'AxmSensorGetSignal';
    function AxmSensorReadSignal; external dll_name name 'AxmSensorReadSignal';
    function AxmSensorMovePos; external dll_name name 'AxmSensorMovePos';
    function AxmSensorStartMovePos; external dll_name name 'AxmSensorStartMovePos';
    function AxmHomeGetStepTrace; external dll_name name 'AxmHomeGetStepTrace';
    function AxmHomeSetConfig; external dll_name name 'AxmHomeSetConfig';
    function AxmHomeGetConfig; external dll_name name 'AxmHomeGetConfig';
    function AxmHomeSetMoveSearch; external dll_name name 'AxmHomeSetMoveSearch';
    function AxmHomeSetMoveReturn; external dll_name name 'AxmHomeSetMoveReturn';
    function AxmHomeSetMoveLeave; external dll_name name 'AxmHomeSetMoveLeave';
    function AxmHomeSetMultiMoveSearch; external dll_name name 'AxmHomeSetMultiMoveSearch';
    function AxmContiSetProfileMode; external dll_name name 'AxmContiSetProfileMode';
    function AxmContiGetProfileMode; external dll_name name 'AxmContiGetProfileMode';
    function AxdiInterruptFlagReadBit; external dll_name name 'AxdiInterruptFlagReadBit';
    function AxdiInterruptFlagReadByte; external dll_name name 'AxdiInterruptFlagReadByte';
    function AxdiInterruptFlagReadWord; external dll_name name 'AxdiInterruptFlagReadWord';
    function AxdiInterruptFlagReadDword; external dll_name name 'AxdiInterruptFlagReadDword';
    function AxdiInterruptFlagRead; external dll_name name 'AxdiInterruptFlagRead';
    function AxmLogSetAxis; external dll_name name 'AxmLogSetAxis';
    function AxmLogGetAxis; external dll_name name 'AxmLogGetAxis';
    function AxaiLogSetChannel; external dll_name name 'AxaiLogSetChannel';
    function AxaiLogGetChannel; external dll_name name 'AxaiLogGetChannel';
    function AxaoLogSetChannel; external dll_name name 'AxaoLogSetChannel';
    function AxaoLogGetChannel; external dll_name name 'AxaoLogGetChannel';
    function AxdLogSetModule; external dll_name name 'AxdLogSetModule';
    function AxdLogGetModule; external dll_name name 'AxdLogGetModule';
    function AxlGetFirmwareVersion; external dll_name name 'AxlGetFirmwareVersion';
    function AxlSetFirmwareCopy; external dll_name name 'AxlSetFirmwareCopy';
    function AxlSetFirmwareUpdate; external dll_name name 'AxlSetFirmwareUpdate';
    function AxlCheckStatus; external dll_name name 'AxlCheckStatus';
    function AxlRtexUniversalCmd; external dll_name name 'AxlRtexUniversalCmd';
    function AxmRtexSlaveCmd; external dll_name name 'AxmRtexSlaveCmd';
    function AxmRtexGetSlaveCmdResult; external dll_name name 'AxmRtexGetSlaveCmdResult';
    function AxmRtexGetSlaveCmdResultEx; external dll_name name 'AxmRtexGetSlaveCmdResultEx';
    function AxmRtexGetAxisStatus; external dll_name name 'AxmRtexGetAxisStatus';
    function AxmRtexGetAxisReturnData; external dll_name name 'AxmRtexGetAxisReturnData';
    function AxmRtexGetAxisSlaveStatus; external dll_name name 'AxmRtexGetAxisSlaveStatus';
    function AxmSetAxisCmd; external dll_name name 'AxmSetAxisCmd';
    function AxmGetAxisCmdResult; external dll_name name 'AxmGetAxisCmdResult';
    function AxdSetAndGetSlaveCmdResult; external dll_name name 'AxdSetAndGetSlaveCmdResult';
    function AxaSetAndGetSlaveCmdResult; external dll_name name 'AxaSetAndGetSlaveCmdResult';
    function AxcSetAndGetSlaveCmdResult; external dll_name name 'AxcSetAndGetSlaveCmdResult';
    function AxlGetDpRamData; external dll_name name 'AxlGetDpRamData';
    function AxlBoardReadDpramWord; external dll_name name 'AxlBoardReadDpramWord';
    function AxlBoardWriteDpramWord; external dll_name name 'AxlBoardWriteDpramWord';
    function AxlSetSendBoardEachCommand; external dll_name name 'AxlSetSendBoardEachCommand';
    function AxlSetSendBoardCommand; external dll_name name 'AxlSetSendBoardCommand';
    function AxlGetResponseBoardCommand; external dll_name name 'AxlGetResponseBoardCommand';
    function AxmInfoGetFirmwareVersion; external dll_name name 'AxmInfoGetFirmwareVersion';
    function AxaInfoGetFirmwareVersion; external dll_name name 'AxaInfoGetFirmwareVersion';
    function AxdInfoGetFirmwareVersion; external dll_name name 'AxdInfoGetFirmwareVersion';
    function AxcInfoGetFirmwareVersion; external dll_name name 'AxcInfoGetFirmwareVersion';
    function AxmSetTorqFeedForward; external dll_name name 'AxmSetTorqFeedForward';
    function AxmGetTorqFeedForward; external dll_name name 'AxmGetTorqFeedForward';
    function AxmSetVelocityFeedForward; external dll_name name 'AxmSetVelocityFeedForward';
    function AxmGetVelocityFeedForward; external dll_name name 'AxmGetVelocityFeedForward';
    function AxmSignalSetEncoderType; external dll_name name 'AxmSignalSetEncoderType';
    function AxmSignalGetEncoderType; external dll_name name 'AxmSignalGetEncoderType';
    function AxmMotSetUserMotion; external dll_name name 'AxmMotSetUserMotion';
    function AxmMotSetUserMotionUsage; external dll_name name 'AxmMotSetUserMotionUsage';
    function AxmMotSetUserPosMotion; external dll_name name 'AxmMotSetUserPosMotion';
    function AxmMotSetUserPosMotionUsage; external dll_name name 'AxmMotSetUserPosMotionUsage';
    function AxcKeWriteRamDataAddr; external dll_name name 'AxcKeWriteRamDataAddr';
    function AxcKeReadRamDataAddr; external dll_name name 'AxcKeReadRamDataAddr';
    function AxcKeResetRamDataAll; external dll_name name 'AxcKeResetRamDataAll';
    function AxcTriggerSetTimeout; external dll_name name 'AxcTriggerSetTimeout';
    function AxcTriggerGetTimeout; external dll_name name 'AxcTriggerGetTimeout';
    function AxcStatusGetWaitState; external dll_name name 'AxcStatusGetWaitState';
    function AxcStatusSetWaitState; external dll_name name 'AxcStatusSetWaitState';
    function AxcKeSetCommandData32; external dll_name name 'AxcKeSetCommandData32';
    function AxcKeSetCommandData16; external dll_name name 'AxcKeSetCommandData16';
    function AxcKeGetCommandData32; external dll_name name 'AxcKeGetCommandData32';
    function AxcKeGetCommandData16; external dll_name name 'AxcKeGetCommandData16';
    function AxmSeqSetAxisMap; external dll_name name 'AxmSeqSetAxisMap';
    function AxmSeqGetAxisMap; external dll_name name 'AxmSeqGetAxisMap';
    function AxmSeqSetMasterAxisNo; external dll_name name 'AxmSeqSetMasterAxisNo';
    function AxmSeqBeginNode; external dll_name name 'AxmSeqBeginNode';
    function AxmSeqEndNode; external dll_name name 'AxmSeqEndNode';
    function AxmSeqStart; external dll_name name 'AxmSeqStart';
    function AxmSeqAddNode; external dll_name name 'AxmSeqAddNode';
    function AxmSeqGetNodeNum; external dll_name name 'AxmSeqGetNodeNum';
    function AxmSeqGetTotalNodeNum; external dll_name name 'AxmSeqGetTotalNodeNum';
    function AxmSeqIsMotion; external dll_name name 'AxmSeqIsMotion';
    function AxmSeqWriteClear; external dll_name name 'AxmSeqWriteClear';
    function AxmSeqStop; external dll_name name 'AxmSeqStop';
    function AxmStatusSetMon; external dll_name name 'AxmStatusSetMon';
    function AxmStatusGetMon; external dll_name name 'AxmStatusGetMon';
    function AxmStatusReadMon; external dll_name name 'AxmStatusReadMon';
    function AxmStatusReadMonEx; external dll_name name 'AxmStatusReadMonEx';
    function AxlSetIoPort; external dll_name name 'AxlSetIoPort';
    function AxlGetIoPort; external dll_name name 'AxlGetIoPort';
    function AxlM3SetFWUpdateInit; external dll_name name 'AxlM3SetFWUpdateInit';
    function AxlM3GetFWUpdateInit; external dll_name name 'AxlM3GetFWUpdateInit';
    function AxlM3SetFWUpdateCopy; external dll_name name 'AxlM3SetFWUpdateCopy';
    function AxlM3GetFWUpdateCopy; external dll_name name 'AxlM3GetFWUpdateCopy';
    function AxlM3SetFWUpdate; external dll_name name 'AxlM3SetFWUpdate';
    function AxlM3GetFWUpdate; external dll_name name 'AxlM3GetFWUpdate';
    function AxlM3SetCFGData; external dll_name name 'AxlM3SetCFGData';
    function AxlM3GetCFGData; external dll_name name 'AxlM3GetCFGData';
    function AxlM3SetMCParaUpdateInit; external dll_name name 'AxlM3SetMCParaUpdateInit';
    function AxlM3GetMCParaUpdateInit; external dll_name name 'AxlM3GetMCParaUpdateInit';
    function AxlM3SetMCParaUpdateCopy; external dll_name name 'AxlM3SetMCParaUpdateCopy';
    function AxlM3GetMCParaUpdateCopy; external dll_name name 'AxlM3GetMCParaUpdateCopy';
    function AxlBoardReadDWord; external dll_name name 'AxlBoardReadDWord';
    function AxlBoardWriteDWord; external dll_name name 'AxlBoardWriteDWord';
    function AxlBoardReadDWordEx; external dll_name name 'AxlBoardReadDWordEx';
    function AxlBoardWriteDWordEx; external dll_name name 'AxlBoardWriteDWordEx';
    function AxmM3ServoSetCtrlStopMode; external dll_name name 'AxmM3ServoSetCtrlStopMode';
    function AxmM3ServoSetCtrlLtSel; external dll_name name 'AxmM3ServoSetCtrlLtSel';
    function AxmStatusReadServoCmdIOInput; external dll_name name 'AxmStatusReadServoCmdIOInput';
    function AxmM3ServoExInterpolate; external dll_name name 'AxmM3ServoExInterpolate';
    function AxmM3ServoSetExpoAccBias; external dll_name name 'AxmM3ServoSetExpoAccBias';
    function AxmM3ServoSetExpoAccTime; external dll_name name 'AxmM3ServoSetExpoAccTime';
    function AxmM3ServoSetMoveAvrTime; external dll_name name 'AxmM3ServoSetMoveAvrTime';
    function AxmM3ServoSetAccFilter; external dll_name name 'AxmM3ServoSetAccFilter';
    function AxmM3ServoSetCprmMonitor1; external dll_name name 'AxmM3ServoSetCprmMonitor1';
    function AxmM3ServoSetCprmMonitor2; external dll_name name 'AxmM3ServoSetCprmMonitor2';
    function AxmM3ServoStatusReadCprmMonitor1; external dll_name name 'AxmM3ServoStatusReadCprmMonitor1';
    function AxmM3ServoStatusReadCprmMonitor2; external dll_name name 'AxmM3ServoStatusReadCprmMonitor2';
    function AxmM3ServoSetAccDec; external dll_name name 'AxmM3ServoSetAccDec';
    function AxmM3ServoSetStop; external dll_name name 'AxmM3ServoSetStop';
    function AxlM3GetStationParameter; external dll_name name 'AxlM3GetStationParameter';
    function AxlM3SetStationParameter; external dll_name name 'AxlM3SetStationParameter';
    function AxlM3GetStationIdRd; external dll_name name 'AxlM3GetStationIdRd';
    function AxlM3SetStationNop; external dll_name name 'AxlM3SetStationNop';
    function AxlM3SetStationConfig; external dll_name name 'AxlM3SetStationConfig';
    function AxlM3GetStationAlarm; external dll_name name 'AxlM3GetStationAlarm';
    function AxlM3SetStationAlarmClear; external dll_name name 'AxlM3SetStationAlarmClear';
    function AxlM3SetStationSyncSet; external dll_name name 'AxlM3SetStationSyncSet';
    function AxlM3SetStationConnect; external dll_name name 'AxlM3SetStationConnect';
    function AxlM3SetStationDisConnect; external dll_name name 'AxlM3SetStationDisConnect';
    function AxlM3GetStationStoredParameter; external dll_name name 'AxlM3GetStationStoredParameter';
    function AxlM3SetStationStoredParameter; external dll_name name 'AxlM3SetStationStoredParameter';
    function AxlM3GetStationMemory; external dll_name name 'AxlM3GetStationMemory';
    function AxlM3SetStationMemory; external dll_name name 'AxlM3SetStationMemory';
    function AxlM3SetStationAccessMode; external dll_name name 'AxlM3SetStationAccessMode';
    function AxlM3GetStationAccessMode; external dll_name name 'AxlM3GetStationAccessMode';
    function AxlM3SetAutoSyncConnectMode; external dll_name name 'AxlM3SetAutoSyncConnectMode';
    function AxlM3GetAutoSyncConnectMode; external dll_name name 'AxlM3GetAutoSyncConnectMode';
    function AxlM3SyncConnectSingle; external dll_name name 'AxlM3SyncConnectSingle';
    function AxlM3SyncDisconnectSingle; external dll_name name 'AxlM3SyncDisconnectSingle';
    function AxlM3IsOnLine; external dll_name name 'AxlM3IsOnLine';
    function AxlM3GetStationRWS; external dll_name name 'AxlM3GetStationRWS';
    function AxlM3SetStationRWS; external dll_name name 'AxlM3SetStationRWS';
    function AxlM3GetStationRWA; external dll_name name 'AxlM3GetStationRWA';
    function AxlM3SetStationRWA; external dll_name name 'AxlM3SetStationRWA';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmHomeGetM3FWRealRate; external dll_name name 'AxmHomeGetM3FWRealRate';
    function AxmHomeGetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeGetM3OffsetAvoideSenArea';
    function AxmHomeSetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeSetM3OffsetAvoideSenArea';
    function AxmM3SetAbsEncOrgResetDisable; external dll_name name 'AxmM3SetAbsEncOrgResetDisable';
    function AxmM3GetAbsEncOrgResetDisable; external dll_name name 'AxmM3GetAbsEncOrgResetDisable';
    function AxmM3SetOfflineAlarmEnable; external dll_name name 'AxmM3SetOfflineAlarmEnable';
    function AxmM3GetOfflineAlarmEnable; external dll_name name 'AxmM3GetOfflineAlarmEnable';
    function AxmM3ReadOnlineToOfflineStatus; external dll_name name 'AxmM3ReadOnlineToOfflineStatus';
    function AxlECatGetProductInfo; external dll_name name 'AxlECatGetProductInfo';
    function AxlECatGetModuleStatus; external dll_name name 'AxlECatGetModuleStatus';
    function AxlECatReadPdoInput; external dll_name name 'AxlECatReadPdoInput';
    function AxlECatReadPdoOutput; external dll_name name 'AxlECatReadPdoOutput';
    function AxlECatWritePdoOutput; external dll_name name 'AxlECatWritePdoOutput';
    function AxlECatReadSdo; external dll_name name 'AxlECatReadSdo';
    function AxlECatWriteSdo; external dll_name name 'AxlECatWriteSdo';
    function AxlECatReadSdoFromAxisDword; external dll_name name 'AxlECatReadSdoFromAxisDword';
    function AxlECatWriteSdoFromAxisDword; external dll_name name 'AxlECatWriteSdoFromAxisDword';
    function AxlECatReadSdoFromAxisWord; external dll_name name 'AxlECatReadSdoFromAxisWord';
    function AxlECatWriteSdoFromAxisWord; external dll_name name 'AxlECatWriteSdoFromAxisWord';
    function AxlECatReadSdoFromAxisByte; external dll_name name 'AxlECatReadSdoFromAxisByte';
    function AxlECatWriteSdoFromAxisByte; external dll_name name 'AxlECatWriteSdoFromAxisByte';
    function AxlECatReadEEPRom; external dll_name name 'AxlECatReadEEPRom';
    function AxlECatWriteEEPRom; external dll_name name 'AxlECatWriteEEPRom';
    function AxlECatReadRegister; external dll_name name 'AxlECatReadRegister';
    function AxlECatWriteRegister; external dll_name name 'AxlECatWriteRegister';
    function AxlECatSaveHotSwapData; external dll_name name 'AxlECatSaveHotSwapData';
    function AxlECatLoadHotSwapData; external dll_name name 'AxlECatLoadHotSwapData';
    function AxlECatSetHotSwap; external dll_name name 'AxlECatSetHotSwap';
    function AxlECatIsSetHotSwap; external dll_name name 'AxlECatIsSetHotSwap';
    function AxlECatReSetHotSwap; external dll_name name 'AxlECatReSetHotSwap';
    function AxlECatSetMasterMode; external dll_name name 'AxlECatSetMasterMode';
    function AxlECatGetMasterMode; external dll_name name 'AxlECatGetMasterMode';
    function AxlECatSetMasterOperationMode; external dll_name name 'AxlECatSetMasterOperationMode';
    function AxlECatGetMasterOperationMode; external dll_name name 'AxlECatGetMasterOperationMode';
    function AxlECatRequestScanData; external dll_name name 'AxlECatRequestScanData';
    function AxlECatGetScanSlaveCount; external dll_name name 'AxlECatGetScanSlaveCount';
    function AxlECatGetStatus; external dll_name name 'AxlECatGetStatus';
    function AxlEcatReConnect; external dll_name name 'AxlEcatReConnect';
    function AxmECatReadAddress; external dll_name name 'AxmECatReadAddress';
    function AxdECatReadAddress; external dll_name name 'AxdECatReadAddress';
    function AxaECatReadAddress; external dll_name name 'AxaECatReadAddress';
    function AxsECatReadAddress; external dll_name name 'AxsECatReadAddress';
    function AxlMonitorSetItem; external dll_name name 'AxlMonitorSetItem';
    function AxlMonitorGetIndexInfo; external dll_name name 'AxlMonitorGetIndexInfo';
    function AxlMonitorGetItemInfo; external dll_name name 'AxlMonitorGetItemInfo';
    function AxlMonitorResetAllItem; external dll_name name 'AxlMonitorResetAllItem';
    function AxlMonitorResetItem; external dll_name name 'AxlMonitorResetItem';
    function AxlMonitorSetTriggerOption; external dll_name name 'AxlMonitorSetTriggerOption';
    function AxlMonitorResetTriggerOption; external dll_name name 'AxlMonitorResetTriggerOption';
    function AxlMonitorStart; external dll_name name 'AxlMonitorStart';
    function AxlMonitorStop; external dll_name name 'AxlMonitorStop';
    function AxlMonitorReadData; external dll_name name 'AxlMonitorReadData';
    function AxlMonitorReadPeriod; external dll_name name 'AxlMonitorReadPeriod';
    function AxlMonitorExSetItem; external dll_name name 'AxlMonitorExSetItem';
    function AxlMonitorExGetIndexInfo; external dll_name name 'AxlMonitorExGetIndexInfo';
    function AxlMonitorExGetItemInfo; external dll_name name 'AxlMonitorExGetItemInfo';
    function AxlMonitorExResetAllItem; external dll_name name 'AxlMonitorExResetAllItem';
    function AxlMonitorExResetItem; external dll_name name 'AxlMonitorExResetItem';
    function AxlMonitorExSetTriggerOption; external dll_name name 'AxlMonitorExSetTriggerOption';
    function AxlMonitorExResetTriggerOption; external dll_name name 'AxlMonitorExResetTriggerOption';
    function AxlMonitorExStart; external dll_name name 'AxlMonitorExStart';
    function AxlMonitorExStop; external dll_name name 'AxlMonitorExStop';
    function AxlMonitorExReadData; external dll_name name 'AxlMonitorExReadData';
    function AxlMonitorExReadPeriod; external dll_name name 'AxlMonitorExReadPeriod';
    function AxmLineMoveDual01; external dll_name name 'AxmLineMoveDual01';
    function AxmCircleCenterMoveDual01; external dll_name name 'AxmCircleCenterMoveDual01';
    function AxdSetFirmwareUpdateInfo; external dll_name name 'AxdSetFirmwareUpdateInfo';
    function AxdSetFirmwareDataTrans; external dll_name name 'AxdSetFirmwareDataTrans';
    function AxdSetFirmwareUpdate; external dll_name name 'AxdSetFirmwareUpdate';
    function AxaSetFirmwareUpdateInfo; external dll_name name 'AxaSetFirmwareUpdateInfo';
    function AxaSetFirmwareDataTrans; external dll_name name 'AxaSetFirmwareDataTrans';
    function AxaSetFirmwareUpdate; external dll_name name 'AxaSetFirmwareUpdate';
    function AxmSetFirmwareUpdateInfo; external dll_name name 'AxmSetFirmwareUpdateInfo';
    function AxmSetFirmwareDataTrans; external dll_name name 'AxmSetFirmwareDataTrans';
    function AxmSetFirmwareUpdate; external dll_name name 'AxmSetFirmwareUpdate';
    function AxmMotSetOperationMode; external dll_name name 'AxmMotSetOperationMode';
    function AxmMotGetOperationMode; external dll_name name 'AxmMotGetOperationMode';
    function AxlGetBoardAddress; external dll_name name 'AxlGetBoardAddress';
    function AxlGetBoardID; external dll_name name 'AxlGetBoardID';
    function AxlGetBoardVersion; external dll_name name 'AxlGetBoardVersion';
    function AxlGetModuleID; external dll_name name 'AxlGetModuleID';
    function AxlGetModuleVersion; external dll_name name 'AxlGetModuleVersion';
    function AxlGetModuleNodeInfo; external dll_name name 'AxlGetModuleNodeInfo';
    function AxlSetDataFlash; external dll_name name 'AxlSetDataFlash';
    function AxlSetEStopInterLock; external dll_name name 'AxlSetEStopInterLock';
    function AxlGetEStopInterLock; external dll_name name 'AxlGetEStopInterLock';
    function AxlReadEStopInterLock; external dll_name name 'AxlReadEStopInterLock';
    function AxlGetDataFlash; external dll_name name 'AxlGetDataFlash';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxmSetCommand; external dll_name name 'AxmSetCommand';
    function AxmSetCommandData08; external dll_name name 'AxmSetCommandData08';
    function AxmGetCommandData08; external dll_name name 'AxmGetCommandData08';
    function AxmSetCommandData16; external dll_name name 'AxmSetCommandData16';
    function AxmGetCommandData16; external dll_name name 'AxmGetCommandData16';
    function AxmSetCommandData24; external dll_name name 'AxmSetCommandData24';
    function AxmGetCommandData24; external dll_name name 'AxmGetCommandData24';
    function AxmSetCommandData32; external dll_name name 'AxmSetCommandData32';
    function AxmGetCommandData32; external dll_name name 'AxmGetCommandData32';
    function AxmSetCommandQi; external dll_name name 'AxmSetCommandQi';
    function AxmSetCommandData08Qi; external dll_name name 'AxmSetCommandData08Qi';
    function AxmGetCommandData08Qi; external dll_name name 'AxmGetCommandData08Qi';
    function AxmSetCommandData16Qi; external dll_name name 'AxmSetCommandData16Qi';
    function AxmGetCommandData16Qi; external dll_name name 'AxmGetCommandData16Qi';
    function AxmSetCommandData24Qi; external dll_name name 'AxmSetCommandData24Qi';
    function AxmGetCommandData24Qi; external dll_name name 'AxmGetCommandData24Qi';
    function AxmSetCommandData32Qi; external dll_name name 'AxmSetCommandData32Qi';
    function AxmGetCommandData32Qi; external dll_name name 'AxmGetCommandData32Qi';
    function AxmGetPortData; external dll_name name 'AxmGetPortData';
    function AxmSetPortData; external dll_name name 'AxmSetPortData';
    function AxmGetPortDataQi; external dll_name name 'AxmGetPortDataQi';
    function AxmSetPortDataQi; external dll_name name 'AxmSetPortDataQi';
    function AxmSetScriptCaptionIp; external dll_name name 'AxmSetScriptCaptionIp';
    function AxmGetScriptCaptionIp; external dll_name name 'AxmGetScriptCaptionIp';
    function AxmSetScriptCaptionQi; external dll_name name 'AxmSetScriptCaptionQi';
    function AxmGetScriptCaptionQi; external dll_name name 'AxmGetScriptCaptionQi';
    function AxmSetScriptCaptionQueueClear; external dll_name name 'AxmSetScriptCaptionQueueClear';
    function AxmGetScriptCaptionQueueCount; external dll_name name 'AxmGetScriptCaptionQueueCount';
    function AxmGetScriptCaptionQueueDataCount; external dll_name name 'AxmGetScriptCaptionQueueDataCount';
    function AxmGetOptimizeDriveData; external dll_name name 'AxmGetOptimizeDriveData';
    function AxmBoardWriteByte; external dll_name name 'AxmBoardWriteByte';
    function AxmBoardReadByte; external dll_name name 'AxmBoardReadByte';
    function AxmBoardWriteWord; external dll_name name 'AxmBoardWriteWord';
    function AxmBoardReadWord; external dll_name name 'AxmBoardReadWord';
    function AxmBoardWriteDWord; external dll_name name 'AxmBoardWriteDWord';
    function AxmBoardReadDWord; external dll_name name 'AxmBoardReadDWord';
    function AxmModuleWriteByte; external dll_name name 'AxmModuleWriteByte';
    function AxmModuleReadByte; external dll_name name 'AxmModuleReadByte';
    function AxmModuleWriteWord; external dll_name name 'AxmModuleWriteWord';
    function AxmModuleReadWord; external dll_name name 'AxmModuleReadWord';
    function AxmModuleWriteDWord; external dll_name name 'AxmModuleWriteDWord';
    function AxmModuleReadDWord; external dll_name name 'AxmModuleReadDWord';
    function AxmStatusSetActComparatorPos; external dll_name name 'AxmStatusSetActComparatorPos';
    function AxmStatusGetActComparatorPos; external dll_name name 'AxmStatusGetActComparatorPos';
    function AxmStatusSetCmdComparatorPos; external dll_name name 'AxmStatusSetCmdComparatorPos';
    function AxmStatusGetCmdComparatorPos; external dll_name name 'AxmStatusGetCmdComparatorPos';
    function AxmLineMoveVel; external dll_name name 'AxmLineMoveVel';
    function AxmSensorSetSignal; external dll_name name 'AxmSensorSetSignal';
    function AxmSensorGetSignal; external dll_name name 'AxmSensorGetSignal';
    function AxmSensorReadSignal; external dll_name name 'AxmSensorReadSignal';
    function AxmSensorMovePos; external dll_name name 'AxmSensorMovePos';
    function AxmSensorStartMovePos; external dll_name name 'AxmSensorStartMovePos';
    function AxmHomeGetStepTrace; external dll_name name 'AxmHomeGetStepTrace';
    function AxmHomeSetConfig; external dll_name name 'AxmHomeSetConfig';
    function AxmHomeGetConfig; external dll_name name 'AxmHomeGetConfig';
    function AxmHomeSetMoveSearch; external dll_name name 'AxmHomeSetMoveSearch';
    function AxmHomeSetMoveReturn; external dll_name name 'AxmHomeSetMoveReturn';
    function AxmHomeSetMoveLeave; external dll_name name 'AxmHomeSetMoveLeave';
    function AxmHomeSetMultiMoveSearch; external dll_name name 'AxmHomeSetMultiMoveSearch';
    function AxmContiSetProfileMode; external dll_name name 'AxmContiSetProfileMode';
    function AxmContiGetProfileMode; external dll_name name 'AxmContiGetProfileMode';
    function AxdiInterruptFlagReadBit; external dll_name name 'AxdiInterruptFlagReadBit';
    function AxdiInterruptFlagReadByte; external dll_name name 'AxdiInterruptFlagReadByte';
    function AxdiInterruptFlagReadWord; external dll_name name 'AxdiInterruptFlagReadWord';
    function AxdiInterruptFlagReadDword; external dll_name name 'AxdiInterruptFlagReadDword';
    function AxdiInterruptFlagRead; external dll_name name 'AxdiInterruptFlagRead';
    function AxmLogSetAxis; external dll_name name 'AxmLogSetAxis';
    function AxmLogGetAxis; external dll_name name 'AxmLogGetAxis';
    function AxaiLogSetChannel; external dll_name name 'AxaiLogSetChannel';
    function AxaiLogGetChannel; external dll_name name 'AxaiLogGetChannel';
    function AxaoLogSetChannel; external dll_name name 'AxaoLogSetChannel';
    function AxaoLogGetChannel; external dll_name name 'AxaoLogGetChannel';
    function AxdLogSetModule; external dll_name name 'AxdLogSetModule';
    function AxdLogGetModule; external dll_name name 'AxdLogGetModule';
    function AxlGetFirmwareVersion; external dll_name name 'AxlGetFirmwareVersion';
    function AxlSetFirmwareCopy; external dll_name name 'AxlSetFirmwareCopy';
    function AxlSetFirmwareUpdate; external dll_name name 'AxlSetFirmwareUpdate';
    function AxlCheckStatus; external dll_name name 'AxlCheckStatus';
    function AxlRtexUniversalCmd; external dll_name name 'AxlRtexUniversalCmd';
    function AxmRtexSlaveCmd; external dll_name name 'AxmRtexSlaveCmd';
    function AxmRtexGetSlaveCmdResult; external dll_name name 'AxmRtexGetSlaveCmdResult';
    function AxmRtexGetSlaveCmdResultEx; external dll_name name 'AxmRtexGetSlaveCmdResultEx';
    function AxmRtexGetAxisStatus; external dll_name name 'AxmRtexGetAxisStatus';
    function AxmRtexGetAxisReturnData; external dll_name name 'AxmRtexGetAxisReturnData';
    function AxmRtexGetAxisSlaveStatus; external dll_name name 'AxmRtexGetAxisSlaveStatus';
    function AxmSetAxisCmd; external dll_name name 'AxmSetAxisCmd';
    function AxmGetAxisCmdResult; external dll_name name 'AxmGetAxisCmdResult';
    function AxdSetAndGetSlaveCmdResult; external dll_name name 'AxdSetAndGetSlaveCmdResult';
    function AxaSetAndGetSlaveCmdResult; external dll_name name 'AxaSetAndGetSlaveCmdResult';
    function AxcSetAndGetSlaveCmdResult; external dll_name name 'AxcSetAndGetSlaveCmdResult';
    function AxlGetDpRamData; external dll_name name 'AxlGetDpRamData';
    function AxlBoardReadDpramWord; external dll_name name 'AxlBoardReadDpramWord';
    function AxlBoardWriteDpramWord; external dll_name name 'AxlBoardWriteDpramWord';
    function AxlSetSendBoardEachCommand; external dll_name name 'AxlSetSendBoardEachCommand';
    function AxlSetSendBoardCommand; external dll_name name 'AxlSetSendBoardCommand';
    function AxlGetResponseBoardCommand; external dll_name name 'AxlGetResponseBoardCommand';
    function AxmInfoGetFirmwareVersion; external dll_name name 'AxmInfoGetFirmwareVersion';
    function AxaInfoGetFirmwareVersion; external dll_name name 'AxaInfoGetFirmwareVersion';
    function AxdInfoGetFirmwareVersion; external dll_name name 'AxdInfoGetFirmwareVersion';
    function AxcInfoGetFirmwareVersion; external dll_name name 'AxcInfoGetFirmwareVersion';
    function AxmSetTorqFeedForward; external dll_name name 'AxmSetTorqFeedForward';
    function AxmGetTorqFeedForward; external dll_name name 'AxmGetTorqFeedForward';
    function AxmSetVelocityFeedForward; external dll_name name 'AxmSetVelocityFeedForward';
    function AxmGetVelocityFeedForward; external dll_name name 'AxmGetVelocityFeedForward';
    function AxmSignalSetEncoderType; external dll_name name 'AxmSignalSetEncoderType';
    function AxmSignalGetEncoderType; external dll_name name 'AxmSignalGetEncoderType';
    function AxmMotSetUserMotion; external dll_name name 'AxmMotSetUserMotion';
    function AxmMotSetUserMotionUsage; external dll_name name 'AxmMotSetUserMotionUsage';
    function AxmMotSetUserPosMotion; external dll_name name 'AxmMotSetUserPosMotion';
    function AxmMotSetUserPosMotionUsage; external dll_name name 'AxmMotSetUserPosMotionUsage';
    function AxcKeWriteRamDataAddr; external dll_name name 'AxcKeWriteRamDataAddr';
    function AxcKeReadRamDataAddr; external dll_name name 'AxcKeReadRamDataAddr';
    function AxcKeResetRamDataAll; external dll_name name 'AxcKeResetRamDataAll';
    function AxcTriggerSetTimeout; external dll_name name 'AxcTriggerSetTimeout';
    function AxcTriggerGetTimeout; external dll_name name 'AxcTriggerGetTimeout';
    function AxcStatusGetWaitState; external dll_name name 'AxcStatusGetWaitState';
    function AxcStatusSetWaitState; external dll_name name 'AxcStatusSetWaitState';
    function AxcKeSetCommandData32; external dll_name name 'AxcKeSetCommandData32';
    function AxcKeSetCommandData16; external dll_name name 'AxcKeSetCommandData16';
    function AxcKeGetCommandData32; external dll_name name 'AxcKeGetCommandData32';
    function AxcKeGetCommandData16; external dll_name name 'AxcKeGetCommandData16';
    function AxmSeqSetAxisMap; external dll_name name 'AxmSeqSetAxisMap';
    function AxmSeqGetAxisMap; external dll_name name 'AxmSeqGetAxisMap';
    function AxmSeqSetMasterAxisNo; external dll_name name 'AxmSeqSetMasterAxisNo';
    function AxmSeqBeginNode; external dll_name name 'AxmSeqBeginNode';
    function AxmSeqEndNode; external dll_name name 'AxmSeqEndNode';
    function AxmSeqStart; external dll_name name 'AxmSeqStart';
    function AxmSeqAddNode; external dll_name name 'AxmSeqAddNode';
    function AxmSeqGetNodeNum; external dll_name name 'AxmSeqGetNodeNum';
    function AxmSeqGetTotalNodeNum; external dll_name name 'AxmSeqGetTotalNodeNum';
    function AxmSeqIsMotion; external dll_name name 'AxmSeqIsMotion';
    function AxmSeqWriteClear; external dll_name name 'AxmSeqWriteClear';
    function AxmSeqStop; external dll_name name 'AxmSeqStop';
    function AxmStatusSetMon; external dll_name name 'AxmStatusSetMon';
    function AxmStatusGetMon; external dll_name name 'AxmStatusGetMon';
    function AxmStatusReadMon; external dll_name name 'AxmStatusReadMon';
    function AxmStatusReadMonEx; external dll_name name 'AxmStatusReadMonEx';
    function AxlSetIoPort; external dll_name name 'AxlSetIoPort';
    function AxlGetIoPort; external dll_name name 'AxlGetIoPort';
    function AxlM3SetFWUpdateInit; external dll_name name 'AxlM3SetFWUpdateInit';
    function AxlM3GetFWUpdateInit; external dll_name name 'AxlM3GetFWUpdateInit';
    function AxlM3SetFWUpdateCopy; external dll_name name 'AxlM3SetFWUpdateCopy';
    function AxlM3GetFWUpdateCopy; external dll_name name 'AxlM3GetFWUpdateCopy';
    function AxlM3SetFWUpdate; external dll_name name 'AxlM3SetFWUpdate';
    function AxlM3GetFWUpdate; external dll_name name 'AxlM3GetFWUpdate';
    function AxlM3SetCFGData; external dll_name name 'AxlM3SetCFGData';
    function AxlM3GetCFGData; external dll_name name 'AxlM3GetCFGData';
    function AxlM3SetMCParaUpdateInit; external dll_name name 'AxlM3SetMCParaUpdateInit';
    function AxlM3GetMCParaUpdateInit; external dll_name name 'AxlM3GetMCParaUpdateInit';
    function AxlM3SetMCParaUpdateCopy; external dll_name name 'AxlM3SetMCParaUpdateCopy';
    function AxlM3GetMCParaUpdateCopy; external dll_name name 'AxlM3GetMCParaUpdateCopy';
    function AxlBoardReadDWord; external dll_name name 'AxlBoardReadDWord';
    function AxlBoardWriteDWord; external dll_name name 'AxlBoardWriteDWord';
    function AxlBoardReadDWordEx; external dll_name name 'AxlBoardReadDWordEx';
    function AxlBoardWriteDWordEx; external dll_name name 'AxlBoardWriteDWordEx';
    function AxmM3ServoSetCtrlStopMode; external dll_name name 'AxmM3ServoSetCtrlStopMode';
    function AxmM3ServoSetCtrlLtSel; external dll_name name 'AxmM3ServoSetCtrlLtSel';
    function AxmStatusReadServoCmdIOInput; external dll_name name 'AxmStatusReadServoCmdIOInput';
    function AxmM3ServoExInterpolate; external dll_name name 'AxmM3ServoExInterpolate';
    function AxmM3ServoSetExpoAccBias; external dll_name name 'AxmM3ServoSetExpoAccBias';
    function AxmM3ServoSetExpoAccTime; external dll_name name 'AxmM3ServoSetExpoAccTime';
    function AxmM3ServoSetMoveAvrTime; external dll_name name 'AxmM3ServoSetMoveAvrTime';
    function AxmM3ServoSetAccFilter; external dll_name name 'AxmM3ServoSetAccFilter';
    function AxmM3ServoSetCprmMonitor1; external dll_name name 'AxmM3ServoSetCprmMonitor1';
    function AxmM3ServoSetCprmMonitor2; external dll_name name 'AxmM3ServoSetCprmMonitor2';
    function AxmM3ServoStatusReadCprmMonitor1; external dll_name name 'AxmM3ServoStatusReadCprmMonitor1';
    function AxmM3ServoStatusReadCprmMonitor2; external dll_name name 'AxmM3ServoStatusReadCprmMonitor2';
    function AxmM3ServoSetAccDec; external dll_name name 'AxmM3ServoSetAccDec';
    function AxmM3ServoSetStop; external dll_name name 'AxmM3ServoSetStop';
    function AxlM3GetStationParameter; external dll_name name 'AxlM3GetStationParameter';
    function AxlM3SetStationParameter; external dll_name name 'AxlM3SetStationParameter';
    function AxlM3GetStationIdRd; external dll_name name 'AxlM3GetStationIdRd';
    function AxlM3SetStationNop; external dll_name name 'AxlM3SetStationNop';
    function AxlM3SetStationConfig; external dll_name name 'AxlM3SetStationConfig';
    function AxlM3GetStationAlarm; external dll_name name 'AxlM3GetStationAlarm';
    function AxlM3SetStationAlarmClear; external dll_name name 'AxlM3SetStationAlarmClear';
    function AxlM3SetStationSyncSet; external dll_name name 'AxlM3SetStationSyncSet';
    function AxlM3SetStationConnect; external dll_name name 'AxlM3SetStationConnect';
    function AxlM3SetStationDisConnect; external dll_name name 'AxlM3SetStationDisConnect';
    function AxlM3GetStationStoredParameter; external dll_name name 'AxlM3GetStationStoredParameter';
    function AxlM3SetStationStoredParameter; external dll_name name 'AxlM3SetStationStoredParameter';
    function AxlM3GetStationMemory; external dll_name name 'AxlM3GetStationMemory';
    function AxlM3SetStationMemory; external dll_name name 'AxlM3SetStationMemory';
    function AxlM3SetStationAccessMode; external dll_name name 'AxlM3SetStationAccessMode';
    function AxlM3GetStationAccessMode; external dll_name name 'AxlM3GetStationAccessMode';
    function AxlM3SetAutoSyncConnectMode; external dll_name name 'AxlM3SetAutoSyncConnectMode';
    function AxlM3GetAutoSyncConnectMode; external dll_name name 'AxlM3GetAutoSyncConnectMode';
    function AxlM3SyncConnectSingle; external dll_name name 'AxlM3SyncConnectSingle';
    function AxlM3SyncDisconnectSingle; external dll_name name 'AxlM3SyncDisconnectSingle';
    function AxlM3IsOnLine; external dll_name name 'AxlM3IsOnLine';
    function AxlM3GetStationRWS; external dll_name name 'AxlM3GetStationRWS';
    function AxlM3SetStationRWS; external dll_name name 'AxlM3SetStationRWS';
    function AxlM3GetStationRWA; external dll_name name 'AxlM3GetStationRWA';
    function AxlM3SetStationRWA; external dll_name name 'AxlM3SetStationRWA';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmHomeGetM3FWRealRate; external dll_name name 'AxmHomeGetM3FWRealRate';
    function AxmHomeGetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeGetM3OffsetAvoideSenArea';
    function AxmHomeSetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeSetM3OffsetAvoideSenArea';
    function AxmM3SetAbsEncOrgResetDisable; external dll_name name 'AxmM3SetAbsEncOrgResetDisable';
    function AxmM3GetAbsEncOrgResetDisable; external dll_name name 'AxmM3GetAbsEncOrgResetDisable';
    function AxmM3SetOfflineAlarmEnable; external dll_name name 'AxmM3SetOfflineAlarmEnable';
    function AxmM3GetOfflineAlarmEnable; external dll_name name 'AxmM3GetOfflineAlarmEnable';
    function AxmM3ReadOnlineToOfflineStatus; external dll_name name 'AxmM3ReadOnlineToOfflineStatus';
    function AxlECatGetProductInfo; external dll_name name 'AxlECatGetProductInfo';
    function AxlECatGetModuleStatus; external dll_name name 'AxlECatGetModuleStatus';
    function AxlECatReadPdoInput; external dll_name name 'AxlECatReadPdoInput';
    function AxlECatReadPdoOutput; external dll_name name 'AxlECatReadPdoOutput';
    function AxlECatWritePdoOutput; external dll_name name 'AxlECatWritePdoOutput';
    function AxlECatReadSdo; external dll_name name 'AxlECatReadSdo';
    function AxlECatWriteSdo; external dll_name name 'AxlECatWriteSdo';
    function AxlECatReadSdoFromAxisDword; external dll_name name 'AxlECatReadSdoFromAxisDword';
    function AxlECatWriteSdoFromAxisDword; external dll_name name 'AxlECatWriteSdoFromAxisDword';
    function AxlECatReadSdoFromAxisWord; external dll_name name 'AxlECatReadSdoFromAxisWord';
    function AxlECatWriteSdoFromAxisWord; external dll_name name 'AxlECatWriteSdoFromAxisWord';
    function AxlECatReadSdoFromAxisByte; external dll_name name 'AxlECatReadSdoFromAxisByte';
    function AxlECatWriteSdoFromAxisByte; external dll_name name 'AxlECatWriteSdoFromAxisByte';
    function AxlECatReadEEPRom; external dll_name name 'AxlECatReadEEPRom';
    function AxlECatWriteEEPRom; external dll_name name 'AxlECatWriteEEPRom';
    function AxlECatReadRegister; external dll_name name 'AxlECatReadRegister';
    function AxlECatWriteRegister; external dll_name name 'AxlECatWriteRegister';
    function AxlECatSaveHotSwapData; external dll_name name 'AxlECatSaveHotSwapData';
    function AxlECatLoadHotSwapData; external dll_name name 'AxlECatLoadHotSwapData';
    function AxlECatSetHotSwap; external dll_name name 'AxlECatSetHotSwap';
    function AxlECatIsSetHotSwap; external dll_name name 'AxlECatIsSetHotSwap';
    function AxlECatReSetHotSwap; external dll_name name 'AxlECatReSetHotSwap';
    function AxlECatSetMasterMode; external dll_name name 'AxlECatSetMasterMode';
    function AxlECatGetMasterMode; external dll_name name 'AxlECatGetMasterMode';
    function AxlECatSetMasterOperationMode; external dll_name name 'AxlECatSetMasterOperationMode';
    function AxlECatGetMasterOperationMode; external dll_name name 'AxlECatGetMasterOperationMode';
    function AxlECatRequestScanData; external dll_name name 'AxlECatRequestScanData';
    function AxlECatGetScanSlaveCount; external dll_name name 'AxlECatGetScanSlaveCount';
    function AxlECatGetStatus; external dll_name name 'AxlECatGetStatus';
    function AxlEcatReConnect; external dll_name name 'AxlEcatReConnect';
    function AxmECatReadAddress; external dll_name name 'AxmECatReadAddress';
    function AxdECatReadAddress; external dll_name name 'AxdECatReadAddress';
    function AxaECatReadAddress; external dll_name name 'AxaECatReadAddress';
    function AxsECatReadAddress; external dll_name name 'AxsECatReadAddress';
    function AxlMonitorSetItem; external dll_name name 'AxlMonitorSetItem';
    function AxlMonitorGetIndexInfo; external dll_name name 'AxlMonitorGetIndexInfo';
    function AxlMonitorGetItemInfo; external dll_name name 'AxlMonitorGetItemInfo';
    function AxlMonitorResetAllItem; external dll_name name 'AxlMonitorResetAllItem';
    function AxlMonitorResetItem; external dll_name name 'AxlMonitorResetItem';
    function AxlMonitorSetTriggerOption; external dll_name name 'AxlMonitorSetTriggerOption';
    function AxlMonitorResetTriggerOption; external dll_name name 'AxlMonitorResetTriggerOption';
    function AxlMonitorStart; external dll_name name 'AxlMonitorStart';
    function AxlMonitorStop; external dll_name name 'AxlMonitorStop';
    function AxlMonitorReadData; external dll_name name 'AxlMonitorReadData';
    function AxlMonitorReadPeriod; external dll_name name 'AxlMonitorReadPeriod';
    function AxlMonitorExSetItem; external dll_name name 'AxlMonitorExSetItem';
    function AxlMonitorExGetIndexInfo; external dll_name name 'AxlMonitorExGetIndexInfo';
    function AxlMonitorExGetItemInfo; external dll_name name 'AxlMonitorExGetItemInfo';
    function AxlMonitorExResetAllItem; external dll_name name 'AxlMonitorExResetAllItem';
    function AxlMonitorExResetItem; external dll_name name 'AxlMonitorExResetItem';
    function AxlMonitorExSetTriggerOption; external dll_name name 'AxlMonitorExSetTriggerOption';
    function AxlMonitorExResetTriggerOption; external dll_name name 'AxlMonitorExResetTriggerOption';
    function AxlMonitorExStart; external dll_name name 'AxlMonitorExStart';
    function AxlMonitorExStop; external dll_name name 'AxlMonitorExStop';
    function AxlMonitorExReadData; external dll_name name 'AxlMonitorExReadData';
    function AxlMonitorExReadPeriod; external dll_name name 'AxlMonitorExReadPeriod';
    function AxmLineMoveDual01; external dll_name name 'AxmLineMoveDual01';
    function AxmCircleCenterMoveDual01; external dll_name name 'AxmCircleCenterMoveDual01';
    function AxdSetFirmwareUpdateInfo; external dll_name name 'AxdSetFirmwareUpdateInfo';
    function AxdSetFirmwareDataTrans; external dll_name name 'AxdSetFirmwareDataTrans';
    function AxdSetFirmwareUpdate; external dll_name name 'AxdSetFirmwareUpdate';
    function AxaSetFirmwareUpdateInfo; external dll_name name 'AxaSetFirmwareUpdateInfo';
    function AxaSetFirmwareDataTrans; external dll_name name 'AxaSetFirmwareDataTrans';
    function AxaSetFirmwareUpdate; external dll_name name 'AxaSetFirmwareUpdate';
    function AxmSetFirmwareUpdateInfo; external dll_name name 'AxmSetFirmwareUpdateInfo';
    function AxmSetFirmwareDataTrans; external dll_name name 'AxmSetFirmwareDataTrans';
    function AxmSetFirmwareUpdate; external dll_name name 'AxmSetFirmwareUpdate';
    function AxmMotSetOperationMode; external dll_name name 'AxmMotSetOperationMode';
    function AxmMotGetOperationMode; external dll_name name 'AxmMotGetOperationMode';
    function AxlGetBoardAddress; external dll_name name 'AxlGetBoardAddress';
    function AxlGetBoardID; external dll_name name 'AxlGetBoardID';
    function AxlGetBoardVersion; external dll_name name 'AxlGetBoardVersion';
    function AxlGetModuleID; external dll_name name 'AxlGetModuleID';
    function AxlGetModuleVersion; external dll_name name 'AxlGetModuleVersion';
    function AxlGetModuleNodeInfo; external dll_name name 'AxlGetModuleNodeInfo';
    function AxlSetDataFlash; external dll_name name 'AxlSetDataFlash';
    function AxlSetEStopInterLock; external dll_name name 'AxlSetEStopInterLock';
    function AxlGetEStopInterLock; external dll_name name 'AxlGetEStopInterLock';
    function AxlReadEStopInterLock; external dll_name name 'AxlReadEStopInterLock';
    function AxlGetDataFlash; external dll_name name 'AxlGetDataFlash';
    function AxaInfoGetModuleNo; external dll_name name 'AxaInfoGetModuleNo';
    function AxdInfoGetModuleNo; external dll_name name 'AxdInfoGetModuleNo';
    function AxmSetCommand; external dll_name name 'AxmSetCommand';
    function AxmSetCommandData08; external dll_name name 'AxmSetCommandData08';
    function AxmGetCommandData08; external dll_name name 'AxmGetCommandData08';
    function AxmSetCommandData16; external dll_name name 'AxmSetCommandData16';
    function AxmGetCommandData16; external dll_name name 'AxmGetCommandData16';
    function AxmSetCommandData24; external dll_name name 'AxmSetCommandData24';
    function AxmGetCommandData24; external dll_name name 'AxmGetCommandData24';
    function AxmSetCommandData32; external dll_name name 'AxmSetCommandData32';
    function AxmGetCommandData32; external dll_name name 'AxmGetCommandData32';
    function AxmSetCommandQi; external dll_name name 'AxmSetCommandQi';
    function AxmSetCommandData08Qi; external dll_name name 'AxmSetCommandData08Qi';
    function AxmGetCommandData08Qi; external dll_name name 'AxmGetCommandData08Qi';
    function AxmSetCommandData16Qi; external dll_name name 'AxmSetCommandData16Qi';
    function AxmGetCommandData16Qi; external dll_name name 'AxmGetCommandData16Qi';
    function AxmSetCommandData24Qi; external dll_name name 'AxmSetCommandData24Qi';
    function AxmGetCommandData24Qi; external dll_name name 'AxmGetCommandData24Qi';
    function AxmSetCommandData32Qi; external dll_name name 'AxmSetCommandData32Qi';
    function AxmGetCommandData32Qi; external dll_name name 'AxmGetCommandData32Qi';
    function AxmGetPortData; external dll_name name 'AxmGetPortData';
    function AxmSetPortData; external dll_name name 'AxmSetPortData';
    function AxmGetPortDataQi; external dll_name name 'AxmGetPortDataQi';
    function AxmSetPortDataQi; external dll_name name 'AxmSetPortDataQi';
    function AxmSetScriptCaptionIp; external dll_name name 'AxmSetScriptCaptionIp';
    function AxmGetScriptCaptionIp; external dll_name name 'AxmGetScriptCaptionIp';
    function AxmSetScriptCaptionQi; external dll_name name 'AxmSetScriptCaptionQi';
    function AxmGetScriptCaptionQi; external dll_name name 'AxmGetScriptCaptionQi';
    function AxmSetScriptCaptionQueueClear; external dll_name name 'AxmSetScriptCaptionQueueClear';
    function AxmGetScriptCaptionQueueCount; external dll_name name 'AxmGetScriptCaptionQueueCount';
    function AxmGetScriptCaptionQueueDataCount; external dll_name name 'AxmGetScriptCaptionQueueDataCount';
    function AxmGetOptimizeDriveData; external dll_name name 'AxmGetOptimizeDriveData';
    function AxmBoardWriteByte; external dll_name name 'AxmBoardWriteByte';
    function AxmBoardReadByte; external dll_name name 'AxmBoardReadByte';
    function AxmBoardWriteWord; external dll_name name 'AxmBoardWriteWord';
    function AxmBoardReadWord; external dll_name name 'AxmBoardReadWord';
    function AxmBoardWriteDWord; external dll_name name 'AxmBoardWriteDWord';
    function AxmBoardReadDWord; external dll_name name 'AxmBoardReadDWord';
    function AxmModuleWriteByte; external dll_name name 'AxmModuleWriteByte';
    function AxmModuleReadByte; external dll_name name 'AxmModuleReadByte';
    function AxmModuleWriteWord; external dll_name name 'AxmModuleWriteWord';
    function AxmModuleReadWord; external dll_name name 'AxmModuleReadWord';
    function AxmModuleWriteDWord; external dll_name name 'AxmModuleWriteDWord';
    function AxmModuleReadDWord; external dll_name name 'AxmModuleReadDWord';
    function AxmStatusSetActComparatorPos; external dll_name name 'AxmStatusSetActComparatorPos';
    function AxmStatusGetActComparatorPos; external dll_name name 'AxmStatusGetActComparatorPos';
    function AxmStatusSetCmdComparatorPos; external dll_name name 'AxmStatusSetCmdComparatorPos';
    function AxmStatusGetCmdComparatorPos; external dll_name name 'AxmStatusGetCmdComparatorPos';
    function AxmLineMoveVel; external dll_name name 'AxmLineMoveVel';
    function AxmSensorSetSignal; external dll_name name 'AxmSensorSetSignal';
    function AxmSensorGetSignal; external dll_name name 'AxmSensorGetSignal';
    function AxmSensorReadSignal; external dll_name name 'AxmSensorReadSignal';
    function AxmSensorMovePos; external dll_name name 'AxmSensorMovePos';
    function AxmSensorStartMovePos; external dll_name name 'AxmSensorStartMovePos';
    function AxmHomeGetStepTrace; external dll_name name 'AxmHomeGetStepTrace';
    function AxmHomeSetConfig; external dll_name name 'AxmHomeSetConfig';
    function AxmHomeGetConfig; external dll_name name 'AxmHomeGetConfig';
    function AxmHomeSetMoveSearch; external dll_name name 'AxmHomeSetMoveSearch';
    function AxmHomeSetMoveReturn; external dll_name name 'AxmHomeSetMoveReturn';
    function AxmHomeSetMoveLeave; external dll_name name 'AxmHomeSetMoveLeave';
    function AxmHomeSetMultiMoveSearch; external dll_name name 'AxmHomeSetMultiMoveSearch';
    function AxmContiSetProfileMode; external dll_name name 'AxmContiSetProfileMode';
    function AxmContiGetProfileMode; external dll_name name 'AxmContiGetProfileMode';
    function AxdiInterruptFlagReadBit; external dll_name name 'AxdiInterruptFlagReadBit';
    function AxdiInterruptFlagReadByte; external dll_name name 'AxdiInterruptFlagReadByte';
    function AxdiInterruptFlagReadWord; external dll_name name 'AxdiInterruptFlagReadWord';
    function AxdiInterruptFlagReadDword; external dll_name name 'AxdiInterruptFlagReadDword';
    function AxdiInterruptFlagRead; external dll_name name 'AxdiInterruptFlagRead';
    function AxmLogSetAxis; external dll_name name 'AxmLogSetAxis';
    function AxmLogGetAxis; external dll_name name 'AxmLogGetAxis';
    function AxaiLogSetChannel; external dll_name name 'AxaiLogSetChannel';
    function AxaiLogGetChannel; external dll_name name 'AxaiLogGetChannel';
    function AxaoLogSetChannel; external dll_name name 'AxaoLogSetChannel';
    function AxaoLogGetChannel; external dll_name name 'AxaoLogGetChannel';
    function AxdLogSetModule; external dll_name name 'AxdLogSetModule';
    function AxdLogGetModule; external dll_name name 'AxdLogGetModule';
    function AxlGetFirmwareVersion; external dll_name name 'AxlGetFirmwareVersion';
    function AxlSetFirmwareCopy; external dll_name name 'AxlSetFirmwareCopy';
    function AxlSetFirmwareUpdate; external dll_name name 'AxlSetFirmwareUpdate';
    function AxlCheckStatus; external dll_name name 'AxlCheckStatus';
    function AxlRtexUniversalCmd; external dll_name name 'AxlRtexUniversalCmd';
    function AxmRtexSlaveCmd; external dll_name name 'AxmRtexSlaveCmd';
    function AxmRtexGetSlaveCmdResult; external dll_name name 'AxmRtexGetSlaveCmdResult';
    function AxmRtexGetSlaveCmdResultEx; external dll_name name 'AxmRtexGetSlaveCmdResultEx';
    function AxmRtexGetAxisStatus; external dll_name name 'AxmRtexGetAxisStatus';
    function AxmRtexGetAxisReturnData; external dll_name name 'AxmRtexGetAxisReturnData';
    function AxmRtexGetAxisSlaveStatus; external dll_name name 'AxmRtexGetAxisSlaveStatus';
    function AxmSetAxisCmd; external dll_name name 'AxmSetAxisCmd';
    function AxmGetAxisCmdResult; external dll_name name 'AxmGetAxisCmdResult';
    function AxdSetAndGetSlaveCmdResult; external dll_name name 'AxdSetAndGetSlaveCmdResult';
    function AxaSetAndGetSlaveCmdResult; external dll_name name 'AxaSetAndGetSlaveCmdResult';
    function AxcSetAndGetSlaveCmdResult; external dll_name name 'AxcSetAndGetSlaveCmdResult';
    function AxlGetDpRamData; external dll_name name 'AxlGetDpRamData';
    function AxlBoardReadDpramWord; external dll_name name 'AxlBoardReadDpramWord';
    function AxlBoardWriteDpramWord; external dll_name name 'AxlBoardWriteDpramWord';
    function AxlSetSendBoardEachCommand; external dll_name name 'AxlSetSendBoardEachCommand';
    function AxlSetSendBoardCommand; external dll_name name 'AxlSetSendBoardCommand';
    function AxlGetResponseBoardCommand; external dll_name name 'AxlGetResponseBoardCommand';
    function AxmInfoGetFirmwareVersion; external dll_name name 'AxmInfoGetFirmwareVersion';
    function AxaInfoGetFirmwareVersion; external dll_name name 'AxaInfoGetFirmwareVersion';
    function AxdInfoGetFirmwareVersion; external dll_name name 'AxdInfoGetFirmwareVersion';
    function AxcInfoGetFirmwareVersion; external dll_name name 'AxcInfoGetFirmwareVersion';
    function AxmSetTorqFeedForward; external dll_name name 'AxmSetTorqFeedForward';
    function AxmGetTorqFeedForward; external dll_name name 'AxmGetTorqFeedForward';
    function AxmSetVelocityFeedForward; external dll_name name 'AxmSetVelocityFeedForward';
    function AxmGetVelocityFeedForward; external dll_name name 'AxmGetVelocityFeedForward';
    function AxmSignalSetEncoderType; external dll_name name 'AxmSignalSetEncoderType';
    function AxmSignalGetEncoderType; external dll_name name 'AxmSignalGetEncoderType';
    function AxmMotSetUserMotion; external dll_name name 'AxmMotSetUserMotion';
    function AxmMotSetUserMotionUsage; external dll_name name 'AxmMotSetUserMotionUsage';
    function AxmMotSetUserPosMotion; external dll_name name 'AxmMotSetUserPosMotion';
    function AxmMotSetUserPosMotionUsage; external dll_name name 'AxmMotSetUserPosMotionUsage';
    function AxcKeWriteRamDataAddr; external dll_name name 'AxcKeWriteRamDataAddr';
    function AxcKeReadRamDataAddr; external dll_name name 'AxcKeReadRamDataAddr';
    function AxcKeResetRamDataAll; external dll_name name 'AxcKeResetRamDataAll';
    function AxcTriggerSetTimeout; external dll_name name 'AxcTriggerSetTimeout';
    function AxcTriggerGetTimeout; external dll_name name 'AxcTriggerGetTimeout';
    function AxcStatusGetWaitState; external dll_name name 'AxcStatusGetWaitState';
    function AxcStatusSetWaitState; external dll_name name 'AxcStatusSetWaitState';
    function AxcKeSetCommandData32; external dll_name name 'AxcKeSetCommandData32';
    function AxcKeSetCommandData16; external dll_name name 'AxcKeSetCommandData16';
    function AxcKeGetCommandData32; external dll_name name 'AxcKeGetCommandData32';
    function AxcKeGetCommandData16; external dll_name name 'AxcKeGetCommandData16';
    function AxmSeqSetAxisMap; external dll_name name 'AxmSeqSetAxisMap';
    function AxmSeqGetAxisMap; external dll_name name 'AxmSeqGetAxisMap';
    function AxmSeqSetMasterAxisNo; external dll_name name 'AxmSeqSetMasterAxisNo';
    function AxmSeqBeginNode; external dll_name name 'AxmSeqBeginNode';
    function AxmSeqEndNode; external dll_name name 'AxmSeqEndNode';
    function AxmSeqStart; external dll_name name 'AxmSeqStart';
    function AxmSeqAddNode; external dll_name name 'AxmSeqAddNode';
    function AxmSeqGetNodeNum; external dll_name name 'AxmSeqGetNodeNum';
    function AxmSeqGetTotalNodeNum; external dll_name name 'AxmSeqGetTotalNodeNum';
    function AxmSeqIsMotion; external dll_name name 'AxmSeqIsMotion';
    function AxmSeqWriteClear; external dll_name name 'AxmSeqWriteClear';
    function AxmSeqStop; external dll_name name 'AxmSeqStop';
    function AxmStatusSetMon; external dll_name name 'AxmStatusSetMon';
    function AxmStatusGetMon; external dll_name name 'AxmStatusGetMon';
    function AxmStatusReadMon; external dll_name name 'AxmStatusReadMon';
    function AxmStatusReadMonEx; external dll_name name 'AxmStatusReadMonEx';
    function AxlSetIoPort; external dll_name name 'AxlSetIoPort';
    function AxlGetIoPort; external dll_name name 'AxlGetIoPort';
    function AxlM3SetFWUpdateInit; external dll_name name 'AxlM3SetFWUpdateInit';
    function AxlM3GetFWUpdateInit; external dll_name name 'AxlM3GetFWUpdateInit';
    function AxlM3SetFWUpdateCopy; external dll_name name 'AxlM3SetFWUpdateCopy';
    function AxlM3GetFWUpdateCopy; external dll_name name 'AxlM3GetFWUpdateCopy';
    function AxlM3SetFWUpdate; external dll_name name 'AxlM3SetFWUpdate';
    function AxlM3GetFWUpdate; external dll_name name 'AxlM3GetFWUpdate';
    function AxlM3SetCFGData; external dll_name name 'AxlM3SetCFGData';
    function AxlM3GetCFGData; external dll_name name 'AxlM3GetCFGData';
    function AxlM3SetMCParaUpdateInit; external dll_name name 'AxlM3SetMCParaUpdateInit';
    function AxlM3GetMCParaUpdateInit; external dll_name name 'AxlM3GetMCParaUpdateInit';
    function AxlM3SetMCParaUpdateCopy; external dll_name name 'AxlM3SetMCParaUpdateCopy';
    function AxlM3GetMCParaUpdateCopy; external dll_name name 'AxlM3GetMCParaUpdateCopy';
    function AxlBoardReadDWord; external dll_name name 'AxlBoardReadDWord';
    function AxlBoardWriteDWord; external dll_name name 'AxlBoardWriteDWord';
    function AxlBoardReadDWordEx; external dll_name name 'AxlBoardReadDWordEx';
    function AxlBoardWriteDWordEx; external dll_name name 'AxlBoardWriteDWordEx';
    function AxmM3ServoSetCtrlStopMode; external dll_name name 'AxmM3ServoSetCtrlStopMode';
    function AxmM3ServoSetCtrlLtSel; external dll_name name 'AxmM3ServoSetCtrlLtSel';
    function AxmStatusReadServoCmdIOInput; external dll_name name 'AxmStatusReadServoCmdIOInput';
    function AxmM3ServoExInterpolate; external dll_name name 'AxmM3ServoExInterpolate';
    function AxmM3ServoSetExpoAccBias; external dll_name name 'AxmM3ServoSetExpoAccBias';
    function AxmM3ServoSetExpoAccTime; external dll_name name 'AxmM3ServoSetExpoAccTime';
    function AxmM3ServoSetMoveAvrTime; external dll_name name 'AxmM3ServoSetMoveAvrTime';
    function AxmM3ServoSetAccFilter; external dll_name name 'AxmM3ServoSetAccFilter';
    function AxmM3ServoSetCprmMonitor1; external dll_name name 'AxmM3ServoSetCprmMonitor1';
    function AxmM3ServoSetCprmMonitor2; external dll_name name 'AxmM3ServoSetCprmMonitor2';
    function AxmM3ServoStatusReadCprmMonitor1; external dll_name name 'AxmM3ServoStatusReadCprmMonitor1';
    function AxmM3ServoStatusReadCprmMonitor2; external dll_name name 'AxmM3ServoStatusReadCprmMonitor2';
    function AxmM3ServoSetAccDec; external dll_name name 'AxmM3ServoSetAccDec';
    function AxmM3ServoSetStop; external dll_name name 'AxmM3ServoSetStop';
    function AxlM3GetStationParameter; external dll_name name 'AxlM3GetStationParameter';
    function AxlM3SetStationParameter; external dll_name name 'AxlM3SetStationParameter';
    function AxlM3GetStationIdRd; external dll_name name 'AxlM3GetStationIdRd';
    function AxlM3SetStationNop; external dll_name name 'AxlM3SetStationNop';
    function AxlM3SetStationConfig; external dll_name name 'AxlM3SetStationConfig';
    function AxlM3GetStationAlarm; external dll_name name 'AxlM3GetStationAlarm';
    function AxlM3SetStationAlarmClear; external dll_name name 'AxlM3SetStationAlarmClear';
    function AxlM3SetStationSyncSet; external dll_name name 'AxlM3SetStationSyncSet';
    function AxlM3SetStationConnect; external dll_name name 'AxlM3SetStationConnect';
    function AxlM3SetStationDisConnect; external dll_name name 'AxlM3SetStationDisConnect';
    function AxlM3GetStationStoredParameter; external dll_name name 'AxlM3GetStationStoredParameter';
    function AxlM3SetStationStoredParameter; external dll_name name 'AxlM3SetStationStoredParameter';
    function AxlM3GetStationMemory; external dll_name name 'AxlM3GetStationMemory';
    function AxlM3SetStationMemory; external dll_name name 'AxlM3SetStationMemory';
    function AxlM3SetStationAccessMode; external dll_name name 'AxlM3SetStationAccessMode';
    function AxlM3GetStationAccessMode; external dll_name name 'AxlM3GetStationAccessMode';
    function AxlM3SetAutoSyncConnectMode; external dll_name name 'AxlM3SetAutoSyncConnectMode';
    function AxlM3GetAutoSyncConnectMode; external dll_name name 'AxlM3GetAutoSyncConnectMode';
    function AxlM3SyncConnectSingle; external dll_name name 'AxlM3SyncConnectSingle';
    function AxlM3SyncDisconnectSingle; external dll_name name 'AxlM3SyncDisconnectSingle';
    function AxlM3IsOnLine; external dll_name name 'AxlM3IsOnLine';
    function AxlM3GetStationRWS; external dll_name name 'AxlM3GetStationRWS';
    function AxlM3SetStationRWS; external dll_name name 'AxlM3SetStationRWS';
    function AxlM3GetStationRWA; external dll_name name 'AxlM3GetStationRWA';
    function AxlM3SetStationRWA; external dll_name name 'AxlM3SetStationRWA';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmHomeGetM3FWRealRate; external dll_name name 'AxmHomeGetM3FWRealRate';
    function AxmHomeGetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeGetM3OffsetAvoideSenArea';
    function AxmHomeSetM3OffsetAvoideSenArea; external dll_name name 'AxmHomeSetM3OffsetAvoideSenArea';
    function AxmM3SetAbsEncOrgResetDisable; external dll_name name 'AxmM3SetAbsEncOrgResetDisable';
    function AxmM3GetAbsEncOrgResetDisable; external dll_name name 'AxmM3GetAbsEncOrgResetDisable';
    function AxmM3SetOfflineAlarmEnable; external dll_name name 'AxmM3SetOfflineAlarmEnable';
    function AxmM3GetOfflineAlarmEnable; external dll_name name 'AxmM3GetOfflineAlarmEnable';
    function AxmM3ReadOnlineToOfflineStatus; external dll_name name 'AxmM3ReadOnlineToOfflineStatus';
    function AxlSetLockMode; external dll_name name 'AxlSetLockMode';
    function AxlSetLockData; external dll_name name 'AxlSetLockData';
    function AxmMoveStartPosWithAVC; external dll_name name 'AxmMoveStartPosWithAVC';
    function AxlECatGetProductInfo; external dll_name name 'AxlECatGetProductInfo';
    function AxlECatGetProductInfoEx; external dll_name name 'AxlECatGetProductInfoEx';
    function AxlECatGetModuleStatus; external dll_name name 'AxlECatGetModuleStatus';
    function AxlECatReadPdoInput; external dll_name name 'AxlECatReadPdoInput';
    function AxlECatReadPdoInputEx; external dll_name name 'AxlECatReadPdoInputEx';
    function AxlECatReadPdoOutput; external dll_name name 'AxlECatReadPdoOutput';
    function AxlECatReadPdoOutputEx; external dll_name name 'AxlECatReadPdoOutputEx';
    function AxlECatWritePdoOutput; external dll_name name 'AxlECatWritePdoOutput';
    function AxlECatReadSdo; external dll_name name 'AxlECatReadSdo';
    function AxlECatReadSdoEx; external dll_name name 'AxlECatReadSdoEx';
    function AxlECatWriteSdo; external dll_name name 'AxlECatWriteSdo';
    function AxlECatWriteSdoEx; external dll_name name 'AxlECatWriteSdoEx';
    function AxlECatReadSdoFromAxisDouble; external dll_name name 'AxlECatReadSdoFromAxisDouble';
    function AxlECatWriteSdoFromAxisDouble; external dll_name name 'AxlECatWriteSdoFromAxisDouble';
    function AxlECatReadSdoFromAxisDword; external dll_name name 'AxlECatReadSdoFromAxisDword';
    function AxlECatWriteSdoFromAxisDword; external dll_name name 'AxlECatWriteSdoFromAxisDword';
    function AxlECatReadSdoFromAxisWord; external dll_name name 'AxlECatReadSdoFromAxisWord';
    function AxlECatWriteSdoFromAxisWord; external dll_name name 'AxlECatWriteSdoFromAxisWord';
    function AxlECatReadSdoFromAxisByte; external dll_name name 'AxlECatReadSdoFromAxisByte';
    function AxlECatWriteSdoFromAxisByte; external dll_name name 'AxlECatWriteSdoFromAxisByte';
    function AxlECatReadEEPRom; external dll_name name 'AxlECatReadEEPRom';
    function AxlECatWriteEEPRom; external dll_name name 'AxlECatWriteEEPRom';
    function AxlECatReadEEPRomEx; external dll_name name 'AxlECatReadEEPRomEx';
    function AxlECatWriteEEPRomEx; external dll_name name 'AxlECatWriteEEPRomEx';
    function AxlECatReadRegister; external dll_name name 'AxlECatReadRegister';
    function AxlECatWriteRegister; external dll_name name 'AxlECatWriteRegister';
    function AxlECatSaveHotSwapData; external dll_name name 'AxlECatSaveHotSwapData';
    function AxlECatLoadHotSwapData; external dll_name name 'AxlECatLoadHotSwapData';
    function AxlECatSetHotSwap; external dll_name name 'AxlECatSetHotSwap';
    function AxlECatIsSetHotSwap; external dll_name name 'AxlECatIsSetHotSwap';
    function AxlECatReSetHotSwap; external dll_name name 'AxlECatReSetHotSwap';
    function AxlECatSetMasterMode; external dll_name name 'AxlECatSetMasterMode';
    function AxlECatGetMasterMode; external dll_name name 'AxlECatGetMasterMode';
    function AxlECatSetMasterOperationMode; external dll_name name 'AxlECatSetMasterOperationMode';
    function AxlECatGetMasterOperationMode; external dll_name name 'AxlECatGetMasterOperationMode';
    function AxlECatRequestScanData; external dll_name name 'AxlECatRequestScanData';
    function AxlECatGetScanSlaveCount; external dll_name name 'AxlECatGetScanSlaveCount';
    function AxlECatGetStatus; external dll_name name 'AxlECatGetStatus';
    function AxlEcatReConnect; external dll_name name 'AxlEcatReConnect';
    function AxmECatReadAddress; external dll_name name 'AxmECatReadAddress';
    function AxdECatReadAddress; external dll_name name 'AxdECatReadAddress';
    function AxaECatReadAddress; external dll_name name 'AxaECatReadAddress';
    function AxsECatReadAddress; external dll_name name 'AxsECatReadAddress';
    function AxlMonitorSetItem; external dll_name name 'AxlMonitorSetItem';
    function AxlMonitorGetIndexInfo; external dll_name name 'AxlMonitorGetIndexInfo';
    function AxlMonitorGetItemInfo; external dll_name name 'AxlMonitorGetItemInfo';
    function AxlMonitorResetAllItem; external dll_name name 'AxlMonitorResetAllItem';
    function AxlMonitorResetItem; external dll_name name 'AxlMonitorResetItem';
    function AxlMonitorSetTriggerOption; external dll_name name 'AxlMonitorSetTriggerOption';
    function AxlMonitorResetTriggerOption; external dll_name name 'AxlMonitorResetTriggerOption';
    function AxlMonitorStart; external dll_name name 'AxlMonitorStart';
    function AxlMonitorStop; external dll_name name 'AxlMonitorStop';
    function AxlMonitorReadData; external dll_name name 'AxlMonitorReadData';
    function AxlMonitorReadPeriod; external dll_name name 'AxlMonitorReadPeriod';
    function AxlMonitorExSetItem; external dll_name name 'AxlMonitorExSetItem';
    function AxlMonitorExGetIndexInfo; external dll_name name 'AxlMonitorExGetIndexInfo';
    function AxlMonitorExGetItemInfo; external dll_name name 'AxlMonitorExGetItemInfo';
    function AxlMonitorExResetAllItem; external dll_name name 'AxlMonitorExResetAllItem';
    function AxlMonitorExResetItem; external dll_name name 'AxlMonitorExResetItem';
    function AxlMonitorExSetTriggerOption; external dll_name name 'AxlMonitorExSetTriggerOption';
    function AxlMonitorExResetTriggerOption; external dll_name name 'AxlMonitorExResetTriggerOption';
    function AxlMonitorExStart; external dll_name name 'AxlMonitorExStart';
    function AxlMonitorExStop; external dll_name name 'AxlMonitorExStop';
    function AxlMonitorExReadData; external dll_name name 'AxlMonitorExReadData';
    function AxlMonitorExReadPeriod; external dll_name name 'AxlMonitorExReadPeriod';
    function AxmLineMoveDual01; external dll_name name 'AxmLineMoveDual01';
    function AxmCircleCenterMoveDual01; external dll_name name 'AxmCircleCenterMoveDual01';
    function AxdSetFirmwareUpdateInfo; external dll_name name 'AxdSetFirmwareUpdateInfo';
    function AxdSetFirmwareDataTrans; external dll_name name 'AxdSetFirmwareDataTrans';
    function AxdSetFirmwareUpdate; external dll_name name 'AxdSetFirmwareUpdate';
    function AxaSetFirmwareUpdateInfo; external dll_name name 'AxaSetFirmwareUpdateInfo';
    function AxaSetFirmwareDataTrans; external dll_name name 'AxaSetFirmwareDataTrans';
    function AxaSetFirmwareUpdate; external dll_name name 'AxaSetFirmwareUpdate';
    function AxmSetFirmwareUpdateInfo; external dll_name name 'AxmSetFirmwareUpdateInfo';
    function AxmSetFirmwareDataTrans; external dll_name name 'AxmSetFirmwareDataTrans';
    function AxmSetFirmwareUpdate; external dll_name name 'AxmSetFirmwareUpdate';
    function AxmSetFoeUploadInfo; external dll_name name 'AxmSetFoeUploadInfo';
    function AxmGetFoeUploadData; external dll_name name 'AxmGetFoeUploadData';
    function AxmSetFoeUpload; external dll_name name 'AxmSetFoeUpload';
    function AxmMotSetOperationMode; external dll_name name 'AxmMotSetOperationMode';
    function AxmMotGetOperationMode; external dll_name name 'AxmMotGetOperationMode';
    function AxcTriggerSetPatternData; external dll_name name 'AxcTriggerSetPatternData';
    function AxcTriggerGetPatternData; external dll_name name 'AxcTriggerGetPatternData';
    function AxmSpiralMoveEx; external dll_name name 'AxmSpiralMoveEx';
    function AxmFilletMove; external dll_name name 'AxmFilletMove';
    function AxmSignalIsServoOnSingleAxis; external dll_name name 'AxmSignalIsServoOnSingleAxis';
    function AxmMotSetTorqueConnection; external dll_name name 'AxmMotSetTorqueConnection';
    function AxmMotGetTorqueConnection; external dll_name name 'AxmMotGetTorqueConnection';
