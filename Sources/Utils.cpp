#include "Utils.hpp"

namespace {

static constexpr auto g_moving_point = 0;

const auto swap = [](Matrix const& i_matrix, Point const a, Point const b) -> Matrix
{
	auto result = i_matrix;
	std::swap(result[a.i][a.j], result[b.i][b.j]);
	return result;
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

Matrix Utils::move(Matrix const& i_matrix, Move i_move)
{
	if (!Utils::isValid(i_matrix, i_move))
		throw std::logic_error("Invalid move");
	const auto p = movingPointCoordinates(i_matrix);
	switch (i_move)
	{
		case Move::Left:
			return swap(i_matrix, p, {p.i, p.j - 1});
		case Move::Right:
			return swap(i_matrix, p, {p.i, p.j + 1});
		case Move::Up:
			return swap(i_matrix, p, {p.i - 1, p.j});
		case Move::Down:
			return swap(i_matrix, p, {p.i + 1, p.j});
		default:
			throw std::logic_error("Impossible move");
	}
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

RowMatrix Utils::makeRow(const Matrix& i_matrix)
{
	auto result = RowMatrix();
	for (auto i = 0; i < i_matrix.size(); ++i)
		for (auto j = 0; j < i_matrix.size(); ++j)
			result.push_back(i_matrix[i][j]);
	return result;
};
