#pragma once
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include <windows.h>
#include <stdio.h>

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

//-------------------------------//
#define SHALLOCSIZE   (0x40000 * 2)       //4KB * 2

enum TRunType { RUN_SEQ = 1, RUN_MMI = 2 };
//-------------------------------//

using _manual = struct
{
	int TenKeyNumber;
};

using _tenkeyjog = struct
{
    int uAxisNo;
    bool bTenKeyJog;
};

using _lampbuzzer = struct
{
	unsigned int uLampBuzzer[1000][10];
};

using _lifetime = struct
{			// item #0-7:machine fix,#8-15:conv'kit strip,#16-31:conv'kit picker pad
	DWORD Data[32][3];  // [item][0]=set, [][1]=current, [][2]=use/skip
};

using _errorcode = struct
{
	WORD uErrorCode[100];
	unsigned int uMTBA_MTBF;
} ;

using _iobit = struct
{
	unsigned short int uStart;
	unsigned short int uCount;
	unsigned short int uData[100];
};
//-------------------------------//
using _datamemory = struct
{
	unsigned short int uStart;
	unsigned short int uCount;
	unsigned long	   uData[300];
};
//-------------------------------//
using _mtmove = struct
{
	unsigned int uAxisNo;
	int iDir;
	unsigned int uIdx;
	bool bOnOff;
	int			 iPos;
	unsigned int uVel;
};
//-------------------------------//
using _mtstatus = struct{
	int		MotorNum;
	bool	Org;
	bool	CW;
	bool	CCW;
	bool	HOME;
	bool	Busy;
	int		CurrentIndex;
	int		NextIndex;
	double	CurrentPosition;
	double	NextPosition;
	bool	ALM;
	bool	SVON;
	
	unsigned short int uHomeStep;
	int dwServoAlarmCode;
	char strServoAlarmName[128];
	double dServoLoadRatio;
};

//-------------------------------//
using _mtcfg = struct
{
	unsigned int uAxisNo;
	unsigned int uRate;
	unsigned int uAccel;
	unsigned int uMaxVel;
	unsigned int uJogVel;
	unsigned int uHomeVel;
	unsigned int uMotorType;
	unsigned int uCardType;
	unsigned int uCardIndex;
	unsigned int uUseSkip;
	unsigned int uHomeLevel;
	unsigned int uLimitLevel;
	unsigned int uServoOnLevel;
	unsigned int uAlarmLevel;
	unsigned int uInpUse;
	unsigned int uHomeMethod;
	unsigned int uMtrDir;
	unsigned int uEncDir;
	unsigned int uMaxRec;
	unsigned int uEncoderType;
};
//-------------------------------//
using _mtdata = struct
{
	int	   uAxisNo;
	double fPos[100];
	double fVel[100];
	double uPos[100];
	double uVel[100];
	int	   HomeSpeed;
	int	   ZPhaseSpeed;
};

using _device = struct {
	double Unit_X_Size;
	double Unit_Y_Size;
	double Unit_X_Count;
	double Unit_Y_Count;
	double Unit_X_Pitch;
	double Unit_Y_Pitch;
	double Tray_X_Count;
	double Tray_Y_Count;
	double Vision_Snap_X_Count;
	double Vision_Snap_Y_Count;
	double Picker_Angle;
	double Picker_Place_Vac_Off_Offset;

	bool   Front_Picker_1_Skip;
	bool   Front_Picker_2_Skip;
	bool   Front_Picker_3_Skip;
	bool   Front_Picker_4_Skip;
	bool   Front_Picker_5_Skip;
	bool   Front_Picker_6_Skip;
	bool   Front_Picker_7_Skip;
	bool   Front_Picker_8_Skip;
	bool   Rear_Picker_1_Skip;
	bool   Rear_Picker_2_Skip;
	bool   Rear_Picker_3_Skip;
	bool   Rear_Picker_4_Skip;
	bool   Rear_Picker_5_Skip;
	bool   Rear_Picker_6_Skip;
	bool   Rear_Picker_7_Skip;
	bool   Rear_Picker_8_Skip;
	bool   Scrap_Skip;
	bool   Sponge_Clean_Skip;

	int Saw_Picker_Sponge_Clean;
	int Water_Jet_Water_Clean;
	int Water_Jet_Air_Clean;
	int Saw_Picker_Flip_Y1_Air_Clean;
	int Saw_Picker_Flip_Y2_Air_Clean;
	int Flip_Y1_Air_Clean;
	int Flip_Y2_Air_Clean;
	int Pallet_Y1_Air_Clean;
	int Pallet_Y2_Air_Clean;

	double Front_Picker_Air_Blow_Time;
	double Rear_Picker_Air_Blow_Time;
	double Front_Picker_Vac_On_Time;
	double Rear_Picker_Vac_On_Time;

	double Load_Picker_Air_Blow_Time;
	double Load_Picker_Vac_On_Time;
	double Saw_Picker_Air_Blow_Time;
	double Saw_Picker_Vac_On_Time;

	double Pallet1_Receive_Vac_Value;
	double Pallet2_Receive_Vac_Value;
	double Pallet_First_Sort_Vac_Value;
	double Pallet_Middle_Sort_Vac_Value;
	double Pallet_Last_Sort_Vac_Value;
	double Pallet_First_Sort_PKG_Rate;
	double Pallet_Last_Sort_PKG_Rate;

};

