#include "Utils.hpp"
#include "State.hpp"
#include "Matrix.hpp"

namespace {

static constexpr auto g_moving_point = 0;

const auto swap = [](MatrixSP& iop_matrix, Point const a, Point const b)
{
	std::swap(iop_matrix->at(a.i, a.j), iop_matrix->at(b.i, b.j));
};

const auto movingPointCoordinates = [](const auto& ip_matrix) -> Point
{
	for (std::size_t i = 0; i < ip_matrix->size(); ++i)
		for (std::size_t j = 0; j < ip_matrix->size(); ++j)
			if (ip_matrix->at(i, j) == g_moving_point)
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

auto Utils::possibleMoves(MatrixSP const& ip_matrix) -> std::unordered_set<Move>
{
	std::unordered_set<Move> result;
	const auto p = movingPointCoordinates(ip_matrix);
	if (p.i != 0) result.insert(Move::Up);
	if (p.i != ip_matrix->size() - 1) result.insert(Move::Down);
	if (p.j != 0) result.insert(Move::Left);
	if (p.j != ip_matrix->size() - 1) result.insert(Move::Right);
	return result;
}

bool Utils::isValid(MatrixSP const& ip_matrix, Move i_move)
{
	const auto ms = Utils::possibleMoves(ip_matrix);
	return ms.find(i_move) != ms.cend();
}

MatrixSP Utils::move(const MatrixSP& ip_matrix, Move i_move)
{
	auto p_result = ip_matrix->clone();
	move(p_result, i_move);
	return p_result;
}

MatrixSP& Utils::move(MatrixSP& iop_matrix, Move i_move)
{
	if (!Utils::isValid(iop_matrix, i_move))
		throw std::logic_error("Invalid move");
	const auto p = movingPointCoordinates(iop_matrix);
	switch (i_move)
	{
		case Move::Left:
			swap(iop_matrix, p, {p.i, p.j - 1});
			break;
		case Move::Right:
			swap(iop_matrix, p, {p.i, p.j + 1});
			break;
		case Move::Up:
			swap(iop_matrix, p, {p.i - 1, p.j});
			break;
		case Move::Down:
			swap(iop_matrix, p, {p.i + 1, p.j});
			break;
		default:
			throw std::logic_error("Impossible move");
	}
	return iop_matrix;
}

Move Utils::inferMove(MatrixSP const& ip_from, MatrixSP const& ip_to)
{
	if (eq(ip_from, ip_to))
		throw std::logic_error("Unequal matrices expected");
	for (auto const m : Utils::possibleMoves(ip_from))
		if (eq(Utils::move(ip_from, m), ip_to))
			return m;
	throw std::logic_error("Impossible to reach the state in a single move");
}

bool Utils::eq(const MatrixSP& ip_lhs, const MatrixSP& ip_rhs)
{
	for (std::size_t i = 0; i < ip_lhs->size(); ++i)
		for (std::size_t j = 0; j < ip_lhs->size(); ++j)
			if (ip_lhs->at(i, j) != ip_rhs->at(i, j))
				return false;
	return true;
}

bool Utils::solvable(const MatrixSP& ip_matrix, const MatrixSP& ip_solution)
{
	if (ip_matrix->size() % 2 != 0){
		return countInversions(makeRow(ip_matrix), makeRow(ip_solution)) % 2 == 0; 
	}
	else{
		throw "Unimplemented";
	}
}

// TODO: refactor
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

std::size_t Utils::countInversions(const MatrixSP& ip_matrix, const RowMatrix& i_solution)
{
	auto result = 0;
	for (std::size_t i = 0; i < i_solution.size(); ++i){
		for (std::size_t j = i + 1; j < i_solution.size(); ++j){
			if (isInverted(i_solution, ip_matrix->at(i / ip_matrix->size(), i % ip_matrix->size()),
					ip_matrix->at(j / ip_matrix->size(), j % ip_matrix->size())))
				++result;
		}
	}
	return result;
}

// TODO: delete
RowMatrix Utils::makeRow(const MatrixSP& ip_matrix)
{
	auto result = RowMatrix();
	for (std::size_t i = 0; i < ip_matrix->size(); ++i)
		for (std::size_t j = 0; j < ip_matrix->size(); ++j)
			result.push_back(ip_matrix->at(i, j));
	return result;
};

// TODO: refactor so as to cache better
bool Utils::cmp(const MatrixSP& ip_lhs, const MatrixSP& ip_rhs)
{
	for (std::size_t i = 0; i < ip_lhs->size(); ++i)
		for (std::size_t j = 0; j < ip_rhs->size(); ++j)
			if (ip_lhs->at(i, j) != ip_rhs->at(i, j))
				return ip_lhs->at(i, j) < ip_rhs->at(i, j);
	return false;
}

bool Utils::cmp(const State& i_lhs, const State& i_rhs)
{
	return i_lhs.m_heuristic_cost < i_rhs.m_heuristic_cost ||
		(i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost &&
			i_lhs.m_distance < i_rhs.m_distance) ||
			(i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost &&
				i_lhs.m_distance == i_rhs.m_distance &&
					cmp(data(i_lhs), data(i_rhs)));
}

const MatrixSP& Utils::data(const State& i_state)
{
	if (!i_state.mp_data)
		throw std::logic_error("data(s), initialized matrix expected");
	return i_state.mp_data;
}

std::vector<State> Utils::expand(const State& i_state, const HeuristicFunction& i_heuristic_function)
{
	const auto ms = possibleMoves(data(i_state));
	auto result = std::vector<State>();
	for (const auto m : ms){
		auto p_matrix = move(data(i_state), m);
		const auto cost = i_heuristic_function(p_matrix);
		result.emplace_back(std::move(p_matrix), cost);
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
