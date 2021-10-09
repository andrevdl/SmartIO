#pragma once

//#define PRE_COMPILER_CONST_INT(name, val) \
//	constexpr uint64_t __sio_version_name = val; \
//	constexpr char "__sio_name";
//
//PRE_COMPILER_CONST_INT(version, 1)

#define	RET_DELETE_AND_NULL(v) delete v; return nullptr;

#define CLASSNAME(o) typeid(*o).name()
#define CLASSNAME_THIS CLASSNAME(this)

#define _DEFINE_BIT_MASK(name, pos, size) constexpr size name = 1 << pos
#define DEFINE_BIT_MASK(name, pos) _DEFINE_BIT_MASK(name, pos, char)

#define BIT_SET(set, val) (set & val) != 0
#define BIT_NOT_SET(set, val) (set & val) == 0