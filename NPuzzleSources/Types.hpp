#pragma once

#include "Matrix.hpp"

#include <vector>
#include <list>
#include <unordered_map>

struct State;
class IContainer;

using Solution = std::list<Move>;
using MatrixSP = std::shared_ptr<Matrix>;
using StateSP = std::shared_ptr<State>;

using MaybeSolution = std::unique_ptr<Solution>;
using IContainerUP = std::unique_ptr<IContainer>;
using HeuristicFunction = std::function<std::size_t(const Matrix&)>;

using ValueToPosition = std::unordered_map<char, std::size_t>;

struct Less{};
struct NotLess{};
