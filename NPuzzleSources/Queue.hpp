#pragma once

#include "Types.hpp"
#include "State.hpp"
#include "Comparator.hpp"

#include <queue>

template <typename Container>
class Queue
{
public:
    Queue(Comparator<NotLess> i_cmp);
    void push(const State& i_state);
    bool empty() const;
    State top() const;
    void pop();
    std::size_t size() const;
private:
    using QueueType = std::priority_queue<State, Container, Comparator<NotLess>>;
    QueueType m_data;
};

template <typename Container>
Queue<Container>::Queue(Comparator<NotLess> i_cmp)
    : m_data(std::move(i_cmp))
{
}

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

template <typename Container>
std::size_t Queue<Container>::size() const
{
    return m_data.size();
}
