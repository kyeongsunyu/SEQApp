
#ifndef _FILELOG_H_
#define _FILELOG_H_

#include <io.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include <windows.h>
#include <winbase.h>

#pragma once

enum {
	LT_PROCESS = 0,
	LT_OPERATION,
	LT_ERROR,
	LT_RESULT,
};

enum {
	RT_V1 = 1,
	RT_V2 = 2,
	RT_LIFETIME = 3,
	RT_THICKNESS = 4,
};
class CFileLog
{
public:
	CFileLog();
	virtual ~CFileLog();

	char logdate[128];
	char filename[128];
	char logtime[128];
	char lotlogfilename[128];

	char logdate_year[20];
	char logdate_month[20];
	char logdate_day[20];

	char pastdate[128];

	char* Get_file_head(int type);
	void CreateDir(char* Path);
	char* Get_search_path(int type);
	char* Get_log_date();
	char* Get_log_filename(int type);

	int LOG_MSG(int type, char* msg);
	int LOG_MSG_P(int type, char* func, int line_no, char* format, ...);
	int LOG_MSG_E(int type, char* func, int line_no, char* format, ...);
//	int LOG_MSG_E(int type, int errcode, char* format, ...);
	int LOG_MSG_LOT(int type, char* func, int line_no, char* format, ...);

	void Delete_Dated_File(char* dir, int ndeleteday);
	void Delete_Limited_File(int type);
	bool TimeNDayCheck(FILETIME ftm, int n_day);

	int is_leap_year(int year);
	int get_last_day(int year, int month);
	long get_passed_day(int year, int month, int day, int start_year);

	void Delete_Limited_LotInfo_file(void);


	void Clear(void);
};

#endif