using _systemdata = struct{
	double dData[100];
};

using _machinestatus = struct{
	int nDeviceNo;
	char strDeviceName[64];

	int UPH;
	int TPH;

	int PanelInCnt;
	int UnitInCnt;
	int UnitOutCnt;
	int UnitGoodCnt;
	int UnitReworkCnt;
	int UnitNGCnt;
	int FlipY1AirCleanCnt;
	int FlipY2AirCleanCnt;
	int PalletY1AirCleanCnt;
	int PalletY2AirCleanCnt;
	int SawPkFlipY1AirClenaCnt;
	int SawPkFlipY2AirClenaCnt;
	int SpongeCleanCnt;
	int WaterJetWaterCleanCnt;
	int WaterJetAirCleanCnt;
	int HomeState[60];
	double AirPressure1;
	double AirPressure2;
	double AirPressure3;

	int GoodTray1FullCnt;
	int GoodTray2FullCnt;
	int ReworkTrayFullCnt;
	int NGTrayFullCnt;

	bool bInputState[20][16];
	bool bOutputState[20][16];

	bool bVisionConnected;
};

using _userinfo = struct
{
	char strUserName[64];
};

using _lotinfo = struct
{
	char strLotID[128];
	int nLotCount;
};

using _deviceinfo = struct
{
	int nDeviceNumber;
	char strDeviceName[64];
};

using _set3point = struct
{
	int pktype;
	int target;
	int pointno;

	double offsetX;
	double offsetY;
	double offsetT;
};

using _flip1visionresult = struct
{
	int Result[50][50];
};
using _flip2visionresult = struct
{
	int Result[50][50];
};

using _pallet1visionresult = struct
{
	int Result[50][50];
};

using _pallet2visionresult = struct
{
	int Result[50][50];
};

using _frontpkvisionresult = struct
{
	int Result[10];
};
using _rearpkvisionresult = struct
{
	int Result[10];
};

using _goodtray1visionresult = struct 
{
	int Result[50][50];
};
using _goodtray2visionresult = struct
{
	int Result[50][50];
};
using _reworktrayvisionresult = struct
{
	int Result[50][50];
};
using _ngtrayresult = struct
{
	int Result[50][50];
};

using _flip1map = struct
{
	int Map[50][50];
};
using _flip2map = struct
{
	int Map[50][50];
};
using _pallet1map = struct
{
	int Map[50][50];
};
using _pallet2map = struct
{
	int Map[50][50];
};
using _frontpkmap = struct
{
	int Map[10];
};
using _rearpkmap = struct
{
	int Map[10];
};

using _goodtray1map = struct 
{
	int Map[50][50];
};
using _goodtray2map = struct
{
	int Map[50][50];
};
using _reworktraymap = struct
{
	int Map[50][50];
};
using _ngtraymap = struct
{
	int Map[50][50];
};

using _pkcentermove = struct
{
	int PkType;
	int PkNo;
	double posx[10];
	double posy[10];
};
using _frontpkcenteroffset = struct
{
	double XOffset[10];
	double YOffset[10];
};
using _rearpkcenteroffset = struct
{
	double XOffset[10];
	double YOffset[10];
};

