#include "Queue.hpp"
#include "State.hpp"
#include "Utils.hpp"

#include <string>

using namespace Utils;

namespace {

static constexpr auto g_bucket_count = 8;

}

Queue::Queue()
	: m_queue(cmp)
	, m_set(g_bucket_count, hash, [](const auto& l, const auto& r){ return eq(l, r); })
{
}

void Queue::push(const State& i_state)
{
	m_queue.push(i_state);
	m_set.insert(i_state);
}

bool Queue::empty() const
{
	return m_set.empty();
}

State Queue::top() const
{
	if (empty())
		throw std::logic_error("top() on an empty Container");
	while (true){
		const auto& s = m_queue.top();
		const auto previouslyDeleted = m_set.find(s) == m_set.end();
		if (previouslyDeleted){
			m_queue.pop();
		}
		else{
			return s;
		}
	}
}

bool Queue::contains(const State& i_state) const
{
	const auto range = m_set.equal_range(i_state);
	return std::any_of(range.first, range.second,
		[&i_state](auto const& i_e){
			// TODO: use data()
			return eq(*i_e.mp_data, *i_state.mp_data);
	});
}

void Queue::pop()
{
	if (empty())
		throw std::logic_error("pop() on an empty Container");
	while (true){
		const auto& s = m_queue.top();
		const auto previouslyDeleted = m_set.find(s) == m_set.end();
		if (previouslyDeleted){
			m_queue.pop();
		}
		else{
			m_set.erase(s);
			m_queue.pop();
			return;
		}
	}
}

void Queue::pop(const State& i_state)
{
	if (!contains(i_state))
		throw std::logic_error("pop(s), s not found");
	const auto range = m_set.equal_range(i_state);
	for (auto i = range.first; i != range.second; ++i){
		if (eq(*i->mp_data, *i_state.mp_data)){
			m_set.erase(i);
			return;
		}
	}
}
