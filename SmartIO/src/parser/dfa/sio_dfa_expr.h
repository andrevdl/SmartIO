/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "sio_dfa_tree.h"
#include "sio_dfa_id.h"

// visitors
bool tree_expr_compare(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_compare_eq(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_compare_neq(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_expr_logic_low(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_logic_or(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_expr_logic_high(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_logic_and(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_expr_arith(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_arith_add(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_arith_min(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_expr_term(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_term2_mul(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_term2_div(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_expr_factor(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_factor_inverse(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_expr_factor_nested(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_factor_val(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_factor_literal(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

// handlers
bool tree_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state); // interface;

bool tree_expr_compare_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr_compare2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);

bool tree_expr_logic_low_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr_logic_low2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);

bool tree_expr_logic_high_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr_logic_high2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);

bool tree_expr_arith_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr_arith2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);

bool tree_expr_term_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr_term2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);

bool tree_expr_factor_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr_factor2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);