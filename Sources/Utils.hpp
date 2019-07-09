#pragma once

#include "Types.hpp"

#include <unordered_set>

namespace Utils{

auto possibleMoves(Matrix const& i_state) -> std::unordered_set<Move>;
bool isValid(Matrix const& i_state, Move i_move);
Matrix move(Matrix const& i_state, Move i_move);
Move inferMove(Matrix const& i_from, Matrix const& i_to);

bool isSquare(const Matrix& i_matrix);
bool eq(const Matrix& i_lhs, const Matrix& i_rhs);
bool solvable(const Matrix& i_matrix, const Matrix& i_solution);

std::size_t countInversions(const RowMatrix& i_input, const RowMatrix& i_solution);
std::size_t countInversions(const Matrix& i_matrix, const RowMatrix& i_solution);
RowMatrix makeRow(const Matrix& i_matrix);

static const auto cmp = [](const auto& i_lhs, const auto& i_rhs){
	return i_lhs.m_heuristic_cost < i_rhs.m_heuristic_cost
		|| (i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost &&
			i_lhs.m_distance < i_rhs.m_distance);
};

}
