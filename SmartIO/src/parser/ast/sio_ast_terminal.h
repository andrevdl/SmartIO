#pragma once

#include <parser/ast/sio_ast.h>

class SIOAstLiteral : public SIOAst
{
public:
	uintptr_t val; // debug

	void print(SIODotDebugger* debugger, SIOContext* ctx)
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
	uintptr_t val; // debug

	void print(SIODotDebugger* debugger, SIOContext* ctx)
	{
		debugger->create_node("Value", to_string(val));
		debugger->close_node();
	}

	const AstNodeType get_type()
	{
		return AstNodeType::VALUE;
	}
};