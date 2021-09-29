#include "SIOParser.h"

SIOParser::SIOParser(SIOTokenizer* tokenizer) : walker(tokenizer)
{
	
}

SIONProgram* SIOParser::parse(string& error)
{
	bool success = true;
	SIONProgram* program = new SIONProgram(nullptr);

	if (program->parse(walker))
	{
		return program;
	}

	RET_DELETE_AND_NULL(program);
}

//void SIOParser::print(SIOBaseNode* node)
//{
//	cout << "digraph G {" << endl;
//	cout << "root[shape = record label = \"root\"];" << endl;
//	cout << *node;
//	cout << "}" << endl;
//}
