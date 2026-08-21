#include "..\pch.h"
#include "CLASS_Main.h"
#include "DEFINE_GVX.h"

//////////////////////////////////////////////////////////////////////////
void CSeqMain::Sequence(void)
{
	if (!ErrorProcedure()) {
		if (bit.AutoRun) {
			AutoRun();
		}
		//CommonCycle();
		MTBA_MTBF();
	}
	CommonCycle();
	//MTBA_MTBF();

	if (bit.ComTestCucle) {
//		SEND_MSG_ALL("%s", "server test");
		bit.ComTestCucle = 0;
	}

}
