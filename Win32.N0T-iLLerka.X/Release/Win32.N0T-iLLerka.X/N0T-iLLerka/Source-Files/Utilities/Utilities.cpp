#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnIsUserAdmin(VOID) {
	SID_IDENTIFIER_AUTHORITY siaSNtA = SECURITY_NT_AUTHORITY;
	PSID psAg;
	BOOL bAais = AllocateAndInitializeSid(&siaSNtA, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &psAg);
	if (bAais) {
		if (!CheckTokenMembership(NULL, psAg, &bAais)) {
			bAais = FALSE;
		}
		FreeSid(psAg);
	}

	return bAais;
}

#ifdef DEBUG_MSG
/* This will be rewritten/improved again in order to make it
 *
 * Possible Changes:
 * - Improve FormatMessage:
 *	 - Cut out LANGID and replace it with something else because its deprecated
 *
 * - Cut out check for dwLe (due to it causing some issues if no error occurred previously)
 * - Add some check for the variables that got passed to the function in order to further format the ErrorMessage
 * - Some minor changes to be made that I won't go further into
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

	LPVOID lpMsgBuf;
	DWORD dwMsgBuf = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwLe, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPWSTR)& lpMsgBuf, 0, NULL);
	if (!dwMsgBuf) {
		MessageBox(NULL, L"Couldn't format Message\nPointer to MsgBuf is invalid", L"fnErrorHandlerW", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
		return;
	}

	LPVOID pszDest = (LPVOID)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, nMAX_HEAP_SIZE);
	if (pszDest) {
		size_t nHeap = HeapSize(hHeap, NULL, pszDest) / 2;
		if (nHeap != (SIZE_T)-1) {
			if (SUCCEEDED(StringCchVPrintf((LPWSTR)pszDest, nHeap, lpText, va_l))) {
				std::wstring szFormat = szFORMAT + ((std::wstring)((LPWSTR)pszDest));
				pszDest = (LPVOID)HeapReAlloc(hHeap, HEAP_ZERO_MEMORY, pszDest, (nFORMAT_LEN + lstrlen(lpFunction) + 10 + dwMsgBuf + lstrlen(szFormat.c_str())) * 2);
				if (pszDest) {
					nHeap = HeapSize(hHeap, NULL, pszDest) / 2;
					if (nHeap != (SIZE_T)-1) {
						if (SUCCEEDED(StringCchPrintf((LPWSTR)pszDest, nHeap, szFormat.c_str(), lpFunction, dwLe, (LPWSTR)lpMsgBuf))) {
							MessageBox(NULL, (LPCWSTR)pszDest, lpCaption, uType | MB_SYSTEMMODAL);
						} else {
							MessageBox(NULL, L"Couldn't format Error Message", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
						}
					} else {
						MessageBox(NULL, L"Couldn't get reallocated Heap size", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
					}
				} else {
					MessageBox(NULL, L"Couldn't reallocate Message Heap\nPointer to Message Heap is invalid", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
				}
			} else {
				MessageBox(NULL, L"Couldn't format Text Message", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
			}
		} else {
			MessageBox(NULL, L"Couldn't get allocated Heap size", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		}
	} else {
		MessageBox(NULL, L"Couldn't allocate Message Heap\nPointer to Message Heap is invalid", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}

	if (pszDest) { HeapFree(hHeap, NULL, pszDest); }
	if (lpMsgBuf) { HeapFree(hHeap, NULL, lpMsgBuf); }

	va_end(va_l);
}
#endif // DEBUG_MSG