//-------------------------------//
//-------------------------------//
// Why a recipe was refused. Mirrors on the MMI side by number, so append only.
enum SCANTRIGGER_VALIDATE
{
	SCANTRIGGER_VALIDATE_OK            = 0,
	SCANTRIGGER_VALIDATE_AXIS          = 1,   // axis number out of range, or not built
	SCANTRIGGER_VALIDATE_RANGE         = 2,   // end is not beyond start
	SCANTRIGGER_VALIDATE_PITCH         = 3,   // pitch is not positive
	SCANTRIGGER_VALIDATE_SPEED_ZERO    = 4,   // entered speed is not positive
	SCANTRIGGER_VALIDATE_PITCH_FRACTION= 5,   // pitch is not a whole number of counts
	SCANTRIGGER_VALIDATE_SPEED_MAX     = 6,   // entered speed exceeds the axis maximum
	SCANTRIGGER_VALIDATE_LINECOUNT     = 7,   // no lines, or more than the cap
	SCANTRIGGER_VALIDATE_NO_COUNTER    = 8,   // no counter channel to trigger from
	SCANTRIGGER_VALIDATE_PULSERATE     = 9,   // axis pulse rate unset, mm cannot convert
	SCANTRIGGER_VALIDATE_NOT_HOMED     = 10,  // axis has not found its origin
	SCANTRIGGER_VALIDATE_PULSEWIDTH    = 11,  // pulse width under 1 us, or too wide
                                              // for the line period the speed gives
	SCANTRIGGER_VALIDATE_INDEXPOS      = 12,  // motor index 50..53 are not in order,
                                              // or the trigger block has no length
	SCANTRIGGER_VALIDATE_LINERATE      = 13,  // timer mode: the line rate the pitch and
                                              // speed give is outside 1 Hz .. 500 kHz
	SCANTRIGGER_VALIDATE_MOVING        = 14,  // the axis is still moving, so the cycle
                                              // cannot take it over
};
//-------------------------------//
// How the pulses are generated. The choice is a trade, not a preference:
//
//   PERIODIC  the counter compares the encoder and emits one pulse every N
//             counts. The pitch is exact and holds however the velocity
//             wanders, but N is a whole number of counts, so with a 1 um
//             encoder the pitch can only be a whole number of micrometres.
//             18.1 um is not reachable and is refused rather than rounded.
//
//   TIMER     the counter free runs at a set frequency and the encoder is not
//             involved at all. Any pitch can be asked for - the quantisation
//             is gone - but the pitch is only v / f while the stage actually
//             holds v, so velocity error goes straight into the image, and
//             the block edges are found by software rather than by hardware.
enum SCANTRIGGER_MODE
{
	SCANTRIGGER_MODE_PERIODIC = 0,   // AxcTriggerSetFunction(ch, 0x03)
	SCANTRIGGER_MODE_TIMER    = 1,   // AxcTriggerSetFunction(ch, 0x01)
};
//-------------------------------//
// Cycle progress, reported in _scantriggerdisplay.nState.
enum SCANTRIGGER_STATE
{
	SCANTRIGGER_IDLE        = 0,
	SCANTRIGGER_GOTO_START  = 1,   // moving to the trigger start position
	SCANTRIGGER_WAIT_START  = 2,   // waiting for the axis to settle there
	SCANTRIGGER_ARM         = 3,   // aligning the counter and enabling the trigger
	SCANTRIGGER_RUN         = 4,   // constant velocity run through the block
	SCANTRIGGER_WAIT_END    = 5,   // waiting for the axis to stop
	SCANTRIGGER_DISARM      = 6,   // disabling the trigger, reading the count
	SCANTRIGGER_DONE        = 7,
	SCANTRIGGER_ABORTED     = 8,
	SCANTRIGGER_OUTPUT_TEST = 9,   // driving the trigger pin directly, for a scope
	SCANTRIGGER_RETURN      = 10,  // going back to the scan start position
	SCANTRIGGER_WAIT_RETURN = 11,  // waiting for that move to finish
};
//-------------------------------//
// Line scan trigger recipe. Positions are absolute machine coordinates in mm.
//
// Speed, line rate and pitch are one relation:
//     speed [mm/s] = pitch [mm] x line rate [Hz]
// so exactly two of the three can be entered. The operator enters the pitch,
// which the optics fix, and the speed, which is what the machine is actually
// commanded to do and what the tact time is argued about in. SEQ derives the
// line rate from those two and reports it back, so the camera is set from a
// number nobody had to work out by hand.
//
// The trigger pulse width is entered rather than chosen here, because only the
// camera datasheet says what it needs. SEQ checks it against the line period
// and refuses a width that cannot fit.
//
// The four positions are NOT here. They live in the motor index table, at
// SCANTRIGGER_IDX_* in SEQ04_ScanTrigger.cpp, which is the machine's own way of
// naming a position and is what the motor screen already edits. Indices 50 and
// above sit in MOTOR_COMMON, so they belong to the machine rather than to one
// device, which is what a scan geometry is.
using _scantriggerrecipe = struct
{
	unsigned int uAxisNo;        // 0 based, same numbering the MMI uses elsewhere
	double dPitch;               // mm   (5 um = 0.005)
	double dSpeed;               // mm/s, entered
	double dPulseWidthUS;        // us,   entered
	unsigned int uTriggerMode;   // SCANTRIGGER_MODE

	// Reserved. The cycle runs at constant velocity through the trigger block,
	// so these are carried but not used yet. Present now so that adding the
	// approach profile later does not change the union layout.
	double dAccel;               // mm/s^2
	double dDecel;               // mm/s^2
	int    nDirection;           // +1 / -1

	// Grows and shrinks with the fields above so the struct keeps its size, and
	// a build that disagrees about one of them still agrees about the rest.
	// uTriggerMode came out of here, which is what it was for.
	unsigned int uReserved[9];
};
//-------------------------------//
// Everything SEQ computes from the recipe. Kept on one side only so the two
// programs cannot disagree about what a recipe means.
using _scantriggerdisplay = struct
{
	double dSpeed;               // mm/s  echoed back after validation
	double dLineRate;            // Hz    = speed / pitch, derived here
	int    nLineCount;           // lines = (end - start) / pitch
	double dScanTime;            // s     = (end - start) / speed
	double dMotionStart;         // mm    where the move begins, index 50
	double dMotionEnd;           // mm    where it ends, index 53
	double dTrigStart;           // mm    trigger block lower, index 51
	double dTrigEnd;             // mm    trigger block upper, index 52

	double dPitchCounts;         // pitch expressed in encoder counts
	bool   bPitchIsInteger;      // false means the comparator will round
	int    nValidateCode;        // 0 = accepted, see SCANTRIGGER_VALIDATE_*
	int    nState;               // current cycle state, SCANTRIGGER_STATE
	int    nTriggerCount;        // triggers counted, -1 when unavailable

	// What the chosen mode can actually deliver, which is the whole reason for
	// having two of them.
	//
	// PERIODIC rounds the pitch to a whole encoder count, so asking for 18.1 um
	// with a 1 um encoder gives 18.0 um - a 100 nm error, every line, in the
	// same direction. That is why it is refused rather than accepted quietly.
	//
	// TIMER sets an integer number of Hz, so the pitch lands on v / f. SEQ then
	// trims the speed to pitch x f, which removes the quantisation entirely:
	// dPitchErrorNM comes back 0 and dSpeedAdjusted says what the stage is
	// actually being asked to run at. What is left is velocity error, which no
	// number here can show.
	int    nTriggerMode;         // SCANTRIGGER_MODE actually programmed
	double dPitchAchieved;       // mm,   what the hardware will really emit
	double dPitchErrorNM;        // nm,   achieved - requested
	double dSpeedAdjusted;       // mm/s, the speed that makes the pitch exact

	// The recipe these numbers were computed from, echoed straight back.
	//
	// Every other field here is derived, so a panel showing them cannot tell
	// "this is my recipe's answer" from "this is the answer to a recipe SEQ
	// still has because my SET never landed". The two look identical - a set of
	// numbers that agree with each other and with nothing the operator typed -
	// and telling them apart has needed a console every time.
	//
	// With the recipe echoed, the panel compares it against its own boxes and
	// says so itself.
	double dRecipePitch;         // mm
	double dRecipeSpeed;         // mm/s
	double dRecipePulseUS;       // us
};
//-------------------------------//
// Counter board settings the scan trigger runs with. SEQ starts with the
// values the machine was commissioned with (SCANTRIGGER_DEFAULT_* in
// SEQ04_ScanTrigger.cpp) and the engineer screen can read and change them.
// A write is refused while a cycle or an output test is running, and SEQ
// answers a write with the settings it now holds, so the screen can check
// them rather than assume.
enum SCANTRIGGER_HWCFG_RESULT
{
	SCANTRIGGER_HWCFG_OK    = 0,
	SCANTRIGGER_HWCFG_BUSY  = 1,   // a cycle or an output test is running
	SCANTRIGGER_HWCFG_RANGE = 2,   // a value is outside what the board takes
};
using _scantriggerhwcfg = struct
{
	int          nChannel;         // counter channel, 0 based
	unsigned int uEncoderInput;    // which of the four encoder inputs feeds it
	unsigned int uOutPortMask;     // trigger outputs, bit0 = Trigger Out 0
	double       dEncUnitMM;       // mm per encoder count
	int          bEncReverse;      // 1 = count the encoder the other way
	unsigned int uTriggerLevel;    // 0 = low active, 1 = high active
	unsigned int uDirectionCheck;  // 0 = both, 1 = count up only, 2 = down only
	double       dWrongWayCounts;  // counts the counter may run backwards
	                               // during a scan before it is aborted
	int          nResult;          // SCANTRIGGER_HWCFG_RESULT, on a write's answer

	unsigned int uReserved[8];
};
//-------------------------------//
// What the counter channel is doing right now, for the live monitor.
using _scantriggercounter = struct
{
	int    bRead;            // 1 when the board answered the position read
	double dEncCount;        // counter position, counts
	double dEncPosMM;        // the same in mm
	int    nTriggerCount;    // pulses counted, -1 when the board cannot say
	int    nOutput;          // trigger output pin: 1 high, 0 low, -1 unknown
	double dArmCount;        // counter position when the last scan armed
	double dBlockLowerCnt;   // trigger block, counts (index 51)
	double dBlockUpperCnt;   // trigger block, counts (index 52)
	int    nState;           // SCANTRIGGER_STATE

	unsigned int uReserved[8];
};
//-------------------------------//
// Counter clear. Refused, like a settings write, unless the cycle is idle.
enum SCANTRIGGER_CNTCLR_MODE
{
	SCANTRIGGER_CNTCLR_TRIGGER_COUNT = 0,   // zero the pulse counter
	SCANTRIGGER_CNTCLR_ENC_TO_AXIS   = 1,   // set the counter to the axis position
};
using _scantriggercntclr = struct
{
	int nMode;               // SCANTRIGGER_CNTCLR_MODE
	int nResult;             // SCANTRIGGER_HWCFG_RESULT, on the answer
};
using _arg = union
{
    BYTE		Buffer[12000];
	_iobit	    IoBit;
    _datamemory DataMemory;
	_mtmove	    MotorMove;
	_mtstatus   MotorStatus;
	_mtdata	    MotorData;
	_mtcfg      MotorCfg;
	_device     Device;
	_manual		Manual;
    _tenkeyjog  TenKeyJog;
	_lifetime	LifeTime;
	_lampbuzzer	LampBuzzer;
	_errorcode	ErrorCode;
	_machinestatus		MachineStatus;
	_userinfo	UserInfo;
    _lotinfo	LotInfo;
	_deviceinfo DeviceInfo;
	_systemdata SystemData;
	_set3point	Set3Point;
	_flip1visionresult Flip1VisionResult;
	_flip2visionresult Flip2VisionResult;
	_pallet1visionresult Pallet1VisionResult;
	_pallet2visionresult Pallet2VisionResult;
	_frontpkvisionresult FrontPkVisionResult;
	_rearpkvisionresult RearPkVisionResult;
	_goodtray1visionresult	GoodTray1VisionResult;
	_goodtray2visionresult	GoodTray2VisionResult;
	_reworktrayvisionresult ReworkTrayVisionResult;
	_ngtrayresult NGTrayVisionResult;
	_flip1map	Flip1Map;
	_flip2map	Flip2Map;
	_pallet1map Pallet1Map;
	_pallet2map Pallet2Map;
	_frontpkmap FrontPkMap;
	_rearpkmap RearPkMap;
	_goodtray1map GoodTray1Map;
	_goodtray2map GoodTray2Map;
	_reworktraymap ReworkTrayMap;
	_ngtraymap NGTrayMap;
	_pkcentermove PkCenterMove;
	_frontpkcenteroffset FrontPkCenterOffset;
	_rearpkcenteroffset RearPkCenterOffset;
	_scantriggerrecipe  ScanTriggerRecipe;
	_scantriggerdisplay ScanTriggerDisplay;
	_scantriggerhwcfg   ScanTriggerHwCfg;
	_scantriggercounter ScanTriggerCounter;
	_scantriggercntclr  ScanTriggerCntClr;
};

