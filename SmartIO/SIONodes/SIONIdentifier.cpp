#include "SIONIdentifier.h"

bool SIONIdentifier::create_id(SIOTokenWalker& walker, SIONIdentifier* node)
{
	START_TREE_NODE("Identifier", "");
	FINISH_TREE_NODE(node->parse_leaf(walker, node->symbol) && node->parse_node(walker, node->id2));
}

void SIONIdentifier::print_dot_graph_body(ostream& os) const // TODO: RESOLVE THIS VALUES IN THE NEW SYSTEM !!!
{
	if (id2 != nullptr)
	{
		switch (id2->get_type())
		{
		case SIOTokenType::CALL:
			os << "function";
			return;
		default:
			os << "variable";
			return;
		}
	}

	os << token_type_str(get_type());
}

bool SIONIdentifier2::create_call(SIOTokenWalker& walker, SIONIdentifier2* node)
{
	START_TREE_NODE("Parameters", "");

	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::EMPTY)
	{
		if (type != SIOTokenType::RPAR)
		{
			while (type != SIOTokenType::RPAR)
			{
				if (!node->parse_node(walker, node->params, false))
				{
					FINISH_TREE_NODE(false);
				}
					

				type = walker.pop_type();
				if (type == SIOTokenType::EMPTY || (type != SIOTokenType::COMMA && type != SIOTokenType::RPAR))
				{
					FINISH_TREE_NODE(false);
				}
			}

			FINISH_TREE_NODE(type == SIOTokenType::RPAR && node->parse_node(walker, node->arr) && node->parse_node(walker, node->chain));
		}
		else
		{
			walker.pop();
			FINISH_TREE_NODE(node->parse_node(walker, node->arr) && node->parse_node(walker, node->chain));
		}
	}

	FINISH_TREE_NODE(false);
}

bool SIONIdentifier2::create_array(SIOTokenWalker& walker, SIONIdentifier2* node)
{
	START_TREE_NODE("ID2Array", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->arr));
}

bool SIONIdentifier2::create_chain(SIOTokenWalker& walker, SIONIdentifier2* node)
{
	START_TREE_NODE("ID2Chain", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->chain));
}

void SIONIdentifier2::print_dot_graph_body(ostream& os) const
{
	switch (get_type())
	{
	case SIOTokenType::CALL:
		os << "parameters";
		return;
	}

	os << token_type_str(get_type());
}

bool SIONArray::create_array(SIOTokenWalker& walker, SIONArray* node)
{
	START_TREE_NODE("Indices", "");

	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::EMPTY)
	{
		if (type != SIOTokenType::RBR)
		{
			while (type != SIOTokenType::RBR)
			{
				if (!node->parse_node(walker, node->indices, false))
				{
					FINISH_TREE_NODE(false);
				}

				type = walker.pop_type();
				if (type == SIOTokenType::EMPTY || (type != SIOTokenType::COMMA && type != SIOTokenType::RBR))
				{
					FINISH_TREE_NODE(false);
				}
			}

			FINISH_TREE_NODE(type == SIOTokenType::RBR && node->parse_node(walker, node->arr));
		}
		else
		{
			walker.pop();
			FINISH_TREE_NODE(node->parse_node(walker, node->arr));
		}
	}

	FINISH_TREE_NODE(false);
}

bool SIONArray::create_chain(SIOTokenWalker& walker, SIONArray* node)
{
	START_TREE_NODE("ArrayChain", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->chain));
}

void SIONArray::print_dot_graph_body(ostream& os) const
{
	os << "indices";
}

bool SIONIdentifierChain::create_chain(SIOTokenWalker& walker, SIONIdentifierChain* node)
{
	START_TREE_NODE("IDChain", "");
	FINISH_TREE_NODE(node->parse_node(walker, node->id) && node->parse_node(walker, node->chain));
}
