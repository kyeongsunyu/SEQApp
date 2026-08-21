#ifndef _GV_H_
#define _GV_H_

#pragma once

#include <Windows.h>
#include <stdexcept>

#include "Define\DEFINE_IO.h"
#include "Define\DEFINE_Bit.h"
#include "Define\DEFINE_Macro.h"
#include "Define\DEFINE_DM.h"
#include "Define\DEFINE_ErrorCode.h"
#include "Define\DEFINE_Data.h"
#include "Define\DEFINE_MotorPosition.h"
#include "..\Func\NVMMF.h"
#include "..\Func\CLASS_TIMER.h"
#include "..\Tools\CLASS_FileLog.h"
#include "..\Hardware\CLASS_AjinIO.h"
#include "..\Hardware\CLASS_AjinMotor.h"
#include "..\Hardware\CLASS_TenKey.h"
#include "..\\Hardware\CLASS_AjinCounter.h"
#include "..\Comm\CLASS_ComPacket.h"
#include "..\Comm\CLASS_TcpClient.h"
//#include "..\Comm\CLASS_SECSGEM.h"
#include "..\Func\CLASS_IOError.h"
#include "..\Hardware\CLASS_TRIGGER.h"
#include "..\Func\SharedMemBase.h"
#include "..\Tools\CLASS_MediaPlayer.h"
#include "..\Tools\Spline\Bezier.h"
#include "..\Tools\Spline\BSpline.h"

//////////////////////////////////////////////////////
//CLASS_SECSGEM secsGem;

CAjinBase* AjinBase;
CAjinIO* AjinIO;
CAjinAIO* AjinAIO;
CAjinCounter* AjinCounter;

CAjinMotor* MTAxis[50];

CAjinMotor* MTStageX;			   // Axis 01	//Stage X
CAjinMotor* MTStageY;			   // Axis 02	//Stage Y
CAjinMotor* MTStageZ;			   // Axis 03	//Stage Z

//////////////////////////////////////////////////////
CCommPacket Rs232Ionizer(_T("COM1"), 9600);	// Ionizer
//CCommPacket CommPacket2(_T("COM2"), 9600);	// Light Controller
SOCKET VisionSocket;

VISION_HEADER VisionHeader;
VISION_TX_DATA VisionTXData;
VISION_RX_DATA VisionRXData;
VISION_RX_DATA V1RxData;
VISION_RX_DATA V2RxData;
VISION_RX_DATA V3RxData;

CTcpClient ClientVision;
CTenKey	 Key10;
CFileLog* pFileLog;
CMediaPlayer MP3;
//CRTT_RUN_CHECK			pgm_check;

TDeviceData		DeviceData;
TRcpVal			RcpVal;
TSystemData		SystemData;
TMachineStatus	MachineStatus;
TUSER_INFO		UserInfo;
TLOT_INFO		LotInfo;
TDeviceInfo     DeviceInfo;
CNVMMF			nvMMF;
_NV_BIT			nvBit;
_NV_COUNT		nvCount;
_NV_FLIP1_MAP	nvFlip1Map;
_NV_FLIP2_MAP	nvFlip2Map;
_NV_PALLET1_MAP nvPallet1Map;
_NV_PALLET2_MAP nvPallet2Map;
_NV_GOODTRAY1_MAP nvGoodTray1Map;
_NV_GOODTRAY2_MAP nvGoodTray2Map;
_NV_REWORKTRAY_MAP nvReworkTrayMap;
_NV_NGTRAY_MAP nvNGTrayMap;

_NV_FLIP1_RESULT nvFlip1VisionResult;
_NV_FLIP2_RESULT nvFlip2VisionResult;
_NV_PALLET1_RESULT nvPallet1VisionResult;
_NV_PALLET2_RESULT nvPallet2VisionResult;
_NV_FRONT_PK_RESULT nvFrontPkVisionResult;
_NV_REAR_PK_RESULT nvRearPkVisionResult;
_NV_GOOD_TRAY1_RESULT nvGoodTray1VisionResult;
_NV_GOOD_TRAY2_RESULT nvGoodTray2VisionResult;
_NV_REWORK_TRAY_RESULT nvReworkTrayVisionResult;
_NV_NG_TRAY_RESULT nvNGTrayVisionResult;

TPkCenterMove PkCenterMove;
TFrontPkCenterOffset FrontPkCenterOffset;
TRearPkCenterOffset RearPkCenterOffset;

