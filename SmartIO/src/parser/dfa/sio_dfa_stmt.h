#pragma once

#include "sio_dfa_tree.h"

bool tree_stmt_var(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_stmt_assign(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_stmt_if(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);
bool tree_stmt_while(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_stmt_io_add(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);

bool tree_stmt_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func, AstNodeState& state);