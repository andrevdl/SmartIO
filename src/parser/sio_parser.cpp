/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "sio_parser.h"

// debug
#include "sio_debug_win.h"

SIOParser::SIOParser(SIOTokenizer* tokenizer, SIOLogger* logger) : walker(tokenizer), logger(logger)
{
	
}

bool SIOParser::parse(SIOContext* ctx)
{
	//bool success = true;
	//SIONProgram* program = new SIONProgram(nullptr);

	//if (program->parse(walker))
	//{
	//	return program;
	//}

	AstNodeState* state = new AstNodeState();
	bool r = tree_parse_token(*ctx, walker, tree_expr_handler, *state);

	if (state->root_node != nullptr)
	{
		state->root_node->print(ctx->get_dot_ast_debugger(), ctx);
		set_clipboard(ctx->get_dot_ast_debugger()->str());
	}

	return r;

	//RET_DELETE_AND_NULL(program);
}

//void SIOParser::print(SIOBaseNode* node)
//{
//	cout << "digraph G {" << endl;
//	cout << "root[shape = record label = \"root\"];" << endl;
//	cout << *node;
//	cout << "}" << endl;
//}
