/*-----------------------------------------------------+---------------------------\
 |    ___    __________   __  ___          ______  ___ |  _______   __   ____      |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / |  \      \_/  |_|    |     |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  |  /   |   \   __\    |     |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  | /    |    \  | |    |___  |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ | \____|__  /__| |_______ \ |
 |   \__\    \/        \/     /__/      \/         \_/ |         \/             \/ |
 +------------------------------------------+----------+---------------------------/
 | ntrtl.h :: (d0t)niX's NT/RTL Header File |
 \------------------------------------------*/                          #pragma once

#if NT_FUNCTIONS == TRUE
	// NT Library //
	#pragma comment(lib, "ntdll.lib")

	// NT Macros //
	#define OPTION_SHUTDOWN_SYSTEM 0x6
	#define SE_SHUTDOWN_PRIVILEGE 0x13
	#define SE_DEBUG_PRIVILEGE 0x14

	// NT Typedefinitions //
	typedef struct {
		USHORT Length;
		USHORT MaximumLength;
		LPWSTR  Buffer;
	} UNICODE_STRING, *PUNICODE_STRING;

	// NT/RTL Function Prototypes //
	EXTERN_C NTSYSAPI NTSTATUS NTAPI RtlAdjustPrivilege(
		_In_ ULONG,
		_In_ BOOLEAN,
		_In_ BOOLEAN,
		_Out_ PBOOLEAN
	);
	EXTERN_C NTSYSAPI NTSTATUS STDAPIVCALLTYPE RtlSetProcessIsCritical(
		_In_ BOOLEAN,
		_Out_opt_ PBOOLEAN,
		_In_ BOOLEAN
	);
	EXTERN_C NTSYSAPI NTSTATUS NTAPI NtRaiseHardError(
		_In_ NTSTATUS,
		_In_ ULONG,
		_In_opt_ PUNICODE_STRING,
		_In_opt_ LPVOID*,
		_In_ UINT,
		_Out_ LPUINT
	);

	// NT Utilitie Functions //
	BOOL fnNTSetProcessIsCritical(
		_In_ BOOLEAN blIsCritical
	);
	BOOL fnNTRaiseHardError(VOID);
#endif // NT_FUNCTIONS