#pragma once

#include "sio_common.h"

// temp
#include "sio_expr.h"
#include "sio_logic_expr.h"
#include "sio_id.h"

#include "ast/sio_ast.h"

extern bool create_parse_tree(SIOContext& ctx, SIOTokenType last, SIOTokenWalker& walker, AstNodeState& state);