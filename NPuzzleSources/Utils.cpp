#include "Utils.hpp"
#include "State.hpp"

// TODO: test
template <std::size_t N>
auto Utils<N>::possibleMoves(const MatrixNxN& i_matrix) -> std::unordered_set<Move>
{
	auto result = std::unordered_set<Move>();
	// TODO: make constant
	const auto movingPointIndex = std::distance(i_matrix.cbegin(),
		std::find(i_matrix.cbegin(), i_matrix.cend(), g_moving_point));
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
bool Utils<N>::isValid(const MatrixNxN& i_matrix, Move i_move)
{
	const auto ms = Utils<N>::possibleMoves(i_matrix);
	return ms.find(i_move) != ms.cend();
}

template <std::size_t N>
MatrixSP<N> Utils<N>::move(const MatrixSP<N>& ip_matrix, Move i_move)
{
	if (!ip_matrix)
		throw std::logic_error("move(), initialized matrix expected");
	auto p_result = std::make_shared<Matrix<N>>(*ip_matrix);
	moveInput(*p_result, i_move);
	return p_result;
}

template <std::size_t N>
Matrix<N> Utils<N>::move(const Matrix<N>& i_matrix, Move i_move)
{
	auto result = i_matrix;
	moveInput(result, i_move);
	return result;
}

template <std::size_t N>
void Utils<N>::moveInput(Matrix<N>& io_matrix, Move i_move)
{
	if (!isValid(io_matrix, i_move))
		throw std::logic_error("moveInput(), invalid move");
	// TODO: make constant
	const auto movingPointIndex = std::distance(io_matrix.cbegin(),
		std::find(io_matrix.cbegin(), io_matrix.cend(), g_moving_point));
	switch (i_move){
		case Move::Left:
			std::swap(io_matrix[movingPointIndex], io_matrix[movingPointIndex - 1]);
			break;
		case Move::Right:
			std::swap(io_matrix[movingPointIndex], io_matrix[movingPointIndex + 1]);
			break;
		case Move::Up:
			std::swap(io_matrix[movingPointIndex], io_matrix[movingPointIndex - N]);
			break;
		case Move::Down:
			std::swap(io_matrix[movingPointIndex], io_matrix[movingPointIndex + N]);
			break;
		default:
			throw std::logic_error("Invalid move type");
	}
}

template <std::size_t N>
Move Utils<N>::inferMove(MatrixNxN const& i_from, MatrixNxN const& i_to)
{
	// TODO: make move cheaper
	if (eq(i_from, i_to))
		throw std::logic_error("Unequal matrices expected");
	for (auto const m : Utils<N>::possibleMoves(i_from))
		if (eq(Utils<N>::move(i_from, m), i_to))
			return m;
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
	if (!i_state.mp_data)
		throw std::logic_error("data(s), initialized matrix expected");
	return *i_state.mp_data;
}

template <std::size_t N>
std::vector<State<N>> Utils<N>::expand(const State<N>& i_state, const HeuristicFunction<N>& i_heuristic_function)
{
	// TODO: provide cache
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
