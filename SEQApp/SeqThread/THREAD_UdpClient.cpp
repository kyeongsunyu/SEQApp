#include "..\pch.h"
#include "..\SeqMain\CLASS_Main.h"
#include "..\SeqMain\DEFINE_GVX.h"
#include "..\Tools\CLASS_INI.h"
#include <Windows.h>


#define MAX_BUF_LEN		4096
#define STX						0x02
#define ETX						0x03

extern HANDLE hMutex;

UINT CSeqMain::CLIENT_UDP_Thread(void* pArg)
{
	int nReadBytes = 0;

	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	SOCKADDR_IN serverAddr;

	udp_Client = socket(AF_INET, SOCK_DGRAM, 0);
	if (udp_Client == INVALID_SOCKET) {
		printf("Failed to call udp socket() with error code : %d\n", WSAGetLastError());
		WSACleanup();
	}

	memset(&serverAddr, 0x00, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 문자열을 4바이트 주소 정보로 변환
	serverAddr.sin_port = htons(9999); // 포트 번호로 변환

	char buf[MAX_BUF_LEN] = { 0, };

	if (connect(udp_Client, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		printf("Failed to upd connect with error code : %d\n", WSAGetLastError());
	}
	else {
		seqMain->m_bUDPClientConnect = true;
		printf("UDP Successfully Connected to Server...\n");
	}

	while (!seqMain->m_bSeqExit)
	{
		memset(buf, 0x00, sizeof(buf));

		nReadBytes = recv(udp_Client, buf, MAX_BUF_LEN, 0);
		if (nReadBytes > 0) {
			printf("received data buf= %s\n", buf);
		}
		Sleep(1);
	}

	sprintf(strFileLog, "%s", "UDP CLIENT SOCKET Thread Exit");
	LOG_TRACE(strFileLog);

	return 701;
}

void CSeqMain::SEND_UDP(SOCKET s, char* msg)
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