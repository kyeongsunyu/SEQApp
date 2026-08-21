#ifndef _DEF_DATA_STRUCTURE_H
#define _DEF_DATA_STRUCTURE_H

#pragma once

/************************************************************************/
/*	DWORD128 사용법	                                                    */
/*	DWORD128 MatchData[100];                                            */
/*	DWORD64 mask	                                                    */
/*	MatchData[y].Data[0]&=(~mask);                                      */
/*	MatchData[y].Data[1]&=(~mask);	                                    */
/*	MatchData[y].Data[0]=0xffffffffffffffff;	  // 64 Bit             */
/*	MatchData[y].Data[1]=0xffffffffffffffff;	  // 64 Bit             */
/************************************************************************/
struct DWORD128
{
	__int64 Data[2];
	DWORD128 operator & (DWORD128& in);
	DWORD128 operator | (DWORD128& in);
	DWORD128 operator << (int in);
	DWORD128 operator >> (int in);
	DWORD128& operator = (int in);
	DWORD128& operator = (DWORD128 in);
	bool operator == (int in);
};
//---------------------------------------------------------------------------
inline DWORD128 DWORD128::operator&(DWORD128& in)
{
	DWORD128 ret;
	ret.Data[0] = Data[0];
	ret.Data[1] = Data[1];

	ret.Data[0] &= in.Data[0];
	ret.Data[1] &= in.Data[1];
	return ret;
}
//---------------------------------------------------------------------------
inline DWORD128 DWORD128::operator|(DWORD128& in)
{
	DWORD128 ret;
	ret.Data[0] = Data[0];
	ret.Data[1] = Data[1];

	ret.Data[0] |= in.Data[0];
	ret.Data[1] |= in.Data[1];
	return ret;
}
//---------------------------------------------------------------------------
inline DWORD128 DWORD128::operator<<(int in)
{
	DWORD128 ret;
	__int64 temp;

	ret.Data[0] = Data[0];
	ret.Data[1] = Data[1];

	if (in < sizeof(__int64) * 8) {
		temp = ret.Data[0];
		temp >>= (sizeof(__int64) * 8 - (__int64)in);

		ret.Data[0] <<= in;
		ret.Data[1] <<= in;

		ret.Data[1] = ret.Data[1] | temp;
	}
	else {
		ret.Data[0] = 0;
		ret.Data[1] = ret.Data[0] << (in - sizeof(__int64) * 8);
	}
	return ret;
}
inline DWORD128 DWORD128::operator>>(int in)
{
	DWORD128 ret;
	__int64 temp;

	ret.Data[0] = Data[0];
	ret.Data[1] = Data[1];

	if (in < sizeof(__int64) * 8) {
		temp = ret.Data[1];
		temp <<= (sizeof(__int64) * 8 - (__int64)in);

		ret.Data[0] >>= in;
		ret.Data[1] >>= in;

		ret.Data[0] = ret.Data[0] | temp;
	}
	else {
		ret.Data[1] = 0;
		ret.Data[0] = ret.Data[1] >> (in - sizeof(__int64) * 8);
	}
	return ret;
}
inline DWORD128& DWORD128::operator=(int in)
{
	Data[0] = (__int64)in;
	Data[1] = (__int64)0;
	return *this;
}
inline DWORD128& DWORD128::operator=(DWORD128 in)
{
	Data[0] = (__int64)in.Data[0];
	Data[1] = (__int64)in.Data[1];
	return *this;
}
inline bool DWORD128::operator==(int in)
{
	if (Data[0] == (__int64)in && Data[1] == 0)
		return true;
	else
		return false;
}

enum SENSOR_TYPE {
	ORG = 1,
	CCW = 2,
	ORG_CCW = 3,
	Z_ORG_CCW = 4,
};

enum _eHomeState
{
	HOME_STATE_ALARM = 0x00,
	HOME_STATE_READY = 0x01,
	HOME_STATE_HOMMING = 0x02,
	HOME_STATE_COMPLETE = 0x03,
};

enum _eMZStatus
{
	MZ_EMPTY = 0,
	MZ_WORK_READY = 1,
	MZ_WORK_DONE = 2,
};

