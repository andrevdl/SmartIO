#pragma once

#include "sio_common.h"
#include "sio_id.h"

bool tree_expr(SIOTokenWalker& walker, void* dest);
bool tree_expr2_add(SIOTokenWalker& walker, void* dest);
bool tree_expr2_min(SIOTokenWalker& walker, void* dest);
bool tree_expr_term(SIOTokenWalker& walker, void* dest);
bool tree_expr_term2_mul(SIOTokenWalker& walker, void* dest);
bool tree_expr_term2_div(SIOTokenWalker& walker, void* dest);
bool tree_expr_factor_nested(SIOTokenWalker& walker, void* dest);
bool tree_expr_factor_val(SIOTokenWalker& walker, void* dest);
bool tree_expr_factor_literal(SIOTokenWalker& walker, void* dest);

bool tree_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_expr_term_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_expr_term2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_expr_factor_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);