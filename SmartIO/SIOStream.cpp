#include "SIOStream.h"

SIOStream::SIOStream(string file)
{
	my_str = file;
	my_str_index = 0;
}

char SIOStream::get_char()
{
	if (my_str_index >= my_str.length())
	{
		return 0;
	}
	return my_str[my_str_index];
}

char SIOStream::get_and_move_char()
{
	if (my_str_index >= my_str.length())
	{
		return 0;
	}
	return my_str[my_str_index++];
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

bool SIOStream::rollback(int i)
{
	my_str_index -= i;
	return i >= 0;
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