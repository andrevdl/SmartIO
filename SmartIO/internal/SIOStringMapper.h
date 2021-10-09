#pragma once

#include <unordered_map>
#include <vector>

//#include "SIOCommon.h"
//
//class SIOStringMapper
//{
//private:
//	unordered_map<string, uint64_t> refs;
//	vector<string> strings;
//
//	unordered_map<string, uint64_t>::const_iterator find(string str);
//public:
//	static SIOStringMapper* global_mapper(); // temp -> make later part of the compiler
//
//	uint64_t store_str(string str);
//	bool load_str(uint64_t& i, string& str);
//};