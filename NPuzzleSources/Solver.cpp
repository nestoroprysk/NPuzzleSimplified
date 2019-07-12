#include "Solver.hpp"
#include "Utils.hpp"
#include "IContainer.hpp"
#include "State.hpp"
#include "Hash.hpp"

template <std::size_t N>
Solver<N>::Solver(const Matrix<N>& i_desired_solution,
		const HeuristicFunction<N>& i_heuristic_function,
		const ContainerCreator<N>& i_container_creator)
	: m_desired_solution(i_desired_solution)
	, m_heuristic_function(i_heuristic_function)
	, m_container_creator(i_container_creator)
{
}

template <std::size_t N>
MaybeSolution Solver<N>::solve(const Matrix<N>& i_matrix) const
{
	if (!Utils<N>::solvable(i_matrix, m_desired_solution))
		return {};
	auto p_open = m_container_creator.create();
	auto p_closed = m_container_creator.create();
	auto& open = *p_open;
	auto& closed = *p_closed;
	open.push(State<N>(std::make_shared<Matrix<N>>(i_matrix), m_heuristic_function(i_matrix)));
	auto created_states_container = Hash<N>();
	while (!open.empty()){
		auto e = open.top();
		if (!Utils<N>::h(e) && Utils<N>::eq(Utils<N>::data(e), m_desired_solution))
			return std::make_unique<Solution>(Utils<N>::collectMoves(e));
		open.pop();
		closed.push(e);
		for (auto n : Utils<N>::expand(e, m_heuristic_function)){
			if (!created_states_container.contains(n)){
				Utils<N>::predecessor(n) = std::make_shared<State<N>>(e);
				open.push(n);
				Utils<N>::g(n) = Utils<N>::g(e) + Utils<N>::g_step_cost;
			}
			else{
				if (Utils<N>::g(n) + Utils<N>::h(n) <
						Utils<N>::g(e) + Utils<N>::g_step_cost + Utils<N>::h(e)){
					Utils<N>::g(n) = Utils<N>::g(e) + Utils<N>::g_step_cost;
					Utils<N>::predecessor(n) = std::make_shared<State<N>>(e);
					if (closed.contains(n)){
						closed.pop(n);
						open.push(n);
					}
				}
			}
			created_states_container.push(n);
		}
	}
	return {};
}

EXPLICITLY_INSTANTIATE_CLASS(Solver);
