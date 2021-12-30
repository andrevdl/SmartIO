/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "sio_context.h"

unordered_map<string, SIODataRef*>::iterator SIOContext::find(string str)
{
	return refs.find(str);
}

bool SIOContext::is_valid_str_index(size_t index)
{
	return index >= 0 && index < strings.size();
}

SIOContext::SIOContext(SIOLogger* logger)
{
	this->logger = logger;
#ifdef SIO_DEBUG
	dot_tree_debugger = new SIODotDebugger();
#endif
#ifdef SIO_AST_DEBUG_CAP
	dot_ast_debugger = new SIODotDebugger();
#endif;

	// lets at compiler literals
	store_const("void", define_data_val(SIODataType::VOID, SIO_DATA_MARKER, 0));
	store_const("char", define_data_val(SIODataType::INTEGER, SIO_DATA_MARKER, 0));
	store_const("int", define_data_val(SIODataType::INTEGER, SIO_DATA_MARKER, 0));
	store_const("double", define_data_val(SIODataType::DOUBLE, SIO_DATA_MARKER, 0));
	store_const("string", define_data_val(SIODataType::STRING, SIO_DATA_MARKER, 0));
	store_const("bool", define_data_val(SIODataType::INTEGER, SIO_DATA_MARKER, 0));
	//store_const("date", define_data_val(SIODataType::DOUBLE, SIO_DATA_BUILDIN, 0)); // Delphi style or unix style
	//store_const("time", define_data_val(SIODataType::DOUBLE, SIO_DATA_BUILDIN, 0)); // Delphi style or unix style
	//store_const("datetime", define_data_val(SIODataType::DOUBLE, SIO_DATA_BUILDIN, 0)); // Delphi style or unix style

	// The tokenizer will resolve them -> precompiler
	store_const("null", define_data_val(SIODataType::INTEGER, SIO_DATA_CONST, 0));
	store_const("false", define_data_val(SIODataType::INTEGER, SIO_DATA_CONST, 0));
	store_const("true", define_data_val(SIODataType::INTEGER, SIO_DATA_CONST, 1));

	store_str_const("__sio_runtime_version_name", 0, RUNTIME_VERSION_NAME);
	store_str_const("__sio_lang_version_name", 0, LANG_VERSION_NAME);	
}

SIOContext::~SIOContext()
{
#ifdef SIO_DEBUG
	delete dot_tree_debugger;
#endif
#ifdef SIO_AST_DEBUG_CAP
	delete dot_ast_debugger;
#endif;

	// todo: destroy unordered_map -> refs
}

SIOLogger* SIOContext::get_logger()
{
	return logger;
}

SIODataRef* SIOContext::store_str(string str)
{
	auto got = find(str);
	if (got != refs.end())
	{
		got->second->ref_count++;
		return got->second;
	}

	strings.push_back(str);

	SIODataRef* ref = new SIODataRef{ SIODataRef::Type::STRING, strings.size() - 1, 1 };
	refs.insert(make_pair(str, ref));

	return ref;
}

bool SIOContext::load_str(uintptr_t ptr, string& str)
{
	uint64_t ref = get_ref(ptr);
	if (is_valid_str_index(ref))
	{
		str = strings[ref];
		return true;
	}

	return false;
}

bool SIOContext::load_str(SIOData& data, string& str)
{
	uint64_t ref = get_ref(data);
	if (is_valid_str_index(ref))
	{
		str = strings[ref];
		return true;
	}

	return false;
}

const char* SIOContext::load_str_as_c_char(SIOData& data)
{
	uint64_t ref = get_ref(data);
	if (is_valid_str_index(ref))
	{
		return strings[ref].c_str();
	}
	return nullptr;
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

	refs.insert(make_pair(str, new SIODataRef{ SIODataRef::Type::LITERAL, pos, 1 }));
	return true;
}

bool SIOContext::store_str_const(string str, char flags, string val)
{
	flags |= SIO_DATA_CONST;
	return store_const(str, define_data_ptr(SIODataType::STRING, flags, (uintptr_t)store_str(val)));
}

bool SIOContext::load_const(string str, SIOData& data)
{
	SIODataRef* ref = nullptr;
	if (load_const_ref(str, ref) && ref != nullptr)
	{
		return load_const(ref->ref, data);
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

bool SIOContext::load_const_ref(string str, SIODataRef* ref)
{
	auto got = find(str);
	if (got != refs.end())
	{
		ref = got->second;
		return true;
	}

	return false;
}

SIODataRef* SIOContext::str_token_translate(string str, SIODataType& type)
{
	SIOData data;
	SIODataRef* ref = nullptr;

	if (load_const_ref(str, ref) && ref != nullptr && load_const(ref->ref, data))
	{
		if (BIT_NOT_SET(data.flags, SIO_DATA_MARKER))
		{
			type = data.datatype;
			return ref;

		}
	}

	type = SIODataType::STRING;
	return store_str(str);
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

void SIOContext::optimize()
{
	// todo: remove all records with ref_count 0
	// alter all datarefs to the correct item
	// by reverse lookup
}

#ifdef SIO_DEBUG
SIODotDebugger* SIOContext::get_dot_tree_debugger()
{
	return dot_tree_debugger;
}
#endif
#ifdef SIO_AST_DEBUG_CAP
SIODotDebugger* SIOContext::get_dot_ast_debugger()
{
	return dot_ast_debugger;
}
#endif