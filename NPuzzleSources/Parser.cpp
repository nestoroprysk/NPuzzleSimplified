#include "Parser.hpp"
#include "Utils.hpp"

#include <fstream>
#include <sstream>
#include <cmath>

namespace {

static constexpr auto g_comment = '#';

std::vector<std::string> readContent(const std::string& i_file_name){
    auto file = std::ifstream(i_file_name);
    if (!file)
        throw Parser::ParseError("Cannot open the file [" + i_file_name + "]");
    std::vector<std::string> result;
    for (std::string line; std::getline(file, line);)
        result.emplace_back(std::move(line));
    return result;
}

bool isComment(const std::string i_line){
    if (i_line.empty())
        throw Parser::ParseError("Non empty line expected");
    return i_line[0] == g_comment;
}

std::vector<std::string> purifyLines(const std::vector<std::string>& i_lines){
    std::vector<std::string> result;
    for (const auto& line : i_lines){
        if (line.empty())
            continue;
        if (std::all_of(line.cbegin(), line.cend(),
            [](const auto i_ch){return std::isspace(i_ch);}))
                continue;
        if (isComment(line))
            continue;
        auto trimmedLine = line.substr(0, line.find(g_comment));
        if (!std::all_of(trimmedLine.cbegin(), trimmedLine.cend(),
                [](const auto i_ch){ return std::isdigit(i_ch) || std::isspace(i_ch);}))
            throw Parser::ParseError("Unrecognised symbol met in the line [" + line + ']');
        result.emplace_back(std::move(trimmedLine));
    }
    return result;
}

std::vector<std::size_t> extractNumbers(const std::vector<std::string>& i_pure_lines){
    std::vector<std::size_t> result;
    for (const auto& line : i_pure_lines){
        auto stream = std::stringstream(line);
        auto n = std::size_t(0);
        while (stream >> n)
            result.push_back(n);
    }
    return result;
}

std::string toString(const std::vector<std::size_t>& i_numbers){
    auto result = std::string();
    for (auto it = std::next(i_numbers.cbegin()); it != i_numbers.cend(); ++it)
        result += std::to_string(*it) + ' ';
    return result;
}

}

Matrix Parser::parseFile(const std::string& i_file_name)
{
    const auto lines = readContent(i_file_name);
    return parseContent(lines);
}

Matrix Parser::parseContent(const std::vector<std::string>& i_content)
{
    const auto pureLines = purifyLines(i_content);
    const auto numbers = extractNumbers(pureLines);
    validate(numbers);
    return std::vector<std::size_t>{ std::next(numbers.cbegin()), numbers.cend() };
}

void Parser::validate(const std::vector<std::size_t>& i_numbers){
    if (i_numbers.empty())
        throw Parser::ParseError("Failed to extract numbers");
    const auto n = i_numbers[0];
    if (n < Utils::g_min_n || n > Utils::g_max_n)
        throw Parser::ParseError("The provided N is " + std::to_string(n) +
            ", N should be in the range [" + std::to_string(Utils::g_min_n) +
                ", " + std::to_string(Utils::g_max_n) + ']');
    if (i_numbers.size() != n * n + 1)
        throw Parser::ParseError("Trying to parse matrix " +
            std::to_string(n) + '*' + std::to_string(n) + ", got " +
                std::to_string(i_numbers.size() - 1) + " numbers, expected " + std::to_string(n * n));
    auto expectedNumbers = std::vector<std::size_t>(n * n, 0);
    for (auto it = std::next(i_numbers.cbegin()); it != i_numbers.cend(); ++it){
        if (*it >= n * n)
            throw Parser::ParseError("Invalid number met [" + std::to_string(*it) + ']');
        ++expectedNumbers[*it];
    }
    if (!std::all_of(expectedNumbers.cbegin(), expectedNumbers.cend(),
            [](const auto i_nb){ return i_nb == 1; }))
        throw Parser::ParseError("Invalid numbers of the matrix: [ " + toString(i_numbers) + ']');
}
