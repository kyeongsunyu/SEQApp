'*****************************************************************************
'/****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ---------
'**
'** AXM.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Ajinextek Motion Library Header File
'** 
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Source Change Indices
'** ----------------------
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

Attribute VB_Name = "AXM"


'****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ---------
'**
'** AXM.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Ajinextek Motion Library Header File
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
'*

'========== Board and module verification API(Info) - Information =================================================================================

' Return board number, module position and module ID of relevant axis.
Public Declare Function AxmInfoGetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpBoardNo As Long, ByRef lpModulePos As Long, ByRef upModuleID As Long) As Long

' Get the specified module board : Sub ID, module name, module description
'===============================================/
' support product      : EtherCAT
' upModuleSubID        : EtherCAT SubID(for distinguish between EtherCAT modules)
' szModuleName         : model name of module(50 Bytes)
' szModuleDescription  : description of module(80 Bytes)
'======================================================//
Public Declare Function AxmInfoGetAxisEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upModuleSubID As Long, ByRef szModuleName As String, ByRef szMoculeDescription As String) As Long


' Return whether the motion module exists.
Public Declare Function AxmInfoIsMotionModule Lib "AXL.dll" (ByRef upStatus As Long) As Long
' Return whether relevant axis is valid.
Public Declare Function AxmInfoIsInvalidAxisNo Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' Return whether relevant axis status.
Public Declare Function AxmInfoGetAxisStatus Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' number of RTEX Products, return number of valid axis installed in system.
Public Declare Function AxmInfoGetAxisCount Lib "AXL.dll" (ByRef lpAxisCount As Long) As Long
' Return the first axis number of relevant board/module
Public Declare Function AxmInfoGetFirstAxisNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpAxisNo As Long) As Long
' Return the first axis number of relevant board
Public Declare Function AxmInfoGetBoardFirstAxisNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpAxisNo As Long) As Long



'========= virtual axis function ============================================================================================

' Set virtual axis.
Public Declare Function AxmVirtualSetAxisNoMap Lib "AXL.dll" (ByVal lRealAxisNo As Long, ByVal lVirtualAxisNo As Long) As Long
' Return the set virtual channel(axis) number.
Public Declare Function AxmVirtualGetAxisNoMap Lib "AXL.dll" (ByVal lRealAxisNo As Long, ByRef lpVirtualAxisNo As Long) As Long
' Set multi-virtual axes.
Public Declare Function AxmVirtualSetMultiAxisNoMap Lib "AXL.dll" (ByVal lSize As Long, ByRef lpRealAxesNo As Long, ByRef lpVirtualAxesNo As Long) As Long
' Return the set multi-virtual channel(axis) number.
Public Declare Function AxmVirtualGetMultiAxisNoMap Lib "AXL.dll" (ByVal lSize As Long, ByRef lpRealAxesNo As Long, ByRef lpVirtualAxesNo As Long) As Long
' Reset the virtual axis setting.
Public Declare Function AxmVirtualResetAxisMap Lib "AXL.dll" () As Long

    Public Declare Function AxmVirtualSetMultiReDefineAxisNo Lib "AXL.dll" (ByVal lSize As Long, ByRef lpReDefineAxesNo As Long) As Long
    Public Declare Function AxmVirtualGetMultiReDefineAxisNo Lib "AXL.dll" (ByVal lSize As Long, ByRef lpReDefineAxesNo As Long) As Long


'========= API related interrupt ======================================================================================

' Call-back API method has the advantage which can be advised the event most fast timing as the call-back API is called immediately when the event occurs, but
' the main processor shall be congested until the call-back API is completed.
' i.e, it shall be carefully used when there is any work loaded in the call-bak API.
' Event method monitors if interrupt occurs continuously by using thread, and when interrupt is occurs
' it manages, and even though this method has disadvantage which system resource is occupied by thread ,
' it can detect interrupt most quickly and manage it.
' It is not used a lot in general, but used when quick management of interrupt is the most concern.
' Event method is operated using specific thread which monitors the occurrence of event separately from main processor , so
' it able to use the resources efficiently in multi-processor system and expressly recommendable method.

' Window message or call back API is used for getting the interrupt message.
' (message handle, message ID, call back API, interrupt event)
'    hWnd    : use to get window handle and window message. Enter NULL if it is not used.
'    wMsg    : message of window handle, enter 0 if is not used or default value is used.
'    proc    : API pointer to be called when interrupted, enter NULL if not use
'    pEvent  : Event handle when event method is used.
' Ex)
' AxmInterruptSetAxis(0, Null, 0, AxtInterruptProc, NULL);
' void __stdcall AxtInterruptProc(long lActiveNo, DWORD uFlag){
'     ... ;
' }
Public Declare Function AxmInterruptSetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal hWnd As Long, ByVal uMessage As Long, ByVal pProc As Long, ByRef pEvent As Long) As Long


' Set whether to use interrupt of set axis or not.
' Set interrupt in the relevant axis/ verification
' uUse : use or not use => DISABLE(0), ENABLE(1)
Public Declare Function AxmInterruptSetAxisEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long
' Return whether to use interrupt of set axis or not
Public Declare Function AxmInterruptGetAxisEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long


' Read relevant information when interrupt is used in event method
Public Declare Function AxmInterruptRead Lib "AXL.dll" (ByRef lpAxisNo As Long, ByRef upFlag As Long) As Long

' Return interrupt flag value of relevant axis.
Public Declare Function AxmInterruptReadAxisFlag Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBank As Long, ByRef upFlag As Long) As Long


' Set whether the interrupt set by user to specific axis occurs or not
' lBank         : Enable to set interrupt bank number(0 - 1).
' uInterruptNum : Enable to set interrupt number by setting bit number( 0 - 31 ).
Public Declare Function AxmInterruptSetUserEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBank As Long, ByVal lInterruptNum As Long) As Long

' Verify whether the interrupt set by user of specific axis occurs or not
Public Declare Function AxmInterruptGetUserEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBank As Long, ByRef upInterruptNum As Long) As Long




'======== set motion parameter ===========================================================================================================================================================
' If file is not loaded by AxmMotLoadParaAll, set default parameter in initial parameter setting.
' Apply to all axes which is being used in PC equally. Default parameters are as below.
' 00:AXIS_NO.             =0       01:PULSE_OUT_METHOD.    =4      02:ENC_INPUT_METHOD.    =3     03:INPOSITION.          =2
' 04:ALARM.               =0       05:NEG_END_LIMIT.       =0      06:POS_END_LIMIT.       =0     07:MIN_VELOCITY.        =1
' 08:MAX_VELOCITY.        =700000  09:HOME_SIGNAL.         =4      10:HOME_LEVEL.          =1     11:HOME_DIR.            =-1
' 12:ZPHASE_LEVEL.        =1       13:ZPHASE_USE.          =0      14:STOP_SIGNAL_MODE.    =0     15:STOP_SIGNAL_LEVEL.   =0
' 16:HOME_FIRST_VELOCITY. =10000   17:HOME_SECOND_VELOCITY.=10000  18:HOME_THIRD_VELOCITY. =2000  19:HOME_LAST_VELOCITY.  =100
' 20:HOME_FIRST_ACCEL.    =40000   21:HOME_SECOND_ACCEL.   =40000  22:HOME_END_CLEAR_TIME. =1000  23:HOME_END_OFFSET.     =0
' 24:NEG_SOFT_LIMIT.      =0.000   25:POS_SOFT_LIMIT.      =0      26:MOVE_PULSE.          =1     27:MOVE_UNIT.           =1
' 28:INIT_POSITION.       =1000    29:INIT_VELOCITY.       =200    30:INIT_ACCEL.          =400   31:INIT_DECEL.          =400
' 32:INIT_ABSRELMODE.     =0       33:INIT_PROFILEMODE.    =4

' 00=[AXIS_NO             ]: axis (start from 0axis)
' 01=[PULSE_OUT_METHOD    ]: Pulse out method TwocwccwHigh = 6
' 02=[ENC_INPUT_METHOD    ]: disable = 0   1 multiplication = 1  2 multiplication = 2  4 multiplication = 3, for replacing the direction of splicing (-).1 multiplication = 11  2 multiplication = 12  4 multiplication = 13
' 03=[INPOSITION          ], 04=[ALARM     ], 05,06 =[END_LIMIT   ]  : 0 = A contact 1= B contact 2 = not use. 3 = keep current mode
' 07=[MIN_VELOCITY        ]: START VELOCITY
' 08=[MAX_VELOCITY        ]: command velocity which driver can accept. Generally normal servo is 700k
' Ex> screw : 20mm pitch drive: 10000 pulse motor: 400w
' 09=[HOME_SIGNAL         ]: 4 - Home in0 , 0 :PosEndLimit , 1 : NegEndLimit ' refer _HOME_SIGNAL.
' 10=[HOME_LEVEL          ]: : 0 = A contact 1= B contact 2 = not use. 3 = keep current mode
' 11=[HOME_DIR            ]: HOME DIRECTION 1:+direction, 0:-direction
' 12=[ZPHASE_LEVEL        ]: : 0 = A contact 1= B contact 2 = not use. 3 = keep current mode
' 13=[ZPHASE_USE          ]: use of Z phase. 0: not use , 1: - direction, 2: +direction
' 14=[STOP_SIGNAL_MODE    ]: ESTOP, mode in use of SSTOP  0:slowdown stop, 1:emergency stop
' 15=[STOP_SIGNAL_LEVEL   ]: ESTOP, SSTOP use level. : 0 = A contact 1= B contact 2 = not use. 3 = keep current mode
' 16=[HOME_FIRST_VELOCITY ]: 1st move velocity
' 17=[HOME_SECOND_VELOCITY]: velocity after detecting
' 18=[HOME_THIRD_VELOCITY ]: the last velocity
' 19=[HOME_LAST_VELOCITY  ]: velocity for index detecting and detail detecting
' 20=[HOME_FIRST_ACCEL    ]: 1st acceleration, 21=[HOME_SECOND_ACCEL   ] : 2nd acceleration
' 22=[HOME_END_CLEAR_TIME ]: queue time to set origin detecting Enc value,  23=[HOME_END_OFFSET] : move as much as offset after detecting of origin.
' 24=[NEG_SOFT_LIMIT      ]: - not use if set same as SoftWare Limit , 25=[POS_SOFT_LIMIT ]: - not use if set same as SoftWare Limit.
' 26=[MOVE_PULSE          ]: amount of pulse per driver revolution               , 27=[MOVE_UNIT  ]: travel distance per driver revolution :screw Pitch
' 28=[INIT_POSITION       ]: initial position when use agent , user can use optionally
' 29=[INIT_VELOCITY       ]: initial velocity when use agent, user can use optionally
' 30=[INIT_ACCEL          ]: initial acceleration when use agent, user can use optionally
' 31=[INIT_DECEL          ]: initial deceleration when use agent, user can use optionally
' 32=[INIT_ABSRELMODE     ]: absolute(0)/relative(1) set position
' 33=[INIT_PROFILEMODE    ]: set profile mode in (0 - 4)
'                            '0': symmetry Trapezode, '1': asymmetric Trapezode, '2': symmetry Quasi-S Curve, '3':symmetry S Curve, '4':asymmetric S Curve
' 34=[SVON_LEVEL          ]: 0 = contact B, 1 = contact A
' 35=[ALARM_RESET_LEVEL   ]: 0 = contact B, 1 = contact A
' 36=[ENCODER_TYPE        ]: 0 = TYPE_INCREMENTAL, 1 = TYPE_ABSOLUTE, 2 = TYPE_NONE
' 37=[SOFT_LIMIT_SEL      ]: 0 = COMMAND, 1 = ACTUAL
' 38=[SOFT_LIMIT_STOP_MODE]: 0 = EMERGENCY_STOP, 1 = SLOWDOWN_STOP
' 39=[SOFT_LIMIT_ENABLE   ]: 0 = DISABLE, 1 = ENABLE

' load .mot file which is saved as AxmMotSaveParaAll. Optional modification is available by user.
Public Declare Function AxmMotLoadParaAll Lib "AXL.dll" (ByVal szFilePath As String) As Long
' Save all parameter for all current axis by axis. Save as .mot file. Load file by using  AxmMotLoadParaAll.
Public Declare Function AxmMotSaveParaAll Lib "AXL.dll" (ByVal szFilePath As String) As Long


' In parameter 28 - 31, user sets by using this API in the program.
Public Declare Function AxmMotSetParaLoad Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dInitPos As Double, ByVal dInitVel As Double, ByVal dInitAccel As Double, ByVal dInitDecel As Double) As Long
' In parameter 28 - 31, user verifys by using this API in the program.
Public Declare Function AxmMotGetParaLoad Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpInitPos As Double, ByRef dpInitVel As Double, ByRef dpInitAccel As Double, ByRef dpInitDecel As Double) As Long


' Set the pulse output method of specific axis.
'uMethod  0 :OneHighLowHigh, 1 :OneHighHighLow, 2 :OneLowLowHigh, 3 :OneLowHighLow, 4 :TwoCcwCwHigh
'         5 :TwoCcwCwLow,    6 :TwoCwCcwHigh,   7 :TwoCwCcwLow,   8 :TwoPhase,      9 :TwoPhaseReverse
'    OneHighLowHigh          = 0x0,   // 1 pulse method, PULSE(Active High), forward direction(DIR=Low)  / reverse direction(DIR=High)
'    OneHighHighLow          = 0x1,   // 1 pulse method, PULSE(Active High), forward direction (DIR=High) / reverse direction (DIR=Low)
'    OneLowLowHigh           = 0x2,   // 1 pulse method, PULSE(Active Low), forward direction (DIR=Low)  / reverse direction (DIR=High)
'    OneLowHighLow           = 0x3,   // 1 pulse method, PULSE(Active Low), forward direction (DIR=High) / reverse direction (DIR=Low)
'    TwoCcwCwHigh            = 0x4,   // 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active High
'    TwoCcwCwLow             = 0x5,   // 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active Low
'    TwoCwCcwHigh            = 0x6,   // 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active High
'    TwoCwCcwLow             = 0x7,   // 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active Low
'    TwoPhase                = 0x8,   // 2 phase (90' phase difference),  PULSE lead DIR(CW: forward direction), PULSE lag DIR(CCW: reverse direction)
'    TwoPhaseReverse         = 0x9    // 2 phase(90' phase difference),  PULSE lead DIR(CCW: Forward diredtion), PULSE lag DIR(CW: Reverse direction)

Public Declare Function AxmMotSetPulseOutMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMethod As Long) As Long
' Return the setting of pulse output method of specific axis.
Public Declare Function AxmMotGetPulseOutMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMethod As Long) As Long


' Set the Encoder input method including the setting of increase direction of actual count of specific axis.
'    ObverseUpDownMode       = 0x0,   // Forward direction Up/Down
'    ObverseSqr1Mode         = 0x1,   // Forward direction 1 multiplication
'    ObverseSqr2Mode         = 0x2,   // Forward direction 2 multiplication
'    ObverseSqr4Mode         = 0x3,   // Forward direction 4 multiplication
'    ReverseUpDownMode       = 0x4,   // Reverse direction Up/Down
'    ReverseSqr1Mode         = 0x5,   // Reverse direction 1 multiplication
'    ReverseSqr2Mode         = 0x6,   // Reverse direction 2 multiplication
'    ReverseSqr4Mode         = 0x7    // Reverse direction 4 multiplication

Public Declare Function AxmMotSetEncInputMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMethod As Long) As Long
' Return the Encoder input method including the setting of increase direction of actual count of specific axis.
Public Declare Function AxmMotGetEncInputMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMethod As Long) As Long



' If you want to set specified velocity unit in RPM(Revolution Per Minute),
' ex>    calculate rpm :
' 4500 rpm ?
' When unit/ pulse = 1 : 1, then it becomes pulse per sec, and
' if you want to set at 4500 rpm , then  4500 / 60 sec : 75 revolution / 1sec
' The number of pulse per 1 revolution of motor shall be known. This can be know by detecting of Z phase in Encoder.
' If 1 revolution:1800 pulse,  75 x 1800 = 135000 pulses are required.
' Operate by input Unit = 1, Pulse = 1800 into AxmMotSetMoveUnitPerPulse.
' Caution : If it is controlled with rpm, velocity and acceleration will be changed to rpm unit as well.

