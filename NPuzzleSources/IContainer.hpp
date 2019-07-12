#pragma once

#include "Types.hpp"

template <std::size_t N>
class IContainer
{
public:
	virtual void push(const State<N>& i_state) = 0;
	virtual bool empty() const = 0;
	virtual State<N> top() const = 0;
	virtual void pop() = 0;
	virtual ~IContainer(){}
};
