#include "../HeaderFiles/N0TiLLerka.h"

const WCHAR szCharSet[] = {
	L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	L"abcdefghijklmnopqrstuvwxyz"
	L"1234567890"
};
const size_t cnCharSet = (sizeof(szCharSet) - 2) / 2;

PWCHAR pszDest = new WCHAR[0x7d0];
const size_t cnDest = 0x7d0;