#pragma once

#include "Types.hpp"

// TODO: make Container a template argument
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
