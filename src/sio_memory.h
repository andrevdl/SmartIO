/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <algorithm>

#include <bitset>

#define GET_BIT(pos, data) ((data >> pos) & 0x01)
#define SET_BIT(pos, data) ((data) | (0x01 << pos))
#define FLIP_BIT(pos, data) (GET_BIT(pos, data) ^ 0x01) 
// xxxx

//#define READ_OPCODE(instr) instr && 0xE0; => example (read the first 3 bits of 8 total) => mask: 1110 0000

// 32 bytes
// (Max div 8) - (Min div 8) + 1 => max bytes
// (E div 8) - (Min div 8) => read byte
// E mod 8 => read bit

template<unsigned char min, unsigned char max>
struct SIOBitArray
{
private:
	const inline unsigned char get_pos(const unsigned char ord)
	{
		return ord % 8;
	}
	inline unsigned char* get_byte(const unsigned char ord)
	{
		return bytes + (get_pos(ord) - (min % 8));
	}
public:
	unsigned char bytes[((max / 8) - (min / 8) + 1)];

	SIOBitArray()
	{
		for (size_t i = 0; i < sizeof(bytes); i++)
		{
			bytes[i] = 0;
		}
	}

	bool get_bit(const unsigned char ord)
	{
		return GET_BIT(get_pos(ord), *get_byte(ord));
	}

	void set_bit(const unsigned char ord)
	{
		*get_byte(ord) |= 1 << get_pos(ord);
	}

	void flip_bit(const unsigned char ord)
	{
		//
	}

	void clear_bit(const unsigned char ord)
	{
		//
	}
};

typedef SIOBitArray<0, 255> SIOSet;