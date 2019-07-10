#include "HeuristicFunctions.hpp"
#include "Utils.hpp"
#include "Matrix.hpp"

#include <string>

namespace {

const auto diff = [](std::size_t i_a, std::size_t i_b)
{
    return i_a > i_b ? i_a - i_b : i_b - i_a;
};

const auto distance = [](Point const& i_from, Point const& i_to)
{
	return diff(i_from.i, i_to.i) + diff(i_from.j, i_to.j);
};

const auto expectedPosition = [](const auto i_n, const auto& ip_solution) -> Point{
	for (std::size_t i = 0; i < ip_solution->size(); ++i)
		for (std::size_t j = 0; j < ip_solution->size(); ++j)
			if (ip_solution->at(i, j) == i_n)
				return {i, j};
	throw std::logic_error("Invalid number [" + std::to_string(i_n) + "]");
};

}

std::size_t Heuristic::manhattan(const MatrixSP& ip_input, const MatrixSP& ip_solution)
{
	auto result = 0;
	for (std::size_t i = 0; i < ip_input->size(); ++i)
		for (std::size_t j = 0; j < ip_input->size(); ++j)
			result += distance({i, j}, expectedPosition(ip_input->at(i, j), ip_solution));
	return result;
};

std::size_t Heuristic::inversions(const MatrixSP& ip_input, const RowMatrix& i_solution)
{
	return Utils::countInversions(ip_input, i_solution);
}
