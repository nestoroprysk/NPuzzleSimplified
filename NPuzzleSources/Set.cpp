#include "Set.hpp"
#include "State.hpp"
#include "Utils.hpp"

#include <string>

Set::Set()
	: m_data([](const auto& l, const auto& r)
		{ return Utils::cmp(l, r); })
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

void Set::pop()
{
	if (empty())
		throw std::logic_error("pop() on an empty Container");
	m_data.erase(m_data.begin());
}
