/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "sio_stream.h"

char SIOStream::_get_char(int pos)
{
	char c = my_str[pos];
	if (c == '\n')
	{
		update_ln_pos();
	}
	else
	{
		update_col_pos();
	}

	return c;
}

SIOStream::SIOStream(string file)
{
	my_str = file;
	my_str_index = 0;

	bookmark_ln = 1;
	bookmark_col = 0;
	
	bookmark_pos = 0;
}

char SIOStream::get_char()
{
	if (my_str_index >= my_str.length())
	{
		return 0;
	}

	return _get_char(my_str_index);
}

char SIOStream::get_and_move_char()
{
	if (my_str_index >= my_str.length())
	{
		return 0;
	}

	return _get_char(my_str_index++);
}

bool SIOStream::skip_char(int i)
{
	my_str_index += i;
	return my_str_index < my_str.length();
}

char SIOStream::rollback_and_get_char(int i)
{
	return rollback(i) ? get_char() : 0;
}

bool SIOStream::bookmark()
{
	if (my_str_index >= 0 && my_str_index < my_str.length())
	{
		bookmark_ln = get_ln_pos();
		bookmark_col = get_col_pos();
		bookmark_pos = my_str_index;
		return true;
	}
	return false;
}

void SIOStream::restore_bookmark()
{
	rollback(my_str_index - bookmark_pos);
	set_pos_info(bookmark_ln, bookmark_col);
}

bool SIOStream::compare_and_trap(const char c, const char check, bool& trap)
{
	trap = (c == check) || trap;
	return c == check;
}

bool SIOStream::rollback(int i)
{
	my_str_index -= i;
	return my_str_index >= 0;
}

bool SIOStream::done()
{
	return my_str_index >= my_str.length();
}

bool SIOStream::is_token_end()
{
	char c = get_char();
	return iscntrl(c) || isspace(c) || ispunct(c);
}