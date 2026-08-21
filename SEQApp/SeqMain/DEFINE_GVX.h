#ifndef _GVX_H_
#define _GVX_H_

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
//extern CLASS_SECSGEM secsGem;

extern CAjinBase* AjinBase;
extern CAjinIO* AjinIO;
extern CAjinAIO* AjinAIO;
extern CAjinCounter* AjinCounter;
extern CAjinTrigger* AjinTrigger;

extern CAjinMotor* MTAxis[50];

extern CAjinMotor* MTStageX;			// Axis 01	// MTStageX,	STEP
extern CAjinMotor* MTStageY;			// Axis 02	// MTStageY,	STEP
extern CAjinMotor* MTStageZ;			// Axis 03	// MTStageZ,	STEP

//////////////////////////////////////////////////////
extern CCommPacket Rs232Ionizer;	// Barcode Reader
//extern CCommPacket CommPacket2;	// Light Controller

extern SOCKET VisionSocket;

extern VISION_HEADER VisionHeader;
extern VISION_TX_DATA VisionTXData;
extern VISION_RX_DATA VisionRXData;
extern VISION_RX_DATA V1RxData;
extern VISION_RX_DATA V2RxData;
extern VISION_RX_DATA V3RxData;

extern CTcpClient ClientVision;
extern CTenKey	 Key10;
extern CFileLog* pFileLog;
extern CMediaPlayer MP3;
//extern CRTT_RUN_CHECK			pgm_check;

extern TDeviceData		DeviceData;
extern TRcpVal			RcpVal;
extern TSystemData		SystemData;
extern TMachineStatus	MachineStatus;
extern TUSER_INFO		UserInfo;
extern TLOT_INFO		LotInfo;
extern TDeviceInfo		DeviceInfo;
extern CNVMMF			nvMMF;
extern _NV_BIT			nvBit;
extern _NV_COUNT		nvCount;
extern _NV_FLIP1_MAP	nvFlip1Map;
extern _NV_FLIP2_MAP	nvFlip2Map;
extern _NV_PALLET1_MAP nvPallet1Map;
extern _NV_PALLET2_MAP nvPallet2Map;
extern _NV_GOODTRAY1_MAP nvGoodTray1Map;
extern _NV_GOODTRAY2_MAP nvGoodTray2Map;
extern _NV_REWORKTRAY_MAP nvReworkTrayMap;
extern _NV_NGTRAY_MAP nvNGTrayMap;

extern _NV_FLIP1_RESULT nvFlip1VisionResult;
extern _NV_FLIP2_RESULT nvFlip2VisionResult;
extern _NV_PALLET1_RESULT nvPallet1VisionResult;
extern _NV_PALLET2_RESULT nvPallet2VisionResult;
extern _NV_FRONT_PK_RESULT nvFrontPkVisionResult;
extern _NV_REAR_PK_RESULT nvRearPkVisionResult;
extern _NV_GOOD_TRAY1_RESULT nvGoodTray1VisionResult;
extern _NV_GOOD_TRAY2_RESULT nvGoodTray2VisionResult;
extern _NV_REWORK_TRAY_RESULT nvReworkTrayVisionResult;
extern _NV_NG_TRAY_RESULT nvNGTrayVisionResult;

extern TPkCenterMove PkCenterMove;
extern TFrontPkCenterOffset FrontPkCenterOffset;
extern TRearPkCenterOffset RearPkCenterOffset;

extern LARGE_INTEGER sysfreq;
extern LARGE_INTEGER st;

extern Curve* curvePallet;
//////////////////////////////////////////////////////

extern _ubitbuf ubitbuf;
extern _bit	 bit;

extern _udmbuf  udmbuf;
extern _dm		 dm;

extern _uinbuf  uinbuf;
extern _uoutbuf uoutbuf;
extern _uiobuf	 uiobuf;

extern char lotstarttime[128];
extern struct tm* tm_LotStart;
extern time_t lstarttime;

extern char lotendtime[128];
extern struct tm* tm_LotEnd;
extern time_t lendtime;