' Set the travel distance of specific axis per pulse.
Public Declare Function AxmMotSetMoveUnitPerPulse Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dUnit As Double, ByVal lPulse As Long) As Long
' Return the travel distance of specific axis per pulse.
Public Declare Function AxmMotGetMoveUnitPerPulse Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpUnit As Double, ByRef lpPulse As Long) As Long


' Set deceleration starting point detecting method to specific axis.
' AutoDetect 0x0 : automatic acceleration/deceleration.
' RestPulse  0x1 : manual acceleration/deceleration."
Public Declare Function AxmMotSetDecelMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMethod As Long) As Long
' Return the deceleration starting point detecting method of specific axis.
Public Declare Function AxmMotGetDecelMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMethod As Long) As Long


' Set remain pulse to the specific axis in manual deceleration mode.
Public Declare Function AxmMotSetRemainPulse Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uData As Long) As Long
' Return remain pulse of the specific axis in manual deceleration mode.
Public Declare Function AxmMotGetRemainPulse Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long) As Long


' Set maximum velocity to the specific axis in uniform velocity movement API.
' Note : Input maximum speed value is not PPS but UNIT.
' ex) Maximum output frequency(PCI-N804/404 : 10 MPPS)
' ex) Maximum output Unit/Sec(PCI-N804/404 : 10MPPS * Unit/Pulse)
Public Declare Function AxmMotSetMaxVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double) As Long
' Return maximum velocity of the specific axis in uniform velocity movement API
Public Declare Function AxmMotGetMaxVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpVel As Double) As Long


' Set travel distance calculation mode of specific axis.
'uAbsRelMode : POS_ABS_MODE '0' - absolute coordinate system
'              POS_REL_MODE '1' - relative coordinate system
Public Declare Function AxmMotSetAbsRelMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uAbsRelMode As Long) As Long
' Return travel distance calculation mode of specific axis.
Public Declare Function AxmMotGetAbsRelMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upAbsRelMode As Long) As Long


'Set move velocity profile mode of specific axis.
'ProfileMode : SYM_TRAPEZOIDE_MODE  '0' - symmetry Trapezode
'              ASYM_TRAPEZOIDE_MODE '1' - asymmetric Trapezode
'              QUASI_S_CURVE_MODE   '2' - symmetry Quasi-S Curve
'              SYM_S_CURVE_MODE     '3' - symmetry S Curve
'              ASYM_S_CURVE_MODE    '4' - asymmetric S Curve
'              SYM_TRAP_M3_SW_MODE    '5' - Symmetry Trapezode : MLIII internal S/W Profile
'              ASYM_TRAP_M3_SW_MODE   '6' - Asymmetry Trapezode : MLIII internal S/W Profile
'              SYM_S_M3_SW_MODE       '7' - Symmetry S Curve : MLIII internal S/W Profile
'              ASYM_S_M3_SW_MODE      '8' - Asymmetric S Curve : MLIII internal S/W Profile
Public Declare Function AxmMotSetProfileMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uProfileMode As Long) As Long
' Return move velocity profile mode of specific axis.
Public Declare Function AxmMotGetProfileMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upProfileMode As Long) As Long


'Set acceleration unit of specific axis.
'AccelUnit : UNIT_SEC2  '0' ? use unit/sec2 for the unit of acceleration/deceleration
'            SEC        '1' - use sec for the unit of acceleration/deceleration
Public Declare Function AxmMotSetAccelUnit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uAccelUnit As Long) As Long
' Return acceleration unit of specific axis.
Public Declare Function AxmMotGetAccelUnit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upAccelUnit As Long) As Long


' Set initial velocity to the specific axis.
Public Declare Function AxmMotSetMinVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dMinVel As Double) As Long
' Return initial velocity of the specific axis.
Public Declare Function AxmMotGetMinVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpMinVel As Double) As Long


' Set acceleration jerk value of specific axis.[%].
Public Declare Function AxmMotSetAccelJerk Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dAccelJerk As Double) As Long
' Return acceleration jerk value of specific axis.
Public Declare Function AxmMotGetAccelJerk Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpAccelJerk As Double) As Long


' Set deceleration jerk value of specific axis.[%].
Public Declare Function AxmMotSetDecelJerk Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dDecelJerk As Double) As Long
' Return deceleration jerk value of specific axis.
Public Declare Function AxmMotGetDecelJerk Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpDecelJerk As Double) As Long

' Setting priority when determining speed profile of specified axis.(Velocity or Acceleration)
' Priority : PRIORITY_VELOCITY   '0' - Calculate close to specified speed value when determining velocity profile.
'            PRIORITY_ACCELTIME  '1' - Calculate close to specified speed value when determining Acceleration / Deceleration time profile.
Public Declare Function AxmMotSetProfilePriority Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uPriority As Long) As Long
' Return priority when determining speed profile of specified axis.(Velocity or Acceleration)
Public Declare Function AxmMotGetProfilePriority Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upPriority As Long) As Long


'=========== Setting API related in/output signal ================================================================================
' Set Z phase level of specific axis.
' uLevel : LOW(0), HIGH(1)
Public Declare Function AxmSignalSetZphaseLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' Return Z phase level of specific axis.
Public Declare Function AxmSignalGetZphaseLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long


' Set output level of Servo-On signal of specific axis.
' uLevel : LOW(0), HIGH(1)
Public Declare Function AxmSignalSetServoOnLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' Return output level of Servo-On signal of specific axis.
Public Declare Function AxmSignalGetServoOnLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long


' Set output level of Servo-Alarm Reset signal of specific axis.
' uLevel : LOW(0), HIGH(1)
Public Declare Function AxmSignalSetServoAlarmResetLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' Return output level of Servo-Alarm Reset signal of specific axis.
Public Declare Function AxmSignalGetServoAlarmResetLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long


' Set whether to use Inposition signal of specific axis and signal input level.
' uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
Public Declare Function AxmSignalSetInpos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long
' Return whether to use Inposition signal of specific axis and signal input level.
Public Declare Function AxmSignalGetInpos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long
' Return inposition signal input mode of specific axis.
Public Declare Function AxmSignalReadInpos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long


' Set whether to use emergency stop or not against to alarm signal input and set signal input level of specific axis.
' uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
Public Declare Function AxmSignalSetServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long
' Return whether to use emergency stop or not against to alarm signal input and set signal input level of specific axis.
Public Declare Function AxmSignalGetServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long
' Return input level of alarm signal of specific axis.
Public Declare Function AxmSignalReadServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long


' Set whether to use end limit sensor of specific axis and input level of signal.
' Available to set of slow down stop or emergency stop when end limit sensor is input.
' uStopMode: EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
' uPositiveLevel, uNegativeLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
Public Declare Function AxmSignalSetLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uStopMode As Long, ByVal uPositiveLevel As Long, ByVal uNegativeLevel As Long) As Long
' Return whether to use end limit sensor of specific axis , input level of signal and stop mode for signal input.
Public Declare Function AxmSignalGetLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStopMode As Long, ByRef upPositiveLevel As Long, ByRef upNegativeLevel As Long) As Long
' Return the input state of end limit sensor of specific axis.
Public Declare Function AxmSignalReadLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upPositiveStatus As Long, ByRef upNegativeStatus As Long) As Long


' Set whether to use software limit, count to use and stop method of specific axis.
' uUse       : DISABLE(0), ENABLE(1)
' uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
' uSelection : COMMAND(0), ACTUAL(1)
' Caution: When software limit is set in advance by using above API in origin detecting and is moving, if the detecting of origin is stopped during detecting, it becomes DISABLE.
Public Declare Function AxmSignalSetSoftLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long, ByVal uStopMode As Long, ByVal uSelection As Long, ByVal dPositivePos As Double, ByVal dNegativePos As Double) As Long
' Return whether to use software limit, count to use and stop method of specific axis.
Public Declare Function AxmSignalGetSoftLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long, ByRef upStopMode As Long, ByRef upSelection As Long, ByRef dpPositivePos As Double, ByRef dpNegativePos As Double) As Long
Public Declare Function AxmSignalReadSoftLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upPositiveStatus As Long, ByRef upNegativeStatus As Long) As Long


' Set the stop method of emergency stop(emergency stop/slowdown stop) ,or whether to use or not.
' uStopMode  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
' uLevel : LOW(0), HIGH(1), UNUSED(2), USED(3)
Public Declare Function AxmSignalSetStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uStopMode As Long, ByVal uLevel As Long) As Long
' Return the stop method of emergency stop(emergency stop/slowdown stop) ,or whether to use or not.
Public Declare Function AxmSignalGetStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStopMode As Long, ByRef upLevel As Long) As Long
' Return input state of emergency stop.
Public Declare Function AxmSignalReadStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long


' Output the Servo-On signal of specific axis.
' uOnOff : FALSE(0), TRUE(1) ( The case of universal 0 output)
Public Declare Function AxmSignalServoOn Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uOnOff As Long) As Long
' Return the output state of Servo-On signal of specific axis.
Public Declare Function AxmSignalIsServoOn Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upOnOff As Long) As Long


' Output the Servo-Alarm Reset signal of specific axis.
' uOnOff : FALSE(0), TRUE(1) (The case of universal 1 output)
Public Declare Function AxmSignalServoAlarmReset Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uOnOff As Long) As Long


' Set universal output value.
' uValue : Hex Value 0x00
Public Declare Function AxmSignalWriteOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uValue As Long) As Long
' Return universal output value.
Public Declare Function AxmSignalReadOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upValue As Long) As Long


' ML3 Only
' Return Brake sensor state of target axis.
Public Declare Function AxmSignalReadBrakeOn Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upOnOff As Long) As Long


' lBitNo : Bit Number(0 - 4)
' uOnOff : FALSE(0), TRUE(1)
' Set universal output values by bit.
Public Declare Function AxmSignalWriteOutputBit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBitNo As Long, ByVal uOnOff As Long) As Long
' Return universal output values by bit.
Public Declare Function AxmSignalReadOutputBit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBitNo As Long, ByRef upOnOff As Long) As Long


' Return universal input value in Hex value.
Public Declare Function AxmSignalReadInput Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upValue As Long) As Long

' lBitNo : Bit Number(0 - 4)
' Return universal input value by bit.
Public Declare Function AxmSignalReadInputBit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBitNo As Long, ByRef upOn As Long) As Long


' Set universal In/Out digital filter coefficient.
' uSignal: END_LIMIT(0), INP_ALARM(1), UIN_00_01(2), UIN_02_04(3)
' dBandwidthUsec: 0.2uSec~26666usec
Public Declare Function AxmSignalSetFilterBandwidth Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSignal As Long, ByVal dBandwidthUsec As Double) As Long


'========== API which verifies the state during motion moving and after moving. ============================================================
' Return number of bits of general purpose input.
Public Declare Function AxmSignalGetInputBitCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upInputCount As Long) As Long


' Return number of bits of general purpose output.
Public Declare Function AxmSignalGetOutputBitCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upOutputCount As Long) As Long


'========== API for checking status during or after motion. ==============================================================
' Return pulse output status of specified axis.(In motion state)
Public Declare Function AxmStatusReadInMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long


'  Return move pulse counter value of specific axis after start of move.
'  (pulse count value)"
Public Declare Function AxmStatusReadDrivePulseCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpPulse As Long) As Long


' Return DriveStatus register (status of in-motion) of specific Axis.
' Caution: All Motion Product is different Hardware bit signal. Let's refer Manual and AXHS.xxx
Public Declare Function AxmStatusReadMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long


' Return EndStatus(status of stop) register of specific axis.
' Caution: All Motion Product is different Hardware bit signal. Let's refer Manual and AXHS.xxx
Public Declare Function AxmStatusReadStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long


' Return Mechanical Signal Data(Current mechanical signal status)of specific axis.
' Caution: All Motion Product is different Hardware bit signal. Let's refer Manual and AXHS.xxx
Public Declare Function AxmStatusReadMechanical Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long


' Read current move velocity oo specific axis.
Public Declare Function AxmStatusReadVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpVel As Double) As Long


' Return the error between Command Pos and Actual Pos of specific axis.
Public Declare Function AxmStatusReadPosError Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpError As Double) As Long


' Verify the travel(traveled) distance to the final drive.
Public Declare Function AxmStatusReadDriveDistance Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpUnit As Double) As Long


' Set use the Position information Type of specific Axis.
' uPosType  : Select Position Information Type (Actual position / Command position)
'    POSITION_LIMIT '0' - Normal action, In all round action.
'    POSITION_BOUND '1' - Position cycle type, dNegativePos ~ dPositivePos Range
' Caution(PCI-Nx04)
' - If count value exceeds the max value, it becomes min value when setting BOUND.
' The other way, count value exceeds the min value, it becomes max value.

' dPositivePos setting range : 0 ~ positive number
' dNegativePos setting range : negative number ~ 0
Public Declare Function AxmStatusSetPosType Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uPosType As Long, ByVal dPositivePos As Double, ByVal dNegativePos As Double) As Long
' Return the Position Information Type of of specific axis.
Public Declare Function AxmStatusGetPosType Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upPosType As Long, ByRef dpPositivePos As Double, ByRef dpNegativePos As Double) As Long
' Set absolute encoder origin offset Position of specific axis. [Only for PCI-R1604-MLII]
Public Declare Function AxmStatusSetAbsOrgOffset Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOrgOffsetPos As Double) As Long
' Set absolute encoder origin offset Position of specific axis. [Only for PCI-R1604-MLII]
Public Declare Function AxmStatusGetAbsOrgOffset Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpOrgOffsetPos As Double) As Long


' Set the actual position of specific axis.
Public Declare Function AxmStatusSetActPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' Return the actual position of specific axis.
Public Declare Function AxmStatusGetActPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long
    Public Declare Function AxmStatusGetAmpActPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long


' Set command position of specific axis.
Public Declare Function AxmStatusSetCmdPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
' Return command position of specific axis.
Public Declare Function AxmStatusGetCmdPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long
' Set command position and actual position of specific axis
' Only RTEX use
Public Declare Function AxmStatusSetPosMatch Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long


' You can check motion status of specified axis at once by using this API.(Cmd, Act, Driver Status, Mechanical Signal, Universal Signal)
' Specify motion status information by dwMask setting of MOTION_INFO structure.
' dwMask : Display of the motion state (6bit) - ex) dwMask = Display all status if you set '0x1F'.
' The Level(In/Out) is not reflected which is set by user.
'    [0]        |    Command Position Read
'    [1]        |    Actual Position Read
'    [2]        |    Mechanical Signal Read
'    [3]        |    Driver Status Read
'    [4]        |    Universal Signal Input Read
'               |    Universal Signal Output Read
Public Declare Function AxmStatusReadMotionInfo Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef pMI As MOTION_INFO) As Long


' API for Network product only
' API for read AlarmCode of specified axis.
Public Declare Function AxmStatusRequestServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' API for read AlarmCode of specified axis.
' upAlarmCode      : Refer to Alarm Code of SERVOPACK.
' MR_J4_xxB        : Upper 16bit(Decimal value of 2 digits alarm code), Lower 16bit(Decimal value of 1digit detail alarm code)
' uReturnMode      : Set return condition of API.[Not used in SIIIH(MR-J4-xxB)]
' [0-Immediate]    : Return immediately after function execution.
' [1-Blocking]     : Does not return until the alarm code is read from SERVOPACK.
' [2-Non Blocking] : Does not return until the alarm code is read from SERVOPACK. but program is not blocked.
Public Declare Function AxmStatusReadServoAlarm Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uReturnMode As Long, ByRef upAlarmCode As Long) As Long
' The API to recieve alarm string about specified error code.
Public Declare Function AxmStatusGetServoAlarmString Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uAlarmCode As Long, ByVal lAlarmStringSize As Long, ByRef szAlarmString As String) As Long
    Public Declare Function AxmStatusReadServoAlarmString Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lAlarmStringSize As Long, ByRef szAlarmString As char*) As Long

