#pragma once

#include "Types.hpp"

struct SolverConfiguration;

namespace Utils {

static constexpr auto g_step_cost = 1;
static constexpr auto g_bucket_count = 8;
static constexpr auto g_min_n = 3;
static constexpr auto g_max_n = 500;

auto possibleMoves(const Matrix& i_state) -> std::vector<Move>;
MatrixSP move(const MatrixSP& ip_matrix, Move i_move);
Matrix move(const Matrix& i_matrix, Move i_move);
Move inferMove(Matrix const& i_from, Matrix const& i_to);

bool eq(const Matrix& ip_lhs, const Matrix& ip_rhs);
bool cmp(const Matrix& ip_lhs, const Matrix& ip_rhs);
bool solvable(const Matrix& ip_matrix, const Matrix& ip_solution);

std::size_t countInversions(const Matrix& i_input, const ValueToPosition& i_mapper);

bool eq(const State& i_lhs, const State& i_rhs);

const Matrix& data(const State& i_state);
std::vector<State> expand(const State& i_state, const HeuristicFunction& i_heuristic_function);
const std::size_t& h(State& i_state);
std::size_t& g(State& i_state);
const StateSP& predecessor(const State& i_state);
StateSP& predecessor(State& i_state);
std::list<Move> collectMoves(const State& i_state);

bool isInverted(const ValueToPosition& i_mapper, const std::size_t l, const std::size_t r);
std::list<Move> collectMovesImpl(const State& i_state,
                                 const StateSP& i_opt_predecessor,
                                 std::list<Move> o_result = std::list<Move>());
ValueToPosition map(const Matrix& i_solution);

std::size_t accumulateHeuristicCost(const Matrix& i_matrix, const HeuristicFunction& i_h);
std::size_t updateCost(const Matrix& i_old, const Matrix& i_new,
    const HeuristicFunction& i_heuristic_function, const std::size_t i_old_cost);

Move oppositeMove(Move i_move);

bool isCorrectlySolved(Matrix i_initial, const Matrix& i_desired, const Solution& i_solution);

Matrix generateSnakeSolution(const std::size_t i_n);
Matrix generateRandomMap(const std::size_t i_n);

}
