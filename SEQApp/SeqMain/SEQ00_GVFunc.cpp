#include "..\pch.h"
#include "CLASS_Main.h"

//////////////////////////////////////////////////////////////////////////
void CSeqMain::GetNVMMF(void)
{
	nvBit = nvMMF.GetBit();
	memcpy(ubitbuf.wbitbuf, nvBit.bitbuf, sizeof(BITTYPE) * 25);
	bit = ubitbuf.bit;

	nvCount = nvMMF.GetCount();
	MachineStatus.UPH = nvCount.UPH;
	MachineStatus.PanelInCnt = nvCount.PanelInCnt;
	MachineStatus.UnitInCnt = nvCount.UnitInCnt;
	MachineStatus.UnitOutCnt = nvCount.UnitOutCnt;
	MachineStatus.UnitGoodCnt = nvCount.UnitGoodCnt;
	MachineStatus.UnitNGCnt = nvCount.UnitNGCnt;
	MachineStatus.UnitReworkCnt = nvCount.UnitReworkCnt;

	MachineStatus.FlipY1AirCleanCnt = nvCount.FlipY1AirCleanCnt;
	MachineStatus.FlipY2AirCleanCnt = nvCount.FlipY2AirCleanCnt;
	MachineStatus.PalletY1AirCleanCnt = nvCount.PalletY1AirCleanCnt;
	MachineStatus.PalletY2AirCleanCnt = nvCount.PalletY2AirCleanCnt;
	MachineStatus.SawPkFlipY1AirClenaCnt = nvCount.SawPkFlipY1AirClenaCnt;
	MachineStatus.SawPkFlipY2AirClenaCnt = nvCount.SawPkFlipY2AirClenaCnt;
	MachineStatus.SpongeCleanCnt = nvCount.SpongeCleanCnt;
	MachineStatus.WaterJetAirCleanCnt = nvCount.WaterJetAirCleanCnt;

	// Map Status
	nvFlip1Map = nvMMF.GetFlip1Map();
	memcpy(Flip1Map, nvFlip1Map.Map, sizeof(int) * 50 * 50);

	nvFlip2Map = nvMMF.GetFlip2Map();
	memcpy(Flip2Map, nvFlip2Map.Map, sizeof(int) * 50 * 50);

	nvPallet1Map = nvMMF.GetPallet1Map();
	memcpy(Pallet1Map, nvPallet1Map.Map, sizeof(int) * 50 * 50);

	nvPallet2Map = nvMMF.GetPallet2Map();
	memcpy(Pallet2Map, nvPallet2Map.Map, sizeof(int) * 50 * 50);

	nvGoodTray1Map = nvMMF.GetGoodTray1Map();
	memcpy(GoodTray1Map, nvGoodTray1Map.Map, sizeof(int) * 50 * 50);

	nvGoodTray2Map = nvMMF.GetGoodTray2Map();
	memcpy(GoodTray2Map, nvGoodTray2Map.Map, sizeof(int) * 50 * 50);

	nvReworkTrayMap = nvMMF.GetReworkTrayMap();
	memcpy(RewTrayMap, nvReworkTrayMap.Map, sizeof(int) * 50 * 50);

	nvNGTrayMap = nvMMF.GetNGTrayMap();
	memcpy(NGTrayMap, nvNGTrayMap.Map, sizeof(int) * 50 * 50);

	// Vision Result
	nvFlip1VisionResult = nvMMF.GetFlip1Result();
	memcpy(Flip1VisionResult, nvFlip1VisionResult.Result, sizeof(int) * 50 * 50);

	nvFlip2VisionResult = nvMMF.GetFlip2Result();
	memcpy(Flip2VisionResult, nvFlip2VisionResult.Result, sizeof(int) * 50 * 50);

	nvPallet1VisionResult = nvMMF.GetPallet1Result();
	memcpy(Pallet1VisionResult, nvPallet1VisionResult.Result, sizeof(int) * 50 * 50);

	nvPallet2VisionResult = nvMMF.GetPallet2Result();
	memcpy(Pallet2VisionResult, nvPallet2VisionResult.Result, sizeof(int) * 50 * 50);

	nvFrontPkVisionResult = nvMMF.GetFrontPkResult();
	memcpy(FrontPkVisionResult, nvFrontPkVisionResult.Result, sizeof(int) * 10);

	nvRearPkVisionResult = nvMMF.GetRearPkResult();
	memcpy(RearPkVisionResult, nvRearPkVisionResult.Result, sizeof(int) * 10);

	nvGoodTray1VisionResult = nvMMF.GetGoodTray1Result();
	memcpy(GoodTray1VisionResult, nvGoodTray1VisionResult.Result, sizeof(int) * 50 * 50);

	nvGoodTray2VisionResult = nvMMF.GetGoodTray2Result();
	memcpy(GoodTray2VisionResult, nvGoodTray2VisionResult.Result, sizeof(int) * 50 * 50);

	nvReworkTrayVisionResult = nvMMF.GetReworkTrayResult();
	memcpy(RewTrayVisionResult, nvReworkTrayVisionResult.Result, sizeof(int) * 50 * 50);

	nvNGTrayVisionResult = nvMMF.GetNGTrayResult();
	memcpy(NGTrayVisionResult, nvNGTrayVisionResult.Result, sizeof(int) * 50 * 50);

}
void CSeqMain::SetNVMMF(void)
{
	// bit
	ubitbuf.bit = bit;
	memcpy(nvBit.bitbuf, ubitbuf.wbitbuf, sizeof(BITTYPE) * 25);
	nvMMF.SetBit(nvBit);

	// Count
	nvCount.UPH = MachineStatus.UPH;
	nvCount.TPH = MachineStatus.TPH;
	nvCount.PanelInCnt = MachineStatus.PanelInCnt;
	nvCount.UnitInCnt = MachineStatus.UnitInCnt;
	nvCount.UnitOutCnt = MachineStatus.UnitOutCnt;
	nvCount.SpongeCleanCnt = MachineStatus.SpongeCleanCnt;
	nvCount.WaterJetAirCleanCnt = MachineStatus.WaterJetAirCleanCnt;
	nvCount.SawPkFlipY1AirClenaCnt = MachineStatus.SawPkFlipY1AirClenaCnt;
	nvCount.SawPkFlipY2AirClenaCnt = MachineStatus.SawPkFlipY2AirClenaCnt;
	nvCount.FlipY1AirCleanCnt = MachineStatus.FlipY1AirCleanCnt;
	nvCount.FlipY2AirCleanCnt = MachineStatus.FlipY2AirCleanCnt;
	nvCount.PalletY1AirCleanCnt = MachineStatus.PalletY1AirCleanCnt;
	nvCount.PalletY2AirCleanCnt = MachineStatus.PalletY2AirCleanCnt;
	nvCount.UnitGoodCnt = MachineStatus.UnitGoodCnt;
	nvCount.UnitReworkCnt = MachineStatus.UnitReworkCnt;
	nvCount.UnitNGCnt = MachineStatus.UnitNGCnt;

	nvMMF.SetCount(nvCount);

	// Map
	memcpy(nvFlip1Map.Map, Flip1Map, sizeof(int) * 50 * 50);
	nvMMF.SetFlip1Map(nvFlip1Map);

	memcpy(nvFlip2Map.Map, Flip2Map, sizeof(int) * 50 * 50);
	nvMMF.SetFlip2Map(nvFlip2Map);

	memcpy(nvPallet1Map.Map, Pallet1Map, sizeof(int) * 50 * 50);
	nvMMF.SetPallet1Map(nvPallet1Map);

	memcpy(nvPallet2Map.Map, Pallet2Map, sizeof(int) * 50 * 50);
	nvMMF.SetPallet2Map(nvPallet2Map);

	memcpy(nvGoodTray1Map.Map, GoodTray1Map, sizeof(int) * 50 * 50);
	nvMMF.SetGoodTray1Map(nvGoodTray1Map);

	memcpy(nvGoodTray2Map.Map, GoodTray2Map, sizeof(int) * 50 * 50);
	nvMMF.SetGoodTray2Map(nvGoodTray2Map);

	memcpy(nvReworkTrayMap.Map, RewTrayMap, sizeof(int) * 50 * 50);
	nvMMF.SetReworkTrayMap(nvReworkTrayMap);

	memcpy(nvNGTrayMap.Map, NGTrayMap, sizeof(int) * 50 * 50);
	nvMMF.SetNGTrayMap(nvNGTrayMap);

	memcpy(nvFlip1VisionResult.Result, Flip1VisionResult, sizeof(int) * 50 * 50);
	nvMMF.SetFlip1Result(nvFlip1VisionResult);

	memcpy(nvFlip2VisionResult.Result, Flip2VisionResult, sizeof(int) * 50 * 50);
	nvMMF.SetFlip2Result(nvFlip2VisionResult);

	memcpy(nvPallet1VisionResult.Result, Pallet1VisionResult, sizeof(int) * 50 * 50);
	nvMMF.SetPallet1Result(nvPallet1VisionResult);

	memcpy(nvPallet2VisionResult.Result, Pallet2VisionResult, sizeof(int) * 50 * 50);
	nvMMF.SetPallet2Result(nvPallet2VisionResult);

	memcpy(nvFrontPkVisionResult.Result, FrontPkVisionResult, sizeof(int) * 10);
	nvMMF.SetFrontPkResult(nvFrontPkVisionResult);

	memcpy(nvRearPkVisionResult.Result, RearPkVisionResult, sizeof(int) * 10);
	nvMMF.SetRearPkResult(nvRearPkVisionResult);

	memcpy(nvGoodTray1VisionResult.Result, GoodTray1VisionResult, sizeof(int) * 50 * 50);
	nvMMF.SetGoodTray1Result(nvGoodTray1VisionResult);

	memcpy(nvGoodTray2VisionResult.Result, GoodTray2VisionResult, sizeof(int) * 50 * 50);
	nvMMF.SetGoodTray2Result(nvGoodTray2VisionResult);

	memcpy(nvReworkTrayVisionResult.Result, RewTrayVisionResult, sizeof(int) * 50 * 50);
	nvMMF.SetReworkTrayResult(nvReworkTrayVisionResult);

	memcpy(nvNGTrayVisionResult.Result, NGTrayVisionResult, sizeof(int) * 50 * 50);
	nvMMF.SetNGTrayResult(nvNGTrayVisionResult);

}
void CSeqMain::SetAllMap(int Target[50][50], int MapState)
{	// FlipY1, FlipY2, PalletY1, PalletY2 자재 유무 상태
	//for (int i = 0; i < 50; i++) {
	//	for (int j = 0; j < 50; j++) {
	//		Target[i][j] = MapState;
	//	}
	//}

	fill(Target[0], Target[50], MapState);
}

