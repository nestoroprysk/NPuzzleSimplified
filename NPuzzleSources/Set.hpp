#pragma once

#include "IContainer.hpp"
#include "Types.hpp"
#include "State.hpp"

#include <set>

template <std::size_t N>
class Set final : public IContainer<N>
{
public:
	Set();
	virtual void push(const State<N>& i_state) override;
	virtual bool empty() const override;
	virtual State<N> top() const override;
	virtual void pop() override;
private:
	std::set<State<N>, Comparator<N>> m_data;
};