enum _eCycle
{
	CYCLE_CART_RESET = 0,
	CYCLE_CART_RELEASE = 1,
	CYCLE_CART_DOCKING = 2,
	CYCLE_MZIN_PNP = 3,
	CYCLE_MZOUT_PNP = 4,
	CYCLE_MZIN_CONV_LOADING = 5,
	CYCLE_LDMZELEV_MZ_LOADING = 6,
	CYCLE_LDMZELEV_MZ_EJECT = 7,
	CYCLE_LDMZELEV_BOAT_LOADING = 8,
};

enum _ePkAngle
{
	ANGLE_0	= 0,
	ANGLE_90 = 1,
	ANGLE_180 = 2,
	ANGLE_270 = 3,
};

enum _ePicker
{
	FRONT_PK = 0,
	REAR_PK = 1,
};

enum _eFlip
{
	HORIZONTAL =0,	// 좌우 Flip
	VERTICAL = 1,	// 상하 Flip
};

enum _eZigZagLeftRight
{
	LEFT_TO_RIGHT = 0,
	RIGHT_TP_LEFT = 1,
};
enum _eZigZagUpDn
{
	UP_TO_DOWN = 0,
	DOWN_TO_UP = 1,
};

enum _eTrayCheck
{
	TRAY_CHECK_ERR_REAR = -2,
	TRAY_CHECK_ERR_FRONT = -1,
	TRAY_CHECK_OFF = 0,
	TRAY_CHECK_ON = 1,
};

enum _eTrayMap
{
	TRAY_MAP_EMPTY = 0,
	TRAY_MAP_GOOD1,
	TRAY_MAP_GOOD2,
	TRAY_MAP_REWORK,
	TRAY_MAP_NG,
};

//enum _eDeviceData
//{
//	UNIT_X_SIZE = 0,
//	UNIT_Y_SIZE = 1,
//	UNIT_X_CNT = 2,
//	UNIT_Y_CNT = 3,
//	UINT_X_PITCH = 4,
//	UINT_Y_PITCH = 5,
//	TRAY_X_CNT = 6,
//	TRAY_Y_CNT = 7,
//	VISION_SNAP_X_CNT = 8,
//	VISION_SNAP_Y_CNT = 9,
//	PK_T_ANGLE = 10,
//	PLACE_VAC_OFF_OFFSET = 11,
//};
//
//enum _eDeviceIntData
//{
//	SPONGE_CLEAN_CNT = 0,
//	WATERJET_WATER_CLEAN_CNT = 1,
//	WATERJET_AIR_CLEAN_CNT = 2,
//	SAW_PK_FLIPY1_AIR_CLEAN_CNT = 3,
//	SAW_PK_FLIPY2_AIR_CLEAN_CNT = 4,
//	FLIPY1_AIR_CLEAN_CNT = 5,
//	FLIPY2_AIR_CLEAN_CNT = 6,
//	PALLETY1_AIR_CLEAN_CNT = 7,
//	PALLETY2_AIR_CLEAN_CNT = 8,
//	
//};
//enum _eDeviceBoolData
//{
//	FRONT_PK1_SKIP = 0,
//	FRONT_PK2_SKIP = 1,
//	FRONT_PK3_SKIP = 2,
//	FRONT_PK4_SKIP = 3,
//	FRONT_PK5_SKIP = 4,
//	FRONT_PK6_SKIP = 5,
//	FRONT_PK7_SKIP = 6,
//	FRONT_PK8_SKIP = 7,
//	REAR_PK1_SKIP = 8,
//	REAR_PK2_SKIP = 9,
//	REAR_PK3_SKIP = 10,
//	REAR_PK4_SKIP = 11,
//	REAR_PK5_SKIP = 12,
//	REAR_PK6_SKIP = 13,
//	REAR_PK7_SKIP = 14,
//	REAR_PK8_SKIP = 15,
//
//	SCRAP_SKIP = 16,
//	SPONDGE_CLEAN_SKIP = 17,
//};
//enum _eDeviceDoubleData
//{
//	FRONT_PK_BLOW_TIME = 0,
//	REAR_PK_BLOW_TIME = 1,
//};

