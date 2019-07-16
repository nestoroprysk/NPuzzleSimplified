#include "catch.hpp"

#include <Solver.hpp>
#include <HeuristicFunctions.hpp>
#include <Set.hpp>
#include <Queue.hpp>
#include <Tester.hpp>
#include <Printer.hpp>

#include <iostream>
#include <deque>
#include <set>

namespace {

template <typename Container>
void test(const SolverConfiguration& i_config, const Matrix& i_input)
{
	using namespace Utils;
	const auto solver = Solver<Container>(i_config);
	auto result_ptr = std::unique_ptr<Result<Container>>();
	REQUIRE_NOTHROW(result_ptr = std::make_unique<Result<Container>>(solver.solve(i_input)));
	REQUIRE(result_ptr);
	Printer<Container>::printShort(std::cout, *result_ptr); std::cout << std::endl;
	REQUIRE(result_ptr->m_opt_solution);
	REQUIRE(Tester::isCorrectlySolved(i_input, i_config.m_desired_solution, *result_ptr->m_opt_solution));
}

}

TEST_CASE("<3x3><Set><Manhattan><h=1><g=1>")
{
	const auto desired_solution = Matrix{{{
		1, 2, 3,
		8, 0, 4,
		7, 6, 5
	}}};
	const auto heuristic_function = Manhattan(desired_solution);
	const auto h = [&heuristic_function](const auto& i_matrix, const std::size_t i)
			{ return heuristic_function(i_matrix, i); };
	const auto heuristic_function_weight = double(1);
	const auto distance_weight = double(1);
	const auto configuration = SolverConfiguration{"Test 0", desired_solution, h,
		heuristic_function.getName(), heuristic_function_weight, distance_weight};
	const auto input = Matrix{{{
		5, 2, 4,
		6, 0, 1,
		8, 3, 7
	}}};
	test<Set>(configuration, input);
}

TEST_CASE("<3x3><QueueOnVector><Manhattan><h=1><g=1>")
{
	const auto desired_solution = Matrix{{{
		1, 2, 3,
		8, 0, 4,
		7, 6, 5
	}}};
	const auto heuristic_function = Manhattan(desired_solution);
	const auto h = [&heuristic_function](const auto& i_matrix, const std::size_t i)
			{ return heuristic_function(i_matrix, i); };
	const auto heuristic_function_weight = double(1);
	const auto distance_weight = double(1);
	const auto configuration = SolverConfiguration{"Test 0", desired_solution, h,
		heuristic_function.getName(), heuristic_function_weight, distance_weight};
	const auto input = Matrix{{{
		5, 2, 4,
		6, 0, 1,
		8, 3, 7
	}}};
	test<Queue<std::vector<State>>>(configuration, input);
}

TEST_CASE("<3x3><QueueOnDeque><CountCorrectPositions><h=1><g=1>")
{
	const auto desired_solution = Matrix{{{
		1, 2, 3,
		8, 0, 4,
		7, 6, 5
	}}};
	const auto heuristic_function = CountCorrectPositions(desired_solution);
	const auto h = [&heuristic_function](const auto& i_matrix, const std::size_t i)
			{ return heuristic_function(i_matrix, i); };
	const auto heuristic_function_weight = double(1);
	const auto distance_weight = double(1);
	const auto configuration = SolverConfiguration{"Test 0", desired_solution, h,
		heuristic_function.getName(), heuristic_function_weight, distance_weight};
	const auto input = Matrix{{{
		5, 2, 4,
		6, 0, 1,
		8, 3, 7
	}}};
	test<Queue<std::deque<State>>>(configuration, input);
}
