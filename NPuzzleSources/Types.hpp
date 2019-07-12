#pragma once

#include "Matrix.hpp"

#include <vector>
#include <list>
#include <unordered_map>

template <std::size_t N>
struct State;

template <std::size_t N>
class IContainer;

using Solution = std::list<Move>;

template <std::size_t N>
using MatrixSP = std::shared_ptr<Matrix<N>>;

template <std::size_t N>
using StateSP = std::shared_ptr<State<N>>;

using MaybeSolution = std::unique_ptr<Solution>;

template <std::size_t N>
using IContainerUP = std::unique_ptr<IContainer<N>>;

template <std::size_t N>
using HeuristicFunction = std::function<std::size_t(const Matrix<N> &)>;

template <std::size_t N>
using Comparator = std::function<bool(const State<N> &, const State<N> &)>;

using ValueToPosition = std::unordered_map<char, std::size_t>;

struct Less{};
struct Greater{};
struct LessOrEqual{};
struct GreaterOrEqual{};
