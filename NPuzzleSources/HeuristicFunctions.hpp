#pragma once

#include "Types.hpp"

template <std::size_t N>
class Heuristic
{
public:
	Heuristic(const Matrix<N>& i_solution);
	std::size_t manhattan(const Matrix<N>& i_matrix) const;
	std::size_t inversions(const Matrix<N>& i_matrix) const;

private:
	std::size_t distanceX(const Matrix<N>& i_matrix, const std::size_t i) const;
	std::size_t distanceY(const Matrix<N>& i_matrix, const std::size_t i) const;

private:
	ValueToPosition m_mapper;
};
