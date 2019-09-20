#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL CheckRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD edwType, BYTE ebValue) {
	HKEY hKey;
	DWORD dwType;
	BYTE bValue;
	DWORD dwlen = sizeof(DWORD);

	if (!RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey)) {
		if (!RegQueryValueEx(hKey, lpValueName, 0, &dwType, (BYTE*)& bValue, &dwlen)) {
			if (dwType == edwType && bValue == ebValue) {
				RegCloseKey(hKey);
				return TRUE;
			} else {
#ifdef DEBUG
				MessageBox(NULL, L"Registry Key/Type/Value doesn't match expacted Values", L"Illerka.X HKLM", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif
			}
		} else {
#ifdef DEBUG
			MessageBox(NULL, L"Couldn't Enumerate Registry Type/Value", L"RegQueryValueExW HKLM", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif
		}
	} else {
#ifdef DEBUG
		MessageBox(NULL, L"Couldn't Open Registry Key", L"RegOpenKeyExW HKLM", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif
	}

	// If HKLM can't be read try HKCU
	hKey = NULL;
	if (!RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey)) {
		if (!RegQueryValueEx(hKey, lpValueName, 0, &dwType, (BYTE*)& bValue, &dwlen)) {
			if (dwType == edwType && bValue == ebValue) {
				RegCloseKey(hKey);
				return TRUE;
			} else {
#ifdef DEBUG
				MessageBox(NULL, L"Registry Key/Type/Value doesn't match expacted Values", L"Illerka.X HKCU", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			}
		} else {
#ifdef DEBUG
			MessageBox(NULL, L"Couldn't Enumerate Registry Type/Value", L"RegQueryValueExW HKCU", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
		}
	} else {
#ifdef DEBUG
		MessageBox(NULL, L"Couldn't Open Registry Key", L"RegOpenKeyExW HKCU", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
	}

	RegCloseKey(hKey);
	return FALSE;
}