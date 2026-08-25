#include "..\pch.h"
#include "CLASS_Main.h"
#include <windows.h>

#ifdef _DEBUG
	#ifdef UNICODE
		#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
		#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif
#endif

BOOL WINAPI ContrlHandler(DWORD Opcode);

void CSeqMain::InitConsole(void)
{
	// No console in the Windows-subsystem (Release) build: the /subsystem:console
	// switch above is guarded by _DEBUG. Without this guard the system() calls below
	// would allocate a console and flash a cmd window on startup.
	if (::GetConsoleWindow() == NULL)
		return;

	HANDLE hwndConsole = ::GetConsoleWindow();
	HMENU hmenu = ::GetSystemMenu(::GetConsoleWindow(), FALSE);
//	::MoveWindow(::GetConsoleWindow(), 200, 300, 100, 30, 1);
	::SetWindowPos(::GetConsoleWindow(), HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	::SetConsoleTitle(TEXT("SEQ Running LOG"));			// Console Title

	::EnableMenuItem(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);	// Maximize 아이콘이 보이기는 하지만 작동하지 않음
	::DeleteMenu(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);

	::EnableMenuItem(hmenu, SC_CLOSE, MF_BYCOMMAND);		// X 아이콘이 보이기는 하지만 Disabl 됨
	::DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
	::DrawMenuBar(::GetConsoleWindow());

	ShowWindow(::GetConsoleWindow(), SW_HIDE);
	
	SetConsoleRGB(2);		// 글씨 color 변경

	system("MODE CON:COLS=120 LINES=30");// Console 크기
	SetConsoleSize(10000, 2000);			 // Console buffer 크기 설정

	system("VER");	// OS version 표시	

	// 투명도 적용 Win7이상 적용 가능	
	/*SetWindowLong(::GetConsoleWindow(), GWL_EXSTYLE, WS_EX_LAYERED);
	SetLayeredWindowAttributes(::GetConsoleWindow(), RGB(0, 0, 0), 150, LWA_ALPHA);*/

	// 컨트롤 핸들러, 키보드 입력 처리
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_MOUSE_INPUT);
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ~ENABLE_INSERT_MODE | ~ENABLE_QUICK_EDIT_MODE);

	DWORD prevMode = 0;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(handle, &prevMode);
	SetConsoleMode(handle, prevMode & ~ENABLE_QUICK_EDIT_MODE);

	BOOL ret = SetConsoleCtrlHandler((PHANDLER_ROUTINE)ContrlHandler, TRUE);
	if (!ret) {
		printf("Could not set CtrlHandler\n");
	}

	 //  console 을 tray로 이동
	 //	ShowWindow(::GetConsoleWindow(), SW_HIDE);
	 //	NOTIFYICONDATA Tray;
	 //	//tray info
	 //	Tray.cbSize=sizeof(Tray);
	 //	Tray.hIcon=LoadIcon(NULL,IDI_WINLOGO);
	 ////	Tray.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	 //	Tray.hWnd=::GetConsoleWindow();;
		//wcscpy(Tray.szTip,L"SEQ Running Log");
	 //	Tray.uCallbackMessage=WM_LBUTTONDOWN;
	 //	Tray.uFlags=NIF_ICON | NIF_TIP | NIF_MESSAGE;
	 //	Tray.uID=1;
	 //	
	 //	//set the icon in tasbar tray
	 //	Shell_NotifyIcon(NIM_ADD, &Tray);
	//	Sleep(5000);
	// 
	// 	//remove the icon
	// 	Shell_NotifyIcon(NIM_DELETE, &Tray);
	// 	ShowWindow(::GetConsoleWindow(), SW_SHOW);
}
void CSeqMain::ShowConsoleWindow(void)
{
	ShowWindow(::GetConsoleWindow(), SW_SHOW);
}
void CSeqMain::HideConsoleWindow(void)
{
	ShowWindow(::GetConsoleWindow(), SW_HIDE);
}
void CSeqMain::SetConsoleRGB(int color)
{
	//	system("color 1a");		// 창 전체 color 변경	color xy => (x,y=0~F)

	switch (color)
	{
	case 0:    // White on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 1:    // Red on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED);
		break;
	case 2:    // Green on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_GREEN);
		break;
	case 3:    // Yellow on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case 4:    // Blue on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_BLUE);
		break;
	case 5:    // Magenta on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case 6:    // Cyan on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 7:    // Black on Gray
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
			BACKGROUND_INTENSITY);
		break;
	case 8:    // Black on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
			FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		break;
	case 9:    // Red on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
			FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
			FOREGROUND_RED);
		break;
	case 10:    // Green on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
			FOREGROUND_GREEN);
		break;
	case 11:    // Yellow on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
			FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case 12:    // Blue on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
			FOREGROUND_BLUE);
		break;
	case 13:    // Magenta on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
			FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case 14:    // Cyan on White SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_BLUE); break; case 15: // White on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default:    // White on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
}

void CSeqMain::SetConsoleSize(SHORT width, SHORT height)
{
	// 콘솔 버퍼 크기 지정
	COORD coord = { width, height };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	//	콘솔 크기 지정
	// 	SMALL_RECT rect;
	// 	rect.Left = 0;
	// 	rect.Right = width - 1;
	// 	rect.Top = 0;
	// 	rect.Bottom = height - 1;
	//	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);
}
BOOL WINAPI ContrlHandler(DWORD Opcode)
{
	switch (Opcode)
	{
	case CTRL_C_EVENT:		// VisualStudio의 Menu->Debug->창->예외설정->Win32 Exceptions->Ctrl-C Thrown uncheck해야 한다.
		system("CLS");		// Clear screen
		return TRUE;
	case CTRL_BREAK_EVENT:	// VisualStudio의 Menu->Debug->창->예외설정->Win32 Exceptions->Ctrl-Break Thrown uncheck해야 한다.
		return TRUE;
	case CTRL_CLOSE_EVENT:
		return TRUE;
	case CTRL_SHUTDOWN_EVENT:
		return TRUE;
	case CTRL_LOGOFF_EVENT:
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}