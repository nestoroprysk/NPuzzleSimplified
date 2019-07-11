#pragma once

#include "Types.hpp"
#include "ContainerCreator.hpp"

template <std::size_t N>
class Solver
{
public:
	Solver(const Matrix<N>& i_desired_solution,
		const HeuristicFunction<N>& i_heuristic_function,
		const ContainerCreator<N>& i_container_creator);
	MaybeSolution solve(const Matrix<N>& i_matrix) const;
private:
	const Matrix<N> m_desired_solution;
	const HeuristicFunction<N> m_heuristic_function;
	const ContainerCreator<N> m_container_creator;
};