//-------------------------------//
enum TCmdType {
	CMD_READ_BITV = 1,
	CMD_WRITE_BITV,
	CMD_READ_DM,
	CMD_WRITE_DM,
	CMD_READ_IO,
	CMD_WRITE_IO,
	CMD_READ_ERRORCODE,
	CMD_SERVO_ONOFF,
	CMD_SERVO_HOME,
	CMD_SERVO_ALARM_CLEAR,
	CMD_READ_MOTORSTATUS,
	CMD_MOTORSCONTINUE,
	CMD_MOTORSRELATIVE,
	CMD_MOTORINDEXMOVE,
	CMD_MOTORSTOP,
	CMD_WRITE_MOTORDATA,
	CMD_READ_MOTORDATA,
	CMD_READ_MOTORCONFIG,
	CMD_WRITE_MOTORCONFIG,
	CMD_READ_DEVICEDATA,
	CMD_WRITE_DEVICEDATA,
	CMD_TENKEY,
	CMD_LAMPBUZZER,
	CMD_READ_STATUS,
	CMD_WRITE_STATUS,
	CMD_READ_USER_INFO,
	CMD_WRITE_USER_INFO,
	CMD_READ_LOTINFO,
	CMD_WRITE_LOTINFO,
	CMD_READ_DEVICE_INFO,
	CMD_WRITE_DEVICE_INFO,
	CMD_WRITE_TENKEYJOG,
	CMD_WRITE_LOAD_CNT_CLEAR,
	CMD_WRITE_UNLOAD_CNT_CLEAR,
	CMD_WRITE_EMERGENCY_STOP,
	CMD_WRITE_SYSTEM_DATA,
	CMD_WRITE_BUZZER_OFF,
	CMD_WRITE_3POINT_SETTING,
	CMD_READ_3POINT_OFFSET,

