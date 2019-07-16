#pragma once

#include "Result.hpp"

#include <ostream>

template <typename Container>
class Printer
{
public:
	static void printFull(std::ostream& o_stream, const Result<Container>& i_result);
	static void printShort(std::ostream& o_stream, const Result<Container>& i_result);
private:
	Printer() = delete;
	static void printMatrix(std::ostream& o_stream, const Matrix& i_matrix);
	static void printConfig(std::ostream& o_stream, const SolverConfiguration& i_config);
	static void printMove(std::ostream& o_stream, Move i_move);
	static void printSolution(std::ostream& o_stream, const Result<Container>& i_result);
	static void printSolutionDetails(std::ostream& o_stream, const Result<Container>& i_result);
	static void printContainer(std::ostream& o_stream);
};

template <typename Container>
void Printer<Container>::printFull(std::ostream& o_stream, const Result<Container>& i_result)
{
	printShort(o_stream, i_result);
	printSolutionDetails(o_stream, i_result);
}

template <typename Container>
void Printer<Container>::printShort(std::ostream& o_stream, const Result<Container>& i_result)
{
	o_stream << "===Solver Configuration===" << std::endl;
	printConfig(o_stream, i_result.m_config); o_stream << std::endl;
	o_stream << "Container: "; printContainer(o_stream); o_stream << std::endl;
	o_stream << "===Input===" << std::endl;
	printMatrix(o_stream, i_result.m_input); o_stream << std::endl;
	o_stream << "===Results Collected===" << std::endl;
	o_stream << "Number of states selected: " << i_result.m_number_of_selected_states << std::endl;
	o_stream << "Max number of states in memory: " << i_result.m_max_number_of_states_in_memory << std::endl;
	o_stream << "Execution time: " << i_result.m_execution_time << " milliseconds" << std::endl;
	o_stream << "===Solution===" << std::endl;
	printSolution(o_stream, i_result);
}

template <typename Container>
void Printer<Container>::printMatrix(std::ostream& o_stream, const Matrix& i_matrix)
{
	for (std::size_t i = 0; i < i_matrix.sizeSquared(); ++i){
		if (i == 0)
			;
		else if (i % i_matrix.size() == 0)
			o_stream << std::endl;
		else
			o_stream << ' ';
		o_stream << i_matrix[i];
	}
}

template <typename Container>
void Printer<Container>::printConfig(std::ostream& o_stream, const SolverConfiguration& i_config)
{
	o_stream << "Test name: " << i_config.m_name << std::endl;
	o_stream << "Desired solution:" << std::endl;
	printMatrix(o_stream, i_config.m_desired_solution); o_stream << std::endl;
	// print heuristic
	o_stream << "Heuristic function weight: " << i_config.m_heuristic_function_weight << std::endl;
	o_stream << "Distance weight: " << i_config.m_distance_weight;
}

template <typename Container>
void Printer<Container>::printMove(std::ostream& o_stream, Move i_move)
{
	switch (i_move){
		case Move::Up:
			o_stream << "Up";
			break;
		case Move::Down:
			o_stream << "Down";
			break;
		case Move::Left:
			o_stream << "Left";
			break;
		case Move::Right:
			o_stream << "Right";
			break;
		default: throw std::logic_error("<<(move), Invalid move");
	}
}

template <typename Container>
void Printer<Container>::printSolution(std::ostream& o_stream, const Result<Container>& i_result)
{
	if (!i_result.m_opt_solution){
		o_stream << "The puzzle is unsolvable";
		return;
	}
	o_stream << "Number of moves: " << i_result.m_opt_solution->size();
}

template <typename Container>
void Printer<Container>::printSolutionDetails(std::ostream& o_stream, const Result<Container>& i_result)
{
	const auto& moves = *i_result.m_opt_solution;
	auto matrix = i_result.m_input;
	for (auto m : moves){
		matrix.move(m);
		o_stream << m << std::endl;
		o_stream << matrix << std::endl;
	}
}


template <>
inline void Printer<Set>::printContainer(std::ostream& o_stream)
{
	o_stream << "Set";
}

template <>
inline void Printer<Queue<std::vector<State>>>::printContainer(std::ostream& o_stream)
{
	o_stream << "queue on vector";
}

template <>
inline void Printer<Queue<std::deque<State>>>::printContainer(std::ostream& o_stream)
{
	o_stream << "queue on deque";
}
