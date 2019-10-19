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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

DWORD WINAPI thWindowThread(
	_In_ LPVOID lParam
) {
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = fnCryptGenRandomStringW(NULL, nRNG_RAN(nMIN_RS_LEN, nMAX_RS_LEN), szCharSet, cculCharSet);

	RegisterClassEx(&wc);

	HWND hwnd = CreateWindowEx(0, wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, NULL, NULL);
	if (hwnd) {
		MSG mMsg; BOOL bRet;
		while ((bRet = GetMessage(&mMsg, NULL, 0, 0)) != 0) {
			if (bRet == -1) {
				fnMessageHandlerW(NULL, L"Couldn't get Message", L"GetMessageW", MB_ICONERROR);
			} else {
				TranslateMessage(&mMsg);
				DispatchMessage(&mMsg);
			}
		}
	}

	delete[] wc.lpszClassName;
}