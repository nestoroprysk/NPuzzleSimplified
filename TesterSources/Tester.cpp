#include "Tester.hpp"

#include <Solver.hpp>
#include <Utils.hpp>

namespace {

using It = Solution::const_iterator;

bool isCorrectlySolvedImpl(Matrix& i_state, const Matrix& i_desired, It const& i_it, It const& i_end)
{
	if (i_it == i_end)
		return Utils::eq(i_state, i_desired);
	Utils::move(i_state, *i_it);
	return isCorrectlySolvedImpl(i_state, i_desired, std::next(i_it), i_end);
}

}

bool Tester::isCorrectlySolved(const Matrix& i_initial, const Matrix& i_desired, const Solution& i_solution)
{
	auto input = i_initial;
	return isCorrectlySolvedImpl(input, i_desired, i_solution.cbegin(), i_solution.cend());
}
