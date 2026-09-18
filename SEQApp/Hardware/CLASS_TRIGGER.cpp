#include "CLASS_TRIGGER.h"
#include <math.h>

//==========================================================================
//  Optional AXC calls, resolved from the loaded AXL.dll
//
//  See the note in CLASS_TRIGGER.h. Linking these implicitly would make the
//  whole application fail to load on a site whose AXL lacks them; resolving
//  them here degrades to a log line instead.
//==========================================================================

typedef DWORD (__stdcall *PFN_AXC_CH_DW)  (long, DWORD);
typedef DWORD (__stdcall *PFN_AXC_CH_DWP) (long, DWORD*);
typedef DWORD (__stdcall *PFN_AXC_CH)     (long);
typedef DWORD (__stdcall *PFN_AXC_CH_LP)  (long, long*);

static PFN_AXC_CH_DW  g_pfnSetOutport    = NULL;
static PFN_AXC_CH_DWP g_pfnGetOutport    = NULL;
static PFN_AXC_CH_DW  g_pfnSetEncInput   = NULL;
static PFN_AXC_CH     g_pfnCountClear    = NULL;
static PFN_AXC_CH_LP  g_pfnReadCount     = NULL;
static bool           g_bOptionalChecked = false;

static void ResolveOptionalAxc(void)
{
	if (g_bOptionalChecked) {
		return;
	}
	g_bOptionalChecked = true;

	// AXL is linked in, so it is already mapped. Ask for that instance rather
	// than loading a second copy which might not be the one AXL calls go to.
	HMODULE hAxl = GetModuleHandleA("AXL.dll");
	if (hAxl == NULL) {
		hAxl = LoadLibraryA("AXL.dll");
	}
	if (hAxl == NULL) {
		printf("[TRIGGER] AXL.dll handle unavailable - optional counter calls disabled\n");
		return;
	}

	g_pfnSetOutport  = (PFN_AXC_CH_DW) GetProcAddress(hAxl, "AxcTriggerSetTriggerOutport");
	g_pfnGetOutport  = (PFN_AXC_CH_DWP)GetProcAddress(hAxl, "AxcTriggerGetTriggerOutport");
	g_pfnSetEncInput = (PFN_AXC_CH_DW) GetProcAddress(hAxl, "AxcTriggerSetEncoderInput");
	g_pfnCountClear  = (PFN_AXC_CH)    GetProcAddress(hAxl, "AxcTriggerSetTriggerCountClear");
	g_pfnReadCount   = (PFN_AXC_CH_LP) GetProcAddress(hAxl, "AxcTriggerReadTriggerCount");

	char szVer[128];
	memset(szVer, 0, sizeof(szVer));
	if (AxlGetLibVersion(szVer) == AXT_RT_SUCCESS) {
		printf("[TRIGGER] AXL library version %s\n", szVer);
	}

	printf("[TRIGGER] optional AXC calls : SetTriggerOutport %s, GetTriggerOutport %s,"
		   " SetEncoderInput %s, SetTriggerCountClear %s, ReadTriggerCount %s\n",
		   (g_pfnSetOutport  != NULL) ? "yes" : "NO",
		   (g_pfnGetOutport  != NULL) ? "yes" : "NO",
		   (g_pfnSetEncInput != NULL) ? "yes" : "NO",
		   (g_pfnCountClear  != NULL) ? "yes" : "NO",
		   (g_pfnReadCount   != NULL) ? "yes" : "NO");
}

bool CAjinTrigger::HasOutportApi(void)
{
	ResolveOptionalAxc();
	return (g_pfnSetOutport != NULL);
}

bool CAjinTrigger::HasTriggerCountApi(void)
{
	ResolveOptionalAxc();
	return (g_pfnReadCount != NULL);
}

