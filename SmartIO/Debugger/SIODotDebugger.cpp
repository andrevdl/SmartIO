#include "SIODotDebugger.h"

uint64_t SIODotDebugger::get_uuid()
{
	static uint64_t uuid = 0;
	if (uuid == ULLONG_MAX)
	{
		uuid = 0;
	}
	else
	{
		++uuid;
	}
	return uuid;
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

ostream& operator<<(ostream& os, const SIODotDebugger& debugger)
{
	debugger.print(os);
	return os;
}
