#pragma once

#include <parser/ast/sio_ast.h>
#include <parser/ast/sio_ast_terminal.h>

class SIOAstArray : public SIOAstBaseChilds
{
public:
	SIOAstArray* arr = nullptr;

	void print(SIODotDebugger* debugger, SIOContext* ctx);

	const AstNodeType get_type()
	{
		return AstNodeType::ARRAY;
	}
};

class SIOAstFunction;

class SIOAstId : public SIOAst
{
public:
	uintptr_t name_ref = 0;
	SIOAstId* next_id = nullptr;
	SIOAstFunction* next_func = nullptr;
	SIOAstArray* arr = nullptr;

	void print(SIODotDebugger* debugger, SIOContext* ctx);

	const AstNodeType get_type()
	{
		return AstNodeType::ID;
	}
};

class SIOAstFunction : public SIOAstBaseChilds
{
public:
	uintptr_t name_ref = 0;
	SIOAstId* next_id = nullptr;
	SIOAstFunction* next_func = nullptr;
	SIOAstArray* arr = nullptr;

	void print(SIODotDebugger* debugger, SIOContext* ctx);

	const AstNodeType get_type()
	{
		return AstNodeType::FUNCTION;
	}
};