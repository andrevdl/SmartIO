/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>
#include <sio_log.h>

using namespace std;

class SIOStream : public SIOPosInfo
{
private:
	string my_str;
	int my_str_index;

	int bookmark_pos;
	int bookmark_ln, bookmark_col;

	char _get_char(int pos);
public:
	SIOStream(string file);
protected:
	char get_char();
	char get_and_move_char();
	bool skip_char(int i = 1);
	char rollback_and_get_char(int i = 1);

	bool bookmark();
	void restore_bookmark();

	bool compare_and_trap(const char c, const char check, bool& trap);

	virtual bool rollback(int i = 1);
	bool done();

	bool is_token_end();
};