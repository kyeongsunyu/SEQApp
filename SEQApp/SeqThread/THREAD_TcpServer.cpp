#include "..\pch.h"
#include "..\SeqMain\CLASS_Main.h"
#include "..\SeqMain\DEFINE_GVX.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

extern HANDLE h_server_socket;

//////////////////////////////////////////////////////////////////////////
int		clntNumber = 0;
SOCKET	servSock;
SOCKET	clntSock;
SOCKET	clntSocks[10];
char* clntAddrs[10];
int		clntPorts[10];

extern HANDLE	hMutex;

#define BUFSIZE		2048
#define STX_SIZE                    1
#define ETX_SIZE                    1

void DecodeMSG(int n_strlen, char msg[1024]);
void ParseResult(char strpara[]);

typedef struct _ThrArg {	// ClientConn 에 전달할 arg
	SOCKET clntSock;
	char clntIP[16];
	int  clntPort;
} THRARG;
THRARG* p_ThrArg;

UINT CSeqMain::SERVER_SOCKET_Thread(void* pArg)
{
	WSADATA		wsData;

	SOCKADDR_IN servAddr;
	SOCKADDR_IN clntAddr;
	int			clntAddrSize;
	int			option;
	int			iError;
	int			TimeStamp = FALSE;
	int			TcpNoDelay = TRUE;

	HANDLE		hThread = nullptr;
	DWORD		dwThreadID;

	p_ThrArg = new THRARG;

	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
		printf("WSAStartup() error\n");
	}

	hMutex = CreateMutex(NULL, FALSE, NULL);
	if (hMutex == NULL) {
		printf("CreateMutex() error\n");
	}

	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock == INVALID_SOCKET) {
		printf("socket() error\n");
	}

	option = TRUE;
	iError = setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, sizeof(option));
	if (iError == INVALID_SOCKET) {
		printf("socket option failed: SO_REUSERADDR(%d)\n", WSAGetLastError());
	}

	struct linger LINGER;
	LINGER.l_onoff = 1;     /* SO_LINGER 옵션을 적용한다, TRUE/FALSE */
	LINGER.l_linger = 0;    /* 대기시간 (sec) */
	shutdown(servSock, SD_BOTH); /* 소켓이 닫히기 전에 모든 데이터를 보내고, 수신하도록 확실히 하기 위해서 */
	setsockopt(servSock, SOL_SOCKET, SO_LINGER, (const char*)&LINGER, sizeof(LINGER));  /* 옵션 적용 */

	iError = setsockopt(servSock, IPPROTO_TCP, TCP_NODELAY, (const char*)&TcpNoDelay, sizeof(int));
	printf("*** Nagle Algorithm is disabled ***\n");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(5555);

	//DWORD dwMode = SOCK_MODE_NON_BOLCKING;
	//int nResult = ioctlsocket(servSock, FIONBIO, &dwMode);
	//if (nResult != NO_ERROR) {
	//	printf("ioctlsocket() call failed with error code : %ld\n", nResult);
	//	return false;
	//}

	if (bind(servSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		printf("bind() error\n");
	}

	if (listen(servSock, 5) == SOCKET_ERROR) {
		printf("listen() error\n");
	}

	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	while (!seqMain->m_bSeqExit) {
		clntAddrSize = sizeof(clntAddr);
		clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &clntAddrSize);
		if (clntSock == INVALID_SOCKET) {
			printf("accept() error\n");
		}
		//WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntNumber] = clntSock;						// client socket
		clntAddrs[clntNumber] = inet_ntoa(clntAddr.sin_addr);	// client IP
		clntPorts[clntNumber++] = clntAddr.sin_port;			// client Port
		//ReleaseMutex(hMutex);
		printf("new connection, client IP:%s, PORT:%u\n", inet_ntoa(clntAddr.sin_addr), clntAddr.sin_port);
		seqMain->m_bClientConnect = true;

		p_ThrArg->clntSock = clntSock;
		strcpy(p_ThrArg->clntIP, inet_ntoa(clntAddr.sin_addr));
		p_ThrArg->clntPort = clntAddr.sin_port;

//		if (!strcmp(inet_ntoa(clntAddr.sin_addr), "10.10.1.40")) {
			VisionSocket = clntSock;
			hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ClientVisionConn, (LPVOID)p_ThrArg, 0, &dwThreadID);