CAjinTrigger::CAjinTrigger()
{
	ResolveOptionalAxc();

	// Stays zero unless a counter module actually reports channels, so every
	// periodic mode call refuses instead of driving a channel that is not there.
	lCntChannelCounts = 0;

	// Each failure path says why. Reporting nothing made a board-less PC look
	// identical to a wiring fault, which cost a debugging session.
	if (!AxlIsOpened()) {
		printf("[TRIGGER] AXL not opened - counter trigger unavailable\n");
		return;
	}

	DWORD uStatus = 0;
	DWORD dwCode  = AxcInfoIsCNTModule(&uStatus);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[TRIGGER] AxcInfoIsCNTModule() failed, code 0x%lx\n", dwCode);
		return;
	}
	if (uStatus != STATUS_EXIST) {
		printf("[TRIGGER] CNT module not found - counter trigger unavailable\n");
		return;
	}

	dwCode = AxcInfoGetTotalChannelCount(&lCntChannelCounts);
	if (dwCode != AXT_RT_SUCCESS) {
		lCntChannelCounts = 0;
		printf("[TRIGGER] AxcInfoGetTotalChannelCount() failed, code 0x%lx\n", dwCode);
		return;
	}
	printf("[TRIGGER] CNT module ready, %ld channel(s)\n", lCntChannelCounts);
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
	if (g_pfnSetEncInput != NULL) {
		DWORD dwEncCode = g_pfnSetEncInput(ch, cfg.dwEncoderInput);
		if (dwEncCode != AXT_RT_SUCCESS) {
			printf("StartPeriodicTrigger: AxcTriggerSetEncoderInput(ch%ld, %lu) failed, code 0x%lx\n",
				   ch, cfg.dwEncoderInput, dwEncCode);
			return false;
		}
	}
	else {
		printf("[TRIGGER] ch%ld : AxcTriggerSetEncoderInput missing, relying on the"
			   " channel's own encoder input\n", ch);
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

	//< Everything below this line is in RAW ENCODER COUNTS, not mm.
	//
	//  AxcMotSetMoveUnitPerPulse is headed "API for SIO-CN2CH only" in AXC.h,
	//  and this is an SIO-HPC4L. Setting it returned success and changed
	//  nothing: the board read the unit back as 1.000000 while the block read
	//  back as raw counts. Writing mm and trusting the library to scale them
	//  put the block a factor of 1/unit away from where the counter actually
	//  runs, so the stage never entered it and not one trigger could fire.
	//
	//  Ask for 1.0 anyway, so that a board which does honour the call is left
	//  in the same counts-are-counts state as this one, and do the mm to count
	//  conversion here where it can be printed and checked.
	AxcMotSetMoveUnitPerPulse(ch, 1.0);

	const double dCountsPerMM = 1.0 / cfg.dMoveUnitPerPulse;
	const double dLowerCnt = cfg.dScanStart * dCountsPerMM;
	const double dUpperCnt = cfg.dScanEnd   * dCountsPerMM;
	const double dPitchCnt = floor(cfg.dPitch * dCountsPerMM + 0.5);

	//< Position period mode
	if (AXT_RT_SUCCESS != AxcTriggerSetFunction(ch, 0x03)) {
		return false;
	}

	//< The step this driver was missing, and the reason the trigger pin stayed
	//  quiet while every call above returned success.
	//
	//  An EzSpy trace of EzManager's own CounterAgent shows it reading channel
	//  register 0x16 back and writing it straight out again through the write
	//  alias 0x96 (150 = 0x16 | 0x80) - between disabling the trigger and
	//  writing the period and block - and the output only pulses when those
	//  two calls are in the sequence. CLASS_AjinCounter::SetTriggerPosition()
	//  in this same project already carries the identical pair for absolute
	//  mode, so this is Ajinextek's sequence rather than a guess. AXDev.h
	//  declares the accessors but documents neither the register nor bit 1.
	WORD  wTrigReg  = 0;
	DWORD dwRegCode = AxcKeGetCommandData16(ch, 22, &wTrigReg);
	if (dwRegCode != AXT_RT_SUCCESS) {
		printf("StartPeriodicTrigger: AxcKeGetCommandData16(ch%ld, 22) failed, code 0x%lx\n",
			   ch, dwRegCode);
		return false;
	}
	dwRegCode = AxcKeSetCommandData16(ch, 150, (WORD)(wTrigReg | 0x0002));
	if (dwRegCode != AXT_RT_SUCCESS) {
		printf("StartPeriodicTrigger: AxcKeSetCommandData16(ch%ld, 150, 0x%04X) failed, code 0x%lx\n",
			   ch, (unsigned int)(wTrigReg | 0x0002), dwRegCode);
		return false;
	}
	printf("[TRIGGER] ch%ld trigger register 0x16 : 0x%04X -> 0x%04X\n",
		   ch, (unsigned int)wTrigReg, (unsigned int)(wTrigReg | 0x0002));

	//< Block range and pitch in a single call, in counts
	if (AXT_RT_SUCCESS != AxcTriggerSetBlock(ch, dLowerCnt, dUpperCnt, dPitchCnt)) {
		return false;
	}

	//< Read it straight back. This is the check that would have caught the unit
	//  problem on the first run instead of the fifth.
	double dGotLower = 0.0, dGotUpper = 0.0, dGotPitch = 0.0;
	if (AXT_RT_SUCCESS == AxcTriggerGetBlock(ch, &dGotLower, &dGotUpper, &dGotPitch)) {
		if (fabs(dGotLower - dLowerCnt) > 1.0 ||
			fabs(dGotUpper - dUpperCnt) > 1.0 ||
			fabs(dGotPitch - dPitchCnt) > 1.0) {
			printf("StartPeriodicTrigger: the board did not take the block.\n"
				   "  wrote %.0f .. %.0f counts, pitch %.0f\n"
				   "  read  %.0f .. %.0f counts, pitch %.0f\n"
				   "  The counter is not being programmed in the unit this code assumes.\n",
				   dLowerCnt, dUpperCnt, dPitchCnt, dGotLower, dGotUpper, dGotPitch);
			return false;
		}
	}

	//< Restrict to the scanning direction so vibration at rest cannot dither
	//  the counter across a period boundary and emit stray triggers.
	if (AXT_RT_SUCCESS != AxcTriggerSetDirectionCheck(ch, cfg.dwDirectionCheck)) {
		return false;
	}

	//< Output port, pulse width [us], active level
	//
	//  The port mask is what connects the comparator to a pin. It was being
	//  skipped, on the assumption that a channel always drives its own output;
	//  that assumption is what this call existing contradicts, and a mask left
	//  at zero produces exactly the symptom seen here - every setting accepted,
	//  nothing on the connector.
	if (g_pfnSetOutport != NULL) {
		DWORD dwPortCode = g_pfnSetOutport(ch, cfg.dwTriggerOutPort);
		if (dwPortCode != AXT_RT_SUCCESS) {
			printf("StartPeriodicTrigger: AxcTriggerSetTriggerOutport(ch%ld, 0x%lX) failed,"
				   " code 0x%lx\n", ch, cfg.dwTriggerOutPort, dwPortCode);
			return false;
		}
	}
	else {
		printf("[TRIGGER] ch%ld : AxcTriggerSetTriggerOutport missing, the trigger output"
			   " port mask cannot be set from here\n", ch);
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

	if (g_pfnCountClear != NULL) {
		g_pfnCountClear(ch);
	}

	if (AXT_RT_SUCCESS != AxcTriggerSetEnable(ch, 1)) {
		return false;
	}

	printf("Periodic trigger ch%ld : pitch %.5f mm = %.0f counts, block %.3f..%.3f mm"
		   " = %.0f..%.0f counts, %.1f us, expect %.0f triggers\n",
		   ch, cfg.dPitch, dPitchCnt, cfg.dScanStart, cfg.dScanEnd,
		   dLowerCnt, dUpperCnt, cfg.dPulseWidthUS,
		   (cfg.dScanEnd - cfg.dScanStart) / cfg.dPitch);

	// Every call above returned success, which is exactly what it did while no
	// pulse ever reached the connector. Print what the board holds instead.
	ReportChannelConfig(ch, "armed");
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
	if (g_pfnCountClear == NULL) {
		return false;
	}
	return (AXT_RT_SUCCESS == g_pfnCountClear(lChannelNo));
}

bool CAjinTrigger::ReadTriggerCount(long lChannelNo, long* lpCount)
{
	if (!IsChannelValid(lChannelNo) || lpCount == nullptr) {
		return false;
	}
	*lpCount = 0;
	if (g_pfnReadCount == NULL) {
		return false;
	}
	return (AXT_RT_SUCCESS == g_pfnReadCount(lChannelNo, lpCount));
}

bool CAjinTrigger::SetTriggerOutPortMask(long lChannelNo, DWORD dwMask)
{
	if (!IsChannelValid(lChannelNo) || g_pfnSetOutport == NULL) {
		return false;
	}
	return (AXT_RT_SUCCESS == g_pfnSetOutport(lChannelNo, dwMask));
}

bool CAjinTrigger::ReadOutputState(long lChannelNo, bool* pbOn)
{
	if (!IsChannelValid(lChannelNo) || pbOn == NULL) {
		return false;
	}
	DWORD dwStatus = 0;
	if (AXT_RT_SUCCESS != AxcStatusGetChannel(lChannelNo, &dwStatus)) {
		return false;
	}
	// AXC.h, AxcStatusGetChannel : bit 2 is the trigger output status.
	*pbOn = ((dwStatus & 0x04) != 0);
	return true;
}

bool CAjinTrigger::ForceOutput(long lChannelNo, bool bOn)
{
	if (!IsChannelValid(lChannelNo)) {
		return false;
	}
	const DWORD dwCode = AxcTriggerSetOutput(lChannelNo, bOn ? 0x01 : 0x00);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[TRIGGER] AxcTriggerSetOutput(ch%ld, %d) failed, code 0x%lx\n",
			   lChannelNo, bOn ? 1 : 0, dwCode);
		return false;
	}
	return true;
}

