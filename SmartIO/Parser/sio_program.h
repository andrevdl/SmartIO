#pragma once

#include "tree/sio_tree.h"

// temp
#include "tree/sio_expr.h"
//#include "sio_logic_expr.h"
#include "tree/sio_id.h"

#include "ast/sio_ast.h"

extern bool create_parse_tree(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);