	CMD_READ_FLIP1_VISION_RESULT,
	CMD_WRITE_FLIP1_VISION_RESULT,
	CMD_READ_FLIP2_VISION_RESULT,
	CMD_WRITE_FLIP2_VISION_RESULT,
	CMD_READ_PALLET1_VISION_RESULT,
	CMD_WRITE_PALLET1_VISION_RESULT,
	CMD_READ_PALLET2_VISION_RESULT,
	CMD_WRITE_PALLET2_VISION_RESULT,
	CMD_READ_FRONT_PICKER_RESULT,
	CMD_WRITE_FRONT_PICKER_VISION_RESULT,
	CMD_READ_REAR_PICKER_RESULT,
	CMD_WRITE_REAR_PICKER_VISION_RESULT,
	CMD_READ_GOOD_TRAY1_VISION_RESULT,
	CMD_READ_GOOD_TRAY2_VISION_RESULT,
	CMD_READ_REWORK_TRAY_VISION_RESULT,
	CMD_READ_NG_TRAY_VISION_RESULT,
	
	CMD_READ_FLIP1_MAP,
	CMD_WRITE_FLIP1_MAP,
	CMD_READ_FLIP2_MAP,
	CMD_WRITE_FLIP2_MAP,
	CMD_READ_PALLET1_MAP,
	CMD_WRITE_PALLET1_MAP,
	CMD_READ_PALLET2_MAP,
	CMD_WRITE_PALLET2_MAP,
	CMD_READ_FRONT_PICKER_MAP,
	CMD_WRITE_FRONT_PK_MAP,
	CMD_READ_REAR_PICKER_MAP,
	CMD_WRITE_REAR_PK_MAP,
	CMD_READ_GOOD_TRAY1_MAP,
	CMD_WRITE_GOOD_TRAY1_MAP,
	CMD_READ_GOOD_TRAY2_MAP,
	CMD_WRITE_GOOD_TRAY2_MAP,
	CMD_READ_REWORK_TRAY_MAP,
	CMD_WRITE_REWORK_TRAY_MAP,
	CMD_READ_NG_TRAY_MAP,
	CMD_WRITE_NG_TRAY_MAP,
	