LARGE_INTEGER sysfreq;
LARGE_INTEGER st;

Curve* curvePallet;
//////////////////////////////////////////////////////

_ubitbuf ubitbuf;
_bit	 bit;

_udmbuf  udmbuf;
_dm		 dm;

_uinbuf  uinbuf;
_uoutbuf uoutbuf;
_uiobuf	 uiobuf;

char lotstarttime[128];
struct tm* tm_LotStart;
time_t lstarttime;

char lotendtime[128];
struct tm* tm_LotEnd;
time_t lendtime;

WORD spmcount30s;
WORD ManualNumber;
WORD cntbuzzer;
WORD errorcode[100], bferrorcode, tmperrorcode;
WORD errvalue[10];
WORD totalAxisCnt;
WORD stack[200], uphstackno;
WORD unloadingunitcount;
WORD unloadingTrayCount;
WORD tphstack[200], tphstackno;
WORD NoofWfInLdMz;
WORD NoofWfInUlMz;
WORD DeviceSize;
WORD n_TestStep;

bool bTenKeyJog;
bool bMTAxisHomeFinished[50];
bool bAlarmCheck[1000];
bool bVisionTriggerStart[10];

bool bSearchFrontPkPickUpPos;
bool bSearchFrontPkPlacePos;
bool bSearchRearPkPickUpPos;
bool bSearchRearPkPlacePos;

bool bErr_FrontPk_OffsetX_Range[8];
bool bErr_FrontPk_OffsetY_Range[8];
bool bErr_FrontPk_OffsetT_Range[8];

bool bErr_FrontPk_OffsetX_InvalidValue[8];
bool bErr_FrontPk_OffsetY_InvalidValue[8];
bool bErr_FrontPk_OffsetT_InvalidValue[8];

bool bErr_RearPk_OffsetX_Range[8];
bool bErr_RearPk_OffsetY_Range[8];
bool bErr_RearPk_OffsetT_Range[8];

bool bErr_RearPk_OffsetX_InvalidValue[8];
bool bErr_RearPk_OffsetY_InvalidValue[8];
bool bErr_RearPk_OffsetT_InvalidValue[8];

int MachineSpeed;
int tenkeyJogmtno;

unsigned int LampBuzzerType[1000][10];
unsigned int BUZZERONTIME;
unsigned int BUZZEROFFTIME;
unsigned int nPickUpRetryCnt;

char strUserName[64]="NO_USER";
char strFileLog[512];

SOCKET socket_Client;
SOCKET udp_Client;

int nVisionResultUnitCount;

int WorkingIndex;

int FlipY1TrigMap[50][50];
int FlipY2TrigMap[50][50];
int PalletY1TrigMap[50][50];
int PalletY2TrigMap[50][50];

int UnitXCnt;
int UnitYCnt;
int SnapXCnt;
int SnapYCnt;
int TrigXCnt;
int TrigYCnt;

int FlipY1TrigX;
int FlipY1TrigY;
int FlipY1TrigPosIdx;
int PrevFlipY1TrigX;
int PrevFlipY1TrigY;

int FlipY2TrigX;
int FlipY2TrigY;
int FlipY2TrigPosIdx;
int PrevFlipY2TrigX;
int PrevFlipY2TrigY;

int PalletY1TrigX;
int PalletY1TrigY;
int PalletY1TrigPosIdx;
int PrevPalletY1TrigX;
int PrevPalletY1TrigY;

int PalletY2TrigX;
int PalletY2TrigY;
int PalletY2TrigPosIdx;
int PrevPalletY2TrigX;
int PrevPalletY2TrigY;

int TrayPkMap;

int FrontPk_PY1PickStXY;
int FrontPk_PY1PickEdXY;
int RearPk_PY1PickStXY;
int RearPk_PY1PickEdXY;
int FrontPk_PY2PickStXY;
int FrontPk_PY2PickEdXY;
int RearPk_PY2PickStXY;
int RearPk_PY2PickEdXY;
int FrontPk_Good1PlaceStXY;
int FrontPk_Good1PlaceEdXY;
int RearPk_Good1PlaceStXY;
int RearPk_Good1PlaceEdXY;
int FrontPk_Good2PlaceStXY;
int FrontPk_Good2PlaceEdXY;
int RearPk_Good2PlaceStXY;
int RearPk_Good2PlaceEdXY;
int FrontPk_RewPlaceStXY;
int FrontPk_RewPlaceEdXY;
int RearPk_RewPlaceStXY;
int RearPk_RewPlaceEdXY;
int FrontPk_NGPlaceStXY;
int FrontPk_NGPlaceEdXY;
int RearPk_NGPlaceStXY;
int RearPk_NGPlaceEdXY;

