#pragma once

#include <windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <time.h>
#include <tuple>

//-------------------------------//
#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

#define MMFSIZE   (250000)

#define MAX_WORKTABLE	2

using _NV_BIT = struct
{
	BITTYPE bitbuf[25];
};

using _NV_COUNT = struct
{
	int UPH;
	int TPH;

	int PanelInCnt;
	int UnitInCnt;
	int UnitOutCnt;

	int SpongeCleanCnt;
	int WaterJetAirCleanCnt;
	int SawPkFlipY1AirClenaCnt;
	int SawPkFlipY2AirClenaCnt;
	int FlipY1AirCleanCnt;
	int FlipY2AirCleanCnt;
	int PalletY1AirCleanCnt;
	int PalletY2AirCleanCnt;

	int UnitGoodCnt;
	int UnitReworkCnt;
	int UnitNGCnt;
};
using _NV_FLIP1_MAP = struct
{
	int Map[50][50];
};
using _NV_FLIP2_MAP = struct
{
	int Map[50][50];
};
using _NV_PALLET1_MAP = struct
{
	int Map[50][50];
};
using _NV_PALLET2_MAP = struct
{
	int Map[50][50];
};
using _NV_GOODTRAY1_MAP = struct
{
	int Map[50][50];
};
using _NV_GOODTRAY2_MAP = struct
{
	int Map[50][50];
};
using _NV_REWORKTRAY_MAP = struct
{
	int Map[50][50];
};
using _NV_NGTRAY_MAP = struct
{
	int Map[50][50];
};

using _NV_FLIP1_RESULT = struct
{
	int Result[50][50];
};
using _NV_FLIP2_RESULT = struct
{
	int Result[50][50];
};
using _NV_PALLET1_RESULT = struct
{
	int Result[50][50];
};
using _NV_PALLET2_RESULT = struct
{
	int Result[50][50];
};
using _NV_FRONT_PK_RESULT = struct
{
	int Result[10];
};
using _NV_REAR_PK_RESULT = struct
{
	int Result[10];
};
using _NV_GOOD_TRAY1_RESULT = struct
{
	int Result[50][50];
};
using _NV_GOOD_TRAY2_RESULT = struct
{
	int Result[50][50];
};
using _NV_REWORK_TRAY_RESULT = struct
{
	int Result[50][50];
};
using _NV_NG_TRAY_RESULT = struct
{
	int Result[50][50];
};
using _MMF = struct
{
	_NV_BIT NVBit;
	
	_NV_COUNT NVCount;
	
	_NV_FLIP1_MAP NVFlip1Map;
	_NV_FLIP2_MAP NVFlip2Map;
	_NV_PALLET1_MAP NVPallet1Map;
	_NV_PALLET2_MAP NVPallet2Map;
	_NV_GOODTRAY1_MAP NVGoodTray1Map;
	_NV_GOODTRAY2_MAP NVGoodTray2Map;
	_NV_REWORKTRAY_MAP NVReworkTrayMap;
	_NV_NGTRAY_MAP NVNGTrayMap;

	_NV_FLIP1_RESULT NVFlip1Result;
	_NV_FLIP2_RESULT NVFlip2Result;
	_NV_PALLET1_RESULT NVPallet1Result;
	_NV_PALLET2_RESULT NVPallet2Result;
	_NV_FRONT_PK_RESULT NVFrontPkResult;
	_NV_REAR_PK_RESULT NVRearPkResult;
	_NV_GOOD_TRAY1_RESULT NVGoodTray1Result;
	_NV_GOOD_TRAY2_RESULT NVGoodTray2Result;
	_NV_REWORK_TRAY_RESULT NVReworkTrayResult;
	_NV_NG_TRAY_RESULT NVNGTrayResult;
};

//-------------------------------//
class CNVMMF
{
protected:
	HANDLE hFile, hMap;
	PVOID pLoc;
protected:
	void CleanObject(void)
	{
		if (pLoc != nullptr)
		{
			UnmapViewOfFile(pLoc);
		}
		if (hMap != nullptr)
		{
			CloseHandle(hMap);
		}
		if (hFile)
		{
			CloseHandle(hFile);
		}
	}

public:
	CNVMMF()
	{
		InitObject();
	}

	~CNVMMF()
	{
		CleanObject();
	}

