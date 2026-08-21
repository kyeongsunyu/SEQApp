#ifndef _DEFINE_MACRO_H_
#define _DEFINE_MACRO_H_

#pragma once

//////////////////////////////////////////////////////////////////////////
#define PI						3.14159265359
//////////////////////////////////////////////////////////////////////////
#define FLIP1_SKIP					(dm.UseSkip1&0x00000001)	//	[1]
#define FLIP2_SKIP					(dm.UseSkip1&0x00000002)	//	[2]	
#define BTM_VISION_SKIP 			(dm.UseSkip1&0x00000004)	//	[3]	
#define USESKIP4 						(dm.UseSkip1&0x00000008)	//	[4]	
#define USESKIP5 						(dm.UseSkip1&0x00000010)	//	[5]	
#define USESKIP6						(dm.UseSkip1&0x00000020)	//	[6]	
#define USESKIP7						(dm.UseSkip1&0x00000040)	//	[7]	
#define USESKIP8						(dm.UseSkip1&0x00000080)	//	[8]	
#define USESKIP9						(dm.UseSkip1&0x00000100)	//	[9]	
#define USESKIP10					(dm.UseSkip1&0x00000200)	//	[10]			
#define USESKIP11					(dm.UseSkip1&0x00000400)	//	[11]	
#define USESKIP12					(dm.UseSkip1&0x00000800)	//	[12]
#define USESKIP13					(dm.UseSkip1&0x00001000)	//	[13]
#define USESKIP14					(dm.UseSkip1&0x00002000)	//	[14]
#define USESKIP15					(dm.UseSkip1&0x00004000)	//	[15]
#define USESKIP16					(dm.UseSkip1&0x00008000)	//	[16]
#define USESKIP17					(dm.UseSkip1&0x00010000)	//	[17]
#define USESKIP18					(dm.UseSkip1&0x00020000)	//	[18]
#define USESKIP19					(dm.UseSkip1&0x00040000)	//	[19]
#define USESKIP20					(dm.UseSkip1&0x00080000)	//	[20]
#define USESKIP21					(dm.UseSkip1&0x00100000)	//	[21]
#define USESKIP22					(dm.UseSkip1&0x00200000)	//	[22]	// Z개별 옵션 추가필.
#define USESKIP23					(dm.UseSkip1&0x00400000)	//	[23]	
#define USESKIP24					(dm.UseSkip1&0x00800000)	//	[24]
#define USESKIP25					(dm.UseSkip1&0x01000000)	//	[25]
#define USESKIP26					(dm.UseSkip1&0x02000000)	//	[26]
#define USESKIP27					(dm.UseSkip1&0x04000000)	//	[27]
#define USESKIP28					(dm.UseSkip1&0x08000000)	//	[28]
#define USESKIP29					(dm.UseSkip1&0x10000000)	//	[29]
#define USESKIP30					(dm.UseSkip1&0x20000000)	//	[30]
#define USESKIP31					(dm.UseSkip1&0x40000000)	//	[31]
#define USESKIP32					(dm.UseSkip1&0x80000000)	//	[32]

#define USESKIP33					(dm.UseSkip2&0x00000001)	//	[1]
#define USESKIP34					(dm.UseSkip2&0x00000002)	//	[2]	
#define USESKIP35					(dm.UseSkip2&0x00000004)	//	[3]	
#define USESKIP36					(dm.UseSkip2&0x00000008)	//	[4]	
#define USESKIP37					(dm.UseSkip2&0x00000010)	//	[5]	
#define USESKIP38					(dm.UseSkip2&0x00000020)	//	[6]	
#define USESKIP39					(dm.UseSkip2&0x00000040)	//	[7]	
#define USESKIP40					(dm.UseSkip2&0x00000080)	//	[8]	
#define USESKIP41					(dm.UseSkip2&0x00000100)	//	[9]	
#define USESKIP42					(dm.UseSkip2&0x00000200)	//	[10]
#define USESKIP43					(dm.UseSkip2&0x00000400)	//	[11]
#define USESKIP44					(dm.UseSkip2&0x00000800)	//	[12]
#define USESKIP45					(dm.UseSkip2&0x00001000)	//	[13]
#define USESKIP46					(dm.UseSkip2&0x00002000)	//	[14]
#define USESKIP47					(dm.UseSkip2&0x00004000)	//	[15]
#define USESKIP48					(dm.UseSkip2&0x00008000)	//	[16]
#define USESKIP49					(dm.UseSkip2&0x00010000)	//	[17]
#define USESKIP50					(dm.UseSkip2&0x00020000)	//	[18]
#define USESKIP51					(dm.UseSkip2&0x00040000)	//	[19]
#define USESKIP52					(dm.UseSkip2&0x00080000)	//	[20]
#define USESKIP53					(dm.UseSkip2&0x00100000)	//	[21]
#define USESKIP54					(dm.UseSkip2&0x00200000)	//	[22]
#define USESKIP55					(dm.UseSkip2&0x00400000)	//	[23]
#define USESKIP56					(dm.UseSkip2&0x00800000)	//	[24]
#define USESKIP57					(dm.UseSkip2&0x01000000)	//	[25]
#define USESKIP58					(dm.UseSkip2&0x02000000)	//	[26]
#define USESKIP59					(dm.UseSkip2&0x04000000)	//	[27]
#define USESKIP60					(dm.UseSkip2&0x08000000)	//	[28]
#define USESKIP61					(dm.UseSkip2&0x10000000)	//	[29]
#define USESKIP62					(dm.UseSkip2&0x20000000)	//	[30]
#define USESKIP63					(dm.UseSkip2&0x40000000)	//	[31]
#define USESKIP64					(dm.UseSkip2&0x80000000)	//	[32]

