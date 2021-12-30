/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <parser/sio_dfa_parser.h>

bool tree_stmt_var(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_stmt_assign(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_stmt_if(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_stmt_while(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_stmt_io_add(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_stmt_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);