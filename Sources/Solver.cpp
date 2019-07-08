#include "Solver.hpp"
#include "Utils.hpp"
#include "IContainer.hpp"
#include "State.hpp"

using namespace Utils;

namespace {

static constexpr auto g_step_cost = 1;

const Matrix& data(const State& i_state)
{
	if (!i_state.mp_data)
		throw std::logic_error("data(s), initialized matrix expected");
	return *i_state.mp_data;
}

const auto expand = [](const auto& i_state, const auto& i_heuristic_function){
	const auto ms = possibleMoves(data(i_state));
	auto result = std::vector<State>();
	for (const auto m : ms){
		auto matrix = move(data(i_state), m);
		const auto cost = i_heuristic_function(matrix);
		result.emplace_back(std::move(matrix), cost);
	}
	return result;
};

const std::size_t& h(State& i_state){
	return i_state.m_heuristic_cost;
}

std::size_t& g(State& i_state){
	return i_state.m_distance;
}

const StateSP& predecessor(const State& i_state){
	return i_state.mp_predecessor;
}

StateSP& predecessor(State& i_state){
	return i_state.mp_predecessor;
}

std::list<Move> collectMovesImpl(const State& i_state,
								 const StateSP& i_opt_predecessor,
								 std::list<Move> o_result = std::list<Move>())
{
	if (i_opt_predecessor)
	{
		o_result.push_front(inferMove(data(*i_opt_predecessor), data(i_state)));
		return collectMovesImpl(*i_opt_predecessor, predecessor(*i_opt_predecessor), std::move(o_result));
	}
	return o_result;
}

std::list<Move> collectMoves(const State& i_state)
{
	return collectMovesImpl(i_state, predecessor(i_state));
}

}

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
	while (!open->empty()){
		auto e = open->top();
		if (h(e) == 0)
			return std::make_unique<Solution>(collectMoves(e));
		open->pop();
		closed->push(e);
		for (auto n : expand(e, m_heuristic_function)){
			if (!open->contains(n) && !closed->contains(n)){
				open->push(n);
				predecessor(n) = std::make_shared<State>(e);
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