	BOOL InitObject()
	{
		pLoc = nullptr;

		int nSize = sizeof(_MMF);
		hFile = CreateFile(_T("C:\\Work\\NV.map"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
			nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE != hFile)
		{
			hMap = CreateFileMapping(hFile, nullptr, PAGE_READWRITE, 0, MMFSIZE, _T("MMF_MAP"));
			if (nullptr == hMap)
			{
				printf("\nShared Memory Allocate CreateFileMapping Error\n");
				return FALSE;
			}
			pLoc = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, MMFSIZE);
			if (pLoc == nullptr)
			{
				printf("\nShared Memory Allocation MapViewOfFile Error\n");
				return FALSE;
			}
		}
		return TRUE;
	}

	_NV_BIT GetBit()
	{
		_NV_BIT nvmap = ((_MMF*)pLoc)->NVBit;
		return nvmap;
	}

	template <typename T1>
	bool SetBit(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVBit = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}


	_NV_COUNT GetCount()
	{
		_NV_COUNT nvmap = ((_MMF*)pLoc)->NVCount;
		return nvmap;
	}

	template <typename T1>
	bool SetCount(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVCount = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}


	_NV_FLIP1_MAP GetFlip1Map()
	{
		_NV_FLIP1_MAP nvmap = ((_MMF*)pLoc)->NVFlip1Map;
		return nvmap;
	}
	template <typename T1>
	bool SetFlip1Map(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVFlip1Map = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_FLIP2_MAP GetFlip2Map()
	{
		_NV_FLIP2_MAP nvmap = ((_MMF*)pLoc)->NVFlip2Map;
		return nvmap;
	}
	template <typename T1>
	bool SetFlip2Map(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVFlip2Map = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_PALLET1_MAP GetPallet1Map()
	{
		_NV_PALLET1_MAP nvmap = ((_MMF*)pLoc)->NVPallet1Map;
		return nvmap;
	}
	template <typename T1>
	bool SetPallet1Map(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVPallet1Map = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_PALLET2_MAP GetPallet2Map()
	{
		_NV_PALLET2_MAP nvmap = ((_MMF*)pLoc)->NVPallet2Map;
		return nvmap;
	}
	template <typename T1>
	bool SetPallet2Map(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVPallet2Map = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_GOODTRAY1_MAP GetGoodTray1Map()
	{
		_NV_GOODTRAY1_MAP nvmap = ((_MMF*)pLoc)->NVGoodTray1Map;
		return nvmap;
	}
	template <typename T1>
	bool SetGoodTray1Map(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVGoodTray1Map = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_GOODTRAY2_MAP GetGoodTray2Map()
	{
		_NV_GOODTRAY2_MAP nvmap = ((_MMF*)pLoc)->NVGoodTray2Map;
		return nvmap;
	}
	template <typename T1>
	bool SetGoodTray2Map(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVGoodTray2Map = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_REWORKTRAY_MAP GetReworkTrayMap()
	{
		_NV_REWORKTRAY_MAP nvmap = ((_MMF*)pLoc)->NVReworkTrayMap;
		return nvmap;
	}
	template <typename T1>
	bool SetReworkTrayMap(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVReworkTrayMap = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_NGTRAY_MAP GetNGTrayMap()
	{
		_NV_NGTRAY_MAP nvmap = ((_MMF*)pLoc)->NVNGTrayMap;
		return nvmap;
	}
	template <typename T1>
	bool SetNGTrayMap(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVNGTrayMap = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_FLIP1_RESULT GetFlip1Result()
	{
		_NV_FLIP1_RESULT nvmap = ((_MMF*)pLoc)->NVFlip1Result;
		return nvmap;
	}
	template <typename T1>
	bool SetFlip1Result(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVFlip1Result = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_FLIP2_RESULT GetFlip2Result()
	{
		_NV_FLIP2_RESULT nvmap = ((_MMF*)pLoc)->NVFlip2Result;
		return nvmap;
	}
	template <typename T1>
	bool SetFlip2Result(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVFlip2Result = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_PALLET1_RESULT GetPallet1Result()
	{
		_NV_PALLET1_RESULT nvmap = ((_MMF*)pLoc)->NVPallet1Result;
		return nvmap;
	}
	template <typename T1>
	bool SetPallet1Result(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVPallet1Result = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_PALLET2_RESULT GetPallet2Result()
	{
		_NV_PALLET2_RESULT nvmap = ((_MMF*)pLoc)->NVPallet2Result;
		return nvmap;
	}
	template <typename T1>
	bool SetPallet2Result(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVPallet2Result = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_FRONT_PK_RESULT GetFrontPkResult()
	{
		_NV_FRONT_PK_RESULT nvmap = ((_MMF*)pLoc)->NVFrontPkResult;
		return nvmap;
	}
	template <typename T1>
	bool SetFrontPkResult(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVFrontPkResult = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_REAR_PK_RESULT GetRearPkResult()
	{
		_NV_REAR_PK_RESULT nvmap = ((_MMF*)pLoc)->NVRearPkResult;
		return nvmap;
	}
	template <typename T1>
	bool SetRearPkResult(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVRearPkResult = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_GOOD_TRAY1_RESULT GetGoodTray1Result()
	{
		_NV_GOOD_TRAY1_RESULT nvmap = ((_MMF*)pLoc)->NVGoodTray1Result;
		return nvmap;
	}
	template <typename T1>
	bool SetGoodTray1Result(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVGoodTray1Result = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_GOOD_TRAY2_RESULT GetGoodTray2Result()
	{
		_NV_GOOD_TRAY2_RESULT nvmap = ((_MMF*)pLoc)->NVGoodTray2Result;
		return nvmap;
	}
	template <typename T1>
	bool SetGoodTray2Result(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVGoodTray2Result = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_REWORK_TRAY_RESULT GetReworkTrayResult()
	{
		_NV_REWORK_TRAY_RESULT nvmap = ((_MMF*)pLoc)->NVReworkTrayResult;
		return nvmap;
	}
	template <typename T1>
	bool SetReworkTrayResult(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVReworkTrayResult = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}

	_NV_NG_TRAY_RESULT GetNGTrayResult()
	{
		_NV_NG_TRAY_RESULT nvmap = ((_MMF*)pLoc)->NVNGTrayResult;
		return nvmap;
	}
	template <typename T1>
	bool SetNGTrayResult(T1 nvdata)
	{
		if (pLoc == nullptr) {
			return false;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->NVNGTrayResult = static_cast<T1>(nvdata);

		//printf("NVMap Write success.\n");
		return true;
	}
	//int DataGetInCount()
	//{
	//	if (pLoc == nullptr)
	//	{
	//		return FALSE;
	//	}

	//	auto pData = static_cast<_MMF*>(pLoc);

	//	return pData->Count.PanelInCnt;
	//}


	//int DataGetOutCountNG()
	//{
	//	if (pLoc == nullptr)
	//	{
	//		return FALSE;
	//	}

	//	auto pData = static_cast<_MMF*>(pLoc);

	//	return pData->Counter.nOutCountNG;
	//}
	//int DataGetOutCountOK()
	//{
	//	if (pLoc == nullptr)
	//	{
	//		return FALSE;
	//	}

	//	auto pData = static_cast<_MMF*>(pLoc);

	//	return pData->Counter.nOutCountOK;
	//}

	//int DataGetTotal()
	//{
	//	if (pLoc == nullptr)
	//	{
	//		return FALSE;
	//	}

	//	auto pData = static_cast<_MMF*>(pLoc);

	//	return pData->Counter.nTotal;
	//}

	//int DataSetInCount(int val)
	//{
	//	if (pLoc == nullptr)
	//	{
	//		return FALSE;
	//	}

	//	auto pData = static_cast<_MMF*>(pLoc);

	//	pData->Counter.nInCount = val;

	//	spdlog::info("MMF Input count Write : {}", val);
	//	return TRUE;
	//}

	//int DataSetOutCountNG(int val)
	//{
	//	if (pLoc == nullptr)
	//	{
	//		return FALSE;
	//	}

	//	auto pData = static_cast<_MMF*>(pLoc);

	//	pData->Counter.nOutCountNG = val;
	//	spdlog::info("MMF Output NG count Write : {}", val);
	//	return TRUE;
	//}

	//int DataSetOutCountOK(int val)
	//{
	//	if (pLoc == nullptr)
	//	{
	//		return FALSE;
	//	}

	//	auto pData = static_cast<_MMF*>(pLoc);

	//	pData->Counter.nOutCountOK = val;
	//	spdlog::info("MMF Output OK count Write : {}", val);
	//	return TRUE;
	//}

	//int DataSetTotal(int val)
	//{
	//	if (pLoc == nullptr)
	//	{
	//		return FALSE;
	//	}

	//	auto pData = static_cast<_MMF*>(pLoc);

	//	pData->Counter.nTotal = val;
	//	spdlog::info("MMF Total count Write : {}", val);
	//	return TRUE;
	//}

	//--
	/*template <typename T>
	BOOL DataWrite(T nWorkTable, int nPartNum, int nSharpNum, int nWorkNum)
	{
		int nWT = static_cast<int>(nWorkTable);
		if (nWT >= MAX_WORKTABLE) return FALSE;
		if (pLoc == nullptr)
		{
			return FALSE;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->WorkTable[nWT].InTime = time(nullptr);
		pData->WorkTable[nWT].nLoading = 1;
		pData->WorkTable[nWT].nPartNumber = nPartNum;
		pData->WorkTable[nWT].nSharpNumber = nSharpNum;
		ZeroMemory(pData->WorkTable[nWT].sInspectData, sizeof(pData->WorkTable[nWT].sInspectData));
		pData->WorkTable[nWT].nWorkNumber = nWorkNum;

		for (int n = 0; n < 3; n++)
		{
			pData->WorkTable[nWT].nStatus[n] = 0;
		}
		spdlog::info("MMF Data Write 워크테이블[{}], 파트넘버[{}], 샵오더[{}], 작업번호[{}]", nWT, nPartNum, nSharpNum, nWorkNum);
		return TRUE;
	}

	template <typename T1, typename T2, typename T3>
	BOOL DataWriteStatus(T1 nWorkTable, T2 nDevide, T3 nStatus)
	{
		int nWT = static_cast<int>(nWorkTable);
		if (nWT >= MAX_WORKTABLE) return FALSE;
		if (static_cast<int>(nDevide) > 2) return FALSE;
		if (pLoc == nullptr)
		{
			return FALSE;
		}

		auto pData = static_cast<_MMF*>(pLoc);
		pData->WorkTable[nWT].nStatus[static_cast<int>(nDevide)] = static_cast<int>(nStatus);
		spdlog::info("MMF Status Write 워크테이블[{}], 위치[{}], 상태[{}]", nWT, static_cast<int>(nDevide), static_cast<int>(nStatus));
		return TRUE;
	}*/


	//template <typename T>
	//bool DataClear(T map)
	//{
	//	if (pLoc == nullptr) {
	//		return false;
	//	}
	//	auto pData = static_cast<_MMF*>(pLoc);
	//	pData->NVMap.FlipY1AirCleanCnt = 0;
	//	pData->NVMap.FlipY2AirCleanCnt = 0;
	//	pData->NVMap.PalletY1AirCleanCnt = 0;
	//	pData->NVMap.PalletY2AirCleanCnt = 0;
	//	pData->NVMap.PanelInCnt = 0;
	//	pData->NVMap.SpongeCleanCnt = 0;
	//	pData->NVMap.TotalUnitInCnt = 0;
	//	pData->NVMap.TotalUnitOutCnt = 0;
	//	pData->NVMap.UnitGoodCnt = 0;
	//	pData->NVMap.UnitNGCnt = 0;
	//	pData->NVMap.UnitReworkCnt = 0;
	//	pData->NVMap.WaterJetAirCleanCnt = 0;
	//}
	

	//template <typename T>
	//BOOL DataClear(T nWorkTable)
	//{
	//	int nWT = static_cast<int>(nWorkTable);
	//	if (nWT >= MAX_WORKTABLE) return FALSE;
	//	if (pLoc == nullptr)
	//	{
	//		return FALSE;
	//	}

	//	auto pData = static_cast<_MMF*>(pLoc);
	//	pData->WorkTable[nWT].InTime = 0;
	//	pData->WorkTable[nWT].nLoading = 0;
	//	pData->WorkTable[nWT].nSharpNumber = 0;
	//	pData->WorkTable[nWT].nPartNumber = 0;
	//	pData->WorkTable[nWT].nWorkNumber = 0;
	//	ZeroMemory(pData->WorkTable[nWT].sInspectData, sizeof(pData->WorkTable[nWT].sInspectData));
	//	for (int n = 0; n < 3; n++)
	//	{
	//		pData->WorkTable[nWT].nStatus[n] = 0;
	//	}
	//	spdlog::info("MMF Data Clear [{}] Side", nWT);
	//	return TRUE;
	//}
};

#pragma pack(pop)   /* restore original alignment from stack */
