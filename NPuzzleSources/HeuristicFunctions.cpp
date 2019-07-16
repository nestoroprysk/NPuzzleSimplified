#include "HeuristicFunctions.hpp"
#include "Utils.hpp"

namespace {

std::size_t diff(const std::size_t a, const std::size_t b)
{
	return a > b ? a - b : b - a;
}

}

Manhattan::Manhattan(const Matrix& i_solution)
	: m_mapper(Utils::map(i_solution))
{
}

// TODO: test
std::size_t Manhattan::operator()(const Matrix& i_matrix, const std::size_t i) const
{
	return distanceX(i_matrix, i) + distanceY(i_matrix, i);
}

std::size_t Manhattan::distanceX(const Matrix& i_matrix, const std::size_t i) const
{
	const auto xPosActual = i % i_matrix.size();
	const auto xPosExpected = m_mapper.at(i_matrix[i]) % i_matrix.size();
	return diff(xPosActual, xPosExpected);
}

std::size_t Manhattan::distanceY(const Matrix& i_matrix, const std::size_t i) const
{
	const auto yPosActual = i / i_matrix.size();
	const auto yPosExpected =  m_mapper.at(i_matrix[i]) / i_matrix.size();
	return diff(yPosActual, yPosExpected);
}