enum _eSysData
{
	FRONT_PK1_LIFETIME = 0,
	FRONT_PK2_LIFETIME = 1,
	FRONT_PK3_LIFETIME = 2,
	FRONT_PK4_LIFETIME = 3,
	FRONT_PK5_LIFETIME = 4,
	FRONT_PK6_LIFETIME = 5,
	FRONT_PK7_LIFETIME = 6,
	FRONT_PK8_LIFETIME = 7,

	REAR_PK1_LIFETIME = 8,
	REAR_PK2_LIFETIME = 9,
	REAR_PK3_LIFETIME = 10,
	REAR_PK4_LIFETIME = 11,
	REAR_PK5_LIFETIME = 12,
	REAR_PK6_LIFETIME = 13,
	REAR_PK7_LIFETIME = 14,
	REAR_PK8_LIFETIME = 15,

	SPONGE_LIFETIME = 16,

	GOOD_TRAY1_FULL = 17,
	GOOD_TRAY2_FULL = 18,
	REWORK_TRAY_FULL = 19,
	NG_TRAY_FULL = 20,
};

enum _eMapTarget
{
	FLIPY1=0,
	FLIPY2,
	PALLETY1,
	PALLETY2,
	GOOD_TRAY1,
	GOOD_TRAY2,
	REWORK_TRAY,
	NG_TRAY,
};

enum _eMapDir
{
	MAP_DIR_X = 0,
	MAP_DIR_Y = 1,
};
enum _eMapState
{
	DUMMY =-1,
	EMPTY = 0,
	EXIST = 1,
};

enum _eInspectResult
{
	TVR_NONE = 0,
	TVR_BALL_GOOD = 1,
	TVR_BALL_NG = 2,
	TVR_BALL_REWORK = 3,

	TVR_MARK_GOOD = 4,
	TVR_MARK_NG = 5,
	TVR_MARK_REWORK = 6,

	TVR_BTM_GOOD = 7,
	TVR_BTM_NG = 8,
	TVR_BTM_REWORK = 9,
};

enum _eVisionResult
{
	TVR_DUMMY = -1,
	TVR_EMPTY = 0,
	TVR_GOOD = 1,
	TVR_REWORK = 2,
	TVR_NG = 3,
};

enum _ePickerDir
{
	PK_FORWARD = 0,
	PK_REVERSE = 1,
};

enum _e3Point
{
	P1 = 1,
	P2 = 2,
	P3 = 3,
};

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */
typedef struct {
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
} TDeviceData;
#pragma pack(pop)   /* restore original alignment from stack */

typedef struct {
	// 
	double UnitXSize;
	double UnitYSize;
	
	int UnitXCnt;
	int UnitYCnt;

	double UnitXPitch;
	double UnitYPitch;

	int TrayXCnt;
	int TrayYCnt;

	int SnapXCnt;
	int SnapYCnt;

	int PkTAngle;

	double PkPlaceVacOffOffset;

	// 
	bool bFrontPk1SKIP;
	bool bFrontPk2SKIP;
	bool bFrontPk3SKIP;
	bool bFrontPk4SKIP;
	bool bFrontPk5SKIP;
	bool bFrontPk6SKIP;
	bool bFrontPk7SKIP;
	bool bFrontPk8SKIP;
	bool bFrontPickerSKIP[8];

	bool bRearPk1SKIP;
	bool bRearPk2SKIP;
	bool bRearPk3SKIP;
	bool bRearPk4SKIP;
	bool bRearPk5SKIP;
	bool bRearPk6SKIP;
	bool bRearPk7SKIP;
	bool bRearPk8SKIP;
	bool bRearPickerSKIP[8];

	bool bScrapSKIP;
	bool bSpongeCleanSKIP;

	// 
	int SpongeCleanCnt;
	int WaterJetWaterCleanCnt;
	int WaterJetAirCleanCnt;
	int SawPkFlipY1AirClenaCnt;
	int SawPkFlipY2AirClenaCnt;
	int FlipY1AirCleanCnt;
	int FlipY2AirCleanCnt;
	int PalletY1AirCleanCnt;
	int PalletY2AirCleanCnt;

	// 
	int FrontPkBlowTime;
	int RearPkBlowTime;
	int FrontPkVacOnTime;
	int RearPkVacOnTime;

	int LoadPkAirBlowTime;
	int LoadPkVacOnTime;
	int SawPkAirBlowTime;
	int SawPkVacOnTime;

	double Pallet1_Receive_Vac_Value;
	double Pallet2_Receive_Vac_Value;
	double PalletFirstSortVacValue;
	double PalletMiddleSortVacValue;
	double PalletLastSortVacValue;
	double PalletFirstSortPKGRate;
	double PalletLastSortPKGRate;
} TRcpVal;

