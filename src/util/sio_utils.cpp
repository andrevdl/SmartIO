#include "sio_utils.h"

uint64_t str2int64(const char* str, int64_t def)
{
	int64_t val;
	return try_str2int64(str, val) ? val : def;
}

bool try_str2int64(const char* str, int64_t& val)
{
	errno = 0;
	char* end = 0;

	val = strtoll(str, &end, 10);
	return errno == 0 && *end == 0;
}

uint64_t str2uint64(const char* str, uint64_t def)
{
	uint64_t val;
	return try_str2uint64(str, val) ? val : def;
}

bool try_str2uint64(const char* str, uint64_t& val)
{
	errno = 0;
	char* end = 0;

	val = strtoull(str, &end, 10);
	return errno == 0 && *end == 0;
}

uint32_t str2int32(const char* str, int32_t def)
{
	int32_t val;
	return try_str2int32(str, val) ? val : def;
}

bool try_str2int32(const char* str, int32_t& val)
{
	errno = 0;
	char* end = 0;

	val = strtol(str, &end, 10);
	return errno == 0 && *end == 0;
}

uint32_t str2uint32(const char* str, uint32_t def)
{
	uint32_t val;
	return try_str2uint32(str, val) ? val : def;
}

bool try_str2uint32(const char* str, uint32_t& val)
{
	errno = 0;
	char* end = 0;

	val = strtoul(str, &end, 10);
	return errno == 0 && *end == 0;
}

float str2float(const char* str, float def)
{
	float val;
	return try_str2float(str, val) ? val : def;
}

bool try_str2float(const char* str, float& val)
{
	errno = 0;
	char* end = 0;

	val = strtof(str, &end);
	return errno == 0 && *end == 0;
}

bool str2bool(const char* str, bool def)
{
	bool val;
	return try_str2bool(str, val) ? val : def;
}

bool try_str2bool(const char* str, bool& val)
{
	size_t len = strlen(str);
	if (len == 1)
	{
		if (str[0] == 'y' || str[0] == 'Y' || str[0] == '1')
		{
			val = true;
			return true;
		} 
		else if (str[0] == 'n' || str[0] == 'N' || str[0] == '0')
		{
			val = false;
			return true;
		}

		return false;
	}
	else if (len == 4 && (str[0] == 'T' || str[0] == 't') && (str[1] == 'R' || str[1] == 'r') && (str[2] == 'U' || str[2] == 'u') && (str[3] == 'E' || str[3] == 'e')) // true
	{
		val = true;
		return true;
	}
	else if (len == 5 && (str[0] == 'F' || str[0] == 'f') && (str[1] == 'A' || str[1] == 'a') && (str[2] == 'L' || str[2] == 'l') && (str[3] == 'S' || str[3] == 's') && (str[4] == 'E' || str[4] == 'e')) // false
	{
		val = false;
		return true;
	}
	else if (len == 2 && (str[0] == 'N' || str[0] == 'n') && (str[1] == 'O' || str[1] == 'o')) // no
	{
		val = false;
		return true;
	}
	else if (len == 3 && (str[0] == 'Y' || str[0] == 'y') && (str[1] == 'E' || str[1] == 'e') && (str[2] == 'S' || str[2] == 's')) // yes
	{
		val = true;
		return true;
	}

	return false;
}