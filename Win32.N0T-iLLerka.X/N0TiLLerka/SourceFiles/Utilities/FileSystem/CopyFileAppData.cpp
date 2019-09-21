#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL fnCopyFileW(LPCWSTR lpAdpn, LPCWSTR lpAdfn, WCHAR szMfn[]) {
	if (CreateDirectory(lpAdpn, NULL)) {
		if (CopyFile(szMfn, lpAdfn, FALSE)) {
			return TRUE;
		} else {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't copy Binary to target Path", L"CopyFileW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			return FALSE;
		}
	} else {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Directory already exist", L"CreateDirectoryW", MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif // DEBUG_MSG
			if (CopyFile(szMfn, lpAdfn, FALSE)) {
				return TRUE;
			} else {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Couldn't copy Binary to target Path", L"CopyFileW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
				return FALSE;
			}
		} else {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't create target Directory", L"CreateDirectoryW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			return FALSE;
		}
	}

	return FALSE;
}