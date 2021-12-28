/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <parser/ast/sio_ast.h>

class SIOAstLiteral : public SIOAst
{
public:
	uintptr_t val; // debug

	void print(SIODotDebugger* debugger, SIOContext* ctx)
	{
		debugger->create_node("Literal", to_string(val));
		debugger->close_node();
	}

	const AstNodeType get_type()
	{
		return AstNodeType::LITERAL;
	}
};

class SIOAstValue : public SIOAst
{
public:
	uintptr_t val; // debug

	void print(SIODotDebugger* debugger, SIOContext* ctx)
	{
		debugger->create_node("Value", to_string(val));
		debugger->close_node();
	}

	const AstNodeType get_type()
	{
		return AstNodeType::VALUE;
	}
};