#include "SIONIdentifier.h"

bool SIONIdentifier::create_id(SIOTokenWalker& walker, SIONIdentifier* node)
{
	return node->parse_leaf(walker, node->symbol) && node->parse_node(walker, node->id2);
}

void SIONIdentifier::print_dot_graph_body(ostream& os) const
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
	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::EMPTY)
	{
		if (type != SIOTokenType::RPAR)
		{
			while (type != SIOTokenType::RPAR)
			{
				if (!node->parse_node(walker, node->params, false))
					return false;

				type = walker.pop_type();
				if (type == SIOTokenType::EMPTY || (type != SIOTokenType::COMMA && type != SIOTokenType::RPAR))
					return false;
			}

			return type == SIOTokenType::RPAR && node->parse_node(walker, node->arr) && node->parse_node(walker, node->chain);
		}
		else
		{
			walker.pop();
			return node->parse_node(walker, node->arr) && node->parse_node(walker, node->chain);
		}
	}

	return false;
}

bool SIONIdentifier2::create_array(SIOTokenWalker& walker, SIONIdentifier2* node)
{
	return node->parse_node(walker, node->arr);
}

bool SIONIdentifier2::create_chain(SIOTokenWalker& walker, SIONIdentifier2* node)
{
	return node->parse_node(walker, node->chain);
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
	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::EMPTY)
	{
		if (type != SIOTokenType::RBR)
		{
			while (type != SIOTokenType::RBR)
			{
				if (!node->parse_node(walker, node->indices, false))
					return false;

				type = walker.pop_type();
				if (type == SIOTokenType::EMPTY || (type != SIOTokenType::COMMA && type != SIOTokenType::RBR))
					return false;
			}

			return type == SIOTokenType::RBR && node->parse_node(walker, node->arr);
		}
		else
		{
			walker.pop();
			return node->parse_node(walker, node->arr);
		}
	}

	return false;
}

bool SIONArray::create_chain(SIOTokenWalker& walker, SIONArray* node)
{
	return node->parse_node(walker, node->chain);
}

void SIONArray::print_dot_graph_body(ostream& os) const
{
	os << "indices";
}

bool SIONIdentifierChain::create_chain(SIOTokenWalker& walker, SIONIdentifierChain* node)
{
	return node->parse_node(walker, node->id) && node->parse_node(walker, node->chain);
}
