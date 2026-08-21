#ifndef SEQ_CLASS_MAIN_H
#define SEQ_CLASS_MAIN_H

#pragma once
#include <memory>
#include "DEFINE_GVX.h"
#include "Define\DEFINE_WinMsg.h"


using namespace std;

class CSeqMain
{
private:
	static shared_ptr<CSeqMain>   m_pInstance;

public:
	CSeqMain();
	~CSeqMain();

	bool m_bSeqExit;
	bool m_bClientConnect;
	bool m_bUDPClientConnect;

	static CSeqMain* GetInstance();
	

	//////////////////////////////////////////////////////////////////////////
	// ENV_CalVelocity.cpp
	void Make_Parameter1(CAjinMotor* Axis);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_Console.cpp
	void InitConsole(void);
	void ShowConsoleWindow(void);
	void HideConsoleWindow(void);
	void SetConsoleRGB(int color);
	void SetConsoleSize(SHORT width, SHORT height);

	//////////////////////////////////////////////////////////////////////////
	// ENV_LampBuzzer.cpp
	void TowerLamp_CycleC(void);
	void Buzzer_CycleC(void);

	//////////////////////////////////////////////////////////////////////////
	// ENV_AjinMotorProcess.cpp
	void AjinHomeFunction(CAjinMotor* Axis);
	void AjinMotorC(CAjinMotor* Axis);
	void AjinMotorStatus(int startaxis, int endaxis);
	void Motor_Pause(CAjinMotor* Axis, int Stop);
	void Motor_Adjust(CAjinMotor* Axis);
	void Motor_Tunning(CAjinMotor* Axis);

