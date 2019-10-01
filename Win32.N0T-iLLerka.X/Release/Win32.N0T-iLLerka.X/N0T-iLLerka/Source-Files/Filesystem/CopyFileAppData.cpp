#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnCopyFileW(
	_In_ LPCWSTR lpAdpn,
	_In_ LPCWSTR lpAdfn,
	_In_ WCHAR szMfn[]
) {
	if (CreateDirectory(lpAdpn, NULL)) {
		if (CopyFile(szMfn, lpAdfn, FALSE)) {
			return TRUE;
		} else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't copy Binary to target Path\nFile: %s\nPath: %s", NULL, L"CopyFileW", MB_OK | MB_ICONERROR, szMfn, lpAdfn);
#endif // DEBUG_MSG
			return FALSE;
		}
	} else {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Directory already exist\nPath: %s", NULL, L"CreateDirectoryW", MB_OK | MB_ICONWARNING, lpAdpn);
#endif // DEBUG_MSG
			if (CopyFile(szMfn, lpAdfn, FALSE)) {
				return TRUE;
			} else {
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Couldn't copy Binary to target Path\nFile: %s\nPath: %s", NULL, L"CopyFileW", MB_OK | MB_ICONERROR, szMfn, lpAdfn);
#endif // DEBUG_MSG
				return FALSE;
			}
		} else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't create target Directory\nPath: %s", NULL, L"CreateDirectoryW", MB_OK | MB_ICONERROR, lpAdpn);
#endif // DEBUG_MSG
			return FALSE;
		}
	}

	return FALSE;
}