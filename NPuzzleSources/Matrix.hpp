#pragma once

#include "Move.hpp"

#include <vector>
#include <ostream>

class Matrix
{
public:
    Matrix(std::vector<std::size_t> i_args);
    std::size_t operator[](const std::size_t i) const;
    std::size_t getMovingPointIndex() const;
    void move(Move i_move);
    std::size_t size() const;
    std::size_t sizeSquared() const;
private:
    std::vector<std::size_t> m_data;
    std::size_t m_moving_point_index = 0;
    std::size_t m_size = 0;
};

inline std::ostream& operator<<(std::ostream& o_s, const Matrix& i_m)
{
    for (std::size_t i = 0; i < i_m.sizeSquared(); ++i){
        if (i == 0)
            ;
        else if (i % i_m.size() == 0)
            o_s << std::endl;
        else
            o_s << ' ';
        o_s << i_m[i];
    }
    return o_s;
}
