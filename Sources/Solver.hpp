#pragma once

#include "Types.hpp"
#include "ContainerCreator.hpp"

class Solver
{
public:
	Solver(const Matrix& i_desired_solution,
		const HeuristicFunction& i_heuristic_function,
		const ContainerCreator& i_container_creator);
	MaybeSolution solve(const Matrix& i_matrix) const;
private:
	const Matrix m_desired_solution;
	const HeuristicFunction m_heuristic_function;
	const ContainerCreator m_container_creator;
};
