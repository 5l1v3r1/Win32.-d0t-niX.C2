#include "../../Header-Files/pch.h"
#include "../../Header-Files/N0t-iLLerka.h"

#if defined(_CONSOLE)
	BOOL fnPrintConsoleNiXW(VOID) {
		CreateThread(NULL, 0, &thPrintConsoleTitleW, NULL, NULL, NULL);
		std::wcout << szN0TiLLerkaX << std::endl;

		return FALSE;
	}

	DWORD WINAPI thPrintConsoleTitleW(
		_In_ LPVOID lpParam
	) {
		std::wstring szCt = szMALWR_NAME, szCt_t;
		for (INT i = 0; szCt[i] != '\0'; i++) {
			szCt_t += szCt[i];
			SetConsoleTitle(szCt_t.c_str());

			Sleep(100);
		}

		return TRUE;
	}
#endif // _CONSOLE