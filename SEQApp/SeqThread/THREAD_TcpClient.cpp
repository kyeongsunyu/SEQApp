#include "..\pch.h"
#include "..\SeqMain\CLASS_Main.h"
#include "..\Tools\CLASS_INI.h"
#include "..\Comm\CLASS_TcpClient.h"
#include <Windows.h>


#define MAX_BUF_LEN		4096
//Start of Text의 약자로, 통신 프로토콜에서 데이터의 시작을 알리는 제어 문자입니다
//(ASCII SOH, STX, ETX 등 제어 문자를 사용하는 고전적인 프로토콜 방식).
#define STX				0x02 
//End of Text의 약자로, 데이터의 끝을 알리는 제어 문자입니다.
#define ETX				0x03

//#pragma pack(push,1)
//typedef struct
//{
//	WORD    m_wPktLen;
//	WORD	m_wCommandID;
//	BYTE	byData[MAX_BUF_LEN];
//} PROTOCOL_DATA, * PPROTOCOL_DATA;

//UINT CSeqMain::CLIENT_SOCKET_Thread(void* pArg)
//{
//	int nReadBytes = 0;
//	int iError;
//	int option;
//	int TimeStamp = FALSE;
//	int TcpNoDelay = TRUE;
//
//	CString strIP;
//	CStringA strIPA;
//	const char* strServerIP;
//	int nPort = 0;
//
//	CIni Ini(L"C:/WORK/Config.ini");
//	if (Ini.IsKeyExist(L"VISION 1",L"IP"))
//	{
//		strIP = Ini.GetString(L"VISION 1", L"IP", L"127.0.0.1");
//		strIPA = CStringA(strIP);
//		strServerIP = strIPA.GetBuffer();
//	}
//	else {
//		strServerIP = "192.168.0.0.1";
//		Ini.WriteString(L"VISION 1", L"IP", L"192.168.0.1");
//	}
//
//	if (Ini.IsKeyExist(L"VISION 1", L"PORT")) {
//		nPort = Ini.GetInt(L"VISION 1", L"PORT", 9999);
//	}
//	else {
//		Ini.WriteInt(L"VISION 1", L"PORT", 9999);
//	}
//
//	CSeqMain* seqMain = CSeqMain::GetInstance();
//	assert(seqMain != nullptr);
//
//	while (!seqMain->m_bSeqExit)
//	{
//		struct sockaddr_in  m_srv_addr;
//
//		socket_Client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		if (socket_Client == INVALID_SOCKET) {
//			printf("Failed to call socket() with error code : %d\n", WSAGetLastError());
//			WSACleanup();
//		}
//
//		option = TRUE;
//		iError = setsockopt(socket_Client, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, sizeof(option));
//		if (iError == INVALID_SOCKET) {
//			printf("socket option failed: SO_REUSEADDR(%d)\n", WSAGetLastError());
//		}
//		struct linger LINGER;
//		LINGER.l_onoff = 1;
//		LINGER.l_linger = 0;
//		shutdown(socket_Client, SD_BOTH);
//		
//		setsockopt(socket_Client, SOL_SOCKET, SO_LINGER, (const char*)&LINGER, sizeof(LINGER));
//		iError = setsockopt(socket_Client, IPPROTO_TCP, TCP_NODELAY, (const char*)&TcpNoDelay, sizeof(int));
//		printf("*** Nagle Algorithm is disabled ***\n");
//
//		memset(&m_srv_addr, 0x00, sizeof(struct sockaddr_in));
//		m_srv_addr.sin_family = AF_INET;
//		//m_srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//		//m_srv_addr.sin_port = htons(5555);
//		m_srv_addr.sin_addr.s_addr = inet_addr(strServerIP);
//		m_srv_addr.sin_port = htons(nPort); 
//		printf("Attemp to Connect on Server IP : %s, Port : %d\n", strServerIP, nPort);
//
//		char    buf[MAX_BUF_LEN] = { 0, };
//
//		if (connect(socket_Client, (struct sockaddr*)&m_srv_addr, sizeof(m_srv_addr)) < 0)
//		{
//			printf("Failed to connect with error code : %d\n", WSAGetLastError());
//			closesocket(socket_Client);
////			SendMessage(Communicator->Handle, WM_SERVER_DISCONNECT, 0, 0);
//		}
//		else {
//			seqMain->m_bClientConnect = true;
////			SendMessage(Communicator->Handle, WM_SERVER_CONNECT, 0, 0);
//			printf("Successfully Connected to Server...\n");
//
//			DWORD dwMode = SOCK_MODE_NON_BOLCKING;
//			int nResult = ioctlsocket(socket_Client, FIONBIO, &dwMode);
//			if (nResult != NO_ERROR) {
//				printf("ioctlsocket() call failed with error code : %ld\n", nResult);
//				return 9000;
//			}
//		}
//
//		while (seqMain->m_bClientConnect) {
//			char* ptr = nullptr;
//
//			memset(buf, 0x00, sizeof(buf));
//			ptr = (char*)buf;
//
//			int nTotPktLen = 0;
//
//			nReadBytes = recv(socket_Client, ptr, sizeof(WORD), 0); // Read Packet Length (2 bytes)
//			if (nReadBytes > 0) {
//				ptr += nReadBytes;
//				PROTOCOL_DATA* pCommPkt = (PROTOCOL_DATA*)buf;
//				nTotPktLen = pCommPkt->m_wPktLen;
//
//				nReadBytes = recv(socket_Client, ptr, nTotPktLen - 2, 0);
//				if (nReadBytes > 0) {
//					ptr += nReadBytes;
//					*ptr = '\0';
//					printf("received data buf= %s\n", buf);
//					ProcessPacket(buf, pCommPkt->m_wCommandID);
//				}
//			}
//			else if (nReadBytes == 0)
//			{
//				printf("Gracefully socket closed by remote peer : [%s]\n", inet_ntoa(m_srv_addr.sin_addr));
//				seqMain->m_bClientConnect = false;
//				closesocket(socket_Client);
//			}
//			else if (nReadBytes < 0)
//			{
//				int nErrCode = WSAGetLastError();
//				if (nErrCode != WSAEWOULDBLOCK) {
//					printf("recv() call failed with error code : %d\n", WSAGetLastError());
//					seqMain->m_bClientConnect = false;
//					closesocket(socket_Client);
//				}
//			}
//			Sleep(1);
//		}
//		Sleep(3000);
//	}
//	printf("CLIENT SOCKET Thread Exit\n");
//
//	sprintf(strFileLog, "%s", "CLIENT SOCKET Thread Exit");
//	LOG_TRACE(strFileLog);
//
//	return 501;
//}
//
//int CSeqMain::ProcessPacket(char* buf, WORD wCommandID)
//{
//
//	bit.VisionDataReceived = 1;
//	//if (wCommandID == 0x03) {
//	//	PROTOCOL_DATA* pCommPkt = (PROTOCOL_DATA*)buf;
//	//	assert(pCommPkt!=nullptr);
//
//	//	printf("wCommand = %d, pCommPkt->m_wPktLen=%d, pCommPkt->byData=%s \n", wCommandID, pCommPkt->m_wPktLen, pCommPkt->byData);
//	//	return 0;
//	//}
//	//else if (wCommandID == 0x04) {
//	//	PROTOCOL_DATA* pCommPkt = (PROTOCOL_DATA*)buf;
//	//	assert(pCommPkt != nullptr);
//
//	//	printf("wCommand = %d, pCommPkt->m_wPktLen=%d, pCommPkt->byData=%s \n", wCommandID, pCommPkt->m_wPktLen, pCommPkt->byData);
//	//	return 0;
//	//}
//	return -1;
//}

