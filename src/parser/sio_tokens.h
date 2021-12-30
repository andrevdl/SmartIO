/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <sio_code_insight.h>

enum class SIOTokenCategory
{
	OTHER,
	SYNTAX,
	EXPR,
	ARITH,
	VALUE,
	FLOW,
	DECL,
	ASSIGN,
	IO_OUTPUT,
};

#define SIO_TOKENS \
X(EMPTY, "Empty", SIOTokenCategory::OTHER) \
X(IDENTIFIER, "IDENTIFIER", SIOTokenCategory::VALUE) \
X(VALUE, "VALUE", SIOTokenCategory::VALUE) \
X(DSTRING, "DSTRING", SIOTokenCategory::VALUE) \
X(SSTRING, "SSTRING", SIOTokenCategory::VALUE) \
X(DOUBLE, "DOUBLE", SIOTokenCategory::VALUE) \
X(IF, "IF", SIOTokenCategory::FLOW) \
X(ELSE, "ELSE", SIOTokenCategory::FLOW) \
X(WHILE, "WHILE", SIOTokenCategory::FLOW) \
X(VAR, "VAR", SIOTokenCategory::DECL) \
X(IO_ADD, "IO_ADD", SIOTokenCategory::IO_OUTPUT) \
X(DOT, "'.'", SIOTokenCategory::SYNTAX) \
X(COMMA, "','", SIOTokenCategory::SYNTAX) \
X(COLON, "':'", SIOTokenCategory::SYNTAX) \
X(DCOLON, "'::'", SIOTokenCategory::SYNTAX) \
X(SEMICOLON, "';'", SIOTokenCategory::SYNTAX) \
X(LPAR, "'('", SIOTokenCategory::SYNTAX) \
X(RPAR, "')'", SIOTokenCategory::SYNTAX) \
X(LBR, "'['", SIOTokenCategory::SYNTAX) \
X(RBR, "']'", SIOTokenCategory::SYNTAX) \
X(LCURL, "'{'", SIOTokenCategory::SYNTAX) \
X(RCURL, "'}'", SIOTokenCategory::SYNTAX) \
X(SMALLER, "'<'", SIOTokenCategory::EXPR) \
X(LARGER, "'>'", SIOTokenCategory::EXPR) \
X(DOLLAR, "'$'", SIOTokenCategory::EXPR) \
X(BSLASH, "'\'", SIOTokenCategory::SYNTAX) \
X(HASH, "'#'", SIOTokenCategory::SYNTAX) \
X(AND, "'&&'", SIOTokenCategory::EXPR) \
X(OR, "'||'", SIOTokenCategory::EXPR) \
X(MODULO, "'%'", SIOTokenCategory::EXPR) \
X(NOT, "'!'", SIOTokenCategory::EXPR) \
X(LOGIC_EQUAL, "'=='", SIOTokenCategory::EXPR) \
X(LOGIC_UNEQUAL, "'<>'", SIOTokenCategory::EXPR) \
X(LOGIC_GREATER_EQUAL, "'>='", SIOTokenCategory::EXPR) \
X(LOGIC_SMALLER_EQUAL, "'<='", SIOTokenCategory::EXPR) \
X(ADD, "'+'", SIOTokenCategory::ARITH) \
X(MIN, "'-'", SIOTokenCategory::ARITH) \
X(STAR, "'*'", SIOTokenCategory::ARITH) \
X(SLASH, "'/'", SIOTokenCategory::ARITH) \
X(ASSIGN, "'='", SIOTokenCategory::ASSIGN) \
X(ASSIGN_ADD, "'+='", SIOTokenCategory::ASSIGN) \
X(ASSIGN_MIN, "'-='", SIOTokenCategory::ASSIGN) \
X(ASSIGN_STAR, "'*='", SIOTokenCategory::ASSIGN) \
X(ASSIGN_SLASH, "'/='", SIOTokenCategory::ASSIGN) \
X(INC, "'++'", SIOTokenCategory::ARITH) \
X(DEC, "'--'", SIOTokenCategory::ARITH)

#define X(e, name, cat) e,
enum class SIOTokenType
{
	SIO_TOKENS
};
#undef X

#define X(e, name, cat) name,
static char const* sio_token_name[] =
{
	SIO_TOKENS
};
#undef X

#define X(e, name, cat) cat,
static SIOTokenCategory sio_token_category[]
{
	SIO_TOKENS
};
#undef X

// update
// block
// looping... while, for ...
// case
// func
// iter
// config
// proc
// import, use
// define -> datasource/io

struct SIOToken
{
	SIOTokenType type;
	uint64_t value;
	SIOLineInfoRange code_range;
};

//inline const char* token_type_str(const SIOTokenType& type)
//{
//	switch (type)
//	{
//	case SIOTokenType::EMPTY:
//		return "empty";
//	case SIOTokenType::NESTED:
//		return "nested";
//	case SIOTokenType::SYMBOL:
//		return "symbol";
//	case SIOTokenType::CALL:
//		return "function";
//	case SIOTokenType::ARRAY:
//		return "array";
//	case SIOTokenType::IDENTIFIER:
//		return "identifier";
//	case SIOTokenType::VALUE:
//		return "value";
//	case SIOTokenType::DSTRING:
//		return "dstring";
//	case SIOTokenType::SSTRING:
//		return "sstring";
//	default:
//		return "";
//	}
//}