#pragma once

#include <Types.hpp>

template <std::size_t N>
struct Tester
{
static bool isCorrectlySolved(const Matrix<N>& i_initial, const Matrix<N>& i_desired, const Solution& i_solution);
Tester() = delete;
};