extern WORD spmcount30s;
extern WORD ManualNumber;
extern WORD errorcode[100], bferrorcode, tmperrorcode;
extern WORD errvalue[10];
extern WORD cntbuzzer;
extern WORD totalAxisCnt;
extern WORD stack[200], uphstackno;
extern WORD unloadingunitcount;
extern WORD unloadingTrayCount;
extern WORD tphstack[200], tphstackno;
extern WORD NoofWfInLdMz;
extern WORD NoofWfInUlMz;
extern WORD DeviceSize;
extern WORD n_TestStep;

extern bool bTenKeyJog;
extern bool bMTAxisHomeFinished[50];
extern bool bAlarmCheck[1000];
extern bool bVisionTriggerStart[10];

extern bool bRearPk1SKIP;
extern bool bRearPk2SKIP;
extern bool bRearPk3SKIP;
extern bool bRearPk4SKIP;
extern bool bRearPk5SKIP;
extern bool bRearPk6SKIP;
extern bool bRearPk7SKIP;
extern bool bRearPk8SKIP;

extern bool bSearchFrontPkPickUpPos;
extern bool bSearchFrontPkPlacePos;
extern bool bSearchRearPkPickUpPos;
extern bool bSearchRearPkPlacePos;

extern bool bErr_FrontPk_OffsetX_Range[8];
extern bool bErr_FrontPk_OffsetY_Range[8];
extern bool bErr_FrontPk_OffsetT_Range[8];

extern bool bErr_FrontPk_OffsetX_InvalidValue[8];
extern bool bErr_FrontPk_OffsetY_InvalidValue[8];
extern bool bErr_FrontPk_OffsetT_InvalidValue[8];

extern bool bErr_RearPk_OffsetX_Range[8];
extern bool bErr_RearPk_OffsetY_Range[8];
extern bool bErr_RearPk_OffsetT_Range[8];

extern bool bErr_RearPk_OffsetX_InvalidValue[8];
extern bool bErr_RearPk_OffsetY_InvalidValue[8];
extern bool bErr_RearPk_OffsetT_InvalidValue[8];

extern int MachineSpeed;
extern int tenkeyJogmtno;

extern unsigned int LampBuzzerType[1000][10];
extern unsigned int BUZZERONTIME;
extern unsigned int BUZZEROFFTIME;
extern unsigned int nPickUpRetryCnt;

extern char strUserName[64];
extern char strFileLog[512];

extern SOCKET socket_Client;
extern SOCKET udp_Client;

extern int nVisionResultUnitCount;

extern int WorkingIndex;

extern int FlipY1TrigMap[50][50];
extern int FlipY2TrigMap[50][50];
extern int PalletY1TrigMap[50][50];
extern int PalletY2TrigMap[50][50];

extern int UnitXCnt;
extern int UnitYCnt;
extern int SnapXCnt;
extern int SnapYCnt;
extern int TrigXCnt;
extern int TrigYCnt;

extern int FlipY1TrigX;
extern int FlipY1TrigY;
extern int FlipY1TrigPosIdx;
extern int PrevFlipY1TrigX;
extern int PrevFlipY1TrigY;

extern int FlipY2TrigX;
extern int FlipY2TrigY;
extern int FlipY2TrigPosIdx;
extern int PrevFlipY2TrigX;
extern int PrevFlipY2TrigY;

extern int PalletY1TrigX;
extern int PalletY1TrigY;
extern int PalletY1TrigPosIdx;
extern int PrevPalletY1TrigX;
extern int PrevPalletY1TrigY;

extern int PalletY2TrigX;
extern int PalletY2TrigY;
extern int PalletY2TrigPosIdx;
extern int PrevPalletY2TrigX;
extern int PrevPalletY2TrigY;

extern int TrayPkMap;

extern int FrontPk_PY1PickStXY;
extern int FrontPk_PY1PickEdXY;
extern int RearPk_PY1PickStXY;
extern int RearPk_PY1PickEdXY;
extern int FrontPk_PY2PickStXY;
extern int FrontPk_PY2PickEdXY;
extern int RearPk_PY2PickStXY;
extern int RearPk_PY2PickEdXY;
extern int FrontPk_Good1PlaceStXY;
extern int FrontPk_Good1PlaceEdXY;
extern int RearPk_Good1PlaceStXY;
extern int RearPk_Good1PlaceEdXY;
extern int FrontPk_Good2PlaceStXY;
extern int FrontPk_Good2PlaceEdXY;
extern int RearPk_Good2PlaceStXY;
extern int RearPk_Good2PlaceEdXY;
extern int FrontPk_RewPlaceStXY;
extern int FrontPk_RewPlaceEdXY;
extern int RearPk_RewPlaceStXY;
extern int RearPk_RewPlaceEdXY;
extern int FrontPk_NGPlaceStXY;
extern int FrontPk_NGPlaceEdXY;
extern int RearPk_NGPlaceStXY;
extern int RearPk_NGPlaceEdXY;

