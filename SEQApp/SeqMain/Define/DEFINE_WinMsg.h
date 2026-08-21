#ifndef _DEFINE_WIN_MSG_H_
#define _DEFINE_WIN_MSG_H_

#pragma once
enum _eResponseResut {
	RESPONSE_ACK = 0x00,
	RESPONSE_NAK = 0x01,
};

enum _eMessageTarget
{
	SEQ_MODULE = 0x00,
	MMI_MODULE = 0x01,
	COMM_MODULE = 0x02,
	ALL_MODULE = 0x03,
};

enum _eSeqOperation
{
	SEQ_START = 0x01,
	SEQ_STOP = 0x02,
	SEQ_RESET = 0x03,
	SEQ_LOTEND = 0x04,
};

typedef struct
{
	bool bExit;
} SEQ_EXIT, * PSEQ_EXIT;

typedef struct
{
	int nSeqOperation;
} SEQ_OPERATION, * PSEQ_OPERATION;

typedef struct
{
	char strMsg[512];
} NOTIFY_MSG, * PNOTIFY_MSG;

typedef struct
{
	char strUserName[64];
} USER_INFO, * PUSER_INFO;

typedef struct {
	char strLotID[128];
	int nLotCount;
} SEQ_LOT_INFO_REQ, * PSEQ_LOT_INFO_REQ;

typedef struct
{
	int nDeviceNumber;
	char strDeviceName[64];
} DEVICE_INFO, * PDEVICE_INFO;

typedef struct {
	int nMsgNo;
	int nResult;
	char strResultMsg[256];
} SEQ_RSP, * PSEQ_RSP;

typedef struct {
	char strSeqLog[512];
} SEQ_LOG, *PSEQ_LOG;

typedef struct {
	char strLotID[128];
	int nLotCount;
	int TotalUnitCnt;
	int nResult;
	char strUserName[64];
} LOTEND_RESULT, *PLOTEND_RESULT;

// Send Message to Seq
#define WM_APP_LINK_REQ					(WM_APP + 101)
#define WM_APP_LINK_RSP   				(WM_APP + 102)

// Send Cppy Data Message to Seq
#define WM_SEQ_EXIT_REQ   	  			(WM_APP + 1001)
#define WM_SEQ_EXIT_RSP   	  			(WM_APP + 1002)

#define WM_SEQ_OPERATION_REQ   			(WM_APP + 1003)
#define WM_SEQ_OPERATION_RSP   			(WM_APP + 1004)

#define WM_USER_LOG_IN_REQ   			(WM_APP + 1005)
#define WM_USER_LOG_IN_RSP   			(WM_APP + 1006)

#define WM_USER_LOG_OUT_REQ   			(WM_APP + 1007)
#define WM_USER_LOG_OUT_RSP   			(WM_APP + 1008)

#define WM_LOT_INPUT_REQ				(WM_APP + 1009)	
#define WM_LOT_INPUT_RSP				(WM_APP + 1010)

#define WM_LOT_CANCEL_REQ				(WM_APP + 1011)	
#define WM_LOT_CANCEL_RSP				(WM_APP + 1012)

#define WM_DEVICE_INFO_REQ				(WM_APP + 1013)	
#define WM_DEVICE_INFO_RSP				(WM_APP + 1014)

#define WM_LOT_CLEAR_REQ				(WM_APP + 1015)
#define WM_LOT_CLEAR_RSP				(WM_APP + 1016)

#define WM_SEQ_TO_MMI_NOTIFY			(WM_APP + 2001)
#define WM_SEQ_TO_MMI_SEQLOG			(WM_APP + 2002)	
#define WM_SEQ_TO_MMI_LOTEND_CLAR		(WM_APP + 2003)
#define WM_SEQ_TO_MMI_LOTEND_RESULT		(WM_APP + 2004)
#define WM_SEQ_TO_MMI_ALLHOME_COMPLETE	(WM_APP + 2005)

#endif