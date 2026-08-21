#ifndef _DATA_MEMORY_H_
#define _DATA_MEMORY_H_

#pragma once

typedef unsigned long DMTYPE;

typedef struct {
    DMTYPE SERIALNO;						    // #00: MMI->SEQ MMI Use , Don't touch in seqeunce
    DMTYPE SEQLAMPSTATUS;				    // #01: SEQ->MMI SEQ Lamp Status
    DMTYPE MmiButtonOperation;			    // #02: MMI->SEQ MMI Lamp Status
    DMTYPE errorcode;						    // #03: SEQ->MMI Eeeor Code
    DMTYPE FirstErrorCode;       			    // #04:	SEQ->MMI First Error code for MTBA/MTBF
    DMTYPE MTBA_MTBF;	    			    // #05:	SEQ->MMI MTBA_MTBF
    DMTYPE SystemInitialize;        		    // #06: SEQ->MMI SEQ Initial finish
    DMTYPE ScreenNo;						    // #07: MMI->SEQ Screen No 1:Auto
    DMTYPE LampStatus;        				    // #08: DUMMY08
    DMTYPE LampTest;         				    // #09: DUMMY09

    DMTYPE DeviceNo;         				    // #10:	MMI->SEQ Device No
    DMTYPE DeviceOptionFlag1;         	    // #11: MMI->SEQ Device Option Flag 1(32)
    DMTYPE DeviceOptionFlag2;        	    // #12: MMI->SEQ Device Option Flag 2(64)
    DMTYPE DeviceOptionFlag3;         	    // #13: MMI->SEQ Device Option Flag 3(96)
    DMTYPE dummy14;         				    // #14:
    DMTYPE DeviceWriteFlag;         		    // #15: MMI->SEQ 1: MMI Write Start 2: Write Finish
    DMTYPE UseSkip1;         				    // #16: MMI->SEQ (32)
    DMTYPE UseSkip2;         				    // #17: MMI->SEQ (64)
    DMTYPE dummy18;			         	    // #18: SEQ->MMI Barcode Read Start Trigger
    DMTYPE MotorTestNo;  					    // #19:	MMI->SEQ Barcode Read Complete

    DMTYPE TenKeyNo;		    			    // #20: MMI->SEQ Software Ten Key no.
    DMTYPE TenKeySet;	     				    // #21: MMI->SEQ Software Ten Key set. 1:*, 2:#, 3:STOP
    DMTYPE TunningMotorNo;     			    // #22: MMI->SEQ Motor Tunning No.
    DMTYPE spmcount;         				    // #23:
    DMTYPE dummy24;         				    // #24:
    DMTYPE inputcheck;         				    // #25:
    DMTYPE dummy26;         				    // #26:
    DMTYPE MachineSpeed;       			    // #27:
    DMTYPE scantime;         				    // #28:
    DMTYPE scantimemax;        			    // #29:
    //////////////////////////////////////////////////////////////////////////
    // NO.30 Below for Sequence
    DMTYPE UPH;		       					    // #30: SEQ->MMI
    DMTYPE TPH;								    // #31: SEQ->MMI
    DMTYPE inputcnt;   						    // #32: SEQ->MMI
    DMTYPE unloadingcount;   				    // #33: SEQ->MMI
    DMTYPE dummy34;			 			    // #34: SEQ->MMI
    DMTYPE dummy35;   					    // #35: SEQ->MMI
    DMTYPE dummy36;   					    // #36: SEQ->MMI
    DMTYPE dummy37;   					    // #37: SEQ->MMI
    DMTYPE dummy38;   					    // #38: SEQ->MMI
    DMTYPE dummy39;   					    // #39: SEQ->MMI

    DMTYPE FrontPkCenterOffset; 			    // #40: SEQ->MMI
    DMTYPE RearPkCenterOffset;			    // #41: SEQ->MMI
    DMTYPE Set3PointOffset;				    // #42: SEQ->MMI
    DMTYPE dummy43;   					    // #43: SEQ->MMI
    DMTYPE dummy44;	  					    // #44:
    DMTYPE dummy45;						    // #45:
    DMTYPE dummy46;						    // #46:
    DMTYPE dummy47;					        // #47:
    DMTYPE dummy48;   					    // #48:
    DMTYPE dummy49;				  	        // #49:

    DMTYPE checktime;				 		    // #50:
    DMTYPE semilabchecktime;				    // #51:
    DMTYPE isrtwfcheck1;       				    // #52:
    DMTYPE waferguidetesttime;    		    // #53:
    DMTYPE dummy54;         				    // #54:
    DMTYPE dummy55;         				    // #55:
    DMTYPE dummy56;         				    // #56:
    DMTYPE dummy57;         				    // #57:
    DMTYPE dummy58;         				    // #58:
    DMTYPE dummy59;         				    // #59:

    DMTYPE LotEndMMICheck;         	    // #60:
    DMTYPE dummy61;         				    // #61:
    DMTYPE dummy62;         				    // #62:
    DMTYPE dummy63;         				    // #63:
    DMTYPE dummy64;         				    // #64:
    DMTYPE dummy65;        				    // #65:
    DMTYPE dummy66;         				    // #66:
    DMTYPE dummy67;         				    // #67:
    DMTYPE dummy68;         				    // #68:
    DMTYPE dummy69;         				    // #69:

    DMTYPE LPkPickingCount;         		    // #70:
    DMTYPE RPkPickingCount;      		    // #71:
    DMTYPE dummy72;         				    // #72:
    DMTYPE dummy73;         				    // #73:
    DMTYPE dummy74;         				    // #74:
    DMTYPE dummy75;         				    // #75:
    DMTYPE dummy76;         				    // #76:
    DMTYPE dummy77;         				    // #77:
    DMTYPE dummy78;         				    // #78:
    DMTYPE dummy79;         				    // #79:

    DMTYPE dummy80;         				    // #80:
    DMTYPE dummy81;         				    // #81:
    DMTYPE dummy82;         				    // #82:
    DMTYPE dummy83;         				    // #83:
    DMTYPE dummy84;         				    // #84:
    DMTYPE dummy85;         				    // #85:
    DMTYPE dummy86;         				    // #86:
    DMTYPE dummy87;         				    // #87:
    DMTYPE dummy88;         				    // #88:
    DMTYPE dummy89;         				    // #89:

    DMTYPE dummy90;         				    // #90:
    DMTYPE dummy91;         				    // #91:
    DMTYPE dummy92;         				    // #92:
    DMTYPE dummy93;         				    // #93:
    DMTYPE dummy94;         				    // #94:
    DMTYPE dummy95;         				    // #95:
    DMTYPE dummy96;         				    // #96:
    DMTYPE dummy97;         				    // #97:
    DMTYPE dummy98;         				    // #98:
    DMTYPE dummy99;         				    // #99:

    DMTYPE LifeTimeFrontPkPad1;			    // #100:
    DMTYPE LifeTimeFrontPkPad2;	            // #101:
    DMTYPE LifeTimeFrontPkPad3;	            // #102:
    DMTYPE LifeTimeFrontPkPad4;	            // #103:
    DMTYPE LifeTimeFrontPkPad5;	            // #104:
    DMTYPE LifeTimeFrontPkPad6;   	        // #105:
    DMTYPE LifeTimeFrontPkPad7;	            // #106:
    DMTYPE LifeTimeFrontPkPad8;  	        // #107:
    DMTYPE LifeTimeRearPkPad1;  	        // #108:
    DMTYPE LifeTimeRearPkPad2;  	        // #109:

    DMTYPE LifeTimeRearPkPad3;              // #110:
    DMTYPE LifeTimeRearPkPad4;              // #111:
    DMTYPE LifeTimeRearPkPad5;              // #112:
    DMTYPE LifeTimeRearPkPad6;              // #113:
    DMTYPE LifeTimeRearPkPad7;              // #114:
    DMTYPE LifeTimeRearPkPad8;              // #115:
    DMTYPE LifeTimeSponge;                   // #116:
    DMTYPE GoodTray1InCnt;                   // #117:
    DMTYPE GoodTray2InCnt;  	                // #118:
    DMTYPE ReworkTrayInCnt;  	            // #119:

    DMTYPE NGTrayInCnt;   	                    // #120:
    DMTYPE dummy121;                    	    // #121:
    DMTYPE dummy122;	                        // #122:
    DMTYPE dummy123;                         // #123:
    DMTYPE dummy124;                         // #124:
    DMTYPE dummy125;                         // #125:
    DMTYPE dummy126;                         // #126:
    DMTYPE dummy127;                         // #127:
    DMTYPE dummy128;                         // #128:
    DMTYPE dummy129;                         // #129:

    DMTYPE dummy130;                         // #130:
    DMTYPE dummy131;                         // #131:
    DMTYPE dummy132;                         // #132:
    DMTYPE dummy133;	                        // #133:
    DMTYPE dummy134;                		    // #134:
    DMTYPE dummy135;      	                // #135:
    DMTYPE dummy136;     		                // #136:
    DMTYPE dummy137;    		                // #137:
    DMTYPE dummy138;      	                // #138:
    DMTYPE dummy139;     		                // #139:

    DMTYPE dummy140;      	                // #140:
    DMTYPE dummy141;     	            	    // #141:
    DMTYPE dummy142;    	            	    // #142:
    DMTYPE dummy143;     	            	    // #143:
    DMTYPE dummy144;		            	    // #144:
    DMTYPE dummy145;      	                // #145:
    DMTYPE dummy146;    	            	    // #146:
    DMTYPE dummy147;     		                // #147:
    DMTYPE dummy148;      	                // #148:
    DMTYPE dummy149;                        	// #149:

    DMTYPE dummy150;     	            	    // #150:
    DMTYPE dummy151;		            	    // #151:
    DMTYPE dummy152;                    	    // #152:
    DMTYPE dummy153;		            	    // #153:
    DMTYPE dummy154;                    	    // #154:
    DMTYPE dummy155;                      	// #155:
    DMTYPE dummy156;                      	// #156:
    DMTYPE dummy157;                        	// #157:
    DMTYPE dummy158;                        	// #158:
    DMTYPE dummy159;     	            	    // #159:

    DMTYPE dummy160;                        	// #160:
    DMTYPE dummy161;     	            	    // #161:
    DMTYPE dummy162;                        	// #162:
    DMTYPE dummy163;                        	// #163:
    DMTYPE dummy164;                 		    // #164:
    DMTYPE dummy165;        				    // #165:
    DMTYPE dummy166;        				    // #166:
    DMTYPE dummy167;        				    // #167:
    DMTYPE dummy168;        				    // #168:
    DMTYPE dummy169;        				    // #169:

    DMTYPE dummy170;        				    // #170:
    DMTYPE dummy171;        				    // #171:
    DMTYPE dummy172;        				    // #172:
    DMTYPE dummy173;        				    // #173:
    DMTYPE dummy174;        				    // #174:
    DMTYPE dummy175;        				    // #175:
    DMTYPE dummy176;        				    // #176:
    DMTYPE dummy177;        				    // #177:
    DMTYPE dummy178;        				    // #178:
    DMTYPE dummy179;        				    // #179:

    DMTYPE dummy180;        				    // #180:
    DMTYPE dummy181;        				    // #181:
    DMTYPE dummy182;        				    // #182:
    DMTYPE dummy183;        				    // #183:
    DMTYPE dummy184;        				    // #184:
    DMTYPE dummy185;        				    // #185:
    DMTYPE dummy186;        				    // #186:
    DMTYPE dummy187;        				    // #187:
    DMTYPE dummy188;        				    // #188:
    DMTYPE dummy189;        				    // #189:

    DMTYPE dummy190;						    // #190:
    DMTYPE dummy191;        				    // #191:
    DMTYPE dummy192;        				    // #192:
    DMTYPE dummy193;        				    // #193:
    DMTYPE dummy194;        				    // #194:
    DMTYPE dummy195;        				    // #195:
    DMTYPE dummy196;        				    // #196:
    DMTYPE dummy197;        				    // #197:
    DMTYPE dummy198;        				    // #198:
    DMTYPE dummy199;        				    // #199:

    DMTYPE dummy200;					        // #200:
    DMTYPE dummy201;					        // #201:
    DMTYPE dummy202;					        // #202:
    DMTYPE dummy203;					        // #203:
    DMTYPE dummy204;					        // #204:
    DMTYPE dummy205;					        // #205:
    DMTYPE dummy206;	    			        // #206:
    DMTYPE dummy207;        			        // #207:
    DMTYPE dummy208;        			        // #208:
    DMTYPE dummy209;        			        // #209:

    DMTYPE dummy210;       				    // #210:
    DMTYPE dummy211;       				    // #211:
    DMTYPE dummy212;		     		        // #212:
    DMTYPE dummy213;					        // #213:
    DMTYPE dummy214;		    		        // #214:
    DMTYPE dummy215;		      		        // #215:
    DMTYPE dummy216;					        // #216:
    DMTYPE dummy217;		     		        // #217:
    DMTYPE dummy218;       				    // #218:
    DMTYPE dummy219;       				    // #219:

    DMTYPE dummy220;       				    // #220:
    DMTYPE dummy221;       				    // #221:
    DMTYPE dummy222;        			        // #222:
    DMTYPE dummy223;        			        // #223:
    DMTYPE dummy224;        			        // #224:
    DMTYPE dummy225;        			        // #225:
    DMTYPE dummy226;       				    // #226:
    DMTYPE dummy227;       				    // #227:
    DMTYPE dummy228;       				    // #228:
    DMTYPE dummy229;       				    // #229:

    DMTYPE dummy230;				    	    // #230:
    DMTYPE dummy231;        		    	    // #231:
    DMTYPE dummy232;        		    	    // #232:
    DMTYPE dummy233;        		    	    // #233:
    DMTYPE dummy234;        		    	    // #234:
    DMTYPE dummy235;        		    	    // #235:
    DMTYPE dummy236;        		    	    // #236:
    DMTYPE dummy237;        		    	    // #237:
    DMTYPE dummy238;        		    	    // #238:
    DMTYPE dummy239;        		    	    // #239:

    DMTYPE dummy240;        		    	    // #240:
    DMTYPE dummy241;        		    	    // #241:
    DMTYPE dummy242;        		    	    // #242:
    DMTYPE dummy243;        		    	    // #243:
    DMTYPE dummy244;        		    	    // #244:
    DMTYPE dummy245;        		    	    // #245:
    DMTYPE dummy246;        		    	    // #246:
    DMTYPE dummy247;        		    	    // #247:
    DMTYPE dummy248;        		    	    // #248:
    DMTYPE dummy249;        		    	    // #249:

    DMTYPE dummy250;        		    	    // #250:
    DMTYPE dummy251;        		    	    // #251:
    DMTYPE dummy252;        		    	    // #252:
    DMTYPE dummy253;        		    	    // #253:
    DMTYPE dummy254;        			        // #254:
    DMTYPE dummy255;                         // #255:
    DMTYPE dummy256;                         // #256:
    DMTYPE dummy257;                         // #257:
    DMTYPE dummy258;                         // #258:
    DMTYPE dummy259;                         // #259:

    DMTYPE dummy260;                        // #260:
    DMTYPE dummy261;                        // #261:
    DMTYPE dummy262;                        // #262:
    DMTYPE dummy263;                        // #263:
    DMTYPE dummy264;                        // #264:
    DMTYPE dummy265;                        // #265:
    DMTYPE dummy266;                        // #266:
    DMTYPE dummy267;                        // #267:
    DMTYPE dummy268;                        // #268:
    DMTYPE dummy269;                        // #269:

    DMTYPE dummy270;                        // #270:
    DMTYPE dummy271;                        // #271:
    DMTYPE dummy272;                        // #272:
    DMTYPE dummy273;                        // #273:
    DMTYPE dummy274;                        // #274:
    DMTYPE dummy275;                        // #275:
    DMTYPE dummy276;                        // #276:
    DMTYPE dummy277;                        // #277:
    DMTYPE dummy278;                        // #278:
    DMTYPE dummy279;                        // #279:

    DMTYPE dummy280;                        // #280:
    DMTYPE dummy281;                        // #281:
    DMTYPE dummy282;                        // #282:
    DMTYPE dummy283;                        // #283:
    DMTYPE dummy284;                        // #284:
    DMTYPE dummy285;                        // #285:
    DMTYPE dummy286;                        // #286:
    DMTYPE dummy287;                        // #287:
    DMTYPE dummy288;                        // #288:
    DMTYPE dummy289;                        // #289:

    DMTYPE dummy290;                        // #290:
    DMTYPE dummy291;                        // #291:
    DMTYPE dummy292;                        // #292:
    DMTYPE dummy293;                        // #293:
    DMTYPE dummy294;                        // #294:
    DMTYPE dummy295;                        // #295:
    DMTYPE dummy296;                        // #296:
    DMTYPE dummy297;                        // #297:
    DMTYPE dummy298;                        // #298:
    DMTYPE dummy299;                        // #299:
} _dm;

typedef union {
    _dm dm;
    DMTYPE wdmbuf[sizeof(_dm) / sizeof(DMTYPE)];
} _udmbuf;

#endif