	CMD_WRITE_PK_CENTER_MOVE,
	CMD_WRITE_PK_CENTER_TRIGGER,
	CMD_READ_FRONT_PK_CENTER_OFFSET,
	CMD_READ_REAR_PK_CENTER_OFFSET,
	CMD_WRITE_PK_CENTER_AUTO_CAL,
	CMD_WRITE_SCANTRIGGER_RECIPE,
	CMD_READ_SCANTRIGGER_DISPLAY,
	CMD_WRITE_SCANTRIGGER_START,
	CMD_WRITE_SCANTRIGGER_STOP,
	CMD_WRITE_SCANTRIGGER_TEST,
	CMD_READ_SCANTRIGGER_COUNTER,
	CMD_WRITE_SCANTRIGGER_CNTCLR,
	CMD_READ_SCANTRIGGER_HWCFG,
	CMD_WRITE_SCANTRIGGER_HWCFG,

	CMD_PROGRAMEXIT	= 199,
};
//-------------------------------//
using TMemCommand = struct {
	BYTE  Flag;
	BYTE  Command;
	BYTE  Result;
	_arg  Arg;
	bool  isack;
	DWORD CRC;
};
//-------------------------------//
class SHARED_MEMORY_BASE
{
private:
	int	SM_TM_OUT;
protected:
	HANDLE  hEventTx, hEventRx;
	HANDLE  hMutexTx, hMutexRx;
	HANDLE  hSharedMemory;
	PUCHAR  pTxBuffer, pRxBuffer;

protected:
	bool InitMutex(HANDLE hdl)
	{
		int iFailCount = 0;
		while (true) {
			BOOLEAN  flagExit = false;

			DWORD dwWaitResult = WaitForSingleObject(hdl, 3000); //3_secound
			switch (dwWaitResult)
			{
			case WAIT_OBJECT_0:
				ReleaseMutex(hdl);
				flagExit = true;
				break;
			case WAIT_ABANDONED:
				ReleaseMutex(hdl);
				break;
			case WAIT_TIMEOUT:
				return false;
			default:
				break;
			}

			if (false != flagExit) { break; }
			else { iFailCount++; }
			if (iFailCount > 3) return false;
		}

		return true;
	}
	void CleanObject(void)
	{
		if (nullptr != hSharedMemory)
		{ 
			CloseHandle(hSharedMemory);	
			hSharedMemory = NULL; 
		}
		if (nullptr != hMutexRx)
		{ 
			CloseHandle(hMutexRx);
			hMutexRx = nullptr; 
		}
		if (nullptr != hMutexTx)
		{ 
			CloseHandle(hMutexTx);
			hMutexTx = nullptr; 
		}
		if (nullptr != hEventRx)		
		{ 
			CloseHandle(hEventRx);
			hEventRx = nullptr; 
		}
		if (nullptr != hEventTx)		
		{ 
			CloseHandle(hEventTx);		
			hEventTx = nullptr; 
		}
		//--------------------------//
		pTxBuffer = pRxBuffer = nullptr;
		//--------------------------//
	}
public:
	SHARED_MEMORY_BASE()
	{
		hEventTx = hEventRx = nullptr;
		hMutexTx = hMutexRx = nullptr;
		hSharedMemory = nullptr;
		pTxBuffer = pRxBuffer = nullptr;
		SM_TM_OUT = 1;
	}

