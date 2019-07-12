#pragma once

#include "Utils.hpp"
#include <unordered_set>

namespace Detail {

static constexpr auto g_bucket_count = 8;

template <std::size_t N>
std::size_t hash(const State<N>& i_state)
{
	std::hash<char> hasher;
	auto result = std::size_t(0);;
	const auto& array = Utils<N>::data(i_state);
	for(std::size_t i = 0; i < N * N; ++i)
		result = (result << 1) ^ hasher(array[i]);
	return result;
}

template <std::size_t N>
bool eq(const State<N>& i_lhs, const State<N>& i_rhs)
{
	return i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost
		&& Utils<N>::eq(Utils<N>::data(i_lhs), Utils<N>::data(i_rhs));
}

}

template <std::size_t N>
class Hash
{
public:
	bool contains(const State<N>& i_state) const;
	void push(const State<N>& i_state);
private:
	using HashFunctionType = std::function<std::size_t(const State<N>&)>;
	using EqFunctionType = std::function<bool(const State<N>&, const State<N>&)>;
	using HashType = std::unordered_set<State<N>, HashFunctionType, EqFunctionType>;
	HashType m_data =
		HashType(Detail::g_bucket_count,
			[](const auto& i_state){ return Detail::hash<N>(i_state); },
			[](const auto& i_lhs, const auto& i_rhs){ return Detail::eq<N>(i_lhs, i_rhs); });
};

template <std::size_t N>
bool Hash<N>::contains(const State<N>& i_state) const
{
	return m_data.find(i_state) != m_data.end();
}

template <std::size_t N>
void Hash<N>::push(const State<N>& i_state)
{
	m_data.insert(i_state);
}
