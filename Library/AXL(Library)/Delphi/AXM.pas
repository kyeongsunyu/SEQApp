//****************************************************************************
///****************************************************************************
//*****************************************************************************
//**
//** File Name
//** ---------
//**
//** AXM.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Ajinextek Motion Library Header File
//** 
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Source Change Indices
//** ----------------------
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

unit AXM;

interface

uses Windows, Messages, AXHS;



//========== Board and module verification API(Info) - Information =================================================================================

// Return board number, module position and module ID of relevant axis.
function AxmInfoGetAxis (lAxisNo : LongInt; lpBoardNo : PLongInt; lpModulePos : PLongInt; upModuleID : PDWord) : DWord; stdcall;

// Get the specified module board : Sub ID, module name, module description
//===============================================/
// support product      : EtherCAT
// upModuleSubID        : EtherCAT SubID(for distinguish between EtherCAT modules)
// szModuleName         : model name of module(50 Bytes)
// szModuleDescription  : description of module(80 Bytes)
//======================================================//
function AxmInfoGetAxisEx (lAxisNo : LongInt; upModuleSubID : PDWord; szModuleName : PChar; szModuleDescription : PChar) : DWord; stdcall;

// Return whether the motion module exists.
function AxmInfoIsMotionModule (upStatus : PDWord) : DWord; stdcall;
// Return whether relevant axis is valid.
function AxmInfoIsInvalidAxisNo (lAxisNo : LongInt) : DWord; stdcall;
// Return whether relevant axis status.
function AxmInfoGetAxisStatus (lAxisNo : LongInt) : DWord; stdcall;
// number of RTEX Products, return number of valid axis installed in system.
function AxmInfoGetAxisCount (lpAxisCount : PLongInt) : DWord; stdcall;
// Return the first axis number of relevant board/module
function AxmInfoGetFirstAxisNo (lBoardNo : LongInt; lModulePos : LongInt; lpAxisNo : PLongInt) : DWord; stdcall;
// Return the first axis number of relevant board.
function AxmInfoGetBoardFirstAxisNo (lBoardNo : LongInt; lModulePos : LongInt; lpAxisNo : PLongInt) : DWord; stdcall;



//========= virtual axis function ============================================================================================

// Set virtual axis.
function AxmVirtualSetAxisNoMap (lRealAxisNo : LongInt; lVirtualAxisNo : LongInt) : DWord; stdcall;
// Return the set virtual channel(axis) number.
function AxmVirtualGetAxisNoMap (lRealAxisNo : LongInt; lpVirtualAxisNo : PLongInt) : DWord; stdcall;
// Set multi-virtual axes.
function AxmVirtualSetMultiAxisNoMap (lSize : LongInt; lpRealAxesNo : PLongInt; lpVirtualAxesNo : PLongInt) : DWord; stdcall;
// Return the set multi-virtual channel(axis) number.
function AxmVirtualGetMultiAxisNoMap (lSize : LongInt; lpRealAxesNo : PLongInt; lpVirtualAxesNo : PLongInt) : DWord; stdcall;
// Reset the virtual axis setting.
function AxmVirtualResetAxisMap () : DWord; stdcall;


// Redefine the axis number.
function AxmVirtualSetMultiReDefineAxisNo (lSize : LongInt; lpReDefineAxesNo : PLongInt) : DWord; stdcall;
// Get the redefined axis number.
function AxmVirtualGetMultiReDefineAxisNo (lSize : LongInt; lpReDefineAxesNo : PLongInt) : DWord; stdcall;

//========= API related interrupt ======================================================================================

// Call-back API method has the advantage which can be advised the event most fast timing as the call-back API is called immediately when the event occurs, but
// the main processor shall be congested until the call-back API is completed.
// i.e, it shall be carefully used when there is any work loaded in the call-bak API.
// Event method monitors if interrupt occurs continuously by using thread, and when interrupt is occurs
// it manages, and even though this method has disadvantage which system resource is occupied by thread ,
// it can detect interrupt most quickly and manage it.
// It is not used a lot in general, but used when quick management of interrupt is the most concern.
// Event method is operated using specific thread which monitors the occurrence of event separately from main processor , so
// it able to use the resources efficiently in multi-processor system and expressly recommendable method.

// Window message or call back API is used for getting the interrupt message.
// (message handle, message ID, call back API, interrupt event)
//    hWnd    : use to get window handle and window message. Enter NULL if it is not used.
//    wMsg    : message of window handle, enter 0 if is not used or default value is used.
//    proc    : API pointer to be called when interrupted, enter NULL if not use
//    pEvent  : Event handle when event method is used.
// Ex)
// AxmInterruptSetAxis(0, Null, 0, AxtInterruptProc, NULL);
// void __stdcall AxtInterruptProc(long lActiveNo, DWORD uFlag){
//     ... ;
// }
function AxmInterruptSetAxis (lAxisNo : LongInt; hWnd : HWND; uMessage : DWord; pProc : AXT_INTERRUPT_PROC; pEvent : PDWord) : DWord; stdcall;


// Set whether to use interrupt of set axis or not.
// Set interrupt in the relevant axis/ verification
// uUse : use or not use => DISABLE(0), ENABLE(1)
function AxmInterruptSetAxisEnable (lAxisNo : LongInt; uUse : DWord) : DWord; stdcall;
// Return whether to use interrupt of set axis or not
function AxmInterruptGetAxisEnable (lAxisNo : LongInt; upUse : PDWord) : DWord; stdcall;


// Read relevant information when interrupt is used in event method
function AxmInterruptRead (lpAxisNo : PLongInt; upFlag : PDWord) : DWord; stdcall;

// Return interrupt flag value of relevant axis.
function AxmInterruptReadAxisFlag (lAxisNo : LongInt; lBank : LongInt; upFlag : PDWord) : DWord; stdcall;


// Set whether the interrupt set by user to specific axis occurs or not
// lBank         : Enable to set interrupt bank number(0 - 1).
// uInterruptNum : Enable to set interrupt number by setting bit number( 0 - 31 ).
function AxmInterruptSetUserEnable (lAxisNo : LongInt; lBank : LongInt; uInterruptNum : DWord) : DWord; stdcall;

// Verify whether the interrupt set by user of specific axis occurs or not
function AxmInterruptGetUserEnable (lAxisNo : LongInt; lBank : LongInt; upInterruptNum : PDWord) : DWord; stdcall;




//======== set motion parameter ===========================================================================================================================================================
// If file is not loaded by AxmMotLoadParaAll, set default parameter in initial parameter setting.
// Apply to all axes which is being used in PC equally. Default parameters are as below.
// 00:AXIS_NO.             =0       01:PULSE_OUT_METHOD.    =4      02:ENC_INPUT_METHOD.    =3     03:INPOSITION.          =2
// 04:ALARM.               =0       05:NEG_END_LIMIT.       =0      06:POS_END_LIMIT.       =0     07:MIN_VELOCITY.        =1
// 08:MAX_VELOCITY.        =700000  09:HOME_SIGNAL.         =4      10:HOME_LEVEL.          =1     11:HOME_DIR.            =-1
// 12:ZPHASE_LEVEL.        =1       13:ZPHASE_USE.          =0      14:STOP_SIGNAL_MODE.    =0     15:STOP_SIGNAL_LEVEL.   =0
// 16:HOME_FIRST_VELOCITY. =10000   17:HOME_SECOND_VELOCITY.=10000  18:HOME_THIRD_VELOCITY. =2000  19:HOME_LAST_VELOCITY.  =100
// 20:HOME_FIRST_ACCEL.    =40000   21:HOME_SECOND_ACCEL.   =40000  22:HOME_END_CLEAR_TIME. =1000  23:HOME_END_OFFSET.     =0
// 24:NEG_SOFT_LIMIT.      =0.000   25:POS_SOFT_LIMIT.      =0      26:MOVE_PULSE.          =1     27:MOVE_UNIT.           =1
// 28:INIT_POSITION.       =1000    29:INIT_VELOCITY.       =200    30:INIT_ACCEL.          =400   31:INIT_DECEL.          =400
// 32:INIT_ABSRELMODE.     =0       33:INIT_PROFILEMODE.    =4

// 00=[AXIS_NO             ]: axis (start from 0axis)
// 01=[PULSE_OUT_METHOD    ]: Pulse out method TwocwccwHigh = 6
// 02=[ENC_INPUT_METHOD    ]: disable = 0   1 multiplication = 1  2 multiplication = 2  4 multiplication = 3, for replacing the direction of splicing (-).1 multiplication = 11  2 multiplication = 12  4 multiplication = 13
// 03=[INPOSITION          ], 04=[ALARM     ], 05,06 =[END_LIMIT   ]  : 0 = A contact 1= B contact 2 = not use. 3 = keep current mode
// 07=[MIN_VELOCITY        ]: START VELOCITY
// 08=[MAX_VELOCITY        ]: command velocity which driver can accept. Generally normal servo is 700k
// Ex> screw : 20mm pitch drive: 10000 pulse motor: 400w
// 09=[HOME_SIGNAL         ]: 4 - Home in0 , 0 :PosEndLimit , 1 : NegEndLimit // refer _HOME_SIGNAL.
// 10=[HOME_LEVEL          ]: : 0 = A contact 1= B contact 2 = not use. 3 = keep current mode
// 11=[HOME_DIR            ]: HOME DIRECTION 1:+direction, 0:-direction
// 12=[ZPHASE_LEVEL        ]: : 0 = A contact 1= B contact 2 = not use. 3 = keep current mode
// 13=[ZPHASE_USE          ]: use of Z phase. 0: not use , 1: - direction, 2: +direction
// 14=[STOP_SIGNAL_MODE    ]: ESTOP, mode in use of SSTOP  0:slowdown stop, 1:emergency stop
// 15=[STOP_SIGNAL_LEVEL   ]: ESTOP, SSTOP use level. : 0 = A contact 1= B contact 2 = not use. 3 = keep current mode
// 16=[HOME_FIRST_VELOCITY ]: 1st move velocity
// 17=[HOME_SECOND_VELOCITY]: velocity after detecting
// 18=[HOME_THIRD_VELOCITY ]: the last velocity
// 19=[HOME_LAST_VELOCITY  ]: velocity for index detecting and detail detecting
// 20=[HOME_FIRST_ACCEL    ]: 1st acceleration, 21=[HOME_SECOND_ACCEL   ] : 2nd acceleration
// 22=[HOME_END_CLEAR_TIME ]: queue time to set origin detecting Enc value,  23=[HOME_END_OFFSET] : move as much as offset after detecting of origin.
// 24=[NEG_SOFT_LIMIT      ]: - not use if set same as SoftWare Limit , 25=[POS_SOFT_LIMIT ]: - not use if set same as SoftWare Limit.
// 26=[MOVE_PULSE          ]: amount of pulse per driver revolution               , 27=[MOVE_UNIT  ]: travel distance per driver revolution :screw Pitch
// 28=[INIT_POSITION       ]: initial position when use agent , user can use optionally
// 29=[INIT_VELOCITY       ]: initial velocity when use agent, user can use optionally
// 30=[INIT_ACCEL          ]: initial acceleration when use agent, user can use optionally
// 31=[INIT_DECEL          ]: initial deceleration when use agent, user can use optionally
// 32=[INIT_ABSRELMODE     ]: absolute(0)/relative(1) set position
// 33=[INIT_PROFILEMODE    ]: set profile mode in (0 - 4)
//                            '0': symmetry Trapezode, '1': asymmetric Trapezode, '2': symmetry Quasi-S Curve, '3':symmetry S Curve, '4':asymmetric S Curve
// 34=[SVON_LEVEL          ]: 0 = contact B, 1 = contact A
// 35=[ALARM_RESET_LEVEL   ]: 0 = contact B, 1 = contact A
// 36=[ENCODER_TYPE        ]: 0 = TYPE_INCREMENTAL, 1 = TYPE_ABSOLUTE, 2 = TYPE_NONE
// 37=[SOFT_LIMIT_SEL      ]: 0 = COMMAND, 1 = ACTUAL
// 38=[SOFT_LIMIT_STOP_MODE]: 0 = EMERGENCY_STOP, 1 = SLOWDOWN_STOP
// 39=[SOFT_LIMIT_ENABLE   ]: 0 = DISABLE, 1 = ENABLE

// load .mot file which is saved as AxmMotSaveParaAll. Optional modification is available by user.
function AxmMotLoadParaAll (szFilePath : PChar) : DWord; stdcall;
// Save all parameter for all current axis by axis. Save as .mot file. Load file by using  AxmMotLoadParaAll.
function AxmMotSaveParaAll (szFilePath : PChar) : DWord; stdcall;


// In parameter 28 - 31, user sets by using this API in the program.
function AxmMotSetParaLoad (lAxisNo : LongInt; dInitPos : Double; dInitVel : Double; dInitAccel : Double; dInitDecel : Double) : DWord; stdcall;
// In parameter 28 - 31, user verifys by using this API in the program.
function AxmMotGetParaLoad (lAxisNo : LongInt; dpInitPos : PDouble; dpInitVel : PDouble; dpInitAccel : PDouble; dpInitDecel : PDouble) : DWord; stdcall;


// Set the pulse output method of specific axis.
//uMethod  0 :OneHighLowHigh, 1 :OneHighHighLow, 2 :OneLowLowHigh, 3 :OneLowHighLow, 4 :TwoCcwCwHigh
//         5 :TwoCcwCwLow,    6 :TwoCwCcwHigh,   7 :TwoCwCcwLow,   8 :TwoPhase,      9 :TwoPhaseReverse
//    OneHighLowHigh          = 0x0,        // 1 pulse method, PULSE(Active High), forward direction(DIR=Low)  / reverse direction(DIR=High)
//    OneHighHighLow          = 0x1,        // 1 pulse method, PULSE(Active High), forward direction (DIR=High) / reverse direction (DIR=Low)
//    OneLowLowHigh           = 0x2,        // 1 pulse method, PULSE(Active Low), forward direction (DIR=Low)  / reverse direction (DIR=High)
//    OneLowHighLow           = 0x3,        // 1 pulse method, PULSE(Active Low), forward direction (DIR=High) / reverse direction (DIR=Low)
//    TwoCcwCwHigh            = 0x4,        // 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active High
//    TwoCcwCwLow             = 0x5,        // 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active Low
//    TwoCwCcwHigh            = 0x6,        // 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active High
//    TwoCwCcwLow             = 0x7,        // 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active Low
//    TwoPhase                = 0x8,        // 2 phase (90' phase difference),  PULSE lead DIR(CW: forward direction), PULSE lag DIR(CCW: reverse direction)
//    TwoPhaseReverse         = 0x9         // 2 phase(90' phase difference),  PULSE lead DIR(CCW: Forward diredtion), PULSE lag DIR(CW: Reverse direction)
function AxmMotSetPulseOutMethod (lAxisNo : LongInt; uMethod : DWord) : DWord; stdcall;
// Return the setting of pulse output method of specific axis.
function AxmMotGetPulseOutMethod (lAxisNo : LongInt; upMethod : PDWord) : DWord; stdcall;


// Set the Encoder input method including the setting of increase direction of actual count of specific axis.
//    ObverseUpDownMode       = 0x0,        // Forward direction Up/Down
//    ObverseSqr1Mode         = 0x1,        // Forward direction 1 multiplication
//    ObverseSqr2Mode         = 0x2,        // Forward direction 2 multiplication
//    ObverseSqr4Mode         = 0x3,        // Forward direction 4 multiplication
//    ReverseUpDownMode       = 0x4,        // Reverse direction Up/Down
//    ReverseSqr1Mode         = 0x5,        // Reverse direction 1 multiplication
//    ReverseSqr2Mode         = 0x6,        // Reverse direction 2 multiplication
//    ReverseSqr4Mode         = 0x7         // Reverse direction 4 multiplication
function AxmMotSetEncInputMethod (lAxisNo : LongInt; uMethod : DWord) : DWord; stdcall;
// Return the Encoder input method including the setting of increase direction of actual count of specific axis.
function AxmMotGetEncInputMethod (lAxisNo : LongInt; upMethod : PDWord) : DWord; stdcall;



// If you want to set specified velocity unit in RPM(Revolution Per Minute),
// ex>    calculate rpm :
// 4500 rpm ?
// When unit/ pulse = 1 : 1, then it becomes pulse per sec, and
// if you want to set at 4500 rpm , then  4500 / 60 sec : 75 revolution / 1sec
// The number of pulse per 1 revolution of motor shall be known. This can be know by detecting of Z phase in Encoder.
// If 1 revolution:1800 pulse,  75 x 1800 = 135000 pulses are required.
// Operate by input Unit = 1, Pulse = 1800 into AxmMotSetMoveUnitPerPulse.
// Caution : If it is controlled with rpm, velocity and acceleration will be changed to rpm unit as well.

// Set the travel distance of specific axis per pulse.
function AxmMotSetMoveUnitPerPulse (lAxisNo : LongInt; dUnit : Double; lPulse : LongInt) : DWord; stdcall;
// Return the travel distance of specific axis per pulse.
function AxmMotGetMoveUnitPerPulse (lAxisNo : LongInt; dpUnit : PDouble; lpPulse : PLongInt) : DWord; stdcall;


// Set deceleration starting point detecting method to specific axis.
// AutoDetect 0x0 : automatic acceleration/deceleration.
// RestPulse  0x1 : manual acceleration/deceleration.
function AxmMotSetDecelMode (lAxisNo : LongInt; uMethod : DWord) : DWord; stdcall;
// Return the deceleration starting point detecting method of specific axis.
function AxmMotGetDecelMode (lAxisNo : LongInt; upMethod : PDWord) : DWord; stdcall;


// Set remain pulse to the specific axis in manual deceleration mode.
function AxmMotSetRemainPulse (lAxisNo : LongInt; uData : DWord) : DWord; stdcall;
// Return remain pulse of the specific axis in manual deceleration mode.
function AxmMotGetRemainPulse (lAxisNo : LongInt; upData : PDWord) : DWord; stdcall;


// Set maximum velocity to the specific axis in uniform velocity movement API.
// Note : Input maximum speed value is not PPS but UNIT.
// ex) Maximum output frequency(PCI-N804/404 : 10 MPPS)
// ex) Maximum output Unit/Sec(PCI-N804/404 : 10MPPS * Unit/Pulse)
function AxmMotSetMaxVel (lAxisNo : LongInt; dVel : Double) : DWord; stdcall;
// Return maximum velocity of the specific axis in uniform velocity movement API
function AxmMotGetMaxVel (lAxisNo : LongInt; dpVel : PDouble) : DWord; stdcall;


// Set travel distance calculation mode of specific axis.
//uAbsRelMode : POS_ABS_MODE '0' - absolute coordinate system
//              POS_REL_MODE '1' - relative coordinate system
function AxmMotSetAbsRelMode (lAxisNo : LongInt; uAbsRelMode : DWord) : DWord; stdcall;
// Return travel distance calculation mode of specific axis.
function AxmMotGetAbsRelMode (lAxisNo : LongInt; upAbsRelMode : PDWord) : DWord; stdcall;


//Set move velocity profile mode of specific axis.
//ProfileMode : SYM_TRAPEZOIDE_MODE  '0' - symmetry Trapezode
//              ASYM_TRAPEZOIDE_MODE '1' - asymmetric Trapezode
//              QUASI_S_CURVE_MODE   '2' - symmetry Quasi-S Curve
//              SYM_S_CURVE_MODE     '3' - symmetry S Curve
//              ASYM_S_CURVE_MODE    '4' - asymmetric S Curve
//               SYM_TRAP_M3_SW_MODE    '5' - Symmetry Trapezode : MLIII internal S/W Profile
//               ASYM_TRAP_M3_SW_MODE   '6' - Asymmetry Trapezode : MLIII internal S/W Profile
//               SYM_S_M3_SW_MODE       '7' - Symmetry S Curve : MLIII internal S/W Profile
//               ASYM_S_M3_SW_MODE      '8' - Asymmetric S Curve : MLIII internal S/W Profile
function AxmMotSetProfileMode (lAxisNo : LongInt; uProfileMode : DWord) : DWord; stdcall;
// Return move velocity profile mode of specific axis.
function AxmMotGetProfileMode (lAxisNo : LongInt; upProfileMode : PDWord) : DWord; stdcall;


//Set acceleration unit of specific axis.
//AccelUnit : UNIT_SEC2  '0' ? use unit/sec2 for the unit of acceleration/deceleration
//            SEC        '1' - use sec for the unit of acceleration/deceleration
function AxmMotSetAccelUnit (lAxisNo : LongInt; uAccelUnit : DWord) : DWord; stdcall;
// Return acceleration unit of specific axis.
function AxmMotGetAccelUnit (lAxisNo : LongInt; upAccelUnit : PDWord) : DWord; stdcall;


// Set initial velocity to the specific axis.
function AxmMotSetMinVel (lAxisNo : LongInt; dMinVel : Double) : DWord; stdcall;
// Return initial velocity of the specific axis.
function AxmMotGetMinVel (lAxisNo : LongInt; dpMinVel : PDouble) : DWord; stdcall;

// Set acceleration jerk value of specific axis.[%].
function AxmMotSetAccelJerk (lAxisNo : LongInt; dAccelJerk : Double) : DWord; stdcall;
// Return acceleration jerk value of specific axis.
function AxmMotGetAccelJerk (lAxisNo : LongInt; dpAccelJerk : PDouble) : DWord; stdcall;

// Set deceleration jerk value of specific axis.[%].
function AxmMotSetDecelJerk (lAxisNo : LongInt; dDecelJerk : Double) : DWord; stdcall;
// Return deceleration jerk value of specific axis.
function AxmMotGetDecelJerk (lAxisNo : LongInt; dpDecelJerk : PDouble) : DWord; stdcall;


// Setting priority when determining speed profile of specified axis.(Velocity or Acceleration)
// Priority : PRIORITY_VELOCITY   '0' - Calculate close to specified speed value when determining velocity profile.
//            PRIORITY_ACCELTIME  '1' - Calculate close to specified speed value when determining Acceleration / Deceleration time profile.
function AxmMotSetProfilePriority(lAxisNo : LongInt; uPriority : DWord) : DWord; stdcall;
// Return priority when determining speed profile of specified axis.(Velocity or Acceleration)
function AxmMotGetProfilePriority(lAxisNo : LongInt; upPriority : PDWord) : DWord; stdcall;


//=========== Setting API related in/output signal ================================================================================

// Set Z phase level of specific axis.
// uLevel : LOW(0), HIGH(1)
function AxmSignalSetZphaseLevel (lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// Return Z phase level of specific axis.
function AxmSignalGetZphaseLevel (lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;


// Set output level of Servo-On signal of specific axis.
// uLevel : LOW(0), HIGH(1)
function AxmSignalSetServoOnLevel (lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// Return output level of Servo-On signal of specific axis.
function AxmSignalGetServoOnLevel (lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;


// Set output level of Servo-Alarm Reset signal of specific axis.
// uLevel : LOW(0), HIGH(1)
function AxmSignalSetServoAlarmResetLevel (lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// Return output level of Servo-Alarm Reset signal of specific axis.
function AxmSignalGetServoAlarmResetLevel (lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;


//    Set whether to use Inposition signal of specific axis and signal input level.
// uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSignalSetInpos (lAxisNo : LongInt; uUse : DWord) : DWord; stdcall;
// Return whether to use Inposition signal of specific axis and signal input level.
function AxmSignalGetInpos (lAxisNo : LongInt; upUse : PDWord) : DWord; stdcall;
// Return inposition signal input mode of specific axis.
function AxmSignalReadInpos (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;


//    Set whether to use emergency stop or not against to alarm signal input and set signal input level of specific axis.
// uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSignalSetServoAlarm (lAxisNo : LongInt; uUse : DWord) : DWord; stdcall;
// Return whether to use emergency stop or not against to alarm signal input and set signal input level of specific axis.
function AxmSignalGetServoAlarm (lAxisNo : LongInt; upUse : PDWord) : DWord; stdcall;
// Return input level of alarm signal of specific axis.
function AxmSignalReadServoAlarm (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;


// Set whether to use end limit sensor of specific axis and input level of signal.
// Available to set of slow down stop or emergency stop when end limit sensor is input.
// uStopMode: EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// uPositiveLevel, uNegativeLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSignalSetLimit (lAxisNo : LongInt; uStopMode : DWord; uPositiveLevel : DWord; uNegativeLevel : DWord) : DWord; stdcall;
// Return whether to use end limit sensor of specific axis , input level of signal and stop mode for signal input.
function AxmSignalGetLimit (lAxisNo : LongInt; upStopMode : PDWord; upPositiveLevel : PDWord; upNegativeLevel : PDWord) : DWord; stdcall;
// Return the input state of end limit sensor of specific axis.
function AxmSignalReadLimit (lAxisNo : LongInt; upPositiveStatus : PDWord; upNegativeStatus : PDWord) : DWord; stdcall;


// Set whether to use software limit, count to use and stop method of specific axis.
// uUse       : DISABLE(0), ENABLE(1)
// uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// uSelection : COMMAND(0), ACTUAL(1)
// Caution: When software limit is set in advance by using above API in origin detecting and is moving, if the detecting of origin is stopped during detecting, it becomes DISABLE.
function AxmSignalSetSoftLimit (lAxisNo : LongInt; uUse : DWord; uStopMode : DWord; uSelection : DWord; dPositivePos : Double; dNegativePos : Double) : DWord; stdcall;
// Return whether to use software limit, count to use and stop method of specific axis.
function AxmSignalGetSoftLimit (lAxisNo : LongInt; upUse : PDWord; upStopMode : PDWord; upSelection : PDWord; dpPositivePos : PDouble; dpNegativePos : PDouble) : DWord; stdcall;
function AxmSignalReadSoftLimit(lAxisNo : LongInt; upPositiveStatus : PDWord; upNegativeStatus : PDWord) : DWord; stdcall;


// Set the stop method of emergency stop(emergency stop/slowdown stop) ,or whether to use or not.
// uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// uLevel     : LOW(0), HIGH(1), UNUSED(2), USED(3)
function AxmSignalSetStop (lAxisNo : LongInt; uStopMode : DWord; uLevel : DWord) : DWord; stdcall;
// Return the stop method of emergency stop(emergency stop/slowdown stop) ,or whether to use or not.
function AxmSignalGetStop (lAxisNo : LongInt; upStopMode : PDWord; upLevel : PDWord) : DWord; stdcall;
// Return input state of emergency stop.
function AxmSignalReadStop (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;


// Output the Servo-On signal of specific axis.
// uOnOff : FALSE(0), TRUE(1) ( The case of universal 0 output)
function AxmSignalServoOn (lAxisNo : LongInt; uOnOff : DWord) : DWord; stdcall;
// Return the output state of Servo-On signal of specific axis.
function AxmSignalIsServoOn (lAxisNo : LongInt; upOnOff : PDWord) : DWord; stdcall;


// Output the Servo-Alarm Reset signal of specific axis.
// uOnOff : FALSE(0), TRUE(1) (The case of universal 1 output)
function AxmSignalServoAlarmReset (lAxisNo : LongInt; uOnOff : DWord) : DWord; stdcall;


// Set universal output value.
// uValue : Hex Value 0x00
function AxmSignalWriteOutput (lAxisNo : LongInt; uValue : DWord) : DWord; stdcall;
// Return universal output value.
function AxmSignalReadOutput (lAxisNo : LongInt; upValue : PDWord) : DWord; stdcall;


// ML3 Only
// Return Break Sensor Status
function AxmSignalReadBrakeOn (lAxisNo : LongInt; upOnOff : PDWord) : DWord; stdcall;


// lBitNo : Bit Number(0 - 4)
// uOnOff : FALSE(0), TRUE(1)
// Set universal output values by bit.
function AxmSignalWriteOutputBit (lAxisNo : LongInt; lBitNo : LongInt; uOnOff : DWord) : DWord; stdcall;
// Return universal output values by bit.
function AxmSignalReadOutputBit (lAxisNo : LongInt; lBitNo : LongInt; upOnOff : PDWord) : DWord; stdcall;


// Return universal input value in Hex value.
function AxmSignalReadInput (lAxisNo : LongInt; upValue : PDWord) : DWord; stdcall;

// lBitNo : Bit Number(0 - 4)
// Return universal input value by bit.
function AxmSignalReadInputBit (lAxisNo : LongInt; lBitNo : LongInt; upOn : PDWord) : DWord; stdcall;


// uSignal: END_LIMIT(0), INP_ALARM(1), UIN_00_01(2), UIN_02_04(3)
// dBandwidthUsec: 0.2uSec~26666uSec
function AxmSignalSetFilterBandwidth(lAxisNo : LongInt; uSignal : DWord; dBandwidthUsec : Double) : DWord; stdcall;


//========== API which verifies the state during motion moving and after moving. ============================================================
// Return number of bits of general purpose input.
function AxmSignalGetInputBitCount(lAxisNo : LongInt; upInputCount : PDWord) : DWord; stdcall;


// Return number of bits of general purpose output.
function AxmSignalGetOutputBitCount(lAxisNo : LongInt; upOutputCount : PDWord) : DWord; stdcall;


//========== API which verifies the state during motion moving and after moving. ============================================================
// Return pulse output state of specific axis.
// (Status of move)
function AxmStatusReadInMotion (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;


//  Return move pulse counter value of specific axis after start of move.
//  (pulse count value)
function AxmStatusReadDrivePulseCount (lAxisNo : LongInt; lpPulse : PLongInt) : DWord; stdcall;


// Return DriveStatus register (status of in-motion) of specific Axis.
// Caution: All Motion Product is different Hardware bit signal. Refer Manual and AXHS.xxx
function AxmStatusReadMotion (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;


// Return EndStatus(status of stop) register of specific axis.
// Caution: All Motion Product is different Hardware bit signal. Refer Manual and AXHS.xxx
function AxmStatusReadStop (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;


// Return Mechanical Signal Data(Current mechanical signal status)of specific axis.
// Caution: All Motion Product is different Hardware bit signal. Refer Manual and AXHS.xxx
function AxmStatusReadMechanical (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;


// Read current move velocity oo specific axis.
function AxmStatusReadVel (lAxisNo : LongInt; dpVel : PDouble) : DWord; stdcall;


// Return the error between Command Pos and Actual Pos of specific axis.
function AxmStatusReadPosError (lAxisNo : LongInt; dpError : PDouble) : DWord; stdcall;


// Verify the travel(traveled) distance to the final drive.
function AxmStatusReadDriveDistance (lAxisNo : LongInt; dpUnit : PDouble) : DWord; stdcall;


// Set use the Position information Type of specific Axis.
// uPosType  : Select Position Information Type (Actual position / Command position)
//    POSITION_LIMIT '0' - Normal action, In all round action.
//    POSITION_BOUND '1' - Position cycle type, dNegativePos ~ dPositivePos Range
// Caution(PCI-Nx04)
// - If count value exceeds the max value, it becomes min value when setting BOUND.
// The other way, count value exceeds the min value, it becomes max value.

// dPositivePos setting range : 0 ~ positive number
// dNegativePos setting range : negative number ~ 0
function AxmStatusSetPosType(lAxisNo : LongInt; uPosType : DWord; dPositivePos : Double; dNegativePos : Double) : DWord; stdcall;
// Return the Position Information Type of of specific axis.
function AxmStatusGetPosType(lAxisNo : LongInt; upPosType : PDWord; dpPositivePos : PDouble; dpNegativePos : PDouble) : DWord; stdcall;
// Set absolute encoder origin offset Position of specific axis. [Only for PCI-R1604-MLII]
function AxmStatusSetAbsOrgOffset(lAxisNo : LongInt; dOrgOffsetPos : Double) : DWord; stdcall;
// Return absolute encoder origin offset Position of specific axis.
function AxmStatusGetAbsOrgOffset(lAxisNo : LongInt; dpOrgOffsetPos : PDouble) : DWord; stdcall;


// Set the actual position of specific axis.
function AxmStatusSetActPos (lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// Return the actual position of specific axis.
function AxmStatusGetActPos (lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;
    function AxmStatusGetAmpActPos (lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;


// Set command position of specific axis.
function AxmStatusSetCmdPos (lAxisNo : LongInt; dPos : Double) : DWord; stdcall;
// Return command position of specific axis.
function AxmStatusGetCmdPos (lAxisNo : LongInt; dpPos : PDouble) : DWord; stdcall;
// Set command position and actual position of specific axi
// Only RTEX use
function AxmStatusSetPosMatch(lAxisNo : LongInt; dPos : Double) : DWord; stdcall;


// You can check motion status of specified axis at once by using this API.(Cmd, Act, Driver Status, Mechanical Signal, Universal Signal)
// Specify motion status information by dwMask setting of MOTION_INFO structure.
// dwMask : Display of the motion state (6bit) - ex) dwMask = Display all status if you set '0x1F'.
// The Level(In/Out) is not reflected which is set by user.
//    [0]        |    Command Position Read
//    [1]        |    Actual Position Read
//    [2]        |    Mechanical Signal Read
//    [3]        |    Driver Status Read
//    [4]        |    Universal Signal Input Read
//               |    Universal Signal Output Read
function AxmStatusReadMotionInfo(lAxisNo : LongInt; pMI : PMOTION_INFO) : DWord; stdcall;


// API for Network product only
// API for read AlarmCode of specified axis.
function AxmStatusRequestServoAlarm(lAxisNo : LongInt) : DWord; stdcall;
// API for read AlarmCode of specified axis.
// upAlarmCode      : Refer to Alarm Code of SERVOPACK.
// MR_J4_xxB        : Upper 16bit(Decimal value of 2 digits alarm code), Lower 16bit(Decimal value of 1digit detail alarm code)
// uReturnMode      : Set return condition of API.[Not used in SIIIH(MR-J4-xxB)]
// [0-Immediate]    : Return immediately after function execution.
// [1-Blocking]     : Does not return until the alarm code is read from SERVOPACK.
// [2-Non Blocking] : Does not return until the alarm code is read from SERVOPACK. but program is not blocked.
function AxmStatusReadServoAlarm(lAxisNo : LongInt; uReturnMode : DWord; upAlarmCode : PDWord) : DWord; stdcall;
// The API to recieve alarm string about specified error code.
function AxmStatusGetServoAlarmString(lAxisNo : LongInt; uAlarmCode : DWord; lAlarmStringSize : LongInt; szAlarmString : PChar) : DWord; stdcall;
    function AxmStatusReadServoAlarmString (lAxisNo : LongInt; lAlarmStringSize : LongInt; szAlarmString : char*) : DWord; stdcall;

// The API to Command to SERVOPACK for read Alarm History of specified axis.
function AxmStatusRequestServoAlarmHistory(lAxisNo : LongInt) : DWord; stdcall;
// The API to read SERVOPACK alarm history of specified axis.
// lpCount          : Number of read alarm history.
// upAlarmCode      : The array to return alarm history.
// uReturnMode      : Set return mode of this API.
// [0-Immediate]    : Return immediately after function execution.
// [1-Blocking]     : Not return until reading alarm code from SERVOPACK.
// [2-Non Blocking] : Not return until reading alarm code from SERVOPACK. but program is not blocked.
function AxmStatusReadServoAlarmHistory(lAxisNo : LongInt; uReturnMode : DWord; lpCount : PLongInt; upAlarmCode : PDWord) : DWord; stdcall;
// Clear SERVOPACK alarm history of specified axis.
function AxmStatusClearServoAlarmHistory(lAxisNo : LongInt) : DWord; stdcall;


//======== API related home. ==========================================================================================================================
// Set home sensor level of specific axis.
// uLevel : LOW(0), HIGH(1)
function AxmHomeSetSignalLevel (lAxisNo : LongInt; uLevel : DWord) : DWord; stdcall;
// Return home sensor level of specific axis.
function AxmHomeGetSignalLevel (lAxisNo : LongInt; upLevel : PDWord) : DWord; stdcall;

// Verify current home signal input status. Hoe signal can be set by user optionally by using AxmHomeSetMethod API.
// upStatus : OFF(0), ON(1)
function AxmHomeReadSignal (lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;


// Parameters related to origin detecting must be set in order to detect origin of relevant axis.
// If the initialization is done properly by using MotionPara setting file, no separate setting is required.
// In the setting of origin detecting method, direction of detecting proceed, signal to be used for origin, active level of origin sensor and detecting/no detecting of encoder Z phase are set.
// Caution : When the level is set wrong, it may operate + direction even though ? direction is set, and may cause problem in finding home.
// (Refer the guide part of AxmMotSaveParaAll for detail information. )
// Use AxmSignalSetHomeLevel for home level.
// HClrTim : HomeClear Time : Queue time for setting origin detecting Encoder value.
// HmDir(Home direction): DIR_CCW(0): - direction    , DIR_CW(1) = + direction   // HOffset ? traveled distance after detecting of origin.
// uZphas: Set whether to detect of encoder Z phase after completion of the 1st detecting of origin.
// HmSig : PosEndLimit(0) -> +Limit
//         NegEndLimit(1) -> -Limit
//         HomeSensor (4) -> origin sensor(universal input 0)
function AxmHomeSetMethod (lAxisNo : LongInt; lHmDir : LongInt; uHomeSignal : DWord; uZphas : DWord; dHomeClrTime : Double; dHomeOffset : Double) : DWord; stdcall;
// Return set parameters related to home.
function AxmHomeGetMethod (lAxisNo : LongInt; lpHmDir : PLongInt; upHomeSignal : PDWord; upZphas : PDWord; dpHomeClrTime : PDouble; dpHomeOffset : PDouble) : DWord; stdcall;


// Set Home Search Fine tunning Method (Don't care Setting by default).
// dHomeDogDistance[500 pulse]: Set Dog Length. (Unit = AxmMotSetMoveUnitPerPulse function Setting Unit)
// lLevelScanTime[100msec]: Set level status confirmation scan time. (msec[1~1000])
// dwFineSearchUse[USE]: Select find search method. (Default use 5Step, Select 0 use 3Step)
// dwHomeClrUse[USE]: Set After Home Search Automatically Command/Actual Position Set 0 value of  specific axis.
function AxmHomeSetFineAdjust(lAxisNo : LongInt; dHomeDogLength : Double; lLevelScanTime : LongInt; uFineSearchUse : DWord; uHomeClrUse : DWord) : DWord; stdcall;
// Return set Home  Search fine tunning Method parameters related to home.
function AxmHomeGetFineAdjust(lAxisNo : LongInt; dpHomeDogLength : PDouble; lpLevelScanTime : PLongInt; upFineSearchUse : PDWord; upHomeClrUse : PDWord) : DWord; stdcall;

    function AxmHomeSetInterlock (lAxisNo : LongInt; uInterlockMode : DWord; dInterlockData : Double) : DWord; stdcall;
    function AxmHomeGetInterlock (lAxisNo : LongInt; upInterlockMode : PDWord; dpInterlockData : PDouble) : DWord; stdcall;


// Detect through several steps in order to detect origin quickly and precisely. Now, set velocities to be used for each step.
// The time of origin detecting and the accuracy of origin detecting are decided by setting of these velocities.
// Set velocity of origin detecting of each axis by changing velocities of each step.
// (Refer the guide part of AxmMotSaveParaAll for detail information.)
// API which sets velocity to be used in origin detecting.
// [dVelFirst]- 1st move velocity   [dVelSecond]- velocity after detecting   [dVelThird]- the last velocity  [dvelLast]- index detecting and in order to detect precisely.
// [dAccFirst]- 1st move acceleration [dAccSecond]-acceleration after detecting.
function AxmHomeSetVel (lAxisNo : LongInt; dVelFirst : Double; dVelSecond : Double; dVelThird : Double; dVelLast : Double; dAccFirst : Double; dAccSecond : Double) : DWord; stdcall;
// Return set velocity to be used in origin detecting.
function AxmHomeGetVel (lAxisNo : LongInt; dpVelFirst : PDouble; dpVelSecond : PDouble; dpVelThird : PDouble; dpVelLast : PDouble; dpAccFirst : PDouble; dpAccSecond : PDouble) : DWord; stdcall;


// Start to detect origin.
// When origin detecting start API is executed, thread which will detect origin of relevant axis in the library is created automatically and it is automatically closed after carrying out of the origin detecting in sequence.
function AxmHomeSetStart (lAxisNo : LongInt) : DWord; stdcall;
// User sets the result of origin detecting optionally.
// When the detecting of origin is completed successfully by using origin detecting API, the result of detecting is set as HOME_SUCCESS.
// This API enables user to set result optionally without execution of origin detecting.
// uHomeResult Setup
// HOME_SUCCESS              = 0x01,
// HOME_SEARCHING            = 0x02,
// HOME_ERR_GNT_RANGE        = 0x10, // Gantry Home Range Over
// HOME_ERR_USER_BREAK       = 0x11, // User Stop Command
// HOME_ERR_VELOCITY         = 0x12, // Velocity is very slow and fast
// HOME_ERR_AMP_FAULT        = 0x13, // Servo Drive Alarm
// HOME_ERR_NEG_LIMIT        = 0x14, // (+)Limit sensor check (-)dir during Motion
// HOME_ERR_POS_LIMIT        = 0x15, // (-)Limit sensor check (+)dir during Motion
// HOME_ERR_NOT_DETECT       = 0x16, // not detect User set signal
// HOME_ERR_UNKNOWN          = 0xFF,
function AxmHomeSetResult (lAxisNo : LongInt; uHomeResult : DWord) : DWord; stdcall;
// Return the result of origin detecting.
// Verify detecting result of origin detection API. When detecting of origin is started, it sets as HOME_SEARCHING, and if the detecting of origin is failed the reason of failure is set. Redo origin detecting after eliminating of failure reasons.
function AxmHomeGetResult (lAxisNo : LongInt; upHomeResult : PDWord) : DWord; stdcall;


// Return progress rate of origin detection.
// Progress rate can be verified when origin detection is commenced. When origin detection is completed, return 100% whether success or failure. The success or failure of origin detection result can be verified by using GetHome Result API.
// upHomeMainStepNumber : Progress rate of Main Step .
// In case of gentry FALSE upHomeMainStepNumber : When 0 , only selected axis is in proceeding, home progress rate is indicated upHomeStepNumber.
// In case of gentry TRUE upHomeMainStepNumber : When 0, master home is in proceeding, master home progress rate is indicated upHomeStepNumber.
// In case of gentry TRUE upHomeMainStepNumber : When 10 , slave home is in proceeding, master home progress rate is indicated upHomeStepNumber .
// upHomeStepNumber     : Indicate progress rate against to selected axis.
// In case of gentry FALSE  : Indicate progress rate against to selected axis only.
// In case of gentry TRUE, progress rate is indicated by sequence of master axis and slave axis.
function AxmHomeGetRate (lAxisNo : LongInt; upHomeMainStepNumber : PDWord; upHomeStepNumber : PDWord) : DWord; stdcall;




//========= Position move API ===============================================================================================================

// If you want to set specified velocity unit in RPM(Revolution Per Minute),
// ex>    calculate rpm :
// 4500 rpm ?
// When unit/ pulse = 1 : 1, then it becomes pulse per sec, and
// if you want to set at 4500 rpm , then  4500 / 60 sec : 75 revolution / 1sec
// The number of pulse per 1 revolution of motor shall be known. This can be know by detecting of Z phase in Encoder.
// If 1 revolution:1800 pulse,  75 x 1800 = 135000 pulses are required.
// Operate by input Unit = 1, Pulse = 1800 into AxmMotSetMoveUnitPerPulse.

// Travel up to set distance or position.
// It moves by set velocity and acceleration up to the position set by absolute coordinates/ relative coordinates of specific axis.
// Velocity profile is set in AxmMotSetProfileMode API.
// It separates from API at the timing of pulse output start.
function AxmMoveStartPos (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;


// Travel up to set distance or position.
// It moves by set velocity and acceleration up to the position set by absolute coordinates/ relative coordinates of specific axis.
// Velocity profile is set in AxmMotSetProfileMode API
// It separates from API at the timing of pulse output finish.
function AxmMovePos (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;


// Move by set velocity.
// It maintain velocity mode move by velocity and acceleration  set against to specific axis.
// It separates from API at the timing of pulse output start.
// It moves toward to CW direction when Vel value is positive, CCW when negative.
function AxmMoveVel (lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;


// It maintain velocity mode move by velocity and acceleration  set against to specific multi-axis.
// It separates from API at the timing of pulse output start.
// It moves toward to CW direction when Vel value is positive, CCW when negative.
function AxmMoveStartMultiVel (lArraySize : LongInt; lpAxesNo : PLongInt; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble) : DWord; stdcall;

// Driving set velocity and acceleration rate of specified multi axis.
// Driving speed mode consistently according to SyncMode.
// It separates from API at the timing of pulse output start.
// It moves toward to CW direction when Vel value is positive, CCW when negative.
// dwSyncMode : Disable synchronous stop function(0), Only use syncronous stop function(1), Use Synchronous stop function for alarm(2)
function AxmMoveStartMultiVelEx(lArraySize : LongInt; lpAxesNo : PLongInt; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble; dwSyncMode : DWord) : DWord; stdcall;


// Driving in continuous speed mode with set speed and acceleration rate about specified multi axis.
// It separates from API at the timing of pulse output finish. The master axis moves at dVel speed, move at distance ratio of remaining axes.
// Only velocity of lowest axis number is read among corresponding chip.
function AxmMoveStartLineVel(lArraySize : LongInt; lpAxesNo : PLongInt; dpDis : PDouble; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;


// API which detects Edge of specific Input signal and makes emergency stop or slowdown stop.
// lDetect Signal : Select input signal to detect .
// lDetectSignal  : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
// Signal Edge    : Select edge direction of selected input signal (rising or falling edge).
//                  SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
// Move direction : CW when Vel value is positive, CCW when negative.
// SignalMethod   : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// Caution: When SignalMethod is used as EMERGENCY_STOP(0), acceleration/deceleration is ignored and it is accelerated to specific velocity and emergency stop.
//          lDetectSignal is PosEndLimit , in case of searching NegEndLimit(0,1) active status of signal level is detected.
function AxmMoveSignalSearch (lAxisNo : LongInt; dVel : Double; dAccel : Double; lDetectSignal : LongInt; lSignalEdge : LongInt; lSignalMethod : LongInt) : DWord; stdcall;


// API which detects Edge of specific Input signal and makes move by user-specified value.(MLIII : Sigma-5/7 only)
// dVel           : It moves toward to CW direction when Vel value is positive, CCW when negative.
// dAccel         : Acceleration value
// dDecel         : Deceleration value(Generally, set for 50 times of dAccel value)
// lDetectSignal  : HomeSensor(4)
// dDis           : It is driven relative to the user-specified position based on the detection position of the input signal.
// Notice :
//         - It can be driven in reverse direction when input dDis value in direction opposite to driving direction.
//         - If velocity is fast and dDis value is small, It can be driven in reverse to go to final position when after motor has detect signal and stop.
//         - Home sensor must be set 'LOW' or 'HIGH' before use this API.
function AxmMoveSignalSearchAtDis (lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double; lDetectSignal : LongInt; dDis : Double) : DWord; stdcall;


// API which detects signal set in specific axis and travels in order to save the position.
// In case of searching acting API to select and find desired signal, save the position and read the value using AxmGetCapturePos.
// Signal Edge   : Select edge direction of selected input signal. (rising or falling edge).
//                 SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
// Move direction      : CW when Vel value is positive, CCW when negative.
// SignalMethod  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// lDetect Signal: Select input signal to detect edge .SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
// lDetectSignal : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
// lTarget       : COMMAND(0), ACTUAL(1)
// Caution: When SignalMethod is used as EMERGENCY_STOP(0), acceleration/deceleration is ignored and it is accelerated to specific velocity and emergency stop.
// lDetectSignal is PosEndLimit , in case of searching NegEndLimit(0,1) active status of signal level is detected.
function AxmMoveSignalCapture (lAxisNo : LongInt; dVel : Double; dAccel : Double; lDetectSignal : LongInt; lSignalEdge : LongInt; lTarget : LongInt; lSignalMethod : LongInt) : DWord; stdcall;
// API which verifies saved position value in 'AxmMoveSignalCapture' API.
function AxmMoveGetCapturePos (lAxisNo : LongInt; dpCapPotition : PDouble) : DWord; stdcall;


// API which travels up to set distance or position.
// When execute API, it starts relevant motion action and escapes from API without waiting until motion is completed ”
function AxmMoveStartMultiPos (lArraySize : LongInt; lpAxisNo : PLongInt; dpPos : PDouble; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble) : DWord; stdcall;


// Travels up to the distance which sets multi-axis or position.
// It moves by set velocity and acceleration up to the position set by absolute coordinates of specific axis. specific axes.
function AxmMoveMultiPos (lArraySize : LongInt; lpAxisNo : PLongInt; dpPos : PDouble; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble) : DWord; stdcall;



// When execute API, it starts open-loop torque motion action of specific axis.(only for MLII, Sigma 5 servo drivers)
// dTroque        : Percentage value(%) of maximum torque. (negative value : CCW, positive value : CW)
// dVel           : Percentage value(%) of maximum velocity.
// dwAccFilterSel : LINEAR_ACCDCEL(0), EXPO_ACCELDCEL(1), SCURVE_ACCELDECEL(2)
// dwGainSel      : GAIN_1ST(0), GAIN_2ND(1)
// dwSpdLoopSel   : PI_LOOP(0), P_LOOP(1)
function AxmMoveStartTorque(lAxisNo : LongInt; dTorque : Double; dVel : Double; dwAccFilterSel : DWord; dwGainSel : DWord; dwSpdLoopSel : DWord) : DWord; stdcall;


// It stops motion during torque motion action.
// it can be only applied for AxmMoveStartTorque API.
function AxmMoveTorqueStop(lAxisNo : LongInt; dwMethod : DWord) : DWord; stdcall;



// To Move Set Position or distance
// Absolute coordinates / position set to the coordinates relative to the set speed / acceleration rate to drive of specific Axis.
// Velocity Profile is fixed Asymmetric trapezoid.
// Accel/Decel Setting Unit is fixed Unit/Sec^2
// When dAccel is not 0.0 and dDecel is 0.0, it accelerates from the previous speed to the specified speed without deceleration.
// If dAccel is not 0.0 and dDecel is not 0.0, acceleration from the previous speed to the specified speed without deceleration.
// If dAccel is 0.0 and dDecel is not 0.0, acceleration from the previous speed to the specified speed without deceleration.

// The following conditions must be satisfied.
// dVel[1] == dVel[3] must be satisfied.
// dVel [2] that can occur as a constant speed drive range is greater dPosition should be enough.
// Ex) dPosition = 10000;
// dVel[0] = 300., dAccel[0] = 200., dDecel[0] = 0.;    <== Acceleration
// dVel[1] = 500., dAccel[1] = 100., dDecel[1] = 0.;    <== Acceleration
// dVel[2] = 700., dAccel[2] = 200., dDecel[2] = 250.;  <== Acceleration, constant velocity, Deceleration
// dVel[3] = 500., dAccel[3] = 0.,   dDecel[3] = 150.;  <== Deceleration
// dVel[4] = 200., dAccel[4] = 0.,   dDecel[4] = 350.;  <== Deceleration
// Exits API at the point that pulse out starts.
function AxmMoveStartPosWithList(lAxisNo : LongInt; dPosition : Double; dpVel : PDouble; dpAccel : PDouble; dpDecel : PDouble; lListNum : LongInt) : DWord; stdcall;



// Is set by the distance to the target axis position or the position to increase or decrease the movement begins.
// lEvnetAxisNo    : Start condition occurs axis.
// dComparePosition: Conditions Occurrence Area of Start condition occurs axis.
// uPositionSource : Set Conditions Occurrence Area of Start condition occurs axis => COMMAND(0), ACTUAL(1)
// Cancellations after reservation AxmMoveStop, AxmMoveEStop, AxmMoveSStop use
// Motion Axis and Start condition occurs axis must be In same group(case by 2V04 In same module).
function AxmMoveStartPosWithPosEvent(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDccel : Double; lEventAxisNo : LongInt; dComparePosition : Double; uPositionSource : DWord) : DWord; stdcall;


// It slowdown stops by deceleration set for specific axis.
// dDecel : Deceleration value when stop.
function AxmMoveStop (lAxisNo : LongInt; dDecel : Double) : DWord; stdcall;
// It slowdown stops by deceleration set for specific axis.(PCI-Nx04 Only)
// This API can decelerating immediately refardless of current acceleration/deceleration state. Also, it can be used for limited drive.
// -- Applicable functions : AxmMoveStartPos, AxmMoveVel, AxmLineMoveEx2.
// dDecel : Deceleration rate value at stop.
// Note : Deceleration rate value should be greater than or equal to deceleration rate of initial setting.
// Note : When deceleration setting is set to time unit, It must be less than or equal to initial settling time.
function AxmMoveStopEx(lAxisNo : LongInt; dDecel : Double): DWord; stdcall;
// Stops specific axis emergently .
function AxmMoveEStop (lAxisNo : LongInt) : DWord; stdcall;
// Stops specific axis slow down.
function AxmMoveSStop (lAxisNo : LongInt) : DWord; stdcall;


//========= Overdrive API ============================================================================

// Overdrives position.
// Adjust number of specific pulse before the move of specific axis is finished.
// Cautions : In here when put in the position subjected to overdrive, as the travel distance is put into the position value of relative form,
//            position must be put in as position value of relative form.
function AxmOverridePos (lAxisNo : LongInt; dOverridePos : Double) : DWord; stdcall;


// Set the maximum velocity subjected to overdirve before velocity overdriving of specific axis.
// Caution : If the velocity overdrive is done 5 times, the max velocity shall be set among them.
function AxmOverrideSetMaxVel (lAxisNo : LongInt; dOverrideMaxVel : Double) : DWord; stdcall;

// Overdrive velocity.
// Set velocity variably during the move of specific axis. (Make sure to set variably during the motion.)
// Caution: Before use of AxmOverrideVel API, set the maximum velocity which can be set by AxmOverrideMaxVel
// EX> If velocity overdrive two times,
// 1. Set the highest velocity among the two as the highest setting velocity of AxmOverrideMaxVel.
// 2. Set the AxmOverrideVel  variably with the velocity in the moving of AxmMoveStartPos execution specific axis (including move API all) as the first velocity.
// 3. Set the AxmOverrideVel  variably with the velocity in the moving of specific axis (including move API all) as the 2nd velocity.
function AxmOverrideVel (lAxisNo : LongInt; dOverrideVel : Double) : DWord; stdcall;

// Overdrive velocity.
// Set velocity variably during the move of specific axis. (Make sure to set variably during the motion.)
// Caution: Before use of AxmOverrideVel API, set the maximum velocity which can be set by AxmOverrideMaxVel
// EX> If velocity overdrive two times,
// 1. Set the highest velocity among the two as the highest setting velocity of AxmOverrideMaxVel.
// 2. Set the AxmOverrideAccelVelDecel  variably with the velocity in the moving of AxmMoveStartPos execution specific axis (including move API all) as the first velocity.
// 3. Set the AxmOverrideAccelVelDecel  variably with the velocity in the moving of specific axis (including move API all) as the 2nd velocity.
function AxmOverrideAccelVelDecel (lAxisNo : LongInt; dOverrideVel : Double; dMaxAccel : Double; dMaxDecel : Double) : DWord; stdcall;

// Velocity overdrive at certain timing.
// API which becomes overdrive at the position when a certain position point and velocity to be overdrived
// lTarget : COMMAND(0), ACTUAL(1)
function AxmOverrideVelAtPos (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; dOverridePos : Double; dOverrideVel : Double; lTarget : LongInt) : DWord; stdcall;
// Override with specified velocity at specified times.
// lArraySize     : Set number of positions to override.
// *dpOverridePos : An array of positions to override. (It should be greater than or equal to set value at lArraySize.)
// *dpOverrideVel : Velocity array to be changed at position to override. (It should be greater than or equal to set value at lArraySize.)
// lTarget        : COMMAND(0), ACTUAL(1)
// dwOverrideMode : Specify how to start overriding.
//                : OVERRIDE_POS_START(0) - Start override at specified velocity at specified position.
//                : OVERRIDE_POS_END(1)   - Start override in advance to become specified velocity at specified position.
function AxmOverrideVelAtMultiPos (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lArraySize : LongInt; dpOverridePos : PDouble; dpOverrideVel : PDouble; lTarget : LongInt; uOverrideMode : DWord) : DWord; stdcall;

//========= Move API by master, slave gear ration. ===========================================================================

// Override with specified velocity/acceleration/deceleration at specified times.(MLII Only)
// lArraySize     : Set number of positions to override.
// *dpOverridePos : An array of positions to override. (It should be greater than or equal to set value at lArraySize.)
// *dpOverrideVel : Velocity array to be changed at position to override. (It should be greater than or equal to set value at lArraySize.)
// *dpOverrideAccelDecel : Acceleration/Deceleration array to be changed at position to override. (It should be greater than or equal to set value at lArraySize.)
// lTarget        : COMMAND(0), ACTUAL(1)
// dwOverrideMode : Specify how to start overriding.
//                : OVERRIDE_POS_START(0) - Start overriding at specified velocity at specified position.
//                : OVERRIDE_POS_END(1)   - Start overriding in advance to become specified velocity at specified position.
//                : OVERRIDE_POS_AUTO(2)  - Start overriding at specified velocity at specified position when in acceleration section.
//                                          Also, start overriding in advance to become specified velocity at specified position when in deceleration section.
function AxmOverrideVelAtMultiPos2 (lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lArraySize : LongInt; dpOverridePos : PDouble; dpOverrideVel : PDouble; dpOverrideAccelDecel : PDouble; lTarget : LongInt; uOverrideMode : DWord) : DWord; stdcall;

// In Electric Gear mode, set gear ratio between master axis and slave axis.
// dSlaveRatio : Gear ratio of slave against to master axis ( 0 : 0% , 0.5 : 50%, 1 : 100%)
function AxmLinkSetMode (lMasterAxisNo : LongInt; lSlaveAxisNo : LongInt; dSlaveRatio : Double) : DWord; stdcall;
// In Electric Gear mode, return gear ratio between master axis and slave axis.
function AxmLinkGetMode (lMasterAxisNo : LongInt; lpSlaveAxisNo : PLongInt; dpGearRatio : PDouble) : DWord; stdcall;
// Reset electric gear ration between Master axis and slave axis.
function AxmLinkResetMode (lMasterAxisNo : LongInt) : DWord; stdcall;


//======== API related to gentry===========================================================================================================================================================
// Motion module supports gentry move system control which two axes are linked mechanically..
// When set master axis for gentry control by using this API, relevant slave axis synchronizes with master axis and moves.
// However after setting of gentry, even if any move command or stop command is directed, they are ignored
// uSlHomeUse     : Whether to use home of slave axis or not ( 0 - 2)
//             (0 : Search home of master axis without using home of slave axis.)
//             (1 : Search home of master axis, slave axis. Compensating by applying slave dSlOffset value.)
//             (2 : Search home of master axis, slave axis. No compensating by applying slave dSlOffset value.))
// dSlOffset      : Offset value of slave axis
// dSlOffsetRange : Set offset value range of slave axis.
// Caution in use : When gentry is enabled, it is normal operation if the slave axis is verified as Inmotion by AxmStatusReadMotion API in its motion, and verified as True.
//                When slave axis is verified by AxmStatusReadMotion, if InMotion is False then Gantry Enable is not available, therefore verify whether alarm hits limit.
function AxmGantrySetEnable (lMasterAxisNo : LongInt; lSlaveAxisNo : LongInt; uSlHomeUse : DWord; dSlOffset : Double; dSlOffsetRange : Double) : DWord; stdcall;



// The method to know offset value of Slave axis.
// A. Servo-On both master and slave.
// B. After set uSlHomeUse = 2 in AxmGantrySetEnableAPI, then search home by using  AxmHomeSetStart API.
// C. After search home, twisted offset value of master axis and slave axis can be seen by reading command value of master axis.
// D. Read Offsetvalue, and put it into dSlOffset argument of AxmGantrySetEnable API.
// E. As dSlOffset value is the slave axis value against to master axis, put its value with reversed sign as ?dSlOffset.
// F. dSIOffsetRange means the range of Slave Offset, it is used to originate error when it is out of the specified range.
// G. If the offset has been input into AxmGantrySetEnable API, in AxmGantrySetEnable API,after  set uSlHomeUse = 1 then search home by using AxmHomeSetStart API.

// In gentry move, return parameter set by user.
function AxmGantryGetEnable (lMasterAxisNo : LongInt; upSlHomeUse : PDWord; dpSlOffset : PDouble; dpSlORange : PDouble; upGatryOn : PDWord) : DWord; stdcall;
// Motion module releases gentry move system control which two axes are linked mechanically.
function AxmGantrySetDisable (lMasterAxisNo : LongInt; lSlaveAxisNo : LongInt) : DWord; stdcall;


// Only for PCI-Rxx04-MLII.
// Set Synchronous compensation of Gentry System.
// lMasterGain, lSlaveGain : Set % value of Between the two axes about position deviation.
// lMasterGain, lSlaveGain : If Set Input 0 Not Use. Default value : 0%
function AxmGantrySetCompensationGain (lMasterAxisNo : LongInt; lMasterGain : LongInt; lSlaveGain : LongInt) : DWord; stdcall;
// Return Synchronous compensation of Gentry System.
function AxmGantryGetCompensationGain (lMasterAxisNo : LongInt; lpMasterGain : PLongInt; lpSlaveGain : PLongInt) : DWord; stdcall;


// Set position deviation range between master and slave.
// API for PCI-R1604 / PCI-R3200-MLIII only
// lMasterAxisNo : Gantry Master Axis No
// dErrorRange : Setting value for position deviation range.
// uUse : A value for mode setting.
//      ( 0 : Disable)
//      ( 1 : Normal mode)
//      ( 2 : Flag Latch mode)
//      ( 3 : Flag Latch mode + SSTOP when error is occured)
//      ( 4 : Flag Latch mode + ESTOP when error is occured)
function AxmGantrySetErrorRange(lMasterAxisNo : LongInt; dErrorRange : Double; uUse : DWord) : DWord; stdcall;
// Return setting value about position deviation range between master and slave.
function AxmGantryGetErrorRange(lMasterAxisNo : LongInt; dpErrorRange : PDouble; upUse : PDWord) : DWord; stdcall;
// Return result of comparing position deviation value between master and slave.
// dwpStatus : FALSE(0) -> Range of position deviation between master and slave is less than setting range. (Normal state)
//             TRUE(1)  -> Range of position deviation between master and slave is greater than setting range. (Abnormal state)
// It is returned 'AXT_RT_SUCCESS' only when Gantry Enable && Master/Slave's servo on state is satisfied.
// Call the 'AxmGantryReadErrorRangeComparePos', if you want to reset Latch Flag in case of latch mode.
function AxmGantryReadErrorRangeStatus(lMasterAxisNo : LongInt; dwpStatus : PDWord) : DWord; stdcall;
// Return position deviation value between master and slave.
// Maintain position deviation value at time of previous error occurrence until next error is occured.
// You should read only when 'dwpStatus' is 1. If you read ComparePos continuously, response speed will be slowed down by overload.
function AxmGantryReadErrorRangeComparePos(lMasterAxisNo : LongInt; dpComparePos : PDouble) : DWord; stdcall;





//====Regular interpolation API ============================================================================================================================================;
// Do linear interpolate.
// API which moves multi-axis linear interpolation by specifying start point and ending point. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the queue which moves linear interpolation by specifying start point and ending point in the specified  coordinates system.
// For the continuous interpolation move of linear profile, save it in internal queue and start by using AxmContiStart API.
function AxmLineMove (lCoord : LongInt; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;


// Do linear interpolate. (Software)
// API which moves multi-axis linear interpolation by specifying start point and ending point. It escapes from API after commencing of move. (Software Core)
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the queue which moves linear interpolation by specifying start point and ending point in the specified  coordinates system.
// For the continuous interpolation move of linear profile, save it in internal queue and start by using AxmContiStart API.
function AxmLineMoveEx2(lCoord : LongInt; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;


// Interpolate 2 axis arc
// API which moves arc interpolation by specifying start point, ending point and center point. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying start point, ending point and center point in the specified  coordinates system.
// For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
// lAxisNo = 2 axis array , dCenterPos = center point X,Y array , dEndPos = ending point X,Y array.
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
function AxmCircleCenterMove (lCoord : LongInt; lAxisNo : PLongInt; dCenterPos : PDouble; dEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;


// API which arc interpolation moves by specifying middle point and ending point. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying middle point and ending point in the specified  coordinates system.
// For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
// lAxisNo = 2 axis array , dMidPos = middle point, X,Y array , dEndPos = ending point X,Y array, lArcCircle = arc(0), circle(1)
function AxmCirclePointMove (lCoord : LongInt; lAxisNo : PLongInt; dMidPos : PDouble; dEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; lArcCircle : LongInt) : DWord; stdcall;


function AxmCirclePointMoveEx(lCoordNo : LongInt; lAxisNo : PLongInt; dpMidPos : PDouble; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; lArcCircle : LongInt; lArraySize : LongInt) : DWord; stdcall;


// API which arc interpolation moves by specifying start point, ending point and radius. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying start point, ending point and radius in the specified  coordinates system.
// For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
// lAxisNo = 2 axis array , dRadius = radius, dEndPos = ending point X,Y array , uShortDistance = small circle(0), large circle(1)
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
function AxmCircleRadiusMove (lCoord : LongInt; lAxisNo : PLongInt; dRadius : Double; dEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord) : DWord; stdcall;


// API which arc interpolation moves by specifying start point, revolution angle and radius. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode,
// it becomes Save API in the arc interpolation queue which moves by specifying start point, revolution angle and radius in the specified  coordinates system.
// For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
// lAxisNo = 2 axis array , dCenterPos = center point X,Y array , dAngle = angle.
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
function AxmCircleAngleMove (lCoord : LongInt; lAxisNo : PLongInt; dCenterPos : PDouble; dAngle : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;


//==== continuous interpolation API ============================================================================================================================================;
//Set continuous interpolation axis mapping in specific coordinates system.
//(Start axis mapping number from 0)
// Caution: In the axis mapping, the input must be started from smaller number.
//          In here, the axis of smallest number becomes master.
function AxmContiSetAxisMap (lCoord : LongInt; lSize : LongInt; lpRealAxesNo : PLongInt) : DWord; stdcall;
// Return continuous interpolation axis mapping in specific coordinates system.
function AxmContiGetAxisMap (lCoord : LongInt; lpSize : PLongInt; lpRealAxesNo : PLongInt) : DWord; stdcall;
    function AxmContiResetAxisMap (lCoordinate : LongInt) : DWord; stdcall;


// Set continuous interpolation axis absolute/relative mode in specific coordinates system.
// (Caution : available to use only after axis mapping)
// St travel distance calculation mode of specific axis.
//uAbsRelMode : POS_ABS_MODE '0' - absolute coordinate system
//              POS_REL_MODE '1' - relative coordinate system
function AxmContiSetAbsRelMode (lCoord : LongInt; uAbsRelMode : DWord) : DWord; stdcall;
// Return interpolation axis absolute/relative mode in specific coordinates system.
function AxmContiGetAbsRelMode (lCoord : LongInt; upAbsRelMode : PDWord) : DWord; stdcall;

// API which verifies whether internal Queue for the interpolation move is empty in specific coordinate system.
function AxmContiReadFree (lCoord : LongInt; upQueueFree : PDWord) : DWord; stdcall;
// API which verifies the number of interpolation move saved in internal Queue for the interpolation move in specific coordinate system
function AxmContiReadIndex (lCoord : LongInt; lpQueueIndex : PLongInt) : DWord; stdcall;

// API which deletes all internal Queue saved for the continuous interpolation move in specific coordinate system
function AxmContiWriteClear (lCoord : LongInt) : DWord; stdcall;


// Start registration of tasks to be executed in continuous interpolation at the specific  coordinate system. After call this API,
// all motion tasks to be executed before calling of AxmContiEndNode API are not execute actual motion, but are registered as continuous interpolation motion,
// and when AxmContiStart API is called, then the registered motions execute actually
function AxmContiBeginNode (lCoord : LongInt) : DWord; stdcall;
// Finish registration of tasks to be executed in continuous interpolation at the specific  coordinate system.
function AxmContiEndNode (lCoord : LongInt) : DWord; stdcall;


// Start continuous interpolation.
// if dwProfileset is  CONTI_NODE_VELOCITY(0), use continuous interpolation.
//                     CONTI_NODE_MANUAL(1)  , set profile interpolation use.
//                     CONTI_NODE_AUTO(2)    , use auto-profile interpolation.
function AxmContiStart (lCoord : LongInt; dwProfileset : DWord; lAngle : LongInt) : DWord; stdcall;
// API which verifies whether the continuous interpolation is moving in the specific coordinate system.
function AxmContiIsMotion (lCoord : LongInt; upInMotion : PDWord) : DWord; stdcall;


// API which verifies the index number of the continuous interpolation that is being moving currently while the continuous interpolation is moving in the specific coordinate system.
function AxmContiGetNodeNum (lCoord : LongInt; lpNodeNum : PLongInt) : DWord; stdcall;
// API which verifies the total number of continuous interpolation index that were set in  the specific coordinate system.
function AxmContiGetTotalNodeNum (lCoord : LongInt; lpNodeNum : PLongInt) : DWord; stdcall;



// Outputs digital signal from a specific motion segment.
// It should be used between the AxmContiBeginNode function and the AxmContiEndNode function.
// It is valid only for continuous interpolation drive function (ex: AxmLineMove, AxmCircleCenterMove, etc ...).
// Digital output is made earlier than the condition based on the end point of the next continuous interpolation drive function.
//
// lSize        : Number of IO contacts to be output simultaneously (1~8)
// lModuleNo    : If dwModuleType is 0, it is axis number. if dwModuleType is 1, it is Digital I / O Module No.
// dwModuleType : Motion I/O Output(Output of the slave itself)(0), Digital I/O Output(1)
//
// The following four parameters can be used to control multiple output contacts simultaneously by entering them in an array of lSize.
// lpBit          : Offset position for output contact
// lpOffOn        : Output value of corresponding output contact. LOW(0), HIGH(1)
// dpDistTime     : Distance(pulse) or Time(msec) ==> Based on the motion profile end point.
// lpDistTimeMode : Distance mode(0), Time mode(1) ==> Based on the motion profile end point.
function AxmContiDigitalOutputBit(lCoord : LongInt; lSize : LongInt; lModuleType : LongInt; lpModuleNo : PLongInt; lpBit : PLongInt; lpOffOn : PLongInt; dpDistTime : PDouble; lpDistTimeMode : PLongInt) : DWord; stdcall;

    function AxmContiReadStop (lCoord : LongInt; upStatus : PDWord) : DWord; stdcall;

    function AxmContiSetLineMoveVelMode (lCoord : LongInt; uVelMode : DWord; lMasterAxisNo : LongInt) : DWord; stdcall;
    function AxmContiGetLineMoveVelMode (lCoord : LongInt; upVelMode : PDWord; lpMasterAxisNo : PLongInt) : DWord; stdcall;

    function AxmContiSetCheckSoftLimit (lCoord : LongInt; uUse : DWord) : DWord; stdcall;
    function AxmContiGetCheckSoftLimit (lCoord : LongInt; upUse : PDWord) : DWord; stdcall;

    function AxmContiSetConnectionRadius (lCoord : LongInt; dRadius : Double) : DWord; stdcall;
    function AxmContiSetConnectionMaxCentripetalAccel (lCoord : LongInt; dMaxAccel : Double) : DWord; stdcall;



//==================== trigger API ===============================================================================================================================
// Precautions : If you want set trigger position, you should be set according to setting status of Unit/Pulse.
//               If trigger position unit is smaller than Unit/Pulse, you can't output to desired position exactly because minimum unit will be set to UNIT/PULSE.

// Set whether to use of trigger function, output level, position comparator, trigger signal delay time and trigger output mode ino specific axis.
//  dTrigTime  : trigger output time
//             : 1usec - max 50msec ( set 1 - 50000)
//  upTriggerLevel  : whether to use or not use     => LOW(0), HIGH(1), UNUSED(2), USED(3)
//  uSelect         : Standard position to use    => COMMAND(0), ACTUAL(1)
//  uInterrupt      : set interrupt        => DISABLE(0), ENABLE(1)

// Set trigger signal delay time , trigger output level and trigger output method in specific axis.
function AxmTriggerSetTimeLevel (lAxisNo : LongInt; dTrigTime : Double; uTriggerLevel : DWord; uSelect : DWord; uInterrupt : DWord) : DWord; stdcall;
// Return trigger signal delay time , trigger output level and trigger output method to specific axis.
function AxmTriggerGetTimeLevel (lAxisNo : LongInt; dpTrigTime : PDouble; upTriggerLevel : PDWord; upSelect : PDWord; upInterrupt : PDWord) : DWord; stdcall;


//  uMethod :   PERIOD_MODE   0x0 : cycle trigger method using trigger position value
//              ABS_POS_MODE  0x1 : Trigger occurs at trigger absolute position,  absolute position method
//  dPos : in case of cycle selection : the relevant position  for output by position and position.
// in case of absolute selection: The position on which to output, If same as this position then output goes out unconditionally.
function AxmTriggerSetAbsPeriod (lAxisNo : LongInt; uMethod : DWord; dPos : Double) : DWord; stdcall;
// Return whether to use of trigger function, output level, position comparator, trigger signal delay time and trigger output mode to specific axis.
function AxmTriggerGetAbsPeriod (lAxisNo : LongInt; upMethod : PDWord; dpPos : PDouble) : DWord; stdcall;


//  Output the trigger by regular interval from the starting position to the ending position specified by user.
function AxmTriggerSetBlock (lAxisNo : LongInt; dStartPos : Double; dEndPos : Double; dPeriodPos : Double) : DWord; stdcall;
// Read trigger setting value of 'AxmTriggerSetBlock' API.
function AxmTriggerGetBlock (lAxisNo : LongInt; dpStartPos : PDouble; dpEndPos : PDouble; dpPeriodPos : PDouble) : DWord; stdcall;


// User outputs a trigger pulse.
function AxmTriggerOneShot (lAxisNo : LongInt) : DWord; stdcall;
// User outputs a trigger pulse after several seconds.
function AxmTriggerSetTimerOneshot (lAxisNo : LongInt; lmSec : LongInt) : DWord; stdcall;
// Output absolute position trigger infinite absolute position output.
function AxmTriggerOnlyAbs (lAxisNo : LongInt; lTrigNum : LongInt; dpTrigPos : PDouble) : DWord; stdcall;
// Reset trigger settings.
function AxmTriggerSetReset (lAxisNo : LongInt) : DWord; stdcall;


//======== CRC( Remaining pulse clear API) =====================================================================
//Level   : LOW(0), HIGH(1), UNUSED(2), USED(3)
//uMethod : Available to set the width of remaining pulse eliminating output signal pulse in 2 - 6.
//          0: Don't care , 1: Don't care, 2: 500 uSec, 3:1 mSec, 4:10 mSec, 5:50 mSec, 6:100 mSec
//Set whether to use CRC signal in specific axis and output level.
function AxmCrcSetMaskLevel (lAxisNo : LongInt; uLevel : Dword; lMethod : Dword) : DWord; stdcall;
// Return whether to use CRC signal of specific axis and output level.
function AxmCrcGetMaskLevel (lAxisNo : LongInt; upLevel : PDWord; upMethod : PDword) : DWord; stdcall;


//uOnOff  : Whether to generate CRC signal to the Program or not.  (FALSE(0),TRUE(1))
// Force to generate CRC signal to the specific axis.
function AxmCrcSetOutput (lAxisNo : LongInt; uOnOff : DWord) : DWord; stdcall;
// Return whether to forcedly generate CRC signal of specific axis.
function AxmCrcGetOutput (lAxisNo : LongInt; upOnOff : PDWord) : DWord; stdcall;



//====== MPG(Manual Pulse Generation) API ===========================================================
// lInputMethod : Available to set 0-3. 0:OnePhase, 1:TwoPhase1, 2:TwoPhase2, 3:TwoPhase4
// lDriveMode   : Available to set 0-5
//                0 : MPG continuous mode,             1 : MPG PRESET mode (Travel up to specific pulse), 2 : COMMAND ABSOLUTE MPG PRESET mode
//                3 : ACTUAL ABSOLUTE MPG PRESET mode, 4 : COMMAND ABSOLUTE ZERO MPG PRESET mode,         5 : ACTUAL ABSOLUTE ZERO MPG PRESET mode
// MPGPos        : the travel distance by every MPG input signal
// MPGdenominator: Divide value in MPG(Enter manual pulse generating device)movement
// dMPGnumerator : Product value in MPG(Enter manual pulse generating device)movement
// dwNumerator   : Available to set max(from 1 to  64)
// dwDenominator : Available to set max(from 1 to  4096)
// dMPGdenominator = 4096 and MPGnumerator=1 mean that
// the output is 1 by 1 pulse as 1:1 if one turn of MPG is 200pulse.
// If dMPGdenominator = 4096 and MPGnumerator=2 , then it means the output is 2 by 2 pulse as 1:2.
// In here, MPG PULSE = ((Numerator) * (Denominator)/ 4096 ) It’s the calculation which outputs to the inside of chip.

// Set MPG input method, Drive move mode, travel distance, MPG velocity in specific axis.
function AxmMPGSetEnable (lAxisNo : LongInt; lInputMethod : LongInt; lDriveMode : LongInt; dMPGPos : Double; dVel : Double; dAcc : Double) : DWord; stdcall;
// Return MPG input method, Drive move mode, travel distance, MPG velocity in specific axis.
function AxmMPGGetEnable (lAxisNo : LongInt; lpInputMethod : PLongInt; lpDriveMode : PLongInt; dpMPGPos : PDouble; dpVel : PDouble) : DWord; stdcall;


// Set the pulse ratio to travel per pulse in MPG drive move mode to specific axis.
function AxmMPGSetRatio (lAxisNo : LongInt; dMPGnumerator : Double; dMPGdenominator : Double) : DWord; stdcall;
// Return the pulse ratio to travel per pulse in MPG drive move mode to specific axis.
function AxmMPGGetRatio (lAxisNo : LongInt; dpMPGnumerator : PDouble; dpMPGdenominator : PDouble) : DWord; stdcall;

// Release MPG drive settings to specific axis.
function AxmMPGReset (lAxisNo : LongInt) : DWord; stdcall;



//======= Helical move ===========================================================================
// API which moves helical interpolation by specifying start point, ending point and center point to specific coordinate system.
// API which moves helical continuous interpolation by specifying start point, ending point and center point to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
// API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
//dCenterPos = center point X,Y , dEndPos = ending point X,Y.
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
function AxmHelixCenterMove (lCoord : LongInt; dCenterXPos : Double; dCenterYPos : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;


// API which moves helical interpolation by specifying start point, ending point and radius to specific coordinate system.
// API which moves helical continuous interpolation by specifying middle point and ending point to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
// API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
// dMidPos = middle point X,Y  , dEndPos = ending point X,Y
function AxmHelixPointMove (lCoord : LongInt; dMidXPos : Double; dMidYPos : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;


// API which moves helical interpolation by specifying start point, ending point and radius to specific coordinate system.
// API which moves helical continuous interpolation by specifying middle point ,ending point and radius to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
// API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
// dRadius = radius, dEndPos = ending point X,Y  , uShortDistance = small circle(0), large circle(1)
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
function AxmHelixRadiusMove (lCoord : LongInt; dRadius : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord) : DWord; stdcall;


// API which moves helical interpolation by specifying start point, revolution angle and radius to specific coordinate system.
// API which moves helical continuous interpolation by specifying start point , revolution angle and radius to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
// API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
// dCenterPos = center point X,Y , dAngle = angle.
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
function AxmHelixAngleMove (lCoord : LongInt; dCenterXPos : Double; dCenterYPos : Double; dAngle : Double; dZPos : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;



//======== Spline move ===========================================================================

// It’s not used with AxmContiBeginNode and AxmContiEndNode together.
// API which moves spline continuous interpolation. API which saves in internal Queue in order to move the arc continuous interpolation.
//It is started using AxmContiStart API. ( It is used with continuous interpolation API together)

// lPosSize : Minimum more than 3 pieces.
// Enter 0 as for dPoZ value when it is used with 2 axes.
// Enter 3 piece as for axis mapping and dPosZ value when it is used with 3axes.
function AxmSplineWrite (lCoord : LongInt; lPosSize : LongInt; dpPosX : PDouble; dpPosY : PDouble; dVel : Double; dAccel : Double; dDecel : Double; dPosZ : Double; lPointFactor : LongInt) : DWord; stdcall;


//======== Compensation Table ====================================================================
// API which set the parameters for using the geometric compensation feature (Mechatrolink-II products)
// lNumEntry : minimum entries are 2, maximum entries are 512.
// dStartPos : starting relative position to apply the compensation.
// dpPosition, dpCorrection : arrays of position and correction values.
// bRollOver : enable/disable the roll over feature if the table can not cover the motor travel distance.
function AxmCompensationSet (lAxisNo : LongInt; lNumEntry : LongInt; dStartPos : Double; dpPosition : PDouble; dpCorrection : PDouble; lRollOver : LongInt) : DWord; stdcall;
// Return the number of entry, start position, array of position for moving, array of correction for compensating, setting RollOver feature on specific axis.
function AxmCompensationGet (lAxisNo : LongInt; lpNumEntry : PLongInt; dpStartPos : PDouble; dpPosition : PDouble; dpCorrection : PDouble; lpRollOver : PLongInt) : DWord; stdcall;

// API which enable/disable the compensation feature.
function AxmCompensationEnable (lAxisNo : LongInt; lEnable : LongInt) : DWord; stdcall;
// Return the setting enable/disable the compensation feature on specific axis.
function AxmCompensationIsEnable (lAxisNo : LongInt; lpEnable : PLongInt) : DWord; stdcall;
// Return Current Position Compensation Value
function AxmCompensationGetCorrection(lAxisNo : LongInt; dpCorrection : PDouble) : DWord; stdcall;

// Functions that make settings related to backlash
// > lBacklashDir: Set driving direction to apply backlash compensation (set same as home search direction)
//   - [0] -> Applies the specified backlash when the Command Position value is driven in (+) direction.
//   - [1] -> Applies the specified backlash when the Command Position value is driven in (-) direction.
//   - Ex1) When lBacklashDir is 0 and backlash is 0.01, the actual moving position becomes 100.01 when moving from 0.0 to 100.0
//   - Ex2) When lBacklashDir is 0 and backlash is 0.01, the actual moving position becomes -100.0 when moving from 0.0 to> -100.0
//   ※ NOTANDUM
//   - For accurate backlash compensation, move backward (+) or (-) by the amount of backlash at the end of the home search,
//     complete the home search, and use backlash compensation.
//     If backlash_dir is driven by backlash_dir [1] (-) and backlash_dir is set to [0] (+) if backlash_dir is driven by backlash_dir.
// > dBacklash: Sets the amount of backlash that occurs in the direction of change from the mechanical direction to the opposite direction.
// { RETURN VALUE }
//   - [0] -> When Backlash setup succeeded
function AxmCompensationSetBacklash(lAxisNo : LongInt; lBacklashDir : LongInt; dBacklash : Double) : DWord; stdcall;
// Returns the configuration related to backlash.
function AxmCompensationGetBacklash(lAxisNo : LongInt; lpBacklashDir : PLongInt; dpBacklash : PDouble) : DWord; stdcall;
// Function to set / check whether to use backlash
// > dwEnable: Specify whether to use backlash compensation
//   - [0]DISABLE -> Disable backlash compensation
//   - [1]ENABLE  -> Enable backlash compensation
// { RETURN VALUE }
//   - [0]    -> Backlash setting When return is successful
//   - [4303] -> When the backlash compensation function is not set
function AxmCompensationEnableBacklash(lAxisNo : LongInt; dwEnable : DWord) : DWord; stdcall;
function AxmCompensationIsEnableBacklash(lAxisNo : LongInt; dwpEnable : PDWord) : DWord; stdcall;
// When backlash compensation function is used, it moves left and right by the amount of backlash to automatically align the position of the equipment (used once after servo-on)
// > dVel: Movement speed[unit / sec]
// > dAccel: Movement acceleration[unit / sec^2]
// > dAccel: Movement deceleration[unit / sec^2]
// > dWaitTime: Waiting time to return to original position after driving backlash amount[msec]
// { RETURN VALUE }
//   - [0]    -> When positioning for backlash compensation is successful
//   - [4303] -> When the backlash compensation function is not set
function AxmCompensationSetLocating(lAxisNo : LongInt; dVel : Double; dAccel : Double; dDecel : Double; dWaitTime : Double) : DWord; stdcall;


//======== Electronic CAM ========================================================================
// API which set the parameters for using the Ecam feature (Mechatrolink-II products)
// lAxisNo : one slave axis only has one master axis.
// lMasterAxis : one master axis can have more than one slave axis.
// lNumEntry : minimum entries are 2, maximum entries are 512.
// dMasterStartPos : starting relative position to apply Ecam on master axis.
// dpMasterPos, dpSlavePos : arrays of position values on master and slave axis.
function AxmEcamSet (lAxisNo : LongInt; lMasterAxis : LongInt; lNumEntry : LongInt; dMasterStartPos : Double; dpMasterPos : PDouble; dpSlavePos : PDouble) : DWord; stdcall;
function AxmEcamSetWithSource(lAxisNo : LongInt; lMasterAxis : LongInt; lNumEntry : LongInt; dMasterStartPos : Double; dpMasterPos : PDouble; dpSlavePos : PDouble;  dwSource : DWord) : DWord; stdcall;
// Return the number of master axis, entries, start position of master axis, array of position on master axis, array of position on slave axis.
function AxmEcamGet (lAxisNo : LongInt; lpMasterAxis : PLongInt; lpNumEntry : PLongInt; dpMasterStartPos : PDouble; dpMasterPos : PDouble; dpSlavePos : PDouble) : DWord; stdcall;
function AxmEcamGetWithSource(lAxisNo : LongInt; lpMasterAxis : PLongInt; lpNumEntry : PLongInt; dpMasterStartPos : PDouble; dpMasterPos : PDouble; dpSlavePos : PDouble; dwpSource : PDWord) : DWord; stdcall;

// API which enable the Ecam feature on slave axis.
function AxmEcamEnableBySlave (lAxisNo : LongInt; lEnable : LongInt) : DWord; stdcall;
// API which enable the Ecam feature on corresponding slave axes.
function AxmEcamEnableByMaster (lAxisNo : LongInt; lEnable : LongInt) : DWord; stdcall;
// Return the setting enable/disable the Ecam feature on slave axis.
function AxmEcamIsSlaveEnable (lAxisNo : LongInt; lpEnable : PLongInt) : DWord; stdcall;


//======== Servo Status Monitor =====================================================================================
// Set up for exception handling function of specified axis. (MLII : Sigma-5 and SIIIH : MR_J4_xxB only)
// dwSelMon(0~3): select monitoring information.
//          [0] : Torque
//          [1] : Velocity of motor
//          [2] : Accel. of motor
//          [3] : Decel. of motor
//          [4] : Position error between Cmd. position and Act. position.
// dwActionValue: Set reference value of abnormal operation. According to each information, meaning of setting value is different.
//          [0] : Not handling exception about selected monitoring information in dwSelMon.
//          [1] : Apply handling exception about selected monitoring information in dwSelMon.
// dwAction(0~3): Set exception handling method when surveillance information is confirmed more than dwActionValue.
//          [0] : Warning(setting flag only)
//          [1] : Warning(setting flag) + Slow-down stop
//          [2] : Warning(setting flag) + Emergency stop
//          [3] : Warning(setting flag) + Emergency stop + Servo-Off
// ※ Note : You can be set exception handling separetely for 5 SelMon info. If you don't want to exception handling in use,
//           be sure to set the ActionValue of specific SelMon info to 0 to disable the monitoring function.
// Set exception function of specific axis. (Only for MLII, Sigma-5)
function AxmStatusSetServoMonitor(lAxisNo : LongInt; dwSelMon : DWord; dActionValue : Double; dwAction : DWord) : DWord; stdcall;
// Return exception function of specific axis. (Only for MLII, Sigma-5)
function AxmStatusGetServoMonitor(lAxisNo : LongInt; dwSelMon : DWord; dpActionValue : PDouble; dwpAction : PDWord) : DWord; stdcall;
// Set exception function usage of specific axis. (Only for MLII, Sigma-5)
function AxmStatusSetServoMonitorEnable(lAxisNo : LongInt; dwEnable : DWord) : DWord; stdcall;
// Return exception function usage of specific axis. (Only for MLII, Sigma-5)
function AxmStatusGetServoMonitorEnable(lAxisNo : LongInt; dwpEnable : PDWord) : DWord; stdcall;


// Return exception function execution result Flag of specific axis. Auto reset after function execution. (Only for MLII, Sigma-5)
function AxmStatusReadServoMonitorFlag(lAxisNo : LongInt; dwSelMon : DWord; dwpMonitorFlag : PDWord; dpMonitorValue : PDouble) : DWord; stdcall;
// Return exception function monitoring information of specific axis. (Only for MLII, Sigma-5)
function AxmStatusReadServoMonitorValue(lAxisNo : LongInt; dwSelMon : DWord; dpMonitorValue : PDouble) : DWord; stdcall;
// Set load ratio monitor function of specific axis. (Only for MLII, Sigma-5)
// (MLII, Sigma-5, dwSelMon : 0 ~ 2) ==
// dwSelMon = 0 : Accumulated load ratio
// dwSelMon = 1 : Regenerative load ratio
// dwSelMon = 2 : Reference Torque load ratio
// (SIIIH, MR_J4_xxB, dwSelMon : 0 ~ 4) ==
//     [0] : Assumed load inertia ratio(0.1times)
//     [1] : Regeneration load factor(%)
//     [2] : Effective load factor(%)
//     [3] : Peak load factor(%)
//     [4] : Current feedback(0.1%)
// (RTEX, A5Nx, dwSelMon : 0 ~ 4) ==
//     [0] : Command Torque(0.1%)
//     [1] : Regenertive load ratio(0.1%)
//     [2] : Overload ratio(0.1%)
//     [3] : Inertia ratio(%)
function AxmStatusSetReadServoLoadRatio(lAxisNo : LongInt; dwSelMon : DWord) : DWord; stdcall;
// Return load ratio of specific axis. (Only for MLII, Sigma-5)
function AxmStatusReadServoLoadRatio(lAxisNo : LongInt; dpMonitorValue : PDouble) : DWord; stdcall;


//======== Only for PCI-R1604-RTEX ==================================================================================
// Set RTEX A4Nx Scale Coefficient. (Only for RTEX, A4Nx)
function AxmMotSetScaleCoeff(lAxisNo : LongInt; lScaleCoeff : LongInt) : DWord; stdcall;
// Return RTEX A4Nx Scale Coefficient. (Only for RTEX, A4Nx)
function AxmMotGetScaleCoeff(lAxisNo : LongInt; lpScaleCoeff : PLongInt) : DWord; stdcall;

// Edge detection of specific Input Signal that stop or slow down to stop the function.
// lDetectSignal : Select input signal to detect edge.
//                 PosEndLimit(0), NegEndLimit(1), HomeSensor(4)
// lSignalEdge   : Select edge direction of selected input signal.
//                 SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
// lSignalMethod : Select stop method.
//                 EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// * Move direction : CW(dVel is positive), CCW(dVel is negative)
// * Note : Acceleration / deceleration is ignored when lSignalMethod is EMERGENCY_STOP(0), and acceleration suddenly stops at the specified speed.
//          If lDetectSignal is PosEndLimit(0) or NegEndLimit(1) in use PCI-Nx04, the level of the signal active state is detected.
function AxmMoveSignalSearchEx(lAxisNo : LongInt; dVel : Double; dAccel : Double; lDetectSignal : LongInt; lSignalEdge : LongInt; lSignalMethod : LongInt) : DWord; stdcall;

//---------------------------------------------------------------------------------------------------------------------

//======== Only for PCI-R1604-MLII ==================================================================================
// Move to the set absolute position.
// Velocity profile use Trapezoid.
// Exits API at the point that pulse out starts.
// Always position(include -position), Velocity, Accel/Deccel Change possible.
function AxmMoveToAbsPos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;
// Return current drive velocity of specific axis.
function AxmStatusReadVelEx(lAxisNo : LongInt; dpVel : PDouble) : DWord; stdcall;

//-------------------------------------------------------------------------------------------------------------------

//======== Only for PCI-R1604-SSCNETIIIH ==================================================================================
// Set electric ratio. This parameter saved Non-volatile memory.
// Default value(lNumerator : 4194304(2^22), lDenominator : 10000)
// MR-J4-B is don't Setting electric ratio, Must be set from the host controller.
// No.PA06, No.PA07 of Existing Pulse type Servo Driver(MR-J4-A)
function AxmMotSetElectricGearRatio(lAxisNo : LongInt; lNumerator  : LongInt; lDenominator : LongInt) : DWord; stdcall;

// Return electric ratio of specific axis.
function AxmMotGetElectricGearRatio(lAxisNo : LongInt; lpNumerator : PLongInt; lpDenominator : PLongInt) : DWord; stdcall;


// Set limit torque value of specific axis.
// Forward, Backward drive torque limit function.
// Setting range 1 ~ 1000
// 0.1% of the maximum torque are controlled.
function AxmMotSetTorqueLimit(lAxisNo : LongInt; dbPluseDirTorqueLimit : Double; dbMinusDirTorqueLimit : Double) : DWord; stdcall;

// Return torque limit value of specific axis.
function AxmMotGetTorqueLimit(lAxisNo : LongInt; dbpPluseDirTorqueLimit : PDouble; dbpMinusDirTorqueLimit : PDouble) : DWord; stdcall;

    function AxmMotSetTorqueLimitEx (lAxisNo : LongInt; dbPlusDirTorqueLimit : Double; dbMinusDirTorqueLimit : Double) : DWord; stdcall;

    function AxmMotGetTorqueLimitEx (lAxisNo : LongInt; dbpPlusDirTorqueLimit : PDouble; dbpMinusDirTorqueLimit : PDouble) : DWord; stdcall;


// Sets the torque limit value of the specified axis.
// Limit the torque value during forward and reverse drive.
// The setting range is from 1 to 3000 (0.1% ~ 300.0%).
// It is controlled in 0.1% of maximum torque.
// dPosition : Position information to change the torque limit value (applicable when event with same position information and target position occur).
// lTarget   : COMMAND(0), ACTUAL(1)
function AxmMotSetTorqueLimitAtPos(lAxisNo : LongInt; dbPlusDirTorqueLimit : Double; dbMinusDirTorqueLimit : Double; dPosition : Double; lTarget : LongInt) : DWord; stdcall;


// Get the torque limit value of the specified axis.
function AxmMotGetTorqueLimitAtPos(lAxisNo : LongInt; dbpPlusDirTorqueLimit : PDouble; dbpMinusDirTorqueLimit : PDouble; dpPosition : PDouble; lpTarget : PLongInt) : DWord; stdcall;


function AxmMotSetTorqueLimitEnable(lAxisNo : LongInt; DWORD : DWord) : DWord; stdcall;


function AxmMotGetTorqueLimitEnable(lAxisNo : LongInt; upUse : PDWord) : DWord; stdcall;


function AxmOverridePosSetFunction(lAxisNo : LongInt; dwUsage : DWord; lDecelPosRatio: LongInt; dReserved : Double) : DWord; stdcall;
function AxmOverridePosGetFunction(lAxisNo : LongInt; dwpUsage : PDWord; lpDecelPosRatio: PLongInt; dpReserved : PDouble) : DWord; stdcall;


// Controls the digital output value set at a specific position on the specified axis.
// lModuleNo   : Module Number
// lOffset     : Offset position for output contact
// uValue      : OFF(0)
//             : OM(1)
//             : Function Clear(0xFF)
// dPosition   : DO output value is changed (executed when an event occurs in which the position information is the same as the target position).
// lTarget     : COMMAND(0), ACTUAL(1)
function AxmSignalSetWriteOutputBitAtPos(lAxisNo : LongInt; lModuleNo : LongInt; lOffset : LongInt; uValue : DWord; dPosition : Double; lTarget : LongInt) : DWord; stdcall;
// Get the digital output value control setting set at a specific position on the specified axis.
function AxmSignalGetWriteOutputBitAtPos(lAxisNo : LongInt; lpModuleNo : PLongInt; lpOffset : PLongInt; upValue : PDWord; dpPosition : PDouble; lpTarget : PLongInt) : DWord; stdcall;


//-------------------------------------------------------------------------------------------------------------------

function AxmAdvVSTSetParameter(lCoord : LongInt; uISTSize : DWord; dbpFrequency : PDouble; dbpDampingRatio : PDouble; upImpulseCount : PDWord) : DWord; stdcall;
function AxmAdvVSTGetParameter(lCoord : LongInt; upISTSize : PDWord; dbpFrequency : PDouble; dbpDampingRatio : PDouble; upImpulseCount : PDWord) : DWord; stdcall;

function AxmAdvVSTSetEnabele(lCoord : LongInt; uISTEnable : DWord) : DWord; stdcall;
function AxmAdvVSTGetEnabele(lCoord : LongInt; upISTEnable : PDWord) : DWord; stdcall;


function AxmAdvLineMove(lCoordinate : LongInt; dpPosition : PDouble; dMaxVelocity : Double; dStartVel : Double; dStopVel : Double; dMaxAccel : Double; dMaxDecel : Double) : DWord; stdcall;

function AxmAdvOvrLineMove(lCoordinate : LongInt; dpPosition : PDouble; dMaxVelocity : Double; dStartVel : Double; dStopVel : Double; dMaxAccel : Double; dMaxDecel : Double; lOverrideMode : LongInt) : DWord; stdcall;

function AxmAdvCircleCenterMove(lCoord : LongInt; lpAxisNo : PLongInt; dpCenterPos : PDouble; dpEndPos : PDouble; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;

function AxmAdvCirclePointMove(lCoord : LongInt; lpAxisNo : PLongInt; dpMidPos : PDouble; dpEndPos : PDouble; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; lArcCircle : LongInt) : DWord; stdcall;

function AxmAdvCircleAngleMove(lCoord : LongInt; lpAxisNo : PLongInt; dpCenterPos : PDouble; dAngle : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;

function AxmAdvCircleRadiusMove(lCoord : LongInt; lpAxisNo : PLongInt; dRadius : Double; dEndPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord) : DWord; stdcall;

function AxmAdvOvrCircleRadiusMove(lCoord : LongInt; lpAxisNo : PLongInt; dRadius : Double; dEndPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord; lOverrideMode : LongInt) : DWord; stdcall;



function AxmAdvHelixCenterMove(lCoord : LongInt; dCenterXPos : Double; dCenterYPos : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;

function AxmAdvHelixPointMove(lCoord : LongInt; dMidXPos : Double; dMidYPos : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;

function AxmAdvHelixAngleMove(lCoord : LongInt; dCenterXPos : Double; dCenterYPos : Double; dAngle : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;

function AxmAdvHelixRadiusMove(lCoord : LongInt; dRadius : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord) : DWord; stdcall;

function AxmAdvOvrHelixRadiusMove(lCoord : LongInt; dRadius : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord; lOverrideMode : LongInt) : DWord; stdcall;


function AxmAdvScriptLineMove(lCoordinate : LongInt; dpPosition : PDouble; dMaxVelocity : Double; dStartVel : Double; dStopVel : Double; dMaxAccel : Double; dMaxDecel : Double; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptOvrLineMove(lCoordinate : LongInt; dpPosition : PDouble; dMaxVelocity : Double; dStartVel : Double; dStopVel : Double; dMaxAccel : Double; dMaxDecel : Double; lOverrideMode : LongInt; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptCircleCenterMove(lCoord : LongInt; lpAxisNo : PLongInt; dpCenterPos : PDouble; dpEndPos : PDouble; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptCirclePointMove(lCoord : LongInt; lpAxisNo : PLongInt; dpMidPos : PDouble; dpEndPos : PDouble; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; lArcCircle : LongInt; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptCircleAngleMove(lCoord : LongInt; lpAxisNo : PLongInt; dpCenterPos : PDouble; dAngle : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptCircleRadiusMove(lCoord : LongInt; lpAxisNo : PLongInt; dRadius : Double; dpEndPos : PDouble; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptOvrCircleRadiusMove(lCoord : LongInt; lpAxisNo : PLongInt; dRadius : Double; dpEndPos : PDouble; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord; lOverrideMode : LongInt; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;



function AxmAdvScriptHelixCenterMove(lCoord : LongInt; dCenterXPos : Double; dCenterYPos : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptHelixPointMove(lCoord : LongInt; dMidXPos : Double; dMidYPos : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptHelixAngleMove(lCoord : LongInt; dCenterXPos : Double; dCenterYPos : Double; dAngle : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptHelixRadiusMove(lCoord : LongInt; dRadius : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;

function AxmAdvScriptOvrHelixRadiusMove(lCoord : LongInt; dRadius : Double; dEndXPos : Double; dEndYPos : Double; dZPos : Double; dVel : Double; dStartVel : Double; dStopVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord; lOverrideMode : LongInt; uScript : DWord; lScirptAxisNo : LongInt; dScriptPos : Double) : DWord; stdcall;


function AxmAdvContiGetNodeNum(lCoordinate : LongInt; lpNodeNum : PLongInt) : DWord; stdcall;

function AxmAdvContiGetTotalNodeNum(lCoordinate : LongInt; lpNodeNum : PLongInt) : DWord; stdcall;

function AxmAdvContiReadIndex(lCoordinate : LongInt; lpQueueIndex : PLongInt) : DWord; stdcall;

function AxmAdvContiReadFree(lCoordinate : LongInt; upQueueFree : PDWord) : DWord; stdcall;

function AxmAdvContiWriteClear(lCoordinate : LongInt) : DWord; stdcall;

function AxmAdvOvrContiWriteClear(lCoordinate : LongInt) : DWord; stdcall;

function AxmAdvContiStart(lCoord : LongInt; uProfileset : DWord; lAngle : LongInt) : DWord; stdcall;

function AxmAdvContiStop(lCoord : LongInt; dDecel : Double) : DWord; stdcall;

function AxmAdvContiSetAxisMap(lCoord : LongInt; lSize : LongInt; lpAxesNo : PLongInt) : DWord; stdcall;

function AxmAdvContiGetAxisMap(lCoord : LongInt; lpSize : PLongInt; lpAxesNo : PLongInt) : DWord; stdcall;

function AxmAdvContiSetAbsRelMode(lCoord : LongInt; uAbsRelMode : DWord) : DWord; stdcall;

function AxmAdvContiGetAbsRelMode(lCoord : LongInt; upAbsRelMode : PDWord) : DWord; stdcall;

function AxmAdvContiIsMotion(lCoordinate : LongInt; upInMotion : PDWord) : DWord; stdcall;

function AxmAdvContiBeginNode(lCoord : LongInt) : DWord; stdcall;

function AxmAdvContiEndNode(lCoord : LongInt) : DWord; stdcall;


function AxmMoveMultiStop(lArraySize : LongInt; lpAxesNo : PLongInt; dpMaxDecel : PDouble) : DWord; stdcall;

function AxmMoveMultiEStop(lArraySize : LongInt; lpAxesNo : PLongInt) : DWord; stdcall;

function AxmMoveMultiSStop(lArraySize : LongInt; lpAxesNo : PLongInt) : DWord; stdcall;


function AxmStatusReadActVel(lAxisNo : LongInt; dpVel : PDouble) : DWord; stdcall;

function AxmStatusReadServoCmdStat(lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;

function AxmStatusReadServoCmdCtrl(lAxisNo : LongInt; upStatus : PDWord) : DWord; stdcall;


function AxmGantryGetMstToSlvOverDist(lAxisNo : LongInt; dpPosition : PDouble) : DWord; stdcall;

function AxmGantrySetMstToSlvOverDist(lAxisNo : LongInt; dPosition : Double) : DWord; stdcall;


function AxmSignalReadServoAlarmCode(lAxisNo : LongInt; upCodeStatus : PDWord) : DWord; stdcall;


function AxmM3ServoCoordinatesSet(lAxisNo : LongInt; uPosData : DWord; uPos_sel : DWord; uRefe : DWord) : DWord; stdcall;

function AxmM3ServoBreakOn(lAxisNo : LongInt) : DWord; stdcall;

function AxmM3ServoBreakOff(lAxisNo : LongInt) : DWord; stdcall;

function AxmM3ServoConfig(lAxisNo : LongInt; uCfMode : DWord) : DWord; stdcall;

function AxmM3ServoSensOn(lAxisNo : LongInt) : DWord; stdcall;

function AxmM3ServoSensOff(lAxisNo : LongInt) : DWord; stdcall;

function AxmM3ServoSmon(lAxisNo : LongInt) : DWord; stdcall;

function AxmM3ServoGetSmon(lAxisNo : LongInt; bpParam : PByte) : DWord; stdcall;

function AxmM3ServoSvOn(lAxisNo : LongInt) : DWord; stdcall;

function AxmM3ServoSvOff(lAxisNo : LongInt) : DWord; stdcall;

function AxmM3ServoInterpolate(lAxisNo : LongInt; uTPOS : DWord; uVFF : DWord; uTFF : DWord; uTLIM : DWord) : DWord; stdcall;

function AxmM3ServoPosing(lAxisNo : LongInt; uTPOS : DWord; uSPD : DWord; uACCR : DWord; uDECR : DWord; uTLIM : DWord) : DWord; stdcall;

function AxmM3ServoFeed(lAxisNo : LongInt; lSPD : LongInt; uACCR : DWord; uDECR : DWord; uTLIM : DWord) : DWord; stdcall;

function AxmM3ServoExFeed(lAxisNo : LongInt; lSPD : LongInt; uACCR : DWord; uDECR : DWord; uTLIM : DWord; uExSig1 : DWord; uExSig2 : DWord) : DWord; stdcall;

function AxmM3ServoExPosing(lAxisNo : LongInt; uTPOS : DWord; uSPD : DWord; uACCR : DWord; uDECR : DWord; uTLIM : DWord; uExSig1 : DWord; uExSig2 : DWord) : DWord; stdcall;

function AxmM3ServoZret(lAxisNo : LongInt; uSPD : DWord; uACCR : DWord; uDECR : DWord; uTLIM : DWord; uExSig1 : DWord; uExSig2 : DWord; bHomeDir : Byte; bHomeType : Byte) : DWord; stdcall;

function AxmM3ServoVelctrl(lAxisNo : LongInt; uTFF : DWord; uVREF : DWord; uACCR : DWord; uDECR : DWord; uTLIM : DWord) : DWord; stdcall;

function AxmM3ServoTrqctrl(lAxisNo : LongInt; uVLIM : DWord; lTQREF : LongInt) : DWord; stdcall;

function AxmM3ServoGetParameter(lAxisNo : LongInt; wNo : Word; bSize : Byte; bMode : Byte; bpParam : PByte) : DWord; stdcall;

function AxmM3ServoSetParameter(lAxisNo : LongInt; wNo : Word; bSize : Byte; bMode : Byte; bpParam : PByte) : DWord; stdcall;
// Execute Command Execution in M3 SERVOPACK
// dwSize is the number of variables to use(Ex: 1)M3StatNop : AxmServoCmdExecution(m_lAxis, 0, NULL), 2)M3GetStationIdRd : AxmServoCmdExecution(m_lAxis, 3, *pbIdRd))
// M3StationNop(int lNodeNum)                                                                                                   : bwSize = 0
// M3GetStationIdRd(int lNodeNum, BYTE bIdCode, BYTE bOffset, BYTE bSize, BYTE *pbIdRd)                                         : bwSize = 3
// M3ServoSetConfig(int lNodeNum, BYTE bMode)                                                                                   : bwSize = 1
// M3SetStationAlarmClear(int lNodeNum, WORD wAlarmClrMod)                                                                      : bwSize = 1
// M3ServoSyncSet(int lNodeNum)                                                                                                 : bwSize = 0
// M3SetStationConnect(int lNodeNum, BYTE bVer, uByteComMod ubComMode, BYTE bComTime, BYTE bProfileType)                        : bwSize = 4
// M3SetStationDisconnect(int lNodeNum)                                                                                         : bwSize = 0
// M3ServoSmon(int lNodeNum)                                                                                                    : bwSize = 0
// M3ServoSvOn(int lNodeNum)                                                                                                    : bwSize = 0
// M3ServoSvOff(int lNodeNum)                                                                                                   : bwSize = 0
// M3ServoInterpolate(int lNodeNum, LONG lTPOS, LONG lVFF, LONG lTFF)                                                           : bwSize = 3
// M3ServoPosing(int lNodeNum, LONG lTPOS, LONG lSPD, LONG lACCR, LONG lDECR, LONG lTLIM)                                       : bwSize = 5
// M3ServoFeed(int lNodeNum, LONG lSPD, LONG lACCR, LONG lDECR, LONG lTLIM)                                                     : bwSize = 4
// M3ServoExFeed(int lNodeNum, LONG lSPD, LONG lACCR, LONG lDECR, LONG lTLIM, DWORD dwExSig1, DWORD dwExSig2)                   : bwSize = 6
// M3ServoExPosing(int lNodeNum, LONG lTPOS, LONG lSPD, LONG lACCR, LONG lDECR, LONG lTLIM, DWORD dwExSig1, DWORD dwExSig2)     : bwSize = 7
// M3ServoTrqctrl(int lNodeNum, LONG lVLIM, LONG lTQREF)                                                                        : bwSize = 2
// M3ServoGetParameter(int lNodeNum, WORD wNo, BYTE bSize, BYTE bMode, BYTE *pbParam)                                           : bwSize = 3
// M3ServoSetParameter(int lNodeNum, WORD wNo, BYTE bSize, BYTE bMode, BYTE *pbParam)                                           : bwSize = 7
function AxmServoCmdExecution(lAxisNo : LongInt; dwCommand : DWord; dwSize : DWord; pdwExcData : PDWord) : DWord; stdcall;
function AxmM3ServoGetTorqLimit(lAxisNo : LongInt; upTorqLimit : PDWord) : DWord; stdcall;

function AxmM3ServoSetTorqLimit(lAxisNo : LongInt; uTorqLimit : DWord) : DWord; stdcall;


function AxmM3ServoGetSendSvCmdIOOutput(lAxisNo : LongInt; upData : PDWord) : DWord; stdcall;

function AxmM3ServoSetSendSvCmdIOOutput(lAxisNo : LongInt; uData : DWord) : DWord; stdcall;


function AxmM3ServoGetSvCmdCtrl(lAxisNo : LongInt; upData : PDWord) : DWord; stdcall;

function AxmM3ServoSetSvCmdCtrl(lAxisNo : LongInt; uData : DWord) : DWord; stdcall;


function AxmM3AdjustmentOperation(lAxisNo : LongInt; uReqCode : DWord) : DWord; stdcall;

function AxmM3ServoSetMonSel(lAxisNo : LongInt; uMon0 : DWord; uMon1 : DWord; uMon2 : DWord) : DWord; stdcall;

function AxmM3ServoGetMonSel(lAxisNo : LongInt; upMon0 : PDWord; upMon1 : PDWord; upMon2 : PDWord) : DWord; stdcall;

function AxmM3ServoReadMonData(lAxisNo : LongInt; uMonSel : DWord; upMonData : PDWord) : DWord; stdcall;

function AxmAdvTorqueContiSetAxisMap(lCoord : LongInt; lSize : LongInt; lpAxesNo : PLongInt; uTLIM : DWord; uConMode : DWord) : DWord; stdcall;

function AxmM3ServoSetTorqProfile(lCoord : LongInt; lAxisNo : LongInt; lTorqueSign : LongInt; uVLIM : DWord; uProfileMode : DWord; uStdTorq : DWord; uStopTorq : DWord) : DWord; stdcall;

function AxmM3ServoGetTorqProfile(lCoord : LongInt; lAxisNo : LongInt; lpTorqueSign : PLongInt; updwVLIM : PDWord; upProfileMode : PDWord; upStdTorq : PDWord; upStopTorq : PDWord) : DWord; stdcall;

//-------------------------------------------------------------------------------------------------------------------
//======== For EtherCAT Only =======================================================================================
// Set for Inposition signal range. (dInposRange > 0)
function AxmSignalSetInposRange(lAxisNo : LongInt; dInposRange : Double) : DWord; stdcall;
// Get the Inposition signal range.
function AxmSignalGetInposRange(lAxisNo : LongInt; dpInposRange : PDouble) : DWord; stdcall;


// Set for absolute encoder position to dPosition.
function AxmStatusSetEncClear(lAxisNo : LongInt; dPosition : Double) : DWord; stdcall;


// The command position and actual position of the SERVOPACK corresponding to the designated axis are matched with the dPos value.
// Reserved
function AxmStatusSetMotorPosMatch(lAxisNo : LongInt; dPosition : Double) : DWord; stdcall;


// Set for Work coordinate system. The default value matches World coordinate.
// lCoordNo : Coordinate No(0 ~ 7)
// dpOrigin : Work coordinate system origin position based on World Coordinate
// dpXPos   : Work coordinate system based on World Coordinate Any position on X axis
// dpYPos   : Work coordinate system based on World Coordinate Any position on Y axis
function AxmMotSetWorkCoordinate(lCoordNo : LongInt; dpOrigin : PDouble; dpXPos : PDouble; dpYPos : PDouble) : DWord; stdcall;
// Get the set Work coordinate system.
function AxmMotGetWorkCoordinate(lCoordNo : LongInt; dpOrigin : PDouble; dpXPos : PDouble; dpYPos : PDouble) : DWord; stdcall;

// Set the location property (absolute / relative) when overriding.
function AxmMotSetOverridePosMode(lAxisNo : LongInt; uAbsRelMode : DWord) : DWord; stdcall;
// Get the location property (absolute / relative) when overriding.
function AxmMotGetOverridePosMode(lAxisNo : LongInt; upAbsRelMode : PDWord) : DWord; stdcall;
// Set the location property (absolute / relative) when LineMove overriding.
function AxmMotSetOverrideLinePosMode(lCoordNo : LongInt; uAbsRelMode : DWord) : DWord; stdcall;
// Get the location property (absolute / relative) when LineMove overriding.
function AxmMotGetOverrideLinePosMode(lCoordNo : LongInt; upAbsRelMode : PDWord) : DWord; stdcall;


// Set the Vibration Control setting value(Set the Vibration Control setting value (frequency, damping ratio, impulse count) of the specified axis.
function AxmMotSetVibrationControl(lAxisNo : LongInt; lSize : LongInt; dpFrequency : PDouble; dpDampingRatio : PDouble; lpImpulseCount : PLongInt) : DWord; stdcall;

// Enable or disable the Vibration Control of the specific axis.
function AxmMotVibrationControlEnable(lAxisNo : LongInt; uEnable : DWord) : DWord; stdcall;

// Reads whether Vibration Control of the specified axis is enabled.
function AxmMotVibrationControlIsEnable(lAxisNo : LongInt; upEnable : PDWord) : DWord; stdcall;

// Enable or Disable the Vibration Control of the specified coordinate system.
function AxmMotVibrationControlCoordEnable(lAxisNo : LongInt; uEnable : DWord) : DWord; stdcall;

// Reads whether Vibration Control is enabled in the specified coordinate system.
function AxmMotVibrationControlCoordIsEnable(lAxisNo : LongInt; upEnable : PDWord) : DWord; stdcall;


// Sets the TorqueLimit for each Position range of the specified axis.
// The number of dpPosition array is lSize.
// The number of dpPlusTorqueLimit and dpMinusTorqueLimit is (lSize - 1)
// ※ Note : Position must be entered in ascending order.
//          EtherCAT only applies the same TorqueLimit to both PlusTorqueLimit values.
function AxmMotSetMultiTorqueLimit(lAxisNo : LongInt; lSize : LongInt; dpPosition : PDouble; dpPlusTorqueLimit : PDouble; dpMinusTorqueLimit : PDouble; lTarget : LongInt) : DWord; stdcall;

// Enable or Disable the Multi TorqueLimit of the specified axis.
function AxmMotMultiTorqueLimitEnable(lAxisNo : LongInt; uEnable : DWord) : DWord; stdcall;

// Reads whether Multi TorqueLimit of the specified axis is enabled.
function AxmMotMultiTorqueLimitIsEnable(lAxisNo : LongInt; upEnable : PDWord) : DWord; stdcall;


// Equivalent to AxmMoveStartPos and added end rate (EndVel).
function AxmMoveStartPosEx(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; dEndVel : Double) : DWord; stdcall;
// Equivalent to AxmMovePos and added end rate (EndVel).
function AxmMovePosEx(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; dEndVel : Double) : DWord; stdcall;


// Normal-Stop the Coordinate Motion on path.
function AxmMoveCoordStop(lCoordNo : LongInt; dDecel : Double) : DWord; stdcall;
// Emergency-Stop the Coordinate Motion on path.
function AxmMoveCoordEStop(lCoordNo : LongInt) : DWord; stdcall;
// Slowdown-Stop the Coordinate Motion on path.
function AxmMoveCoordSStop(lCoordNo : LongInt) : DWord; stdcall;



// Override the position of the AxmLineMove motion.
function AxmOverrideLinePos(lCoordNo : LongInt; dpOverridePos : PDouble) : DWord; stdcall;
// Override the velocity of the AxmLineMove motion. The speed ratio of each axis is determined by dpDistance.
function AxmOverrideLineVel(lCoordNo : LongInt; dOverrideVel : Double; dpDistance : PDouble) : DWord; stdcall;

// Override the velocity, acceleration, deceleration of the AxmLineMove motion.
// dMaxAccel  : Acceleration value for overriding
// dMaxDecel  : Deceleration value for overriding
// dpDistance : Speed ratio of each axis
function AxmOverrideLineAccelVelDecel(lCoordNo : LongInt; dOverrideVelocity : Double; dMaxAccel : Double; dMaxDecel : Double; dpDistance : PDouble) : DWord; stdcall;
// In addition to AxmOverrideVelAtPos, override AccelDecel.
function AxmOverrideAccelVelDecelAtPos(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; dOverridePos : Double; dOverrideVel : Double; dOverrideAccel : Double; dOverrideDecel : Double; lTarget : LongInt) : DWord; stdcall;


// A plurality of slave axes are connected to one master axis. (Electronic Gearing)
// lMasterAxisNo : Master axis number
// lSize         : Slave axis count(Max : 8)
// lpSlaveAxisNo : Array of Slave axis number
// dpGearRatio   : Slave axis ratio based on master axis (Except 0. 1.0 is 100%)
function AxmEGearSet(lMasterAxisNo : LongInt; lSize : LongInt; lpSlaveAxisNo : PLongInt; dpGearRatio : PDouble) : DWord; stdcall;
// Reads Electronic Gearing information.
function AxmEGearGet(lMasterAxisNo : LongInt; lpSize : PLongInt; lpSlaveAxisNo : PLongInt; dpGearRatio : PDouble) : DWord; stdcall;
// Reset Electronic Gearing.
function AxmEGearReset(lMasterAxisNo : LongInt) : DWord; stdcall;
// Enable or disable Electronic Gearing.
function AxmEGearEnable(lMasterAxisNo : LongInt; uEnable : DWord) : DWord; stdcall;
// Reads whether Electronic Gearing is enabled.
function AxmEGearIsEnable(lMasterAxisNo : LongInt; upEnable : PDWord) : DWord; stdcall;




//function AxmLineMoveEx(lCoordNo : LongInt; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; dEndVel : Double) : DWord; stdcall;

//function AxmCirclePointMoveEx(lCoordNo : LongInt; lpAxisNo : PLongInt; dpMidPos : PDouble; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; lArcCircle : LongInt; lArraySize : LongInt) : DWord; stdcall;

// Helical interpolation drive that rotates around any axis is supported.
// dpFirstCenterPos  : Center position
// dpSecondCenterPos : Center position on opposite side
// dPitch            : Movement amount(mm) / 1 Revolution
// dTraverseDistance : Movement amount(mm)
// The line connecting dpFirstCenterPos to dpSecondCenterPos is the axis of rotation.
// The straight line from the center(dpFirstCenterPos-->dpSecondCenterPos) and the straight line to the start position(dpFirstCenterPos-->Starting position) is perpendicular to each other.
// dTraverseDistance is the distance of a straight line parallel to the axis of rotation at the starting position.
// Axis mapping is possible for more than 3 axes, and axes more than 3 axes are linear interpolation.
function AxmHelixPitchMove(lCoordNo : LongInt; dpFirstCenterPos : PDouble; dpSecondCenterPos : PDouble; dPitch : Double; dTraverseDistance : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;


//function AxmHelixPitchMoveEx(lCoordNo : LongInt; dpFirstCenterPos : PDouble; dpSecondCenterPos : PDouble; dPitch : Double; dTraverseDistance : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; dEndVel : Double) : DWord; stdcall;

// 1-D correction function
// When driving beyond the compensation table range, the first and last compensation values of the compensation table should always be set to "0".
// That is, pdMotorPosition and pdLoadPosition must be the same.
// You can set the axis to measure the correction value (lSourceAxis) and the axis to apply the correction value (lTargetAxis) to the same axis or another axis.
// The position value of the correction table is set to an absolute position.
function AxmCompensationOneDimSet(lTableNo : LongInt; lSourceAxis : LongInt; lTargetAxis : LongInt; lSize : LongInt; dpMotorPosition : PDouble; dpLoadPosition : PDouble) : DWord; stdcall;
function AxmCompensationOneDimGet(lTableNo : LongInt; lpSourceAxis : PLongInt; lpTargetAxis : PLongInt; lpSize : PLongInt; dpMotorPosition : PDouble; dpLoadPosition : PDouble) : DWord; stdcall;
function AxmCompensationOneDimReset(lTableNo : LongInt) : DWord; stdcall;
    function AxmCompensationOneDimIsSet (lTableNo : LongInt; dwpSet : PDWord) : DWord; stdcall;
function AxmCompensationOneDimEnable(lTableNo : LongInt; uEnable : DWord) : DWord; stdcall;
function AxmCompensationOneDimIsEnable(lTableNo : LongInt; upEnable : PDWord) : DWord; stdcall;


// Returns the compensation value at the current command position.
function AxmCompensationOneDimGetCorrection(lTableNo : LongInt; dpCorrection : PDouble) : DWord; stdcall;

    function AxmCompensationOneDimSetReverse (lTableNo : LongInt; dpLoadPosition : PDouble) : DWord; stdcall;
    function AxmCompensationOneDimGetReverse (lTableNo : LongInt; dpLoadPosition : PDouble) : DWord; stdcall;
    function AxmCompensationOneDimGetCorrectionReverse (lTableNo : LongInt; pdCorrection : PDouble) : DWord; stdcall;

    function AxmCompensationOneDimFileLoad (lTableNo : LongInt; lSourceAxis : LongInt; lTargetAxis : LongInt; szFilePath : char*; 0 : DWORD dwInterpolationMethod =) : DWord; stdcall;
    function AxmCompensationOneDimFileSave (lTableNo : LongInt; szFilePath : char*) : DWord; stdcall;

    function AxmCompensationOneDimSetInterpolationMethod (lTableNo : LongInt; dwMethod : DWord) : DWord; stdcall;
    function AxmCompensationOneDimGetInterpolationMethod (lTableNo : LongInt; dwpMethod : PDWord) : DWord; stdcall;

    function AxmCompensationTwoDimSet (lTableNo : LongInt; lSourceAxis1 : LongInt; lSourceAxis2 : LongInt; lTargetAxis1 : LongInt; lTargetAxis2 : LongInt; lSize1 : LongInt; lSize2 : LongInt; dpMotorPosition1 : PDouble; dpMotorPosition2 : PDouble; dpLoadPosition1 : PDouble; dpLoadPosition2 : PDouble) : DWord; stdcall;
    function AxmCompensationTwoDimGet (lTableNo : LongInt; lpSourceAxis1 : PLongInt; lpSourceAxis2 : PLongInt; lpTargetAxis1 : PLongInt; lpTargetAxis2 : PLongInt; lpSize1 : PLongInt; lpSize2 : PLongInt; dpMotorPosition1 : PDouble; dpMotorPosition2 : PDouble; dpLoadPosition1 : PDouble; dpLoadPosition2 : PDouble) : DWord; stdcall;
    function AxmCompensationTwoDimReset (lTableNo : LongInt) : DWord; stdcall;
    function AxmCompensationTwoDimIsSet (lTableNo : LongInt; dwpSet : PDWord) : DWord; stdcall;
    function AxmCompensationTwoDimEnable (lTableNo : LongInt; dwEnable : DWord) : DWord; stdcall;
    function AxmCompensationTwoDimIsEnable (lTableNo : LongInt; dwpEnable : PDWord) : DWord; stdcall;

    function AxmCompensationTwoDimGetCorrection (lTableNo : LongInt; pdCorrection : PDouble) : DWord; stdcall;

    function AxmCompensationTwoDimFileLoad (lTableNo : LongInt; lSourceAxis1 : LongInt; lSourceAxis2 : LongInt; lTargetAxis1 : LongInt; lTargetAxis2 : LongInt; szFilePath : char*) : DWord; stdcall;
    function AxmCompensationTwoDimFileSave (lTableNo : LongInt; szFilePath : char*) : DWord; stdcall;



//function AxmCompensationTwoDimSet(lTableNo : LongInt; lSourceAxis1 : LongInt; lSourceAxis2 : LongInt; lTargetAxis1 : LongInt; lTargetAxis2 : LongInt; lSize1 : LongInt; lSize2 : LongInt; dpMotorPosition1 : PDouble; dpMotorPosition2 : PDouble; dpLoadPosition1 : PDouble; dpLoadPosition2 : PDouble) : DWord; stdcall;
//function AxmCompensationTwoDimGet(lTableNo : LongInt; lpSourceAxis1 : PLongInt; lpSourceAxis2 : PLongInt; lpTargetAxis1 : PLongInt; lpTargetAxis2 : PLongInt; lpSize1 : PLongInt; lpSize2 : PLongInt; dpMotorPosition1 : PDouble; dpMotorPosition2 : PDouble; dpLoadPosition1 : PDouble; dpLoadPosition2 : PDouble) : DWord; stdcall;
//function AxmCompensationTwoDimReset(lTableNo : LongInt) : DWord; stdcall;
//function AxmCompensationTwoDimEnable(lTableNo : LongInt; uEnable : DWord) : DWord; stdcall;
//function AxmCompensationTwoDimIsEnable(lTableNo : LongInt; upEnable : PDWord) : DWord; stdcall;

// Reserved
//function AxmBlendingSet(lAxisNo : LongInt; dValue : Double; uMethod : DWord) : DWord; stdcall;
//function AxmBlendingGet(lAxisNo : LongInt; dpValue : PDouble; upMethod : PDWord) : DWord; stdcall;
//function AxmBlendingReset(lAxisNo : LongInt) : DWord; stdcall;
//function AxmBlendingEnable(lAxisNo : LongInt; uEnable : DWord) : DWord; stdcall;
//function AxmBlendingIsEnable(lAxisNo : LongInt; upEnable : PDWord) : DWord; stdcall;

// Blending motion is supported.
// dValue   : At the start of blending based on the ending point of the first motion segment
// dwMethod : Distance(mm)-0, Time(msec)-1, Distance ratio(%)-2
// Blending mode is canceled in automatic acceleration / deceleration and automatic arc insertion mode.
function AxmBlendingCoordSet(lCoordNo : LongInt; dValue : Double; uMethod : DWord) : DWord; stdcall;
function AxmBlendingCoordGet(lAxisNo : LongInt; dpValue : PDouble; upMethod : PDWord) : DWord; stdcall;
function AxmBlendingCoordReset(lAxisNo : LongInt) : DWord; stdcall;
function AxmBlendingCoordEnable(lAxisNo : LongInt; uEnable : DWord) : DWord; stdcall;
function AxmBlendingCoordIsEnable(lAxisNo : LongInt; upEnable : PDWord) : DWord; stdcall;





//function AxmMoveMultiSignalCapture(lAxisNo : LongInt; dPos : Double; dVel : Double; dAccel : Double; dDecel : Double; lDetectSignal : LongInt; lSignalEdge : LongInt; lTarget : LongInt) : DWord; stdcall;

//function AxmMoveGetMultiCapturePos(lAxisNo : LongInt; dpCapPosition : PDouble; lpSize : PLongInt) : DWord; stdcall;

// Read the torque value of the corresponding axis.
function AxmStatusReadTorque(lAxisNo : LongInt; dpTorque : PDouble) : DWord; stdcall;


//ProfilePosition Mode          = 1,
//Velocity Mode                 = 2,
//ProfileVelocity Mode          = 3,
//ProfileTorque Mode            = 4,
//Homing Mode                   = 6,
//InterpolatedPosition Mode     = 7,
//CyclicSyncPosition Mode       = 8,
//CyclicSyncVelocity Mode       = 9,
//CyclicSyncTorque Mode         = 10,
//function AxmMotSetOperationMode(lAxisNo : LongInt; uOperationMode : DWord) : DWord; stdcall;

//function AxmMotGetOperationMode(lAxisNo : LongInt; upOperationMode : PDWord) : DWord; stdcall;

// Set the end speed on the specified axis.
// * Note : It is reset to '0' if the entered end rate is below '0' and to 'MaxVel' if it exceeds the maximum speed set by 'AxmMotSetMaxVel'.
function AxmMotSetEndVel(lAxisNo : LongInt; dEndVelocity : Double) : DWord; stdcall;
// Returns the ending speed of the specified axis.
function AxmMotGetEndVel(lAxisNo : LongInt; dpEndVelocity : PDouble) : DWord; stdcall;


// Linear interpolation.
// Axis linear interpolation drive by specifying a start point and an end point. The function is exited after the start of driving.
// When using with AxmContiBeginNode and AxmContiEndNode, the start point and the end point are specified in the specified coordinate system and stored in the queue for linear interpolation driving.
// For linear profile continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
// The axes corresponding to the axis array of lpAxisNo are subjected to linear interpolation and the axes of the remaining coordinate axes perform the single axis driving according to the linear interpolation ratio.
function AxmLineMoveWithAxes(lCoord : LongInt; lArraySize : LongInt; lpAxisNo : PLongInt; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double) : DWord; stdcall;


// 2-D / 3-D circular interpolation and linear interpolation are performed for the further axes.
// The start point, end point, and center point are specified and circular interpolation drive is performed. The function is exited after the start of driving.
// When used with AxmContiBeginNode and AxmContiEndNode, it is stored in the circular interpolation queue that is driven by specifying the start point, end point, and center point in the specified coordinate system.
// For profile circular continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
// lAxis           : Axis array
// dCenterPosition : Center position array(X,Y or X,Y,Z)
// dEndPosition    : End position array(X,Y or X,Y,Z)
// For 2-D / 3-D or more axes, the value of dEndPosition is used as Targetposition when performing linear interpolation.
// uCWDir          : DIR_CCW(0), DIR_CW(1)
// dw3DCircle      : 2-D circular interpolation and linear interpolation for more axes(0), 3-D circular interpolation and linear interpolation for more axes(1)
function AxmCircleCenterMoveWithAxes(lCoord : LongInt; lArraySize : LongInt; lpAxisNo : PLongInt; dCenterPosition : PDouble; dEndPosition : PDouble; dMaxVelocity : Double; dMaxAccel : Double; dMaxDecel : Double; uCWDir : DWord; b3DCircle : LongBool) : DWord; stdcall;

    function AxmCircleRadiusMoveWithAxes (lCoord : LongInt; lArraySize : LongInt; lpAxisNo : PLongInt; dRadius : Double; dEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord; uShortDistance : DWord) : DWord; stdcall;


    function AxmCircleAngleMoveWithAxes (lCoord : LongInt; lArraySize : LongInt; lpAxisNo : PLongInt; dCenterPos : PDouble; dAngle : Double; dVel : Double; dAccel : Double; dDecel : Double; uCWDir : DWord) : DWord; stdcall;

    function AxmCirclePointMoveWithAxes (lCoordNo : LongInt; lArraySize : LongInt; lpAxisNo : PLongInt; dpMidPos : PDouble; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; lArcCircle : LongInt) : DWord; stdcall;


// Linear interpolation.
// Axis linear interpolation drive by specifying a start point and an end point. The function is exited after the start of driving.
// When using with AxmContiBeginNode and AxmContiEndNode, the start point and the end point are specified in the specified coordinate system and stored in the queue for linear interpolation driving.
// For linear profile continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
// The axes corresponding to the axis array of lpAxisNo are subjected to linear interpolation and the axes of the remaining coordinate axes perform the single axis driving according to the linear interpolation ratio.
function AxmLineMoveWithAxesWithEvent(lCoord : LongInt; lArraySize : LongInt; lpAxisNo : PLongInt; dpEndPos : PDouble; dVel : Double; dAccel : Double; dDecel : Double; uEventFlag : DWord) : DWord; stdcall;


// 2-D / 3-D circular interpolation and linear interpolation are performed for the further axes.
// The start point, end point, and center point are specified and circular interpolation drive is performed. The function is exited after the start of driving.
// When used with AxmContiBeginNode and AxmContiEndNode, it is stored in the circular interpolation queue that is driven by specifying the start point, end point, and center point in the specified coordinate system.
// For profile circular continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
// lAxis           : Axis array
// dCenterPosition : Center position array(X,Y or X,Y,Z)
// dEndPosition    : End position array(X,Y or X,Y,Z)
// For 2-D / 3-D or more axes, the value of dEndPosition is used as Targetposition when performing linear interpolation.
// uCWDir          : DIR_CCW(0), DIR_CW(1)
// dw3DCircle      : 2-D circular interpolation and linear interpolation for more axes(0), 3-D circular interpolation and linear interpolation for more axes(1)
function AxmCircleCenterMoveWithAxesWithEvent(lCoord : LongInt; lArraySize : LongInt; lpAxisNo : PLongInt; dCenterPosition : PDouble; dpEndPosition : PDouble; dMaxVelocity : Double; dMaxAccel : Double; dMaxDecel : Double; uCWDir : DWord; u3DCircle : DWord; uEventFlag : DWord) : DWord; stdcall;


    function AxmMovePVT (lAxisNo : LongInt; dwArraySize : DWord; pdPos : PDouble; pdVel : PDouble; pdwUsec : PDWord) : DWord; stdcall;


    function AxmSyncSetAxisMap (lSyncNo : LongInt; lSize : LongInt; lpAxesNo : PLongInt) : DWord; stdcall;

    function AxmSyncClear (lSyncNo : LongInt) : DWord; stdcall;

    function AxmSyncBegin (lSyncNo : LongInt) : DWord; stdcall;

    function AxmSyncEnd (lSyncNo : LongInt) : DWord; stdcall;

    function AxmSyncStart (lSyncNo : LongInt) : DWord; stdcall;


implementation

const

    dll_name    = 'AXL.dll';
    function AxmInfoGetAxis; external dll_name name 'AxmInfoGetAxis';
    function AxmInfoGetAxisEx; external dll_name name 'AxmInfoGetAxisEx';
    function AxmInfoIsMotionModule; external dll_name name 'AxmInfoIsMotionModule';
    function AxmInfoIsInvalidAxisNo; external dll_name name 'AxmInfoIsInvalidAxisNo';
    function AxmInfoGetAxisStatus; external dll_name name 'AxmInfoGetAxisStatus';
    function AxmInfoGetAxisCount; external dll_name name 'AxmInfoGetAxisCount';
    function AxmInfoGetFirstAxisNo; external dll_name name 'AxmInfoGetFirstAxisNo';
    function AxmInfoGetBoardFirstAxisNo; external dll_name name 'AxmInfoGetBoardFirstAxisNo';
    function AxmVirtualSetAxisNoMap; external dll_name name 'AxmVirtualSetAxisNoMap';
    function AxmVirtualGetAxisNoMap; external dll_name name 'AxmVirtualGetAxisNoMap';
    function AxmVirtualSetMultiAxisNoMap; external dll_name name 'AxmVirtualSetMultiAxisNoMap';
    function AxmVirtualGetMultiAxisNoMap; external dll_name name 'AxmVirtualGetMultiAxisNoMap';
    function AxmVirtualResetAxisMap; external dll_name name 'AxmVirtualResetAxisMap';
    function AxmVirtualSetMultiReDefineAxisNo; external dll_name name 'AxmVirtualSetMultiReDefineAxisNo';
    function AxmVirtualGetMultiReDefineAxisNo; external dll_name name 'AxmVirtualGetMultiReDefineAxisNo';
    function AxmInterruptSetAxis; external dll_name name 'AxmInterruptSetAxis';
    function AxmInterruptSetAxisEnable; external dll_name name 'AxmInterruptSetAxisEnable';
    function AxmInterruptGetAxisEnable; external dll_name name 'AxmInterruptGetAxisEnable';
    function AxmInterruptRead; external dll_name name 'AxmInterruptRead';
    function AxmInterruptReadAxisFlag; external dll_name name 'AxmInterruptReadAxisFlag';
    function AxmInterruptSetUserEnable; external dll_name name 'AxmInterruptSetUserEnable';
    function AxmInterruptGetUserEnable; external dll_name name 'AxmInterruptGetUserEnable';
    function AxmMotLoadParaAll; external dll_name name 'AxmMotLoadParaAll';
    function AxmMotSaveParaAll; external dll_name name 'AxmMotSaveParaAll';
    function AxmMotSetParaLoad; external dll_name name 'AxmMotSetParaLoad';
    function AxmMotGetParaLoad; external dll_name name 'AxmMotGetParaLoad';
    function AxmMotSetPulseOutMethod; external dll_name name 'AxmMotSetPulseOutMethod';
    function AxmMotGetPulseOutMethod; external dll_name name 'AxmMotGetPulseOutMethod';
    function AxmMotSetEncInputMethod; external dll_name name 'AxmMotSetEncInputMethod';
    function AxmMotGetEncInputMethod; external dll_name name 'AxmMotGetEncInputMethod';
    function AxmMotSetMoveUnitPerPulse; external dll_name name 'AxmMotSetMoveUnitPerPulse';
    function AxmMotGetMoveUnitPerPulse; external dll_name name 'AxmMotGetMoveUnitPerPulse';
    function AxmMotSetDecelMode; external dll_name name 'AxmMotSetDecelMode';
    function AxmMotGetDecelMode; external dll_name name 'AxmMotGetDecelMode';
    function AxmMotSetRemainPulse; external dll_name name 'AxmMotSetRemainPulse';
    function AxmMotGetRemainPulse; external dll_name name 'AxmMotGetRemainPulse';
    function AxmMotSetMaxVel; external dll_name name 'AxmMotSetMaxVel';
    function AxmMotGetMaxVel; external dll_name name 'AxmMotGetMaxVel';
    function AxmMotSetAbsRelMode; external dll_name name 'AxmMotSetAbsRelMode';
    function AxmMotGetAbsRelMode; external dll_name name 'AxmMotGetAbsRelMode';
    function AxmMotSetProfileMode; external dll_name name 'AxmMotSetProfileMode';
    function AxmMotGetProfileMode; external dll_name name 'AxmMotGetProfileMode';
    function AxmMotSetAccelUnit; external dll_name name 'AxmMotSetAccelUnit';
    function AxmMotGetAccelUnit; external dll_name name 'AxmMotGetAccelUnit';
    function AxmMotSetMinVel; external dll_name name 'AxmMotSetMinVel';
    function AxmMotGetMinVel; external dll_name name 'AxmMotGetMinVel';
    function AxmMotSetAccelJerk; external dll_name name 'AxmMotSetAccelJerk';
    function AxmMotGetAccelJerk; external dll_name name 'AxmMotGetAccelJerk';
    function AxmMotSetDecelJerk; external dll_name name 'AxmMotSetDecelJerk';
    function AxmMotGetDecelJerk; external dll_name name 'AxmMotGetDecelJerk';
    function AxmMotSetProfilePriority; external dll_name name 'AxmMotSetProfilePriority';
    function AxmMotGetProfilePriority; external dll_name name 'AxmMotGetProfilePriority';
    function AxmSignalSetZphaseLevel; external dll_name name 'AxmSignalSetZphaseLevel';
    function AxmSignalGetZphaseLevel; external dll_name name 'AxmSignalGetZphaseLevel';
    function AxmSignalSetServoOnLevel; external dll_name name 'AxmSignalSetServoOnLevel';
    function AxmSignalGetServoOnLevel; external dll_name name 'AxmSignalGetServoOnLevel';
    function AxmSignalSetServoAlarmResetLevel; external dll_name name 'AxmSignalSetServoAlarmResetLevel';
    function AxmSignalGetServoAlarmResetLevel; external dll_name name 'AxmSignalGetServoAlarmResetLevel';
    function AxmSignalSetInpos; external dll_name name 'AxmSignalSetInpos';
    function AxmSignalGetInpos; external dll_name name 'AxmSignalGetInpos';
    function AxmSignalReadInpos; external dll_name name 'AxmSignalReadInpos';
    function AxmSignalSetServoAlarm; external dll_name name 'AxmSignalSetServoAlarm';
    function AxmSignalGetServoAlarm; external dll_name name 'AxmSignalGetServoAlarm';
    function AxmSignalReadServoAlarm; external dll_name name 'AxmSignalReadServoAlarm';
    function AxmSignalSetLimit; external dll_name name 'AxmSignalSetLimit';
    function AxmSignalGetLimit; external dll_name name 'AxmSignalGetLimit';
    function AxmSignalReadLimit; external dll_name name 'AxmSignalReadLimit';
    function AxmSignalSetSoftLimit; external dll_name name 'AxmSignalSetSoftLimit';
    function AxmSignalGetSoftLimit; external dll_name name 'AxmSignalGetSoftLimit';
    function AxmSignalReadSoftLimit; external dll_name name 'AxmSignalReadSoftLimit';
    function AxmSignalSetStop; external dll_name name 'AxmSignalSetStop';
    function AxmSignalGetStop; external dll_name name 'AxmSignalGetStop';
    function AxmSignalReadStop; external dll_name name 'AxmSignalReadStop';
    function AxmSignalServoOn; external dll_name name 'AxmSignalServoOn';
    function AxmSignalIsServoOn; external dll_name name 'AxmSignalIsServoOn';
    function AxmSignalServoAlarmReset; external dll_name name 'AxmSignalServoAlarmReset';
    function AxmSignalWriteOutput; external dll_name name 'AxmSignalWriteOutput';
    function AxmSignalReadOutput; external dll_name name 'AxmSignalReadOutput';
    function AxmSignalReadBrakeOn; external dll_name name 'AxmSignalReadBrakeOn';
    function AxmSignalWriteOutputBit; external dll_name name 'AxmSignalWriteOutputBit';
    function AxmSignalReadOutputBit; external dll_name name 'AxmSignalReadOutputBit';
    function AxmSignalReadInput; external dll_name name 'AxmSignalReadInput';
    function AxmSignalReadInputBit; external dll_name name 'AxmSignalReadInputBit';
    function AxmSignalSetFilterBandwidth; external dll_name name 'AxmSignalSetFilterBandwidth';
    function AxmSignalGetInputBitCount; external dll_name name 'AxmSignalGetInputBitCount';
    function AxmSignalGetOutputBitCount; external dll_name name 'AxmSignalGetOutputBitCount';
    function AxmStatusReadInMotion; external dll_name name 'AxmStatusReadInMotion';
    function AxmStatusReadDrivePulseCount; external dll_name name 'AxmStatusReadDrivePulseCount';
    function AxmStatusReadMotion; external dll_name name 'AxmStatusReadMotion';
    function AxmStatusReadStop; external dll_name name 'AxmStatusReadStop';
    function AxmStatusReadMechanical; external dll_name name 'AxmStatusReadMechanical';
    function AxmStatusReadVel; external dll_name name 'AxmStatusReadVel';
    function AxmStatusReadPosError; external dll_name name 'AxmStatusReadPosError';
    function AxmStatusReadDriveDistance; external dll_name name 'AxmStatusReadDriveDistance';
    function AxmStatusSetPosType; external dll_name name 'AxmStatusSetPosType';
    function AxmStatusGetPosType; external dll_name name 'AxmStatusGetPosType';
    function AxmStatusSetAbsOrgOffset; external dll_name name 'AxmStatusSetAbsOrgOffset';
    function AxmStatusGetAbsOrgOffset; external dll_name name 'AxmStatusGetAbsOrgOffset';
    function AxmStatusSetActPos; external dll_name name 'AxmStatusSetActPos';
    function AxmStatusGetActPos; external dll_name name 'AxmStatusGetActPos';
    function AxmStatusGetAmpActPos; external dll_name name 'AxmStatusGetAmpActPos';
    function AxmStatusSetCmdPos; external dll_name name 'AxmStatusSetCmdPos';
    function AxmStatusGetCmdPos; external dll_name name 'AxmStatusGetCmdPos';
    function AxmStatusSetPosMatch; external dll_name name 'AxmStatusSetPosMatch';
    function AxmStatusReadMotionInfo; external dll_name name 'AxmStatusReadMotionInfo';
    function AxmStatusRequestServoAlarm; external dll_name name 'AxmStatusRequestServoAlarm';
    function AxmStatusReadServoAlarm; external dll_name name 'AxmStatusReadServoAlarm';
    function AxmStatusGetServoAlarmString; external dll_name name 'AxmStatusGetServoAlarmString';
    function AxmStatusRequestServoAlarmHistory; external dll_name name 'AxmStatusRequestServoAlarmHistory';
    function AxmStatusReadServoAlarmHistory; external dll_name name 'AxmStatusReadServoAlarmHistory';
    function AxmStatusClearServoAlarmHistory; external dll_name name 'AxmStatusClearServoAlarmHistory';
    function AxmHomeSetSignalLevel; external dll_name name 'AxmHomeSetSignalLevel';
    function AxmHomeGetSignalLevel; external dll_name name 'AxmHomeGetSignalLevel';
    function AxmHomeReadSignal; external dll_name name 'AxmHomeReadSignal';
    function AxmHomeSetMethod; external dll_name name 'AxmHomeSetMethod';
    function AxmHomeGetMethod; external dll_name name 'AxmHomeGetMethod';
    function AxmHomeSetFineAdjust; external dll_name name 'AxmHomeSetFineAdjust';
    function AxmHomeGetFineAdjust; external dll_name name 'AxmHomeGetFineAdjust';
    function AxmHomeSetVel; external dll_name name 'AxmHomeSetVel';
    function AxmHomeGetVel; external dll_name name 'AxmHomeGetVel';
    function AxmHomeSetStart; external dll_name name 'AxmHomeSetStart';
    function AxmHomeSetResult; external dll_name name 'AxmHomeSetResult';
    function AxmHomeGetResult; external dll_name name 'AxmHomeGetResult';
    function AxmHomeGetRate; external dll_name name 'AxmHomeGetRate';
    function AxmMoveStartPos; external dll_name name 'AxmMoveStartPos';
    function AxmMovePos; external dll_name name 'AxmMovePos';
    function AxmMoveVel; external dll_name name 'AxmMoveVel';
    function AxmMoveStartMultiVel; external dll_name name 'AxmMoveStartMultiVel';
    function AxmMoveStartMultiVelEx; external dll_name name 'AxmMoveStartMultiVelEx';
    function AxmMoveStartLineVel; external dll_name name 'AxmMoveStartLineVel';
    function AxmMoveSignalSearch; external dll_name name 'AxmMoveSignalSearch';
    function AxmMoveSignalSearchAtDis; external dll_name name 'AxmMoveSignalSearchAtDis';
    function AxmMoveSignalCapture; external dll_name name 'AxmMoveSignalCapture';
    function AxmMoveGetCapturePos; external dll_name name 'AxmMoveGetCapturePos';
    function AxmMoveStartMultiPos; external dll_name name 'AxmMoveStartMultiPos';
    function AxmMoveMultiPos; external dll_name name 'AxmMoveMultiPos';
    function AxmMoveStartTorque; external dll_name name 'AxmMoveStartTorque';
    function AxmMoveTorqueStop; external dll_name name 'AxmMoveTorqueStop';
    function AxmMoveStartPosWithList; external dll_name name 'AxmMoveStartPosWithList';
    function AxmMoveStartPosWithPosEvent; external dll_name name 'AxmMoveStartPosWithPosEvent';
    function AxmMoveStop; external dll_name name 'AxmMoveStop';
    function AxmMoveStopEx; external dll_name name 'AxmMoveStopEx';
    function AxmMoveEStop; external dll_name name 'AxmMoveEStop';
    function AxmMoveSStop; external dll_name name 'AxmMoveSStop';
    function AxmOverridePos; external dll_name name 'AxmOverridePos';
    function AxmOverrideSetMaxVel; external dll_name name 'AxmOverrideSetMaxVel';
    function AxmOverrideVel; external dll_name name 'AxmOverrideVel';
    function AxmOverrideAccelVelDecel; external dll_name name 'AxmOverrideAccelVelDecel';
    function AxmOverrideVelAtPos; external dll_name name 'AxmOverrideVelAtPos';
    function AxmOverrideVelAtMultiPos; external dll_name name 'AxmOverrideVelAtMultiPos';
    function AxmOverrideVelAtMultiPos2; external dll_name name 'AxmOverrideVelAtMultiPos2';
    function AxmLinkSetMode; external dll_name name 'AxmLinkSetMode';
    function AxmLinkGetMode; external dll_name name 'AxmLinkGetMode';
    function AxmLinkResetMode; external dll_name name 'AxmLinkResetMode';
    function AxmGantrySetEnable; external dll_name name 'AxmGantrySetEnable';
    function AxmGantryGetEnable; external dll_name name 'AxmGantryGetEnable';
    function AxmGantrySetDisable; external dll_name name 'AxmGantrySetDisable';
    function AxmGantrySetCompensationGain; external dll_name name 'AxmGantrySetCompensationGain';
    function AxmGantryGetCompensationGain; external dll_name name 'AxmGantryGetCompensationGain';
    function AxmGantrySetErrorRange; external dll_name name 'AxmGantrySetErrorRange';
    function AxmGantryGetErrorRange; external dll_name name 'AxmGantryGetErrorRange';
    function AxmGantryReadErrorRangeStatus; external dll_name name 'AxmGantryReadErrorRangeStatus';
    function AxmGantryReadErrorRangeComparePos; external dll_name name 'AxmGantryReadErrorRangeComparePos';
    function AxmLineMove; external dll_name name 'AxmLineMove';
    function AxmLineMoveEx2; external dll_name name 'AxmLineMoveEx2';
    function AxmCircleCenterMove; external dll_name name 'AxmCircleCenterMove';
    function AxmCirclePointMove; external dll_name name 'AxmCirclePointMove';
    function AxmCirclePointMoveEx; external dll_name name 'AxmCirclePointMoveEx';
    function AxmCircleRadiusMove; external dll_name name 'AxmCircleRadiusMove';
    function AxmCircleAngleMove; external dll_name name 'AxmCircleAngleMove';
    function AxmContiSetAxisMap; external dll_name name 'AxmContiSetAxisMap';
    function AxmContiGetAxisMap; external dll_name name 'AxmContiGetAxisMap';
    function AxmContiResetAxisMap; external dll_name name 'AxmContiResetAxisMap';
    function AxmContiSetAbsRelMode; external dll_name name 'AxmContiSetAbsRelMode';
    function AxmContiGetAbsRelMode; external dll_name name 'AxmContiGetAbsRelMode';
    function AxmContiReadFree; external dll_name name 'AxmContiReadFree';
    function AxmContiReadIndex; external dll_name name 'AxmContiReadIndex';
    function AxmContiWriteClear; external dll_name name 'AxmContiWriteClear';
    function AxmContiBeginNode; external dll_name name 'AxmContiBeginNode';
    function AxmContiEndNode; external dll_name name 'AxmContiEndNode';
    function AxmContiStart; external dll_name name 'AxmContiStart';
    function AxmContiIsMotion; external dll_name name 'AxmContiIsMotion';
    function AxmContiGetNodeNum; external dll_name name 'AxmContiGetNodeNum';
    function AxmContiGetTotalNodeNum; external dll_name name 'AxmContiGetTotalNodeNum';
    function AxmContiDigitalOutputBit; external dll_name name 'AxmContiDigitalOutputBit';
    function AxmContiReadStop; external dll_name name 'AxmContiReadStop';
    function AxmContiSetLineMoveVelMode; external dll_name name 'AxmContiSetLineMoveVelMode';
    function AxmContiGetLineMoveVelMode; external dll_name name 'AxmContiGetLineMoveVelMode';
    function AxmContiSetCheckSoftLimit; external dll_name name 'AxmContiSetCheckSoftLimit';
    function AxmContiGetCheckSoftLimit; external dll_name name 'AxmContiGetCheckSoftLimit';
    function AxmTriggerSetTimeLevel; external dll_name name 'AxmTriggerSetTimeLevel';
    function AxmTriggerGetTimeLevel; external dll_name name 'AxmTriggerGetTimeLevel';
    function AxmTriggerSetAbsPeriod; external dll_name name 'AxmTriggerSetAbsPeriod';
    function AxmTriggerGetAbsPeriod; external dll_name name 'AxmTriggerGetAbsPeriod';
    function AxmTriggerSetBlock; external dll_name name 'AxmTriggerSetBlock';
    function AxmTriggerGetBlock; external dll_name name 'AxmTriggerGetBlock';
    function AxmTriggerOneShot; external dll_name name 'AxmTriggerOneShot';
    function AxmTriggerSetTimerOneshot; external dll_name name 'AxmTriggerSetTimerOneshot';
    function AxmTriggerOnlyAbs; external dll_name name 'AxmTriggerOnlyAbs';
    function AxmTriggerSetReset; external dll_name name 'AxmTriggerSetReset';
    function AxmCrcSetMaskLevel; external dll_name name 'AxmCrcSetMaskLevel';
    function AxmCrcGetMaskLevel; external dll_name name 'AxmCrcGetMaskLevel';
    function AxmCrcSetOutput; external dll_name name 'AxmCrcSetOutput';
    function AxmCrcGetOutput; external dll_name name 'AxmCrcGetOutput';
    function AxmMPGSetEnable; external dll_name name 'AxmMPGSetEnable';
    function AxmMPGGetEnable; external dll_name name 'AxmMPGGetEnable';
    function AxmMPGSetRatio; external dll_name name 'AxmMPGSetRatio';
    function AxmMPGGetRatio; external dll_name name 'AxmMPGGetRatio';
    function AxmMPGReset; external dll_name name 'AxmMPGReset';
    function AxmHelixCenterMove; external dll_name name 'AxmHelixCenterMove';
    function AxmHelixPointMove; external dll_name name 'AxmHelixPointMove';
    function AxmHelixRadiusMove; external dll_name name 'AxmHelixRadiusMove';
    function AxmHelixAngleMove; external dll_name name 'AxmHelixAngleMove';
    function AxmSplineWrite; external dll_name name 'AxmSplineWrite';
    function AxmCompensationSet; external dll_name name 'AxmCompensationSet';
    function AxmCompensationGet; external dll_name name 'AxmCompensationGet';
    function AxmCompensationEnable; external dll_name name 'AxmCompensationEnable';
    function AxmCompensationIsEnable; external dll_name name 'AxmCompensationIsEnable';
    function AxmCompensationGetCorrection; external dll_name name 'AxmCompensationGetCorrection';
    function AxmCompensationSetBacklash; external dll_name name 'AxmCompensationSetBacklash';
    function AxmCompensationGetBacklash; external dll_name name 'AxmCompensationGetBacklash';
    function AxmCompensationEnableBacklash; external dll_name name 'AxmCompensationEnableBacklash';
    function AxmCompensationIsEnableBacklash; external dll_name name 'AxmCompensationIsEnableBacklash';
    function AxmCompensationSetLocating; external dll_name name 'AxmCompensationSetLocating';
    function AxmEcamSet; external dll_name name 'AxmEcamSet';
    function AxmEcamSetWithSource; external dll_name name 'AxmEcamSetWithSource';
    function AxmEcamGet; external dll_name name 'AxmEcamGet';
    function AxmEcamGetWithSource; external dll_name name 'AxmEcamGetWithSource';
    function AxmEcamEnableBySlave; external dll_name name 'AxmEcamEnableBySlave';
    function AxmEcamEnableByMaster; external dll_name name 'AxmEcamEnableByMaster';
    function AxmEcamIsSlaveEnable; external dll_name name 'AxmEcamIsSlaveEnable';
    function AxmStatusSetServoMonitor; external dll_name name 'AxmStatusSetServoMonitor';
    function AxmStatusGetServoMonitor; external dll_name name 'AxmStatusGetServoMonitor';
    function AxmStatusSetServoMonitorEnable; external dll_name name 'AxmStatusSetServoMonitorEnable';
    function AxmStatusGetServoMonitorEnable; external dll_name name 'AxmStatusGetServoMonitorEnable';
    function AxmStatusReadServoMonitorFlag; external dll_name name 'AxmStatusReadServoMonitorFlag';
    function AxmStatusReadServoMonitorValue; external dll_name name 'AxmStatusReadServoMonitorValue';
    function AxmStatusSetReadServoLoadRatio; external dll_name name 'AxmStatusSetReadServoLoadRatio';
    function AxmStatusReadServoLoadRatio; external dll_name name 'AxmStatusReadServoLoadRatio';
    function AxmMotSetScaleCoeff; external dll_name name 'AxmMotSetScaleCoeff';
    function AxmMotGetScaleCoeff; external dll_name name 'AxmMotGetScaleCoeff';
    function AxmMoveSignalSearchEx; external dll_name name 'AxmMoveSignalSearchEx';
    function AxmMoveToAbsPos; external dll_name name 'AxmMoveToAbsPos';
    function AxmStatusReadVelEx; external dll_name name 'AxmStatusReadVelEx';
    function AxmMotSetElectricGearRatio; external dll_name name 'AxmMotSetElectricGearRatio';
    function AxmMotGetElectricGearRatio; external dll_name name 'AxmMotGetElectricGearRatio';
    function AxmMotSetTorqueLimit; external dll_name name 'AxmMotSetTorqueLimit';
    function AxmMotGetTorqueLimit; external dll_name name 'AxmMotGetTorqueLimit';
    function AxmMotSetTorqueLimitAtPos; external dll_name name 'AxmMotSetTorqueLimitAtPos';
    function AxmMotGetTorqueLimitAtPos; external dll_name name 'AxmMotGetTorqueLimitAtPos';
    function AxmMotSetTorqueLimitEnable; external dll_name name 'AxmMotSetTorqueLimitEnable';
    function AxmMotGetTorqueLimitEnable; external dll_name name 'AxmMotGetTorqueLimitEnable';
    function AxmOverridePosSetFunction; external dll_name name 'AxmOverridePosSetFunction';
    function AxmOverridePosGetFunction; external dll_name name 'AxmOverridePosGetFunction';
    function AxmSignalSetWriteOutputBitAtPos; external dll_name name 'AxmSignalSetWriteOutputBitAtPos';
    function AxmSignalGetWriteOutputBitAtPos; external dll_name name 'AxmSignalGetWriteOutputBitAtPos';
    function AxmAdvVSTSetParameter; external dll_name name 'AxmAdvVSTSetParameter';
    function AxmAdvVSTGetParameter; external dll_name name 'AxmAdvVSTGetParameter';
    function AxmAdvVSTSetEnabele; external dll_name name 'AxmAdvVSTSetEnabele';
    function AxmAdvVSTGetEnabele; external dll_name name 'AxmAdvVSTGetEnabele';
    function AxmAdvLineMove; external dll_name name 'AxmAdvLineMove';
    function AxmAdvOvrLineMove; external dll_name name 'AxmAdvOvrLineMove';
    function AxmAdvCircleCenterMove; external dll_name name 'AxmAdvCircleCenterMove';
    function AxmAdvCirclePointMove; external dll_name name 'AxmAdvCirclePointMove';
    function AxmAdvCircleAngleMove; external dll_name name 'AxmAdvCircleAngleMove';
    function AxmAdvCircleRadiusMove; external dll_name name 'AxmAdvCircleRadiusMove';
    function AxmAdvOvrCircleRadiusMove; external dll_name name 'AxmAdvOvrCircleRadiusMove';
    function AxmAdvHelixCenterMove; external dll_name name 'AxmAdvHelixCenterMove';
    function AxmAdvHelixPointMove; external dll_name name 'AxmAdvHelixPointMove';
    function AxmAdvHelixAngleMove; external dll_name name 'AxmAdvHelixAngleMove';
    function AxmAdvHelixRadiusMove; external dll_name name 'AxmAdvHelixRadiusMove';
    function AxmAdvOvrHelixRadiusMove; external dll_name name 'AxmAdvOvrHelixRadiusMove';
    function AxmAdvScriptLineMove; external dll_name name 'AxmAdvScriptLineMove';
    function AxmAdvScriptOvrLineMove; external dll_name name 'AxmAdvScriptOvrLineMove';
    function AxmAdvScriptCircleCenterMove; external dll_name name 'AxmAdvScriptCircleCenterMove';
    function AxmAdvScriptCirclePointMove; external dll_name name 'AxmAdvScriptCirclePointMove';
    function AxmAdvScriptCircleAngleMove; external dll_name name 'AxmAdvScriptCircleAngleMove';
    function AxmAdvScriptCircleRadiusMove; external dll_name name 'AxmAdvScriptCircleRadiusMove';
    function AxmAdvScriptOvrCircleRadiusMove; external dll_name name 'AxmAdvScriptOvrCircleRadiusMove';
    function AxmAdvScriptHelixCenterMove; external dll_name name 'AxmAdvScriptHelixCenterMove';
    function AxmAdvScriptHelixPointMove; external dll_name name 'AxmAdvScriptHelixPointMove';
    function AxmAdvScriptHelixAngleMove; external dll_name name 'AxmAdvScriptHelixAngleMove';
    function AxmAdvScriptHelixRadiusMove; external dll_name name 'AxmAdvScriptHelixRadiusMove';
    function AxmAdvScriptOvrHelixRadiusMove; external dll_name name 'AxmAdvScriptOvrHelixRadiusMove';
    function AxmAdvContiGetNodeNum; external dll_name name 'AxmAdvContiGetNodeNum';
    function AxmAdvContiGetTotalNodeNum; external dll_name name 'AxmAdvContiGetTotalNodeNum';
    function AxmAdvContiReadIndex; external dll_name name 'AxmAdvContiReadIndex';
    function AxmAdvContiReadFree; external dll_name name 'AxmAdvContiReadFree';
    function AxmAdvContiWriteClear; external dll_name name 'AxmAdvContiWriteClear';
    function AxmAdvOvrContiWriteClear; external dll_name name 'AxmAdvOvrContiWriteClear';
    function AxmAdvContiStart; external dll_name name 'AxmAdvContiStart';
    function AxmAdvContiStop; external dll_name name 'AxmAdvContiStop';
    function AxmAdvContiSetAxisMap; external dll_name name 'AxmAdvContiSetAxisMap';
    function AxmAdvContiGetAxisMap; external dll_name name 'AxmAdvContiGetAxisMap';
    function AxmAdvContiSetAbsRelMode; external dll_name name 'AxmAdvContiSetAbsRelMode';
    function AxmAdvContiGetAbsRelMode; external dll_name name 'AxmAdvContiGetAbsRelMode';
    function AxmAdvContiIsMotion; external dll_name name 'AxmAdvContiIsMotion';
    function AxmAdvContiBeginNode; external dll_name name 'AxmAdvContiBeginNode';
    function AxmAdvContiEndNode; external dll_name name 'AxmAdvContiEndNode';
    function AxmMoveMultiStop; external dll_name name 'AxmMoveMultiStop';
    function AxmMoveMultiEStop; external dll_name name 'AxmMoveMultiEStop';
    function AxmMoveMultiSStop; external dll_name name 'AxmMoveMultiSStop';
    function AxmStatusReadActVel; external dll_name name 'AxmStatusReadActVel';
    function AxmStatusReadServoCmdStat; external dll_name name 'AxmStatusReadServoCmdStat';
    function AxmStatusReadServoCmdCtrl; external dll_name name 'AxmStatusReadServoCmdCtrl';
    function AxmGantryGetMstToSlvOverDist; external dll_name name 'AxmGantryGetMstToSlvOverDist';
    function AxmGantrySetMstToSlvOverDist; external dll_name name 'AxmGantrySetMstToSlvOverDist';
    function AxmSignalReadServoAlarmCode; external dll_name name 'AxmSignalReadServoAlarmCode';
    function AxmM3ServoCoordinatesSet; external dll_name name 'AxmM3ServoCoordinatesSet';
    function AxmM3ServoBreakOn; external dll_name name 'AxmM3ServoBreakOn';
    function AxmM3ServoBreakOff; external dll_name name 'AxmM3ServoBreakOff';
    function AxmM3ServoConfig; external dll_name name 'AxmM3ServoConfig';
    function AxmM3ServoSensOn; external dll_name name 'AxmM3ServoSensOn';
    function AxmM3ServoSensOff; external dll_name name 'AxmM3ServoSensOff';
    function AxmM3ServoSmon; external dll_name name 'AxmM3ServoSmon';
    function AxmM3ServoGetSmon; external dll_name name 'AxmM3ServoGetSmon';
    function AxmM3ServoSvOn; external dll_name name 'AxmM3ServoSvOn';
    function AxmM3ServoSvOff; external dll_name name 'AxmM3ServoSvOff';
    function AxmM3ServoInterpolate; external dll_name name 'AxmM3ServoInterpolate';
    function AxmM3ServoPosing; external dll_name name 'AxmM3ServoPosing';
    function AxmM3ServoFeed; external dll_name name 'AxmM3ServoFeed';
    function AxmM3ServoExFeed; external dll_name name 'AxmM3ServoExFeed';
    function AxmM3ServoExPosing; external dll_name name 'AxmM3ServoExPosing';
    function AxmM3ServoZret; external dll_name name 'AxmM3ServoZret';
    function AxmM3ServoVelctrl; external dll_name name 'AxmM3ServoVelctrl';
    function AxmM3ServoTrqctrl; external dll_name name 'AxmM3ServoTrqctrl';
    function AxmM3ServoGetParameter; external dll_name name 'AxmM3ServoGetParameter';
    function AxmM3ServoSetParameter; external dll_name name 'AxmM3ServoSetParameter';
    function AxmServoCmdExecution; external dll_name name 'AxmServoCmdExecution';
    function AxmM3ServoGetTorqLimit; external dll_name name 'AxmM3ServoGetTorqLimit';
    function AxmM3ServoSetTorqLimit; external dll_name name 'AxmM3ServoSetTorqLimit';
    function AxmM3ServoGetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoGetSendSvCmdIOOutput';
    function AxmM3ServoSetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoSetSendSvCmdIOOutput';
    function AxmM3ServoGetSvCmdCtrl; external dll_name name 'AxmM3ServoGetSvCmdCtrl';
    function AxmM3ServoSetSvCmdCtrl; external dll_name name 'AxmM3ServoSetSvCmdCtrl';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmM3ServoSetMonSel; external dll_name name 'AxmM3ServoSetMonSel';
    function AxmM3ServoGetMonSel; external dll_name name 'AxmM3ServoGetMonSel';
    function AxmM3ServoReadMonData; external dll_name name 'AxmM3ServoReadMonData';
    function AxmAdvTorqueContiSetAxisMap; external dll_name name 'AxmAdvTorqueContiSetAxisMap';
    function AxmM3ServoSetTorqProfile; external dll_name name 'AxmM3ServoSetTorqProfile';
    function AxmM3ServoGetTorqProfile; external dll_name name 'AxmM3ServoGetTorqProfile';
    function AxmSignalSetInposRange; external dll_name name 'AxmSignalSetInposRange';
    function AxmSignalGetInposRange; external dll_name name 'AxmSignalGetInposRange';
    function AxmStatusSetEncClear; external dll_name name 'AxmStatusSetEncClear';
    function AxmStatusSetMotorPosMatch; external dll_name name 'AxmStatusSetMotorPosMatch';
    function AxmMotSetWorkCoordinate; external dll_name name 'AxmMotSetWorkCoordinate';
    function AxmMotGetWorkCoordinate; external dll_name name 'AxmMotGetWorkCoordinate';
    function AxmMotSetOverridePosMode; external dll_name name 'AxmMotSetOverridePosMode';
    function AxmMotGetOverridePosMode; external dll_name name 'AxmMotGetOverridePosMode';
    function AxmMotSetOverrideLinePosMode; external dll_name name 'AxmMotSetOverrideLinePosMode';
    function AxmMotGetOverrideLinePosMode; external dll_name name 'AxmMotGetOverrideLinePosMode';
    function AxmMotSetVibrationControl; external dll_name name 'AxmMotSetVibrationControl';
    function AxmMotVibrationControlEnable; external dll_name name 'AxmMotVibrationControlEnable';
    function AxmMotVibrationControlIsEnable; external dll_name name 'AxmMotVibrationControlIsEnable';
    function AxmMotVibrationControlCoordEnable; external dll_name name 'AxmMotVibrationControlCoordEnable';
    function AxmMotVibrationControlCoordIsEnable; external dll_name name 'AxmMotVibrationControlCoordIsEnable';
    function AxmMotSetMultiTorqueLimit; external dll_name name 'AxmMotSetMultiTorqueLimit';
    function AxmMotMultiTorqueLimitEnable; external dll_name name 'AxmMotMultiTorqueLimitEnable';
    function AxmMotMultiTorqueLimitIsEnable; external dll_name name 'AxmMotMultiTorqueLimitIsEnable';
    function AxmMoveStartPosEx; external dll_name name 'AxmMoveStartPosEx';
    function AxmMovePosEx; external dll_name name 'AxmMovePosEx';
    function AxmMoveCoordStop; external dll_name name 'AxmMoveCoordStop';
    function AxmMoveCoordEStop; external dll_name name 'AxmMoveCoordEStop';
    function AxmMoveCoordSStop; external dll_name name 'AxmMoveCoordSStop';
    function AxmOverrideLinePos; external dll_name name 'AxmOverrideLinePos';
    function AxmOverrideLineVel; external dll_name name 'AxmOverrideLineVel';
    function AxmOverrideLineAccelVelDecel; external dll_name name 'AxmOverrideLineAccelVelDecel';
    function AxmOverrideAccelVelDecelAtPos; external dll_name name 'AxmOverrideAccelVelDecelAtPos';
    function AxmEGearSet; external dll_name name 'AxmEGearSet';
    function AxmEGearGet; external dll_name name 'AxmEGearGet';
    function AxmEGearReset; external dll_name name 'AxmEGearReset';
    function AxmEGearEnable; external dll_name name 'AxmEGearEnable';
    function AxmEGearIsEnable; external dll_name name 'AxmEGearIsEnable';
    function AxmHelixPitchMove; external dll_name name 'AxmHelixPitchMove';
    function AxmCompensationOneDimSet; external dll_name name 'AxmCompensationOneDimSet';
    function AxmCompensationOneDimGet; external dll_name name 'AxmCompensationOneDimGet';
    function AxmCompensationOneDimReset; external dll_name name 'AxmCompensationOneDimReset';
    function AxmCompensationOneDimEnable; external dll_name name 'AxmCompensationOneDimEnable';
    function AxmCompensationOneDimIsEnable; external dll_name name 'AxmCompensationOneDimIsEnable';
    function AxmCompensationOneDimGetCorrection; external dll_name name 'AxmCompensationOneDimGetCorrection';
    function AxmCompensationTwoDimSet; external dll_name name 'AxmCompensationTwoDimSet';
    function AxmCompensationTwoDimGet; external dll_name name 'AxmCompensationTwoDimGet';
    function AxmCompensationTwoDimReset; external dll_name name 'AxmCompensationTwoDimReset';
    function AxmCompensationTwoDimEnable; external dll_name name 'AxmCompensationTwoDimEnable';
    function AxmCompensationTwoDimIsEnable; external dll_name name 'AxmCompensationTwoDimIsEnable';
    function AxmCompensationTwoDimGetCorrection; external dll_name name 'AxmCompensationTwoDimGetCorrection';
    function AxmBlendingCoordSet; external dll_name name 'AxmBlendingCoordSet';
    function AxmBlendingCoordGet; external dll_name name 'AxmBlendingCoordGet';
    function AxmBlendingCoordReset; external dll_name name 'AxmBlendingCoordReset';
    function AxmBlendingCoordEnable; external dll_name name 'AxmBlendingCoordEnable';
    function AxmBlendingCoordIsEnable; external dll_name name 'AxmBlendingCoordIsEnable';
    function AxmStatusReadTorque; external dll_name name 'AxmStatusReadTorque';
    function AxmMotSetEndVel; external dll_name name 'AxmMotSetEndVel';
    function AxmMotGetEndVel; external dll_name name 'AxmMotGetEndVel';
    function AxmLineMoveWithAxes; external dll_name name 'AxmLineMoveWithAxes';
    function AxmCircleCenterMoveWithAxes; external dll_name name 'AxmCircleCenterMoveWithAxes';
    function AxmLineMoveWithAxesWithEvent; external dll_name name 'AxmLineMoveWithAxesWithEvent';
    function AxmCircleCenterMoveWithAxesWithEvent; external dll_name name 'AxmCircleCenterMoveWithAxesWithEvent';
    function AxmInfoGetAxis; external dll_name name 'AxmInfoGetAxis';
    function AxmInfoGetAxisEx; external dll_name name 'AxmInfoGetAxisEx';
    function AxmInfoIsMotionModule; external dll_name name 'AxmInfoIsMotionModule';
    function AxmInfoIsInvalidAxisNo; external dll_name name 'AxmInfoIsInvalidAxisNo';
    function AxmInfoGetAxisStatus; external dll_name name 'AxmInfoGetAxisStatus';
    function AxmInfoGetAxisCount; external dll_name name 'AxmInfoGetAxisCount';
    function AxmInfoGetFirstAxisNo; external dll_name name 'AxmInfoGetFirstAxisNo';
    function AxmInfoGetBoardFirstAxisNo; external dll_name name 'AxmInfoGetBoardFirstAxisNo';
    function AxmVirtualSetAxisNoMap; external dll_name name 'AxmVirtualSetAxisNoMap';
    function AxmVirtualGetAxisNoMap; external dll_name name 'AxmVirtualGetAxisNoMap';
    function AxmVirtualSetMultiAxisNoMap; external dll_name name 'AxmVirtualSetMultiAxisNoMap';
    function AxmVirtualGetMultiAxisNoMap; external dll_name name 'AxmVirtualGetMultiAxisNoMap';
    function AxmVirtualResetAxisMap; external dll_name name 'AxmVirtualResetAxisMap';
    function AxmInterruptSetAxis; external dll_name name 'AxmInterruptSetAxis';
    function AxmInterruptSetAxisEnable; external dll_name name 'AxmInterruptSetAxisEnable';
    function AxmInterruptGetAxisEnable; external dll_name name 'AxmInterruptGetAxisEnable';
    function AxmInterruptRead; external dll_name name 'AxmInterruptRead';
    function AxmInterruptReadAxisFlag; external dll_name name 'AxmInterruptReadAxisFlag';
    function AxmInterruptSetUserEnable; external dll_name name 'AxmInterruptSetUserEnable';
    function AxmInterruptGetUserEnable; external dll_name name 'AxmInterruptGetUserEnable';
    function AxmMotLoadParaAll; external dll_name name 'AxmMotLoadParaAll';
    function AxmMotSaveParaAll; external dll_name name 'AxmMotSaveParaAll';
    function AxmMotSetParaLoad; external dll_name name 'AxmMotSetParaLoad';
    function AxmMotGetParaLoad; external dll_name name 'AxmMotGetParaLoad';
    function AxmMotSetPulseOutMethod; external dll_name name 'AxmMotSetPulseOutMethod';
    function AxmMotGetPulseOutMethod; external dll_name name 'AxmMotGetPulseOutMethod';
    function AxmMotSetEncInputMethod; external dll_name name 'AxmMotSetEncInputMethod';
    function AxmMotGetEncInputMethod; external dll_name name 'AxmMotGetEncInputMethod';
    function AxmMotSetMoveUnitPerPulse; external dll_name name 'AxmMotSetMoveUnitPerPulse';
    function AxmMotGetMoveUnitPerPulse; external dll_name name 'AxmMotGetMoveUnitPerPulse';
    function AxmMotSetDecelMode; external dll_name name 'AxmMotSetDecelMode';
    function AxmMotGetDecelMode; external dll_name name 'AxmMotGetDecelMode';
    function AxmMotSetRemainPulse; external dll_name name 'AxmMotSetRemainPulse';
    function AxmMotGetRemainPulse; external dll_name name 'AxmMotGetRemainPulse';
    function AxmMotSetMaxVel; external dll_name name 'AxmMotSetMaxVel';
    function AxmMotGetMaxVel; external dll_name name 'AxmMotGetMaxVel';
    function AxmMotSetAbsRelMode; external dll_name name 'AxmMotSetAbsRelMode';
    function AxmMotGetAbsRelMode; external dll_name name 'AxmMotGetAbsRelMode';
    function AxmMotSetProfileMode; external dll_name name 'AxmMotSetProfileMode';
    function AxmMotGetProfileMode; external dll_name name 'AxmMotGetProfileMode';
    function AxmMotSetAccelUnit; external dll_name name 'AxmMotSetAccelUnit';
    function AxmMotGetAccelUnit; external dll_name name 'AxmMotGetAccelUnit';
    function AxmMotSetMinVel; external dll_name name 'AxmMotSetMinVel';
    function AxmMotGetMinVel; external dll_name name 'AxmMotGetMinVel';
    function AxmMotSetAccelJerk; external dll_name name 'AxmMotSetAccelJerk';
    function AxmMotGetAccelJerk; external dll_name name 'AxmMotGetAccelJerk';
    function AxmMotSetDecelJerk; external dll_name name 'AxmMotSetDecelJerk';
    function AxmMotGetDecelJerk; external dll_name name 'AxmMotGetDecelJerk';
    function AxmMotSetProfilePriority; external dll_name name 'AxmMotSetProfilePriority';
    function AxmMotGetProfilePriority; external dll_name name 'AxmMotGetProfilePriority';
    function AxmSignalSetZphaseLevel; external dll_name name 'AxmSignalSetZphaseLevel';
    function AxmSignalGetZphaseLevel; external dll_name name 'AxmSignalGetZphaseLevel';
    function AxmSignalSetServoOnLevel; external dll_name name 'AxmSignalSetServoOnLevel';
    function AxmSignalGetServoOnLevel; external dll_name name 'AxmSignalGetServoOnLevel';
    function AxmSignalSetServoAlarmResetLevel; external dll_name name 'AxmSignalSetServoAlarmResetLevel';
    function AxmSignalGetServoAlarmResetLevel; external dll_name name 'AxmSignalGetServoAlarmResetLevel';
    function AxmSignalSetInpos; external dll_name name 'AxmSignalSetInpos';
    function AxmSignalGetInpos; external dll_name name 'AxmSignalGetInpos';
    function AxmSignalReadInpos; external dll_name name 'AxmSignalReadInpos';
    function AxmSignalSetServoAlarm; external dll_name name 'AxmSignalSetServoAlarm';
    function AxmSignalGetServoAlarm; external dll_name name 'AxmSignalGetServoAlarm';
    function AxmSignalReadServoAlarm; external dll_name name 'AxmSignalReadServoAlarm';
    function AxmSignalSetLimit; external dll_name name 'AxmSignalSetLimit';
    function AxmSignalGetLimit; external dll_name name 'AxmSignalGetLimit';
    function AxmSignalReadLimit; external dll_name name 'AxmSignalReadLimit';
    function AxmSignalSetSoftLimit; external dll_name name 'AxmSignalSetSoftLimit';
    function AxmSignalGetSoftLimit; external dll_name name 'AxmSignalGetSoftLimit';
    function AxmSignalReadSoftLimit; external dll_name name 'AxmSignalReadSoftLimit';
    function AxmSignalSetStop; external dll_name name 'AxmSignalSetStop';
    function AxmSignalGetStop; external dll_name name 'AxmSignalGetStop';
    function AxmSignalReadStop; external dll_name name 'AxmSignalReadStop';
    function AxmSignalServoOn; external dll_name name 'AxmSignalServoOn';
    function AxmSignalIsServoOn; external dll_name name 'AxmSignalIsServoOn';
    function AxmSignalServoAlarmReset; external dll_name name 'AxmSignalServoAlarmReset';
    function AxmSignalWriteOutput; external dll_name name 'AxmSignalWriteOutput';
    function AxmSignalReadOutput; external dll_name name 'AxmSignalReadOutput';
    function AxmSignalReadBrakeOn; external dll_name name 'AxmSignalReadBrakeOn';
    function AxmSignalWriteOutputBit; external dll_name name 'AxmSignalWriteOutputBit';
    function AxmSignalReadOutputBit; external dll_name name 'AxmSignalReadOutputBit';
    function AxmSignalReadInput; external dll_name name 'AxmSignalReadInput';
    function AxmSignalReadInputBit; external dll_name name 'AxmSignalReadInputBit';
    function AxmSignalSetFilterBandwidth; external dll_name name 'AxmSignalSetFilterBandwidth';
    function AxmSignalGetInputBitCount; external dll_name name 'AxmSignalGetInputBitCount';
    function AxmSignalGetOutputBitCount; external dll_name name 'AxmSignalGetOutputBitCount';
    function AxmStatusReadInMotion; external dll_name name 'AxmStatusReadInMotion';
    function AxmStatusReadDrivePulseCount; external dll_name name 'AxmStatusReadDrivePulseCount';
    function AxmStatusReadMotion; external dll_name name 'AxmStatusReadMotion';
    function AxmStatusReadStop; external dll_name name 'AxmStatusReadStop';
    function AxmStatusReadMechanical; external dll_name name 'AxmStatusReadMechanical';
    function AxmStatusReadVel; external dll_name name 'AxmStatusReadVel';
    function AxmStatusReadPosError; external dll_name name 'AxmStatusReadPosError';
    function AxmStatusReadDriveDistance; external dll_name name 'AxmStatusReadDriveDistance';
    function AxmStatusSetPosType; external dll_name name 'AxmStatusSetPosType';
    function AxmStatusGetPosType; external dll_name name 'AxmStatusGetPosType';
    function AxmStatusSetAbsOrgOffset; external dll_name name 'AxmStatusSetAbsOrgOffset';
    function AxmStatusGetAbsOrgOffset; external dll_name name 'AxmStatusGetAbsOrgOffset';
    function AxmStatusSetActPos; external dll_name name 'AxmStatusSetActPos';
    function AxmStatusGetActPos; external dll_name name 'AxmStatusGetActPos';
    function AxmStatusSetCmdPos; external dll_name name 'AxmStatusSetCmdPos';
    function AxmStatusGetCmdPos; external dll_name name 'AxmStatusGetCmdPos';
    function AxmStatusSetPosMatch; external dll_name name 'AxmStatusSetPosMatch';
    function AxmStatusReadMotionInfo; external dll_name name 'AxmStatusReadMotionInfo';
    function AxmStatusRequestServoAlarm; external dll_name name 'AxmStatusRequestServoAlarm';
    function AxmStatusReadServoAlarm; external dll_name name 'AxmStatusReadServoAlarm';
    function AxmStatusGetServoAlarmString; external dll_name name 'AxmStatusGetServoAlarmString';
    function AxmStatusRequestServoAlarmHistory; external dll_name name 'AxmStatusRequestServoAlarmHistory';
    function AxmStatusReadServoAlarmHistory; external dll_name name 'AxmStatusReadServoAlarmHistory';
    function AxmStatusClearServoAlarmHistory; external dll_name name 'AxmStatusClearServoAlarmHistory';
    function AxmHomeSetSignalLevel; external dll_name name 'AxmHomeSetSignalLevel';
    function AxmHomeGetSignalLevel; external dll_name name 'AxmHomeGetSignalLevel';
    function AxmHomeReadSignal; external dll_name name 'AxmHomeReadSignal';
    function AxmHomeSetMethod; external dll_name name 'AxmHomeSetMethod';
    function AxmHomeGetMethod; external dll_name name 'AxmHomeGetMethod';
    function AxmHomeSetFineAdjust; external dll_name name 'AxmHomeSetFineAdjust';
    function AxmHomeGetFineAdjust; external dll_name name 'AxmHomeGetFineAdjust';
    function AxmHomeSetVel; external dll_name name 'AxmHomeSetVel';
    function AxmHomeGetVel; external dll_name name 'AxmHomeGetVel';
    function AxmHomeSetStart; external dll_name name 'AxmHomeSetStart';
    function AxmHomeSetResult; external dll_name name 'AxmHomeSetResult';
    function AxmHomeGetResult; external dll_name name 'AxmHomeGetResult';
    function AxmHomeGetRate; external dll_name name 'AxmHomeGetRate';
    function AxmMoveStartPos; external dll_name name 'AxmMoveStartPos';
    function AxmMovePos; external dll_name name 'AxmMovePos';
    function AxmMoveVel; external dll_name name 'AxmMoveVel';
    function AxmMoveStartMultiVel; external dll_name name 'AxmMoveStartMultiVel';
    function AxmMoveStartMultiVelEx; external dll_name name 'AxmMoveStartMultiVelEx';
    function AxmMoveStartLineVel; external dll_name name 'AxmMoveStartLineVel';
    function AxmMoveSignalSearch; external dll_name name 'AxmMoveSignalSearch';
    function AxmMoveSignalSearchAtDis; external dll_name name 'AxmMoveSignalSearchAtDis';
    function AxmMoveSignalCapture; external dll_name name 'AxmMoveSignalCapture';
    function AxmMoveGetCapturePos; external dll_name name 'AxmMoveGetCapturePos';
    function AxmMoveStartMultiPos; external dll_name name 'AxmMoveStartMultiPos';
    function AxmMoveMultiPos; external dll_name name 'AxmMoveMultiPos';
    function AxmMoveStartTorque; external dll_name name 'AxmMoveStartTorque';
    function AxmMoveTorqueStop; external dll_name name 'AxmMoveTorqueStop';
    function AxmMoveStartPosWithList; external dll_name name 'AxmMoveStartPosWithList';
    function AxmMoveStartPosWithPosEvent; external dll_name name 'AxmMoveStartPosWithPosEvent';
    function AxmMoveStop; external dll_name name 'AxmMoveStop';
    function AxmMoveStopEx; external dll_name name 'AxmMoveStopEx';
    function AxmMoveEStop; external dll_name name 'AxmMoveEStop';
    function AxmMoveSStop; external dll_name name 'AxmMoveSStop';
    function AxmOverridePos; external dll_name name 'AxmOverridePos';
    function AxmOverrideSetMaxVel; external dll_name name 'AxmOverrideSetMaxVel';
    function AxmOverrideVel; external dll_name name 'AxmOverrideVel';
    function AxmOverrideAccelVelDecel; external dll_name name 'AxmOverrideAccelVelDecel';
    function AxmOverrideVelAtPos; external dll_name name 'AxmOverrideVelAtPos';
    function AxmOverrideVelAtMultiPos; external dll_name name 'AxmOverrideVelAtMultiPos';
    function AxmOverrideVelAtMultiPos2; external dll_name name 'AxmOverrideVelAtMultiPos2';
    function AxmLinkSetMode; external dll_name name 'AxmLinkSetMode';
    function AxmLinkGetMode; external dll_name name 'AxmLinkGetMode';
    function AxmLinkResetMode; external dll_name name 'AxmLinkResetMode';
    function AxmGantrySetEnable; external dll_name name 'AxmGantrySetEnable';
    function AxmGantryGetEnable; external dll_name name 'AxmGantryGetEnable';
    function AxmGantrySetDisable; external dll_name name 'AxmGantrySetDisable';
    function AxmGantrySetCompensationGain; external dll_name name 'AxmGantrySetCompensationGain';
    function AxmGantryGetCompensationGain; external dll_name name 'AxmGantryGetCompensationGain';
    function AxmGantrySetErrorRange; external dll_name name 'AxmGantrySetErrorRange';
    function AxmGantryGetErrorRange; external dll_name name 'AxmGantryGetErrorRange';
    function AxmGantryReadErrorRangeStatus; external dll_name name 'AxmGantryReadErrorRangeStatus';
    function AxmGantryReadErrorRangeComparePos; external dll_name name 'AxmGantryReadErrorRangeComparePos';
    function AxmLineMove; external dll_name name 'AxmLineMove';
    function AxmLineMoveEx2; external dll_name name 'AxmLineMoveEx2';
    function AxmCircleCenterMove; external dll_name name 'AxmCircleCenterMove';
    function AxmCirclePointMove; external dll_name name 'AxmCirclePointMove';
    function AxmCirclePointMoveEx; external dll_name name 'AxmCirclePointMoveEx';
    function AxmCircleRadiusMove; external dll_name name 'AxmCircleRadiusMove';
    function AxmCircleAngleMove; external dll_name name 'AxmCircleAngleMove';
    function AxmContiSetAxisMap; external dll_name name 'AxmContiSetAxisMap';
    function AxmContiGetAxisMap; external dll_name name 'AxmContiGetAxisMap';
    function AxmContiSetAbsRelMode; external dll_name name 'AxmContiSetAbsRelMode';
    function AxmContiGetAbsRelMode; external dll_name name 'AxmContiGetAbsRelMode';
    function AxmContiReadFree; external dll_name name 'AxmContiReadFree';
    function AxmContiReadIndex; external dll_name name 'AxmContiReadIndex';
    function AxmContiWriteClear; external dll_name name 'AxmContiWriteClear';
    function AxmContiBeginNode; external dll_name name 'AxmContiBeginNode';
    function AxmContiEndNode; external dll_name name 'AxmContiEndNode';
    function AxmContiStart; external dll_name name 'AxmContiStart';
    function AxmContiIsMotion; external dll_name name 'AxmContiIsMotion';
    function AxmContiGetNodeNum; external dll_name name 'AxmContiGetNodeNum';
    function AxmContiGetTotalNodeNum; external dll_name name 'AxmContiGetTotalNodeNum';
    function AxmContiDigitalOutputBit; external dll_name name 'AxmContiDigitalOutputBit';
    function AxmTriggerSetTimeLevel; external dll_name name 'AxmTriggerSetTimeLevel';
    function AxmTriggerGetTimeLevel; external dll_name name 'AxmTriggerGetTimeLevel';
    function AxmTriggerSetAbsPeriod; external dll_name name 'AxmTriggerSetAbsPeriod';
    function AxmTriggerGetAbsPeriod; external dll_name name 'AxmTriggerGetAbsPeriod';
    function AxmTriggerSetBlock; external dll_name name 'AxmTriggerSetBlock';
    function AxmTriggerGetBlock; external dll_name name 'AxmTriggerGetBlock';
    function AxmTriggerOneShot; external dll_name name 'AxmTriggerOneShot';
    function AxmTriggerSetTimerOneshot; external dll_name name 'AxmTriggerSetTimerOneshot';
    function AxmTriggerOnlyAbs; external dll_name name 'AxmTriggerOnlyAbs';
    function AxmTriggerSetReset; external dll_name name 'AxmTriggerSetReset';
    function AxmCrcSetMaskLevel; external dll_name name 'AxmCrcSetMaskLevel';
    function AxmCrcGetMaskLevel; external dll_name name 'AxmCrcGetMaskLevel';
    function AxmCrcSetOutput; external dll_name name 'AxmCrcSetOutput';
    function AxmCrcGetOutput; external dll_name name 'AxmCrcGetOutput';
    function AxmMPGSetEnable; external dll_name name 'AxmMPGSetEnable';
    function AxmMPGGetEnable; external dll_name name 'AxmMPGGetEnable';
    function AxmMPGSetRatio; external dll_name name 'AxmMPGSetRatio';
    function AxmMPGGetRatio; external dll_name name 'AxmMPGGetRatio';
    function AxmMPGReset; external dll_name name 'AxmMPGReset';
    function AxmHelixCenterMove; external dll_name name 'AxmHelixCenterMove';
    function AxmHelixPointMove; external dll_name name 'AxmHelixPointMove';
    function AxmHelixRadiusMove; external dll_name name 'AxmHelixRadiusMove';
    function AxmHelixAngleMove; external dll_name name 'AxmHelixAngleMove';
    function AxmSplineWrite; external dll_name name 'AxmSplineWrite';
    function AxmCompensationSet; external dll_name name 'AxmCompensationSet';
    function AxmCompensationGet; external dll_name name 'AxmCompensationGet';
    function AxmCompensationEnable; external dll_name name 'AxmCompensationEnable';
    function AxmCompensationIsEnable; external dll_name name 'AxmCompensationIsEnable';
    function AxmCompensationGetCorrection; external dll_name name 'AxmCompensationGetCorrection';
    function AxmCompensationSetBacklash; external dll_name name 'AxmCompensationSetBacklash';
    function AxmCompensationGetBacklash; external dll_name name 'AxmCompensationGetBacklash';
    function AxmCompensationEnableBacklash; external dll_name name 'AxmCompensationEnableBacklash';
    function AxmCompensationIsEnableBacklash; external dll_name name 'AxmCompensationIsEnableBacklash';
    function AxmCompensationSetLocating; external dll_name name 'AxmCompensationSetLocating';
    function AxmEcamSet; external dll_name name 'AxmEcamSet';
    function AxmEcamSetWithSource; external dll_name name 'AxmEcamSetWithSource';
    function AxmEcamGet; external dll_name name 'AxmEcamGet';
    function AxmEcamGetWithSource; external dll_name name 'AxmEcamGetWithSource';
    function AxmEcamEnableBySlave; external dll_name name 'AxmEcamEnableBySlave';
    function AxmEcamEnableByMaster; external dll_name name 'AxmEcamEnableByMaster';
    function AxmEcamIsSlaveEnable; external dll_name name 'AxmEcamIsSlaveEnable';
    function AxmStatusSetServoMonitor; external dll_name name 'AxmStatusSetServoMonitor';
    function AxmStatusGetServoMonitor; external dll_name name 'AxmStatusGetServoMonitor';
    function AxmStatusSetServoMonitorEnable; external dll_name name 'AxmStatusSetServoMonitorEnable';
    function AxmStatusGetServoMonitorEnable; external dll_name name 'AxmStatusGetServoMonitorEnable';
    function AxmStatusReadServoMonitorFlag; external dll_name name 'AxmStatusReadServoMonitorFlag';
    function AxmStatusReadServoMonitorValue; external dll_name name 'AxmStatusReadServoMonitorValue';
    function AxmStatusSetReadServoLoadRatio; external dll_name name 'AxmStatusSetReadServoLoadRatio';
    function AxmStatusReadServoLoadRatio; external dll_name name 'AxmStatusReadServoLoadRatio';
    function AxmMotSetScaleCoeff; external dll_name name 'AxmMotSetScaleCoeff';
    function AxmMotGetScaleCoeff; external dll_name name 'AxmMotGetScaleCoeff';
    function AxmMoveSignalSearchEx; external dll_name name 'AxmMoveSignalSearchEx';
    function AxmMoveToAbsPos; external dll_name name 'AxmMoveToAbsPos';
    function AxmStatusReadVelEx; external dll_name name 'AxmStatusReadVelEx';
    function AxmMotSetElectricGearRatio; external dll_name name 'AxmMotSetElectricGearRatio';
    function AxmMotGetElectricGearRatio; external dll_name name 'AxmMotGetElectricGearRatio';
    function AxmMotSetTorqueLimit; external dll_name name 'AxmMotSetTorqueLimit';
    function AxmMotGetTorqueLimit; external dll_name name 'AxmMotGetTorqueLimit';
    function AxmMotSetTorqueLimitAtPos; external dll_name name 'AxmMotSetTorqueLimitAtPos';
    function AxmMotGetTorqueLimitAtPos; external dll_name name 'AxmMotGetTorqueLimitAtPos';
    function AxmMotSetTorqueLimitEnable; external dll_name name 'AxmMotSetTorqueLimitEnable';
    function AxmMotGetTorqueLimitEnable; external dll_name name 'AxmMotGetTorqueLimitEnable';
    function AxmOverridePosSetFunction; external dll_name name 'AxmOverridePosSetFunction';
    function AxmOverridePosGetFunction; external dll_name name 'AxmOverridePosGetFunction';
    function AxmSignalSetWriteOutputBitAtPos; external dll_name name 'AxmSignalSetWriteOutputBitAtPos';
    function AxmSignalGetWriteOutputBitAtPos; external dll_name name 'AxmSignalGetWriteOutputBitAtPos';
    function AxmAdvVSTSetParameter; external dll_name name 'AxmAdvVSTSetParameter';
    function AxmAdvVSTGetParameter; external dll_name name 'AxmAdvVSTGetParameter';
    function AxmAdvVSTSetEnabele; external dll_name name 'AxmAdvVSTSetEnabele';
    function AxmAdvVSTGetEnabele; external dll_name name 'AxmAdvVSTGetEnabele';
    function AxmAdvLineMove; external dll_name name 'AxmAdvLineMove';
    function AxmAdvOvrLineMove; external dll_name name 'AxmAdvOvrLineMove';
    function AxmAdvCircleCenterMove; external dll_name name 'AxmAdvCircleCenterMove';
    function AxmAdvCirclePointMove; external dll_name name 'AxmAdvCirclePointMove';
    function AxmAdvCircleAngleMove; external dll_name name 'AxmAdvCircleAngleMove';
    function AxmAdvCircleRadiusMove; external dll_name name 'AxmAdvCircleRadiusMove';
    function AxmAdvOvrCircleRadiusMove; external dll_name name 'AxmAdvOvrCircleRadiusMove';
    function AxmAdvHelixCenterMove; external dll_name name 'AxmAdvHelixCenterMove';
    function AxmAdvHelixPointMove; external dll_name name 'AxmAdvHelixPointMove';
    function AxmAdvHelixAngleMove; external dll_name name 'AxmAdvHelixAngleMove';
    function AxmAdvHelixRadiusMove; external dll_name name 'AxmAdvHelixRadiusMove';
    function AxmAdvOvrHelixRadiusMove; external dll_name name 'AxmAdvOvrHelixRadiusMove';
    function AxmAdvScriptLineMove; external dll_name name 'AxmAdvScriptLineMove';
    function AxmAdvScriptOvrLineMove; external dll_name name 'AxmAdvScriptOvrLineMove';
    function AxmAdvScriptCircleCenterMove; external dll_name name 'AxmAdvScriptCircleCenterMove';
    function AxmAdvScriptCirclePointMove; external dll_name name 'AxmAdvScriptCirclePointMove';
    function AxmAdvScriptCircleAngleMove; external dll_name name 'AxmAdvScriptCircleAngleMove';
    function AxmAdvScriptCircleRadiusMove; external dll_name name 'AxmAdvScriptCircleRadiusMove';
    function AxmAdvScriptOvrCircleRadiusMove; external dll_name name 'AxmAdvScriptOvrCircleRadiusMove';
    function AxmAdvScriptHelixCenterMove; external dll_name name 'AxmAdvScriptHelixCenterMove';
    function AxmAdvScriptHelixPointMove; external dll_name name 'AxmAdvScriptHelixPointMove';
    function AxmAdvScriptHelixAngleMove; external dll_name name 'AxmAdvScriptHelixAngleMove';
    function AxmAdvScriptHelixRadiusMove; external dll_name name 'AxmAdvScriptHelixRadiusMove';
    function AxmAdvScriptOvrHelixRadiusMove; external dll_name name 'AxmAdvScriptOvrHelixRadiusMove';
    function AxmAdvContiGetNodeNum; external dll_name name 'AxmAdvContiGetNodeNum';
    function AxmAdvContiGetTotalNodeNum; external dll_name name 'AxmAdvContiGetTotalNodeNum';
    function AxmAdvContiReadIndex; external dll_name name 'AxmAdvContiReadIndex';
    function AxmAdvContiReadFree; external dll_name name 'AxmAdvContiReadFree';
    function AxmAdvContiWriteClear; external dll_name name 'AxmAdvContiWriteClear';
    function AxmAdvOvrContiWriteClear; external dll_name name 'AxmAdvOvrContiWriteClear';
    function AxmAdvContiStart; external dll_name name 'AxmAdvContiStart';
    function AxmAdvContiStop; external dll_name name 'AxmAdvContiStop';
    function AxmAdvContiSetAxisMap; external dll_name name 'AxmAdvContiSetAxisMap';
    function AxmAdvContiGetAxisMap; external dll_name name 'AxmAdvContiGetAxisMap';
    function AxmAdvContiSetAbsRelMode; external dll_name name 'AxmAdvContiSetAbsRelMode';
    function AxmAdvContiGetAbsRelMode; external dll_name name 'AxmAdvContiGetAbsRelMode';
    function AxmAdvContiIsMotion; external dll_name name 'AxmAdvContiIsMotion';
    function AxmAdvContiBeginNode; external dll_name name 'AxmAdvContiBeginNode';
    function AxmAdvContiEndNode; external dll_name name 'AxmAdvContiEndNode';
    function AxmMoveMultiStop; external dll_name name 'AxmMoveMultiStop';
    function AxmMoveMultiEStop; external dll_name name 'AxmMoveMultiEStop';
    function AxmMoveMultiSStop; external dll_name name 'AxmMoveMultiSStop';
    function AxmStatusReadActVel; external dll_name name 'AxmStatusReadActVel';
    function AxmStatusReadServoCmdStat; external dll_name name 'AxmStatusReadServoCmdStat';
    function AxmStatusReadServoCmdCtrl; external dll_name name 'AxmStatusReadServoCmdCtrl';
    function AxmGantryGetMstToSlvOverDist; external dll_name name 'AxmGantryGetMstToSlvOverDist';
    function AxmGantrySetMstToSlvOverDist; external dll_name name 'AxmGantrySetMstToSlvOverDist';
    function AxmSignalReadServoAlarmCode; external dll_name name 'AxmSignalReadServoAlarmCode';
    function AxmM3ServoCoordinatesSet; external dll_name name 'AxmM3ServoCoordinatesSet';
    function AxmM3ServoBreakOn; external dll_name name 'AxmM3ServoBreakOn';
    function AxmM3ServoBreakOff; external dll_name name 'AxmM3ServoBreakOff';
    function AxmM3ServoConfig; external dll_name name 'AxmM3ServoConfig';
    function AxmM3ServoSensOn; external dll_name name 'AxmM3ServoSensOn';
    function AxmM3ServoSensOff; external dll_name name 'AxmM3ServoSensOff';
    function AxmM3ServoSmon; external dll_name name 'AxmM3ServoSmon';
    function AxmM3ServoGetSmon; external dll_name name 'AxmM3ServoGetSmon';
    function AxmM3ServoSvOn; external dll_name name 'AxmM3ServoSvOn';
    function AxmM3ServoSvOff; external dll_name name 'AxmM3ServoSvOff';
    function AxmM3ServoInterpolate; external dll_name name 'AxmM3ServoInterpolate';
    function AxmM3ServoPosing; external dll_name name 'AxmM3ServoPosing';
    function AxmM3ServoFeed; external dll_name name 'AxmM3ServoFeed';
    function AxmM3ServoExFeed; external dll_name name 'AxmM3ServoExFeed';
    function AxmM3ServoExPosing; external dll_name name 'AxmM3ServoExPosing';
    function AxmM3ServoZret; external dll_name name 'AxmM3ServoZret';
    function AxmM3ServoVelctrl; external dll_name name 'AxmM3ServoVelctrl';
    function AxmM3ServoTrqctrl; external dll_name name 'AxmM3ServoTrqctrl';
    function AxmM3ServoGetParameter; external dll_name name 'AxmM3ServoGetParameter';
    function AxmM3ServoSetParameter; external dll_name name 'AxmM3ServoSetParameter';
    function AxmServoCmdExecution; external dll_name name 'AxmServoCmdExecution';
    function AxmM3ServoGetTorqLimit; external dll_name name 'AxmM3ServoGetTorqLimit';
    function AxmM3ServoSetTorqLimit; external dll_name name 'AxmM3ServoSetTorqLimit';
    function AxmM3ServoGetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoGetSendSvCmdIOOutput';
    function AxmM3ServoSetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoSetSendSvCmdIOOutput';
    function AxmM3ServoGetSvCmdCtrl; external dll_name name 'AxmM3ServoGetSvCmdCtrl';
    function AxmM3ServoSetSvCmdCtrl; external dll_name name 'AxmM3ServoSetSvCmdCtrl';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmM3ServoSetMonSel; external dll_name name 'AxmM3ServoSetMonSel';
    function AxmM3ServoGetMonSel; external dll_name name 'AxmM3ServoGetMonSel';
    function AxmM3ServoReadMonData; external dll_name name 'AxmM3ServoReadMonData';
    function AxmAdvTorqueContiSetAxisMap; external dll_name name 'AxmAdvTorqueContiSetAxisMap';
    function AxmM3ServoSetTorqProfile; external dll_name name 'AxmM3ServoSetTorqProfile';
    function AxmM3ServoGetTorqProfile; external dll_name name 'AxmM3ServoGetTorqProfile';
    function AxmSignalSetInposRange; external dll_name name 'AxmSignalSetInposRange';
    function AxmSignalGetInposRange; external dll_name name 'AxmSignalGetInposRange';
    function AxmStatusSetEncClear; external dll_name name 'AxmStatusSetEncClear';
    function AxmStatusSetMotorPosMatch; external dll_name name 'AxmStatusSetMotorPosMatch';
    function AxmMotSetWorkCoordinate; external dll_name name 'AxmMotSetWorkCoordinate';
    function AxmMotGetWorkCoordinate; external dll_name name 'AxmMotGetWorkCoordinate';
    function AxmMotSetOverridePosMode; external dll_name name 'AxmMotSetOverridePosMode';
    function AxmMotGetOverridePosMode; external dll_name name 'AxmMotGetOverridePosMode';
    function AxmMotSetOverrideLinePosMode; external dll_name name 'AxmMotSetOverrideLinePosMode';
    function AxmMotGetOverrideLinePosMode; external dll_name name 'AxmMotGetOverrideLinePosMode';
    function AxmMotSetVibrationControl; external dll_name name 'AxmMotSetVibrationControl';
    function AxmMotVibrationControlEnable; external dll_name name 'AxmMotVibrationControlEnable';
    function AxmMotVibrationControlIsEnable; external dll_name name 'AxmMotVibrationControlIsEnable';
    function AxmMotVibrationControlCoordEnable; external dll_name name 'AxmMotVibrationControlCoordEnable';
    function AxmMotVibrationControlCoordIsEnable; external dll_name name 'AxmMotVibrationControlCoordIsEnable';
    function AxmMotSetMultiTorqueLimit; external dll_name name 'AxmMotSetMultiTorqueLimit';
    function AxmMotMultiTorqueLimitEnable; external dll_name name 'AxmMotMultiTorqueLimitEnable';
    function AxmMotMultiTorqueLimitIsEnable; external dll_name name 'AxmMotMultiTorqueLimitIsEnable';
    function AxmMoveStartPosEx; external dll_name name 'AxmMoveStartPosEx';
    function AxmMovePosEx; external dll_name name 'AxmMovePosEx';
    function AxmMoveCoordStop; external dll_name name 'AxmMoveCoordStop';
    function AxmMoveCoordEStop; external dll_name name 'AxmMoveCoordEStop';
    function AxmMoveCoordSStop; external dll_name name 'AxmMoveCoordSStop';
    function AxmOverrideLinePos; external dll_name name 'AxmOverrideLinePos';
    function AxmOverrideLineVel; external dll_name name 'AxmOverrideLineVel';
    function AxmOverrideLineAccelVelDecel; external dll_name name 'AxmOverrideLineAccelVelDecel';
    function AxmOverrideAccelVelDecelAtPos; external dll_name name 'AxmOverrideAccelVelDecelAtPos';
    function AxmEGearSet; external dll_name name 'AxmEGearSet';
    function AxmEGearGet; external dll_name name 'AxmEGearGet';
    function AxmEGearReset; external dll_name name 'AxmEGearReset';
    function AxmEGearEnable; external dll_name name 'AxmEGearEnable';
    function AxmEGearIsEnable; external dll_name name 'AxmEGearIsEnable';
    function AxmHelixPitchMove; external dll_name name 'AxmHelixPitchMove';
    function AxmCompensationOneDimSet; external dll_name name 'AxmCompensationOneDimSet';
    function AxmCompensationOneDimGet; external dll_name name 'AxmCompensationOneDimGet';
    function AxmCompensationOneDimReset; external dll_name name 'AxmCompensationOneDimReset';
    function AxmCompensationOneDimEnable; external dll_name name 'AxmCompensationOneDimEnable';
    function AxmCompensationOneDimIsEnable; external dll_name name 'AxmCompensationOneDimIsEnable';
    function AxmCompensationOneDimGetCorrection; external dll_name name 'AxmCompensationOneDimGetCorrection';
    function AxmBlendingCoordSet; external dll_name name 'AxmBlendingCoordSet';
    function AxmBlendingCoordGet; external dll_name name 'AxmBlendingCoordGet';
    function AxmBlendingCoordReset; external dll_name name 'AxmBlendingCoordReset';
    function AxmBlendingCoordEnable; external dll_name name 'AxmBlendingCoordEnable';
    function AxmBlendingCoordIsEnable; external dll_name name 'AxmBlendingCoordIsEnable';
    function AxmStatusReadTorque; external dll_name name 'AxmStatusReadTorque';
    function AxmMotSetEndVel; external dll_name name 'AxmMotSetEndVel';
    function AxmMotGetEndVel; external dll_name name 'AxmMotGetEndVel';
    function AxmContiDigitalOutputBit; external dll_name name 'AxmContiDigitalOutputBit';
    function AxmLineMoveWithAxes; external dll_name name 'AxmLineMoveWithAxes';
    function AxmCircleCenterMoveWithAxes; external dll_name name 'AxmCircleCenterMoveWithAxes';
    function AxmLineMoveWithAxesWithEvent; external dll_name name 'AxmLineMoveWithAxesWithEvent';
    function AxmCircleCenterMoveWithAxesWithEvent; external dll_name name 'AxmCircleCenterMoveWithAxesWithEvent';
    function AxmInfoGetAxis; external dll_name name 'AxmInfoGetAxis';
    function AxmInfoGetAxisEx; external dll_name name 'AxmInfoGetAxisEx';
    function AxmInfoIsMotionModule; external dll_name name 'AxmInfoIsMotionModule';
    function AxmInfoIsInvalidAxisNo; external dll_name name 'AxmInfoIsInvalidAxisNo';
    function AxmInfoGetAxisStatus; external dll_name name 'AxmInfoGetAxisStatus';
    function AxmInfoGetAxisCount; external dll_name name 'AxmInfoGetAxisCount';
    function AxmInfoGetFirstAxisNo; external dll_name name 'AxmInfoGetFirstAxisNo';
    function AxmInfoGetBoardFirstAxisNo; external dll_name name 'AxmInfoGetBoardFirstAxisNo';
    function AxmVirtualSetAxisNoMap; external dll_name name 'AxmVirtualSetAxisNoMap';
    function AxmVirtualGetAxisNoMap; external dll_name name 'AxmVirtualGetAxisNoMap';
    function AxmVirtualSetMultiAxisNoMap; external dll_name name 'AxmVirtualSetMultiAxisNoMap';
    function AxmVirtualGetMultiAxisNoMap; external dll_name name 'AxmVirtualGetMultiAxisNoMap';
    function AxmVirtualResetAxisMap; external dll_name name 'AxmVirtualResetAxisMap';
    function AxmInterruptSetAxis; external dll_name name 'AxmInterruptSetAxis';
    function AxmInterruptSetAxisEnable; external dll_name name 'AxmInterruptSetAxisEnable';
    function AxmInterruptGetAxisEnable; external dll_name name 'AxmInterruptGetAxisEnable';
    function AxmInterruptRead; external dll_name name 'AxmInterruptRead';
    function AxmInterruptReadAxisFlag; external dll_name name 'AxmInterruptReadAxisFlag';
    function AxmInterruptSetUserEnable; external dll_name name 'AxmInterruptSetUserEnable';
    function AxmInterruptGetUserEnable; external dll_name name 'AxmInterruptGetUserEnable';
    function AxmMotLoadParaAll; external dll_name name 'AxmMotLoadParaAll';
    function AxmMotSaveParaAll; external dll_name name 'AxmMotSaveParaAll';
    function AxmMotSetParaLoad; external dll_name name 'AxmMotSetParaLoad';
    function AxmMotGetParaLoad; external dll_name name 'AxmMotGetParaLoad';
    function AxmMotSetPulseOutMethod; external dll_name name 'AxmMotSetPulseOutMethod';
    function AxmMotGetPulseOutMethod; external dll_name name 'AxmMotGetPulseOutMethod';
    function AxmMotSetEncInputMethod; external dll_name name 'AxmMotSetEncInputMethod';
    function AxmMotGetEncInputMethod; external dll_name name 'AxmMotGetEncInputMethod';
    function AxmMotSetMoveUnitPerPulse; external dll_name name 'AxmMotSetMoveUnitPerPulse';
    function AxmMotGetMoveUnitPerPulse; external dll_name name 'AxmMotGetMoveUnitPerPulse';
    function AxmMotSetDecelMode; external dll_name name 'AxmMotSetDecelMode';
    function AxmMotGetDecelMode; external dll_name name 'AxmMotGetDecelMode';
    function AxmMotSetRemainPulse; external dll_name name 'AxmMotSetRemainPulse';
    function AxmMotGetRemainPulse; external dll_name name 'AxmMotGetRemainPulse';
    function AxmMotSetMaxVel; external dll_name name 'AxmMotSetMaxVel';
    function AxmMotGetMaxVel; external dll_name name 'AxmMotGetMaxVel';
    function AxmMotSetAbsRelMode; external dll_name name 'AxmMotSetAbsRelMode';
    function AxmMotGetAbsRelMode; external dll_name name 'AxmMotGetAbsRelMode';
    function AxmMotSetProfileMode; external dll_name name 'AxmMotSetProfileMode';
    function AxmMotGetProfileMode; external dll_name name 'AxmMotGetProfileMode';
    function AxmMotSetAccelUnit; external dll_name name 'AxmMotSetAccelUnit';
    function AxmMotGetAccelUnit; external dll_name name 'AxmMotGetAccelUnit';
    function AxmMotSetMinVel; external dll_name name 'AxmMotSetMinVel';
    function AxmMotGetMinVel; external dll_name name 'AxmMotGetMinVel';
    function AxmMotSetAccelJerk; external dll_name name 'AxmMotSetAccelJerk';
    function AxmMotGetAccelJerk; external dll_name name 'AxmMotGetAccelJerk';
    function AxmMotSetDecelJerk; external dll_name name 'AxmMotSetDecelJerk';
    function AxmMotGetDecelJerk; external dll_name name 'AxmMotGetDecelJerk';
    function AxmMotSetProfilePriority; external dll_name name 'AxmMotSetProfilePriority';
    function AxmMotGetProfilePriority; external dll_name name 'AxmMotGetProfilePriority';
    function AxmSignalSetZphaseLevel; external dll_name name 'AxmSignalSetZphaseLevel';
    function AxmSignalGetZphaseLevel; external dll_name name 'AxmSignalGetZphaseLevel';
    function AxmSignalSetServoOnLevel; external dll_name name 'AxmSignalSetServoOnLevel';
    function AxmSignalGetServoOnLevel; external dll_name name 'AxmSignalGetServoOnLevel';
    function AxmSignalSetServoAlarmResetLevel; external dll_name name 'AxmSignalSetServoAlarmResetLevel';
    function AxmSignalGetServoAlarmResetLevel; external dll_name name 'AxmSignalGetServoAlarmResetLevel';
    function AxmSignalSetInpos; external dll_name name 'AxmSignalSetInpos';
    function AxmSignalGetInpos; external dll_name name 'AxmSignalGetInpos';
    function AxmSignalReadInpos; external dll_name name 'AxmSignalReadInpos';
    function AxmSignalSetServoAlarm; external dll_name name 'AxmSignalSetServoAlarm';
    function AxmSignalGetServoAlarm; external dll_name name 'AxmSignalGetServoAlarm';
    function AxmSignalReadServoAlarm; external dll_name name 'AxmSignalReadServoAlarm';
    function AxmSignalSetLimit; external dll_name name 'AxmSignalSetLimit';
    function AxmSignalGetLimit; external dll_name name 'AxmSignalGetLimit';
    function AxmSignalReadLimit; external dll_name name 'AxmSignalReadLimit';
    function AxmSignalSetSoftLimit; external dll_name name 'AxmSignalSetSoftLimit';
    function AxmSignalGetSoftLimit; external dll_name name 'AxmSignalGetSoftLimit';
    function AxmSignalReadSoftLimit; external dll_name name 'AxmSignalReadSoftLimit';
    function AxmSignalSetStop; external dll_name name 'AxmSignalSetStop';
    function AxmSignalGetStop; external dll_name name 'AxmSignalGetStop';
    function AxmSignalReadStop; external dll_name name 'AxmSignalReadStop';
    function AxmSignalServoOn; external dll_name name 'AxmSignalServoOn';
    function AxmSignalIsServoOn; external dll_name name 'AxmSignalIsServoOn';
    function AxmSignalServoAlarmReset; external dll_name name 'AxmSignalServoAlarmReset';
    function AxmSignalWriteOutput; external dll_name name 'AxmSignalWriteOutput';
    function AxmSignalReadOutput; external dll_name name 'AxmSignalReadOutput';
    function AxmSignalReadBrakeOn; external dll_name name 'AxmSignalReadBrakeOn';
    function AxmSignalWriteOutputBit; external dll_name name 'AxmSignalWriteOutputBit';
    function AxmSignalReadOutputBit; external dll_name name 'AxmSignalReadOutputBit';
    function AxmSignalReadInput; external dll_name name 'AxmSignalReadInput';
    function AxmSignalReadInputBit; external dll_name name 'AxmSignalReadInputBit';
    function AxmSignalSetFilterBandwidth; external dll_name name 'AxmSignalSetFilterBandwidth';
    function AxmSignalGetInputBitCount; external dll_name name 'AxmSignalGetInputBitCount';
    function AxmSignalGetOutputBitCount; external dll_name name 'AxmSignalGetOutputBitCount';
    function AxmStatusReadInMotion; external dll_name name 'AxmStatusReadInMotion';
    function AxmStatusReadDrivePulseCount; external dll_name name 'AxmStatusReadDrivePulseCount';
    function AxmStatusReadMotion; external dll_name name 'AxmStatusReadMotion';
    function AxmStatusReadStop; external dll_name name 'AxmStatusReadStop';
    function AxmStatusReadMechanical; external dll_name name 'AxmStatusReadMechanical';
    function AxmStatusReadVel; external dll_name name 'AxmStatusReadVel';
    function AxmStatusReadPosError; external dll_name name 'AxmStatusReadPosError';
    function AxmStatusReadDriveDistance; external dll_name name 'AxmStatusReadDriveDistance';
    function AxmStatusSetPosType; external dll_name name 'AxmStatusSetPosType';
    function AxmStatusGetPosType; external dll_name name 'AxmStatusGetPosType';
    function AxmStatusSetAbsOrgOffset; external dll_name name 'AxmStatusSetAbsOrgOffset';
    function AxmStatusGetAbsOrgOffset; external dll_name name 'AxmStatusGetAbsOrgOffset';
    function AxmStatusSetActPos; external dll_name name 'AxmStatusSetActPos';
    function AxmStatusGetActPos; external dll_name name 'AxmStatusGetActPos';
    function AxmStatusSetCmdPos; external dll_name name 'AxmStatusSetCmdPos';
    function AxmStatusGetCmdPos; external dll_name name 'AxmStatusGetCmdPos';
    function AxmStatusSetPosMatch; external dll_name name 'AxmStatusSetPosMatch';
    function AxmStatusReadMotionInfo; external dll_name name 'AxmStatusReadMotionInfo';
    function AxmStatusRequestServoAlarm; external dll_name name 'AxmStatusRequestServoAlarm';
    function AxmStatusReadServoAlarm; external dll_name name 'AxmStatusReadServoAlarm';
    function AxmStatusGetServoAlarmString; external dll_name name 'AxmStatusGetServoAlarmString';
    function AxmStatusRequestServoAlarmHistory; external dll_name name 'AxmStatusRequestServoAlarmHistory';
    function AxmStatusReadServoAlarmHistory; external dll_name name 'AxmStatusReadServoAlarmHistory';
    function AxmStatusClearServoAlarmHistory; external dll_name name 'AxmStatusClearServoAlarmHistory';
    function AxmHomeSetSignalLevel; external dll_name name 'AxmHomeSetSignalLevel';
    function AxmHomeGetSignalLevel; external dll_name name 'AxmHomeGetSignalLevel';
    function AxmHomeReadSignal; external dll_name name 'AxmHomeReadSignal';
    function AxmHomeSetMethod; external dll_name name 'AxmHomeSetMethod';
    function AxmHomeGetMethod; external dll_name name 'AxmHomeGetMethod';
    function AxmHomeSetFineAdjust; external dll_name name 'AxmHomeSetFineAdjust';
    function AxmHomeGetFineAdjust; external dll_name name 'AxmHomeGetFineAdjust';
    function AxmHomeSetVel; external dll_name name 'AxmHomeSetVel';
    function AxmHomeGetVel; external dll_name name 'AxmHomeGetVel';
    function AxmHomeSetStart; external dll_name name 'AxmHomeSetStart';
    function AxmHomeSetResult; external dll_name name 'AxmHomeSetResult';
    function AxmHomeGetResult; external dll_name name 'AxmHomeGetResult';
    function AxmHomeGetRate; external dll_name name 'AxmHomeGetRate';
    function AxmMoveStartPos; external dll_name name 'AxmMoveStartPos';
    function AxmMovePos; external dll_name name 'AxmMovePos';
    function AxmMoveVel; external dll_name name 'AxmMoveVel';
    function AxmMoveStartMultiVel; external dll_name name 'AxmMoveStartMultiVel';
    function AxmMoveStartMultiVelEx; external dll_name name 'AxmMoveStartMultiVelEx';
    function AxmMoveStartLineVel; external dll_name name 'AxmMoveStartLineVel';
    function AxmMoveSignalSearch; external dll_name name 'AxmMoveSignalSearch';
    function AxmMoveSignalSearchAtDis; external dll_name name 'AxmMoveSignalSearchAtDis';
    function AxmMoveSignalCapture; external dll_name name 'AxmMoveSignalCapture';
    function AxmMoveGetCapturePos; external dll_name name 'AxmMoveGetCapturePos';
    function AxmMoveStartMultiPos; external dll_name name 'AxmMoveStartMultiPos';
    function AxmMoveMultiPos; external dll_name name 'AxmMoveMultiPos';
    function AxmMoveStartTorque; external dll_name name 'AxmMoveStartTorque';
    function AxmMoveTorqueStop; external dll_name name 'AxmMoveTorqueStop';
    function AxmMoveStartPosWithList; external dll_name name 'AxmMoveStartPosWithList';
    function AxmMoveStartPosWithPosEvent; external dll_name name 'AxmMoveStartPosWithPosEvent';
    function AxmMoveStop; external dll_name name 'AxmMoveStop';
    function AxmMoveStopEx; external dll_name name 'AxmMoveStopEx';
    function AxmMoveEStop; external dll_name name 'AxmMoveEStop';
    function AxmMoveSStop; external dll_name name 'AxmMoveSStop';
    function AxmOverridePos; external dll_name name 'AxmOverridePos';
    function AxmOverrideSetMaxVel; external dll_name name 'AxmOverrideSetMaxVel';
    function AxmOverrideVel; external dll_name name 'AxmOverrideVel';
    function AxmOverrideAccelVelDecel; external dll_name name 'AxmOverrideAccelVelDecel';
    function AxmOverrideVelAtPos; external dll_name name 'AxmOverrideVelAtPos';
    function AxmOverrideVelAtMultiPos; external dll_name name 'AxmOverrideVelAtMultiPos';
    function AxmOverrideVelAtMultiPos2; external dll_name name 'AxmOverrideVelAtMultiPos2';
    function AxmLinkSetMode; external dll_name name 'AxmLinkSetMode';
    function AxmLinkGetMode; external dll_name name 'AxmLinkGetMode';
    function AxmLinkResetMode; external dll_name name 'AxmLinkResetMode';
    function AxmGantrySetEnable; external dll_name name 'AxmGantrySetEnable';
    function AxmGantryGetEnable; external dll_name name 'AxmGantryGetEnable';
    function AxmGantrySetDisable; external dll_name name 'AxmGantrySetDisable';
    function AxmGantrySetCompensationGain; external dll_name name 'AxmGantrySetCompensationGain';
    function AxmGantryGetCompensationGain; external dll_name name 'AxmGantryGetCompensationGain';
    function AxmGantrySetErrorRange; external dll_name name 'AxmGantrySetErrorRange';
    function AxmGantryGetErrorRange; external dll_name name 'AxmGantryGetErrorRange';
    function AxmGantryReadErrorRangeStatus; external dll_name name 'AxmGantryReadErrorRangeStatus';
    function AxmGantryReadErrorRangeComparePos; external dll_name name 'AxmGantryReadErrorRangeComparePos';
    function AxmLineMove; external dll_name name 'AxmLineMove';
    function AxmLineMoveEx2; external dll_name name 'AxmLineMoveEx2';
    function AxmCircleCenterMove; external dll_name name 'AxmCircleCenterMove';
    function AxmCirclePointMove; external dll_name name 'AxmCirclePointMove';
    function AxmCirclePointMoveEx; external dll_name name 'AxmCirclePointMoveEx';
    function AxmCircleRadiusMove; external dll_name name 'AxmCircleRadiusMove';
    function AxmCircleAngleMove; external dll_name name 'AxmCircleAngleMove';
    function AxmContiSetAxisMap; external dll_name name 'AxmContiSetAxisMap';
    function AxmContiGetAxisMap; external dll_name name 'AxmContiGetAxisMap';
    function AxmContiSetAbsRelMode; external dll_name name 'AxmContiSetAbsRelMode';
    function AxmContiGetAbsRelMode; external dll_name name 'AxmContiGetAbsRelMode';
    function AxmContiReadFree; external dll_name name 'AxmContiReadFree';
    function AxmContiReadIndex; external dll_name name 'AxmContiReadIndex';
    function AxmContiWriteClear; external dll_name name 'AxmContiWriteClear';
    function AxmContiBeginNode; external dll_name name 'AxmContiBeginNode';
    function AxmContiEndNode; external dll_name name 'AxmContiEndNode';
    function AxmContiStart; external dll_name name 'AxmContiStart';
    function AxmContiIsMotion; external dll_name name 'AxmContiIsMotion';
    function AxmContiGetNodeNum; external dll_name name 'AxmContiGetNodeNum';
    function AxmContiGetTotalNodeNum; external dll_name name 'AxmContiGetTotalNodeNum';
    function AxmContiDigitalOutputBit; external dll_name name 'AxmContiDigitalOutputBit';
    function AxmTriggerSetTimeLevel; external dll_name name 'AxmTriggerSetTimeLevel';
    function AxmTriggerGetTimeLevel; external dll_name name 'AxmTriggerGetTimeLevel';
    function AxmTriggerSetAbsPeriod; external dll_name name 'AxmTriggerSetAbsPeriod';
    function AxmTriggerGetAbsPeriod; external dll_name name 'AxmTriggerGetAbsPeriod';
    function AxmTriggerSetBlock; external dll_name name 'AxmTriggerSetBlock';
    function AxmTriggerGetBlock; external dll_name name 'AxmTriggerGetBlock';
    function AxmTriggerOneShot; external dll_name name 'AxmTriggerOneShot';
    function AxmTriggerSetTimerOneshot; external dll_name name 'AxmTriggerSetTimerOneshot';
    function AxmTriggerOnlyAbs; external dll_name name 'AxmTriggerOnlyAbs';
    function AxmTriggerSetReset; external dll_name name 'AxmTriggerSetReset';
    function AxmCrcSetMaskLevel; external dll_name name 'AxmCrcSetMaskLevel';
    function AxmCrcGetMaskLevel; external dll_name name 'AxmCrcGetMaskLevel';
    function AxmCrcSetOutput; external dll_name name 'AxmCrcSetOutput';
    function AxmCrcGetOutput; external dll_name name 'AxmCrcGetOutput';
    function AxmMPGSetEnable; external dll_name name 'AxmMPGSetEnable';
    function AxmMPGGetEnable; external dll_name name 'AxmMPGGetEnable';
    function AxmMPGSetRatio; external dll_name name 'AxmMPGSetRatio';
    function AxmMPGGetRatio; external dll_name name 'AxmMPGGetRatio';
    function AxmMPGReset; external dll_name name 'AxmMPGReset';
    function AxmHelixCenterMove; external dll_name name 'AxmHelixCenterMove';
    function AxmHelixPointMove; external dll_name name 'AxmHelixPointMove';
    function AxmHelixRadiusMove; external dll_name name 'AxmHelixRadiusMove';
    function AxmHelixAngleMove; external dll_name name 'AxmHelixAngleMove';
    function AxmSplineWrite; external dll_name name 'AxmSplineWrite';
    function AxmCompensationSet; external dll_name name 'AxmCompensationSet';
    function AxmCompensationGet; external dll_name name 'AxmCompensationGet';
    function AxmCompensationEnable; external dll_name name 'AxmCompensationEnable';
    function AxmCompensationIsEnable; external dll_name name 'AxmCompensationIsEnable';
    function AxmCompensationGetCorrection; external dll_name name 'AxmCompensationGetCorrection';
    function AxmCompensationSetBacklash; external dll_name name 'AxmCompensationSetBacklash';
    function AxmCompensationGetBacklash; external dll_name name 'AxmCompensationGetBacklash';
    function AxmCompensationEnableBacklash; external dll_name name 'AxmCompensationEnableBacklash';
    function AxmCompensationIsEnableBacklash; external dll_name name 'AxmCompensationIsEnableBacklash';
    function AxmCompensationSetLocating; external dll_name name 'AxmCompensationSetLocating';
    function AxmEcamSet; external dll_name name 'AxmEcamSet';
    function AxmEcamSetWithSource; external dll_name name 'AxmEcamSetWithSource';
    function AxmEcamGet; external dll_name name 'AxmEcamGet';
    function AxmEcamGetWithSource; external dll_name name 'AxmEcamGetWithSource';
    function AxmEcamEnableBySlave; external dll_name name 'AxmEcamEnableBySlave';
    function AxmEcamEnableByMaster; external dll_name name 'AxmEcamEnableByMaster';
    function AxmEcamIsSlaveEnable; external dll_name name 'AxmEcamIsSlaveEnable';
    function AxmStatusSetServoMonitor; external dll_name name 'AxmStatusSetServoMonitor';
    function AxmStatusGetServoMonitor; external dll_name name 'AxmStatusGetServoMonitor';
    function AxmStatusSetServoMonitorEnable; external dll_name name 'AxmStatusSetServoMonitorEnable';
    function AxmStatusGetServoMonitorEnable; external dll_name name 'AxmStatusGetServoMonitorEnable';
    function AxmStatusReadServoMonitorFlag; external dll_name name 'AxmStatusReadServoMonitorFlag';
    function AxmStatusReadServoMonitorValue; external dll_name name 'AxmStatusReadServoMonitorValue';
    function AxmStatusSetReadServoLoadRatio; external dll_name name 'AxmStatusSetReadServoLoadRatio';
    function AxmStatusReadServoLoadRatio; external dll_name name 'AxmStatusReadServoLoadRatio';
    function AxmMotSetScaleCoeff; external dll_name name 'AxmMotSetScaleCoeff';
    function AxmMotGetScaleCoeff; external dll_name name 'AxmMotGetScaleCoeff';
    function AxmMoveSignalSearchEx; external dll_name name 'AxmMoveSignalSearchEx';
    function AxmMoveToAbsPos; external dll_name name 'AxmMoveToAbsPos';
    function AxmStatusReadVelEx; external dll_name name 'AxmStatusReadVelEx';
    function AxmMotSetElectricGearRatio; external dll_name name 'AxmMotSetElectricGearRatio';
    function AxmMotGetElectricGearRatio; external dll_name name 'AxmMotGetElectricGearRatio';
    function AxmMotSetTorqueLimit; external dll_name name 'AxmMotSetTorqueLimit';
    function AxmMotGetTorqueLimit; external dll_name name 'AxmMotGetTorqueLimit';
    function AxmMotSetTorqueLimitAtPos; external dll_name name 'AxmMotSetTorqueLimitAtPos';
    function AxmMotGetTorqueLimitAtPos; external dll_name name 'AxmMotGetTorqueLimitAtPos';
    function AxmMotSetTorqueLimitEnable; external dll_name name 'AxmMotSetTorqueLimitEnable';
    function AxmMotGetTorqueLimitEnable; external dll_name name 'AxmMotGetTorqueLimitEnable';
    function AxmOverridePosSetFunction; external dll_name name 'AxmOverridePosSetFunction';
    function AxmOverridePosGetFunction; external dll_name name 'AxmOverridePosGetFunction';
    function AxmSignalSetWriteOutputBitAtPos; external dll_name name 'AxmSignalSetWriteOutputBitAtPos';
    function AxmSignalGetWriteOutputBitAtPos; external dll_name name 'AxmSignalGetWriteOutputBitAtPos';
    function AxmAdvVSTSetParameter; external dll_name name 'AxmAdvVSTSetParameter';
    function AxmAdvVSTGetParameter; external dll_name name 'AxmAdvVSTGetParameter';
    function AxmAdvVSTSetEnabele; external dll_name name 'AxmAdvVSTSetEnabele';
    function AxmAdvVSTGetEnabele; external dll_name name 'AxmAdvVSTGetEnabele';
    function AxmAdvLineMove; external dll_name name 'AxmAdvLineMove';
    function AxmAdvOvrLineMove; external dll_name name 'AxmAdvOvrLineMove';
    function AxmAdvCircleCenterMove; external dll_name name 'AxmAdvCircleCenterMove';
    function AxmAdvCirclePointMove; external dll_name name 'AxmAdvCirclePointMove';
    function AxmAdvCircleAngleMove; external dll_name name 'AxmAdvCircleAngleMove';
    function AxmAdvCircleRadiusMove; external dll_name name 'AxmAdvCircleRadiusMove';
    function AxmAdvOvrCircleRadiusMove; external dll_name name 'AxmAdvOvrCircleRadiusMove';
    function AxmAdvHelixCenterMove; external dll_name name 'AxmAdvHelixCenterMove';
    function AxmAdvHelixPointMove; external dll_name name 'AxmAdvHelixPointMove';
    function AxmAdvHelixAngleMove; external dll_name name 'AxmAdvHelixAngleMove';
    function AxmAdvHelixRadiusMove; external dll_name name 'AxmAdvHelixRadiusMove';
    function AxmAdvOvrHelixRadiusMove; external dll_name name 'AxmAdvOvrHelixRadiusMove';
    function AxmAdvScriptLineMove; external dll_name name 'AxmAdvScriptLineMove';
    function AxmAdvScriptOvrLineMove; external dll_name name 'AxmAdvScriptOvrLineMove';
    function AxmAdvScriptCircleCenterMove; external dll_name name 'AxmAdvScriptCircleCenterMove';
    function AxmAdvScriptCirclePointMove; external dll_name name 'AxmAdvScriptCirclePointMove';
    function AxmAdvScriptCircleAngleMove; external dll_name name 'AxmAdvScriptCircleAngleMove';
    function AxmAdvScriptCircleRadiusMove; external dll_name name 'AxmAdvScriptCircleRadiusMove';
    function AxmAdvScriptOvrCircleRadiusMove; external dll_name name 'AxmAdvScriptOvrCircleRadiusMove';
    function AxmAdvScriptHelixCenterMove; external dll_name name 'AxmAdvScriptHelixCenterMove';
    function AxmAdvScriptHelixPointMove; external dll_name name 'AxmAdvScriptHelixPointMove';
    function AxmAdvScriptHelixAngleMove; external dll_name name 'AxmAdvScriptHelixAngleMove';
    function AxmAdvScriptHelixRadiusMove; external dll_name name 'AxmAdvScriptHelixRadiusMove';
    function AxmAdvScriptOvrHelixRadiusMove; external dll_name name 'AxmAdvScriptOvrHelixRadiusMove';
    function AxmAdvContiGetNodeNum; external dll_name name 'AxmAdvContiGetNodeNum';
    function AxmAdvContiGetTotalNodeNum; external dll_name name 'AxmAdvContiGetTotalNodeNum';
    function AxmAdvContiReadIndex; external dll_name name 'AxmAdvContiReadIndex';
    function AxmAdvContiReadFree; external dll_name name 'AxmAdvContiReadFree';
    function AxmAdvContiWriteClear; external dll_name name 'AxmAdvContiWriteClear';
    function AxmAdvOvrContiWriteClear; external dll_name name 'AxmAdvOvrContiWriteClear';
    function AxmAdvContiStart; external dll_name name 'AxmAdvContiStart';
    function AxmAdvContiStop; external dll_name name 'AxmAdvContiStop';
    function AxmAdvContiSetAxisMap; external dll_name name 'AxmAdvContiSetAxisMap';
    function AxmAdvContiGetAxisMap; external dll_name name 'AxmAdvContiGetAxisMap';
    function AxmAdvContiSetAbsRelMode; external dll_name name 'AxmAdvContiSetAbsRelMode';
    function AxmAdvContiGetAbsRelMode; external dll_name name 'AxmAdvContiGetAbsRelMode';
    function AxmAdvContiIsMotion; external dll_name name 'AxmAdvContiIsMotion';
    function AxmAdvContiBeginNode; external dll_name name 'AxmAdvContiBeginNode';
    function AxmAdvContiEndNode; external dll_name name 'AxmAdvContiEndNode';
    function AxmMoveMultiStop; external dll_name name 'AxmMoveMultiStop';
    function AxmMoveMultiEStop; external dll_name name 'AxmMoveMultiEStop';
    function AxmMoveMultiSStop; external dll_name name 'AxmMoveMultiSStop';
    function AxmStatusReadActVel; external dll_name name 'AxmStatusReadActVel';
    function AxmStatusReadServoCmdStat; external dll_name name 'AxmStatusReadServoCmdStat';
    function AxmStatusReadServoCmdCtrl; external dll_name name 'AxmStatusReadServoCmdCtrl';
    function AxmGantryGetMstToSlvOverDist; external dll_name name 'AxmGantryGetMstToSlvOverDist';
    function AxmGantrySetMstToSlvOverDist; external dll_name name 'AxmGantrySetMstToSlvOverDist';
    function AxmSignalReadServoAlarmCode; external dll_name name 'AxmSignalReadServoAlarmCode';
    function AxmM3ServoCoordinatesSet; external dll_name name 'AxmM3ServoCoordinatesSet';
    function AxmM3ServoBreakOn; external dll_name name 'AxmM3ServoBreakOn';
    function AxmM3ServoBreakOff; external dll_name name 'AxmM3ServoBreakOff';
    function AxmM3ServoConfig; external dll_name name 'AxmM3ServoConfig';
    function AxmM3ServoSensOn; external dll_name name 'AxmM3ServoSensOn';
    function AxmM3ServoSensOff; external dll_name name 'AxmM3ServoSensOff';
    function AxmM3ServoSmon; external dll_name name 'AxmM3ServoSmon';
    function AxmM3ServoGetSmon; external dll_name name 'AxmM3ServoGetSmon';
    function AxmM3ServoSvOn; external dll_name name 'AxmM3ServoSvOn';
    function AxmM3ServoSvOff; external dll_name name 'AxmM3ServoSvOff';
    function AxmM3ServoInterpolate; external dll_name name 'AxmM3ServoInterpolate';
    function AxmM3ServoPosing; external dll_name name 'AxmM3ServoPosing';
    function AxmM3ServoFeed; external dll_name name 'AxmM3ServoFeed';
    function AxmM3ServoExFeed; external dll_name name 'AxmM3ServoExFeed';
    function AxmM3ServoExPosing; external dll_name name 'AxmM3ServoExPosing';
    function AxmM3ServoZret; external dll_name name 'AxmM3ServoZret';
    function AxmM3ServoVelctrl; external dll_name name 'AxmM3ServoVelctrl';
    function AxmM3ServoTrqctrl; external dll_name name 'AxmM3ServoTrqctrl';
    function AxmM3ServoGetParameter; external dll_name name 'AxmM3ServoGetParameter';
    function AxmM3ServoSetParameter; external dll_name name 'AxmM3ServoSetParameter';
    function AxmServoCmdExecution; external dll_name name 'AxmServoCmdExecution';
    function AxmM3ServoGetTorqLimit; external dll_name name 'AxmM3ServoGetTorqLimit';
    function AxmM3ServoSetTorqLimit; external dll_name name 'AxmM3ServoSetTorqLimit';
    function AxmM3ServoGetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoGetSendSvCmdIOOutput';
    function AxmM3ServoSetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoSetSendSvCmdIOOutput';
    function AxmM3ServoGetSvCmdCtrl; external dll_name name 'AxmM3ServoGetSvCmdCtrl';
    function AxmM3ServoSetSvCmdCtrl; external dll_name name 'AxmM3ServoSetSvCmdCtrl';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmM3ServoSetMonSel; external dll_name name 'AxmM3ServoSetMonSel';
    function AxmM3ServoGetMonSel; external dll_name name 'AxmM3ServoGetMonSel';
    function AxmM3ServoReadMonData; external dll_name name 'AxmM3ServoReadMonData';
    function AxmAdvTorqueContiSetAxisMap; external dll_name name 'AxmAdvTorqueContiSetAxisMap';
    function AxmM3ServoSetTorqProfile; external dll_name name 'AxmM3ServoSetTorqProfile';
    function AxmM3ServoGetTorqProfile; external dll_name name 'AxmM3ServoGetTorqProfile';
    function AxmSignalSetInposRange; external dll_name name 'AxmSignalSetInposRange';
    function AxmSignalGetInposRange; external dll_name name 'AxmSignalGetInposRange';
    function AxmStatusSetEncClear; external dll_name name 'AxmStatusSetEncClear';
    function AxmStatusSetMotorPosMatch; external dll_name name 'AxmStatusSetMotorPosMatch';
    function AxmMotSetWorkCoordinate; external dll_name name 'AxmMotSetWorkCoordinate';
    function AxmMotGetWorkCoordinate; external dll_name name 'AxmMotGetWorkCoordinate';
    function AxmMotSetOverridePosMode; external dll_name name 'AxmMotSetOverridePosMode';
    function AxmMotGetOverridePosMode; external dll_name name 'AxmMotGetOverridePosMode';
    function AxmMotSetOverrideLinePosMode; external dll_name name 'AxmMotSetOverrideLinePosMode';
    function AxmMotGetOverrideLinePosMode; external dll_name name 'AxmMotGetOverrideLinePosMode';
    function AxmMotSetVibrationControl; external dll_name name 'AxmMotSetVibrationControl';
    function AxmMotVibrationControlEnable; external dll_name name 'AxmMotVibrationControlEnable';
    function AxmMotVibrationControlIsEnable; external dll_name name 'AxmMotVibrationControlIsEnable';
    function AxmMotVibrationControlCoordEnable; external dll_name name 'AxmMotVibrationControlCoordEnable';
    function AxmMotVibrationControlCoordIsEnable; external dll_name name 'AxmMotVibrationControlCoordIsEnable';
    function AxmMotSetMultiTorqueLimit; external dll_name name 'AxmMotSetMultiTorqueLimit';
    function AxmMotMultiTorqueLimitEnable; external dll_name name 'AxmMotMultiTorqueLimitEnable';
    function AxmMotMultiTorqueLimitIsEnable; external dll_name name 'AxmMotMultiTorqueLimitIsEnable';
    function AxmMoveStartPosEx; external dll_name name 'AxmMoveStartPosEx';
    function AxmMovePosEx; external dll_name name 'AxmMovePosEx';
    function AxmMoveCoordStop; external dll_name name 'AxmMoveCoordStop';
    function AxmMoveCoordEStop; external dll_name name 'AxmMoveCoordEStop';
    function AxmMoveCoordSStop; external dll_name name 'AxmMoveCoordSStop';
    function AxmOverrideLinePos; external dll_name name 'AxmOverrideLinePos';
    function AxmOverrideLineVel; external dll_name name 'AxmOverrideLineVel';
    function AxmOverrideLineAccelVelDecel; external dll_name name 'AxmOverrideLineAccelVelDecel';
    function AxmOverrideAccelVelDecelAtPos; external dll_name name 'AxmOverrideAccelVelDecelAtPos';
    function AxmEGearSet; external dll_name name 'AxmEGearSet';
    function AxmEGearGet; external dll_name name 'AxmEGearGet';
    function AxmEGearReset; external dll_name name 'AxmEGearReset';
    function AxmEGearEnable; external dll_name name 'AxmEGearEnable';
    function AxmEGearIsEnable; external dll_name name 'AxmEGearIsEnable';
    function AxmHelixPitchMove; external dll_name name 'AxmHelixPitchMove';
    function AxmCompensationOneDimSet; external dll_name name 'AxmCompensationOneDimSet';
    function AxmCompensationOneDimGet; external dll_name name 'AxmCompensationOneDimGet';
    function AxmCompensationOneDimReset; external dll_name name 'AxmCompensationOneDimReset';
    function AxmCompensationOneDimEnable; external dll_name name 'AxmCompensationOneDimEnable';
    function AxmCompensationOneDimIsEnable; external dll_name name 'AxmCompensationOneDimIsEnable';
    function AxmCompensationOneDimGetCorrection; external dll_name name 'AxmCompensationOneDimGetCorrection';
    function AxmBlendingCoordSet; external dll_name name 'AxmBlendingCoordSet';
    function AxmBlendingCoordGet; external dll_name name 'AxmBlendingCoordGet';
    function AxmBlendingCoordReset; external dll_name name 'AxmBlendingCoordReset';
    function AxmBlendingCoordEnable; external dll_name name 'AxmBlendingCoordEnable';
    function AxmBlendingCoordIsEnable; external dll_name name 'AxmBlendingCoordIsEnable';
    function AxmStatusReadTorque; external dll_name name 'AxmStatusReadTorque';
    function AxmMotSetEndVel; external dll_name name 'AxmMotSetEndVel';
    function AxmMotGetEndVel; external dll_name name 'AxmMotGetEndVel';
    function AxmContiDigitalOutputBit; external dll_name name 'AxmContiDigitalOutputBit';
    function AxmLineMoveWithAxes; external dll_name name 'AxmLineMoveWithAxes';
    function AxmCircleCenterMoveWithAxes; external dll_name name 'AxmCircleCenterMoveWithAxes';
    function AxmLineMoveWithAxesWithEvent; external dll_name name 'AxmLineMoveWithAxesWithEvent';
    function AxmCircleCenterMoveWithAxesWithEvent; external dll_name name 'AxmCircleCenterMoveWithAxesWithEvent';
    function AxmInfoGetAxis; external dll_name name 'AxmInfoGetAxis';
    function AxmInfoGetAxisEx; external dll_name name 'AxmInfoGetAxisEx';
    function AxmInfoIsMotionModule; external dll_name name 'AxmInfoIsMotionModule';
    function AxmInfoIsInvalidAxisNo; external dll_name name 'AxmInfoIsInvalidAxisNo';
    function AxmInfoGetAxisStatus; external dll_name name 'AxmInfoGetAxisStatus';
    function AxmInfoGetAxisCount; external dll_name name 'AxmInfoGetAxisCount';
    function AxmInfoGetFirstAxisNo; external dll_name name 'AxmInfoGetFirstAxisNo';
    function AxmInfoGetBoardFirstAxisNo; external dll_name name 'AxmInfoGetBoardFirstAxisNo';
    function AxmVirtualSetAxisNoMap; external dll_name name 'AxmVirtualSetAxisNoMap';
    function AxmVirtualGetAxisNoMap; external dll_name name 'AxmVirtualGetAxisNoMap';
    function AxmVirtualSetMultiAxisNoMap; external dll_name name 'AxmVirtualSetMultiAxisNoMap';
    function AxmVirtualGetMultiAxisNoMap; external dll_name name 'AxmVirtualGetMultiAxisNoMap';
    function AxmVirtualResetAxisMap; external dll_name name 'AxmVirtualResetAxisMap';
    function AxmInterruptSetAxis; external dll_name name 'AxmInterruptSetAxis';
    function AxmInterruptSetAxisEnable; external dll_name name 'AxmInterruptSetAxisEnable';
    function AxmInterruptGetAxisEnable; external dll_name name 'AxmInterruptGetAxisEnable';
    function AxmInterruptRead; external dll_name name 'AxmInterruptRead';
    function AxmInterruptReadAxisFlag; external dll_name name 'AxmInterruptReadAxisFlag';
    function AxmInterruptSetUserEnable; external dll_name name 'AxmInterruptSetUserEnable';
    function AxmInterruptGetUserEnable; external dll_name name 'AxmInterruptGetUserEnable';
    function AxmMotLoadParaAll; external dll_name name 'AxmMotLoadParaAll';
    function AxmMotSaveParaAll; external dll_name name 'AxmMotSaveParaAll';
    function AxmMotSetParaLoad; external dll_name name 'AxmMotSetParaLoad';
    function AxmMotGetParaLoad; external dll_name name 'AxmMotGetParaLoad';
    function AxmMotSetPulseOutMethod; external dll_name name 'AxmMotSetPulseOutMethod';
    function AxmMotGetPulseOutMethod; external dll_name name 'AxmMotGetPulseOutMethod';
    function AxmMotSetEncInputMethod; external dll_name name 'AxmMotSetEncInputMethod';
    function AxmMotGetEncInputMethod; external dll_name name 'AxmMotGetEncInputMethod';
    function AxmMotSetMoveUnitPerPulse; external dll_name name 'AxmMotSetMoveUnitPerPulse';
    function AxmMotGetMoveUnitPerPulse; external dll_name name 'AxmMotGetMoveUnitPerPulse';
    function AxmMotSetDecelMode; external dll_name name 'AxmMotSetDecelMode';
    function AxmMotGetDecelMode; external dll_name name 'AxmMotGetDecelMode';
    function AxmMotSetRemainPulse; external dll_name name 'AxmMotSetRemainPulse';
    function AxmMotGetRemainPulse; external dll_name name 'AxmMotGetRemainPulse';
    function AxmMotSetMaxVel; external dll_name name 'AxmMotSetMaxVel';
    function AxmMotGetMaxVel; external dll_name name 'AxmMotGetMaxVel';
    function AxmMotSetAbsRelMode; external dll_name name 'AxmMotSetAbsRelMode';
    function AxmMotGetAbsRelMode; external dll_name name 'AxmMotGetAbsRelMode';
    function AxmMotSetProfileMode; external dll_name name 'AxmMotSetProfileMode';
    function AxmMotGetProfileMode; external dll_name name 'AxmMotGetProfileMode';
    function AxmMotSetAccelUnit; external dll_name name 'AxmMotSetAccelUnit';
    function AxmMotGetAccelUnit; external dll_name name 'AxmMotGetAccelUnit';
    function AxmMotSetMinVel; external dll_name name 'AxmMotSetMinVel';
    function AxmMotGetMinVel; external dll_name name 'AxmMotGetMinVel';
    function AxmMotSetAccelJerk; external dll_name name 'AxmMotSetAccelJerk';
    function AxmMotGetAccelJerk; external dll_name name 'AxmMotGetAccelJerk';
    function AxmMotSetDecelJerk; external dll_name name 'AxmMotSetDecelJerk';
    function AxmMotGetDecelJerk; external dll_name name 'AxmMotGetDecelJerk';
    function AxmMotSetProfilePriority; external dll_name name 'AxmMotSetProfilePriority';
    function AxmMotGetProfilePriority; external dll_name name 'AxmMotGetProfilePriority';
    function AxmSignalSetZphaseLevel; external dll_name name 'AxmSignalSetZphaseLevel';
    function AxmSignalGetZphaseLevel; external dll_name name 'AxmSignalGetZphaseLevel';
    function AxmSignalSetServoOnLevel; external dll_name name 'AxmSignalSetServoOnLevel';
    function AxmSignalGetServoOnLevel; external dll_name name 'AxmSignalGetServoOnLevel';
    function AxmSignalSetServoAlarmResetLevel; external dll_name name 'AxmSignalSetServoAlarmResetLevel';
    function AxmSignalGetServoAlarmResetLevel; external dll_name name 'AxmSignalGetServoAlarmResetLevel';
    function AxmSignalSetInpos; external dll_name name 'AxmSignalSetInpos';
    function AxmSignalGetInpos; external dll_name name 'AxmSignalGetInpos';
    function AxmSignalReadInpos; external dll_name name 'AxmSignalReadInpos';
    function AxmSignalSetServoAlarm; external dll_name name 'AxmSignalSetServoAlarm';
    function AxmSignalGetServoAlarm; external dll_name name 'AxmSignalGetServoAlarm';
    function AxmSignalReadServoAlarm; external dll_name name 'AxmSignalReadServoAlarm';
    function AxmSignalSetLimit; external dll_name name 'AxmSignalSetLimit';
    function AxmSignalGetLimit; external dll_name name 'AxmSignalGetLimit';
    function AxmSignalReadLimit; external dll_name name 'AxmSignalReadLimit';
    function AxmSignalSetSoftLimit; external dll_name name 'AxmSignalSetSoftLimit';
    function AxmSignalGetSoftLimit; external dll_name name 'AxmSignalGetSoftLimit';
    function AxmSignalReadSoftLimit; external dll_name name 'AxmSignalReadSoftLimit';
    function AxmSignalSetStop; external dll_name name 'AxmSignalSetStop';
    function AxmSignalGetStop; external dll_name name 'AxmSignalGetStop';
    function AxmSignalReadStop; external dll_name name 'AxmSignalReadStop';
    function AxmSignalServoOn; external dll_name name 'AxmSignalServoOn';
    function AxmSignalIsServoOn; external dll_name name 'AxmSignalIsServoOn';
    function AxmSignalServoAlarmReset; external dll_name name 'AxmSignalServoAlarmReset';
    function AxmSignalWriteOutput; external dll_name name 'AxmSignalWriteOutput';
    function AxmSignalReadOutput; external dll_name name 'AxmSignalReadOutput';
    function AxmSignalReadBrakeOn; external dll_name name 'AxmSignalReadBrakeOn';
    function AxmSignalWriteOutputBit; external dll_name name 'AxmSignalWriteOutputBit';
    function AxmSignalReadOutputBit; external dll_name name 'AxmSignalReadOutputBit';
    function AxmSignalReadInput; external dll_name name 'AxmSignalReadInput';
    function AxmSignalReadInputBit; external dll_name name 'AxmSignalReadInputBit';
    function AxmSignalSetFilterBandwidth; external dll_name name 'AxmSignalSetFilterBandwidth';
    function AxmSignalGetInputBitCount; external dll_name name 'AxmSignalGetInputBitCount';
    function AxmSignalGetOutputBitCount; external dll_name name 'AxmSignalGetOutputBitCount';
    function AxmStatusReadInMotion; external dll_name name 'AxmStatusReadInMotion';
    function AxmStatusReadDrivePulseCount; external dll_name name 'AxmStatusReadDrivePulseCount';
    function AxmStatusReadMotion; external dll_name name 'AxmStatusReadMotion';
    function AxmStatusReadStop; external dll_name name 'AxmStatusReadStop';
    function AxmStatusReadMechanical; external dll_name name 'AxmStatusReadMechanical';
    function AxmStatusReadVel; external dll_name name 'AxmStatusReadVel';
    function AxmStatusReadPosError; external dll_name name 'AxmStatusReadPosError';
    function AxmStatusReadDriveDistance; external dll_name name 'AxmStatusReadDriveDistance';
    function AxmStatusSetPosType; external dll_name name 'AxmStatusSetPosType';
    function AxmStatusGetPosType; external dll_name name 'AxmStatusGetPosType';
    function AxmStatusSetAbsOrgOffset; external dll_name name 'AxmStatusSetAbsOrgOffset';
    function AxmStatusGetAbsOrgOffset; external dll_name name 'AxmStatusGetAbsOrgOffset';
    function AxmStatusSetActPos; external dll_name name 'AxmStatusSetActPos';
    function AxmStatusGetActPos; external dll_name name 'AxmStatusGetActPos';
    function AxmStatusSetCmdPos; external dll_name name 'AxmStatusSetCmdPos';
    function AxmStatusGetCmdPos; external dll_name name 'AxmStatusGetCmdPos';
    function AxmStatusSetPosMatch; external dll_name name 'AxmStatusSetPosMatch';
    function AxmStatusReadMotionInfo; external dll_name name 'AxmStatusReadMotionInfo';
    function AxmStatusRequestServoAlarm; external dll_name name 'AxmStatusRequestServoAlarm';
    function AxmStatusReadServoAlarm; external dll_name name 'AxmStatusReadServoAlarm';
    function AxmStatusGetServoAlarmString; external dll_name name 'AxmStatusGetServoAlarmString';
    function AxmStatusRequestServoAlarmHistory; external dll_name name 'AxmStatusRequestServoAlarmHistory';
    function AxmStatusReadServoAlarmHistory; external dll_name name 'AxmStatusReadServoAlarmHistory';
    function AxmStatusClearServoAlarmHistory; external dll_name name 'AxmStatusClearServoAlarmHistory';
    function AxmHomeSetSignalLevel; external dll_name name 'AxmHomeSetSignalLevel';
    function AxmHomeGetSignalLevel; external dll_name name 'AxmHomeGetSignalLevel';
    function AxmHomeReadSignal; external dll_name name 'AxmHomeReadSignal';
    function AxmHomeSetMethod; external dll_name name 'AxmHomeSetMethod';
    function AxmHomeGetMethod; external dll_name name 'AxmHomeGetMethod';
    function AxmHomeSetFineAdjust; external dll_name name 'AxmHomeSetFineAdjust';
    function AxmHomeGetFineAdjust; external dll_name name 'AxmHomeGetFineAdjust';
    function AxmHomeSetVel; external dll_name name 'AxmHomeSetVel';
    function AxmHomeGetVel; external dll_name name 'AxmHomeGetVel';
    function AxmHomeSetStart; external dll_name name 'AxmHomeSetStart';
    function AxmHomeSetResult; external dll_name name 'AxmHomeSetResult';
    function AxmHomeGetResult; external dll_name name 'AxmHomeGetResult';
    function AxmHomeGetRate; external dll_name name 'AxmHomeGetRate';
    function AxmMoveStartPos; external dll_name name 'AxmMoveStartPos';
    function AxmMovePos; external dll_name name 'AxmMovePos';
    function AxmMoveVel; external dll_name name 'AxmMoveVel';
    function AxmMoveStartMultiVel; external dll_name name 'AxmMoveStartMultiVel';
    function AxmMoveStartMultiVelEx; external dll_name name 'AxmMoveStartMultiVelEx';
    function AxmMoveStartLineVel; external dll_name name 'AxmMoveStartLineVel';
    function AxmMoveSignalSearch; external dll_name name 'AxmMoveSignalSearch';
    function AxmMoveSignalSearchAtDis; external dll_name name 'AxmMoveSignalSearchAtDis';
    function AxmMoveSignalCapture; external dll_name name 'AxmMoveSignalCapture';
    function AxmMoveGetCapturePos; external dll_name name 'AxmMoveGetCapturePos';
    function AxmMoveStartMultiPos; external dll_name name 'AxmMoveStartMultiPos';
    function AxmMoveMultiPos; external dll_name name 'AxmMoveMultiPos';
    function AxmMoveStartTorque; external dll_name name 'AxmMoveStartTorque';
    function AxmMoveTorqueStop; external dll_name name 'AxmMoveTorqueStop';
    function AxmMoveStartPosWithList; external dll_name name 'AxmMoveStartPosWithList';
    function AxmMoveStartPosWithPosEvent; external dll_name name 'AxmMoveStartPosWithPosEvent';
    function AxmMoveStop; external dll_name name 'AxmMoveStop';
    function AxmMoveStopEx; external dll_name name 'AxmMoveStopEx';
    function AxmMoveEStop; external dll_name name 'AxmMoveEStop';
    function AxmMoveSStop; external dll_name name 'AxmMoveSStop';
    function AxmOverridePos; external dll_name name 'AxmOverridePos';
    function AxmOverrideSetMaxVel; external dll_name name 'AxmOverrideSetMaxVel';
    function AxmOverrideVel; external dll_name name 'AxmOverrideVel';
    function AxmOverrideAccelVelDecel; external dll_name name 'AxmOverrideAccelVelDecel';
    function AxmOverrideVelAtPos; external dll_name name 'AxmOverrideVelAtPos';
    function AxmOverrideVelAtMultiPos; external dll_name name 'AxmOverrideVelAtMultiPos';
    function AxmOverrideVelAtMultiPos2; external dll_name name 'AxmOverrideVelAtMultiPos2';
    function AxmLinkSetMode; external dll_name name 'AxmLinkSetMode';
    function AxmLinkGetMode; external dll_name name 'AxmLinkGetMode';
    function AxmLinkResetMode; external dll_name name 'AxmLinkResetMode';
    function AxmGantrySetEnable; external dll_name name 'AxmGantrySetEnable';
    function AxmGantryGetEnable; external dll_name name 'AxmGantryGetEnable';
    function AxmGantrySetDisable; external dll_name name 'AxmGantrySetDisable';
    function AxmGantrySetCompensationGain; external dll_name name 'AxmGantrySetCompensationGain';
    function AxmGantryGetCompensationGain; external dll_name name 'AxmGantryGetCompensationGain';
    function AxmGantrySetErrorRange; external dll_name name 'AxmGantrySetErrorRange';
    function AxmGantryGetErrorRange; external dll_name name 'AxmGantryGetErrorRange';
    function AxmGantryReadErrorRangeStatus; external dll_name name 'AxmGantryReadErrorRangeStatus';
    function AxmGantryReadErrorRangeComparePos; external dll_name name 'AxmGantryReadErrorRangeComparePos';
    function AxmLineMove; external dll_name name 'AxmLineMove';
    function AxmLineMoveEx2; external dll_name name 'AxmLineMoveEx2';
    function AxmCircleCenterMove; external dll_name name 'AxmCircleCenterMove';
    function AxmCirclePointMove; external dll_name name 'AxmCirclePointMove';
    function AxmCirclePointMoveEx; external dll_name name 'AxmCirclePointMoveEx';
    function AxmCircleRadiusMove; external dll_name name 'AxmCircleRadiusMove';
    function AxmCircleAngleMove; external dll_name name 'AxmCircleAngleMove';
    function AxmContiSetAxisMap; external dll_name name 'AxmContiSetAxisMap';
    function AxmContiGetAxisMap; external dll_name name 'AxmContiGetAxisMap';
    function AxmContiSetAbsRelMode; external dll_name name 'AxmContiSetAbsRelMode';
    function AxmContiGetAbsRelMode; external dll_name name 'AxmContiGetAbsRelMode';
    function AxmContiReadFree; external dll_name name 'AxmContiReadFree';
    function AxmContiReadIndex; external dll_name name 'AxmContiReadIndex';
    function AxmContiWriteClear; external dll_name name 'AxmContiWriteClear';
    function AxmContiBeginNode; external dll_name name 'AxmContiBeginNode';
    function AxmContiEndNode; external dll_name name 'AxmContiEndNode';
    function AxmContiStart; external dll_name name 'AxmContiStart';
    function AxmContiIsMotion; external dll_name name 'AxmContiIsMotion';
    function AxmContiGetNodeNum; external dll_name name 'AxmContiGetNodeNum';
    function AxmContiGetTotalNodeNum; external dll_name name 'AxmContiGetTotalNodeNum';
    function AxmContiDigitalOutputBit; external dll_name name 'AxmContiDigitalOutputBit';
    function AxmTriggerSetTimeLevel; external dll_name name 'AxmTriggerSetTimeLevel';
    function AxmTriggerGetTimeLevel; external dll_name name 'AxmTriggerGetTimeLevel';
    function AxmTriggerSetAbsPeriod; external dll_name name 'AxmTriggerSetAbsPeriod';
    function AxmTriggerGetAbsPeriod; external dll_name name 'AxmTriggerGetAbsPeriod';
    function AxmTriggerSetBlock; external dll_name name 'AxmTriggerSetBlock';
    function AxmTriggerGetBlock; external dll_name name 'AxmTriggerGetBlock';
    function AxmTriggerOneShot; external dll_name name 'AxmTriggerOneShot';
    function AxmTriggerSetTimerOneshot; external dll_name name 'AxmTriggerSetTimerOneshot';
    function AxmTriggerOnlyAbs; external dll_name name 'AxmTriggerOnlyAbs';
    function AxmTriggerSetReset; external dll_name name 'AxmTriggerSetReset';
    function AxmCrcSetMaskLevel; external dll_name name 'AxmCrcSetMaskLevel';
    function AxmCrcGetMaskLevel; external dll_name name 'AxmCrcGetMaskLevel';
    function AxmCrcSetOutput; external dll_name name 'AxmCrcSetOutput';
    function AxmCrcGetOutput; external dll_name name 'AxmCrcGetOutput';
    function AxmMPGSetEnable; external dll_name name 'AxmMPGSetEnable';
    function AxmMPGGetEnable; external dll_name name 'AxmMPGGetEnable';
    function AxmMPGSetRatio; external dll_name name 'AxmMPGSetRatio';
    function AxmMPGGetRatio; external dll_name name 'AxmMPGGetRatio';
    function AxmMPGReset; external dll_name name 'AxmMPGReset';
    function AxmHelixCenterMove; external dll_name name 'AxmHelixCenterMove';
    function AxmHelixPointMove; external dll_name name 'AxmHelixPointMove';
    function AxmHelixRadiusMove; external dll_name name 'AxmHelixRadiusMove';
    function AxmHelixAngleMove; external dll_name name 'AxmHelixAngleMove';
    function AxmSplineWrite; external dll_name name 'AxmSplineWrite';
    function AxmCompensationSet; external dll_name name 'AxmCompensationSet';
    function AxmCompensationGet; external dll_name name 'AxmCompensationGet';
    function AxmCompensationEnable; external dll_name name 'AxmCompensationEnable';
    function AxmCompensationIsEnable; external dll_name name 'AxmCompensationIsEnable';
    function AxmCompensationGetCorrection; external dll_name name 'AxmCompensationGetCorrection';
    function AxmCompensationSetBacklash; external dll_name name 'AxmCompensationSetBacklash';
    function AxmCompensationGetBacklash; external dll_name name 'AxmCompensationGetBacklash';
    function AxmCompensationEnableBacklash; external dll_name name 'AxmCompensationEnableBacklash';
    function AxmCompensationIsEnableBacklash; external dll_name name 'AxmCompensationIsEnableBacklash';
    function AxmCompensationSetLocating; external dll_name name 'AxmCompensationSetLocating';
    function AxmEcamSet; external dll_name name 'AxmEcamSet';
    function AxmEcamSetWithSource; external dll_name name 'AxmEcamSetWithSource';
    function AxmEcamGet; external dll_name name 'AxmEcamGet';
    function AxmEcamGetWithSource; external dll_name name 'AxmEcamGetWithSource';
    function AxmEcamEnableBySlave; external dll_name name 'AxmEcamEnableBySlave';
    function AxmEcamEnableByMaster; external dll_name name 'AxmEcamEnableByMaster';
    function AxmEcamIsSlaveEnable; external dll_name name 'AxmEcamIsSlaveEnable';
    function AxmStatusSetServoMonitor; external dll_name name 'AxmStatusSetServoMonitor';
    function AxmStatusGetServoMonitor; external dll_name name 'AxmStatusGetServoMonitor';
    function AxmStatusSetServoMonitorEnable; external dll_name name 'AxmStatusSetServoMonitorEnable';
    function AxmStatusGetServoMonitorEnable; external dll_name name 'AxmStatusGetServoMonitorEnable';
    function AxmStatusReadServoMonitorFlag; external dll_name name 'AxmStatusReadServoMonitorFlag';
    function AxmStatusReadServoMonitorValue; external dll_name name 'AxmStatusReadServoMonitorValue';
    function AxmStatusSetReadServoLoadRatio; external dll_name name 'AxmStatusSetReadServoLoadRatio';
    function AxmStatusReadServoLoadRatio; external dll_name name 'AxmStatusReadServoLoadRatio';
    function AxmMotSetScaleCoeff; external dll_name name 'AxmMotSetScaleCoeff';
    function AxmMotGetScaleCoeff; external dll_name name 'AxmMotGetScaleCoeff';
    function AxmMoveSignalSearchEx; external dll_name name 'AxmMoveSignalSearchEx';
    function AxmMoveToAbsPos; external dll_name name 'AxmMoveToAbsPos';
    function AxmStatusReadVelEx; external dll_name name 'AxmStatusReadVelEx';
    function AxmMotSetElectricGearRatio; external dll_name name 'AxmMotSetElectricGearRatio';
    function AxmMotGetElectricGearRatio; external dll_name name 'AxmMotGetElectricGearRatio';
    function AxmMotSetTorqueLimit; external dll_name name 'AxmMotSetTorqueLimit';
    function AxmMotGetTorqueLimit; external dll_name name 'AxmMotGetTorqueLimit';
    function AxmMotSetTorqueLimitAtPos; external dll_name name 'AxmMotSetTorqueLimitAtPos';
    function AxmMotGetTorqueLimitAtPos; external dll_name name 'AxmMotGetTorqueLimitAtPos';
    function AxmMotSetTorqueLimitEnable; external dll_name name 'AxmMotSetTorqueLimitEnable';
    function AxmMotGetTorqueLimitEnable; external dll_name name 'AxmMotGetTorqueLimitEnable';
    function AxmOverridePosSetFunction; external dll_name name 'AxmOverridePosSetFunction';
    function AxmOverridePosGetFunction; external dll_name name 'AxmOverridePosGetFunction';
    function AxmSignalSetWriteOutputBitAtPos; external dll_name name 'AxmSignalSetWriteOutputBitAtPos';
    function AxmSignalGetWriteOutputBitAtPos; external dll_name name 'AxmSignalGetWriteOutputBitAtPos';
    function AxmAdvVSTSetParameter; external dll_name name 'AxmAdvVSTSetParameter';
    function AxmAdvVSTGetParameter; external dll_name name 'AxmAdvVSTGetParameter';
    function AxmAdvVSTSetEnabele; external dll_name name 'AxmAdvVSTSetEnabele';
    function AxmAdvVSTGetEnabele; external dll_name name 'AxmAdvVSTGetEnabele';
    function AxmAdvLineMove; external dll_name name 'AxmAdvLineMove';
    function AxmAdvOvrLineMove; external dll_name name 'AxmAdvOvrLineMove';
    function AxmAdvCircleCenterMove; external dll_name name 'AxmAdvCircleCenterMove';
    function AxmAdvCirclePointMove; external dll_name name 'AxmAdvCirclePointMove';
    function AxmAdvCircleAngleMove; external dll_name name 'AxmAdvCircleAngleMove';
    function AxmAdvCircleRadiusMove; external dll_name name 'AxmAdvCircleRadiusMove';
    function AxmAdvOvrCircleRadiusMove; external dll_name name 'AxmAdvOvrCircleRadiusMove';
    function AxmAdvHelixCenterMove; external dll_name name 'AxmAdvHelixCenterMove';
    function AxmAdvHelixPointMove; external dll_name name 'AxmAdvHelixPointMove';
    function AxmAdvHelixAngleMove; external dll_name name 'AxmAdvHelixAngleMove';
    function AxmAdvHelixRadiusMove; external dll_name name 'AxmAdvHelixRadiusMove';
    function AxmAdvOvrHelixRadiusMove; external dll_name name 'AxmAdvOvrHelixRadiusMove';
    function AxmAdvScriptLineMove; external dll_name name 'AxmAdvScriptLineMove';
    function AxmAdvScriptOvrLineMove; external dll_name name 'AxmAdvScriptOvrLineMove';
    function AxmAdvScriptCircleCenterMove; external dll_name name 'AxmAdvScriptCircleCenterMove';
    function AxmAdvScriptCirclePointMove; external dll_name name 'AxmAdvScriptCirclePointMove';
    function AxmAdvScriptCircleAngleMove; external dll_name name 'AxmAdvScriptCircleAngleMove';
    function AxmAdvScriptCircleRadiusMove; external dll_name name 'AxmAdvScriptCircleRadiusMove';
    function AxmAdvScriptOvrCircleRadiusMove; external dll_name name 'AxmAdvScriptOvrCircleRadiusMove';
    function AxmAdvScriptHelixCenterMove; external dll_name name 'AxmAdvScriptHelixCenterMove';
    function AxmAdvScriptHelixPointMove; external dll_name name 'AxmAdvScriptHelixPointMove';
    function AxmAdvScriptHelixAngleMove; external dll_name name 'AxmAdvScriptHelixAngleMove';
    function AxmAdvScriptHelixRadiusMove; external dll_name name 'AxmAdvScriptHelixRadiusMove';
    function AxmAdvScriptOvrHelixRadiusMove; external dll_name name 'AxmAdvScriptOvrHelixRadiusMove';
    function AxmAdvContiGetNodeNum; external dll_name name 'AxmAdvContiGetNodeNum';
    function AxmAdvContiGetTotalNodeNum; external dll_name name 'AxmAdvContiGetTotalNodeNum';
    function AxmAdvContiReadIndex; external dll_name name 'AxmAdvContiReadIndex';
    function AxmAdvContiReadFree; external dll_name name 'AxmAdvContiReadFree';
    function AxmAdvContiWriteClear; external dll_name name 'AxmAdvContiWriteClear';
    function AxmAdvOvrContiWriteClear; external dll_name name 'AxmAdvOvrContiWriteClear';
    function AxmAdvContiStart; external dll_name name 'AxmAdvContiStart';
    function AxmAdvContiStop; external dll_name name 'AxmAdvContiStop';
    function AxmAdvContiSetAxisMap; external dll_name name 'AxmAdvContiSetAxisMap';
    function AxmAdvContiGetAxisMap; external dll_name name 'AxmAdvContiGetAxisMap';
    function AxmAdvContiSetAbsRelMode; external dll_name name 'AxmAdvContiSetAbsRelMode';
    function AxmAdvContiGetAbsRelMode; external dll_name name 'AxmAdvContiGetAbsRelMode';
    function AxmAdvContiIsMotion; external dll_name name 'AxmAdvContiIsMotion';
    function AxmAdvContiBeginNode; external dll_name name 'AxmAdvContiBeginNode';
    function AxmAdvContiEndNode; external dll_name name 'AxmAdvContiEndNode';
    function AxmMoveMultiStop; external dll_name name 'AxmMoveMultiStop';
    function AxmMoveMultiEStop; external dll_name name 'AxmMoveMultiEStop';
    function AxmMoveMultiSStop; external dll_name name 'AxmMoveMultiSStop';
    function AxmStatusReadActVel; external dll_name name 'AxmStatusReadActVel';
    function AxmStatusReadServoCmdStat; external dll_name name 'AxmStatusReadServoCmdStat';
    function AxmStatusReadServoCmdCtrl; external dll_name name 'AxmStatusReadServoCmdCtrl';
    function AxmGantryGetMstToSlvOverDist; external dll_name name 'AxmGantryGetMstToSlvOverDist';
    function AxmGantrySetMstToSlvOverDist; external dll_name name 'AxmGantrySetMstToSlvOverDist';
    function AxmSignalReadServoAlarmCode; external dll_name name 'AxmSignalReadServoAlarmCode';
    function AxmM3ServoCoordinatesSet; external dll_name name 'AxmM3ServoCoordinatesSet';
    function AxmM3ServoBreakOn; external dll_name name 'AxmM3ServoBreakOn';
    function AxmM3ServoBreakOff; external dll_name name 'AxmM3ServoBreakOff';
    function AxmM3ServoConfig; external dll_name name 'AxmM3ServoConfig';
    function AxmM3ServoSensOn; external dll_name name 'AxmM3ServoSensOn';
    function AxmM3ServoSensOff; external dll_name name 'AxmM3ServoSensOff';
    function AxmM3ServoSmon; external dll_name name 'AxmM3ServoSmon';
    function AxmM3ServoGetSmon; external dll_name name 'AxmM3ServoGetSmon';
    function AxmM3ServoSvOn; external dll_name name 'AxmM3ServoSvOn';
    function AxmM3ServoSvOff; external dll_name name 'AxmM3ServoSvOff';
    function AxmM3ServoInterpolate; external dll_name name 'AxmM3ServoInterpolate';
    function AxmM3ServoPosing; external dll_name name 'AxmM3ServoPosing';
    function AxmM3ServoFeed; external dll_name name 'AxmM3ServoFeed';
    function AxmM3ServoExFeed; external dll_name name 'AxmM3ServoExFeed';
    function AxmM3ServoExPosing; external dll_name name 'AxmM3ServoExPosing';
    function AxmM3ServoZret; external dll_name name 'AxmM3ServoZret';
    function AxmM3ServoVelctrl; external dll_name name 'AxmM3ServoVelctrl';
    function AxmM3ServoTrqctrl; external dll_name name 'AxmM3ServoTrqctrl';
    function AxmM3ServoGetParameter; external dll_name name 'AxmM3ServoGetParameter';
    function AxmM3ServoSetParameter; external dll_name name 'AxmM3ServoSetParameter';
    function AxmServoCmdExecution; external dll_name name 'AxmServoCmdExecution';
    function AxmM3ServoGetTorqLimit; external dll_name name 'AxmM3ServoGetTorqLimit';
    function AxmM3ServoSetTorqLimit; external dll_name name 'AxmM3ServoSetTorqLimit';
    function AxmM3ServoGetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoGetSendSvCmdIOOutput';
    function AxmM3ServoSetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoSetSendSvCmdIOOutput';
    function AxmM3ServoGetSvCmdCtrl; external dll_name name 'AxmM3ServoGetSvCmdCtrl';
    function AxmM3ServoSetSvCmdCtrl; external dll_name name 'AxmM3ServoSetSvCmdCtrl';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmM3ServoSetMonSel; external dll_name name 'AxmM3ServoSetMonSel';
    function AxmM3ServoGetMonSel; external dll_name name 'AxmM3ServoGetMonSel';
    function AxmM3ServoReadMonData; external dll_name name 'AxmM3ServoReadMonData';
    function AxmAdvTorqueContiSetAxisMap; external dll_name name 'AxmAdvTorqueContiSetAxisMap';
    function AxmM3ServoSetTorqProfile; external dll_name name 'AxmM3ServoSetTorqProfile';
    function AxmM3ServoGetTorqProfile; external dll_name name 'AxmM3ServoGetTorqProfile';
    function AxmSignalSetInposRange; external dll_name name 'AxmSignalSetInposRange';
    function AxmSignalGetInposRange; external dll_name name 'AxmSignalGetInposRange';
    function AxmStatusSetEncClear; external dll_name name 'AxmStatusSetEncClear';
    function AxmStatusSetMotorPosMatch; external dll_name name 'AxmStatusSetMotorPosMatch';
    function AxmMotSetWorkCoordinate; external dll_name name 'AxmMotSetWorkCoordinate';
    function AxmMotGetWorkCoordinate; external dll_name name 'AxmMotGetWorkCoordinate';
    function AxmMotSetOverridePosMode; external dll_name name 'AxmMotSetOverridePosMode';
    function AxmMotGetOverridePosMode; external dll_name name 'AxmMotGetOverridePosMode';
    function AxmMotSetOverrideLinePosMode; external dll_name name 'AxmMotSetOverrideLinePosMode';
    function AxmMotGetOverrideLinePosMode; external dll_name name 'AxmMotGetOverrideLinePosMode';
    function AxmMotSetVibrationControl; external dll_name name 'AxmMotSetVibrationControl';
    function AxmMotVibrationControlEnable; external dll_name name 'AxmMotVibrationControlEnable';
    function AxmMotVibrationControlIsEnable; external dll_name name 'AxmMotVibrationControlIsEnable';
    function AxmMotVibrationControlCoordEnable; external dll_name name 'AxmMotVibrationControlCoordEnable';
    function AxmMotVibrationControlCoordIsEnable; external dll_name name 'AxmMotVibrationControlCoordIsEnable';
    function AxmMotSetMultiTorqueLimit; external dll_name name 'AxmMotSetMultiTorqueLimit';
    function AxmMotMultiTorqueLimitEnable; external dll_name name 'AxmMotMultiTorqueLimitEnable';
    function AxmMotMultiTorqueLimitIsEnable; external dll_name name 'AxmMotMultiTorqueLimitIsEnable';
    function AxmMoveStartPosEx; external dll_name name 'AxmMoveStartPosEx';
    function AxmMovePosEx; external dll_name name 'AxmMovePosEx';
    function AxmMoveCoordStop; external dll_name name 'AxmMoveCoordStop';
    function AxmMoveCoordEStop; external dll_name name 'AxmMoveCoordEStop';
    function AxmMoveCoordSStop; external dll_name name 'AxmMoveCoordSStop';
    function AxmOverrideLinePos; external dll_name name 'AxmOverrideLinePos';
    function AxmOverrideLineVel; external dll_name name 'AxmOverrideLineVel';
    function AxmOverrideLineAccelVelDecel; external dll_name name 'AxmOverrideLineAccelVelDecel';
    function AxmOverrideAccelVelDecelAtPos; external dll_name name 'AxmOverrideAccelVelDecelAtPos';
    function AxmEGearSet; external dll_name name 'AxmEGearSet';
    function AxmEGearGet; external dll_name name 'AxmEGearGet';
    function AxmEGearReset; external dll_name name 'AxmEGearReset';
    function AxmEGearEnable; external dll_name name 'AxmEGearEnable';
    function AxmEGearIsEnable; external dll_name name 'AxmEGearIsEnable';
    function AxmHelixPitchMove; external dll_name name 'AxmHelixPitchMove';
    function AxmCompensationOneDimSet; external dll_name name 'AxmCompensationOneDimSet';
    function AxmCompensationOneDimGet; external dll_name name 'AxmCompensationOneDimGet';
    function AxmCompensationOneDimReset; external dll_name name 'AxmCompensationOneDimReset';
    function AxmCompensationOneDimEnable; external dll_name name 'AxmCompensationOneDimEnable';
    function AxmCompensationOneDimIsEnable; external dll_name name 'AxmCompensationOneDimIsEnable';
    function AxmCompensationOneDimGetCorrection; external dll_name name 'AxmCompensationOneDimGetCorrection';
    function AxmBlendingCoordSet; external dll_name name 'AxmBlendingCoordSet';
    function AxmBlendingCoordGet; external dll_name name 'AxmBlendingCoordGet';
    function AxmBlendingCoordReset; external dll_name name 'AxmBlendingCoordReset';
    function AxmBlendingCoordEnable; external dll_name name 'AxmBlendingCoordEnable';
    function AxmBlendingCoordIsEnable; external dll_name name 'AxmBlendingCoordIsEnable';
    function AxmStatusReadTorque; external dll_name name 'AxmStatusReadTorque';
    function AxmMotSetEndVel; external dll_name name 'AxmMotSetEndVel';
    function AxmMotGetEndVel; external dll_name name 'AxmMotGetEndVel';
    function AxmContiDigitalOutputBit; external dll_name name 'AxmContiDigitalOutputBit';
    function AxmLineMoveWithAxes; external dll_name name 'AxmLineMoveWithAxes';
    function AxmCircleCenterMoveWithAxes; external dll_name name 'AxmCircleCenterMoveWithAxes';
    function AxmLineMoveWithAxesWithEvent; external dll_name name 'AxmLineMoveWithAxesWithEvent';
    function AxmCircleCenterMoveWithAxesWithEvent; external dll_name name 'AxmCircleCenterMoveWithAxesWithEvent';
    function AxmInfoGetAxis; external dll_name name 'AxmInfoGetAxis';
    function AxmInfoGetAxisEx; external dll_name name 'AxmInfoGetAxisEx';
    function AxmInfoIsMotionModule; external dll_name name 'AxmInfoIsMotionModule';
    function AxmInfoIsInvalidAxisNo; external dll_name name 'AxmInfoIsInvalidAxisNo';
    function AxmInfoGetAxisStatus; external dll_name name 'AxmInfoGetAxisStatus';
    function AxmInfoGetAxisCount; external dll_name name 'AxmInfoGetAxisCount';
    function AxmInfoGetFirstAxisNo; external dll_name name 'AxmInfoGetFirstAxisNo';
    function AxmInfoGetBoardFirstAxisNo; external dll_name name 'AxmInfoGetBoardFirstAxisNo';
    function AxmVirtualSetAxisNoMap; external dll_name name 'AxmVirtualSetAxisNoMap';
    function AxmVirtualGetAxisNoMap; external dll_name name 'AxmVirtualGetAxisNoMap';
    function AxmVirtualSetMultiAxisNoMap; external dll_name name 'AxmVirtualSetMultiAxisNoMap';
    function AxmVirtualGetMultiAxisNoMap; external dll_name name 'AxmVirtualGetMultiAxisNoMap';
    function AxmVirtualResetAxisMap; external dll_name name 'AxmVirtualResetAxisMap';
    function AxmVirtualSetMultiReDefineAxisNo; external dll_name name 'AxmVirtualSetMultiReDefineAxisNo';
    function AxmVirtualGetMultiReDefineAxisNo; external dll_name name 'AxmVirtualGetMultiReDefineAxisNo';
    function AxmInterruptSetAxis; external dll_name name 'AxmInterruptSetAxis';
    function AxmInterruptSetAxisEnable; external dll_name name 'AxmInterruptSetAxisEnable';
    function AxmInterruptGetAxisEnable; external dll_name name 'AxmInterruptGetAxisEnable';
    function AxmInterruptRead; external dll_name name 'AxmInterruptRead';
    function AxmInterruptReadAxisFlag; external dll_name name 'AxmInterruptReadAxisFlag';
    function AxmInterruptSetUserEnable; external dll_name name 'AxmInterruptSetUserEnable';
    function AxmInterruptGetUserEnable; external dll_name name 'AxmInterruptGetUserEnable';
    function AxmMotLoadParaAll; external dll_name name 'AxmMotLoadParaAll';
    function AxmMotSaveParaAll; external dll_name name 'AxmMotSaveParaAll';
    function AxmMotSetParaLoad; external dll_name name 'AxmMotSetParaLoad';
    function AxmMotGetParaLoad; external dll_name name 'AxmMotGetParaLoad';
    function AxmMotSetPulseOutMethod; external dll_name name 'AxmMotSetPulseOutMethod';
    function AxmMotGetPulseOutMethod; external dll_name name 'AxmMotGetPulseOutMethod';
    function AxmMotSetEncInputMethod; external dll_name name 'AxmMotSetEncInputMethod';
    function AxmMotGetEncInputMethod; external dll_name name 'AxmMotGetEncInputMethod';
    function AxmMotSetMoveUnitPerPulse; external dll_name name 'AxmMotSetMoveUnitPerPulse';
    function AxmMotGetMoveUnitPerPulse; external dll_name name 'AxmMotGetMoveUnitPerPulse';
    function AxmMotSetDecelMode; external dll_name name 'AxmMotSetDecelMode';
    function AxmMotGetDecelMode; external dll_name name 'AxmMotGetDecelMode';
    function AxmMotSetRemainPulse; external dll_name name 'AxmMotSetRemainPulse';
    function AxmMotGetRemainPulse; external dll_name name 'AxmMotGetRemainPulse';
    function AxmMotSetMaxVel; external dll_name name 'AxmMotSetMaxVel';
    function AxmMotGetMaxVel; external dll_name name 'AxmMotGetMaxVel';
    function AxmMotSetAbsRelMode; external dll_name name 'AxmMotSetAbsRelMode';
    function AxmMotGetAbsRelMode; external dll_name name 'AxmMotGetAbsRelMode';
    function AxmMotSetProfileMode; external dll_name name 'AxmMotSetProfileMode';
    function AxmMotGetProfileMode; external dll_name name 'AxmMotGetProfileMode';
    function AxmMotSetAccelUnit; external dll_name name 'AxmMotSetAccelUnit';
    function AxmMotGetAccelUnit; external dll_name name 'AxmMotGetAccelUnit';
    function AxmMotSetMinVel; external dll_name name 'AxmMotSetMinVel';
    function AxmMotGetMinVel; external dll_name name 'AxmMotGetMinVel';
    function AxmMotSetAccelJerk; external dll_name name 'AxmMotSetAccelJerk';
    function AxmMotGetAccelJerk; external dll_name name 'AxmMotGetAccelJerk';
    function AxmMotSetDecelJerk; external dll_name name 'AxmMotSetDecelJerk';
    function AxmMotGetDecelJerk; external dll_name name 'AxmMotGetDecelJerk';
    function AxmMotSetProfilePriority; external dll_name name 'AxmMotSetProfilePriority';
    function AxmMotGetProfilePriority; external dll_name name 'AxmMotGetProfilePriority';
    function AxmSignalSetZphaseLevel; external dll_name name 'AxmSignalSetZphaseLevel';
    function AxmSignalGetZphaseLevel; external dll_name name 'AxmSignalGetZphaseLevel';
    function AxmSignalSetServoOnLevel; external dll_name name 'AxmSignalSetServoOnLevel';
    function AxmSignalGetServoOnLevel; external dll_name name 'AxmSignalGetServoOnLevel';
    function AxmSignalSetServoAlarmResetLevel; external dll_name name 'AxmSignalSetServoAlarmResetLevel';
    function AxmSignalGetServoAlarmResetLevel; external dll_name name 'AxmSignalGetServoAlarmResetLevel';
    function AxmSignalSetInpos; external dll_name name 'AxmSignalSetInpos';
    function AxmSignalGetInpos; external dll_name name 'AxmSignalGetInpos';
    function AxmSignalReadInpos; external dll_name name 'AxmSignalReadInpos';
    function AxmSignalSetServoAlarm; external dll_name name 'AxmSignalSetServoAlarm';
    function AxmSignalGetServoAlarm; external dll_name name 'AxmSignalGetServoAlarm';
    function AxmSignalReadServoAlarm; external dll_name name 'AxmSignalReadServoAlarm';
    function AxmSignalSetLimit; external dll_name name 'AxmSignalSetLimit';
    function AxmSignalGetLimit; external dll_name name 'AxmSignalGetLimit';
    function AxmSignalReadLimit; external dll_name name 'AxmSignalReadLimit';
    function AxmSignalSetSoftLimit; external dll_name name 'AxmSignalSetSoftLimit';
    function AxmSignalGetSoftLimit; external dll_name name 'AxmSignalGetSoftLimit';
    function AxmSignalReadSoftLimit; external dll_name name 'AxmSignalReadSoftLimit';
    function AxmSignalSetStop; external dll_name name 'AxmSignalSetStop';
    function AxmSignalGetStop; external dll_name name 'AxmSignalGetStop';
    function AxmSignalReadStop; external dll_name name 'AxmSignalReadStop';
    function AxmSignalServoOn; external dll_name name 'AxmSignalServoOn';
    function AxmSignalIsServoOn; external dll_name name 'AxmSignalIsServoOn';
    function AxmSignalServoAlarmReset; external dll_name name 'AxmSignalServoAlarmReset';
    function AxmSignalWriteOutput; external dll_name name 'AxmSignalWriteOutput';
    function AxmSignalReadOutput; external dll_name name 'AxmSignalReadOutput';
    function AxmSignalReadBrakeOn; external dll_name name 'AxmSignalReadBrakeOn';
    function AxmSignalWriteOutputBit; external dll_name name 'AxmSignalWriteOutputBit';
    function AxmSignalReadOutputBit; external dll_name name 'AxmSignalReadOutputBit';
    function AxmSignalReadInput; external dll_name name 'AxmSignalReadInput';
    function AxmSignalReadInputBit; external dll_name name 'AxmSignalReadInputBit';
    function AxmSignalSetFilterBandwidth; external dll_name name 'AxmSignalSetFilterBandwidth';
    function AxmSignalGetInputBitCount; external dll_name name 'AxmSignalGetInputBitCount';
    function AxmSignalGetOutputBitCount; external dll_name name 'AxmSignalGetOutputBitCount';
    function AxmStatusReadInMotion; external dll_name name 'AxmStatusReadInMotion';
    function AxmStatusReadDrivePulseCount; external dll_name name 'AxmStatusReadDrivePulseCount';
    function AxmStatusReadMotion; external dll_name name 'AxmStatusReadMotion';
    function AxmStatusReadStop; external dll_name name 'AxmStatusReadStop';
    function AxmStatusReadMechanical; external dll_name name 'AxmStatusReadMechanical';
    function AxmStatusReadVel; external dll_name name 'AxmStatusReadVel';
    function AxmStatusReadPosError; external dll_name name 'AxmStatusReadPosError';
    function AxmStatusReadDriveDistance; external dll_name name 'AxmStatusReadDriveDistance';
    function AxmStatusSetPosType; external dll_name name 'AxmStatusSetPosType';
    function AxmStatusGetPosType; external dll_name name 'AxmStatusGetPosType';
    function AxmStatusSetAbsOrgOffset; external dll_name name 'AxmStatusSetAbsOrgOffset';
    function AxmStatusGetAbsOrgOffset; external dll_name name 'AxmStatusGetAbsOrgOffset';
    function AxmStatusSetActPos; external dll_name name 'AxmStatusSetActPos';
    function AxmStatusGetActPos; external dll_name name 'AxmStatusGetActPos';
    function AxmStatusGetAmpActPos; external dll_name name 'AxmStatusGetAmpActPos';
    function AxmStatusSetCmdPos; external dll_name name 'AxmStatusSetCmdPos';
    function AxmStatusGetCmdPos; external dll_name name 'AxmStatusGetCmdPos';
    function AxmStatusSetPosMatch; external dll_name name 'AxmStatusSetPosMatch';
    function AxmStatusReadMotionInfo; external dll_name name 'AxmStatusReadMotionInfo';
    function AxmStatusRequestServoAlarm; external dll_name name 'AxmStatusRequestServoAlarm';
    function AxmStatusReadServoAlarm; external dll_name name 'AxmStatusReadServoAlarm';
    function AxmStatusGetServoAlarmString; external dll_name name 'AxmStatusGetServoAlarmString';
    function AxmStatusReadServoAlarmString; external dll_name name 'AxmStatusReadServoAlarmString';
    function AxmStatusRequestServoAlarmHistory; external dll_name name 'AxmStatusRequestServoAlarmHistory';
    function AxmStatusReadServoAlarmHistory; external dll_name name 'AxmStatusReadServoAlarmHistory';
    function AxmStatusClearServoAlarmHistory; external dll_name name 'AxmStatusClearServoAlarmHistory';
    function AxmHomeSetSignalLevel; external dll_name name 'AxmHomeSetSignalLevel';
    function AxmHomeGetSignalLevel; external dll_name name 'AxmHomeGetSignalLevel';
    function AxmHomeReadSignal; external dll_name name 'AxmHomeReadSignal';
    function AxmHomeSetMethod; external dll_name name 'AxmHomeSetMethod';
    function AxmHomeGetMethod; external dll_name name 'AxmHomeGetMethod';
    function AxmHomeSetFineAdjust; external dll_name name 'AxmHomeSetFineAdjust';
    function AxmHomeGetFineAdjust; external dll_name name 'AxmHomeGetFineAdjust';
    function AxmHomeSetInterlock; external dll_name name 'AxmHomeSetInterlock';
    function AxmHomeGetInterlock; external dll_name name 'AxmHomeGetInterlock';
    function AxmHomeSetVel; external dll_name name 'AxmHomeSetVel';
    function AxmHomeGetVel; external dll_name name 'AxmHomeGetVel';
    function AxmHomeSetStart; external dll_name name 'AxmHomeSetStart';
    function AxmHomeSetResult; external dll_name name 'AxmHomeSetResult';
    function AxmHomeGetResult; external dll_name name 'AxmHomeGetResult';
    function AxmHomeGetRate; external dll_name name 'AxmHomeGetRate';
    function AxmMoveStartPos; external dll_name name 'AxmMoveStartPos';
    function AxmMovePos; external dll_name name 'AxmMovePos';
    function AxmMoveVel; external dll_name name 'AxmMoveVel';
    function AxmMoveStartMultiVel; external dll_name name 'AxmMoveStartMultiVel';
    function AxmMoveStartMultiVelEx; external dll_name name 'AxmMoveStartMultiVelEx';
    function AxmMoveStartLineVel; external dll_name name 'AxmMoveStartLineVel';
    function AxmMoveSignalSearch; external dll_name name 'AxmMoveSignalSearch';
    function AxmMoveSignalSearchAtDis; external dll_name name 'AxmMoveSignalSearchAtDis';
    function AxmMoveSignalCapture; external dll_name name 'AxmMoveSignalCapture';
    function AxmMoveGetCapturePos; external dll_name name 'AxmMoveGetCapturePos';
    function AxmMoveStartMultiPos; external dll_name name 'AxmMoveStartMultiPos';
    function AxmMoveMultiPos; external dll_name name 'AxmMoveMultiPos';
    function AxmMoveStartTorque; external dll_name name 'AxmMoveStartTorque';
    function AxmMoveTorqueStop; external dll_name name 'AxmMoveTorqueStop';
    function AxmMoveStartPosWithList; external dll_name name 'AxmMoveStartPosWithList';
    function AxmMoveStartPosWithPosEvent; external dll_name name 'AxmMoveStartPosWithPosEvent';
    function AxmMoveStop; external dll_name name 'AxmMoveStop';
    function AxmMoveStopEx; external dll_name name 'AxmMoveStopEx';
    function AxmMoveEStop; external dll_name name 'AxmMoveEStop';
    function AxmMoveSStop; external dll_name name 'AxmMoveSStop';
    function AxmOverridePos; external dll_name name 'AxmOverridePos';
    function AxmOverrideSetMaxVel; external dll_name name 'AxmOverrideSetMaxVel';
    function AxmOverrideVel; external dll_name name 'AxmOverrideVel';
    function AxmOverrideAccelVelDecel; external dll_name name 'AxmOverrideAccelVelDecel';
    function AxmOverrideVelAtPos; external dll_name name 'AxmOverrideVelAtPos';
    function AxmOverrideVelAtMultiPos; external dll_name name 'AxmOverrideVelAtMultiPos';
    function AxmOverrideVelAtMultiPos2; external dll_name name 'AxmOverrideVelAtMultiPos2';
    function AxmLinkSetMode; external dll_name name 'AxmLinkSetMode';
    function AxmLinkGetMode; external dll_name name 'AxmLinkGetMode';
    function AxmLinkResetMode; external dll_name name 'AxmLinkResetMode';
    function AxmGantrySetEnable; external dll_name name 'AxmGantrySetEnable';
    function AxmGantryGetEnable; external dll_name name 'AxmGantryGetEnable';
    function AxmGantrySetDisable; external dll_name name 'AxmGantrySetDisable';
    function AxmGantrySetCompensationGain; external dll_name name 'AxmGantrySetCompensationGain';
    function AxmGantryGetCompensationGain; external dll_name name 'AxmGantryGetCompensationGain';
    function AxmGantrySetErrorRange; external dll_name name 'AxmGantrySetErrorRange';
    function AxmGantryGetErrorRange; external dll_name name 'AxmGantryGetErrorRange';
    function AxmGantryReadErrorRangeStatus; external dll_name name 'AxmGantryReadErrorRangeStatus';
    function AxmGantryReadErrorRangeComparePos; external dll_name name 'AxmGantryReadErrorRangeComparePos';
    function AxmLineMove; external dll_name name 'AxmLineMove';
    function AxmLineMoveEx2; external dll_name name 'AxmLineMoveEx2';
    function AxmCircleCenterMove; external dll_name name 'AxmCircleCenterMove';
    function AxmCirclePointMove; external dll_name name 'AxmCirclePointMove';
    function AxmCirclePointMoveEx; external dll_name name 'AxmCirclePointMoveEx';
    function AxmCircleRadiusMove; external dll_name name 'AxmCircleRadiusMove';
    function AxmCircleAngleMove; external dll_name name 'AxmCircleAngleMove';
    function AxmContiSetAxisMap; external dll_name name 'AxmContiSetAxisMap';
    function AxmContiGetAxisMap; external dll_name name 'AxmContiGetAxisMap';
    function AxmContiResetAxisMap; external dll_name name 'AxmContiResetAxisMap';
    function AxmContiSetAbsRelMode; external dll_name name 'AxmContiSetAbsRelMode';
    function AxmContiGetAbsRelMode; external dll_name name 'AxmContiGetAbsRelMode';
    function AxmContiReadFree; external dll_name name 'AxmContiReadFree';
    function AxmContiReadIndex; external dll_name name 'AxmContiReadIndex';
    function AxmContiWriteClear; external dll_name name 'AxmContiWriteClear';
    function AxmContiBeginNode; external dll_name name 'AxmContiBeginNode';
    function AxmContiEndNode; external dll_name name 'AxmContiEndNode';
    function AxmContiStart; external dll_name name 'AxmContiStart';
    function AxmContiIsMotion; external dll_name name 'AxmContiIsMotion';
    function AxmContiGetNodeNum; external dll_name name 'AxmContiGetNodeNum';
    function AxmContiGetTotalNodeNum; external dll_name name 'AxmContiGetTotalNodeNum';
    function AxmContiDigitalOutputBit; external dll_name name 'AxmContiDigitalOutputBit';
    function AxmContiReadStop; external dll_name name 'AxmContiReadStop';
    function AxmContiSetLineMoveVelMode; external dll_name name 'AxmContiSetLineMoveVelMode';
    function AxmContiGetLineMoveVelMode; external dll_name name 'AxmContiGetLineMoveVelMode';
    function AxmContiSetCheckSoftLimit; external dll_name name 'AxmContiSetCheckSoftLimit';
    function AxmContiGetCheckSoftLimit; external dll_name name 'AxmContiGetCheckSoftLimit';
    function AxmContiSetConnectionRadius; external dll_name name 'AxmContiSetConnectionRadius';
    function AxmContiSetConnectionMaxCentripetalAccel; external dll_name name 'AxmContiSetConnectionMaxCentripetalAccel';
    function AxmTriggerSetTimeLevel; external dll_name name 'AxmTriggerSetTimeLevel';
    function AxmTriggerGetTimeLevel; external dll_name name 'AxmTriggerGetTimeLevel';
    function AxmTriggerSetAbsPeriod; external dll_name name 'AxmTriggerSetAbsPeriod';
    function AxmTriggerGetAbsPeriod; external dll_name name 'AxmTriggerGetAbsPeriod';
    function AxmTriggerSetBlock; external dll_name name 'AxmTriggerSetBlock';
    function AxmTriggerGetBlock; external dll_name name 'AxmTriggerGetBlock';
    function AxmTriggerOneShot; external dll_name name 'AxmTriggerOneShot';
    function AxmTriggerSetTimerOneshot; external dll_name name 'AxmTriggerSetTimerOneshot';
    function AxmTriggerOnlyAbs; external dll_name name 'AxmTriggerOnlyAbs';
    function AxmTriggerSetReset; external dll_name name 'AxmTriggerSetReset';
    function AxmCrcSetMaskLevel; external dll_name name 'AxmCrcSetMaskLevel';
    function AxmCrcGetMaskLevel; external dll_name name 'AxmCrcGetMaskLevel';
    function AxmCrcSetOutput; external dll_name name 'AxmCrcSetOutput';
    function AxmCrcGetOutput; external dll_name name 'AxmCrcGetOutput';
    function AxmMPGSetEnable; external dll_name name 'AxmMPGSetEnable';
    function AxmMPGGetEnable; external dll_name name 'AxmMPGGetEnable';
    function AxmMPGSetRatio; external dll_name name 'AxmMPGSetRatio';
    function AxmMPGGetRatio; external dll_name name 'AxmMPGGetRatio';
    function AxmMPGReset; external dll_name name 'AxmMPGReset';
    function AxmHelixCenterMove; external dll_name name 'AxmHelixCenterMove';
    function AxmHelixPointMove; external dll_name name 'AxmHelixPointMove';
    function AxmHelixRadiusMove; external dll_name name 'AxmHelixRadiusMove';
    function AxmHelixAngleMove; external dll_name name 'AxmHelixAngleMove';
    function AxmSplineWrite; external dll_name name 'AxmSplineWrite';
    function AxmCompensationSet; external dll_name name 'AxmCompensationSet';
    function AxmCompensationGet; external dll_name name 'AxmCompensationGet';
    function AxmCompensationEnable; external dll_name name 'AxmCompensationEnable';
    function AxmCompensationIsEnable; external dll_name name 'AxmCompensationIsEnable';
    function AxmCompensationGetCorrection; external dll_name name 'AxmCompensationGetCorrection';
    function AxmCompensationSetBacklash; external dll_name name 'AxmCompensationSetBacklash';
    function AxmCompensationGetBacklash; external dll_name name 'AxmCompensationGetBacklash';
    function AxmCompensationEnableBacklash; external dll_name name 'AxmCompensationEnableBacklash';
    function AxmCompensationIsEnableBacklash; external dll_name name 'AxmCompensationIsEnableBacklash';
    function AxmCompensationSetLocating; external dll_name name 'AxmCompensationSetLocating';
    function AxmEcamSet; external dll_name name 'AxmEcamSet';
    function AxmEcamSetWithSource; external dll_name name 'AxmEcamSetWithSource';
    function AxmEcamGet; external dll_name name 'AxmEcamGet';
    function AxmEcamGetWithSource; external dll_name name 'AxmEcamGetWithSource';
    function AxmEcamEnableBySlave; external dll_name name 'AxmEcamEnableBySlave';
    function AxmEcamEnableByMaster; external dll_name name 'AxmEcamEnableByMaster';
    function AxmEcamIsSlaveEnable; external dll_name name 'AxmEcamIsSlaveEnable';
    function AxmStatusSetServoMonitor; external dll_name name 'AxmStatusSetServoMonitor';
    function AxmStatusGetServoMonitor; external dll_name name 'AxmStatusGetServoMonitor';
    function AxmStatusSetServoMonitorEnable; external dll_name name 'AxmStatusSetServoMonitorEnable';
    function AxmStatusGetServoMonitorEnable; external dll_name name 'AxmStatusGetServoMonitorEnable';
    function AxmStatusReadServoMonitorFlag; external dll_name name 'AxmStatusReadServoMonitorFlag';
    function AxmStatusReadServoMonitorValue; external dll_name name 'AxmStatusReadServoMonitorValue';
    function AxmStatusSetReadServoLoadRatio; external dll_name name 'AxmStatusSetReadServoLoadRatio';
    function AxmStatusReadServoLoadRatio; external dll_name name 'AxmStatusReadServoLoadRatio';
    function AxmMotSetScaleCoeff; external dll_name name 'AxmMotSetScaleCoeff';
    function AxmMotGetScaleCoeff; external dll_name name 'AxmMotGetScaleCoeff';
    function AxmMoveSignalSearchEx; external dll_name name 'AxmMoveSignalSearchEx';
    function AxmMoveToAbsPos; external dll_name name 'AxmMoveToAbsPos';
    function AxmStatusReadVelEx; external dll_name name 'AxmStatusReadVelEx';
    function AxmMotSetElectricGearRatio; external dll_name name 'AxmMotSetElectricGearRatio';
    function AxmMotGetElectricGearRatio; external dll_name name 'AxmMotGetElectricGearRatio';
    function AxmMotSetTorqueLimit; external dll_name name 'AxmMotSetTorqueLimit';
    function AxmMotGetTorqueLimit; external dll_name name 'AxmMotGetTorqueLimit';
    function AxmMotSetTorqueLimitEx; external dll_name name 'AxmMotSetTorqueLimitEx';
    function AxmMotGetTorqueLimitEx; external dll_name name 'AxmMotGetTorqueLimitEx';
    function AxmMotSetTorqueLimitAtPos; external dll_name name 'AxmMotSetTorqueLimitAtPos';
    function AxmMotGetTorqueLimitAtPos; external dll_name name 'AxmMotGetTorqueLimitAtPos';
    function AxmMotSetTorqueLimitEnable; external dll_name name 'AxmMotSetTorqueLimitEnable';
    function AxmMotGetTorqueLimitEnable; external dll_name name 'AxmMotGetTorqueLimitEnable';
    function AxmOverridePosSetFunction; external dll_name name 'AxmOverridePosSetFunction';
    function AxmOverridePosGetFunction; external dll_name name 'AxmOverridePosGetFunction';
    function AxmSignalSetWriteOutputBitAtPos; external dll_name name 'AxmSignalSetWriteOutputBitAtPos';
    function AxmSignalGetWriteOutputBitAtPos; external dll_name name 'AxmSignalGetWriteOutputBitAtPos';
    function AxmAdvVSTSetParameter; external dll_name name 'AxmAdvVSTSetParameter';
    function AxmAdvVSTGetParameter; external dll_name name 'AxmAdvVSTGetParameter';
    function AxmAdvVSTSetEnabele; external dll_name name 'AxmAdvVSTSetEnabele';
    function AxmAdvVSTGetEnabele; external dll_name name 'AxmAdvVSTGetEnabele';
    function AxmAdvLineMove; external dll_name name 'AxmAdvLineMove';
    function AxmAdvOvrLineMove; external dll_name name 'AxmAdvOvrLineMove';
    function AxmAdvCircleCenterMove; external dll_name name 'AxmAdvCircleCenterMove';
    function AxmAdvCirclePointMove; external dll_name name 'AxmAdvCirclePointMove';
    function AxmAdvCircleAngleMove; external dll_name name 'AxmAdvCircleAngleMove';
    function AxmAdvCircleRadiusMove; external dll_name name 'AxmAdvCircleRadiusMove';
    function AxmAdvOvrCircleRadiusMove; external dll_name name 'AxmAdvOvrCircleRadiusMove';
    function AxmAdvHelixCenterMove; external dll_name name 'AxmAdvHelixCenterMove';
    function AxmAdvHelixPointMove; external dll_name name 'AxmAdvHelixPointMove';
    function AxmAdvHelixAngleMove; external dll_name name 'AxmAdvHelixAngleMove';
    function AxmAdvHelixRadiusMove; external dll_name name 'AxmAdvHelixRadiusMove';
    function AxmAdvOvrHelixRadiusMove; external dll_name name 'AxmAdvOvrHelixRadiusMove';
    function AxmAdvScriptLineMove; external dll_name name 'AxmAdvScriptLineMove';
    function AxmAdvScriptOvrLineMove; external dll_name name 'AxmAdvScriptOvrLineMove';
    function AxmAdvScriptCircleCenterMove; external dll_name name 'AxmAdvScriptCircleCenterMove';
    function AxmAdvScriptCirclePointMove; external dll_name name 'AxmAdvScriptCirclePointMove';
    function AxmAdvScriptCircleAngleMove; external dll_name name 'AxmAdvScriptCircleAngleMove';
    function AxmAdvScriptCircleRadiusMove; external dll_name name 'AxmAdvScriptCircleRadiusMove';
    function AxmAdvScriptOvrCircleRadiusMove; external dll_name name 'AxmAdvScriptOvrCircleRadiusMove';
    function AxmAdvScriptHelixCenterMove; external dll_name name 'AxmAdvScriptHelixCenterMove';
    function AxmAdvScriptHelixPointMove; external dll_name name 'AxmAdvScriptHelixPointMove';
    function AxmAdvScriptHelixAngleMove; external dll_name name 'AxmAdvScriptHelixAngleMove';
    function AxmAdvScriptHelixRadiusMove; external dll_name name 'AxmAdvScriptHelixRadiusMove';
    function AxmAdvScriptOvrHelixRadiusMove; external dll_name name 'AxmAdvScriptOvrHelixRadiusMove';
    function AxmAdvContiGetNodeNum; external dll_name name 'AxmAdvContiGetNodeNum';
    function AxmAdvContiGetTotalNodeNum; external dll_name name 'AxmAdvContiGetTotalNodeNum';
    function AxmAdvContiReadIndex; external dll_name name 'AxmAdvContiReadIndex';
    function AxmAdvContiReadFree; external dll_name name 'AxmAdvContiReadFree';
    function AxmAdvContiWriteClear; external dll_name name 'AxmAdvContiWriteClear';
    function AxmAdvOvrContiWriteClear; external dll_name name 'AxmAdvOvrContiWriteClear';
    function AxmAdvContiStart; external dll_name name 'AxmAdvContiStart';
    function AxmAdvContiStop; external dll_name name 'AxmAdvContiStop';
    function AxmAdvContiSetAxisMap; external dll_name name 'AxmAdvContiSetAxisMap';
    function AxmAdvContiGetAxisMap; external dll_name name 'AxmAdvContiGetAxisMap';
    function AxmAdvContiSetAbsRelMode; external dll_name name 'AxmAdvContiSetAbsRelMode';
    function AxmAdvContiGetAbsRelMode; external dll_name name 'AxmAdvContiGetAbsRelMode';
    function AxmAdvContiIsMotion; external dll_name name 'AxmAdvContiIsMotion';
    function AxmAdvContiBeginNode; external dll_name name 'AxmAdvContiBeginNode';
    function AxmAdvContiEndNode; external dll_name name 'AxmAdvContiEndNode';
    function AxmMoveMultiStop; external dll_name name 'AxmMoveMultiStop';
    function AxmMoveMultiEStop; external dll_name name 'AxmMoveMultiEStop';
    function AxmMoveMultiSStop; external dll_name name 'AxmMoveMultiSStop';
    function AxmStatusReadActVel; external dll_name name 'AxmStatusReadActVel';
    function AxmStatusReadServoCmdStat; external dll_name name 'AxmStatusReadServoCmdStat';
    function AxmStatusReadServoCmdCtrl; external dll_name name 'AxmStatusReadServoCmdCtrl';
    function AxmGantryGetMstToSlvOverDist; external dll_name name 'AxmGantryGetMstToSlvOverDist';
    function AxmGantrySetMstToSlvOverDist; external dll_name name 'AxmGantrySetMstToSlvOverDist';
    function AxmSignalReadServoAlarmCode; external dll_name name 'AxmSignalReadServoAlarmCode';
    function AxmM3ServoCoordinatesSet; external dll_name name 'AxmM3ServoCoordinatesSet';
    function AxmM3ServoBreakOn; external dll_name name 'AxmM3ServoBreakOn';
    function AxmM3ServoBreakOff; external dll_name name 'AxmM3ServoBreakOff';
    function AxmM3ServoConfig; external dll_name name 'AxmM3ServoConfig';
    function AxmM3ServoSensOn; external dll_name name 'AxmM3ServoSensOn';
    function AxmM3ServoSensOff; external dll_name name 'AxmM3ServoSensOff';
    function AxmM3ServoSmon; external dll_name name 'AxmM3ServoSmon';
    function AxmM3ServoGetSmon; external dll_name name 'AxmM3ServoGetSmon';
    function AxmM3ServoSvOn; external dll_name name 'AxmM3ServoSvOn';
    function AxmM3ServoSvOff; external dll_name name 'AxmM3ServoSvOff';
    function AxmM3ServoInterpolate; external dll_name name 'AxmM3ServoInterpolate';
    function AxmM3ServoPosing; external dll_name name 'AxmM3ServoPosing';
    function AxmM3ServoFeed; external dll_name name 'AxmM3ServoFeed';
    function AxmM3ServoExFeed; external dll_name name 'AxmM3ServoExFeed';
    function AxmM3ServoExPosing; external dll_name name 'AxmM3ServoExPosing';
    function AxmM3ServoZret; external dll_name name 'AxmM3ServoZret';
    function AxmM3ServoVelctrl; external dll_name name 'AxmM3ServoVelctrl';
    function AxmM3ServoTrqctrl; external dll_name name 'AxmM3ServoTrqctrl';
    function AxmM3ServoGetParameter; external dll_name name 'AxmM3ServoGetParameter';
    function AxmM3ServoSetParameter; external dll_name name 'AxmM3ServoSetParameter';
    function AxmServoCmdExecution; external dll_name name 'AxmServoCmdExecution';
    function AxmM3ServoGetTorqLimit; external dll_name name 'AxmM3ServoGetTorqLimit';
    function AxmM3ServoSetTorqLimit; external dll_name name 'AxmM3ServoSetTorqLimit';
    function AxmM3ServoGetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoGetSendSvCmdIOOutput';
    function AxmM3ServoSetSendSvCmdIOOutput; external dll_name name 'AxmM3ServoSetSendSvCmdIOOutput';
    function AxmM3ServoGetSvCmdCtrl; external dll_name name 'AxmM3ServoGetSvCmdCtrl';
    function AxmM3ServoSetSvCmdCtrl; external dll_name name 'AxmM3ServoSetSvCmdCtrl';
    function AxmM3AdjustmentOperation; external dll_name name 'AxmM3AdjustmentOperation';
    function AxmM3ServoSetMonSel; external dll_name name 'AxmM3ServoSetMonSel';
    function AxmM3ServoGetMonSel; external dll_name name 'AxmM3ServoGetMonSel';
    function AxmM3ServoReadMonData; external dll_name name 'AxmM3ServoReadMonData';
    function AxmAdvTorqueContiSetAxisMap; external dll_name name 'AxmAdvTorqueContiSetAxisMap';
    function AxmM3ServoSetTorqProfile; external dll_name name 'AxmM3ServoSetTorqProfile';
    function AxmM3ServoGetTorqProfile; external dll_name name 'AxmM3ServoGetTorqProfile';
    function AxmSignalSetInposRange; external dll_name name 'AxmSignalSetInposRange';
    function AxmSignalGetInposRange; external dll_name name 'AxmSignalGetInposRange';
    function AxmStatusSetEncClear; external dll_name name 'AxmStatusSetEncClear';
    function AxmStatusSetMotorPosMatch; external dll_name name 'AxmStatusSetMotorPosMatch';
    function AxmMotSetWorkCoordinate; external dll_name name 'AxmMotSetWorkCoordinate';
    function AxmMotGetWorkCoordinate; external dll_name name 'AxmMotGetWorkCoordinate';
    function AxmMotSetOverridePosMode; external dll_name name 'AxmMotSetOverridePosMode';
    function AxmMotGetOverridePosMode; external dll_name name 'AxmMotGetOverridePosMode';
    function AxmMotSetOverrideLinePosMode; external dll_name name 'AxmMotSetOverrideLinePosMode';
    function AxmMotGetOverrideLinePosMode; external dll_name name 'AxmMotGetOverrideLinePosMode';
    function AxmMotSetVibrationControl; external dll_name name 'AxmMotSetVibrationControl';
    function AxmMotVibrationControlEnable; external dll_name name 'AxmMotVibrationControlEnable';
    function AxmMotVibrationControlIsEnable; external dll_name name 'AxmMotVibrationControlIsEnable';
    function AxmMotVibrationControlCoordEnable; external dll_name name 'AxmMotVibrationControlCoordEnable';
    function AxmMotVibrationControlCoordIsEnable; external dll_name name 'AxmMotVibrationControlCoordIsEnable';
    function AxmMotSetMultiTorqueLimit; external dll_name name 'AxmMotSetMultiTorqueLimit';
    function AxmMotMultiTorqueLimitEnable; external dll_name name 'AxmMotMultiTorqueLimitEnable';
    function AxmMotMultiTorqueLimitIsEnable; external dll_name name 'AxmMotMultiTorqueLimitIsEnable';
    function AxmMoveStartPosEx; external dll_name name 'AxmMoveStartPosEx';
    function AxmMovePosEx; external dll_name name 'AxmMovePosEx';
    function AxmMoveCoordStop; external dll_name name 'AxmMoveCoordStop';
    function AxmMoveCoordEStop; external dll_name name 'AxmMoveCoordEStop';
    function AxmMoveCoordSStop; external dll_name name 'AxmMoveCoordSStop';
    function AxmOverrideLinePos; external dll_name name 'AxmOverrideLinePos';
    function AxmOverrideLineVel; external dll_name name 'AxmOverrideLineVel';
    function AxmOverrideLineAccelVelDecel; external dll_name name 'AxmOverrideLineAccelVelDecel';
    function AxmOverrideAccelVelDecelAtPos; external dll_name name 'AxmOverrideAccelVelDecelAtPos';
    function AxmEGearSet; external dll_name name 'AxmEGearSet';
    function AxmEGearGet; external dll_name name 'AxmEGearGet';
    function AxmEGearReset; external dll_name name 'AxmEGearReset';
    function AxmEGearEnable; external dll_name name 'AxmEGearEnable';
    function AxmEGearIsEnable; external dll_name name 'AxmEGearIsEnable';
    function AxmHelixPitchMove; external dll_name name 'AxmHelixPitchMove';
    function AxmCompensationOneDimSet; external dll_name name 'AxmCompensationOneDimSet';
    function AxmCompensationOneDimGet; external dll_name name 'AxmCompensationOneDimGet';
    function AxmCompensationOneDimReset; external dll_name name 'AxmCompensationOneDimReset';
    function AxmCompensationOneDimIsSet; external dll_name name 'AxmCompensationOneDimIsSet';
    function AxmCompensationOneDimEnable; external dll_name name 'AxmCompensationOneDimEnable';
    function AxmCompensationOneDimIsEnable; external dll_name name 'AxmCompensationOneDimIsEnable';
    function AxmCompensationOneDimGetCorrection; external dll_name name 'AxmCompensationOneDimGetCorrection';
    function AxmCompensationOneDimSetReverse; external dll_name name 'AxmCompensationOneDimSetReverse';
    function AxmCompensationOneDimGetReverse; external dll_name name 'AxmCompensationOneDimGetReverse';
    function AxmCompensationOneDimGetCorrectionReverse; external dll_name name 'AxmCompensationOneDimGetCorrectionReverse';
    function AxmCompensationOneDimFileLoad; external dll_name name 'AxmCompensationOneDimFileLoad';
    function AxmCompensationOneDimFileSave; external dll_name name 'AxmCompensationOneDimFileSave';
    function AxmCompensationOneDimSetInterpolationMethod; external dll_name name 'AxmCompensationOneDimSetInterpolationMethod';
    function AxmCompensationOneDimGetInterpolationMethod; external dll_name name 'AxmCompensationOneDimGetInterpolationMethod';
    function AxmCompensationTwoDimSet; external dll_name name 'AxmCompensationTwoDimSet';
    function AxmCompensationTwoDimGet; external dll_name name 'AxmCompensationTwoDimGet';
    function AxmCompensationTwoDimReset; external dll_name name 'AxmCompensationTwoDimReset';
    function AxmCompensationTwoDimIsSet; external dll_name name 'AxmCompensationTwoDimIsSet';
    function AxmCompensationTwoDimEnable; external dll_name name 'AxmCompensationTwoDimEnable';
    function AxmCompensationTwoDimIsEnable; external dll_name name 'AxmCompensationTwoDimIsEnable';
    function AxmCompensationTwoDimGetCorrection; external dll_name name 'AxmCompensationTwoDimGetCorrection';
    function AxmCompensationTwoDimFileLoad; external dll_name name 'AxmCompensationTwoDimFileLoad';
    function AxmCompensationTwoDimFileSave; external dll_name name 'AxmCompensationTwoDimFileSave';
    function AxmBlendingCoordSet; external dll_name name 'AxmBlendingCoordSet';
    function AxmBlendingCoordGet; external dll_name name 'AxmBlendingCoordGet';
    function AxmBlendingCoordReset; external dll_name name 'AxmBlendingCoordReset';
    function AxmBlendingCoordEnable; external dll_name name 'AxmBlendingCoordEnable';
    function AxmBlendingCoordIsEnable; external dll_name name 'AxmBlendingCoordIsEnable';
    function AxmStatusReadTorque; external dll_name name 'AxmStatusReadTorque';
    function AxmMotSetEndVel; external dll_name name 'AxmMotSetEndVel';
    function AxmMotGetEndVel; external dll_name name 'AxmMotGetEndVel';
    function AxmContiDigitalOutputBit; external dll_name name 'AxmContiDigitalOutputBit';
    function AxmLineMoveWithAxes; external dll_name name 'AxmLineMoveWithAxes';
    function AxmCircleCenterMoveWithAxes; external dll_name name 'AxmCircleCenterMoveWithAxes';
    function AxmCircleRadiusMoveWithAxes; external dll_name name 'AxmCircleRadiusMoveWithAxes';
    function AxmCircleAngleMoveWithAxes; external dll_name name 'AxmCircleAngleMoveWithAxes';
    function AxmCirclePointMoveWithAxes; external dll_name name 'AxmCirclePointMoveWithAxes';
    function AxmLineMoveWithAxesWithEvent; external dll_name name 'AxmLineMoveWithAxesWithEvent';
    function AxmCircleCenterMoveWithAxesWithEvent; external dll_name name 'AxmCircleCenterMoveWithAxesWithEvent';
    function AxmMovePVT; external dll_name name 'AxmMovePVT';
    function AxmSyncSetAxisMap; external dll_name name 'AxmSyncSetAxisMap';
    function AxmSyncClear; external dll_name name 'AxmSyncClear';
    function AxmSyncBegin; external dll_name name 'AxmSyncBegin';
    function AxmSyncEnd; external dll_name name 'AxmSyncEnd';
    function AxmSyncStart; external dll_name name 'AxmSyncStart';
