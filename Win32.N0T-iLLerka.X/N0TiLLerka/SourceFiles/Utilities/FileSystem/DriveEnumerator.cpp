#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL DriveEnumeratorW(std::vector<std::wstring>& vwsDrive) {
	WCHAR szDrives[MAX_PATH] = { L'\0' };

	if (GetLogicalDriveStrings(MAX_PATH, szDrives)) {
		for (INT i = 0; i <= 100; i += 4) {
			if (szDrives[i] != L'\0') {
				UINT uDt = GetDriveType(std::wstring{ szDrives[i], szDrives[i + 1], szDrives[i + 2] }.c_str());
				if (uDt != DRIVE_UNKNOWN && uDt != DRIVE_NO_ROOT_DIR && uDt != DRIVE_CDROM) {
					vwsDrive.push_back(std::wstring{ szDrives[i], szDrives[i + 1], szDrives[i + 2] });
				}
			}
		}
	} else {
#ifdef DEBUG
		MessageBox(NULL, L"Couldn't Enumerate Drives", L"GetLogicalDriveStringsW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
		return FALSE;
	}

	return TRUE;
}