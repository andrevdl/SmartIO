#include "SIODotDebugger.h"

uint64_t SIODotDebugger::get_uuid()
{
	if (uuid_counter == ULLONG_MAX)
	{
		uuid_counter = 0;
	}
	else
	{
		++uuid_counter;
	}
	return uuid_counter;
}

void SIODotDebugger::store_link(uint64_t uuid)
{
	if (path.size() > 0)
	{
		buffer << path.top() << "->" << uuid << endl;
	}
	else
	{
		buffer << "root->" << uuid << endl;
	}
}

void SIODotDebugger::close_node()
{
	if (path.size() > 0)
	{
		path.pop();
	}
}

void SIODotDebugger::clear()
{
	buffer.clear();
}

const void SIODotDebugger::print(ostream& os) const
{
	os << "digraph G {" << endl;
	os << "root[shape = record label = \"root\"];" << endl;
	os << buffer.str();
	os << "}" << endl;
}

string SIODotDebugger::str()
{ 
	stringstream ss;
	print(ss);

	return ss.str();
}

ostream& operator<<(ostream& os, const SIODotDebugger& debugger)
{
	debugger.print(os);
	return os;
}