	~SHARED_MEMORY_BASE()
	{
		CleanObject();
	}

	bool InitObject(int SM_TYPE, int iTimeout)
	{
		HANDLE  hA, hB, hC, hD;
		//--------------------------//
		SM_TM_OUT = iTimeout;
		//--------------------------//
		while (true) 
		{
			hA = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"/MUTEXA");
			if (nullptr == hA) {
				hA = CreateMutex(nullptr, false, L"/MUTEXA");
				if (nullptr == hA) {
					printf("\nMutex A Create Error\n");
					break;
				}
			}
			hB = OpenMutex(MUTEX_ALL_ACCESS, false, L"/MUTEXB");
			if (nullptr == hB) {
				hB = CreateMutex(nullptr, false, L"/MUTEXB");
				if (nullptr == hB) {
					printf("\nMutex B Create Error\n");
					break;
				}
			}
			hC = OpenEvent(EVENT_ALL_ACCESS, false, L"/EVENT/RTXA");
			if (nullptr == hC) {
				hC = CreateEvent(nullptr, TRUE, TRUE, L"/EVENT/RTXA");
				if (nullptr == hC) {
					printf("\nEvent A Create Error\n");
					break;
				}
			}
			hD = OpenEvent(EVENT_ALL_ACCESS, false, L"/EVENT/RTXB");
			if (nullptr == hD) {
				hD = CreateEvent(nullptr, TRUE, TRUE, L"/EVENT/RTXB");
				if (nullptr == hD) {
					printf("\nEvent B Create Error\n");
					break;
				}
			}

			PVOID  pLoc;
			pLoc = nullptr;

			//-- WIN 32 --//
			hSharedMemory = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"/SMEMORY");
			if (nullptr == hSharedMemory) 
			{
				hSharedMemory = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, SHALLOCSIZE, L"/SMEMORY");
				
