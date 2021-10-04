#include "SIONode.h"

// temp -> may move
#include "../SIOStringMapper.h"

void SIOBaseNode::print_dot_graph(ostream& os) const
{
	os << get_uuid() << "[shape=record label=\"{" << get_name() << "|";
	print_dot_graph_body(os);
	os << "}}\"];" << endl;

	create_dot_graph_link(os);
	after_print_dot_graph(os);
}

void SIOBaseNode::create_dot_graph_link(ostream& os) const
{
	if (parent != nullptr)
	{
		os << parent->get_uuid() << "->" << get_uuid() << endl;
	}
	else
	{
		os << "root->" << get_uuid() << endl;
	}
}

SIOBaseNode::SIOBaseNode(SIONonTerminalNode* parent) : parent(parent)
{
	static uint64_t uuid = 0;
	if (this->uuid == 0)
	{
		if (uuid == ULLONG_MAX)
		{
			uuid = 0;
		}

		this->uuid = ++uuid;
	}
}

void SIONonTerminalNode::after_print_dot_graph(ostream& os) const
{
	for each (SIOBaseNode * c in childs)
	{
		os << *c;
	}
}

void SIONonTerminalNode::print_dot_graph_body(ostream& os) const
{
	os << token_type_str(type);
}

const SIOTokenType SIONonTerminalNode::get_type() const
{
	return type;
}

SIONonTerminalNode::SIONonTerminalNode(SIONonTerminalNode* parent) : SIOBaseNode(parent)
{
	if (parent != nullptr)
	{
		parent->childs.push_back(this);
	}
}

bool SIONonTerminalNode::parse_leaf(SIOTokenWalker& walker, SIONSymbol* target)
{
	SIOToken* token = walker.pop();
	if (token != nullptr)
	{
		target = new SIONSymbol(token, this);
		return true;
	}
	
	return false;
}

void SIONSymbol::print_dot_graph_body(ostream& os) const
{
	if (this->token->type == SIOTokenType::IDENTIFIER)
	{
		string s;
		if (SIOStringMapper::global_mapper()->load_str(this->token->value, s))
		{
			os << s << " RAW";
		}
		else
		{
			os << this->token->value;
		}	
	}
	else
	{
		os << this->token->value;
	}
}

SIONSymbol::SIONSymbol(SIOToken* token, SIONonTerminalNode* parent) : SIOBaseNode(parent), token(token)
{
	if (parent != nullptr)
	{
		parent->childs.push_back(this);
	}

	this->token = token;
}

ostream& operator<<(ostream& os, const SIOBaseNode& node)
{
	node.print_dot_graph(os);
	return os;
}

const char* SIOBaseNode::get_raw_name() const
{
	return typeid(*this).name();
}

const char* SIOBaseNode::get_name() const
{
	// The prefix is always "class SIO", except the base class
	return get_raw_name() + 10;
}

const uint64_t SIOBaseNode::get_uuid() const
{
	return uuid;
}