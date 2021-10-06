#include "sio_expr.h"

bool tree_expr(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("Expr", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_expr_term_handler, dest) && tree_parse_token(walker, tree_expr2_handler, dest));
}

bool tree_expr2_add(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("ExprOp", "+");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_expr_term_handler, dest) && tree_parse_token(walker, tree_expr2_handler, dest));
}

bool tree_expr2_min(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("ExprOp", "-");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_expr_term_handler, dest) && tree_parse_token(walker, tree_expr2_handler, dest));
}

bool tree_expr_term(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("Expr", "Term");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_expr_factor_handler, dest) && tree_parse_token(walker, tree_expr_term2_handler, dest));
}

bool tree_expr_term2_mul(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("TermOp", "*");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_expr_factor_handler, dest) && tree_parse_token(walker, tree_expr_term2_handler, dest));
}

bool tree_expr_term2_div(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("TermOp", "/");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_expr_factor_handler, dest) && tree_parse_token(walker, tree_expr_term2_handler, dest));
}

bool tree_expr_factor_nested(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("Expr", "Nested");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_expr_handler, dest) && walker.pop_type() == SIOTokenType::RPAR);
}

bool tree_expr_factor_val(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("ExprFactor", "Value");
	//FINISH_TREE_NODE(node->parse_leaf(walker, node->symbol));

	// temp code -> push symbol to AST, for now pop it
	walker.pop();
	FINISH_TREE_NODE(true);
}

bool tree_expr_factor_id(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("ExprFactor", "ID");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_id_handler, dest));
}

bool tree_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	func = tree_expr;
	return true;
}

bool tree_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	switch (type)
	{
	case SIOTokenType::ADD:
		func = tree_expr2_add;
		eat = true;
		break;
	case SIOTokenType::MIN:
		func = tree_expr2_min;
		eat = true;
		break;
	default:
		type = SIOTokenType::EMPTY;
	}
	return true;
}

bool tree_expr_term_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	func = tree_expr_term;
	return true;
}

bool tree_expr_term2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	switch (type)
	{
	case SIOTokenType::STAR:
		func = tree_expr_term2_mul;
		eat = true;
		break;
	case SIOTokenType::SLASH:
		func = tree_expr_term2_div;
		eat = true;
		break;
	default:
		type = SIOTokenType::EMPTY;
	}
	return true;
}

bool tree_expr_factor_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		eat = true;
		type = SIOTokenType::NESTED;
		func = tree_expr_factor_nested;
		return true;
	case SIOTokenType::VALUE:
		type = SIOTokenType::SYMBOL;
		func = tree_expr_factor_val;
		return true;
	case SIOTokenType::IDENTIFIER:
		func = tree_expr_factor_id;
		return true;
	default:
		return false;
	}
}