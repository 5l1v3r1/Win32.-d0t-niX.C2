#include "../../HeaderFiles/N0TiLLerka.h"

int RandomNumberGeneratorW() {
	int iRn;
	if (BCryptGenRandom(NULL, (BYTE*)& iRn, sizeof(iRn), BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
#ifdef DEBUG
		MessageBox(NULL, L"Failed to Generate Random Buffer", L"BCryptGenRandom", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif
	}

	return iRn & 0x7fffffff;
}

std::wstring RandomStringGeneratorW(int rsg_strlen) {
	std::wstring wsRcs;
	for (int i = 0; i < rsg_strlen; i++) {
		wsRcs += CharSet[RandomNumberGenerator() % nCharSet];
	}

	return wsRcs;
}