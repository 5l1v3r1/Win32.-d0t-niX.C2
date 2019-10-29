/*-----------------------------------------------------+-----------------------------\
 |    ___    __________   __  ___          ______  ___ | __________      _________   |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | \______   \____ \_   ___ \  |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  |  |     ___/  _ \/    \  \/  |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  |  |    |  (  <_> )     \____ |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ |  |____|   \____/ \______  / |
 |   \__\    \/        \/     /__/      \/         \_/ |                         \/  |
 +-----------------------------------------------------+------------------------+----/
 | ProcessPesistence.cpp :: (d0t)niX's Process Persistency/Protection Functions |
 \------------------------------------------------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

// (this will be used to look for processes in a list (passed by an array) and kill them (or something else) if they exist)
BOOL fnProcessMonitorW(
	_In_ LPCWSTR lpProcs[],
	_In_ SIZE_T  ulProcSize
) {
	while (TRUE) {
		HANDLE hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (hProcSnap) {
			PROCESSENTRY32W pe32;
			pe32.dwSize = sizeof(pe32);

			if (Process32FirstW(hProcSnap, &pe32)) {
				do {
					for (INT i = 0; i < ulProcSize; i++) {
						if (!lstrcmpW(pe32.szExeFile, lpProcs[i])) {
							HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
							if (hProc) {
								if (!TerminateProcess(hProc, EXIT_FAILURE)) {
									fnMessageHandlerW(NULL, L"Couldn't terminate Process\n ProcessID: %d", L"TerminateProcess",
										MB_ICONWARNING, pe32.th32ProcessID);
								}

								CloseHandle(hProc);
							}
						}
					}
				} while (Process32NextW(hProcSnap, &pe32));
			}

			CloseHandle(hProcSnap);
		}
	}

	return FALSE;
}

// Placeholder (ripped from msdn, will be modified)
BOOL GetProcessList() {
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		// printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
		return(FALSE);
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32)) {
		// printError(TEXT("Process32First")); // show cause of failure
		CloseHandle(hProcessSnap);          // clean the snapshot object
		return(FALSE);
	}

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do {
		// _tprintf(TEXT("\n\n====================================================="));
		// _tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
		// _tprintf(TEXT("\n-------------------------------------------------------"));

		// Retrieve the priority class.
		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if (hProcess == NULL) {
			// printError(TEXT("OpenProcess"));
		} else {
			dwPriorityClass = GetPriorityClass(hProcess);
			if (!dwPriorityClass) {
				// printError(TEXT("GetPriorityClass"));
			}
			CloseHandle(hProcess);
		}

		// _tprintf(TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID);
		// _tprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads);
		// _tprintf(TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID);
		// _tprintf(TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase);
		if (dwPriorityClass) {
			// _tprintf(TEXT("\n  Priority class    = %d"), dwPriorityClass);
		}

		// List the modules and threads associated with this process
		// ListProcessModules(pe32.th32ProcessID);
		// ListProcessThreads(pe32.th32ProcessID);

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return(TRUE);
}

// Placeholder (ripped from msdn, will be modified)
BOOL ListProcessModules(DWORD dwPID) {
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	// Take a snapshot of all modules in the specified process.
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE) {
		//printError(TEXT("CreateToolhelp32Snapshot (of modules)"));
		return(FALSE);
	}

	// Set the size of the structure before using it.
	me32.dwSize = sizeof(MODULEENTRY32);

	// Retrieve information about the first module,
	// and exit if unsuccessful
	if (!Module32First(hModuleSnap, &me32)) {
		//printError(TEXT("Module32First"));  // show cause of failure
		CloseHandle(hModuleSnap);           // clean the snapshot object
		return(FALSE);
	}

	// Now walk the module list of the process,
	// and display information about each module
	do {
		//_tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
		//_tprintf(TEXT("\n     Executable     = %s"), me32.szExePath);
		//_tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID);
		//_tprintf(TEXT("\n     Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
		//_tprintf(TEXT("\n     Ref count (p)  = 0x%04X"), me32.ProccntUsage);
		//_tprintf(TEXT("\n     Base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
		//_tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize);

	} while (Module32Next(hModuleSnap, &me32));

	CloseHandle(hModuleSnap);
	return(TRUE);
}