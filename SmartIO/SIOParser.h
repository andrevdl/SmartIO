#pragma once

#include "SIOCommon.h"
#include "SIONodes/SIONProgram.h"
#include "SIOTokenizer.h"
#include "SIOTokenWalker.h"

class SIOParser
{
private:
	SIOTokenWalker walker;
public:
	SIOParser(SIOTokenizer* tokenizer);

	SIONProgram* parse(string& error);
};