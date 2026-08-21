#include "..\pch.h"
#include "..\SEQAppDlg.h"
#include "..\SeqMain\CLASS_Main.h"

//////////////////////////////////////////////////////////////////////////
UINT CSeqMain::RS232_Thread(void* pArg)
{
	CSeqMain* seqMain = CSeqMain::GetInstance();
	assert(seqMain != nullptr);

	CSEQAppDlg* pMain = (CSEQAppDlg*)pArg;

	Rs232Ionizer.CommServer = RS232_Comm1;
	// 	CommPacket2.CommServer = RS232_Comm2;

	while (!seqMain->m_bSeqExit)
	{
		Rs232Ionizer.Thread();
		Sleep(1);
//		WaitForSingleObject(pMain->m_pThread_SeqRS232, 1);
	}
	printf("RS232 Thread1 Exit\n");

	sprintf(strFileLog, "%s", "RS232 Thread1 Exit");
	LOG_TRACE(strFileLog);

	return 401;
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::RS232_Comm1(char packet[], CCommPacket* ComPacket)
{
	printf("Packet 1 Received= %s\n", packet);
	bit.Comm1PacketReceived = 1;
	// 	int i;
	// 	char	*pStrpara;
	// 	char	seps[]="|,\t\n;";
	// 	char	*token;
	// 
	// 	pStrpara = packet;
	// 	token    = strtok(pStrpara,seps);
	// 
	// 	i=0;
	// 	while(token!=NULL){
	// 		switch(i){
	// 			case 0:
	// 				printf("token=%s\n",token);	
	// 				break;
	// 			case 1:
	// 				printf("token=%s\n",token);
	// 				break;
	// 			case 2:
	// 				printf("token=%s\n",token);
	// 				break;
	// 			default:
	// 				break;
	// 		}
	// 		i++;
	// 		if(i==3){
	// 			break;
	// 		}
	// 		token = strtok(NULL,seps);
	// 	}
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::RS232_Comm2(char packet[], CCommPacket* ComPacket)
{
	printf("Packet 2 Received= %s\n", packet);
	bit.Comm2PacketReceived = 1;
	// 	int i;
	// 	char	*pStrpara;
	// 	char	seps[]="|,\t\n;";
	// 	char	*token;
	// 
	// 	pStrpara = packet;
	// 	token    = strtok(pStrpara,seps);
	// 
	// 	i=0;
	// 	while(token!=NULL){
	// 		switch(i){
	// 			case 0:
	// 				printf("token=%s\n",token);	
	// 				break;
	// 			case 1:
	// 				printf("token=%s\n",token);
	// 				break;
	// 			case 2:
	// 				printf("token=%s\n",token);
	// 				break;
	// 			default:
	// 				break;
	// 		}
	// 		i++;
	// 		if(i==3){
	// 			break;
	// 		}
	// 		token = strtok(NULL,seps);
	// 	}
}
