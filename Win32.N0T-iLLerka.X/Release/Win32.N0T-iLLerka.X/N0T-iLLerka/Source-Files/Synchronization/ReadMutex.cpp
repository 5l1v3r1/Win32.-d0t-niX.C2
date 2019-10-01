#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

#ifndef DISABLE_MUTEX
BOOL fnCheckMutexW(
	_In_ LPCWSTR lpName
) {
	if (OpenMutex(SYNCHRONIZE, FALSE, lpName)) {
		return TRUE;
	} else {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Mutex doesn't exist", L"OpenMutexW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			return FALSE;
		} else {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't Open Mutex", L"OpenMutexW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			return FALSE;
		}
	}
}
#endif // !DISABLE_MUTEX