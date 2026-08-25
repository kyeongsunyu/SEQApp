#include "..\pch.h"
#include "CLASS_FileLog.h"
#include "..\SeqMain\DEFINE_GVX.h"
#include "..\SeqMain\CLASS_Main.h"
#include "..\SeqMain\Define\DEFINE_WinMsg.h"
#include <chrono>
#include <time.h>



CFileLog::CFileLog()
{
	Clear();
}

CFileLog::~CFileLog()
{
}

char* CFileLog::Get_file_head(int type)
{
	char* head = "";
	switch (type) {
	case LT_PROCESS:
		head = "C:\\WORK\\LOG\\SEQ\\PORCESS\\";
		break;
	case LT_OPERATION:
		head = "C:\\WORK\\LOG\\SEQ\\OPERATION\\";
		break;
	case LT_ERROR:
		head = "C:\\WORK\\LOG\\\\SEQ\\ERROR\\";
		break;
	case LT_RESULT:
		head = "C:\\WORK\\LOG\\\\SEQ\\RESULT\\";
		break;

	}
	CreateDir(head);
	return head;
}
void CFileLog::CreateDir(char* Path)
{
	// 이미 있으면 생성하지 않는다.
	char DirName[256] = { 0, };  //생성할 디렉초리 이름 
	char* p = Path;     //인자로 받은 디렉토리 
	char* q = DirName;
	while (*p)
	{
		if (('\\' == *p) || ('/' == *p))   //루트디렉토리 혹은 Sub디렉토리 
		{
			if (':' != *(p - 1))
			{
				CreateDirectoryA(DirName, NULL);
			}
		}
		*q++ = *p++;
		*q = '\0';
	}
	CreateDirectoryA(DirName, NULL);
}

char* CFileLog::Get_search_path(int type)
{
	char* path = "";
	switch (type) {
	case LT_PROCESS:
		path = ".\\LOG\\SEQ\\PORCESS\\*.log";
		break;
	case LT_OPERATION:
		path = ".\\LOG\\SEQ\\OPERATION\\*.log";
		break;
	case LT_ERROR:
		path = ".\\LOG\\SEQ\\ERROR\\*.log";
		break;
	case LT_RESULT:
		path = ".\\LOG\\SEQ\\RESULT\\*.log";
		break;
	}
	return path;
}

char* CFileLog::Get_log_date()
{
	struct tm* today;
	time_t ltime;
	_tzset();
	/* Use time structure to build a customized time string. */
	time(&ltime);
	today = localtime(&ltime);
	/* Use strftime to build a customized time string. */
	strftime(logdate, 128, "%Y_%m_%d", today);

	return logdate;
}

