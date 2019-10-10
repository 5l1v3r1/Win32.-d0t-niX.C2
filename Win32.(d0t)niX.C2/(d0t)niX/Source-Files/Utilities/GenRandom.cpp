/*-----------------------------------------------------+-----------------------------\
 |    ___    __________   __  ___          ______  ___ | _________       __________  |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | \_   ___ \   ___\______   \ |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  | /    \  \/  / ___\       _/ |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  | \     \____/ /_/  >   |   \ |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ |  \______  /\___  /____|_  / |
 |   \__\    \/        \/     /__/      \/         \_/ |         \/______/       \/  |
 +-----------------------------------------------------+-+---------------------------/
 | GenRandom.cpp :: (d0t)niX's RandomGenerator Functions |
 \-------------------------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

INT fnCryptGenRandomNumber(VOID) {
	INT nRn;
	if (BCryptGenRandom(NULL, (LPBYTE)& nRn, sizeof(nRn), BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
		fnMESSAGEHANDLERW(NULL, L"Failed to Generate Random Buffer", L"BCryptGenRandom", MB_ICONWARNING);
	}

	return nRn & 0x7fffffff;
}

// TODO: use Pointers
std::wstring fnCryptGenRandomStringW(
	_In_ INT nLen
) {
	std::wstring szRcs;
	for (INT i = 0; i < nLen; i++) {
		szRcs += szCharSet[fnCryptGenRandomNumber() % cculCharSet];
	}

	return szRcs;
}