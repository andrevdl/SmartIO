#include "SIONExpr.h"

bool SIONExpr::create_expr(SIOTokenWalker& walker, SIONExpr* node)
{
	START_TREE_NODE("Expr", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->term) && node->parse_node(walker, node->expr2));
}

bool SIONExprTerm::create_term(SIOTokenWalker& walker, SIONExprTerm* node)
{
	START_TREE_NODE("Expr", "Term");
	FINISH_TREE_NODE(node->parse_node(walker, node->factor) && node->parse_node(walker, node->term2));
}

bool SIONExprFactor::create_factor_nested(SIOTokenWalker& walker, SIONExprFactor* node)
{
	START_TREE_NODE("Expr", "Nested");
	FINISH_TREE_NODE(node->parse_node(walker, node->expr) && walker.pop_type() == SIOTokenType::RPAR);
}

bool SIONExprFactor::create_factor_value(SIOTokenWalker& walker, SIONExprFactor* node)
{
	START_TREE_NODE("ExprFactor", "Value");
	FINISH_TREE_NODE(node->parse_leaf(walker, node->symbol));
}

bool SIONExprFactor::create_factor_id(SIOTokenWalker& walker, SIONExprFactor* node)
{
	START_TREE_NODE("ExprFactor", "ID");
	FINISH_TREE_NODE(node->parse_node(walker, node->id));
}

bool SIONExpr2::create_expr_add(SIOTokenWalker& walker, SIONExpr2* node)
{
	START_TREE_NODE("ExprOp", "+");
	FINISH_TREE_NODE(node->parse_node(walker, node->term) && node->parse_node(walker, node->expr2));
}

bool SIONExpr2::create_expr_min(SIOTokenWalker& walker, SIONExpr2* node)
{
	START_TREE_NODE("ExprOp", "-");
	FINISH_TREE_NODE(node->parse_node(walker, node->term) && node->parse_node(walker, node->expr2));
}

void SIONExpr2::print_dot_graph_body(ostream& os) const
{
	if (get_type() == SIOTokenType::ADD)
	{
		os << "+";
	}
	else if (get_type() == SIOTokenType::MIN)
	{
		os << "-";
	}
	else
	{
		os << "e";
	}
}

bool SIONExprTerm2::create_term_multi(SIOTokenWalker& walker, SIONExprTerm2* node)
{
	START_TREE_NODE("TermOp", "*");
	FINISH_TREE_NODE(node->parse_node(walker, node->factor) && node->parse_node(walker, node->term2));
}

bool SIONExprTerm2::create_term_divide(SIOTokenWalker& walker, SIONExprTerm2* node)
{
	START_TREE_NODE("TermOp", "/");
	FINISH_TREE_NODE(node->parse_node(walker, node->factor) && node->parse_node(walker, node->term2));
}

void SIONExprTerm2::print_dot_graph_body(ostream& os) const
{
	if (get_type() == SIOTokenType::STAR)
	{
		os << "*";
	}
	else if (get_type() == SIOTokenType::SLASH)
	{
		os << "/";
	}
	else
	{
		os << "e";
	}
}