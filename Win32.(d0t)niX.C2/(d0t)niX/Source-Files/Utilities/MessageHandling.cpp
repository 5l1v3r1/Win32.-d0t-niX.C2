/*-----------------------------------------------------+------------------------------\
 |    ___    __________   __  ___          ______  ___ | ___________        ___ ___   |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | \_   _____/ _____ /   |   \  |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  |  |    __)_ /     \    ~    \ |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  |  |        \  Y Y  \   Y    / |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ | /_______  /__|_|  /___|_  /  |
 |   \__\    \/        \/     /__/      \/         \_/ |         \/      \/      \/   |
 +-----------------------------------------------------+--------------+---------------/
 | MessageHandling.cpp :: (d0t)niX's Error/Message Handling Functions |
 \--------------------------------------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

#if DEBUG_MSG == TRUE
	// TODO: improve/modify this again
VOID fnMessageHandlerExW(
	_In_opt_ LPCWSTR lpCaption,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ WORD    wTextID,
	_In_opt_ LPCWSTR lpFunction,
	_In_opt_ UINT    uType,
	_In_opt_         ...
) {
	va_list va_l;
	va_start(va_l, uType);

	if (!lpCaption) { lpCaption = szMALWR_NAME; }
	if (!uType) { uType = MB_ICONWARNING; }

#if DEBUG_MSG_FORCE_MODAL == TRUE
	uType |= MB_SYSTEMMODAL;
#endif // DEBUG_MSG_FORCE_MODAL

	HANDLE hHeap = GetProcessHeap();
	if (!hHeap) {
		MessageBoxW(NULL, L"Couldn't get Handle to Process Heap", L"fnMessageHandlerW (GetProcessHeap)", MB_ICONERROR | MB_SYSTEMMODAL);
		return;
	}

	// Temporery
	// TODO: Improve this / embed it in the code
	LPVOID lpStringBuf = NULL;
	if (wTextID) {
		lpStringBuf = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, (0x3e8 * sizeof(WCHAR)));
		if (lpStringBuf) {
			if (LoadStringW(GetModuleHandleW(NULL), IDS_STRING101, (LPWSTR)lpStringBuf, 0x3e8)) {
				lpText = (LPCWSTR)lpStringBuf;
			} else {
				MessageBoxW(NULL, L"Couldn't load String", L"fnMessageHandlerW (LoadStringW)", MB_ICONERROR | MB_SYSTEMMODAL);
			}
		} else {
			MessageBoxW(NULL, L"Couldn't allocate String Heap", L"fnMessageHandlerW (HeapAlloc)", MB_ICONERROR | MB_SYSTEMMODAL);
			return;
		}
	}

	DWORD dwLE = GetLastError();
	LPVOID lpMsgBuf;
	DWORD dwMsgSize = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwLE, 0x409, (LPWSTR)&lpMsgBuf, 0, NULL);
	if (!dwMsgSize) {
		MessageBoxW(NULL, L"Couldn't format Message", L"fnMessageHandlerW (FormatMessageW)", MB_ICONINFORMATION | MB_SYSTEMMODAL);
		return;
	}

	SIZE_T cbHeapSize = ((lstrlenW(lpFunction) + lstrlenW(szFORMAT) + 0xa + dwMsgSize) * sizeof(WCHAR));
	LPVOID lpDest = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbHeapSize);
	if (lpDest) {
		if (SUCCEEDED(StringCbPrintfW((LPWSTR)lpDest, cbHeapSize, szFORMAT, lpFunction, dwLE, (LPWSTR)lpMsgBuf))) {
			if (lpText) {
				std::wstring szFormat = (std::wstring)lpText + L"\n\nErrordetails:\n" + ((std::wstring)((LPWSTR)lpDest));
				cbHeapSize = ((lstrlenW(szFormat.c_str()) * sizeof(WCHAR)) + cbMAX_HEAP_SIZE);
				LPVOID lpDest_t = HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, lpDest, cbHeapSize);
				if (lpDest_t) {
					lpDest = lpDest_t;

					if (SUCCEEDED(StringCbVPrintfW((LPWSTR)lpDest, cbHeapSize, szFormat.c_str(), va_l))) {
						MessageBoxW(NULL, (LPCWSTR)lpDest, lpCaption, uType);
					} else {
						MessageBoxW(NULL, L"Couldn't format Text Message", L"fnMessageHandlerW (StringCbVPrintf)", MB_ICONERROR | MB_SYSTEMMODAL);
					}
				} else {
					MessageBoxW(NULL, L"Couldn't reallocate Message Heap", L"fnMessageHandlerW (HeapReAlloc)", MB_ICONERROR | MB_SYSTEMMODAL);
				}
			} else {
				MessageBoxW(NULL, (LPCWSTR)lpDest, lpCaption, uType);
			}
		} else {
			MessageBoxW(NULL, L"Couldn't format Error Message", L"fnMessageHandlerW (StringcbPrintfW)", MB_ICONERROR | MB_SYSTEMMODAL);
		}
	} else {
		MessageBoxW(NULL, L"Couldn't allocate Message Heap", L"fnMessageHandlerW (HeapAlloc)", MB_ICONERROR | MB_SYSTEMMODAL);
	}

	if (lpDest) { HeapFree(hHeap, NULL, lpDest); }
	if (lpMsgBuf) { HeapFree(hHeap, NULL, lpMsgBuf); }
	if (wTextID) { if (lpStringBuf) { HeapFree(hHeap, NULL, lpStringBuf); } }

	SetLastError(ERROR_SUCCESS);
	va_end(va_l);
}
#endif // DEBUG_MSG