char* CFileLog::Get_log_filename(int type)
{
	strcpy(filename, Get_file_head(type));
	strcat(filename, Get_log_date());
	strcat(filename, ".log");
	return filename;
}
int CFileLog::LOG_MSG(int type, char* msg)
{
	char logfilename[512];
	FILE* fp;
	char tmpbuf[128] = "";

	sprintf(logfilename, Get_log_filename(type));

	if ((fp = fopen(logfilename, "a+")) == NULL) {
		if ((fp = fopen(logfilename, "w+t")) == NULL) {
			return -1;
		}
		else {
			fclose(fp);
		}
	}
	else {
		struct tm* today;
		time_t ltime;
		_tzset();
		time(&ltime);
		today = localtime(&ltime);
		strftime(logtime, 128, "%H:%M:%S", today);

		fprintf(fp, "[%s] %s\n", logtime, msg);
		fclose(fp);
	}
	Delete_Limited_File(type);
	return 0;
}
int CFileLog::LOG_MSG_P(int type, char* func, int line_no, char* format, ...)
{
	char msg[512];
	char fbuff[512] = { 0, };

	va_list args;

	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	char head[512] = "";
	char deleteHead[512] = "";

	char* Path = "C:\\Work\\LOG\\SEQ\\";
	char* logdate = Get_log_date();

	sprintf(head, "%s%s%s%s%s", Path, MachineStatus.strDeviceName, "\\PROCESS\\",logdate, "\\");
	sprintf(deleteHead, "%s%s%s", Path, MachineStatus.strDeviceName, "\\PROCESS\\");
	CreateDir(head);

	// log file
	char logfilename[512];
	sprintf(logfilename, "%s%s.log", head,logdate);

	FILE* fp;
	if ((fp = fopen(logfilename, "a+")) == NULL) {
		if ((fp = fopen(logfilename, "w+t")) == NULL) {
			return -1;
		}
		else {
			fclose(fp);
		}
	}
	else {
		//struct tm* today;
		//time_t ltime;
		//_tzset();
		//time(&ltime);
		//today = localtime(&ltime);
		//strftime(logtime, 128, "%H:%M:%S", today);

		struct timeb itb;
		struct tm* lt;
		ftime(&itb);
		lt = localtime(&itb.time);
		sprintf(logtime, "%02d:%02d:%02d:%03u", lt->tm_hour, lt->tm_min, lt->tm_sec, itb.millitm);

		if (type == LT_PROCESS) {
			sprintf(fbuff, "%s, %s, USER = %s, DEVICE = %s, TRACE, Call = %s, LIne = %d, %s\n", 
							logdate, logtime, UserInfo.strUserName, MachineStatus.strDeviceName, func, line_no, msg);
			fprintf(fp, fbuff);

			CSeqMain* seqMain = CSeqMain::GetInstance();
			assert(seqMain != nullptr);
			seqMain->SEND_UDP(udp_Client, fbuff);

			//MachineStatus.strSeqLogFlag[SeqLogCnt] = true;
			//MachineStatus.strSeqLogLength[SeqLogCnt] = strlen(fbuff) + 1;
			//strcpy(MachineStatus.strSeqLog[SeqLogCnt], fbuff);
			//SeqLogCnt++;
			//if (SeqLogCnt > 100) {
			//	SeqLogCnt = 0;
			//}
		}
		else if (type == LT_ERROR) {
			sprintf(fbuff, "%s, %s, USER = %s, DEVICE = %s, ERROR, Call = %s, LIne = %d, %s\n",
							logdate, logtime, UserInfo.strUserName, MachineStatus.strDeviceName, func, line_no, msg);
			fprintf(fp, fbuff);

			CSeqMain* seqMain = CSeqMain::GetInstance();
			assert(seqMain != nullptr);
			seqMain->SEND_UDP(udp_Client, fbuff);

			//MachineStatus.strSeqLogFlag[SeqLogCnt] = true;
			//MachineStatus.strSeqLogLength[SeqLogCnt] = strlen(fbuff) + 1;
			//strcpy(MachineStatus.strSeqLog[SeqLogCnt], fbuff);
			//SeqLogCnt++;
			//if (SeqLogCnt > 100) {
			//	SeqLogCnt = 0;
			//}
		}
		fclose(fp);

		if (dm.SystemInitialize == 0) {
			CSeqMain* seqMain = CSeqMain::GetInstance();
			assert(seqMain != nullptr);
			SEQ_LOG seq_log;
			memset(&seq_log, 0x00, sizeof(SEQ_LOG));
			strcpy(seq_log.strSeqLog, fbuff);
			//sprintf(seq_log.strSeqLog, "[%s] [USER = %s] [DEVICE = %s] %s\n", logtime, strUserName, strDeviceName, msg);
			seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_SEQLOG, sizeof(SEQ_LOG), (void*)&seq_log);
		}
	}
	Delete_Dated_File(deleteHead, 90);
	return 0;
}
int CFileLog::LOG_MSG_E(int type, char* func, int line_no, char* format, ...)
{
	char msg[512] = { 0, };
	char fbuff[512] = { 0, };

	va_list args;

	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	char head[512] = "";
	char deleteHead[512] = "";
	char* Path = "C:\\Work\\LOG\\SEQ\\";
	char* logdate = Get_log_date();

	sprintf(head, "%s%s%s%s%s", Path, MachineStatus.strDeviceName, "\\ERROR\\", logdate, "\\");
	sprintf(deleteHead, "%s%s%s", Path, MachineStatus.strDeviceName, "\\ERROR\\");
	CreateDir(head);

	// log file
	char logfilename[512];
	sprintf(logfilename, "%s%s.log", head, logdate);

	FILE* fp;
	if ((fp = fopen(logfilename, "a+")) == NULL) {
		if ((fp = fopen(logfilename, "w+t")) == NULL) {
			return -1;
		}
		else {
			fclose(fp);
		}
	}
	else {
		//struct tm* today;
		//time_t ltime;
		//_tzset();
		//time(&ltime);
		//today = localtime(&ltime);
		//strftime(logtime, 128, "%H:%M:%S", today);
		struct timeb itb;
		struct tm* lt;
		ftime(&itb);
		lt = localtime(&itb.time);
		sprintf(logtime, "%02d:%02d:%02d:%03u", lt->tm_hour, lt->tm_min, lt->tm_sec, itb.millitm);

		if (type == LT_PROCESS) {
			sprintf(fbuff, "%s, %s, USER = %s, DEVICE = %s, TRACE, Call = %s, LIne = %d, %s\n",
							logdate, logtime, UserInfo.strUserName, MachineStatus.strDeviceName, func, line_no, msg);
			fprintf(fp, fbuff);

			CSeqMain* seqMain = CSeqMain::GetInstance();
			assert(seqMain != nullptr);
			seqMain->SEND_UDP(udp_Client, fbuff);

			//MachineStatus.strSeqLogFlag[SeqLogCnt] = true;
			//MachineStatus.strSeqLogLength[SeqLogCnt] = strlen(fbuff) + 1;
			//strcpy(MachineStatus.strSeqLog[SeqLogCnt], fbuff);
			//SeqLogCnt++;
			//if (SeqLogCnt > 100) {
			//	SeqLogCnt = 0;
			//}
		}
		else if (type == LT_ERROR) {
			sprintf(fbuff, "%s, %s, USER = %s, DEVICE = %s, ERROR, Call = %s, LIne = %d, %s\n",
							logdate, logtime, UserInfo.strUserName, MachineStatus.strDeviceName, func, line_no, msg);
			fprintf(fp, fbuff);

			CSeqMain* seqMain = CSeqMain::GetInstance();
			assert(seqMain != nullptr);
			seqMain->SEND_UDP(udp_Client, fbuff);

			//MachineStatus.strSeqLogFlag[SeqLogCnt] = true;
			//MachineStatus.strSeqLogLength[SeqLogCnt] = strlen(fbuff) + 1;
			//strcpy(MachineStatus.strSeqLog[SeqLogCnt], fbuff);
			//SeqLogCnt++;
			//if (SeqLogCnt > 100) {
			//	SeqLogCnt = 0;
			//}
		}
		fclose(fp);

		if (dm.SystemInitialize == 0) {
			CSeqMain* seqMain = CSeqMain::GetInstance();
			assert(seqMain != nullptr);
			SEQ_LOG seq_log;
			memset(&seq_log, 0x00, sizeof(SEQ_LOG));
			strcpy(seq_log.strSeqLog, fbuff);
			//		sprintf(seq_log.strSeqLog, "[%s] [USER = %s] [DEVICE = %s] %s\n", logtime, strUserName, strDeviceName, msg);
			seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_SEQLOG, sizeof(SEQ_LOG), (void*)&seq_log);
		}
	}
	Delete_Dated_File(deleteHead, 90);
	return 0;
}
//int CFileLog::LOG_MSG_E(int type, int errcode, char* format, ...)
//{
//	char msg[260];
//	va_list args;
//
//	va_start(args, format);
//	vsprintf(msg, format, args);
//	va_end(args);
//
//	char logfilename[512];
//	FILE* fp;
//	char tmpbuf[128] = "";
//
//	sprintf(logfilename, Get_log_filename(type));
//
//	if ((fp = fopen(logfilename, "a+")) == NULL) {
//		if ((fp = fopen(logfilename, "w+t")) == NULL) {
//			return -1;
//		}
//		else {
//			fclose(fp);
//		}
//	}
//	else {
//		struct tm* today;
//		time_t ltime;
//		_tzset();
//		time(&ltime);
//		today = localtime(&ltime);
//		strftime(logtime, 128, "%H:%M:%S", today);
//
//		fprintf(fp, "[%s][ERROR CODE = %d] : %s\n", logtime, errcode, msg);
//		fclose(fp);
//	}
//	Delete_Limited_File(type);
//	return 0;
//}
int CFileLog::LOG_MSG_LOT(int type, char* func, int line_no, char* format, ...)
{
	char msg[512];
	char fbuff[512];

	va_list args;

	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	char head[512] = "";
	char* Path = "C:\\Work\\LOG\\LOT\\";
	char* logdate = Get_log_date();

	sprintf(head, "%s%s%s", Path, MachineStatus.strDeviceName, "\\");
	CreateDir(head);

	// log file
	char logfilename[512];
	sprintf(logfilename, "%s%s_%s.log", head, logdate, LotInfo.strLotID);

	FILE* fp;
	if ((fp = fopen(logfilename, "a+")) == NULL) {
		if ((fp = fopen(logfilename, "w+t")) == NULL) {
			return -1;
		}
		else {
			fclose(fp);
		}
	}
	else {
		//struct tm* today;
		//time_t ltime;
		//_tzset();
		//time(&ltime);
		//today = localtime(&ltime);
		//strftime(logtime, 128, "%H:%M:%S", today);
		struct timeb itb;
		struct tm* lt;
		ftime(&itb);
		lt = localtime(&itb.time);
		sprintf(logtime, "%02d:%02d:%02d:%03u", lt->tm_hour, lt->tm_min, lt->tm_sec, itb.millitm);

		sprintf(fbuff, "[%s] %s\n", logtime, msg);
		fprintf(fp, fbuff);

		fclose(fp);

		CSeqMain* seqMain = CSeqMain::GetInstance();
		assert(seqMain != nullptr);
		SEQ_LOG seq_log;
		memset(&seq_log, 0x00, sizeof(SEQ_LOG));
		sprintf(seq_log.strSeqLog, "[%s] [USER = %s] [DEVICE = %s] %s\n", logtime, strUserName, MachineStatus.strDeviceName, msg);
		seqMain->SendCopyDataToMMI(WM_SEQ_TO_MMI_SEQLOG, sizeof(SEQ_LOG), (void*)&seq_log);
	}
	Delete_Dated_File(head, 30);
	return 0;
}
void CFileLog::Delete_Dated_File(char *dir, int ndeleteday)
{
	char delFileDir[512] = "";
	char delFileName[512] = "";

	WIN32_FIND_DATA FindFileData;

	SYSTEMTIME convFTime;

	HANDLE hFind;
	hFind = FindFirstFile((LPCWSTR)dir, &FindFileData);
	
	if (hFind) {
		do {
			if (wcscmp(FindFileData.cFileName, L".") && wcscmp(FindFileData.cFileName, L"..")) {
				if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
					// Read-Only file 처리
					SetFileAttributes(FindFileData.cFileName, FindFileData.dwFileAttributes & ~FILE_ATTRIBUTE_READONLY);
				}
			}
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				sprintf(delFileDir, "%s%ws%s", dir, FindFileData.cFileName, "\\");
				Delete_Dated_File(delFileDir, ndeleteday);
				RemoveDirectory((LPCWSTR)delFileDir);
			}
			else {
				FileTimeToSystemTime(&FindFileData.ftLastWriteTime, &convFTime);
				if (TimeNDayCheck(FindFileData.ftLastAccessTime, ndeleteday)) {
					sprintf(delFileName, "%s%ws", delFileDir, FindFileData.cFileName);
				}
			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
}
void CFileLog::Delete_Limited_File(int type)
{
	struct tm* today;
	time_t ltime, pasttime;

	_tzset();
	time(&ltime);
	today = localtime(&ltime);
	//    printf( "Current time is %s\n", asctime( today ) );

	today->tm_mday = today->tm_mday - 30;

	for (int i = 0; i < 30; i++) {
		if ((pasttime = mktime(today)) != (time_t)-1) {
			strftime(pastdate, 128, "%Y_%m_%d", today);

			char delfilename[128] = "";
			strcpy(delfilename, Get_file_head(type));
			strcat(delfilename, pastdate);
			strcat(delfilename, ".log");
			DeleteFileA(delfilename);

			today->tm_mday--;
		}
		else {
			printf("maketime failed\n");
		}
	}
}
bool CFileLog::TimeNDayCheck(FILETIME ftm, int n_day)
{
	FILETIME ftWriteTime = ftm;
	FILETIME now;
	SYSTEMTIME nowst, convFTime;
	ULARGE_INTEGER t1, t2;

	// 	__int64 IN_WEEK = (__int64)10000000 * 60 * 60 * 24 * 7;
	__int64 IN_DAY = (__int64)10000000 * 60 * 60 * 24;
	// 	__int64 IN_HOUR = (__int64)10000000 * 60 * 60;
	//	__int64 IN_MIN  = (__int64)10000000 * 60;
	//	__int64 IN_SEC =  (__int64)10000000;

	GetSystemTime(&nowst);
	SystemTimeToFileTime(&nowst, &now);

	FileTimeToSystemTime(&ftm, &convFTime);

	memcpy(&t1, &ftWriteTime, sizeof(t1));
	memcpy(&t2, &now, sizeof(t1));
	__int64 diff = (t1.QuadPart < t2.QuadPart) ? (t2.QuadPart - t1.QuadPart) : (t1.QuadPart - t2.QuadPart);

	if (diff > IN_DAY * n_day)
	{
		return TRUE;
	}
	return FALSE;
}
int CFileLog::is_leap_year(int year)
/* year가 윤년이면 1을, 아니면 0을 리턴한다.*/
/* 이 함수는 매크로 함수로 만들어도 된다.   */
{
	if (year % 400 == 0) return(1);
	else if (year % 100 == 0) return(0);
	else if (year % 4 == 0) return(1);
	else return(0);
}

int CFileLog::get_last_day(int year, int month)
/* year년 month월의 마지막 날을 숫자로 리턴한다. */
{
	if (month == 2) {
		if (is_leap_year(year)) return(29);
		else return(28);
	}
	else if (month == 2 || month == 4 || month == 6 || month == 9 || month == 11) return(30);
	else return(31);
}

long CFileLog::get_passed_day(int year, int month, int day, int start_year)
/* start_year년 1월 1일부터 year년 month월 day일까지 경과된 날 수를 리턴한다. */
{
	long passed_day;
	int i;

	passed_day = day - 1;
	/* 윤년이면 366일을 더하고,평년이면 365일을 더한다. */
	for (i = start_year; i < year; i++) if (is_leap_year(i)) passed_day += 366;
	else passed_day += 365;
	for (i = 1; i < month; i++) passed_day += get_last_day(year, month);
	return(passed_day);
}
//////////////////////////////////////////////////////////////////////////
void CFileLog::Delete_Limited_LotInfo_file(void)
{
	struct tm* today;
	time_t ltime, pasttime;

	_tzset();
	time(&ltime);
	today = localtime(&ltime);
	today->tm_mday = today->tm_mday - 60;

	for (int i = 0; i < 60; i++) {
		if ((pasttime = mktime(today)) != (time_t)-1) {
			strftime(pastdate, 128, "%Y_%m_%d", today);

			char delfilename[128] = "";
			strcpy(delfilename, "C:\\WORK\\LOG\\SEQ\\LOT_INFO\\");
			strcat(delfilename, pastdate);
			strcat(delfilename, "_*.*");

			DeleteFileA(delfilename);

			today->tm_mday--;
		}
		else {
			printf("maketime failed\n");
		}
	}
}


void CFileLog::Clear(void)
{
	memset(lotlogfilename, 0, sizeof(lotlogfilename));
}