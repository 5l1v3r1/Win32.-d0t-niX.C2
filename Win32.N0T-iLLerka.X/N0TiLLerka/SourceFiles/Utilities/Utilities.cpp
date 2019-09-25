#include "../../HeaderFiles/N0TiLLerka.h"

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
VOID fnErrorHandlerW(LPCWSTR lpText, LPCWSTR lpCaption, LPCWSTR lpFunction, UINT uType, ...) {
	va_list va_l;
	if (lpText) { va_start(va_l, uType); }

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
	DWORD dwMsgBuf = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwLe, 0, (LPWSTR)& lpMsgBuf, 0, NULL);
	if (!dwMsgBuf) {
		MessageBox(NULL, L"Couldn't format Message\nPointer to MsgBuf is invalid", L"fnErrorHandlerW", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
		return;
	}

	LPVOID pszDest = (LPVOID)HeapAlloc(hHeap, HEAP_ZERO_MEMORY,
		(lstrlen((LPCWSTR)lpText) + lstrlen((LPCWSTR)lpFunction) + dwMsgBuf + 42) * sizeof(WCHAR));
	if (pszDest) {
		size_t nHsize = HeapSize(hHeap, NULL, pszDest) / sizeof(WCHAR);
		if (nHsize != (SIZE_T)-1) {
			std::wstring szFormat = L"%s failed with Errorcode:\n%u : %s\n\nNote:\n" + (std::wstring)lpText;
			if (SUCCEEDED(StringCchPrintf((LPWSTR)pszDest, nHsize, szFormat.c_str(), lpFunction, dwLe, (LPWSTR)lpMsgBuf, &va_l))) {
				MessageBox(NULL, (LPCWSTR)pszDest, lpCaption, uType | MB_SYSTEMMODAL);
			} else {
				MessageBox(NULL, L"Couldn't format Error Message", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
			}
		} else {
			MessageBox(NULL, L"Couldn't get Heap size", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		}
	} else {
		MessageBox(NULL, L"Couldn't allocate Message Heap\nPointer to Message Heap is invalid", L"fnErrorHandlerW", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}

	if (pszDest) { HeapFree(hHeap, NULL, pszDest); }
	if (lpMsgBuf) { HeapFree(hHeap, NULL, lpMsgBuf); }

	if (lpText) { va_end(va_l); }
}
#endif // DEBUG_MSG