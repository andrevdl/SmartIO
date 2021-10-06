#pragma once

#include "../SIOTokenWalker.h"
#include "../Debugger/SIODotDebugger.h"

typedef bool (*t_parse_tree_func)(SIOTokenWalker&, void* /*AST*/);
typedef bool (*t_parse_tree_handler)(SIOTokenType& type, bool&, t_parse_tree_func&);

inline bool tree_parse_token(SIOTokenWalker& walker, t_parse_tree_handler handler, void* dest)
{
	SIOTokenType type = walker.peek_type();
	bool eat = false;

	t_parse_tree_func func = nullptr;
	if (handler(type, eat, func))
	{
		if (func != nullptr)
		{
			if (eat)
			{
				walker.pop();
			}
			return func(walker, dest);
		}
		return true;
	}
	return false;
}