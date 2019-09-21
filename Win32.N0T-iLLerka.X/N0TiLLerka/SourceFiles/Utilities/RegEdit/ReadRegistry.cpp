#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL fnCheckRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwEType, BYTE bEValue) {
	HKEY hKey;
	DWORD dwType;
	BYTE bValue;
	DWORD dwlen = sizeof(DWORD);

	if (!RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey)) {
		if (!RegQueryValueEx(hKey, lpValueName, 0, &dwType, (PBYTE)& bValue, &dwlen)) {
			if (dwType == dwEType && bValue == bEValue) {
				RegCloseKey(hKey);
				return TRUE;
			} else {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Registry Key/Type/Value doesn't match expacted Values (HKLM)", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
			}
		} else {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't Enumerate Registry Type/Value", L"RegQueryValueExW HKLM", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
		}
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't Open Registry Key", L"RegOpenKeyExW HKLM", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
	}

	// If HKLM can't be read try HKCU
	hKey = NULL;
	if (!RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey)) {
		if (!RegQueryValueEx(hKey, lpValueName, 0, &dwType, (PBYTE)& bValue, &dwlen)) {
			if (dwType == dwEType && bValue == bEValue) {
				RegCloseKey(hKey);
				return TRUE;
			} else {
#ifdef DEBUG_MSG
				MessageBox(NULL, L"Registry Key/Type/Value doesn't match expacted Values (HKCU)", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			}
		} else {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't Enumerate Registry Type/Value", L"RegQueryValueExW HKCU", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
		}
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't Open Registry Key", L"RegOpenKeyExW HKCU", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
	}

	RegCloseKey(hKey);
	return FALSE;
}