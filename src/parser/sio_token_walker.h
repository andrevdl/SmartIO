/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>
#include <parser/sio_tokenizer.h>

using namespace std;

class SIOTokenWalker
{
private:
	SIOTokenizer* tokenizer;

	vector<SIOToken*>::iterator begin;
	vector<SIOToken*>::iterator it;
	vector<SIOToken*>::iterator end;

	inline SIOToken* _pop();
	inline SIOToken* _peek();
public:
	SIOTokenWalker(SIOTokenizer* tokenizer);

	SIOToken* pop();
	SIOToken* peek();
	bool rollback();
	bool eof();

	SIOTokenType pop_type();
	SIOTokenType peek_type();
};