#pragma once

#include "SIONCommon.h"

class SIONArray;
class SIONExpr;
class SIONIdentifier2;
class SIONIdentifierChain;

class SIONIdentifier : public SIONonTerminalNode
{
private:
	SIONSymbol* symbol = 0;
	SIONIdentifier2* id2 = 0;

	static bool create_id(SIOTokenWalker& walker, SIONIdentifier* node);
protected:
	virtual void print_dot_graph_body(ostream& os) const;
public:
	SIONIdentifier(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONIdentifierChain : public SIONonTerminalNode
{
private:
	SIONIdentifier* id = 0;
	SIONIdentifierChain* chain = 0;

	static bool create_chain(SIOTokenWalker& walker, SIONIdentifierChain* node);
public:
	SIONIdentifierChain(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONIdentifier2 : public SIONonTerminalNode
{
private:
	vector<SIONExpr*> params;
	SIONArray* arr = 0;
	SIONIdentifierChain* chain = 0;

	static bool create_call(SIOTokenWalker& walker, SIONIdentifier2* node);
	static bool create_array(SIOTokenWalker& walker, SIONIdentifier2* node);
	static bool create_chain(SIOTokenWalker& walker, SIONIdentifier2* node);
protected:
	virtual void print_dot_graph_body(ostream& os) const;
public:
	SIONIdentifier2(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONArray : public SIONonTerminalNode
{
private:
	vector<SIONExpr*> indices;
	SIONArray* arr = 0;
	SIONIdentifierChain* chain = 0;

	static bool create_array(SIOTokenWalker& walker, SIONArray* node);
	static bool create_chain(SIOTokenWalker& walker, SIONArray* node);
protected:
	virtual void print_dot_graph_body(ostream& os) const;
public:
	SIONArray(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

template<class T>
inline bool SIONIdentifier::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	handler = create_id;
	return true;
}

template<class T>
inline bool SIONIdentifier2::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		eat = true;
		type = SIOTokenType::CALL;
		handler = create_call;
		break;
	case SIOTokenType::LBR:
		type = SIOTokenType::ARRAY;
		handler = create_array;
		break;
	case SIOTokenType::DOT:
		type = SIOTokenType::NESTED;
		handler = create_chain;
		break;
	}

	return true;
}

template<class T>
inline bool SIONArray::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	switch (type)
	{
	case SIOTokenType::LBR:
		eat = true;
		type = SIOTokenType::ARRAY;
		handler = create_array;
		break;
	case SIOTokenType::DOT:
		type = SIOTokenType::NESTED;
		handler = create_chain;
		break;
	}

	return true;
}

template<class T>
inline bool SIONIdentifierChain::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	if (type == SIOTokenType::DOT)
	{
		eat = true;
		handler = create_chain;
	}
	
	return true;
}
