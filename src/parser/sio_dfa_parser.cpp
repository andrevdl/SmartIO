#include "sio_dfa_parser.h"

bool tree_parse_token(SIOContext& ctx, SIOTokenWalker& walker, t_parse_tree_handler handler, AstNodeState& state)
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
				return false;
			}

#ifdef SIO_DEBUG
			ctx.get_dot_tree_debugger()->close_node();
#endif
		}
		state.empty = func == nullptr;
		return true;
	}

	SIOToken* token = walker.peek();
	if (token != nullptr)
	{
		ctx.get_logger()->log_error(create_expected_msg(state.expected, token->type), token->code_range.start_ln, token->code_range.start_col);
	}
	else
	{
		ctx.get_logger()->log_error(create_expected_msg(state.expected, SIOTokenType::EMPTY), 0, 0);
	}

	//ctx.get_logger()->log_error("Following token expected: xxx, but found: yyy", token->code_range.start_ln, token->code_range.start_col);
	return false;
}