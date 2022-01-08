#include "parse.h"

//#include <parser/sio_tokenizer.h>
//#include <parser/sio_parser.h>
//#include <parser/sio_dfa_parser.h>
//#include <sio_context.h>
//#include <sio_define.h>
//#include <sio_memory.h>
//
//#include <compiler/sio_ast_walker.h>
//
//#include <runtime/sio_vm.h>
//#include <runtime/sio_native.h>

void SIOCLParseModule::init(SIOArgParser& parser)
{
    parser.add_switch("file", "", SIOArgKind::FILE, true);

    parser.add_switch("print_parse_tokens", "", SIOArgKind::BOOL);
    parser.add_switch("print_ast", "", SIOArgKind::BOOL);

    parser.add_switch("store_parse_tokens", "", SIOArgKind::FILE);
    parser.add_switch("store_ast", "", SIOArgKind::FILE);
}

void SIOCLParseModule::execute(SIOArgParser& parser)
{
    // https://en.cppreference.com/w/cpp/filesystem#Notes
}

const char* SIOCLParseModule::get_switch_name()
{
    return nullptr;
}

//// --------------- Above code will be the new interface, everthing else will be moved --------------- //
//
//SIOLogger* logger = new SIOConsoleLogger();
//SIOContext* context = new SIOContext(logger);
//
//string text;
//
//cout << "Provided statement (exit, for closing): ";
//getline(cin, text);
//
//while (text != "exit")
//{
//	if (text != "")
//	{
//		SIOTokenizer tokenizer(text, context, logger);
//		logger->set_section("Parsing");
//
//		if (tokenizer.tokenize())
//		{
//			//cout << tokenizer << endl; // dumps the parsed token list
//
//			SIOParser parser(&tokenizer, logger);
//			logger->set_section("Compiling");
//
//			if (parser.parse(context))
//			{
//#ifdef SIO_DEBUG
//				cout << endl << *(context->get_dot_tree_debugger());
//#endif // SIO_DEBUG
//			}
//		}
//	}
//
//	// clear console
//	//std::cout << "\x1B[2J\x1B[H";
//#ifdef SIO_DEBUG
//	context->get_dot_tree_debugger()->clear();
//#endif // SIO_DEBUG
//
//	cout << endl << "Provided statement (exit, for closing): ";
//	getline(cin, text);
//}
//
//return 0;