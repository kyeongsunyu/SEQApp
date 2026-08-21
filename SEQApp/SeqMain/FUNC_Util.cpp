#include "..\pch.h"
#include "CLASS_Main.h"
#include "Define\DEFINE_WinMsg.h"
#include <algorithm>
#include <vector>

#define SEND_MESSAGE_TIME_OUT	3000

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Wait(1000)==Sleep(1)                                                 */
/* Wait(1000) »ç¿ë½Ã CPU Á¡À¯À² Áõ°¡                                    */
/************************************************************************/
void CSeqMain::Wait(int tm_delay)
{
	LARGE_INTEGER freq, start, end;

	if (QueryPerformanceFrequency(&freq)) {
		QueryPerformanceCounter(&start);
		QueryPerformanceCounter(&end);
		while (((double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000000) < tm_delay)
			QueryPerformanceCounter(&end);
	}
	else Sleep(1);
}
//////////////////////////////////////////////////////////////////////////

void CSeqMain::SetMZSlotAllExist(WORD WhichMZ)
{
	//if (WhichMZ == LOADER_MZ1) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.LdMZ1Slot[i] = SLOT_EXIST;
	//	}
	//}
	//if (WhichMZ == LOADER_MZ2) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.LdMZ2Slot[i] = SLOT_EXIST;
	//	}
	//}
	//if (WhichMZ == LOADER_MZ3) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.LdMZ3Slot[i] = SLOT_EXIST;
	//	}
	//}
	//if (WhichMZ == LOADER_MZ4) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.LdMZ4Slot[i] = SLOT_EXIST;
	//	}
	//}

	//if (WhichMZ == UNLOADER_MZ1) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.ULdMZ1Slot[i] = SLOT_EXIST;
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ2) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.ULdMZ2Slot[i] = SLOT_EXIST;
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ3) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.ULdMZ3Slot[i] = SLOT_EXIST;
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ4) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.ULdMZ3Slot[i] = SLOT_EXIST;
	//	}
	//}
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::SetMZSlotAllEmpty(WORD WhichMZ)
{
	//if (WhichMZ == LOADER_MZ1) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.LdMZ1Slot[i] = SLOT_EMPTY;
	//	}
	//}
	//if (WhichMZ == LOADER_MZ2) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.LdMZ2Slot[i] = SLOT_EMPTY;
	//	}
	//}
	//if (WhichMZ == LOADER_MZ3) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.LdMZ3Slot[i] = SLOT_EMPTY;
	//	}
	//}
	//if (WhichMZ == LOADER_MZ4) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.LdMZ4Slot[i] = SLOT_EMPTY;
	//	}
	//}

	//if (WhichMZ == UNLOADER_MZ1) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.ULdMZ1Slot[i] = SLOT_EMPTY;
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ2) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.ULdMZ2Slot[i] = SLOT_EMPTY;
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ3) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.ULdMZ3Slot[i] = SLOT_EMPTY;
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ4) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		MachineStatus.ULdMZ4Slot[i] = SLOT_EMPTY;
	//	}
	//}
}
//////////////////////////////////////////////////////////////////////////
int CSeqMain::FindFirstMZSlotExist(WORD WhichMZ)
{
	//if (WhichMZ == LOADER_MZ1) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.LdMZ1Slot[i]== SLOT_EXIST) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == LOADER_MZ2) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.LdMZ2Slot[i] == SLOT_EXIST) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == LOADER_MZ3) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.LdMZ3Slot[i] == SLOT_EXIST) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == LOADER_MZ4) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.LdMZ4Slot[i] == SLOT_EXIST) {
	//			return i;
	//		}
	//	}
	//}

	//if (WhichMZ == UNLOADER_MZ1) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.ULdMZ1Slot[i] == SLOT_EXIST) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ2) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.ULdMZ2Slot[i] == SLOT_EXIST) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ3) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.ULdMZ3Slot[i] == SLOT_EXIST) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ4) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.ULdMZ4Slot[i] == SLOT_EXIST) {
	//			return i;
	//		}
	//	}
	//}
	return -1;
}
//////////////////////////////////////////////////////////////////////////
int CSeqMain::FindFirstMZSlotEmpty(WORD WhichMZ)
{
	//if (WhichMZ == LOADER_MZ1) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.LdMZ1Slot[i]== SLOT_EMPTY) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == LOADER_MZ2) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.LdMZ2Slot[i] == SLOT_EMPTY) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == LOADER_MZ3) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.LdMZ3Slot[i] == SLOT_EMPTY) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == LOADER_MZ4) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.LdMZ4Slot[i] == SLOT_EMPTY) {
	//			return i;
	//		}
	//	}
	//}

	//if (WhichMZ == UNLOADER_MZ1) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.ULdMZ1Slot[i] == SLOT_EMPTY) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ2) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.ULdMZ2Slot[i] == SLOT_EMPTY) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ3) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.ULdMZ3Slot[i] == SLOT_EMPTY) {
	//			return i;
	//		}
	//	}
	//}
	//if (WhichMZ == UNLOADER_MZ4) {
	//	for (int i = 0; i < DeviceData.MZSlotCnt; i++) {
	//		if (MachineStatus.ULdMZ4Slot[i] == SLOT_EMPTY) {
	//			return i;
	//		}
	//	}
	//}
	return -1;
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::SetMZSlotExist(WORD WhichMZ, WORD pos)
{
	//if (WhichMZ == LOADER_MZ1) {
	//	MachineStatus.LdMZ1Slot[pos] = SLOT_EXIST;
	//}
	//else if (WhichMZ == LOADER_MZ2) {
	//	MachineStatus.LdMZ2Slot[pos] = SLOT_EXIST;
	//}
	//else if (WhichMZ == LOADER_MZ3) {
	//	MachineStatus.LdMZ3Slot[pos] = SLOT_EXIST;
	//}
	//else if (WhichMZ == LOADER_MZ4) {
	//	MachineStatus.LdMZ4Slot[pos] = SLOT_EXIST;
	//}

	//else if (WhichMZ == UNLOADER_MZ1) {
	//	MachineStatus.ULdMZ1Slot[pos] = SLOT_EXIST;
	//}
	//else if (WhichMZ == UNLOADER_MZ2) {
	//	MachineStatus.ULdMZ2Slot[pos] = SLOT_EXIST;
	//}
	//else if (WhichMZ == UNLOADER_MZ3) {
	//	MachineStatus.ULdMZ3Slot[pos] = SLOT_EXIST;
	//}
	//else if (WhichMZ == UNLOADER_MZ4) {
	//	MachineStatus.ULdMZ4Slot[pos] = SLOT_EXIST;
	//}
}
void CSeqMain::SetMZSlotEmpty(WORD WhichMZ, WORD pos)
{
	/*if (WhichMZ == LOADER_MZ1) {
		MachineStatus.LdMZ1Slot[pos] = SLOT_EMPTY;
	}
	else if (WhichMZ == LOADER_MZ2) {
		MachineStatus.LdMZ2Slot[pos] = SLOT_EMPTY;
	}
	else if (WhichMZ == LOADER_MZ3) {
		MachineStatus.LdMZ3Slot[pos] = SLOT_EMPTY;
	}
	else if (WhichMZ == LOADER_MZ4) {
		MachineStatus.LdMZ4Slot[pos] = SLOT_EMPTY;
	}
	else if (WhichMZ == UNLOADER_MZ1) {
		MachineStatus.ULdMZ1Slot[pos] = SLOT_EMPTY;
	}
	else if (WhichMZ == UNLOADER_MZ2) {
		MachineStatus.ULdMZ2Slot[pos] = SLOT_EMPTY;
	}
	else if (WhichMZ == UNLOADER_MZ3) {
		MachineStatus.ULdMZ3Slot[pos] = SLOT_EMPTY;
	}
	else if (WhichMZ == UNLOADER_MZ4) {
		MachineStatus.ULdMZ4Slot[pos] = SLOT_EMPTY;
	}*/
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::InitMZ(WORD WhichMZ)
{
	/*if (WhichMZ == LOADER_MZ1) {
		memset(MachineStatus.LdMZ1Slot, 0, sizeof(MachineStatus.LdMZ1Slot));
	}
	if (WhichMZ == LOADER_MZ2) {
		memset(MachineStatus.LdMZ2Slot, 0, sizeof(MachineStatus.LdMZ2Slot));
	}
	if (WhichMZ == LOADER_MZ3) {
		memset(MachineStatus.LdMZ3Slot, 0, sizeof(MachineStatus.LdMZ3Slot));
	}
	if (WhichMZ == LOADER_MZ4) {
		memset(MachineStatus.LdMZ4Slot, 0, sizeof(MachineStatus.LdMZ4Slot));
	}

	if (WhichMZ == UNLOADER_MZ1) {
		memset(MachineStatus.ULdMZ1Slot, 0, sizeof(MachineStatus.ULdMZ1Slot));
	}
	if (WhichMZ == UNLOADER_MZ2) {
		memset(MachineStatus.ULdMZ2Slot, 0, sizeof(MachineStatus.ULdMZ2Slot));
	}
	if (WhichMZ == UNLOADER_MZ3) {
		memset(MachineStatus.ULdMZ3Slot, 0, sizeof(MachineStatus.ULdMZ3Slot));
	}
	if (WhichMZ == UNLOADER_MZ4) {
		memset(MachineStatus.ULdMZ4Slot, 0, sizeof(MachineStatus.ULdMZ4Slot));
	}*/
}
//////////////////////////////////////////////////////////////////////////
bool CSeqMain::ISBITON(int data, int BitNo)
{
	if (data & (1 << BitNo)) {
		return true;
	}
	else {
		return false;
	}
}
void CSeqMain::BITONOFF(int* data, int BitNo, bool ONOFF)
{
	ONOFF ? ((*data) | (1 << BitNo)) : ((*data) & (~(1 << BitNo)));
}
int CSeqMain::BITCHANGE(int data, int BitNo)
{
	if (ISBITON(data, BitNo)) {
		(data & (~(1 << BitNo)));
	}
	else {
		(data | (1 << BitNo));
	}
	return data;
}
unsigned CSeqMain::getbits(unsigned x, int p, int n)
{
	/* get n bits from position p */
	return (x >> (p + 1 - n)) & ~(~0 << n);
}
//////////////////////////////////////////////////////////////////////////
void CSeqMain::max_min(double* d_arr, int n_size, double& max, double& min)
{	// double comp[20]
	// max_min(&comp[0], comp_max, comp_min);
	max = *d_arr;
	min = *d_arr;

	for (int i = 0; i < n_size; i++) {
		if (max < *(d_arr + i))	max = *(d_arr + i);
		if (min > *(d_arr + i))	min = *(d_arr + i);
	}
}

bool CSeqMain::SendCopyDataToMMI(WORD msg, WORD size, LPVOID ptrData)
{
	bool sendResult = false;

	COPYDATASTRUCT copyData;
	memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));

	copyData.dwData = msg;
	copyData.cbData = size;
	copyData.lpData = ptrData;

	HWND handle = FindWindowA(NULL, "MMIApp");
	if (handle != NULL)
	{
		sendResult = SendMessageTimeout(handle, WM_COPYDATA, 0, (LPARAM)&copyData, 0, SEND_MESSAGE_TIME_OUT, 0);
	}
	return sendResult;
}
bool CSeqMain::SendSeqRspToMMI(WORD msg, WORD size, SEQ_RSP seq_rsp)
{
	bool sendResult = false;

	COPYDATASTRUCT copyData;
	memset(&copyData, 0x00, sizeof(COPYDATASTRUCT));

	copyData.dwData = msg;
	copyData.cbData = size;
	copyData.lpData = (void*)&seq_rsp;

	HWND handle = FindWindowA(NULL, "MMIApp");
	if (handle != NULL)
	{
		sendResult = SendMessageTimeout(handle, WM_COPYDATA, 0, (LPARAM)&copyData, 0, SEND_MESSAGE_TIME_OUT, 0);
	}
	return sendResult;
}
void CSeqMain::SendPostMessage(WORD msgNo, WORD target)
{
	HWND targetHWND = NULL;

	if (target == MMI_MODULE)
	{
		targetHWND = FindWindowA(NULL, "MMIApp");
		if (targetHWND != NULL)
		{
			PostMessage(targetHWND, msgNo, 0, 0);
		}
	}
	else if (target == COMM_MODULE)
	{
		targetHWND = FindWindowA(NULL, "COMMUNICATION_App");
		if (targetHWND != NULL)
		{
			PostMessage(targetHWND, msgNo, 0, 0);
		}
	}
	else if (target == ALL_MODULE)
	{
		targetHWND = FindWindowA(NULL, "SEQ_App");
		if (targetHWND != NULL)
		{
			PostMessage(targetHWND, msgNo, 0, 0);
		}

		targetHWND = FindWindowA(NULL, "COMMUNICATION_App");
		if (targetHWND != NULL)
		{
			PostMessage(targetHWND, msgNo, 0, 0);
		}
	}
}
bool CSeqMain::LevelUp_Privileges()
{
	HANDLE hProc = NULL;
	HANDLE hToken = NULL;

	LUID luid;
	TOKEN_PRIVILEGES tp;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
		{
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			tp.Privileges[0].Luid = luid;
			tp.PrivilegeCount = 1;
			AdjustTokenPrivileges(hToken, false, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
			return true;
		}
	}
	return false;
}
void CSeqMain::FlipArray(int Row, int Col, int A[50][50], int dir)
{
	// N : 행의 갯수
	// M : 열의 갯수
	// A : 2차원 배열
	// d : 상하 or 좌우 반전
	//int B[N][M];
	//copy(&A[0][0], &A[0][0] + N * M, &B[0][0]);

	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < M; j++) {
	//		if (dir == 0) {
	//			A[i][j] = B[N - 1 - i][j];	// 좌우 반전
	//		}
	//		else {
	//			A[i][j] = B[i][M - 1 - j];	// 상하 반전
	//		}
	//			
	//	}
	//}
	/////////
	vector<vector<int>> vtB(Row, vector<int >(Col));
	//vtB.clear();
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++) {
			vtB[i][j] = A[i][j];
		}
	}

	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			if (dir == 0) {
				A[i][j] = vtB[Row - 1 - i][j];	// 좌우 반전
			}
			else {
				A[i][j] = vtB[i][Col - 1 - j];	// 상하 반전
			}
		}
	}
	// 사용법
	/*int map[100][100];
	int row = 13;
	int col = 15;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j] = i * col + j;
		}
	}
	printf("=============================\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%2d,", map[i][j]);
		}
		printf("\n\n");
	}
	printf("------------------------------\n");
	FlipArray(row, col, map, 1);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%2d,", map[i][j]);
		}
		printf("\n\n");
	}
	printf("=============================\n");*/
}
void CSeqMain::RotateArray(int Row, int Col, int A[100][100], int deg)
{
	int B[100][100];
		
	copy(&A[0][0], &A[0][0] + 100 * 100, &B[0][0]);
	
	for (int i = 0; i < Col; i++) {
		for (int j = 0; j < Row; j++) {
			if (deg == 90) {
				A[i][j] = B[Row - 1 - j][i];
			}
			else if (deg == -90) {
				A[i][j] = B[j][Col - 1 - i];
			}
			else if (deg == 180) {
				A[Row - 1 - j][Col - 1 - i] = B[j][i];
			}
			else if (deg == -1) {	// transpose
				A[i][j] = B[j][i];		
			}
		}
	}
}

template<typename T>
inline T limit(const T& value)
{
	return ((value > 255) ? 255 : ((value < 0) ? 0 : value));
}


