#pragma once

#include <parser/ast/sio_ast_expr.h>
#include <parser/ast/sio_ast_terminal.h>

class SIOAstLogic : public SIOAstBaseTwoWay
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

class SIOAstLogicCompare : public SIOAstBaseTwoWay
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

class SIOAstExpr : public SIOAstBaseTwoWay
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