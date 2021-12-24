#pragma once

#include <vector>

class CallInfo
{
	CallInfo* prev;
	CallInfo* next;
};

class SIOVMState
{
	std::vector<int> stack;
};