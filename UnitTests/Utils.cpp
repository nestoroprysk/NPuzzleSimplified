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

TEST_CASE("<RenerateSnakeSolution><InvalidInput>")
{
    REQUIRE_THROWS(Utils::generateSnakeSolution(Utils::g_min_n - 1));
    REQUIRE_THROWS(Utils::generateSnakeSolution(Utils::g_max_n + 1));
}

TEST_CASE("<RenerateSnakeSolution><3>")
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

TEST_CASE("<RenerateSnakeSolution><4>")
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
