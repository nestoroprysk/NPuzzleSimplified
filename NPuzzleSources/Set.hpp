#pragma once

#include "IContainer.hpp"
#include "Types.hpp"
#include "State.hpp"

#include <set>

class Set final : public IContainer
{
public:
	Set();
	virtual void push(const State& i_state) override;
	virtual bool empty() const override;
	virtual State top() const override;
	virtual bool contains(const State& i_state) const override;
	virtual void pop() override;
	virtual void pop(const State& i_state) override;
private:
	std::set<State, Comparator> m_data;
};
