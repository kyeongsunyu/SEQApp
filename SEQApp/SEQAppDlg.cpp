
// SEQAppDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SEQApp.h"
#include "SEQAppDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
//#include "CLASS_Main.h"
//#include "DEFINE_GV.h"
//#include "DEFINE_Macro.h"
//#include "DEFINE_WinMsg.h"

#include "SeqMain\CLASS_Main.h"
#include "SeqMain\DEFINE_GVX.h"
#include "SeqMain\Define\DEFINE_Macro.h"
#include "SeqMain\Define\DEFINE_WinMsg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern UINT SERVER_SOCKET_Thread(void* pArg);
extern void WinSockInitialize();
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSEQAppDlg 대화 상자



CSEQAppDlg::CSEQAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEQAPP_DIALOG, pParent), h_MainThreadEvent(nullptr), m_bShowStatus(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	CSeqMain* pSeqMain = CSeqMain::GetInstance();
	assert(pSeqMain != nullptr);

	bool bret = pSeqMain->LevelUp_Privileges();
}

CSEQAppDlg::~CSEQAppDlg()
{
	//CSeqMain* seqMain = CSeqMain::GetInstance();
	//assert(seqMain != nullptr);

	//seqMain->ShowConsoleWindow();

	//CloseSequence();
}

void CSEQAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSEQAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_APP_LINK_REQ, OnLinkTestRequest)
	ON_MESSAGE(WM_TRAYICON_MSG, TrayIconMsg)
	ON_WM_DESTROY()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CSEQAppDlg 메시지 처리기

BOOL CSEQAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetWindowText(L"SEQApp");
	RegistTrayIcon();
	RunSequence();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSEQAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSEQAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSEQAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CSEQAppDlg::RegistTrayIcon()
{
	NOTIFYICONDATA  nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd; // 메인 윈도우 핸들
	nid.uID = IDR_MAINFRAME;  // 아이콘 리소스 ID
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; // 플래그 설정
	nid.uCallbackMessage = WM_TRAYICON_MSG; // 콜백메시지 설정
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); // 아이콘 로드
	TCHAR strTitle[256];
	GetWindowText(strTitle, 256); // 캡션바에 출력된 문자열 얻음
	lstrcpy(nid.szTip, strTitle);
	
	Shell_NotifyIcon(NIM_ADD, &nid);
	SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
	m_bShowStatus = false;
}

void CSEQAppDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	seqMain->ShowConsoleWindow();

	CloseSequence();

	if (m_bShowStatus) // 현재 트레이 아이콘으로 설정되었는지 확인
	{
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd; // 메인 윈도우 핸들
		nid.uID = IDR_MAINFRAME;

		// 작업 표시줄(TaskBar)의 상태 영역에 아이콘을 삭제한다.
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
}

LRESULT CSEQAppDlg::TrayIconMsg(WPARAM wParam, LPARAM lParam)
{
	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	if (lParam == WM_LBUTTONDBLCLK) {
	//	ShowWindow(SW_SHOW);

		seqMain->ShowConsoleWindow();
		m_bShowStatus = true;
	}
	else if (lParam == WM_RBUTTONDBLCLK) {
		seqMain->ShowConsoleWindow();
	}
	else if (lParam == WM_RBUTTONDOWN) {
		seqMain->HideConsoleWindow();
	}
	return 0L;
}

void CSEQAppDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);

	if (m_bShowStatus == true) {
		lpwndpos->flags |= SWP_SHOWWINDOW;
	}
	else {
		lpwndpos->flags &= ~SWP_SHOWWINDOW;
	}
}

afx_msg LRESULT	CSEQAppDlg::OnLinkTestRequest(WPARAM wParam, LPARAM lParam)
{
	try
	{
		CSeqMain* seqMain = CSeqMain::GetInstance();
		assert(seqMain != nullptr);

		seqMain->SendPostMessage(WM_APP_LINK_RSP, MMI_MODULE);
		return 0;
	}
	catch (exception ex)
	{
		return 0;
	}
}

