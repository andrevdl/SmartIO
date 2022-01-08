#pragma once

#include <util/sio_arg_parser.h>

class SIOCLModule
{
public:
	virtual void init(SIOArgParser& parser) = 0;
	virtual void execute(SIOArgParser& parser) = 0;

	virtual const char* get_switch_name() = 0;
};