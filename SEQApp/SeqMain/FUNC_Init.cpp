#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"
#include "..\Tools\TinyXML\tinyxml2.h"


using namespace tinyxml2;
//////////////////////////////////////////////////////////////////////////
void CSeqMain::Load_Motor_Parameter(void)
{
	int nMotorNo;  //현재 처리 중인 **모터 번호(Motor Number)**를 저장할 정수형 변수를 선언합니다.
	tinyxml2::XMLDocument doc;  //TinyXML-2의 핵심 클래스인 XMLDocument 객체를 생성합니다. 이 객체가 XML 파일 전체를 메모리에 로드하고 관리합니다 
	doc.LoadFile("C:\\WORK\\CONFIG\\MotorConfig.xml");	//지정된 경로에서 "MotorConfig.xml" 파일을 읽어 들여 doc 객체에 파싱(parsing)합니다.

	tinyxml2::XMLElement* pRoot = doc.RootElement(); //XML 문서의 **최상위 엘리먼트 (Root Element)**를 가져옵니다. 예를 들어, XML 파일이 <CONFIG>...</CONFIG>로 시작한다면, pRoot는 <CONFIG> 엘리먼트를 가리킵니다. 
	tinyxml2::XMLElement* cfg = pRoot->FirstChildElement("MOTOR");  //루트 엘리먼트의 자식 중에서 태그 이름이 "MOTOR"인 첫 번째 엘리먼트를 찾아서 cfg 포인터에 할당합니다. 이 코드는 일반적으로 모터 설정의 반복 시작점을 찾습니다.
	for (tinyxml2::XMLElement* ele = cfg; ele != NULL; ele = ele->NextSiblingElement()) //반복 시작 (ele = cfg): 반복 변수 ele가 첫 번째 "MOTOR" 엘리먼트를 가리키며 시작합니다.

		/*반복 조건(ele != NULL) : 현재 엘리먼트 포인터가 NULL이 아니면(즉, 다음 엘리먼트가 존재하면) 계속 반복합니다.

		반복 증감(ele = ele->NextSiblingElement()) : 현재 "MOTOR" 엘리먼트와 * *동일한 레벨(Sibling) * *에 있는 다음 엘리먼트를 찾아서 ele에 할당합니다. 
		* *NextSiblingElement() * *는 태그 이름을 지정하지 않았으므로, 다음 모든 엘리먼트를 찾지만, cfg가 이미 "MOTOR" 엘리먼트이므로, 
		이 반복문은 보통 파일 내의 모든 "MOTOR" 블록을 순서대로 처리하게 됩니다.*/
	{
		nMotorNo = ele->IntAttribute("NO");//현재 <MOTOR> 엘리먼트의 NO 속성(Attribute) 값을 정수로 읽어와 nMotorNo에 저장합니다. 이 값이 현재 설정할 모터의 고유 번호입니다.
		if (MTAxis[nMotorNo + 1] != NULL) {//MTAxis는 모터 축 객체(포인터 배열)로 추정됩니다. nMotorNo + 1 인덱스에 해당하는 모터 객체가 유효한지 (NULL이 아닌지) 확인하여, 객체가 초기화된 경우에만 설정 값을 적용합니다. (인덱스가 +1인 것은 프로그래밍 관례상 모터 번호가 0부터 시작하지만 배열 인덱스는 1부터 시작할 수 있기 때문입니다.)
			MTAxis[nMotorNo + 1]->bCwLimitLevel = ele->IntAttribute("PEndL"); //정방향 리미트 센서 레벨 (Positive End Limit Level) 속성 **PEndL**의 값을 읽어와 모터 객체의 bCwLimitLevel 멤버 변수에 설정합니다.
			MTAxis[nMotorNo + 1]->bCCwLimitLevel = ele->IntAttribute("NEndL");//역방향 리미트 센서 레벨 (Negative End Limit Level) 속성 **NEndL**의 값을 읽어와 bCCwLimitLevel에 설정합니다.
			MTAxis[nMotorNo + 1]->bServoOnLevel = ele->IntAttribute("SONL");//서보 On 신호 레벨 (Servo ON Level) 속성 **SONL**의 값을 설정합
			MTAxis[nMotorNo + 1]->bAlarmLevel = ele->IntAttribute("AlmL");//알람 신호 레벨 (Alarm Level) 속성 **AlmL**의 값을 설정합니다.
			MTAxis[nMotorNo + 1]->bInpLevel = ele->IntAttribute("InpL");//위치 결정 완료 신호 레벨 (In-Position Level) 속성 **InpL**의 값을 설정합니다.
			MTAxis[nMotorNo + 1]->bInpEnable = ele->IntAttribute("InpE");//위치 결정 완료 신호 사용 여부 (In-Position Enable) 속성 **InpE**의 값을 설정합니다.
			MTAxis[nMotorNo + 1]->nPulseOutM = ele->IntAttribute("PulseM");//출력 펄스 모드 (Pulse Out Mode) 속성 **PulseM**의 값을 설정합니다.
			MTAxis[nMotorNo + 1]->nEncDir = ele->IntAttribute("EncDir");//엔코더 방향 (Encoder Direction) 속성 **EncDir**의 값을 설정합니다.
			MTAxis[nMotorNo + 1]->nEncType = ele->IntAttribute("EncType");//엔코더 타입 (Encoder Type) 속성 **EncType**의 값을 설정합니다.
			MTAxis[nMotorNo + 1]->nMotorType = ele->IntAttribute("MotorType");//모터 타입 (Motor Type) 속성 **MotorType**의 값을 설정합니다.
			MTAxis[nMotorNo + 1]->nSensorType = ele->IntAttribute("SensorType");//센서 타입 (Sensor Type) 속성 **SensorType**의 값을 설정합니다.
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void CSeqMain::InitMotor(void)
{
	MTStageX = new CAjinMotor(0, 0);
	MTStageY = new CAjinMotor(1, 1);
	MTStageZ = new CAjinMotor(2, 2);

	MTAxis[1] = MTStageX;
	MTAxis[2] = MTStageY;
	MTAxis[3] = MTStageZ;

	// Load Motor Config data
	Load_Motor_Parameter();

	totalAxisCnt = 3;

	Sleep(100);

	for (int j = 1; j <= totalAxisCnt; j++) {
		memset(MTAxis[j]->SpeedArray, 0, sizeof(MTAxis[j]->SpeedArray));
		memset(MTAxis[j]->PositionArray, 0, sizeof(MTAxis[j]->PositionArray));
		MTAxis[j]->SpeedArray[0] = 300;  // home speed
		MTAxis[j]->PositionArray[0] = 30; // z phase speed

		MTAxis[j]->SetHWLimitMode(MTAxis[j]->bCwLimitLevel, MTAxis[j]->bCCwLimitLevel);
		Sleep(10);
		MTAxis[j]->SetSWLimitMode(DISABLE);

		MTAxis[j]->HomeSpeed = &MTAxis[j]->SpeedArray[0];
		if (MTAxis[j]->nEncDir == 0) {
			MTAxis[j]->SetEncoderInputMethos(ObverseSqr4Mode);
		}
		else if (MTAxis[j]->nEncDir == 1) {
			MTAxis[j]->SetEncoderInputMethos(ReverseSqr4Mode);
		}
		MTAxis[j]->SetPulseMode(MTAxis[j]->nPulseOutM);
		Sleep(10);
		MTAxis[j]->SetMoveRatio();
		//		MTAxis[j]->SetServoOnLogic(MTAxis[j]->bServoOnLevel);
		Sleep(10);
		MTAxis[j]->SetInpositionMode(MTAxis[j]->bInpLevel, MTAxis[j]->bInpEnable);
		//		MTAxis[j]->SetCommandPosition(0); // internal program encoder count
		//		MTAxis[j]->SetActualPosition(0);  // actual program encoder count
		//		MTAxis[j]->SetAlarmEnable(MTAxis[j]->bAlarmLevel);
		Sleep(10);

		MTAxis[j]->SetSignalStop(EMERGENCY_STOP, UNUSED);
		MTAxis[j]->SetHomeSignalLevel(HIGH);

		MTAxis[j]->SensorType = MTAxis[j]->nSensorType;

		MTAxis[j]->ostart = 1;
		MTAxis[j]->Accel = 15000;
		MTAxis[j]->Decel = 15000;
		MTAxis[j]->Jerk = 24;
		MTAxis[j]->Speed = 1000;
		MTAxis[j]->DfltWorking = 1;
		MTAxis[j]->fDoHome = false;
		MTAxis[j]->fDriving = false;
		MTAxis[j]->fMotorPause = 0;
		MTAxis[j]->InitSpeed = 100; //250;
		MTAxis[j]->SetInitSpeed(MTAxis[j]->InitSpeed);
		MTAxis[j]->SetMaxSpeed(80 * 10000);	// 20mm pitch, 3000rpm, 1turn=>8000 pulse인 경우 1mm=400pulse
		MTAxis[j]->SpeedDevide = 10;			// 50rps =>50*20mm/s => 1000mm/s => 1000*400 pps = 400kpps
		MTAxis[j]->MinMovingTime = 150;
		MTAxis[j]->omove = 0;
		MTAxis[j]->CurPos = 299;
		MTAxis[j]->NxtPos = 299;
		MTAxis[j]->CurArrpos = 0;
		MTAxis[j]->NxtArrpos = 0;
		MTAxis[j]->imrs = 0;

		MTAxis[j]->IsAlarm = 0;
		MTAxis[j]->IsDRVRDY = 1;
		MTAxis[j]->isend = 0;
		MTAxis[j]->IsHWLimitCCW = 0;
		MTAxis[j]->IsHWLimitCW = 0;
		MTAxis[j]->IsDriving = 0;
		MTAxis[j]->IsInposition = 1;
		MTAxis[j]->IsServoOn = 0;
		MTAxis[j]->IsStop = 1;
		MTAxis[j]->IsZPhase = 0;
		MTAxis[j]->IsORG = 0;
		MTAxis[j]->idrvalm = 0;
		MTAxis[j]->EncoderType = MTAxis[j]->nEncType;
		MTAxis[j]->MotorType = MTAxis[j]->nMotorType;
		MTAxis[j]->bCamType = 0;
		MTAxis[j]->fMotorHome = 0;

		MTAxis[j]->SetServoLoadRatio(0x02);
		MTAxis[j]->SetActualPosition(0);
	}
	//AxmSignalSetLimit(0, SLOWDOWN_STOP, LOW, LOW);
	MTStageX->DfltWorking = STAGE_X_WAIT;
	MTStageY->DfltWorking = STAGE_Y_WAIT;
	MTStageZ->DfltWorking = STAGE_Z_UP;
	
	//////////////////////////////////////////////////////////////////////////
	int k;
	for (k = 1; k <= totalAxisCnt; k++) {
		MTAxis[k]->SetAlarmClearOff();
	}
	Sleep(150);

	for (k = 1; k <= totalAxisCnt; k++) {
		MTAxis[k]->ServoOff();
	}
	Sleep(150);

	for (k = 1; k <= totalAxisCnt; k++) {
		MTAxis[k]->SetAlarmClearOn();
	}
	Sleep(150);
	for (k = 1; k <= totalAxisCnt; k++) {
		MTAxis[k]->SetAlarmClearOff();
	}
	Sleep(150);
	for (k = 1; k <= totalAxisCnt; k++) {
		MTAxis[k]->ServoOn();
	}

	//_ON(oMCPower);
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::InitIO(void)
{
	AjinIO = new CAjinIO;
	bit.TestMode = AjinIO->Isct2dMode();

	AjinAIO = new CAjinAIO;
	AjinAIO->InitCard();
	// 	aio->ExtTriggerStart();

	AjinCounter = new CAjinCounter();
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::InitMotorBase(void)
{
	AjinBase = new CAjinBase;
	AjinBase->InitBase();
	bit.TestMode = AjinBase->Isct2dMode();
}

void CSeqMain::InitMemory(void)
{
	ZeroMemory(&bit, sizeof(_bit));
	ZeroMemory(&dm, sizeof(_dm));
	printf("\n Memory Initialize....\n");
}

void CSeqMain::InitSequence(void)
{
	//pgm_check.Check();

	pFileLog = new CFileLog;

	InitMotorBase();
	InitIO();
	InitMotor();

	InitMemory();
	InitComm();

	Key10.SetKeyDigit(TKeyDigit::KEYDIGIT3);

	bTenKeyJog = FALSE;

	tm_gUPH.SetTime();
	tm_gTPH.SetTime();
	/*_ON(oLight);
	_ON(oEmptyLight);
	_ON(oDoorOpen);
	_ON(oEmptyDoorOpen);*/

	curvePallet = new BSpline();
	memset(LotInfo.strLotID, 0, sizeof(LotInfo.strLotID));

	strcpy(MachineStatus.strDeviceName, "no_device");

	bit.MotorTunning = 0;
	bit.AutoRun = 0;

	bit.PAutoStop = 0;
	bit.AllHome = 0;
	bit.DryRun = 0;
	bit.AllDry = 0;
	bit.BuzzerOn = 0;
	bit.NewBuzzer = 0;
	bit.AllCycleStop = 0;
	bit.BeforeEmer = 0;
	bit.LotEnd = 0;
	bit.LotEndMem = 0;
	bit.TestMode = 0;
	bit.AllReset = 0;
	bit.TenkeyJogMove = 0;
	bit.LotEndCntClear = 1;
	bit.DeviceDataReceived = 0;


	MachineStatus.SpongeCleanCnt = 0;
	MachineStatus.WaterJetWaterCleanCnt = 0;
	MachineStatus.WaterJetAirCleanCnt = 0;
	MachineStatus.SawPkFlipY1AirClenaCnt = 0;
	MachineStatus.SawPkFlipY2AirClenaCnt = 0;
	MachineStatus.FlipY1AirCleanCnt = 0;
	MachineStatus.FlipY2AirCleanCnt = 0;
	MachineStatus.PalletY1AirCleanCnt = 0;
	MachineStatus.PalletY2AirCleanCnt = 0;

	WorkPallet = PALLETY1;
	WorkTray = GOOD_TRAY1;

	fill(FrontPkVisionResult, FrontPkVisionResult + 10, TVR_EMPTY);
	fill(FrontPkOffsetX, FrontPkOffsetX + 10, 0);
	fill(FrontPkOffsetY, FrontPkOffsetY + 10, 0);
	fill(FrontPkOffsetT, FrontPkOffsetT + 10, 0);
	fill(RearPkVisionResult, RearPkVisionResult + 10, TVR_EMPTY);
	fill(RearPkOffsetX, RearPkOffsetX + 10, 0);
	fill(RearPkOffsetY, RearPkOffsetY + 10, 0);
	fill(RearPkOffsetT, RearPkOffsetT + 10, 0);

	ZeroMemory(bAlarmCheck, sizeof(bAlarmCheck));
	
	bit.Comm1PacketReceived = 0;
	bit.Comm2PacketReceived = 0;

	memset(&V1RxData, 0x00, sizeof(VISION_RX_DATA));
	memset(&V2RxData, 0x00, sizeof(VISION_RX_DATA));
	memset(&V3RxData, 0x00, sizeof(VISION_RX_DATA));
}

void CSeqMain::ObjectDelete(void)
{
	delete MTStageX;
	delete MTStageY;
	delete MTStageZ;

	if (curvePallet != NULL)	delete curvePallet;
	if (AjinBase != NULL)		delete AjinBase;
	if (AjinIO != NULL)			delete AjinIO;
	if (AjinAIO != NULL)		delete AjinAIO;
	if (AjinCounter != NULL)	delete AjinCounter;
	if (pFileLog != NULL)		delete pFileLog;
}
