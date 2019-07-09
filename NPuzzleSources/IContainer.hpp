#pragma once

#include "Types.hpp"

class IContainer
{
public:
	virtual void push(const State& i_state) = 0;
	virtual bool empty() const = 0;
	virtual State top() const = 0;
	virtual bool contains(const State& i_state) const = 0;
	virtual void pop() = 0;
	virtual void pop(const State& i_state) = 0;
	virtual ~IContainer(){}
};