' The API to Command to SERVOPACK for read Alarm History of specified axis.
Public Declare Function AxmStatusRequestServoAlarmHistory Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' The API to read SERVOPACK alarm history of specified axis.
' lpCount          : Number of read alarm history.
' upAlarmCode      : The array to return alarm history.
' uReturnMode      : Set return mode of this API.
' [0-Immediate]    : Return immediately after function execution.
' [1-Blocking]     : Not return until reading alarm code from SERVOPACK.
' [2-Non Blocking] : Not return until reading alarm code from SERVOPACK. but program is not blocked.
Public Declare Function AxmStatusReadServoAlarmHistory Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uReturnMode As Long, ByRef lpCount As Long, ByRef upAlarmCode As Long) As Long
' Clear SERVOPACK alarm history of specified axis.
Public Declare Function AxmStatusClearServoAlarmHistory Lib "AXL.dll" (ByVal lAxisNo As Long) As Long


'======== API related home. =============================================================================================================================================================================================
' Set home sensor level of specific axis.
' uLevel : LOW(0), HIGH(1)
Public Declare Function AxmHomeSetSignalLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
' Return home sensor level of specific axis.
Public Declare Function AxmHomeGetSignalLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long
' Verify current home signal input status. Hoe signal can be set by user optionally by using AxmHomeSetMethod API.
' upStatus : OFF(0), ON(1)
Public Declare Function AxmHomeReadSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long



' Parameters related to origin detecting must be set in order to detect origin of relevant axis.
' If the initialization is done properly by using MotionPara setting file, no separate setting is required.
' In the setting of origin detecting method, direction of detecting proceed, signal to be used for origin, active level of origin sensor and detecting/no detecting of encoder Z phase are set.
' Caution : When the level is set wrong, it may operate + direction even though ? direction is set, and may cause problem in finding home.
' (Refer the guide part of AxmMotSaveParaAll for detail information. )
' Use AxmSignalSetHomeLevel for home level.
' HClrTim : HomeClear Time : Queue time for setting origin detecting Encoder value.
' HmDir(Home direction): DIR_CCW(0): - direction    , DIR_CW(1) = + direction   // HOffset ? traveled distance after detecting of origin.
' uZphas: Set whether to detect of encoder Z phase after completion of the 1st detecting of origin.
' HmSig : PosEndLimit(0) -> +Limit
'         NegEndLimit(1) -> -Limit
'         HomeSensor (4) -> origin sensor(universal input 0)

Public Declare Function AxmHomeSetMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lHmDir As Long, ByVal uHomeSignal As Long, ByVal uZphas As Long, ByVal dHomeClrTime As Double, ByVal dHomeOffset As Double) As Long
' Return set parameters related to home.
Public Declare Function AxmHomeGetMethod Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpHmDir As Long, ByRef upHomeSignal As Long, ByRef upZphas As Long, ByRef dpHomeClrTime As Double, ByRef dpHomeOffset As Double) As Long


' Set Home Search Fine tunning Method (Don't care Setting by default).
' dHomeDogDistance[500 pulse]: Set Dog Length. (Unit = AxmMotSetMoveUnitPerPulse function Setting Unit)
' lLevelScanTime[100msec]: Set level status confirmation scan time. (msec[1~1000])
' dwFineSearchUse[USE]: Select find search method. (Default use 5Step, Select 0 use 3Step)
' dwHomeClrUse[USE]: Set After Home Search Automatically Command/Actual Position Set 0 value of  specific axis.
Public Declare Function AxmHomeSetFineAdjust Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dHomeDogLength As Double, ByVal lLevelScanTime As Long, ByVal uFineSearchUse As Long, ByVal uHomeClrUse As Long) As Long
' Return set Home  Search fine tunning Method parameters related to home.
Public Declare Function AxmHomeGetFineAdjust Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpHomeDogLength As Double, ByRef lpLevelScanTime As Long, ByRef upFineSearchUse As Long, ByRef upHomeClrUse As Long) As Long

    Public Declare Function AxmHomeSetInterlock Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uInterlockMode As Long, ByVal dInterlockData As Double) As Long
    Public Declare Function AxmHomeGetInterlock Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upInterlockMode As Long, ByRef dpInterlockData As Double) As Long


' Detect through several steps in order to detect origin quickly and precisely. Now, set velocities to be used for each step.
' The time of origin detecting and the accuracy of origin detecting are decided by setting of these velocities.
' Set velocity of origin detecting of each axis by changing velocities of each step.
' (Refer the guide part of AxmMotSaveParaAll for detail information.)
' API which sets velocity to be used in origin detecting.
' [dVelFirst]- 1st move velocity   [dVelSecond]- velocity after detecting   [dVelThird]- the last velocity  [dvelLast]- index detecting and in order to detect precisely.
' [dAccFirst]- 1st move acceleration [dAccSecond]-acceleration after detecting.
Public Declare Function AxmHomeSetVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelFirst As Double, ByVal dVelSecond As Double, ByVal dVelThird As Double, ByVal dVelLast As Double, ByVal dAccFirst As Double, ByVal dAccSecond As Double) As Long
' Return set velocity to be used in origin detecting.
Public Declare Function AxmHomeGetVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpVelFirst As Double, ByRef dpVelSecond As Double, ByRef dpVelThird As Double, ByRef dpVelLast As Double, ByRef dpAccFirst As Double, ByRef dpAccSecond As Double) As Long


' Start to detect origin.
' When origin detecting start API is executed, thread which will detect origin of relevant axis in the library is created automatically and it is automatically closed after carrying out of the origin detecting in sequence.
Public Declare Function AxmHomeSetStart Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' User sets the result of origin detecting optionally.
' When the detecting of origin is completed successfully by using origin detecting API, the result of detecting is set as HOME_SUCCESS.
' This API enables user to set result optionally without execution of origin detecting.
' uHomeResult Setup
' HOME_SUCCESS           = 0x01,
' HOME_SEARCHING         = 0x02,
' HOME_ERR_GNT_RANGE     = 0x10, // Gantry Home Range Over
' HOME_ERR_USER_BREAK    = 0x11, // User Stop Command
' HOME_ERR_VELOCITY      = 0x12, // Velocity is very slow and fast
' HOME_ERR_AMP_FAULT     = 0x13, // Servo Drive Alarm
' HOME_ERR_NEG_LIMIT     = 0x14, // (+)Limit sensor check (-)dir during Motion
' HOME_ERR_POS_LIMIT     = 0x15, // (-)Limit sensor check (+)dir during Motion
' HOME_ERR_NOT_DETECT    = 0x16, // not detect User set signal
' HOME_ERR_UNKNOWN       = 0xFF,
Public Declare Function AxmHomeSetResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uHomeResult As Long) As Long
' Return the result of origin detecting.
' Verify detecting result of origin detection API. When detecting of origin is started, it sets as HOME_SEARCHING, and if the detecting of origin is failed the reason of failure is set. Redo origin detecting after eliminating of failure reasons.
Public Declare Function AxmHomeGetResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upHomeResult As Long) As Long


' Return progress rate of origin detection.
' Progress rate can be verified when origin detection is commenced. When origin detection is completed, return 100% whether success or failure. The success or failure of origin detection result can be verified by using GetHome Result API.
' upHomeMainStepNumber : Progress rate of Main Step .
' In case of gentry FALSE upHomeMainStepNumber : When 0 , only selected axis is in proceeding, home progress rate is indicated upHomeStepNumber.
' In case of gentry TRUE upHomeMainStepNumber : When 0, master home is in proceeding, master home progress rate is indicated upHomeStepNumber.
' In case of gentry TRUE upHomeMainStepNumber : When 10 , slave home is in proceeding, master home progress rate is indicated upHomeStepNumber .
' upHomeStepNumber     : Indicate progress rate against to selected axis.
' In case of gentry FALSE  : Indicate progress rate against to selected axis only.
' In case of gentry TRUE, progress rate is indicated by sequence of master axis and slave axis.
Public Declare Function AxmHomeGetRate Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upHomeMainStepNumber As Long, ByRef upHomeStepNumber As Long) As Long




'======= Position move API =================================================================================

' If you want to set specified velocity unit in RPM(Revolution Per Minute),
' ex>    calculate rpm :
' 4500 rpm ?
' When unit/ pulse = 1 : 1, then it becomes pulse per sec, and
' if you want to set at 4500 rpm , then  4500 / 60 sec : 75 revolution / 1sec
' The number of pulse per 1 revolution of motor shall be known. This can be know by detecting of Z phase in Encoder.
' If 1 revolution:1800 pulse,  75 x 1800 = 135000 pulses are required.
' Operate by input Unit = 1, Pulse = 1800 into AxmMotSetMoveUnitPerPulse.

' Travel up to set distance or position.
' It moves by set velocity and acceleration up to the position set by absolute coordinates/ relative coordinates of specific axis.
' Velocity profile is set in AxmMotSetProfileMode API.
' It separates from API at the timing of pulse output start.
Public Declare Function AxmMoveStartPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long


' Travel up to set distance or position.
' It moves by set velocity and acceleration up to the position set by absolute coordinates/ relative coordinates of specific axis.
' Velocity profile is set in AxmMotSetProfileMode API
' It separates from API at the timing of pulse output finish.
Public Declare Function AxmMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long


' Move by set velocity.
' It maintain velocity mode move by velocity and acceleration  set against to specific axis.
' It separates from API at the timing of pulse output start.
' It moves toward to CW direction when Vel value is positive, CCW when negative.
Public Declare Function AxmMoveVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long


' It maintain velocity mode move by velocity and acceleration  set against to specific multi-axis.
' It separates from API at the timing of pulse output start.
' It moves toward to CW direction when Vel value is positive, CCW when negative.
Public Declare Function AxmMoveStartMultiVel Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Long

' Driving set velocity and acceleration rate of specified multi axis.
' Driving speed mode consistently according to SyncMode.
' It separates from API at the timing of pulse output start.
' It moves toward to CW direction when Vel value is positive, CCW when negative.
' dwSyncMode : Disable synchronous stop function(0), Only use syncronous stop function(1), Use Synchronous stop function for alarm(2)
Public Declare Function AxmMoveStartMultiVelEx Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByVal dwSyncMode As Long) As Long


' Driving in continuous speed mode with set speed and acceleration rate about specified multi axis.
' It separates from API at the timing of pulse output finish. The master axis moves at dVel speed, move at distance ratio of remaining axes.
' Only velocity of lowest axis number is read among corresponding chip.
Public Declare Function AxmMoveStartLineVel Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpDis As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long


' API which detects Edge of specific Input signal and makes emergency stop or slowdown stop.
' lDetect Signal : Select input signal to detect .
' lDetectSignal  : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
' Signal Edge    : Select edge direction of selected input signal (rising or falling edge).
'                  SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
' Move direction : CW when Vel value is positive, CCW when negative.
' SignalMethod   : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
' Caution: When SignalMethod is used as EMERGENCY_STOP(0), acceleration/deceleration is ignored and it is accelerated to specific velocity and emergency stop.
'          lDetectSignal is PosEndLimit , in case of searching NegEndLimit(0,1) active status of signal level is detected.
Public Declare Function AxmMoveSignalSearch Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal lDetectSignal As Long, ByVal lSignalEdge As Long, ByVal lSignalMethod As Long) As Long


' API which detects Edge of specific Input signal and makes move by user-specified value.(MLIII : Sigma-5/7 only)
' dVel           : It moves toward to CW direction when Vel value is positive, CCW when negative.
' dAccel         : Acceleration value
' dDecel         : Deceleration value(Generally, set for 50 times of dAccel value)
' lDetectSignal  : HomeSensor(4)
' dDis           : It is driven relative to the user-specified position based on the detection position of the input signal.
' Notice :
'         - It can be driven in reverse direction when input dDis value in direction opposite to driving direction.
'        - If velocity is fast and dDis value is small, It can be driven in reverse to go to final position when after motor has detect signal and stop.
'         - Home sensor must be set 'LOW' or 'HIGH' before use this API.
Public Declare Function AxmMoveSignalSearchAtDis Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lDetectSignal As Long, ByVal dDis As Double) As Long


' API which detects signal set in specific axis and travels in order to save the position.
' In case of searching acting API to select and find desired signal, save the position and read the value using AxmGetCapturePos.
' Signal Edge   : Select edge direction of selected input signal. (rising or falling edge).
'                 SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
' Move direction: CW when Vel value is positive, CCW when negative.
' SignalMethod  : EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
' lDetect Signal: Select input signal to detect edge .SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
' lDetectSignal : PosEndLimit(0), NegEndLimit(1), HomeSensor(4), EncodZPhase(5), UniInput02(6), UniInput03(7)
' lTarget       : COMMAND(0), ACTUAL(1)
' Caution: When SignalMethod is used as EMERGENCY_STOP(0), acceleration/deceleration is ignored and it is accelerated to specific velocity and emergency stop.
' lDetectSignal is PosEndLimit , in case of searching NegEndLimit(0,1) active status of signal level is detected.
Public Declare Function AxmMoveSignalCapture Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal lDetectSignal As Long, ByVal lSignalEdge As Long, ByVal lTarget As Long, ByVal lSignalMethod As Long) As Long
' API which verifies saved position value in 'AxmMoveSignalCapture' API.
Public Declare Function AxmMoveGetCapturePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpCapPotition As Double) As Long


' " API which travels up to set distance or position.
' When execute API, it starts relevant motion action and escapes from API without waiting until motion is completed ”
Public Declare Function AxmMoveStartMultiPos Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dpPos As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByVal uStopMode As Long) As Long


' Travels up to the distance which sets multi-axis or position.
' It moves by set velocity and acceleration up to the position set by absolute coordinates of specific axis. specific axes.
Public Declare Function AxmMoveMultiPos Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dpPos As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByVal uStopMode As Long) As Long



' When execute API, it starts open-loop torque motion action of specific axis.(only for MLII, Sigma 5 servo drivers)
' dTroque        : Percentage value(%) of maximum torque. (negative value : CCW, positive value : CW)
' dVel           : Percentage value(%) of maximum velocity.
' dwAccFilterSel : LINEAR_ACCDCEL(0), EXPO_ACCELDCEL(1), SCURVE_ACCELDECEL(2)
' dwGainSel      : GAIN_1ST(0), GAIN_2ND(1)
' dwSpdLoopSel   : PI_LOOP(0), P_LOOP(1)
'
Public Declare Function AxmMoveStartTorque Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dTorque As Double, ByVal dVel As Double, ByVal dwAccFilterSel As Long, ByVal dwGainSel As Long, ByVal dwSpdLoopSel As Long) As Long


' It stops motion during torque motion action.
' it can be only applied for AxmMoveStartTorque API.
Public Declare Function AxmMoveTorqueStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwMethod As Long) As Long



' To Move Set Position or distance
' Absolute coordinates / position set to the coordinates relative to the set speed / acceleration rate to drive of specific Axis.
' Velocity Profile is fixed Asymmetric trapezoid.
' Accel/Decel Setting Unit is fixed Unit/Sec^2
' When dAccel is not 0.0 and dDecel is 0.0, it accelerates from the previous speed to the specified speed without deceleration.
' If dAccel is not 0.0 and dDecel is not 0.0, acceleration from the previous speed to the specified speed without deceleration.
' If dAccel is 0.0 and dDecel is not 0.0, acceleration from the previous speed to the specified speed without deceleration.

' The following conditions must be satisfied.
' dVel[1] == dVel[3] must be satisfied.
' dVel [2] that can occur as a constant speed drive range is greater dPosition should be enough.
' Ex) dPosition = 10000;
' dVel[0] = 300., dAccel[0] = 200., dDecel[0] = 0.;    <== Acceleration
' dVel[1] = 500., dAccel[1] = 100., dDecel[1] = 0.;    <== Acceleration
' dVel[2] = 700., dAccel[2] = 200., dDecel[2] = 250.;  <== Acceleration, constant velocity, Deceleration
' dVel[3] = 500., dAccel[3] = 0.,   dDecel[3] = 150.;  <== Deceleration
' dVel[4] = 200., dAccel[4] = 0.,   dDecel[4] = 350.;  <== Deceleration
' Exits API at the point that pulse out starts.
Public Declare Function AxmMoveStartPosWithList Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPosition As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByVal lListNum As Long) As Long



