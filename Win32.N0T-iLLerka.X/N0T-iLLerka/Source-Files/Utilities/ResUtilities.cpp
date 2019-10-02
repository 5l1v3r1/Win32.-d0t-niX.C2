#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnExtractResourceW(
	_In_ LPCWSTR lpResID,
	_In_ LPCWSTR lpResType,
	_In_ LPCWSTR lpFileName
) {
	LPVOID lpBuffer = NULL;
	DWORD dwBuffersize = NULL;

	return FALSE;
}

LPVOID fnLoadResourceW(
	_In_ WORD resID,
	_Out_ LPDWORD dwBufferSize
) {
	*dwBufferSize = 0;

	HRSRC hResFind = FindResource(NULL, MAKEINTRESOURCE(resID), RT_RCDATA);
	if (hResFind) {
		HGLOBAL hResLoad = LoadResource(NULL, hResFind);
		if (hResLoad) {
			LPVOID lpBuffer = LockResource(hResLoad);
			if (!lpBuffer) {
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Couldn't lock Resource", NULL, L"LockResource", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
				return NULL;
			}

			*dwBufferSize = SizeofResource(NULL, hResFind);
			if (!*dwBufferSize) {
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Couldn't get size of Resource", NULL, L"SizeOfResource", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
				return NULL;
			}

			return lpBuffer;
		} else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't load Resource", NULL, L"LoadResource", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
		}
	} else {
#ifdef DEBUG_MSG
		fnErrorHandlerW(L"Couldn't find Resource\nResourceID: %d\nResourceTYPE: %s", NULL, L"FindResourceW", MB_OK | MB_ICONERROR, resID, RT_RCDATA);
#endif // DEBUG_MSG
	}

	return NULL;
}

BOOL fnSaveResourceW(
	_In_ LPCWSTR lpName,
	_In_ LPVOID lpBuffer,
	_In_ DWORD dwBufferSize
) {
	HANDLE hFile = CreateFile(lpName, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	if (hFile) {
		DWORD dwNOBW;
		if (WriteFile(hFile, lpBuffer, dwBufferSize, &dwNOBW, NULL)) {
			CloseHandle(hFile);
			return TRUE;
		} else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"", NULL, L"", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
			CloseHandle(hFile);
			return FALSE;
		}
	} else {
#ifdef DEBUG_MSG
		fnErrorHandlerW(L"", NULL, L"", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}
}