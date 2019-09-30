#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

INT fnCryptGenRandomNumber(VOID) {
	INT nRn;
	if (BCryptGenRandom(NULL, (PBYTE)& nRn, sizeof(nRn), BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Failed to Generate Random Buffer", L"BCryptGenRandom", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
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
	_Inout_ PBYTE pszRd,
	_In_ ULONG ulFs
) {
	if (BCryptGenRandom(NULL, pszRd, ulFs, BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't generate Random Buffer Content\nusing ZeroMemory instead", L"BCryptGenRandom", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
#endif // DEBUG_MSG
		ZeroMemory(pszRd, ulFs);
	}
}