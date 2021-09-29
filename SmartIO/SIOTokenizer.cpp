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

const char* SIOTokenizer::get_buffer()
{
	// Terminate string
	str_buffer[str_buffer_i] = 0;
	return str_buffer;
}

void SIOTokenizer::flush_cache()
{
	str_buffer_i = 0;
}

bool SIOTokenizer::parse(string& error)
{
	char c = get_and_move_char();

	if (is_empty(c))
	{
		return true;
	} 
	else if (c == 'a')
	{
		c = get_and_move_char();
		if (c == 'd')
		{
			c = get_and_move_char();
			if (c == 'd')
			{
				if (is_token_end())
				{
					return PUSH_TOKEN(SIOTokenType::IO_ADD);
				}
			}
		}
	}
	else if (c == 'e')
	{
		c = get_and_move_char();
		if (c == 'l')
		{
			c = get_and_move_char();
			if (c == 's')
			{
				c = get_and_move_char();
				if (c == 'e')
				{
					return PUSH_TOKEN(SIOTokenType::ELSE);
				}
			}
		}
	}
	else if (c == 'i')
	{
		c = get_and_move_char();
		if (c == 'f')
		{
			if (is_token_end())
			{
				return PUSH_TOKEN(SIOTokenType::IF);
			}
		}
	}
	else if (c == 'v')
	{
		c = get_and_move_char();
		if (c == 'a')
		{
			c = get_and_move_char();
			if (c == 'r')
			{
				if (is_token_end())
				{
					return PUSH_TOKEN(SIOTokenType::VAR);
				}
			}
		}
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
		flush_cache();

		char p = 0;
		c = get_and_move_char();
		while (c != '"' || p == '\\')
		{
			p = c;
			c = get_and_move_char();
		}

		if (c == '"')
		{
			rollback();
			return PUSH_TOKEN_VAL(SIOTokenType::DSTRING, 1); // TODO: implement string table
		}
		
		return false;
	}
	else if (c == '\'')
	{
		flush_cache();

		char p = 0;
		c = get_and_move_char();
		while (c != '\'' || p == '\\')
		{
			p = c;
			c = get_and_move_char();
		}

		if (c == '\'')
		{
			rollback();
			return PUSH_TOKEN_VAL(SIOTokenType::SSTRING, 1); // TODO: implement string table
		}

		return false;
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
			SIOStream::rollback();
			rollback();
		}
		else if (isspace(c))
		{
			rollback();
		}
		else if (c != 0)
		{
			return false;
		}

		errno = 0;
		char* end = 0;

		uint64_t val = strtoll(get_buffer(), &end, 10);
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
			SIOStream::rollback();
			rollback();
		}
		else if (isspace(c))
		{
			rollback();
		}
		else if (c != 0)
		{
			return false;
		}

		return PUSH_TOKEN_VAL(SIOTokenType::VALUE, 1); // TODO: implement string table
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

bool SIOTokenizer::rollback()
{
	return --str_buffer_i > -1;
}

SIOTokenizer::SIOTokenizer(string file) : SIOStream(file)
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
		flush_cache();
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