////////////////////////////////////////////////////////
#define SCR_AUTO			    2000
#define SCR_MAN 				3000

/////////////////////////////////////////////////////////
#define BITON(text)		(!text)
#define BITOFF(text)	(text)
#define BITMOV(db,sb){  \
            if(sb){     \
                (db)=1; \
            }           \
            else{       \
                (db)=0; \
            }           \
        }

#define CPLBITMOV(db,sb){  \
            if(sb){        \
                (db)=0;    \
            }              \
            else{          \
                (db)=1;    \
            }              \
         }
#define BITMOVETOOUT(dst,src)\
{\
	if(src)	_ON(dst);\
	else _OFF(dst);\
}

#define CPLBITMOVETOOUT(dst,src)\
{\
	if(!(src))	_ON(dst);\
	else _OFF(dst);\
}

/////////////////////////////////////////////////////////
// I/O
/////////////////////////////////////////////////////////
#define _IN uiobuf.siobuf.sinbuf
#define _OUT uiobuf.siobuf.soutbuf

#define CHIN(n) ((WORD)(uiobuf.wiobuf[n]))
#define CHOUT(n,v) (uiobuf.wiobuf[n]=(WORD)(v))

#define AINON(p) ((uiobuf.siobuf.sinbuf.p)==1)
#define AINOFF(p) ((uiobuf.siobuf.sinbuf.p)==0)

#define BINON(p) ((uiobuf.siobuf.sinbuf.p)==0)
#define BINOFF(p) ((uiobuf.siobuf.sinbuf.p)==1)

#define OUTON(p) ((uiobuf.siobuf.soutbuf.p)==1)
#define OUTOFF(p) ((uiobuf.siobuf.soutbuf.p)==0)

#define _ON(p) ((uiobuf.siobuf.soutbuf.p)=1)
#define _OFF(p) ((uiobuf.siobuf.soutbuf.p)=0)

/////////////////////////////////////////////////////////
// MOTOR
/////////////////////////////////////////////////////////
#define MAXNUMBER_OF_MOTOR    3

#define SUDDEN_STOP			1
#define DECEL_STOP				2

enum {
	Axis_Fault = 0,
	Wait_Reset,
	Lock_Cmd,
	Wait_Cmd,
	Move_CCW,
	Move_CW,
	Move_Home
};

enum {
	Init = 0,
	Go_CCW,
	Go_CW,
	Wait_motorstop,	//3
	Stop_ORG,		//4
	GO_NO_ORG,		//5
	Search_ORG,		//6
	Stop_CCW,		//7
	Stop_No_CCW,
	Complete
};

#define NOOFPK							8
#define PULSE20_1MM					500			// 20mm pitch : 10000 pulse
#define PULSE10_1MM					1000			// 10mm pitch : 10000 pulse
#define PULSE5_1MM					2000			// 5mm pitch  : 10000 pulse
#define ONE_TURN						8000			// 1 turn : 10000 pulse

#define MAX_SPEED						500000		//480kpps
#define JERK_P								6250

