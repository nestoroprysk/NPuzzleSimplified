#pragma once

#include "Types.hpp"
#include "SolverConfiguration.hpp"

template <typename Container>
struct Result
{
	const SolverConfiguration m_config;
	const Matrix m_input;
	const std::size_t m_number_of_selected_states;
	const std::size_t m_max_number_of_states_in_memory;
	const std::size_t m_execution_time;
	const MaybeSolution m_opt_solution;
};
