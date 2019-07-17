#pragma once

#include "Types.hpp"
#include <string>

class Manhattan
{
public:
    Manhattan(const Matrix& i_solution);
    std::size_t operator()(const Matrix& i_matrix, const std::size_t i) const;
    std::string getName() const;
private:
    std::size_t distanceX(const Matrix& i_matrix, const std::size_t i) const;
    std::size_t distanceY(const Matrix& i_matrix, const std::size_t i) const;

private:
    const ValueToPosition m_mapper;
};

class IsInCorrectPositions
{
public:
    IsInCorrectPositions(const Matrix& i_solution);
    std::size_t operator()(const Matrix& i_matrix, const std::size_t i) const;
    std::string getName() const;
private:
    const Matrix m_solution;
};

class IsNearCorrectPosition
{
public:
    IsNearCorrectPosition(const Matrix& i_solution);
    std::size_t operator()(const Matrix& i_matrix, const std::size_t i) const;
    std::string getName() const;
private:
    const Matrix m_solution;
};
