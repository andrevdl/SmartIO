#pragma once

#include <parser/ast/sio_ast.h>

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