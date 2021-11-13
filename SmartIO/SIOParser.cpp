#include "SIOParser.h"

// debug
#include "parser/sio_debug_win.h"

SIOParser::SIOParser(SIOTokenizer* tokenizer) : walker(tokenizer)
{
	
}

bool SIOParser::parse(SIOContext& ctx, string& error)
{
	//bool success = true;
	//SIONProgram* program = new SIONProgram(nullptr);

	//if (program->parse(walker))
	//{
	//	return program;
	//}

	AstNodeState* state = new AstNodeState();
	bool r = create_parse_tree(ctx, SIOTokenType::EMPTY, walker, *state);

	state->root_node->print(ctx.get_dot_ast_debugger());
	set_clipboard(ctx.get_dot_ast_debugger()->str());

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