' Is set by the distance to the target axis position or the position to increase or decrease the movement begins.
' lEvnetAxisNo    : Start condition occurs axis.
' dComparePosition: Conditions Occurrence Area of Start condition occurs axis.
' uPositionSource : Set Conditions Occurrence Area of Start condition occurs axis => COMMAND(0), ACTUAL(1)
' Cancellations after reservation AxmMoveStop, AxmMoveEStop, AxmMoveSStop use
' Motion Axis and Start condition occurs axis must be In same group(case by 2V04 In same module).
Public Declare Function AxmMoveStartPosWithPosEvent Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lEventAxisNo As Long, ByVal dComparePosition As Double, ByVal uPositionSource As Long) As Long


' It slowdown stops by deceleration set for specific axis.
' dDecel : Deceleration value when stop.
Public Declare Function AxmMoveStop Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dDecel As Double) As Long
' It slowdown stops by deceleration set for specific axis.(PCI-Nx04 Only)
' This API can decelerating immediately refardless of current acceleration/deceleration state. Also, it can be used for limited drive.
' -- Applicable functions : AxmMoveStartPos, AxmMoveVel, AxmLineMoveEx2.
' dDecel : Deceleration rate value at stop.
' Note : Deceleration rate value should be greater than or equal to deceleration rate of initial setting.
' Note : When deceleration setting is set to time unit, It must be less than or equal to initial settling time.
Public Declare Function AxmMoveStopEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dDecel As Double) As Long
' Stops specific axis emergently .
Public Declare Function AxmMoveEStop Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' Stops specific axis slow down.
Public Declare Function AxmMoveSStop Lib "AXL.dll" (ByVal lAxisNo As Long) As Long


'========= Overdrive API ============================================================================

' Overdrives position.
' Adjust number of specific pulse before the move of specific axis is finished.
' Cautions : In here when put in the position subjected to overdrive, as the travel distance is put into the position value of relative form,
'            position must be put in as position value of relative form.
Public Declare Function AxmOverridePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOverridePos As Double) As Long


' Set the maximum velocity subjected to overdirve before velocity overdriving of specific axis.
' Caution : If the velocity overdrive is done 5 times, the max velocity shall be set among them.
Public Declare Function AxmOverrideSetMaxVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOverrideMaxVel As Double) As Long

' Overdrive velocity.
' Set velocity variably during the move of specific axis. (Make sure to set variably during the motion.)
' Caution: Before use of AxmOverrideVel API, set the maximum velocity which can be set by AxmOverrideMaxVel
' EX> If velocity overdrive two times,
' 1. Set the highest velocity among the two as the highest setting velocity of AxmOverrideMaxVel.
' 2. Set the AxmOverrideVel  variably with the velocity in the moving of AxmMoveStartPos execution specific axis (including move API all) as the first velocity.
' 3. Set the AxmOverrideVel  variably with the velocity in the moving of specific axis (including move API all) as the 2nd velocity.
Public Declare Function AxmOverrideVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOverrideVel As Double) As Long


' Overdrive velocity.
' Set velocity variably during the move of specific axis. (Make sure to set variably during the motion.)
' Caution: Before use of AxmOverrideVel API, set the maximum velocity which can be set by AxmOverrideMaxVel
' EX> If velocity overdrive two times,
' 1. Set the highest velocity among the two as the highest setting velocity of AxmOverrideMaxVel.
' 2. Set the AxmOverrideAccelVelDecel  variably with the velocity in the moving of AxmMoveStartPos execution specific axis (including move API all) as the first velocity.
' 3. Set the AxmOverrideAccelVelDecel  variably with the velocity in the moving of specific axis (including move API all) as the 2nd velocity.
Public Declare Function AxmOverrideAccelVelDecel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dOverrideVel As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double) As Long


' Velocity overdrive at certain timing.
' API which becomes overdrive at the position when a certain position point and velocity to be overdrived
' lTarget : COMMAND(0), ACTUAL(1)
Public Declare Function AxmOverrideVelAtPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dOverridePos As Double, ByVal dOverrideVel As Double, ByVal lTarget As Long) As Long
' Override with specified velocity at specified times.
' lArraySize     : Set number of positions to override.
' *dpOverridePos : An array of positions to override. (It should be greater than or equal to set value at lArraySize.)
' *dpOverrideVel : Velocity array to be changed at position to override. (It should be greater than or equal to set value at lArraySize.)
' lTarget        : COMMAND(0), ACTUAL(1)
' dwOverrideMode : Specify how to start overriding.
'                : OVERRIDE_POS_START(0) - Start override at specified velocity at specified position.
'                : OVERRIDE_POS_END(1)   - Start override in advance to become specified velocity at specified position.
Public Declare Function AxmOverrideVelAtMultiPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArraySize As Long, ByRef dpOverridePos As Double, ByRef dpOverrideVel As Double, ByVal lTarget As Long, ByVal dwOverrideMode As Long) As Long

'========= Move API by master, slave gear ration. ===========================================================================
' Override with specified velocity/acceleration/deceleration at specified times.(MLII Only)
' lArraySize     : Set number of positions to override.
' *dpOverridePos : An array of positions to override. (It should be greater than or equal to set value at lArraySize.)
' *dpOverrideVel : Velocity array to be changed at position to override. (It should be greater than or equal to set value at lArraySize.)
' *dpOverrideAccelDecel : Acceleration/Deceleration array to be changed at position to override. (It should be greater than or equal to set value at lArraySize.)
' lTarget        : COMMAND(0), ACTUAL(1)
' dwOverrideMode : Specify how to start overriding.
'                : OVERRIDE_POS_START(0) - Start overriding at specified velocity at specified position.
'                : OVERRIDE_POS_END(1)   - Start overriding in advance to become specified velocity at specified position.
'                : OVERRIDE_POS_AUTO(2)  - Start overriding at specified velocity at specified position when in acceleration section.
'                                          Also, start overriding in advance to become specified velocity at specified position when in deceleration section.


Public Declare Function AxmOverrideVelAtMultiPos2 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArraySize As Long, ByRef dpOverridePos As Double, ByRef dpOverrideVel As Double, ByRef dpOverrideAccelDecel As Double, ByVal lTarget As Long, ByVal dwOverrideMode As Long) As Long


'========= Move API by master, slave gear ration. ===========================================================================

' In Electric Gear mode, set gear ratio between master axis and slave axis.
' dSlaveRatio : Gear ratio of slave against to master axis ( 0 : 0% , 0.5 : 50%, 1 : 100%)
Public Declare Function AxmLinkSetMode Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSlaveAxisNo As Long, ByVal dSlaveRatio As Double) As Long
' In Electric Gear mode, return gear ratio between master axis and slave axis.
Public Declare Function AxmLinkGetMode Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSlaveAxisNo As Long, ByRef dpGearRatio As Double) As Long
' Reset electric gear ration between Master axis and slave axis.
Public Declare Function AxmLinkResetMode Lib "AXL.dll" (ByVal lMasterAxisNo As Long) As Long


'======== API related to gentry ===========================================================================================================================================================
' Motion module supports gentry move system control which two axes are linked mechanically..
' When set master axis for gentry control by using this API, relevant slave axis synchronizes with master axis and moves.
' However after setting of gentry, even if any move command or stop command is directed, they are ignored
' uSlHomeUse     : Whether to use home of slave axis or not ( 0 - 2)
'             (0 : Search home of master axis without using home of slave axis.)
'             (1 : Search home of master axis, slave axis. Compensating by applying slave dSlOffset value.)
'             (2 : Search home of master axis, slave axis. No compensating by applying slave dSlOffset value.))
' dSlOffset      : Offset value of slave axis
' dSlOffsetRange : Set offset value range of slave axis.
' Caution in use : When gentry is enabled, it is normal operation if the slave axis is verified as Inmotion by AxmStatusReadMotion API in its motion, and verified as True.

'                When slave axis is verified by AxmStatusReadMotion, if InMotion is False then Gantry Enable is not available, therefore verify whether alarm hits limit.

Public Declare Function AxmGantrySetEnable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSlaveAxisNo As Long, ByVal uSlHomeUse As Long, ByVal dSlOffset As Double, ByVal dSlOffsetRange As Double) As Long



' The method to know offset value of Slave axis.
' A. Servo-On both master and slave.
' B. After set uSlHomeUse = 2 in AxmGantrySetEnableAPI, then search home by using  AxmHomeSetStart API.
' C. After search home, twisted offset value of master axis and slave axis can be seen by reading command value of master axis.
' D. Read Offsetvalue, and put it into dSlOffset argument of AxmGantrySetEnable API.
' E. As dSlOffset value is the slave axis value against to master axis, put its value with reversed sign as ?dSlOffset.
' F. dSIOffsetRange means the range of Slave Offset, it is used to originate error when it is out of the specified range.
' G. If the offset has been input into AxmGantrySetEnable API, in AxmGantrySetEnable API,after  set uSlHomeUse = 1 then search home by using AxmHomeSetStart API.

' In gentry move, return parameter set by user.
Public Declare Function AxmGantryGetEnable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef upSlHomeUse As Long, ByRef dpSlOffset As Double, ByRef dpSlORange As Double, ByRef upGatryOn As Long) As Long
' Motion module releases gentry move system control which two axes are linked mechanically.
Public Declare Function AxmGantrySetDisable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSlaveAxisNo As Long) As Long


' Only for PCI-Rxx04-MLII.
' Set Synchronous compensation of Gentry System.
' lMasterGain, lSlaveGain : Set % value of Between the two axes about position deviation.
' lMasterGain, lSlaveGain : If Set Input 0 Not Use. Default value : 0%
Public Declare Function AxmGantrySetCompensationGain Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lMasterGain As Long, ByVal lSlaveGain As Long) As Long
' Return Synchronous compensation of Gentry System.
Public Declare Function AxmGantryGetCompensationGain Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef lpMasterGain As Long, ByRef lpSlaveGain As Long) As Long


' Set position deviation range between master and slave.
' API for PCI-R1604 / PCI-R3200-MLIII only
' lMasterAxisNo : Gantry Master Axis No
' dErrorRange : Setting value for position deviation range.
' uUse : A value for mode setting.
'      ( 0 : Disable)
'      ( 1 : Normal mode)
'      ( 2 : Flag Latch mode)
'      ( 3 : Flag Latch mode + SSTOP when error is occured)
'      ( 4 : Flag Latch mode + ESTOP when error is occured)
Public Declare Function AxmGantrySetErrorRange Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal dErrorRange As Double, ByVal uUse As Long) As Long
' Return setting value about position deviation range between master and slave.
Public Declare Function AxmGantryGetErrorRange Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef dpErrorRange As Double, ByRef upUse As Long) As Long
' Return result of comparing position deviation value between master and slave.
' dwpStatus : FALSE(0) -> Range of position deviation between master and slave is less than setting range. (Normal state)
'             TRUE(1)  -> Range of position deviation between master and slave is greater than setting range. (Abnormal state)
' It is returned 'AXT_RT_SUCCESS' only when Gantry Enable && Master/Slave's servo on state is satisfied.
' Call the 'AxmGantryReadErrorRangeComparePos', if you want to reset Latch Flag in case of latch mode.
Public Declare Function AxmGantryReadErrorRangeStatus Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef dwpStatus As Long) As Long
' Return position deviation value between master and slave.
' Maintain position deviation value at time of previous error occurrence until next error is occured.
' You should read only when 'dwpStatus' is 1. If you read ComparePos continuously, response speed will be slowed down by overload.
Public Declare Function AxmGantryReadErrorRangeComparePos Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef dpComparePos As Double) As Long






'==== Regular interpolation API ============================================================================================================================================;
' Do linear interpolate.
' API which moves multi-axis linear interpolation by specifying start point and ending point. It escapes from API after commencing of move.
' When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the queue which moves linear interpolation by specifying start point and ending point in the specified  coordinates system.
' For the continuous interpolation move of linear profile, save it in internal queue and start by using AxmContiStart API.
Public Declare Function AxmLineMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' Do linear interpolate. (Software)
' API which moves multi-axis linear interpolation by specifying start point and ending point. It escapes from API after commencing of move.
' When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the queue which moves linear interpolation by specifying start point and ending point in the specified  coordinates system.
' For the continuous interpolation move of linear profile, save it in internal queue and start by using AxmContiStart API.
Public Declare Function AxmLineMoveEx2 Lib "AXL.dll" (ByVal lCoord As Long, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' Interpolate 2 axis arc
' API which moves arc interpolation by specifying start point, ending point and center point. It escapes from API after commencing of move.
' When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying start point, ending point and center point in the specified  coordinates system.
' For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
' lAxisNo = 2 axis array , dCenterPos = center point X,Y array , dEndPos = ending point X,Y array.
' uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
Public Declare Function AxmCircleCenterMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dCenterPos As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long


' API which arc interpolation moves by specifying middle point and ending point. It escapes from API after commencing of move.
' When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying middle point and ending point in the specified  coordinates system.
' For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
' lAxisNo = 2 axis array , dMidPos = middle point, X,Y array , dEndPos = ending point X,Y array, lArcCircle = arc(0), circle(1)
Public Declare Function AxmCirclePointMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dMidPos As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArcCircle As Long) As Long

Public Declare Function AxmCirclePointMoveEx Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef lAxisNo As Long, ByRef dpMidPos As Double, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArcCircle As Long, ByVal lArraySize As Long) As Long


' API which arc interpolation moves by specifying start point, ending point and radius. It escapes from API after commencing of move.
' When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying start point, ending point and radius in the specified  coordinates system.
' For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
' lAxisNo = 2 axis array , dRadius = radius, dEndPos = ending point X,Y array , uShortDistance = small circle(0), large circle(1)
' uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
Public Declare Function AxmCircleRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByVal dRadius As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long) As Long


' API which arc interpolation moves by specifying start point, revolution angle and radius. It escapes from API after commencing of move.
' When it is used with AxmContiBeginNode and AxmContiEndNode, it becomes Save API in the arc interpolation queue which moves by specifying start point, revolution angle and radius in the specified  coordinates system.
' For the profile arc continuous interpolation move, save it internal queue and start by using AxmContiStart API.
' lAxisNo = 2 axis array , dCenterPos = center point X,Y array , dAngle = angle.
' uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
Public Declare Function AxmCircleAngleMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dCenterPos As Double, ByVal dAngle As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long


'==== continuous interpolation API ============================================================================================================================================;
'Set continuous interpolation axis mapping in specific coordinates system.
'(Start axis mapping number from 0)
' Caution: In the axis mapping, the input must be started from smaller number.
'         In here, the axis of smallest number becomes master.
Public Declare Function AxmContiSetAxisMap Lib "AXL.dll" (ByVal lCoord As Long, ByVal lSize As Long, ByRef lpRealAxesNo As Long) As Long
' Return continuous interpolation axis mapping in specific coordinates system.
Public Declare Function AxmContiGetAxisMap Lib "AXL.dll" (ByVal lCoord As Long, ByRef lpSize As Long, ByRef lpRealAxesNo As Long) As Long
    Public Declare Function AxmContiResetAxisMap Lib "AXL.dll" (ByVal lCoordinate As Long) As Long


' Set continuous interpolation axis absolute/relative mode in specific coordinates system.
' (Caution : available to use only after axis mapping)
' St travel distance calculation mode of specific axis.
' uAbsRelMode : POS_ABS_MODE '0' - absolute coordinate system
'               POS_REL_MODE '1' - relative coordinate system
Public Declare Function AxmContiSetAbsRelMode Lib "AXL.dll" (ByVal lCoord As Long, ByVal uAbsRelMode As Long) As Long
' Return interpolation axis absolute/relative mode in specific coordinates system.
Public Declare Function AxmContiGetAbsRelMode Lib "AXL.dll" (ByVal lCoord As Long, ByRef upAbsRelMode As Long) As Long


' API which verifies whether internal Queue for the interpolation move is empty in specific coordinate system.
Public Declare Function AxmContiReadFree Lib "AXL.dll" (ByVal lCoord As Long, ByRef upQueueFree As Long) As Long
' API which verifies the number of interpolation move saved in internal Queue for the interpolation move in specific coordinate system
Public Declare Function AxmContiReadIndex Lib "AXL.dll" (ByVal lCoord As Long, ByRef lpQueueIndex As Long) As Long