	//////////////////////////////////////////////////////////////////////////
	// ENV_Seq.cpp
	void Sequence(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_ComCycle.cpp
	void CommonCycle(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_ComTimer.cpp
	void CommonTimer(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_EmerOff.cpp
	void EmerOffProcess(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_Error.cpp
	void ERRIF0(int ec);
	void ERRCLRIF0(int ec);
	int ErrorProcedure(void);
	void AllCycleStop(void);
	void MTBA_MTBF(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_Init.cpp
	void Load_Motor_Parameter(void);
	void InitMotor(void);
	void InitIO(void);
	void InitMotorBase(void);
	
	void InitMemory(void);
	void InitSequence(void);
	void ObjectDelete(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_LotEnd.cpp
	void LotEndCheck(void);
	void LotEndProcess_Cycle(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_MMI_MSG.cpp
	void InitComm(void);
	void MMI_MessageCommunication(void);
	void MMI_MessageMotorCommand(unsigned int cmdNo, int mtNo);
	void MMI_MessageMotorCmdHomeFunc(unsigned int cmdNo, int mtNo);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_ReadWrite.cpp
	void Read_All(void);
	void Write_All(void);
	void OffAllOutput(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_Reset.cpp
	void DRVRESETIFDRVERR(void);
	void KeyReset(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_Safety.cpp
	void MotorSafetyFunction(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_StartStop.cpp
	void AutoStart(void);
	void AutoStop(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_TenkeyOperation.cpp
	void ManualTenkeyOperation(void);
	void TenKeyJogMove(int dir);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_TenKeyProcess.cpp
	void OutManualNumber(WORD num);
	void KeySetProcess(void);
	void TenKeyProcess(void);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_TimerHandler.cpp
	//static void CALLBACK TimerHandler(UINT _timerid, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void CALLBACK TimerHandler(UINT _timerid, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

	//////////////////////////////////////////////////////////////////////////
	// FUNC_Util.cpp
	void Wait(int tm_delay);
	void SetMZSlotAllExist(WORD WhichMZ);
	void SetMZSlotAllEmpty(WORD WhichMZ);
	int FindFirstMZSlotExist(WORD WhichMZ);
	int FindFirstMZSlotEmpty(WORD WhichMZ);
	void SetMZSlotExist(WORD WhichMZ, WORD pos);
	void SetMZSlotEmpty(WORD WhichMZ, WORD pos);
	void InitMZ(WORD WhichMZ);

	bool ISBITON(int data, int BitNo);
	void BITONOFF(int* data, int BitNo, bool ONOFF);
	int BITCHANGE(int data, int BitNo);
	unsigned getbits(unsigned x, int p, int n);
	void max_min(double* d_arr, int n_size, double& max, double& min);
	bool SendCopyDataToMMI(WORD msg, WORD size, LPVOID ptrData);
	bool SendSeqRspToMMI(WORD msg, WORD size, SEQ_RSP seq_rsp);
	void SendPostMessage(WORD msgNo, WORD target);
	bool LevelUp_Privileges();
	void FlipArray(int Row, int Col, int A[50][50], int dir);
	void RotateArray(int Row, int Col, int A[100][100], int dir);
	
	//////////////////////////////////////////////////////////////////////////
#pragma region SEQ00_GVFunc.cpp
	void GetNVMMF(void);
	void SetNVMMF(void);
	void SetAllMap(int Target[50][50], int MapState);
	/*void SetAllVisionResult(int Target[50][50], int MapState);
	void SetVisionResult(int Target[50][50], int x, int y, int Result);
	void CopyVisionResult(int dest[50][50], int source[50][50]);
	void ClearVisionResult(int dest[50][50]);
	void CopyPkVisionResult(int Target[10], int pkno, int Result);
	void SetPkVisionResult(int Target[10], int pkno, int Result);
	void ClearPkVisionResult(int Target[10], int pkno);

	void SetAllTriggerMap(int Target[50][50], int MapState);
	bool GetTriggerPosIDX(int Target[50][50], int& xpos, int& ypos);

	void SetTriggerPosIDX(int Target[50][50], int x, int y, int MapState);
	void CalcTriggerPos(int Target);

	int GetPickUpDirection(int Target[50][50], int MapDir);
	int GetPlaceDirection(int Target[50][50], int MapDir);

	bool GetPickUpPosIDX(int Target[50][50], int MapDir, int ZigZag, int* xpos, int* ypos);
	void SetPickUpPosIDX(int Target[50][50], int xpos, int ypos, int state);
	
	bool GetPlacePosIDX(int Target, int MapDir, int ZigZag, int* xpos, int* ypos);
	void SetPlacePosIDX(int Target[50][50], int xpos, int ypos, int state);*/

	void SetDeviceData(void);
#pragma endregion 

	//////////////////////////////////////////////////////////////////////////
#pragma region	SEQ00_AutoRun.cpp
	void AutoRun(void);
#pragma endregion 

//#pragma region	SEQ00_PreStartInit.cpp
//	void PreStartInitC(void);
//#pragma endregion 

	//////////////////////////////////////////////////////////////////////////
#pragma region	SEQ01_MTAxis.cpp
	bool bJogCondition(int axisno);
	bool bJogIndexCondition(int axisno);

	void JogMoveContinious(int apsMtNo, int speed, int dir);
	void JogMoveRelative(int apsMtNo, int pos, int JogVel);
	void JogMoveIndex(int apsMtNo, int idx);

	#pragma region AXIS 01 MTStageX
	void MTStageXHomeM(void);
	void MTStageXMoveM(void);
	#pragma endregion
#pragma region AXIS 02 MTStageY
	void MTStageYHomeM(void);
	void MTStageYMoveM(void);
#pragma endregion
#pragma region AXIS 03 MTStageZ
	void MTStageZHomeM(void);
	void MTStageZMoveM(void);
#pragma endregion

	//////////////////////////////////////////////////////////////////////////
//#pragma region	SEQ_02Pneumatic.cpp
//	#pragma region SAW_PICKER_AIR_KNIFE_UP_DOWN
//	void SawPkAirKnifeUpDnC();
//	bool bIsSawPkAirKnifeUp(int nTime);
//	bool bIsSawPkAirKnifeDn(int nTime);
//	bool bIsSawPkAirKnifeUpDnOUTOFF(int n_Time);
//	void SawPkAirKnifeUp(void);
//	void SawPkAirKnifeDn(void);
//	void SawPkAirKnifeUpDnM(void);
//	#pragma endregion
//
//	#pragma region PALLET1_UP_DOWN
//	void Pallet1UpDnC();
//	bool bIsPallet1Up(int nTime);
//	bool bIsPallet1Dn(int nTime);
//	bool bIsPallet1UpDnOUTOFF(int n_Time);
//	void Pallet1Up(void);
//	void Pallet1Dn(void);
//	void Pallet1UpDnM(void);
//	#pragma endregion
//
//	#pragma region PALLET2_UP_DOWN
//	void Pallet2UpDnC();
//	bool bIsPallet2Up(int nTime);
//	bool bIsPallet2Dn(int nTime);
//	bool bIsPallet2UpDnOUTOFF(int n_Time);
//	void Pallet2Up(void);
//	void Pallet2Dn(void);
//	void Pallet2UpDnM(void);
//	#pragma endregion
//
//	#pragma region TRAY_PICKER_LEFT_CLAMP_OPEN_CLOSE
//	void TrayPkLeftClampOpenCloseC();
//	bool bIsTrayPkLeftClampClose(int nTime);
//	bool bIsTrayPkLeftClampOpen(int nTime);
//	bool bIsTrayPkLeftClampOUTOFF(int n_Time);
//	void TrayPkLeftClampClose(void);
//	void TrayPkLeftClampOpen(void);
//	void TrayPkLeftClampOpenCloseM(void);
//	#pragma endregion
//
//	#pragma region TRAY_PICKER_RIGHT_CLAMP_OPEN_CLOSE
//	void TrayPkRightClampOpenCloseC();
//	bool bIsTrayPkRightClampClose(int nTime);
//	bool bIsTrayPkRightClampOpen(int nTime );
//	bool bIsTrayPkRightClampOUTOFF(int n_Time);
//	void TrayPkRightClampClose(void);
//	void TrayPkRightClampOpen(void);
//	void TrayPkRightClampOpenCloseM(void);
//	#pragma endregion
//
//	#pragma region TRAY_PICKER_CLAMP_OPEN_CLOSE
//	bool bIsTrayPkClampClose(int nTime);
//	bool bIsTrayPkClampOpen(int nTime);
//	bool bIsTrayPkClampOUTOFF(int nTime);
//	void TrayPkClampClose(void);
//	void TrayPkClampOpen(void);
//	void TrayPkClampOpenCloseM(void);
//	#pragma endregion
//
//	#pragma region GOOD_TRAY_ELEV1_DOOR_LOCK_UNLOCK
//	bool bIsGoodElev1Lock(int nTime);
//	bool bIsGoodElev1Unlock(int nTime);
//	void GoodElev1Lock(void);
//	void GoodElev1UnLock(void);
//	void GoodElev1LockUnlockM(void);
//	#pragma endregion
//
//	#pragma region GOOD_TRAY_ELEV2_DOOR_LOCK_UNLOCK
//	bool bIsGoodElev2Lock(int nTime);
//	bool bIsGoodElev2Unlock(int nTime);
//	void GoodElev2Lock(void);
//	void GoodElev2UnLock(void);
//	void GoodElev2LockUnlockM(void);
//	#pragma endregion
//
//	#pragma region REWORK_TRAY_ELEV_DOOR_LOCK_UNLOCK
//	bool bIsRewElevLock(int nTime);
//	bool bIsRewElevUnlock(int nTime);
//	void RewElevLock(void);
//	void RewElevUnLock(void);
//	void RewElevLockUnlockM(void);
//	#pragma endregion
//
//	#pragma region NG_TRAY_ELEV_DOOR_LOCK_UNLOCK
//	bool bIsNGElevLock(int nTime);
//	bool bIsNGElevUnlock(int nTime);
//	void NGElevLock(void);
//	void NGElevUnLock(void);
//	void NGElevLockUnlockM(void);
//	#pragma endregion
//
//	#pragma region GOOD_TRAY_Y1_CLAMP
//	bool bIsGoodTrayY1GrabClampOn(int nTime);
//	bool bIsGoodTrayY1GrabClampOff(int nTime);
//	void GoodTrayY1GrabClampOn();
//	void GoodTrayY1GrabClampOff();
//	void GoodTrayY1GrabClampOnOffM();
//
//	bool bIsGoodTrayY1RightClampOn(int nTime);
//	bool bIsGoodTrayY1RightClampOff(int nTime);
//	void GoodTrayY1RightClampOn();
//	void GoodTrayY1RightClampOff();
//	void GoodTrayY1RightClampOnOffM();
//
//	bool bIsGoodTrayY1RearClampOn(int nTime);
//	bool bIsGoodTrayY1RearClampOff(int nTime);
//	void GoodTrayY1RearClampOn();
//	void GoodTrayY1RearClampOff();
//	void GoodTrayY1RearClampOnOffM();
//
//	bool bIsGoodTrayY1AllClampOff(int nTime);
//	void GoodTrayY1AllClampOff(void);
//	#pragma endregion
//
//	#pragma region GOOD_TRAY_Y2_CLAMP
//	bool bIsGoodTrayY2GrabClampOn(int nTime);
//	bool bIsGoodTrayY2GrabClampOff(int nTime);
//	void GoodTrayY2GrabClampOn();
//	void GoodTrayY2GrabClampOff();
//	void GoodTrayY2GrabClampOnOffM();
//	
//	bool bIsGoodTrayY2RightClampOn(int nTime);
//	bool bIsGoodTrayY2RightClampOff(int nTime);
//	void GoodTrayY2RightClampOn();
//	void GoodTrayY2RightClampOff();
//	void GoodTrayY2RightClampOnOffM();
//	
//	bool bIsGoodTrayY2RearClampOn(int nTime);
//	bool bIsGoodTrayY2RearClampOff(int nTime);
//	void GoodTrayY2RearClampOn();
//	void GoodTrayY2RearClampOff();
//	void GoodTrayY2RearClampOnOffM();
//	bool bIsGoodTrayY2AllClampOff(int nTime);
//	void GoodTrayY2AllClampOff(void);
//	#pragma endregion
//
//	#pragma region NG_TRAY_Y_CLAMP
//	bool bIsNGTrayYGrabClampOn(int nTime);
//	bool bIsNGTrayYGrabClampOff(int nTime);
//	void NGTrayYGrabClampOn();
//	void NGTrayYGrabClampOff();
//	void NGTrayYGrabClampOnOffM();
//		 
//	bool bIsNGTrayYRightClampOn(int nTime);
//	bool bIsNGTrayYRightClampOff(int nTime);
//	void NGTrayYRightClampOn();
//	void NGTrayYRightClampOff();
//	void NGTrayYRightClampOnOffM();
//		 
//	bool bIsNGTrayYRearClampOn(int nTime);
//	bool bIsNGTrayYRearClampOff(int nTime);
//	void NGTrayYRearClampOn();
//	void NGTrayYRearClampOff();
//	void NGTrayYRearClampOnOffM();
//	bool bIsNGTrayYAllClampOff(int);
//	void NGTrayYAllClampOff(void);
//	#pragma endregion
//
//	#pragma region Rework_TRAY_Y_CLAMP
//	bool bIsRewTrayYGrabClampOn(int nTime);
//	bool bIsRewTrayYGrabClampOff(int nTime);
//	void RewTrayYGrabClampOn();
//	void RewTrayYGrabClampOff();
//	void RewTrayYGrabClampOnOffM();
//
//	bool bIsRewTrayYRightClampOn(int nTime);
//	bool bIsRewTrayYRightClampOff(int nTime);
//	void RewTrayYRightClampOn();
//	void RewTrayYRightClampOff();
//	void RewTrayYRightClampOnOffM();
//
//	bool bIsRewTrayYRearClampOn(int nTime);
//	bool bIsRewTrayYRearClampOff(int nTime);
//	void RewTrayYRearClampOn();
//	void RewTrayYRearClampOff();
//	void RewTrayYRearClampOnOffM();
//	bool bIsRewTrayYAllClampOff(int nTime);
//	void RewTrayYAllClampOff(void);
//	#pragma endregion
//
//	#pragma region EMPTY_PICKER_LEFT_CLAMP_OPEN_CLOSE
//	void EmptyPkLeftClampOpenCloseC();
//	bool bIsEmptyPkLeftClampClose(int nTime);
//	bool bIsEmptyPkLeftClampOpen(int nTime);
//	bool bIsEmptyPkLeftClampOUTOFF(int n_Time);
//	void EmptyPkLeftClampClose(void);
//	void EmptyPkLeftClampOpen(void);
//	void EmptyPkLeftClampOpenCloseM(void);
//	#pragma endregion
//
//	#pragma region EMPTY_PICKER_RIGHT_CLAMP_OPEN_CLOSE
//	void EmptyPkRightClampOpenCloseC();
//	bool bIsEmptyPkRightClampClose(int nTime);
//	bool bIsEmptyPkRightClampOpen(int nTime );
//	bool bIsEmptyPkRightClampOUTOFF(int n_Time);
//	void EmptyPkRightClampClose(void);
//	void EmptyPkRightClampOpen(void);
//	void EmptyPkRightClampOpenCloseM(void);
//	#pragma endregion
//
//	#pragma region EMPTY_PICKER_CLAMP_OPEN_CLOSE
//	bool bIsEmptyPkClampClose(int nTime);
//	bool bIsEmptyPkClampOpen(int nTime);
//	bool bIsEmptyPkClampOUTOFF(int nTime);
//	void EmptyPkClampClose(void);
//	void EmptyPkClampOpen(void);
//	void EmptyPkClampOpenCloseM(void);
//	#pragma endregion
//
//	#pragma region EMPTY_TRAY_ELEV1_DOOR_LOCK_UNLOC
//	bool bIsEmptyElev1Lock(int nTime);
//	bool bIsEmptyElev1Unlock(int nTime);
//	void EmptyElev1Lock(void);
//	void EmptyElev1UnLock(void);
//	void EmptyElev1LockUnlockM(void);
//	#pragma endregion
//
//	#pragma region EMPTY_TRAY_ELEV2_DOOR_LOCK_UNLOCK
//	bool bIsEmptyElev2Lock(int nTime);
//	bool bIsEmptyElev2Unlock(int nTime);
//	void EmptyElev2Lock(void);
//	void EmptyElev2UnLock(void);
//	void EmptyElev2LockUnlockM(void);
//	#pragma endregion
//
//	#pragma region EMPTY_TRAY_ELEV3_DOOR_LOCK_UNLOCK
//	bool bIsEmptyElev3Lock(int nTime);
//	bool bIsEmptyElev3Unlock(int nTime);
//	void EmptyElev3Lock(void);
//	void EmptyElev3UnLock(void);
//	void EmptyElev3LockUnlockM(void);
//	#pragma endregion
//
//	#pragma region SAW_PK_AIR_KNIFE_ON_FF
//	bool bIsSawPkAirKnifeOUTON(int nTime);
//	bool bIsSawPkAirKnifeOUTOFF(int nTime);
//	void SawPkAirKnifeOn();
//	void SawPkAirKnifeOff();
//	void SawPkAirKnifeOnOffM();
//	#pragma endregion
//
//	#pragma region FLIPY1_AIR_KNIFE_ON_FF
//	bool bIsFlipY1AirKnifeOUTON(int nTime);
//	bool bIsFlipY1AirKnifeOUTOFF(int nTime);
//	void FlipY1AirKnifeOn();
//	void FlipY1AirKnifeOff();
//	void FlipY1AirKnifeOnOffM();
//	#pragma endregion
//
//	#pragma region FLIPY2_AIR_KNIFE_ON_FF
//	bool bIsFlipY2AirKnifeOUTON(int nTime);
//	bool bIsFlipY2AirKnifeOUTOFF(int nTime);
//	void FlipY2AirKnifeOn();
//	void FlipY2AirKnifeOff();
//	void FlipY2AirKnifeOnOffM();
//	#pragma endregion
//
//	#pragma region PALLETY1_AIR_KNIFE_ON_FF
//	bool bIsPalletY1AirKnifeOUTON(int nTime);
//	bool bIsPalletY1AirKnifeOUTOFF(int nTime);
//	void PalletY1AirKnifeOn();
//	void PalletY1AirKnifeOff();
//	void PalletY1AirKnifeOnOffM();
//	#pragma endregion
//
//	#pragma region PALLETY2_AIR_KNIFE_ON_FF
//	bool bIsPalletY2AirKnifeOUTON(int nTime);
//	bool bIsPalletY2AirKnifeOUTOFF(int nTime);
//	void PalletY2AirKnifeOn();
//	void PalletY2AirKnifeOff();
//	void PalletY2AirKnifeOnOffM();
//	#pragma endregion
//
//	#pragma region IONIZER_AIR_BLOW
//	void SortingZoneIonizerOn();
//	void SortingZoneIonizerOnOffM();
//	void TrayElevZoneIonizerOn();
//	void TrayElevZoneIonizerOnOffM();
//	void FlipZoneIonizerOn();
//	void FlipZoneIonizerOnOffM();
//	void IonizerAllOn();
//	void IonizerAllOff();
//	void IonizerAllOnOffM();
//	#pragma endregion

#pragma endregion

	//////////////////////////////////////////////////////////////////////////
#pragma region SEQ03_AllHome.cpp
	void AllHomeC(void);
	void AllHomeM(void);
#pragma endregion

	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ04_LoadPkPnP.cpp
//	bool bIsLoadPkVacOn(int nTime);
//	bool bIsLoadPkVacOff(int nTime);
//	bool bIsLoadPkVacOUTON(int nTime);
//	bool bIsLoadPkVacOUTOFF(int nTime);
//
//	void LoadPkVacOn();
//	void LoadPkVacOff();
//	void LoadPkVacC();
//	void LoadPkVacOnOffM();
//
//	void LoadPkZMove(int pos, int speed);
//	bool bIsLoadPkCanMove(void);
//	void LoadPkPnPC(void);
//	void LoadPkPnPM(void);
//	void PIOStartC(void);
//	void PIOStartM(void);
//	void PIOEndC(void);
//	void PIOEndM(void);
//	void PIO_INIT(void);
//	void LoadPkSawIOInterfaceC();
//	void LoadPkSawIOInterfaceM();
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ05_SawPkPnP.cpp
//	#pragma region SAW_PICKER_VACUUM
//	bool bIsSawPkVacOn(int nTime);
//	bool bIsSawPkVacOff(int nTime);
//	bool bIsSawPkVacOUTON(int nTime);
//	bool bIsSawPkVacOUTOFF(int nTime);
//	void SawPkVacOn();
//	void SawPkVacOff();
//	void SawPkVacC();
//	void SawPkVacOnOffM();
//	#pragma endregion
//
//	#pragma region SAW_PICKER_SCRAP_VACUUM
//	bool bIsSawPkScrap1VacOn(int nTime);
//	bool bIsSawPkScrap1VacOff(int nTime);
//	void SawPkScrap1VacOn();
//	void SawPkScrap1VacOff();
//	bool bIsSawPkScrap1VacOUTON(int nTime);
//	bool bIsSawPkScrap1VacOUTOFF(int nTime);
//	void SawPkScrap1VacOnOffM(void);
//
//	bool bIsSawPkScrap2VacOn(int nTime);
//	bool bIsSawPkScrap2VacOff(int nTime);
//	void SawPkScrap2VacOn();
//	void SawPkScrap2VacOff();
//	bool bIsSawPkScrap2VacOUTON(int nTime);
//	bool bIsSawPkScrap2VacOUTOFF(int nTime);
//	void SawPkScrap2VacOnOffM(void);
//
//	bool bIsSawPkScrap3VacOn(int nTime);
//	bool bIsSawPkScrap3VacOff(int nTime);
//	void SawPkScrap3VacOn();
//	void SawPkScrap3VacOff();
//	void SawPkScrap3VacOnOffM(void);
//
//	bool bIsSawPkScrapVacOn(int nTime);
//	bool bIsSawPkScrapVacOff(int nTime);
//	bool bIsSawPkScrapVacOUTON(int nTime);
//	bool bIsSawPkScrapVacOUTOFF(int nTime);
//	void SawPkScrapVacOn();
//	void SawPkScrapVacOff();
//	void SawPkScrapVacC();
//	void SawPkScrapVacOnOffM();
//	#pragma endregion
//
//	void SawPkZMove(int pos, int speed);
//	bool bIsSawPkCanMove(void);
//	void SawPkMoveToNextPos(void);
//	void SawPkPnPC(void);
//	void SawPkPnPM(void);
//
//	void SawPkSawIOInterfaceC(void);
//	void SawPkSawIOInterfaceM(void);
//#pragma endregion
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ06_Sawing.cpp
//	void SawingC(void);
//#pragma endregion
//
//#pragma region SEQ07_WaterJet.cpp
//	#pragma region WATERJET_SPONGE_CLEAN
//	bool bIsWaterJetSpongeCleanOUTON(int nTime);
//	bool bIsWaterJetSpongeCleanOUTOFF(int nTime);
//	void WaterJetSpongeCleanOn();
//	void WaterJetSpongeCleanOff();
//	void WaterJetSpongeCleanOnOffM();
//	#pragma endregion
//
//	#pragma region WATERJET_WATER_KNIFE
//	bool bIsWaterJetWaterKnifeOUTON(int nTime);
//	bool bIsWaterJetWaterKnifeOUTOFF(int nTime);
//	void WaterJetWaterKnifeOn();
//	void WaterJetWaterKnifeOff();
//	void WaterJetWaterKinfeOnOffM();
//	#pragma endregion
//
//	#pragma region WATERJET_AIR_KNIFE
//	bool bIsWaterJetAirKnifeOUTON(int nTime);
//	bool bIsWaterJetAirKnifeOUTOFF(int nTime);
//	void WaterJetAirKnifeOn();
//	void WaterJetAirKnifeOff();
//	void WaterJetAirKinfeOnOffM();
//	#pragma endregion
//
//	void WaterJetCleanC();
//	void WaterJetCleanM();
//
//#pragma endregion
//	//////////////////////////////////////////////////////////////////////////
//
//#pragma region SEQ08_Flip1.cpp
//	#pragma region FLIPY1_VACUUM
//	bool bIsFlipY1VacOn(int nTime);
//	bool bIsFlipY1VacOff(int nTime);
//	bool bIsFlipY1VacOUTON(int nTime);
//	bool bIsFlipY1VacOUTOFF(int nTime);
//	void FlipY1VacOn();
//	void FlipY1VacOff();
//	void FlipY1VacC();
//	void FlipY1VacOnOffM();
//	#pragma endregion
//	
//	void FlipY1C(void);
//	void FlipY1M(void);
//
//	void Flip1VisionProcess(void);
//#pragma endregion
//	//////////////////////////////////////////////////////////////////////////
//
//#pragma region SEQ09_Flip2.cpp
//	#pragma region FLIPY2_VACUUM
//	bool bIsFlipY2VacOn(int nTime);
//	bool bIsFlipY2VacOff(int nTime);
//	bool bIsFlipY2VacOUTON(int nTime);
//	bool bIsFlipY2VacOUTOFF(int nTime);
//	void FlipY2VacOn();
//	void FlipY2VacOff();
//	void FlipY2VacC();
//	void FlipY2VacOnOffM();
//	#pragma endregion
//
//	void FlipY2C(void);
//	void FlipY2M(void);
//
//	void Flip2VisionProcess(void);
//
//#pragma endregion
//	//////////////////////////////////////////////////////////////////////////
//
//#pragma region SEQ10_Pallet1.cpp
//	#pragma region PALLETY1_VACUUM
//	bool bIsPalletY1VacOn(int nTime);
//	bool bIsPalletY1VacOff(int nTime);
//	bool bIsPalletY1VacOUTON(int nTime);
//	bool bIsPalletY1VacOUTOFF(int nTime);
//	void PalletY1VacOn();
//	void PalletY1VacOff();
//	void PalletY1VacC();
//	void PalletY1VacOnOffM();
//	#pragma endregion
//
//	void PalletY1C(void);
//	void PalletY1M(void);
//
//	void Pallet1VisionProcess(void);
//	void Pallet1VacValveControl(double KpaVal);
//
//#pragma endregion
//	//////////////////////////////////////////////////////////////////////////
//
//#pragma region SEQ11_Pallet2.cpp
//	#pragma region PALLETY2_VACUUM
//	bool bIsPalletY2VacOn(int nTime);
//	bool bIsPalletY2VacOff(int nTime);
//	bool bIsPalletY2VacOUTON(int nTime);
//	bool bIsPalletY2VacOUTOFF(int nTime);
//	void PalletY2VacOn();
//	void PalletY2VacOff();
//	void PalletY2VacC();
//	void PalletY2VacOnOffM();
//	#pragma endregion
//
//	void PalletY2C(void);
//	void PalletY2M(void);
//
//	void Pallet2VisionProcess(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ20_EmptyElev1.cpp
//	bool bIsEmptyElev1DoorSwitchOn(int nTime);
//	bool bIsEmptyElev1DoorSwitchOff(int nTime);
//
//	bool bIsEmptyElev1DoorClose(int nTime);
//	bool bIsEmptyElev1DoorOpen(int nTime);
//
//	void EmptyElev1Stop();
//	
//	void EmptyElev1C();
//
//	bool bIsEmptyElev1Up(void);
//	bool bIsEmptyElev1Dn(void);
//
//	void EmptyElev1Up(double dVel);
//	void EmptyElev1Dn(double dVel);
//	void EmptyElev1UpM(void);
//	void EmptyElev1DnM(void);
//	
//	bool bIsEmptyElev1TrayLevelOn(int nTime);
//	bool bIsEmptyElev1TrayLevelOff(int nTime);
//	bool bIsEmptyElev1TrayExistOn(int nTime);
//	bool bIsEmptyElev1TrayExistOff(int nTime);
//
//	void EmptyElev1CycleC(void);
//	void EmptyElev1CycleM(void);
//
//	void EmptyElev1SwitchDownC(void);
//	void EmptyElev1SwitchDownM(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ21_EmptyElev2.cpp
//	bool bIsEmptyElev2DoorSwitchOn(int nTime);
//	bool bIsEmptyElev2DoorSwitchOff(int nTime);
//
//	bool bIsEmptyElev2DoorClose(int nTime);
//	bool bIsEmptyElev2DoorOpen(int nTime);
//
//	void EmptyElev2Stop();
//
//	void EmptyElev2C();
//
//	void EmptyElev2Up(double dVel);
//	void EmptyElev2Dn(double dVel);
//
//	bool bIsEmptyElev2Up(void);
//	bool bIsEmptyElev2Dn(void);
//
//	void EmptyElev2UpM(void);
//	void EmptyElev2DnM(void);
//
//	bool bIsEmptyElev2TrayLevelOn(int nTime);
//	bool bIsEmptyElev2TrayLevelOff(int nTime);
//	bool bIsEmptyElev2TrayExistOn(int nTime);
//	bool bIsEmptyElev2TrayExistOff(int nTime);
//
//	void EmptyElev2CycleC(void);
//	void EmptyElev2CycleM(void);
//
//	void EmptyElev2SwitchDownC(void);
//	void EmptyElev2SwitchDownM(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ22_EmptyElev3.cpp
//	bool bIsEmptyElev3DoorSwitchOn(int nTime);
//	bool bIsEmptyElev3DoorSwitchOff(int nTime);
//
//	bool bIsEmptyElev3DoorClose(int nTime);
//	bool bIsEmptyElev3DoorOpen(int nTime);
//
//	void EmptyElev3Stop();
//
//	void EmptyElev3C();
//	
//	bool bIsEmptyElev3Up(void);
//	bool bIsEmptyElev3Dn(void);
//
//	void EmptyElev3Up(double dVel);
//	void EmptyElev3Dn(double dVel);
//
//	void EmptyElev3UpM(void);
//	void EmptyElev3DnM(void);
//
//	bool bIsEmptyElev3TrayLevelOn(int nTime);
//	bool bIsEmptyElev3TrayLevelOff(int nTime);
//	bool bIsEmptyElev3TrayExistOn(int nTime);
//	bool bIsEmptyElev3TrayExistOff(int nTime);
//
//	void EmptyElev3CycleC(void);
//	void EmptyElev3CycleM(void);
//
//	void EmptyElev3SwitchDownC(void);
//	void EmptyElev3SwitchDownM(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ23_EmptyPkPnP.cpp
//	int EmptyPkTrayCheck(void);
//	void EmptyPkMoveToNextPos(void);
//	void EmptyPkPnPC(void);
//	void EmptyPkPnPM(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ30_GoodElev1.cpp
//	bool bIsGoodElev1DoorSwitchOn(int nTime);
//	bool bIsGoodElev1DoorSwitchOff(int nTime);
//
//	void GoodElev1Stop();
//
//	void GoodElev1C();
//
//	void GoodElev1Up(double dVel);
//	void GoodElev1Dn(double dVel);
//
//	void GoodElev1UpM(void);
//	void GoodElev1DnM(void);
//
//	bool bIsGoodElev1DoorClose(int nTime);
//	bool bIsGoodElev1DoorOpen(int nTime);
//
//	bool bIsGoodElev1TrayLevelOn(int nTime);
//	bool bIsGoodElev1TrayLevelOff(int nTime);
//	bool bIsGoodElev1TrayExistOn(int nTime);
//	bool bIsGoodElev1TrayExistOff(int nTime);
//	bool bIsGoodElev1TrayFullOn(int nTime);
//	bool bIsGoodElev1TrayFullOff(int nTime);
//
//	void GoodElev1CycleC(void);
//	void GoodElev1CycleM(void);
//
//	void GoodElev1SwitchDownC(void);
//	void GoodElev1SwitchDownM(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ31_GoodElev2.cpp
//	bool bIsGoodElev2DoorSwitchOn(int nTime);
//	bool bIsGoodElev2DoorSwitchOff(int nTime);
//
//	void GoodElev2Stop();
//
//	void GoodElev2C();
//
//	void GoodElev2Up(double dVel);
//	void GoodElev2Dn(double dVel);
//
//	void GoodElev2UpM(void);
//	void GoodElev2DnM(void);
//
//	bool bIsGoodElev2DoorClose(int nTime);
//	bool bIsGoodElev2DoorOpen(int nTime);
//
//	bool bIsGoodElev2TrayLevelOn(int nTime);
//	bool bIsGoodElev2TrayLevelOff(int nTime);
//	bool bIsGoodElev2TrayExistOn(int nTime);
//	bool bIsGoodElev2TrayExistOff(int nTime);
//	bool bIsGoodElev2TrayFullOn(int nTime);
//	bool bIsGoodElev2TrayFullOff(int nTime);
//
//	void GoodElev2CycleC(void);
//	void GoodElev2CycleM(void);
//
//	void GoodElev2SwitchDownC(void);
//	void GoodElev2SwitchDownM(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ32_ReworkElev.cpp
//	bool bIsReworkElevDoorSwitchOn(int nTime);
//	bool bIsReworkElevDoorSwitchOff(int nTime);
//
//	void RewElevStop();
//
//	void RewElevC();
//
//	void RewElevUp(double dVel);
//	void RewElevDn(double dVel);
//
//	void RewElevUpM(void);
//	void RewElevDnM(void);
//
//	bool bIsRewElevDoorClose(int nTime);
//	bool bIsRewElevDoorOpen(int nTime);
//
//	bool bIsRewElevTrayLevelOn(int nTime);
//	bool bIsRewElevTrayLevelOff(int nTime);
//	bool bIsRewElevTrayExistOn(int nTime);
//	bool bIsRewElevTrayExistOff(int nTime);
//	bool bIsRewElevTrayFullOn(int nTime);
//	bool bIsRewElevTrayFullOff(int nTime);
//
//	void RewElevCycleC(void);
//	void RewElevCycleM(void);
//
//	void RewElevSwitchDownC(void);
//	void RewElevSwitchDownM(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ33_NGElev.cpp
//	bool bIsNGElevDoorSwitchOn(int nTime);
//	bool bIsNGElevDoorSwitchOff(int nTime);
//
//	void NGElevStop();
//
//	void NGElevC();
//
//	void NGElevUp(double dVel);
//	void NGElevDn(double dVel);
//
//	void NGElevUpM(void);
//	void NGElevDnM(void);
//
//	bool bIsNGElevDoorClose(int nTime);
//	bool bIsNGElevDoorOpen(int nTime);
//
//	bool bIsNGElevTrayLevelOn(int nTime);
//	bool bIsNGElevTrayLevelOff(int nTime);
//	bool bIsNGElevTrayExistOn(int nTime);
//	bool bIsNGElevTrayExistOff(int nTime);
//	bool bIsNGElevTrayFullOn(int nTime);
//	bool bIsNGElevTrayFullOff(int nTime);
//
//	void NGElevCycleC(void);
//	void NGElevCycleM(void);
//
//	void NGElevSwitchDownC(void);
//	void NGElevSwitchDownM(void);
//#pragma endregion
//
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ35_GoodTrayY1.cpp
//	bool bIsGoodTrayY1ExistOn(int nTime);
//	bool bIsGoodTrayY1ExistOff(int nTime);
//
//	void GoodTrayY1C(void);
//	void GoodTrayY1M(void);
//	
//	void GoodTray1EjectC(void);
//	void GoodTray1EjectM(void);
//#pragma endregion
//
//#pragma region SEQ36_GoodTrayY2.cpp
//	bool bIsGoodTrayY2ExistOn(int nTime);
//	bool bIsGoodTrayY2ExistOff(int nTime);
//
//	void GoodTrayY2C(void);
//	void GoodTrayY2M(void);
//
//	void GoodTray2EjectC(void);
//	void GoodTray2EjectM(void);
//#pragma endregion
//
//#pragma region SEQ37_NGTrayY.cpp
//	bool bIsNGTrayYExistOn(int nTime);
//	bool bIsNGTrayYExistOff(int nTime);
//
//	void NGTrayYC(void);
//	void NGTrayYM(void);
//
//	void NGTrayEjectC(void);
//	void NGTrayEjectM(void);
//#pragma endregion
//
//#pragma region SEQ38_RewTrayY.cpp
//	bool bIsRewTrayYExistOn(int nTime);
//	bool bIsRewTrayYExistOff(int nTime);
//
//	void RewTrayYC(void);
//	void RewTrayYM(void);
//
//	void RewTrayEjectC(void);
//	void RewTrayEjectM(void);
//#pragma endregion
//
//#pragma region SEQ39_TrayPkPnP.cpp
//	int TrayPkTrayCheck(void);
//	void TrayPkMoveToNextPos(void);
//
//	void TrayPkPnPC(void);
//	void TrayPkPnPM(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ40_FrontRearPk.cpp
//	int GetPkZEmpty(int pktype, int pkdir);
//	bool bIsPkZVacAnyOn(int pktype);
//	bool bIsPkZVacAnyOff(int pktype);
//	bool bIsPkZVacAllOn(int pktype);
//	void PkZVacOn(int pktype, int padno);
//	void PkZVacOff(int pktype, int padno);
//	
//	bool bIsPkZVacOn(int pktype, int padno);
//	bool bIsPkZVacOff(int pktype, int padno);
//	bool bIsPkZVacOffPos(int pktype, int pkno);
//
//	bool bIsPkZVacOUTON(int pkType, int padno, int nTime);
//	bool bIsPkZVacOUTOFF(int pkType, int padno, int nTime);
//	bool bIsPkZVacINOn(int pktype, int padno);
//	void PkZVacOnOffM(int pktype, int padno);
//	void SetPkZVacError(int pktype, int padno);
//
//	bool bIsPkZAllUp(int pktype);
//	bool bIsPkZSyncAllUp(int pktype);
//	bool bIsPkZUp(int pktype, int padno);
//	bool bIsPkZInPos(int pktype, int pkno, int pos);
//	void PkZAllUp(int pktype, int speed);
//	void PkZDn(int pktype, int padno, int pos, int speed);
//	
//	bool bIsPkZDn(int pktype, int padno);
//	int GetPkZDn(int pktype);
//
//	bool bIsPkTAllPos(int pktype, int pos);
//	void PkTAllMove(int pktype, int pos, int speed);
//	void PkTOffsetMove(int pktype, int pkno, double offset);
//
//	void SetPkZLifeTime(int pktype, int padno);
//	int GetPkZSortResult(int pktype, int vr, int pkdir);
//	void SetPkZSortResult(int pktype, int pkno);
//	void SetPkZAllSortResult(int Target[10], _eVisionResult vr);
//
//	void PkZ_PauseAdjust(CAjinMotor* mtx, CAjinMotor* mty, int pos, CAjinMotor* mtz, int zpos);
//
//	void FrontRearPkZC();
//
//	int MTXYNextInPos(CAjinMotor* mtx);
//	void MOVEXY(int Target, int pktype, int xidx, int yidx, int pkno);
//
//	void PkCenterMoveC(void);
//	void PkCenterMoveM(void);
//
//	void GetPkCenterOffsetC(void);
//	void GetPkCenterOffsetM(void);
//
//	void PkCenterAutoCalibrationC(void);
//	void PkCenterAutoCalibrationM(void);
//#pragma endregion
//
//	//////////////////////////////////////////////////////////////////////////
//#pragma region SEQ41_FrontPkPnP.cpp
//	void FrontPkZ_SyncMove();
//	int FrontPkMoveToNextPos();
//	void FrontPkPnPC(void);
//	int FrontPkPnPM(void);
//	void FrontPkSetTriggerPosition(void);
//	void FrontPkVisionResultTestC(void);
//	void FrontPkVisionResultTestM(void);
//
//	//void FrontPkAutoPadAlignC(void);
//	//void FrontPkAutoPadAlignM(void);
//	void GetFrontPkOffset(void);
//#pragma endregion
//
//#pragma region SEQ42_RearPkPnP.cpp
//	void RearPkZ_SyncMove();
//	int RearPkMoveToNextPos();
//	void RearPkPnPC(void);
//	int RearPkPnPM(void);
//	void RearPkSetTriggerPosition(void);
//	void RearPkVisionResultTestC(void);
//	void RearPkVisionResultTestM(void);
//
//	//void RearPkAutoPadAlignC(void);
//	//void RearPkAutoPadAlignM(void);
//	void GetRearPkOffset(void);
//#pragma endregion
//
//#pragma region SEQ50_3Point.cpp
//	void PickUp3PointC(void);
//	void PickUp3PointM(int Target, int pktype, int point);
//
//	void Place3PointC(void);
//	void Place3PointM(int Target, int pktype, int point);
//#pragma endregion
//	//////////////////////////////////////////////////////////////////////////
	// THREAD_Main.cpp
	void SetPalletBegier(void);
	static UINT SEQ_Main_Thread(LPVOID param);

	//////////////////////////////////////////////////////////////////////////
	// THREAD_MMI.cpp
	static UINT MMI_Thread(void* pArg);
		
	//////////////////////////////////////////////////////////////////////////
	// THREAD_Motion.cpp
	static UINT SEQ_Motion_Thread1(LPVOID param);
	/*static UINT SEQ_Motion_Thread2(LPVOID param);
	static UINT SEQ_Motion_Thread3(LPVOID param);
	static UINT SEQ_Motion_Thread4(LPVOID param);
	static UINT SEQ_Motion_Thread5(LPVOID param);
	static UINT SEQ_Motion_Thread6(LPVOID param);*/

	//////////////////////////////////////////////////////////////////////////
	// THREAD_SocketClient.cpp
	static UINT RS232_Thread(void* pArg);
	static void RS232_Comm1(char packet[], CCommPacket* ComPacket);
	static void RS232_Comm2(char packet[], CCommPacket* ComPacket);
	//////////////////////////////////////////////////////////////////////////
	// THREAD_SocketClient.cpp
	static UINT CLIENT_SOCKET_Thread(void* pArg);
	static int ProcessPacket(char* buf, WORD wCommandID);
	static void ReadVisionPacket(char* buf);
	//////////////////////////////////////////////////////////////////////////
	// THREAD_SocketServer.cpp
	static UINT SERVER_SOCKET_Thread(void* pArg);
	static DWORD WINAPI ClientVisionConn(LPVOID arg);
	static void ProcessVisionRxData(VISION_PROTOCOL_DATA VisionData);
	static void SendVision(int CameraNo, VISION_TX_DATA VisionData);
	size_t SERVER_SEND_MSG_ALL(char* sendmsg, char* format, ...);
	size_t SERVER_SEND_MSG(char IP[], int port, char* sendmsg, char* format, ...);
	//size_t SERVER_SEND_MSG(SOCKET s, char* sendmsg, char* format, ...);
	size_t SERVER_SEND_MSG(SOCKET s, char* format, ...);
	static void DecodeMSG(int n_strlen, char msg[2052]);
	void ParseResult(char strpara[]);
	size_t MakePacket(char* sendmsg, char* format, ...);

	//////////////////////////////////////////////////////////////////////////
	// THREAD_UdpClient.cpp
	static UINT CLIENT_UDP_Thread(void* pArg);
	void SEND_UDP(SOCKET s, char* msg);
};

#endif
