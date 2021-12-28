/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "sio_tokenizer.h"

#include <sio_message.h>

const char SIOTokenizer::cache_char(const char c)
{
	if (c == 0 || str_buffer_i < 0 || str_buffer_i >= TOKENIZER_BUFFER_SIZE - 1)
	{
		return 0;
	}

	str_buffer[str_buffer_i++] = c;
	return c;
}

const char* SIOTokenizer::get_str_buffer()
{
	// Terminate string
	str_buffer[str_buffer_i] = 0;
	return str_buffer;
}

void SIOTokenizer::flush_str_cache()
{
	str_buffer_i = 0;
}

bool SIOTokenizer::parse()
{
	bookmark();
	char c = get_and_move_char();
	bool trap = false;

	if (isspace(c))
	{
		return true;
	} 
	else if (compare_and_trap(c, 'a', trap))
	{
		c = get_and_move_char();
		if (compare_and_trap(c, 'd', trap))
		{
			c = get_and_move_char();
			if (compare_and_trap(c, 'd', trap))
			{
				if (is_token_end())
				{
					return push_token(SIOTokenType::IO_ADD);
				}
			}
		}
	}
	else if (compare_and_trap(c, 'e', trap))
	{
		c = get_and_move_char();
		if (compare_and_trap(c, 'l', trap))
		{
			c = get_and_move_char();
			if (compare_and_trap(c, 's', trap))
			{
				c = get_and_move_char();
				if (compare_and_trap(c, 'e', trap))
				{
					return push_token(SIOTokenType::ELSE);
				}
			}
		}
	}
	else if (compare_and_trap(c, 'i', trap))
	{
		c = get_and_move_char();
		if (compare_and_trap(c, 'f', trap))
		{
			if (is_token_end())
			{
				return push_token(SIOTokenType::IF);
			}
		}
	}
	else if (compare_and_trap(c, 'v', trap))
	{
		c = get_and_move_char();
		if (compare_and_trap(c, 'a', trap))
		{
			c = get_and_move_char();
			if (compare_and_trap(c, 'r', trap))
			{
				if (is_token_end())
				{
					return push_token(SIOTokenType::VAR);
				}
			}
		}
	}

	else if (compare_and_trap(c, 'w', trap))
	{
		c = get_and_move_char();
		if (compare_and_trap(c, 'h', trap))
		{
			c = get_and_move_char();
			if (compare_and_trap(c, 'i', trap))
			{
				c = get_and_move_char();
				if (compare_and_trap(c, 'l', trap))
				{
					c = get_and_move_char();
					if (compare_and_trap(c, 'e', trap))
					{
						if (is_token_end())
						{
							return push_token(SIOTokenType::WHILE);
						}
					}
				}
			}
		}
	}
	else if (c == '.')
	{
		return push_token(SIOTokenType::DOT);
	}
	else if (c == ',')
	{
		return push_token(SIOTokenType::COMMA);
	}
	else if (c == ':')
	{
		if (get_char() == ':')
		{
			skip_char();
			return push_token(SIOTokenType::DCOLON);
		}
		return push_token(SIOTokenType::COLON);
	}
	else if (c == ';')
	{
		return push_token(SIOTokenType::SEMICOLON);
	}
	else if (c == '(')
	{
		return push_token(SIOTokenType::LPAR);
	}
	else if (c == ')')
	{
		return push_token(SIOTokenType::RPAR);
	} 
	else if (c == '[')
	{
		return push_token(SIOTokenType::LBR);
	}
	else if (c == ']')
	{
		return push_token(SIOTokenType::RBR);
	}
	else if (c == '{')
	{
		return push_token(SIOTokenType::LCURL);
	}
	else if (c == '}')
	{
		return push_token(SIOTokenType::RCURL);
	}
	else if (c == '<')
	{	
		c = get_char();
		if (c == '>')
		{
			skip_char();
			return push_token(SIOTokenType::LOGIC_UNEQUAL);
		}
		else if (c == '=')
		{
			skip_char();
			return push_token(SIOTokenType::LOGIC_SMALLER_EQUAL);
		}
		return push_token(SIOTokenType::SMALLER);
	}
	else if (c == '>')
	{
		if (get_char() == '=')
		{
			skip_char();
			return push_token(SIOTokenType::LOGIC_GREATER_EQUAL);
		}
		return push_token(SIOTokenType::LARGER);
	}
	else if (c == '$')
	{
		return push_token(SIOTokenType::DOLLAR);
	}
	else if (c == '\\')
	{
		return push_token(SIOTokenType::BSLASH);
	}
	else if (c == '#')
	{
		return push_token(SIOTokenType::HASH);
	}
	else if (c == '&')
	{
		c = get_and_move_char();
		if (c == '&')
		{
			return push_token(SIOTokenType::AND);
		}

		logger->log_error(ERROR_INVALID_TOKEN, this);
		return false;
	}
	else if (c == '|')
	{
		c = get_and_move_char();
		if (c == '|')
		{
			return push_token(SIOTokenType::OR);
		}

		logger->log_error(ERROR_INVALID_TOKEN, this);
		return false;
	}
	else if (c == '%')
	{
		return push_token(SIOTokenType::MODULO);
	}
	else if (c == '!')
	{
		if (get_char() == '=')
		{
			skip_char();
			return push_token(SIOTokenType::LOGIC_UNEQUAL);
		}
		return push_token(SIOTokenType::NOT);
	}
	else if (c == '=')
	{
		if (get_char() == '=')
		{
			skip_char();
			return push_token(SIOTokenType::LOGIC_EQUAL);
		}
		return push_token(SIOTokenType::ASSIGN);
	}
	else if (c == '+')
	{
		c = get_char();
		if (c == '=')
		{
			skip_char();
			return push_token(SIOTokenType::ASSIGN_ADD);
		}
		else if (c == '+')
		{
			skip_char();
			return push_token(SIOTokenType::INC);
		}
		return push_token(SIOTokenType::ADD);
	}
	else if (c == '-')
	{
		c = get_char();
		if (c == '=')
		{
			skip_char();
			return push_token(SIOTokenType::ASSIGN_MIN);
		}
		else if (c == '-')
		{
			skip_char();
			return push_token(SIOTokenType::DEC);
		}
		return push_token(SIOTokenType::MIN);
	}
	else if (c == '*')
	{
		if (get_char() == '=')
		{
			skip_char();
			return push_token(SIOTokenType::ASSIGN_STAR);
		}
		return push_token(SIOTokenType::STAR);
	}
	else if (c == '/')
	{
		c = get_char();

		// Skip comments
		if (c == '/') 
		{
			// single line
			skip_char();

			char p = get_and_move_char();
			while (p != '\n' && p != 0)
			{
				p = get_and_move_char();
			}

			return true;
		}
		else if (c == '*') 
		{
			// multi line
			skip_char();

			c = get_and_move_char();
			char p = get_char();

			while (c != '*' && p != '/' && c != 0 && p != 0)
			{
				c = get_and_move_char();
				p = get_char();
			}

			skip_char();
			return c == '*' && p == '/';
		}
		else if (c == '=') {
			skip_char();
			return push_token(SIOTokenType::ASSIGN_SLASH);
		}
		return push_token(SIOTokenType::SLASH);
	}
	else if (c == '"')
	{
		return parse_str(c, SIOTokenType::DSTRING, '"');
	}
	else if (c == '\'')
	{
		return parse_str(c, SIOTokenType::SSTRING, '\'');
	}

	if (trap)
	{
		restore_bookmark();
		c = get_and_move_char();
	}

	return parse_non_keyword(c);
}

