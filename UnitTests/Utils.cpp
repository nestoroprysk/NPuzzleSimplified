#include "catch.hpp"

#include <Types.hpp>
#include <State.hpp>
#include <Utils.hpp>

TEST_CASE("State Copy Constructor")
{
	const auto m = Matrix{
		{1, 2, 3},
		{8, 0, 4},
		{7, 6, 5}
	};
	const auto cost = 0;
	auto a = State(m, cost);
	auto b = State(m, cost);
	auto c = State(m, cost);
	using namespace Utils;
	predecessor(a) = std::make_shared<State>(b);
	predecessor(b) = std::make_shared<State>(a);
	REQUIRE(predecessor(a));
	REQUIRE(predecessor(b));
	REQUIRE(predecessor(*predecessor(b)));
}
