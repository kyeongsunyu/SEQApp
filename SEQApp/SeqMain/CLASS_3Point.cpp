#include "CLASS_3Point.h"
#include "DEFINE_GVX.h"
#include "CLASS_Main.h"

C3Point::C3Point()
{
	Step = static_cast<int>(e3Point::INIT);
}
void C3Point::SetTarget(int pktype, int target, int point)
{
	Pktype3P = pktype;
	Target3P = target;
	Point3P = point;
#pragma region TARGET_SETTING
	if (pktype == FRONT_PK) {
		mtxno = MTFrontPkX->AxisNO;
		mtz1no = MTFrontPkZ1->AxisNO;
		mtz2no = MTFrontPkZ2->AxisNO;
		mtz3no = MTFrontPkZ3->AxisNO;
		mtz4no = MTFrontPkZ4->AxisNO;
	}
	else if(pktype == REAR_PK) {
		mtxno = MTRearPkX->AxisNO;
		mtz1no = MTRearPkZ1->AxisNO;
		mtz2no = MTRearPkZ2->AxisNO;
		mtz3no = MTRearPkZ3->AxisNO;
		mtz4no = MTRearPkZ4->AxisNO;
	}

	if (target == PALLETY1) {
		mtyno = MTPalletY1->AxisNO;
		if (pktype == FRONT_PK) {
			if (point == P1) {
				posx = PK_X_PALLET1_P1;
				posy = PALLET_Y_FRONT_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_PALLET1_P2;
				posy = PALLET_Y_FRONT_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_PALLET1_P3;
				posy = PALLET_Y_FRONT_PK_P3;
			}
		}
		else if (pktype == REAR_PK) {
			if (point == P1) {
				posx = PK_X_PALLET1_P1;
				posy = PALLET_Y_REAR_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_PALLET1_P2;
				posy = PALLET_Y_REAR_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_PALLET1_P3;
				posy = PALLET_Y_REAR_PK_P3;
			}
		}
		posz = PK_Z_3POINT_PALLET;
	}
	else if (target == PALLETY2) {
		mtyno = MTPalletY2->AxisNO;
		if (pktype == FRONT_PK) {
			if (point == P1) {
				posx = PK_X_PALLET2_P1;
				posy = PALLET_Y_FRONT_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_PALLET2_P2;
				posy = PALLET_Y_FRONT_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_PALLET2_P3;
				posy = PALLET_Y_FRONT_PK_P3;
			}
		}
		else if (pktype == REAR_PK) {
			if (point == P1) {
				posx = PK_X_PALLET2_P1;
				posy = PALLET_Y_REAR_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_PALLET2_P2;
				posy = PALLET_Y_REAR_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_PALLET2_P3;
				posy = PALLET_Y_REAR_PK_P3;
			}
		}
		posz = PK_Z_3POINT_PALLET;
	}
	else if (target == GOOD_TRAY1) {
		mtyno = MTGoodTrayY1->AxisNO;
		if (pktype == FRONT_PK) {
			if (point == P1) {
				posx = PK_X_GOOD_TRAY1_P1;
				posy = TRAY_Y_FRONT_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_GOOD_TRAY1_P2;
				posy = TRAY_Y_FRONT_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_GOOD_TRAY1_P3;
				posy = TRAY_Y_FRONT_PK_P3;
			}
		}
		else if (pktype == REAR_PK) {
			if (point == P1) {
				posx = PK_X_GOOD_TRAY1_P1;
				posy = TRAY_Y_REAR_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_GOOD_TRAY1_P2;
				posy = TRAY_Y_REAR_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_GOOD_TRAY1_P3;
				posy = TRAY_Y_REAR_PK_P3;
			}
		}
		posz = PK_Z_3POINT_TRAY;
	}
	else if (target == GOOD_TRAY2) {
		mtyno = MTGoodTrayY2->AxisNO;
		if (pktype == FRONT_PK) {
			if (point == P1) {
				posx = PK_X_GOOD_TRAY2_P1;
				posy = TRAY_Y_FRONT_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_GOOD_TRAY2_P2;
				posy = TRAY_Y_FRONT_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_GOOD_TRAY2_P3;
				posy = TRAY_Y_FRONT_PK_P3;
			}
		}
		else if (pktype == REAR_PK) {
			if (point == P1) {
				posx = PK_X_GOOD_TRAY2_P1;
				posy = TRAY_Y_REAR_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_GOOD_TRAY2_P2;
				posy = TRAY_Y_REAR_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_GOOD_TRAY2_P3;
				posy = TRAY_Y_REAR_PK_P3;
			}
		}
		posz = PK_Z_3POINT_TRAY;
	}
	else if (target == REWORK_TRAY) {
		mtyno = MTRewTrayY->AxisNO;
		if (pktype == FRONT_PK) {
			if (point == P1) {
				posx = PK_X_REWORK_TRAY_P1;
				posy = TRAY_Y_FRONT_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_REWORK_TRAY_P2;
				posy = TRAY_Y_FRONT_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_REWORK_TRAY_P3;
				posy = TRAY_Y_FRONT_PK_P3;
			}
		}
		else if (pktype == REAR_PK) {
			if (point == P1) {
				posx = PK_X_REWORK_TRAY_P1;
				posy = TRAY_Y_REAR_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_REWORK_TRAY_P2;
				posy = TRAY_Y_REAR_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_REWORK_TRAY_P3;
				posy = TRAY_Y_REAR_PK_P3;
			}
		}
		posz = PK_Z_3POINT_TRAY;
	}
	else if (target == NG_TRAY) {
		mtyno = MTNGTrayY->AxisNO;
		if (pktype == FRONT_PK) {
			if (point == P1) {
				posx = PK_X_NG_TRAY_P1;
				posy = TRAY_Y_FRONT_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_NG_TRAY_P2;
				posy = TRAY_Y_FRONT_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_NG_TRAY_P3;
				posy = TRAY_Y_FRONT_PK_P3;
			}
		}
		else if (pktype == REAR_PK) {
			if (point == P1) {
				posx = PK_X_NG_TRAY_P1;
				posy = TRAY_Y_REAR_PK_P1;
			}
			else if (point == P2) {
				posx = PK_X_NG_TRAY_P2;
				posy = TRAY_Y_REAR_PK_P2;
			}
			else if (point == P3) {
				posx = PK_X_NG_TRAY_P3;
				posy = TRAY_Y_REAR_PK_P3;
			}
		}
		posz = PK_Z_3POINT_TRAY;
	}
#pragma endregion
}
//void C3Point::PickUpC()
//{
//	CSeqMain* pSeqMain = CSeqMain::GetInstance();
//	assert(pSeqMain != nullptr);
//
//	if (!bit.Run_PickUp3Point || bit.AutoRun) {
//		return;
//	}
//
//	if (!MTRDY(MTAxis[mtxno + 1]) || !MTRDY(MTAxis[mtyno + 1]) ||
//		!MTRDY(MTAxis[mtz1no + 1]) || !MTRDY(MTAxis[mtz2no + 1]) || 
//		!MTRDY(MTAxis[mtz3no + 1]) || !MTRDY(MTAxis[mtz4no + 1])) {
//		return;
//	}
//
//	if (MTRDY(MTAxis[mtxno + 1]) && MTAxis[mtxno + 1]->MotorStop.TimeOvermS(200) &&
//		MTCEP(MTAxis[mtxno + 1], posx) &&
//		MTRDY(MTAxis[mtyno + 1]) && MTAxis[mtyno + 1]->MotorStop.TimeOvermS(200) &&
//		MTCEP(MTAxis[mtyno + 1], posy)) {
//		if (pSeqMain->bIsPkZAllUp(Pktype3P)) {
//			if (pSeqMain->bIsPkZVacOn(Pktype3P, 0)) {
//				MTMOVE(MTAxis[mtxno + 1], PK_X_PAD1_VISION, AUTOSPEED);
//				if (Pktype3P == FRONT_PK) {
//					MTMOVE(MTBtmVisionY, BTM_VISION_Y_FRONT_PAD1, AUTOSPEED);
//				}
//				else if (Pktype3P == REAR_PK) {
//					MTMOVE(MTBtmVisionY, BTM_VISION_Y_REAR_PAD1, AUTOSPEED);
//				}
//			}
//			else {
//				pSeqMain->PkZDn(Pktype3P, 0, posz, AUTOSPEED);
//			}
//		}
//		else {
//			if (pSeqMain->bIsPkZInPos(Pktype3P, 0, posz)) {
//				if (pSeqMain->bIsPkZVacOn(Pktype3P, 0)) {
//					pSeqMain->PkZAllUp(Pktype3P, AUTOSPEED);
//				}
//				else {
//					pSeqMain->PkZVacOn(Pktype3P, 0);
//					if (pSeqMain->bIsPkZVacOUTON(Pktype3P, 0, 1000)) {
//						pSeqMain->PkZAllUp(Pktype3P, AUTOSPEED);
//						pSeqMain->SetPkZVacError(Pktype3P, 0);
//						bit.Run_PickUp3Point = 0;
//					}
//				}
//			}
//		}
//	}
//	else if (MTCEP(MTAxis[mtxno + 1], PK_X_PAD1_VISION)) {
//		if (pSeqMain->bIsPkZAllUp(Pktype3P)) {
//			if (pSeqMain->bIsPkZVacOn(Pktype3P, 0)) {
//				bit.Run_PickUp3Point = 0;
//			}
//			else {
//				MTMOVE(MTAxis[mtxno + 1], posx, AUTOSPEED);
//				MTMOVE(MTAxis[mtyno + 1], posy, AUTOSPEED);
//			}
//		}
//	}
//}
//void C3Point::PickUpM()
//{
//	CSeqMain* pSeqMain = CSeqMain::GetInstance();
//	assert(pSeqMain != nullptr);
//
//	if (bit.Run_PickUp3Point || bit.AutoRun) {
//		return;
//	}
//
//	if (MTRDY(MTAxis[mtxno + 1]) && MTRDY(MTAxis[mtyno + 1]) &&
//		MTRDY(MTAxis[mtz1no + 1]) && MTRDY(MTAxis[mtz2no + 1]) && 
//		MTRDY(MTAxis[mtz3no + 1]) && MTRDY(MTAxis[mtz4no + 1])) {
//		if (pSeqMain->bIsPkZVacOff(Pktype3P, 0)) {
//			bit.Run_PickUp3Point = 1;
//		}
//	}
//}
//
//void C3Point::PlaceC(void)
//{
//	CSeqMain* pSeqMain = CSeqMain::GetInstance();
//	assert(pSeqMain != nullptr);
//
//	if (!bit.Run_Place3Point || bit.AutoRun) {
//		return;
//	}
//
//	if (!MTRDY(MTAxis[mtxno + 1]) || !MTRDY(MTAxis[mtyno + 1]) ||
//		!MTRDY(MTAxis[mtz1no + 1]) || !MTRDY(MTAxis[mtz2no + 1]) ||
//		!MTRDY(MTAxis[mtz3no + 1]) || !MTRDY(MTAxis[mtz4no + 1])) {
//		return;
//	}
//
//	if (MTRDY(MTAxis[mtxno + 1]) && MTAxis[mtxno + 1]->MotorStop.TimeOvermS(200) &&
//		MTCEP(MTAxis[mtxno + 1], posx) &&
//		MTRDY(MTAxis[mtyno + 1]) && MTAxis[mtyno + 1]->MotorStop.TimeOvermS(200) &&
//		MTCEP(MTAxis[mtyno + 1], posy)) {
//		if (pSeqMain->bIsPkZAllUp(Pktype3P)) {
//			if (pSeqMain->bIsPkZVacOff(Pktype3P, 0)) {
//				bit.Run_Place3Point = 0;
//			}
//			else {
//				pSeqMain->PkZDn(Pktype3P, 0, posz, AUTOSPEED);
//			}
//		}
//		else {
//			if (pSeqMain->bIsPkZInPos(Pktype3P, 0, posz)) {
//				if (pSeqMain->bIsPkZVacOff(Pktype3P, 0)) {
//					if (pSeqMain->bIsPkZVacOUTOFF(Pktype3P, 0, 200)) {
//						pSeqMain->PkZAllUp(Pktype3P, AUTOSPEED);
//					}
//				}
//				else {
//					pSeqMain->PkZVacOff(Pktype3P, 0);
//				}
//			}
//		}
//	}
//	else {
//		if (pSeqMain->bIsPkZAllUp(Pktype3P)) {
//			MTMOVE(MTAxis[mtxno + 1], posx, AUTOSPEED);
//			MTMOVE(MTAxis[mtyno + 1], posy, AUTOSPEED);
//		}
//	}
//}
//void C3Point::PlaceM()
//{
//	CSeqMain* pSeqMain = CSeqMain::GetInstance();
//	assert(pSeqMain != nullptr);
//
//	if (bit.Run_Place3Point || bit.AutoRun) {
//		return;
//	}
//
//	if (MTRDY(MTAxis[mtxno + 1]) && MTRDY(MTAxis[mtyno + 1]) &&
//		MTRDY(MTAxis[mtz1no + 1]) && MTRDY(MTAxis[mtz2no + 1]) &&
//		MTRDY(MTAxis[mtz3no + 1]) && MTRDY(MTAxis[mtz4no + 1])) {
//		if (pSeqMain->bIsPkZVacOn(Pktype3P, 0)) {
//			bit.Run_Place3Point = 1;
//		}
//	}
//}

