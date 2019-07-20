#include "Runner.hpp"
#include "Parser.hpp"
#include "HeuristicFunctions.hpp"
#include "SolverConfiguration.hpp"
#include "Set.hpp"
#include "Queue.hpp"
#include "Result.hpp"
#include "Printer.hpp"
#include "Solver.hpp"

#include <set>
#include <fstream>
#include <vector>
#include <deque>
#include <iostream>

namespace {

const auto g_set_of_tags = std::set<std::string>{
    "-c", "-f", "-g", "-v", "-h", "-gc", "-hc", "-n", "-t", "-d"
};

std::unordered_map<std::string, std::string> parseArgcArgv(const int argc, const char** argv)
{
    auto result = std::unordered_map<std::string, std::string>();
    for (auto i = 1; i < argc; i += 2){
        if (g_set_of_tags.find(argv[i]) == g_set_of_tags.end())
            throw Runner::ConfigurationError("Unrecognised option [" + std::string(argv[i]) + ']');
        if (i == argc - 1)
            throw Runner::ConfigurationError("The option [" + std::string(argv[i]) + "] expects value");
        result[argv[i]] = argv[i + 1];
    }
    return result;
}

}

Runner::Runner(const int argc, const char** argv)
    : m_tag_to_value(parseArgcArgv(argc, argv))
{
    defineNumberOfRuns();
    defineTimeLimit();
    defineRandomMapSize();
    defineInputProvider();
    defineDesiredSolution();
    defineHeuristicFunctionWeight();
    defineDistanceWeight();
    defineHeuristicFunction();
    defineRunner();
}

void Runner::run()
{
    --m_number_of_runs;
    m_runner();
}

bool Runner::hasSomethingToRun() const
{
    return m_number_of_runs > 0;
}

void Runner::defineNumberOfRuns()
{
    static constexpr auto correspondingTag = "-n";
    if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end())
        return;
    try{
        m_number_of_runs = std::stoll(m_tag_to_value[correspondingTag]);
    }
    catch (const std::invalid_argument&){
        throw ConfigurationError("Invalid argument of the option -n [" +
            m_tag_to_value[correspondingTag] + ']');
    }
    catch (const std::out_of_range&){
        throw ConfigurationError("Invalid number for the option -n [" +
            m_tag_to_value[correspondingTag] + ']');
    }
}

void Runner::defineTimeLimit()
{
    static constexpr auto correspondingTag = "-t";
    if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end())
        return;
    try{
        m_time_limit = std::stoll(m_tag_to_value[correspondingTag]);
    }
    catch (const std::invalid_argument&){
        throw ConfigurationError("Invalid argument of the option -t [" +
            m_tag_to_value[correspondingTag] + ']');
    }
    catch (const std::out_of_range&){
        throw ConfigurationError("Invalid number for the option -t [" +
            m_tag_to_value[correspondingTag] + ']');
    }
}

void Runner::defineRandomMapSize()
{
    static constexpr auto correspondingTag = "-g";
    if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end())
        return;
    try{
        m_random_map_size = std::stoll(m_tag_to_value[correspondingTag]);
        if (m_random_map_size < Utils::g_min_n || m_random_map_size > Utils::g_max_n)
            throw ConfigurationError("The option -g expects numbers within the range [" +
                std::to_string(Utils::g_min_n) + ", " + std::to_string(Utils::g_max_n) + ']');
    }
    catch (const std::invalid_argument&){
        throw ConfigurationError("Invalid argument of the option -g [" +
            m_tag_to_value[correspondingTag] + ']');
    }
    catch (const std::out_of_range&){
        throw ConfigurationError("Invalid number for the option -g [" +
            m_tag_to_value[correspondingTag] + ']');
    }
}

void Runner::defineInputProvider()
{
    static constexpr auto correspondingTag = "-f";
    if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end()){
        m_input_provider = [this]{
            return Utils::generateRandomMap(m_random_map_size);
        };
        return;
    }
    m_input_provider = [matrix = Parser::parseFile(m_tag_to_value[correspondingTag])]{
        return matrix;
    };
}

void Runner::defineDesiredSolution()
{
    static constexpr auto correspondingTag = "-d";
    if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end()){
        mp_desired_solution = std::make_unique<Matrix>(
            Utils::generateSnakeSolution(m_random_map_size));
        return;
    }
    mp_desired_solution = std::make_unique<Matrix>(
        Parser::parseFile(m_tag_to_value[correspondingTag]));
}

