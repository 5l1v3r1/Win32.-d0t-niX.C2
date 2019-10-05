#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

#if DISABLE_SYNCHRONIZATION == FALSE
BOOL fnCheckMutexW(
	_In_ LPCWSTR lpName
) {
	if (OpenMutex(SYNCHRONIZE, FALSE, lpName)) {
		return TRUE;
	} else {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			fnERRORHANDLERW(L"Mutex doesn't exist", NULL, L"OpenMutexW", MB_ICONERROR);
			return FALSE;
		} else {
			fnERRORHANDLERW(L"Couldn't Open Mutex", NULL, L"OpenMutexW", MB_ICONERROR);
			return FALSE;
		}
	}
}

HANDLE fnCheckSemaphoreW(
	_In_ LPCWSTR lpName
) {
	HANDLE hSema = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, lpName);
	if (hSema) {
		return hSema;
	} else {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			fnERRORHANDLERW(L"Semaphore doesn't exist", NULL, L"OpenSemaphoreW", MB_ICONERROR);
			return NULL;
		} else {
			fnERRORHANDLERW(L"Couldn't Open Semaphore", NULL, L"OpenSemaphoreW", MB_ICONERROR);
			return NULL;
		}
	}
}
#endif // !DISABLE_SEMAPHORE