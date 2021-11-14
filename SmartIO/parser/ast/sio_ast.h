#pragma once

#include <vector>

#include "../SIOTokens.h"
#include "../../debugger/SIODotDebugger.h"

enum class AstNodeType
{
	LITERAL,
	VALUE,
	FUNCTION,
	EXPR,
	LOGIC_EXPR,
	COMPARE_EXPR
};

class SIOAst
{
public:
	bool inverse;

	SIOAst() : inverse(false) {}

	virtual void print(SIODotDebugger* debugger) = 0;
	virtual const AstNodeType get_type() = 0;
};

//class SIOAst
//{
//public:
//	//SIOAst* left = nullptr;
//	//SIOAst* right = nullptr;
//	//string emit_encoded_instr
//	//string emit_plain_instr
//
//	virtual void print(SIODotDebugger* debugger) {}
//};

#ifdef SIO_DEBUG
struct AstNodeDebugInfo
{
	char* debug_name;
	char* debug_body;
};
#endif // SIO_DEBUG

struct AstNodeState
{
#ifdef SIO_DEBUG
	AstNodeDebugInfo debug_info;
#endif // SIO_DEBUG

	SIOAst* root_node = nullptr;
	SIOAst* curr_node = nullptr;

	string err;

	void store_node(SIOAst* curr)
	{
		if (root_node == nullptr)
		{
			root_node = curr;
		}
		curr_node = curr;
	}
};

class SIOAstBaseThreeWay : public SIOAst
{
private:
	void rotate(AstNodeState& state)
	{
		if (left == state.root_node)
		{
			// steal the root
			state.root_node = this;
		}
	}
public:
	SIOTokenType op = SIOTokenType::EMPTY;
	SIOAst* left = nullptr;
	SIOAst* right = nullptr;

	void assign_left(AstNodeState& state)
	{
		left = state.curr_node;
		rotate(state);
	}

	void assign_right(SIOTokenType op, AstNodeState& state)
	{
		this->op = op;
		right = state.curr_node;
	}
};

class SIOAstBaseChilds : public SIOAst
{
public:
	vector<SIOAst*>* childs;

	SIOAstBaseChilds()
	{
		this->childs = new vector<SIOAst*>();
	}
};

class SIOAstLogic: public SIOAstBaseThreeWay
{
public:
	void print(SIODotDebugger* debugger)
	{
		debugger->create_node("Logic", "test");
		if (left != nullptr)
		{
			left->print(debugger);
		}
		if (right != nullptr)
		{
			right->print(debugger);
		}
		debugger->close_node();
	}

	const AstNodeType get_type()
	{
		return AstNodeType::LOGIC_EXPR;
	}
};

class SIOAstLogicCompare : public SIOAstBaseThreeWay
{
public:
	void print(SIODotDebugger* debugger)
	{
		debugger->create_node("compare", "test");
		if (left != nullptr)
		{
			left->print(debugger);
		}
		if (right != nullptr)
		{
			right->print(debugger);
		}
		debugger->close_node();
	}

	const AstNodeType get_type()
	{
		return AstNodeType::COMPARE_EXPR;
	}
};

class SIOAstExpr : public SIOAstBaseThreeWay
{
public:
	void print(SIODotDebugger* debugger)
	{
		debugger->create_node("Expr", "test");
		if (left != nullptr)
		{
			left->print(debugger);
		}
		if (right != nullptr)
		{
			right->print(debugger);
		}
		debugger->close_node();
	}

	const AstNodeType get_type()
	{
		return AstNodeType::EXPR;
	}
};

class SIOAstLiteral : public SIOAst
{
public:
	int val; // debug

	void print(SIODotDebugger* debugger)
	{
		debugger->create_node("Literal", to_string(val));
		debugger->close_node();
	}

	const AstNodeType get_type()
	{
		return AstNodeType::LITERAL;
	}
};

class SIOAstValue : public SIOAst
{
public:
	int val; // debug

	void print(SIODotDebugger* debugger)
	{
		debugger->create_node("Value", to_string(val));
		debugger->close_node();
	}

	const AstNodeType get_type()
	{
		return AstNodeType::VALUE;
	}
};

class SIOAstFunction : public SIOAstBaseChilds
{
private:
	void rotate(AstNodeState& state)
	{
		if (literal == state.root_node)
		{
			// steal the root
			state.root_node = this;
		}
	}
public:
	SIOAstLiteral* literal;

	void assign_literal(AstNodeState& state)
	{
		literal = (SIOAstLiteral*)state.curr_node;
		rotate(state);
	}

	void print(SIODotDebugger* debugger)
	{
		debugger->create_node("Function", "");
		for (auto it = childs->cbegin(); it != childs->cend(); ++it)
		{
			(*it)->print(debugger);
		}
		debugger->close_node();
	}

	const AstNodeType get_type()
	{
		return AstNodeType::FUNCTION;
	}
};