' API which deletes all internal Queue saved for the continuous interpolation move in specific coordinate system
Public Declare Function AxmContiWriteClear Lib "AXL.dll" (ByVal lCoord As Long) As Long


' Start registration of tasks to be executed in continuous interpolation at the specific  coordinate system. After call this API,
' all motion tasks to be executed before calling of AxmContiEndNode API are not execute actual motion, but are registered as continuous interpolation motion,
' and when AxmContiStart API is called, then the registered motions execute actually
Public Declare Function AxmContiBeginNode Lib "AXL.dll" (ByVal lCoord As Long) As Long
' Finish registration of tasks to be executed in continuous interpolation at the specific  coordinate system.
Public Declare Function AxmContiEndNode Lib "AXL.dll" (ByVal lCoord As Long) As Long


' Start continuous interpolation.
' if dwProfileset is  CONTI_NODE_VELOCITY(0), use continuous interpolation.
'                     CONTI_NODE_MANUAL(1)  , set profile interpolation use.
'                     CONTI_NODE_AUTO(2)    , use auto-profile interpolation.

Public Declare Function AxmContiStart Lib "AXL.dll" (ByVal lCoord As Long, ByVal dwProfileset As Long, ByVal lAngle As Long) As Long
' API which verifies whether the continuous interpolation is moving in the specific coordinate system.
Public Declare Function AxmContiIsMotion Lib "AXL.dll" (ByVal lCoord As Long, ByRef upInMotion As Long) As Long

' API which verifies the index number of the continuous interpolation that is being moving currently while the continuous interpolation is moving in the specific coordinate system.
Public Declare Function AxmContiGetNodeNum Lib "AXL.dll" (ByVal lCoord As Long, ByRef lpNodeNum As Long) As Long
' API which verifies the index number of the continuous interpolation that is being moving currently while the continuous interpolation is moving in the specific coordinate system.
Public Declare Function AxmContiGetTotalNodeNum Lib "AXL.dll" (ByVal lCoord As Long, ByRef lpNodeNum As Long) As Long


' Outputs digital signal from a specific motion segment.
' It should be used between the AxmContiBeginNode function and the AxmContiEndNode function.
' It is valid only for continuous interpolation drive function (ex: AxmLineMove, AxmCircleCenterMove, etc ...).
' Digital output is made earlier than the condition based on the end point of the next continuous interpolation drive function.
'
' lSize        : Number of IO contacts to be output simultaneously (1~8)
' lModuleNo    : If dwModuleType is 0, it is axis number. if dwModuleType is 1, it is Digital I / O Module No.
' dwModuleType : Motion I/O Output(Output of the slave itself)(0), Digital I/O Output(1)
'
' The following four parameters can be used to control multiple output contacts simultaneously by entering them in an array of lSize.
' lpBit          : Offset position for output contact
' lpOffOn        : Output value of corresponding output contact. LOW(0), HIGH(1)
' dpDistTime     : Distance(pulse) or Time(msec) ==> Based on the motion profile end point.
' lpDistTimeMode : Distance mode(0), Time mode(1) ==> Based on the motion profile end point.
Public Declare Function AxmContiDigitalOutputBit Lib "AXL.dll" (ByVal lCoord As Long, ByVal lSize As Long, ByVal lModuleType As Long, ByRef lpModuleNo As Long, ByRef lpBit As Long, ByRef lpOffOn As Long, ByRef dpDistTime As Double, ByRef lpDistTimeMode As Long) As Long

    Public Declare Function AxmContiReadStop Lib "AXL.dll" (ByVal lCoord As Long, ByRef upStatus As Long) As Long

    Public Declare Function AxmContiSetLineMoveVelMode Lib "AXL.dll" (ByVal lCoord As Long, ByVal uVelMode As Long, ByVal lMasterAxisNo As Long) As Long
    Public Declare Function AxmContiGetLineMoveVelMode Lib "AXL.dll" (ByVal lCoord As Long, ByRef upVelMode As Long, ByRef lpMasterAxisNo As Long) As Long

    Public Declare Function AxmContiSetCheckSoftLimit Lib "AXL.dll" (ByVal lCoord As Long, ByVal uUse As Long) As Long
    Public Declare Function AxmContiGetCheckSoftLimit Lib "AXL.dll" (ByVal lCoord As Long, ByRef upUse As Long) As Long

    Public Declare Function AxmContiSetConnectionRadius Lib "AXL.dll" (ByVal lCoord As Long, ByVal dRadius As Double) As Long
    Public Declare Function AxmContiSetConnectionMaxCentripetalAccel Lib "AXL.dll" (ByVal lCoord As Long, ByVal dMaxAccel As Double) As Long



'==================== trigger API ===============================================================================================================================
' Precautions : If you want set trigger position, you should be set according to setting status of Unit/Pulse.
'               If trigger position unit is smaller than Unit/Pulse, you can't output to desired position exactly because minimum unit will be set to UNIT/PULSE.

' Set whether to use of trigger function, output level, position comparator, trigger signal delay time and trigger output mode ino specific axis.
'  dTrigTime  : trigger output time
'             : 1usec - max 50msec ( set 1 - 50000)
'  upTriggerLevel  : whether to use or not use     => LOW(0), HIGH(1), UNUSED(2), USED(3)
'  uSelect         : Standard position to use    => COMMAND(0), ACTUAL(1)
'  uInterrupt      : set interrupt        => DISABLE(0), ENABLE(1)

' Set trigger signal delay time , trigger output level and trigger output method in specific axis.
Public Declare Function AxmTriggerSetTimeLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dTrigTime As Double, ByVal uTriggerLevel As Long, ByVal uSelect As Long, ByVal uInterrupt As Long) As Long
' Return trigger signal delay time , trigger output level and trigger output method to specific axis.
Public Declare Function AxmTriggerGetTimeLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpTrigTime As Double, ByRef upTriggerLevel As Long, ByRef upSelect As Long, ByRef upInterrupt As Long) As Long


'  uMethod :   PERIOD_MODE   0x0 : cycle trigger method using trigger position value
'              ABS_POS_MODE   0x1 : Trigger occurs at trigger absolute position,  absolute position method
'  dPos : in case of cycle selection : the relevant position  for output by position and position.
' in case of absolute selection: The position on which to output, If same as this position then output goes out unconditionally.
Public Declare Function AxmTriggerSetAbsPeriod Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMethod As Long, ByVal dPos As Double) As Long
' Return whether to use of trigger function, output level, position comparator, trigger signal delay time and trigger output mode to specific axis.
Public Declare Function AxmTriggerGetAbsPeriod Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMethod As Long, ByRef dpPos As Double) As Long


'  Output the trigger by regular interval from the starting position to the ending position specified by user.
Public Declare Function AxmTriggerSetBlock Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dStartPos As Double, ByVal dEndPos As Double, ByVal dPeriodPos As Double) As Long
' Read trigger setting value of 'AxmTriggerSetBlock' API.
Public Declare Function AxmTriggerGetBlock Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpStartPos As Double, ByRef dpEndPos As Double, ByRef dpPeriodPos As Double) As Long

' User outputs a trigger pulse.
Public Declare Function AxmTriggerOneShot Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
' User outputs a trigger pulse after several seconds.
Public Declare Function AxmTriggerSetTimerOneshot Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lmSec As Long) As Long
' Output absolute position trigger infinite absolute position output.
Public Declare Function AxmTriggerOnlyAbs Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lTrigNum As Long, ByRef dpTrigPos As Double) As Long
' Reset trigger settings.
Public Declare Function AxmTriggerSetReset Lib "AXL.dll" (ByVal lAxisNo As Long) As Long


'======== CRC( Remaining pulse clear API) =====================================================================

'Level   : LOW(0), HIGH(1), UNUSED(2), USED(3)
'uMethod : Available to set the width of remaining pulse eliminating output signal pulse in 2 - 6.
'          0: Don't care , 1: Don't care, 2: 500 uSec, 3:1 mSec, 4:10 mSec, 5:50 mSec, 6:100 mSec

'Set whether to use CRC signal in specific axis and output level.
Public Declare Function AxmCrcSetMaskLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long, ByVal lMethod As Long) As Long
' Return whether to use CRC signal of specific axis and output level.
Public Declare Function AxmCrcGetMaskLevel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long, ByVal lMethod As Long) As Long


'uOnOff  : Whether to generate CRC signal to the Program or not.  (FALSE(0),TRUE(1))

' Force to generate CRC signal to the specific axis.
Public Declare Function AxmCrcSetOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uOnOff As Long) As Long
' Return whether to forcedly generate CRC signal of specific axis.
Public Declare Function AxmCrcGetOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upOnOff As Long) As Long



'====== MPG(Manual Pulse Generation) API ===========================================================

' lInputMethod : Available to set 0-3. 0:OnePhase, 1:TwoPhase1, 2:TwoPhase2, 3:TwoPhase4
' lDriveMode   : Available to set 0-5
'                0 :MPG continuous mode ,1 :MPG PRESET mode (Travel up to specific pulse), 2 :COMMAND ABSOLUTE MPG PRESET mode
'                3 :ACTUAL ABSOLUTE MPG PRESET mode ,4 :COMMAND ABSOLUTE ZERO MPG PRESET mode, 5 :ACTUAL ABSOLUTE ZERO MPG PRESET mode
' MPGPos       : the travel distance by every MPG input signal

' MPGdenominator: Divide value in MPG(Enter manual pulse generating device)movement
' dMPGnumerator : Product value in MPG(Enter manual pulse generating device)movement
' dwNumerator   : Available to set max(from 1 to  64)
' dwDenominator : Available to set max(from 1 to  4096)
' dMPGdenominator = 4096 and MPGnumerator=1 mean that
' the output is 1 by 1 pulse as 1:1 if one turn of MPG is 200pulse.
' If dMPGdenominator = 4096 and MPGnumerator=2 , then it means the output is 2 by 2 pulse as 1:2.
' In here, MPG PULSE = ((Numerator) * (Denominator)/ 4096 ) It’s the calculation which outputs to the inside of chip.

' Set MPG input method, Drive move mode, travel distance, MPG velocity in specific axis.
Public Declare Function AxmMPGSetEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lInputMethod As Long, ByVal lDriveMode As Long, ByVal dMPGPos As Double, ByVal dVel As Double, ByVal dAccel As Double) As Long
' Return MPG input method, Drive move mode, travel distance, MPG velocity in specific axis.
Public Declare Function AxmMPGGetEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpInputMethod As Long, ByRef lpDriveMode As Long, ByRef dpMPGPos As Double, ByRef dpVel As Double, ByRef dpAccel As Double) As Long


' Set the pulse ratio to travel per pulse in MPG drive move mode to specific axis.
Public Declare Function AxmMPGSetRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uMPGnumerator As Long, ByVal uMPGdenominator As Long) As Long
' Return the pulse ratio to travel per pulse in MPG drive move mode to specific axis.
Public Declare Function AxmMPGGetRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMPGnumerator As Long, ByRef upMPGdenominator As Long) As Long

' Release MPG drive settings to specific axis.
Public Declare Function AxmMPGReset Lib "AXL.dll" (ByVal lAxisNo As Long) As Long



'======= Helical move ===========================================================================
' API which moves helical interpolation by specifying start point, ending point and center point to specific coordinate system.
' API which moves helical continuous interpolation by specifying start point, ending point and center point to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
' API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
'dCenterPos = center point X,Y , dEndPos = ending point X,Y.
' uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
Public Declare Function AxmHelixCenterMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dCenterXPos As Double, ByVal dCenterYPos As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long


' API which moves helical interpolation by specifying start point, ending point and radius to specific coordinate system.
' API which moves helical continuous interpolation by specifying middle point and ending point to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
' API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
' dMidPos = middle point X,Y  , dEndPos = ending point X,Y
Public Declare Function AxmHelixPointMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dMidXPos As Double, ByVal dMidYPos As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long


' API which moves helical interpolation by specifying start point, ending point and radius to specific coordinate system.
' API which moves helical continuous interpolation by specifying middle point ,ending point and radius to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
' API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
' dRadius = radius, dEndPos = ending point X,Y  , uShortDistance = small circle(0), large circle(1)
' uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
Public Declare Function AxmHelixRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dRadius As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long) As Long


' API which moves helical interpolation by specifying start point, revolution angle and radius to specific coordinate system.
' API which moves helical continuous interpolation by specifying start point , revolution angle and radius to specific coordinate system when it is used with AxmContiBeginNode and  AxmContiEndNode together.
' API which saves in internal Queue in order to move the arc continuous interpolation. It is started using AxmContiStart API. ( It is used with continuous interpolation API together)
' dCenterPos = center point X,Y , dAngle = angle.
' uCWDir   DIR_CCW(0): Counterclockwise direction,   DIR_CW(1) Clockwise direction
Public Declare Function AxmHelixAngleMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dCenterXPos As Double, ByVal dCenterYPos As Double, ByVal dAngle As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long



'======== Spline move ===========================================================================

' It’s not used with AxmContiBeginNode and AxmContiEndNode together.
' API which moves spline continuous interpolation. API which saves in internal Queue in order to move the arc continuous interpolation.
'It is started using AxmContiStart API. ( It is used with continuous interpolation API together)

' lPosSize : Minimum more than 3 pieces.
' Enter 0 as for dPoZ value when it is used with 2 axes.
' Enter 3 piece as for axis mapping and dPosZ value when it is used with 3axes.
Public Declare Function AxmSplineWrite Lib "AXL.dll" (ByVal lCoord As Long, ByVal lPosSize As Long, ByRef dpPosX As Double, ByRef dpPosY As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dPosZ As Double, ByVal lPointFactor As Long) As Long


'======== Compensation Table ====================================================================
' API which set the parameters for using the geometric compensation feature (Mechatrolink-II products)
' lNumEntry : minimum entries are 2, maximum entries are 512.
' dStartPos : starting relative position to apply the compensation.
' dpPosition, dpCorrection : arrays of position and correction values.
' bRollOver : enable/disable the roll over feature if the table can not cover the motor travel distance.
Public Declare Function AxmCompensationSet Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lNumEntry As Long, ByVal dStartPos As Double, ByRef dpPosition As Double, ByRef dpCorrection As Double, ByVal lRollOver As Long) As Long
' Return the number of entry, start position, array of position for moving, array of correction for compensating, setting RollOver feature on specific axis.
Public Declare Function AxmCompensationGet Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpNumEntry As Long, ByRef dpStartPos As Double, ByRef dpPosition As Double, ByRef dpCorrection As Double, ByRef lpRollOver As Long) As Long

' API which enable/disable the compensation feature.
Public Declare Function AxmCompensationEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lEnable As Long) As Long
' Return the setting enable/disable the compensation feature on specific axis.
Public Declare Function AxmCompensationIsEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpEnable As Long) As Long
' Return Current Position Compensation Value
Public Declare Function AxmCompensationGetCorrection Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpCorrection As Double) As Long

' Functions that make settings related to backlash
' > lBacklashDir: Set driving direction to apply backlash compensation (set same as home search direction)
'   - [0] -> Applies the specified backlash when the Command Position value is driven in (+) direction.
'   - [1] -> Applies the specified backlash when the Command Position value is driven in (-) direction.
'   - Ex1) When lBacklashDir is 0 and backlash is 0.01, the actual moving position becomes 100.01 when moving from 0.0 to 100.0
'   - Ex2) When lBacklashDir is 0 and backlash is 0.01, the actual moving position becomes -100.0 when moving from 0.0 to> -100.0
'   NOTANDUM
'   - For accurate backlash compensation, move backward (+) or (-) by the amount of backlash at the end of the home search,
'     complete the home search, and use backlash compensation.
'     If backlash_dir is driven by backlash_dir [1] (-) and backlash_dir is set to [0] (+) if backlash_dir is driven by backlash_dir.
' > dBacklash: Sets the amount of backlash that occurs in the direction of change from the mechanical direction to the opposite direction.
' { RETURN VALUE }
'   - [0] -> When Backlash setup succeeded
Public Declare Function AxmCompensationSetBacklash Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lBacklashDir As Long, ByVal dBacklash As Double) As Long
' Returns the configuration related to backlash.
Public Declare Function AxmCompensationGetBacklash Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpBacklashDir As Long, ByRef dpBacklash As Double) As Long
' Function to set / check whether to use backlash
' > dwEnable: Specify whether to use backlash compensation
'   - [0]DISABLE -> Disable backlash compensation
'   - [1]ENABLE  -> Enable backlash compensation
' { RETURN VALUE }
'   - [0]    -> Backlash setting When return is successful
'   - [4303] -> When the backlash compensation function is not set
Public Declare Function AxmCompensationEnableBacklash Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwEnable As Long) As Long

