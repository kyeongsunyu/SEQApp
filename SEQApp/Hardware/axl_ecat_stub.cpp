// Stub implementations for AxlECat functions when EtherCAT is disabled
#include <Windows.h>
#include <cstring>

// Define AXL_ECAT_STUB in project preprocessor definitions when building
// in non-communication (no EtherCAT) mode to provide no-op implementations
// and satisfy the linker. Otherwise, link against the vendor AXL.lib/AXL.dll.
#ifdef AXL_ECAT_STUB

extern "C" DWORD __stdcall AxlECatReadPdoInput(DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData)
{
    // Clear destination buffer (bit length -> byte length)
    DWORD bytes = (dwDataBitLength + 7) / 8;
    if (pbyData && bytes) std::memset(pbyData, 0, bytes);
    return 0; // success / no data
}

extern "C" DWORD __stdcall AxlECatWritePdoOutput(DWORD dwBitOffset, DWORD dwDataBitLength, BYTE* pbyData)
{
    // No-op when EtherCAT communication is disabled
    (void)dwBitOffset; (void)dwDataBitLength; (void)pbyData;
    return 0; // success
}

#endif // AXL_ECAT_STUB
