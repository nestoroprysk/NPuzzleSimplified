#include "HeuristicFunctions.hpp"
#include "Utils.hpp"

namespace {

std::size_t diff(const std::size_t a, const std::size_t b)
{
	return a > b ? a - b : b - a;
}

}

Heuristic::Heuristic(const Matrix& i_solution)
	: m_mapper(Utils::map(i_solution))
{
}

// TODO: test
std::size_t Heuristic::manhattan(const Matrix& i_matrix) const
{
	auto result = std::size_t(0);
	for (std::size_t i = 0; i < i_matrix.sizeSquared(); ++i)
		result += distanceX(i_matrix, i) + distanceY(i_matrix, i);
	return result;
}

std::size_t Heuristic::inversions(const Matrix& i_input) const
{
	return Utils::countInversions(i_input, m_mapper);
}

std::size_t Heuristic::distanceX(const Matrix& i_matrix, const std::size_t i) const
{
	const auto xPosActual = i % i_matrix.size();
	const auto xPosExpected = m_mapper.at(i_matrix[i]) % i_matrix.size();
	return diff(xPosActual, xPosExpected);
}

std::size_t Heuristic::distanceY(const Matrix& i_matrix, const std::size_t i) const
{
	const auto yPosActual = i / i_matrix.size();
	const auto yPosExpected =  m_mapper.at(i_matrix[i]) / i_matrix.size();
	return diff(yPosActual, yPosExpected);
}
