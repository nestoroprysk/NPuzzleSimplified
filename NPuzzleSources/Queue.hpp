#pragma once

#include "Types.hpp"
#include "State.hpp"

#include <queue>

template <typename Container>
class Queue final
{
public:
	void push(const State& i_state);
	bool empty() const;
	State top() const;
	void pop();
private:
	using QueueType = std::priority_queue<State, Container, Comparator>;
	QueueType m_data = QueueType([](const auto i_lhs, const auto i_rhs)
			{ return !Utils::template cmp<Less>(i_lhs, i_rhs); });
};

template <typename Container>
void Queue<Container>::push(const State& i_state)
{
	m_data.push(i_state);
}

template <typename Container>
bool Queue<Container>::empty() const
{
	return m_data.empty();
}

template <typename Container>
State Queue<Container>::top() const
{
	return m_data.top();
}

template <typename Container>
void Queue<Container>::pop()
{
	m_data.pop();
}
