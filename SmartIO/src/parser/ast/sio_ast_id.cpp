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
