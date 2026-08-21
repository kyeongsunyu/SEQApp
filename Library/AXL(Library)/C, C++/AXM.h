/****************************************************************************
*****************************************************************************
**
** File Name
** ---------
**
** AXM.H
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Ajinextek Motion Library Header File
** 
**
*****************************************************************************
*****************************************************************************
**
** Source Change Indices
** ----------------------
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


#ifndef __AXT_AXM_H__
#define __AXT_AXM_H__

#include "AXHS.h"

#ifdef __cplusplus
extern "C" {
#endif    //__cplusplus


//========== Board and module verification API(Info) - Information =================================================================================
// Return board number, module position and module ID of relevant axis.
DWORD    __stdcall AxmInfoGetAxis(long lAxisNo, long *lpBoardNo, long *lpModulePos, DWORD *upModuleID);

// Get the specified module board : Sub ID, module name, module description
//===============================================/
// support product      : EtherCAT
// upModuleSubID        : EtherCAT SubID(for distinguish between EtherCAT modules)
// szModuleName         : model name of module(50 Bytes)
// szModuleDescription  : description of module(80 Bytes)
//======================================================//
DWORD    __stdcall AxmInfoGetAxisEx(long lAxisNo, DWORD *upModuleSubID, char* szModuleName, char* szModuleDescription);

// Return whether the motion module exists.
DWORD    __stdcall AxmInfoIsMotionModule(DWORD *upStatus);
// Return whether relevant axis is valid.
DWORD    __stdcall AxmInfoIsInvalidAxisNo(long lAxisNo);
// Return whether relevant axis status.
DWORD    __stdcall AxmInfoGetAxisStatus(long lAxisNo);
// number of RTEX Products, return number of valid axis installed in system.
DWORD    __stdcall AxmInfoGetAxisCount(long *lpAxisCount);
// Return the first axis number of relevant board/module
DWORD    __stdcall AxmInfoGetFirstAxisNo(long lBoardNo, long lModulePos, long *lpAxisNo);
// Return the first axis number of relevant board.
DWORD    __stdcall AxmInfoGetBoardFirstAxisNo(long lBoardNo, long lModulePos, long *lpAxisNo);


//========= virtual axis function ============================================================================================
//
// Set virtual axis.
DWORD    __stdcall AxmVirtualSetAxisNoMap(long lRealAxisNo, long lVirtualAxisNo);
// Return the set virtual channel(axis) number.
DWORD    __stdcall AxmVirtualGetAxisNoMap(long lRealAxisNo, long *lpVirtualAxisNo);
// Set multi-virtual axes.
DWORD    __stdcall AxmVirtualSetMultiAxisNoMap(long lSize, long *lpRealAxesNo, long *lpVirtualAxesNo);
// Return the set multi-virtual channel(axis) number.
DWORD    __stdcall AxmVirtualGetMultiAxisNoMap(long lSize, long *lpRealAxesNo, long *lpVirtualAxesNo);
// Reset the virtual axis setting.
DWORD    __stdcall AxmVirtualResetAxisMap();


// Redefine the axis number.
DWORD    __stdcall AxmVirtualSetMultiReDefineAxisNo(long lSize, long *lpReDefineAxesNo);
// Get the redefined axis number.
DWORD    __stdcall AxmVirtualGetMultiReDefineAxisNo(long lSize, long *lpReDefineAxesNo);

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
DWORD    __stdcall AxmInterruptSetAxis(long lAxisNo, HWND hWnd, DWORD uMessage, AXT_INTERRUPT_PROC pProc, HANDLE *pEvent);


// Set whether to use interrupt of set axis or not.
// Set interrupt in the relevant axis/ verification
// uUse : use or not use => DISABLE(0), ENABLE(1)
DWORD    __stdcall AxmInterruptSetAxisEnable(long lAxisNo, DWORD uUse);
// Return whether to use interrupt of set axis or not
DWORD    __stdcall AxmInterruptGetAxisEnable(long lAxisNo, DWORD *upUse);


//Read relevant information when interrupt is used in event method
DWORD    __stdcall AxmInterruptRead(long *lpAxisNo, DWORD *upFlag);

// Return interrupt flag value of relevant axis.
DWORD    __stdcall AxmInterruptReadAxisFlag(long lAxisNo, long lBank, DWORD *upFlag);


// Set whether the interrupt set by user to specific axis occurs or not
// lBank         : Enable to set interrupt bank number(0 - 1).
// uInterruptNum : Enable to set interrupt number by setting bit number( 0 - 31 ).
DWORD    __stdcall AxmInterruptSetUserEnable(long lAxisNo, long lBank, DWORD uInterruptNum);

// Verify whether the interrupt set by user of specific axis occurs or not
DWORD    __stdcall AxmInterruptGetUserEnable(long lAxisNo, long lBank, DWORD *upInterruptNum);




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
DWORD    __stdcall AxmMotLoadParaAll(char *szFilePath);
// Save all parameter for all current axis by axis. Save as .mot file. Load file by using  AxmMotLoadParaAll.
DWORD    __stdcall AxmMotSaveParaAll(char *szFilePath);


// In parameter 28 - 31, user sets by using this API in the program.
DWORD    __stdcall AxmMotSetParaLoad(long lAxisNo, double dInitPos, double dInitVel, double dInitAccel, double dInitDecel);
// In parameter 28 - 31, user verifys by using this API in the program.
DWORD    __stdcall AxmMotGetParaLoad(long lAxisNo, double *dpInitPos, double *dpInitVel, double *dpInitAccel, double *dpInitDecel);


// Set the pulse output method of specific axis.
//uMethod  0 :OneHighLowHigh, 1 :OneHighHighLow, 2 :OneLowLowHigh, 3 :OneLowHighLow, 4 :TwoCcwCwHigh
//         5 :TwoCcwCwLow,    6 :TwoCwCcwHigh,   7 :TwoCwCcwLow,   8 :TwoPhase,      9 :TwoPhaseReverse
// OneHighLowHigh          = 0x0,   // 1 pulse method, PULSE(Active High), forward direction(DIR=Low)  / reverse direction(DIR=High)
// OneHighHighLow          = 0x1,   // 1 pulse method, PULSE(Active High), forward direction (DIR=High) / reverse direction (DIR=Low)
// OneLowLowHigh           = 0x2,   // 1 pulse method, PULSE(Active Low), forward direction (DIR=Low)  / reverse direction (DIR=High)
// OneLowHighLow           = 0x3,   // 1 pulse method, PULSE(Active Low), forward direction (DIR=High) / reverse direction (DIR=Low)
// TwoCcwCwHigh            = 0x4,   // 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active High
// TwoCcwCwLow             = 0x5,   // 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active Low
// TwoCwCcwHigh            = 0x6,   // 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active High
// TwoCwCcwLow             = 0x7,   // 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active Low
// TwoPhase                = 0x8,   // 2 phase (90' phase difference),  PULSE lead DIR(CW: forward direction), PULSE lag DIR(CCW: reverse direction)
// TwoPhaseReverse         = 0x9    // 2 phase(90' phase difference),  PULSE lead DIR(CCW: Forward diredtion), PULSE lag DIR(CW: Reverse direction)
DWORD    __stdcall AxmMotSetPulseOutMethod(long lAxisNo, DWORD uMethod);
// Return the setting of pulse output method of specific axis.
DWORD    __stdcall AxmMotGetPulseOutMethod(long lAxisNo, DWORD *upMethod);


// Set the Encoder input method including the setting of increase direction of actual count of specific axis.
// ObverseUpDownMode       = 0x0,   // Forward direction Up/Down
// ObverseSqr1Mode         = 0x1,   // Forward direction 1 multiplication
// ObverseSqr2Mode         = 0x2,   // Forward direction 2 multiplication
// ObverseSqr4Mode         = 0x3,   // Forward direction 4 multiplication
// ReverseUpDownMode       = 0x4,   // Reverse direction Up/Down
// ReverseSqr1Mode         = 0x5,   // Reverse direction 1 multiplication
// ReverseSqr2Mode         = 0x6,   // Reverse direction 2 multiplication
// ReverseSqr4Mode         = 0x7    // Reverse direction 4 multiplication
DWORD    __stdcall AxmMotSetEncInputMethod(long lAxisNo, DWORD uMethod);
// Return the Encoder input method including the setting of increase direction of actual count of specific axis.
DWORD    __stdcall AxmMotGetEncInputMethod(long lAxisNo, DWORD *upMethod);



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
DWORD    __stdcall AxmMotSetMoveUnitPerPulse(long lAxisNo, double dUnit, long lPulse);
// Return the travel distance of specific axis per pulse.
DWORD    __stdcall AxmMotGetMoveUnitPerPulse(long lAxisNo, double *dpUnit, long *lpPulse);


// Set deceleration starting point detecting method to specific axis.
// AutoDetect 0x0 : automatic acceleration/deceleration.
// RestPulse  0x1 : manual acceleration/deceleration."
DWORD    __stdcall AxmMotSetDecelMode(long lAxisNo, DWORD uMethod);
// Return the deceleration starting point detecting method of specific axis.
DWORD    __stdcall AxmMotGetDecelMode(long lAxisNo, DWORD *upMethod);


// Set remain pulse to the specific axis in manual deceleration mode.
DWORD    __stdcall AxmMotSetRemainPulse(long lAxisNo, DWORD uData);
// Return remain pulse of the specific axis in manual deceleration mode.
DWORD    __stdcall AxmMotGetRemainPulse(long lAxisNo, DWORD *upData);


// Set maximum velocity to the specific axis in uniform velocity movement API.
// Note : Input maximum speed value is not PPS but UNIT.
// ex) Maximum output frequency(PCI-N804/404 : 10 MPPS)
// ex) Maximum output Unit/Sec(PCI-N804/404 : 10MPPS * Unit/Pulse)
DWORD    __stdcall AxmMotSetMaxVel(long lAxisNo, double dVel);
// Return maximum velocity of the specific axis in uniform velocity movement API
DWORD    __stdcall AxmMotGetMaxVel(long lAxisNo, double *dpVel);


// Set travel distance calculation mode of specific axis.
//uAbsRelMode : POS_ABS_MODE '0' - absolute coordinate system
//              POS_REL_MODE '1' - relative coordinate system
DWORD    __stdcall AxmMotSetAbsRelMode(long lAxisNo, DWORD uAbsRelMode);
// Return travel distance calculation mode of specific axis.
DWORD    __stdcall AxmMotGetAbsRelMode(long lAxisNo, DWORD *upAbsRelMode);


//Set move velocity profile mode of specific axis.
//ProfileMode : SYM_TRAPEZOIDE_MODE  '0' - symmetry Trapezode
//              ASYM_TRAPEZOIDE_MODE '1' - asymmetric Trapezode
//              QUASI_S_CURVE_MODE   '2' - symmetry Quasi-S Curve
//              SYM_S_CURVE_MODE     '3' - symmetry S Curve
//              ASYM_S_CURVE_MODE    '4' - asymmetric S Curve
//              SYM_TRAP_M3_SW_MODE  '5' - Symmetry Trapezode : MLIII internal S/W Profile
//              ASYM_TRAP_M3_SW_MODE '6' - Asymmetry Trapezode : MLIII internal S/W Profile
//              SYM_S_M3_SW_MODE     '7' - Symmetry S Curve : MLIII internal S/W Profile
//              ASYM_S_M3_SW_MODE    '8' - Asymmetric S Curve : MLIII internal S/W Profile
DWORD    __stdcall AxmMotSetProfileMode(long lAxisNo, DWORD uProfileMode);
// Return move velocity profile mode of specific axis.
DWORD    __stdcall AxmMotGetProfileMode(long lAxisNo, DWORD *upProfileMode);


//Set acceleration unit of specific axis.
//AccelUnit : '0' - use unit/sec2 for the unit of acceleration/deceleration
//            '1' - use sec for the unit of acceleration/deceleration
DWORD    __stdcall AxmMotSetAccelUnit(long lAxisNo, DWORD uAccelUnit);
// Return acceleration unit of specific axis.
DWORD    __stdcall AxmMotGetAccelUnit(long lAxisNo, DWORD *upAccelUnit);


// Set initial velocity to the specific axis.
DWORD    __stdcall AxmMotSetMinVel(long lAxisNo, double dMinVel);
// Return initial velocity of the specific axis.
DWORD    __stdcall AxmMotGetMinVel(long lAxisNo, double *dpMinVel);


// Set acceleration jerk value of specific axis.[%].
DWORD    __stdcall AxmMotSetAccelJerk(long lAxisNo, double dAccelJerk);
// Return acceleration jerk value of specific axis.
DWORD    __stdcall AxmMotGetAccelJerk(long lAxisNo, double *dpAccelJerk);


// Set deceleration jerk value of specific axis.[%].
DWORD    __stdcall AxmMotSetDecelJerk(long lAxisNo, double dDecelJerk);
// Return deceleration jerk value of specific axis.
DWORD    __stdcall AxmMotGetDecelJerk(long lAxisNo, double *dpDecelJerk);


// Setting priority when determining speed profile of specified axis.(Velocity or Acceleration)
// Priority : PRIORITY_VELOCITY   '0' - Calculate close to specified speed value when determining velocity profile.
//            PRIORITY_ACCELTIME  '1' - Calculate close to specified speed value when determining Acceleration / Deceleration time profile.
DWORD    __stdcall AxmMotSetProfilePriority(long lAxisNo, DWORD uPriority);
// Return priority when determining speed profile of specified axis.(Velocity or Acceleration)
DWORD    __stdcall AxmMotGetProfilePriority(long lAxisNo, DWORD *upPriority);


//=========== Setting API related in/output signal ================================================================================

// Set Z phase level of specific axis.
// uLevel : LOW(0), HIGH(1)
DWORD    __stdcall AxmSignalSetZphaseLevel(long lAxisNo, DWORD uLevel);
// Return Z phase level of specific axis.
DWORD    __stdcall AxmSignalGetZphaseLevel(long lAxisNo, DWORD *upLevel);


// Set output level of Servo-On signal of specific axis.
// uLevel : LOW(0), HIGH(1)
DWORD    __stdcall AxmSignalSetServoOnLevel(long lAxisNo, DWORD uLevel);
// Return output level of Servo-On signal of specific axis.
DWORD    __stdcall AxmSignalGetServoOnLevel(long lAxisNo, DWORD *upLevel);


// Set output level of Servo-Alarm Reset signal of specific axis.
// uLevel : LOW(0), HIGH(1)
DWORD    __stdcall AxmSignalSetServoAlarmResetLevel(long lAxisNo, DWORD uLevel);
// Return output level of Servo-Alarm Reset signal of specific axis.
DWORD    __stdcall AxmSignalGetServoAlarmResetLevel(long lAxisNo, DWORD *upLevel);


//    Set whether to use Inposition signal of specific axis and signal input level.
// uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
DWORD    __stdcall AxmSignalSetInpos(long lAxisNo, DWORD uUse);
// Return whether to use Inposition signal of specific axis and signal input level.
DWORD    __stdcall AxmSignalGetInpos(long lAxisNo, DWORD *upUse);
// Return inposition signal input mode of specific axis.
DWORD    __stdcall AxmSignalReadInpos(long lAxisNo, DWORD *upStatus);


// Set whether to use emergency stop or not against to alarm signal input and set signal input level of specific axis.
// uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
DWORD    __stdcall AxmSignalSetServoAlarm(long lAxisNo, DWORD uUse);
// Return whether to use emergency stop or not against to alarm signal input and set signal input level of specific axis.
DWORD    __stdcall AxmSignalGetServoAlarm(long lAxisNo, DWORD *upUse);
// Return input level of alarm signal of specific axis.
DWORD    __stdcall AxmSignalReadServoAlarm(long lAxisNo, DWORD *upStatus);


// Set whether to use end limit sensor of specific axis and input level of signal.
// Available to set of slow down stop or emergency stop when end limit sensor is input.
// uStopMode: EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// uPositiveLevel, uNegativeLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
DWORD    __stdcall AxmSignalSetLimit(long lAxisNo, DWORD uStopMode, DWORD uPositiveLevel, DWORD uNegativeLevel);
// Return whether to use end limit sensor of specific axis , input level of signal and stop mode for signal input.
DWORD    __stdcall AxmSignalGetLimit(long lAxisNo, DWORD *upStopMode, DWORD *upPositiveLevel, DWORD *upNegativeLevel);
// Return the input state of end limit sensor of specific axis.
DWORD    __stdcall AxmSignalReadLimit(long lAxisNo, DWORD *upPositiveStatus, DWORD *upNegativeStatus);


// Set whether to use software limit, count to use and stop method of specific axis.
// uUse       : DISABLE(0), ENABLE(1)
// uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// uSelection : COMMAND(0), ACTUAL(1)
// Caution: When software limit is set in advance by using above API in origin detecting and is moving, if the detecting of origin is stopped during detecting, it becomes DISABLE.
DWORD    __stdcall AxmSignalSetSoftLimit(long lAxisNo, DWORD uUse, DWORD uStopMode, DWORD uSelection, double dPositivePos, double dNegativePos);
// Return whether to use software limit, count to use and stop method of specific axis.
DWORD    __stdcall AxmSignalGetSoftLimit(long lAxisNo, DWORD *upUse, DWORD *upStopMode, DWORD *upSelection, double *dpPositivePos, double *dpNegativePos);
DWORD    __stdcall AxmSignalReadSoftLimit(long lAxisNo, DWORD *upPositiveStatus, DWORD *upNegativeStatus);


// Set the stop method of emergency stop(emergency stop/slowdown stop) ,or whether to use or not.
// uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
DWORD    __stdcall AxmSignalSetStop(long lAxisNo, DWORD uStopMode, DWORD uLevel);
// Return the stop method of emergency stop(emergency stop/slowdown stop) ,or whether to use or not.
DWORD    __stdcall AxmSignalGetStop(long lAxisNo, DWORD *upStopMode, DWORD *upLevel);
// Return input state of emergency stop.
DWORD    __stdcall AxmSignalReadStop(long lAxisNo, DWORD *upStatus);


// Output the Servo-On signal of specific axis.
// uOnOff : FALSE(0), TRUE(1) ( The case of universal 0 output)
DWORD    __stdcall AxmSignalServoOn(long lAxisNo, DWORD uOnOff);
// Return the output state of Servo-On signal of specific axis.
DWORD    __stdcall AxmSignalIsServoOn(long lAxisNo, DWORD *upOnOff);


// Output the Servo-Alarm Reset signal of specific axis.
// uOnOff : FALSE(0), TRUE(1) (The case of universal 1 output)
DWORD    __stdcall AxmSignalServoAlarmReset(long lAxisNo, DWORD uOnOff);


//    Set universal output value.
//  uValue : Hex Value 0x00
DWORD    __stdcall AxmSignalWriteOutput(long lAxisNo, DWORD uValue);
// Return universal output value.
DWORD    __stdcall AxmSignalReadOutput(long lAxisNo, DWORD *upValue);


// ML3 Only
// Return Break Sensor Status
DWORD    __stdcall AxmSignalReadBrakeOn(long lAxisNo, DWORD *upOnOff);


// lBitNo : Bit Number(0 - 4)
// uOnOff : FALSE(0), TRUE(1)
// Set universal output values by bit.
DWORD    __stdcall AxmSignalWriteOutputBit(long lAxisNo, long lBitNo, DWORD uOnOff);
// Return universal output values by bit.
DWORD    __stdcall AxmSignalReadOutputBit(long lAxisNo, long lBitNo, DWORD *upOnOff);


// Return universal input value in Hex value.
DWORD    __stdcall AxmSignalReadInput(long lAxisNo, DWORD *upValue);

// lBitNo : Bit Number(0 - 4)
// Return universal input value by bit.
DWORD    __stdcall AxmSignalReadInputBit(long lAxisNo, long lBitNo, DWORD *upOn);


// Set universal In/Out digital filter coefficient.
// uSignal: END_LIMIT(0), INP_ALARM(1), UIN_00_01(2), UIN_02_04(3)
// dBandwidthUsec: 0.2uSec~26666usec
DWORD    __stdcall AxmSignalSetFilterBandwidth(long lAxisNo, DWORD uSignal, double dBandwidthUsec);


//========== API which verifies the state during motion moving and after moving. ============================================================
// Return number of bits of general purpose input.
DWORD   __stdcall AxmSignalGetInputBitCount(long lAxisNo, DWORD* upInputCount);


// Return number of bits of general purpose output.
DWORD   __stdcall AxmSignalGetOutputBitCount(long lAxisNo, DWORD* upOutputCount);


//========== API for checking status during or after motion. ==============================================================
// Return pulse output status of specified axis.(In motion state)
DWORD    __stdcall AxmStatusReadInMotion(long lAxisNo, DWORD *upStatus);


//  Return move pulse counter value of specific axis after start of move.
//  (pulse count value)"
DWORD    __stdcall AxmStatusReadDrivePulseCount(long lAxisNo, long *lpPulse);


// Return DriveStatus register (status of in-motion) of specific Axis.
// Caution: All Motion Product is different Hardware bit signal. Let's refer Manual and AXHS.xxx
DWORD    __stdcall AxmStatusReadMotion(long lAxisNo, DWORD *upStatus);


// Return EndStatus(status of stop) register of specific axis.
// Caution: All Motion Product is different Hardware bit signal. Let's refer Manual and AXHS.xxx
DWORD    __stdcall AxmStatusReadStop(long lAxisNo, DWORD *upStatus);


// Return Mechanical Signal Data(Current mechanical signal status)of specific axis.
// Caution: All Motion Product is different Hardware bit signal. Let's refer Manual and AXHS.xxx
DWORD    __stdcall AxmStatusReadMechanical(long lAxisNo, DWORD *upStatus);


// Read current move velocity oo specific axis.
DWORD    __stdcall AxmStatusReadVel(long lAxisNo, double *dpVel);


// Return the error between Command Pos and Actual Pos of specific axis.
DWORD    __stdcall AxmStatusReadPosError(long lAxisNo, double *dpError);


// Verify the travel(traveled) distance to the final drive.
DWORD    __stdcall AxmStatusReadDriveDistance(long lAxisNo, double *dpUnit);


// Set use the Position information Type of specific Axis.
// uPosType  : Select Position Information Type (Actual position / Command position)
//    POSITION_LIMIT '0' - Normal action, In all round action.
//    POSITION_BOUND '1' - Position cycle type, dNegativePos ~ dPositivePos Range
// Caution(PCI-Nx04)
// - If count value exceeds the max value, it becomes min value when setting BOUND.
// The other way, count value exceeds the min value, it becomes max value.

// dPositivePos setting range : 0 ~ positive number
// dNegativePos setting range : negative number ~ 0
DWORD    __stdcall AxmStatusSetPosType(long lAxisNo, DWORD uPosType, double dPositivePos, double dNegativePos);
// Return the Position Information Type of of specific axis.
DWORD    __stdcall AxmStatusGetPosType(long lAxisNo, DWORD *upPosType, double *dpPositivePos, double *dpNegativePos);
// Set absolute encoder origin offset Position of specific axis. [Only for PCI-R1604-MLII]
DWORD    __stdcall AxmStatusSetAbsOrgOffset(long lAxisNo, double dOrgOffsetPos);
// Return absolute encoder origin offset Position of specific axis.
DWORD    __stdcall AxmStatusGetAbsOrgOffset(long lAxisNo, double* dpOrgOffsetPos);


// Set the actual position of specific axis.
DWORD    __stdcall AxmStatusSetActPos(long lAxisNo, double dPos);
// Return the actual position of specific axis.
DWORD    __stdcall AxmStatusGetActPos(long lAxisNo, double *dpPos);
// Return the actual position of specific axis.(received from servo)
DWORD    __stdcall AxmStatusGetAmpActPos(long lAxisNo, double *dpPos);


// Set command position of specific axis.
DWORD    __stdcall AxmStatusSetCmdPos(long lAxisNo, double dPos);
// Return command position of specific axis.
DWORD    __stdcall AxmStatusGetCmdPos(long lAxisNo, double *dpPos);

// Set command position and actual position of specific axis
// Only RTEX use
DWORD    __stdcall AxmStatusSetPosMatch(long lAxisNo, double dPos);


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
DWORD    __stdcall AxmStatusReadMotionInfo(long lAxisNo, PMOTION_INFO pMI);


// API for Network product only
// API for read AlarmCode of specified axis.
DWORD    __stdcall AxmStatusRequestServoAlarm(long lAxisNo);
// API for read AlarmCode of specified axis.
// upAlarmCode      : Refer to Alarm Code of SERVOPACK.
// MR_J4_xxB        : Upper 16bit(Decimal value of 2 digits alarm code), Lower 16bit(Decimal value of 1digit detail alarm code)
// uReturnMode      : Set return condition of API.[Not used in SIIIH(MR-J4-xxB)]
// [0-Immediate]    : Return immediately after function execution.
// [1-Blocking]     : Does not return until the alarm code is read from SERVOPACK.
// [2-Non Blocking] : Does not return until the alarm code is read from SERVOPACK. but program is not blocked.
DWORD    __stdcall AxmStatusReadServoAlarm(long lAxisNo, DWORD uReturnMode, DWORD *upAlarmCode);
// The API to recieve alarm string about specified error code.
DWORD    __stdcall AxmStatusGetServoAlarmString(long lAxisNo, DWORD uAlarmCode, long lAlarmStringSize, char *szAlarmString);
DWORD    __stdcall AxmStatusReadServoAlarmString(long lAxisNo, long lAlarmStringSize, char *szAlarmString);

// The API to Command to SERVOPACK for read Alarm History of specified axis.
DWORD    __stdcall AxmStatusRequestServoAlarmHistory(long lAxisNo);
// The API to read SERVOPACK alarm history of specified axis.
// lpCount          : Number of read alarm history.
// upAlarmCode      : The array to return alarm history.
// uReturnMode      : Set return mode of this API.
// [0-Immediate]    : Return immediately after function execution.
// [1-Blocking]     : Not return until reading alarm code from SERVOPACK.
// [2-Non Blocking] : Not return until reading alarm code from SERVOPACK. but program is not blocked.
DWORD    __stdcall AxmStatusReadServoAlarmHistory(long lAxisNo, DWORD uReturnMode, long *lpCount, DWORD *upAlarmCode);
// Clear SERVOPACK alarm history of specified axis.
DWORD    __stdcall AxmStatusClearServoAlarmHistory(long lAxisNo);


//======== API related home. ======================================================================================================

// Set home sensor level of specific axis.
// uLevel : LOW(0), HIGH(1)
DWORD    __stdcall AxmHomeSetSignalLevel(long lAxisNo, DWORD uLevel);
// Return home sensor level of specific axis.
DWORD    __stdcall AxmHomeGetSignalLevel(long lAxisNo, DWORD *upLevel);
// Verify current home signal input status. Hoe signal can be set by user optionally by using AxmHomeSetMethod API.
// upStatus : OFF(0), ON(1)
DWORD    __stdcall AxmHomeReadSignal(long lAxisNo, DWORD *upStatus);


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
DWORD   __stdcall AxmHomeSetMethod(long lAxisNo, long lHmDir, DWORD uHomeSignal, DWORD uZphas, double dHomeClrTime, double dHomeOffset);
// Return set parameters related to home.
DWORD   __stdcall AxmHomeGetMethod(long lAxisNo, long *lpHmDir, DWORD *upHomeSignal, DWORD *upZphas, double *dpHomeClrTime, double *dpHomeOffset);


// Set Home Search Fine tunning Method (Don't care Setting by default).
// dHomeDogDistance[500 pulse]: Set Dog Length. (Unit = AxmMotSetMoveUnitPerPulse function Setting Unit)
// lLevelScanTime[100msec]: Set level status confirmation scan time. (msec[1~1000])
// dwFineSearchUse[USE]: Select find search method. (Default use 5Step, Select 0 use 3Step)
// dwHomeClrUse[USE]: Set After Home Search Automatically Command/Actual Position Set 0 value of  specific axis.
DWORD   __stdcall AxmHomeSetFineAdjust(long lAxisNo, double dHomeDogLength, long lLevelScanTime, DWORD uFineSearchUse, DWORD uHomeClrUse);
// Return set Home  Search fine tunning Method parameters related to home.
DWORD   __stdcall AxmHomeGetFineAdjust(long lAxisNo, double *dpHomeDogLength, long *lpLevelScanTime, DWORD *upFineSearchUse, DWORD *upHomeClrUse);

DWORD   __stdcall AxmHomeSetInterlock(long lAxisNo, DWORD uInterlockMode, double dInterlockData);
DWORD   __stdcall AxmHomeGetInterlock(long lAxisNo, DWORD *upInterlockMode, double *dpInterlockData);


// Detect through several steps in order to detect origin quickly and precisely. Now, set velocities to be used for each step.
// The time of origin detecting and the accuracy of origin detecting are decided by setting of these velocities.
// Set velocity of origin detecting of each axis by changing velocities of each step.
// (Refer the guide part of AxmMotSaveParaAll for detail information.)
// API which sets velocity to be used in origin detecting.
// [dVelFirst]- 1st move velocity   [dVelSecond]- velocity after detecting   [dVelThird]- the last velocity  [dvelLast]- index detecting and in order to detect precisely.
// [dAccFirst]- 1st move acceleration [dAccSecond]-acceleration after detecting.
DWORD    __stdcall AxmHomeSetVel(long lAxisNo, double dVelFirst, double dVelSecond, double dVelThird, double dVelLast, double dAccFirst, double dAccSecond);
// Return set velocity to be used in origin detecting.
DWORD    __stdcall AxmHomeGetVel(long lAxisNo, double *dpVelFirst, double *dpVelSecond, double *dpVelThird, double *dpVelLast, double *dpAccFirst, double *dpAccSecond);


// Start to detect origin.
// When origin detecting start API is executed, thread which will detect origin of relevant axis in the library is created automatically and it is automatically closed after carrying out of the origin detecting in sequence.
DWORD    __stdcall AxmHomeSetStart(long lAxisNo);
// User sets the result of origin detecting optionally.
// When detecting of origin is completed successfully by using origin detecting API, result of detecting is set as HOME_SUCCESS.
// This API enables user to set result optionally without execution of origin detecting.
// uHomeResult Setup
// HOME_SUCCESS               = 0x01,
// HOME_SEARCHING             = 0x02,
// HOME_ERR_GNT_RANGE         = 0x10, // Gantry Home Range Over
// HOME_ERR_USER_BREAK        = 0x11, // User Stop Command
// HOME_ERR_VELOCITY          = 0x12, // Velocity is very slow and fast
// HOME_ERR_AMP_FAULT         = 0x13, // Servo Drive Alarm
// HOME_ERR_NEG_LIMIT         = 0x14, // (+)Limit sensor check (-)dir during Motion
// HOME_ERR_POS_LIMIT         = 0x15, // (-)Limit sensor check (+)dir during Motion
// HOME_ERR_NOT_DETECT        = 0x16, // not detect User set signal
// HOME_ERR_UNKNOWN           = 0xFF,
DWORD    __stdcall AxmHomeSetResult(long lAxisNo, DWORD uHomeResult);
// Return result of origin detecting.
// Verify detecting result of origin detection API. When detecting of origin is started, it sets as HOME_SEARCHING, and if the detecting of origin is failed the reason of failure is set. Redo origin detecting after eliminating of failure reasons.
DWORD    __stdcall AxmHomeGetResult(long lAxisNo, DWORD *upHomeResult);


// Return progress rate of origin detection.
// Progress rate can be verified when origin detection is commenced. When origin detection is completed, return 100% whether success or failure. The success or failure of origin detection result can be verified by using GetHome Result API.
// upHomeMainStepNumber : Progress rate of Main Step .
// In case of gentry FALSE upHomeMainStepNumber : When 0 , only selected axis is in proceeding, home progress rate is indicated upHomeStepNumber.
// In case of gentry TRUE upHomeMainStepNumber : When 0, master home is in proceeding, master home progress rate is indicated upHomeStepNumber.
// In case of gentry TRUE upHomeMainStepNumber : When 10 , slave home is in proceeding, master home progress rate is indicated upHomeStepNumber .
// upHomeStepNumber     : Indicate progress rate against to selected axis.
// In case of gentry FALSE  : Indicate progress rate against to selected axis only.
// In case of gentry TRUE, progress rate is indicated by sequence of master axis and slave axis.
DWORD    __stdcall AxmHomeGetRate(long lAxisNo, DWORD *upHomeMainStepNumber, DWORD *upHomeStepNumber);




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
DWORD    __stdcall AxmMoveStartPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel);


// Travel up to set distance or position.
// It moves by set velocity and acceleration up to the position set by absolute coordinates/ relative coordinates of specific axis.
// Velocity profile is set in AxmMotSetProfileMode API
// It separates from API at the timing of pulse output finish.
DWORD    __stdcall AxmMovePos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel);


// Move by set velocity.
// It maintain velocity mode move by velocity and acceleration  set against to specific axis.
// It separates from API at the timing of pulse output start.
// It moves toward to CW direction when Vel value is positive, CCW when negative.
DWORD    __stdcall AxmMoveVel(long lAxisNo, double dVel, double dAccel, double dDecel);


// It maintain velocity mode move by velocity and acceleration  set against to specific multi-axis.
// It separates from API at the timing of pulse output start.
// It moves toward to CW direction when Vel value is positive, CCW when negative.
DWORD    __stdcall AxmMoveStartMultiVel(long lArraySize, long *lpAxesNo, double *dpVel, double *dpAccel, double *dpDecel);

// Driving set velocity and acceleration rate of specified multi axis.
// Driving speed mode consistently according to SyncMode.
// It separates from API at the timing of pulse output start.
// It moves toward to CW direction when Vel value is positive, CCW when negative.
// dwSyncMode : Disable synchronous stop function(0), Only use syncronous stop function(1), Use Synchronous stop function for alarm(2)
DWORD    __stdcall AxmMoveStartMultiVelEx(long lArraySize, long *lpAxesNo, double *dpVel, double *dpAccel, double *dpDecel, DWORD dwSyncMode);


// Driving in continuous speed mode with set speed and acceleration rate about specified multi axis.
// It separates from API at the timing of pulse output finish. The master axis moves at dVel speed, move at distance ratio of remaining axes.
// Only velocity of lowest axis number is read among corresponding chip.
DWORD    __stdcall AxmMoveStartLineVel(long lArraySize, long *lpAxesNo, double *dpDis, double dVel, double dAccel, double dDecel);


// API which detects Edge of specific Input signal and makes emergency stop or slowdown stop.
// lDetect Signal : Select input signal to detect .
// lDetectSignal  : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
// Signal Edge   : Select edge direction of selected input signal (rising or falling edge).
//                  SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
// Move direction      : CW when Vel value is positive, CCW when negative.
// SignalMethod  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// Caution: When SignalMethod is used as EMERGENCY_STOP(0), acceleration/deceleration is ignored and it is accelerated to specific velocity and emergency stop.
//          lDetectSignal is PosEndLimit , in case of searching NegEndLimit(0,1) active status of signal level is detected.
DWORD    __stdcall AxmMoveSignalSearch(long lAxisNo, double dVel, double dAccel, long lDetectSignal, long lSignalEdge, long lSignalMethod);


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
DWORD    __stdcall AxmMoveSignalSearchAtDis(long lAxisNo, double dVel, double dAccel, double dDecel, long lDetectSignal, double dDis);


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
DWORD    __stdcall AxmMoveSignalCapture(long lAxisNo, double dVel, double dAccel, long lDetectSignal, long lSignalEdge, long lTarget, long lSignalMethod);

// API which verifies saved position value in 'AxmMoveSignalCapture' API.
DWORD    __stdcall AxmMoveGetCapturePos(long lAxisNo, double *dpCapPotition);


// API which travels up to set distance or position.
// When execute API, it starts relevant motion action and escapes from API without waiting until motion is completed ”
DWORD    __stdcall AxmMoveStartMultiPos(long lArraySize, long *lpAxisNo, double *dpPos, double *dpVel, double *dpAccel, double *dpDecel);


// Travels up to the distance which sets multi-axis or position.
// It moves by set velocity and acceleration up to the position set by absolute coordinates of specific axis. specific axes.
DWORD    __stdcall AxmMoveMultiPos(long lArraySize, long *lpAxisNo, double *dpPos, double *dpVel, double *dpAccel, double *dpDecel);



// When execute API, it starts open-loop torque motion action of specific axis.(only for MLII, Sigma 5 servo drivers)
// dTroque        : Percentage value(%) of maximum torque. (negative value : CCW, positive value : CW)
// dVel           : Percentage value(%) of maximum velocity.
// dwAccFilterSel : LINEAR_ACCDCEL(0), EXPO_ACCELDCEL(1), SCURVE_ACCELDECEL(2)
// dwGainSel      : GAIN_1ST(0), GAIN_2ND(1)
// dwSpdLoopSel   : PI_LOOP(0), P_LOOP(1)
DWORD    __stdcall AxmMoveStartTorque(long lAxisNo, double dTorque, double dVel, DWORD dwAccFilterSel, DWORD dwGainSel, DWORD dwSpdLoopSel);


// It stops motion during torque motion action.
// it can be only applied for AxmMoveStartTorque API.
DWORD    __stdcall AxmMoveTorqueStop(long lAxisNo, DWORD dwMethod);



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
DWORD    __stdcall AxmMoveStartPosWithList(long lAxisNo, double dPosition, double *dpVel, double *dpAccel, double *dpDecel, long lListNum);



// Is set by the distance to the target axis position or the position to increase or decrease the movement begins.
// lEvnetAxisNo    : Start condition occurs axis.
// dComparePosition: Conditions Occurrence Area of Start condition occurs axis.
// uPositionSource : Set Conditions Occurrence Area of Start condition occurs axis => COMMAND(0), ACTUAL(1)
// Cancellations after reservation AxmMoveStop, AxmMoveEStop, AxmMoveSStop use
// Motion Axis and Start condition occurs axis must be In same group(case by 2V04 In same module).
DWORD    __stdcall AxmMoveStartPosWithPosEvent(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, long lEventAxisNo, double dComparePosition, DWORD uPositionSource);


// It slowdown stops by deceleration set for specific axis.
// dDecel : Deceleration value when stop.
DWORD    __stdcall AxmMoveStop(long lAxisNo, double dDecel);
// It slowdown stops by deceleration set for specific axis.(PCI-Nx04 Only)
// This API can decelerating immediately refardless of current acceleration/deceleration state. Also, it can be used for limited drive.
// -- Applicable functions : AxmMoveStartPos, AxmMoveVel, AxmLineMoveEx2.
// dDecel : Deceleration rate value at stop.
// Note : Deceleration rate value should be greater than or equal to deceleration rate of initial setting.
// Note : When deceleration setting is set to time unit, It must be less than or equal to initial settling time.
DWORD    __stdcall AxmMoveStopEx(long lAxisNo, double dDecel);
// Stops specific axis emergently .
DWORD    __stdcall AxmMoveEStop(long lAxisNo);
// Stops specific axis slow down.
DWORD    __stdcall AxmMoveSStop(long lAxisNo);


//========= Overdrive API ============================================================================
// Overdrives position.
// Adjust number of specific pulse before the move of specific axis is finished.
// Cautions : In here when put in the position subjected to overdrive, as the travel distance is put into the position value of relative form,
//            position must be put in as position value of relative form.
DWORD    __stdcall AxmOverridePos(long lAxisNo, double dOverridePos);


// Set the maximum velocity subjected to overdirve before velocity overdriving of specific axis.
// Caution : If the velocity overdrive is done 5 times, the max velocity shall be set among them.
DWORD    __stdcall AxmOverrideSetMaxVel(long lAxisNo, double dOverrideMaxVel);

// Overdrive velocity.
// Set velocity variably during the move of specific axis. (Make sure to set variably during the motion.)
// Caution: Before use of AxmOverrideVel API, set the maximum velocity which can be set by AxmOverrideMaxVel
// EX> If velocity overdrive two times,
// 1. Set the highest velocity among the two as the highest setting velocity of AxmOverrideMaxVel.
// 2. Set the AxmOverrideVel  variably with the velocity in the moving of AxmMoveStartPos execution specific axis (including move API all) as the first velocity.
// 3. Set the AxmOverrideVel  variably with the velocity in the moving of specific axis (including move API all) as the 2nd velocity.
DWORD    __stdcall AxmOverrideVel(long lAxisNo, double dOverrideVel);

// Overdrive velocity.
// Set velocity variably during the move of specific axis. (Make sure to set variably during the motion.)
// Caution: Before use of AxmOverrideVel API, set the maximum velocity which can be set by AxmOverrideMaxVel
// EX> If velocity overdrive two times,
// 1. Set the highest velocity among the two as the highest setting velocity of AxmOverrideMaxVel.
// 2. Set the AxmOverrideAccelVelDecel  variably with the velocity in the moving of AxmMoveStartPos execution specific axis (including move API all) as the first velocity.
// 3. Set the AxmOverrideAccelVelDecel  variably with the velocity in the moving of specific axis (including move API all) as the 2nd velocity.
DWORD    __stdcall AxmOverrideAccelVelDecel(long lAxisNo, double dOverrideVelocity, double dMaxAccel, double dMaxDecel);

// Velocity overdrive at certain timing.
// API which becomes overdrive at the position when a certain position point and velocity to be overdrived
// lTarget : COMMAND(0), ACTUAL(1)
DWORD    __stdcall AxmOverrideVelAtPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel,double dOverridePos, double dOverrideVel, long lTarget);
// Override with specified velocity at specified times.
// lArraySize     : Set number of positions to override.
// *dpOverridePos : An array of positions to override. (It should be greater than or equal to set value at lArraySize.)
// *dpOverrideVel : Velocity array to be changed at position to override. (It should be greater than or equal to set value at lArraySize.)
// lTarget        : COMMAND(0), ACTUAL(1)
// dwOverrideMode : Specify how to start overriding.
//                : OVERRIDE_POS_START(0) - Start override at specified velocity at specified position.
//                : OVERRIDE_POS_END(1)   - Start override in advance to become specified velocity at specified position.
DWORD    __stdcall AxmOverrideVelAtMultiPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, long lArraySize, double* dpOverridePos, double* dpOverrideVel, long lTarget, DWORD dwOverrideMode);

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
DWORD    __stdcall AxmOverrideVelAtMultiPos2(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, long lArraySize, double* dpOverridePos, double* dpOverrideVel, double* dpOverrideAccelDecel, long lTarget, DWORD dwOverrideMode);

// In Electric Gear mode, set gear ratio between master axis and slave axis.
// dSlaveRatio : Gear ratio of slave against to master axis ( 0 : 0% , 0.5 : 50%, 1 : 100%)
DWORD    __stdcall AxmLinkSetMode(long lMasterAxisNo, long lSlaveAxisNo, double dSlaveRatio);
// In Electric Gear mode, return gear ratio between master axis and slave axis.
DWORD    __stdcall AxmLinkGetMode(long lMasterAxisNo, long *lpSlaveAxisNo, double *dpGearRatio);
// Reset electric gear ration between Master axis and slave axis.
DWORD    __stdcall AxmLinkResetMode(long lMasterAxisNo);


//======== API related to gentry ===========================================================================================================================================================
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
DWORD    __stdcall AxmGantrySetEnable(long lMasterAxisNo, long lSlaveAxisNo, DWORD uSlHomeUse, double dSlOffset, double dSlOffsetRange);



// The method to know offset value of Slave axis.
// A. Servo-On both master and slave.
// B. After set uSlHomeUse = 2 in AxmGantrySetEnableAPI, then search home by using  AxmHomeSetStart API.
// C. After search home, twisted offset value of master axis and slave axis can be seen by reading command value of master axis.
// D. Read Offsetvalue, and put it into dSlOffset argument of AxmGantrySetEnable API.
// E. As dSlOffset value is the slave axis value against to master axis, put its value with reversed sign as ?dSlOffset.
// F. dSIOffsetRange means the range of Slave Offset, it is used to originate error when it is out of the specified range.
// G. If the offset has been input into AxmGantrySetEnable API, in AxmGantrySetEnable API,after  set uSlHomeUse = 1 then search home by using AxmHomeSetStart API.

// In gentry move, return parameter set by user.
DWORD    __stdcall AxmGantryGetEnable(long lMasterAxisNo, DWORD *upSlHomeUse, double *dpSlOffset, double *dpSlORange, DWORD *upGatryOn);
// Motion module releases gentry move system control which two axes are linked mechanically.
DWORD    __stdcall AxmGantrySetDisable(long lMasterAxisNo, long lSlaveAxisNo);


// Only for PCI-Rxx04-MLII.
// Set Synchronous compensation of Gentry System.
// lMasterGain, lSlaveGain : Set % value of Between the two axes about position deviation.
// lMasterGain, lSlaveGain : If Set Input 0 Not Use. Default value : 0%
DWORD    __stdcall AxmGantrySetCompensationGain(long lMasterAxisNo, long lMasterGain, long lSlaveGain);
// Return Synchronous compensation of Gentry System.
DWORD    __stdcall AxmGantryGetCompensationGain(long lMasterAxisNo, long *lpMasterGain, long *lpSlaveGain);


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
DWORD   __stdcall AxmGantrySetErrorRange(long lMasterAxisNo, double dErrorRange, DWORD uUse);
// Return setting value about position deviation range between master and slave.
DWORD   __stdcall AxmGantryGetErrorRange(long lMasterAxisNo, double *dpErrorRange, DWORD *upUse);
// Return result of comparing position deviation value between master and slave.
// dwpStatus : FALSE(0) -> Range of position deviation between master and slave is less than setting range. (Normal state)
//             TRUE(1)  -> Range of position deviation between master and slave is greater than setting range. (Abnormal state)
// It is returned 'AXT_RT_SUCCESS' only when Gantry Enable && Master/Slave's servo on state is satisfied.
// Call the 'AxmGantryReadErrorRangeComparePos', if you want to reset Latch Flag in case of latch mode.
DWORD   __stdcall AxmGantryReadErrorRangeStatus(long lMasterAxisNo, DWORD *dwpStatus);
// Return position deviation value between master and slave.
// Maintain position deviation value at time of previous error occurrence until next error is occured.
// You should read only when 'dwpStatus' is 1. If you read ComparePos continuously, response speed will be slowed down by overload.
DWORD   __stdcall AxmGantryReadErrorRangeComparePos(long lMasterAxisNo, double *dpComparePos);





//==== Regular interpolation API ============================================================================================================================================;
// Do linear interpolate.
// API which moves multi-axis linear interpolation by specifying start point and ending point. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the queue which moves linear interpolation by specifying start point and ending point in the specified  coordinates system.
// For the continuous interpolation move of linear profile, save it in internal queue and start by using AxmContiStart API.
DWORD    __stdcall AxmLineMove(long lCoord, double *dpEndPos, double dVel, double dAccel, double dDecel);


// Do linear interpolate. (Software)
// API which moves multi-axis linear interpolation by specifying start point and ending point. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the queue which moves linear interpolation by specifying start point and ending point in the specified  coordinates system.
// For the continuous interpolation move of linear profile, save it in internal queue and start by using AxmContiStart API.
DWORD    __stdcall AxmLineMoveEx2(long lCoord, double *dpEndPos, double dVel, double dAccel, double dDecel);


// Interpolate 2 axis arc
// API which moves arc interpolation by specifying start point, ending point and center point. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying start point, ending point and center point in the specified  coordinates system.
// For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
// lAxisNo = 2 axis array , dCenterPos = center point X,Y array , dEndPos = ending point X,Y array.
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
DWORD   __stdcall AxmCircleCenterMove(long lCoord, long *lAxisNo, double *dCenterPos, double *dEndPos, double dVel, double dAccel, double dDecel, DWORD uCWDir);


// API which arc interpolation moves by specifying middle point and ending point. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying middle point and ending point in the specified  coordinates system.
// For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
// lAxisNo = 2 axis array , dMidPos = middle point, X,Y array , dEndPos = ending point X,Y array, lArcCircle = arc(0), circle(1)
DWORD    __stdcall AxmCirclePointMove(long lCoord, long *lAxisNo, double *dMidPos, double *dEndPos, double dVel, double dAccel, double dDecel, long lArcCircle);


DWORD    __stdcall AxmCirclePointMoveEx(long lCoordNo, long *lAxisNo, double *dpMidPos, double *dpEndPos, double dVel, double dAccel, double dDecel, long lArcCircle, long lArraySize);


// API which arc interpolation moves by specifying start point, ending point and radius. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying start point, ending point and radius in the specified  coordinates system.
// For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
// lAxisNo = 2 axis array , dRadius = radius, dEndPos = ending point X,Y array , uShortDistance = small circle(0), large circle(1)
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
DWORD   __stdcall AxmCircleRadiusMove(long lCoord, long *lAxisNo, double dRadius, double *dEndPos, double dVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance);


// API which arc interpolation moves by specifying start point, revolution angle and radius. It escapes from API after commencing of move.
// When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying start point, revolution angle and radius in the specified  coordinates system.
// For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
// lAxisNo = 2 axis array , dCenterPos = center point X,Y array , dAngle = angle.
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
DWORD   __stdcall AxmCircleAngleMove(long lCoord, long *lAxisNo, double *dCenterPos, double dAngle, double dVel, double dAccel, double dDecel, DWORD uCWDir);


//==== continuous interpolation API ============================================================================================================================================;
//Set continuous interpolation axis mapping in specific coordinates system.
//(Start axis mapping number from 0)
// Caution: In the axis mapping, the input must be started from smaller number.
//         In here, the axis of smallest number becomes master.
DWORD    __stdcall AxmContiSetAxisMap(long lCoord, long lSize, long *lpAxesNo);
// Return continuous interpolation axis mapping in specific coordinates system.
DWORD    __stdcall AxmContiGetAxisMap(long lCoord, long *lpSize, long *lpAxesNo);
// Reset continuous interpolation axis mapping in specific coordinates system.
DWORD    __stdcall AxmContiResetAxisMap(long lCoordinate);


// Set continuous interpolation axis absolute/relative mode in specific coordinates system.
// (Caution : available to use only after axis mapping)
// St travel distance calculation mode of specific axis.
//uAbsRelMode : POS_ABS_MODE '0' - absolute coordinate system
//              POS_REL_MODE '1' - relative coordinate system
DWORD    __stdcall AxmContiSetAbsRelMode(long lCoord, DWORD uAbsRelMode);
// Return interpolation axis absolute/relative mode in specific coordinates system.
DWORD    __stdcall AxmContiGetAbsRelMode(long lCoord, DWORD *upAbsRelMode);


// API which verifies whether internal Queue for the interpolation move is empty in specific coordinate system.
DWORD    __stdcall AxmContiReadFree(long lCoord, DWORD *upQueueFree);
// API which verifies the number of interpolation move saved in internal Queue for the interpolation move in specific coordinate system
DWORD    __stdcall AxmContiReadIndex(long lCoord, long *lpQueueIndex);

// API which deletes all internal Queue saved for the continuous interpolation move in specific coordinate system
DWORD    __stdcall AxmContiWriteClear(long lCoord);


// Start registration of tasks to be executed in continuous interpolation at the specific  coordinate system. After call this API,
// all motion tasks to be executed before calling of AxmContiEndNode API are not execute actual motion, but are registered as continuous interpolation motion,
// and when AxmContiStart API is called, then the registered motions execute actually
DWORD    __stdcall AxmContiBeginNode(long lCoord);
// Finish registration of tasks to be executed in continuous interpolation at the specific  coordinate system.
DWORD    __stdcall AxmContiEndNode(long lCoord);


// Start continuous interpolation.
// if dwProfileset is  CONTI_NODE_VELOCITY(0), use continuous interpolation.
//                     CONTI_NODE_MANUAL(1)  , set profile interpolation use.
//                     CONTI_NODE_AUTO(2)    , use auto-profile interpolation.
DWORD    __stdcall AxmContiStart(long lCoord, DWORD dwProfileset, long lAngle);
// API which verifies whether the continuous interpolation is moving in the specific coordinate system.
DWORD    __stdcall AxmContiIsMotion(long lCoord, DWORD *upInMotion);


// API which verifies the index number of the continuous interpolation that is being moving currently while the continuous interpolation is moving in the specific coordinate system.
DWORD    __stdcall AxmContiGetNodeNum(long lCoord, long *lpNodeNum);
// API which verifies the total number of continuous interpolation index that were set in  the specific coordinate system.
DWORD    __stdcall AxmContiGetTotalNodeNum(long lCoord, long *lpNodeNum);



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
DWORD    __stdcall AxmContiDigitalOutputBit(long lCoord, long lSize, long lModuleType, long* lpModuleNo, long* lpBit, long* lpOffOn, double* dpDistTime, long* lpDistTimeMode);


DWORD    __stdcall AxmContiReadStop(long lCoord, DWORD *upStatus);

DWORD    __stdcall AxmContiSetLineMoveVelMode(long lCoord, DWORD uVelMode, long lMasterAxisNo);
DWORD    __stdcall AxmContiGetLineMoveVelMode(long lCoord, DWORD *upVelMode, long *lpMasterAxisNo);

DWORD    __stdcall AxmContiSetCheckSoftLimit(long lCoord, DWORD uUse);
DWORD    __stdcall AxmContiGetCheckSoftLimit(long lCoord, DWORD *upUse);

DWORD    __stdcall AxmContiSetConnectionRadius(long lCoord, double dRadius);
DWORD    __stdcall AxmContiSetConnectionMaxCentripetalAccel(long lCoord, double dMaxAccel);


//==================== trigger API ===============================================================================================================================
// Precautions : If you want set trigger position, you should be set according to setting status of Unit/Pulse.
//               If trigger position unit is smaller than Unit/Pulse, you can't output to desired position exactly because minimum unit will be set to UNIT/PULSE.

// Set whether to use of trigger function, output level, position comparator, trigger signal delay time and trigger output mode ino specific axis.
//  dTrigTime  : trigger output time
//             : 1usec - max 50msec ( set 1 - 50000)
//  upTriggerLevel  : whether to use or not use => LOW(0), HIGH(1), UNUSED(2), USED(3)
//  uSelect         : Standard position to use  => COMMAND(0), ACTUAL(1)
//  uInterrupt      : set interrupt             => DISABLE(0), ENABLE(1)

// Set trigger signal delay time , trigger output level and trigger output method in specific axis.
DWORD    __stdcall AxmTriggerSetTimeLevel(long lAxisNo, double dTrigTime, DWORD uTriggerLevel, DWORD uSelect, DWORD uInterrupt);
// Return trigger signal delay time , trigger output level and trigger output method to specific axis.
DWORD    __stdcall AxmTriggerGetTimeLevel(long lAxisNo, double *dpTrigTime, DWORD *upTriggerLevel, DWORD *upSelect, DWORD *upInterrupt);


//  uMethod :   PERIOD_MODE   0x0 : cycle trigger method using trigger position value
//              ABS_POS_MODE   0x1 : Trigger occurs at trigger absolute position,  absolute position method
//  dPos : in case of cycle selection : the relevant position  for output by position and position.
// in case of absolute selection: The position on which to output, If same as this position then output goes out unconditionally.
DWORD    __stdcall AxmTriggerSetAbsPeriod(long lAxisNo, DWORD uMethod, double dPos);
// Return whether to use of trigger function, output level, position comparator, trigger signal delay time and trigger output mode to specific axis.
DWORD    __stdcall AxmTriggerGetAbsPeriod(long lAxisNo, DWORD *upMethod, double *dpPos);


//  Output the trigger by regular interval from the starting position to the ending position specified by user.
DWORD    __stdcall AxmTriggerSetBlock(long lAxisNo, double dStartPos, double dEndPos, double dPeriodPos);
// Read trigger setting value of 'AxmTriggerSetBlock' API.
DWORD    __stdcall AxmTriggerGetBlock(long lAxisNo, double *dpStartPos, double *dpEndPos, double *dpPeriodPos);


// User outputs a trigger pulse.
DWORD    __stdcall AxmTriggerOneShot(long lAxisNo);
// User outputs a trigger pulse after several seconds.
DWORD    __stdcall AxmTriggerSetTimerOneshot(long lAxisNo, long lmSec);
// Output absolute position trigger infinite absolute position output.
DWORD    __stdcall AxmTriggerOnlyAbs(long lAxisNo,long lTrigNum, double* dpTrigPos);
// Reset trigger settings.
DWORD    __stdcall AxmTriggerSetReset(long lAxisNo);


//======== CRC( Remaining pulse clear API) =====================================================================
//Level   : LOW(0), HIGH(1), UNUSED(2), USED(3)
//uMethod : Available to set the width of remaining pulse eliminating output signal pulse in 2 - 6.
//          0: Don't care , 1: Don't care, 2: 500 uSec, 3:1 mSec, 4:10 mSec, 5:50 mSec, 6:100 mSec
//Set whether to use CRC signal in specific axis and output level.
DWORD    __stdcall AxmCrcSetMaskLevel(long lAxisNo, DWORD uLevel, DWORD uMethod);
// Return whether to use CRC signal of specific axis and output level.
DWORD    __stdcall AxmCrcGetMaskLevel(long lAxisNo, DWORD *upLevel, DWORD *upMethod);


//uOnOff  : Whether to generate CRC signal to the Program or not.  (FALSE(0),TRUE(1))
// Force to generate CRC signal to the specific axis.
DWORD    __stdcall AxmCrcSetOutput(long lAxisNo, DWORD uOnOff);
// Return whether to forcedly generate CRC signal of specific axis.
DWORD    __stdcall AxmCrcGetOutput(long lAxisNo, DWORD *upOnOff);



//====== MPG(Manual Pulse Generation) API ===========================================================
// lInputMethod : Available to set 0-3. 0:OnePhase, 1:TwoPhase1, 2:TwoPhase2, 3:TwoPhase4
// lDriveMode   : Available to set 0-5
//                0 :MPG continuous mode,             1 :MPG PRESET mode (Travel up to specific pulse), 2 :COMMAND ABSOLUTE MPG PRESET mode
//                3 :ACTUAL ABSOLUTE MPG PRESET mode, 4 :COMMAND ABSOLUTE ZERO MPG PRESET mode,         5 :ACTUAL ABSOLUTE ZERO MPG PRESET mode
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
DWORD    __stdcall AxmMPGSetEnable(long lAxisNo, long lInputMethod, long lDriveMode, double dMPGPos, double dVel, double dAccel);
// Return MPG input method, Drive move mode, travel distance, MPG velocity in specific axis.
DWORD    __stdcall AxmMPGGetEnable(long lAxisNo, long *lpInputMethod, long *lpDriveMode, double *dpMPGPos, double *dpVel, double *dAccel);


// Set the pulse ratio to travel per pulse in MPG drive move mode to specific axis.
DWORD    __stdcall AxmMPGSetRatio(long lAxisNo, DWORD uMPGnumerator, DWORD uMPGdenominator);
// Return the pulse ratio to travel per pulse in MPG drive move mode to specific axis.
DWORD    __stdcall AxmMPGGetRatio(long lAxisNo, DWORD *upMPGnumerator, DWORD *upMPGdenominator);

// Release MPG drive settings to specific axis.
DWORD    __stdcall AxmMPGReset(long lAxisNo);



//======= Helical move ===========================================================================
// API which moves helical interpolation by specifying start point, ending point and center point to specific coordinate system.
// API which moves helical continuous interpolation by specifying start point, ending point and center point to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
// API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
//dCenterPos = center point X,Y , dEndPos = ending point X,Y.
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
DWORD    __stdcall AxmHelixCenterMove(long lCoord, double dCenterXPos, double dCenterYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dAccel, double dDecel, DWORD uCWDir);


// API which moves helical interpolation by specifying start point, ending point and radius to specific coordinate system.
// API which moves helical continuous interpolation by specifying middle point and ending point to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
// API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
// dMidPos = middle point X,Y  , dEndPos = ending point X,Y
DWORD    __stdcall AxmHelixPointMove(long lCoord, double dMidXPos, double dMidYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dAccel, double dDecel);


// API which moves helical interpolation by specifying start point, ending point and radius to specific coordinate system.
// API which moves helical continuous interpolation by specifying middle point ,ending point and radius to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
// API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
// dRadius = radius, dEndPos = ending point X,Y  , uShortDistance = small circle(0), large circle(1)
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
DWORD    __stdcall AxmHelixRadiusMove(long lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance);


// API which moves helical interpolation by specifying start point, revolution angle and radius to specific coordinate system.
// API which moves helical continuous interpolation by specifying start point , revolution angle and radius to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
// API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
// dCenterPos = center point X,Y , dAngle = angle.
// uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
DWORD    __stdcall AxmHelixAngleMove(long lCoord, double dCenterXPos, double dCenterYPos, double dAngle, double dZPos, double dVel, double dAccel, double dDecel, DWORD uCWDir);



//======== Spline move ===========================================================================
// It’s not used with AxmContiBeginNode and AxmContiEndNode together.
// API which moves spline continuous interpolation. API which saves in internal Queue in order to move the arc continuous interpolation.
//It is started using AxmContiStart API. ( It is used with continuous interpolation API together)

// lPosSize : Minimum more than 3 pieces.
// Enter 0 as for dPoZ value when it is used with 2 axes.
// Enter 3 piece as for axis mapping and dPosZ value when it is used with 3axes.
DWORD    __stdcall AxmSplineWrite(long lCoord, long lPosSize, double *dpPosX, double *dpPosY, double dVel, double dAccel, double dDecel, double dPosZ, long lPointFactor);


//======== Compensation Table ====================================================================
// API which set the parameters for using the geometric compensation feature (Mechatrolink-II products)
// lNumEntry : minimum entries are 2, maximum entries are 512.
// dStartPos : starting relative position to apply the compensation.
// dpPosition, dpCorrection : arrays of position and correction values.
// bRollOver : enable/disable the roll over feature if the table can not cover the motor travel distance.
DWORD __stdcall AxmCompensationSet(long lAxisNo, long lNumEntry, double dStartPos, double *dpPosition, double *dpCorrection, DWORD dwRollOver);
// Return the number of entry, start position, array of position for moving, array of correction for compensating, setting RollOver feature on specific axis.
DWORD __stdcall AxmCompensationGet(long lAxisNo, long *lpNumEntry, double *dpStartPos, double *dpPosition, double *dpCorrection, DWORD *dwpRollOver);

// API which enable/disable the compensation feature.
DWORD __stdcall AxmCompensationEnable(long lAxisNo, DWORD dwEnable);
// Return the setting enable/disable the compensation feature on specific axis.
DWORD __stdcall AxmCompensationIsEnable(long lAxisNo, DWORD *dwpEnable);
// Return Current Position Compensation Value
DWORD __stdcall AxmCompensationGetCorrection(long lAxisNo, double *dpCorrection);

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
DWORD __stdcall AxmCompensationSetBacklash(long lAxisNo, long lBacklashDir, double dBacklash);
// Returns the configuration related to backlash.
DWORD __stdcall AxmCompensationGetBacklash(long lAxisNo, long *lpBacklashDir, double *dpBacklash);
// Function to set / check whether to use backlash
// > dwEnable: Specify whether to use backlash compensation
//   - [0]DISABLE -> Disable backlash compensation
//   - [1]ENABLE  -> Enable backlash compensation
// { RETURN VALUE }
//   - [0]    -> Backlash setting When return is successful
//   - [4303] -> When the backlash compensation function is not set
DWORD __stdcall AxmCompensationEnableBacklash(long lAxisNo, DWORD dwEnable);
DWORD __stdcall AxmCompensationIsEnableBacklash(long lAxisNo, DWORD *dwpEnable);
// When backlash compensation function is used, it moves left and right by the amount of backlash to automatically align the position of the equipment (used once after servo-on)
// > dVel: Movement speed[unit / sec]
// > dAccel: Movement acceleration[unit / sec^2]
// > dAccel: Movement deceleration[unit / sec^2]
// > dWaitTime: Waiting time to return to original position after driving backlash amount[msec]
// { RETURN VALUE }
//   - [0]    -> When positioning for backlash compensation is successful
//   - [4303] -> When the backlash compensation function is not set
DWORD __stdcall AxmCompensationSetLocating(long lAxisNo, double dVel, double dAccel, double dDecel, double dWaitTime);


//======== Electronic CAM ========================================================================
// API which set the parameters for using the Ecam feature (Mechatrolink-II products)
// lAxisNo : one slave axis only has one master axis.
// lMasterAxis : one master axis can have more than one slave axis.
// lNumEntry : minimum entries are 2, maximum entries are 512.
// dMasterStartPos : starting relative position to apply Ecam on master axis.
// dpMasterPos, dpSlavePos : arrays of position values on master and slave axis.
DWORD __stdcall AxmEcamSet(long lAxisNo, long lMasterAxis, long lNumEntry, double dMasterStartPos, double *dpMasterPos, double *dpSlavePos);
// Ecam Set With Select Source (COMMAND :0, ACTUAL : 1)
DWORD __stdcall AxmEcamSetWithSource(long lAxisNo, long lMasterAxis, long lNumEntry, double dMasterStartPos, double *dpMasterPos, double *dpSlavePos, DWORD dwSource);
// Return the number of master axis, entries, start position of master axis, array of position on master axis, array of position on slave axis.
DWORD __stdcall AxmEcamGet(long lAxisNo, long *lpMasterAxis, long *lpNumEntry, double *dpMasterStartPos, double *dpMasterPos, double *dpSlavePos);
// Ecam Get With Select Source
DWORD __stdcall AxmEcamGetWithSource(long lAxisNo, long *lpMasterAxis, long *lpNumEntry, double *dpMasterStartPos, double *dpMasterPos, double *dpSlavePos, DWORD *dwpSource);

// API which enable the Ecam feature on slave axis.
DWORD __stdcall AxmEcamEnableBySlave(long lAxisNo, DWORD dwEnable);
// Return the setting enable/disable the Ecam feature on slave axis.
DWORD __stdcall AxmEcamEnableByMaster(long lAxisNo, DWORD dwEnable);
// API which enable the Ecam feature on corresponding slave axes.
DWORD __stdcall AxmEcamIsSlaveEnable(long lAxisNo, DWORD *dwpEnable);


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
DWORD __stdcall AxmStatusSetServoMonitor(long lAxisNo, DWORD dwSelMon, double dActionValue, DWORD dwAction);
// Return exception function of specific axis. (Only for MLII, Sigma-5)
DWORD __stdcall AxmStatusGetServoMonitor(long lAxisNo, DWORD dwSelMon, double *dpActionValue, DWORD *dwpAction);
// Set exception function usage of specific axis. (Only for MLII, Sigma-5)
DWORD __stdcall AxmStatusSetServoMonitorEnable(long lAxisNo, DWORD dwEnable);
// Return exception function usage of specific axis. (Only for MLII, Sigma-5)
DWORD __stdcall AxmStatusGetServoMonitorEnable(long lAxisNo, DWORD *dwpEnable);


// Return exception function execution result Flag of specific axis. Auto reset after function execution. (Only for MLII, Sigma-5)
DWORD __stdcall AxmStatusReadServoMonitorFlag(long lAxisNo, DWORD dwSelMon, DWORD *dwpMonitorFlag, double *dpMonitorValue);
// Return exception function monitoring information of specific axis. (Only for MLII, Sigma-5)
DWORD __stdcall AxmStatusReadServoMonitorValue(long lAxisNo, DWORD dwSelMon, double *dpMonitorValue);
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
DWORD __stdcall AxmStatusSetReadServoLoadRatio(long lAxisNo, DWORD dwSelMon);
// Return load ratio of specific axis. (Only for MLII, Sigma-5)
DWORD __stdcall AxmStatusReadServoLoadRatio(long lAxisNo, double *dpMonitorValue);


//======== Only for PCI-R1604-RTEX ==================================================================================
// Set RTEX A4Nx Scale Coefficient. (Only for RTEX, A4Nx)
DWORD __stdcall AxmMotSetScaleCoeff(long lAxisNo, long lScaleCoeff);
// Return RTEX A4Nx Scale Coefficient. (Only for RTEX, A4Nx)
DWORD __stdcall AxmMotGetScaleCoeff(long lAxisNo, long *lpScaleCoeff);

// Edge detection of specific Input Signal that stop or slow down to stop the function.
// lDetectSignal : Select input signal to detect edge.
//                 PosEndLimit(0), NegEndLimit(1), HomeSensor(4)
// lSignalEdge   : Select edge direction of selected input signal.
//                 SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
// lSignalMethod : Select stop method.
//                 EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
// ※ Move direction : CW(dVel is positive), CCW(dVel is negative)
// ※ Note : Acceleration / deceleration is ignored when lSignalMethod is EMERGENCY_STOP(0), and acceleration suddenly stops at the specified speed.
//          If lDetectSignal is PosEndLimit(0) or NegEndLimit(1) in use PCI-Nx04, the level of the signal active state is detected.
DWORD    __stdcall AxmMoveSignalSearchEx(long lAxisNo, double dVel, double dAccel, long lDetectSignal, long lSignalEdge, long lSignalMethod);

//-------------------------------------------------------------------------------------------------------------------

//======== Only for PCI-R1604-MLII ==================================================================================
// Move to the set absolute position.
// Velocity profile use Trapezoid.
// Exits API at the point that pulse out starts.
// Always position(include -position), Velocity, Accel/Deccel Change possible.
DWORD    __stdcall AxmMoveToAbsPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel);
// Return current drive velocity of specific axis.
DWORD    __stdcall AxmStatusReadVelEx(long lAxisNo, double *dpVel);

//-------------------------------------------------------------------------------------------------------------------

//======== Only for PCI-R1604-SSCNETIIIH ==================================================================================
// Set electric ratio. This parameter saved Non-volatile memory.
// Default value(lNumerator : 4194304(2^22), lDenominator : 10000)
// MR-J4-B is don't Setting electric ratio, Must be set from the host controller.
// No.PA06, No.PA07 of Existing Pulse type Servo Driver(MR-J4-A)
DWORD    __stdcall AxmMotSetElectricGearRatio(long lAxisNo, long lNumerator, long lDenominator);
// Return electric ratio of specific axis.
DWORD    __stdcall AxmMotGetElectricGearRatio(long lAxisNo, long *lpNumerator, long *lpDenominator);


// Set limit torque value of specific axis.
// Forward, Backward drive torque limit function.
// Setting range 1 ~ 1000
// 0.1% of the maximum torque are controlled.
DWORD    __stdcall AxmMotSetTorqueLimit(long lAxisNo, double dbPlusDirTorqueLimit, double dbMinusDirTorqueLimit);


// Return torque limit value of specific axis.
DWORD    __stdcall AxmMotGetTorqueLimit(long lAxisNo, double* dbpPlusDirTorqueLimit, double* dbpMinusDirTorqueLimit);

DWORD    __stdcall AxmMotSetTorqueLimitEx(long lAxisNo, double dbPlusDirTorqueLimit, double dbMinusDirTorqueLimit);

DWORD    __stdcall AxmMotGetTorqueLimitEx(long lAxisNo, double* dbpPlusDirTorqueLimit, double* dbpMinusDirTorqueLimit);


// Sets the torque limit value of the specified axis.
// Limit the torque value during forward and reverse drive.
// The setting range is from 1 to 3000 (0.1% ~ 300.0%).
// It is controlled in 0.1% of maximum torque.
// dPosition : Position information to change the torque limit value (applicable when event with same position information and target position occur).
// lTarget   : COMMAND(0), ACTUAL(1)
DWORD    __stdcall AxmMotSetTorqueLimitAtPos(long lAxisNo, double dbPlusDirTorqueLimit, double dbMinusDirTorqueLimit, double dPosition, long lTarget);


// Get the torque limit value of the specified axis.
DWORD    __stdcall AxmMotGetTorqueLimitAtPos(long lAxisNo, double* dbpPlusDirTorqueLimit, double* dbpMinusDirTorqueLimit, double* dpPosition, long* lpTarget);

DWORD    __stdcall AxmMotSetTorqueLimitEnable(long lAxisNo, DWORD uUse);


DWORD    __stdcall AxmMotGetTorqueLimitEnable(long lAxisNo, DWORD* upUse);

DWORD    __stdcall AxmOverridePosSetFunction(long lAxisNo, DWORD dwUsage, long lDecelPosRatio, double dReserved);
DWORD    __stdcall AxmOverridePosGetFunction(long lAxisNo, DWORD *dwpUsage, long *lpDecelPosRatio, double *dpReserved);


// Controls the digital output value set at a specific position on the specified axis.
// lModuleNo   : Module Number
// lOffset     : Offset position for output contact
// uValue      : OFF(0)
//             : OM(1)
//             : Function Clear(0xFF)
// dPosition   : DO output value is changed (executed when an event occurs in which the position information is the same as the target position).
// lTarget     : COMMAND(0), ACTUAL(1)
DWORD    __stdcall AxmSignalSetWriteOutputBitAtPos(long lAxisNo, long lModuleNo, long lOffset, DWORD uValue, double dPosition, long lTarget);
// Get the digital output value control setting set at a specific position on the specified axis.
DWORD    __stdcall AxmSignalGetWriteOutputBitAtPos(long lAxisNo, long* lpModuleNo, long* lpOffset, DWORD* upValue, double* dpPosition, long* lpTarget);


//-------------------------------------------------------------------------------------------------------------------

DWORD    __stdcall AxmAdvVSTSetParameter(long lCoord, DWORD dwISTSize, double* dbpFrequency, double* dbpDampingRatio, DWORD* dwpImpulseCount);
DWORD    __stdcall AxmAdvVSTGetParameter(long lCoord, DWORD* dwpISTSize, double* dbpFrequency, double* dbpDampingRatio, DWORD* dwpImpulseCount);
DWORD    __stdcall AxmAdvVSTSetEnabele(long lCoord, DWORD dwISTEnable);
DWORD    __stdcall AxmAdvVSTGetEnabele(long lCoord, DWORD* dwpISTEnable);

DWORD    __stdcall AxmAdvLineMove(long lCoordinate, double *dPosition, double dMaxVelocity, double dStartVel, double dStopVel, double dMaxAccel, double dMaxDecel);
DWORD    __stdcall AxmAdvOvrLineMove(long lCoordinate, double *dPosition, double dMaxVelocity, double dStartVel, double dStopVel, double dMaxAccel, double dMaxDecel, long lOverrideMode);
DWORD    __stdcall AxmAdvCircleCenterMove(long lCoord, long *lAxisNo, double *dCenterPos, double *dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir);
DWORD    __stdcall AxmAdvCirclePointMove(long lCoord, long *lAxisNo, double *dMidPos, double *dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, long lArcCircle);
DWORD    __stdcall AxmAdvCircleAngleMove(long lCoord, long *lAxisNo, double *dCenterPos, double dAngle, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir);
DWORD    __stdcall AxmAdvCircleRadiusMove(long lCoord, long *lAxisNo, double dRadius, double *dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance);
DWORD    __stdcall AxmAdvOvrCircleRadiusMove(long lCoord, long *lAxisNo, double dRadius, double *dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance, long lOverrideMode);


DWORD    __stdcall AxmAdvHelixCenterMove(long lCoord, double dCenterXPos, double dCenterYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir);
DWORD    __stdcall AxmAdvHelixPointMove(long lCoord, double dMidXPos, double dMidYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel);
DWORD    __stdcall AxmAdvHelixAngleMove(long lCoord, double dCenterXPos, double dCenterYPos, double dAngle, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir);
DWORD    __stdcall AxmAdvHelixRadiusMove(long lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance);
DWORD    __stdcall AxmAdvOvrHelixRadiusMove(long lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance, long lOverrideMode);

DWORD    __stdcall AxmAdvScriptLineMove(long lCoordinate, double *dPosition, double dMaxVelocity, double dStartVel, double dStopVel, double dMaxAccel, double dMaxDecel, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptOvrLineMove(long lCoordinate, double *dPosition, double dMaxVelocity, double dStartVel, double dStopVel, double dMaxAccel, double dMaxDecel, long lOverrideMode, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptCircleCenterMove(long lCoord, long *lAxisNo, double *dCenterPos, double *dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptCirclePointMove(long lCoord, long *lAxisNo, double *dMidPos, double *dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, long lArcCircle, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptCircleAngleMove(long lCoord, long *lAxisNo, double *dCenterPos, double dAngle, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptCircleRadiusMove(long lCoord, long *lAxisNo, double dRadius, double *dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptOvrCircleRadiusMove(long lCoord, long *lAxisNo, double dRadius, double *dEndPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance, long lOverrideMode, DWORD dwScript, long lScirptAxisNo, double dScriptPos);


DWORD    __stdcall AxmAdvScriptHelixCenterMove(long lCoord, double dCenterXPos, double dCenterYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptHelixPointMove(long lCoord, double dMidXPos, double dMidYPos, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptHelixAngleMove(long lCoord, double dCenterXPos, double dCenterYPos, double dAngle, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptHelixRadiusMove(long lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance, DWORD dwScript, long lScirptAxisNo, double dScriptPos);
DWORD    __stdcall AxmAdvScriptOvrHelixRadiusMove(long lCoord, double dRadius, double dEndXPos, double dEndYPos, double dZPos, double dVel, double dStartVel, double dStopVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance, long lOverrideMode, DWORD dwScript, long lScirptAxisNo, double dScriptPos);

DWORD    __stdcall AxmAdvContiGetNodeNum(long lCoordinate, long *lpNodeNum);
DWORD    __stdcall AxmAdvContiGetTotalNodeNum(long lCoordinate, long *lpNodeNum);
DWORD    __stdcall AxmAdvContiReadIndex(long lCoordinate, long *lpQueueIndex);
DWORD    __stdcall AxmAdvContiReadFree(long lCoordinate, DWORD *upQueueFree);
DWORD    __stdcall AxmAdvContiWriteClear(long lCoordinate);
DWORD    __stdcall AxmAdvOvrContiWriteClear(long lCoordinate);
DWORD    __stdcall AxmAdvContiStart(long lCoord, DWORD dwProfileset, long lAngle);
DWORD    __stdcall AxmAdvContiStop(long lCoordinate, double dDecel);
DWORD    __stdcall AxmAdvContiSetAxisMap(long lCoord, long lSize, long *lpAxesNo);
DWORD    __stdcall AxmAdvContiGetAxisMap(long lCoord, long *lpSize, long *lpAxesNo);
DWORD    __stdcall AxmAdvContiSetAbsRelMode(long lCoord, DWORD uAbsRelMode);
DWORD    __stdcall AxmAdvContiGetAbsRelMode(long lCoord, DWORD *uAbsRelMode);
DWORD    __stdcall AxmAdvContiIsMotion(long lCoordinate, DWORD *upInMotion);
DWORD    __stdcall AxmAdvContiBeginNode(long lCoord);
DWORD    __stdcall AxmAdvContiEndNode(long lCoord);

DWORD    __stdcall AxmMoveMultiStop(long lArraySize, long *lpAxesNo, double *dMaxDecel);
DWORD    __stdcall AxmMoveMultiEStop(long lArraySize, long *lpAxesNo);
DWORD    __stdcall AxmMoveMultiSStop(long lArraySize, long *lpAxesNo);

DWORD    __stdcall AxmStatusReadActVel(long lAxisNo, double *dpVel);          //2010.10.11
DWORD    __stdcall AxmStatusReadServoCmdStat(long lAxisNo, DWORD *upStatus);
DWORD    __stdcall AxmStatusReadServoCmdCtrl(long lAxisNo, DWORD *upStatus);

DWORD    __stdcall AxmGantryGetMstToSlvOverDist(long lAxisNo, double *dpPosition);
DWORD    __stdcall AxmGantrySetMstToSlvOverDist(long lAxisNo, double dPosition);

DWORD    __stdcall AxmSignalReadServoAlarmCode(long lAxisNo, WORD *upCodeStatus);

DWORD    __stdcall AxmM3ServoCoordinatesSet(long lAxisNo, DWORD dwPosData, DWORD dwPos_sel, DWORD dwRefe);
DWORD    __stdcall AxmM3ServoBreakOn(long lAxisNo);
DWORD    __stdcall AxmM3ServoBreakOff(long lAxisNo);
DWORD    __stdcall AxmM3ServoConfig(long lAxisNo, DWORD dwCfMode);
DWORD    __stdcall AxmM3ServoSensOn(long lAxisNo);
DWORD    __stdcall AxmM3ServoSensOff(long lAxisNo);
DWORD    __stdcall AxmM3ServoSmon(long lAxisNo);
DWORD    __stdcall AxmM3ServoGetSmon(long lAxisNo,BYTE *pbParam);
DWORD    __stdcall AxmM3ServoSvOn(long lAxisNo);
DWORD    __stdcall AxmM3ServoSvOff(long lAxisNo);
DWORD    __stdcall AxmM3ServoInterpolate(long lAxisNo, DWORD dwTPOS, DWORD dwVFF, DWORD dwTFF, DWORD dwTLIM);
DWORD    __stdcall AxmM3ServoPosing(long lAxisNo, DWORD dwTPOS, DWORD dwSPD, DWORD dwACCR, DWORD dwDECR, DWORD dwTLIM);
DWORD    __stdcall AxmM3ServoFeed(long lAxisNo, long lSPD, DWORD dwACCR, DWORD dwDECR, DWORD dwTLIM);
DWORD    __stdcall AxmM3ServoExFeed(long lAxisNo, long lSPD, DWORD dwACCR, DWORD dwDECR, DWORD dwTLIM, DWORD dwExSig1, DWORD dwExSig2);
DWORD    __stdcall AxmM3ServoExPosing(long lAxisNo, DWORD dwTPOS, DWORD dwSPD, DWORD dwACCR, DWORD dwDECR, DWORD dwTLIM, DWORD dwExSig1, DWORD dwExSig2);
DWORD    __stdcall AxmM3ServoZret(long lAxisNo, DWORD dwSPD, DWORD dwACCR, DWORD dwDECR, DWORD dwTLIM, DWORD dwExSig1, DWORD dwExSig2, BYTE bHomeDir, BYTE bHomeType);
DWORD    __stdcall AxmM3ServoVelctrl(long lAxisNo, DWORD dwTFF, DWORD dwVREF, DWORD dwACCR, DWORD dwDECR, DWORD dwTLIM);
DWORD    __stdcall AxmM3ServoTrqctrl(long lAxisNo, DWORD dwVLIM, long lTQREF);
DWORD    __stdcall AxmM3ServoGetParameter(long lAxisNo, WORD wNo, BYTE bSize, BYTE bMode, BYTE *pbParam);
DWORD    __stdcall AxmM3ServoSetParameter(long lAxisNo, WORD wNo, BYTE bSize, BYTE bMode, BYTE *pbParam);
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
DWORD   __stdcall AxmServoCmdExecution(long lAxisNo, DWORD dwCommand, DWORD dwSize, DWORD *pdwExcData);
DWORD    __stdcall AxmM3ServoGetTorqLimit(long lAxisNo, DWORD *dwpTorqLimit);
DWORD    __stdcall AxmM3ServoSetTorqLimit(long lAxisNo, DWORD dwTorqLimit);

DWORD    __stdcall AxmM3ServoGetSendSvCmdIOOutput(long lAxisNo, DWORD *dwData);
DWORD    __stdcall AxmM3ServoSetSendSvCmdIOOutput(long lAxisNo, DWORD dwData);

DWORD    __stdcall AxmM3ServoGetSvCmdCtrl(long lAxisNo, DWORD *dwData);
DWORD    __stdcall AxmM3ServoSetSvCmdCtrl(long lAxisNo, DWORD dwData);

DWORD    __stdcall AxmM3AdjustmentOperation(long lAxisNo, DWORD dwReqCode);
DWORD    __stdcall AxmM3ServoSetMonSel(long lAxisNo, DWORD dwMon0, DWORD dwMon1, DWORD dwMon2);
DWORD    __stdcall AxmM3ServoGetMonSel(long lAxisNo, DWORD *upMon0, DWORD *upMon1, DWORD *upMon2);
DWORD    __stdcall AxmM3ServoReadMonData(long lAxisNo, DWORD dwMonSel, DWORD *dwpMonData);
DWORD    __stdcall AxmAdvTorqueContiSetAxisMap(long lCoord, long lSize, long *lpAxesNo, DWORD dwTLIM, DWORD dwConMode);
DWORD    __stdcall AxmM3ServoSetTorqProfile(long lCoord, long lAxisNo, long TorqueSign, DWORD dwVLIM, DWORD dwProfileMode, DWORD dwStdTorq, DWORD dwStopTorq);
DWORD    __stdcall AxmM3ServoGetTorqProfile(long lCoord, long lAxisNo, long *lpTorqueSign, DWORD *updwVLIM, DWORD *upProfileMode, DWORD *upStdTorq, DWORD *upStopTorq);

//-------------------------------------------------------------------------------------------------------------------

//======== For EtherCAT Only =======================================================================================
// Set for Inposition signal range. (dInposRange > 0)
DWORD   __stdcall AxmSignalSetInposRange(long lAxisNo, double dInposRange);
// Get the Inposition signal range.
DWORD   __stdcall AxmSignalGetInposRange(long lAxisNo, double *dpInposRange);


// Set for absolute encoder position to dPosition.
DWORD    __stdcall AxmStatusSetEncClear(long lAxisNo, double dPosition);


// The command position and actual position of the SERVOPACK corresponding to the designated axis are matched with the dPos value.
// Reserved
DWORD    __stdcall AxmStatusSetMotorPosMatch(long lAxisNo);


// Set for Work coordinate system. The default value matches World coordinate.
// lCoordNo : Coordinate No(0 ~ 7)
// dpOrigin : Work coordinate system origin position based on World Coordinate
// dpXPos   : Work coordinate system based on World Coordinate Any position on X axis
// dpYPos   : Work coordinate system based on World Coordinate Any position on Y axis
DWORD    __stdcall AxmMotSetWorkCoordinate(long lCoordNo, double *dpOrigin, double *dpXPos, double *dpYPos);
// Get the set Work coordinate system.
DWORD    __stdcall AxmMotGetWorkCoordinate(long lCoordNo, double *dpOrigin, double *dpXPos, double *dpYPos);

// Set the location property (absolute / relative) when overriding.
DWORD    __stdcall AxmMotSetOverridePosMode(long lAxisNo, DWORD dwAbsRelMode);
// Get the location property (absolute / relative) when overriding.
DWORD    __stdcall AxmMotGetOverridePosMode(long lAxisNo, DWORD *dwpAbsRelMode);
// Set the location property (absolute / relative) when LineMove overriding.
DWORD    __stdcall AxmMotSetOverrideLinePosMode(long lCoordNo, DWORD dwAbsRelMode);
// Get the location property (absolute / relative) when LineMove overriding.
DWORD    __stdcall AxmMotGetOverrideLinePosMode(long lCoordNo, DWORD *dwpAbsRelMode);


// Set the Vibration Control setting value(Set the Vibration Control setting value (frequency, damping ratio, impulse count) of the specified axis.
DWORD    __stdcall AxmMotSetVibrationControl(long lAxisNo, long lSize, double* pdFrequency, double* pdDampingRatio, long* lpImpulseCount);

// Enable or disable the Vibration Control of the specific axis.
DWORD    __stdcall AxmMotVibrationControlEnable(long lAxisNo, DWORD dwEnable);

// Reads whether Vibration Control of the specified axis is enabled.
DWORD    __stdcall AxmMotVibrationControlIsEnable(long lAxisNo, DWORD* pdwEnable);

// Enable or Disable the Vibration Control of the specified coordinate system.
DWORD    __stdcall AxmMotVibrationControlCoordEnable(long lCoordNo, DWORD dwEnable);

// Reads whether Vibration Control is enabled in the specified coordinate system.
DWORD    __stdcall AxmMotVibrationControlCoordIsEnable(long lCoordNo, DWORD* pdwEnable);


// Sets the TorqueLimit for each Position range of the specified axis.
// The number of dpPosition array is lSize.
// The number of dpPlusTorqueLimit and dpMinusTorqueLimit is (lSize - 1)
// ※ Note : Position must be entered in ascending order.
//          EtherCAT only applies the same TorqueLimit to both PlusTorqueLimit values.
DWORD    __stdcall AxmMotSetMultiTorqueLimit(long lAxisNo, long lSize, double* dpPosition, double* dpPlusTorqueLimit, double* dpMinusTorqueLimit, long lTarget);

// Enable or Disable the Multi TorqueLimit of the specified axis.
DWORD    __stdcall AxmMotMultiTorqueLimitEnable(long lAxisNo, DWORD dwEnable);

// Reads whether Multi TorqueLimit of the specified axis is enabled.
DWORD    __stdcall AxmMotMultiTorqueLimitIsEnable(long lAxisNo, DWORD* dwpEnable);


// Equivalent to AxmMoveStartPos and added end rate (EndVel).
DWORD    __stdcall AxmMoveStartPosEx(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, double dEndVel);
// Equivalent to AxmMovePos and added end rate (EndVel).
DWORD    __stdcall AxmMovePosEx(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, double dEndVel);

//DWORD    __stdcall AxmMoveStartMultiPosEx(long lArraySize, long *lpAxisNo, double *dpPos, double *dpVel, double *dpAccel, double *dpDecel, double *dpEndVel);
//DWORD    __stdcall AxmMoveMultiPosEx(long lArraySize, long *lpAxisNo, double *dpPos, double *dpVel, double *dpAccel, double *dpDecel, double *dpEndVel);

// Normal-Stop the Coordinate Motion on path.
DWORD    __stdcall AxmMoveCoordStop(long lCoordNo, double dDecel);
// Emergency-Stop the Coordinate Motion on path.
DWORD    __stdcall AxmMoveCoordEStop(long lCoordNo);
// Slowdown-Stop the Coordinate Motion on path.
DWORD    __stdcall AxmMoveCoordSStop(long lCoordNo);



//DWORD    __stdcall AxmMoveStartPosWithPosEventEx(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, long lEventAxisNo, double dComparePos, DWORD uPosSource, double dEndVel);

// Override the position of the AxmLineMove motion.
DWORD    __stdcall AxmOverrideLinePos(long lCoordNo, double *dpOverridePos);
// Override the velocity of the AxmLineMove motion. The speed ratio of each axis is determined by dpDistance.
DWORD    __stdcall AxmOverrideLineVel(long lCoordNo, double dOverrideVel, double *dpDistance);

// Override the velocity, acceleration, deceleration of the AxmLineMove motion.
// dMaxAccel  : Acceleration value for overriding
// dMaxDecel  : Deceleration value for overriding
// dpDistance : Speed ratio of each axis
DWORD    __stdcall AxmOverrideLineAccelVelDecel(long lCoordNo, double dOverrideVelocity, double dMaxAccel, double dMaxDecel, double *dpDistance);
// In addition to AxmOverrideVelAtPos, override AccelDecel.
DWORD    __stdcall AxmOverrideAccelVelDecelAtPos(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel,double dOverridePos, double dOverrideVel, double dOverrideAccel, double dOverrideDecel, long lTarget);


// A plurality of slave axes are connected to one master axis. (Electronic Gearing)
// lMasterAxisNo : Master axis number
// lSize         : Slave axis count(Max : 8)
// lpSlaveAxisNo : Array of Slave axis number
// dpGearRatio   : Slave axis ratio based on master axis (Except 0. 1.0 is 100%)
DWORD    __stdcall AxmEGearSet(long lMasterAxisNo, long lSize, long* lpSlaveAxisNo, double* dpGearRatio);
// Reads Electronic Gearing information.
DWORD    __stdcall AxmEGearGet(long lMasterAxisNo, long* lpSize, long* lpSlaveAxisNo, double* dpGearRatio);
// Reset Electronic Gearing.
DWORD    __stdcall AxmEGearReset(long lMasterAxisNo);
// Enable or disable Electronic Gearing.
DWORD    __stdcall AxmEGearEnable(long lMasterAxisNo, DWORD dwEnable);
// Reads whether Electronic Gearing is enabled.
DWORD    __stdcall AxmEGearIsEnable(long lMasterAxisNo, DWORD *dwpEnable);




//DWORD    __stdcall AxmLineMoveEx(long lCoordNo, double *dpEndPos, double dVel, double dAccel, double dDecel, double dEndVel);

//DWORD    __stdcall AxmCirclePointMoveEx(long lCoordNo, long *lAxisNo, double *dpMidPos, double *dpEndPos, double dVel, double dAccel, double dDecel, long lArcCircle, long lArraySize, double dEndVel);

// Helical interpolation drive that rotates around any axis is supported.
// dpFirstCenterPos  : Center position
// dpSecondCenterPos : Center position on opposite side
// dPitch            : Movement amount(mm) / 1 Revolution
// dTraverseDistance : Movement amount(mm)
// The line connecting dpFirstCenterPos to dpSecondCenterPos is the axis of rotation.
// The straight line from the center(dpFirstCenterPos-->dpSecondCenterPos) and the straight line to the start position(dpFirstCenterPos-->Starting position) is perpendicular to each other.
// dTraverseDistance is the distance of a straight line parallel to the axis of rotation at the starting position.
// Axis mapping is possible for more than 3 axes, and axes more than 3 axes are linear interpolation.
DWORD    __stdcall AxmHelixPitchMove(long lCoordNo, double *dpFirstCenterPos, double *dpSecondCenterPos, double dPitch, double dTraverseDistance, double dVel, double dAccel, double dDecel, DWORD uCWDir);

//DWORD    __stdcall AxmHelixPitchMoveEx(long lCoordNo, double *dpFirstCenterPos, double *dpSecondCenterPos, double dPitch, double dTraverseDistance, double dVel, double dAccel, double dDecel, DWORD uCWDir, double dEndVel);

    // 1-D correction function
    // When driving beyond the compensation table range, the first and last compensation values of the compensation table should always be set to "0".
    // That is, pdMotorPosition and pdLoadPosition must be the same.
    // You can set the axis to measure the correction value (lSourceAxis) and the axis to apply the correction value (lTargetAxis) to the same axis or another axis.
    // The position value of the correction table is set to an absolute position.
    DWORD    __stdcall AxmCompensationOneDimSet(long lTableNo, long lSourceAxis, long lTargetAxis, long lSize, double* dpMotorPosition, double* dpLoadPosition, DWORD dwInterpolationMethod = 0, DWORD dwUseReverse = 0, double* dpLoadReversePosition = NULL);
    DWORD    __stdcall AxmCompensationOneDimGet(long lTableNo, long *lpSourceAxis, long *lpTargetAxis, long *lpSize, double *dpMotorPosition, double *dpLoadPosition);
    DWORD    __stdcall AxmCompensationOneDimReset(long lTableNo);
    DWORD    __stdcall AxmCompensationOneDimIsSet(long lTableNo, DWORD* dwpSet);
    DWORD    __stdcall AxmCompensationOneDimEnable(long lTableNo, DWORD dwEnable);
    DWORD    __stdcall AxmCompensationOneDimIsEnable(long lTableNo, DWORD *dwpEnable);


// Returns the compensation value at the current command position.
DWORD    __stdcall AxmCompensationOneDimGetCorrection(long lTableNo, double* pdCorrection);

DWORD    __stdcall AxmCompensationOneDimSetReverse(long lTableNo, double* dpLoadPosition);
DWORD    __stdcall AxmCompensationOneDimGetReverse(long lTableNo, double *dpLoadPosition);
DWORD    __stdcall AxmCompensationOneDimGetCorrectionReverse(long lTableNo, double* pdCorrection);

DWORD    __stdcall AxmCompensationOneDimFileLoad(long lTableNo, long lSourceAxis, long lTargetAxis, char *szFilePath, DWORD dwInterpolationMethod = 0);
DWORD    __stdcall AxmCompensationOneDimFileSave(long lTableNo, char *szFilePath);

DWORD    __stdcall AxmCompensationOneDimSetInterpolationMethod(long lTableNo, DWORD dwMethod);
DWORD    __stdcall AxmCompensationOneDimGetInterpolationMethod(long lTableNo, DWORD *dwpMethod);


DWORD    __stdcall AxmCompensationTwoDimSet(long lTableNo, long lSourceAxis1, long lSourceAxis2, long lTargetAxis1, long lTargetAxis2, long lSize1, long lSize2, double *dpMotorPosition1, double *dpMotorPosition2, double *dpLoadPosition1, double *dpLoadPosition2);
DWORD    __stdcall AxmCompensationTwoDimGet(long lTableNo, long *lpSourceAxis1, long *lpSourceAxis2, long *lpTargetAxis1, long *lpTargetAxis2, long *lpSize1, long *lpSize2, double *dpMotorPosition1, double *dpMotorPosition2, double *dpLoadPosition1, double *dpLoadPosition2);
DWORD    __stdcall AxmCompensationTwoDimReset(long lTableNo);
DWORD    __stdcall AxmCompensationTwoDimIsSet(long lTableNo, DWORD* dwpSet);
DWORD    __stdcall AxmCompensationTwoDimEnable(long lTableNo, DWORD dwEnable);
DWORD    __stdcall AxmCompensationTwoDimIsEnable(long lTableNo, DWORD *dwpEnable);


DWORD    __stdcall AxmCompensationTwoDimGetCorrection(long lTableNo, double* pdCorrection);

DWORD    __stdcall AxmCompensationTwoDimFileLoad(long lTableNo, long lSourceAxis1, long lSourceAxis2, long lTargetAxis1, long lTargetAxis2, char *szFilePath);
DWORD    __stdcall AxmCompensationTwoDimFileSave(long lTableNo, char *szFilePath);


// Reserved
//DWORD    __stdcall AxmBlendingSet(long lAxisNo, double dValue, DWORD dwMethod);
//DWORD    __stdcall AxmBlendingGet(long lAxisNo, double *dpValue, DWORD *dwpMethod);
//DWORD    __stdcall AxmBlendingReset(long lAxisNo);
//DWORD    __stdcall AxmBlendingEnable(long lAxisNo, DWORD dwEnable);
//DWORD    __stdcall AxmBlendingIsEnable(long lAxisNo, DWORD *dwpEnable);

// Blending motion is supported.
// dValue   : At the start of blending based on the ending point of the first motion segment
// dwMethod : Distance(mm)-0, Time(msec)-1, Distance ratio(%)-2
// Blending mode is canceled in automatic acceleration / deceleration and automatic arc insertion mode.
DWORD    __stdcall AxmBlendingCoordSet(long lCoordNo, double dValue, DWORD dwMethod);
DWORD    __stdcall AxmBlendingCoordGet(long lCoordNo, double *dpValue, DWORD *dwpMethod);
DWORD    __stdcall AxmBlendingCoordReset(long lCoordNo);
DWORD    __stdcall AxmBlendingCoordEnable(long lCoordNo, DWORD dwEnable);
DWORD    __stdcall AxmBlendingCoordIsEnable(long lCoordNo, DWORD *dwpEnable);





//DWORD    __stdcall AxmMoveMultiSignalCapture(long lAxisNo, double dPos, double dVel, double dAccel, double dDecel, long lDetectSignal, long lSignalEdge, long lTarget);
//DWORD    __stdcall AxmMoveGetMultiCapturePos(long lAxisNo, double *dpCapPosition, long* lpSize);

//DWORD    __stdcall AxmStatusReadServoAlarm(long lAxisNo, DWORD uReturnMode, DWORD *upAlarmCode);

//DWORD    __stdcall AxmStatusGetServoAlarmString(long lAxisNo, DWORD uAlarmCode, long lAlarmStringSize, char *szAlarmString);

// Read the torque value of the corresponding axis.
DWORD    __stdcall AxmStatusReadTorque(long lAxisNo, double* pdTorque);


// Set the end speed on the specified axis.
// ※ Note : It is reset to '0' if the entered end rate is below '0' and to 'MaxVel' if it exceeds the maximum speed set by 'AxmMotSetMaxVel'.
DWORD    __stdcall AxmMotSetEndVel(long lAxisNo, double dEndVelocity);
// Returns the ending speed of the specified axis.
DWORD    __stdcall AxmMotGetEndVel(long lAxisNo, double *dpEndVelocity);

// Linear interpolation.
// Axis linear interpolation drive by specifying a start point and an end point. The function is exited after the start of driving.
// When using with AxmContiBeginNode and AxmContiEndNode, the start point and the end point are specified in the specified coordinate system and stored in the queue for linear interpolation driving.
// For linear profile continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
// The axes corresponding to the axis array of lpAxisNo are subjected to linear interpolation and the axes of the remaining coordinate axes perform the single axis driving according to the linear interpolation ratio.
DWORD    __stdcall AxmLineMoveWithAxes(long lCoord, long lArraySize, long *lpAxisNo, double *dpEndPos, double dVel, double dAccel, double dDecel);


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
DWORD    __stdcall AxmCircleCenterMoveWithAxes(long lCoord, long lArraySize, long *lpAxisNo, double* dCenterPosition, double* dEndPosition, double dMaxVelocity, double dMaxAccel, double dMaxDecel, DWORD uCWDir, DWORD dw3DCircle);

DWORD    __stdcall AxmCircleRadiusMoveWithAxes(long lCoord, long lArraySize, long *lpAxisNo, double dRadius, double *dEndPos, double dVel, double dAccel, double dDecel, DWORD uCWDir, DWORD uShortDistance);


DWORD    __stdcall AxmCircleAngleMoveWithAxes(long lCoord, long lArraySize, long *lpAxisNo, double *dCenterPos, double dAngle, double dVel, double dAccel, double dDecel, DWORD uCWDir);

DWORD    __stdcall AxmCirclePointMoveWithAxes(long lCoordNo, long lArraySize, long *lpAxisNo, double *dpMidPos,    double *dpEndPos,   double dVel, double dAccel, double dDecel, long lArcCircle);


// Linear interpolation.
// Axis linear interpolation drive by specifying a start point and an end point. The function is exited after the start of driving.
// When using with AxmContiBeginNode and AxmContiEndNode, the start point and the end point are specified in the specified coordinate system and stored in the queue for linear interpolation driving.
// For linear profile continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
// The axes corresponding to the axis array of lpAxisNo are subjected to linear interpolation and the axes of the remaining coordinate axes perform the single axis driving according to the linear interpolation ratio.
DWORD    __stdcall AxmLineMoveWithAxesWithEvent(long lCoord, long lArraySize, long *lpAxisNo, double *dpEndPos, double dVel, double dAccel, double dDecel, DWORD dwEventFlag);


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
DWORD    __stdcall AxmCircleCenterMoveWithAxesWithEvent(long lCoord, long lArraySize, long *lpAxisNo, double* dCenterPosition, double* dEndPosition, double dMaxVelocity, double dMaxAccel, double dMaxDecel, DWORD uCWDir, DWORD dw3DCircle,  DWORD dwEventFlag);


DWORD    __stdcall AxmMovePVT(long lAxisNo, DWORD dwArraySize, double* pdPos, double* pdVel, DWORD* pdwUsec);


DWORD    __stdcall AxmSyncSetAxisMap(long lSyncNo, long lSize, long *lpAxesNo);

DWORD    __stdcall AxmSyncClear(long lSyncNo);

DWORD    __stdcall AxmSyncBegin(long lSyncNo);

DWORD    __stdcall AxmSyncEnd(long lSyncNo);

DWORD    __stdcall AxmSyncStart(long lSyncNo);


#ifdef __cplusplus
}
#endif    //__cplusplus

#endif    //__AXT_AXM_H__
