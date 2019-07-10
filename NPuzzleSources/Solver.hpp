#pragma once

#include "Types.hpp"
#include "ContainerCreator.hpp"

class Solver
{
public:
	Solver(const MatrixSP& i_desired_solution,
		const HeuristicFunction& i_heuristic_function,
		const ContainerCreator& i_container_creator);
	MaybeSolution solve(const MatrixSP& ip_matrix) const;
private:
	const MatrixSP mp_desired_solution;
	const HeuristicFunction m_heuristic_function;
	const ContainerCreator m_container_creator;
};
