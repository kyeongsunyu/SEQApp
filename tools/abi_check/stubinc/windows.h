#pragma once
/*
 * Minimal stand-in for <windows.h>, used only by the ABI probe in this folder.
 * The widths below are MSVC's: note that `long` stays 32-bit on x64 as well
 * (Windows uses LLP64), which is why run.sh rewrites `long` to `int` in the
 * extracted copies of the real headers before feeding them to clang on Linux.
 */
typedef unsigned char  BYTE, UCHAR, *PUCHAR;
typedef unsigned short WORD, USHORT;
typedef unsigned int   DWORD, ULONG, UINT;
typedef int            LONG, INT, BOOL;
typedef void          *PVOID, *LPVOID, *HANDLE;
typedef char          *LPSTR;
typedef const char    *LPCSTR;
typedef wchar_t       *LPWSTR;
typedef const wchar_t *LPCWSTR;
#define __stdcall
#define WINAPI
