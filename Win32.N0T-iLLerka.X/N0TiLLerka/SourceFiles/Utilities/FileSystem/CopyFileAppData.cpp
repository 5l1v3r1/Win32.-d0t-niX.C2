#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL CopyFileAppDataW(LPCWSTR lpAdpn, LPCWSTR lpAdfn, WCHAR mfn[]) {
	if (CreateDirectory(lpAdpn, NULL)) {
		if (CopyFile(mfn, lpAdfn, FALSE)) {
			return TRUE;
		} else {
#ifdef DEBUG
			MessageBox(NULL, L"Couldn't copy Binary to target Path", L"CopyFileW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			return FALSE;
		}
	} else {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
#ifdef DEBUG
			MessageBox(NULL, L"Directory already exist", L"CreateDirectoryW", MB_OK | MB_SYSTEMMODAL | MB_ICONINFORMATION);
#endif
			if (CopyFile(mfn, lpAdfn, FALSE)) {
				return TRUE;
			} else {
#ifdef DEBUG
				MessageBox(NULL, L"Couldn't copy Binary to target Path", L"CopyFileW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
				return FALSE;
			}
		} else {
#ifdef DEBUG
			MessageBox(NULL, L"Couldn't create target Directory", L"CreateDirectoryW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			return FALSE;
		}
	}

	return FALSE;
}