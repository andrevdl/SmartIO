#pragma once

enum class SIOTokenType
{
	// Parser flow
	EMPTY,	
	NESTED,
	SYMBOL,

	// Symbol types
	IDENTIFIER,
	VALUE,
	DSTRING, // double qouted string
	SSTRING, // single qouted string

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