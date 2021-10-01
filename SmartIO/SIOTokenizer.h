#pragma once

#include <vector>
#include <iostream>

#include "SIOCommon.h"
#include "SIOStream.h"
#include "SIOTokens.h"

constexpr auto TOKENIZER_BUFFER_SIZE = 4096;

#define PUSH_TOKEN_VAL(t, v) push_token(new SIOToken{ t, v })
#define PUSH_TOKEN(t) PUSH_TOKEN_VAL(t, 0)

class SIOTokenizer : SIOStream
{
private:
	char* str_buffer;
	short str_buffer_i;

	vector<SIOToken*> tokens;

	const char cache_char(const char c);
	const char* get_str_buffer();
	void flush_str_cache();

	bool parse(string& error);
	bool parse_non_keyword(char c, string& error);

	bool push_token(SIOToken* token);
protected:
	char get_and_move_char();
	bool rollback(int i = 1);
	bool rollback_str_buffer(int i = 1);
public:
	SIOTokenizer(string file);
	~SIOTokenizer();

	bool tokenize(string& error);

	vector<SIOToken*>::iterator begin();
	vector<SIOToken*>::iterator end();

	friend ostream& operator<<(ostream& os, const SIOTokenizer& tokenizer);
};