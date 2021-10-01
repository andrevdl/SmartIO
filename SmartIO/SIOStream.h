#pragma once

#include "SIOCommon.h"

class SIOStream
{
private:
	string my_str;
	int my_str_index;

	int bookmark_pos;
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

	bool rollback(int i = 1);
	bool done();

	bool is_token_end();
};