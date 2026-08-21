
// SEQAppDlg.h: 헤더 파일
//

// tray icon ID
#define ID_SYSTEMTRAY		0x1000

// custom message ID
#define  WM_TRAYICON_MSG	WM_USER + 1

// tray icon resource ID
#define ID_ICON_TRAY_INITIAL 0x2000

#pragma once


// CSEQAppDlg 대화 상자
class CSEQAppDlg : public CDialogEx
{
// 생성입니다.
public:
	CSEQAppDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CSEQAppDlg();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEQAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT	OnLinkTestRequest(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

public:
	DWORD timerID = 0;
	UINT  wTimeRes = 0;

//	bool m_bSeqExit = false;
	HANDLE h_MainThreadEvent;

	CWinThread* m_pThread_SeqMain = nullptr;
	CWinThread* m_pThread_SeqMMI = nullptr;
	CWinThread* m_pThread_SeqMotion1 = nullptr;
	/*CWinThread* m_pThread_SeqMotion2 = nullptr;
	CWinThread* m_pThread_SeqMotion3 = nullptr;
	CWinThread* m_pThread_SeqMotion4 = nullptr;
	CWinThread* m_pThread_SeqMotion5 = nullptr;
	CWinThread* m_pThread_SeqMotion6 = nullptr;*/

	CWinThread* m_pThread_SeqRS232 = nullptr;

	CWinThread* m_pThread_SeqClientSocket = nullptr;
	CWinThread* m_pThread_SeqServerSocket = nullptr;

	CWinThread* m_pThread_SeqUDPSocket = nullptr;

	void RunSequence();
	void CloseSequence();

protected:
	bool m_bShowStatus;
	LRESULT TrayIconMsg(WPARAM wParam, LPARAM lParam);
private:
	void RegistTrayIcon();
public:
	afx_msg void OnDestroy();
	
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
