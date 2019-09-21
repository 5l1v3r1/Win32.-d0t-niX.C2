#include "../../../HeaderFiles/N0TiLLerka.h"

BOOL fnCreateRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, DWORD dwValue) {
	HKEY hKey;
	BOOL bReturnvalHKLM, bReturnvalHKCU;

	if (!RegCreateKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &hKey, NULL)) {
		if (!RegSetValueEx(hKey, lpValueName, 0, dwType, (PBYTE)& dwValue, sizeof(DWORD))) {
			bReturnvalHKLM = TRUE;
		} else {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't set Registry Type/Value", L"RegSetValueExW", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
			bReturnvalHKLM = FALSE;
		}
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't create Registry Key", L"RegCreateKeyExW", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif // DEBUG_MSG
		bReturnvalHKLM = FALSE;
	}

	hKey = NULL;
	if (!RegCreateKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &hKey, NULL)) {
		if (!RegSetValueEx(hKey, lpValueName, 0, dwType, (PBYTE)& dwValue, sizeof(DWORD))) {
			bReturnvalHKCU = TRUE;
		} else {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't set Registry Type/Value", L"RegSetValueExW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			bReturnvalHKCU = FALSE;
		}
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't create Registry Key", L"RegCreateKeyExW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
		bReturnvalHKCU = FALSE;
	}

	RegCloseKey(hKey);
	if (bReturnvalHKLM == TRUE || bReturnvalHKCU == TRUE) {
		return TRUE;
	} else {
		return FALSE;
	}
}