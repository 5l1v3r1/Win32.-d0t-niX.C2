#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnLoadResourceW(
	_In_ WORD resID,
	_Out_ LPVOID lpBuffer,
	_Out_ PDWORD dwBufferSize
) {
	lpBuffer = NULL;
	dwBufferSize = NULL;

	HRSRC hResFind = FindResource(NULL, MAKEINTRESOURCE(resID), RT_RCDATA);
	if (hResFind) {
		HGLOBAL hResLoad = LoadResource(NULL, hResFind);
		if (hResLoad) {
			LPVOID lpResLock = LockResource(hResLoad);
			if (!lpResLock) {
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Couldn't lock Resource", NULL, L"LockResource", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
				return FALSE;
			}

			DWORD dwResSize = SizeofResource(NULL, hResFind);
			if (!dwResSize) {
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Couldn't get size of Resource", NULL, L"SizeOfResource", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
				return FALSE;
			}

			lpBuffer = lpResLock;
			dwBufferSize = &dwResSize;
			return TRUE;
		} else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't load Resource", NULL, L"LoadResource", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
			return FALSE;
		}
	} else {
#ifdef DEBUG_MSG
		fnErrorHandlerW(L"Couldn't find Resource\nResourceID: %d\nResourceTYPE: %s", NULL, L"FindResourceW", MB_OK | MB_ICONERROR, resID, RT_RCDATA);
#endif // DEBUG_MSG
		return FALSE;
	}
}

BOOL fnSaveResource(
	_In_ LPCWSTR lpName,
	_In_ LPVOID lpBuffer,
	_In_ DWORD dwBufferSize
) {


	return FALSE;
}