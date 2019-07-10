#pragma once

#include "Types.hpp"

#include <unordered_set>

namespace Utils{

static constexpr auto g_step_cost = 1;

auto possibleMoves(MatrixSP const& ip_state) -> std::unordered_set<Move>;
bool isValid(MatrixSP const& ip_state, Move i_move);
MatrixSP move(const MatrixSP& ip_state, Move i_move);
MatrixSP& move(MatrixSP& iop_state, Move i_move);
Move inferMove(MatrixSP const& ip_from, MatrixSP const& ip_to);

bool eq(const MatrixSP& ip_lhs, const MatrixSP& ip_rhs);
bool cmp(const MatrixSP& ip_lhs, const MatrixSP& ip_rhs);
bool solvable(const MatrixSP& ip_matrix, const MatrixSP& ip_solution);

std::size_t countInversions(const RowMatrix& i_input, const RowMatrix& i_solution);
std::size_t countInversions(const MatrixSP& ip_matrix, const RowMatrix& i_solution);
RowMatrix makeRow(const MatrixSP& ip_matrix);

bool cmp(const State& i_lhs, const State& i_rhs);

const MatrixSP& data(const State& i_state);
std::vector<State> expand(const State& i_state, const HeuristicFunction& i_heuristic_function);
const std::size_t& h(State& i_state);
std::size_t& g(State& i_state);
const StateSP& predecessor(const State& i_state);
StateSP& predecessor(State& i_state);
std::list<Move> collectMoves(const State& i_state);

}
