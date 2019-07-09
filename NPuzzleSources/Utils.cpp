#include "Utils.hpp"

#include "State.hpp"

namespace {

static constexpr auto g_moving_point = 0;

const auto swap = [](Matrix& io_matrix, Point const a, Point const b)
{
	std::swap(io_matrix[a.i][a.j], io_matrix[b.i][b.j]);
};

const auto movingPointCoordinates = [](const auto& i_matrix) -> Point
{
	for (std::size_t i = 0; i < i_matrix.size(); ++i)
		for (std::size_t j = 0; j < i_matrix.size(); ++j)
			if (i_matrix[i][j] == g_moving_point)
				return {i, j};
	throw std::logic_error("No moving point found");
};

const auto isInverted = [](const auto& i_solution, const auto l, const auto r){
	const auto lPos = std::find(i_solution.cbegin(), i_solution.cend(), l);
	const auto rPos = std::find(i_solution.cbegin(), i_solution.cend(), r);
	if (lPos == rPos || lPos == i_solution.cend() || rPos == i_solution.cend())
		throw std::logic_error("isInverted(), invalid input");
	return lPos > rPos;
};

std::list<Move> collectMovesImpl(const State& i_state,
								 const StateSP& i_opt_predecessor,
								 std::list<Move> o_result = std::list<Move>())
{
	if (i_opt_predecessor)
	{
		o_result.push_front(Utils::inferMove(Utils::data(*i_opt_predecessor), Utils::data(i_state)));
		return collectMovesImpl(*i_opt_predecessor, Utils::predecessor(*i_opt_predecessor), std::move(o_result));
	}
	return o_result;
}

}

auto Utils::possibleMoves(Matrix const& i_matrix) -> std::unordered_set<Move>
{
	std::unordered_set<Move> result;
	const auto p = movingPointCoordinates(i_matrix);
	if (p.i != 0) result.insert(Move::Up);
	if (p.i != i_matrix.size() - 1) result.insert(Move::Down);
	if (p.j != 0) result.insert(Move::Left);
	if (p.j != i_matrix.size() - 1) result.insert(Move::Right);
	return result;
}

bool Utils::isValid(Matrix const& i_matrix, Move i_move)
{
	const auto ms = Utils::possibleMoves(i_matrix);
	return ms.find(i_move) != ms.cend();
}

Matrix Utils::move(const Matrix& i_matrix, Move i_move)
{
	auto result = i_matrix;
	move(result, i_move);
	return result;
}

Matrix& Utils::move(Matrix& io_matrix, Move i_move)
{
	if (!Utils::isValid(io_matrix, i_move))
		throw std::logic_error("Invalid move");
	const auto p = movingPointCoordinates(io_matrix);
	switch (i_move)
	{
		case Move::Left:
			swap(io_matrix, p, {p.i, p.j - 1});
			break;
		case Move::Right:
			swap(io_matrix, p, {p.i, p.j + 1});
			break;
		case Move::Up:
			swap(io_matrix, p, {p.i - 1, p.j});
			break;
		case Move::Down:
			swap(io_matrix, p, {p.i + 1, p.j});
			break;
		default:
			throw std::logic_error("Impossible move");
	}
	return io_matrix;
}

Move Utils::inferMove(Matrix const& i_from, Matrix const& i_to)
{
	if (i_from == i_to)
		throw std::logic_error("Unequal matrices expected");
	for (auto const m : Utils::possibleMoves(i_from))
		if (Utils::move(i_from, m) == i_to)
			return m;
	throw std::logic_error("Impossible to reach the state in a single move");
}

bool Utils::isSquare(const Matrix& i_matrix)
{
	const auto size = i_matrix.size();
	return std::all_of(i_matrix.cbegin(), i_matrix.cend(),
		[size](const auto& i_row){return i_row.size() == size;});
}

bool Utils::eq(const Matrix& i_lhs, const Matrix& i_rhs)
{
	const auto valid = isSquare(i_lhs) && isSquare(i_rhs) &&
		i_rhs.size() == i_rhs.size();
	if (!valid)
		throw std::logic_error("Invalid eq arguments");
	for (auto i = 0; i < i_lhs.size(); ++i)
		for (auto j = 0; j < i_lhs.size(); ++j)
			if (i_lhs[i][j] != i_rhs[i][j])
				return false;
	return true;
}

bool Utils::solvable(const Matrix& i_matrix, const Matrix& i_solution)
{
	if (i_matrix.size() % 2 != 0){
		return countInversions(makeRow(i_matrix), makeRow(i_solution)) % 2 == 0; 
	}
	else{
		throw "Unimplemented";
	}
}

std::size_t Utils::countInversions(const RowMatrix& i_input, const RowMatrix& i_solution)
{
	auto result = 0;
	for (std::size_t i = 0; i < i_input.size(); ++i){
		for (std::size_t j = i + 1; j < i_input.size(); ++j){
			if (isInverted(i_solution, i_input[i], i_input[j]))
				++result;
		}
	}
	return result;
}

std::size_t Utils::countInversions(const Matrix& i_matrix, const RowMatrix& i_solution)
{
	auto result = 0;
	for (std::size_t i = 0; i < i_solution.size(); ++i){
		for (std::size_t j = i + 1; j < i_solution.size(); ++j){
			if (isInverted(i_solution, i_matrix[i / i_matrix.size()][i % i_matrix.size()],
					i_matrix[j / i_matrix.size()][j % i_matrix.size()]))
				++result;
		}
	}
	return result;
}

RowMatrix Utils::makeRow(const Matrix& i_matrix)
{
	auto result = RowMatrix();
	for (auto i = 0; i < i_matrix.size(); ++i)
		for (auto j = 0; j < i_matrix.size(); ++j)
			result.push_back(i_matrix[i][j]);
	return result;
};

std::size_t Utils::hash(const State& i_state)
{
	return i_state.m_heuristic_cost;
}

bool Utils::eq(const State& i_lhs, const State& i_rhs)
{
	return !cmp(i_lhs, i_rhs) && !cmp(i_rhs, i_lhs);
}

bool Utils::cmp(const State& i_lhs, const State& i_rhs)
{
	return i_lhs.m_heuristic_cost < i_rhs.m_heuristic_cost
		|| (i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost &&
			i_lhs.m_distance < i_rhs.m_distance);
}

const Matrix& Utils::data(const State& i_state)
{
	if (!i_state.mp_data)
		throw std::logic_error("data(s), initialized matrix expected");
	return *i_state.mp_data;
}

std::vector<State> Utils::expand(const State& i_state, const HeuristicFunction& i_heuristic_function)
{
	const auto ms = possibleMoves(data(i_state));
	auto result = std::vector<State>();
	for (const auto m : ms){
		auto matrix = move(data(i_state), m);
		const auto cost = i_heuristic_function(matrix);
		result.emplace_back(std::move(matrix), cost);
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
