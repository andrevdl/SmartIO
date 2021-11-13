#pragma once

#include "sio_common.h"
#include "sio_id.h"

bool tree_expr(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr2_add(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr2_min(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_term(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_term2_mul(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_term2_div(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_factor_nested(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_factor_val(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_expr_factor_literal(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr_term_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr_term2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);
bool tree_expr_factor_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);