//		}
		
		if (hThread == nullptr) {
			printf("Create Thread Error\n");
		}
		Sleep(1);
	}
	WSACleanup();
	delete p_ThrArg;

	printf("SERVER SOCKET Thread Exit\n");

	sprintf(strFileLog, "%s", "SERVER SOCKET Exit");
	LOG_TRACE(strFileLog);

	return 601;
}


//////////////////////////////////////////////////////////////////////////
void CSeqMain::ClientVisionConn(void* arg)
{
	THRARG* p_arg = (THRARG*)arg;
	char clntIP[16];

	SOCKET clientSock = (SOCKET)p_arg->clntSock;
	memcpy(clntIP, p_arg->clntIP, sizeof(p_arg->clntIP));

	int	clntPort = p_arg->clntPort;
	int nReadBytes = 0;
	
	char buf[BUFSIZE];
	int i;

	VISION_HEADER pVisionHeader;

	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	while(!seqMain->m_bSeqExit){
		memset(buf, 0, BUFSIZE);
		int nTotPktLen = 0;
		nReadBytes = recv(clientSock, buf, STX_SIZE + VISION_HEADER_SIZE, 0);
		if (nReadBytes > 0) {
			if (buf[0] == 0x02) {	// STX
				memcpy(&pVisionHeader, &buf[1], VISION_HEADER_SIZE);
				nTotPktLen = pVisionHeader.wMsgLength;

				memset(buf, 0, BUFSIZE);
				nReadBytes = recv(clientSock, buf, pVisionHeader.wMsgLength - STX_SIZE - VISION_HEADER_SIZE, 0); // BODY + ETX Receive
				if (nReadBytes > 0) {
					if (buf[(pVisionHeader.wMsgLength) - VISION_HEADER_SIZE - STX_SIZE - ETX_SIZE] == 0x03){	// ETX
						VISION_PROTOCOL_DATA visionTCPData;
						memset(&visionTCPData, 0x00, sizeof(VISION_PROTOCOL_DATA));
						memcpy(&visionTCPData.VisionHeader, &pVisionHeader, sizeof(VISION_HEADER));
						memcpy(&visionTCPData.bVisionData, buf, pVisionHeader.wMsgLength - VISION_HEADER_SIZE - STX_SIZE - ETX_SIZE);
						ProcessVisionRxData(visionTCPData);
					}
					else {	// Invalid ETX
						printf("IP:%s, Port:%d ETX Invalid\n", clntIP, clntPort);
					}
				}
				else if(nReadBytes == 0){
					printf("IP:%s, Port:%d Client socket disconnected(%d)\n", clntIP, clntPort, WSAGetLastError());
					seqMain->m_bClientConnect = false;
					break;
				}
				else if (nReadBytes == INVALID_SOCKET) {
					printf("IP:%s, Port:%d Client socket disconnected(%d)\n", clntIP, clntPort, WSAGetLastError());
					seqMain->m_bClientConnect = false;
					break;
				}
				else if (nReadBytes < 0) {
					printf("IP:%s, Port:%d Client socket disconnected(%d)\n", clntIP, clntPort, WSAGetLastError());
					seqMain->m_bClientConnect = false;
					break;
				}
			}
			else {	// Invalid STX
				printf("IP:%s, Port:%d STX Invalid\n", clntIP, clntPort);
			}
		}
		else if (nReadBytes == 0) {
			printf("IP:%s, Port:%d Client socket disconnected(%d)\n", clntIP, clntPort, WSAGetLastError());
			seqMain->m_bClientConnect = false;
			break;
		}
		else if (nReadBytes == INVALID_SOCKET) {
			printf("IP:%s, Port:%d Client socket disconnected(%d)\n", clntIP, clntPort, WSAGetLastError());
			seqMain->m_bClientConnect = false;
			break;
		}
		else if (nReadBytes < 0) {
			printf("IP:%s, Port:%d Client socket disconnected(%d)\n", clntIP, clntPort, WSAGetLastError());
			seqMain->m_bClientConnect = false;
			break;
		}
	}

	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntNumber; i++) {
		if (clientSock == clntSocks[i]) {
			for (; i < clntNumber - 1; i++) {
				clntSocks[i] = clntSocks[i + 1];
				clntAddrs[i] = clntAddrs[i + 1];
				clntPorts[i] = clntPorts[i + 1];
				break;
			}
		}
	}
	clntNumber--;
	ReleaseMutex(hMutex);
	if (clientSock == VisionSocket) {
		closesocket(VisionSocket);
	}
	closesocket(clientSock);
	shutdown(clientSock, SD_BOTH);
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::ProcessVisionRxData(VISION_PROTOCOL_DATA VisionData)
{
	memset(&VisionHeader, 0x00, sizeof(VISION_HEADER));
	memcpy(&VisionHeader, &VisionData.VisionHeader, sizeof(VISION_HEADER));

	memset(&VisionRXData, 0x00, sizeof(VISION_RX_DATA));
	memcpy(&VisionRXData, VisionData.bVisionData, sizeof(VISION_RX_DATA));
	
	if (VisionHeader.bCameraNumber == 1) {
		memset(&V1RxData, 0x00, sizeof(VISION_RX_DATA));
		memcpy(&V1RxData, VisionData.bVisionData, sizeof(VISION_RX_DATA));
		bit.TopV1DataReceived = 1;
		LOG_TRACE("bit.TopV1DataReceived = 1;");
	}
	else if (VisionHeader.bCameraNumber == 2) {
		memset(&V2RxData, 0x00, sizeof(VISION_RX_DATA));
		memcpy(&V2RxData, VisionData.bVisionData, sizeof(VISION_RX_DATA));
		bit.TopV2DataReceived = 1;
		LOG_TRACE("bit.TopV2DataReceived = 1;");
	}
	else if (VisionHeader.bCameraNumber == 3) {
		memset(&V3RxData, 0x00, sizeof(VISION_RX_DATA));
		memcpy(&V3RxData, VisionData.bVisionData, sizeof(VISION_RX_DATA));
		bit.BtmVDataReceived = 1;
		LOG_TRACE("bit.BtmVDataReceived = 1;");
	}

	printf("============================================================\n");
	printf("VisionHeader.wMsgLength = %d\n",			VisionHeader.wMsgLength);
	printf("VisionHeader.bCameraNumber = %d\n",		VisionHeader.bCameraNumber);
	printf("VisionHeader.bMsgCode = %d\n",				VisionHeader.bMsgCode);

	printf("VisionRXData.bCommand = %d\n",				VisionRXData.byCommand);
	printf("VisionRXData.wRecipeNo = %d\n",				VisionRXData.wRecipeNo);
	printf("VisionRXData.strRecipeID[20] = %.20s\n",		VisionRXData.strRecipeID);
	printf("VisionRXData.strUnitXSize[5] = %.5s\n",		VisionRXData.strUnitXSize); 
	printf("VisionRXData.strUnitYSize[5] = %.5s\n",		VisionRXData.strUnitYSize);
	printf("VisionRXData.bSnapXCnt = %d\n",				VisionRXData.bySnapXCnt);
	printf("VisionRXData.bSnapYCnt = %d\n",				VisionRXData.bySnapYCnt);
	printf("VisionRXData.bTrigNo = %d\n",					VisionRXData.byTrigNo);
	printf("VisionRXData.bPointNo = %d\n",				VisionRXData.byPointNo);
	printf("VisionRXData.bInspectionType = %d\n",		VisionRXData.byInspectionType);
	printf("VisionRXData.bBallResult = %d\n",				VisionRXData.byBallResult);
	printf("VisionRXData.bMarkResult = %d\n",			VisionRXData.byMarkResult);
	printf("VisionRXData.strPk1OffsetX[5] = %.5s\n",		VisionRXData.strPk1OffsetX);
	printf("VisionRXData.strPk1OffsetY[5] = %.5s\n",		VisionRXData.strPk1OffsetY);
	printf("VisionRXData.strPk1OffsetT[5] = %.5s\n",		VisionRXData.strPk1OffsetT);
	printf("VisionRXData.strPk2OffsetX[5] = %.5s\n",		VisionRXData.strPk2OffsetX);
	printf("VisionRXData.strPk2OffsetY[5] = %.5s\n",		VisionRXData.strPk2OffsetY);
	printf("VisionRXData.strPk2OffsetT[5] = %.5s\n",		VisionRXData.strPk2OffsetT);
	printf("VisionRXData.strPk3OffsetX[5] = %.5s\n",		VisionRXData.strPk3OffsetX);
	printf("VisionRXData.strPk3OffsetY[5] = %.5s\n",		VisionRXData.strPk3OffsetY);
	printf("VisionRXData.strPk3OffsetT[5] = %.5s\n",		VisionRXData.strPk3OffsetT);
	printf("VisionRXData.strPk4OffsetX[5] = %.5s\n",		VisionRXData.strPk4OffsetX);
	printf("VisionRXData.strPk4OffsetY[5] = %.5s\n",		VisionRXData.strPk4OffsetY);
	printf("VisionRXData.strPk4OffsetT[5] = %.5s\n",		VisionRXData.strPk4OffsetT);
	printf("VisionRXData.strPk5OffsetX[5] = %.5s\n",		VisionRXData.strPk5OffsetX);
	printf("VisionRXData.strPk5OffsetY[5] = %.5s\n",		VisionRXData.strPk5OffsetY);
	printf("VisionRXData.strPk5OffsetT[5] = %.5s\n",		VisionRXData.strPk5OffsetT);
	printf("VisionRXData.strPk6OffsetX[5] = %.5s\n",		VisionRXData.strPk6OffsetX);
	printf("VisionRXData.strPk6OffsetY[5] = %.5s\n",		VisionRXData.strPk6OffsetY);
	printf("VisionRXData.strPk6OffsetT[5] = %.5s\n",		VisionRXData.strPk6OffsetT);
	printf("VisionRXData.strPk7OffsetX[5] = %.5s\n",		VisionRXData.strPk7OffsetX);
	printf("VisionRXData.strPk7OffsetY[5] = %.5s\n",		VisionRXData.strPk7OffsetY);
	printf("VisionRXData.strPk7OffsetT[5] = %.5s\n",		VisionRXData.strPk7OffsetT);
	printf("VisionRXData.strPk8OffsetX[5] = %.5s\n",		VisionRXData.strPk8OffsetX);
	printf("VisionRXData.strPk8OffsetY[5] = %.5s\n",		VisionRXData.strPk8OffsetY);
	printf("VisionRXData.strPk8OffsetT[5] = %.5s\n",		VisionRXData.strPk8OffsetT);

	double Pk1offsetX = stod(VisionRXData.strPk1OffsetX);
	double Pk1offsetY = stod(VisionRXData.strPk1OffsetY);
	double Pk1offsetT = stod(VisionRXData.strPk1OffsetT);

	double Pk2offsetX = stod(VisionRXData.strPk2OffsetX);
	double Pk2offsetY = stod(VisionRXData.strPk2OffsetY);
	double Pk2offsetT = stod(VisionRXData.strPk2OffsetT);

	double Pk3offsetX = stod(VisionRXData.strPk3OffsetX);
	double Pk3offsetY = stod(VisionRXData.strPk3OffsetY);
	double Pk3offsetT = stod(VisionRXData.strPk3OffsetT);

	double Pk4offsetX = stod(VisionRXData.strPk4OffsetX);
	double Pk4offsetY = stod(VisionRXData.strPk4OffsetY);
	double Pk4offsetT = stod(VisionRXData.strPk4OffsetT);

	double Pk5offsetX = stod(VisionRXData.strPk5OffsetX);
	double Pk5offsetY = stod(VisionRXData.strPk5OffsetY);
	double Pk5offsetT = stod(VisionRXData.strPk5OffsetT);

	double Pk6offsetX = stod(VisionRXData.strPk6OffsetX);
	double Pk6offsetY = stod(VisionRXData.strPk6OffsetY);
	double Pk6offsetT = stod(VisionRXData.strPk6OffsetT);

	double Pk7offsetX = stod(VisionRXData.strPk7OffsetX);
	double Pk7offsetY = stod(VisionRXData.strPk7OffsetY);
	double Pk7offsetT = stod(VisionRXData.strPk7OffsetT);

	double Pk8offsetX = stod(VisionRXData.strPk8OffsetX);
	double Pk8offsetY = stod(VisionRXData.strPk8OffsetY);
	double Pk8offsetT = stod(VisionRXData.strPk8OffsetT);
	printf("VisionRXData.Pk1offsetX = %.3f\n", Pk1offsetX);
	printf("VisionRXData.Pk1offsetY = %.3f\n", Pk1offsetY);
	printf("VisionRXData.Pk1offsetT = %.3f\n", Pk1offsetT);


	
}

