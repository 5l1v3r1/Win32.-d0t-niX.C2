#include "../../../HeaderFiles/N0TiLLerka.h"


bool CheckMutexW(LPCWSTR lpName) {
	if (!OpenMutex(SYNCHRONIZE, NULL, lpName)) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
#ifdef DEBUG
			MessageBox(NULL, L"Mutex doesn't exist", L"OpenMutexW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			return FALSE;
		} else {
#ifdef DEBUG
			MessageBox(NULL, L"Couldn't Open Mutex", L"OpenMutexW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			return FALSE;
		}
	} else {
		return TRUE;
	}

	return FALSE;
}