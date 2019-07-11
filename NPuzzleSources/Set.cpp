#include "Set.hpp"
#include "State.hpp"
#include "Utils.hpp"

#include <string>

template <std::size_t N>
Set<N>::Set()
	: m_data([](const auto& l, const auto& r)
		{ return Utils<N>::cmp(l, r); })
{
}

template <std::size_t N>
void Set<N>::push(const State<N>& i_state)
{
	m_data.insert(i_state);
}

template <std::size_t N>
bool Set<N>::empty() const
{
	return m_data.empty();
}

template <std::size_t N>
State<N> Set<N>::top() const
{
	if (empty())
		throw std::logic_error("top() on an empty Container");
	return *m_data.cbegin();
}

template <std::size_t N>
bool Set<N>::contains(const State<N>& i_state) const
{
	// TODO: provide hash lookup
	return m_data.find(i_state) != m_data.end();
}

template <std::size_t N>
void Set<N>::pop()
{
	if (empty())
		throw std::logic_error("pop() on an empty Container");
	m_data.erase(m_data.begin());
}

template <std::size_t N>
void Set<N>::pop(const State<N>& i_state)
{
	if (!contains(i_state))
		throw std::logic_error("pop(s), s not found");
	m_data.erase(m_data.find(i_state));
}


EXPLICITLY_INSTANTIATE_CLASS(Set);
