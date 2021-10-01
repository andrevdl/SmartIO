#pragma once

#include "SIONCommon.h"

class SIONExprTerm;
class SIONExprTerm2;
class SIONExpr2;
class SIONExprFactor;

class SIONIdentifier;

class SIONExpr : public SIONonTerminalNode
{
private:
	SIONExprTerm* term = 0;
	SIONExpr2* expr2 = 0;

	static bool create_expr(SIOTokenWalker& walker, SIONExpr* node);
public:
	SIONExpr(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONExpr2 : public SIONonTerminalNode
{
private:
	SIONExprTerm* term = 0;
	SIONExpr2* expr2 = 0;

	static bool create_expr_add(SIOTokenWalker& walker, SIONExpr2* node);
	static bool create_expr_min(SIOTokenWalker& walker, SIONExpr2* node);
protected:
	virtual void print_dot_graph_body(ostream& os) const;	

public:
	SIONExpr2(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};


class SIONExprTerm : public SIONonTerminalNode
{
private:
	SIONExprFactor* factor = 0;
	SIONExprTerm2* term2 = 0;

	static bool create_term(SIOTokenWalker& walker, SIONExprTerm* node);
public:
	SIONExprTerm(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONExprTerm2 : public SIONonTerminalNode
{
private:
	SIONExprFactor* factor = 0;
	SIONExprTerm2* term2 = 0;

	static bool create_term_multi(SIOTokenWalker& walker, SIONExprTerm2* node);
	static bool create_term_divide(SIOTokenWalker& walker, SIONExprTerm2* node);
protected:
	virtual void print_dot_graph_body(ostream& os) const;	
public:
	SIONExprTerm2(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}	

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONExprFactor : public SIONonTerminalNode
{
private:
	SIONExpr* expr = 0;
	SIONSymbol* symbol = 0;
	SIONIdentifier* id = 0;

	static bool create_factor_nested(SIOTokenWalker& walker, SIONExprFactor* node);
	static bool create_factor_value(SIOTokenWalker& walker, SIONExprFactor* node);
	static bool create_factor_id(SIOTokenWalker& walker, SIONExprFactor* node);
public:
	SIONExprFactor(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}	

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

template<class T>
bool SIONExpr::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	handler = create_expr;
	return true;
}

template<class T>
inline bool SIONExpr2::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	switch (type)
	{
	case SIOTokenType::ADD:
		handler = create_expr_add;
		eat = true;
		break;
	case SIOTokenType::MIN:
		handler = create_expr_min;
		eat = true;
		break;
	default:
		type = SIOTokenType::EMPTY;
	}
	return true;
}

template<class T>
inline bool SIONExprTerm::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	handler = create_term;
	return true;
}

template<class T>
inline bool SIONExprTerm2::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	switch (type)
	{
	case SIOTokenType::STAR:
		handler = create_term_multi;
		eat = true;
		break;
	case SIOTokenType::SLASH:
		handler = create_term_divide;
		eat = true;
		break;
	default:
		type = SIOTokenType::EMPTY;
	}
	return true;
}

template<class T>
inline bool SIONExprFactor::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		eat = true;
		type = SIOTokenType::NESTED;
		handler = create_factor_nested;
		return true;
	case SIOTokenType::VALUE:
		type = SIOTokenType::SYMBOL;
		handler = create_factor_value;
		return true;
	case SIOTokenType::IDENTIFIER:	
		handler = create_factor_id;
		return true;
	default:
		return false;
	}
}

// Goal   -> Expr

// Expr   -> Term Expr`
// Expr`  -> + Term Expr` | - Term Expr` | e {empty}
// Term   -> Factor Term`
// Term`  -> x Factor Term` | % Factor Term` | e {empty}

// Factor -> ( Expr ) | num | name