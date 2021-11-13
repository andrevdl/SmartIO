#pragma once

#include "SIOCommon.h"
#include "parser/ast/sio_ast.h"
#include "Parser/sio_program.h"
#include "SIOTokenizer.h"
#include "SIOTokenWalker.h"
#include "internal/sio_context.h"

class SIOParser
{
private:
	SIOTokenWalker walker;
public:
	SIOParser(SIOTokenizer* tokenizer);

	bool parse(SIOContext& ctx, string& error);
};