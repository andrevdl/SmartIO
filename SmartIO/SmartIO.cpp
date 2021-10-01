// SmartIO.cpp : Defines the entry point for the application.
//

#include "SmartIO.h"

#include "SIOTokenizer.h"
#include "SIOParser.h"
#include "SIONodes/SIONCommon.h"

using namespace std;

int main()
{
	string text = "2 / (5 - 4) - x(y[n][r] + j(o)[u], z + p + q().m)";
	//string text = "x(y[n][r])"; // parse error
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

	return 0;
}
