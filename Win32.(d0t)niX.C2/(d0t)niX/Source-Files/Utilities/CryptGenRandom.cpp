/*-----------------------------------------------------+-----------------------------\
 |    ___    __________   __  ___          ______  ___ | _________       __________  |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | \_   ___ \   ___\______   \ |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  | /    \  \/  / ___\       _/ |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  | \     \____/ /_/  >   |   \ |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ |  \______  /\___  /____|_  / |
 |   \__\    \/        \/     /__/      \/         \_/ |         \/______/       \/  |
 +-----------------------------------------------------+------+----------------------/
 | CryptGenRandom.cpp :: (d0t)niX's RandomGenerator Functions |
 \------------------------------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

INT fnCryptGenRandomNumber(VOID) {
	INT nRN;
	if (BCryptGenRandom(NULL, (LPBYTE)& nRN, sizeof(nRN), BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
		fnMessageHandlerW(NULL, L"Failed to Generate Random Buffer\nMemLoc: 0x%x", L"BCryptGenRandom", MB_ICONWARNING, &nRN);
	}

	return nRN & 0x7fffffff;
}

LPWSTR fnCryptGenRandomStringW(
	_In_opt_ HANDLE  hHeap,
	_In_opt_ LPWSTR  lpBuffer,
	_In_     INT     nBufferSize,
	_In_     LPCWSTR lpCharSet,
	_In_     SIZE_T  nCharSetSize
) {
	if (!lpBuffer) {
		if (hHeap) {
			lpBuffer = (LPWSTR)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, nBufferSize + 1);
		}
	} if (lpBuffer) {
		ZeroMemory(lpBuffer, (nBufferSize + 1) * sizeof(WCHAR));

		for (INT i = 0; i < nBufferSize; i++) {
			lpBuffer[i] = lpCharSet[fnCryptGenRandomNumber() % nCharSetSize];
		}

		return lpBuffer;
	} else {
		fnMessageHandlerW(NULL, L"Pointer to Buffer is invalid", L"Stack / HeapAlloc", MB_ICONERROR);
		return nullptr;
	}
}

LPCWSTR fnCryptGenUUIDW(
	_In_ LPCWSTR lpCharSet,
	_In_ INT nIdLen,
	_In_ INT nIds
) {


	return NULL;
}