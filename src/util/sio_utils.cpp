#include "sio_utils.h"

uint64_t str2int64(const char* str, uint64_t def)
{
	uint64_t val;
	return try_str2int64(str, val) ? val : def;
}

bool try_str2int64(const char* str, uint64_t& val)
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