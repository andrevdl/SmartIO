#include "sio_id.h"

bool tree_id(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	//FINISH_TREE_NODE(node.parse_leaf(walker, token) && node.parse_node(walker, id2));

	SIOAstLiteral* lit = new SIOAstLiteral();
	lit->val = walker.pop()->value;

	state.store_node(lit, AstNodeType::LITERAL);

	return tree_parse_token(ctx, walker, tree_id2_handler, state);
}

bool tree_id2_call(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::EMPTY)
	{
		if (type != SIOTokenType::RPAR)
		{
			SIOAstFunction* func = new SIOAstFunction();
			func->assign_literal(state);

			while (type != SIOTokenType::RPAR)
			{
				if (!tree_parse_token(ctx, walker, tree_expr_handler, state)) // TODO: replace handler by more general handler (instruction)
				{
					state.err = "Invalid parameter";
					return false;
				}

				func->childs->push_back(state.curr_node);

				type = walker.pop_type();
				if (type == SIOTokenType::EMPTY || (type != SIOTokenType::COMMA && type != SIOTokenType::RPAR))
				{
					state.err = "Function is incorrect formatted";
					return false;
				}
			}

			state.store_node(func, AstNodeType::FUNCTION);
			return type == SIOTokenType::RPAR;
	
			//FINISH_TREE_NODE(type == SIOTokenType::RPAR 
			//	&& tree_parse_token(walker, tree_array_handler, dest) 
			//	&& tree_parse_token(walker, tree_id_chain_handler, dest));
		}
		else
		{
			walker.pop();
			return tree_parse_token(ctx, walker, tree_array_handler, state)
				&& tree_parse_token(ctx, walker, tree_id_chain_handler, state);
		}
	}
	
	return false;
}

bool tree_id2_array(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_array_handler, state);
}

bool tree_id2_chain(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_id_chain_handler, state);
}

bool tree_array(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::EMPTY)
	{		
		//SIONArray arr;

		if (type != SIOTokenType::RBR)
		{
			return false;

			//vector<SIONExpr> indices;

			//while (type != SIOTokenType::RBR)
			//{
			//	if (!tree_parse_token(walker, indices, false))
			//	{
			//		FINISH_TREE_NODE(false);
			//	}

			//	type = walker.pop_type();
			//	if (type == SIOTokenType::EMPTY || (type != SIOTokenType::COMMA && type != SIOTokenType::RBR))
			//	{
			//		FINISH_TREE_NODE(false);
			//	}
			//}

			//FINISH_TREE_NODE(type == SIOTokenType::RBR && tree_parse_token(walker, tree_array_handler, dest));
		}
		else
		{
			walker.pop();
			return tree_parse_token(ctx, walker, tree_array_handler, state);
		}
	}

	return false;
}

bool tree_array_chain(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_id_chain_handler, state);
}

bool tree_id_chain(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return tree_parse_token(ctx, walker, tree_id_handler, state) && tree_parse_token(ctx, walker, tree_id_chain_handler, state);
}

bool tree_id_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	SIO_TREE_DEBUG_INFO("Identifier", "");
	func = tree_id;
	return true;
}

bool tree_id2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		SIO_TREE_DEBUG_INFO("Parameters", "");
		eat = true;
		type = SIOTokenType::CALL;
		func = tree_id2_call;
		break;
	case SIOTokenType::LBR:
		SIO_TREE_DEBUG_INFO("ID2Array", "");
		type = SIOTokenType::ARRAY;
		func = tree_id2_array;
		break;
	case SIOTokenType::DOT:
		SIO_TREE_DEBUG_INFO("ArrayChain", "");
		type = SIOTokenType::NESTED;
		func = tree_id2_chain;
		break;
	}
	
	return true;
}

bool tree_array_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::LBR:
		SIO_TREE_DEBUG_INFO("Indices", "");
		eat = true;
		type = SIOTokenType::ARRAY;
		func = tree_array;
		break;
	case SIOTokenType::DOT: /* bug: q().m => m is chain of method, not of the array => add extra node? */
		SIO_TREE_DEBUG_INFO("ArrayChain", "");
		type = SIOTokenType::NESTED;
		func = tree_array_chain;
		break;
	}
	
	return true;
}

bool tree_id_chain_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	if (type == SIOTokenType::DOT)
	{
		SIO_TREE_DEBUG_INFO("IDChain", "");
		eat = true;
		func = tree_id_chain;
	}
		
	return true;
}
