#include "Set.hpp"
#include "State.hpp"
#include "Utils.hpp"

#include <string>

using namespace Utils;

Set::Set() : m_data(cmp) {}

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
	const auto range = m_data.equal_range(i_state);
	return std::any_of(range.first, range.second,
		[&i_state](auto const& i_e){
			return eq(*i_e.mp_data, *i_state.mp_data);
	});
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
	auto nbItemsDeleted = 0;
	auto range = m_data.equal_range(i_state);
	for (auto i = range.first; i != range.second;){
		if (eq(*i->mp_data, *i_state.mp_data)){
			i = m_data.erase(i);
			++nbItemsDeleted;
		}
		else
			++i;
	}
	if (nbItemsDeleted != 1)
		throw std::logic_error("pop(s), only one s expected, got [" + std::to_string(nbItemsDeleted) + "]");
}
