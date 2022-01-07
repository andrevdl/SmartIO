#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint64_t str2int64(const char* str, uint64_t def = 0);
bool try_str2int64(const char* str, uint64_t& val);

uint64_t str2uint64(const char* str, uint64_t def = 0);
bool try_str2uint64(const char* str, uint64_t& val);

bool str2bool(const char* str, bool def = false);
bool try_str2bool(const char* str, bool& val);