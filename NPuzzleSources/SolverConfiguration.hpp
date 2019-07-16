#pragma once

#include "Types.hpp"
#include <string>

struct SolverConfiguration
{
	const std::string m_name;
	const Matrix m_desired_solution;
	const HeuristicFunction m_heuristic_function;
	const std::string m_heuristic_function_name;
	const double m_heuristic_function_weight;
	const double m_distance_weight;
};
