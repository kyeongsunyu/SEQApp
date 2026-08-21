// ABI probe: instantiates every struct that crosses a process boundary so that
// clang can dump its record layout. See run.sh / README.md in this folder.
#include <windows.h>

#include "gen/wire_shm.h"     // TMemCommand & friends  (shared memory, SharedMemBase.h)
#include "DEFINE_Bit.h"       // BITTYPE, needed by NVMMF.h
#include "gen/wire_nvmmf.h"   // _MMF                   (memory-mapped file, NVMMF.h)
#include "DEFINE_WinMsg.h"    // WM_COPYDATA payloads
#include "DEFINE_Data.h"      // vision protocol + device/machine data

// --- shared memory -------------------------------------------------------
TMemCommand    p_TMemCommand;
_arg           p_arg;
_iobit         p_iobit;
_datamemory    p_datamemory;
_mtmove        p_mtmove;
_mtstatus      p_mtstatus;
_mtdata        p_mtdata;
_mtcfg         p_mtcfg;
_device        p_device;
_manual        p_manual;
_tenkeyjog     p_tenkeyjog;
_lifetime      p_lifetime;
_lampbuzzer    p_lampbuzzer;
_errorcode     p_errorcode;
_machinestatus p_machinestatus;
_userinfo      p_userinfo;
_lotinfo       p_lotinfo;

// --- memory-mapped file --------------------------------------------------
_MMF           p_MMF;

// --- WM_COPYDATA payloads ------------------------------------------------
SEQ_RSP          p_SEQ_RSP;
SEQ_LOG          p_SEQ_LOG;
USER_INFO        p_USER_INFO;
DEVICE_INFO      p_DEVICE_INFO;
SEQ_LOT_INFO_REQ p_SEQ_LOT_INFO_REQ;

// --- vision TCP protocol -------------------------------------------------
VISION_HEADER        p_VISION_HEADER;
VISION_PROTOCOL_DATA p_VISION_PROTOCOL_DATA;
VISION_TX_DATA       p_VISION_TX_DATA;
VISION_RX_DATA       p_VISION_RX_DATA;

// --- device / machine data ----------------------------------------------
TDeviceData    p_TDeviceData;
TMachineStatus p_TMachineStatus;
TUSER_INFO     p_TUSER_INFO;
TLOT_INFO      p_TLOT_INFO;
TDeviceInfo    p_TDeviceInfo;
