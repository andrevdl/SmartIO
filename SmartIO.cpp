/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

// SmartIO.cpp : Defines the entry point for the application.
//

#include "SmartIO.h"

#include <iostream>

#include <cl/core.h>
#include <cl/parse.h>

using namespace std;

constexpr int NO_TASK_FOUND = 1;
constexpr int INVALID_PARAMETERS = 2;

int main(int argc, char* argv[])
{
	SIOArgParser main_parser("");
	main_parser.add_switch("task", "", SIOArgKind::STRING);
	main_parser.add_switch("help", "", SIOArgKind::BOOL);

	SIOCLModule* m = nullptr;
	
	sio_arg_parse_result arg_err;
	if (main_parser.parse(argc, argv, arg_err))
	{
		string task;
		if (main_parser.get_arg<bool>("help", false))
		{
			// show help page
			return 0;
		}
		else if (main_parser.try_get_arg<string>("task", task))
		{
			m = new SIOCLParseModule(); // todo: load the correct tool => reg system or glob object...
		}
	}
	else
	{
		for (tuple<SIOArgSwitch*, SIOArgState> x : arg_err) // -> abstract this code => same as common tools, make common error handling args
		{
			SIOArgSwitch* l_sw = get<0>(x);
			if (l_sw != nullptr)
			{
				cout << l_sw->name << endl;
			}
		}

		return INVALID_PARAMETERS;
	}

	if (m != nullptr)
	{
		SIOArgParser module_arg_parser("");
		m->init(module_arg_parser);

		if (module_arg_parser.parse(argc, argv, arg_err))
		{
			m->execute(module_arg_parser);
		}
		else
		{
			for (tuple<SIOArgSwitch*, SIOArgState> x : arg_err)
			{
				SIOArgSwitch* l_sw = get<0>(x);
				if (l_sw != nullptr)
				{
					cout << l_sw->name << endl;
				}
			}

			return INVALID_PARAMETERS;
		}
	}
	else
	{
		// show error ...
		return NO_TASK_FOUND;
	}

	//SIOArgSwitch* file_sw = main_parser.add_switch("file", "", SIOArgKind::FILE);

	//SIOArgSwitch* repl_sw = main_parser.add_switch("repl", "", SIOArgKind::BOOL, true);
	//repl_sw->add_dependencies(file_sw);

	//sio_arg_parse_result arg_err;
	//bool r = main_parser.parse(argc, argv, arg_err);

	//sio_arg_value v;
	//if (main_parser.try_get_arg("repl", v))
	//{
	//	cout << get<string>(v);
	//}

	//cout << parser.get_arg<string>("repl", "xxx");

	return 0;
}
