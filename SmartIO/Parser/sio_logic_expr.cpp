#include "sio_logic_expr.h"

bool tree_logic_expr(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_logic_expr_unit_handler, state)
		&& tree_parse_token(ctx, walker, tree_logic_expr2_handler, state);
}

bool tree_logic_expr2(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstLogic* logic = new SIOAstLogic();
	logic->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_logic_expr_unit_handler, state))
	{
		logic->assign_right(last, state);
		state.store_node(logic, AstNodeType::LOGIC_EXPR);

		return tree_parse_token(ctx, walker, tree_logic_expr2_handler, state);
	}
	return false;
}

bool tree_logic_compare(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_logic_expr_expr_handler, state)
		&& tree_parse_token(ctx, walker, tree_logic_compare2_handler, state);
}

bool tree_logic_compare2(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstLogicCompare* compare = new SIOAstLogicCompare();
	compare->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_logic_expr_expr_handler, state))
	{
		compare->assign_right(last, state);
		state.store_node(compare, AstNodeType::COMPARE_EXPR);

		return tree_parse_token(ctx, walker, tree_logic_compare2_handler, state);
	}
	return false;
}

bool tree_logic_unit(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_logic_expr_unit2_handler, state);
}

bool tree_logic_unit_not(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	if (tree_parse_token(ctx, walker, tree_logic_expr_unit2_handler, state))
	{
		state.curr_node->inverse = true;
		return true;
	}
	return false;
}

bool tree_logic_unit2(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_logic_compare_handler, state);
}

bool tree_logic_unit2_nested(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_logic_expr_handler, state)
		&& walker.pop_type() == SIOTokenType::RPAR && tree_parse_token(ctx, walker, tree_logic_compare2_handler, state);
}

bool tree_logic_expr_expr(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_logic_expr_expr2_handler, state);
}

bool tree_logic_expr_expr_nested(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_logic_expr_expr2_handler, state) && walker.pop_type() == SIOTokenType::RPAR;
}

bool tree_logic_expr_expr2(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_expr_handler, state);
}

bool tree_logic_expr_expr2_not(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	if (tree_parse_token(ctx, walker, tree_expr_handler, state))
	{
		state.curr_node->inverse = true;
		return true;
	}
	return false;
}

bool tree_logic_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	SIO_TREE_DEBUG_INFO("LogicExpr", "Expr");
	func = tree_logic_expr;
	return true;
}

bool tree_logic_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	if (is_logic_op(type))
	{
		SIO_TREE_DEBUG_INFO("LogicExpr2", "Logic");
		func = tree_logic_expr2;
		eat = true;
	}
	else
	{
		type = SIOTokenType::EMPTY;
	}

	return true;
}

bool tree_logic_compare_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	SIO_TREE_DEBUG_INFO("Compare", "");
	func = tree_logic_compare;
	return true;
}

bool tree_logic_compare2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	if (is_comp_op(type))
	{
		SIO_TREE_DEBUG_INFO("Compare2", "");
		func = tree_logic_compare2;
		eat = true;
	}
	else
	{
		type = SIOTokenType::EMPTY;
	}

	return true;
}

bool tree_logic_expr_unit_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::NOT:
		SIO_TREE_DEBUG_INFO("LogicExprUnit", "Not");
		eat = true;
		func = tree_logic_unit_not;
		return true;
	default:
		SIO_TREE_DEBUG_INFO("LogicExprUnit", "");
		func = tree_logic_unit;
		return true;
	}
}

bool tree_logic_expr_unit2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		SIO_TREE_DEBUG_INFO("LogicExprUnit2", "Nested");
		eat = true;
		type = SIOTokenType::NESTED;
		func = tree_logic_unit2_nested;
		return true;
	default:
		SIO_TREE_DEBUG_INFO("LogicExprUnit2", "");
		func = tree_logic_unit2;
		return true;
	}
}

bool tree_logic_expr_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		SIO_TREE_DEBUG_INFO("LogicExprExpr", "Nested");
		eat = true;
		type = SIOTokenType::NESTED;
		func = tree_logic_expr_expr_nested;
		return true;
	default:
		SIO_TREE_DEBUG_INFO("LogicExprExpr", "Expr");
		func = tree_logic_expr_expr;
		return true;
	}
}

bool tree_logic_expr_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	if (type == SIOTokenType::NOT)
	{
		SIO_TREE_DEBUG_INFO("LogicExprExpr2", "Not");
		eat = true;
		func = tree_logic_expr_expr2_not;
		return true;
	}

	SIO_TREE_DEBUG_INFO("LogicExprExpr2", "");
	func = tree_logic_expr_expr2;
	return true;
}