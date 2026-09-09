#include "..\pch.h"
#include "..\SeqMain\CLASS_Main.h"
#include "..\SeqMain\DEFINE_GVX.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#define DEFAULT_FAMILY     PF_INET // Accept either IPv4 or IPv6 기본적으로 IPv4 주소 패밀리를 사용함을 나타냅니다.

#define	MAX_PACKET_SIZE		65535
#define DEFAULT_PACKET_SIZE	1024
#define MAX_TCP_LIMIT				1460 //TCP 세그먼트의 최대 데이터 크기(MTU 1500에서 TCP/IP 헤더를 뺀 값 근처)입니다.
#define MAX_UDP_LIMIT			1472 //UDP 데이터그램의 최대 데이터 크기(MTU 1500에서 UDP/IP 헤더를 뺀 값 근처)입니다.

#define RECV_TIMEOUT				5000 //수신 타임아웃 값 (5000ms, 즉 5초)입니다.
#define SEND_TIMEOUT				5000 //송신 타임아웃 값 (5000ms, 즉 5초)입니다.

#define WFD_RECV_DATA			1     //WaitForData 함수에서 수신 대기 유형을 나타냅니다.
#define WFD_SEND_DATA			2     //WaitForData 함수에서 송신 가능 대기 유형을 나타냅니다.

#define RECV_BUF_ERROR			0
#define RECV_BUF_TIMEOUT		-1   //수신 함수에서 타임아웃 발생을 나타내는 반환 값입니다.

_Post_ _Notnull_ HANDLE hMutex;
//////////////////////////////////////////////////////////////////////////
void WinSockInitialize(void);
int SendBuffer(SOCKET s, char* Buffer, int Length, int iFragmentBuffer, int iTimeOut);
BOOL WaitForData(SOCKET pSocket, long iTimeOut, long WaitType);
int RecvBuffer(SOCKET s, char* Buffer, int MaxLength, int iTimeOut);
void SEND_MSG(SOCKET s, char* msg);
void SEND_MSG_STR(SOCKET s, char* msg, char* format, ...);
void error(char* str);
USHORT checksum(USHORT* buffer, int size);
void cmp_ping(void);

void WinSockInitialize(void)
{
	int iError;
	WORD wVersionRequested;
	WSADATA wsaData;

	WSACleanup(); // 기존에 초기화된 소켓 환경 정리 (안전 조치)

	wVersionRequested = MAKEWORD(2, 2);
	iError = WSAStartup(wVersionRequested, &wsaData);	// Winsock 2.2 버전으로 초기화 Winsock DLL을 로드하고 Winsock 2.2 버전을 사용하도록 초기화합니다.
																			//이는 모든 Winsock 함수를 사용하기 전에 반드시 호출되어야 하는 함수입니다.
	if (iError != 0) {
		printf("Error %d: Winsock not available\n", iError);
	}
	else printf("*** Client: WinSock started ***\n");
}
//////////////////////////////////////////////////////////////////////////
int SendBuffer(SOCKET s, char* Buffer, int Length, int iFragmentBuffer, int iTimeOut)
{
	long TotalSent, SendLength;
	long pSequenceNumber = 1;
	DWORD* LengthArea = (DWORD*)Buffer;
	*LengthArea = Length;

	TotalSent = 0;

	if (!WaitForData(s, iTimeOut, WFD_SEND_DATA)) {
		printf("send: Timeout on select()\n");
	}

	SendLength = send(s, &Buffer[TotalSent], Length, 0);// 데이터 전송
	if (SendLength == SOCKET_ERROR) {
		printf("Socket send failed with error (%d)\n", WSAGetLastError());
		return(0);
	}

	TotalSent = SendLength;
	return(TotalSent);
}
//////////////////////////////////////////////////////////////////////////
BOOL WaitForData(SOCKET pSocket, long iTimeOut, long WaitType) 
//특정 소켓에서 데이터를 수신할 수 있는지 또는 데이터를 송신할 수 있는지를 지정된 iTimeOut 시간 동안 select() 함수를 사용하여 기다립니다.
{
	struct timeval timeout;
	fd_set fdSet;
	long errorCode;

	// Timeout after 1 seconds, 0 microseconds 
	timeout.tv_sec = iTimeOut / 1000; // Extract the seconds
	timeout.tv_usec = (iTimeOut % 1000) * 1000; // and microseconds of the timeout, timeval 구조체 설정

												// Clear file descriptor set
	FD_ZERO(&fdSet); // 감시할 소켓을 fd_set에 추가

	// Set the bit for network socket 'dataSock' in the descriptor set
	FD_SET(pSocket, &fdSet); 

	// Block until data is available on this socket, or iTimeOut milliseconds has passed
	if (WaitType == WFD_RECV_DATA) //수신 가능 여부 감시
		errorCode = select(1, &fdSet, NULL, NULL, &timeout);
	//역할: 특정 소켓에서 데이터를 수신할 수 있는지 또는 데이터를 송신할 수 있는지를 지정된 iTimeOut 시간 동안 select() 함수를 사용하여 기다립니다.
	else
		if (WaitType == WFD_SEND_DATA)// 송신 가능 여부 감시
			errorCode = select(1, NULL, &fdSet, NULL, &timeout);
		else
			errorCode = 0;

	if (errorCode <= 0)
		return(FALSE);

	return(TRUE);

}
//////////////////////////////////////////////////////////////////////////

