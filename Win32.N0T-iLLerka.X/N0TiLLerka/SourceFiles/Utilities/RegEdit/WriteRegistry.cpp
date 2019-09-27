#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL fnCreateRegistryKeyW(
	_In_ BOOL hKeyOpt,
	_In_ LPCWSTR lpSubKey
) {
	HKEY hKey = NULL;
	BOOL bReturn = FALSE;

	if (hKeyOpt & HKLM) {
		if (!RegCreateKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &hKey, NULL)) {
			bReturn |= HKLM;
		} else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't create Registry Key\nKey: %s", NULL, L"RegCreateKeyExW", MB_OK | MB_ICONWARNING, lpSubKey);
#endif // DEBUG_MSG
		}
	}

	if (hKeyOpt & HKCU) {
		if (!RegCreateKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &hKey, NULL)) {
			bReturn |= HKCU;
		} else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't create Registry Key\nKey: %s", NULL, L"RegCreateKeyExW", MB_OK | MB_ICONWARNING, lpSubKey);
#endif // DEBUG_MSG
		}
	}

	if (hKey) { RegCloseKey(hKey); }
	return bReturn;
}