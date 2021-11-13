#pragma once

#include "internal/sio_data.h"

enum class SIOTokenType
{
	// Parser flow
	EMPTY,	
	NESTED,
	SYMBOL,
	CALL,
	ARRAY,

	// Symbol types
	IDENTIFIER,
	VALUE,
	DSTRING, // double qouted string
	SSTRING, // single qouted string
	DOUBLE,

	// Keywords
	IF,
	ELSE,
	VAR,

	// true, false, null

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
};

inline const char* token_type_str(const SIOTokenType& type)
{
	switch (type)
	{
	case SIOTokenType::EMPTY:
		return "empty";
	case SIOTokenType::NESTED:
		return "nested";
	case SIOTokenType::SYMBOL:
		return "symbol";
	case SIOTokenType::CALL:
		return "function";
	case SIOTokenType::ARRAY:
		return "array";
	case SIOTokenType::IDENTIFIER:
		return "identifier";
	case SIOTokenType::VALUE:
		return "value";
	case SIOTokenType::DSTRING:
		return "dstring";
	case SIOTokenType::SSTRING:
		return "sstring";
	default:
		return "";
	}
}

inline const bool is_comp_op(const SIOTokenType& type)
{
	return type == SIOTokenType::LOGIC_EQUAL ||
		type == SIOTokenType::LOGIC_UNEQUAL ||
		type == SIOTokenType::LOGIC_GREATER_EQUAL ||
		type == SIOTokenType::LOGIC_SMALLER_EQUAL;
}

inline const bool is_logic_op(const SIOTokenType& type)
{
	return type == SIOTokenType::AND || type == SIOTokenType::OR;
}

inline const bool translate_literal_to_token(const SIODataType type, SIOTokenType& token_type)
{
	switch (type)
	{
	case SIODataType::INTEGER:
		token_type = SIOTokenType::VALUE;
		return true;
	case SIODataType::STRING:
		token_type = SIOTokenType::DSTRING;
		return true;
	case SIODataType::DOUBLE:
		token_type = SIOTokenType::DOUBLE;
		return true;
	}

	return false;
}