void Runner::defineHeuristicFunctionWeight()
{
    static constexpr auto correspondingTag = "-hc";
    if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end())
        return;
    try{
        m_heuristic_function_weight = std::stod(m_tag_to_value[correspondingTag]);
        if (m_heuristic_function_weight < Utils::g_min_weight || m_random_map_size > Utils::g_max_weight)
            throw ConfigurationError("The option -hc expects numbers within the range [" +
                std::to_string(Utils::g_min_weight) + ", " + std::to_string(Utils::g_max_weight) + ']');
    }
    catch (const std::invalid_argument&){
        throw ConfigurationError("Invalid argument of the option -hc [" +
            m_tag_to_value[correspondingTag] + ']');
    }
    catch (const std::out_of_range&){
        throw ConfigurationError("Invalid number for the option -hc [" +
            m_tag_to_value[correspondingTag] + ']');
    }
}

void Runner::defineDistanceWeight()
{
    static constexpr auto correspondingTag = "-gc";
    if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end())
        return;
    try{
        m_distance_weight = std::stod(m_tag_to_value[correspondingTag]);
        if (m_distance_weight < Utils::g_min_weight || m_distance_weight > Utils::g_max_weight)
            throw ConfigurationError("The option -gc expects numbers within the range [" +
                std::to_string(Utils::g_min_weight) + ", " + std::to_string(Utils::g_max_weight) +
                    "], got " + std::to_string(m_distance_weight));
    }
    catch (const std::invalid_argument&){
        throw ConfigurationError("Invalid argument of the option -gc [" +
            m_tag_to_value[correspondingTag] + ']');
    }
    catch (const std::out_of_range&){
        throw ConfigurationError("Invalid number for the option -gc [" +
            m_tag_to_value[correspondingTag] + ']');
    }
}

void Runner::defineHeuristicFunction()
{
    static constexpr auto correspondingTag = "-h";
    if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end() ||
                    m_tag_to_value[correspondingTag] == "Manhattan"){
        m_heuristic_function = [h = Manhattan(*mp_desired_solution)]
            (const auto& i_matrix, const std::size_t i){ return h(i_matrix, i); };
        m_heuristic_function_name = Manhattan::getName();
        return;
    }
    if (m_tag_to_value[correspondingTag] == "InPos"){
        m_heuristic_function = [h = IsInCorrectPositions(*mp_desired_solution)]
            (const auto& i_matrix, const std::size_t i){ return h(i_matrix, i); };
        m_heuristic_function_name = IsInCorrectPositions::getName();
        return;
    }
    if (m_tag_to_value[correspondingTag] == "NearPos"){
        m_heuristic_function = [h = IsNearCorrectPosition(*mp_desired_solution)]
            (const auto& i_matrix, const std::size_t i){ return h(i_matrix, i); };
        m_heuristic_function_name = IsNearCorrectPosition::getName();
        return;
    }
}

namespace {

template <typename Container>
void print(std::unordered_map<std::string, std::string>& i_tag_to_value,
                std::ostream& o_output_stream,
                const Result<Container>& i_result)
{
    static constexpr auto correspondingTag = "-v";
    if (i_tag_to_value.find(correspondingTag) == i_tag_to_value.end() ||
            i_tag_to_value[correspondingTag] == "short"){
        Printer<Container>::printShort(o_output_stream, i_result); o_output_stream << std::endl;
        return;
    }
    if (i_tag_to_value[correspondingTag] == "long"){
        Printer<Container>::printFull(o_output_stream, i_result); o_output_stream << std::endl;
        return;
    }
    if (i_tag_to_value[correspondingTag] == "result"){
        Printer<Container>::printResult(o_output_stream, i_result); o_output_stream << std::endl;
        return;
    }
}

}

void Runner::defineRunner()
{
    m_runner = [this]{
        const auto configuration = SolverConfiguration{*mp_desired_solution,
            m_heuristic_function, m_heuristic_function_name,
                m_heuristic_function_weight, m_distance_weight,
                    Utils::generateTestName(), m_time_limit};
        static constexpr auto correspondingTag = "-c";
        if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end() ||
                m_tag_to_value[correspondingTag] == "Set"){
            const auto solver = Solver<Set>(configuration);
            const auto input = m_input_provider();
            const auto result = solver.solve(input);
            print<Set>(m_tag_to_value, std::cout, result);
            return;
        }
        if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end() ||
                m_tag_to_value[correspondingTag] == "QueueOnVector"){
            const auto solver = Solver<Queue<std::vector<State>>>(configuration);
            const auto input = m_input_provider();
            const auto result = solver.solve(input);
            print<Queue<std::vector<State>>>(m_tag_to_value, std::cout, result);
            return;
        }
        if (m_tag_to_value.find(correspondingTag) == m_tag_to_value.end() ||
                m_tag_to_value[correspondingTag] == "QueueOnDequeue"){
            const auto solver = Solver<Queue<std::deque<State>>>(configuration);
            const auto input = m_input_provider();
            const auto result = solver.solve(input);
            print<Queue<std::deque<State>>>(m_tag_to_value, std::cout, result);
            return;
        }
    };
}
