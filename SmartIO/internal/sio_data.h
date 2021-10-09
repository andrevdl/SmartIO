#pragma once

#include "sio_define.h"

enum class SIODataType
{
	UNKNOWN, // At compile time unkown => not possible to compile
	VOID,    // Empty
	COMPLEX, // Can't be caputered within the language self => external symbols
	FSTRING, // Formatted/Function string => use as constant date/time
	
	INTEGER, // 64 bit integer (cast: double)
	DOUBLE,  // 64 bit double (downcast: integer)

	STRING,  // String
};

enum class SIOCastInfo
{
	NOT_SUPPORTED,
	NO_ACTION,
	CAST,
	DOWNCAST
};

DEFINE_BIT_MASK(SIO_DATA_CONST, 0);
DEFINE_BIT_MASK(SIO_DATA_MARKER, 1); // Marker for datatype translation

struct SIOData
{
	SIODataType datatype;
	char flags;
	uint64_t value;	
};

inline SIOData define_data(SIODataType datatype, char flags, uint64_t value)
{
	return { datatype, flags, value };
}

inline bool is_nummeric_data(SIODataType type)
{
	return type >= SIODataType::INTEGER && type <= SIODataType::DOUBLE;
}

inline bool no_cast_support(SIODataType type)
{
	return type <= SIODataType::FSTRING; // for now not possible, may later ... date/time support
}

inline SIOCastInfo get_cast_info(SIODataType lval, SIODataType rval)
{
	if (no_cast_support(lval) || no_cast_support(rval))
	{
		return SIOCastInfo::NOT_SUPPORTED;
	}
	else if (lval == rval)
	{
		return SIOCastInfo::NO_ACTION;
	}
	else if (is_nummeric_data(lval) && is_nummeric_data(rval))
	{
		return lval > rval ? SIOCastInfo::CAST : SIOCastInfo::DOWNCAST;
	}
	return SIOCastInfo::NOT_SUPPORTED;
}