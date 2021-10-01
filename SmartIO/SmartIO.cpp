// SmartIO.cpp : Defines the entry point for the application.
//

#include "SmartIO.h"

#include <iostream>

#include "SIOTokenizer.h"
#include "SIOParser.h"
#include "SIONodes/SIONCommon.h"

using namespace std;

int main()
{
	//string text = "(0)==(2)==3"; // should throw an error
	//string text = "(4 == 5) == 7"; // should work
	//string text = "(2 / (5 - 4) - x(y[n][r] + j(o)[u], z + p + q().m)) == 99"; // == 99 is missing in the tree
	//string text = "5 && (2 == ((3 + 4) + 7))";

	string text;

	cout << "Provided statement (exit, for closing): ";
	getline(cin, text);

	while (text != "exit")
	{
		if (text != "")
		{
			SIOTokenizer tokenizer(text);

			string err = "";
			if (tokenizer.tokenize(err))
			{
				cout << "scanning success" << endl << endl;
				cout << tokenizer << endl;

				SIOParser parser(&tokenizer);
				SIONProgram* node = parser.parse(err);

				if (node != nullptr)
				{
					cout << "parsing success" << endl << endl << *node;
					//cout << "parsing success" << endl << endl << *node;
					//SIOParser::print(node);
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

		cout << "Provided statement (exit, for closing): ";
		getline(cin, text);
	}

	return 0;
}