extern int FrontPk_PY1PickUpIDX;
extern int FrontPk_PY2PickUpIDX;

extern int FrontPk_PickUpIDX;
extern int FrontPk_PickUpDir;
extern int FrontPk_PickUpX;
extern int FrontPk_PickUpY;
extern int FrontPk_PickupPkNo;
extern int FrontPk_PlaceIDX;
extern int FrontPk_PlaceDir;
extern int FrontPk_PlaceX;
extern int FrontPk_PlaceY;
extern int FrontPk_PlacePkNo;

extern int RearPk_PickUpIDX;
extern int RearPk_PickUpDir;
extern int RearPk_PickUpX;
extern int RearPk_PickUpY;
extern int RearPk_PickupPkNo;
extern int RearPk_PlaceIDX;
extern int RearPk_PlaceDir;
extern int RearPk_PlaceX;
extern int RearPk_PlaceY;
extern int RearPk_PlacePkNo;

extern int WorkPallet;
extern int WorkTray;

extern int manualx;
extern int manualy;
extern int manualpkno;

extern int manualtrigx;
extern int manualtrigy;

extern int Flip1VisionResult[50][50];
extern int Flip2VisionResult[50][50];
extern int Pallet1VisionResult[50][50];
extern int Pallet2VisionResult[50][50];
extern int FrontPkVisionResult[10];
extern int RearPkVisionResult[10];
extern int GoodTray1VisionResult[50][50];
extern int GoodTray2VisionResult[50][50];
extern int NGTrayVisionResult[50][50];
extern int RewTrayVisionResult[50][50];

extern int Flip1Map[50][50];
extern int Flip2Map[50][50];
extern int Pallet1Map[50][50];
extern int Pallet2Map[50][50];
extern int GoodTray1Map[50][50];
extern int GoodTray2Map[50][50];
extern int RewTrayMap[50][50];
extern int NGTrayMap[50][50];

extern int FrontPk_SortResult[10];
extern int RearPk_SortResult[10];
extern int SeqLogCnt;

extern int _3PtPkType;
extern int _3PtTarget;
extern int _3PtPointNo;

extern int FrontPkAutoPadAlignIdx;
extern int FrontPkAutoPadAlignNo;

extern int RearPkAutoPadAlignIdx;
extern int RearPkAutoPadAlignNo;

extern double FlipY1TrigPosX[50][50];
extern double FlipY1TrigPosY[50][50];
extern double FlipY2TrigPosX[50][50];
extern double FlipY2TrigPosY[50][50];
extern double PalletY1TrigPosX[50][50];
extern double PalletY1TrigPosY[50][50];
extern double PalletY2TrigPosX[50][50];
extern double PalletY2TrigPosY[50][50];

extern double FrontPkZActPos[10];
extern double RearPkZActPos[10];
extern double FrontPkZUp[10];
extern double RearPkZUp[10];

extern double FrontPkOffsetX[10];
extern double FrontPkOffsetY[10];
extern double FrontPkOffsetT[10];

extern double RearPkOffsetX[10];
extern double RearPkOffsetY[10];
extern double RearPkOffsetT[10];

extern double pkmovingstart;
extern double pkmovingend;
extern double pkmovingtime;

extern double mtmovingstart;
extern double mtmovingend;
extern double mtmovingtime;

extern double pkVacInOn;
extern double pkVacInOff;
extern double pkVacOutOn;
extern double pkVacOutOff;
extern double pkVacOntime;
extern double pkVacOfftime;

extern double FrontPkAutoPadAlignPosX;
extern double FrontPkAutoPadAlignPosY;
extern double FrontPkAutoPadAlignOffsetX[10];
extern double FrontPkAutoPadAlignOffsetY[10];

extern double RearPkAutoPadAlignPosX;
extern double RearPkAutoPadAlignPosY;
extern double RearPkAutoPadAlignOffsetX[10];
extern double RearPkAutoPadAlignOffsetY[10];

