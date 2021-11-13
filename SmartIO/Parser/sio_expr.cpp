#include "sio_expr.h"

bool tree_expr(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_expr_term_handler, state) && tree_parse_token(ctx, walker, tree_expr2_handler, state);
}

bool tree_expr2_add(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstExpr* expr = new SIOAstExpr();
	expr->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_expr_term_handler, state))
	{
		expr->assign_right(last, state);
		state.store_node(expr, AstNodeType::EXPR);

		return tree_parse_token(ctx, walker, tree_expr2_handler, state);
	}
	return false;
}

bool tree_expr2_min(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstExpr* expr = new SIOAstExpr();
	expr->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_expr_term_handler, state))
	{
		expr->assign_right(last, state);
		state.store_node(expr, AstNodeType::EXPR);

		return tree_parse_token(ctx, walker, tree_expr2_handler, state);
	}
	return false;
}

bool tree_expr_term(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_expr_factor_handler, state) && tree_parse_token(ctx, walker, tree_expr_term2_handler, state);
}

bool tree_expr_term2_mul(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstExpr* expr = new SIOAstExpr();
	expr->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_expr_factor_handler, state))
	{
		expr->assign_right(last, state);
		state.store_node(expr, AstNodeType::EXPR);

		return tree_parse_token(ctx, walker, tree_expr_term2_handler, state);
	}
	return false;
}

bool tree_expr_term2_div(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstExpr* expr = new SIOAstExpr();
	expr->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_expr_factor_handler, state))
	{
		expr->assign_right(last, state);
		state.store_node(expr, AstNodeType::EXPR);

		return tree_parse_token(ctx, walker, tree_expr_term2_handler, state);
	}
	return false;
}

bool tree_expr_factor_nested(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_expr_handler, state) && walker.pop_type() == SIOTokenType::RPAR;
}

bool tree_expr_factor_val(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	//FINISH_TREE_NODE(node->parse_leaf(walker, node->symbol));

	SIOAstValue* val = new SIOAstValue();
	val->val = walker.pop()->value;

	state.store_node(val, AstNodeType::VALUE);
	return true;
}

bool tree_expr_factor_literal(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_id_handler, state);
}

bool tree_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	SIO_TREE_DEBUG_INFO("Expr", "");
	func = tree_expr;
	return true;
}

bool tree_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::ADD:
		SIO_TREE_DEBUG_INFO("ExprOp", "+");
		func = tree_expr2_add;
		eat = true;
		break;
	case SIOTokenType::MIN:
		SIO_TREE_DEBUG_INFO("ExprOp", "-");
		func = tree_expr2_min;
		eat = true;
		break;
	default:
		type = SIOTokenType::EMPTY;
	}
	return true;
}

bool tree_expr_term_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	SIO_TREE_DEBUG_INFO("ExprTerm", "");
	func = tree_expr_term;
	return true;
}

bool tree_expr_term2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::STAR:
		SIO_TREE_DEBUG_INFO("ExprTerm2", "*");
		func = tree_expr_term2_mul;
		eat = true;
		break;
	case SIOTokenType::SLASH:
		SIO_TREE_DEBUG_INFO("ExprTerm2", "/");
		func = tree_expr_term2_div;
		eat = true;
		break;
	default:
		type = SIOTokenType::EMPTY;
	}
	return true;
}

bool tree_expr_factor_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		SIO_TREE_DEBUG_INFO("ExprFactor", "Nested");
		eat = true;
		type = SIOTokenType::NESTED;
		func = tree_expr_factor_nested;
		return true;
	case SIOTokenType::VALUE:
		SIO_TREE_DEBUG_INFO("ExprFactor", "Value");
		type = SIOTokenType::SYMBOL;
		func = tree_expr_factor_val;
		return true;
	case SIOTokenType::IDENTIFIER:
		SIO_TREE_DEBUG_INFO("ExprFactor", "Literal");
		func = tree_expr_factor_literal;
		return true;
	default:
		return false;
	}
}