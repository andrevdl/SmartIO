#pragma once

#include <vector>
#include <iostream>

#include "SIOCommon.h"
#include "SIOStream.h"
#include "SIOTokens.h"

constexpr auto TOKENIZER_BUFFER_SIZE = 4096;

class SIOTokenizer : SIOStream
{
private:
	char* str_buffer;
	short str_buffer_i;

	vector<SIOToken> tokens;

	const char cache_char(const char c);
	const char* get_buffer();
	void flush_cache();

	bool parse(string& error);
	bool parse_non_keyword(char c, string& error);

	bool push_token(SIOToken token);
protected:
	char get_and_move_char();
	bool rollback();
public:
	SIOTokenizer(string file);
	~SIOTokenizer();

	bool tokenize(string& error);

	friend ostream& operator<<(ostream& os, const SIOTokenizer& tokenizer);
};