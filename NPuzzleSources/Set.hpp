#pragma once

#include "Types.hpp"
#include "State.hpp"

#include <set>

class Set
{
public:
	Set();
	void push(const State& i_state);
	bool empty() const;
	State top() const;
	void pop();
private:
	std::set<State, Comparator> m_data;
};
