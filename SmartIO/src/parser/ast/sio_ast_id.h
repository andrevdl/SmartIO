#pragma once

#include <parser/ast/sio_ast.h>
#include <parser/ast/sio_ast_terminal.h>

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