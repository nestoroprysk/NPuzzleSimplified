#pragma once

#include "Types.hpp"

#include <unordered_set>

#define EXPLICITLY_INSTANTIATE_STRUCT_IMPL(T, N) \
template struct T<N>

#define EXPLICITLY_INSTANTIATE_STRUCT(T) \
EXPLICITLY_INSTANTIATE_STRUCT_IMPL(T, 3); \
EXPLICITLY_INSTANTIATE_STRUCT_IMPL(T, 4); \
EXPLICITLY_INSTANTIATE_STRUCT_IMPL(T, 5)

#define EXPLICITLY_INSTANTIATE_CLASS_IMPL(T, N) \
template class T<N>

#define EXPLICITLY_INSTANTIATE_CLASS(T) \
EXPLICITLY_INSTANTIATE_CLASS_IMPL(T, 3); \
EXPLICITLY_INSTANTIATE_CLASS_IMPL(T, 4); \
EXPLICITLY_INSTANTIATE_CLASS_IMPL(T, 5)

template <std::size_t N>
struct Utils
{

using MatrixNxN = Matrix<N>;

static constexpr auto g_step_cost = 1;
static constexpr auto g_moving_point = 0;

static auto possibleMoves(const MatrixNxN& i_state) -> std::unordered_set<Move>;
static bool isValid(const MatrixNxN& i_state, Move i_move);
static MatrixSP<N> move(const MatrixSP<N>& ip_matrix, Move i_move);
static Matrix<N> move(const Matrix<N>& i_matrix, Move i_move);
static void moveInput(Matrix<N>& io_matrix, Move i_move);
static Move inferMove(MatrixNxN const& i_from, MatrixNxN const& i_to);

static bool eq(const MatrixNxN& ip_lhs, const MatrixNxN& ip_rhs);
template <typename Order>
static bool cmp(const MatrixNxN& ip_lhs, const MatrixNxN& ip_rhs);
static bool solvable(const MatrixNxN& ip_matrix, const MatrixNxN& ip_solution);

static std::size_t countInversions(const MatrixNxN& i_input, const ValueToPosition& i_mapper);

template <typename Order>
static bool cmp(const State<N>& i_lhs, const State<N>& i_rhs);

static const MatrixNxN& data(const State<N>& i_state);
static std::vector<State<N>> expand(const State<N>& i_state, const HeuristicFunction<N>& i_heuristic_function);
static const std::size_t& h(State<N>& i_state);
static std::size_t& g(State<N>& i_state);
static const StateSP<N>& predecessor(const State<N>& i_state);
static StateSP<N>& predecessor(State<N>& i_state);
static std::list<Move> collectMoves(const State<N>& i_state);

static bool isInverted(const ValueToPosition& i_mapper, const char l, const char r);
static std::list<Move> collectMovesImpl(const State<N>& i_state,
								 const StateSP<N>& i_opt_predecessor,
								 std::list<Move> o_result = std::list<Move>());
static ValueToPosition map(const Matrix<N>& i_solution);

Utils() = delete;

};

namespace Detail {

template <std::size_t N, typename Order>
struct Comparator{
static bool compare(const Matrix<N>&, const Matrix<N>&){
	throw std::logic_error("compare(), Greater, Less, GreaterOrEqual, or LessOrEqual expected");
}
};

template <std::size_t N>
struct Comparator<N, Greater>{
static bool compare(const Matrix<N>& i_lhs, const Matrix<N>& i_rhs){
	for (std::size_t i = 0; i < N * N; ++i)
		if (i_lhs[i] != i_rhs[i])
			return i_lhs[i] > i_rhs[i];
	return false;
}
};

template <std::size_t N>
struct Comparator<N, Less>{
static bool compare(const Matrix<N>& i_lhs, const Matrix<N>& i_rhs){
	for (std::size_t i = 0; i < N * N; ++i)
		if (i_lhs[i] != i_rhs[i])
			return i_lhs[i] < i_rhs[i];
	return false;
}
};

template <std::size_t N>
struct Comparator<N, GreaterOrEqual>{
static bool compare(const Matrix<N>& i_lhs, const Matrix<N>& i_rhs){
	for (std::size_t i = 0; i < N * N; ++i)
		if (i_lhs[i] != i_rhs[i])
			return i_lhs[i] > i_rhs[i];
	return true;
}
};

template <std::size_t N>
struct Comparator<N, LessOrEqual>{
static bool compare(const Matrix<N>& i_lhs, const Matrix<N>& i_rhs){
	for (std::size_t i = 0; i < N * N; ++i)
		if (i_lhs[i] != i_rhs[i])
			return i_lhs[i] < i_rhs[i];
	return true;
}
};

}

template <std::size_t N>
template <typename Order>
bool Utils<N>::cmp(const MatrixNxN& i_lhs, const MatrixNxN& i_rhs)
{
	return Detail::Comparator<N, Order>::compare(i_lhs, i_rhs);
}

template <std::size_t N>
template <typename Order>
bool Utils<N>::cmp(const State<N>& i_lhs, const State<N>& i_rhs)
{
	return i_lhs.m_heuristic_cost < i_rhs.m_heuristic_cost ||
		(i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost &&
			i_lhs.m_distance < i_rhs.m_distance) ||
			(i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost &&
				i_lhs.m_distance == i_rhs.m_distance &&
					cmp<Order>(data(i_lhs), data(i_rhs)));
}
