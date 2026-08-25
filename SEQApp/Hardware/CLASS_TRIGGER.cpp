#include "CLASS_TRIGGER.h"

CAjinTrigger::CAjinTrigger()
{
	if (AxlIsOpened()) {
		DWORD uStatus;
		AxcInfoIsCNTModule(&uStatus);
		if (uStatus == STATUS_EXIST) {
			printf("CNT module Exist");

			uStatus = AxcInfoGetTotalChannelCount(&lCntChannelCounts);
			printf("Total Channel Count = %d\n", lCntChannelCounts);

		}
		else {
			printf("CNT module not Found");
		}
	}
}

CAjinTrigger::~CAjinTrigger()
{
	
}

bool CAjinTrigger::SetTriggerActPos(int nTableNo, double fActPos = 0.0, double fUPP = 0.001)
{
//	DWORD uStatus;

	// Motor Unit / Pulse
	if (AXT_RT_SUCCESS != AxcMotSetMoveUnitPerPulse(nTableNo, fUPP)){
		return false;
	}

	// Motor Encoder Count Reset
	if (AXT_RT_SUCCESS != AxcStatusSetActPos(nTableNo, fActPos))
	{
		return false;
	}
	return true;
}

bool CAjinTrigger :: SetTriggerEncReverse(int nTableNo, bool bRevers = true)
{
	DWORD uStatus;

	DWORD dwReverse = (bRevers) ? 0x01 : 0x00;

	uStatus = AxcSignalSetEncReverse(nTableNo, dwReverse);
	if (uStatus == AXT_RT_SUCCESS) {
		return true;
	}

	return false;

}
bool CAjinTrigger::SetTriggerOnOff(int nModNo, int nTableNo, bool bEnable)
{
	DWORD uStatus;
	DWORD uEnable;

	uEnable = bEnable ? 1 : 0;
	uStatus = AxcTableSetEnable(nModNo, nTableNo, uEnable);
	if (uStatus == AXT_RT_SUCCESS) {
		return true;
	}
	return false;
}

bool CAjinTrigger::SetTriggerOutPort(int nModNo, int nTableNo, int nTrigOutPortNo)
{
	DWORD uStatus;

	uStatus = AxcTableSetTriggerOutport(nModNo, nTableNo, nTrigOutPortNo);
	if (uStatus == AXT_RT_SUCCESS) {
		return true;
	}
	return false;
}

bool CAjinTrigger::SetTriggerConfig(int nModNo, int nTableNo, int nEncoderPortNo, int nTrigOutPortNo, double fPulsWidthUS)
{
//	DWORD uStatus;

	//< Encoder 4채배 설정
	if (AXT_RT_SUCCESS != AxcSignalSetEncInputMethod(nTableNo, 3)){
		return false;
	}

	//< 카운터 모듈의 각 테이블에 할당 할 엔코더 소스 설정
	if (AXT_RT_SUCCESS != AxcSignalSetEncSource(nTableNo, 0)){
		return false;
	}

	//< 카운터 모듈의 각 테이블에 할당 할 엔코더 출력 포트 설정
	if (AXT_RT_SUCCESS != AxcTableSetTriggerOutport(nModNo, nTableNo, nTrigOutPortNo)){
		return false;
	}

	//< 카운터 모듈의 각 테이블에 할당 할 엔코더 입력 포트 설정
	if (AXT_RT_SUCCESS != AxcTableSetEncoderInput(nModNo, nTableNo, nEncoderPortNo, nEncoderPortNo)){
		return false;
	}

	//< 카운터 모듈의 각 테이블에 할당 할 엔코더 입력 포트 설정
	if (AXT_RT_SUCCESS != AxcTableSetTriggerLevel(nModNo, nTableNo, 1)){
		return false;
	}

	//< Trigger Mode : CCGC_CNT_VECTOR_TRIGGER (지정한 트리거 위치에 설정한 허용 범위와 벡터 방향이 일치할 때 트리거를 출력하는 모드)
	if (AXT_RT_SUCCESS != AxcTableSetTriggerMode(nModNo, nTableNo, 0)){
		return false;
	}

	//< 카운터 모듈의 각 테이블에 할당 할 Data Clear 설정
	if (AXT_RT_SUCCESS != AxcTableSetTriggerDataClear(nModNo, nTableNo)){
		return false;
	}

	//< Trigger Plus Width [uS]
	if (AXT_RT_SUCCESS != AxcTableSetTriggerTime(nModNo, nTableNo, fPulsWidthUS)){
		return false;
	}

	//< Trigger Position Error Range : default 1 puls
	if (AXT_RT_SUCCESS != AxcTableSetErrorRange(nModNo, nTableNo, 0.005000)){
		return false;
	}
	return true;
}

bool CAjinTrigger::StartTrigger(int nModNo, int nTableNo, int nTrigCount, double fTrigStartPos, double fTrigDistance)
{

	if ( nTrigCount<=0){
		return false;
	}

	// 트리거 간격 미입력 확인
	if (fTrigDistance <= 0){
		return false;
	}

	double fPos[10];
	long nTrigOutCount[10];
	double fTrigInterval[10];

	for (int nInd = 0; nInd < nTrigCount; nInd++){
		fPos[nInd] = fTrigStartPos + (fTrigDistance * nInd);
		nTrigOutCount[nInd] = 1;
		fTrigInterval[nInd] = 50;
	}

	double fTrigData[20];
	for (int nInd = 0; nInd < nTrigCount; nInd++){
		fTrigData[nInd * 2] = fPos[nInd];
		fTrigData[(nInd * 2) + 1] = fPos[nInd];
	}

	//< Set Trigger Position, Count, Interval
	 //- 정상 실행시 자동으로 트리거 활성화 됨. (TriggerOnOff(true))
	if (AXT_RT_SUCCESS != AxcTableSetTriggerData(nModNo, nTableNo, -1, nullptr, nullptr, nullptr))
	{
		return false;
	}
	if (AXT_RT_SUCCESS != AxcTableSetTriggerData(nModNo, nTableNo, nTrigCount, fTrigData, nTrigOutCount, fTrigInterval))
	{
		return false;
	}
	SetTriggerOnOff(nModNo, nTableNo, true);

	return true;

}