#include "Utils.hpp"
#include "State.hpp"
#include "SolverConfiguration.hpp"

#include <unordered_set>
#include <deque>

template <typename Container>
class Queue;

class Set;

namespace {

Move oppositeMove(Move i_move)
{
	switch (i_move){
		case Move::Left: return Move::Right;
		case Move::Right: return Move::Left;
		case Move::Up: return Move::Down;
		case Move::Down: return Move::Up;
		default: throw std::logic_error("oppositeMove(), invalid move type");
	}
}

}

// TODO: test
auto Utils::possibleMoves(const Matrix& i_matrix) -> std::unordered_set<Move>
{
	auto result = std::unordered_set<Move>();
	const auto movingPointIndex = i_matrix.getMovingPointIndex();
	if (movingPointIndex % i_matrix.size() != 0)
		result.insert(Move::Left);
	if (movingPointIndex % i_matrix.size() != i_matrix.size() - 1)
		result.insert(Move::Right);
	if (movingPointIndex / i_matrix.size() != 0)
		result.insert(Move::Up);
	if (movingPointIndex / i_matrix.size() != i_matrix.size() - 1)
		result.insert(Move::Down);
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
	for (const auto m : ms){
		auto p_matrix = move(i_state.mp_data, m);
		const auto cost = i_heuristic_function(*p_matrix);
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

std::ostream& Utils::operator<<(std::ostream& o_stream, const Matrix& i_matrix)
{
	for (std::size_t i = 0; i < i_matrix.sizeSquared(); ++i){
		if (i == 0)
			;
		else if (i % i_matrix.size() == 0)
			o_stream << std::endl;
		else
			o_stream << ' ';
		o_stream << i_matrix[i];
	}
	return o_stream;
}

std::ostream& Utils::operator<<(std::ostream& o_stream, const SolverConfiguration& i_config)
{
	o_stream << "Test name: " << i_config.m_name << std::endl;
	o_stream << "Desired solution:" << std::endl;
	o_stream << i_config.m_desired_solution << std::endl;
	// print heuristic
	o_stream << "Heuristic function weight: " << i_config.m_heuristic_function_weight << std::endl;
	o_stream << "Distance weight: " << i_config.m_distance_weight << std::endl;
	return o_stream;
}

std::ostream& Utils::operator<<(std::ostream& o_stream, Move i_move)
{
	switch (i_move){
		case Move::Up:
			o_stream << "Up";
			break;
		case Move::Down:
			o_stream << "Down";
			break;
		case Move::Left:
			o_stream << "Left";
			break;
		case Move::Right:
			o_stream << "Right";
			break;
		default: throw std::logic_error("<<(move), Invalid move");
	}
	return o_stream;
}

template <>
void Utils::printContainer<Set>(std::ostream& o_stream)
{
	o_stream << "Set";
}

template <>
void Utils::printContainer<Queue<std::vector<State>>>(std::ostream& o_stream)
{
	o_stream << "queue on vector";
}

template <>
void Utils::printContainer<Queue<std::deque<State>>>(std::ostream& o_stream)
{
	o_stream << "queue on deque";
}