void C3Point::Set3PointC(void)
{
	CSeqMain* pSeqMain = CSeqMain::GetInstance();
	assert(pSeqMain != nullptr);

	if (!bit.Run_3PointPnP || bit.AutoRun) {
		return;
	}

	switch (Step)
	{
		case static_cast<int>(e3Point::INIT):
		{
			Step = static_cast<int>(e3Point::PICK_UP);
			break;
		}
		case static_cast<int>(e3Point::PICK_UP):
		{
			if (MTRDYTM(MTAxis[mtxno + 1], 200) && MTCEP(MTAxis[mtxno + 1], posx) &&
				MTRDYTM(MTAxis[mtyno + 1], 200) && MTCEP(MTAxis[mtyno + 1], posy)) {
				if (pSeqMain->bIsPkZAllUp(Pktype3P)) {
					if (pSeqMain->bIsPkZVacOn(Pktype3P, 0)) {
						MTMOVE(MTAxis[mtxno + 1], PK_X_PAD1_VISION, AUTOSPEED);
						if (Pktype3P == FRONT_PK) {
							MTMOVE(MTBtmVisionY, BTM_VISION_Y_FRONT_PAD1, AUTOSPEED);
						}
						else if (Pktype3P == REAR_PK) {
							MTMOVE(MTBtmVisionY, BTM_VISION_Y_REAR_PAD1, AUTOSPEED);
						}
						Step = static_cast<int>(e3Point::BTM_VISION_TRIGGER);
					}
					else {
						if ((Target3P == PALLETY1) || (Target3P == PALLETY2)) {
							if (pSeqMain->bIsPkTAllPos(Pktype3P, PK_T_0)) {
								pSeqMain->PkZDn(Pktype3P, 0, posz, AUTOSPEED);
							}
							else {
								pSeqMain->PkTAllMove(Pktype3P, PK_T_0, AUTOSPEED);
							}
						}
						else {
							if (pSeqMain->bIsPkTAllPos(Pktype3P, RcpVal.PkTAngle)) {
								pSeqMain->PkZDn(Pktype3P, 0, posz, AUTOSPEED);
							}
							else {
								pSeqMain->PkTAllMove(Pktype3P, RcpVal.PkTAngle, AUTOSPEED);
							}
						}
					}
				}
				else {
					if (pSeqMain->bIsPkZInPos(Pktype3P, 0, posz)) {
						if (pSeqMain->bIsPkZVacOn(Pktype3P, 0)) {
							pSeqMain->PkZAllUp(Pktype3P, AUTOSPEED);
						}
						else {
							if (pSeqMain->bIsPkTAllPos(Pktype3P, PK_T_0)) {
								pSeqMain->PkZVacOn(Pktype3P, 0);
								if (pSeqMain->bIsPkZVacOUTON(Pktype3P, 0, 1000)) {
									pSeqMain->PkZAllUp(Pktype3P, AUTOSPEED);
									pSeqMain->SetPkZVacError(Pktype3P, 0);
									bit.Run_3PointPnP = 0;
								}
							}
							else {
								pSeqMain->PkTAllMove(Pktype3P, PK_T_0, AUTOSPEED);
							}
						}
					}
				}
			}
			else {
				if (pSeqMain->bIsPkZAllUp(Pktype3P)) {
					MTMOVE(MTAxis[mtxno + 1], posx, AUTOSPEED);
					MTMOVE(MTAxis[mtyno + 1], posy, AUTOSPEED);
				}
				else {
					pSeqMain->PkZAllUp(Pktype3P, AUTOSPEED);
				}
			}
			break;
		}
		case static_cast<int>(e3Point::BTM_VISION_TRIGGER):
		{
			if (MTRDYTM(MTAxis[mtxno + 1], 500) && MTCEP(MTAxis[mtxno + 1], PK_X_PAD1_VISION) &&
				MTRDYTM(MTBtmVisionY, 500)) {
				if (MTAxis[mtxno + 1] == MTFrontPkX) {
					AjinCounter->TriggerOut(0, TRUE);
					Sleep(100);
					AjinCounter->TriggerOut(0, FALSE);
				}
				else if (MTAxis[mtxno + 1] == MTRearPkX) {
					AjinCounter->TriggerOut(1, TRUE);
					Sleep(100);
					AjinCounter->TriggerOut(1, FALSE);
				}
				bit.BtmVDataReceived = 0;
				Step = static_cast<int>(e3Point::BTM_VISION_ALIGN);
			}
			break;
		}
		case static_cast<int>(e3Point::BTM_VISION_ALIGN):
		{
			if (MTRDYTM(MTAxis[mtxno + 1], 200) && MTCEP(MTAxis[mtxno + 1], PK_X_PAD1_VISION) &&
				MTRDYTM(MTBtmVisionY, 200)) {
				if (bit.AllDry) {
					Set3PointOffset.pktype = _3PtPkType;
					Set3PointOffset.target = _3PtTarget;
					Set3PointOffset.pointno = _3PtPointNo;
					Set3PointOffset.offsetX = 0.0;
					Set3PointOffset.offsetY = 0.0;
					Set3PointOffset.offsetT = 0.0;
					dm.Set3PointOffset = 1;
					bit.BtmVDataReceived = 0;
					Step = static_cast<int>(e3Point::PLACE);
				}
				else {
					if (bit.BtmVDataReceived) {
						Set3PointOffset.pktype = _3PtPkType;
						Set3PointOffset.target = _3PtTarget;
						Set3PointOffset.pointno = _3PtPointNo;
						Set3PointOffset.offsetX = stod(V3RxData.strPk1OffsetX);
						Set3PointOffset.offsetY = stod(V3RxData.strPk1OffsetY);
						Set3PointOffset.offsetT = stod(V3RxData.strPk1OffsetT);
						dm.Set3PointOffset = 1;
						bit.BtmVDataReceived = 0;
						Step = static_cast<int>(e3Point::PLACE);
					}
				}
			}
			break;
		}
		case static_cast<int>(e3Point::PLACE):
		{
			if (MTRDYTM(MTAxis[mtxno + 1], 200) && MTCEP(MTAxis[mtxno + 1], posx) &&
				MTRDYTM(MTAxis[mtyno + 1], 200) && MTCEP(MTAxis[mtyno + 1], posy)) {
				if (pSeqMain->bIsPkZAllUp(Pktype3P)) {
					if (pSeqMain->bIsPkZVacOff(Pktype3P, 0)) {
						Step = static_cast<int>(e3Point::INIT);
						bit.Run_3PointPnP = 0;
					}
					else {
						pSeqMain->PkZDn(Pktype3P, 0, posz, AUTOSPEED);
					}
				}
				else {
					if (pSeqMain->bIsPkZInPos(Pktype3P, 0, posz)) {
						if (pSeqMain->bIsPkZVacOff(Pktype3P, 0)) {
							if (pSeqMain->bIsPkZVacOUTOFF(Pktype3P, 0, 200)) {
								pSeqMain->PkZAllUp(Pktype3P, AUTOSPEED);
							}
						}
						else {
							pSeqMain->PkZVacOff(Pktype3P, 0);
						}
					}
				}
			}
			else {
				if (pSeqMain->bIsPkZAllUp(Pktype3P)) {
					MTMOVE(MTAxis[mtxno + 1], posx, AUTOSPEED);
					MTMOVE(MTAxis[mtyno + 1], posy, AUTOSPEED);
				}
				else {
					pSeqMain->PkZAllUp(Pktype3P, AUTOSPEED);
				}
			}
			break;
		}
	}
}
void C3Point::Set3PointM(void)
{
	if (bit.Run_3PointPnP || bit.AutoRun) {
		return;
	}

	if (MTRDY(MTAxis[mtxno + 1]) && MTRDY(MTAxis[mtyno + 1]) &&
		MTRDY(MTAxis[mtz1no + 1]) && MTRDY(MTAxis[mtz2no + 1]) &&
		MTRDY(MTAxis[mtz3no + 1]) && MTRDY(MTAxis[mtz4no + 1])) {
		Step = static_cast<int>(e3Point::INIT);
		bit.Run_3PointPnP = 1;
	}
}
