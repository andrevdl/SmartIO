#pragma once

#include <parser/dfa/sio_dfa_tree.h>

// temp
#include <parser/dfa/sio_dfa_expr.h>
//#include "sio_logic_expr.h"
#include <parser/dfa/sio_dfa_id.h>

#include <parser/ast/sio_ast.h>

extern bool create_parse_tree(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);