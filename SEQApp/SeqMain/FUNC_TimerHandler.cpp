#include "..\pch.h"
#include "CLASS_Main.h"



//////////////////////////////////////////////////////////////////////////
//void CALLBACK CSeqMain::TimerHandler(UINT _timerid, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2)
void CALLBACK CSeqMain::TimerHandler(UINT _timerid, UINT msg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{

	//	long m_AI_ChannelNum[4];
//	double m_dVolt[4];
//
//	AxaiSwReadMultiVoltage(4, m_AI_ChannelNum, m_dVolt);
//	printf("CH[0] : m_dVlot[0]=%.3f\t\t 	CH[4] : m_dVlot[4]=%.3f\n", m_dVolt[0], m_dVolt[4]);
//
////	A1_ValveLaserDistance = 17.1875*x - 43.75;
//
	//double m_dValue1;
	//AxaiSwReadVoltage(0, &m_dValue1);
	////	printf("A1 Analog Value : m_dValue1=%.3lf\n", m_dValue1);
	//	//slope = (300-25)/(20-4) = 17.1876
	//A1_ValveLaserDistance = 17.1876 * m_dValue1 - 43.75;
	////	printf("A1_ValveLaserDistance =%.3lf\n", A1_ValveLaserDistance);

}
