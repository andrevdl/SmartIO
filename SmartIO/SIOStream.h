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
	bool skip_char(int i = 1);
	char rollback_and_get_char(int i = 1);

	bool rollback(int i = 1);
	bool done();

	bool is_token_end();
};