BOOL CSEQAppDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	COPYDATASTRUCT* receiveData = new COPYDATASTRUCT();
	memset(receiveData, 0x00, sizeof(COPYDATASTRUCT));
	memcpy(receiveData, pCopyDataStruct, sizeof(COPYDATASTRUCT));

	SEQ_RSP seq_rsp;
	memset(&seq_rsp, 0x00, sizeof(SEQ_RSP));

	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	switch (receiveData->dwData)
	{
	case WM_SEQ_EXIT_REQ:
	{
		SEQ_EXIT seq_exit;
		memset(&seq_exit, 0x00, sizeof(SEQ_EXIT));
		memcpy(&seq_exit, (SEQ_EXIT*)receiveData->lpData, sizeof(SEQ_EXIT));
		if (seq_exit.bExit) {
			PostMessage(WM_CLOSE);
		}
	}
		break;
	case WM_SEQ_OPERATION_REQ:
	{	
		SEQ_OPERATION seq_operation;
		memset(&seq_operation, 0x00, sizeof(SEQ_OPERATION));
		memcpy(&seq_operation, (SEQ_OPERATION*)receiveData->lpData, sizeof(SEQ_OPERATION));

		if (seq_operation.nSeqOperation == SEQ_START) {
			if (errorcode[0] && errorcode[0] < 0x0350) {
				seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
				seq_rsp.nResult = RESPONSE_NAK;
				strcpy(seq_rsp.strResultMsg, "Clear Alarm First");
			}
			//else if (!strcmp(strUserName, "")) {
			//	seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			//	seq_rsp.nResult = RESPONSE_NAK;
			//	sprintf(seq_rsp.strResultMsg, "User 정보가 없습니다. 로그인 하세요");
			//}
			//else if (!strcmp(LotInfo.strLotID, "")) {
			//	seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			//	seq_rsp.nResult = RESPONSE_NAK;
			//	sprintf(seq_rsp.strResultMsg, "Lot 정보를 입력 하세요.");
			//}
			else {
				seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
				seq_rsp.nResult = RESPONSE_ACK;

				seqMain->AutoStart();
				printf("WM_SEQ_OPERATION_REQ : SEQ_START\n");

				sprintf(strFileLog, "%s", "WM_SEQ_OPERATION_REQ : SEQ_START");
				LOG_TRACE(strFileLog);

			}
		}
		else if (seq_operation.nSeqOperation == SEQ_STOP) {
			seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			seq_rsp.nResult = RESPONSE_ACK;

			seqMain->AutoStop();
			printf("WM_SEQ_OPERATION_REQ : SEQ_STOP\n");

			sprintf(strFileLog, "%s", "WM_SEQ_OPERATION_REQ : SEQ_STOP");
			LOG_TRACE(strFileLog);
		}
		else if (seq_operation.nSeqOperation == SEQ_RESET) {
			seqMain->KeyReset();
			printf("WM_SEQ_OPERATION_REQ : SEQ_RESET\n");

			//if (bit.AutoRun) {
			//	seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			//	seq_rsp.nResult = RESPONSE_NAK;
			//	sprintf(seq_rsp.strResultMsg, "Auto Run 중입니다. RESET 할수 없습니다");
			//}
			//else {
			//	seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			//	seq_rsp.nResult = RESPONSE_ACK;

			//	seqMain->KeyReset();
			//	printf("WM_SEQ_OPERATION_REQ : SEQ_RESET\n");
			//	sprintf(strFileLog, "%s", "WM_SEQ_OPERATION_REQ : SEQ_RESET");
			//	LOG_TRACE(strFileLog);
			
			//}
		}
		else if (seq_operation.nSeqOperation == SEQ_LOTEND) {
			//if (bit.AutoRun) {
			//	seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
			//	seq_rsp.nResult = RESPONSE_NAK;
			//	sprintf(seq_rsp.strResultMsg, "Auto Run 중입니다. LOT END 할수 없습니다");
			//}
			//else {
				seq_rsp.nMsgNo = WM_SEQ_OPERATION_RSP;
				seq_rsp.nResult = RESPONSE_ACK;
				bit.ButtonLotEnd = 1;
				printf("WM_SEQ_OPERATION_REQ : SEQ_LOTEND\n");
			
				sprintf(strFileLog, "%s", "WM_SEQ_OPERATION_REQ : SEQ_LOTEND");
				LOG_TRACE(strFileLog);
			//}
		}
	}
		break;
	case WM_USER_LOG_IN_REQ:
	{
		if (bit.AutoRun) {
			seq_rsp.nMsgNo = WM_USER_LOG_IN_RSP;
			seq_rsp.nResult = RESPONSE_NAK;
			sprintf(seq_rsp.strResultMsg, "Auto Running, Can not Log In");
		}
		else {
			seq_rsp.nMsgNo = WM_USER_LOG_IN_RSP;
			seq_rsp.nResult = RESPONSE_ACK;
			sprintf(seq_rsp.strResultMsg, "");

			USER_INFO user_info;
			memset(&user_info, 0x00, sizeof(USER_INFO));
			memcpy(&user_info, (USER_INFO*)receiveData->lpData, sizeof(USER_INFO));

			strcpy(strUserName, user_info.strUserName);
			printf("USER LOG IN : %s\n", strUserName);
		}
	}
		break;
	case WM_USER_LOG_OUT_REQ:
	{
		if (bit.AutoRun) {
			seq_rsp.nMsgNo = WM_USER_LOG_OUT_RSP;
			seq_rsp.nResult = RESPONSE_NAK;
			sprintf(seq_rsp.strResultMsg, "Auto Running. Cant not LOG OUT.");
		}
		else {
			seq_rsp.nMsgNo = WM_USER_LOG_OUT_RSP;
			seq_rsp.nResult = RESPONSE_ACK;
			sprintf(seq_rsp.strResultMsg, "");

			USER_INFO user_info;
			memset(&user_info, 0x00, sizeof(USER_INFO));
			memcpy(&user_info, (USER_INFO*)receiveData->lpData, sizeof(USER_INFO));

			strcpy(strUserName, "NO_USER");
			printf("USER LOG OUT : %s\n", strUserName);
		}
	}
		break;
	case WM_LOT_INPUT_REQ:
	{
		if (bit.AutoRun) {
			seq_rsp.nMsgNo = WM_LOT_INPUT_RSP;
			seq_rsp.nResult = RESPONSE_NAK;
			sprintf(seq_rsp.strResultMsg, "Auto Running. Can not input LOT ID");
		}
		else {
			seq_rsp.nMsgNo = WM_LOT_INPUT_RSP;
			seq_rsp.nResult = RESPONSE_ACK;
			sprintf(seq_rsp.strResultMsg, "");

			SEQ_LOT_INFO_REQ seq_lot_info;
			memset(&seq_lot_info, 0x00, sizeof(SEQ_LOT_INFO_REQ));
			memcpy(&seq_lot_info, (SEQ_LOT_INFO_REQ*)receiveData->lpData, sizeof(SEQ_LOT_INFO_REQ));

			strcpy(LotInfo.strLotID, seq_lot_info.strLotID);
			LotInfo.nLotCount = seq_lot_info.nLotCount;

			LOG_LOT("LOT ID = %s\tLOT COUNT = %d\tUser = %s", LotInfo.strLotID, LotInfo.nLotCount, strUserName);
			bit.LotEndCntClear = 1;
			printf("LOT INFO : LOT ID = %s, LOT COUNT =%d\n", LotInfo.strLotID, LotInfo.nLotCount);
		}
	}
		break;
	case WM_LOT_CANCEL_REQ:
	{
		if (bit.AutoRun) {
			seq_rsp.nMsgNo = WM_LOT_CANCEL_RSP;
			seq_rsp.nResult = RESPONSE_NAK;
			sprintf(seq_rsp.strResultMsg, "Auto Running. Can not cancel LOT");
		}
		else {
			seq_rsp.nMsgNo = WM_LOT_CANCEL_RSP;
			seq_rsp.nResult = RESPONSE_ACK;
			sprintf(seq_rsp.strResultMsg, "adsadfds");

			strcpy(LotInfo.strLotID, "");
			LotInfo.nLotCount = 0;

			printf("LOT CANCEL Succeed\n");

		}
	}
		break;
	case WM_LOT_CLEAR_REQ:
		strcpy(LotInfo.strLotID, "");
		LotInfo.nLotCount = 0;

		bit.LotEndCntClear = 1;
		
		break;
	case WM_DEVICE_INFO_REQ:
	{
		seq_rsp.nMsgNo = WM_DEVICE_INFO_RSP;
		seq_rsp.nResult = RESPONSE_ACK;
		sprintf(seq_rsp.strResultMsg, "");

		DEVICE_INFO	device_info;
		memset(&device_info, 0x00, sizeof(DEVICE_INFO));
		memcpy(&device_info, (DEVICE_INFO*)receiveData->lpData, sizeof(DEVICE_INFO));

		MachineStatus.nDeviceNo = device_info.nDeviceNumber;
		strcpy(MachineStatus.strDeviceName, device_info.strDeviceName);

		printf("DEVICE NAME = %s\n", MachineStatus.strDeviceName);
	}
		break;
	default:
		break;
	}
	seqMain->SendCopyDataToMMI(seq_rsp.nMsgNo, sizeof(SEQ_RSP), (void*)&seq_rsp);

	delete receiveData;
	receiveData = NULL;

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
void CSEQAppDlg::RunSequence()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// MEMORY leak detect
//	_CrtSetBreakAlloc(603);

	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	seqMain->InitConsole();
	seqMain->InitSequence();

	Sleep(100);

	//////////////////////////////////////////////////////////////////////////
	// Timer HANDLER Resolution
	//TIMECAPS tc;
	//if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
	//	return;
	//}
	//wTimeRes = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);
	//if (timeBeginPeriod(wTimeRes) != TIMERR_NOERROR) {
	//	return;
	//}
	////////////////////////////////////////////////////////////////////////////
	//// Timer HANDLER