//void CSeqMain::SetAllVisionResult(int Target[50][50], int MapState)
//{	// FlipY1, FlipY2, PalletY1, PalletY2 Vision Result
//	int setdata;
//	if (MapState == TVR_NONE) {
//		setdata = 0;
//	}
//	else {
//		setdata = (1 << MapState);
//	}
//
//	//for (int i = 0; i < 50; i++) {
//	//	for (int j = 0; j < 50; j++) {
//	//		Target[i][j] = setdata;
//	//	}
//	//}
//	fill(Target[0], Target[50], setdata);
//}
//
//void CSeqMain::SetVisionResult(int Target[50][50], int x, int y, int Result)
//{
//	int setdata;
//	if (Result == TVR_NONE) {
//		setdata = 0;
//	}
//	else {
//		setdata = (1 << Result);
//	}
//
//	Target[x][y] = setdata;
//}
//
//void CSeqMain::CopyVisionResult(int dest[50][50], int source[50][50])
//{
//	//memcpy(dest, source, sizeof(source));
//	memcpy(dest, source, sizeof(int)*50*50);
//}
//void CSeqMain::ClearVisionResult(int dest[50][50])
//{
//	memset(dest, 0, sizeof(int)*50*50);
//}
//
//void CSeqMain::CopyPkVisionResult(int Target[10], int pkno, int Result)
//{
//	Target[pkno] = Result;
//}
//void CSeqMain::SetPkVisionResult(int Target[10], int pkno, int Result)
//{
//	int setdata;
//	if (Result == TVR_NONE) {
//		setdata = 0;
//	}
//	else {
//		setdata = (1 << Result);
//	}
//	Target[pkno] = setdata;
//}
//void CSeqMain::ClearPkVisionResult(int Target[10], int pkno)
//{
//	Target[pkno] = 0;
//}
//
//void CSeqMain::SetAllTriggerMap(int Target[50][50], int MapState)
//{	// FlipY1, FlipY2, PalletY1, PalletY2 Vision Trigger 처리 상태
//
//	//for (int i = 0; i < 50; i++) {
//	//	for (int j = 0; j < 50; j++) {
//	//		Target[i][j] = MapState;
//	//	}
//	//}
//	fill(Target[0], Target[50], MapState);
//}
//
//bool CSeqMain::GetTriggerPosIDX(int Target[50][50], int& xpos, int& ypos)
//{
//	// FlipY1, FlipY2, PalletY1, PalletY2 Vision Trigger 처리 상태
//	int x, y;
//
//	for (x = 0; x < TrigXCnt; x++) {
//		if (x % 2) { // 홀수열
//			for (y = (TrigYCnt - 1); y >= 0; y--) {
//				if (Target[x][y] == 1) {
//					xpos = x;
//					ypos = y;
//					return true;
//				}
//			}
//		}
//		else {	// 짝수 열		
//			for (y = 0; y < TrigYCnt; y++) {
//				if (Target[x][y] == 1) {
//					xpos = x;
//					ypos = y;
//					return true;
//				}
//			}
//		}
//	}
//	xpos = -1;
//	ypos = -1;
//	return false;
//}
//void CSeqMain::SetTriggerPosIDX(int Target[50][50], int x, int y, int MapState)
//{	
//	// FlipY1, FlipY2, PalletY1, PalletY2 Vision Trigger 처리 상태
//	Target[x][y] = MapState;
//}
//
//void CSeqMain::CalcTriggerPos(int Target)
//{	
	/*
	// FlipY1, FlipY2, PalletY1, PalletY2 Vision Trigger Position 계산
	double XSize, YSize;
	double XGap, YGap;
	int SnapX = RcpVal.SnapXCnt;
	int SnapY = RcpVal.SnapYCnt;
	
	if (Target == FLIPY1) {
		for (int i = 0; i < TrigXCnt; i++) {
			for (int j = 0; j < TrigYCnt; j++) {
				XSize = RcpVal.UnitXSize * MTTopVisionX1->MMI_PulseRate;
				YSize = RcpVal.UnitYSize * MTFlipY1->MMI_PulseRate;
				XGap  = RcpVal.UnitXPitch * MTTopVisionX1->MMI_PulseRate;
				YGap  = RcpVal.UnitYPitch * MTFlipY1->MMI_PulseRate;
				double TrigXGap = ((double)XSize + XGap) * SnapX;
				double TrigYGap = ((double)YSize + YGap) * SnapY;
				FlipY1TrigPosX[i][j] = MTTopVisionX1->PositionArray[TOP_VISION_X1_FLIP_INSPECT_START] + (double)i * TrigXGap;
				FlipY1TrigPosY[i][j] = MTFlipY1->PositionArray[FLIP_Y1_INSPECT_START] + (double)j * TrigYGap;
			}
		}
	}
	else if (Target == FLIPY2) {
		for (int i = 0; i < TrigXCnt; i++) {
			for (int j = 0; j < TrigYCnt; j++) {
				XSize = RcpVal.UnitXSize * MTTopVisionX2->MMI_PulseRate;
				YSize = RcpVal.UnitYSize * MTFlipY2->MMI_PulseRate;
				XGap = RcpVal.UnitXPitch * MTTopVisionX2->MMI_PulseRate;
				YGap = RcpVal.UnitYPitch * MTFlipY2->MMI_PulseRate;
				double TrigXGap = ((double)XSize + XGap) * SnapX;
				double TrigYGap = ((double)YSize + YGap) * SnapY;
				FlipY2TrigPosX[i][j] = MTTopVisionX2->PositionArray[TOP_VISION_X2_FLIP_INSPECT_START] - (double)(i * TrigXGap);
				FlipY2TrigPosY[i][j] = MTFlipY2->PositionArray[FLIP_Y2_INSPECT_START] + (double)(j * TrigYGap);
			}
		}
	}
	else if (Target == PALLETY1) {
		for (int i = 0; i < TrigXCnt; i++) {
			for (int j = 0; j < TrigYCnt; j++) {
				XSize = RcpVal.UnitXSize * MTTopVisionX1->MMI_PulseRate;
				YSize = RcpVal.UnitYSize * MTPalletY1->MMI_PulseRate;
				XGap = RcpVal.UnitXPitch * MTTopVisionX1->MMI_PulseRate;
				YGap = RcpVal.UnitYPitch * MTPalletY1->MMI_PulseRate;
				double TrigXGap = ((double)XSize + XGap) * SnapX;
				double TrigYGap = ((double)YSize + YGap) * SnapY;
				PalletY1TrigPosX[i][j] = MTTopVisionX1->PositionArray[TOP_VISION_X1_PALLET_INSPECT_START] + (double)(i * TrigXGap);
				PalletY1TrigPosY[i][j] = MTPalletY1->PositionArray[PALLET_Y_INSPECT_START] + (double)(j * TrigYGap);
			}
		}
	}
	else if (Target == PALLETY2) {
		for (int i = 0; i < TrigXCnt; i++) {
			for (int j = 0; j < TrigYCnt; j++) {
				XSize = RcpVal.UnitXSize * MTTopVisionX2->MMI_PulseRate;
				YSize = RcpVal.UnitYSize * MTPalletY2->MMI_PulseRate;
				XGap = RcpVal.UnitXPitch * MTTopVisionX2->MMI_PulseRate;
				YGap = RcpVal.UnitYPitch * MTPalletY2->MMI_PulseRate;
				double TrigXGap = ((double)XSize + XGap) * SnapX;
				double TrigYGap = ((double)YSize + YGap) * SnapY;
				PalletY2TrigPosX[i][j] = MTTopVisionX2->PositionArray[TOP_VISION_X2_PALLET_INSPECT_START] - (double)i * TrigXGap;
				PalletY2TrigPosY[i][j] = MTPalletY2->PositionArray[PALLET_Y_INSPECT_START] + (double)j * TrigYGap;
			}
		}
	}
}

int CSeqMain::GetPickUpDirection(int Target[50][50], int MapDir)
{
	// MapDir == MAP_DIR_X			// MapDir == MAP_DIR_Y
	// ===================▶		// ||  ▲ ||  ▲
	// ◀===================		// ||  || ||  ||
	// ====================▶		// ||  || ||  ||	
	// ◀===================        // ▼  || ▼  ||


	int ZigZag = RIGHT_TP_LEFT;	// defalut ZigZag direction
	int XCount = RcpVal.UnitXCnt;
	int YCount = RcpVal.UnitYCnt;
	
	int x, y;
	if (MapDir == MAP_DIR_X) {
		for (y = 0; y < YCount; y++) {
			for (x = 0; x < XCount; x++) {
				if (Target[x][y]==EXIST) {
					ZigZag = ((y % 2)==0)? LEFT_TO_RIGHT : RIGHT_TP_LEFT;
					//printf("Target[%d][%d]=%d, ZigZag=%d\n", x, y, Target[x][y], ZigZag);
					return ZigZag;
				}
			}
		}
	}
	else if (MapDir == MAP_DIR_Y) {
		for (x = 0; x < XCount; x++) {
			for (y = 0; y < YCount; y++) {
				if (Target[x][y]==EXIST) {
					// RetZigZag 0: go to down direction, 1: go to up direction
					ZigZag = ((x % 2) == 0) ? UP_TO_DOWN : DOWN_TO_UP;
					return ZigZag;
				}
			}
		}
	}
	return ZigZag;
}
int CSeqMain::GetPlaceDirection(int Target[50][50], int MapDir)
{
	int ZigZag = LEFT_TO_RIGHT;	// defalut ZigZag direction
	int XCount = RcpVal.TrayXCnt;
	int YCount = RcpVal.TrayYCnt;

	int x, y;
	if (MapDir == MAP_DIR_X) {
		for (y = 0; y < YCount; y++) {
			for (x = 0; x < XCount; x++) {
				if (Target[x][y]==EMPTY) {
					ZigZag = (_eZigZagLeftRight)((y % 2) == 0) ? RIGHT_TP_LEFT : LEFT_TO_RIGHT;
					//printf("Target[%d][%d]=%d, ZigZag=%d\n", x, y, Target[x][y], ZigZag);
					return ZigZag;
				}
			}
		}
	}
	else if (MapDir == MAP_DIR_Y) {
		for (x = 0; x < XCount; x++) {
			for (y = 0; y < YCount; y++) {
				if (Target[x][y]==EMPTY) {
					ZigZag = (_eZigZagUpDn)((x % 2) == 0) ? UP_TO_DOWN : DOWN_TO_UP;
					return ZigZag;
				}
			}
		}
	}
	return ZigZag;
}

bool CSeqMain::GetPickUpPosIDX(int Target[50][50], int MapDir, int ZigZag, int* xpos, int* ypos)
{
	// PalletY1, PalletY2 Pick Up Map Position Index
	int x, y;
	
	if (MapDir == MAP_DIR_X) { // 가로 방향
		for (y = 0; y < UnitYCnt; y++) {
			if (ZigZag == RIGHT_TP_LEFT) {
				for (x = UnitXCnt - 1; x >= 0; x--) {
					if (Target[x][y] == EXIST) {
						*xpos = x;
						*ypos = y;
						return true;
					}
				}
			}
			else if (ZigZag == LEFT_TO_RIGHT) {	// 
				for (x = 0; x < UnitXCnt; x++) {
					if (Target[x][y] == EXIST) {
						*xpos = x;
						*ypos = y;
						return true;
					}
				}
			}
		}
	}
	else if (MapDir == MAP_DIR_Y) { // 세로 방향
		for (x = 0; x < UnitXCnt; x++) {
			if (ZigZag == UP_TO_DOWN) {
				for (y = 0; y < UnitYCnt; y++) {
					if (Target[x][y] == EXIST) {
						*xpos = x;
						*ypos = y;
						return true;
					}
				}
			}
			else if (ZigZag == DOWN_TO_UP) {
				for (y = UnitYCnt - 1; y >= 0; y--) {
					if (Target[x][y] == EXIST) {
						*xpos = x;
						*ypos = y;
						return true;
					}
				}
			}
		}
	}
	*xpos = -1;
	*ypos = -1;
	return false;
	*/
