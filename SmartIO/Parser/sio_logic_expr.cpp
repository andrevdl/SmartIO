#include "sio_logic_expr.h"

bool tree_logic_expr(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExpr", "Expr");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_expr_unit_handler, dest) 
		&& tree_parse_token(walker, tree_logic_expr2_handler, dest));
}

bool tree_logic_expr2(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExpr", "Logic");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_expr_unit_handler, dest)
		&& tree_parse_token(walker, tree_logic_expr2_handler, dest));
}

bool tree_logic_compare(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("Compare", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_expr_expr_handler, dest)
		&& tree_parse_token(walker, tree_logic_compare2_handler, dest));
}

bool tree_logic_compare2(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("Compare2", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_expr_expr_handler, dest)
		&& tree_parse_token(walker, tree_logic_compare2_handler, dest));
}

bool tree_logic_unit(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExprUnit", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_expr_unit2_handler, dest));
}

bool tree_logic_unit_not(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExprUnit", "Not");
	//node->inverse = true;
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_expr_unit2_handler, dest));
}

bool tree_logic_unit2(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExprUnit2", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_compare_handler, dest));
}

bool tree_logic_unit2_nested(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExprUnit2", "Nested");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_expr_handler, dest)
		&& walker.pop_type() == SIOTokenType::RPAR && tree_parse_token(walker, tree_logic_compare2_handler, dest));
}

bool tree_logic_expr_expr(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExprExpr", "Expr");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_expr_expr2_handler, dest));
}

bool tree_logic_expr_expr_nested(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExprExpr", "Nested");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_logic_expr_expr2_handler, dest) && walker.pop_type() == SIOTokenType::RPAR);
}

bool tree_logic_expr_expr2(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExpr2", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_expr_handler, dest));
}

bool tree_logic_expr_expr2_not(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("LogicExpr2", "Not");
	//node->inverse = true;
	FINISH_TREE_NODE(tree_parse_token(walker, tree_expr_handler, dest));
}

bool tree_logic_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	func = tree_logic_expr;
	return true;
}

bool tree_logic_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	if (is_logic_op(type))
	{
		func = tree_logic_expr2;
		eat = true;
	}
	else
	{
		type = SIOTokenType::EMPTY;
	}

	return true;
}

bool tree_logic_compare_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	func = tree_logic_compare;
	return true;
}

bool tree_logic_compare2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	if (is_comp_op(type))
	{
		func = tree_logic_compare2;
		eat = true;
	}
	else
	{
		type = SIOTokenType::EMPTY;
	}

	return true;
}

bool tree_logic_expr_unit_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	switch (type)
	{
	case SIOTokenType::NOT:
		eat = true;
		func = tree_logic_unit_not;
		return true;
	default:
		func = tree_logic_unit;
		return true;
	}
}

bool tree_logic_expr_unit2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		eat = true;
		type = SIOTokenType::NESTED;
		func = tree_logic_unit2_nested;
		return true;
	default:
		func = tree_logic_unit2;
		return true;
	}
}

bool tree_logic_expr_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		eat = true;
		type = SIOTokenType::NESTED;
		func = tree_logic_expr_expr_nested;
		return true;
	default:
		func = tree_logic_expr_expr;
		return true;
	}
}

bool tree_logic_expr_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	if (type == SIOTokenType::NOT)
	{
		eat = true;
		func = tree_logic_expr_expr2_not;
		return true;
	}

	func = tree_logic_expr_expr2;
	return true;
}