//==========================================================================
//  The output stage is gated by AxcTriggerSetEnable.
//
//  AXC.h on AxcTriggerSetEnable: "Sets whether the trigger output will be
//  finally output according to the currently set function." The first output
//  test disabled the trigger before forcing the line, which is exactly the
//  switch that stops anything reaching the pin - a flat scope proved nothing.
//
//  Enabling is safe here because the stage does not move during the test, and
//  periodic mode only fires on encoder movement.
//==========================================================================
bool CAjinTrigger::BeginOutputTest(long lChannelNo)
{
	if (!IsChannelValid(lChannelNo)) {
		return false;
	}

	DWORD dwCode = AxcTriggerSetLevel(lChannelNo, 1);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[TRIGGER] AxcTriggerSetLevel(ch%ld, 1) failed, code 0x%lx\n",
			   lChannelNo, dwCode);
	}

	dwCode = AxcTriggerSetEnable(lChannelNo, 1);
	if (dwCode != AXT_RT_SUCCESS) {
		printf("[TRIGGER] AxcTriggerSetEnable(ch%ld, 1) failed, code 0x%lx"
			   " - the output stage stays gated off and the test cannot drive the pin\n",
			   lChannelNo, dwCode);
		return false;
	}

	ForceOutput(lChannelNo, false);
	return true;
}

