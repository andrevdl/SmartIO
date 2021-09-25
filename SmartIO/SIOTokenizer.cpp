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
					return push_token({ SIOTokenType::IO_ADD, 0 });
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
					return push_token({ SIOTokenType::ELSE, 0 });
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
				return push_token({ SIOTokenType::IF, 0 });
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
					return push_token({ SIOTokenType::VAR, 0 });
				}
			}
		}
	}
	else if (c == '.')
	{
		return push_token({ SIOTokenType::DOT, 0 });
	}
	else if (c == ',')
	{
		return push_token({ SIOTokenType::COMMA, 0 });
	}
	else if (c == ':')
	{
		if (get_char() == ':')
		{
			skip_char();
			return push_token({ SIOTokenType::DCOLON, 0 });
		}
		return push_token({ SIOTokenType::COLON, 0 });
	}
	else if (c == ';')
	{
		return push_token({ SIOTokenType::SEMICOLON, 0 });
	}
	else if (c == '(')
	{
		return push_token({ SIOTokenType::LPAR, 0 });
	}
	else if (c == ')')
	{
		return push_token({ SIOTokenType::RPAR, 0 }); 
	} 
	else if (c == '[')
	{
		return push_token({ SIOTokenType::LBR, 0 });
	}
	else if (c == ']')
	{
		return push_token({ SIOTokenType::RBR, 0 });
	}
	else if (c == '{')
	{
		return push_token({ SIOTokenType::LCURL, 0 });
	}
	else if (c == '}')
	{
		return push_token({ SIOTokenType::RCURL, 0 });
	}
	else if (c == '<')
	{	
		c = get_char();
		if (c == '>')
		{
			skip_char();
			return push_token({ SIOTokenType::LOGIC_UNEQUAL, 0 });
		}
		else if (c == '=')
		{
			skip_char();
			return push_token({ SIOTokenType::LOGIC_SMALLER_EQUAL, 0 });
		}
		return push_token({ SIOTokenType::SMALLER, 0 });
	}
	else if (c == '>')
	{
		if (get_char() == '=')
		{
			skip_char();
			return push_token({ SIOTokenType::LOGIC_GREATER_EQUAL, 0 });
		}
		return push_token({ SIOTokenType::LARGER, 0 });
	}
	else if (c == '$')
	{
		return push_token({ SIOTokenType::DOLLAR, 0 });
	}
	else if (c == '\\')
	{
		return push_token({ SIOTokenType::BSLASH, 0 });
	}
	else if (c == '#')
	{
		return push_token({ SIOTokenType::HASH, 0 });
	}
	else if (c == '&')
	{
		c = get_and_move_char();
		if (c == '&')
		{
			return push_token({ SIOTokenType::AND, 0 });
		}

		return false;
	}
	else if (c == '|')
	{
		c = get_and_move_char();
		if (c == '|')
		{
			return push_token({ SIOTokenType::OR, 0 });
		}

		return false;
	}
	else if (c == '%')
	{
		return push_token({ SIOTokenType::MODULO, 0 });
	}
	else if (c == '!')
	{
		if (get_char() == '=')
		{
			skip_char();
			return push_token({ SIOTokenType::LOGIC_UNEQUAL, 0 });
		}
		return push_token({ SIOTokenType::NOT, 0 });
	}
	else if (c == '=')
	{
		if (get_char() == '=')
		{
			skip_char();
			return push_token({ SIOTokenType::LOGIC_EQUAL, 0 });
		}
		return push_token({ SIOTokenType::ASSIGN, 0 });
	}
	else if (c == '+')
	{
		c = get_char();
		if (c == '=')
		{
			skip_char();
			return push_token({ SIOTokenType::ASSIGN_ADD, 0 });
		}
		else if (c == '+')
		{
			skip_char();
			return push_token({ SIOTokenType::INC, 0 });
		}
		return push_token({ SIOTokenType::ADD, 0 });
	}
	else if (c == '-')
	{
		c = get_char();
		if (c == '=')
		{
			skip_char();
			return push_token({ SIOTokenType::ASSIGN_MIN, 0 });
		}
		else if (c == '-')
		{
			skip_char();
			return push_token({ SIOTokenType::DEC, 0 });
		}
		return push_token({ SIOTokenType::MIN, 0 });
	}
	else if (c == '*')
	{
		if (get_char() == '=')
		{
			skip_char();
			return push_token({ SIOTokenType::ASSIGN_STAR, 0 });
		}
		return push_token({ SIOTokenType::STAR, 0 });
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
			return push_token({ SIOTokenType::ASSIGN_SLASH, 0 });
		}

		return push_token({ SIOTokenType::SLASH, 0 });
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
			return push_token({ SIOTokenType::DSTRING, 1 }); // TODO: implement string table
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
			return push_token({ SIOTokenType::SSTRING, 1 }); // TODO: implement string table
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

		if (ispunct(c) || isspace(c))
		{
			rollback();
		}
		else if (c != 0)
		{
			return false;
		}

		errno = 0;
		char* end = 0;

		uint64 val = strtoll(get_buffer(), &end, 10);
		return errno == 0 && *end == 0 && push_token({ SIOTokenType::VALUE, val });
	}
	else if (isalpha(c))
	{
		c = get_and_move_char();
		while (isalnum(c) || c == '_')
		{
			c = get_and_move_char();
		}

		if (ispunct(c) || isspace(c))
		{
			rollback();
		}
		else if (c != 0)
		{
			return false;
		}

		return push_token({ SIOTokenType::IDENTIFIER, 1 }); // TODO: implement string table
	}

	return false;
}

bool SIOTokenizer::push_token(SIOToken token)
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

ostream& operator<<(ostream& os, const SIOTokenizer& tokenizer)
{
	for each (SIOToken token in tokenizer.tokens)
	{
		os << "type:\t" << int(token.type) << "\tvalue: " << token.value << endl;
	}

	return os;
}
