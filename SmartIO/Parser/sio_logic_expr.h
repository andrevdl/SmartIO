#pragma once

#include "sio_common.h"
#include "sio_expr.h"

bool tree_logic_expr(SIOTokenWalker& walker, void* dest);
bool tree_logic_expr2(SIOTokenWalker& walker, void* dest);
bool tree_logic_compare(SIOTokenWalker& walker, void* dest);
bool tree_logic_compare2(SIOTokenWalker& walker, void* dest);
bool tree_logic_unit(SIOTokenWalker& walker, void* dest);
bool tree_logic_unit_not(SIOTokenWalker& walker, void* dest);
bool tree_logic_unit2(SIOTokenWalker& walker, void* dest);
bool tree_logic_unit2_nested(SIOTokenWalker& walker, void* dest);
bool tree_logic_expr_expr(SIOTokenWalker& walker, void* dest);
bool tree_logic_expr_expr_nested(SIOTokenWalker& walker, void* dest);
bool tree_logic_expr_expr2(SIOTokenWalker& walker, void* dest);
bool tree_logic_expr_expr2_not(SIOTokenWalker& walker, void* dest);

bool tree_logic_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_logic_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_logic_compare_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_logic_compare2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_logic_expr_unit_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_logic_expr_unit2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_logic_expr_expr_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_logic_expr_expr2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);