//}
//void CSeqMain::SetPickUpPosIDX(int Target[50][50], int xpos, int ypos, int state)
//{
//	//Target[xpos][ypos] = state;
//}
//
//bool CSeqMain::GetPlacePosIDX(int Target, int MapDir, int ZigZag, int* xpos, int* ypos)
//{
	//// GoodTray1, GoodTray2, ReworkTray, NGTray Place Map Position Index
	//int x, y;
	//int MapData[50][50];
	//int XCount = RcpVal.TrayXCnt;
	//int YCount = RcpVal.TrayYCnt;
	//bool bTrayExist = false;

	//if (Target == GOOD_TRAY1) {
	//	memmove(MapData, GoodTray1Map, sizeof(int)* 50* 50);
	//	bTrayExist = bIsGoodTrayY1ExistOn(200) ? true : false;
	//}
	//else if (Target == GOOD_TRAY2) {
	//	memmove(MapData, GoodTray2Map, sizeof(int)* 50 * 50);
	//	bTrayExist = bIsGoodTrayY2ExistOn(200) ? true : false;
	//}
	//else if (Target == REWORK_TRAY) {
	//	memmove(MapData, RewTrayMap, sizeof(int) * 50 * 50);
	//	bTrayExist = bIsRewTrayYExistOn(200) ? true : false;
	//}
	//else if (Target == NG_TRAY) {
	//	memmove(MapData, NGTrayMap, sizeof(int) * 50 * 50);
	//	bTrayExist = bIsNGTrayYExistOn(200) ? true : false;
	//}

	//if (bTrayExist) {
	//	if (MapDir == MAP_DIR_X) { // 가로 방향
	//		for (y = 0; y < YCount; y++) {
	//			if (ZigZag == RIGHT_TP_LEFT) {
	//				for (x = XCount - 1; x >= 0; x--) {
	//					if (MapData[x][y] == EMPTY) {
	//						*xpos = x;
	//						*ypos = y;
	//						return true;
	//					}
	//				}
	//			}
	//			else if (ZigZag == LEFT_TO_RIGHT) {	// 
	//				for (x = 0; x < XCount; x++) {
	//					if (MapData[x][y] == EMPTY) {
	//						*xpos = x;
	//						*ypos = y;
	//						return true;
	//					}
	//				}
	//			}
	//		}
	//	}
	//	else if (MapDir == MAP_DIR_Y) { // 세로 방향
	//		for (x = 0; x < XCount; x++) {
	//			if (ZigZag == UP_TO_DOWN) {
	//				for (y = 0; y < YCount; y++) {
	//					if (MapData[x][y] == EMPTY) {
	//						*xpos = x;
	//						*ypos = y;
	//						return true;
	//					}
	//				}
	//			}
	//			else if (ZigZag == DOWN_TO_UP) {
	//				for (y = YCount - 1; y >= 0; y--) {
	//					if (MapData[x][y] == EMPTY) {
	//						*xpos = x;
	//						*ypos = y;
	//						return true;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//*xpos = -1;
	//*ypos = -1;