Public Declare Function AxmCompensationIsEnableBacklash Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpEnable As Long) As Long
' When backlash compensation function is used, it moves left and right by the amount of backlash to automatically align the position of the equipment (used once after servo-on)
' > dVel: Movement speed[unit / sec]
' > dAccel: Movement acceleration[unit / sec^2]
' > dAccel: Movement deceleration[unit / sec^2]
' > dWaitTime: Waiting time to return to original position after driving backlash amount[msec]
' { RETURN VALUE }
'   - [0]    -> When positioning for backlash compensation is successful
'   - [4303] -> When the backlash compensation function is not set
Public Declare Function AxmCompensationSetLocating Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dWaitTime As Double) As Long


'======== Electronic CAM ========================================================================
' API which set the parameters for using the Ecam feature (Mechatrolink-II products)
' lAxisNo : one slave axis only has one master axis.
' lMasterAxis : one master axis can have more than one slave axis.
' lNumEntry : minimum entries are 2, maximum entries are 512.
' dMasterStartPos : starting relative position to apply Ecam on master axis.
' dpMasterPos, dpSlavePos : arrays of position values on master and slave axis.
Public Declare Function AxmEcamSet Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lMasterAxisNo As Long, ByVal lNumEntry As Long, ByVal dMasterStartPos As Double, ByRef dpMasterPos As Double, ByRef dpSlavePos As Double) As Long
' Ecam Set With Select Source (COMMAND :0, ACTUAL : 1)
Public Declare Function AxmEcamSetWithSource Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lMasterAxisNo As Long, ByVal lNumEntry As Long, ByVal dMasterStartPos As Double, ByRef dpMasterPos As Double, ByRef dpSlavePos As Double, ByRef dwSource As Long) As Long
' Return the number of master axis, entries, start position of master axis, array of position on master axis, array of position on slave axis.
Public Declare Function AxmEcamGet Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpMasterAxisNo As Long, ByRef lpNumEntry As Long, ByRef dpMasterStartPos As Double, ByRef dpMasterPos As Double, ByRef dpSlavePos As Double) As Long
' Ecam Get With Select Source
Public Declare Function AxmEcamGetWithSource Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpMasterAxisNo As Long, ByRef lpNumEntry As Long, ByRef dpMasterStartPos As Double, ByRef dpMasterPos As Double, ByRef dpSlavePos As Double, ByRef dwpSource As Long) As Long

' API which enable the Ecam feature on slave axis.
Public Declare Function AxmEcamEnableBySlave Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lEnable As Long) As Long
' Return the setting enable/disable the Ecam feature on slave axis.
Public Declare Function AxmEcamEnableByMaster Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lEnable As Long) As Long
' API which enable the Ecam feature on corresponding slave axes.
Public Declare Function AxmEcamIsSlaveEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpEnable As Long) As Long


'------------------------------------------------------------------------------------------------

' ======== Servo Status Monitor =====================================================================================
' Set up for exception handling function of specified axis. (MLII : Sigma-5 and SIIIH : MR_J4_xxB only)
' dwSelMon(0~3): select monitoring information.
'          [0] : Torque
'          [1] : Velocity of motor
'          [2] : Accel. of motor
'          [3] : Decel. of motor
'          [4] : Position error between Cmd. position and Act. position.
' dwActionValue: Set reference value of abnormal operation. According to each information, meaning of setting value is different.
'          [0] : Not handling exception about selected monitoring information in dwSelMon.
'          [1] : Apply handling exception about selected monitoring information in dwSelMon.
' dwAction(0~3): Set exception handling method when surveillance information is confirmed more than dwActionValue.
'          [0] : Warning(setting flag only)
'          [1] : Warning(setting flag) + Slow-down stop
'          [2] : Warning(setting flag) + Emergency stop
'          [3] : Warning(setting flag) + Emergency stop + Servo-Off
' * Note : You can be set exception handling separetely for 5 SelMon info. If you don't want to exception handling in use,
'           be sure to set the ActionValue of specific SelMon info to 0 to disable the monitoring function.
' Set exception function of specific axis. (Only for MLII, Sigma-5)
Public Declare Function AxmStatusSetServoMonitor Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelMon As Long, ByVal dActionValue As Double, ByVal uAction As Long) As Long
' Return exception function of specific axis. (Only for MLII, Sigma-5)
Public Declare Function AxmStatusGetServoMonitor Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelMon As Long, ByRef dpActionValue As Double, ByRef upAction As Long) As Long
' Set exception function usage of specific axis. (Only for MLII, Sigma-5)
Public Declare Function AxmStatusSetServoMonitorEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uEnable As Long) As Long
' Return exception function usage of specific axis. (Only for MLII, Sigma-5)
Public Declare Function AxmStatusGetServoMonitorEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upEnable As Long) As Long


' Return exception function execution result Flag of specific axis. Auto reset after function execution. (Only for MLII, Sigma-5)
Public Declare Function AxmStatusReadServoMonitorFlag Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelMon As Long, ByRef upMonitorFlag As Long, ByRef dpMonitorValue As Double) As Long
' Return exception function monitoring information of specific axis. (Only for MLII, Sigma-5)
Public Declare Function AxmStatusReadServoMonitorValue Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelMon As Long, ByRef dpMonitorValue As Double) As Long

' Set load ratio monitor function of specific axis. (Only for MLII, Sigma-5)
' (MLII, Sigma-5, dwSelMon : 0 ~ 2) ==
' dwSelMon = 0 : Accumulated load ratio
' dwSelMon = 1 : Regenerative load ratio
' dwSelMon = 2 : Reference Torque load ratio
' (SIIIH, MR_J4_xxB, dwSelMon : 0 ~ 4) ==
'     [0] : Assumed load inertia ratio(0.1times)
'     [1] : Regeneration load factor(%)
'     [2] : Effective load factor(%)
'     [3] : Peak load factor(%)
'     [4] : Current feedback(0.1%)
' (RTEX, A5Nx, dwSelMon : 0 ~ 4) ==
'     [0] : Command Torque(0.1%)
'     [1] : Regenertive load ratio(0.1%)
'     [2] : Overload ratio(0.1%)
'     [3] : Inertia ratio(%)
Public Declare Function AxmStatusSetReadServoLoadRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwSelMon As Long) As Long
' Return load ratio of specific axis. (Only for MLII, Sigma-5)
Public Declare Function AxmStatusReadServoLoadRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpMonitorValue As Double) As Long


'======== Only for PCI-R1604-RTEX ==================================================================================
' Set RTEX A4Nx Scale Coefficient. (Only for RTEX, A4Nx)
Public Declare Function AxmMotSetScaleCoeff Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lScaleCoeff As Long) As Long
' Return RTEX A4Nx Scale Coefficient. (Only for RTEX, A4Nx)
Public Declare Function AxmMotGetScaleCoeff Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpScaleCoeff As Long) As Long

' Edge detection of specific Input Signal that stop or slow down to stop the function.
' lDetectSignal : Select input signal to detect edge.
'                 PosEndLimit(0), NegEndLimit(1), HomeSensor(4)
' lSignalEdge   : Select edge direction of selected input signal.
'                 SIGNAL_DOWN_EDGE(0), SIGNAL_UP_EDGE(1)
' lSignalMethod : Select stop method.
'                 EMERGENCY_STOP(0), SLOWDOWN_STOP(1)
' * Move direction : CW(dVel is positive), CCW(dVel is negative)
' * Note : Acceleration / deceleration is ignored when lSignalMethod is EMERGENCY_STOP(0), and acceleration suddenly stops at the specified speed.
'          If lDetectSignal is PosEndLimit(0) or NegEndLimit(1) in use PCI-Nx04, the level of the signal active state is detected.
Public Declare Function AxmMoveSignalSearchEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal lDetectSignal As Long, ByVal lSignalEdge As Long, ByVal lSignalMethod As Long) As Long

'--------------------------------------------------------------------------------------------------------------------
'======== Only for PCI-R1604-MLII ==================================================================================
' Move to the set absolute position.
' Velocity profile use Trapezoid.
' Exits API at the point that pulse out starts.
' Always position(include -position), Velocity, Accel/Deccel Change possible.
Public Declare Function AxmMoveToAbsPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long
' Return current drive velocity of specific axis.
Public Declare Function AxmStatusReadVelEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpVel As Double) As Long


' ======== Only for PCI-R1604-SSCNETIIIH ==================================================================================
' Set electric ratio. This parameter saved Non-volatile memory.
' Default value(lNumerator : 4194304(2^22), lDenominator : 10000)
' MR-J4-B is don't Setting electric ratio, Must be set from the host controller.
' No.PA06, No.PA07 of Existing Pulse type Servo Driver(MR-J4-A)
Public Declare Function AxmMotSetElectricGearRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lNumerator As Long, ByVal lDenominator As Long) As Long
'  Return electric ratio of specific axis.
Public Declare Function AxmMotGetElectricGearRatio Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpNumerator As Long, ByRef lpDenominator As Long) As Long


' Set limit torque value of specific axis.
' Forward, Backward drive torque limit function.
' Setting range 1 ~ 1000
' 0.1% of the maximum torque are controlled.
Public Declare Function AxmMotSetTorqueLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dbPluseDirTorqueLimit As Double, ByVal dbMinusDirTorqueLimit As Double) As Long


' Return torque limit value of specific axis.
Public Declare Function AxmMotGetTorqueLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dbpPluseDirTorqueLimit As Double, ByRef dbpMinusDirTorqueLimit As Double) As Long

    Public Declare Function AxmMotSetTorqueLimitEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dbPlusDirTorqueLimit As Double, ByVal dbMinusDirTorqueLimit As Double) As Long

    Public Declare Function AxmMotGetTorqueLimitEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dbpPlusDirTorqueLimit As Double, ByRef dbpMinusDirTorqueLimit As Double) As Long


' Sets the torque limit value of the specified axis.
' Limit the torque value during forward and reverse drive.
' The setting range is from 1 to 3000 (0.1% ~ 300.0%).
' It is controlled in 0.1% of maximum torque.
' dPosition : Position information to change the torque limit value (applicable when event with same position information and target position occur).
' lTarget   : COMMAND(0), ACTUAL(1)
Public Declare Function AxmMotSetTorqueLimitAtPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dbPlusDirTorqueLimit As Double, ByVal dbMinusDirTorqueLimit As Double, ByVal dPosition As Double, ByVal lTarget As Long) As Long

' Get the torque limit value of the specified axis.
Public Declare Function AxmMotGetTorqueLimitAtPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dbpPlusDirTorqueLimit As Double, ByRef dbpMinusDirTorqueLimit As Double, ByRef dpPosition As Double, ByRef lpTarget As Long) As Long


Public Declare Function AxmMotSetTorqueLimitEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long

Public Declare Function AxmMotGetTorqueLimitEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long


Public Declare Function AxmOverridePosSetFunction Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long, ByVal lDecelPosRatio As Long, ByVal dReserved As Double) As Long

Public Declare Function AxmOverridePosGetFunction Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpUsage As Long, ByRef lpDecelPosRatio As Long, ByRef dpReserved As Double) As Long

' Controls the digital output value set at a specific position on the specified axis.
' lModuleNo   : Module Number
' lOffset     : Offset position for output contact
' uValue      : OFF(0)
'             : OM(1)
'             : Function Clear(0xFF)
' dPosition   : DO output value is changed (executed when an event occurs in which the position information is the same as the target position).
' lTarget     : COMMAND(0), ACTUAL(1)
Public Declare Function AxmSignalSetWriteOutputBitAtPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long, ByVal dPosition As Double, ByVal lTarget As Long) As Long
' Get the digital output value control setting set at a specific position on the specified axis.
Public Declare Function AxmSignalGetWriteOutputBitAtPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpModuleNo As Long, ByRef lpOffset As Long, ByRef upValue As Long, ByRef dpPosition As Double, ByRef lpTarget As Long) As Long


' -------------------------------------------------------------------------------------------------------------------

'======== PCI-R3200-MLIII ==================================================================================                                   <<<<<

Public Declare Function AxmAdvVSTSetParameter Lib "AXL.dll" (ByVal lCoord As Long, ByVal dwISTSize As Long, ByRef dbpFrequency As Double, ByRef dbpDampingRatio As Double, ByRef dwpImpulseCount As Long) As Long
Public Declare Function AxmAdvVSTGetParameter Lib "AXL.dll" (ByVal lCoord As Long, ByRef dwpISTSize As Long, ByRef dbpFrequency As Double, ByRef dbpDampingRatio As Double, ByRef dwpImpulseCount As Long) As Long

Public Declare Function AxmAdvVSTSetEnabele Lib "AXL.dll" (ByVal lCoord As Long, ByVal dwISTEnable As Long) As Long
Public Declare Function AxmAdvVSTGetEnabele Lib "AXL.dll" (ByVal lCoord As Long, ByRef dwpISTEnable As Long) As Long


Public Declare Function AxmAdvLineMove Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef dPosition As Double, ByVal dMaxVelocity As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double) As Long

Public Declare Function AxmAdvOvrLineMove Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef dPosition As Double, ByVal dMaxVelocity As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double, ByVal lOverrideMode As Long) As Long

Public Declare Function AxmAdvCircleCenterMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dCenterPos As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

Public Declare Function AxmAdvCirclePointMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dMidPos As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Long, ByVal dDecel As Double, ByVal lArcCircle As Long) As Long

Public Declare Function AxmAdvCircleAngleMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dCenterPos As Double, ByVal dAngle As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

Public Declare Function AxmAdvCircleRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByVal dRadius As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long) As Long

Public Declare Function AxmAdvOvrCircleRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByVal dRadius As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long, ByVal lOverrideMode As Long) As Long



Public Declare Function AxmAdvHelixCenterMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dCenterXPos As Double, ByVal dCenterYPos As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

Public Declare Function AxmAdvHelixPointMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dMidXPos As Double, ByVal dMidYPos As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

Public Declare Function AxmAdvHelixAngleMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dCenterXPos As Double, ByVal dCenterYPos As Double, ByVal dAngle As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

Public Declare Function AxmAdvHelixRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dRadius As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long) As Long

Public Declare Function AxmAdvOvrHelixRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dRadius As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long, ByVal lOverrideMode As Long) As Long


Public Declare Function AxmAdvScriptLineMove Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef dPosition As Double, ByVal dMaxVelocity As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptOvrLineMove Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef dPosition As Double, ByVal dMaxVelocity As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double, ByVal lOverrideMode As Long, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptCircleCenterMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dCenterPos As Double, ByVal dEndPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptCirclePointMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dMidPos As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArcCircle As Long, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptCircleAngleMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByRef dCenterPos As Double, ByVal dAngle As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptCircleRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByVal dRadius As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptOvrCircleRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByRef lAxisNo As Long, ByVal dRadius As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShotDistance As Long, ByVal lOverrideMode, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long



Public Declare Function AxmAdvScriptHelixCenterMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dCenterXPos As Double, ByVal dCenterYPos As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal dwSceipt As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptHelixPointMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dMidXPos As Double, ByVal dMidYPos As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptHelixAngleMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dCenterXPos As Double, ByVal dCenterYPos As Double, ByVal dAngle As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptHelixRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dRadius As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dScriptPos As Double) As Long

Public Declare Function AxmAdvScriptOvrHelixRadiusMove Lib "AXL.dll" (ByVal lCoord As Long, ByVal dRadius As Double, ByVal dEndXPos As Double, ByVal dEndYPos As Double, ByVal dZPos As Double, ByVal dVel As Double, ByVal dStartVel As Double, ByVal dStopVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long, ByVal lOverrideMode As Long, ByVal dwScript As Long, ByVal lScriptAxisNo As Long, ByVal dSrciptPos As Double) As Long