void CSeqMain::SendVision(int CameraNo, VISION_TX_DATA TxData)
{
	VISION_PROTOCOL_DATA VisionData;
	memset(&VisionData, 0x00, sizeof(VISION_PROTOCOL_DATA));

	VisionData.VisionHeader.wMsgLength = STX_SIZE + sizeof(VISION_HEADER) + sizeof(VISION_TX_DATA) + ETX_SIZE;
	VisionData.VisionHeader.bCameraNumber = CameraNo;
	VisionData.VisionHeader.bMsgCode = 0x01;

	memcpy(VisionData.bVisionData, &TxData, VisionData.VisionHeader.wMsgLength - sizeof(VISION_HEADER) - ETX_SIZE);

	BYTE buf[BUFSIZE];
	memset(buf, 0x00, BUFSIZE);

	BYTE* ptr;
	ptr = buf;
	*ptr = 0x02;	// STX
	ptr++;

	memcpy(ptr, &VisionData, VisionData.VisionHeader.wMsgLength - STX_SIZE - ETX_SIZE);
	ptr += (VisionData.VisionHeader.wMsgLength - STX_SIZE - ETX_SIZE);
	*ptr = 0x03;	// STX

	int nWriteBytes = send(VisionSocket, (char *)buf, VisionData.VisionHeader.wMsgLength, 0);
}

