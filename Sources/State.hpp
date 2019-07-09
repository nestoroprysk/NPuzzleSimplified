#pragma once

#include "Types.hpp"

struct State
{
	State(const Matrix& i_matrix, const std::size_t i_heuristic_cost);
	MatrixSP mp_data;
	std::size_t m_heuristic_cost = 0;
	std::size_t m_distance = 0;
	StateSP mp_predecessor;
};
