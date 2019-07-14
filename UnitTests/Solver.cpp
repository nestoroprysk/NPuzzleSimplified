#include "catch.hpp"

#include <Solver.hpp>
#include <HeuristicFunctions.hpp>
#include <Set.hpp>
#include <Queue.hpp>
#include <Tester.hpp>

#include <deque>

namespace {

template <std::size_t N, typename Container>
void test(const Matrix<N>& i_input, const Matrix<N>& i_result,
		const HeuristicFunction<N>& i_heuristic_function)
{
	const auto solver = Solver<N, Container>(i_result, i_heuristic_function);
	auto opt_result = MaybeSolution();
	REQUIRE_NOTHROW(opt_result = solver.solve(i_input));
	REQUIRE(opt_result);
	REQUIRE(opt_result->size());
	REQUIRE(Tester<N>::isCorrectlySolved(i_input, i_result, *opt_result));
}

}

TEST_CASE("<3x3><Set><Manhattan>")
{
	static constexpr auto N = 3;
	const auto input = Matrix<N>{{{
		5, 2, 4,
		6, 0, 1,
		8, 3, 7
	}}};
	const auto result = Matrix<N>{{{
		1, 2, 3,
		8, 0, 4,
		7, 6, 5
	}}};
	const auto h = [f = Heuristic<N>(result)](const auto& i_matrix)
			{ return f.manhattan(i_matrix); };
	test<N, Set<N>>(input, result, h);
}

TEST_CASE("<3x3><Set><Inversions>")
{
	static constexpr auto N = 3;
	const auto input = Matrix<N>{{{
		5, 2, 4,
		6, 0, 1,
		8, 3, 7
	}}};
	const auto result = Matrix<N>{{{
		1, 2, 3,
		8, 0, 4,
		7, 6, 5
	}}};
	const auto h = [f = Heuristic<N>(result)](const auto& i_matrix)
			{ return f.inversions(i_matrix); };
	test<N, Set<N>>(input, result, h);
}

TEST_CASE("<3x3><QueueOnVector><Manhattan>")
{
	static constexpr auto N = 3;
	const auto input = Matrix<N>{{{
		5, 2, 4,
		6, 0, 1,
		8, 3, 7
	}}};
	const auto result = Matrix<N>{{{
		1, 2, 3,
		8, 0, 4,
		7, 6, 5
	}}};
	const auto h = [f = Heuristic<N>(result)](const auto& i_matrix)
			{ return f.manhattan(i_matrix); };
	test<N, Queue<N, std::vector<State<N>>>>(input, result, h);
}

TEST_CASE("<5x5><Set><Manhattan>")
{
	static constexpr auto N = 5;
	const auto result = Matrix<N>{{{
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	}}};
	const auto input = Matrix<N>{{{
		 4,  12, 21,  6,  3,
		 7,   8, 13,  1, 16,
		 24, 20, 17,  2,  0,
		 9,  23, 19, 18, 10,
		 22,  5, 11, 14, 15
	}}};
	const auto h = [f = Heuristic<N>(result)](const auto& i_matrix)
			{ return f.manhattan(i_matrix); };
	test<N, Set<N>>(input, result, h);
}

TEST_CASE("<5x5><QueueOnVector><Manhattan>")
{
	static constexpr auto N = 5;
	const auto result = Matrix<N>{{{
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	}}};
	const auto input = Matrix<N>{{{
		 4,  12, 21,  6,  3,
		 7,   8, 13,  1, 16,
		 24, 20, 17,  2,  0,
		 9,  23, 19, 18, 10,
		 22,  5, 11, 14, 15
	}}};
	const auto h = [f = Heuristic<N>(result)](const auto& i_matrix)
			{ return f.manhattan(i_matrix); };
	test<N, Queue<N, std::vector<State<N>>>>(input, result, h);
}

TEST_CASE("<5x5><QueueOnDequeue><Manhattan>")
{
	static constexpr auto N = 5;
	const auto result = Matrix<N>{{{
		 1,   2,  3,  4,  5,
		 16, 17, 18, 19,  6,
		 15, 24,  0, 20,  7,
		 14, 23, 22, 21,  8,
		 13, 12, 11, 10,  9
	}}};
	const auto input = Matrix<N>{{{
		 4,  12, 21,  6,  3,
		 7,   8, 13,  1, 16,
		 24, 20, 17,  2,  0,
		 9,  23, 19, 18, 10,
		 22,  5, 11, 14, 15
	}}};
	const auto h = [f = Heuristic<N>(result)](const auto& i_matrix)
			{ return f.manhattan(i_matrix); };
	test<N, Queue<N, std::deque<State<N>>>>(input, result, h);
}
