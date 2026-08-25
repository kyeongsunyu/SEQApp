#include "..\pch.h"
#include "CLASS_TcpClient.h"
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

CTcpClient::CTcpClient()
{
	//클래스 멤버 변수들을 안전한 초기 상태로 설정합
	socket_Client = -1;
	strServerIP = "";	
	nPort = 0;
	bConnected = false;
	PacketProcessor = NULL;
}
bool CTcpClient::Connect(char* IP, int nPort)
{
	//create socket if it is not already created
	//if (socket_Client == -1) 
	//{
		socket_Client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //IPv4(AF_INET) 기반의 TCP 스트림 소켓(SOCK_STREAM, IPPROTO_TCP)을 생성합니다.
		if (socket_Client == INVALID_SOCKET) {
			printf("Failed to call socket() with error code : %d\n", WSAGetLastError());
			WSACleanup(); //// WSAStartup이 이전에 호출되었다고 가정
		}

		//setup socket option	
		option = TRUE;
		// 1. 주소 재사용 허용 (SO_REUSEADDR)
		iError = setsockopt(socket_Client, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, sizeof(option));
		if (iError == INVALID_SOCKET) {
			printf("socket option failed: SO_REUSEADDR(%d)\n", WSAGetLastError());
		}
		// 2. LINGER 옵션 설정 (Close 후 즉시 자원 해제)
		struct linger LINGER;
		LINGER.l_onoff = 1; // Linger 옵션  움
		LINGER.l_linger = 0; // 대기 시간 0초
		shutdown(socket_Client, SD_BOTH); // 연결 종료 요청
		// 이 설정은 closesocket() 호출 시 남아있는 데이터를 기다리지 않고
       // 즉시 소켓을 강제 종료하고 리소스를 해제합니다.
		setsockopt(socket_Client, SOL_SOCKET, SO_LINGER, (const char*)&LINGER, sizeof(LINGER));
		// 3. Nagle 알고리즘 비활성화 (TCP_NODELAY)
		iError = setsockopt(socket_Client, IPPROTO_TCP, TCP_NODELAY, (const char*)&TcpNoDelay, sizeof(int));
		printf("*** Nagle Algorithm is disabled ***\n");

	//}
	//else {/* OK , nothing */}

	//setup address structure
	//... IP와 Port 설정 ...
	memset(&m_srv_addr, 0x00, sizeof(struct sockaddr_in));
	m_srv_addr.sin_family = AF_INET;
	m_srv_addr.sin_addr.s_addr = inet_addr(IP);
	m_srv_addr.sin_port = htons(nPort);

	if (connect(socket_Client, (struct sockaddr*)&m_srv_addr, sizeof(m_srv_addr)) < 0)
	{
		// 연결 실패 처리
		printf("Failed to connect with error code : %d\n", WSAGetLastError());
		closesocket(socket_Client);
		//			SendMessage(Communicator->Handle, WM_SERVER_DISCONNECT, 0, 0);
	}
	else {
		bConnected = true;
		//			SendMessage(Communicator->Handle, WM_SERVER_CONNECT, 0, 0);
		printf("Successfully Connected to Server...\n");

		DWORD dwMode = SOCK_MODE_NON_BOLCKING;// ... 논블로킹 설정 ...
		
		int nResult = ioctlsocket(socket_Client, FIONBIO, &dwMode);
		//소켓을 논블로킹(Non-Blocking) 모드로 변경합니다. 이 설정 덕분에 recv나 send 같은 함수를 호출했을 때, 
		// 당장 데이터가 없더라도 프로그램이 멈추지 않고 즉시 제어를 반환하게 됩니다.
		if (nResult != NO_ERROR) {
			printf("ioctlsocket() call failed with error code : %ld\n", nResult);
			return false;
		}
	}
	return true;
}
void CTcpClient::ReadData()
{
	char* ptr = nullptr;

	memset(buf, 0x00, sizeof(buf));
	ptr = (char*)buf;

	int nTotPktLen = 0;

	nReadBytes = recv(socket_Client, ptr, sizeof(WORD), 0); // Read Packet Length (2 bytes)
	if (nReadBytes > 0) {
		//이 클라이언트는 Length - prefixed protocol(길이 선행 프로토콜) 방식을 사용합니다.
		//첫 번째 recv 호출에서 패킷의 가장 앞 2바이트(WORD)를 읽어와 전체 패킷의 길이(m_wPktLen)를 알아냅니다.
		ptr += nReadBytes;
		PROTOCOL_DATA* pCommPkt = (PROTOCOL_DATA*)buf;
		nTotPktLen = pCommPkt->m_wPktLen; // 전체 패킷 길이 추출 (2바이트)
		
		nReadBytes = recv(socket_Client, ptr, nTotPktLen - 2, 0);// 나머지 데이터 수신
		if (nReadBytes > 0) {
			ptr += nReadBytes;
			*ptr = '\0';// 문자열 종료 (널 문자) 추가
			printf("received data buf= %s\n", buf);
			PacketProcessor(buf);// 등록된 콜백 함수 호출
		}
	}
	else if (nReadBytes == 0)
	{
		//상대방이 정상적으로 소켓을 닫았을 때(Gracefully socket closed).연결 상태를 false로 바꾸고 소켓을 닫습니다.
		printf("Gracefully socket closed by remote peer : [%s]\n", inet_ntoa(m_srv_addr.sin_addr));
		bConnected = false;
		closesocket(socket_Client);
	}
	else if (nReadBytes < 0) //수신 오류 발생.
	{
		int nErrCode = WSAGetLastError();

		//소켓이 논블로킹 모드인데 현재 읽을 데이터가 없을 때 발생하는 정상적인 상태입니다.이 오류는 무시하고 루프를 계속 돌게 됩니다.
		if (nErrCode != WSAEWOULDBLOCK) {
			printf("recv() call failed with error code : %d\n", WSAGetLastError());
			bConnected = false;
			closesocket(socket_Client);
		}
	}
}
void CTcpClient::SendData(char* msg, char* format, ...)
{
	WaitForSingleObject(hMutex, INFINITE); //1. 뮤텍스 획득
	// va_list를 사용하여 가변 인자 형식화 (vsprintf)
	va_list args;
	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	char sndmsg[32];
	memset(sndmsg, 0, sizeof(sndmsg));
	strcpy(sndmsg, msg);
	send(socket_Client, sndmsg, sizeof(sndmsg), 0);
	ReleaseMutex(hMutex);// 2. 뮤텍스 해제
}

void CTcpClient::Close()
{
	closesocket(socket_Client);
}