//이 함수는 UINT를 반환하고 void*를 인자로 받는 것으로 보아, Windows 환경(예: MFC)에서 Worker Thread로 실행되도록 설계된 것으로 보입니다.
// 이 스레드의 주요 임무는 비전 서버와의 연결을 유지하고 데이터 송수신을 처리하는 것입니다.
UINT CSeqMain::CLIENT_SOCKET_Thread(void* pArg)
{
	//싱글톤(Singleton) 패턴: CSeqMain 클래스의 싱글톤 인스턴스를 가져와 스레드가 메인 로직에 접근할 수 있도록 합니다.
	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	/*CIni Ini("C:/WORK/Config.ini");
	char* ServerIP = Ini.ReadString("VISION 1", "IP", "127.0.0.1");
	int nPort = Ini.ReadInteger("VISION 1", "PORT", 9999);*/

	CString strIP;
	CStringA strIPA;
	char* strServerIP;
	int nPort = 0;

	//// CIni 클래스를 사용하여 "C:/WORK/Config.ini" 파일에서 설정을 읽음.
	CIni Ini(L"C:/WORK/Config.ini");
	if (Ini.IsKeyExist(L"VISION 1",L"IP"))
	{
		//Ini 파일에 IP가 있으면 읽어옴. (와이드 문자열(L) -> CStringA -> char* 변환)
		// CStringA::GetBuffer()는 C++ 환경에서 문자열 인코딩 및 타입 변환을 처리하는 일반적인 방식입니다.
		strIP = Ini.GetString(L"VISION 1", L"IP", L"127.0.0.1");
		strIPA = CStringA(strIP);
		strServerIP = strIPA.GetBuffer();
	}
	else {
		strServerIP = "192.168.0.1";
		Ini.WriteString(L"VISION 1", L"IP", L"192.168.0.1");
	}

	if (Ini.IsKeyExist(L"VISION 1", L"PORT")) {
		nPort = Ini.GetInt(L"VISION 1", L"PORT", 9999);
	}
	else {
		Ini.WriteInt(L"VISION 1", L"PORT", 9999);
	}

	
	ClientVision.PacketProcessor = seqMain->ReadVisionPacket;

	while (!seqMain->m_bSeqExit)
	{
		ClientVision.Connect(strServerIP, nPort);

		while (ClientVision.bConnected) {
			ClientVision.ReadData();
			Sleep(1);
		}
	//연결이 끊기면(bConnected가 false가 되면) 
	// 내부 루프를 빠져나와 3초(Sleep(3000)) 대기 후 다시 접속을 시도합니다. 이는 서버(비전 프로그램)가 늦게 켜지거나 네트워크가 일시적으로 끊겼을 때 유용한 견고한 설계입니다.
		Sleep(3000);
	}
	printf("CLIENT SOCKET Thread Exit\n");

	sprintf(strFileLog, "%s", "CLIENT SOCKET Thread Exit");
	LOG_TRACE(strFileLog);

	return 501;
}

void CSeqMain::ReadVisionPacket(char* buf)
{

	bit.VisionDataReceived = 1;
	printf("ReadVisionPacket Data received : %s\n", buf);
	//if (wCommandID == 0x03) {
	//	PROTOCOL_DATA* pCommPkt = (PROTOCOL_DATA*)buf;
	//	assert(pCommPkt!=nullptr);

	//	printf("wCommand = %d, pCommPkt->m_wPktLen=%d, pCommPkt->byData=%s \n", wCommandID, pCommPkt->m_wPktLen, pCommPkt->byData);
	//	return 0;
	//}
	//else if (wCommandID == 0x04) {
	//	PROTOCOL_DATA* pCommPkt = (PROTOCOL_DATA*)buf;
	//	assert(pCommPkt != nullptr);

	//	printf("wCommand = %d, pCommPkt->m_wPktLen=%d, pCommPkt->byData=%s \n", wCommandID, pCommPkt->m_wPktLen, pCommPkt->byData);
	//	return 0;
	//}
	//return -1;
}

