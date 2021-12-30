/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <unordered_map>
#include <string>
#include <debugger/sio_dot_debugger.h>

#include <sio_data.h>

using namespace std;

class SIOContext
{
private:
#ifdef SIO_DEBUG
	SIODotDebugger* dot_tree_debugger;
#endif // SIO_DEBUG
#ifdef SIO_AST_DEBUG_CAP
	SIODotDebugger* dot_ast_debugger;
#endif // SIO_AST_DEBUG_CAP

	// Translates string in code to int reference 
	unordered_map<string, SIODataRef*> refs;
	vector<string> strings;
	vector<SIOData> consts;

	unordered_map<string, SIODataRef*>::iterator find(string str);

	bool is_valid_str_index(size_t index);
public:
	SIOContext();
	~SIOContext();

	SIODataRef* store_str(string str);
	bool load_str(uintptr_t ptr, string& str);
	bool load_str(SIOData& data, string& str);

	const char* load_str_as_c_char(SIOData& data);

	bool store_const(string str, SIOData data);
	bool store_str_const(string str, char flags, string val);
	bool load_const(string str, SIOData& data);
	bool load_const(uint64_t& i, SIOData& data);
	bool load_const_ref(string str, SIODataRef* ref);

	SIODataRef* str_token_translate(string str, SIODataType& type);
	bool allowed_as_literal(string str);
	bool is_data_marker(string str);

	void optimize();

	void store_parse_err(string err) {}; // placeholder for now => add position info ...

#ifdef SIO_DEBUG
	SIODotDebugger* get_dot_tree_debugger();
#endif // SIO_DEBUG
#ifdef SIO_AST_DEBUG_CAP
	SIODotDebugger* get_dot_ast_debugger();
#endif // SIO_DEBUG
};