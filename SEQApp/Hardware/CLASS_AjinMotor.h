#ifndef _AJIN_MOTOR_H_
#define _AJIN_MOTOR_H_

#pragma once
#include "..\..\Library\AXL(Library)\C, C++\AXA.h"
#include "..\..\Library\AXL(Library)\C, C++\AXHS.h"
#include "..\..\Library\AXL(Library)\C, C++\AXM.h"
#include "..\..\Library\AXL(Library)\C, C++\AXDev.h"
#include "..\..\Library\AXL(Library)\C, C++\AXL.h"
#include "..\..\Library\AXL(Library)\C, C++\AXD.h"

#include "..\Func\CLASS_TIMER.h"


//////////////////////////////////////////////////////////////////////////
class  CAjinBase 
{
private:
	unsigned short int* address;
public:
	CAjinBase();
	~CAjinBase();

	void InitBase();
	unsigned short int  Isct2dMode();
	DWORD GetModuleNodeStatus(long lBoardNo, long lModulePos);
	DWORD ReadInportFallback(long lOffset, DWORD* upValue);
	DWORD WriteOutportFallback(long lOffset, DWORD dwValue);
	void ReadECATPdoInput(DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);
	void WriteECATPdoOutput(DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData);
	unsigned char   axis;
	unsigned short int  output;
	BOOL bct2dMode;
};

class CAjinMotor
{
private:
	unsigned char   axis;
public:
	CAjinMotor(unsigned short int axs_no, unsigned short int logical_no);
	~CAjinMotor();

	long GetTotalAxisCount();
	
	void SetSWLimitMode(bool Enable);
	void SetHWLimitMode(DWORD CW_LogicLevel, DWORD CCW_LogicLevel);
	void SetInpositionMode(DWORD LogicLevel, DWORD Enable);
	void SetAlarmEnable(int Enable);
	void SetAlarmClearOn();
	void SetAlarmClearOff();
	void SetPulseMode(int mode);
	void SetEncoderInputMethos(unsigned char method);
	void SetMoveRatio();
	void SetServoOnLogic(DWORD LogicLevel);
	void ServoOn();
	void ServoOff();
	void SetInitSpeed(double InitSpeed);
	void SetMaxSpeed(int maxspeed);
	void SetSignalStop(DWORD uStopMode, DWORD uLevel);
	void SetHomeSignalLevel(DWORD uLevel);

	// Single Axis Drive Function
	void MTSRMove(int pulse);		// Scurve Relative
	void MTSAMove(int Position);	// Scurve Absolute
	void MTSCMove();				// Scurve Continuous
	void MTOverRideMove(double ratio);

	void MTEStop();
	void MTStop();
	void MTDecelStopRate(double rate);
	
	void SetCommandPosition(int Position);
	int GetCommandPosition();
	void SetActualPosition(int Position);
	int GetActualPosition();

	void GetMotorStatus();
	void SetInitPosition();
	void SetTriggerEnable();
	void SetTriggerProfile(int pulse, int time);
	void GetServoAlarmCodeName(void);
	void SetServoLoadRatio(DWORD dwSelMon);
	double GetServoLoadRatio(void);

	MOTION_INFO	MS;

	CRtTimer MotorStop;
	CRtTimer MotorAlarmResetOn;
	CRtTimer MotorResetOff;

	DWORD SensorType;

	DWORD MotorType;

	int ActualPosition;
	int CommandPosition;
	unsigned short int SpeedDevide;  // to seperate manual, auto running speed
	unsigned short int MinMovingTime;
	unsigned short int AxisNO;		// Physical order
	unsigned short int AxisLogicNO;	// program logical order
	unsigned short int sHomeState;
	unsigned short int CancelCmd;
	unsigned short int CmdMode;
	double Speed;
	double Accel;
	double Decel;
	double Jerk;
	double SaveSpeed;
	double SaveAccel;
	double SaveJerk;
	double InitSpeed;
	double MaxSpeed;
	int CurPos;
	int NxtPos;
	unsigned short int WorkPos;
	unsigned short int DfltWorking;
	bool bOverRide;
	double OverRidePos;
	double OverRideRatio;

	//-- FLAG --//
	unsigned short int fDoHome : 1;
	unsigned short int fIMRS : 1;
	unsigned short int fMotorPause : 1;
	unsigned short int fMotorHome : 1;
	unsigned short int fDriving : 1;
	unsigned short int IsHWLimitCW : 1;
	unsigned short int IsHWLimitCCW : 1;
	unsigned short int IsDRVRDY : 1;
	unsigned short int IsORG : 1;
	unsigned short int IsAlarm : 1;
	unsigned short int IsInposition : 1;
	unsigned short int IsServoOn : 1;
	unsigned short int PrevIsServoOn : 1;
	unsigned short int IsDriving : 1;
	unsigned short int IsStop : 1;
	unsigned short int IsZPhase : 1;
	unsigned short int EncoderSet : 1;
	unsigned short int AlramReset : 1;
	unsigned short int EncoderType : 1;
	unsigned short int IsHomming : 1;

	unsigned short int omove : 1;
	unsigned short int moving : 1;
	unsigned short int relative : 1;

	unsigned short int imrs : 1;
	unsigned short int irdy : 1;
	unsigned short int isend : 1;
	unsigned short int idrvalm : 1;
	unsigned short int idrvrdy : 1;
	unsigned short int canmovejog : 1;
	unsigned short int ostart : 1;

	double* ZPhaseSpeed;         // speed that after touch org sensor
	double* HomeSpeed;
	double MovingDistance;
	double TimeDesier;
	int AdjustPosition;
	double CurArrpos;
	double NxtArrpos;
	int Direction;

	double PositionArray[100];			// device dependent positions of motor
	double SpeedArray[100];			// speed of positions of motor
	double AccelArray[100];
	double DecelArray[100];

	/* Motor Config Data from Data File */
	DWORD	bCwLimitLevel;
	DWORD	bCCwLimitLevel;
	DWORD	bServoOnLevel;
	DWORD	bAlarmLevel;
	DWORD	bInpLevel;
	DWORD	bInpEnable;
	DWORD	nPulseOutM;
	DWORD   nEncDir;
	DWORD  	nEncType;
	DWORD	nMotorType;
	DWORD   nSensorType;

	/* Motor Config Data from MMI Data */
	unsigned int MMI_PulseRate;
	unsigned int MMI_MaxVel;
	unsigned int MMI_JogVel;
	unsigned int MMI_HomeVel;
	unsigned int MMI_Accel;
	unsigned int MMI_HomeLevel;
	unsigned int MMI_LimitLevel;
	unsigned int MMI_ServoOnLevel;
	unsigned int MMI_AlarmLevel;
	unsigned int MMI_InpUse;
	unsigned int MMI_MtrDir;
	unsigned int MMI_EncDir;
	unsigned int MMI_MotorType;		// 1:Servo, 2:Cool muscle 3:Step
	unsigned int MMI_Enc_Type;
	//////////////////////////////////////////////////////////////////////////

	unsigned char bCamType;
	

	DWORD dwServoAlarmCode;
	char strServoAlarmName[1025] = "";

	double dServoLoadRatio;

	//////////////////////////////////////////////////////////////////////////
	// EtherCat
	DWORD dwBitOffset;
	DWORD dwDataBitLength;
	BYTE byTorqueValue = 0;

};

#endif