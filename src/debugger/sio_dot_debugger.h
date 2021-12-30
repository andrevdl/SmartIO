/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <ostream>
#include <stack>
#include <sstream>
#include <string>

using namespace std;

class SIODotDebugger
{
private:
	int64_t uuid_counter = 0;

	stack<uint64_t> path;
	uint64_t parent = 0;
	stringstream buffer;

	uint64_t get_uuid();

	template <typename T>
	void store_node_data(uint64_t uuid, char* name, T body);

	void store_link(uint64_t uuid);
public:
	friend ostream& operator<<(ostream& os, const SIODotDebugger& debugger);

	template <typename T>
	uint64_t create_node(char* name, T body);

	template <typename T>
	void create_and_close_node(char* name, T body);

	void close_node();

	const void print(ostream& os) const;
	string str();

	void clear();
};

template<typename T>
inline void SIODotDebugger::store_node_data(uint64_t uuid, char* name, T body)
{
	buffer << uuid << "[shape=record label=\"{" << name << "|";
	buffer << body;
	buffer << "}}\"];" << endl;
}

template<typename T>
inline uint64_t SIODotDebugger::create_node(char* name, T body)
{
	uint64_t uuid = get_uuid();
	store_node_data(uuid, name, body);
	store_link(uuid);
	
	path.push(uuid);
	return uuid;
}

template<typename T>
inline void SIODotDebugger::create_and_close_node(char* name, T body)
{
	uint64_t uuid = get_uuid();
	store_node_data(uuid, name, body);
	store_link(uuid);
}