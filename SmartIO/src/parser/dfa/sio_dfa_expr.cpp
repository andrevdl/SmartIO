#include "sio_dfa_expr.h"

#include <parser/ast/sio_ast_expr.h>
#include <parser/ast/sio_ast_terminal.h>

bool tree_expr_compare(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_expr_logic_low_handler, state) && tree_parse_token(ctx, walker, tree_expr_compare2_handler, state);
}

bool tree_expr_compare_eq(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstLogic* logic = new SIOAstLogic();
	logic->assign_left(state);
	
	if (tree_parse_token(ctx, walker, tree_expr_logic_low_handler, state))
	{
		logic->assign_right(last, state);
		state.store_node(logic);
	
		return tree_parse_token(ctx, walker, tree_expr_compare2_handler, state);
	}
	return false;
}

bool tree_expr_compare_neq(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstLogic* logic = new SIOAstLogic();
	logic->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_expr_logic_low_handler, state))
	{
		logic->assign_right(last, state);
		state.store_node(logic);

		return tree_parse_token(ctx, walker, tree_expr_compare2_handler, state);
	}
	return false;
}

bool tree_expr_logic_low(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_expr_logic_high_handler, state) && tree_parse_token(ctx, walker, tree_expr_logic_low2_handler, state);
}

bool tree_expr_logic_or(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstLogic* logic = new SIOAstLogic();
	logic->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_expr_logic_high_handler, state))
	{
		logic->assign_right(last, state);
		state.store_node(logic);

		return tree_parse_token(ctx, walker, tree_expr_logic_low2_handler, state);
	}
	return false;
}

bool tree_expr_logic_high(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_expr_arith_handler, state) && tree_parse_token(ctx, walker, tree_expr_logic_high2_handler, state);
}

bool tree_expr_logic_and(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstLogic* logic = new SIOAstLogic();
	logic->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_expr_arith_handler, state))
	{
		logic->assign_right(last, state);
		state.store_node(logic);

		return tree_parse_token(ctx, walker, tree_expr_logic_high2_handler, state);
	}
	return false;
}

bool tree_expr_arith(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_expr_term_handler, state) && tree_parse_token(ctx, walker, tree_expr_arith2_handler, state);
}

bool tree_expr_arith_add(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstExpr* expr = new SIOAstExpr();
	expr->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_expr_term_handler, state))
	{
		expr->assign_right(last, state);
		state.store_node(expr);

		return tree_parse_token(ctx, walker, tree_expr_arith2_handler, state);
	}
	return false;
}

bool tree_expr_arith_min(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstExpr* expr = new SIOAstExpr();
	expr->assign_left(state);

	if (tree_parse_token(ctx, walker, tree_expr_term_handler, state))
	{
		expr->assign_right(last, state);
		state.store_node(expr);

		return tree_parse_token(ctx, walker, tree_expr_arith2_handler, state);
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
		state.store_node(expr);

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
		state.store_node(expr);

		return tree_parse_token(ctx, walker, tree_expr_term2_handler, state);
	}
	return false;
}

bool tree_expr_factor(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_expr_factor2_handler, state);
}

bool tree_expr_factor_inverse(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	if (tree_parse_token(ctx, walker, tree_expr_factor2_handler, state))
	{
		state.curr_node->inverse = true;
		return true;
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

	state.store_node(val);
	return true;
}

bool tree_expr_factor_literal(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_id_handler, state);
}

bool tree_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	return tree_expr_compare_handler(type, eat, func, state);
}

bool tree_expr_compare_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	SIO_TREE_DEBUG_INFO("CompareExpr", "");
	func = tree_expr_compare;
	return true;
}

bool tree_expr_compare2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::LOGIC_EQUAL:
		SIO_TREE_DEBUG_INFO("CompareExprOp", "==");
		func = tree_expr_compare_eq;
		eat = true;
		break;
	case SIOTokenType::LOGIC_UNEQUAL:
		SIO_TREE_DEBUG_INFO("CompareExprOp", "<>");
		func = tree_expr_logic_or;
		eat = true;
		break;
	default:
		type = SIOTokenType::EMPTY;
	}
	return true;
}

bool tree_expr_logic_low_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	SIO_TREE_DEBUG_INFO("LogicExpr", "Low");
	func = tree_expr_logic_low;
	return true;
}

bool tree_expr_logic_low2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::OR:
		SIO_TREE_DEBUG_INFO("LogicExprOp", "||");
		func = tree_expr_logic_or;
		eat = true;
		break;
	default:
		type = SIOTokenType::EMPTY;
	}
	return true;
}

bool tree_expr_logic_high_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	SIO_TREE_DEBUG_INFO("LogicExpr", "High");
	func = tree_expr_logic_high;
	return true;
}

bool tree_expr_logic_high2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::AND:
		SIO_TREE_DEBUG_INFO("LogicExprOp", "&&");
		func = tree_expr_logic_and;
		eat = true;
		break;
	default:
		type = SIOTokenType::EMPTY;
	}
	return true;
}

bool tree_expr_arith_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	SIO_TREE_DEBUG_INFO("ArithExpr", "");
	func = tree_expr_arith;
	return true;
}

bool tree_expr_arith2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::ADD:
		SIO_TREE_DEBUG_INFO("ArithExprOp", "+");
		func = tree_expr_arith_add;
		eat = true;
		break;
	case SIOTokenType::MIN:
		SIO_TREE_DEBUG_INFO("ArithExprOp", "-");
		func = tree_expr_arith_min;
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
	case SIOTokenType::NOT:
		SIO_TREE_DEBUG_INFO("ExprFactor", "Not");
		eat = true;
		type = SIOTokenType::NOT;
		func = tree_expr_factor_inverse;
		break;
	default:
		SIO_TREE_DEBUG_INFO("ExprFactor", "");
		func = tree_expr_factor;
	}
	return true;
}

bool tree_expr_factor2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
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