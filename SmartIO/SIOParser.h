#pragma once

#include "SIOCommon.h"
#include "Parser/sio_program.h"
#include "SIOTokenizer.h"
#include "SIOTokenWalker.h"

class SIOParser
{
private:
	SIOTokenWalker walker;
public:
	SIOParser(SIOTokenizer* tokenizer);

	bool parse(string& error);
};