#define AUTOSPEED						100			// speed = 100 %
#define VERYFAST							90				// speed = 90 %
#define FAST								80				// speed = 80 %
#define MIDDLE							50				// speed = 50 %
#define SLOW								30				// speed = 30 %
#define MIDSLOW							20				// speed = 20 %
#define VERYSLOW						10				// speed = 10 %

#define MTHOMERDY(mtvar) (!(mtvar)->omove&&BITON((mtvar)->irdy)&&(mtvar)->IsServoOn)
#define MTRDY(mtvar) ((mtvar)->imrs&&(!(mtvar)->omove))
#define MTRDYTM(mtvar,timeval) ((mtvar)->imrs&&(!(mtvar)->omove)&&(tmReady_##mtvar##.TimeOvermS(timeval)))

#define MTWEC(mtvar) ((mtvar)->WorkPos==(mtvar)->CurPos)
#define MTDEC(mtvar) ((mtvar)->DfltWorking==(mtvar)->CurPos)
#define MTCEP(mtvar,pos) ((mtvar)->CurPos==(pos))
#define MTNEP(mtvar,pos) ((mtvar)->NxtPos==(pos))
#define MTPNEP(mtvar,pulse) ((mtvar)->CurArrpos!=(pulse))
#define MTCNEP(mtvar,pos) ((mtvar)->CurPos!=(pos))
#define MTCINP(mtvar,sp,ep) (((sp)<=(mtvar)->CurPos)&&((mtvar)->CurPos<=(ep)))
#define MTNINP(mtvar,sp,ep) (((sp)<=(mtvar)->NxtPos)&&((mtvar)->NxtPos<=(ep)))

#define MTMOVE(mtvar,pos,manauto){\
	if(MTRDY((mtvar))){\
		(mtvar)->NxtPos=(pos);\
		(mtvar)->NxtArrpos=(mtvar)->PositionArray[(pos)];\
		(mtvar)->SpeedDevide=(manauto);\
		(mtvar)->omove=1;\
	}\
}
#define MTARRMOVE(mtvar,pos,arrpos,manauto){\
	if(MTRDY((mtvar))){\
		(mtvar)->NxtPos=(pos);\
		(mtvar)->NxtArrpos=(arrpos);\
		(mtvar)->SpeedDevide=(manauto);\
		(mtvar)->omove=1;\
	}\
}
#define MTRMOVE(mtvar,arrpos){\
	if(BITON((mtvar)->irdy)){\
		(mtvar)->Speed     = 6000;\
		(mtvar)->NxtPos    = 99;\
		(mtvar)->omove     = 1;\
		(mtvar)->ostart    = 0;\
		(mtvar)->fDriving = 1;\
		(mtvar)->MTSRMove(arrpos);\
	}\
}
#define MTRMOVEPLUS(mtvar,pos){\
	(mtvar)->Speed		 = abs((mtvar)->SpeedArray[pos]);\
	(mtvar)->Accel       = abs((mtvar)->Speed)*10;\
	(mtvar)->Decel       = (mtvar)->Accel;\
	arrpos               = ((mtvar)->PositionArray[(pos)]);\
	(mtvar)->NxtPos		 = 99;\
	(mtvar)->Direction	 = 1;\
	(mtvar)->MTSRMove(arrpos);\
}
#define MTRMOVEMINUS(mtvar,pos){\
	(mtvar)->Speed		 = abs((mtvar)->SpeedArray[pos]);\
	(mtvar)->Accel       = abs((mtvar)->Speed)*10;\
	(mtvar)->Decel       = (mtvar)->Accel;\
    arrpos               = -((mtvar)->PositionArray[(pos)]);\
	(mtvar)->NxtPos		 = 99;\
	(mtvar)->Direction	 = -1;\
	(mtvar)->MTSRMove(arrpos);\
}
//#define MTCMOVE(mtvar,dir,manauto){\
//	(mtvar)->SpeedDevide =(manauto);\
//	(mtvar)->Speed  = (int)((mtvar)->SpeedArray[1]*(dir)*((mtvar)->SpeedDevide/100.)*(MachineSpeed/100.));\
//	(mtvar)->Accel  = abs(((mtvar)->Speed)*10);\
//	(mtvar)->CurPos = 299;\
//	(mtvar)->NxtPos = 300;\
//	(mtvar)->ostart=0;\
//	(mtvar)->fDriving=1;\
//	(mtvar)->MTSCMove();\
//}
#define MTCMOVE(mtvar,dir,manauto){\
	(mtvar)->SpeedDevide =(manauto);\
	(mtvar)->Speed  = (int)((mtvar)->SpeedArray[1]*(dir));\
	(mtvar)->Accel  = abs(((mtvar)->Speed)*5);\
	(mtvar)->Decel  = abs(((mtvar)->Speed)*5);\
	(mtvar)->CurPos = 299;\
	(mtvar)->NxtPos = 300;\
	(mtvar)->ostart=0;\
	(mtvar)->fDriving=1;\
	(mtvar)->MTSCMove();\
}
#define MTVELOCITY_OVERRIDE(mtvar,dir,manauto,speed){\
	(mtvar)->SpeedDevide =(manauto);\
	(mtvar)->Speed  = (int)((mtvar)->SpeedArray[speed]*(dir)*((mtvar)->SpeedDevide/100.)*(MachineSpeed/100.));\
	(mtvar)->Accel  = abs(((mtvar)->Speed)*10);\
	(mtvar)->CurPos = 299;\
	(mtvar)->NxtPos = 300;\
	(mtvar)->ostart=0;\
	(mtvar)->fDriving=1;\
	(mtvar)->MTOverRideMove(10);\
	(mtvar)->Direction = (dir);\
}
#define PLUS	 1
#define MINUS   -1
/////////////////////////////////////////////////////////////
// Error
/////////////////////////////////////////////////////////////
#define AIRERR()	(AINOFF(iMainAir1High)||AINOFF(iMainAir2High))