int FrontPk_PY1PickUpIDX;
int FrontPk_PY2PickUpIDX;

int FrontPk_PickUpIDX;
int FrontPk_PickUpDir;
int FrontPk_PickUpX;
int FrontPk_PickUpY;
int FrontPk_PickupPkNo;
int FrontPk_PlaceIDX;
int FrontPk_PlaceDir;
int FrontPk_PlaceX;
int FrontPk_PlaceY;
int FrontPk_PlacePkNo;

int RearPk_PickUpIDX;
int RearPk_PickUpDir;
int RearPk_PickUpX;
int RearPk_PickUpY;
int RearPk_PickupPkNo;
int RearPk_PlaceIDX;
int RearPk_PlaceDir;
int RearPk_PlaceX;
int RearPk_PlaceY;
int RearPk_PlacePkNo;

int WorkPallet;
int WorkTray;


int manualx;
int manualy;
int manualpkno;

int manualtrigx;
int manualtrigy;

int Flip1VisionResult[50][50];
int Flip2VisionResult[50][50];
int Pallet1VisionResult[50][50];
int Pallet2VisionResult[50][50];
int FrontPkVisionResult[10];
int RearPkVisionResult[10];
int GoodTray1VisionResult[50][50];
int GoodTray2VisionResult[50][50];
int NGTrayVisionResult[50][50];
int RewTrayVisionResult[50][50];

int Flip1Map[50][50];
int Flip2Map[50][50];
int Pallet1Map[50][50];
int Pallet2Map[50][50];
int GoodTray1Map[50][50];
int GoodTray2Map[50][50];
int RewTrayMap[50][50];
int NGTrayMap[50][50];

int FrontPk_SortResult[10];
int RearPk_SortResult[10];
int SeqLogCnt=0;

int _3PtPkType;
int _3PtTarget;
int _3PtPointNo;

int FrontPkAutoPadAlignIdx;
int FrontPkAutoPadAlignNo;

int RearPkAutoPadAlignIdx;
int RearPkAutoPadAlignNo;

double FlipY1TrigPosX[50][50];
double FlipY1TrigPosY[50][50];
double FlipY2TrigPosX[50][50];
double FlipY2TrigPosY[50][50];
double PalletY1TrigPosX[50][50];
double PalletY1TrigPosY[50][50];
double PalletY2TrigPosX[50][50];
double PalletY2TrigPosY[50][50];

double FrontPkZActPos[10];
double RearPkZActPos[10];
double FrontPkZUp[10];
double RearPkZUp[10];

double FrontPkOffsetX[10];
double FrontPkOffsetY[10];
double FrontPkOffsetT[10];

double RearPkOffsetX[10];
double RearPkOffsetY[10];
double RearPkOffsetT[10];

double pkmovingstart;
double pkmovingend;
double pkmovingtime;

double mtmovingstart;
double mtmovingend;
double mtmovingtime;

double pkVacInOn;
double pkVacInOff;
double pkVacOutOn;
double pkVacOutOff;
double pkVacOntime;
double pkVacOfftime;

double FrontPkAutoPadAlignPosX;
double FrontPkAutoPadAlignPosY;
double FrontPkAutoPadAlignOffsetX[10];
double FrontPkAutoPadAlignOffsetY[10];

double RearPkAutoPadAlignPosX;
double RearPkAutoPadAlignPosY;
double RearPkAutoPadAlignOffsetX[10];
double RearPkAutoPadAlignOffsetY[10];

//////////////////////////////////////////////////////



#pragma region GENERAL_TIMER
CRtTimer tm_gScanDelay;
CRtTimer tm_gManualNumberOff;
CRtTimer tm_gSystemOn;
CRtTimer tm_gUPH;
CRtTimer tm_gTPH;
CRtTimer tm_gSPM30s;
CRtTimer tm_gStartBlink;
CRtTimer tm_gStopBlink;
CRtTimer tm_gResetBlink;
CRtTimer tm_gBuzzer1Blink;
CRtTimer tm_gBuzzer2Blink;
CRtTimer tm_gBuzzer3Blink;
CRtTimer tm_gBuzzer4Blink;

