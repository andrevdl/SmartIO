/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

enum class SIOTokenType
{
	EMPTY,

	// Symbol types
	IDENTIFIER,
	VALUE,
	DSTRING, // double qouted string
	SSTRING, // single qouted string
	DOUBLE,

	// Keywords
	IF,
	ELSE,
	WHILE,
	VAR,

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

	// IO
	IO_ADD,

	// Signs
	DOT,
	COMMA,
	COLON,
	DCOLON,
	SEMICOLON,
	LPAR,
	RPAR,
	LBR,
	RBR,
	LCURL,
	RCURL,
	SMALLER,
	LARGER,
	DOLLAR,
	BSLASH,
	HASH,

	// Logic operator
	AND, // &&
	OR, // ||
	MODULO, // %
	NOT, // !
	LOGIC_EQUAL,
	LOGIC_UNEQUAL,
	LOGIC_GREATER_EQUAL,
	LOGIC_SMALLER_EQUAL,

	// Arithmetic operator
	ADD,
	MIN,
	STAR,
	SLASH,

	// Assign
 	ASSIGN,// xxx
	ASSIGN_ADD,
	ASSIGN_MIN,
	ASSIGN_STAR,
	ASSIGN_SLASH,

	// Misc
	INC,
	DEC,
};

struct SIOToken
{
	SIOTokenType type;
	uint64_t value;
	
	int start_ln, start_col, end_ln, end_col;
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