//////////////////////////////////////////////////////



#pragma region GENERAL_TIMER
extern CRtTimer tm_gScanDelay;
extern CRtTimer tm_gManualNumberOff;
extern CRtTimer tm_gSystemOn;
extern CRtTimer tm_gUPH;
extern CRtTimer tm_gTPH;
extern CRtTimer tm_gSPM30s;
extern CRtTimer tm_gStartBlink;
extern CRtTimer tm_gStopBlink;
extern CRtTimer tm_gResetBlink;
extern CRtTimer tm_gBuzzer1Blink;
extern CRtTimer tm_gBuzzer2Blink;
extern CRtTimer tm_gBuzzer3Blink;
extern CRtTimer tm_gBuzzer4Blink;

extern CRtTimer tm_gEmergencyOn;
extern CRtTimer tm_gEmergencyOff;

extern CRtTimer tm_gPautostop;
extern CRtTimer tm_gAllCycleStop;
extern CRtTimer tm_gAllMotionDone;
extern CRtTimer tm_TrayOutToOut;
extern CRtTimer tm_VisionComplete_Wait;
extern CRtTimer tm_gCartReadyBlink;

#pragma endregion

#pragma region MOTOR_TIMER
extern CRtTimer tmReady_MTAxis[50];

extern CRtTimer tmReady_MTStageX;
extern CRtTimer tmMoving_MTStageX;

extern CRtTimer tmReady_MTStageY;
extern CRtTimer tmMoving_MTStageY;

extern CRtTimer tmReady_MTStageZ;
extern CRtTimer tmMoving_MTStageZ;
#pragma endregion

#pragma region INPUT_TIMER
// CH 01
extern CRtTimer tm_iKeyStart_On;
extern CRtTimer tm_iKeyStart_Off;

extern CRtTimer tm_iKeyStop_On;
extern CRtTimer tm_iKeyStop_Off;

extern CRtTimer tm_iKeyReset_On;
extern CRtTimer tm_iKeyReset_Off;

// CH 02

#pragma endregion

#pragma region OUTPUT_TIMER
// CH 01
extern CRtTimer tm_oKeyStart_On;
extern CRtTimer tm_oKeyStart_Off;

extern CRtTimer tm_oKeyStop_On;
extern CRtTimer tm_oKeyStop_Off;

extern CRtTimer tm_oKeyReset_On;
extern CRtTimer tm_oKeyReset_Off;

extern CRtTimer tm_oTowerLampRed_On;
extern CRtTimer tm_oTowerLampRed_Off;

extern CRtTimer tm_oTowerLampYellow_On;
extern CRtTimer tm_oTowerLampYellow_Off;

extern CRtTimer tm_oTowerLampGreen_On;
extern CRtTimer tm_oTowerLampGreen_Off;

extern CRtTimer tm_oBuzzer1_On;
extern CRtTimer tm_oBuzzer1_Off;


// CH 02

#pragma endregion

#pragma region PNEMATIC
//extern CIOError ioErrSawPkAirKnifeUpDn;
//extern CIOError ioErrPallet1UpDn;
//extern CIOError ioErrPallet2UpDn;
//extern CIOError ioErrTrayPkLeftClampOpenClose;
//extern CIOError ioErrTrayPkRightClampOpenClose;
//extern CIOError ioErrGoodElev1LockUnlock;
//extern CIOError ioErrGoodElev2LockUnlock;
//extern CIOError ioErrNGElevLockUnlock;
//extern CIOError ioErrRewElevLockUnlock;
//
//extern CIOError ioErrEmptyTrayPkLeftClampOpenClose;
//extern CIOError ioErrEmptyTrayPkRightClampOpenClose;
//extern CIOError ioErrEmptyElev1LockUnlock;
//extern CIOError ioErrEmptyElev2LockUnlock;
//extern CIOError ioErrEmptyElev3LockUnlock;
#pragma endregion

#pragma region ONE_PULSE
extern COnePulse optmStartBtnResetOnTmOver;
extern COnePulse optmStartBtnStartOnTmOver;
extern COnePulse optmStopBtnOnTmOver;
extern COnePulse optmDoorOpenBtnOnTmOver;
#pragma endregion
#endif