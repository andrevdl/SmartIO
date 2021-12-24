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