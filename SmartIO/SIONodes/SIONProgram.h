#pragma once

#include "SIONCommon.h"

class SIONProgram : public SIONonTerminalNode
{
private:
	SIOBaseNode* base = 0;
public:
	SIONProgram(SIONonTerminalNode* parent) : SIONonTerminalNode(parent) {}

	bool parse(SIOTokenWalker& walker);

	friend ostream& operator<<(ostream& os, const SIONProgram& node);

	//void print_dot_graph(SIOBaseNode* node);
};