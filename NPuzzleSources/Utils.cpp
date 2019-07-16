#include "Utils.hpp"
#include "State.hpp"
#include "SolverConfiguration.hpp"

#include <unordered_set>
#include <deque>

template <typename Container>
class Queue;

class Set;

// TODO: test
auto Utils::possibleMoves(const Matrix& i_matrix) -> std::vector<Move>
{
	auto result = std::vector<Move>();
	const auto movingPointIndex = i_matrix.getMovingPointIndex();
	if (movingPointIndex % i_matrix.size() != 0)
		result.push_back(Move::Left);
	if (movingPointIndex % i_matrix.size() != i_matrix.size() - 1)
		result.push_back(Move::Right);
	if (movingPointIndex / i_matrix.size() != 0)
		result.push_back(Move::Up);
	if (movingPointIndex / i_matrix.size() != i_matrix.size() - 1)
		result.push_back(Move::Down);
	return result;
}

MatrixSP Utils::move(const MatrixSP& ip_matrix, Move i_move)
{
	auto p_result = std::make_shared<Matrix>(*ip_matrix);
	p_result->move(i_move);
	return p_result;
}

Matrix Utils::move(const Matrix& i_matrix, Move i_move)
{
	auto result = i_matrix;
	result.move(i_move);
	return result;
}

Move Utils::inferMove(Matrix const& i_from, Matrix const& i_to)
{
	auto& matrix = const_cast<Matrix&>(i_from);
	for (auto const m : Utils::possibleMoves(i_from)) {
	    const auto reverseMove = oppositeMove(m);
	    matrix.move(m);
        if (eq(matrix, i_to)){
        	matrix.move(reverseMove);
            return m;
        }
        matrix.move(reverseMove);
    }
	throw std::logic_error("Impossible to reach the state in a single move");
}

bool Utils::eq(const Matrix& i_lhs, const Matrix& i_rhs)
{
	for (std::size_t i = 0; i < i_lhs.sizeSquared(); ++i)
		if (i_lhs[i] != i_rhs[i])
			return false;
	return true;
}

bool Utils::cmp(const Matrix& i_lhs, const Matrix& i_rhs)
{
	for (std::size_t i = 0; i < i_lhs.sizeSquared(); ++i)
		if (i_lhs[i] != i_rhs[i])
			return i_lhs[i] < i_rhs[i];
	return false;
}

bool Utils::solvable(const Matrix& i_matrix, const Matrix& i_solution)
{
	if (i_matrix.size() % 2 != 0){
		return countInversions(i_matrix, map(i_solution)) % 2 == 0;
	}
	else{
		throw "Unimplemented";
	}
}

std::size_t Utils::countInversions(const Matrix& i_matrix, const ValueToPosition& i_mapper)
{
	// TODO: test
	auto result = 0;
	for (std::size_t i = 0; i < i_matrix.sizeSquared(); ++i)
		for (std::size_t j = i + 1; j < i_matrix.sizeSquared(); ++j)
			if (isInverted(i_mapper, i_matrix[i], i_matrix[j]))
				++result;
	return result;
}

bool Utils::eq(const State& i_lhs, const State& i_rhs)
{
	return i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost
		&& Utils::eq(Utils::data(i_lhs), Utils::data(i_rhs));
}

auto Utils::data(const State& i_state) -> const Matrix&
{
	return *i_state.mp_data;
}

std::vector<State> Utils::expand(const State& i_state, const HeuristicFunction& i_heuristic_function)
{
	const auto ms = possibleMoves(data(i_state));
	auto result = std::vector<State>();
	const auto& matrix = data(i_state);
	const auto heuristicCost = i_state.m_heuristic_cost;
	for (const auto m : ms){
		auto p_matrix = move(i_state.mp_data, m);
		const auto cost = updateCost(matrix, *p_matrix, i_heuristic_function, heuristicCost);
		result.emplace_back(p_matrix, cost);
	}
	return result;
}

const std::size_t& Utils::h(State& i_state)
{
	return i_state.m_heuristic_cost;
}

std::size_t& Utils::g(State& i_state)
{
	return i_state.m_distance;
}

const StateSP& Utils::predecessor(const State& i_state)
{
	return i_state.mp_predecessor;
}

StateSP& Utils::predecessor(State& i_state)
{
	return i_state.mp_predecessor;
}

std::list<Move> Utils::collectMoves(const State& i_state)
{
	return collectMovesImpl(i_state, predecessor(i_state));
}

bool Utils::isInverted(const ValueToPosition& i_mapper, const char l, const char r)
{
	return i_mapper.at(l) > i_mapper.at(r);
}

std::list<Move> Utils::collectMovesImpl(const State& i_state,
								 const StateSP& i_opt_predecessor,
								 std::list<Move> o_result)
{
	if (i_opt_predecessor)
	{
		o_result.push_front(Utils::inferMove(Utils::data(*i_opt_predecessor), Utils::data(i_state)));
		return collectMovesImpl(*i_opt_predecessor, Utils::predecessor(*i_opt_predecessor), std::move(o_result));
	}
	return o_result;
}

ValueToPosition Utils::map(const Matrix& i_solution)
{
	ValueToPosition result;
	for (std::size_t i = 0; i < i_solution.sizeSquared(); ++i)
		result[i_solution[i]] = i;
	return result;
}

std::size_t Utils::accumulateHeuristicCost(const Matrix& i_matrix, const HeuristicFunction& i_h)
{
	auto result = std::size_t(0);
	for (std::size_t i = 0; i < i_matrix.sizeSquared(); ++i)
		result += i_h(i_matrix, i);
	return result;
}

// TODO: test
std::size_t Utils::updateCost(const Matrix& i_old, const Matrix& i_new,
		const HeuristicFunction& i_heuristic_function, const std::size_t i_old_cost)
{
	const auto oldCost = i_old_cost;
	const auto oldMovingPointIndex = i_old.getMovingPointIndex();
	const auto newMovingPointIndex = i_new.getMovingPointIndex();
	const auto oldCostA = i_heuristic_function(i_old, oldMovingPointIndex);
	const auto oldCostB = i_heuristic_function(i_old, newMovingPointIndex);
	const auto newCostA = i_heuristic_function(i_new, oldMovingPointIndex);
	const auto newCostB = i_heuristic_function(i_new, newMovingPointIndex);
	return oldCost - oldCostA + newCostA - oldCostB + newCostB;
}

Move Utils::oppositeMove(Move i_move)
{
	switch (i_move){
		case Move::Left: return Move::Right;
		case Move::Right: return Move::Left;
		case Move::Up: return Move::Down;
		case Move::Down: return Move::Up;
		default: throw std::logic_error("oppositeMove(), invalid move type");
	}
}
