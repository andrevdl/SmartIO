#pragma once

// --------------- Bitmasks --------------- //

#define ENCODE_UIN64_I32(i32_a, i32_b) (uint64_t)i32_a | ((uint64_t)i32_b << 32)
#define ENCODE_UIN64_I16(i16_a, i16_b, i16_c, i16_d) (uint64_t)i16_a | ((uint64_t)i16_b << 16) | ((uint64_t)i16_c << 32) | ((uint64_t)i16_d << 48)
#define ENCODE_UIN64_I8(i8_a, i8_b, i8_c, i8_d, i8_e, i8_f, i8_g, i8_h) \
	(uint64_t)i16_a | ((uint64_t)i16_b << 8) |\
	((uint64_t)i16_c << 16) | ((uint64_t)i16_d << 24) |\
	((uint64_t)i16_e << 32) | ((uint64_t)i16_f << 40) |\
	((uint64_t)i16_g << 48) | ((uint64_t)i16_h << 56)

#define ENCODE_UIN32_I16(i16_a, i16_b) (uint32_t)i16_a | ((uint32_t)i16_b << 16)
#define ENCODE_UIN32_I8(i8_a, i8_b, i8_c, i8_d) (uint32_t)i8_a | ((uint32_t)i8_b << 8) | ((uint32_t)i8_c << 16) | ((uint32_t)i8_d << 24)

#define ENCODE_UIN16_I8(ii8_a, i8_b) (uint16_t)ii8_a | ((uint16_t)i8_b << 8)

// Index start at 0
#define GET_ENCODED_DATA(data, offset, mask) (data >> (offset * 8)) & mask
#define GET_ENCODED_DATA_I32(data, offset) GET_ENCODED_DATA(data, offset * 4, 0xFFFFFFFF)
#define GET_ENCODED_DATA_I16(data, offset) GET_ENCODED_DATA(data, offset * 2, 0xFFFF)
#define GET_ENCODED_DATA_I8(data, offset) GET_ENCODED_DATA(data, offset * 4, 0xFF)

// --------------- Runtime/compiler consts --------------- //

constexpr auto RUNTIME_VERSION_MAJOR = 0;
constexpr auto RUNTIME_VERSION_MINOR = 1;
constexpr auto RUNTIME_VERSION_RELEASE = 0;
constexpr auto RUNTIME_VERSION_BUILD = 0;

constexpr auto RUNTIME_VERSION_TAG = 'a'; // alpha (a), beta (b), release (r), release candidate (c)
constexpr auto RUNTIME_VERSION_TAG_SUB = 0; // Subversion in tag => alpha 1, alpha 2, rc 1, rc 2, ... -> release always 0

constexpr auto LANG_VERSION_MAJOR = 0;
constexpr auto LANG_VERSION_MINOR = 1;
constexpr auto LANG_VERSION_RELEASE = 0;
constexpr auto LANG_VERSION_BUILD = 0;

constexpr auto LANG_VERSION_TAG = 'a'; // alpha (a), beta (b), release (r), release candidate (c), experimental (e)
constexpr auto LANG_VERSION_TAG_SUB = 0; // Subversion in tag => alpha 1, alpha 2, rc 1, rc 2, ... -> release always 0

constexpr auto RUNTIME_VERSION_NAME = "SmartIO - Pre-Alpha 0.1 Runtime";
constexpr auto LANG_VERSION_NAME = "SmartIO - Pre-Alpha 0.1 Language";

#if defined(SIO_DEBUG) || !defined(SIO_FAST)
#define SIO_AST_DEBUG_CAP
#endif

#define RUNTIME_VERSION ENCODE_UIN64_I16(RUNTIME_VERSION_MAJOR, RUNTIME_VERSION_MINOR, RUNTIME_VERSION_RELEASE, RUNTIME_VERSION_BUILD)
#define RUNTIME_VERSION_TAG ENCODE_UIN16_I8(RUNTIME_VERSION_TAG, RUNTIME_VERSION_TAG_SUB)

#define LANG_VERSION ENCODE_UIN64_I16(RUNTIME_VERSION_MAJOR, RUNTIME_VERSION_MINOR, RUNTIME_VERSION_RELEASE, RUNTIME_VERSION_BUILD)
#define LANG_VERSION_TAG ENCODE_UIN16_I8(LANG_VERSION_TAG, LANG_VERSION_TAG_SUB)

// TODO: MOVE, LAYOUT IDEA OUTPUT FILE
// magic_word = SIO
// HEADER: [magic_word:24bit]:24 [ [[lang_version:64bit][lang_tag:16bit]]:80 [[runtime_version:64bit][runtime_tag:16bit]]:80 ]:160 [ [header_size:64bit][header:...] ]:64+ => fix size: 248 bits (31 bytes)
// May add: description field, date field, owner field and other metadata

// --------------- Other --------------- //

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