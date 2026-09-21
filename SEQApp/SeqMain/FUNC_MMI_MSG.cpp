#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"


SHARED_MEMORY_BASE smemcomm;
TMemCommand             Mmi2Seq, Seq2Mmi;

unsigned short int  uConfigCount = 0;


//////////////////////////////////////////////////////////////////////////
void CSeqMain::InitComm(void)
{
	if (FALSE == smemcomm.InitObject(RUN_SEQ, 1)) {
		printf("\nCommnucation Initialize Failed....\n");
		exit(0);
	}
	else {
		printf("\nCommnucation Initialize OK....\n");
	}
	smemcomm.FlushInOutBuffer();
}

//------------------------------------------------------------------------
void CSeqMain::MMI_MessageCommunication(void)
{
	unsigned int uRtnCode, dwCommand = 0, uIdx = 0;
	bool SendToMmi = false;
	int AxisNo = 0;
	int mtno = 0, start = 0, end = 0;

	int i = 0;
	int j = 0;

	if (smemcomm.Recv(&Mmi2Seq) == true) {
		dwCommand = (BYTE)Mmi2Seq.Command;
		// 		printf("dwCommand=%d\n", dwCommand);
		switch (dwCommand) {
			case CMD_READ_BITV: // Read Bit Variable Data
			{
				ubitbuf.bit = bit;
				memcpy(Mmi2Seq.Arg.IoBit.uData, ubitbuf.wbitbuf, sizeof(ubitbuf.wbitbuf));
				SendToMmi = true;
				break;
			}
			case CMD_WRITE_BITV: // Write Bit Variable Data
			{
				start = Mmi2Seq.Arg.IoBit.uStart;
				end = Mmi2Seq.Arg.IoBit.uCount;
				memcpy(&ubitbuf.wbitbuf[start], &Mmi2Seq.Arg.IoBit.uData[start], sizeof(WORD) * (end));
				bit = ubitbuf.bit;
				break;
			}
			case CMD_READ_DM: // Read Data Memory Variable Data
			{
				udmbuf.dm = dm;
				memcpy(Mmi2Seq.Arg.DataMemory.uData, udmbuf.wdmbuf, sizeof(udmbuf.wdmbuf));
				SendToMmi = true;
				break;
			}
			case CMD_WRITE_DM: // Write Data Memory Variable Data
			{
				start = Mmi2Seq.Arg.DataMemory.uStart;
				end = Mmi2Seq.Arg.DataMemory.uCount;
				memcpy(&udmbuf.wdmbuf[start], &Mmi2Seq.Arg.DataMemory.uData[start], sizeof(DMTYPE) * (end));
				dm = udmbuf.dm;
				break;
			}
			case CMD_READ_IO: // Read Input/Output Variable Data
			{
				memcpy(Mmi2Seq.Arg.IoBit.uData, uiobuf.wiobuf, sizeof(uiobuf.wiobuf));
				SendToMmi = true;
				break;
			}
			case CMD_WRITE_IO: // Write Input/Output Variable Data
			{
				start = Mmi2Seq.Arg.IoBit.uStart;
				end = Mmi2Seq.Arg.IoBit.uCount;
				memcpy(&uiobuf.wiobuf[start], &Mmi2Seq.Arg.IoBit.uData[start], sizeof(signed short int) * (end));
				//			printf("uiobuf.wiobuf[%d]=%d \n",start,uiobuf.wiobuf[start]);
				break;
			}
			case CMD_READ_ERRORCODE: // Read Error Code
			{
				memcpy(Mmi2Seq.Arg.ErrorCode.uErrorCode, errorcode, sizeof(errorcode));
				Mmi2Seq.Arg.ErrorCode.uMTBA_MTBF = dm.MTBA_MTBF;
				break;
			}
			////////// Motor Command ///////////////////////////
			case CMD_SERVO_ONOFF:
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_SERVO_ALARM_CLEAR:
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_SERVO_HOME:
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCmdHomeFunc(dwCommand, mtno);
				break;
			}
			case CMD_READ_MOTORSTATUS: // Read Motor Status
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_MOTORSCONTINUE:
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_MOTORSRELATIVE: // Motor S-Curve Relative Move
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_MOTORINDEXMOVE:
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_MOTORSTOP:
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_WRITE_MOTORDATA: // Write Motor Data
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_READ_MOTORDATA: // Read Motor Data
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_READ_MOTORCONFIG:
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_WRITE_MOTORCONFIG:
			{
				mtno = Mmi2Seq.Arg.MotorMove.uAxisNo;
				MMI_MessageMotorCommand(dwCommand, mtno);
				break;
			}
			case CMD_READ_DEVICEDATA:
			{
			//	memcpy(Mmi2Seq.Arg.Device.dData, DeviceData.dData, sizeof(double) * 100);
				break;
			} 
			case CMD_WRITE_DEVICEDATA:
			{
				int n1 = sizeof(DeviceData);
				int n2 = sizeof(Mmi2Seq.Arg.Device);
				memcpy(&DeviceData, &Mmi2Seq.Arg.Device, sizeof(DeviceData));
				MachineSpeed = 100;

				dm.MachineSpeed = MachineSpeed;
				SetDeviceData();
				bit.DeviceDataReceived = 1;

				// 			printf("dm.MachineSpeed=%d\n",dm.MachineSpeed);
				//
				// 			printf("Mmi2Seq.Arg.Device.DeviceSize=%d\n"				,Mmi2Seq.Arg.Device.DeviceSize);
				// 			printf("Mmi2Seq.Arg.Device.NoofWfInMz=%d\n"				,Mmi2Seq.Arg.Device.NoofWfInMz);
				// 			printf("Mmi2Seq.Arg.Device.MzPitch=%f\n"				,Mmi2Seq.Arg.Device.MzPitch);

				// 			printf("Mmi2Seq.Arg.Device.MachineSpeed=%d\n"			,Mmi2Seq.Arg.Device.MachineSpeed);
				//
				break;
			}
			case CMD_TENKEY:		
			{
				ManualNumber = Mmi2Seq.Arg.Manual.TenKeyNumber;
				//			printf("TenKey Number %d....\n",ManualNumber);
				Key10.SetManualNumber(ManualNumber);
				switch (ManualNumber) {
				case 0:
					KeyReset();
					break;
					//case 255:
					//{
					//	//CSeqMain* seqMain = CSeqMain::GetInstance();
					//	//assert(seqMain != nullptr);

					//	//LOTEND_RESULT lotend_result;
					//	//memset(&lotend_result, 0x00, sizeof(LOTEND_RESULT));

					//	//sprintf(lotend_result.strLotID, "%s", "asdf");
					//	//lotend_result.nLotCount = 200;
					//	//lotend_result.TotalUnitCnt = 200;
					//	//if (LotInfo.nLotCount != MachineStatus.TotalUnitCnt) {
					//	//	lotend_result.nResult = 1;
					//	//}
					//	//else {
					//	//	lotend_result.nResult = 0;
					//	//}
					//	//sprintf(lotend_result.strUserName, "%s", "huck");
					//	//seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_LOTEND_RESULT, sizeof(LOTEND_RESULT), (void*)&lotend_result);
					//}
					//	break;
					//case 297:
					//	ClientVision.SendData("%s", "echo received");
					//	break;
					//case 298:
					//{
					//	char strTest[512];
					//	for (int i = 0; i < 100; i++) {
					//		sprintf(strTest, "%s%d", "testdsfsadfdf dsafdsfdfd dadffd", i);
					//		SEND_UDP(udp_Client, strTest);
					//	}
					//}
					//	break;
					//case 299:
					//	//sprintf(MachineStatus.strCycle[0], "%s", "str Cycle0");
					//	for (int i = 0; i < 100; i++) {
					//		LOG_TRACE("test log %d", SeqLogCnt);
					//	}
					//	break;
				case 350:
				{
					SetAllMap(Flip1Map, EXIST);
					SetAllMap(Flip2Map, EXIST);
					SetAllMap(Pallet1Map, EXIST);
					SetAllMap(Pallet2Map, EXIST);
					SetAllMap(GoodTray1Map, EXIST);
					SetAllMap(GoodTray2Map, EXIST);
					SetAllMap(RewTrayMap, EXIST);
					SetAllMap(NGTrayMap, EXIST);
					break;
				}
				case 351:
				{
					SetAllMap(Flip1Map, EMPTY);
					SetAllMap(Flip2Map, EMPTY);
					SetAllMap(Pallet1Map, EMPTY);
					SetAllMap(Pallet2Map, EMPTY);
					SetAllMap(GoodTray1Map, EMPTY);
					SetAllMap(GoodTray2Map, EMPTY);
					SetAllMap(RewTrayMap, EMPTY);
					SetAllMap(NGTrayMap, EMPTY);
					break;
				}
				case 352:
				{

					break;
				}
				case 353:
				{
					
					break;
				}
				case 354:
				{
				/*	memset(&V3RxData, 0x00, sizeof(VISION_RX_DATA));
					strcpy(V3RxData.strPk1OffsetX, "1.00");
					strcpy(V3RxData.strPk1OffsetY, "1.01");
					strcpy(V3RxData.strPk1OffsetT, "1.02");

					strcpy(V3RxData.strPk2OffsetX, "2.00");
					strcpy(V3RxData.strPk2OffsetY, "2.01");
					strcpy(V3RxData.strPk2OffsetT, "2.02");

					strcpy(V3RxData.strPk3OffsetX, "3.00");
					strcpy(V3RxData.strPk3OffsetY, "3.01");
					strcpy(V3RxData.strPk3OffsetT, "3.02");

					strcpy(V3RxData.strPk4OffsetX, "4.00");
					strcpy(V3RxData.strPk4OffsetY, "4.01");
					strcpy(V3RxData.strPk4OffsetT, "4.02");

					strcpy(V3RxData.strPk5OffsetX, "5.00");
					strcpy(V3RxData.strPk5OffsetY, "5.01");
					strcpy(V3RxData.strPk5OffsetT, "5.02");

					strcpy(V3RxData.strPk6OffsetX, "6.00");
					strcpy(V3RxData.strPk6OffsetY, "6.01");
					strcpy(V3RxData.strPk6OffsetT, "6.02");

					strcpy(V3RxData.strPk7OffsetX, "7.00");
					strcpy(V3RxData.strPk7OffsetY, "7.01");
					strcpy(V3RxData.strPk7OffsetT, "7.02");

					strcpy(V3RxData.strPk8OffsetX, "8.00");
					strcpy(V3RxData.strPk8OffsetY, "8.01");
					strcpy(V3RxData.strPk8OffsetT, "8.02");

					GetFrontPkOffset();*/
					break;
				}
				case 355:
				{
					//VISION_TX_DATA txData;
					//txData.byCommand = 0x01;
					//txData.wRecipeNo = 9;

					//memset(txData.strRecipeID, 0x20, 20);
					//strcpy(txData.strRecipeID, "test");

					//sprintf(txData.strUnitXSize, "%.*f", 2, 46.00);// RcpVal.UnitXSize);
					//sprintf(txData.strUnitYSize, "%.*f", 2, 26.00);// RcpVal.UnitYSize);

					//txData.bySnapXCnt = 2;
					//txData.bySnapYCnt = 2;
					//txData.byInspectionType = 0x01;
					//txData.byTrigNo = 8;
					//txData.byPointNo = 5;

					//sprintf(txData.strLocationX, "%.*f", 3, 123.456);
					//sprintf(txData.strLocationY, "%.*f", 3, 456.789);

					//SendVision(1, txData);
					break;
				}
				case 356:
				{
					/*int len = SERVER_SEND_MSG(VisionSocket, "%s", "TOP_VISION2" );*/
					break;
				}
				case 357:
				{
					SetAllMap(GoodTray1Map, EMPTY);
					break;
				}
				default:
					ManualTenkeyOperation();
					break;
				}

				if (ManualNumber < 200) {
					OutManualNumber(ManualNumber);
				}
				break;
			}
			case CMD_LAMPBUZZER:
			{
				// LampBuzzerType[errorcode][status]
				//			     [errorcode]=0~254, [status]=0~5
				//			     [errorcode][0] = RED    0:OFF, 1:ON, 2:BLINK
				//               [errorcode][1] = YELLOW 0:OFF, 1:ON, 2:BLINK
				//               [errorcode][2] = GREEN  0:OFF, 1:ON, 2:BLINK
				//               [errorcode][3] = BUZZER 0:OFF, 1:ON,
				//               [errorcode][4] = BUZZER ON TIME
				//               [errorcode][5] = BUZZER OFF TIME
				//               [298][0]= START 0:OFF, 1:ON, 2:BLINK
				//		         [299][0]= STOP  0:OFF, 1:ON, 2:BLINK
				memcpy(LampBuzzerType, Mmi2Seq.Arg.LampBuzzer.uLampBuzzer, sizeof(Mmi2Seq.Arg.LampBuzzer.uLampBuzzer));
				break;
			}
			case CMD_READ_STATUS:
			{
				memcpy(&Mmi2Seq.Arg.MachineStatus, &MachineStatus, sizeof(TMachineStatus));
				break;
			}
			case CMD_WRITE_STATUS:
			{
				memcpy(&MachineStatus, &Mmi2Seq.Arg.MachineStatus, sizeof(TMachineStatus));
				break;
			}
			case CMD_READ_USER_INFO:
				break;
			case CMD_WRITE_USER_INFO:
			{
				memcpy(&UserInfo, &Mmi2Seq.Arg.UserInfo, sizeof(TUSER_INFO));
				break;
			}
			case CMD_READ_LOTINFO:
			{
				memcpy(Mmi2Seq.Arg.LotInfo.strLotID, LotInfo.strLotID, sizeof(LotInfo.strLotID));
				Mmi2Seq.Arg.LotInfo.nLotCount = LotInfo.nLotCount;
				break;
			}
			case CMD_WRITE_LOTINFO:
			{
				memcpy(LotInfo.strLotID, Mmi2Seq.Arg.LotInfo.strLotID, sizeof(Mmi2Seq.Arg.LotInfo.strLotID));
				LotInfo.nLotCount = Mmi2Seq.Arg.LotInfo.nLotCount;
				//			pFileLog->Make_Lot_Log_Filename(LotLogName);
				break;
			}
			case CMD_READ_DEVICE_INFO:
			{
				memcpy(Mmi2Seq.Arg.DeviceInfo.strDeviceName, DeviceInfo.strDeviceName, sizeof(DeviceInfo.strDeviceName));
				Mmi2Seq.Arg.DeviceInfo.nDeviceNumber = DeviceInfo.nDeviceNumber;
				break;
			}
			case CMD_WRITE_DEVICE_INFO:
			{
				memcpy(DeviceInfo.strDeviceName, Mmi2Seq.Arg.DeviceInfo.strDeviceName, sizeof(Mmi2Seq.Arg.DeviceInfo.strDeviceName));
				DeviceInfo.nDeviceNumber = Mmi2Seq.Arg.DeviceInfo.nDeviceNumber;
				break;
			}
			case CMD_WRITE_TENKEYJOG:
			{
				tenkeyJogmtno = Mmi2Seq.Arg.TenKeyJog.uAxisNo;
				bTenKeyJog = Mmi2Seq.Arg.TenKeyJog.bTenKeyJog;
				bit.TenkeyJogMove = 0;
				if (bTenKeyJog) {
					printf("MTAxis[%d] Ten-Key Jog mode ON\n", tenkeyJogmtno + 1);
				}
				else {
					printf("MTAxis[%d] Ten-Key Jog mode OFF\n", tenkeyJogmtno + 1);
				}
				break;
			}
			case CMD_WRITE_LOAD_CNT_CLEAR:
			{
				MachineStatus.UnitInCnt = 0;
				break;
			}
			case CMD_WRITE_UNLOAD_CNT_CLEAR:
			{
				MachineStatus.UnitOutCnt = 0;
				break;
			}
			case CMD_WRITE_EMERGENCY_STOP:
			{
				EmerOffProcess();
				break;
			}
			case CMD_WRITE_SYSTEM_DATA:
			{
				memcpy(&SystemData, &Mmi2Seq.Arg.SystemData, sizeof(TSystemData));
				break;
			}
			case CMD_WRITE_BUZZER_OFF:
			{
				bit.NewBuzzer = 0;
				cntbuzzer = 0;
				break;
			}
			case CMD_WRITE_3POINT_SETTING:
			{
	/*			_3PtPkType = Mmi2Seq.Arg.Set3Point.pktype;
				_3PtTarget = Mmi2Seq.Arg.Set3Point.target;
				_3PtPointNo = Mmi2Seq.Arg.Set3Point.pointno;
				Set3Point.SetTarget(_3PtPkType, _3PtTarget, _3PtPointNo);
				Set3Point.Set3PointM();*/
				break;
			}
			case CMD_READ_3POINT_OFFSET:
			{
				break;
			}
			//{
			//	memcpy(&Mmi2Seq.Arg.Set3Point, &Set3PointOffset, sizeof(Set3PointOffset));
			//	break;
			//}
			case CMD_READ_FLIP1_VISION_RESULT:
			{
				break;
			}
		/*	{
				memcpy(&Mmi2Seq.Arg.Flip1VisionResult.Result, &Flip1VisionResult, sizeof(Flip1VisionResult));
				break;
			}*/
			case CMD_WRITE_FLIP1_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Flip1VisionResult, &Mmi2Seq.Arg.Flip1VisionResult.Result, sizeof(Flip1VisionResult));
				break;
			}*/
			case CMD_READ_FLIP2_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.Flip2VisionResult.Result, &Flip2VisionResult, sizeof(Flip2VisionResult));
				break;
			}*/
			case CMD_WRITE_FLIP2_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Flip2VisionResult, &Mmi2Seq.Arg.Flip2VisionResult.Result, sizeof(Flip2VisionResult));
				break;
			}*/
			case CMD_READ_PALLET1_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.Pallet1VisionResult.Result, &Pallet1VisionResult, sizeof(Pallet1VisionResult));
				break;
			}*/
			case CMD_WRITE_PALLET1_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Pallet1VisionResult, &Mmi2Seq.Arg.Pallet1VisionResult.Result, sizeof(Pallet1VisionResult));
				break;
			}*/
			case CMD_READ_PALLET2_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.Pallet2VisionResult.Result, &Pallet2VisionResult, sizeof(Pallet2VisionResult));
				break;
			}*/
			case CMD_WRITE_PALLET2_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Pallet2VisionResult, &Mmi2Seq.Arg.Pallet2VisionResult.Result, sizeof(Pallet2VisionResult));
				break;
			}*/
			case CMD_READ_FRONT_PICKER_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.FrontPkVisionResult.Result, &FrontPkVisionResult, sizeof(FrontPkVisionResult));
				break;
			}*/
			case CMD_WRITE_FRONT_PICKER_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&FrontPkVisionResult, &Mmi2Seq.Arg.FrontPkVisionResult.Result, sizeof(FrontPkVisionResult));
				break;
			}*/
			case CMD_READ_REAR_PICKER_RESULT:
			{
				break;
			}
		/*	{
				memcpy(&Mmi2Seq.Arg.RearPkVisionResult.Result, &RearPkVisionResult, sizeof(RearPkVisionResult));
				break;
			}*/
			case CMD_WRITE_REAR_PICKER_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&RearPkVisionResult, &Mmi2Seq.Arg.RearPkVisionResult.Result, sizeof(RearPkVisionResult));
				break;
			}*/
			case CMD_READ_GOOD_TRAY1_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.GoodTray1VisionResult.Result, &GoodTray1VisionResult, sizeof(GoodTray1VisionResult));
				break;
			}*/
			case CMD_READ_GOOD_TRAY2_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.GoodTray2VisionResult.Result, &GoodTray2VisionResult, sizeof(GoodTray2VisionResult));
				break;
			}*/
			case CMD_READ_REWORK_TRAY_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.ReworkTrayVisionResult.Result, &RewTrayVisionResult, sizeof(RewTrayVisionResult));
				break;
			}*/
			case CMD_READ_NG_TRAY_VISION_RESULT:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.NGTrayVisionResult.Result, &NGTrayVisionResult, sizeof(NGTrayVisionResult));
				break;
			}*/
			case CMD_READ_FLIP1_MAP:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.Flip1Map.Map, &Flip1Map, sizeof(Flip1Map));
				break;
			}*/
			case CMD_WRITE_FLIP1_MAP:
			{
				break;
			}
			/*{
				memcpy(&Flip1Map, &Mmi2Seq.Arg.Flip1Map.Map, sizeof(Flip1Map));
				break;
			}*/
			case CMD_READ_FLIP2_MAP:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.Flip2Map.Map, &Flip2Map, sizeof(Flip2Map));
				break;
			}*/
			case CMD_WRITE_FLIP2_MAP:
			{
				break;
			}
			/*{
				memcpy(&Flip2Map, &Mmi2Seq.Arg.Flip2Map.Map, sizeof(Flip2Map));
				break;
			}*/
			case CMD_READ_PALLET1_MAP:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.Pallet1Map.Map, &Pallet1Map, sizeof(Pallet1Map));
				break;
			}*/

			case CMD_WRITE_PALLET1_MAP:
			{
				break;
			}
			/*{
				memcpy(&Pallet1Map, &Mmi2Seq.Arg.Pallet1Map.Map, sizeof(Pallet1Map));
				break;
			}*/
			case CMD_READ_PALLET2_MAP:
			{
				break;
			}
			/*{
				memcpy(&Mmi2Seq.Arg.Pallet2Map.Map, &Pallet2Map, sizeof(Pallet2Map));
				break;
			}*/
			case CMD_WRITE_PALLET2_MAP:
			{
				break;
			}
			/*{
				memcpy(&Pallet2Map, &Mmi2Seq.Arg.Pallet2Map.Map, sizeof(Pallet2Map));
				break;
			}*/
			case CMD_READ_FRONT_PICKER_MAP:
			{
				break;
			}
			case CMD_WRITE_FRONT_PK_MAP:
			{
				break;
			}
			case CMD_READ_REAR_PICKER_MAP:
			{
				break;
			}
			case CMD_WRITE_REAR_PK_MAP:
			{
				break;
			}
			case CMD_READ_GOOD_TRAY1_MAP:
			{
				memcpy(&Mmi2Seq.Arg.GoodTray1Map.Map, &GoodTray1Map, sizeof(GoodTray1Map));
				break;
			}
			case CMD_WRITE_GOOD_TRAY1_MAP:
			{
				memcpy(&GoodTray1Map, &Mmi2Seq.Arg.GoodTray1Map.Map, sizeof(GoodTray1Map));
				break;
			}
			case CMD_READ_GOOD_TRAY2_MAP:
			{
				memcpy(&Mmi2Seq.Arg.GoodTray2Map.Map, &GoodTray2Map, sizeof(GoodTray2Map));
				break;
			}
			case CMD_WRITE_GOOD_TRAY2_MAP:
			{
				memcpy(&GoodTray2Map, &Mmi2Seq.Arg.GoodTray2Map.Map, sizeof(GoodTray2Map));
				break;
			}
			case CMD_READ_REWORK_TRAY_MAP:
			{
				memcpy(&Mmi2Seq.Arg.ReworkTrayMap.Map, &RewTrayMap, sizeof(RewTrayMap));
				break;
			}
			case CMD_WRITE_REWORK_TRAY_MAP:
			{
				memcpy(&RewTrayMap, &Mmi2Seq.Arg.ReworkTrayMap.Map, sizeof(RewTrayMap));
				break;
			}
			case CMD_READ_NG_TRAY_MAP:
			{
				memcpy(&Mmi2Seq.Arg.NGTrayMap.Map, &NGTrayMap, sizeof(NGTrayMap));
				break;
			}
			case CMD_WRITE_NG_TRAY_MAP:
			{
				memcpy(&NGTrayMap, &Mmi2Seq.Arg.NGTrayMap.Map, sizeof(NGTrayMap));
				break;
			}
			case CMD_WRITE_PK_CENTER_MOVE:
			{
				/*memcpy(&PkCenterMove, &Mmi2Seq.Arg.PkCenterMove, sizeof(PkCenterMove));
				PkCenterMoveM();*/
				break;
			}
			case CMD_WRITE_PK_CENTER_TRIGGER:
			{
				//GetPkCenterOffsetM();
				break;
			}
			case CMD_READ_FRONT_PK_CENTER_OFFSET:
			{
				memcpy(&Mmi2Seq.Arg.FrontPkCenterOffset, &FrontPkCenterOffset, sizeof(FrontPkCenterOffset));
				break;
			}
			case CMD_READ_REAR_PK_CENTER_OFFSET:
			{
				memcpy(&Mmi2Seq.Arg.RearPkCenterOffset, &RearPkCenterOffset, sizeof(RearPkCenterOffset));
				break;
			}
			case CMD_WRITE_PK_CENTER_AUTO_CAL:
			{
				/*memcpy(&PkCenterMove, &Mmi2Seq.Arg.PkCenterMove, sizeof(PkCenterMove));
				PkCenterAutoCalibrationM();*/
				break;
			}
			case CMD_PROGRAMEXIT:		// MMI Program is Exit...
				AfxGetMainWnd()->PostMessage(WM_CLOSE);
				break;
			default:
				Mmi2Seq.isack = false;
				SendToMmi = true;
				printf("default[%u]\n", Mmi2Seq.Command);
				break;
		}

		Seq2Mmi = Mmi2Seq;

		if ((uRtnCode = smemcomm.Send(&Seq2Mmi)) != true) {
			printf("\n  SEND COMMAND ERROR [%u] / E-CODE [%u]...\n", Mmi2Seq.Command, uRtnCode);
		}
	}
}

