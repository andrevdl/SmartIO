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

char SIOStream::peek_char()
{
	if (my_str_index + 1 >= my_str.length())
	{
		return 0;
	}
	return my_str[my_str_index + 1];
}


bool SIOStream::skip_char()
{
	return ++my_str_index < my_str.length();
}

bool SIOStream::rollback()
{
	return --my_str_index >= 0;
}

bool SIOStream::done()
{
	return my_str_index >= my_str.length();
}

bool SIOStream::is_token_end()
{
	char c = get_char();
	return c == ':' || is_empty(c) || c == 0 || ispunct(c);
}

bool SIOStream::is_empty(char c)
{
	return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

bool SIOStream::next_is_empty()
{
	return is_empty(peek_char());
}
