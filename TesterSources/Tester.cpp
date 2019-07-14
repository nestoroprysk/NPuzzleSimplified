#include "Tester.hpp"

#include <Solver.hpp>
#include <Utils.hpp>

namespace {

using It = Solution::const_iterator;

template <std::size_t N>
bool isCorrectlySolvedImpl(const Matrix<N>& i_matrix, const Matrix<N>& i_desired, It const& i_it, It const& i_end)
{
	if (i_it == i_end)
		return Utils<N>::eq(i_matrix, i_desired);
	// TODO: make move cheaper
	return isCorrectlySolvedImpl<N>(Utils<N>::move(i_matrix, *i_it), i_desired, std::next(i_it), i_end);
}

}

template <std::size_t N>
bool Tester<N>::isCorrectlySolved(const Matrix<N>& i_initial, const Matrix<N>& i_desired, const Solution& i_solution)
{
	return isCorrectlySolvedImpl<N>(i_initial, i_desired, i_solution.cbegin(), i_solution.cend());
}

template struct Tester<3>;
template struct Tester<4>;
template struct Tester<5>;
