#include "..\pch.h"
#include "..\SEQAppDlg.h"
#include "..\SeqMain\CLASS_Main.h"


//////////////////////////////////////////////////////////////////////////
UINT CSeqMain::SEQ_Motion_Thread1(LPVOID param)
{
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	CSEQAppDlg* pMain = (CSEQAppDlg*)param;

	while (!seqMain->m_bSeqExit)
	{
		seqMain->AjinMotorStatus(1, 3);
		Sleep(1);
//		WaitForSingleObject(pMain->m_pThread_SeqMotion1, 1);
//		seqMain->Wait(1000);
	}
	printf("Motion Thread1 Exit\n");

	sprintf(strFileLog, "%s", "Motion Thread1 Exit");
	LOG_TRACE(strFileLog);

	return 301;
}

//UINT CSeqMain::SEQ_Motion_Thread2(LPVOID param)
//{
//	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
//
//	CSeqMain* seqMain = CSeqMain::GetInstance();
//	assert(seqMain != nullptr);
//
//	CSEQAppDlg* pMain = (CSEQAppDlg*)param;
//
//	while (!seqMain->m_bSeqExit)
//	{
//		seqMain->AjinMotorStatus(9, 16);
//		Sleep(1);
////		WaitForSingleObject(pMain->m_pThread_SeqMotion2, 1);
////		seqMain->Wait(1000);
//	}
//	printf("Motion Thread2 Exit\n");
//
//	sprintf(strFileLog, "%s", "Motion Thread2 Exit");
//	LOG_TRACE(strFileLog);
//
//	return 302;
//}
//
//UINT CSeqMain::SEQ_Motion_Thread3(LPVOID param)
//{
//	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
//
//	CSeqMain* seqMain = CSeqMain::GetInstance();
//	assert(seqMain != nullptr);
//
//	CSEQAppDlg* pMain = (CSEQAppDlg*)param;
//
//	while (!seqMain->m_bSeqExit)
//	{
//		seqMain->AjinMotorStatus(17, 24);
//		Sleep(1);
////		WaitForSingleObject(pMain->m_pThread_SeqMotion3, 1);
////		seqMain->Wait(1000);
//	}
//	printf("Motion Thread3 Exit\n");
//
//	sprintf(strFileLog, "%s", "Motion Thread3 Exit");
//	LOG_TRACE(strFileLog);
//
//	return 303;
//}
//
//UINT CSeqMain::SEQ_Motion_Thread4(LPVOID param)
//{
//	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
//
//	CSeqMain* seqMain = CSeqMain::GetInstance();
//	assert(seqMain != nullptr);
//
//	CSEQAppDlg* pMain = (CSEQAppDlg*)param;
//
//	while (!seqMain->m_bSeqExit)
//	{
//		seqMain->AjinMotorStatus(25, 32);
//		Sleep(1);
////		WaitForSingleObject(pMain->m_pThread_SeqMotion2, 1);
////		seqMain->Wait(1000);
//	}
//	printf("Motion Thread2 Exit\n");
//
//	sprintf(strFileLog, "%s", "Motion Thread2 Exit");
//	LOG_TRACE(strFileLog);
//
//	return 304;
//}
//
//UINT CSeqMain::SEQ_Motion_Thread5(LPVOID param)
//{
//	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
//
//	CSeqMain* seqMain = CSeqMain::GetInstance();
//	assert(seqMain != nullptr);
//
//	CSEQAppDlg* pMain = (CSEQAppDlg*)param;
//
//	while (!seqMain->m_bSeqExit)
//	{
//		seqMain->AjinMotorStatus(33, 40);
//		Sleep(1);
////		WaitForSingleObject(pMain->m_pThread_SeqMotion5, 1);
////		seqMain->Wait(1000);
//	}
//	printf("Motion Thread5 Exit\n");
//
//	sprintf(strFileLog, "%s", "Motion Thread5 Exit");
//	LOG_TRACE(strFileLog);
//
//	return 305;
//}
//
//UINT CSeqMain::SEQ_Motion_Thread6(LPVOID param)
//{
//	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
//
//	CSeqMain* seqMain = CSeqMain::GetInstance();
//	assert(seqMain != nullptr);
//
//	CSEQAppDlg* pMain = (CSEQAppDlg*)param;
//
//	while (!seqMain->m_bSeqExit)
//	{
//		seqMain->AjinMotorStatus(41, 45);
//		Sleep(1);
////		WaitForSingleObject(pMain->m_pThread_SeqMotion5, 1);
////		seqMain->Wait(1000);
//	}
//	printf("Motion Thread6 Exit\n");
//
//	sprintf(strFileLog, "%s", "Motion Thread6 Exit");
//	LOG_TRACE(strFileLog);

//	return 305;
//}