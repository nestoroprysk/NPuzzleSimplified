#pragma once

#include "Utils.hpp"
#include "Matrix.hpp"

#include <unordered_map>
#include <fstream>

class Runner
{
public:
    Runner(const int argc, const char** argv);
    ~Runner();
    void run();
    bool hasSomethingToRun() const;
public:
    class ConfigurationError : public std::exception{
    public:
        ConfigurationError(const std::string i_error) : m_error(i_error){}
        const char* what() const noexcept override{ return m_error.c_str(); }
    private:
        const std::string m_error;
    };
private:
    void defineNumberOfRuns();
    void defineTimeLimit();
    void defineRandomMapSize();
    void defineInputProvider();
    void defineDesiredSolution();
    void defineHeuristicFunctionWeight();
    void defineDistanceWeight();
    void defineHeuristicFunction();
    void defineRunner();
    void defineOutputFile();
private:
    std::unordered_map<std::string, std::string> m_tag_to_value;
    std::size_t m_number_of_runs = Utils::g_default_number_of_runs;
    std::size_t m_time_limit = Utils::g_default_time_limit;
    std::size_t m_random_map_size = Utils::g_default_random_map_size;
    std::function<Matrix()> m_input_provider;
    std::unique_ptr<Matrix> mp_desired_solution;
    double m_heuristic_function_weight = Utils::g_default_weight;
    double m_distance_weight = Utils::g_default_weight;
    std::function<std::size_t(const Matrix& i_matrix, const std::size_t i)> m_heuristic_function
        = [](auto, auto)->std::size_t{throw std::logic_error("m_heuristic_function(), uninitialized");};
    std::string m_heuristic_function_name;
    std::function<void()> m_runner =
        []{throw std::logic_error("m_runner(), uninitialized");};
    std::unique_ptr<std::ofstream> m_opt_output_file;
    std::streambuf* m_opt_saved_stream = nullptr;
};