Public Declare Function AxmAdvContiGetNodeNum Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef lpNodeNum As Long) As Long

Public Declare Function AxmAdvContiGetTotalNodeNum Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef lpNodeNum As Long) As Long

Public Declare Function AxmAdvContiReadIndex Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef lpQueueIndex As Long) As Long

Public Declare Function AxmAdvContiReadFree Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef upQueueFree As Long) As Long

Public Declare Function AxmAdvContiWriteClear Lib "AXL.dll" (ByVal lCoordinate As Long) As Long

Public Declare Function AxmAdvOvrContiWriteClear Lib "AXL.dll" (ByVal lCoordinate) As Long

Public Declare Function AxmAdvContiStart Lib "AXL.dll" (ByVal lCoord As Long, ByVal dwProfileset As Long, ByVal lAngle As Long) As Long

Public Declare Function AxmAdvContiStop Lib "AXL.dll" (ByVal lCoordinate As Long, ByVal dDecel As Long) As Long

Public Declare Function AxmAdvContiSetAxisMap Lib "AXL.dll" (ByVal lCoord As Long, ByVal lSize As Long, ByRef lpAxisNo As Long) As Long

Public Declare Function AxmAdvContiGetAxisMap Lib "AXL.dll" (ByVal lCoord As Long, ByRef lpSize As Long, ByRef lpAxisNo As Long) As Long

Public Declare Function AxmAdvContiSetAbsRelMode Lib "AXL.dll" (ByVal lCoord As Long, ByVal uAbsRelMode As Long) As Long

Public Declare Function AxmAdvContiGetAbsRelMode Lib "AXL.dll" (ByVal lCoord As Long, ByRef uAbsRelMode As Long) As Long

Public Declare Function AxmAdvContiIsMotion Lib "AXL.dll" (ByVal lCoordinate As Long, ByRef upInMotion As Long) As Long

Public Declare Function AxmAdvContiBeginNode Lib "AXL.dll" (ByVal lCoord As Long) As Long

Public Declare Function AxmAdvContiEndNode Lib "AXL.dll" (ByVal lCoord As Long) As Long



Public Declare Function AxmMoveMultiStop Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dMaxDecel As Double) As Long

Public Declare Function AxmMoveMultiEStop Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxisNo As Long) As Long

Public Declare Function AxmMoveMultiSStop Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxisNo As Long) As Long



Public Declare Function AxmStatusReadActVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpVel As Double) As Long

Public Declare Function AxmStatusReadServoCmdStat Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long

Public Declare Function AxmStatusReadServoCmdCtrl Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long


Public Declare Function AxmGantryGetMstToSlvOverDist Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPosition As Double) As Long

Public Declare Function AxmGantrySetMstToSlvOverDist Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPosition As Double) As Long


Public Declare Function AxmSignalReadServoAlarmCode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upCodeStatus As Long) As Long



Public Declare Function AxmM3ServoCoordinatesSet Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwPosData As Long, ByVal dwPos_sel As Long, ByVal dwRefe As Long) As Long

Public Declare Function AxmM3ServoBreakOn Lib "AXL.dll" (ByVal lAxisNo) As Long

Public Declare Function AxmM3ServoBreakOff Lib "AXL.dll" (ByVal lAxisNo) As Long

Public Declare Function AxmM3ServoConfig Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwCfMode As Long) As Long

Public Declare Function AxmM3ServoSensOn Lib "AXL.dll" (ByVal lAxisNo As Long) As Long

Public Declare Function AxmM3ServoSensOff Lib "AXL.dll" (ByVal lAxisNo As Long) As Long

Public Declare Function AxmM3ServoSmon Lib "AXL.dll" (ByVal lAxisNo As Long) As Long

Public Declare Function AxmM3ServoGetSmon Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef pbParam As Byte) As Long

Public Declare Function AxmM3ServoSvOn Lib "AXL.dll" (ByVal lAxisNo As Long) As Long

Public Declare Function AxmM3ServoSvOff Lib "AXL.dll" (ByVal lAxisNo As Long) As Long

Public Declare Function AxmM3ServoInterpolate Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTPOS As Long, ByVal dwVFF As Long, ByVal dwTFF As Long, ByVal dwTLIM As Long) As Long

Public Declare Function AxmM3ServoPosing Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTOIS As Long, ByVal dwSPD As Long, ByVal dwACCR As Long, ByVal dwDECR As Long, ByVal dwTLIM As Long) As Long

Public Declare Function AxmM3ServoFeed Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lSPD As Long, ByVal dwACCR As Long, ByVal dwDECR As Long, ByVal dwTLIM As Long) As Long

Public Declare Function AxmM3ServoExFeed Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lSPD As Long, ByVal dwACCR As Long, ByVal dwDECR As Long, ByVal dwTLIM As Long, ByVal dwExSig1 As Long, ByVal dwExSig2 As Long) As Long
Public Declare Function AxmM3ServoExPosing Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTPOS As Long, ByVal dwSPD As Long, ByVal dwACCR As Long, ByVal dwDECR As Long, ByVal dwTLIM As Long, ByVal dwExSig1 As Long, ByVal dwExSig2 As Long) As Long

Public Declare Function AxmM3ServoZret Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwSPD As Long, ByVal dwACCR As Long, ByVal dwDECR As Long, ByVal dwTLIM As Long, ByVal dwExSig1 As Long, ByVal dwExSig2 As Long, ByVal bHomeDir As Byte, ByVal bHomeType As Byte) As Long

Public Declare Function AxmM3ServoVelctrl Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTFF As Long, ByVal dwVREF As Long, ByVal dwACCR As Long, ByVal dwDECR As Long, ByVal dwTLIM As Long) As Long

Public Declare Function AxmM3ServoTrqctrl Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwVLIM As Long, ByVal lTQREF As Long) As Long
' bmode 0x00 : common parameters ram
' bmode 0x01 : common parameters flash
' bmode 0x10 : device parameters ram
' bmode 0x11 : device parameters flash

Public Declare Function AxmM3ServoGetParameter Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wNo As Long, ByVal bSize As Byte, ByVal bMode As Byte, ByRef pbParam As Byte) As Long

Public Declare Function AxmM3ServoSetParameter Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wNo As Long, ByVal bSize As Byte, ByVal bMode As Byte, ByRef pbParam As Byte) As Long
Public Declare Function AxmServoCmdExecution Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwCommand As Long, ByVal dwSize As Long, ByRef pdwExcData As Long) As Long
Public Declare Function AxmM3ServoGetTorqLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpTorqLimit As Long) As Long

Public Declare Function AxmM3ServoSetTorqLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTorqLimit As Long) As Long


Public Declare Function AxmM3ServoGetSendSvCmdIOOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwData As Long) As Long

Public Declare Function AxmM3ServoSetSendSvCmdIOOutput Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwData As Long) As Long



Public Declare Function AxmM3ServoGetSvCmdCtrl Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwData As Long) As Long

Public Declare Function AxmM3ServoSetSvCmdCtrl Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwData As Long) As Long



' dwReqCode == 0x1005 : parameter initialization : 20sec
' dwReqCode == 0x1008 : absolute encoder reset   : 5sec
' dwReqCode == 0x100E : automatic offset adjustment of motor current detection signals  : 5sec
' dwReqCode == 0x1013 : Multiturn limit setting  : 5sec
Public Declare Function AxmM3AdjustmentOperation Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwReqCode As Long) As Long

Public Declare Function AxmM3ServoSetMonSel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwMon0 As Long, ByVal dwMon1 As Long, ByVal dwMon2 As Long) As Long

Public Declare Function AxmM3ServoGetMonSel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upMon0 As Long, ByRef upMon1 As Long, ByRef upMon2 As Long) As Long

Public Declare Function AxmM3ServoReadMonData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwMonSel As Long, ByRef dwpMonData As Long) As Long

Public Declare Function AxmAdvTorqueContiSetAxisMap Lib "AXL.dll" (ByVal lCoord As Long, ByVal lSize As Long, ByRef lpAxisNo As Long, ByVal dwTLIM As Long, ByVal dwConMode As Long) As Long

Public Declare Function AxmM3ServoSetTorqProfile Lib "AXL.dll" (ByVal lCoord As Long, ByVal lAxisNo As Long, ByVal TorqueSign As Long, ByVal dwVLIM As Long, ByVal dwProfileMode As Long, ByVal dwStdTorq As Long, ByVal swStopTorq As Long) As Long

Public Declare Function AxmM3ServoGetTorqProfile Lib "AXL.dll" (ByVal lCoord As Long, ByVal lAxisNo As Long, ByRef lpTorqueSign As Long, ByRef updwVLIM As Long, ByRef upProfileMode As Long, ByRef upStdTorq As Long, ByVal upStopTorq As Long) As Long

'-------------------------------------------------------------------------------------------------------------------

'======== For EtherCAT Only =======================================================================================
' Set for Inposition signal range. (dInposRange > 0)
Public Declare Function AxmSignalSetInposRange Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dInposRange As Double) As Long
' Get the Inposition signal range.
Public Declare Function AxmSignalGetInposRange Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpInposRange As Double) As Long


' Set for absolute encoder position to dPosition.
Public Declare Function AxmStatusSetEncClear Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPosition As Double) As Long


' The command position and actual position of the SERVOPACK corresponding to the designated axis are matched with the dPos value.
' Reserved
Public Declare Function AxmStatusSetMotorPosMatch Lib "AXL.dll" (ByVal lAxisNo As Long) As Long



' Set for Work coordinate system. The default value matches World coordinate.
' lCoordNo : Coordinate No(0 ~ 7)
' dpOrigin : Work coordinate system origin position based on World Coordinate
' dpXPos   : Work coordinate system based on World Coordinate Any position on X axis
' dpYPos   : Work coordinate system based on World Coordinate Any position on Y axis
Public Declare Function AxmMotSetWorkCoordinate Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dpOrigin As Double, ByRef dpXPos As Double, ByRef dpYPos As Double) As Long
' Get the set Work coordinate system.
Public Declare Function AxmMotGetWorkCoordinate Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dpOrigin As Double, ByRef dpXPos As Double, ByRef dpYPos As Double) As Long

' Set the location property (absolute / relative) when overriding.
Public Declare Function AxmMotSetOverridePosMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwAbsRelMode As Long) As Long
' Get the location property (absolute / relative) when overriding.
Public Declare Function AxmMotGetOverridePosMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpAbsRelMode As Long) As Long
' Set the location property (absolute / relative) when LineMove overriding.
Public Declare Function AxmMotSetOverrideLinePosMode Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dwAbsRelMode As Long) As Long
' Get the location property (absolute / relative) when LineMove overriding.
Public Declare Function AxmMotGetOverrideLinePosMode Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dwpAbsRelMode As Long) As Long


' Set the Vibration Control setting value(Set the Vibration Control setting value (frequency, damping ratio, impulse count) of the specified axis.
Public Declare Function AxmMotSetVibrationControl Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lSize As Long, ByRef pdFrequency As Double, ByRef pdDampingRatio As Double, ByRef lpImpulseCount As Long) As Long

' Enable or disable the Vibration Control of the specific axis.
Public Declare Function AxmMotVibrationControlEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwEnable As Long) As Long

' Reads whether Vibration Control of the specified axis is enabled.
Public Declare Function AxmMotVibrationControlIsEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef pdwEnable As Long) As Long

' Enable or Disable the Vibration Control of the specified coordinate system.
Public Declare Function AxmMotVibrationControlCoordEnable Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dwEnable As Long) As Long

' Reads whether Vibration Control is enabled in the specified coordinate system.
Public Declare Function AxmMotVibrationControlCoordIsEnable Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef pdwEnable As Long) As Long


' Sets the TorqueLimit for each Position range of the specified axis.
' The number of dpPosition array is lSize.
' The number of dpPlusTorqueLimit and dpMinusTorqueLimit is (lSize - 1)
' * Note : Position must be entered in ascending order.
'          EtherCAT only applies the same TorqueLimit to both PlusTorqueLimit values.
Public Declare Function AxmMotSetMultiTorqueLimit Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lSize As Long, ByRef dpPosition As Double, ByRef dpPlusTorqueLimit As Double, ByRef dpMinusTorqueLimit As Double, ByVal lTarget As Long) As Long

' Enable or Disable the Multi TorqueLimit of the specified axis.
Public Declare Function AxmMotMultiTorqueLimitEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwEnable As Long) As Long

' Reads whether Multi TorqueLimit of the specified axis is enabled.
Public Declare Function AxmMotMultiTorqueLimitIsEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpEnable As Long) As Long


' Equivalent to AxmMoveStartPos and added end rate (EndVel).
Public Declare Function AxmMoveStartPosEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dEndVel As Double) As Long
' Equivalent to AxmMovePos and added end rate (EndVel).
Public Declare Function AxmMovePosEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dEndVel As Double) As Long


'Public Declare Function AxmMoveStartMultiPosEx Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dpPos As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByRef dpEndVel As Double) As Long

'Public Declare Function AxmMoveMultiPosEx Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dpPos As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double, ByRef dpEndVel As Double) As Long

' Normal-Stop the Coordinate Motion on path.
Public Declare Function AxmMoveCoordStop Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dDecel As Double) As Long
' Emergency-Stop the Coordinate Motion on path.
Public Declare Function AxmMoveCoordEStop Lib "AXL.dll" (ByVal lCoordNo As Long) As Long
' Slowdown-Stop the Coordinate Motion on path.
Public Declare Function AxmMoveCoordSStop Lib "AXL.dll" (ByVal lCoordNo As Long) As Long




'Public Declare Function AxmMoveStartPosWithPosEventEx Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lEventAxisNo As Long, ByVal dComparePos As Double, ByVal uPosSource As Long, ByVal dEndVel As Double) As Long

' Override the position of the AxmLineMove motion.
Public Declare Function AxmOverrideLinePos Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dpOverridePos As Double) As Long
' Override the velocity of the AxmLineMove motion. The speed ratio of each axis is determined by dpDistance.
Public Declare Function AxmOverrideLineVel Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dOverrideVel As Double, ByRef dpDistance As Double) As Long

' Override the velocity, acceleration, deceleration of the AxmLineMove motion.
' dMaxAccel  : Acceleration value for overriding
' dMaxDecel  : Deceleration value for overriding
' dpDistance : Speed ratio of each axis
Public Declare Function AxmOverrideLineAccelVelDecel Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dOverrideVelocity As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double, ByRef dpDistance As Double) As Long
' In addition to AxmOverrideVelAtPos, override AccelDecel.
Public Declare Function AxmOverrideAccelVelDecelAtPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dOverridePos As Double, ByVal dOverrideVel As Double, ByVal dOverrideAccel As Double, ByVal dOverrideDecel As Double, ByVal lTarget As Long) As Long


' A plurality of slave axes are connected to one master axis. (Electronic Gearing)
' lMasterAxisNo : Master axis number
' lSize         : Slave axis count(Max : 8)
' lpSlaveAxisNo : Array of Slave axis number
' dpGearRatio   : Slave axis ratio based on master axis (Except 0. 1.0 is 100%)
Public Declare Function AxmEGearSet Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal lSize As Long, ByRef lpSlaveAxisNo As Long, ByRef dpGearRatio As Double) As Long
' Reads Electronic Gearing information.
Public Declare Function AxmEGearGet Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef lpSize As Long, ByRef lpSlaveAxisNo As Long, ByRef dpGearRatio As Double) As Long
' Reset Electronic Gearing.
Public Declare Function AxmEGearReset Lib "AXL.dll" (ByVal lMasterAxisNo As Long) As Long
' Enable or disable Electronic Gearing.
Public Declare Function AxmEGearEnable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByVal dwEnable As Long) As Long
' Reads whether Electronic Gearing is enabled.
Public Declare Function AxmEGearIsEnable Lib "AXL.dll" (ByVal lMasterAxisNo As Long, ByRef dwpEnable As Long) As Long




'Public Declare Function AxmLineMoveEx Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dEndVel As Double) As Long

'Public Declare Function AxmCirclePointMoveEx Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef lAxisNo As Long, ByRef dpMidPos As Double, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArcCircle As Long, ByVal lArraySize As Long) As Long

