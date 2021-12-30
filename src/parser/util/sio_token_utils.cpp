#include "sio_token_utils.h"

char const* sio_token_type2str(SIOTokenType type)
{
	return sio_token_name[static_cast<int>(type)];
}

string create_expected_msg(SIOTokenType expected, SIOTokenType found)
{
	if (expected != SIOTokenType::EMPTY)
	{
		if (found == SIOTokenType::EMPTY)
		{
			return fmt::format(ERROR_EXPECTED_TOKEN_EOF, expected);
		}

		return fmt::format(ERROR_EXPECTED_TOKEN, expected, found);
	}

	return ERROR_EOF_EXPECTED;
}

string create_expected_msg(vector<SIOTokenType> expected, SIOTokenType found)
{
	if (expected.size() > 0)
	{
		if (expected.size() < 2)
		{
			return create_expected_msg(expected[0], found);
		}

		if (found == SIOTokenType::EMPTY)
		{
			return fmt::format(ERROR_EXPECTED_TOKENS_EOF, expected);
		}

		return fmt::format(ERROR_EXPECTED_TOKENS, expected, found);
	}

	return ERROR_EOF_EXPECTED;
}
