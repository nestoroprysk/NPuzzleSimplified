#pragma once

#include "Types.hpp"
#include "Result.hpp"

#include <unordered_set>
#include <ostream>

struct SolverConfiguration;

namespace Utils {

static constexpr auto g_step_cost = 1;
static constexpr auto g_bucket_count = 8;

auto possibleMoves(const Matrix& i_state) -> std::unordered_set<Move>;
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

bool isInverted(const ValueToPosition& i_mapper, const char l, const char r);
std::list<Move> collectMovesImpl(const State& i_state,
								 const StateSP& i_opt_predecessor,
								 std::list<Move> o_result = std::list<Move>());
ValueToPosition map(const Matrix& i_solution);

std::ostream& operator<<(std::ostream& o_stream, const Matrix& i_matrix);
std::ostream& operator<<(std::ostream& o_stream, const SolverConfiguration& i_config);
std::ostream& operator<<(std::ostream& o_stream, Move i_move);

template <typename Container>
std::ostream& operator<<(std::ostream& o_stream, const Result<Container>& i_result);
template <typename Container>
void printSolution(std::ostream& o_stream, const Result<Container>& i_result);
template <typename Container>
void printContainer(std::ostream& o_stream);

}

template <typename Container>
std::ostream& Utils::operator<<(std::ostream& o_stream, const Result<Container>& i_result)
{
	o_stream << "===Solver Configuration===" << std::endl;
	o_stream << i_result.m_config << std::endl;
	o_stream << "Container: "; printContainer<Container>(o_stream); o_stream << std::endl;
	o_stream << "===Input===" << std::endl;
	o_stream << i_result.m_input << std::endl;
	o_stream << "===Results Collected===" << std::endl;
	o_stream << "Number of states selected: " << i_result.m_number_of_selected_states << std::endl;
	o_stream << "Max number of states in memory: " << i_result.m_max_number_of_states_in_memory << std::endl;
	o_stream << "Execution time: " << i_result.m_execution_time << " milliseconds" << std::endl;
	o_stream << "===Solution===" << std::endl;
	printSolution(o_stream, i_result);
	return o_stream;
}

template <typename Container>
void Utils::printSolution(std::ostream& o_stream, const Result<Container>& i_result)
{
	if (!i_result.m_opt_solution){
		o_stream << "The puzzle is unsolvable";
		return;
	}
	const auto& moves = *i_result.m_opt_solution;
	auto matrix = i_result.m_input;
	for (auto m : moves){
		matrix.move(m);
		o_stream << m << std::endl;
		o_stream << matrix << std::endl;
	}
}
