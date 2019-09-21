#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL fnDriveEnumeratorW(std::vector<std::wstring>& vszDrive) {
	WCHAR szDrives[105] = { L'\0' };

	if (GetLogicalDriveStrings(104, szDrives)) {
		for (INT i = 0; i < 104; i += 4) {
			if (szDrives[i] != L'\0') {
				UINT uDt = GetDriveType(std::wstring{ szDrives[i], szDrives[i + 1], szDrives[i + 2] }.c_str());
				if (uDt != DRIVE_UNKNOWN && uDt != DRIVE_NO_ROOT_DIR && uDt != DRIVE_CDROM) {
					vszDrive.push_back(std::wstring{ szDrives[i], szDrives[i + 1], szDrives[i + 2] });
				}
			}
		}
		
		return TRUE;
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't Enumerate Drives", L"GetLogicalDriveStringsW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}
}