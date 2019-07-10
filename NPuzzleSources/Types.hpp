#pragma once

#include <vector>
#include <list>

struct State;
class IContainer;
class IMatrix;

enum class Move { Left, Right, Up, Down };
enum class ContainerType { Set, Queue };

using Solution = std::list<Move>;
using RowMatrix = std::vector<std::size_t>;
using MatrixSP = std::shared_ptr<IMatrix>;
using StateSP = std::shared_ptr<State>;
using MaybeSolution = std::unique_ptr<Solution>;
using IContainerUP = std::unique_ptr<IContainer>;
using HeuristicFunction = std::function<std::size_t(const MatrixSP&)>;
using Comparator = std::function<bool(const State&, const State&)>;

struct Point
{
	std::size_t i = 0;
	std::size_t j = 0;
};
