#pragma once

#include <unordered_map>
#include <string>

#include "sio_data.h"

using namespace std;

struct SIODataRef
{
	enum class Type {
		STRING,
		LITERAL,
	} type;
	uint64_t ref;
};

class SIOContext
{
private:
	// Translates string in code to int reference 
	unordered_map<string, SIODataRef> refs;
	vector<string> strings;
	vector<SIOData> consts;

	unordered_map<string, SIODataRef>::const_iterator find(string str);
public:
	SIOContext();

	uint64_t store_str(string str);
	bool load_str(uint64_t& i, string& str);

	bool store_const(string str, SIOData data);
	bool load_const(string str, SIOData& data);
	bool load_const(uint64_t& i, SIOData& data);

	SIODataRef str_token_translate(string str, SIODataType& type);
	bool allowed_as_literal(string str);
	bool is_data_marker(string str);
};