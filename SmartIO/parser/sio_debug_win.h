#pragma once

#include <cstdlib>
#include <Windows.h> // use < > for all system and library headers
#include <winuser.h>
#include <string>

inline void toClipboard(HWND hwnd, const std::string& s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

inline void set_clipboard(const std::string& s)
{
	HWND hwnd = GetDesktopWindow();
	toClipboard(hwnd, s);
}