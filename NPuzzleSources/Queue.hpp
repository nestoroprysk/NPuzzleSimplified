#pragma once

#include "IContainer.hpp"
#include "Types.hpp"
#include "State.hpp"

#include <queue>

template <std::size_t N, typename Container>
class Queue final : public IContainer<N>
{
public:
	virtual void push(const State<N>& i_state) override;
	virtual bool empty() const override;
	virtual State<N> top() const override;
	virtual void pop() override;
private:
	using QueueType = std::priority_queue<State<N>, Container, Comparator<N>>;
	QueueType m_data = QueueType([](const auto i_lhs, const auto i_rhs)
			{ return !Utils<N>::template cmp<Less>(i_lhs, i_rhs); });
};

template <std::size_t N, typename Container>
void Queue<N, Container>::push(const State<N>& i_state)
{
	m_data.push(i_state);
}

template <std::size_t N, typename Container>
bool Queue<N, Container>::empty() const
{
	return m_data.empty();
}

template <std::size_t N, typename Container>
State<N> Queue<N, Container>::top() const
{
	return m_data.top();
}

template <std::size_t N, typename Container>
void Queue<N, Container>::pop()
{
	m_data.pop();
}
