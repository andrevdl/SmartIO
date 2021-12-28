// SmartIO.cpp : Defines the entry point for the application.
//

#include "SmartIO.h"

#include <iostream>

#include <parser/sio_tokenizer.h>
#include <parser/sio_parser.h>
#include <parser/dfa/sio_dfa_tree.h>
#include <sio_context.h>
#include <sio_define.h>
#include <sio_memory.h>

#include <compiler/sio_ast_walker.h>

#include <runtime/sio_vm.h>
#include <runtime/sio_native.h>

using namespace std;

int main()
{
	//SIOContext* context = new SIOContext();

	//sio_native_example_dynamic();
	//sio_native_testing(context);
	//sio_vm_exec();

	SIOContext* context = new SIOContext();
	SIOLogger* logger = new SIOConsoleLogger();

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
				else
				{
					cout << "parsing error" << endl << endl;
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
