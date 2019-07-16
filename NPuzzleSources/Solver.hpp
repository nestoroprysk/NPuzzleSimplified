#pragma once

#include "Types.hpp"
#include "Utils.hpp"
#include "State.hpp"
#include "Hash.hpp"
#include "SolverConfiguration.hpp"
#include "Comparator.hpp"
#include "Result.hpp"

#include <chrono>

template <typename Container>
class Solver
{
public:
	Solver(SolverConfiguration i_config);
	Result<Container> solve(const Matrix& i_matrix) const;
private:
	const SolverConfiguration m_configuration;
};

template <typename Container>
Solver<Container>::Solver(SolverConfiguration i_config)
	: m_configuration(std::move(i_config))
{
}

template <typename Container>
Result<Container> Solver<Container>::solve(const Matrix& i_matrix) const
{
	using namespace Utils;
	const auto t0 = std::chrono::steady_clock::now();
	auto number_of_selected_states = std::size_t(0);
	auto max_number_of_states_in_memory = std::size_t(0);
	if (!solvable(i_matrix, m_configuration.m_desired_solution))
		return Result<Container>{ m_configuration, i_matrix,
				number_of_selected_states, max_number_of_states_in_memory,
					static_cast<size_t>(std::chrono::duration_cast<std::chrono::milliseconds>
						(std::chrono::steady_clock::now() - t0).count()),
							nullptr };
	auto open = Container(m_configuration);
	auto open_states_hash = Hash();
	auto closed_states_hash = Hash();
	open.push(State(std::make_shared<Matrix>(i_matrix), m_configuration.m_heuristic_function(i_matrix)));
	open_states_hash.push(open.top());
	while (!open.empty()){
		++number_of_selected_states;
		auto e = open.top();
		if (!h(e) && eq(data(e), m_configuration.m_desired_solution))
			return Result<Container>{ m_configuration, i_matrix,
				number_of_selected_states, max_number_of_states_in_memory,
					static_cast<size_t>(std::chrono::duration_cast<std::chrono::milliseconds>
						(std::chrono::steady_clock::now() - t0).count()),
							std::make_shared<Solution>(collectMoves(e)) };
		open.pop();
		open_states_hash.pop(e);
		closed_states_hash.push(e);
		for (auto n : expand(e, m_configuration.m_heuristic_function)){
			if (!open_states_hash.contains(n) && !closed_states_hash.contains(n)){
				predecessor(n) = std::make_shared<State>(e);
				g(n) = g(e) + g_step_cost;
				open.push(n);
				open_states_hash.push(n);
			}
			else{
				if (g(n) + h(n) >
						g(e) + g_step_cost + h(e)){
					g(n) = g(e) + g_step_cost;
					predecessor(n) = std::make_shared<State>(e);
					if (closed_states_hash.contains(n)){
						closed_states_hash.pop(n);
						open.push(n);
						open_states_hash.push(n);
					}
				}
			}
		}
		max_number_of_states_in_memory =
			std::max(max_number_of_states_in_memory,
				open.size() + open_states_hash.size() + closed_states_hash.size());
	}
	throw std::logic_error("isSolvable() failed to detect an unsolvable puzzle");
}
