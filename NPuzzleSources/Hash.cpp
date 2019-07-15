#include "Hash.hpp"
#include "Utils.hpp"
#include "State.hpp"

namespace Detail {

static constexpr auto g_bucket_count = 8;

std::size_t hash(const State& i_state)
{
	std::hash<std::string> hash;
	return hash(Utils::data(i_state).data());
}

bool eq(const State& i_lhs, const State& i_rhs)
{
	return i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost
		&& Utils::eq(Utils::data(i_lhs), Utils::data(i_rhs));
}

}

Hash::Hash()
	: m_data(Detail::g_bucket_count,
			[](const auto& i_state){ return Detail::hash(i_state); },
			[](const auto& i_lhs, const auto& i_rhs){ return Detail::eq(i_lhs, i_rhs); })
{
}

bool Hash::contains(const State& i_state) const
{
	return m_data.find(i_state) != m_data.end();
}

void Hash::push(const State& i_state)
{
	m_data.insert(i_state);
}

void Hash::pop(const State& i_state)
{
	m_data.erase(i_state);
}
