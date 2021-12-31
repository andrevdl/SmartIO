#pragma once

#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <variant>
#include <cstdarg>

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

struct SIOArgSwitch // TODO: make everything readonly
{
	string name;
	string desc;
	
	SIOArgKind kind = SIOArgKind::BOOL;
	bool required = false;
	int pos = 0;

	set<int> dep;
};

enum SIOArgStyle: int8_t
{
	UNIX = 1,
	WINDOWS = 2
};

typedef variant<bool, int, float, string> arg_value;

class SIOArgParser // TODO: add man page system...
{
private:
	int8_t style;
	string desc; // TODO: add a getter

	unordered_map<string, arg_value> args;

	unordered_map<string, SIOArgSwitch*> switch_by_name;
	vector<SIOArgSwitch*> switch_by_index;

	int max_index = 0;

	SIOArgSwitch* find_switch_by_name(char* name);
	SIOArgSwitch* find_switch_by_index(int index);

	bool find_arg_by_name(string name, arg_value val);

	bool is_switch(char* name);
	bool store_arg(SIOArgSwitch* s, char* val, set<int>& filled, set<int>& missing);

	SIOArgSwitch* _add_switch(string name, string desc, SIOArgKind kind, bool req);
	void add_switch_dep(SIOArgSwitch* s, SIOArgSwitch* dep);
public:
	SIOArgParser(string desc, int8_t style = SIOArgStyle::UNIX | SIOArgStyle::WINDOWS);
	~SIOArgParser();

	bool parse(int argc, char* argv[], vector<SIOArgSwitch*>& sw_missing, bool strict = false);

	SIOArgSwitch* add_switch(string name, string desc, SIOArgKind kind, bool req = false);

	template<typename... Args>
	SIOArgSwitch* add_switch(string name, string desc, SIOArgKind kind, bool req, Args... args);

	SIOArgSwitch* get_switch(string name);

	bool has_arg(string name);
	bool get_arg(string name, arg_value& value); // TODO: add subtypes, based on the variant
};

template<typename ...Args>
inline SIOArgSwitch* SIOArgParser::add_switch(string name, string desc, SIOArgKind kind, bool req, Args ...args)
{
	SIOArgSwitch* sw = _add_switch(name, desc, kind, req);
	add_switch_dep(sw, args...);

	return sw;
}