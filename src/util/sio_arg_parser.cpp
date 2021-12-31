#include "sio_arg_parser.h"

SIOArgSwitch* SIOArgParser::find_switch_by_name(char* name)
{
	string s_name = name;
	s_name = s_name.substr(1);

	return get_switch(s_name);
}

SIOArgSwitch* SIOArgParser::find_switch_by_index(int index)
{
	if (index >= 0 && index <= max_index)
	{
		return switch_by_index[index];
	}

	return nullptr;
}

bool SIOArgParser::find_arg_by_name(string name, arg_value val)
{
	unordered_map<string, arg_value>::const_iterator got = args.find(name);
	if (got != args.end())
	{
		val = got->second;
		return true;
	}

	return false;
}

bool SIOArgParser::is_switch(char* name)
{
	char f = name[0];
	return (style & SIOArgStyle::WINDOWS && f == '/') || (style & SIOArgStyle::UNIX && f == '-');
}

bool SIOArgParser::store_arg(SIOArgSwitch* s, char* val, set<int>& filled, set<int>& missing)
{
	bool r = true;

	if (missing.contains(s->pos))
	{
		missing.erase(s->pos);
	}

	for (int d : s->dep)
	{
		if (!filled.contains(d) && !missing.contains(d))
		{
			missing.insert(d);
		}
	}

	// TODO: validate type => may change r
	string x = val;
	args.insert(make_pair(s->name, x)); // change value => use type for casting

	return r;
}

SIOArgSwitch* SIOArgParser::_add_switch(string name, string desc, SIOArgKind kind, bool req)
{
	SIOArgSwitch* sw = new SIOArgSwitch();
	sw->name = name;
	sw->pos = max_index++;
	sw->kind = kind;
	sw->required = req;

	switch_by_name.insert(make_pair(name, sw));
	switch_by_index.push_back(sw);

	return sw;
}

void SIOArgParser::add_switch_dep(SIOArgSwitch* s, SIOArgSwitch* dep)
{
	s->dep.insert(dep->pos);
}

SIOArgParser::SIOArgParser(string desc, int8_t style)
{
	this->desc = desc;
	this->style = style;
}

SIOArgParser::~SIOArgParser()
{
	for (SIOArgSwitch* sw : switch_by_index)
	{
		delete sw;
	}
}

bool SIOArgParser::parse(int argc, char* argv[], vector<SIOArgSwitch*>& sw_missing, bool strict)
{
	args.clear();
	sw_missing.clear();

	int p = 0;

	set<int> filled;
	set<int> missing;

	// Insert all required args into missing
	for (SIOArgSwitch* rsw : switch_by_index)
	{
		if (rsw->required)
		{
			missing.insert(rsw->pos);
		}
	}

	// Skip your own path thing
	for (int i = 1; i < argc; i++)
	{
		SIOArgSwitch* s = nullptr;
		char* val = nullptr;

		if (is_switch(argv[i]))
		{
			s = find_switch_by_name(argv[i]);
		}
		else if (i < max_index)
		{
			s = find_switch_by_index(p);
		}
		else
		{
			// Nothing left for use
			if (strict)
			{
				return false;
			}
			break;
		}

		// peek next one
		if (i + 1 < argc && !is_switch(argv[i + 1]))
		{
			// Always eat the parameter, even if unkown
			val = argv[i + 1];
			++i;
		}

		if (s != nullptr)
		{
			p = s->pos + 1;
			filled.insert(s->pos);

			if (!store_arg(s, val, filled, missing))
			{
				return false;
			}
		}
		else if (strict)
		{
			return false;
		}
	}

	if (missing.size() > 0)
	{
		for (int m : missing)
		{
			sw_missing.push_back(switch_by_index[m]);
		}
	}

	return missing.size() == 0;
}

SIOArgSwitch* SIOArgParser::add_switch(string name, string desc, SIOArgKind kind, bool req)
{
	return _add_switch(name, desc, kind, req);
}

SIOArgSwitch* SIOArgParser::get_switch(string name)
{
	unordered_map<string, SIOArgSwitch*>::const_iterator got = switch_by_name.find(name);
	if (got != switch_by_name.end())
	{
		return got->second;
	}

	return nullptr;
}

bool SIOArgParser::has_arg(string name)
{
	arg_value temp;
	return find_arg_by_name(name, temp);
}

bool SIOArgParser::get_arg(string name, arg_value& value)
{
	return find_arg_by_name(name, value);
}
