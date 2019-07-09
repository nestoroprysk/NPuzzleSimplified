#pragma once

#include "Types.hpp"

#include <unordered_set>

namespace Utils{

static constexpr auto g_step_cost = 1;

auto possibleMoves(Matrix const& i_state) -> std::unordered_set<Move>;
bool isValid(Matrix const& i_state, Move i_move);
Matrix move(const Matrix& i_state, Move i_move);
Matrix& move(Matrix& io_state, Move i_move);
Move inferMove(Matrix const& i_from, Matrix const& i_to);

bool isSquare(const Matrix& i_matrix);
bool eq(const Matrix& i_lhs, const Matrix& i_rhs);
bool solvable(const Matrix& i_matrix, const Matrix& i_solution);

std::size_t countInversions(const RowMatrix& i_input, const RowMatrix& i_solution);
std::size_t countInversions(const Matrix& i_matrix, const RowMatrix& i_solution);
RowMatrix makeRow(const Matrix& i_matrix);

std::size_t hash(const State& i_state);
bool eq(const State& i_lhs, const State& i_rhs);
bool cmp(const State& i_lhs, const State& i_rhs);

const Matrix& data(const State& i_state);
std::vector<State> expand(const State& i_state, const HeuristicFunction& i_heuristic_function);
const std::size_t& h(State& i_state);
std::size_t& g(State& i_state);
const StateSP& predecessor(const State& i_state);
StateSP& predecessor(State& i_state);
std::list<Move> collectMoves(const State& i_state);

}
