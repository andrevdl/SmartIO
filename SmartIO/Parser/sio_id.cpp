#include "sio_id.h"

bool tree_id(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("Identifier", "");
	//FINISH_TREE_NODE(node.parse_leaf(walker, token) && node.parse_node(walker, id2));

	// temp code -> push symbol to AST, for now pop it
	walker.pop();
	FINISH_TREE_NODE(tree_parse_token(walker, tree_id2_handler, dest));
}

bool tree_id2_call(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("Parameters", "");

	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::EMPTY)
	{
		if (type != SIOTokenType::RPAR)
		{
			FINISH_TREE_NODE(false);

			//vector<SIONExpr> params;
	
			//while (type != SIOTokenType::RPAR)
			//{
			//	if (!node.parse_node(walker, params, false))
			//	{
			//		FINISH_TREE_NODE(false);
			//	}
			//			
	
			//	type = walker.pop_type();
			//	if (type == SIOTokenType::EMPTY || (type != SIOTokenType::COMMA && type != SIOTokenType::RPAR))
			//	{
			//		FINISH_TREE_NODE(false);
			//	}
			//}
	
			//FINISH_TREE_NODE(type == SIOTokenType::RPAR 
			//	&& tree_parse_token(walker, tree_array_handler, dest) 
			//	&& tree_parse_token(walker, tree_id_chain_handler, dest));
		}
		else
		{
			walker.pop();
			FINISH_TREE_NODE(tree_parse_token(walker, tree_array_handler, dest)
				&& tree_parse_token(walker, tree_id_chain_handler, dest));
		}
	}
	
	FINISH_TREE_NODE(false);
}

bool tree_id2_array(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("ID2Array", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_array_handler, dest));
}

bool tree_id2_chain(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("ID2Chain", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_id_chain_handler, dest));
}

bool tree_array(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("Indices", "");

	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::EMPTY)
	{		
		//SIONArray arr;

		if (type != SIOTokenType::RBR)
		{
			FINISH_TREE_NODE(false);

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
			FINISH_TREE_NODE(tree_parse_token(walker, tree_array_handler, dest));
		}
	}

	FINISH_TREE_NODE(false);
}

bool tree_array_chain(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("ArrayChain", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_id_chain_handler, dest));
}

bool tree_id_chain(SIOTokenWalker& walker, void* dest)
{
	START_TREE_NODE("IDChain", "");
	FINISH_TREE_NODE(tree_parse_token(walker, tree_id_handler, dest) && tree_parse_token(walker, tree_id_chain_handler, dest));
}

bool tree_id_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	func = tree_id;
	return true;
}

bool tree_id2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		eat = true;
		type = SIOTokenType::CALL;
		func = tree_id2_call;
		break;
	case SIOTokenType::LBR:
		type = SIOTokenType::ARRAY;
		func = tree_id2_array;
		break;
	case SIOTokenType::DOT:
		type = SIOTokenType::NESTED;
		func = tree_id2_chain;
		break;
	}
	
	return true;
}

bool tree_array_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	switch (type)
	{
	case SIOTokenType::LBR:
		eat = true;
		type = SIOTokenType::ARRAY;
		func = tree_array;
		break;
	case SIOTokenType::DOT: /* bug: q().m => m is chain of method, not of the array => add extra node? */
		type = SIOTokenType::NESTED;
		func = tree_array_chain;
		break;
	}
	
	return true;
}

bool tree_id_chain_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func)
{
	if (type == SIOTokenType::DOT)
	{
		eat = true;
		func = tree_id_chain;
	}
		
	return true;
}
