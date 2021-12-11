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
	SIOContext* context = new SIOContext();

	//sio_native_example_dynamic();
	sio_native_testing(context);
	//sio_vm_exec();

//	SIOContext* context = new SIOContext();
//
//	string text;
//
//	cout << "Provided statement (exit, for closing): ";
//	getline(cin, text);
//
//	while (text != "exit")
//	{
//		if (text != "")
//		{
//			SIOTokenizer tokenizer(text, context);
//
//			string err = "";
//			if (tokenizer.tokenize(err))
//			{
//				cout << "scanning success" << endl << endl;
//				cout << tokenizer << endl;
//
//				SIOParser parser(&tokenizer);
//				if (parser.parse(context, err))
//				{
//#ifdef SIO_DEBUG
//					cout << "parsing success" << endl << endl << *(context->get_dot_tree_debugger());
//#else
//					cout << "parsing success" << endl << endl;
//#endif // SIO_DEBUG
//				}
//				else
//				{
//					cout << "parsing error" << endl << endl;
//				}
//
//			}
//			else
//			{
//				cout << "scanning error" << endl << endl;
//				cout << tokenizer << endl;
//			}
//		}
//
//		// clear console
//		std::cout << "\x1B[2J\x1B[H";
//#ifdef SIO_DEBUG
//		context->get_dot_tree_debugger()->clear();
//#endif // SIO_DEBUG
//
//		cout << "Provided statement (exit, for closing): ";
//		getline(cin, text);
//	}

	return 0;
}
