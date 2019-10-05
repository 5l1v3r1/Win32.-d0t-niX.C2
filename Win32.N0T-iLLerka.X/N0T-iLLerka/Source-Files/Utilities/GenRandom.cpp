#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

INT fnCryptGenRandomNumber(VOID) {
	INT nRn;
	if (BCryptGenRandom(NULL, (LPBYTE)& nRn, sizeof(nRn), BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
		fnERRORHANDLERW(L"Failed to Generate Random Buffer", NULL, L"BCryptGenRandom", MB_ICONWARNING);
	}

	return nRn & 0x7fffffff;
}

std::wstring fnCryptGenRandomStringW(
	_In_ INT nLen
) {
	std::wstring szRcs;
	for (INT i = 0; i < nLen; i++) {
		szRcs += szCharSet[fnCryptGenRandomNumber() % cnCharSet];
	}

	return szRcs;
}

// TODO: finish this
VOID fnCryptGenRandomBufferW(
	_Inout_ LPBYTE pszRd,
	_In_ ULONG ulFs
) {
	if (BCryptGenRandom(NULL, pszRd, ulFs, BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
		fnERRORHANDLERW(L"Couldn't generate Random Buffer Content\nusing ZeroMemory instead", NULL, L"BCryptGenRandom", MB_ICONWARNING);
		ZeroMemory(pszRd, ulFs);
	}
}