#pragma once

#include <stdint.h>
#include <stdlib.h>

uint64_t str2int64(const char* str, uint64_t def = 0);
bool try_str2int64(const char* str, uint64_t& val);

uint64_t str2uint64(const char* str, uint64_t def = 0);
bool try_str2uint64(const char* str, uint64_t& val);