//역할: WaitForData를 호출하여 소켓에 데이터가 도착할 때까지 기다린 후, 
// 데이터를 수신합니다. 타임아웃 시 RECV_BUF_TIMEOUT(-1)을 반환하고, 연결 오류 시 RECV_BUF_ERROR(0)을 반환하여 함수 호출자에게 상태를 알립니다.
double RecvStart, RecvEnd;
int RecvBuffer(SOCKET s, char* Buffer, int MaxLength, int iTimeOut)
{
	long TotalRecv, RecvLength;

	// get the start time
	QueryPerformanceCounter(&st);
	RecvStart = (double)st.QuadPart;  // Convert to microsoeconds

	TotalRecv = 0;

	if (!WaitForData(s, iTimeOut, WFD_RECV_DATA)) { //// 수신 가능 대기
		//		RtPrintf("Socket %d recv: Timeout on select()\n", s);
		return(RECV_BUF_TIMEOUT);
	}

	RecvLength = recv(s, &Buffer[TotalRecv], MaxLength, 0);// 데이터 수신
	if (RecvLength == SOCKET_ERROR || RecvLength == 0) {
		printf("%Iu Socket recv failed with error (%d)\n", s, WSAGetLastError());
		return(RECV_BUF_ERROR);
	}
	Buffer[RecvLength] = 0;

	TotalRecv = RecvLength;
	//	printf("received buffer = %s\n",Buffer);
	// get the current time
	QueryPerformanceCounter(&st);
	RecvEnd = (double)st.QuadPart;  // Convert to microsoeconds

									//	printf("Receive Time %f\n", (RecvEnd-RecvStart)/10000.0);
	return(TotalRecv);
}
//////////////////////////////////////////////////////////////////////////
void SEND_MSG(SOCKET s, char* msg)
{
	WaitForSingleObject(hMutex, INFINITE);
	char sndmsg[1024];
	memset(sndmsg, 0, strlen(msg));
	strcpy(sndmsg, msg);
	//	printf("SEND MSG\n");
	//	send(s,sndmsg,sizeof(sndmsg),0);
	send(s, sndmsg, strlen(msg) + 1, 0);
	ReleaseMutex(hMutex);
}
//////////////////////////////////////////////////////////////////////////
void SEND_MSG_STR(SOCKET s, char* msg, char* format, ...)
{
	WaitForSingleObject(hMutex, INFINITE);
	va_list args;
	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	char sndmsg[32];
	memset(sndmsg, 0, sizeof(sndmsg));
	strcpy(sndmsg, msg);
	send(s, sndmsg, sizeof(sndmsg), 0);
	ReleaseMutex(hMutex);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/// Belows are for icmp ping
void error(char* str)
{
	puts(str);
	exit(1);
}
// checksum 검사 함수,IP 및 ICMP 헤더에 사용되는 1의 보수 합(one's complement sum) 체크섬을 계산합니다.
//역할: IP 및 ICMP 프로토콜에서 오류 검출을 위해 사용되는 **체크섬(Checksum)**을 계산합니다. 이는 ICMP 패킷을 직접 구성할 때 필수적인 과정입니다.
USHORT checksum(USHORT* buffer, int size)
{
	unsigned long cksum = 0;
	while (size > 1) {
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}
	if (size) {
		cksum += *(UCHAR*)buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}
// icmp 헤더 구조체 선언
typedef struct icmp_hdr {
	unsigned char icmp_type;
	unsigned char icmp_code;
	unsigned short icmp_checksum;
	unsigned short icmp_id;
	unsigned short icmp_sequence;
	unsigned short icmp_timestamp;
}ICMP_HDR, * PICMP_HDR, FAR* LPICMP_HDR;

void cmp_ping(void)
{

	//ICMP 헤더 직접 구성 : ICMP_HDR 구조체를 만들어 타입(8, Echo Request)과 체크섬을 직접 계산했습니다.
	//RAW 소켓 생성 : socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)를 통해 시스템이 자동으로 헤더를 관리하지 못하게 막고 사용자가 제어권을 가졌습니다.
	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_STORAGE dest;
	ICMP_HDR* icmp = NULL; // ICMP 헤더 구조체 포인터
	char buf[sizeof(ICMP_HDR) + 32];// 체크섬 계산
	icmp = (ICMP_HDR*)buf;
	icmp->icmp_type = 8;
	icmp->icmp_code = 0;
	icmp->icmp_id = (unsigned short)GetCurrentProcessId();
	icmp->icmp_checksum = 0;
	icmp->icmp_sequence = 0;
	icmp->icmp_timestamp = (unsigned short)GetTickCount64();
	memset(&buf[sizeof(ICMP_HDR)], '@', 32);
	icmp->icmp_checksum = checksum((USHORT*)buf, sizeof(ICMP_HDR) + 32);

	if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0)
		error("WSAStartup Error!");
	//일반적인 소켓(TCP의 $SOCK\_STREAM$, UDP의 $SOCK\_DGRAM$)은 커널이 전송 계층 헤더(TCP / UDP 헤더)와 네트워크 계층 헤더(IP 헤더)를 자동으로 생성해 줍니다.
	// 반면, RAW 소켓은 애플리케이션이 이 헤더들을 직접 구성할 수 있게 해줍니다.
	s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);// RAW 소켓 생성

	if (s == INVALID_SOCKET)
		error("socket() Error!");

	((SOCKADDR_IN*)&dest)->sin_family = AF_INET;
	((SOCKADDR_IN*)&dest)->sin_port = htons(0);     // ICMP에서 포트는 무시한다
	((SOCKADDR_IN*)&dest)->sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	for (int i = 0; i < 10; i++) {       // 10번을 ping보낸다, 이때 wireshark를 확인하면 정상적으로 icmp 패킷이 날아가는것을 확인 할 수 있다.
		sendto(s, buf, sizeof(ICMP_HDR) + 32, 0, (SOCKADDR*)&dest, sizeof(dest)); // ICMP 패킷 전송
		Sleep(1000);
	}
	closesocket(s);
	WSACleanup();
}
//////////////////////////////////////////////////////////////////////////

