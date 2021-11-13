#pragma once

#include <string>
#include "../../SIOTokens.h"

using namespace std;

class SIOTreeRule;

class SIOTreeBranch
{
	string name;
	SIOToken* tokens = 0;
	SIOTreeRule* rules = 0;
	//

public:
	SIOTreeBranch(string name, SIOTreeRule* rules);
	SIOTreeBranch(string name, SIOToken* tokens, SIOTreeRule* rules);
};

class SIOTreeRule
{
	string name;
	SIOTreeBranch* branches;
	bool allow_empty
};

class SIOTreeGen
{
public:
	SIOTreeRule create_rule(string name, SIOTreeBranch* branches, bool allow_empty)
};

//
// Example syntax
// 
// SIOTreeBranch branch = new SIOTreeBranch("Compare", [SIOTokenType::EQUAL, SIOTokenType::BRANCH, SIOTokenType::NOT_EQUAL], [my_branch]);
// BRANCH = ALIAS + PLACEHOLDER