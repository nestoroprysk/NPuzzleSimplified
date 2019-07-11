#pragma once

#include "Types.hpp"

template <std::size_t N>
struct Heuristic
{
static std::size_t manhattan(const Matrix<N>& i_matrix, const Matrix<N>& i_solution);
static std::size_t inversions(const Matrix<N>& i_matrix, const Matrix<N>& i_solution);

Heuristic() = delete;
};
