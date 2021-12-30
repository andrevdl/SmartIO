/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

//#include <cstdlib>
//#include <Windows.h> // use < > for all system and library headers
//#include <winuser.h>
//#include <string>
//
//inline void toClipboard(HWND hwnd, const std::string& s) {
//	OpenClipboard(hwnd);
//	EmptyClipboard();
//	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
//	if (!hg) {
//		CloseClipboard();
//		return;
//	}
//	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
//	GlobalUnlock(hg);
//	SetClipboardData(CF_TEXT, hg);
//	CloseClipboard();
//	GlobalFree(hg);
//}
//
//inline void set_clipboard(const std::string& s)
//{
//	HWND hwnd = GetDesktopWindow();
//	toClipboard(hwnd, s);
//}