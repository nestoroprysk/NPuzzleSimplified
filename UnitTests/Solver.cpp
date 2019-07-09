#include "catch.hpp"

#include <Types.hpp>
#include <Solver.hpp>
#include <ContainerCreator.hpp>
#include <HeuristicFunctions.hpp>
#include <Utils.hpp>
#include <Tester.hpp>

TEST_CASE("Basic Solver Test")
{
	const auto desiredSolution = Matrix{
		{1, 2, 3},
		{8, 0, 4},
		{7, 6, 5}
	};
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator(ContainerType::Set);
	const auto solver = Solver(desiredSolution, heuristicFunction, containerCreator);
	const auto solvableTest = Matrix{
		{5, 2, 4},
		{6, 0, 1},
		{8, 3, 7}
	};
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
}
