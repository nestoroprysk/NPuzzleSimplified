#include "Tester.hpp"

#include <Solver.hpp>
#include <Utils.hpp>

namespace {

using It = Solution::const_iterator;

bool isCorrectlySolvedImpl(Matrix i_matrix, const Matrix& i_desired, It const& i_it, It const& i_end)
{
	if (i_it == i_end)
		return Utils::eq(i_matrix, i_desired);
	i_matrix.move(*i_it);
	return isCorrectlySolvedImpl(std::move(i_matrix), i_desired, std::next(i_it), i_end);
}

}

bool Tester::isCorrectlySolved(Matrix i_initial, const Matrix& i_desired, const Solution& i_solution)
{
	return isCorrectlySolvedImpl(std::move(i_initial), i_desired, i_solution.cbegin(), i_solution.cend());
}
