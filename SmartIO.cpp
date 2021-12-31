﻿/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

// SmartIO.cpp : Defines the entry point for the application.
//

#include "SmartIO.h"

#include <iostream>

#include <parser/sio_tokenizer.h>
#include <parser/sio_parser.h>
#include <parser/sio_dfa_parser.h>
#include <sio_context.h>
#include <sio_define.h>
#include <sio_memory.h>

#include <compiler/sio_ast_walker.h>

#include <runtime/sio_vm.h>
#include <runtime/sio_native.h>

#include <util/sio_arg_parser.h>

using namespace std;

int main(int argc, char* argv[])
{

	SIOArgParser parser("");
	parser.add_switch("help", "", SIOArgKind::BOOL);
	SIOArgSwitch* file_sw = parser.add_switch("file", "", SIOArgKind::FILE);
	parser.add_switch("repl", "", SIOArgKind::BOOL, true, file_sw);

	vector<SIOArgSwitch*> arg_err;
	bool r = parser.parse(argc, argv, arg_err);

	for (SIOArgSwitch* x : arg_err)
	{
		cout << x->name << endl;
	}

	arg_value v;	
	if (parser.get_arg("repl", v))
	{
		cout << get<string>(v); // TODO: something goes wrong !!
	}

	return 0;

	// --------------- Above code will be the new interface, everthing else will be moved --------------- //

	SIOLogger* logger = new SIOConsoleLogger();
	SIOContext* context = new SIOContext(logger);
	
	string text;

	cout << "Provided statement (exit, for closing): ";
	getline(cin, text);

	while (text != "exit")
	{
		if (text != "")
		{
			SIOTokenizer tokenizer(text, context, logger);
			logger->set_section("Parsing");

			if (tokenizer.tokenize())
			{
				//cout << tokenizer << endl; // dumps the parsed token list

				SIOParser parser(&tokenizer, logger);
				logger->set_section("Compiling");

				if (parser.parse(context))
				{
#ifdef SIO_DEBUG
					cout << endl << *(context->get_dot_tree_debugger());
#endif // SIO_DEBUG
				}
			}
		}

		// clear console
		//std::cout << "\x1B[2J\x1B[H";
#ifdef SIO_DEBUG
		context->get_dot_tree_debugger()->clear();
#endif // SIO_DEBUG

		cout << endl << "Provided statement (exit, for closing): ";
		getline(cin, text);
	}

	return 0;
}
