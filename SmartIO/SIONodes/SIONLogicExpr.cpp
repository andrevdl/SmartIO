#include "SIONLogicExpr.h"

bool SIONLogicExprExpr::create_expr(SIOTokenWalker& walker, SIONLogicExprExpr* node)
{
	START_TREE_NODE("LogicExprExpr", "Expr");
	FINISH_TREE_NODE(node->parse_node(walker, node->expr));
}

bool SIONLogicExprExpr::create_nested_expr(SIOTokenWalker& walker, SIONLogicExprExpr* node)
{
	START_TREE_NODE("LogicExprExpr", "Nested");
	FINISH_TREE_NODE(node->parse_node(walker, node->expr) && walker.pop_type() == SIOTokenType::RPAR);
}

bool SIONLogicExprExpr2::create_expr(SIOTokenWalker& walker, SIONLogicExprExpr2* node)
{
	START_TREE_NODE("LogicExpr2", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->expr));
}

bool SIONLogicExprExpr2::create_not_expr(SIOTokenWalker& walker, SIONLogicExprExpr2* node)
{
	START_TREE_NODE("LogicExpr2", "Not");
	node->inverse = true;
	FINISH_TREE_NODE(node->parse_node(walker, node->expr));
}

bool SIONLogicExpr::create_expr(SIOTokenWalker& walker, SIONLogicExpr* node)
{
	START_TREE_NODE("LogicExpr", "Expr");
	FINISH_TREE_NODE(node->parse_node(walker, node->unit) && node->parse_node(walker, node->expr2));
}

bool SIONLogicExpr2::create_logic(SIOTokenWalker& walker, SIONLogicExpr2* node)
{
	START_TREE_NODE("LogicExpr", "Logic");
	FINISH_TREE_NODE(node->parse_node(walker, node->unit) && node->parse_node(walker, node->sub));
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
	START_TREE_NODE("Compare", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->expr) && node->parse_node(walker, node->compare2));
}

bool SIONCompareExpr2::create_compare(SIOTokenWalker& walker, SIONCompareExpr2* node)
{
	START_TREE_NODE("Compare2", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->expr) && node->parse_node(walker, node->sub));
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
	START_TREE_NODE("LogicExprUnit", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->unit));
}

bool SIONLogicExprUnit::create_not_unit(SIOTokenWalker& walker, SIONLogicExprUnit* node)
{
	START_TREE_NODE("LogicExprUnit", "Not");
	node->inverse = true;
	FINISH_TREE_NODE(node->parse_node(walker, node->unit));
}

bool SIONLogicExprUnit2::create_unit(SIOTokenWalker& walker, SIONLogicExprUnit2* node)
{
	START_TREE_NODE("LogicExprUnit2", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->compare));
}

bool SIONLogicExprUnit2::create_nested_unit(SIOTokenWalker& walker, SIONLogicExprUnit2* node)
{
	START_TREE_NODE("LogicExprUnit2", "Nested");
	FINISH_TREE_NODE(node->parse_node(walker, node->expr) && walker.pop_type() == SIOTokenType::RPAR && node->parse_node(walker, node->compare2));
}