#define EMERON()	(BINON(iEMO) || BINON(iEmptyEMO))

#define SAFETYON()   (AINON(iDoorFront)&&AINON(iDoorRear)&&AINON(iDoorSide))

#define MTEMEROFF(var)\
{\
	(var)->omove=0;\
	(var)->moving=0;\
	(var)->ostart=1;\
	if(!(var)->IsStop)		(var)->MTEStop();\
	(var)->fMotorPause=0;\
	(var)->fDriving=0;\
	(var)->fIMRS=0;\
	(var)->imrs=0;\
	(var)->fDoHome=0;\
	(var)->fMotorHome=0;\
}

#define DATMCHKOFFOFF222(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1##1)&AINON(i##name1##2),AINON(i##name2##1)&AINON(i##name2##2),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}
#define DATMCHKOFFOFF224(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1##1)&AINON(i##name1##2)&AINON(i##name1##3)&AINON(i##name1##4),\
	                  AINON(i##name2##1)&AINON(i##name2##2)&AINON(i##name2##3)&AINON(i##name2##4),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}
#define DATMCHKOFFOFF22(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),AINON(i##name2),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}
#define DATMCHKOFFON22(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),AINON(i##name2),\
	OUTON(o##name1),OUTON(o##name2))==eNewError){\
	ERRIF0(obj.GetErrorCode());\
	_OFF(o##name1);\
	_ON(o##name2);\
	bit.PAutoStop=1;\
	}\
}
#define DATMCHKOFFOFF22B(obj,name1,name2)\
{\
	if(obj.ErrorCheck(BINON(i##name1),BINON(i##name2),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}

#define DATMCHKONOFF22(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),AINON(i##name2),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_ON(o##name1);\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}

#define DATMCHKOFFOFF12(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),!AINON(i##name1),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}

#define DATMCHKONOFF12(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),!AINON(i##name1),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_ON(o##name1);\
		_OFF(o##name2);\
		bit.pautostop=1;\
	}\
}

#define DATMCHKOFFON12(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),!AINON(i##name1),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		_ON(o##name2);\
		bit.PAutoStop=1;\
	}\
}
#define DATMCHKOFFOFF212(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1##1)&&AINON(i##name1##2),!AINON(i##name1##1)||!AINON(i##name1##2),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}
#define DATMCHKOFFOFF412(obj,name1,name2)\
{\
	if(obj.ErrorCheck( AINON(i##name1##1)&&AINON(i##name1##2)&&AINON(i##name1##3)&&AINON(i##name1##4),\
                       !(AINON(i##name1##1)&&AINON(i##name1##2)&&AINON(i##name1##3)&&AINON(i##name1##4)),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}
#define DATMCHKONOFF412(obj,name1,name2)\
{\
	if(obj.ErrorCheck( AINON(i##name1)&&AINON(i##name2)&&AINON(i##name3)&&AINON(i##name4),\
                       AINOFF(i##name1)||AINOFF(i##name2)||AINOFF(i##name3)||AINOFF(i##name4),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_ON(o##name1);\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}
#define DATMCHKOFFON412(obj,name1,name2)\
{\
	if(obj.ErrorCheck( AINON(i##name1)&&AINON(i##name2)&&AINON(i##name3)&&AINON(i##name4),\
                       AINOFF(i##name1)||AINOFF(i##name2)||AINOFF(i##name3)||AINOFF(i##name4),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		_ON(o##name2);\
		bit.PAutoStop=1;\
	}\
}
#define DATMCHK12(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),!AINON(i##name1),\
					  OUTON(o##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		bit.PAutoStop=1;\
	}\
}

#define SATMCHK11(obj,name1)\
{\
	if(obj.ErrorCheck(AINON(i##name1),OUTON(o##name1))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		bit.PAutoStop=1;\
	}\
}
#define SATMCHK11OFF(obj,name1)\
{\
	if(obj.ErrorCheck(AINON(i##name1),OUTON(o##name1))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		bit.PAutoStop=1;\
	}\
}
// 1 output, 1 input, single sole
// Up/Open/Fwd output => Down/Close/Bwd input sensor
#define SATMCHK11OFFCROSS(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),OUTON(o##name2))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name2);\
		bit.PAutoStop=1;\
	}\
}

// Sensor 4, single sole
#define SATMCHKOFF41(obj,name1)\
{\
	if(obj.ErrorCheck(AINON(i##name1##1)&&AINON(i##name1##2)&&AINON(i##name1##3)&&AINON(i##name1##4),\
						OUTON(o##name1))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		bit.PAutoStop=1;\
	}\
}
#define SATMCHKOFF21(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),AINON(i##name2),\
					  OUTON(o##name1),!OUTON(o##name1))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		bit.PAutoStop=1;\
	}\
}

#define SATMCHK21(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1),AINON(i##name2),\
					  OUTON(o##name1),!OUTON(o##name1))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		bit.PAutoStop=1;\
	}\
}

#define SATMCHK221(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1##1)&AINON(i##name1##2),AINON(i##name2##1)&AINON(i##name2##2),\
					  OUTON(o##name1),!OUTON(o##name1))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		bit.PAutoStop=1;\
	}\
}

#define SATMCHKOFF221(obj,name1,name2)\
{\
	if(obj.ErrorCheck(AINON(i##name1##1)&AINON(i##name1##2),AINON(i##name2##1)&AINON(i##name2##2),\
					  OUTON(o##name1),!OUTON(o##name1))==eNewError){\
		ERRIF0(obj.GetErrorCode());\
		_OFF(o##name1);\
		bit.PAutoStop=1;\
	}\
}


#define LOG_TRACE(...)\
	pFileLog->LOG_MSG_P(LT_PROCESS, __FUNCTION__, __LINE__, __VA_ARGS__);

#define LOG_ERROR(...)\
	pFileLog->LOG_MSG_E(LT_ERROR, __FUNCTION__, __LINE__, __VA_ARGS__);

//#define LOG_TRACE(...)\
//	pFileLog->LOG_MSG_P(LT_PROCESS, __FUNCSIG__, __LINE__, __VA_ARGS__);
//
//#define LOG_ERROR(...)\
//	pFileLog->LOG_MSG_E(LT_ERROR, __FUNCSIG__, __LINE__, __VA_ARGS__);

#define LOG_LOT(...)\
	pFileLog->LOG_MSG_LOT(LT_RESULT, __FUNCSIG__, __LINE__, __VA_ARGS__);

//#define LOG_ERROR( errcode, ...)\
//	pFileLog->LOG_MSG_E(LT_ERROR,errcode, __VA_ARGS__);

#define LOG_OPERATION(...)\
	pFileLog->LOG_MSG_P(LT_OPERATION, __FUNCSIG__, __LINE__, __VA_ARGS__);

//#define LOG_TRACE(...)\
//	pFileLog->LOG_MSG_P(LT_PROCESS, _T(__FUNCSIG__), __LINE__, __VA_ARGS__);
//
//#define LOG_ERROR( errcode, ...)\
//	pFileLog->LOG_MSG_E(LT_ERROR,errcode, __VA_ARGS__);
//
//#define LOG_OPERATION(...)\
//	pFileLog->LOG_MSG_P(LT_OPERATION, _T(__FUNCSIG__), __LINE__, __VA_ARGS__);

#endif