#include "..\pch.h"
#include "..\SEQAppDlg.h"
#include "..\SeqMain\CLASS_Main.h"


//////////////////////////////////////////////////////////////////////////
//HMI(Human Machine Interface) 또는 GUI 프로그램과 하드웨어 제어부(Sequence) 사이의 통신을 담당하는 전용 쓰레드입니다.
//SEQ_Main_Thread가 장비의 물리적인 움직임을 담당한다면, 이 쓰레드는 사용자의 명령을 전달받고 장비의 상태를 화면에 뿌려주는 데이터 통로 역할을 합니다.
UINT CSeqMain::MMI_Thread(void* pArg)
{
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	CSEQAppDlg* pMain = (CSEQAppDlg*)pArg;

	// SHARED MEMORY COMMUNICATION
	while (!seqMain->m_bSeqExit) {
		//독립된 통신 루프: MMI_MessageCommunication()을 별도의 쓰레드에서 돌림으로써, 
		// 통신 지연(Latency)이 발생하더라도 메인 시퀀스(SEQ_Main_Thread)의 스캔 타임에 영향을 주지 않도록 설계되었습니다.
		seqMain->MMI_MessageCommunication();
		Sleep(1);
//		WaitForSingleObject(pMain->m_pThread_SeqMMI, 1);
	}
	printf("MMI Thread Exit\n");

	sprintf(strFileLog, "%s", "MMI Thread Exit");
	LOG_TRACE(strFileLog);

	return 201;
}