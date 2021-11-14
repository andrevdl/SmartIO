#pragma once

#include <string>

#include "ast/sio_ast.h"
#include "sio_program.h"
#include "SIOTokenizer.h"
#include "SIOTokenWalker.h"
#include "../internal/sio_context.h"

using namespace std;

class SIOParser
{
private:
	SIOTokenWalker walker;
public:
	SIOParser(SIOTokenizer* tokenizer);

	bool parse(SIOContext& ctx, string& error);
};