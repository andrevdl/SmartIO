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

bool SIOArgParser::find_arg_by_name(string name, sio_arg_value& val)
{
	unordered_map<string, sio_arg_value>::const_iterator got = args.find(name);
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
	return (options & SIOArgOption::WINDOWS_STYLE && f == '/') || (options & SIOArgOption::UNIX_STYLE && f == '-');
}

SIOArgState SIOArgParser::store_arg(SIOArgSwitch* s, char* val, set<int>& filled, set<int>& missing, set<int>& forbidden)
{
	filled.insert(s->pos);
	if (missing.contains(s->pos))
	{
		missing.erase(s->pos);
	}

	if (forbidden.contains(s->pos))
	{
		return SIOArgState::FORBIDDEN;
	}

	for (int f : s->exclude)
	{
		if (!forbidden.contains(f))
		{
			forbidden.insert(f);
		}
	}

	for (int d : s->dep)
	{
		if (!filled.contains(d) && !missing.contains(d))
		{
			missing.insert(d);
		}
	}

	SIOArgState r = SIOArgState::VALID;

	string str = val;
	bool b_val = false;

	sio_arg_value arg_val;
	if (!str2arg_value(s->kind, val, arg_val))
	{
		return SIOArgState::INCORRECT_VALUE;
	}

	if (s->kind == SIOArgKind::FILE_WITH_EXISTS_CHECK)
	{
		// TODO: xxx
	}
	else if (s->kind == SIOArgKind::FOLDER_WITH_EXISTS_CHECK)
	{
		// TODO: xxx
	}

	if (r == SIOArgState::VALID && s->validator != nullptr && !s->validator(arg_val))
	{
		return SIOArgState::INCORRECT_VALUE;
	}

	if (r == SIOArgState::VALID)
	{
		args.insert(make_pair(s->name, arg_val));
	}

	return r;
}

SIOArgSwitch* SIOArgParser::_add_switch(string name, string desc, SIOArgKind kind, bool req, t_sio_arg_validator validator)
{
	SIOArgSwitch* sw = new SIOArgSwitch(name, desc, kind, req, max_index++, validator);

	switch_by_name.insert(make_pair(name, sw));
	switch_by_index.push_back(sw);

	return sw;
}

SIOArgParser::SIOArgParser(string desc, int8_t options)
{
	this->desc = desc;
	this->options = options;

	if (!(options & SIOArgOption::WINDOWS_STYLE) && !(options & SIOArgOption::UNIX_STYLE))
	{
		options |= SIOArgOption::WINDOWS_STYLE | SIOArgOption::UNIX_STYLE;
	}
}

SIOArgParser::~SIOArgParser()
{
	for (SIOArgSwitch* sw : switch_by_index)
	{
		delete sw;
	}
}

bool SIOArgParser::parse(int argc, char* argv[], sio_arg_parse_result& result)
{
	args.clear();
	result.clear();

	int p = 0;

	set<int> filled;
	set<int> missing;
	set<int> forbidden;

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

			// peek next one
			if (i + 1 < argc && !is_switch(argv[i + 1]))
			{
				// Always eat the parameter, even if unkown
				val = argv[i + 1];
				++i;
			}
		}
		else if (i < max_index)
		{
			s = find_switch_by_index(p);
			val = argv[i];
		}
		else
		{
			// Nothing left for use
			if (options & SIOArgOption::STRICT_MODE)
			{
				result.push_back(make_tuple(nullptr, SIOArgState::UNKNOWN));
				return false;
			}
			break;
		}

		if (s != nullptr)
		{
			p = s->pos + 1;

			SIOArgState state = store_arg(s, val, filled, missing, forbidden);
			if (state != SIOArgState::VALID)
			{
				result.push_back(make_tuple(s, state));
				return false;
			}
		}
		else if (options & SIOArgOption::STRICT_MODE)
		{
			result.push_back(make_tuple(nullptr, SIOArgState::UNKNOWN));
			return false;
		}
	}

	if (missing.size() > 0)
	{
		for (int m : missing)
		{
			result.push_back(make_tuple(switch_by_index[m], SIOArgState::MISSING));
		}
	}

	return missing.size() == 0;
}

SIOArgSwitch* SIOArgParser::add_switch(string name, string desc, SIOArgKind kind, bool req, t_sio_arg_validator validator)
{
	return _add_switch(name, desc, kind, req, validator);
}

SIOArgSwitch* SIOArgParser::add_or_get_switch(string name, string desc, SIOArgKind kind, bool req, t_sio_arg_validator validator)
{
	SIOArgSwitch* sw = get_switch(name);
	if (sw == nullptr)
	{
		return add_switch(name, desc, kind, req, validator);
	}

	return sw;
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
	sio_arg_value temp;
	return find_arg_by_name(name, temp);
}

bool SIOArgParser::try_get_arg(string name, sio_arg_value& value)
{
	return find_arg_by_name(name, value);
}

SIOArgSwitch::SIOArgSwitch(string name, string desc, SIOArgKind kind, bool req, int pos, t_sio_arg_validator validator) :
	name(name), pos(pos), kind(kind), required(req), validator(validator)
{
	assert(name != "");
}

bool SIOArgSwitch::add_dependency(SIOArgSwitch* sw)
{
	if (pos == sw->pos || dep.contains(sw->pos) || exclude.contains(sw->pos))
	{
		return false;
	}

	dep.insert(sw->pos);
	return true;
}

bool SIOArgSwitch::add_exclude(SIOArgSwitch* sw)
{
	if (pos == sw->pos || dep.contains(sw->pos) || exclude.contains(sw->pos))
	{
		return false;
	}

	exclude.insert(sw->pos);
	return true;
}

bool str2bool_arg_value(const char* raw, sio_arg_value& val)
{
	bool b;
	if (try_str2bool(raw, b))
	{
		val = b;
		return true;
	}

	val = false;
	return false;
}

bool str2int_arg_value(const char* raw, sio_arg_value& val)
{
	int i;
	if (try_str2int32(raw, i))
	{
		val = i;
		return true;
	}

	val = 0;
	return false;
}

bool str2uint_arg_value(const char* raw, sio_arg_value& val)
{
	unsigned int i;
	if (try_str2uint32(raw, i))
	{
		val = i;
		return true;
	}

	val = 0;
	return false;
}

bool str2float_arg_value(const char* raw, sio_arg_value& val)
{
	float f;
	if (try_str2float(raw, f))
	{
		val = f;
		return true;
	}

	val = 0;
	return false;
}

bool str2str_arg_value(const char* raw, sio_arg_value& val)
{
	val = raw;
	return true;
}

bool str2arg_value(SIOArgKind kind, const char* raw, sio_arg_value& val)
{
	switch (kind)
	{
	case SIOArgKind::BOOL:
		return str2bool_arg_value(raw, val);
	case SIOArgKind::INT:
		return str2int_arg_value(raw, val);
	case SIOArgKind::UINT:
		return str2uint_arg_value(raw, val);
	case SIOArgKind::FLOAT:
		return str2float_arg_value(raw, val);
	case SIOArgKind::STRING:
		return str2str_arg_value(raw, val);
	case SIOArgKind::FILE:
		return str2str_arg_value(raw, val);
	case SIOArgKind::FOLDER:
		return str2str_arg_value(raw, val);
	case SIOArgKind::FILE_WITH_EXISTS_CHECK:
		return str2str_arg_value(raw, val);
	case SIOArgKind::FOLDER_WITH_EXISTS_CHECK:
		return str2str_arg_value(raw, val);
	}

	return false;
}
