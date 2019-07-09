#pragma once

#include "IContainer.hpp"
#include "Types.hpp"
#include "State.hpp"

#include <queue>
#include <unordered_set>

class Queue : public IContainer
{
public:
	Queue();
	virtual void push(const State& i_state) override;
	virtual bool empty() const override;
	virtual State top() const override;
	virtual bool contains(const State& i_state) const override;
	virtual void pop() override;
	virtual void pop(const State& i_state) override;
private:
	mutable std::priority_queue<State, std::vector<State>, Comparator> m_queue;
	std::unordered_multiset<State, HashFunction, EqFunction> m_set;
};
