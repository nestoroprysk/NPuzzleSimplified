#pragma once

#include "Matrix.hpp"

#include <vector>
#include <list>
#include <unordered_map>
#include <string>

struct State;

using Solution = std::list<Move>;
using MatrixSP = std::shared_ptr<Matrix>;
using StateSP = std::shared_ptr<State>;

using MaybeSolution = std::shared_ptr<Solution>;
using HeuristicFunction = std::function<std::size_t(const Matrix&, const std::size_t)>;

using ValueToPosition = std::unordered_map<char, std::size_t>;

struct Less{};
struct NotLess{};

class ArgcArgvError : public std::exception
{
public:
    ArgcArgvError(const std::string i_error) : m_error(i_error){}
    const char* what() const noexcept override{ return m_error.c_str(); }
private:
    const std::string m_error;
};
