#pragma once

#include "SIOCommon.h"

class SIOStream
{
private:
	string my_str;
	int my_str_index;
public:
	SIOStream(string file);
protected:
	char get_char();
	char get_and_move_char();
	char peek_char();
	bool skip_char();

	bool rollback();
	bool done();

	bool is_token_end();

	bool is_empty(char c);

	bool next_is_empty();
};