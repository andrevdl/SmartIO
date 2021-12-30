/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "sio_dfa_stmt.h"

#include <parser/ast/sio_ast_id.h> // ast_stmt

bool tree_stmt_var(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return false;
}

bool tree_stmt_assign(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state) // add to handler...
{
	return false;
}

bool tree_stmt_if(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return false;
}

bool tree_stmt_while(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return false;
}

bool tree_stmt_io_add(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state)
{
	return false;
}

bool tree_stmt_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state)
{
	switch (type)
	{
	case SIOTokenType::VAR:
		SIO_TREE_DEBUG_INFO("Variable", "");
		func = tree_stmt_var;
		eat = true;
		return true;
	case SIOTokenType::IF:
		SIO_TREE_DEBUG_INFO("If", "");
		func = tree_stmt_if;
		eat = true;
		return true;
	case SIOTokenType::WHILE:
		SIO_TREE_DEBUG_INFO("While", "");
		func = tree_stmt_while;
		eat = true;
		return true;
	case SIOTokenType::IO_ADD:
		SIO_TREE_DEBUG_INFO("IO_Add", "");
		func = tree_stmt_io_add;
		eat = true;
		return true;
	}
	return false;
}