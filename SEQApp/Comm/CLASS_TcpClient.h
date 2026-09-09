//Include Guard입니다. 이 헤더 파일이 컴파일 과정에서 한 번만 포함되도록 보장하여, 재정의 오류를 방지합니다.
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//nclude Guard와 동일한 목적으로 사용되며, 컴파일러에게 이 파일을 한 번만 처리하도록 지시합니다.
// (일반적으로 두 가지를 모두 사용하는 것은 중복이지만 안전을 위해 함께 쓰이기도 합니다.)
#pragma once

//최대 버퍼 길이를 4096 바이트로 정의합니다.
#define MAX_BUF_LEN 4096


//Nagle 알고리즘은 TCP/IP 네트워크 환경에서 작은 패킷(Small Packets)이 과도하게 많이 발생하는 현상을 줄여 네트워크 효율성을 높이기 위해 고안된 알고리즘입니다.
//1984년 존 네이글(John Nagle)이 개발했으며, 특히 텔넷(Telnet)과 같은 상호작용이 잦은 환경에서 발생하는 '작은 쓰기 요청'들이 네트워크를 불필요하게 점유하는 것을 방지하는 데 목적이 있습니다.
//Nagle 알고리즘의 지연 시간 증가 단점 때문에, 실시간성이 중요한 애플리케이션에서는 이 알고리즘을 비활성화해야 합니다.
enum _eSocketMode
{
	//데이터 송수신 함수 호출 시 작업이 완료될 때까지 프로그램 실행이 멈춥니다.
	SOCK_MODE_BLOCKING = 0x00,
	//데이터 송수신 함수 호출 시 즉시 반환되며, 데이터가 준비되지 않았더라도 오류 코드를 반환합니다.
	SOCK_MODE_NON_BOLCKING = 0x01,
};


//CPU가 메모리에서 데이터를 효율적으로 읽으려면, 데이터 타입의 크기(예: int는 4바이트)와 같은 배수의 주소에서 데이터를 시작해야 합니다.
// 이를 **메모리 정렬(Memory Alignment)**이라고 합니다.
//컴파일러는 기본적으로 이 정렬 규칙을 따르기 위해 구조체 멤버 사이에** 빈 공간(Padding)** 을 자동으로 삽입합니다.
//이 구조체의 멤버들을 1바이트 경계로 정렬하도록 설정하여, 멤버 사이에 패딩(Padding)이 들어가는 것을 방지합니다. 
// 이는 서버와 클라이언트 간의 데이터 형식을 정확히 일치시키는 데 필수적입니다.
#pragma pack(push,1)
typedef struct
{
	WORD    m_wPktLen;
	WORD	m_wCommandID;
	BYTE	byData[MAX_BUF_LEN];
} PROTOCOL_DATA, * PPROTOCOL_DATA; //서버-클라이언트 통신에서 사용되는 패킷의 기본 형식을 정의합니다.
//구조체 정의 후 원래의 메모리 정렬 설정으로 복원합니다.
#pragma pack(pop)

class CTcpClient
{
private :
	SOCKET socket_Client; //클라이언트 소켓 핸들 (Windows 소켓 API에서 사용되는 타입).

	const char* strServerIP;
	int nPort;

	struct sockaddr_in  m_srv_addr;

	int option;
	int iError;
	int TimeStamp = FALSE;
	int TcpNoDelay = TRUE; //소켓 옵션 설정 플래그 (예: TcpNoDelay = TRUE는 Nagle 알고리즘을 비활성화).
	int nReadBytes = 0;

	HANDLE hMutex; //쓰레드 간의 동기화를 위한 뮤텍스 핸들 (데이터 송수신 시 동시 접근 방지).
public:
	bool bConnected;
	char buf[MAX_BUF_LEN] = { 0, }; //수신된 데이터를 임시 저장하는 버퍼.

	CTcpClient(); //클래스 객체 초기화.
	bool Connect(char* IP, int nPort); //주어진 IP와 포트로 서버에 연결을 시도합니다.
	void ReadData(); //소켓으로부터 데이터를 수신하는 함수입니다.
	void SendData(char* msg, char* format, ...); //데이터를 서버로 전송하는 함수입니다 (가변 인자를 사용하는 것으로 보아 형식화된 데이터 전송용).
	void Close(); //소켓 연결을 종료하고 리소스를 해제합니다.
	void(*PacketProcessor)(char* packet); //수신된 패킷을 처리하는 콜백 함수를 가리킵니다. 클라이언트가 데이터를 수신할 때마다 이 함수를 호출하여 패킷을 분석하고 처리하게 됩니다.
};

#endif 