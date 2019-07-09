#include <Types.hpp>
#include <Solver.hpp>
#include <ContainerCreator.hpp>
#include <HeuristicFunctions.hpp>
#include <Utils.hpp>
#include <Tester.hpp>

#include <iostream>

namespace {

const auto print = [](const auto& i_matrix){
	if (i_matrix.empty())
		std::cout << "No solution" << std::endl;
	for (const auto& row : i_matrix){
		std::cout << "< ";
		for (const auto n : row)
			std::cout << n << ' ';
		std::cout << ">" << std::endl;
	}
};

const auto check = [](const auto& i_solver, const auto& i_matrix, const auto& i_desired_solution, const auto i_solvable){
	try{
	const auto opt_result = i_solver.solve(i_matrix);
	if ((!opt_result && !i_solvable) || (opt_result && Tester::isCorrectlySolved(i_matrix, i_desired_solution, *opt_result)))
		std::cout << ":)" << std::endl;
	else
		std::cout << ":(" << std::endl;
	}
	catch (std::exception e){
		std::cout << e.what() << std::endl;
	}
	catch (const char* e){
		std::cout << e << std::endl;	
	}
};

}

int main()
{
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
		{
			const auto solvableTest = Matrix{
				{5, 2, 4},
				{6, 0, 1},
				{8, 3, 7}
			};
			check(solver, solvableTest, desiredSolution, true);
		}
		{
			const auto unsolvableTest = Matrix{
				{8, 2, 5},
				{6, 7, 1},
				{0, 4, 3}
			};
			check(solver, unsolvableTest, desiredSolution, false);
		}
	}
		{
		const auto desiredSolution = Matrix{
			{1, 2, 3},
			{8, 0, 4},
			{7, 6, 5}
		};
		const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic::manhattan(i_matrix, desiredSolution); };
		const auto containerCreator = ContainerCreator(ContainerType::Queue);
		const auto solver = Solver(desiredSolution, heuristicFunction, containerCreator);
		{
			const auto solvableTest = Matrix{
				{5, 2, 4},
				{6, 0, 1},
				{8, 3, 7}
			};
			check(solver, solvableTest, desiredSolution, true);
		}
		{
			const auto unsolvableTest = Matrix{
				{8, 2, 5},
				{6, 7, 1},
				{0, 4, 3}
			};
			check(solver, unsolvableTest, desiredSolution, false);
		}
	}
	{
		const auto desiredSolution = Matrix{
			{1, 2, 3},
			{8, 0, 4},
			{7, 6, 5}
		};
		const auto heuristicFunction =
			[&desiredSolution, row_solution = Utils::makeRow(desiredSolution)](const auto& i_matrix)
				{ return Heuristic::inversions(i_matrix, row_solution); };
		const auto containerCreator = ContainerCreator(ContainerType::Set);
		const auto solver = Solver(desiredSolution, heuristicFunction, containerCreator);
		{
			const auto solvableTest = Matrix{
				{5, 2, 4},
				{6, 0, 1},
				{8, 3, 7}
			};
			check(solver, solvableTest, desiredSolution, true);
		}
	}
	{
		const auto desiredSolution = Matrix{
			{1,  2,  3,  4,  5},
			{16, 17, 18, 19, 6},
			{15, 24, 0,  20, 7},
			{14, 23, 22, 21, 8},
			{13, 12, 11, 10, 9}
		};
		const auto heuristicFunction = [&desiredSolution](const auto& i_matrix)
			{ return Heuristic::manhattan(i_matrix, desiredSolution); };
		const auto containerCreator = ContainerCreator(ContainerType::Set);
		const auto solver = Solver(desiredSolution, heuristicFunction, containerCreator);
		{
			const auto solvableTest = Matrix{
				{19, 12,  5,  7,  9},
				{16, 14, 13,  6, 18},
				{0,  23,  1, 10,  8},
				{15, 24,  3, 20, 11},
				{22, 21, 17,  4,  2}
			};
			check(solver, solvableTest, desiredSolution, true);
		}
	}
}
