#include "sio_context.h"

unordered_map<string, SIODataRef>::const_iterator SIOContext::find(string str)
{
	return refs.find(str);
}

SIOContext::SIOContext()
{
	// lets at compiler literals
	store_const("void", define_data(SIODataType::VOID, SIO_DATA_MARKER, 0));
	store_const("char", define_data(SIODataType::INTEGER, SIO_DATA_MARKER, 0));
	store_const("int", define_data(SIODataType::INTEGER, SIO_DATA_MARKER, 0));
	store_const("double", define_data(SIODataType::DOUBLE, SIO_DATA_MARKER, 0));
	store_const("string", define_data(SIODataType::STRING, SIO_DATA_MARKER, 0));
	store_const("bool", define_data(SIODataType::INTEGER, SIO_DATA_MARKER, 0));
	//store_const("date", define_data(SIODataType::DOUBLE, SIO_DATA_BUILDIN, 0)); // Delphi style or unix style
	//store_const("time", define_data(SIODataType::DOUBLE, SIO_DATA_BUILDIN, 0)); // Delphi style or unix style
	//store_const("datetime", define_data(SIODataType::DOUBLE, SIO_DATA_BUILDIN, 0)); // Delphi style or unix style

	// The tokenizer will resolve them -> precompiler
	store_const("null", define_data(SIODataType::INTEGER, SIO_DATA_CONST, 0));
	store_const("false", define_data(SIODataType::INTEGER, SIO_DATA_CONST, 0));
	store_const("true", define_data(SIODataType::INTEGER, SIO_DATA_CONST, 1));

	store_const("__sio_lang_version_name", define_data(SIODataType::INTEGER, SIO_DATA_CONST, 1));
}

uint64_t SIOContext::store_str(string str)
{
	auto got = find(str);
	if (got != refs.end())
	{
		return got->second.ref;
	}

	strings.push_back(str);
	uint64_t pos = strings.size() - 1;

	refs.insert(make_pair(str, SIODataRef{ SIODataRef::Type::STRING, pos }));
	return pos;
}

bool SIOContext::load_str(uint64_t& i, string& str)
{
	if (i >= 0 && i < strings.size())
	{
		str = strings[i];
		return true;
	}

	return false;
}

bool SIOContext::store_const(string str, SIOData data)
{
	if (data.datatype <= SIODataType::COMPLEX && BIT_NOT_SET(data.flags, SIO_DATA_MARKER))
	{
		return false;
	}

	auto got = find(str);
	if (got != refs.end())
	{
		return false;
	}

	consts.push_back(data);
	uint64_t pos = consts.size() - 1;

	refs.insert(make_pair(str, SIODataRef{ SIODataRef::Type::LITERAL, pos }));
	return true;
}

bool SIOContext::load_const(string str, SIOData& data)
{
	auto got = find(str);
	if (got != refs.end())
	{
		uint64_t ref = got->second.ref;
		return load_const(ref, data);
	}
	return false;
}

bool SIOContext::load_const(uint64_t& i, SIOData& data)
{
	if (i >= 0 && i < consts.size())
	{
		data = consts[i];
		return true;
	}
	return false;
}

SIODataRef SIOContext::str_token_translate(string str, SIODataType& type)
{
	SIOData data;
	if (load_const(str, data)) 
	{
		if (BIT_NOT_SET(data.flags, SIO_DATA_MARKER))
		{
			type = data.datatype;
			return { SIODataRef::Type::LITERAL, data.value };
		}
	}

	type = SIODataType::STRING;
	return { SIODataRef::Type::STRING, store_str(str) };
}

bool SIOContext::allowed_as_literal(string str)
{
	return !is_data_marker(str);
}

bool SIOContext::is_data_marker(string str)
{
	SIOData data;
	return load_const(str, data) && BIT_NOT_SET(data.flags, SIO_DATA_MARKER);
}