#include "SIOTokenizer.h"

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

bool SIOTokenizer::parse(string& error)
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
					return PUSH_TOKEN(SIOTokenType::IO_ADD);
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
					return PUSH_TOKEN(SIOTokenType::ELSE);
				}
			}
		}

		trap = true;
	}
	else if (compare_and_trap(c, 'i', trap))
	{
		c = get_and_move_char();
		if (compare_and_trap(c, 'f', trap))
		{
			if (is_token_end())
			{
				return PUSH_TOKEN(SIOTokenType::IF);
			}
		}

		trap = true;
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
					return PUSH_TOKEN(SIOTokenType::VAR);
				}
			}
		}

		trap = true;
	}
	else if (c == '.')
	{
		return PUSH_TOKEN(SIOTokenType::DOT);
	}
	else if (c == ',')
	{
		return PUSH_TOKEN(SIOTokenType::COMMA);
	}
	else if (c == ':')
	{
		if (get_char() == ':')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::DCOLON);
		}
		return PUSH_TOKEN(SIOTokenType::COLON);
	}
	else if (c == ';')
	{
		return PUSH_TOKEN(SIOTokenType::SEMICOLON);
	}
	else if (c == '(')
	{
		return PUSH_TOKEN(SIOTokenType::LPAR);
	}
	else if (c == ')')
	{
		return PUSH_TOKEN(SIOTokenType::RPAR);
	} 
	else if (c == '[')
	{
		return PUSH_TOKEN(SIOTokenType::LBR);
	}
	else if (c == ']')
	{
		return PUSH_TOKEN(SIOTokenType::RBR);
	}
	else if (c == '{')
	{
		return PUSH_TOKEN(SIOTokenType::LCURL);
	}
	else if (c == '}')
	{
		return PUSH_TOKEN(SIOTokenType::RCURL);
	}
	else if (c == '<')
	{	
		c = get_char();
		if (c == '>')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::LOGIC_UNEQUAL);
		}
		else if (c == '=')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::LOGIC_SMALLER_EQUAL);
		}
		return PUSH_TOKEN(SIOTokenType::SMALLER);
	}
	else if (c == '>')
	{
		if (get_char() == '=')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::LOGIC_GREATER_EQUAL);
		}
		return PUSH_TOKEN(SIOTokenType::LARGER);
	}
	else if (c == '$')
	{
		return PUSH_TOKEN(SIOTokenType::DOLLAR);
	}
	else if (c == '\\')
	{
		return PUSH_TOKEN(SIOTokenType::BSLASH);
	}
	else if (c == '#')
	{
		return PUSH_TOKEN(SIOTokenType::HASH);
	}
	else if (c == '&')
	{
		c = get_and_move_char();
		if (c == '&')
		{
			return PUSH_TOKEN(SIOTokenType::AND);
		}

		return false;
	}
	else if (c == '|')
	{
		c = get_and_move_char();
		if (c == '|')
		{
			return PUSH_TOKEN(SIOTokenType::OR);
		}

		return false;
	}
	else if (c == '%')
	{
		return PUSH_TOKEN(SIOTokenType::MODULO);
	}
	else if (c == '!')
	{
		if (get_char() == '=')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::LOGIC_UNEQUAL);
		}
		return PUSH_TOKEN(SIOTokenType::NOT);
	}
	else if (c == '=')
	{
		if (get_char() == '=')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::LOGIC_EQUAL);
		}
		return PUSH_TOKEN(SIOTokenType::ASSIGN);
	}
	else if (c == '+')
	{
		c = get_char();
		if (c == '=')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::ASSIGN_ADD);
		}
		else if (c == '+')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::INC);
		}
		return PUSH_TOKEN(SIOTokenType::ADD);
	}
	else if (c == '-')
	{
		c = get_char();
		if (c == '=')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::ASSIGN_MIN);
		}
		else if (c == '-')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::DEC);
		}
		return PUSH_TOKEN(SIOTokenType::MIN);
	}
	else if (c == '*')
	{
		if (get_char() == '=')
		{
			skip_char();
			return PUSH_TOKEN(SIOTokenType::ASSIGN_STAR);
		}
		return PUSH_TOKEN(SIOTokenType::STAR);
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
			return PUSH_TOKEN(SIOTokenType::ASSIGN_SLASH);
		}
		return PUSH_TOKEN(SIOTokenType::SLASH);
	}
	else if (c == '"')
	{
		flush_str_cache();

		char p = 0;
		c = get_and_move_char();
		while (c != '"' || p == '\\')
		{
			p = c;
			c = get_and_move_char();
		}

		if (c == '"')
		{
			rollback_str_buffer();
			return PUSH_TOKEN_VAL(SIOTokenType::DSTRING, ctx->store_str(get_str_buffer()));
		}
		
		return false;
	}
	else if (c == '\'')
	{
		flush_str_cache();

		char p = 0;
		c = get_and_move_char();
		while (c != '\'' || p == '\\')
		{
			p = c;
			c = get_and_move_char();
		}

		if (c == '\'')
		{
			rollback_str_buffer();
			return PUSH_TOKEN_VAL(SIOTokenType::SSTRING, ctx->store_str(get_str_buffer()));
		}

		return false;
	}

	if (trap)
	{
		restore_bookmark();
		c = get_and_move_char();
	}

	return parse_non_keyword(c, error);
}

bool SIOTokenizer::parse_non_keyword(char c, string& error)
{
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
			return false;
		}

		errno = 0;
		char* end = 0;

		uint64_t val = strtoll(get_str_buffer(), &end, 10);
		return errno == 0 && *end == 0 && PUSH_TOKEN_VAL(SIOTokenType::VALUE, val);
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
			return false;
		}

		SIODataType data_type;
		SIODataRef ref = ctx->str_token_translate(get_str_buffer(), data_type);
		
		// Const folding only for strings and integers (no doubles or formatted data)
		// Doubles and formatted data may in future, for now they are multiple tokens
		// I.e.: Double => VALUE DOT VALUE
		SIOTokenType token_type;
		if (ref.type == SIODataRef::Type::LITERAL && translate_literal_to_token(data_type, token_type))
		{
			return PUSH_TOKEN_VAL(token_type, ref.ref);
		}

		return PUSH_TOKEN_VAL(SIOTokenType::IDENTIFIER, ref.ref);
	}

	return false;
}

bool SIOTokenizer::push_token(SIOToken* token)
{
	tokens.push_back(token);

	return true;
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

SIOTokenizer::SIOTokenizer(string file, SIOContext* ctx) : ctx(ctx), SIOStream(file)
{
	str_buffer = new char[TOKENIZER_BUFFER_SIZE];
	str_buffer_i = 0;
}

SIOTokenizer::~SIOTokenizer()
{
	delete[] str_buffer;
}

bool SIOTokenizer::tokenize(string& error)
{
	str_buffer_i = 0;

	bool state = true;
	while (state && !done())
	{
		state = parse(error);
		flush_str_cache();
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