//	tmHandlerScan.SetTime();
	//UINT interval = 1;
	//timerID = timeSetEvent(interval, wTimeRes, seqMain->TimerHandler, (DWORD)0, TIME_PERIODIC);
	//if (timerID == NULL) {
	//	return;
	//}

	seqMain->m_bSeqExit = false;

	////////////////////////////////////////////////////////////////////////////
	// Main Sequence Thread
	m_pThread_SeqMain = AfxBeginThread(seqMain->SEQ_Main_Thread, this);
	SetThreadPriority(m_pThread_SeqMain->m_hThread, THREAD_PRIORITY_HIGHEST);

	////////////////////////////////////////////////////////////////////////////
	// MMI Thread
	m_pThread_SeqMMI = AfxBeginThread(seqMain->MMI_Thread, this);
	SetThreadPriority(m_pThread_SeqMMI->m_hThread, THREAD_PRIORITY_NORMAL);

	////////////////////////////////////////////////////////////////////////////
	// MOTION Thread
	m_pThread_SeqMotion1 = AfxBeginThread(seqMain->SEQ_Motion_Thread1, this);
	SetThreadPriority(m_pThread_SeqMotion1->m_hThread, THREAD_PRIORITY_NORMAL);

	/*m_pThread_SeqMotion2 = AfxBeginThread(seqMain->SEQ_Motion_Thread2, this);
	SetThreadPriority(m_pThread_SeqMotion2->m_hThread, THREAD_PRIORITY_NORMAL);

	m_pThread_SeqMotion3 = AfxBeginThread(seqMain->SEQ_Motion_Thread3, this);
	SetThreadPriority(m_pThread_SeqMotion3->m_hThread, THREAD_PRIORITY_NORMAL);

	m_pThread_SeqMotion4 = AfxBeginThread(seqMain->SEQ_Motion_Thread4, this);
	SetThreadPriority(m_pThread_SeqMotion4->m_hThread, THREAD_PRIORITY_NORMAL);
	
	m_pThread_SeqMotion5 = AfxBeginThread(seqMain->SEQ_Motion_Thread5, this);
	SetThreadPriority(m_pThread_SeqMotion5->m_hThread, THREAD_PRIORITY_NORMAL);

	m_pThread_SeqMotion6 = AfxBeginThread(seqMain->SEQ_Motion_Thread6, this);
	SetThreadPriority(m_pThread_SeqMotion6->m_hThread, THREAD_PRIORITY_NORMAL);*/

	////////////////////////////////////////////////////////////////////////////
	// RS232 Thread
	m_pThread_SeqRS232 = AfxBeginThread(seqMain->RS232_Thread, this);
	SetThreadPriority(m_pThread_SeqRS232->m_hThread, THREAD_PRIORITY_NORMAL);

	WinSockInitialize();
	////////////////////////////////////////////////////////////////////////////
	// CLIENT Socket Thread
	//m_pThread_SeqClientSocket = AfxBeginThread(seqMain->CLIENT_SOCKET_Thread, this);
	//SetThreadPriority(m_pThread_SeqClientSocket->m_hThread, THREAD_PRIORITY_NORMAL);

	////////////////////////////////////////////////////////////////////////////
	// Server Socket Thread
	m_pThread_SeqServerSocket = AfxBeginThread(seqMain->SERVER_SOCKET_Thread, this);
	SetThreadPriority(m_pThread_SeqServerSocket->m_hThread, THREAD_PRIORITY_NORMAL);

	m_pThread_SeqUDPSocket = AfxBeginThread(seqMain->CLIENT_UDP_Thread, this);
	SetThreadPriority(m_pThread_SeqUDPSocket->m_hThread, THREAD_PRIORITY_NORMAL);

}
void CSEQAppDlg::CloseSequence()
{
	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	//if (timeKillEvent(timerID) != TIMERR_NOERROR) {
	//	return;
	//}
	//timeEndPeriod(wTimeRes);

	seqMain->m_bSeqExit = true;

	////////////////////////////////////////////////////////////////////////////
	// Main Sequence Thread
	WaitForSingleObject(m_pThread_SeqMain->m_hThread, INFINITE);
	
	////////////////////////////////////////////////////////////////////////////
	// MMI Thread
	WaitForSingleObject(m_pThread_SeqMMI->m_hThread, INFINITE);

	////////////////////////////////////////////////////////////////////////////
	// Motion Thread
	WaitForSingleObject(m_pThread_SeqMotion1->m_hThread, INFINITE);
	/*WaitForSingleObject(m_pThread_SeqMotion2->m_hThread, INFINITE);
	WaitForSingleObject(m_pThread_SeqMotion3->m_hThread, INFINITE);
	WaitForSingleObject(m_pThread_SeqMotion4->m_hThread, INFINITE);
	WaitForSingleObject(m_pThread_SeqMotion5->m_hThread, INFINITE);
	WaitForSingleObject(m_pThread_SeqMotion6->m_hThread, INFINITE);*/

	////////////////////////////////////////////////////////////////////////////
	// RS232 Thread
	WaitForSingleObject(m_pThread_SeqRS232->m_hThread, INFINITE);

	////////////////////////////////////////////////////////////////////////////
	// CLIENT Socket Thread
	//ClientVision.Close();
	//WaitForSingleObject(m_pThread_SeqClientSocket->m_hThread, INFINITE);

	////////////////////////////////////////////////////////////////////////////
	// SERVER Socket Thread
	extern SOCKET servSock;
	closesocket(servSock);
	WaitForSingleObject(m_pThread_SeqServerSocket->m_hThread, 2000);

	////////////////////////////////////////////////////////////////////////////
	// UDP CLIENT Socket Thread
	closesocket(udp_Client);
	WaitForSingleObject(m_pThread_SeqUDPSocket->m_hThread, INFINITE);

}