size_t CSeqMain::SERVER_SEND_MSG_ALL(char* sendmsg, char* format, ...)
{
	va_list args;
	va_start(args, format);
	vsprintf(sendmsg, format, args);
	va_end(args);

	for (int i = 0; i < clntNumber; i++) {
		send(clntSocks[i], sendmsg, sizeof(sendmsg), 0);
	}
	return strlen(sendmsg);
}
//////////////////////////////////////////////////////////////////////////
size_t CSeqMain::SERVER_SEND_MSG(char IP[], int port, char* sendmsg, char* format, ...)
{	// SEND_MSG("127.0.0.1",5000,send_msg,"%s","aaa");
	va_list args;
	va_start(args, format);
	vsprintf(sendmsg, format, args);
	va_end(args);

	for (int i = 0; i < clntNumber; i++) {
		if (!strcmp(clntAddrs[i], IP)) {
			send(clntSocks[i], sendmsg, sizeof(sendmsg), 0);
		}
	}
	return strlen(sendmsg);
}
//////////////////////////////////////////////////////////////////////////
size_t CSeqMain::SERVER_SEND_MSG(SOCKET s, char* format, ...)
{
	char buf[1024] = { 0, };
	WaitForSingleObject(hMutex, INFINITE);
	va_list args;
	va_start(args, format);
	vsprintf(buf, format, args);
	va_end(args);

	send(s, buf, strlen(buf)+1, 0);
	ReleaseMutex(hMutex);
	return strlen(buf);
}
void CSeqMain::DecodeMSG(int n_strlen, char msg[2052])
{
	int i;
	char* pStrpara;
	char	seps[] = "+,=";
	char* token;

	pStrpara = msg;
	token = strtok(pStrpara, seps);

	i = 0;
	while (token != NULL) {
		// ex) 0x02+CNT+999,R=1,+0x03
		switch (i) {
		case 0:
			// STX 0x02
			if (msg[0] == 0x02)
				printf("STX");
			nVisionResultUnitCount = 0;
			break;
		case 1:
			if (strcmp("CNT", token) == 0) {
				printf("+CNT");
			}
			// CNT
			break;
		case 2:
			// 개수
			nVisionResultUnitCount = atoi(token);
			printf("nVisionResultUnitCount=%d\n", nVisionResultUnitCount);
			bit.VisionDataReceived = 1;
			break;
		case 3:
			// R -> Result
			printf("R=%s", token);
			break;
		case 4:
			// ETX 0x03
			if (msg[0] == 0x03)
				printf("ETX");

		default:
			break;
		}
		i++;
		if (i == 5) {
			break;
		}
		token = strtok(NULL, seps);
	}
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::ParseResult(char strpara[])
{
	int i;
	char* pStrpara;
	char	seps[] = "|,\t\n[]=";
	char* token;

	pStrpara = strpara;
	token = strtok(pStrpara, seps);

	i = 0;
	while (token != NULL) {
		switch (i) {
		case 0:
		default:
			break;
		}
		i++;
		if (i == 1) {
			break;
		}
		token = strtok(NULL, seps);
	}
}
//////////////////////////////////////////////////////////////////////////
size_t CSeqMain::MakePacket(char* sendmsg, char* format, ...)
{
	va_list args;
	va_start(args, format);
	vsprintf(sendmsg, format, args);
	va_end(args);

	return strlen(sendmsg);
}


