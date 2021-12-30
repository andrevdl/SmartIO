/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>

#include <parser/ast/sio_ast.h>
#include <parser/sio_tokenizer.h>
#include <parser/sio_token_walker.h>
#include <sio_log.h>
#include <sio_context.h>

#include <parser/dfa/sio_dfa_expr.h>

using namespace std;

class SIOParser
{
private:
	SIOTokenWalker walker;
	SIOLogger* logger;
public:
	SIOParser(SIOTokenizer* tokenizer, SIOLogger* logger);

	bool parse(SIOContext* ctx);
};