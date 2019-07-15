#include "catch.hpp"

#include <Solver.hpp>
#include <HeuristicFunctions.hpp>
#include <Set.hpp>
#include <Queue.hpp>
#include <Tester.hpp>

#include <deque>

namespace {

template <typename Container>
void test(const SolverConfiguration& i_config, const Matrix& i_input)
{
	const auto solver = Solver<Container>(i_config);
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(i_input));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester::isCorrectlySolved(i_input, i_config.m_desired_solution, *opt_result));
}

}

TEST_CASE("<3x3><Set><Manhattan>")
{
	const auto desired_solution = Matrix{{{
		1, 2, 3,
		8, 0, 4,
		7, 6, 5
	}}};
	const auto h = [f = Heuristic(desired_solution)](const auto& i_matrix)
			{ return f.manhattan(i_matrix); };
	const auto heuristic_function_weight = double(1);
	const auto distance_weight = double(0);
	const auto configuration = SolverConfiguration{desired_solution, h,
		heuristic_function_weight, distance_weight};
	const auto input = Matrix{{{
		5, 2, 4,
		6, 0, 1,
		8, 3, 7
	}}};
	test<Set>(configuration, input);
}
