#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnLoadResourceW(
	_In_ WORD resID

) {
	HRSRC hResFind = FindResource(NULL, MAKEINTRESOURCE(resID), RT_RCDATA);
	if (hResFind) {
		HGLOBAL hResLoad = LoadResource(NULL, hResFind);
		if (hResLoad) {
			LPVOID lpResLock = LockResource(hResLoad);
			DWORD dwResSize = SizeofResource(NULL, hResFind);
			if (lpResLock && dwResSize) {

			}
			else {
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Couldn't lock Resource or get size of Resource", NULL, L"LockResource/SizeOfResource", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
			}
		}
		else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't load Resource", NULL, L"LoadResource", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
		}
	}
	else {
#ifdef DEBUG_MSG
		fnErrorHandlerW(L"Couldn't find Resource\nResourceID: %d\nResourceTYPE: %s", NULL, L"FindResourceW", MB_OK | MB_ICONERROR, resID, RT_RCDATA);
#endif // DEBUG_MSG
	}

	return TRUE;
}