/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "sio_ast_id.h"

void SIOAstId::print(SIODotDebugger* debugger, SIOContext* ctx)
{
	string str;
	ctx->load_str(name_ref, str);

	debugger->create_node("ID", str);
	if (next_id != nullptr)
	{
		next_id->print(debugger, ctx);
	}
	if (next_func != nullptr)
	{
		next_func->print(debugger, ctx);
	}
	if (arr != nullptr)
	{
		arr->print(debugger, ctx);
	}
	debugger->close_node();
}

void SIOAstFunction::print(SIODotDebugger* debugger, SIOContext* ctx)
{
	string str;
	ctx->load_str(name_ref, str);

	debugger->create_node("Function", str);
	for (auto it = childs->cbegin(); it != childs->cend(); ++it)
	{
		(*it)->print(debugger, ctx);
	}
	if (next_id != nullptr)
	{
		next_id->print(debugger, ctx);
	}
	if (next_func != nullptr)
	{
		next_func->print(debugger, ctx);
	}
	if (arr != nullptr)
	{
		arr->print(debugger, ctx);
	}
	debugger->close_node();
}

void SIOAstArray::print(SIODotDebugger* debugger, SIOContext* ctx)
{
	debugger->create_node("Indices", "");
	for (auto it = childs->cbegin(); it != childs->cend(); ++it)
	{
		(*it)->print(debugger, ctx);
	}
	if (arr != nullptr)
	{
		arr->print(debugger, ctx);
	}
	debugger->close_node();
}
