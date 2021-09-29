#pragma once

#include "SIOCommon.h"
#include "SIOTokenizer.h"

class SIOTokenWalker
{
private:
	SIOTokenizer* tokenizer;

	vector<SIOToken*>::iterator begin;
	vector<SIOToken*>::iterator it;
	vector<SIOToken*>::iterator end;

	inline SIOToken* _pop();
	inline SIOToken* _peek();
public:
	SIOTokenWalker(SIOTokenizer* tokenizer);

	SIOToken* pop();
	SIOToken* peek();
	bool rollback();
	bool eof();

	SIOTokenType pop_type();
	SIOTokenType peek_type();
};