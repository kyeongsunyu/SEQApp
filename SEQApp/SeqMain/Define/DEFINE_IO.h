#ifndef _IOCONFIG_H_
#define _IOCONFIG_H_

typedef unsigned short IOTYPE;

#define ININITVALUE 0xffff
#define OUTINITVALUE 0xffff

typedef struct {
	/* 0000 */
	IOTYPE iKey10 : 7;										//-- 0000	I00.00 ~ I00.06	// Ten Key Input
	IOTYPE idummy0007 : 1;								//-- 0007	I00.07
	IOTYPE idummy0008 : 1;								//-- 0008	I00.08
	IOTYPE idummy0009 : 1;								//-- 0009	I00.09
	IOTYPE idummy0010 : 1;								//-- 0010	I00.10
	IOTYPE idummy0011 : 1;								//-- 0011	I00.11
	IOTYPE idummy0012 : 1;								//-- 0012	I00.12
	IOTYPE idummy0013 : 1;								//-- 0013	I00.13
	IOTYPE idummy0014 : 1;								//-- 0014	I00.14
	IOTYPE idummy0015 : 1;								//-- 0015	I00.15
								
	/* 0100 */													
	IOTYPE iKeyStart : 1;									//-- 0100	I01.00	
	IOTYPE iKeyStop : 1;									//-- 0101	I01.01	// Start Button
	IOTYPE iKeyReset : 1;									//-- 0102	I01.02	// Stop Button
	IOTYPE idummy0103 : 1;								//-- 0103	I01.03	// Reset Button
	IOTYPE idummy0104 : 1;								//-- 0104	I01.04
	IOTYPE idummy0106 : 1;								//-- 0106	I01.06	// Auto Mode Select Switch
	IOTYPE idummy0107 : 1;								//-- 0107	I01.07	// Teach Mode Select Switch
	IOTYPE idummy0108 : 1;								//-- 0108	I01.08	//
	IOTYPE idummy0105 : 1;								//-- 0105	I01.05	// 
	IOTYPE idummy0109 : 1;								//-- 0109	I01.09	// EMO Alarm,	Contact(B)
	IOTYPE idummy0110 : 1;								//-- 0110	I01.10	//
	IOTYPE idummy0111 : 1;								//-- 0111	I01.11	// Front Door Lock Check
	IOTYPE idummy0112 : 1;								//-- 0112	I01.12	// Rear Door Lock Check
	IOTYPE idummy0113 : 1;								//-- 0113	I01.13	// Side Door Lock Check
	IOTYPE idummy0114 : 1;								//-- 0114	I01.14	//
	IOTYPE idummy0115 : 1;								//-- 0115	I01.15	// 
} _sinbuf;

typedef struct {
	/* 0000 not use */
	IOTYPE ofunnuml : 4;									//-- 0000	O0.00	
	IOTYPE ofunnumh : 4;									//-- 0004	O0.04	
	IOTYPE ofunnum100 : 1;								//-- 0008	O0.08	
	IOTYPE odummy0009 : 1;								//-- 0009	O0.09
	IOTYPE odummy0010 : 1;								//-- 0010	O0.10
	IOTYPE odummy0011 : 1;								//-- 0011	O0.11
	IOTYPE odummy0012 : 1;								//-- 0012	O0.12
	IOTYPE odummy0013 : 1;								//-- 0013	O0.13
	IOTYPE odummy0014 : 1;								//-- 0014	O0.14
	IOTYPE odummy0015 : 1;								//-- 0015	O0.15

	/* 0100 */
	IOTYPE oKeyStart : 1;									//-- 0100	O01.00	// Start Button Lamp
	IOTYPE oKeyStop : 1;									//-- 0101	O01.01	// Stop Button	Lamp
	IOTYPE oKeyReset : 1;									//-- 0102	O01.02	// Reset Button	Lamp
	IOTYPE odummy0103 : 1;								//-- 0103	O01.03	// 
	IOTYPE oTowerLampRed : 1;							//-- 0104	O01.04	// Tower Lamp Red
	IOTYPE oTowerLampYellow : 1;						//-- 0105	O01.05	// Tower Lamp Yellow
	IOTYPE oTowerLampGreen : 1;						//-- 0106	O01.06	// Tower Lamp Green	
	IOTYPE oBuzzer1 : 1;									//-- 0107	O01.07	// Buzzer
	IOTYPE odummy0108 : 1;								//-- 0108	O01.08	 
	IOTYPE odummy0109 : 1;								//-- 0109	O01.09	
	IOTYPE odummy0110 : 1;								//-- 0110	O01.10	
	IOTYPE odummy0111 : 1;								//-- 0111	O01.11	
	IOTYPE odummy0112 : 1;								//-- 0112	O01.12	
	IOTYPE odummy0113 : 1;								//-- 0113	O01.13 
	IOTYPE odummy0114 : 1;								//-- 0114	O01.14	
	IOTYPE odummy0115 : 1;								//-- 0115	O01.15	
} _soutbuf;

#define INCOUNT  (sizeof(_sinbuf)  / sizeof(IOTYPE))
#define OUTCOUNT (sizeof(_soutbuf) / sizeof(IOTYPE))

typedef union {
	_sinbuf sinbuf;
	IOTYPE winbuf[INCOUNT];
} _uinbuf;

typedef union {
	_soutbuf soutbuf;
	IOTYPE woutbuf[OUTCOUNT];
} _uoutbuf;

typedef struct {
	_sinbuf  sinbuf;
	_soutbuf soutbuf;
} _siobuf;

typedef union {
	_siobuf siobuf;
	IOTYPE  wiobuf[INCOUNT + OUTCOUNT];
} _uiobuf;

#endif
