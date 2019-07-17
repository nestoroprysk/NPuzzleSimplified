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