				if (nullptr == hSharedMemory) 
				{
					printf("\nShared Memory Creation Error..[%lu]\n", GetLastError());
					break;
				}
			}

			pLoc = MapViewOfFile(hSharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, SHALLOCSIZE);
			if (pLoc == nullptr) {
				printf("\nShared Memory Allocation Error..[%lu]\n", GetLastError());
				break;
			}

			ZeroMemory(pLoc, SHALLOCSIZE);

			if (SM_TYPE == RUN_SEQ) {
				hMutexTx = hA;
				hMutexRx = hB;
				hEventTx = hC;
				hEventRx = hD;
				pTxBuffer = static_cast<PUCHAR>(pLoc); //(PUCHAR)pLoc;
				pRxBuffer = &(static_cast<PUCHAR>(pLoc)[SHALLOCSIZE / 2]); //&(((PUCHAR)pLoc)[SHALLOCSIZE/2]);
			}
			else {
				hMutexTx = hB;
				hMutexRx = hA;
				hEventTx = hD;
				hEventRx = hC;
				pTxBuffer = &(static_cast<PUCHAR>(pLoc)[SHALLOCSIZE / 2]); // &(((PUCHAR)pLoc)[SHALLOCSIZE / 2]);
				pRxBuffer = static_cast<PUCHAR>(pLoc); // (PUCHAR)pLoc;
			}

			SetEvent(hEventRx);
			SetEvent(hEventTx);

			if (false == InitMutex(hMutexTx))
			{ 
				return false; 
			}
			if (false == InitMutex(hMutexRx))
			{ 
				return false; 
			}

			ReleaseMutex(hMutexRx);
			ReleaseMutex(hMutexTx);

			return true;
		}

		CleanObject();
		return true;
	}

	bool Send(TMemCommand* Cmd)
	{
		if (nullptr == hMutexTx) 
		{ 
			return false; 
		}

		if (WaitForSingleObject(hMutexTx, SM_TM_OUT) != WAIT_OBJECT_0) return false;

		auto pCmdBuffer = (PCHAR)pTxBuffer;
		
		if (pCmdBuffer[0] != 0x00) 
		{
			ReleaseMutex(hMutexTx);
			return false;
		}

		CopyMemory(pCmdBuffer, Cmd, sizeof(TMemCommand));

		pCmdBuffer[0] = (-1); 
		ReleaseMutex(hMutexTx);
		SetEvent(hEventTx);
		return true;
	}

	bool Recv(TMemCommand* Cmd)
	{
		if (nullptr == hMutexRx) 
		{ 
			return false; 
		}

		if (WaitForSingleObject(hMutexRx, SM_TM_OUT) != WAIT_OBJECT_0) return false;

		auto pCmdBuffer = (PCHAR)pRxBuffer;
		
		if (pCmdBuffer[0] == 0x00) {
			ReleaseMutex(hMutexRx);
			return false;
		}

		CopyMemory(Cmd, pCmdBuffer, sizeof(TMemCommand));

		pCmdBuffer[0] = 0x00;
		ReleaseMutex(hMutexRx);
		SetEvent(hEventRx);
		return true;
	}

	void FlushInOutBuffer()
	{
		ZeroMemory(pRxBuffer, sizeof(TMemCommand));
		ZeroMemory(pTxBuffer, sizeof(TMemCommand));
	}
};

//class CRTT_RUN_CHECK
//{
//protected:
//	HANDLE  hEventApp;
//public:
//	~CRTT_RUN_CHECK()
//	{
//		if (nullptr != hEventApp) { CloseHandle(hEventApp);  hEventApp = nullptr; }
//	}
//	void Check(int iRuntype = RUN_SEQ)
//	{
//		if (iRuntype == RUN_SEQ) {
//			hEventApp = OpenEvent(SYNCHRONIZE, 0, L"/RUN_SEQ");
//			if (nullptr == hEventApp) {
//				hEventApp = CreateEvent(nullptr, TRUE, TRUE, L"/RUN_SEQ");
//			}
//			else {
//				printf("\n Sequence Program Is Already Execute..........\n");
//				ExitProcess(0);
//			}
//		}
//		else {
//			hEventApp = OpenEvent(SYNCHRONIZE, 0, L"/RUN_MMI");
//			if (nullptr == hEventApp) {
//				hEventApp = CreateEvent(nullptr, TRUE, TRUE, L"/RUN_MMI");
//			}
//			else {
//				printf("\n MMI(GUI) Program Is Already Execute..........\n");
//				ExitProcess(0);
//			}
//		}
//	}
//};

#pragma pack(pop)   /* restore original alignment from stack */
#endif