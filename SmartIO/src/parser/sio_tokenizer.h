#pragma once

#include <vector>
#include <iostream>
#include <string>

#include <sio_stream.h>
#include <parser/sio_tokens.h>

#include <sio_context.h>

using namespace std;

constexpr auto TOKENIZER_BUFFER_SIZE = 4096;

class SIOTokenizer : SIOStream
{
private:
	SIOContext* ctx;
	SIOLogger* logger;

	char* str_buffer;
	short str_buffer_i;

	vector<SIOToken*> tokens;

	const char cache_char(const char c);
	const char* get_str_buffer();
	void flush_str_cache();

	bool parse();
	bool parse_non_keyword(char c);
	bool parse_str(char c, SIOTokenType type, char qoute);

	bool push_token(SIOTokenType type);
	bool push_token(SIOTokenType type, uint64_t value, int start_ln, int start_col);

	const bool translate_literal_to_token(const SIODataType type, SIOTokenType& token_type);
protected:
	char get_and_move_char();
	bool rollback(int i = 1);
	bool rollback_str_buffer(int i = 1);
public:
	SIOTokenizer(string file, SIOContext* ctx, SIOLogger* logger);
	~SIOTokenizer();

	bool tokenize();

	vector<SIOToken*>::iterator begin();
	vector<SIOToken*>::iterator end();

	friend ostream& operator<<(ostream& os, const SIOTokenizer& tokenizer);
};