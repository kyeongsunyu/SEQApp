#include "..\pch.h"
#include "..\SeqMain\CLASS_Main.h"
#include "..\SeqMain\DEFINE_GVX.h"

#pragma warning(push)
#pragma warning(disable:6385)

void CSeqMain::AjinHomeFunction(CAjinMotor* Axis)
{
	if (!Axis->IsStop) {
		Axis->MotorStop.SetTime();
	}
	if (Axis->fDoHome && !Axis->CancelCmd) {
		switch (Axis->sHomeState)
		{
		case  Init:
			Axis->sHomeState = Go_CCW;
			break;
		case Go_CCW:
			//	if(Axis->IsHWLimitCCW){
			if (Axis->IsORG && (Axis->SensorType == CCW)) {
				Axis->MTEStop();
				if (Axis->SensorType == CCW) {
					Axis->sHomeState = Go_CW;
				}
				else {
					Axis->sHomeState = Stop_ORG;
				}
				break;
			}
			if (Axis->IsORG && (Axis->SensorType == ORG || Axis->SensorType == ORG_CCW)) {
				Axis->MTEStop();
				Axis->sHomeState = Stop_ORG;
				break;
			}
			else {
				if (Axis->bCamType) {
					Axis->Speed = -4000;
					Axis->Accel = 4000 * 5.0;
				}
				else {
					Axis->Speed=-((int)(Axis->MMI_HomeVel *Axis->MMI_PulseRate));
					Axis->Accel = abs(Axis->Speed * 5);
				}
				// 				Axis->GetActualPosition();
				// 				printf("Go_CCW: axisno=%d, Speed=%d, Accel=%d, pos=%d, Aixs->IsOrg=%d\n",Axis->axisno,Axis->Speed,Axis->Accel,Axis->ActualPosition, Axis->IsORG);
				Axis->MTSCMove();

				if (Axis->SensorType == CCW) {
					Axis->sHomeState = Stop_CCW;
				}
				else {
					Axis->sHomeState = Stop_ORG;
				}
				break;
			}
			break;
		case Go_CW:
			if (Axis->MotorStop.TimeOvermS(100)) {
				Axis->Speed = 10000;//*Axis->HomeSpeed;
				Axis->Accel = Axis->Speed * 5;
				Axis->InitSpeed = 500;
				Axis->MTSCMove();
				if (Axis->SensorType == CCW) {
					Axis->sHomeState = Stop_No_CCW;
				}
				else {
					Axis->sHomeState = Stop_ORG;
				}
			}
			break;
		case Stop_ORG:
			if (Axis->IsHWLimitCCW) {
				if (Axis->IsStop) {
					if (Axis->MotorStop.TimeOvermS(100)) {
						Axis->Speed = 10000;//*Axis->HomeSpeed;
						Axis->InitSpeed = Axis->Speed * 5;
						Axis->MTSCMove();
						break;
					}
				}
				else if (Axis->Speed < 0) {
					Axis->MTEStop();
				}
			}

			if (Axis->IsORG) {
				if (!(Axis->SensorType == Z_ORG_CCW)) {
					Axis->MTEStop();
					Axis->GetActualPosition();
					//printf("Go_ORG axisno=%d MTEStop, pos=%d,Axis->IsORG=[%x]%d\n",Axis->axisno, Axis->ActualPosition, &Axis, Axis->IsORG);
				}
				else {
					Axis->MTEStop();
					//printf("Go_ORG axisno=%d MTEStop\n",Axis->axisno);
				}

				if (Axis->IsStop) {
					if (Axis->MotorStop.TimeOvermS(200)) {
						Axis->Speed = 10000;//*Axis->HomeSpeed;
						Axis->Accel = Axis->Speed * 5;
						Axis->InitSpeed = 10;
						Axis->sHomeState = GO_NO_ORG;
						Axis->MTSCMove();
					}
				}
				break;
			}
			break;
		case Stop_CCW:
			if (Axis->IsHWLimitCCW) {
				//    if(Axis->IsORG){
				//Sleep(300);
				if (!Axis->IsStop) {
					Axis->MTEStop();
				}
				if (Axis->IsStop) {
					if (Axis->MotorStop.TimeOvermS(100)) {
						Axis->Speed = 10000; //*Axis->ZPhaseSpeed;
						Axis->Accel = Axis->Speed * 5;
						Axis->Decel = Axis->Accel;
						Axis->InitSpeed = 10;
						Axis->MTSCMove();
						Axis->sHomeState = Stop_No_CCW;
						break;
					}
				}
			}
			break;
		case Stop_No_CCW:
			if (!Axis->IsHWLimitCCW) {
				//    if(!Axis->IsORG){
				if (!Axis->IsStop) {
					Axis->MTEStop();
				}
				if (Axis->IsStop && Axis->MotorStop.TimeOvermS(1000)) {
					Axis->Speed = -1000;
					Axis->Accel = abs(Axis->Speed * 5);
					//	Axis->Accel = 10;
					Axis->MTSRMove(10);
					Axis->sHomeState = Complete;
				}
				break;
			}
			//else {
			//	if (Axis->IsStop) {
			//		if (Axis->MotorStop.TimeOvermS(100)) {
			//			Axis->Speed = 10000; //*Axis->ZPhaseSpeed;
			//			Axis->Accel = Axis->Speed * 5;
			//			Axis->Decel = Axis->Accel;
			//			Axis->InitSpeed = 10;
			//			Axis->MTSCMove();
			//		}
			//	}
			//}
			break;
		case GO_NO_ORG:
			if (!Axis->IsORG) {
				Axis->MTEStop();
				Axis->sHomeState = Wait_motorstop;
			}
			break;
		case Wait_motorstop:
			if (Axis->IsStop && Axis->MotorStop.TimeOvermS(300)) {
				Axis->sHomeState = Search_ORG;
				Axis->Speed = -1000;//*Axis->ZPhaseSpeed*-1;
				Axis->Accel = abs(Axis->Speed * 5);
				Axis->InitSpeed = -10;
				Axis->MTSCMove();
			}
			break;
		case Search_ORG:
			if (Axis->IsORG) {
				Axis->MTEStop();
				Axis->sHomeState = Complete;
			}
			break;
		case Complete:
			if (Axis->IsStop && Axis->MotorStop.TimeOvermS(2000)) {
				Axis->fDoHome = false;
				Axis->fIMRS = true;
				Axis->sHomeState = Init;
				Axis->SetActualPosition(0);
				Axis->SetCommandPosition(0);
				Axis->InitSpeed = 50;
			}

			/*
			if(Axis->IsStop&&Axis->MotorStop.TimeOvermS(1500)&&!Axis->MotorStop.TimeOvermS(1600)){
				Axis->SetActualPosition(0);
				Axis->SetCommandPosition(0);
				Axis->InitSpeed= 50;
			}
			else if(Axis->IsStop&&Axis->MotorStop.TimeOvermS(2000)){
				Axis->fDoHome=false;
				Axis->fIMRS=true;
				Axis->sHomeState=Init;
				Axis->GetActualPosition();
				Axis->GetCommandPosition();
			}
			*/
			break;
		default:
			Axis->sHomeState = Init;
			break;
		}
	}

	if (Axis->CancelCmd) {
		Axis->fDoHome = false;
		Axis->sHomeState = Init;
		Axis->CmdMode = Wait_Reset;
	}
	else Axis->CmdMode = Wait_Cmd;

}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::AjinMotorC(CAjinMotor* Axis)
{
	if ((BITON(Axis->ostart) || !Axis->moving) && BITOFF(Axis->irdy)) {
		if (BITON(Axis->ostart)) {
			Axis->moving = 1;
			Axis->ostart = 1;
		}
		else if (!Axis->moving) {
			Axis->omove = 0;
		}
		Axis->fDriving = 0;
	}

	if (Axis->moving) {
		/* stop check */
		if (BITON(Axis->irdy) && !Axis->fDoHome) {
			Axis->CurPos = Axis->NxtPos;
			Axis->CurArrpos = Axis->NxtArrpos;
			Axis->moving = 0;
			Axis->omove = 0;
			if (Axis->fIMRS) {
				Axis->imrs = 1;
				if (Axis->DfltWorking) {
					Axis->NxtPos = Axis->DfltWorking;
					Axis->SpeedDevide = FAST;
					Axis->NxtArrpos = Axis->PositionArray[Axis->DfltWorking];//+PULSE10_1MM*30;
					Axis->CurArrpos = 0L;
					Axis->omove = 1;
					Axis->fIMRS = false;
				}
			}
		}
	}
	else {
		/* not moving now */
		if (Axis->omove) {
			if ((Axis->imrs) || (Axis->NxtPos == 0)) {
				/* signal out routine */
				if (BITOFF(Axis->ostart) && BITON(Axis->irdy)) {
					if (Axis->NxtPos == 0) {
						Axis->CmdMode = Move_Home;
						Axis->CancelCmd = false;
						Axis->fDoHome = true;
						Axis->sHomeState = Init;
					}
					else {
						if (Axis->NxtPos != 99) {
							if (Axis->NxtPos > 100) {
								Axis->Speed = Axis->SpeedArray[0];
								Axis->Accel = Axis->AccelArray[0] * 10;
								Axis->Decel = Axis->Accel;
							}
							else {
								if ((Axis->CurPos == 0) && (Axis->NxtPos == 1)) {
									Axis->Speed = (int)(Axis->SpeedArray[Axis->NxtPos] * 0.5);
									Axis->Accel = Axis->Speed * 5;// Axis->AccelArray[Axis->NxtPos];
									Axis->Decel = Axis->Accel;
								}
								else {
									Axis->Speed = Axis->SpeedArray[Axis->NxtPos];
									Axis->Accel = Axis->Speed * 10;// Axis->AccelArray[Axis->NxtPos];
									Axis->Decel = Axis->Accel;
								}
							}
							Axis->fDriving = 1;

							if (Axis->bCamType) {
								Axis->NxtArrpos = (int)(Axis->NxtArrpos * (8000. / 360.));
							}

							/*if ((Axis == MTFrontPkZ1) || (Axis == MTFrontPkZ2) ||
								(Axis == MTFrontPkZ3) || (Axis == MTFrontPkZ4) ||
								(Axis == MTRearPkZ1) || (Axis == MTRearPkZ2) ||
								(Axis == MTRearPkZ3) || (Axis == MTRearPkZ4)) {
								Axis->Speed = Axis->SpeedArray[Axis->NxtPos];
								Axis->Accel = 5.0 * 9800 * MTFrontPkZ1->MMI_PulseRate;
								Axis->Decel = Axis->Accel;
							}
							else if ((Axis == MTFrontPkX) || (Axis == MTRearPkX)) {
								Axis->Speed = Axis->SpeedArray[Axis->NxtPos];
								Axis->Accel = 2.0 * 9800 * MTFrontPkX->MMI_PulseRate;
								Axis->Decel = Axis->Accel;
							}
							else if ((Axis == MTGoodTrayY1) || (Axis == MTGoodTrayY2) ||
									 (Axis == MTRewTrayY) || (Axis == MTNGTrayY)) {
								Axis->Speed = Axis->SpeedArray[Axis->NxtPos];
								Axis->Accel = 1.0 * 9800 * MTGoodTrayY1->MMI_PulseRate;
								Axis->Decel = Axis->Accel;
							}
							else {
								Make_Parameter1(Axis);
							}*/
							/*if (Axis == MTFrontPkZ3) {
								printf("====MTFrontPkZ3->CurPos=%d, MTFrontPkZ3->NxtPos=%d\n", MTFrontPkZ3->CurPos, MTFrontPkZ3->NxtPos);
							}*/
							Make_Parameter1(Axis);
							Axis->relative = 0;
							if (Axis->relative) {
								Axis->MTSRMove((int)Axis->NxtArrpos);
							}
							else {
								Axis->MTSAMove((int)Axis->NxtArrpos);
							}
						}
					}
					Axis->ostart = 0;
				}
			}
			else {
				Axis->omove = 0;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::AjinMotorStatus(int startaxis, int endaxis)
{
	for (int mtno = startaxis; mtno <= endaxis; mtno++) {
		MTAxis[mtno]->GetMotorStatus();

		BITMOV(MTAxis[mtno]->irdy, MTAxis[mtno]->IsDriving);
		BITMOV(MTAxis[mtno]->isend, (MTAxis[mtno]->IsHWLimitCCW | MTAxis[mtno]->IsHWLimitCW));
		BITMOV(MTAxis[mtno]->idrvrdy, !MTAxis[mtno]->IsDRVRDY);
		BITMOV(MTAxis[mtno]->idrvalm, MTAxis[mtno]->IsAlarm);

		AjinMotorC(MTAxis[mtno]);
		AjinHomeFunction(MTAxis[mtno]);
	}
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::Motor_Pause(CAjinMotor* Axis, int Stop)
{
	if (!Axis->fMotorPause) {
		if (Axis->IsDriving && Axis->omove) {
			if (Stop == SUDDEN_STOP) {
				Axis->MTEStop();
			}
			else {
				Axis->MTStop();
			}
			if (Axis->fDoHome) {
				Axis->fDoHome = false;
				Axis->fMotorHome = 1;
			}
			Axis->fMotorPause = 1;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::Motor_Adjust(CAjinMotor* Axis)
{
	if (Axis->fMotorPause) {
		if (Axis->IsStop) {
			if (Axis->fMotorHome) {
				Axis->fDoHome = true;
				Axis->fMotorHome = 0;
				Axis->sHomeState = Init;
			}
			else {
				Axis->MTSAMove(Axis->AdjustPosition);
			}
			Axis->fMotorPause = 0;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::Motor_Tunning(CAjinMotor* Axis)
{
	if (bit.MotorTunning) {
		Make_Parameter1(Axis);
		if (Axis->imrs && !Axis->irdy && !Axis->omove && Axis->MotorStop.TimeOvermS(100)) {
			if ((Axis->CurPos != 2)) {
				MTMOVE(Axis, 2, AUTOSPEED);
				spmcount30s++;
			}
			else {
				MTMOVE(Axis, 1, AUTOSPEED);
				spmcount30s++;
			}
		}

		if (tm_gSPM30s.TimeOverS(30)) {
			tm_gSPM30s.SetTime();
			dm.spmcount = spmcount30s;
			spmcount30s = (WORD)(30000. / dm.spmcount - 100);

			printf(" ^^ moving average time = %hu\n", spmcount30s);
			printf("    distance= %lf, TimeDesier = %lf ^^^^^^\n", Axis->MovingDistance, Axis->TimeDesier);
			printf("    speed= %lf, accel= %lf  Jerk = %lf^^^^^^\n", Axis->Speed, Axis->Accel, Axis->Jerk);
			spmcount30s = 0;
		}
	}
}
#pragma warning(pop)