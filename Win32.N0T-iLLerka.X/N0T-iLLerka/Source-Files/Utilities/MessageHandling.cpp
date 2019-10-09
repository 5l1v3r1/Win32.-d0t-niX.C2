#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

#if DEBUG_MSG == TRUE
	// TODO: improve/modify this again
	VOID fnMessageHandlerW(
		_In_opt_ LPCWSTR lpCaption,
		_In_opt_ LPCWSTR lpText,
		_In_opt_ LPCWSTR lpFunction,
		_In_opt_ UINT    uType,
		_In_opt_         ...
	) {
		va_list va_l;
		va_start(va_l, uType);

		if (!lpCaption) { lpCaption = szMALWR_NAME; }
		if (!uType) { uType = MB_ICONWARNING; }

		HANDLE hHeap = GetProcessHeap();
		if (!hHeap) {
			MessageBox(NULL, L"Couldn't get Handle to Process Heap", L"fnMessageHandlerW (GetProcessHeap)", MB_ICONERROR | MB_SYSTEMMODAL);
			return;
		}

		DWORD dwLe = GetLastError();
		LPVOID lpMsgBuf;
		DWORD dwMsgSize = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, dwLe, 0x409, (LPWSTR)&lpMsgBuf, 0, NULL);
		if (!dwMsgSize) {
			MessageBox(NULL, L"Couldn't format Message", L"fnMessageHandlerW (FormatMessageW)", MB_ICONINFORMATION | MB_SYSTEMMODAL);
			return;
		}

		LPVOID lpDest = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, ((lstrlen(lpFunction) + nFORMAT_LEN + 0xa + dwMsgSize) * 2));
		if (lpDest) {
			SIZE_T nHeap = HeapSize(hHeap, NULL, lpDest);
			if (nHeap != (SIZE_T)-1) {
				if (SUCCEEDED(StringCbPrintf((LPWSTR)lpDest, nHeap, szFORMAT, lpFunction, dwLe, (LPWSTR)lpMsgBuf))) {
					if (lpText) {
						std::wstring szFormat = (std::wstring)lpText + L"\n\nErrordetails:\n" + ((std::wstring)((LPWSTR)lpDest));
						LPVOID lpDest_t = HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, lpDest, ((lstrlen(szFormat.c_str()) * 2) + cbMAX_HEAP_SIZE));
						if (lpDest_t) {
							lpDest = lpDest_t;

							SIZE_T nHeap = HeapSize(hHeap, NULL, lpDest);
							if (nHeap != (SIZE_T)-1) {
								if (SUCCEEDED(StringCbVPrintf((LPWSTR)lpDest, nHeap, szFormat.c_str(), va_l))) {
	#if DEBUG_MSG_FORCE_MODAL == TRUE
									MessageBox(NULL, (LPCWSTR)lpDest, lpCaption, uType | MB_SYSTEMMODAL);
	#else // DEBUG_MSG_FORCE_MODAL
									MessageBox(NULL, (LPCWSTR)lpDest, lpCaption, uType);
	#endif // !DEBUG_MSG_FORCE_MODAL
								} else {
									MessageBox(NULL, L"Couldn't format Text Message", L"fnMessageHandlerW", MB_ICONERROR | MB_SYSTEMMODAL);
								}
							} else {
								MessageBox(NULL, L"Couldn't get reallocated Heap size", L"fnMessageHandlerW", MB_ICONERROR | MB_SYSTEMMODAL);
							}
						} else {
							MessageBox(NULL, L"Couldn't reallocate Message Heap\nPointer to Message Heap is invalid", L"fnMessageHandlerW",
								MB_ICONERROR | MB_SYSTEMMODAL);
						}
					} else {
	#if DEBUG_MSG_FORCE_MODAL == TRUE
						MessageBox(NULL, (LPCWSTR)lpDest, lpCaption, uType | MB_SYSTEMMODAL);
	#else // DEBUG_MSG_FORCE_MODAL
						MessageBox(NULL, (LPCWSTR)lpDest, lpCaption, uType);
	#endif // !DEBUG_MSG_FORCE_MODAL
					}
				} else {
					MessageBox(NULL, L"Couldn't format Error Message", L"fnMessageHandlerW", MB_ICONERROR | MB_SYSTEMMODAL);
				}
			} else {
				MessageBox(NULL, L"Couldn't get reallocated Heap size", L"fnMessageHandlerW", MB_ICONERROR | MB_SYSTEMMODAL);
			}
		} else {
			MessageBox(NULL, L"Couldn't allocate Message Heap\nPointer to Message Heap is invalid", L"fnMessageHandlerW", MB_ICONERROR | MB_SYSTEMMODAL);
		}

		if (lpDest) { HeapFree(hHeap, NULL, lpDest); }
		if (lpMsgBuf) { HeapFree(hHeap, NULL, lpMsgBuf); }

		SetLastError(ERROR_SUCCESS);
		va_end(va_l);
	}
#endif // DEBUG_MSG