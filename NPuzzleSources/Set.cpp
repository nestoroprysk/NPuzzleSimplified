#include "Set.hpp"
#include "State.hpp"

Set::Set(Comparator<Less> i_cmp)
	: m_data(std::move(i_cmp))
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
	return *m_data.cbegin();
}

void Set::pop()
{
	m_data.erase(m_data.begin());
}
