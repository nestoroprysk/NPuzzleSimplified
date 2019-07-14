#pragma once

#include "Types.hpp"

template <std::size_t N>
struct State
{
	State(const MatrixSP<N>& ip_matrix, const std::size_t i_heuristic_cost);
	MatrixSP<N> mp_data;
	std::size_t m_heuristic_cost = 0;
	std::size_t m_distance = 0;
	StateSP<N> mp_predecessor;
};
