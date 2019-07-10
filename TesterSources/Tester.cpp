#include "Tester.hpp"

#include <Solver.hpp>
#include <Utils.hpp>

namespace {

using It = Solution::const_iterator;

bool isCorrectlySolvedImpl(MatrixSP& ip_state, const MatrixSP& ip_desired, It const& i_it, It const& i_end)
{
	if (i_it == i_end)
		return Utils::eq(ip_state, ip_desired);
	Utils::move(ip_state, *i_it);
	return isCorrectlySolvedImpl(ip_state, ip_desired, std::next(i_it), i_end);
}

}

bool Tester::isCorrectlySolved(const MatrixSP& ip_initial, const MatrixSP& ip_desired, const Solution& i_solution)
{
	auto p_input = ip_initial;
	return isCorrectlySolvedImpl(p_input, ip_desired, i_solution.cbegin(), i_solution.cend());
}
