#pragma once

#include <vector>
#include <list>

struct State;
class IContainer;

enum class Move { Left, Right, Up, Down };
enum class ContainerType { Set };

using Matrix = std::vector<std::vector<std::size_t>>;
using HeuristicFunction = std::function<std::size_t(const Matrix&)>;
using Comparator = std::function<bool(const State&, const State&)>;
using Solution = std::list<Move>;
using RowMatrix = std::vector<std::size_t>;

struct Point
{
	std::size_t i = 0;
	std::size_t j = 0;
};

using MatrixSP = std::shared_ptr<Matrix>;
using StateSP = std::shared_ptr<State>;
using MaybeSolution = std::unique_ptr<Solution>;
using IContainerUP = std::unique_ptr<IContainer>;
