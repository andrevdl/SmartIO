#include "SIONProgram.h"

bool SIONProgram::parse(SIOTokenWalker& walker)
{
	SIONExpr* expr = nullptr;//new SIONExpr(parent);

	bool state = parse_node(walker, expr);
	base = expr;

	// hard coded for now !!!
	return state;
}

ostream& operator<<(ostream& os, const SIONProgram& node)
{
	os << "digraph G {" << endl;
	os << "root[shape = record label = \"root\"];" << endl;
	node.print_dot_graph(os);
	os << "}" << endl;

	return os;
}
