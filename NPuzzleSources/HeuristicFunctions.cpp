#include "HeuristicFunctions.hpp"
#include "Utils.hpp"

#include <string>

namespace {

std::size_t diff(const std::size_t a, const std::size_t b)
{
	return a > b ? a - b : b - a;
}

template <std::size_t N>
std::size_t distanceX(const Matrix<N>& i_matrix, const Matrix<N>& i_solution, const std::size_t i)
{
	const auto xPosActual = i % N;
	// TODO: make const
	const auto xPosExpected = std::distance(i_solution.cbegin(),
		std::find(i_solution.cbegin(), i_solution.cend(), i_matrix[i])) % N;
	return diff(xPosActual, xPosExpected);
}

template <std::size_t N>
std::size_t distanceY(const Matrix<N>& i_matrix, const Matrix<N>& i_solution, const std::size_t i)
{
	const auto yPosActual = i / N;
	// TODO: make const
	const auto yPosExpected =  std::distance(i_solution.cbegin(),
		std::find(i_solution.cbegin(), i_solution.cend(), i_matrix[i])) / N;
	return diff(yPosActual, yPosExpected);
}

}

// TODO: test
template <std::size_t N>
std::size_t Heuristic<N>::manhattan(const Matrix<N>& i_matrix, const Matrix<N>& i_solution)
{
	auto result = std::size_t(0);
	for (std::size_t i = 0; i < N * N; ++i)
		result += distanceX<N>(i_matrix, i_solution, i) + distanceY<N>(i_matrix, i_solution, i);
	return result;
}

template <std::size_t N>
std::size_t Heuristic<N>::inversions(const Matrix<N>& i_input, const Matrix<N>& i_solution)
{
	return Utils<N>::countInversions(i_input, i_solution);
}

EXPLICITLY_INSTANTIATE_STRUCT(Heuristic);
