#include "HeuristicFunctions.hpp"
#include "Utils.hpp"

#include <string>

namespace {

std::size_t diff(const std::size_t a, const std::size_t b)
{
	return a > b ? a - b : b - a;
}

}

template <std::size_t N>
Heuristic<N>::Heuristic(const Matrix<N>& i_solution)
	: m_mapper(Utils<N>::map(i_solution))
{
}

// TODO: test
template <std::size_t N>
std::size_t Heuristic<N>::manhattan(const Matrix<N>& i_matrix) const
{
	auto result = std::size_t(0);
	for (std::size_t i = 0; i < i_matrix.sizeSquared(); ++i)
		result += distanceX(i_matrix, i) + distanceY(i_matrix, i);
	return result;
}

template <std::size_t N>
std::size_t Heuristic<N>::inversions(const Matrix<N>& i_input) const
{
	return Utils<N>::countInversions(i_input, m_mapper);
}

template <std::size_t N>
std::size_t Heuristic<N>::distanceX(const Matrix<N>& i_matrix, const std::size_t i) const
{
	const auto xPosActual = i % i_matrix.size();
	const auto xPosExpected = m_mapper.at(i_matrix[i]) % i_matrix.size();
	return diff(xPosActual, xPosExpected);
}

template <std::size_t N>
std::size_t Heuristic<N>::distanceY(const Matrix<N>& i_matrix, const std::size_t i) const
{
	const auto yPosActual = i / i_matrix.size();
	const auto yPosExpected =  m_mapper.at(i_matrix[i]) / i_matrix.size();
	return diff(yPosActual, yPosExpected);
}

EXPLICITLY_INSTANTIATE_CLASS(Heuristic);
