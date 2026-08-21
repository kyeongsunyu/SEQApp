#include "..\pch.h"
#include "CLASS_TenKey.h"
#include "..\SeqMain\DEFINE_GV.h"

//////////////////////////////////////////////////////////////////////////
BOOL CTenKey::ReadKey(WORD inval)
{
    wCurKeyVal = inval;
    if (bKeyRescan) {
        if (wCurKeyVal) {
            if (wPrevKeyVal == wCurKeyVal) {
                if (t.TimeOvermS(20)) {
                    bKeyOn = TRUE;
                    bKeyPressed = TRUE;
                    bKeyRescan = FALSE;
                    wKeyVal = wCurKeyVal;
                }
            }
            else {
                wPrevKeyVal = wCurKeyVal;
                t.SetTime();
            }
        }
        else {
            bKeyRescan = FALSE;
            wPrevKeyVal = 0;
        }
    }
    else {
        if (wCurKeyVal != wPrevKeyVal) {
            if (t.TimeOvermS(20)) {
                bKeyOn = FALSE;
                bKeyRescan = TRUE;
                bKeyPressed = FALSE;
            }
        }
        else {
            bKeyRescan = FALSE;
            t.SetTime();
        }
    }
    return opProcessKey.Run(bKeyPressed);
}

int CTenKey::MakeKeyCode(void)
{
    int row, col;

    if ((wKeyVal & 0x000f) && (wKeyVal & 0x0070)) {
        // 10 key
        switch (wKeyVal & 0x000f) {
        case 0x0001: row = 1; break;
        case 0x0002: row = 2; break;
        case 0x0004: row = 3; break;
        case 0x0008: row = 4; break;
        default:     row = 0;
        }
        switch (wKeyVal & 0x0070) {
        case 0x0010: col = 1; break;
        case 0x0020: col = 2; break;
        case 0x0040: col = 3; break;
        default:     col = 0;
        }

        if (row && col) {
            switch (row) {
            case 1:
            case 2:
            case 3:
                wKeyCode = (row - 1) * 3 + col + 0x0010;
                break;
            case 4:
                switch (col) {
                case 1:
                    wKeyCode = 0x001a;
                    break;
                case 2:
                    wKeyCode = 0x0010;
                    break;
                case 3:
                    wKeyCode = 0x001b;
                    break;
                } // end of col
                break;
            default:
                return 0;
            } // end of row
            return wKeyCode;
        }
        else {
            return 0;
        }
    }

    if (AINON(iKeyStart))		bit.KeyStartPressed = 1;//KC_START;
    else if (AINON(iKeyStop))	wKeyCode = KC_STOP;
    else if (AINON(iKeyReset))	wKeyCode = KC_RST;
//    else if (AINON(iKeyDry))		wKeyCode = KC_DRY;

    else 						wKeyCode = 0;
    return	wKeyCode;
}

