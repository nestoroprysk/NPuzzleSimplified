#pragma once

#include "Types.hpp"
#include "Utils.hpp"
#include "State.hpp"
#include "Hash.hpp"
#include "SolverConfiguration.hpp"

template <typename Container>
class Solver
{
public:
	Solver(SolverConfiguration i_config);
	MaybeSolution solve(const Matrix& i_matrix) const;
private:
	const SolverConfiguration m_configuration;
};

template <typename Container>
Solver<Container>::Solver(SolverConfiguration i_config)
	: m_configuration(std::move(i_config))
{
}

template <typename Container>
MaybeSolution Solver<Container>::solve(const Matrix& i_matrix) const
{
	if (!Utils::solvable(i_matrix, m_configuration.m_desired_solution))
		return {};
	auto open = Container();
	auto open_states_hash = Hash();
	auto closed_states_hash = Hash();
	open.push(State(std::make_shared<Matrix>(i_matrix), m_configuration.m_heuristic_function(i_matrix)));
	open_states_hash.push(open.top());
	while (!open.empty()){
		auto e = open.top();
		if (!Utils::h(e) && Utils::eq(Utils::data(e), m_configuration.m_desired_solution))
			return std::make_unique<Solution>(Utils::collectMoves(e));
		open.pop();
		open_states_hash.pop(e);
		closed_states_hash.push(e);
		for (auto n : Utils::expand(e, m_configuration.m_heuristic_function)){
			if (!open_states_hash.contains(n) && !closed_states_hash.contains(n)){
				Utils::predecessor(n) = std::make_shared<State>(e);
				Utils::g(n) = Utils::g(e) + Utils::g_step_cost;
				open.push(n);
				open_states_hash.push(n);
			}
			else{
				if (Utils::g(n) + Utils::h(n) >
						Utils::g(e) + Utils::g_step_cost + Utils::h(e)){
					Utils::g(n) = Utils::g(e) + Utils::g_step_cost;
					Utils::predecessor(n) = std::make_shared<State>(e);
					if (closed_states_hash.contains(n)){
						closed_states_hash.pop(n);
						open.push(n);
						open_states_hash.push(n);
					}
				}
			}
		}
	}
	return {};
}
