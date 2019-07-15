#pragma once

#include "Types.hpp"

struct SolverConfiguration
{
	const Matrix m_desired_solution;
	const HeuristicFunction m_heuristic_function;
	const double m_heuristic_function_weight;
	const double m_distance_weight;
};
