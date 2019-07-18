#include "catch.hpp"

#include <Parser.hpp>
#include <Matrix.hpp>
#include <Utils.hpp>

TEST_CASE("<Parser><Valid>")
{
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"3#End comment"},
        {"7 1 6"},
        {"5 0 4"},
        {"3 8 2 "},
        {"     "},
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_NOTHROW(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
    REQUIRE(Utils::eq(*p_matrix, Matrix{{
        7, 1, 6,
        5, 0, 4,
        3, 8, 2
    }}));
}

TEST_CASE("<Parser><Invalid><Empty>")
{
    const auto content = std::vector<std::string>{};
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_THROWS(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
}

TEST_CASE("<Parser><Invalid><NotEnoughNumbers>")
{
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"3#End comment"},
        {"7 1 6"},
        {"5 0 4"},
        {"3 8 "},
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_THROWS(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
}

TEST_CASE("<Parser><Invalid><TooManyNumbers>")
{
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"3#End comment"},
        {"7 1 6"},
        {"5 0 4"},
        {"3 8 2 10"},
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_THROWS(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
}

TEST_CASE("<Parser><Invalid><InvalidNumbers>")
{
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"3#End comment"},
        {"7 1 6"},
        {"5 0 4"},
        {"3 8 123"},
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_THROWS(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
}

TEST_CASE("<Parser><Invalid><InvalidN>")
{
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"999999999#End comment"},
        {"7 1 6"},
        {"5 0 4"},
        {"3 8 2"},
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_THROWS(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
}

TEST_CASE("<Parser><Invalid><UnrecognizedSymbol>")
{
    const auto content = std::vector<std::string>{
        {"# This puzzle is solvable"},
        {"3#End comment"},
        {"7 1 6"},
        {"5 0 4"},
        {"3 8 2 "},
        {"  -   "},
    };
    auto p_matrix = std::unique_ptr<Matrix>();
    REQUIRE_THROWS(p_matrix = std::make_unique<Matrix>(Parser::parseContent(content)));
}
