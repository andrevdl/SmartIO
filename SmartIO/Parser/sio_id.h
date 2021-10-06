#pragma once

#include "sio_common.h"

bool tree_id(SIOTokenWalker& walker, void* dest);
bool tree_id2_call(SIOTokenWalker& walker, void* dest);
bool tree_id2_array(SIOTokenWalker& walker, void* dest);
bool tree_id2_chain(SIOTokenWalker& walker, void* dest);
bool tree_array(SIOTokenWalker& walker, void* dest);
bool tree_array_chain(SIOTokenWalker& walker, void* dest);
bool tree_id_chain(SIOTokenWalker& walker, void* dest);

bool tree_id_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_id2_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_array_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);
bool tree_id_chain_handler(SIOTokenType& type, bool& eat, t_parse_tree_func& func);