bool SIOTokenizer::parse_non_keyword(char c)
{
	int ln = get_ln_pos();
	int col = get_col_pos();

	if (isdigit(c))
	{
		c = get_and_move_char();
		while (isdigit(c))
		{
			c = get_and_move_char();
		}

		if (ispunct(c))
		{
			rollback();
		}
		else if (isspace(c))
		{
			rollback_str_buffer();
		}
		else if (c != 0)
		{
			logger->log_error(ERROR_NUMBER_EXPECTED, this);
			return false;
		}

		errno = 0;
		char* end = 0;

		uint64_t val = strtoll(get_str_buffer(), &end, 10);
		if (errno == 0 && *end == 0)
		{
			return push_token(SIOTokenType::VALUE, val, ln, col);
		}

		logger->log_error(ERROR_INVALID_NUMBER_FORMAT, this);
		return false;
	}
	else if (isalpha(c))
	{
		c = get_and_move_char();
		while (isalnum(c) || c == '_')
		{
			c = get_and_move_char();
		}

		if (ispunct(c))
		{
			rollback();
		}
		else if (isspace(c))
		{
			rollback_str_buffer();
		}
		else if (c != 0)
		{
			logger->log_error(ERROR_INVALID_TOKEN, this);
			return false;
		}

		SIODataType data_type;
		SIODataRef* ref = ctx->str_token_translate(get_str_buffer(), data_type);
		
		// Const folding
		SIOTokenType token_type;
		if (ref->type == SIODataRef::Type::LITERAL && translate_literal_to_token(data_type, token_type))
		{
			return push_token(token_type, (uintptr_t)ref, ln, col);
		}

		return push_token(SIOTokenType::IDENTIFIER, (uintptr_t)ref, ln, col);
	}

	logger->log_error(ERROR_INVALID_TOKEN, this);
	return false;
}

