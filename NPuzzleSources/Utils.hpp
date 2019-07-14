#pragma once

#include "Types.hpp"
#include "State.hpp"

#include <unordered_set>

namespace Utils {

static constexpr auto g_step_cost = 1;

auto possibleMoves(const Matrix& i_state) -> std::unordered_set<Move>;
MatrixSP move(const MatrixSP& ip_matrix, Move i_move);
Matrix move(const Matrix& i_matrix, Move i_move);
Move inferMove(Matrix const& i_from, Matrix const& i_to);

bool eq(const Matrix& ip_lhs, const Matrix& ip_rhs);
template <typename Order>
bool cmp(const Matrix& ip_lhs, const Matrix& ip_rhs);
bool solvable(const Matrix& ip_matrix, const Matrix& ip_solution);

std::size_t countInversions(const Matrix& i_input, const ValueToPosition& i_mapper);

template <typename Order>
bool cmp(const State& i_lhs, const State& i_rhs);

const Matrix& data(const State& i_state);
std::vector<State> expand(const State& i_state, const HeuristicFunction& i_heuristic_function);
const std::size_t& h(State& i_state);
std::size_t& g(State& i_state);
const StateSP& predecessor(const State& i_state);
StateSP& predecessor(State& i_state);
std::list<Move> collectMoves(const State& i_state);

bool isInverted(const ValueToPosition& i_mapper, const char l, const char r);
std::list<Move> collectMovesImpl(const State& i_state,
								 const StateSP& i_opt_predecessor,
								 std::list<Move> o_result = std::list<Move>());
ValueToPosition map(const Matrix& i_solution);

};

namespace Detail {

template <typename Order>
struct Comparator{
static bool compare(const Matrix&, const Matrix&){
	throw std::logic_error("compare(), Greater, Less, GreaterOrEqual, or LessOrEqual expected");
}
};

template <>
struct Comparator<Greater>{
static bool compare(const Matrix& i_lhs, const Matrix& i_rhs){
	for (std::size_t i = 0; i < i_lhs.sizeSquared(); ++i)
		if (i_lhs[i] != i_rhs[i])
			return i_lhs[i] > i_rhs[i];
	return false;
}
};

template <>
struct Comparator<Less>{
static bool compare(const Matrix& i_lhs, const Matrix& i_rhs){
	for (std::size_t i = 0; i < i_lhs.sizeSquared(); ++i)
		if (i_lhs[i] != i_rhs[i])
			return i_lhs[i] < i_rhs[i];
	return false;
}
};

template <>
struct Comparator<GreaterOrEqual>{
static bool compare(const Matrix& i_lhs, const Matrix& i_rhs){
	for (std::size_t i = 0; i < i_lhs.sizeSquared(); ++i)
		if (i_lhs[i] != i_rhs[i])
			return i_lhs[i] > i_rhs[i];
	return true;
}
};

template <>
struct Comparator<LessOrEqual>{
static bool compare(const Matrix& i_lhs, const Matrix& i_rhs){
	for (std::size_t i = 0; i < i_lhs.sizeSquared(); ++i)
		if (i_lhs[i] != i_rhs[i])
			return i_lhs[i] < i_rhs[i];
	return true;
}
};

}

template <typename Order>
bool Utils::cmp(const Matrix& i_lhs, const Matrix& i_rhs)
{
	return Detail::Comparator<Order>::compare(i_lhs, i_rhs);
}

template <typename Order>
bool Utils::cmp(const State& i_lhs, const State& i_rhs)
{
	return i_lhs.m_heuristic_cost < i_rhs.m_heuristic_cost ||
		(i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost &&
			i_lhs.m_distance < i_rhs.m_distance) ||
			(i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost &&
				i_lhs.m_distance == i_rhs.m_distance &&
					cmp<Order>(data(i_lhs), data(i_rhs)));
}
