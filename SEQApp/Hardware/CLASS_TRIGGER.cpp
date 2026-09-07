#include "CLASS_TRIGGER.h"
#include <math.h>

CAjinTrigger::CAjinTrigger()
{
	// Stays zero when AXL is closed or no counter module is present, so the
	// channel range check in the periodic mode calls rejects every channel
	// instead of comparing against an uninitialised value.
	lCntChannelCounts = 0;

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

	// fPos[], nTrigOutCount[] and fTrigInterval[] below hold MAX_TRIGGER_POS
	// entries and fTrigData[] twice that. Without the upper bound a larger
	// nTrigCount walks straight off the end of the stack frame.
	if (nTrigCount <= 0 || nTrigCount > MAX_TRIGGER_POS){
		return false;
	}

	// 트리거 간격 미입력 확인
	if (fTrigDistance <= 0){
		return false;
	}

	double fPos[MAX_TRIGGER_POS];
	long nTrigOutCount[MAX_TRIGGER_POS];
	double fTrigInterval[MAX_TRIGGER_POS];

	for (int nInd = 0; nInd < nTrigCount; nInd++){
		fPos[nInd] = fTrigStartPos + (fTrigDistance * nInd);
		nTrigOutCount[nInd] = 1;
		fTrigInterval[nInd] = 50;
	}

	double fTrigData[MAX_TRIGGER_POS * 2];
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

//==========================================================================
//  Periodic mode : continuous position synchronised line scan trigger
//
//  AxcTriggerSetFunction(ch, 0x03) puts SIO-HPC4 into position period mode.
//  The counter emits a pulse every dPitch of travel entirely in hardware, so
//  there is no position table to fill and no ceiling on the trigger count -
//  a 200 mm scan at 5 um pitch yields 40,000 triggers from the same setup a
//  10 trigger scan uses.
//
//  SIO-HPC4 has no distance-periodic trigger mode (that one belongs to
//  CNT_RECAT_SC_10), and its PATTERN mode is a frequency timer rather than a
//  position trigger, so this is the only mode here that follows the encoder.
//==========================================================================

bool CAjinTrigger::IsChannelValid(long lChannelNo) const
{
	return (lChannelNo >= 0 && lChannelNo < lCntChannelCounts);
}

bool CAjinTrigger::IsPitchIntegerCounts(double dPitch, double dUPP,
										double* dpCounts, double* dpErrorRatio)
{
	if (dUPP <= 0.0 || dPitch <= 0.0) {
		return false;
	}

	double dCounts  = dPitch / dUPP;
	double dNearest = floor(dCounts + 0.5);

	if (dNearest < 1.0) {
		return false;
	}

	if (dpCounts != nullptr) {
		*dpCounts = dCounts;
	}
	if (dpErrorRatio != nullptr) {
		*dpErrorRatio = fabs(dCounts - dNearest) / dNearest;
	}

	return (fabs(dCounts - dNearest) <= dNearest * 1e-6);
}

bool CAjinTrigger::StartPeriodicTrigger(const PERIODIC_TRIG_CFG& cfg)
{
	long ch = cfg.lChannelNo;

	if (!IsChannelValid(ch)) {
		printf("StartPeriodicTrigger: channel %ld out of range (0..%ld)\n",
			   ch, lCntChannelCounts - 1);
		return false;
	}
	if (cfg.dMoveUnitPerPulse <= 0.0 || cfg.dPitch <= 0.0) {
		printf("StartPeriodicTrigger: unit and pitch must be positive\n");
		return false;
	}
	if (cfg.dScanEnd <= cfg.dScanStart) {
		printf("StartPeriodicTrigger: block end %.4f must exceed start %.4f\n",
			   cfg.dScanEnd, cfg.dScanStart);
		return false;
	}
	if (cfg.dPulseWidthUS < 1.0) {
		// Anything shorter than 1 us the camera silently discards.
		printf("StartPeriodicTrigger: pulse width %.3f us is under the 1 us camera minimum\n",
			   cfg.dPulseWidthUS);
		return false;
	}

	double dCounts = 0.0;
	double dErr    = 0.0;
	if (!IsPitchIntegerCounts(cfg.dPitch, cfg.dMoveUnitPerPulse, &dCounts, &dErr)) {
		printf("StartPeriodicTrigger: pitch %.6f is %.4f encoder counts, not a whole number.\n"
			   "  The comparator rounds, leaving a systematic pitch error of %.3f %%.\n"
			   "  Choose MoveUnitPerPulse so that pitch / unit is an integer.\n",
			   cfg.dPitch, dCounts, dErr * 100.0);
		return false;
	}

	// Keep the output quiet while the channel is reconfigured.
	if (AXT_RT_SUCCESS != AxcTriggerSetEnable(ch, 0)) {
		return false;
	}

	//< Encoder source : physical input, A/B phase 4x, count direction
	if (AXT_RT_SUCCESS != AxcTriggerSetEncoderInput(ch, cfg.dwEncoderInput)) {
		return false;
	}
	if (AXT_RT_SUCCESS != AxcSignalSetEncInputMethod(ch, 0x03)) {
		return false;
	}
	if (AXT_RT_SUCCESS != AxcSignalSetEncSource(ch, 0x00)) {
		return false;
	}
	if (AXT_RT_SUCCESS != AxcSignalSetEncReverse(ch, cfg.bEncReverse ? 0x01 : 0x00)) {
		return false;
	}

	//< One encoder count equals dMoveUnitPerPulse. Every position below is
	//  expressed in that unit.
	if (AXT_RT_SUCCESS != AxcMotSetMoveUnitPerPulse(ch, cfg.dMoveUnitPerPulse)) {
		return false;
	}

	//< Position period mode, then block range and pitch in a single call
	if (AXT_RT_SUCCESS != AxcTriggerSetFunction(ch, 0x03)) {
		return false;
	}
	if (AXT_RT_SUCCESS != AxcTriggerSetBlock(ch, cfg.dScanStart, cfg.dScanEnd, cfg.dPitch)) {
		return false;
	}

	//< Restrict to the scanning direction so vibration at rest cannot dither
	//  the counter across a period boundary and emit stray triggers.
	if (AXT_RT_SUCCESS != AxcTriggerSetDirectionCheck(ch, cfg.dwDirectionCheck)) {
		return false;
	}

	//< Output port, pulse width [us], active level
	if (AXT_RT_SUCCESS != AxcTriggerSetTriggerOutport(ch, cfg.dwTriggerOutPort)) {
		return false;
	}
	if (AXT_RT_SUCCESS != AxcTriggerSetTime(ch, cfg.dPulseWidthUS)) {
		return false;
	}
	if (AXT_RT_SUCCESS != AxcTriggerSetLevel(ch, cfg.dwTriggerLevel)) {
		return false;
	}

	// AxcTriggerSetTriggerOutCount is deliberately left alone: the AXC header
	// does not list it under SIO-HPC4, and periodic mode already emits exactly
	// one pulse per period.

	AxcTriggerSetTriggerCountClear(ch);

	if (AXT_RT_SUCCESS != AxcTriggerSetEnable(ch, 1)) {
		return false;
	}

	printf("Periodic trigger ch%ld : pitch %.5f (%.0f counts), block %.3f..%.3f, "
		   "%.1fus, expect %.0f triggers\n",
		   ch, cfg.dPitch, dCounts, cfg.dScanStart, cfg.dScanEnd, cfg.dPulseWidthUS,
		   (cfg.dScanEnd - cfg.dScanStart) / cfg.dPitch);
	return true;
}

bool CAjinTrigger::StopPeriodicTrigger(long lChannelNo)
{
	if (!IsChannelValid(lChannelNo)) {
		return false;
	}
	return (AXT_RT_SUCCESS == AxcTriggerSetEnable(lChannelNo, 0));
}

bool CAjinTrigger::ResetScanOrigin(long lChannelNo, double dPos)
{
	if (!IsChannelValid(lChannelNo)) {
		return false;
	}
	return (AXT_RT_SUCCESS == AxcStatusSetActPos(lChannelNo, dPos));
}

bool CAjinTrigger::GetActPos(long lChannelNo, double* dpPos)
{
	if (!IsChannelValid(lChannelNo) || dpPos == nullptr) {
		return false;
	}
	return (AXT_RT_SUCCESS == AxcStatusGetActPos(lChannelNo, dpPos));
}

bool CAjinTrigger::ClearTriggerCount(long lChannelNo)
{
	if (!IsChannelValid(lChannelNo)) {
		return false;
	}
	return (AXT_RT_SUCCESS == AxcTriggerSetTriggerCountClear(lChannelNo));
}

bool CAjinTrigger::ReadTriggerCount(long lChannelNo, long* lpCount)
{
	if (!IsChannelValid(lChannelNo) || lpCount == nullptr) {
		return false;
	}
	return (AXT_RT_SUCCESS == AxcTriggerReadTriggerCount(lChannelNo, lpCount));
}

double CAjinTrigger::CalcPitchError(double dTravel, long lTrigCount, double dPitch)
{
	if (lTrigCount <= 0 || dPitch <= 0.0) {
		return 0.0;
	}
	double dMeasured = dTravel / (double)lTrigCount;
	return (dMeasured - dPitch) / dPitch;
}
