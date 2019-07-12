#include "Utils.hpp"
#include "State.hpp"

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
template <std::size_t N>
auto Utils<N>::possibleMoves(const MatrixNxN& i_matrix) -> std::unordered_set<Move>
{
	auto result = std::unordered_set<Move>();
	const auto movingPointIndex = i_matrix.getMovingPointIndex();
	if (movingPointIndex % N != 0)
		result.insert(Move::Left);
	if (movingPointIndex % N != N - 1)
		result.insert(Move::Right);
	if (movingPointIndex / N != 0)
		result.insert(Move::Up);
	if (movingPointIndex / N != N - 1)
		result.insert(Move::Down);
	return result;
}

template <std::size_t N>
MatrixSP<N> Utils<N>::move(const MatrixSP<N>& ip_matrix, Move i_move)
{
	auto p_result = std::make_shared<Matrix<N>>(*ip_matrix);
	p_result->move(i_move);
	return p_result;
}

template <std::size_t N>
Matrix<N> Utils<N>::move(const Matrix<N>& i_matrix, Move i_move)
{
	auto result = i_matrix;
	result.move(i_move);
	return result;
}

template <std::size_t N>
Move Utils<N>::inferMove(MatrixNxN const& i_from, MatrixNxN const& i_to)
{
	auto& matrix = const_cast<MatrixNxN&>(i_from);
	for (auto const m : Utils<N>::possibleMoves(i_from)) {
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

template <std::size_t N>
bool Utils<N>::eq(const MatrixNxN& i_lhs, const MatrixNxN& i_rhs)
{
	for (std::size_t i = 0; i < N * N; ++i)
		if (i_lhs[i] != i_rhs[i])
			return false;
	return true;
}

template <std::size_t N>
bool Utils<N>::solvable(const MatrixNxN& i_matrix, const MatrixNxN& i_solution)
{
	if (N % 2 != 0){
		return countInversions(i_matrix, map(i_solution)) % 2 == 0;
	}
	else{
		throw "Unimplemented";
	}
}

template <std::size_t N>
std::size_t Utils<N>::countInversions(const MatrixNxN& i_matrix, const ValueToPosition& i_mapper)
{
	// TODO: test
	auto result = 0;
	for (std::size_t i = 0; i < N * N; ++i)
		for (std::size_t j = i + 1; j < N * N; ++j)
			if (isInverted(i_mapper, i_matrix[i], i_matrix[j]))
				++result;
	return result;
}

template <std::size_t N>
auto Utils<N>::data(const State<N>& i_state) -> const MatrixNxN&
{
	return *i_state.mp_data;
}

template <std::size_t N>
std::vector<State<N>> Utils<N>::expand(const State<N>& i_state, const HeuristicFunction<N>& i_heuristic_function)
{
	const auto ms = possibleMoves(data(i_state));
	auto result = std::vector<State<N>>();
	for (const auto m : ms){
		auto p_matrix = move(i_state.mp_data, m);
		const auto cost = i_heuristic_function(*p_matrix);
		result.emplace_back(p_matrix, cost);
	}
	return result;
}

template <std::size_t N>
const std::size_t& Utils<N>::h(State<N>& i_state)
{
	return i_state.m_heuristic_cost;
}

template <std::size_t N>
std::size_t& Utils<N>::g(State<N>& i_state)
{
	return i_state.m_distance;
}

template <std::size_t N>
const StateSP<N>& Utils<N>::predecessor(const State<N>& i_state)
{
	return i_state.mp_predecessor;
}

template <std::size_t N>
StateSP<N>& Utils<N>::predecessor(State<N>& i_state)
{
	return i_state.mp_predecessor;
}

template <std::size_t N>
std::list<Move> Utils<N>::collectMoves(const State<N>& i_state)
{
	return collectMovesImpl(i_state, predecessor(i_state));
}

template <std::size_t N>
bool Utils<N>::isInverted(const ValueToPosition& i_mapper, const char l, const char r)
{
	return i_mapper.at(l) > i_mapper.at(r);
}

template <std::size_t N>
std::list<Move> Utils<N>::collectMovesImpl(const State<N>& i_state,
								 const StateSP<N>& i_opt_predecessor,
								 std::list<Move> o_result)
{
	if (i_opt_predecessor)
	{
		o_result.push_front(Utils<N>::inferMove(Utils<N>::data(*i_opt_predecessor), Utils<N>::data(i_state)));
		return collectMovesImpl(*i_opt_predecessor, Utils<N>::predecessor(*i_opt_predecessor), std::move(o_result));
	}
	return o_result;
}

template <std::size_t N>
ValueToPosition Utils<N>::map(const Matrix<N>& i_solution)
{
	ValueToPosition result;
	for (std::size_t i = 0; i < N * N; ++i)
		result[i_solution[i]] = i;
	return result;
}

EXPLICITLY_INSTANTIATE_STRUCT(Utils);
