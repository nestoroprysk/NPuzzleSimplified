#pragma once

#include "Types.hpp"
#include "State.hpp"
#include "Comparator.hpp"

#include <set>

class Set
{
public:
	Set(Comparator<Less> i_cmp);
	void push(const State& i_state);
	bool empty() const;
	State top() const;
	void pop();
private:
	std::set<State, Comparator<Less>> m_data;
};
