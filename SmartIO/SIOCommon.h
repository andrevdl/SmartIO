#pragma once

#include <string>

#include "SIOTokens.h"

using namespace std;

#define	RET_DELETE_AND_NULL(v) delete v; return nullptr;

#define CLASSNAME(o) typeid(*o).name()
#define CLASSNAME_THIS CLASSNAME(this)