/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "sio_dfa_id.h"

#include <parser/ast/sio_ast_id.h>
#include <parser/ast/sio_ast_terminal.h>

bool tree_id(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	//FINISH_TREE_NODE(node.parse_leaf(walker, token) && node.parse_node(walker, id2));

	uintptr_t name_ref = walker.pop()->value;

	if (tree_parse_token(ctx, walker, tree_id_func_handler, state))
	{
		if (!state.empty)
		{
			SIOAstFunction* func = (SIOAstFunction*)state.curr_node;
			func->name_ref = name_ref;

			state.store_node(func);

			if (tree_parse_token(ctx, walker, tree_id_array_handler, state))
			{
				if (!state.empty)
				{
					func->arr = (SIOAstArray*)state.curr_node;
				}

				state.store_node(func);
				return tree_parse_token(ctx, walker, tree_id_chain_handler, state);
			}
			return false;
		}
		else
		{
			SIOAstId* id = new SIOAstId();
			id->name_ref = name_ref;

			state.store_node(id);

			if (tree_parse_token(ctx, walker, tree_id_array_handler, state))
			{
				if (!state.empty)
				{
					id->arr = (SIOAstArray*)state.curr_node;
				}

				state.store_node(id);
				return tree_parse_token(ctx, walker, tree_id_chain_handler, state);
			}
			return false;
		}
	}
	return false;
}

bool tree_id_func(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstFunction* func = new SIOAstFunction();
	state.store_node(func);

	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::RPAR)
	{
		while (type != SIOTokenType::RPAR)
		{
			if (!tree_parse_token(ctx, walker, tree_expr_handler, state))
			{
				state.err = "Invalid parameter";
				return false;
			}

			func->childs->push_back(state.curr_node);

			type = walker.pop_type();
			if (type == SIOTokenType::EMPTY || (type != SIOTokenType::COMMA && type != SIOTokenType::RPAR))
			{
				state.err = "Function is incorrect formatted";
				return false;
			}
		}
	}
	else
	{
		walker.pop();
	}

	state.store_node(func);
	return type == SIOTokenType::RPAR;
}

bool tree_id_array(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	SIOAstArray* arr = new SIOAstArray();
	state.store_node(arr);

	SIOTokenType type = walker.peek_type();
	if (type != SIOTokenType::RBR)
	{
		while (type != SIOTokenType::RBR)
		{
			if (!tree_parse_token(ctx, walker, tree_expr_handler, state))
			{
				state.err = "Invalid index";
				return false;
			}

			arr->childs->push_back(state.curr_node);

			type = walker.pop_type();
			if (type == SIOTokenType::EMPTY || (type != SIOTokenType::COMMA && type != SIOTokenType::RBR))
			{
				state.err = "Array is incorrect formatted";
				return false;
			}
		}
	}
	else
	{
		walker.pop();
	}

	if (type == SIOTokenType::RBR && tree_parse_token(ctx, walker, tree_id_array_handler, state))
	{
		if (!state.empty)
		{
			arr->arr = (SIOAstArray*)state.curr_node;
		}

		state.store_node(arr);
		return true;
	}
	return false;
}

bool tree_id_chain(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	if (state.curr_node->get_type() == AstNodeType::ID)
	{
		SIOAstId* parent = (SIOAstId*)state.curr_node;
		if (tree_parse_token(ctx, walker, tree_id_handler, state))
		{
			if (state.curr_node->get_type() == AstNodeType::ID)
			{
				parent->next_id = (SIOAstId*)state.curr_node;
			}
			else
			{
				parent->next_func = (SIOAstFunction*)state.curr_node;
			}
			
			return true;
		}
	}
	else
	{
		SIOAstFunction* parent = (SIOAstFunction*)state.curr_node;
		if (tree_parse_token(ctx, walker, tree_id_handler, state))
		{
			if (state.curr_node->get_type() == AstNodeType::ID)
			{
				parent->next_id = (SIOAstId*)state.curr_node;
			}
			else
			{
				parent->next_func = (SIOAstFunction*)state.curr_node;
			}
			return true;
		}
	}

	return false;
}

bool tree_id_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	if (type == SIOTokenType::IDENTIFIER)
	{
		SIO_TREE_DEBUG_INFO("Identifier", "");
		func = tree_id;
		return true;
	}

	return false;
}

bool tree_id_func_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::LPAR:
		SIO_TREE_DEBUG_INFO("Parameters", "");
		eat = true;
		//type = SIOTokenType::CALL;
		func = tree_id_func;
		break;
	}
	
	return true;
}

bool tree_id_array_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::LBR:
		SIO_TREE_DEBUG_INFO("Indices", "");
		eat = true;
		//type = SIOTokenType::ARRAY;
		func = tree_id_array;
		break;
	}
	
	return true;
}

bool tree_id_chain_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	if (type == SIOTokenType::DOT)
	{
		SIO_TREE_DEBUG_INFO("IDChain", "");
		eat = true;
		func = tree_id_chain;
	}
		
	return true;
}