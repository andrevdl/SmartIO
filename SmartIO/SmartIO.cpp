// SmartIO.cpp : Defines the entry point for the application.
//

#include "SmartIO.h"

#include "SIOTokenizer.h"

using namespace std;

int main()
{
	string text = "x /= 2";
	SIOTokenizer tokenizer(text);

	string err = "";
	if (tokenizer.tokenize(err))
	{
		cout << "success" << endl << endl;
	}
	else
	{
		cout << "error" << endl << endl;
	}

	cout << tokenizer;

	return 0;
}
