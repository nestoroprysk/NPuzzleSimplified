#pragma once

#include "IContainer.hpp"
#include "Types.hpp"
#include "State.hpp"

#include <set>

template <std::size_t N>
class Set
{
public:
	Set();
	void push(const State<N>& i_state);
	bool empty() const;
	State<N> top() const;
	void pop();
private:
	std::set<State<N>, Comparator<N>> m_data;
};
