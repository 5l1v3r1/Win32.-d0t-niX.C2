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
VOID fnMessageHandlerW(
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
		MessageBox(NULL, L"Couldn't get Handle to Process Heap", L"fnMessageHandlerW (GetProcessHeap)", MB_ICONERROR | MB_SYSTEMMODAL);
		return;
	}

	// Temporery
	// TODO: Improve this / embed it in the code
	LPVOID lpStringBuf = NULL;
	if (wTextID) {
		lpStringBuf = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, (0x3e8 * 2));
		if (lpStringBuf) {
			if (LoadString(GetModuleHandle(NULL), IDS_STRING101, (LPWSTR)lpStringBuf, 0x3e8)) {
				lpText = (LPCWSTR)lpStringBuf;
			} else {
				MessageBox(NULL, L"Couldn't load String", L"fnMessageHandlerW (LoadStringW)", MB_ICONERROR | MB_SYSTEMMODAL);
			}
		} else {
			MessageBox(NULL, L"Couldn't allocate String Heap", L"fnMessageHandlerW (HeapAlloc)", MB_ICONERROR | MB_SYSTEMMODAL);
			return;
		}
	}

	DWORD dwLE = GetLastError();
	LPVOID lpMsgBuf;
	DWORD dwMsgSize = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwLE, 0x409, (LPWSTR)&lpMsgBuf, 0, NULL);
	if (!dwMsgSize) {
		MessageBox(NULL, L"Couldn't format Message", L"fnMessageHandlerW (FormatMessageW)", MB_ICONINFORMATION | MB_SYSTEMMODAL);
		return;
	}

	SIZE_T cbHeapSize = ((lstrlen(lpFunction) + lstrlen(szFORMAT) + 0xa + dwMsgSize) * 2);
	LPVOID lpDest = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, cbHeapSize);
	if (lpDest) {
		if (SUCCEEDED(StringCbPrintf((LPWSTR)lpDest, cbHeapSize, szFORMAT, lpFunction, dwLE, (LPWSTR)lpMsgBuf))) {
			if (lpText) {
				std::wstring szFormat = (std::wstring)lpText + L"\n\nErrordetails:\n" + ((std::wstring)((LPWSTR)lpDest));
				cbHeapSize = ((lstrlen(szFormat.c_str()) * 2) + cbMAX_HEAP_SIZE);
				LPVOID lpDest_t = HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, lpDest, cbHeapSize);
				if (lpDest_t) {
					lpDest = lpDest_t;

					if (SUCCEEDED(StringCbVPrintf((LPWSTR)lpDest, cbHeapSize, szFormat.c_str(), va_l))) {
						MessageBox(NULL, (LPCWSTR)lpDest, lpCaption, uType);
					} else {
						MessageBox(NULL, L"Couldn't format Text Message", L"fnMessageHandlerW (StringCbVPrintf)", MB_ICONERROR | MB_SYSTEMMODAL);
					}
				} else {
					MessageBox(NULL, L"Couldn't reallocate Message Heap", L"fnMessageHandlerW (HeapReAlloc)", MB_ICONERROR | MB_SYSTEMMODAL);
				}
			} else {
				MessageBox(NULL, (LPCWSTR)lpDest, lpCaption, uType);
			}
		} else {
			MessageBox(NULL, L"Couldn't format Error Message", L"fnMessageHandlerW (StringcbPrintfW)", MB_ICONERROR | MB_SYSTEMMODAL);
		}
	} else {
		MessageBox(NULL, L"Couldn't allocate Message Heap", L"fnMessageHandlerW (HeapAlloc)", MB_ICONERROR | MB_SYSTEMMODAL);
	}

	if (lpDest) { HeapFree(hHeap, NULL, lpDest); }
	if (lpMsgBuf) { HeapFree(hHeap, NULL, lpMsgBuf); }
	if (wTextID) { if (lpStringBuf) { HeapFree(hHeap, NULL, lpStringBuf); } }

	SetLastError(ERROR_SUCCESS);
	va_end(va_l);
}
#endif // DEBUG_MSG