bool CAjinTrigger::EndOutputTest(long lChannelNo)
{
	if (!IsChannelValid(lChannelNo)) {
		return false;
	}
	ForceOutput(lChannelNo, false);
	return (AXT_RT_SUCCESS == AxcTriggerSetEnable(lChannelNo, 0));
}

//==========================================================================
//  What the board holds, read back from the board.
//
//  Written values and held values are not the same thing: the pulse train
//  stayed absent while every setter returned AXT_RT_SUCCESS. Each line below
//  carries the value that means "correct" so a wrong one is visible without
//  opening the header.
//==========================================================================
void CAjinTrigger::ReportChannelConfig(long lChannelNo, const char* pszWhen)
{
	if (!IsChannelValid(lChannelNo)) {
		printf("[TRIGGER] channel %ld out of range (0..%ld)\n",
			   lChannelNo, lCntChannelCounts - 1);
		return;
	}

	double dUnit  = 0.0, dLower = 0.0, dUpper = 0.0, dPitch = 0.0;
	double dPeriod = 0.0, dTime = 0.0, dPos = 0.0;
	DWORD  dwMethod = 0, dwSource = 0, dwReverse = 0, dwFunc = 0;
	DWORD  dwDir = 0, dwLevel = 0, dwEnable = 0, dwOutport = 0, dwStatus = 0;
	WORD   wReg = 0;
	long   lCount = 0;

	AxcMotGetMoveUnitPerPulse  (lChannelNo, &dUnit);
	AxcSignalGetEncInputMethod (lChannelNo, &dwMethod);
	AxcSignalGetEncSource      (lChannelNo, &dwSource);
	AxcSignalGetEncReverse     (lChannelNo, &dwReverse);
	AxcTriggerGetFunction      (lChannelNo, &dwFunc);
	AxcTriggerGetBlock         (lChannelNo, &dLower, &dUpper, &dPitch);
	AxcTriggerGetPosPeriod     (lChannelNo, &dPeriod);
	AxcTriggerGetDirectionCheck(lChannelNo, &dwDir);
	AxcTriggerGetTime          (lChannelNo, &dTime);
	AxcTriggerGetLevel         (lChannelNo, &dwLevel);
	AxcTriggerGetEnable        (lChannelNo, &dwEnable);
	AxcStatusGetActPos         (lChannelNo, &dPos);
	AxcKeGetCommandData16      (lChannelNo, 22, &wReg);

	printf("[TRIGGER] ===== channel %ld, read back from the board (%s) =====\n",
		   lChannelNo, (pszWhen != NULL) ? pszWhen : "");
	// 1.0 is correct here: AxcMotSetMoveUnitPerPulse is CN2CH-only, so this
	// board counts in raw encoder counts and every distance below is a count.
	printf("[TRIGGER]  unit/count  %.6f                 want 1.000000 (counts)\n", dUnit);
	printf("[TRIGGER]  enc method  %-4lu source %-4lu reverse %lu   want 3 / 0 / 0\n",
		   dwMethod, dwSource, dwReverse);
	printf("[TRIGGER]  function    %-4lu                       want 3 (periodic)\n", dwFunc);
	printf("[TRIGGER]  block       %.0f .. %.0f counts  pitch %.0f  period %.0f\n",
		   dLower, dUpper, dPitch, dPeriod);
	printf("[TRIGGER]  dir check   %-4lu pulse %.3f us  level %lu   want 1 / >=1 / 1\n",
		   dwDir, dTime, dwLevel);
	printf("[TRIGGER]  enable      %-4lu register 0x16 0x%04X       want 1 / bit1 set\n",
		   dwEnable, (unsigned int)wReg);

	if (g_pfnGetOutport != NULL && g_pfnGetOutport(lChannelNo, &dwOutport) == AXT_RT_SUCCESS) {
		// A mask of 0 routes the comparator to no pin at all, which looks
		// identical to a dead board on a scope.
		printf("[TRIGGER]  out port    0x%lX%s\n",
			   dwOutport, (dwOutport == 0) ? "   <-- NO OUTPUT PORT SELECTED" : "");
	}
	else {
		printf("[TRIGGER]  out port    not readable on this AXL\n");
	}

	printf("[TRIGGER]  enc pos     %.0f counts%s\n", dPos,
		   (dPos < dLower || dPos > dUpper)
			   ? "   <-- OUTSIDE THE BLOCK, no trigger can fire here" : "");

	const DWORD dwStatCode = AxcStatusGetChannel(lChannelNo, &dwStatus);
	if (dwStatCode == AXT_RT_SUCCESS) {
		printf("[TRIGGER]  status 0x%lX : carry %d  borrow %d  TRIGGER OUT %d  latch %d\n",
			   dwStatus, (int)(dwStatus & 0x01), (int)((dwStatus >> 1) & 0x01),
			   (int)((dwStatus >> 2) & 0x01), (int)((dwStatus >> 3) & 0x01));
	}
	else {
		printf("[TRIGGER]  status      AxcStatusGetChannel refused, code 0x%lx"
			   " - the output line cannot be read back on this board\n", dwStatCode);
	}

	if (g_pfnReadCount != NULL && g_pfnReadCount(lChannelNo, &lCount) == AXT_RT_SUCCESS) {
		printf("[TRIGGER]  triggers emitted so far %ld\n", lCount);
	}
	else {
		printf("[TRIGGER]  triggers emitted so far : not readable on this AXL\n");
	}
	printf("[TRIGGER] =================================================\n");
}

double CAjinTrigger::CalcPitchError(double dTravel, long lTrigCount, double dPitch)
{
	if (lTrigCount <= 0 || dPitch <= 0.0) {
		return 0.0;
	}
	double dMeasured = dTravel / (double)lTrigCount;
	return (dMeasured - dPitch) / dPitch;
}
