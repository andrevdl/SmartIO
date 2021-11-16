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

using namespace std;

int main()
{
	SIOSet bit_array;

	bit_array.set_bit(240);
	bool xy = bit_array.get_bit(240);

	///////////////

	//string text = "(0)==(2)==3"; // should throw an error
	//string text = "(4 == 5) == 7"; // should work
	//string text = "(2 / (5 - 4) - x(y[n][r] + j(o)[u], z + p + q().m)) == 99"; // == 99 is missing in the tree
	//string text = "5 && (2 == ((3 + 4) + 7))";

	// mod: (2 / (5 - 4) - x().m) == 99

	SIOContext* context = new SIOContext();

	string text;

	cout << "Provided statement (exit, for closing): ";
	getline(cin, text);

	while (text != "exit")
	{
		if (text != "")
		{
			SIOTokenizer tokenizer(text, context);

			string err = "";
			if (tokenizer.tokenize(err))
			{
				cout << "scanning success" << endl << endl;
				cout << tokenizer << endl;

				SIOParser parser(&tokenizer);
				if (parser.parse(context, err))
				{
#ifdef SIO_DEBUG
					cout << "parsing success" << endl << endl << *(context->get_dot_tree_debugger());
#else
					cout << "parsing success" << endl << endl;
#endif // SIO_DEBUG
				}
				else
				{
					cout << "parsing error" << endl << endl;
				}

			}
			else
			{
				cout << "scanning error" << endl << endl;
				cout << tokenizer << endl;
			}
		}

		// clear console
		std::cout << "\x1B[2J\x1B[H";
#ifdef SIO_DEBUG
		context->get_dot_tree_debugger()->clear();
#endif // SIO_DEBUG

		cout << "Provided statement (exit, for closing): ";
		getline(cin, text);
	}

	return 0;
}
