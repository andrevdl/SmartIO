#include "SIOStringMapper.h"

//unordered_map<string, uint64_t>::const_iterator SIOStringMapper::find(string str)
//{
//	return refs.find(str);
//}
//
//SIOStringMapper* SIOStringMapper::global_mapper()
//{
//	static SIOStringMapper* mapper = new SIOStringMapper();
//	return mapper;
//}
//
//uint64_t SIOStringMapper::store_str(string str)
//{
//	auto got = find(str);
//	if (got != refs.end())
//	{
//		return got->second;
//	}
//
//	strings.push_back(str);
//	uint64_t pos = strings.size() - 1;
//
//	refs.insert(make_pair(str, pos));
//	return pos;
//}
//
//bool SIOStringMapper::load_str(uint64_t& i, string& str)
//{
//	if (i >= 0 && i < strings.size())
//	{
//		str = strings[i];
//		return true;
//	}
//
//	return false;
//}