typedef struct {
	double dData[100];
} TSystemData;

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */
typedef struct {
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

	bool bInputState[20][16];
	bool bOutputState[20][16];

	bool bVisionConnected;
} TMachineStatus;
#pragma pack(pop)   /* restore original alignment from stack */

typedef struct {
	char strUserName[64];
} TUSER_INFO;

typedef struct {
	char strLotID[128];
	int nLotCount;
} TLOT_INFO;

typedef struct {
	int nDeviceNumber;
	char strDeviceName[64];
} TDeviceInfo;

typedef struct {
	int PkType;
	int PkNo;
	double posx[10];
	double posy[10];
} TPkCenterMove;

typedef struct {
	double XOffset[10];
	double YOffset[10];
} TFrontPkCenterOffset;

typedef struct {
	double XOffset[10];
	double YOffset[10];
} TRearPkCenterOffset;

typedef struct{
	int pktype;
	int target;
	int pointno;

	double offsetX;
	double offsetY;
	double offsetT;
} TSet3Point;



#define VISION_HEADER_SIZE   		4

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */
typedef struct
{
	WORD    wMsgLength;
	BYTE    bCameraNumber;
	BYTE    bMsgCode;
} VISION_HEADER, *PVISION_HEADER;

typedef struct                                                           // OCS Data Struct
{
	VISION_HEADER VisionHeader;
	BYTE    bVisionData[1024];
} VISION_PROTOCOL_DATA, *PVISION_PROTOCOL_DATA;


typedef struct
{
	BYTE byCommand;
	WORD wRecipeNo;
	char strRecipeID[20];
	char strUnitXSize[5];
	char strUnitYSize[5];
	BYTE bySnapXCnt;
	BYTE bySnapYCnt;
	BYTE byInspectionType;
	BYTE byTrigNo;
	BYTE byPointNo;
	char strLocationX[10];
	char strLocationY[10];
} VISION_TX_DATA, *PVISION_TX_DATA;

typedef struct
{
	BYTE byCommand;
	WORD wRecipeNo;
	char strRecipeID[20];
	char strUnitXSize[5];
	char strUnitYSize[5];
	BYTE bySnapXCnt;
	BYTE bySnapYCnt;
	BYTE byTrigNo;
	BYTE byPointNo;
	BYTE byInspectionType;
	BYTE byBallResult;
	BYTE byMarkResult;
	char strPk1OffsetX[5];
	char strPk1OffsetY[5];
	char strPk1OffsetT[5];
	char strPk2OffsetX[5];
	char strPk2OffsetY[5];
	char strPk2OffsetT[5];
	char strPk3OffsetX[5];
	char strPk3OffsetY[5];
	char strPk3OffsetT[5];
	char strPk4OffsetX[5];
	char strPk4OffsetY[5];
	char strPk4OffsetT[5];
	char strPk5OffsetX[5];
	char strPk5OffsetY[5];
	char strPk5OffsetT[5];
	char strPk6OffsetX[5];
	char strPk6OffsetY[5];
	char strPk6OffsetT[5];
	char strPk7OffsetX[5];
	char strPk7OffsetY[5];
	char strPk7OffsetT[5];
	char strPk8OffsetX[5];
	char strPk8OffsetY[5];
	char strPk8OffsetT[5];
} VISION_RX_DATA, *PVISION_RX_DATA;

#pragma pack(pop)   /* restore original alignment from stack */
#endif