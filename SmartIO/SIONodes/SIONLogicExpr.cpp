#include "SIONLogicExpr.h"

bool SIONLogicExprExpr::create_expr(SIOTokenWalker& walker, SIONLogicExprExpr* node)
{
	return node->parse_node(walker, node->expr);
}

bool SIONLogicExprExpr::create_nested_expr(SIOTokenWalker& walker, SIONLogicExprExpr* node)
{
	return node->parse_node(walker, node->expr) && walker.pop_type() == SIOTokenType::RPAR;
}

bool SIONLogicExprExpr2::create_expr(SIOTokenWalker& walker, SIONLogicExprExpr2* node)
{
	return node->parse_node(walker, node->expr);
}

bool SIONLogicExprExpr2::create_not_expr(SIOTokenWalker& walker, SIONLogicExprExpr2* node)
{
	node->inverse = true;
	return node->parse_node(walker, node->expr);
}

bool SIONLogicExpr::create_expr(SIOTokenWalker& walker, SIONLogicExpr* node)
{
	return node->parse_node(walker, node->unit) && node->parse_node(walker, node->expr2);
}

bool SIONLogicExpr2::create_logic(SIOTokenWalker& walker, SIONLogicExpr2* node)
{
	return node->parse_node(walker, node->unit) && node->parse_node(walker, node->sub);
}

void SIONLogicExpr2::print_dot_graph_body(ostream& os) const
{
	if (get_type() == SIOTokenType::AND)
	{
		os << "&&";
	}
	else if (get_type() == SIOTokenType::OR)
	{
		os << "||";
	}
	else
	{
		os << "e";
	}
}

bool SIONCompareExpr::create_compare(SIOTokenWalker& walker, SIONCompareExpr* node)
{
	return node->parse_node(walker, node->expr) && node->parse_node(walker, node->compare2);
}

bool SIONCompareExpr2::create_compare(SIOTokenWalker& walker, SIONCompareExpr2* node)
{
	return node->parse_node(walker, node->expr) && node->parse_node(walker, node->sub);
}

void SIONCompareExpr2::print_dot_graph_body(ostream& os) const
{
	if (get_type() == SIOTokenType::LOGIC_EQUAL)
	{
		os << "==";
	}
	else if (get_type() == SIOTokenType::LOGIC_UNEQUAL)
	{
		os << "<>";
	}
	else
	{
		os << "e";
	}
}

bool SIONLogicExprUnit::create_unit(SIOTokenWalker& walker, SIONLogicExprUnit* node)
{
	return node->parse_node(walker, node->unit);
}

bool SIONLogicExprUnit::create_not_unit(SIOTokenWalker& walker, SIONLogicExprUnit* node)
{
	node->inverse = true;
	return node->parse_node(walker, node->unit);
}

bool SIONLogicExprUnit2::create_unit(SIOTokenWalker& walker, SIONLogicExprUnit2* node)
{
	return node->parse_node(walker, node->compare);
}

bool SIONLogicExprUnit2::create_nested_unit(SIOTokenWalker& walker, SIONLogicExprUnit2* node)
{
	return node->parse_node(walker, node->expr) && walker.pop_type() == SIOTokenType::RPAR && node->parse_node(walker, node->compare2);
}