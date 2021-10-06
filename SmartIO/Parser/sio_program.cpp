#include "sio_program.h"

//bool SIONProgram::parse(SIOTokenWalker& walker)
//{
//	//SIONExpr* expr = nullptr;
//	SIONLogicExpr* expr = nullptr;
//
//	bool state = parse_node(walker, expr);
//	base = expr;
//
//	// hard coded for now !!!
//	return state;
//}

//ostream& operator<<(ostream& os, const SIONProgram& node)
//{
//	os << "digraph G {" << endl;
//	os << "root[shape = record label = \"root\"];" << endl;
//	node.print_dot_graph(os);
//	os << "}" << endl;
//
//	return os;
//}

bool create_parse_tree(SIOTokenWalker& walker, void* dest)
{
	return tree_parse_token(walker, tree_logic_expr_handler, dest);
}
