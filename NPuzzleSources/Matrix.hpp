#pragma once

#include "Move.hpp"

#include <string>

class Matrix
{
public:
    Matrix(std::string i_args);
    std::size_t operator[](const std::size_t i) const;
    std::size_t getMovingPointIndex() const;
    void move(Move i_move);
    const std::string& data() const;
    std::size_t size() const;
    std::size_t sizeSquared() const;
private:
    std::string m_data;
    std::size_t m_moving_point_index = 0;
    std::size_t m_size = 0;
};
