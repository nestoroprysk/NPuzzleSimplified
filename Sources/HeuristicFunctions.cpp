#include "HeuristicFunctions.hpp"

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

const auto expectedPosition = [](const auto i_n, const auto& i_solution) -> Point{
	for (std::size_t i = 0; i < i_solution.size(); ++i)
		for (std::size_t j = 0; j < i_solution.size(); ++j)
			if (i_solution[i][j] == i_n)
				return {i, j};
	throw std::logic_error("Invalid number [" + std::to_string(i_n) + "]");
};

}

std::size_t Heuristic::manhattan(const Matrix& i_input, const Matrix& i_solution)
{
	auto result = 0;
	for (std::size_t i = 0; i < i_input.size(); ++i)
		for (std::size_t j = 0; j < i_input.size(); ++j)
			result += distance({i, j}, expectedPosition(i_input[i][j], i_solution));
	return result;
};
