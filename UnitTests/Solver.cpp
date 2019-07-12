#include "catch.hpp"

#include <Types.hpp>
#include <Solver.hpp>
#include <ContainerCreator.hpp>
#include <HeuristicFunctions.hpp>
#include <Utils.hpp>
#include <Tester.hpp>

TEST_CASE("Basic 3x3 Solver Test")
{
	static constexpr auto n = 3;
	const auto desiredSolution = Matrix<n>{
		1, 2, 3,
		8, 0, 4,
		7, 6, 5
	};
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic<n>::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator<n>(ContainerType::Set);
	const auto solver = Solver<n>(desiredSolution, heuristicFunction, containerCreator);
	const auto solvableTest = Matrix<n>{
		5, 2, 4,
		6, 0, 1,
		8, 3, 7
	};
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester<n>::isCorrectlySolved(solvableTest, desiredSolution, *opt_result));
}

TEST_CASE("Basic 5x5 Solver Test I Set")
{
	static constexpr auto n = 5;
	const auto desiredSolution = Matrix<n>{
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	};
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic<n>::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator<n>(ContainerType::Set);
	const auto solver = Solver<n>(desiredSolution, heuristicFunction, containerCreator);
	const auto solvableTest = Matrix<n>{
		 4,  12, 21,  6,  3,
		 7,   8, 13,  1, 16,
		 24, 20, 17,  2,  0,
		 9,  23, 19, 18, 10,
		 22,  5, 11, 14, 15
	};
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester<n>::isCorrectlySolved(solvableTest, desiredSolution, *opt_result));
}

TEST_CASE("Basic 5x5 Solver Test II Set")
{
	static constexpr auto n = 5;
	const auto desiredSolution = Matrix<n>{
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	};
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic<n>::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator<n>(ContainerType::Set);
	const auto solver = Solver<n>(desiredSolution, heuristicFunction, containerCreator);
	const auto solvableTest = Matrix<n>{
		 8, 23,  0, 14, 18,
		 7, 16, 17, 15, 22,
		 1,  2, 13,  4, 12,
		10,  6, 19,  9, 21,
		20,  3,  5, 24, 11
	};
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester<n>::isCorrectlySolved(solvableTest, desiredSolution, *opt_result));
}

TEST_CASE("Basic 5x5 Solver Test III Set")
{
	static constexpr auto n = 5;
	const auto desiredSolution = Matrix<n>{
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	};
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic<n>::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator<n>(ContainerType::Set);
	const auto solver = Solver<n>(desiredSolution, heuristicFunction, containerCreator);
	const auto solvableTest = Matrix<n>{
		 5,  7, 20,  8,  2,
		11, 19, 23, 17, 24,
		16, 15, 18, 13, 22,
		21,  3,  4,  9, 10,
		14,  6,  0,  1, 12
	};
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester<n>::isCorrectlySolved(solvableTest, desiredSolution, *opt_result));
}

TEST_CASE("Basic 5x5 Solver Test I QueueOnVector")
{
	static constexpr auto n = 5;
	const auto desiredSolution = Matrix<n>{
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	};
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic<n>::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator<n>(ContainerType::QueueOnVector);
	const auto solver = Solver<n>(desiredSolution, heuristicFunction, containerCreator);
	const auto solvableTest = Matrix<n>{
		 4,  12, 21,  6,  3,
		 7,   8, 13,  1, 16,
		 24, 20, 17,  2,  0,
		 9,  23, 19, 18, 10,
		 22,  5, 11, 14, 15
	};
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester<n>::isCorrectlySolved(solvableTest, desiredSolution, *opt_result));
}

TEST_CASE("Basic 5x5 Solver Test II QueueOnVector")
{
	static constexpr auto n = 5;
	const auto desiredSolution = Matrix<n>{
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	};
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic<n>::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator<n>(ContainerType::QueueOnVector);
	const auto solver = Solver<n>(desiredSolution, heuristicFunction, containerCreator);
	const auto solvableTest = Matrix<n>{
		 8, 23,  0, 14, 18,
		 7, 16, 17, 15, 22,
		 1,  2, 13,  4, 12,
		10,  6, 19,  9, 21,
		20,  3,  5, 24, 11
	};
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester<n>::isCorrectlySolved(solvableTest, desiredSolution, *opt_result));
}

TEST_CASE("Basic 5x5 Solver Test III QueueOnVector")
{
	static constexpr auto n = 5;
	const auto desiredSolution = Matrix<n>{
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	};
	const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic<n>::manhattan(i_matrix, desiredSolution); };
	const auto containerCreator = ContainerCreator<n>(ContainerType::QueueOnVector);
	const auto solver = Solver<n>(desiredSolution, heuristicFunction, containerCreator);
	const auto solvableTest = Matrix<n>{
		 5,  7, 20,  8,  2,
		11, 19, 23, 17, 24,
		16, 15, 18, 13, 22,
		21,  3,  4,  9, 10,
		14,  6,  0,  1, 12
	};
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(solvableTest));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester<n>::isCorrectlySolved(solvableTest, desiredSolution, *opt_result));
}
