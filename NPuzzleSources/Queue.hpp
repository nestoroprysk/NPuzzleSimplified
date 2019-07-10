#pragma once

#include "IContainer.hpp"
#include "Types.hpp"
#include "State.hpp"

class Queue final : public IContainer
{
public:
	Queue();
	virtual void push(const State& i_state) override;
	virtual bool empty() const override;
	virtual State top() const override;
	virtual bool contains(const State& i_state) const override;
	virtual void pop() override;
	virtual void pop(const State& i_state) override;
};
