#include "Set.hpp"
#include "State.hpp"
#include "Utils.hpp"

#include <string>

using namespace Utils;

Set::Set()
	: m_data([](const auto& l, const auto& r){ return cmp(l, r); }) 
{
}

void Set::push(const State& i_state)
{
	m_data.insert(i_state);
}

bool Set::empty() const
{
	return m_data.empty();
}

State Set::top() const
{
	if (empty())
		throw std::logic_error("top() on an empty Container");
	return *m_data.cbegin();
}

bool Set::contains(const State& i_state) const
{
	return m_data.find(i_state) != m_data.end();
}

void Set::pop()
{
	if (empty())
		throw std::logic_error("pop() on an empty Container");
	m_data.erase(m_data.begin());
}

void Set::pop(const State& i_state)
{
	if (!contains(i_state))
		throw std::logic_error("pop(s), s not found");
	m_data.erase(m_data.find(i_state));
}