//------------------------------------------------------------------------
void CSeqMain::MMI_MessageMotorCommand(unsigned int cmdNo, int mtNo)
{
	/////////////////////////////////////////////
	switch (cmdNo)
	{
		case CMD_SERVO_ONOFF:
		{
			if (MTAxis[mtNo + 1]->IsServoOn) {
				MTAxis[mtNo + 1]->ServoOff();
				MTAxis[mtNo + 1]->CurPos = 99;
				printf("MTAxis[%d]->ServoOff()\n", mtNo + 1);
				LOG_TRACE("MTAxis[%d]->ServoOff()\n", mtNo + 1);
				// MTAxis[mtno + 1]->imrs = 0;
			}
			else {
				MTAxis[mtNo + 1]->ServoOn();
				MTAxis[mtNo + 1]->CurPos = 99;
			}
			break;
		}
		case CMD_SERVO_ALARM_CLEAR:
		{
			MTAxis[mtNo + 1]->SetAlarmClearOn();
			Sleep(150);
			MTAxis[mtNo + 1]->SetAlarmClearOff();
			break;
		}
		case CMD_READ_MOTORSTATUS: // Read Motor Status
		{
			if (MTAxis[mtNo + 1] != NULL)
			{
				Mmi2Seq.Arg.MotorStatus.Org = MTAxis[mtNo + 1]->IsORG;
				Mmi2Seq.Arg.MotorStatus.CW = MTAxis[mtNo + 1]->IsHWLimitCW;
				Mmi2Seq.Arg.MotorStatus.CCW = MTAxis[mtNo + 1]->IsHWLimitCCW;
				Mmi2Seq.Arg.MotorStatus.HOME = MTAxis[mtNo + 1]->imrs;
				Mmi2Seq.Arg.MotorStatus.Busy = MTAxis[mtNo + 1]->IsDriving;
				Mmi2Seq.Arg.MotorStatus.CurrentIndex = MTAxis[mtNo + 1]->CurPos;
				Mmi2Seq.Arg.MotorStatus.NextIndex = MTAxis[mtNo + 1]->NxtPos;
				Mmi2Seq.Arg.MotorStatus.ALM = MTAxis[mtNo + 1]->IsAlarm;

				Mmi2Seq.Arg.MotorStatus.SVON = MTAxis[mtNo + 1]->IsServoOn;
				Mmi2Seq.Arg.MotorStatus.NextPosition = (int)MTAxis[mtNo + 1]->NxtArrpos;

				Mmi2Seq.Arg.MotorStatus.dwServoAlarmCode = MTAxis[mtNo + 1]->dwServoAlarmCode;
				/*sprintf(MTAxis[mtNo+1]]->strServoAlarmName, "%s", "asdfasdfdsfdlk");
				strcpy(Mmi2Seq.Arg.MotorStatus.strServoAlarmName, MTAxis[mtNo+1]->strServoAlarmName);*/

				Mmi2Seq.Arg.MotorStatus.dServoLoadRatio = MTAxis[mtNo + 1]->dServoLoadRatio;

				if (MTAxis[mtNo + 1]->MotorType == 1) {	// servo
					if (MTAxis[mtNo + 1]->bCamType) {
						Mmi2Seq.Arg.MotorStatus.CurrentPosition = (int)(MTAxis[mtNo + 1]->ActualPosition / (8000. / 360.) + 0.5);
					}
					else {
						Mmi2Seq.Arg.MotorStatus.CurrentPosition = (int)MTAxis[mtNo + 1]->ActualPosition;
					}
				}
				if ((MTAxis[mtNo + 1]->MotorType == 2) || (MTAxis[mtNo + 1]->MotorType == 3)) {		// cool muscle or step
					if (MTAxis[mtNo + 1]->bCamType) {
						// 		double theta_deg,theta_rad;
						// 		theta_deg = (double)(pAxis->CommandPosition)*(360./1600.);
						// 		theta_rad = theta_deg*(PI/180.);
						// 		double c=(2.5*(1-cos(theta_rad)));
						// 		Mmi2Seq.Arg.MotorStatus.CurrentPosition = (int)(2.5*(1-cos(theta_rad))) * MTAxispAxis->MMI_PulseRate;
						Mmi2Seq.Arg.MotorStatus.CurrentPosition = (int)(MTAxis[mtNo + 1]->CommandPosition / (1600. / 360.) + 0.5);
					}
					else {
						Mmi2Seq.Arg.MotorStatus.CurrentPosition = (int)MTAxis[mtNo + 1]->ActualPosition;
					}
				}
			}
			break;
		}
		case CMD_MOTORSCONTINUE:
		{
			int dir = Mmi2Seq.Arg.MotorMove.iDir;
			int Speed = Mmi2Seq.Arg.MotorMove.uVel;
			JogMoveContinious(mtNo, Speed, dir);
			break;
		}
		case CMD_MOTORSRELATIVE: // Motor S-Curve Relative Move
		{
			int pos = Mmi2Seq.Arg.MotorMove.iPos;
			int Speed = Mmi2Seq.Arg.MotorMove.uVel;
			JogMoveRelative(mtNo, pos, Speed);
			break;
		}
		case CMD_MOTORINDEXMOVE:
		{
			int index = Mmi2Seq.Arg.MotorMove.uIdx;
			JogMoveIndex(mtNo, index);
			break;
		}
		case CMD_MOTORSTOP:
		{
			bit.JogCMove = 0;
			MTAxis[mtNo + 1]->MTEStop();
			break;
		}
		case CMD_WRITE_MOTORDATA: // Write Motor Data
		{
			memcpy(MTAxis[mtNo + 1]->PositionArray, Mmi2Seq.Arg.MotorData.uPos, sizeof(MTAxis[mtNo + 1]->PositionArray));
			memcpy(MTAxis[mtNo + 1]->SpeedArray, Mmi2Seq.Arg.MotorData.uVel, sizeof(MTAxis[mtNo + 1]->SpeedArray));
			memcpy(MTAxis[mtNo + 1]->AccelArray, MTAxis[mtNo + 1]->SpeedArray, sizeof(MTAxis[mtNo + 1]->SpeedArray));
			memcpy(MTAxis[mtNo + 1]->DecelArray, MTAxis[mtNo + 1]->SpeedArray, sizeof(MTAxis[mtNo + 1]->SpeedArray));

			MTAxis[mtNo + 1]->SpeedArray[0] = 100.0 * (double)MTAxis[mtNo + 1]->MMI_PulseRate;
			MTAxis[mtNo + 1]->PositionArray[0] = 100;

			//if (MTAxis[mtNo + 1] == MTFrontPkX) {
			//	FrontPkSetTriggerPosition();
			//}
			//if (MTAxis[mtNo + 1] == MTRearPkX) {
			//	RearPkSetTriggerPosition();
			//}
			break;
		}
		case CMD_READ_MOTORDATA: // Read Motor Data
		{
			memcpy(Mmi2Seq.Arg.MotorData.uPos, MTAxis[mtNo + 1]->PositionArray, sizeof(MTAxis[mtNo + 1]->PositionArray));
			memcpy(Mmi2Seq.Arg.MotorData.uVel, MTAxis[mtNo + 1]->SpeedArray, sizeof(MTAxis[mtNo + 1]->SpeedArray));
			Mmi2Seq.Arg.MotorData.HomeSpeed = 100;
			Mmi2Seq.Arg.MotorData.ZPhaseSpeed = 100;
			break;
		}
		case CMD_READ_MOTORCONFIG:
			break;
		case CMD_WRITE_MOTORCONFIG:
		{
			MTAxis[mtNo + 1]->MMI_PulseRate = Mmi2Seq.Arg.MotorCfg.uRate;
			MTAxis[mtNo + 1]->MMI_MaxVel = Mmi2Seq.Arg.MotorCfg.uMaxVel;
			MTAxis[mtNo + 1]->MMI_JogVel = Mmi2Seq.Arg.MotorCfg.uJogVel;
			MTAxis[mtNo + 1]->MMI_HomeVel = Mmi2Seq.Arg.MotorCfg.uHomeVel;
			MTAxis[mtNo + 1]->MMI_Accel = Mmi2Seq.Arg.MotorCfg.uAccel;
			MTAxis[mtNo + 1]->MMI_MotorType = Mmi2Seq.Arg.MotorCfg.uMotorType;
			MTAxis[mtNo + 1]->MMI_HomeLevel = Mmi2Seq.Arg.MotorCfg.uHomeLevel;
			MTAxis[mtNo + 1]->MMI_LimitLevel = Mmi2Seq.Arg.MotorCfg.uLimitLevel;
			MTAxis[mtNo + 1]->MMI_ServoOnLevel = Mmi2Seq.Arg.MotorCfg.uServoOnLevel;
			MTAxis[mtNo + 1]->MMI_AlarmLevel = Mmi2Seq.Arg.MotorCfg.uAlarmLevel;
			MTAxis[mtNo + 1]->MMI_InpUse = Mmi2Seq.Arg.MotorCfg.uInpUse;
			MTAxis[mtNo + 1]->MMI_MtrDir = Mmi2Seq.Arg.MotorCfg.uMtrDir;
			MTAxis[mtNo + 1]->MMI_EncDir = Mmi2Seq.Arg.MotorCfg.uEncDir;
			MTAxis[mtNo + 1]->MMI_Enc_Type = Mmi2Seq.Arg.MotorCfg.uEncoderType;
			MTAxis[mtNo + 1]->MaxSpeed = MTAxis[mtNo + 1]->MMI_MaxVel * (double)MTAxis[mtNo + 1]->MMI_PulseRate;

			//  printf("pAxis->MMI_PulseRate=%d\n",	mtno+1, pAxis->MMI_PulseRate);
			// 	pAxis->MaxSpeed = pAxis->MMI_MaxVel;
			// 	pAxis->SetMaxSpeed(pAxis->MaxSpeed);// 

			// 	RtPrintf("MTAxis[%d]->MMI_MaxVel=%d\n",		mtno+1, MTAxis[mtno+1]->MMI_MaxVel);
			// 	RtPrintf("MTAxis[%d]->MMI_JogVel=%d\n",		mtno+1, MTAxis[mtno+1]->MMI_JogVel);
			// 	RtPrintf("MTAxis[%d]->MMI_HomeVel=%d\n",		mtno+1, MTAxis[mtno+1]->MMI_HomeVel);
			// 	RtPrintf("MTAxis[%d]->MMI_Accel=%d\n",		mtno+1, MTAxis[mtno+1]->MMI_Accel);
			// 	RtPrintf("MTAxis[%d]->MMI_MotorType=%d\n",	mtno+1, MTAxis[mtno+1]->MMI_MotorType);
			// 	RtPrintf("MTAxis[%d]->MMI_HomeLevel=%d\n",    mtno+1, MTAxis[mtno+1]->MMI_HomeLevel);
			// 	RtPrintf("MTAxis[%d]->MMI_LimitLevel=%d\n",   mtno+1, MTAxis[mtno+1]->MMI_LimitLevel);
			// 	RtPrintf("MTAxis[%d]->MMI_ServoOnLevel=%d\n", mtno+1, MTAxis[mtno+1]->MMI_ServoOnLevel);
			// 	RtPrintf("MTAxis[%d]->MMI_AlarmLevel=%d\n",   mtno+1, MTAxis[mtno+1]->MMI_AlarmLevel);
			// 	RtPrintf("MTAxis[%d]->MMI_InpUse=%d\n",		mtno+1, MTAxis[mtno+1]->MMI_InpUse);
			// 	RtPrintf("MTAxis[%d]->MMI_MtrDir=%d\n",		mtno+1, MTAxis[mtno+1]->MMI_MtrDir);
			// 	RtPrintf("MTAxis[%d]->MMI_EncDir=%d\n",		mtno+1, MTAxis[mtno+1]->MMI_EncDir);
			// 	RtPrintf("MTAxis[%d]->MMI_Enc_Type=%d\n",		mtno+1, MTAxis[mtno+1]->MMI_Enc_Type);

			break;
		}
		default:
			break;
	}
}

//------------------------------------------------------------------------
void CSeqMain::MMI_MessageMotorCmdHomeFunc(unsigned int cmdNo, int mtNo)
{
	if (!MTAxis[mtNo + 1]->IsServoOn || bTenKeyJog) return;

	switch (cmdNo)
	{
		case CMD_SERVO_HOME:
		{
			if (MTAxis[mtNo + 1] == MTStageX) {
				MTStageXHomeM();
			}
			else if (MTAxis[mtNo + 1] == MTStageY) {
				MTStageYHomeM();
			}
			else if (MTAxis[mtNo + 1] == MTStageZ) {
				MTStageZHomeM();
			}
			break;
		}
		default:
			break;
	}
}