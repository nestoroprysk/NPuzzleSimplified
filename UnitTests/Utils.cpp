#include "catch.hpp"

#include <Matrix.hpp>
#include <Utils.hpp>
#include <Parser.hpp>

namespace {

std::vector<std::size_t> makeNumberList(const Matrix& i_matrix){
    auto result = std::vector<std::size_t>();
    result.push_back(i_matrix.size());
    for (std::size_t i = 0; i < i_matrix.sizeSquared(); ++i)
        result.push_back(i_matrix[i]);
    return result;
}

}

TEST_CASE("<RandomMatrix>")
{
    static constexpr auto n = 10;
    auto p_matrix1 = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix1 = std::make_unique<Matrix>(Utils::generateRandomMap(n)));
    REQUIRE_NOTHROW(Parser::validate(makeNumberList(*p_matrix1)));
    auto p_matrix2 = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix1 = std::make_unique<Matrix>(Utils::generateRandomMap(n)));
    REQUIRE(p_matrix1 != p_matrix2);
}

TEST_CASE("<GenerateSnakeSolution><InvalidInput>")
{
    REQUIRE_THROWS(Utils::generateSnakeSolution(Utils::g_min_n - 1));
    REQUIRE_THROWS(Utils::generateSnakeSolution(Utils::g_max_n + 1));
}

TEST_CASE("<GenerateSnakeSolution><3>")
{
    static constexpr auto n = 3;
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE(Utils::eq(*p_matrix, Matrix{{
        1, 2, 3,
        8, 0, 4,
        7, 6, 5
    }}));
}

TEST_CASE("<GenerateSnakeSolution><4>")
{
    static constexpr auto n = 4;
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE(Utils::eq(*p_matrix, Matrix{{
        1,  2,  3,  4,
        12, 13, 14, 5,
        11, 0,  15, 6,
        10, 9,  8,  7
    }}));
}

TEST_CASE("<RenerateSnakeSolution><5>")
{
    static constexpr auto n = 5;
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE(Utils::eq(*p_matrix, Matrix{{
        1,  2,  3,  4,  5,
        16, 17, 18, 19, 6,
        15, 24, 0,  20, 7,
        14, 23, 22, 21, 8,
        13, 12, 11, 10, 9
    }}));
}

TEST_CASE("<RenerateSnakeSolution><6>")
{
    static constexpr auto n = 6;
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE(Utils::eq(*p_matrix, Matrix{{
        1,  2,  3,  4,  5,  6,
        20, 21, 22, 23, 24, 7,
        19, 32, 33, 34, 25, 8,
        18, 31, 0,  35, 26, 9,
        17, 30, 29, 28, 27, 10,
        16, 15, 14, 13, 12, 11
    }}));
}

TEST_CASE("<Solvable><3><Unsolvable>")
{
    static constexpr auto n = 3;
    const auto content = std::vector<std::string>{
        {"# This puzzle is unsolvable"},
        {"3"},
        {"8 2 1"},
        {"7 0 3"},
        {"5 6 4"}
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
    auto p_solution = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_solution = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE(!Utils::solvable(*p_matrix, *p_solution));
}

TEST_CASE("<Solvable><3><Solvable>")
{
    static constexpr auto n = 3;
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"3"},
        {"1 5 4"},
        {"3 7 6"},
        {"2 8 0"}
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
    auto p_solution = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_solution = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE(Utils::solvable(*p_matrix, *p_solution));
}

TEST_CASE("<Solvable><4><Unsolvable>")
{
    static constexpr auto n = 4;
    const auto content = std::vector<std::string>{
        {"# This puzzle is unsolvable"},
        {"4"},
        {"10  5 13  1"},
        {"14 15  8  6"},
        {" 7  9 12  0"},
        {" 4  3  2 11"}
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
    auto p_solution = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_solution = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE_NOTHROW(!Utils::solvable(*p_matrix, *p_solution));
    REQUIRE(!Utils::solvable(*p_matrix, *p_solution));
}

TEST_CASE("<Solvable><4><Solvable>")
{
    static constexpr auto n = 4;
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"4"},
        {"14 11 13  0"},
        {" 1 15  5  4"},
        {"12  7  2  6"},
        {" 8  3  9 10"},
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
    auto p_solution = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_solution = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE_NOTHROW(Utils::solvable(*p_matrix, *p_solution));
    REQUIRE(Utils::solvable(*p_matrix, *p_solution));
}

TEST_CASE("<Solvable><5><Unsolvable>")
{
    static constexpr auto n = 5;
    const auto content = std::vector<std::string>{
        {"# This puzzle is unsolvable"},
        {"5"},
        {"12 22 23 15  3"},
        {"13 17  4  0 18"},
        {" 8 14 20  9  7"},
        {"21  1 24  2 10"},
        {"19 16  5 11  6"}
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
    auto p_solution = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_solution = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE_NOTHROW(!Utils::solvable(*p_matrix, *p_solution));
    REQUIRE(!Utils::solvable(*p_matrix, *p_solution));
}

TEST_CASE("<Solvable><5><Solvable>")
{
    static constexpr auto n = 5;
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"5"},
        {"20  9 16 23 17"},
        {" 8 14  5 22 15"},
        {" 6 18 12 21 10"},
        {"11 19 13  0  4"},
        {" 7  3 24  2  1"}
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
    auto p_solution = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_solution = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE_NOTHROW(Utils::solvable(*p_matrix, *p_solution));
    REQUIRE(Utils::solvable(*p_matrix, *p_solution));
}

TEST_CASE("<Solvable><6><Solvable>")
{
    static constexpr auto n = 6;
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"6"},
        {"23 34 35 10  6 24"},
        {"25 32  1 26 11 22"},
        {"21 12 28  8 13  0"},
        {" 5  3 33  4 31 20"},
        {"19 29  9 15 14  7"},
        {"17  2 16 27 30 18"}
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
    auto p_solution = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_solution = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE_NOTHROW(Utils::solvable(*p_matrix, *p_solution));
    REQUIRE(Utils::solvable(*p_matrix, *p_solution));
}

TEST_CASE("<Solvable><6><Unolvable>")
{
    static constexpr auto n = 6;
    const auto content = std::vector<std::string>{
        {"# This puzzle is unsolvable"},
        {"6"},
        {"11  3  2 14 16 23"},
        {" 4 18 26  5 25 15"},
        {"33  9 17 27 30 13"},
        {" 0 12 21 34 19  7"},
        {"28 29 20 32  1  8"},
        {"31 24 35 22 10  6"}
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
    auto p_solution = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_solution = std::make_unique<Matrix>(Utils::generateSnakeSolution(n)));
    REQUIRE_NOTHROW(Utils::solvable(*p_matrix, *p_solution));
    REQUIRE(!Utils::solvable(*p_matrix, *p_solution));
}
