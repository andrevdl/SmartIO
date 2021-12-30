/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "sio_dfa_tree.h"
#include "sio_dfa_expr.h"

bool tree_id(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_id_array(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_id_chain(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_id_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_id_func_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_id_array_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_id_chain_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);