CRtTimer tm_gEmergencyOn;
CRtTimer tm_gEmergencyOff;

CRtTimer tm_gPautostop;
CRtTimer tm_gAllCycleStop;
CRtTimer tm_gAllMotionDone;
CRtTimer tm_TrayOutToOut;

CRtTimer tm_VisionComplete_Wait;
CRtTimer tm_gCartReadyBlink;

#pragma endregion

#pragma region MOTOR_TIMER
CRtTimer tmReady_MTAxis[50];

CRtTimer tmReady_MTStageX;
CRtTimer tmMoving_MTStageX;

CRtTimer tmReady_MTStageY;
CRtTimer tmMoving_MTStageY;

CRtTimer tmReady_MTStageZ;
CRtTimer tmMoving_MTStageZ;

#pragma endregion

#pragma region INPUT_TIMER
// CH 01
CRtTimer tm_iKeyStart_On;
CRtTimer tm_iKeyStart_Off;

CRtTimer tm_iKeyStop_On;
CRtTimer tm_iKeyStop_Off;

CRtTimer tm_iKeyReset_On;
CRtTimer tm_iKeyReset_Off;

// CH 02

#pragma endregion

#pragma region OUTPUT_TIMER
// CH 01
CRtTimer tm_oKeyStart_On;
CRtTimer tm_oKeyStart_Off;

CRtTimer tm_oKeyStop_On;
CRtTimer tm_oKeyStop_Off;

CRtTimer tm_oKeyReset_On;
CRtTimer tm_oKeyReset_Off;

CRtTimer tm_oTowerLampRed_On;
CRtTimer tm_oTowerLampRed_Off;

CRtTimer tm_oTowerLampYellow_On;
CRtTimer tm_oTowerLampYellow_Off;

CRtTimer tm_oTowerLampGreen_On;
CRtTimer tm_oTowerLampGreen_Off;

CRtTimer tm_oBuzzer1_On;
CRtTimer tm_oBuzzer1_Off;

#pragma endregion

#pragma region PNEMATIC
//CIOError ioErrSawPkAirKnifeUpDn(ERROR_SAW_PICKER_AIR_KNIFE_UP_DN, 5000);
//CIOError ioErrPallet1UpDn(ERROR_PALLET1_UP_DN, 5000);
//CIOError ioErrPallet2UpDn(ERROR_PALLET2_UP_DN, 5000);
//CIOError ioErrTrayPkLeftClampOpenClose(ERROR_TRAY_PK_LEFT_CLAMP_OPEN_CLOSE, 5000);
//CIOError ioErrTrayPkRightClampOpenClose(ERROR_TRAY_PK_RIGHT_CLAMP_OPEN_CLOSE, 5000);
//CIOError ioErrGoodElev1LockUnlock(ERROR_GOOD_ELEV1_DOOR_LOCK_UNLOCK, 3000);
//CIOError ioErrGoodElev2LockUnlock(ERROR_GOOD_ELEV2_DOOR_LOCK_UNLOCK, 3000);
//CIOError ioErrNGElevLockUnlock(ERROR_NG_ELEV_DOOR_LOCK_UNLOCK, 3000);
//CIOError ioErrRewElevLockUnlock(ERROR_REWORK_ELEV_DOOR_LOCK_UNLOCK, 3000);
//
//CIOError ioErrEmptyTrayPkLeftClampOpenClose(ERROR_EMPTY_TRAY_PK_LEFT_CLAMP_OPEN_CLOSE, 5000);
//CIOError ioErrEmptyTrayPkRightClampOpenClose(ERROR_EMPTY_TRAY_PK_RIGHT_CLAMP_OPEN_CLOSE, 5000);
//CIOError ioErrEmptyElev1LockUnlock(ERROR_EMPTY_ELEV1_DOOR_LOCK_UNLOCK, 3000);
//CIOError ioErrEmptyElev2LockUnlock(ERROR_EMPTY_ELEV2_DOOR_LOCK_UNLOCK, 3000);
//CIOError ioErrEmptyElev3LockUnlock(ERROR_EMPTY_ELEV3_DOOR_LOCK_UNLOCK, 3000);

#pragma endregion

#pragma region ONE_PULSE
COnePulse optmStartBtnResetOnTmOver;
COnePulse optmStartBtnStartOnTmOver;
COnePulse optmStopBtnOnTmOver;
COnePulse optmDoorOpenBtnOnTmOver;
#pragma endregion
#endif