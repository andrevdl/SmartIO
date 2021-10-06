#include "SIOParser.h"

SIOParser::SIOParser(SIOTokenizer* tokenizer) : walker(tokenizer)
{
	
}

bool SIOParser::parse(string& error)
{
	//bool success = true;
	//SIONProgram* program = new SIONProgram(nullptr);

	//if (program->parse(walker))
	//{
	//	return program;
	//}

	void* temp = nullptr;
	return create_parse_tree(walker, temp);

	//RET_DELETE_AND_NULL(program);
}

//void SIOParser::print(SIOBaseNode* node)
//{
//	cout << "digraph G {" << endl;
//	cout << "root[shape = record label = \"root\"];" << endl;
//	cout << *node;
//	cout << "}" << endl;
//}
