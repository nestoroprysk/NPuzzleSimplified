#pragma once

#include "Types.hpp"

// TODO: refactor and make hash-like
class Heuristic
{
public:
	Heuristic(const Matrix& i_solution);
	std::size_t manhattan(const Matrix& i_matrix) const;
	std::size_t inversions(const Matrix& i_matrix) const;
private:
	std::size_t distanceX(const Matrix& i_matrix, const std::size_t i) const;
	std::size_t distanceY(const Matrix& i_matrix, const std::size_t i) const;

private:
	ValueToPosition m_mapper;
};
