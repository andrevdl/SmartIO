#pragma once

#include <vector>
#include <functional>
#include "../SIOCommon.h"
#include "../SIOTokenWalker.h"

class SIONonTerminalNode;

class SIOBaseNode
{
private:
	uint64_t uuid = 0;
protected:
	SIONonTerminalNode* parent = 0;

	void print_dot_graph(ostream& os) const;
	virtual void print_dot_graph_body(ostream& os) const {}
	void create_dot_graph_link(ostream& os) const;
	virtual void after_print_dot_graph(ostream& os) const {}
public:
	SIOBaseNode(SIONonTerminalNode* parent);

	virtual const char* get_raw_name() const;
	virtual const char* get_name() const;

	const uint64_t get_uuid() const;

	friend ostream& operator<<(ostream& os, const SIOBaseNode& node);
};

class SIONSymbol;

typedef function<bool(SIOTokenWalker&, SIONonTerminalNode*)> TreeHandler;

class SIONonTerminalNode : public SIOBaseNode
{
	friend SIONSymbol;
private:
	vector<SIOBaseNode*> childs;
protected:
	virtual void after_print_dot_graph(ostream& os) const;
	static bool accept(SIOTokenType type);	
	static bool accept(SIOTokenWalker& walker, bool& empty);
public:
	SIONonTerminalNode(SIONonTerminalNode* parent);

	template<typename T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*, bool&)>& handler, SIOTokenType type);

	template<typename T>
	bool parse_node(SIOTokenWalker& walker, T*& target);

	bool parse_leaf(SIOTokenWalker& walker, SIONSymbol* target);
};

class SIONSymbol : public SIOBaseNode
{
private:
	SIOToken* token;
protected:
	virtual void print_dot_graph_body(ostream& os) const;
public:
	SIONSymbol(SIOToken* token, SIONonTerminalNode* parent);
};

template<typename T>
bool SIONonTerminalNode::parse_node(SIOTokenWalker& walker, T*& target)
{
	function<bool(SIOTokenWalker&, T*)> handler;
	bool eat = false;

	if (T::get_handler(handler, walker.peek_type(), eat))
	{
		if (handler != nullptr)
		{
			if (eat)
			{
				walker.pop();
			}

			target = new T(this);
			return handler(walker, target);
		}
		return true;
	}

	return false;
}

template<typename T>
bool SIONonTerminalNode::get_handler(function<bool(SIOTokenWalker&, T*, bool&)>& handler, SIOTokenType type)
{
	handler = nullptr;
	return false;
}