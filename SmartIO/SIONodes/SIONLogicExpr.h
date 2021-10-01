#pragma once

#include "SIONCommon.h"

class SIONLogicExpr;
class SIONLogicExpr2;
class SIONCompareExpr;
class SIONCompareExpr2;
class SIONLogicExprUnit;
class SIONLogicExprUnit2;
class SIONLogicExprExpr2;

class SIONLogicExprExpr : public SIONonTerminalNode
{
private:
	SIONLogicExprExpr2* expr = 0;

	static bool create_expr(SIOTokenWalker& walker, SIONLogicExprExpr* node);
	static bool create_nested_expr(SIOTokenWalker& walker, SIONLogicExprExpr* node);
public:
	SIONLogicExprExpr(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONLogicExprExpr2 : public SIONonTerminalNode
{
private:
	bool inverse = false;
	SIONExpr* expr = 0;

	static bool create_expr(SIOTokenWalker& walker, SIONLogicExprExpr2* node);
	static bool create_not_expr(SIOTokenWalker& walker, SIONLogicExprExpr2* node);
public:
	SIONLogicExprExpr2(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONLogicExpr : public SIONonTerminalNode
{
private:
	SIONLogicExprUnit* unit = 0;
	SIONLogicExpr2* expr2 = 0;

	static bool create_expr(SIOTokenWalker& walker, SIONLogicExpr* node);
public:
	SIONLogicExpr(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONLogicExpr2 : public SIONonTerminalNode
{
	SIONLogicExprUnit* unit = 0;
	SIONLogicExpr2* expr2 = 0;
	SIONLogicExpr2* sub = 0;

	static bool create_logic(SIOTokenWalker& walker, SIONLogicExpr2* node);
protected:
	virtual void print_dot_graph_body(ostream& os) const;
public:
	SIONLogicExpr2(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONLogicExprUnit : public SIONonTerminalNode
{
private:
	bool inverse = false;
	SIONLogicExprUnit2* unit = 0;
protected:
	static bool create_unit(SIOTokenWalker& walker, SIONLogicExprUnit* node);
	static bool create_not_unit(SIOTokenWalker& walker, SIONLogicExprUnit* node);
public:
	SIONLogicExprUnit(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONLogicExprUnit2 : public SIONonTerminalNode
{
private:
	SIONCompareExpr* compare = 0;
	SIONLogicExpr* expr = 0;
	SIONCompareExpr2* compare2 = 0;
protected:
	static bool create_unit(SIOTokenWalker& walker, SIONLogicExprUnit2* node);
	static bool create_nested_unit(SIOTokenWalker& walker, SIONLogicExprUnit2* node);
public:
	SIONLogicExprUnit2(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONCompareExpr : public SIONonTerminalNode
{
private:
	SIONLogicExprExpr* expr = 0;
	SIONCompareExpr2* compare2 = 0;

	static bool create_compare(SIOTokenWalker& walker, SIONCompareExpr* node);
public:
	SIONCompareExpr(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

class SIONCompareExpr2 : public SIONonTerminalNode
{
private:
	SIONLogicExprExpr* expr = 0;
	SIONCompareExpr2* sub = 0;

	static bool create_compare(SIOTokenWalker& walker, SIONCompareExpr2* node);
protected:
	virtual void print_dot_graph_body(ostream& os) const;
public:
	SIONCompareExpr2(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	template<class T>
	static bool get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat);
};

template<class T>
inline bool SIONLogicExprExpr::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		eat = true;
		type = SIOTokenType::NESTED;
		handler = create_nested_expr;
		return true;
	default:
		handler = create_expr;
		return true;
	}
}

template<class T>
inline bool SIONLogicExpr::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	handler = create_expr;
	return true;
}

template<class T>
inline bool SIONLogicExpr2::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	if (is_logic_op(type))
	{
		handler = create_logic;
		eat = true;
	}
	else
	{
		type = SIOTokenType::EMPTY;
	}

	return true;
}

template<class T>
inline bool SIONCompareExpr::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	handler = create_compare;
	return true;
}

template<class T>
inline bool SIONCompareExpr2::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	if (is_comp_op(type))
	{
		handler = create_compare;
		eat = true;
	}
	else
	{
		type = SIOTokenType::EMPTY;
	}

	return true;
}

template<class T>
inline bool SIONLogicExprUnit::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	switch (type)
	{
	case SIOTokenType::NOT:
		eat = true;
		handler = create_not_unit;
		return true;
	default:
		handler = create_unit;
		return true;
	}
}

template<class T>
inline bool SIONLogicExprUnit2::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		eat = true;
		type = SIOTokenType::NESTED;
		handler = create_nested_unit;
		return true;
	default:
		handler = create_unit;
		return true;
	}
}

template<class T>
inline bool SIONLogicExprExpr2::get_handler(function<bool(SIOTokenWalker&, T*)>& handler, SIOTokenType& type, bool& eat)
{
		
	if (type == SIOTokenType::NOT)
	{
		eat = true;
		handler = create_not_expr;
		return true;
	}

	handler = create_expr;
	return true;
}