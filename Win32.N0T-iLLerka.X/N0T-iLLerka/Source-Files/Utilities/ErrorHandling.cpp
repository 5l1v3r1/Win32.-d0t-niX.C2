#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

#ifdef DEBUG_MSG
/* This will be rewritten/improved again in order to make it more modular and safer.
 *
 * Possible Changes:
 * - Improve FormatMessage:
 *	 - Cut out LANGID and replace it with something else because its deprecated (might not happen)
 *
 * - Cut out check for dwLe (due to it causing some issues if no error occurred previously)
 * - Add some check for the variables that got passed to the function in order to further format the ErrorMessage
 * - Some minor changes to be made that I won't go further into
 *
 * - I've noticed a bad mistake relating with the size of the heap, this bug could cause the function to still continue
 *   even if HeapSize fails and write to possibly unallocated memory
 * - Also found a problem that might cause a memory leak
 */
VOID fnErrorHandlerW(
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpCaption,
	_In_opt_ LPCWSTR lpFunction,
	_In_ UINT uType,
	_In_opt_ ...
) {
	va_list va_l;
	va_start(va_l, uType);
	if (!lpCaption) { lpCaption = szMALWR_NAME; }

	DWORD dwLe = GetLastError();
	if (!dwLe) {
		MessageBox(NULL, L"No Error occurred\nThis function was called wrongfully", L"fnErrorHandlerW", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
		return;
	}
	HANDLE hHeap = GetProcessHeap();
	if (!hHeap) {
		MessageBox(NULL, L"Handle to Process Heap is invalid", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return;
	}

	LPVOID lpMsgBuf = nullptr;
	DWORD dwMsgBuf = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwLe, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPWSTR)&lpMsgBuf, 0, NULL);
	if (!dwMsgBuf) {
		MessageBox(NULL, L"Couldn't format Message\nPointer to MsgBuf is invalid", L"fnErrorHandlerW", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
		return;
	}

	LPVOID pszDest = nullptr;
	LPVOID pszReDest = nullptr;
	pszDest = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, nMAX_HEAP_SIZE);
	if (pszDest) {
		size_t nHeap = HeapSize(hHeap, NULL, pszDest) / 2;
		if (nHeap != (SIZE_T)-1) {
			if (SUCCEEDED(StringCchVPrintf((LPWSTR)pszDest, nHeap, lpText, va_l))) {
				std::wstring szFormat = szFORMAT + ((std::wstring)((LPWSTR)pszDest));
				pszReDest = HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, pszDest, (nFORMAT_LEN + lstrlen(lpFunction) + 10 + dwMsgBuf + lstrlen(szFormat.c_str())) * 2);
				if (pszReDest) {
					nHeap = HeapSize(hHeap, NULL, pszReDest) / 2;
					if (nHeap != (SIZE_T)-1) {
						if (SUCCEEDED(StringCchPrintf((LPWSTR)pszReDest, nHeap, szFormat.c_str(), lpFunction, dwLe, (LPWSTR)lpMsgBuf))) {
							MessageBox(NULL, (LPCWSTR)pszReDest, lpCaption, uType | MB_SYSTEMMODAL);
						}
						else {
							MessageBox(NULL, L"Couldn't format Error Message", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
						}
					}
					else {
						MessageBox(NULL, L"Couldn't get reallocated Heap size", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
					}
				}
				else {
					MessageBox(NULL, L"Couldn't reallocate Message Heap\nPointer to Message Heap is invalid", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
				}
			}
			else {
				MessageBox(NULL, L"Couldn't format Text Message", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
			}
		}
		else {
			MessageBox(NULL, L"Couldn't get allocated Heap size", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		}
	}
	else {
		MessageBox(NULL, L"Couldn't allocate Message Heap\nPointer to Message Heap is invalid", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}

	if (pszDest) { HeapFree(hHeap, NULL, pszDest); }
	if (pszReDest) { HeapFree(hHeap, NULL, pszReDest); }
	if (lpMsgBuf) { HeapFree(hHeap, NULL, lpMsgBuf); }

	va_end(va_l);
}
#endif // DEBUG_MSG