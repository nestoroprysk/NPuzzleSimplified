#pragma once

#include <vector>
#include <list>
#include <array>

template <std::size_t N>
struct State;

template <std::size_t N>
class IContainer;

enum class Move {
    Left, Right, Up, Down
};
enum class ContainerType {
    Set, Queue
};

using Solution = std::list<Move>;

template <std::size_t N>
using Matrix = std::array<char, N * N>;

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
