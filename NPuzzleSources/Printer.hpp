#pragma once

#include "Utils.hpp"
#include "Result.hpp"

#include <ostream>

template <typename Container>
class Printer
{
public:
    static void printFull(std::ostream& o_stream, const Result<Container>& i_result);
    static void printShort(std::ostream& o_stream, const Result<Container>& i_result);
    static void printResult(std::ostream& o_stream, const Result<Container>& i_result);
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
    printShort(o_stream, i_result); o_stream << std::endl;
    o_stream << "[desired solution]" << std::endl;
    printMatrix(o_stream, i_result.m_config.m_desired_solution); o_stream << std::endl;
    o_stream << "[input]" << std::endl;
    printMatrix(o_stream, i_result.m_input); o_stream << std::endl;
    printSolutionDetails(o_stream, i_result);
}

template <typename Container>
void Printer<Container>::printShort(std::ostream& o_stream, const Result<Container>& i_result)
{
    o_stream << "<input>";
    printConfig(o_stream, i_result.m_config);
    printContainer(o_stream); o_stream << "<output>";
    o_stream << '[' << i_result.m_number_of_selected_states << " selected states]";
    o_stream << '[' << i_result.m_max_number_of_states_in_memory << " max states in memory]";
    o_stream << '[' << i_result.m_execution_time << " milliseconds]";
    printSolution(o_stream, i_result);
}

template <typename Container>
void Printer<Container>::printResult(std::ostream& o_stream, const Result<Container>& i_result)
{
    if (!i_result.m_opt_solution){
        o_stream << "[na]";
        return;
    }
    o_stream << (Utils::isCorrectlySolved(i_result.m_input, i_result.m_config.m_desired_solution,
                                                                    *i_result.m_opt_solution)
        ? "[ok]"
        : "[ko]");
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
    o_stream << '[' << i_config.m_name << ']';
    o_stream << '[' << i_config.m_heuristic_function_name << ']';
    o_stream << '[' << i_config.m_heuristic_function_weight << " h weight]";
    o_stream << '[' << i_config.m_distance_weight << " g weight]";
    o_stream << '[' << i_config.m_time_limit << " seconds time limit]";
}

template <typename Container>
void Printer<Container>::printMove(std::ostream& o_stream, Move i_move)
{
    switch (i_move){
        case Move::Up:
            o_stream << "[up]";
            break;
        case Move::Down:
            o_stream << "[down]";
            break;
        case Move::Left:
            o_stream << "[left]";
            break;
        case Move::Right:
            o_stream << "[right]";
            break;
        default: throw std::logic_error("<<(move), Invalid move");
    }
}

template <typename Container>
void Printer<Container>::printSolution(std::ostream& o_stream, const Result<Container>& i_result)
{
    if (i_result.m_time_limit_exceeded){
        o_stream << "[time limit exceeded]";
        return;
    }
    if (!i_result.m_opt_solution){
        o_stream << "[unsolvable]";
        return;
    }
    o_stream << '[' << i_result.m_opt_solution->size() << " moves]";
}

template <typename Container>
void Printer<Container>::printSolutionDetails(std::ostream& o_stream, const Result<Container>& i_result)
{
    if (i_result.m_time_limit_exceeded){
        o_stream << "[time limit exceeded]";
        return;
    }
    if (!i_result.m_opt_solution){
        o_stream << "[no solution details]";
        return;
    }
    o_stream << "[moves]";
    const auto& moves = *i_result.m_opt_solution;
    auto matrix = i_result.m_input;
    for (auto m : moves){
        matrix.move(m);
        printMove(o_stream, m); o_stream << std::endl;
        o_stream << matrix << std::endl;
    }
}


template <>
inline void Printer<Set>::printContainer(std::ostream& o_stream)
{
    o_stream << "[set]";
}

template <>
inline void Printer<Queue<std::vector<State>>>::printContainer(std::ostream& o_stream)
{
    o_stream << "[queue on vector]";
}

template <>
inline void Printer<Queue<std::deque<State>>>::printContainer(std::ostream& o_stream)
{
    o_stream << "[queue on deque]";
}