' Helical interpolation drive that rotates around any axis is supported.
' dpFirstCenterPos  : Center position
' dpSecondCenterPos : Center position on opposite side
' dPitch            : Movement amount(mm) / 1 Revolution
' dTraverseDistance : Movement amount(mm)
' The line connecting dpFirstCenterPos to dpSecondCenterPos is the axis of rotation.
' The straight line from the center(dpFirstCenterPos-->dpSecondCenterPos) and the straight line to the start position(dpFirstCenterPos-->Starting position) is perpendicular to each other.
' dTraverseDistance is the distance of a straight line parallel to the axis of rotation at the starting position.
' Axis mapping is possible for more than 3 axes, and axes more than 3 axes are linear interpolation.
Public Declare Function AxmHelixPitchMove Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dpFirstCenterPos As Double, ByRef dpSecondCenterPos As Double, ByVal dPitch As Double, ByVal dTraverseDistance As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

'Public Declare Function AxmHelixPitchMoveEx Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dpFirstCenterPos As Double, ByRef dpSecondCenterPos As Double, ByVal dPitch As Double, ByVal dTraverseDistance As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal dEndCel As Double) As Long

' 1-D correction function
' When driving beyond the compensation table range, the first and last compensation values of the compensation table should always be set to "0".
' That is, pdMotorPosition and pdLoadPosition must be the same.
' You can set the axis to measure the correction value (lSourceAxis) and the axis to apply the correction value (lTargetAxis) to the same axis or another axis.
' The position value of the correction table is set to an absolute position.
Public Declare Function AxmCompensationOneDimSet Lib "AXL.dll" (ByVal lTableNo As Long, ByVal lSourceAxis As Long, ByVal lTargetAxis As Long, ByVal lSize As Long, ByRef dpMotorPosition As Double, ByRef dpLoadPosition As Double) As Long
Public Declare Function AxmCompensationOneDimGet Lib "AXL.dll" (ByVal lTableNo As Long, ByRef lpTargetAxis As Long, ByRef lpSize As Long, ByRef dpMotorPosition As Double, ByRef dpLoadPosition As Double) As Long
Public Declare Function AxmCompensationOneDimReset Lib "AXL.dll" (ByVal lTableNo As Long) As Long
    Public Declare Function AxmCompensationOneDimIsSet Lib "AXL.dll" (ByVal lTableNo As Long, ByRef dwpSet As Long) As Long
Public Declare Function AxmCompensationOneDimEnable Lib "AXL.dll" (ByVal lTableNo As Long, ByVal dwEnable As Long) As Long
Public Declare Function AxmCompensationOneDimIsEnable Lib "AXL.dll" (ByVal lTableNo As Long, ByRef dwpEnable As Long) As Long


' Returns the compensation value at the current command position.
Public Declare Function AxmCompensationOneDimGetCorrection Lib "AXL.dll" (ByVal lTableNo As Long, ByRef pdCorrection As Double) As Long

    Public Declare Function AxmCompensationOneDimSetReverse Lib "AXL.dll" (ByVal lTableNo As Long, ByRef dpLoadPosition As Double) As Long
    Public Declare Function AxmCompensationOneDimGetReverse Lib "AXL.dll" (ByVal lTableNo As Long, ByRef dpLoadPosition As Double) As Long
    Public Declare Function AxmCompensationOneDimGetCorrectionReverse Lib "AXL.dll" (ByVal lTableNo As Long, ByRef pdCorrection As Double) As Long

    Public Declare Function AxmCompensationOneDimFileLoad Lib "AXL.dll" (ByVal lTableNo As Long, ByVal lSourceAxis As Long, ByVal lTargetAxis As Long, ByRef szFilePath As char*, ByVal 0 As DWORD dwInterpolationMethod =) As Long
    Public Declare Function AxmCompensationOneDimFileSave Lib "AXL.dll" (ByVal lTableNo As Long, ByRef szFilePath As char*) As Long

    Public Declare Function AxmCompensationOneDimSetInterpolationMethod Lib "AXL.dll" (ByVal lTableNo As Long, ByVal dwMethod As Long) As Long
    Public Declare Function AxmCompensationOneDimGetInterpolationMethod Lib "AXL.dll" (ByVal lTableNo As Long, ByRef dwpMethod As Long) As Long

    Public Declare Function AxmCompensationTwoDimSet Lib "AXL.dll" (ByVal lTableNo As Long, ByVal lSourceAxis1 As Long, ByVal lSourceAxis2 As Long, ByVal lTargetAxis1 As Long, ByVal lTargetAxis2 As Long, ByVal lSize1 As Long, ByVal lSize2 As Long, ByRef dpMotorPosition1 As Double, ByRef dpMotorPosition2 As Double, ByRef dpLoadPosition1 As Double, ByRef dpLoadPosition2 As Double) As Long
    Public Declare Function AxmCompensationTwoDimGet Lib "AXL.dll" (ByVal lTableNo As Long, ByRef lpSourceAxis1 As Long, ByRef lpSourceAxis2 As Long, ByRef lpTargetAxis1 As Long, ByRef lpTargetAxis2 As Long, ByRef lpSize1 As Long, ByRef lpSize2 As Long, ByRef dpMotorPosition1 As Double, ByRef dpMotorPosition2 As Double, ByRef dpLoadPosition1 As Double, ByRef dpLoadPosition2 As Double) As Long
    Public Declare Function AxmCompensationTwoDimReset Lib "AXL.dll" (ByVal lTableNo As Long) As Long
    Public Declare Function AxmCompensationTwoDimIsSet Lib "AXL.dll" (ByVal lTableNo As Long, ByRef dwpSet As Long) As Long
    Public Declare Function AxmCompensationTwoDimEnable Lib "AXL.dll" (ByVal lTableNo As Long, ByVal dwEnable As Long) As Long
    Public Declare Function AxmCompensationTwoDimIsEnable Lib "AXL.dll" (ByVal lTableNo As Long, ByRef dwpEnable As Long) As Long

    Public Declare Function AxmCompensationTwoDimGetCorrection Lib "AXL.dll" (ByVal lTableNo As Long, ByRef pdCorrection As Double) As Long

    Public Declare Function AxmCompensationTwoDimFileLoad Lib "AXL.dll" (ByVal lTableNo As Long, ByVal lSourceAxis1 As Long, ByVal lSourceAxis2 As Long, ByVal lTargetAxis1 As Long, ByVal lTargetAxis2 As Long, ByRef szFilePath As char*) As Long
    Public Declare Function AxmCompensationTwoDimFileSave Lib "AXL.dll" (ByVal lTableNo As Long, ByRef szFilePath As char*) As Long




'Public Declare Function AxmCompensationTwoDimSet Lib "AXL.dll" (ByVal lTableNo As Long, ByVal lSourceAxis1 As Long, ByVal lSourceAxis2 As Long, ByVal lTatgetAxis1 As Long, ByVal lTargetAxis2 As Long, ByVal lSize1 As Long, ByVal lSize2 As Long, ByRef dpMotorPosition1 As Double, ByRef dpMotorPosition2 As Double, ByRef dpLoadPosition1 As Double, ByRef dpLoadPosition2 As Double) As Long
'Public Declare Function AxmCompensationTwoDimGet Lib "AXL.dll" (ByVal lTableNo As Long, ByRef lpSourceAxis1 As Long, ByRef lpSourceAxis2 As Long, ByRef lpTargetAxis1 As Long, ByRef lpTargetAxis2 As Long, ByRef lpSize1 As Long, ByRef lpSize2 As Long, ByRef dpMotorPosition1 As Double, ByRef dpMotorPosition2 As Double, ByRef dpLoadPosition1 As Double, ByRef dpLoadPosition2 As Double) As Long
'Public Declare Function AxmCompensationTwoDimReset Lib "AXL.dll" (ByVal lTableNo As Long) As Long
'Public Declare Function AxmCompensationTwoDimEnable Lib "AXL.dll" (ByVal lTableNo As Long, ByVal dwEnable As Long) As Long
'Public Declare Function AxmCompensationTwoDimIsEnable Lib "AXL.dll" (ByVal lTableNo As Long, ByRef dwpEnable As Long) As Long

' Reserved
'Public Declare Function AxmBlendingSet Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dValue As Double, ByVal dwMethod As Long) As Long
'Public Declare Function AxmBlendingGet Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpValue As Double, ByRef dwpMethod As Long) As Long
'Public Declare Function AxmBlendingReset Lib "AXL.dll" (ByVal lAxisNo As Long) As Long
'Public Declare Function AxmBlendingEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwEnable As Long) As Long
'Public Declare Function AxmBlendingIsEnable Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpEnable As Long) As Long

' Blending motion is supported.
' dValue   : At the start of blending based on the ending point of the first motion segment
' dwMethod : Distance(mm)-0, Time(msec)-1, Distance ratio(%)-2
' Blending mode is canceled in automatic acceleration / deceleration and automatic arc insertion mode.
Public Declare Function AxmBlendingCoordSet Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dValue As Double, ByVal dwMethod As Long) As Long
Public Declare Function AxmBlendingCoordGet Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dpValue As Double, ByRef dwpMethod As Long) As Long
Public Declare Function AxmBlendingCoordReset Lib "AXL.dll" (ByVal lCoordNo As Long) As Long
Public Declare Function AxmBlendingCoordEnable Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal dwEnable As Long) As Long
Public Declare Function AxmBlendingCoordIsEnable Lib "AXL.dll" (ByVal lCoordNo As Long, ByRef dwpEnable As Long) As Long






'Public Declare Function AxmMoveMultiSignalCapture Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lDetectSignal As Long, ByVal lSignalEdge As Long, ByVal lTarget As Long) As Long

'Public Declare Function AxmMoveGetMultiCapturePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpCapPosition As Double, ByRef lpSize As Long) As Long


'DWORD    __stdcall AxmStatusReadServoAlarm(long lAxisNo, DWORD uReturnMode, DWORD *upAlarmCode);


'DWORD    __stdcall AxmStatusGetServoAlarmString(long lAxisNo, DWORD uAlarmCode, long lAlarmStringSize, char *szAlarmString);

' Read the torque value of the corresponding axis.
Public Declare Function AxmStatusReadTorque Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef pdTorque As Double) As Long


' ProfilePosition Mode          = 1,
' Velocity Mode                 = 2,
' ProfileVelocity Mode          = 3,
' ProfileTorque Mode            = 4,
' Homing Mode                   = 6,
' InterpolatedPosition Mode     = 7,
' CyclicSyncPosition Mode       = 8,
' CyclicSyncVelocity Mode       = 9,
' CyclicSyncTorque Mode         = 10,
'Public Declare Function AxmMotSetOperationMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwOperationMode As Long) As Long
'Public Declare Function AxmMotGetOperationMode Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef pdwOperationMode As Long) As Long

'  Set the end speed on the specified axis.
'  * Note : It is reset to '0' if the entered end rate is below '0' and to 'MaxVel' if it exceeds the maximum speed set by 'AxmMotSetMaxVel'.
Public Declare Function AxmMotSetEndVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dEndVelocity As Double) As Long
' Returns the ending speed of the specified axis.
Public Declare Function AxmMotGetEndVel Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpEndVelocity As Double) As Long

' Linear interpolation.
' Axis linear interpolation drive by specifying a start point and an end point. The function is exited after the start of driving.
' When using with AxmContiBeginNode and AxmContiEndNode, the start point and the end point are specified in the specified coordinate system and stored in the queue for linear interpolation driving.
' For linear profile continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
' The axes corresponding to the axis array of lpAxisNo are subjected to linear interpolation and the axes of the remaining coordinate axes perform the single axis driving according to the linear interpolation ratio.
Public Declare Function AxmLineMoveWithAxes Lib "AXL.dll" (ByVal lCoord As Long, ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' 2-D / 3-D circular interpolation and linear interpolation are performed for the further axes.
' The start point, end point, and center point are specified and circular interpolation drive is performed. The function is exited after the start of driving.
' When used with AxmContiBeginNode and AxmContiEndNode, it is stored in the circular interpolation queue that is driven by specifying the start point, end point, and center point in the specified coordinate system.
' For profile circular continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
' lAxis           : Axis array
' dCenterPosition : Center position array(X,Y or X,Y,Z)
' dEndPosition    : End position array(X,Y or X,Y,Z)
' For 2-D / 3-D or more axes, the value of dEndPosition is used as Targetposition when performing linear interpolation.
' uCWDir          : DIR_CCW(0), DIR_CW(1)
' dw3DCircle      : 2-D circular interpolation and linear interpolation for more axes(0), 3-D circular interpolation and linear interpolation for more axes(1)
Public Declare Function AxmCircleCenterMoveWithAxes Lib "AXL.dll" (ByVal lCoord As Long, ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dCenterPosition As Double, ByRef dEndPosition As Double, ByVal dMaxVelocity As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double, ByVal uCWDir As Long, ByVal b3DCircle As Long) As Long

    Public Declare Function AxmCircleRadiusMoveWithAxes Lib "AXL.dll" (ByVal lCoord As Long, ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByVal dRadius As Double, ByRef dEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long, ByVal uShortDistance As Long) As Long


    Public Declare Function AxmCircleAngleMoveWithAxes Lib "AXL.dll" (ByVal lCoord As Long, ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dCenterPos As Double, ByVal dAngle As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal uCWDir As Long) As Long

    Public Declare Function AxmCirclePointMoveWithAxes Lib "AXL.dll" (ByVal lCoordNo As Long, ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dpMidPos As Double, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lArcCircle As Long) As Long


' Linear interpolation.
' Axis linear interpolation drive by specifying a start point and an end point. The function is exited after the start of driving.
' When using with AxmContiBeginNode and AxmContiEndNode, the start point and the end point are specified in the specified coordinate system and stored in the queue for linear interpolation driving.
' For linear profile continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
' The axes corresponding to the axis array of lpAxisNo are subjected to linear interpolation and the axes of the remaining coordinate axes perform the single axis driving according to the linear interpolation ratio.
Public Declare Function AxmLineMoveWithAxesWithEvent Lib "AXL.dll" (ByVal lCoord As Long, ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dpEndPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal nEventFlag As Integer) As Long


' 2-D / 3-D circular interpolation and linear interpolation are performed for the further axes.
' The start point, end point, and center point are specified and circular interpolation drive is performed. The function is exited after the start of driving.
' When used with AxmContiBeginNode and AxmContiEndNode, it is stored in the circular interpolation queue that is driven by specifying the start point, end point, and center point in the specified coordinate system.
' For profile circular continuous interpolation drive, store it in internal queue and start using AxmContiStart function.
' lAxis           : Axis array
' dCenterPosition : Center position array(X,Y or X,Y,Z)
' dEndPosition    : End position array(X,Y or X,Y,Z)
' For 2-D / 3-D or more axes, the value of dEndPosition is used as Targetposition when performing linear interpolation.
' uCWDir          : DIR_CCW(0), DIR_CW(1)
' dw3DCircle      : 2-D circular interpolation and linear interpolation for more axes(0), 3-D circular interpolation and linear interpolation for more axes(1)
Public Declare Function AxmCircleCenterMoveWithAxesWithEvent Lib "AXL.dll" (ByVal lCoord As Long, ByVal lArraySize As Long, ByRef lpAxisNo As Long, ByRef dCenterPosition As Double, ByRef dEndPosition As Double, ByVal dMaxVelocity As Double, ByVal dMaxAccel As Double, ByVal dMaxDecel As Double, ByVal uCWDir As Integer, ByVal u3DCircle As Integer, ByVal uEventFlag As Integer) As Long


    Public Declare Function AxmMovePVT Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwArraySize As Long, ByRef pdPos As Double, ByRef pdVel As Double, ByRef pdwUsec As Long) As Long


    Public Declare Function AxmSyncSetAxisMap Lib "AXL.dll" (ByVal lSyncNo As Long, ByVal lSize As Long, ByRef lpAxesNo As Long) As Long

    Public Declare Function AxmSyncClear Lib "AXL.dll" (ByVal lSyncNo As Long) As Long

    Public Declare Function AxmSyncBegin Lib "AXL.dll" (ByVal lSyncNo As Long) As Long

    Public Declare Function AxmSyncEnd Lib "AXL.dll" (ByVal lSyncNo As Long) As Long

    Public Declare Function AxmSyncStart Lib "AXL.dll" (ByVal lSyncNo As Long) As Long


