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