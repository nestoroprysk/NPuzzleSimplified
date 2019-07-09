#include "Solver.hpp"
#include "Utils.hpp"
#include "IContainer.hpp"
#include "State.hpp"

using namespace Utils;

Solver::Solver(const Matrix& i_desired_solution,
		const HeuristicFunction& i_heuristic_function,
		const ContainerCreator& i_container_creator)
	: m_desired_solution(i_desired_solution)
	, m_heuristic_function(i_heuristic_function)
	, m_container_creator(i_container_creator)
{
}

MaybeSolution Solver::solve(const Matrix& i_matrix) const
{
	using namespace Utils;
	if (!solvable(i_matrix, m_desired_solution))
		return {};
	auto open = m_container_creator.create();
	auto closed = m_container_creator.create();
	open->push(State(i_matrix, m_heuristic_function(i_matrix)));
	auto it = 0;
	while (!open->empty()){
	    ++it;
		auto e = open->top();
		if (eq(data(e), m_desired_solution))
			return std::make_unique<Solution>(collectMoves(e));
		open->pop();
		closed->push(e);
		for (auto n : expand(e, m_heuristic_function)){
			if (!open->contains(n) && !closed->contains(n)){
				predecessor(n) = std::make_shared<State>(e);
                open->push(n);
				g(n) = g(e) + g_step_cost;
			}
			else{
				if (g(n) + h(n) < g(e) + g_step_cost + h(e)){
					g(n) = g(e) + g_step_cost;
					predecessor(n) = std::make_shared<State>(e);
					if (closed->contains(n)){
						closed->pop(n);
						open->push(n);
					}
				}
			}
		}
	}
	return {};	
}
