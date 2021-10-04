#pragma once

#include <ostream>
#include <stack>
#include <sstream>
#include "../SIOCommon.h"

class SIODotDebugger
{
private:
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
	void clear();
};

inline SIODotDebugger& dot_debugger()
{
	static SIODotDebugger debugger;
	return debugger;
}

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

#ifdef SIO_DEBUG
#define START_TREE_NODE(s, d) dot_debugger().create_node(s, d)
#define CLOSE_TREE_NODE dot_debugger().close_node();
#define FINISH_TREE_NODE(r) uint64_t r_temp = r; CLOSE_TREE_NODE return r_temp
#define CLEAR_TREE_DEBUGGER dot_debugger().clear()
#else
#define START_TREE_NODE(s, d)
#define CLOSE_TREE_NODE
#define FINISH_TREE_NODE(r) return r
#define CLEAR_TREE_DEBUGGER
#endif // SIO_DEBUG