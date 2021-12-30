#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <variant>

using namespace std;

enum class SIOArgKind
{
	BOOL,
	INT,
	FLOAT,
	STRING,
	PATH
};

class SIOArgParser
{
private:
	unordered_map<string, string> raw_args;
	unordered_map<string, string> args;
public:
	SIOArgParser();

	void parse(int argc, char* argv[]);

	bool add_switch(string name, SIOArgKind kind);

	bool has_arg(string name);
	bool get_arg(string name, vector<string> results);
};