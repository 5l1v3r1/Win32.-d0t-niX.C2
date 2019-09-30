#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnDirectoryIteratorW(
	_In_ std::wstring szDir,
	_In_ std::wstring szMask,
	_Inout_ std::vector<std::wstring>& vszDir,
	_Inout_ std::vector<std::wstring>& vszFile
) {
	WIN32_FIND_DATA w32Fd;
	std::wstring szW32fd = szDir + L"\\" + szMask;

	HANDLE hFind = FindFirstFile(szW32fd.c_str(), &w32Fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (w32Fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (wcscmp(w32Fd.cFileName, L".") != 0 && wcscmp(w32Fd.cFileName, L"..") != 0) {
					vszDir.push_back(szDir + L"\\" + w32Fd.cFileName);
				}
			} else {
				vszFile.push_back(szDir + L"\\" + w32Fd.cFileName);
			}
		} while (FindNextFile(hFind, &w32Fd));

		FindClose(hFind);
		return TRUE;
	} else {
#ifdef DEBUG_MSG
		fnErrorHandlerW(L"Couldn't open Handle \"hFind\" to FirstFile", NULL, L"FindFirstFileW", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}
}