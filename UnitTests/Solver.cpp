#include "catch.hpp"

#include <Types.hpp>
#include <Solver.hpp>
#include <ContainerCreator.hpp>
#include <HeuristicFunctions.hpp>
#include <Utils.hpp>
#include <Matrix.hpp>
#include <Tester.hpp>

TEST_CASE("Basic 3x3 Solver Test")
{
	const MatrixSP desiredSolution = std::make_shared<Matrix3x3>(
		1, 2, 3,
		8, 0, 4,
		7, 6, 5
	);
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator(ContainerType::Set);
	const auto solver = Solver(desiredSolution, heuristicFunction, containerCreator);
	const MatrixSP solvableTest = std::make_shared<Matrix3x3>(
		5, 2, 4,
		6, 0, 1,
		8, 3, 7
	);
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester::isCorrectlySolved(solvableTest, desiredSolution, *opt_result));
}

TEST_CASE("Basic 5x5 Solver Test")
{
	const MatrixSP desiredSolution = std::make_shared<Matrix5x5>(
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	);
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator(ContainerType::Set);
	const auto solver = Solver(desiredSolution, heuristicFunction, containerCreator);
	const MatrixSP solvableTest = std::make_shared<Matrix5x5>(
		 4,  12, 21,  6,  3,
		 7,   8, 13,  1, 16,
		 24, 20, 17,  2,  0,
		 9,  23, 19, 18, 10,
		 22,  5, 11, 14, 15
	);
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester::isCorrectlySolved(solvableTest, desiredSolution, *opt_result));
}