//	return false;
//}
//void CSeqMain::SetPlacePosIDX(int Target[50][50], int xpos, int ypos, int state)
//{
//	//Target[xpos][ypos] = state;
//}

void CSeqMain::SetDeviceData(void)
{

#pragma region DEVICE_DATA_ARRAY
	RcpVal.UnitXSize = DeviceData.Unit_X_Size;
	RcpVal.UnitYSize = DeviceData.Unit_Y_Size;

	RcpVal.UnitXCnt = (int)DeviceData.Unit_X_Count;
	RcpVal.UnitYCnt = (int)DeviceData.Unit_Y_Count;

	RcpVal.UnitXPitch = DeviceData.Unit_X_Pitch;
	RcpVal.UnitYPitch = DeviceData.Unit_Y_Pitch;
	
	RcpVal.TrayXCnt = (int)DeviceData.Tray_X_Count;
	RcpVal.TrayYCnt = (int)DeviceData.Tray_Y_Count;

	RcpVal.SnapXCnt = (int)DeviceData.Vision_Snap_X_Count;
	RcpVal.SnapYCnt = (int)DeviceData.Vision_Snap_Y_Count;

	/*if ((int)DeviceData.Picker_Angle == 0) {
		RcpVal.PkTAngle = PK_T_0;
	}
	else if ((int)DeviceData.Picker_Angle == 1) {
		RcpVal.PkTAngle = PK_T_90;
	}
	else if ((int)DeviceData.Picker_Angle == 2) {
		RcpVal.PkTAngle = PK_T_180;
	}
	else if ((int)DeviceData.Picker_Angle == 3) {
		RcpVal.PkTAngle = PK_T_270;
	}*/

	RcpVal.PkPlaceVacOffOffset = DeviceData.Picker_Place_Vac_Off_Offset;

	RcpVal.Pallet1_Receive_Vac_Value = DeviceData.Pallet1_Receive_Vac_Value;
	RcpVal.Pallet2_Receive_Vac_Value = DeviceData.Pallet2_Receive_Vac_Value;
	RcpVal.PalletFirstSortVacValue = DeviceData.Pallet_First_Sort_Vac_Value;
	RcpVal.PalletMiddleSortVacValue = DeviceData.Pallet_Middle_Sort_Vac_Value;
	RcpVal.PalletLastSortVacValue = DeviceData.Pallet_Last_Sort_Vac_Value;
	RcpVal.PalletFirstSortPKGRate = DeviceData.Pallet_First_Sort_PKG_Rate;
	RcpVal.PalletLastSortPKGRate = DeviceData.Pallet_Last_Sort_PKG_Rate;
#pragma endregion

#pragma region DEVICE_DATA_BOOL_ARRAY
	RcpVal.bFrontPickerSKIP[0] = RcpVal.bFrontPk1SKIP = DeviceData.Front_Picker_1_Skip ? true : false;
	RcpVal.bFrontPickerSKIP[1] = RcpVal.bFrontPk2SKIP = DeviceData.Front_Picker_2_Skip ? true : false;
	RcpVal.bFrontPickerSKIP[2] = RcpVal.bFrontPk3SKIP = DeviceData.Front_Picker_3_Skip ? true : false;
	RcpVal.bFrontPickerSKIP[3] = RcpVal.bFrontPk4SKIP = DeviceData.Front_Picker_4_Skip ? true : false;
	RcpVal.bFrontPickerSKIP[4] = RcpVal.bFrontPk5SKIP = DeviceData.Front_Picker_5_Skip ? true : false;
	RcpVal.bFrontPickerSKIP[5] = RcpVal.bFrontPk6SKIP = DeviceData.Front_Picker_6_Skip ? true : false;
	RcpVal.bFrontPickerSKIP[6] = RcpVal.bFrontPk7SKIP = DeviceData.Front_Picker_7_Skip ? true : false;
	RcpVal.bFrontPickerSKIP[7] = RcpVal.bFrontPk8SKIP = DeviceData.Front_Picker_8_Skip ? true : false;

	RcpVal.bRearPickerSKIP[0] = RcpVal.bRearPk1SKIP = DeviceData.Rear_Picker_1_Skip ? true : false;
	RcpVal.bRearPickerSKIP[1] = RcpVal.bRearPk2SKIP = DeviceData.Rear_Picker_2_Skip ? true : false;
	RcpVal.bRearPickerSKIP[2] = RcpVal.bRearPk3SKIP = DeviceData.Rear_Picker_3_Skip ? true : false;
	RcpVal.bRearPickerSKIP[3] = RcpVal.bRearPk4SKIP = DeviceData.Rear_Picker_4_Skip ? true : false;
	RcpVal.bRearPickerSKIP[4] = RcpVal.bRearPk5SKIP = DeviceData.Rear_Picker_5_Skip ? true : false;
	RcpVal.bRearPickerSKIP[5] = RcpVal.bRearPk6SKIP = DeviceData.Rear_Picker_6_Skip ? true : false;
	RcpVal.bRearPickerSKIP[6] = RcpVal.bRearPk7SKIP = DeviceData.Rear_Picker_7_Skip ? true : false;
	RcpVal.bRearPickerSKIP[7] = RcpVal.bRearPk8SKIP = DeviceData.Rear_Picker_8_Skip ? true : false;
	
	RcpVal.bScrapSKIP		= DeviceData.Scrap_Skip ? true : false;
	RcpVal.bSpongeCleanSKIP = DeviceData.Sponge_Clean_Skip ? true : false;
#pragma endregion

#pragma region DEVICE_DAT_INT_ARRAY
	RcpVal.SpongeCleanCnt = DeviceData.Saw_Picker_Sponge_Clean;
	RcpVal.WaterJetWaterCleanCnt = DeviceData.Water_Jet_Water_Clean;
	RcpVal.WaterJetAirCleanCnt = DeviceData.Water_Jet_Air_Clean;
	RcpVal.SawPkFlipY1AirClenaCnt = DeviceData.Saw_Picker_Flip_Y1_Air_Clean;
	RcpVal.SawPkFlipY2AirClenaCnt = DeviceData.Saw_Picker_Flip_Y2_Air_Clean;
	RcpVal.FlipY1AirCleanCnt = DeviceData.Flip_Y1_Air_Clean;
	RcpVal.FlipY2AirCleanCnt = DeviceData.Flip_Y2_Air_Clean;
	RcpVal.PalletY1AirCleanCnt = DeviceData.Pallet_Y1_Air_Clean;
	RcpVal.PalletY2AirCleanCnt = DeviceData.Pallet_Y2_Air_Clean;
#pragma endregion

#pragma region DEVICE_DATA_DOUBLE_ARRAY
	RcpVal.FrontPkBlowTime = (int)DeviceData.Front_Picker_Air_Blow_Time;
	RcpVal.RearPkBlowTime = (int)DeviceData.Rear_Picker_Air_Blow_Time;
	RcpVal.FrontPkVacOnTime = (int)DeviceData.Front_Picker_Vac_On_Time;
	RcpVal.RearPkVacOnTime = (int)DeviceData.Rear_Picker_Vac_On_Time;

	RcpVal.LoadPkAirBlowTime = (int)DeviceData.Load_Picker_Air_Blow_Time;
	RcpVal.LoadPkVacOnTime = (int)DeviceData.Load_Picker_Vac_On_Time;
	RcpVal.SawPkAirBlowTime = (int)DeviceData.Saw_Picker_Air_Blow_Time;
	RcpVal.SawPkVacOnTime = (int)DeviceData.Saw_Picker_Vac_On_Time;

#pragma endregion

	UnitXCnt = (int)RcpVal.UnitXCnt;
	UnitYCnt = (int)RcpVal.UnitYCnt;
	SnapXCnt = (int)RcpVal.SnapXCnt;
	SnapYCnt = (int)RcpVal.SnapYCnt;

	TrigXCnt = (UnitXCnt % SnapXCnt == 0) ? (UnitXCnt / SnapXCnt) : (UnitXCnt / SnapXCnt + 1);
	TrigYCnt = (UnitYCnt % SnapYCnt == 0) ? (UnitYCnt / SnapYCnt) : (UnitYCnt / SnapYCnt + 1);

}