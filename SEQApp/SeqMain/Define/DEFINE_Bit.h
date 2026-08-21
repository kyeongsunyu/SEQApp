#ifndef _BITFLAG_H_
#define _BITFLAG_H_

#pragma once

typedef unsigned short BITTYPE;

typedef struct {
	//0000
	BITTYPE PAutoStop : 1;								// 0000
	BITTYPE AutoRun : 1;									// 0001
	BITTYPE AutoRunB : 1;								// 0002
	BITTYPE TestMode : 1;								// 0003
	BITTYPE AllHome : 1;									// 0004
	BITTYPE AllDry : 1;										// 0005
	BITTYPE DryRun : 1;									// 0006
	BITTYPE AllCycleStop : 1;								// 0007
	BITTYPE BeforeEmer : 1;								// 0008
	BITTYPE BuzzerOn : 1;								// 0009
	BITTYPE NewBuzzer : 1;								// 0010
	BITTYPE LotEnd : 1;									// 0011
	BITTYPE LotEndMem : 1;								// 0012
	BITTYPE AllReset : 1;									// 0013
	BITTYPE AllMotionDone : 1;							// 0014
	BITTYPE MotorTunning : 1;							// 0015

	//0100
	BITTYPE dummy0100 : 1;							   	// 0100	                 		
	BITTYPE ButtonLotEnd : 1;							// 0101								
	BITTYPE NotAutoScreen : 1;							// 0102								
	BITTYPE LotEndCntClear : 1;							// 0103								
	BITTYPE DeviceDataReceived : 1;				   	// 0104								
	BITTYPE KeyStartPressed : 1;						// 0105				 				
	BITTYPE TenkeyJogMove : 1;						// 0106				 				
	BITTYPE dummy0107 : 1;						   		// 0107				 				
	BITTYPE dummy0108 : 1;								// 0108								
	BITTYPE dummy0109 : 1;					   			// 0109				 				
	BITTYPE dummy0110 : 1;			   					// 0110								
	BITTYPE ComTestCucle : 1;							// 0111								
	BITTYPE JogCMove : 1;						   		// 0112								
	BITTYPE SafetyReset : 1;					   			// 0113								
	BITTYPE Comm1PacketReceived : 1;			   	// 0114								
	BITTYPE Comm2PacketReceived : 1;			   	// 0115								

	//0200																					
	BITTYPE dummy0200 : 1;								// 0200								
	BITTYPE VisionDataReceived : 1;					// 0201								
	BITTYPE dummy0202 : 1;								// 0202								
	BITTYPE dummy0203 : 1;							   	// 0203								
	BITTYPE dummy0204 : 1;								// 0204								
	BITTYPE dummy0205 : 1;								// 0205							
	BITTYPE dummy0206 : 1;								// 0206								
	BITTYPE dummy0207 : 1;								// 0207								
	BITTYPE dummy0208 : 1;								// 0208							
	BITTYPE dummy0209 : 1;								// 0209				
	BITTYPE dummy0210 : 1;								// 0210				
	BITTYPE dummy0211 : 1;								// 0211				
	BITTYPE dummy0212 : 1;								// 0212					
	BITTYPE dummy0213 : 1;								// 0213					
	BITTYPE dummy0214 : 1;								// 0214			 	
	BITTYPE dummy0215 : 1;								// 0215			 	

	//0300																					
	BITTYPE TopV1DataReceived : 1;					// 0300								
	BITTYPE TopV2DataReceived : 1;					// 0301								
	BITTYPE BtmVDataReceived : 1;					// 0302								
	BITTYPE dummy0303: 1;						 		// 0303								
	BITTYPE dummy0304: 1;								// 0304								
	BITTYPE dummy0305: 1;								// 0305							
	BITTYPE dummy0306: 1;								// 0306								
	BITTYPE dummy0307: 1;								// 0307								
	BITTYPE dummy0308: 1;								// 0308							
	BITTYPE dummy0309: 1;								// 0309				
	BITTYPE dummy0310: 1;								// 0310				
	BITTYPE dummy0311: 1;								// 0311				
	BITTYPE dummy0312: 1;								// 0312					
	BITTYPE dummy0313: 1;								// 0313					
	BITTYPE dummy0314: 1;								// 0314			 	
	BITTYPE dummy0315: 1;								// 0315			 	

	// 0400															
	BITTYPE StageZCycle : 1;								// 0400								
	BITTYPE dummy0401: 1;								// 0401								
	BITTYPE dummy0402: 1;								// 0402								
	BITTYPE dummy0403: 1;	   							// 0403								
	BITTYPE dummy0404: 1;								// 0404								
	BITTYPE dummy0405: 1;								// 0405							
	BITTYPE dummy0406: 1;								// 0406								
	BITTYPE dummy0407: 1;								// 0407								
	BITTYPE dummy0408: 1;								// 0408							
	BITTYPE dummy0409: 1;								// 0409				
	BITTYPE dummy0410: 1;								// 0410				
	BITTYPE dummy0411: 1;								// 0411				
	BITTYPE dummy0412: 1;								// 0412					
	BITTYPE dummy0413: 1;								// 0413					
	BITTYPE dummy0414: 1;								// 0414			 	
	BITTYPE dummy0415: 1;								// 0415			 	

	//0500																				
	BITTYPE dummy0500: 1;								// 0500								
	BITTYPE dummy0501: 1;								// 0501								
	BITTYPE dummy0502: 1;								// 0502								
	BITTYPE dummy0503: 1;								// 0503								
	BITTYPE dummy0504: 1;								// 0504								
	BITTYPE dummy0505: 1;								// 0505							
	BITTYPE dummy0506: 1;								// 0506								
	BITTYPE dummy0507: 1;								// 0507								
	BITTYPE dummy0508: 1;								// 0508							
	BITTYPE dummy0509: 1;								// 0509				
	BITTYPE dummy0510: 1;								// 0510				
	BITTYPE dummy0511: 1;								// 0511				
	BITTYPE dummy0512: 1;								// 0512					
	BITTYPE dummy0513: 1;								// 0513					
	BITTYPE dummy0514: 1;								// 0514			 	
	BITTYPE dummy0515: 1;								// 0515			 	

	//0600																					
	BITTYPE dummy0600: 1;								// 0600								
	BITTYPE dummy0601: 1;								// 0601								
	BITTYPE dummy0602: 1;								// 0602								
	BITTYPE dummy0603: 1;								// 0603								
	BITTYPE dummy0604: 1;								// 0604								
	BITTYPE dummy0605: 1;								// 0605							
	BITTYPE dummy0606: 1;								// 0606								
	BITTYPE dummy0607: 1;								// 0607								
	BITTYPE dummy0608: 1;								// 0608							
	BITTYPE dummy0609: 1;								// 0609				
	BITTYPE dummy0610: 1;								// 0610				
	BITTYPE dummy0611: 1;								// 0611				
	BITTYPE dummy0612: 1;								// 0612					
	BITTYPE dummy0613: 1;								// 0613					
	BITTYPE dummy0614: 1;								// 0614			 	
	BITTYPE dummy0615: 1;								// 0615

	//0700						
	BITTYPE dummy0700: 1;								// 0700								
	BITTYPE dummy0701: 1;								// 0701								
	BITTYPE dummy0702: 1;								// 0702								
	BITTYPE dummy0703: 1;								// 0703								
	BITTYPE dummy0704: 1;								// 0704								
	BITTYPE dummy0705: 1;								// 0705							
	BITTYPE dummy0706: 1;								// 0706								
	BITTYPE dummy0707: 1;								// 0707								
	BITTYPE dummy0708: 1;								// 0708							
	BITTYPE dummy0709: 1;								// 0709				
	BITTYPE dummy0710: 1;								// 0710				
	BITTYPE dummy0711: 1;								// 0711				
	BITTYPE dummy0712: 1;								// 0712					
	BITTYPE dummy0713: 1;								// 0713					
	BITTYPE dummy0714: 1;								// 0714			 	
	BITTYPE dummy0715: 1;								// 0715
	
	// 0800																					
	BITTYPE dumm0800: 1;								// 0800								
	BITTYPE dumm0801: 1;								// 0801								
	BITTYPE dumm0802: 1;								// 0802								
	BITTYPE dumm0803: 1;	   							// 0803								
	BITTYPE dumm0804: 1;	  							// 0804								
	BITTYPE dumm0805: 1;								// 0805							
	BITTYPE dumm0806: 1;								// 0806								
	BITTYPE dumm0807: 1;								// 0807								
	BITTYPE dumm0808: 1;								// 0808							
	BITTYPE dumm0809: 1;								// 0809
	BITTYPE dumm0810: 1;								// 0810				
	BITTYPE dumm0811: 1;								// 0811				
	BITTYPE dumm0812: 1;								// 0812					
	BITTYPE dumm0813: 1;								// 0813					
	BITTYPE dumm0814: 1;								// 0814			 	
	BITTYPE dumm0815: 1;								// 0815

	//0900																					
	BITTYPE  dumm0900: 1;								// 0900								
	BITTYPE  dumm0901: 1;								// 0901								
	BITTYPE  dumm0902: 1;								// 0902								
	BITTYPE  dumm0903: 1;	   							// 0903								
	BITTYPE  dumm0904: 1;								// 0904								
	BITTYPE  dumm0905: 1;								// 0905							
	BITTYPE  dumm0906: 1;								// 0906								
	BITTYPE  dumm0907: 1;								// 0907								
	BITTYPE  dumm0908: 1;								// 0908							
	BITTYPE  dumm0909: 1;								// 0909				
	BITTYPE  dumm0910: 1;								// 0910				
	BITTYPE  dumm0911: 1;								// 0911				
	BITTYPE  dumm0912: 1;								// 0912					
	BITTYPE  dumm0913: 1;								// 0913					
	BITTYPE  dumm0914: 1;								// 0914			 	
	BITTYPE  dumm0915: 1;								// 0915

	// 1000																					
	BITTYPE dumm1000: 1;								// 1000								
	BITTYPE dumm1001: 1;								// 1001								
	BITTYPE dumm1002: 1;								// 1002								
	BITTYPE dumm1003: 1;								// 1003								
	BITTYPE dumm1004: 1;								// 1004								
	BITTYPE dumm1005: 1;								// 1005							
	BITTYPE dumm1006: 1;								// 1006								
	BITTYPE dumm1007: 1;								// 1007								
	BITTYPE dumm1008: 1;								// 1008							
	BITTYPE dumm1009: 1;								// 1009				
	BITTYPE dumm1010: 1;								// 1010				
	BITTYPE dumm1011: 1;								// 1011				
	BITTYPE dumm1012: 1;								// 1012					
	BITTYPE dumm1013: 1;								// 1013					
	BITTYPE dumm1014: 1;								// 1014			 	
	BITTYPE dumm1015: 1;								// 1015

	// 1100																					
	BITTYPE dumm1100: 1;								// 1100								
	BITTYPE dumm1101: 1;								// 1101								
	BITTYPE dumm1102: 1;								// 1102								
	BITTYPE dumm1103: 1;								// 1103								
	BITTYPE dumm1104: 1;								// 1104								
	BITTYPE dumm1105: 1;								// 1105							
	BITTYPE dumm1106: 1;								// 1106								
	BITTYPE dumm1107: 1;								// 1107								
	BITTYPE dumm1108: 1;								// 1108							
	BITTYPE dumm1109: 1;								// 1109				
	BITTYPE dumm1110: 1;								// 1110				
	BITTYPE dumm1111: 1;								// 1111				
	BITTYPE dumm1112: 1;								// 1112					
	BITTYPE dumm1113: 1;								// 1113					
	BITTYPE dumm1114: 1;								// 1114			 	
	BITTYPE dumm1115: 1;								// 1115

	// 1200																					
	BITTYPE Edumm1200: 1;								// 1200								
	BITTYPE Edumm1201: 1;								// 1201								
	BITTYPE Edumm1202: 1;								// 1202								
	BITTYPE Edumm1203: 1;								// 1203								
	BITTYPE Edumm1204: 1;								// 1204								
	BITTYPE Edumm1205: 1;								// 1205							
	BITTYPE Edumm1206: 1;								// 1206								
	BITTYPE Edumm1207: 1;								// 1207								
	BITTYPE Edumm1208: 1;								// 1208							
	BITTYPE Edumm1209: 1;								// 1209				
	BITTYPE Edumm1210: 1;								// 1210				
	BITTYPE Edumm1211: 1;								// 1211				
	BITTYPE ddumm1212: 1;								// 1212					
	BITTYPE ddumm1213: 1;								// 1213					
	BITTYPE ddumm1214: 1;								// 1214			 	
	BITTYPE ddumm1215: 1;								// 1215

	// 1300																					
	BITTYPE Edumm1300: 1;								// 1300								
	BITTYPE Edumm1301: 1;								// 1301								
	BITTYPE Edumm1302: 1;								// 1302								
	BITTYPE Edumm1303: 1;			   					// 1303								
	BITTYPE Edumm1304: 1;								// 1304								
	BITTYPE Edumm1305: 1;								// 1305							
	BITTYPE Edumm1306: 1;								// 1306								
	BITTYPE Edumm1307: 1;								// 1307								
	BITTYPE Edumm1308: 1;								// 1308							
	BITTYPE Edumm1309: 1;								// 1309				
	BITTYPE Edumm1310: 1;								// 1310				
	BITTYPE Edumm1311: 1;								// 1311				
	BITTYPE ddumm1312: 1;								// 1312					
	BITTYPE ddumm1313: 1;								// 1313					
	BITTYPE ddumm1314: 1;								// 1314			 	
	BITTYPE ddumm1315: 1;								// 1315

	// 1400																					
	BITTYPE Edumm1400: 1;	;							// 1400								
	BITTYPE Edumm1401: 1;	;							// 1401								
	BITTYPE Edumm1402: 1;	;							// 1402								
	BITTYPE Edumm1403: 1;	;			   				// 1403								
	BITTYPE Edumm1404: 1;	;							// 1404								
	BITTYPE Edumm1405: 1;	;							// 1405							
	BITTYPE Edumm1406: 1;	;							// 1406								
	BITTYPE Edumm1407: 1;	;							// 1407								
	BITTYPE Edumm1408: 1;								// 1408							
	BITTYPE Edumm1409: 1;								// 1409				
	BITTYPE Edumm1410: 1;								// 1410				
	BITTYPE Edumm1411: 1;								// 1411				
	BITTYPE ddumm1412: 1;								// 1412					
	BITTYPE ddumm1413: 1;								// 1413					
	BITTYPE ddumm1414: 1;								// 1414			 	
	BITTYPE ddumm1415: 1;								// 1415

	// 1500																					
	BITTYPE dummy1500 : 1;								// 1500						
	BITTYPE dummy1501 : 1;								// 1501						
	BITTYPE dummy1502 : 1;								// 1502						
	BITTYPE dummy1503 : 1;					 			// 1503						
	BITTYPE dummy1504 : 1;								// 1504						
	BITTYPE dummy1505 : 1;								// 1505					
	BITTYPE dummy1506 : 1;								// 1506						
	BITTYPE dummy1507 : 1;								// 1507						
	BITTYPE dummy1508 : 1;								// 1508					
	BITTYPE dummy1509 : 1;								// 1509			
	BITTYPE dummy1510 : 1;								// 1510			
	BITTYPE dummy1511 : 1;								// 1511			
	BITTYPE dummy1512 : 1;								// 1512			
	BITTYPE dummy1513 : 1;								// 1513			
	BITTYPE MotorTest : 1;								// 1514			
	BITTYPE dummy1515 : 1;								// 1515			

	// 1600																					
	BITTYPE dummy1600 : 1;								// 1600								
	BITTYPE dummy1601 : 1;								// 1601								
	BITTYPE dummy1602 : 1;								// 1602								
	BITTYPE dummy1603 : 1;								// 1603								
	BITTYPE dummy1604 : 1;					   			// 1604								
	BITTYPE dummy1605 : 1;								// 1605								
	BITTYPE dummy1606 : 1;								// 1606							
	BITTYPE dummy1607 : 1;								// 1607								
	BITTYPE dummy1608 : 1;								// 1608								
	BITTYPE dummy1609 : 1;								// 1609							
	BITTYPE dummy1610 : 1;								// 1610				
	BITTYPE dummy1611 : 1;								// 1611				
	BITTYPE dummy1612 : 1;								// 1612				
	BITTYPE dummy1613 : 1;								// 1613					
	BITTYPE dummy1614 : 1;								// 1614					
	BITTYPE dummy1615 : 1;								// 1615			 	

	// 1700																					
	BITTYPE dummy1700 : 1;								// 1700								
	BITTYPE dummy1701 : 1;								// 1701								
	BITTYPE dummy1702 : 1;								// 1702								
	BITTYPE dummy1703 : 1;		  						// 1703								
	BITTYPE dummy1704 : 1;								// 1704								
	BITTYPE dummy1705 : 1;								// 1705							
	BITTYPE dummy1706 : 1;								// 1706								
	BITTYPE dummy1707 : 1;								// 1707								
	BITTYPE dummy1708 : 1;								// 1708							
	BITTYPE dummy1709 : 1;								// 1709				
	BITTYPE dummy1710 : 1;								// 1710				
	BITTYPE dummy1711 : 1;								// 1711				
	BITTYPE dummy1712 : 1;								// 1712					
	BITTYPE dummy1713 : 1;								// 1713					
	BITTYPE dummy1714 : 1;								// 1714			 	
	BITTYPE dummy1715 : 1;								// 1715

	// 1800																				
	BITTYPE dummy1800: 1;								// 1800								
	BITTYPE dummy1801: 1;								// 1801								
	BITTYPE dummy1802: 1;								// 1802								
	BITTYPE dummy1803: 1;								// 1803								
	BITTYPE dummy1804: 1;								// 1804								
	BITTYPE dummy1805: 1;								// 1805							
	BITTYPE dummy1806: 1;								// 1806								
	BITTYPE dummy1807: 1;								// 1807								
	BITTYPE dummy1808: 1;								// 1808							
	BITTYPE dummy1809: 1;								// 1809				
	BITTYPE dummy1810: 1;								// 1810				
	BITTYPE dummy1811: 1;								// 1811				
	BITTYPE dummy1812: 1;								// 1812					
	BITTYPE dummy1813: 1;								// 1813					
	BITTYPE dummy1814: 1;								// 1814			 	
	BITTYPE dummy1815: 1;								// 1815

	// 1900																				
	BITTYPE dummy1900 : 1;								// 1900								
	BITTYPE dummy1901 : 1;								// 1901								
	BITTYPE dummy1902 : 1;								// 1902								
	BITTYPE dummy1903 : 1;					   			// 1903								
	BITTYPE dummy1904 : 1;								// 1904								
	BITTYPE dummy1905 : 1;								// 1905							
	BITTYPE dummy1906 : 1;								// 1906								
	BITTYPE dummy1907 : 1;								// 1907								
	BITTYPE dummy1908 : 1;								// 1908							
	BITTYPE dummy1909 : 1;								// 1909				
	BITTYPE dummy1910 : 1;								// 1910				
	BITTYPE dummy1911 : 1;								// 1911				
	BITTYPE dummy1912 : 1;								// 1912					
	BITTYPE dummy1913 : 1;								// 1913					
	BITTYPE dummy1914 : 1;								// 1914			 	
	BITTYPE dummy1915 : 1;								// 1915

	// 2000																				
	BITTYPE dummy2000 : 1;								// 2000								
	BITTYPE dummy2001 : 1;								// 2001								
	BITTYPE dummy2002 : 1;								// 2002								
	BITTYPE dummy2003 : 1;					   			// 2003								
	BITTYPE dummy2004 : 1;								// 2004								
	BITTYPE dummy2005 : 1;								// 2005							
	BITTYPE dummy2006 : 1;								// 2006								
	BITTYPE dummy2007 : 1;								// 2007								
	BITTYPE dummy2008 : 1;								// 2008							
	BITTYPE dummy2009 : 1;								// 2009				
	BITTYPE dummy2010 : 1;								// 2010				
	BITTYPE dummy2011 : 1;								// 2011				
	BITTYPE dummy2012 : 1;								// 2012					
	BITTYPE dummy2013 : 1;								// 2013					
	BITTYPE dummy2014 : 1;								// 2014			 	
	BITTYPE dummy2015 : 1;								// 2015

	// 2100																				
	BITTYPE dummy2100 : 1;								// 2100								
	BITTYPE dummy2101 : 1;								// 2101								
	BITTYPE dummy2102 : 1;								// 2102								
	BITTYPE dummy2103 : 1;					   			// 2103								
	BITTYPE dummy2104 : 1;								// 2104								
	BITTYPE dummy2105 : 1;								// 2105							
	BITTYPE dummy2106 : 1;								// 2106								
	BITTYPE dummy2107 : 1;								// 2107								
	BITTYPE dummy2108 : 1;								// 2108							
	BITTYPE dummy2109 : 1;								// 2109				
	BITTYPE dummy2110 : 1;								// 2110				
	BITTYPE dummy2111 : 1;								// 2111				
	BITTYPE dummy2112 : 1;								// 2112					
	BITTYPE dummy2113 : 1;								// 2113					
	BITTYPE dummy2114 : 1;								// 2114			 	
	BITTYPE dummy2115 : 1;								// 2115

	// 2200																				
	BITTYPE dummy2200 : 1;								// 2200								
	BITTYPE dummy2201 : 1;								// 2201								
	BITTYPE dummy2202 : 1;								// 2202								
	BITTYPE dummy2203 : 1;					   			// 2203								
	BITTYPE dummy2204 : 1;								// 2204								
	BITTYPE dummy2205 : 1;								// 2205							
	BITTYPE dummy2206 : 1;								// 2206								
	BITTYPE dummy2207 : 1;								// 2207								
	BITTYPE dummy2208 : 1;								// 2208							
	BITTYPE dummy2209 : 1;								// 2209				
	BITTYPE dummy2210 : 1;								// 2210				
	BITTYPE dummy2211 : 1;								// 2211				
	BITTYPE dummy2212 : 1;								// 2212					
	BITTYPE dummy2213 : 1;								// 2213					
	BITTYPE dummy2214 : 1;								// 2214			 	
	BITTYPE dummy2215 : 1;								// 2215

	// 2300																			
	BITTYPE dummy2300 : 1;								// 2300								
	BITTYPE dummy2301 : 1;								// 2301								
	BITTYPE dummy2302 : 1;								// 2302								
	BITTYPE dummy2303 : 1;					   			// 2303								
	BITTYPE dummy2304 : 1;								// 2304								
	BITTYPE dummy2305 : 1;								// 2305							
	BITTYPE dummy2306 : 1;								// 2306								
	BITTYPE dummy2307 : 1;								// 2307								
	BITTYPE dummy2308 : 1;								// 2308							
	BITTYPE dummy2309 : 1;								// 2309				
	BITTYPE dummy2310 : 1;								// 2310				
	BITTYPE dummy2311 : 1;								// 2311				
	BITTYPE dummy2312 : 1;								// 2312					
	BITTYPE dummy2313 : 1;								// 2313					
	BITTYPE dummy2314 : 1;								// 2314			 	
	BITTYPE dummy2315 : 1;								// 2315

	// 2400																			
	BITTYPE dummy2400 : 1;								// 2400								
	BITTYPE dummy2401 : 1;								// 2401								
	BITTYPE dummy2402 : 1;								// 2402								
	BITTYPE dummy2403 : 1;					   			// 2403								
	BITTYPE dummy2404 : 1;								// 2404								
	BITTYPE dummy2405 : 1;								// 2405							
	BITTYPE dummy2406 : 1;								// 2406								
	BITTYPE dummy2407 : 1;								// 2407								
	BITTYPE dummy2408 : 1;								// 2408							
	BITTYPE dummy2409 : 1;								// 2409				
	BITTYPE dummy2410 : 1;								// 2410				
	BITTYPE dummy2411 : 1;								// 2411				
	BITTYPE dummy2412 : 1;								// 2412					
	BITTYPE dummy2413 : 1;								// 2413					
	BITTYPE dummy2414 : 1;								// 2414			 	
	BITTYPE dummy2415 : 1;								// 2415
} _bit;

typedef union {
	_bit bit;
	BITTYPE wbitbuf[sizeof(_bit) / sizeof(BITTYPE)];
} _ubitbuf;


#endif
