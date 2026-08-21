#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"

shared_ptr<CSeqMain> CSeqMain::m_pInstance(0);

CSeqMain::CSeqMain()
{



}
CSeqMain::~CSeqMain()
{
	ObjectDelete();
}

CSeqMain* CSeqMain::GetInstance()
{
	if (!m_pInstance.get())
	{
		m_pInstance.reset(new CSeqMain());

		return (CSeqMain*)m_pInstance.get();
	}
	else
	{
		return (CSeqMain*)m_pInstance.get();
	}
}

