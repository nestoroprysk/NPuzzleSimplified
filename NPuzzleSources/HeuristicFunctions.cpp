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

std::string Manhattan::getName() const
{
	return "Manhattan";
}

IsInCorrectPositions::IsInCorrectPositions(const Matrix& i_solution)
	: m_solution(i_solution)
{
}

std::size_t IsInCorrectPositions::operator()(const Matrix& i_matrix, const std::size_t i) const
{
	return m_solution[i] != i_matrix[i];
}

std::string IsInCorrectPositions::getName() const
{
	return "IsInCorrectPositions";
}

IsNearCorrectPosition::IsNearCorrectPosition(const Matrix& i_solution)
	: m_solution(i_solution)
{
}

// TODO: test
std::size_t IsNearCorrectPosition::operator()(const Matrix& i_matrix, const std::size_t i) const
{
	if (m_solution[i] == i_matrix[i])
		return 0;
	if (i % i_matrix.size() != 0)
		if (m_solution[i - 1] == i_matrix[i])
			return 0;
	if (i % i_matrix.size() != i_matrix.size() - 1)
		if (m_solution[i + 1] == i_matrix[i])
			return 0;
	if (i / i_matrix.size() != 0)
		if (m_solution[i - i_matrix.size()] == i_matrix[i])
			return 0;
	if (i / i_matrix.size() != i_matrix.size() - 1)
		if (m_solution[i + i_matrix.size()] == i_matrix[i])
			return 0;
	return 1;
}

std::string IsNearCorrectPosition::getName() const
{
	return "IsNearCorrectPosition";
}
