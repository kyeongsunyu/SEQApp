#include "..\pch.h"
#include "..\SEQAppDlg.h"
#include "..\SeqMain\CLASS_Main.h"
//#include "..\Tools\Spline\Bezier.h"
//#include "..\Tools\Spline\BSpline.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
void CSeqMain::SetPalletBegier(void)
{
	curvePallet->set_steps(100); // generate 100 interpolate points
	
	// Vector(x,y,z)
	// x : analog output digital value
	// y : measured pallet vacuum pascal value
	// z : always 0
	curvePallet->set_steps(100); // generate 100 interpolate points between the last 4 way points
	curvePallet->add_way_point(Vector(0, 0, 0));
	curvePallet->add_way_point(Vector(2047, 0, 0));		// 12mA
	curvePallet->add_way_point(Vector(2303, 0, 0));		// 13mA
	curvePallet->add_way_point(Vector(2559, 0, 0));		// 14mA
	curvePallet->add_way_point(Vector(2687, 10, 0));		// 14.5mA
	curvePallet->add_way_point(Vector(2815, 20, 0));		// 15mA
	curvePallet->add_way_point(Vector(2943, 22.5, 0));	// 15.5mA
	curvePallet->add_way_point(Vector(3071, 25, 0));		// 16mA
	curvePallet->add_way_point(Vector(3199, 27.5, 0));	// 16.5mA
	curvePallet->add_way_point(Vector(3327, 50, 0));		// 17mA
	curvePallet->add_way_point(Vector(3455, 60, 0));		// 17.5mA
	curvePallet->add_way_point(Vector(3583, 70, 0));		// 18mA
	curvePallet->add_way_point(Vector(3711, 71.5, 0));	// 18.5mA
	curvePallet->add_way_point(Vector(3839, 73, 0));		// 19mA
	curvePallet->add_way_point(Vector(3967, 90.5, 0));	// 19.5mA
	curvePallet->add_way_point(Vector(4095, 108, 0));	// 20mA

	std::cout << "nodes: " << curvePallet->node_count() << std::endl;
	std::cout << "total length: " << curvePallet->total_length() << std::endl;
	for (int i = 0; i < curvePallet->node_count(); ++i) {
		std::cout << "node #" << i << ": " << curvePallet->node(i).toString() << " (length so far: " << curvePallet->length_from_starting_point(i) << ")" << std::endl;
	}
	//std::vector<Vector> vtNode;
	//vtNode = curvePallet->Getnode();
	//std::vector<Vector>::iterator itr;
	//double KPA = 3.3;
	//itr = find_if(vtNode.begin(), vtNode.end(), [KPA](Vector& k) {return ((KPA - 0.2 < k.y) && (k.y < KPA + 0.2));	});
	//if (itr != vtNode.end()) {
	//	double digitVal = itr->x;
	//	std::cout << "itr->x" << itr->x << std::endl;
	//}
	//delete curve;
}


UINT CSeqMain::SEQ_Main_Thread(LPVOID param)
{
	/*Windows는 실시간 OS(RTOS)가 아니기 때문에, 제어 루프가 다른 윈도우 작업(업데이트, 
    마우스 움직임 등)에 밀리지 않도록 프로세스 우선순위를 최상위로 올렸습니다.이는 장비 제어에서 매우 중요한 설정입니다.*/
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS); 

	//scantime(한 루프가 도는 데 걸리는 시간)을 마이크로초($\mu s$) 단위로 정밀하게 측정하고 있습니다. 장비의 응답 속도를 모니터링하기 위한 용도입니다.
	QueryPerformanceFrequency(&sysfreq);

	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	CSEQAppDlg* pMain = (CSEQAppDlg*)param;
	
	printf("Sequence Start\n");

	sprintf(strFileLog, "%s", "Sequence Start");
	LOG_TRACE(strFileLog);

	tm_gScanDelay.SetTime();

	//seqMain->GetNVMMF();

	dm.SystemInitialize = 1;
	bit.AllDry = 0;

	while (!seqMain->m_bSeqExit) //이 루프는 while문을 통해 무한히 반복되며, 각 단계가 순차적으로 실행됩니다.
	{
		bool ret = QueryPerformanceCounter(&st);
		seqMain->Read_All(); //1. 센서/입력 정보 갱신
		seqMain->TenKeyProcess();
		seqMain->MotorSafetyFunction();
		seqMain->Sequence();//장비 상태 결정 (State Machine)
		seqMain->Write_All(); //결정된 상태를 실제 하드웨어로 출력

		seqMain->SetNVMMF();
		Sleep(1); //Sleep(1)은 CPU 점유율이 100%가 되는 것을 막아주지만, Windows 환경에서 실제로는 약 1ms~15ms 사이의 불규칙한 대기 시간을 가질 수 있습니다.
//		WaitForSingleObject(pMain->m_pThread_SeqMain, 1);
//		seqMain->Wait(1000);	
		double scantime = tm_gScanDelay.GetTimeDiffmS();
		dm.scantime = (DWORD)(scantime * 1000.);
		//if (scantime > 5) {
		//	printf("Main Seq. scantime = % f(ms)\n", scantime);
		//}
		tm_gScanDelay.SetTime();
	}
	
	AjinCounter->TriggerOut(0, FALSE);
	AjinCounter->TriggerDisable(0);

	AjinCounter->TriggerOut(1, FALSE);
	AjinCounter->TriggerDisable(1);

	seqMain->OffAllOutput();
	printf("Sequence Thread Exit\n");

	sprintf(strFileLog, "%s", "Sequence Thread Exit");
	LOG_TRACE(strFileLog);
	return 101;
}
