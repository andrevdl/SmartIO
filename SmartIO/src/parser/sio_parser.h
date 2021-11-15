#pragma once

#include <string>

#include <parser/ast/sio_ast.h>
#include <parser/sio_program.h>
#include <parser/sio_tokenizer.h>
#include <parser/sio_token_walker.h>
#include <sio_context.h>

using namespace std;

class SIOParser
{
private:
	SIOTokenWalker walker;
public:
	SIOParser(SIOTokenizer* tokenizer);

	bool parse(SIOContext& ctx, string& error);
};