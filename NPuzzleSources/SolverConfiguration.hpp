#pragma once

#include "Utils.hpp"
#include <string>

struct SolverConfiguration
{
    const Matrix m_desired_solution;
    const HeuristicFunction m_heuristic_function;
    const std::string m_heuristic_function_name;
    const double m_heuristic_function_weight;
    const double m_distance_weight;
    const std::string m_name = Utils::generateTestName();
    const std::size_t m_time_limit = Utils::g_default_time_limit;
};
