/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <parser/sio_token_walker.h>
#include <sio_context.h>
#include <parser/util/sio_token_utils.h>

#include <parser/ast/sio_ast.h>

typedef bool (*t_parse_tree_func)(SIOContext&, SIOTokenType /*Last token*/, SIOTokenWalker&, AstNodeState&);
typedef bool (*t_parse_tree_handler)(SIOTokenType& type, bool&, t_parse_tree_func&, AstNodeState& state);

bool tree_parse_token(SIOContext& ctx, SIOTokenWalker& walker, t_parse_tree_handler handler, AstNodeState& state);

#ifdef SIO_DEBUG
#define SIO_TREE_DEBUG_INFO(name, body) state.debug_info = { name, body }
#else
#define SIO_TREE_DEBUG_INFO(name, body)
#endif // SIO_DEBUG