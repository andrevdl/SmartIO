#pragma once

#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <variant>
#include <cstdarg>
#include <assert.h>
#include <tuple>

#include <util/sio_utils.h>

using namespace std;

enum class SIOArgKind
{
	// Boolean (1, 0 or present)
	BOOL,
	// Signed int
	INT,
	// Unsigned int
	UINT,
	// Float/double 
	FLOAT,
	// String
	STRING,
	// Path to a file (without check if exists)
	FILE,
	// Path to a folder (without check if exists)
	FOLDER,
	// Path to a file (with check if exists)
	FILE_WITH_EXISTS_CHECK,
	// Path to a folder (with check if exists)
	FOLDER_WITH_EXISTS_CHECK
};

enum class SIOArgState
{
	VALID,
	FORBIDDEN,
	MISSING,
	INCORRECT_VALUE,
	UNKNOWN
};

typedef variant<bool, int, unsigned int, float, string> sio_arg_value;
typedef bool (*t_sio_arg_validator)(sio_arg_value val);

bool str2bool_arg_value(const char* raw, sio_arg_value& val);
bool str2int_arg_value(const char* raw, sio_arg_value& val);
bool str2uint_arg_value(const char* raw, sio_arg_value& val);
bool str2float_arg_value(const char* raw, sio_arg_value& val);
bool str2str_arg_value(const char* raw, sio_arg_value& val);

bool str2arg_value(SIOArgKind kind, const char* raw, sio_arg_value& val);

class SIOArgParser;

class SIOArgSwitch
{
	friend SIOArgParser;
private:
	set<int> dep;
	set<int> exclude;
	t_sio_arg_validator validator;
public:
	SIOArgSwitch(string name, string desc, SIOArgKind kind, bool req, int pos, t_sio_arg_validator validator);

	const string name;
	const string desc;
	
	const SIOArgKind kind;
	const bool required;
	const int pos;

	bool add_dependency(SIOArgSwitch* sw);
	bool add_exclude(SIOArgSwitch* sw);

	template<typename... Args>
	bool add_dependencies(Args... args);

	template<typename... Args>
	bool add_excludes(Args... args);
};

enum SIOArgOption: int8_t
{
	UNIX_STYLE = 1,
	WINDOWS_STYLE = 2,
	STRICT_MODE = 4,
	CASE_SENSITIVE = 8 // TODO: implement this feature => cap string support on ASCII characters
};

typedef vector<tuple<SIOArgSwitch*, SIOArgState>> sio_arg_parse_result;

class SIOArgParser // TODO: add man page system...
{
private:
	int8_t options;
	string desc; // TODO: add a getter

	unordered_map<string, sio_arg_value> args;

	unordered_map<string, SIOArgSwitch*> switch_by_name;
	vector<SIOArgSwitch*> switch_by_index;

	int max_index = 0;

	SIOArgSwitch* find_switch_by_name(char* name);
	SIOArgSwitch* find_switch_by_index(int index);

	bool find_arg_by_name(string name, sio_arg_value& val);

	bool is_switch(char* name);
	SIOArgState store_arg(SIOArgSwitch* s, char* val, set<int>& filled, set<int>& missing, set<int>& forbidden);

	SIOArgSwitch* _add_switch(string name, string desc, SIOArgKind kind, bool req, t_sio_arg_validator validator);
public:
	SIOArgParser(string desc, int8_t options = SIOArgOption::UNIX_STYLE | SIOArgOption::WINDOWS_STYLE);
	~SIOArgParser();

	bool parse(int argc, char* argv[], sio_arg_parse_result& result);

	SIOArgSwitch* add_switch(string name, string desc, SIOArgKind kind, bool req = false, t_sio_arg_validator validator = nullptr);

	SIOArgSwitch* get_switch(string name);

	bool has_arg(string name);
	bool try_get_arg(string name, sio_arg_value& value);

	template<typename T>
	bool try_get_arg(string name, T& value);

	template<typename T>
	T get_arg(string name, T def);
};

template<typename ...Args>
inline bool SIOArgSwitch::add_dependencies(Args ...args)
{
	return add_dependency(args...);
}

template<typename ...Args>
inline bool SIOArgSwitch::add_excludes(Args ...args)
{
	return add_exclude(args...);
}

template<typename T>
inline bool SIOArgParser::try_get_arg(string name, T& value)
{
	static_assert(is_same<T, bool>::value || is_same<T, int>::value || is_same<T, unsigned int>::value ||
		is_same<T, float>::value || is_same<T, string>::value, "Only type of bool, (unsigned) int, float or string allowed");
	
	sio_arg_value val;
	if (try_get_arg(name, val))
	{
		value = std::get<T>(val);
		return true;
	}

	return false;
}

template<typename T>
inline T SIOArgParser::get_arg(string name, T def)
{
	T val;
	if (!try_get_arg(name, val))
	{
		val = def;
	}

	return val;
}