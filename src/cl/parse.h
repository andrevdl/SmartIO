#pragma once

#include "core.h"

class SIOCLParseModule : public SIOCLModule
{
public:
	virtual void init(SIOArgParser& parser);
	virtual void execute(SIOArgParser& parser);

	virtual const char* get_switch_name();
};