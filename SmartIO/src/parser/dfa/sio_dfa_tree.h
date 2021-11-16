#pragma once

#include <parser/sio_token_walker.h>
#include <sio_context.h>

#include <parser/ast/sio_ast.h>

typedef bool (*t_parse_tree_func)(SIOContext&, SIOTokenType /*Last token*/, SIOTokenWalker&, AstNodeState&);
typedef bool (*t_parse_tree_handler)(SIOTokenType& type, bool&, t_parse_tree_func&, AstNodeState& state);

inline bool tree_parse_token(SIOContext& ctx, SIOTokenWalker& walker, t_parse_tree_handler handler, AstNodeState& state)
{
	SIOTokenType type = walker.peek_type();
	bool eat = false;

	t_parse_tree_func func = nullptr;
	if (handler(type, eat, func, state))
	{
		if (func != nullptr)
		{
#ifdef SIO_DEBUG
			ctx.get_dot_tree_debugger()->create_node(state.debug_info.debug_name, state.debug_info.debug_body);
#endif
			SIOTokenType last = eat ? walker.pop_type() : walker.peek_type();
			if (!func(ctx, last, walker, state))
			{
				ctx.store_parse_err(state.err);
				return false;
			}

#ifdef SIO_DEBUG
			ctx.get_dot_tree_debugger()->close_node();
#endif
		}
		state.empty = func == nullptr;
		return true;
	}

	state.err = "Unkown token...";
	return false;
}

#ifdef SIO_DEBUG
#define SIO_TREE_DEBUG_INFO(name, body) state.debug_info = { name, body }
#else
#define SIO_TREE_DEBUG_INFO(name, body)
#endif // SIO_DEBUG