bool SIOTokenizer::parse_str(char c, SIOTokenType type, char qoute)
{
	flush_str_cache();

	int ln = get_ln_pos();
	int col = get_col_pos();

	char p = 0;
	c = get_and_move_char();
	while ((c != qoute || p == '\\') && c != 0)
	{
		p = c;
		c = get_and_move_char();
	}

	if (c == qoute)
	{
		rollback_str_buffer();
		return push_token(type, (uintptr_t)ctx->store_str(get_str_buffer()), ln, col);
	}

	logger->log_error(ERRROR_UNCLOSED_STRING, this);
	return false;
}

bool SIOTokenizer::push_token(SIOTokenType type)
{
	int ln = get_ln_pos();
	int col = get_col_pos();

	tokens.push_back(new SIOToken{ type, 0, ln, col, ln, col });
	return true;
}

bool SIOTokenizer::push_token(SIOTokenType type, uint64_t value, int start_ln, int start_col)
{
	int ln = get_ln_pos();
	int col = get_col_pos();

	tokens.push_back(new SIOToken{ type, value, start_ln, start_col, ln, col });
	return true;
}

const bool SIOTokenizer::translate_literal_to_token(const SIODataType type, SIOTokenType& token_type)
{
	switch (type)
	{
	case SIODataType::INTEGER:
		token_type = SIOTokenType::VALUE;
		return true;
	case SIODataType::STRING:
		token_type = SIOTokenType::DSTRING;
		return true;
	case SIODataType::DOUBLE:
		token_type = SIOTokenType::DOUBLE;
		return true;
	}
	
	return false;
}

char SIOTokenizer::get_and_move_char()
{
	return cache_char(SIOStream::get_and_move_char());
}

bool SIOTokenizer::rollback(int i)
{
	return SIOStream::rollback(i) && rollback_str_buffer(i);
}

bool SIOTokenizer::rollback_str_buffer(int i)
{
	str_buffer_i -= i;
	return str_buffer_i > -1;
}

SIOTokenizer::SIOTokenizer(string file, SIOContext* ctx, SIOLogger* logger) : ctx(ctx), logger(logger), SIOStream(file)
{
	str_buffer = new char[TOKENIZER_BUFFER_SIZE];
	str_buffer_i = 0;
}

SIOTokenizer::~SIOTokenizer()
{
	delete[] str_buffer;
}

bool SIOTokenizer::tokenize()
{
	str_buffer_i = 0;

	bool state = true;
	while (state && !done())
	{
		state = parse();
		flush_str_cache();
	}

	if (state)
	{
		logger->log_success(INFO_PARSE_BUILD_SUCCES);
	}
	else
	{
		logger->log_error(ERROR_PARSE_BUILD_FAILED);
	}

	return state;
}

vector<SIOToken*>::iterator SIOTokenizer::begin()
{
	return tokens.begin();
}

vector<SIOToken*>::iterator SIOTokenizer::end()
{
	return tokens.end();
}

ostream& operator<<(ostream& os, const SIOTokenizer& tokenizer)
{
	for each (SIOToken* token in tokenizer.tokens)
	{
		os << "type:\t" << int(token->type) << "\tvalue: " << token->value << endl;
	}

	return os;
}
