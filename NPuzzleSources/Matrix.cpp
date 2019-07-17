#include "Matrix.hpp"

#include <cmath>

Matrix::Matrix(std::vector<std::size_t> i_args)
    : m_data(std::move(i_args))
    , m_moving_point_index(std::distance(m_data.cbegin(),
        std::find(m_data.cbegin(), m_data.cend(), 0)))
    , m_size(std::floor(std::sqrt(m_data.size())))
{
}

std::size_t Matrix::operator[](const std::size_t i) const
{
    return static_cast<std::size_t>(m_data[i]);
}

std::size_t Matrix::getMovingPointIndex() const
{
    return m_moving_point_index;
}

void Matrix::move(Move i_move)
{
    switch (i_move){
        case Move::Left:{
            std::swap(m_data[m_moving_point_index],
                m_data[m_moving_point_index - 1]);
            m_moving_point_index -= 1;
            break;
        }
        case Move::Right:{
            std::swap(m_data[m_moving_point_index],
                m_data[m_moving_point_index + 1]);
            m_moving_point_index += 1;
            break;
        }
        case Move::Up:{
            std::swap(m_data[m_moving_point_index],
                m_data[m_moving_point_index - size()]);
            m_moving_point_index -= size();
            break;
        }
        case Move::Down:{
            std::swap(m_data[m_moving_point_index],
                m_data[m_moving_point_index + size()]);
            m_moving_point_index += size();
            break;
        }
        default:
            throw std::logic_error("Invalid move type");
    }
}

std::size_t Matrix::size() const
{
    return m_size;
}

std::size_t Matrix::sizeSquared() const
{
    return m_size * m_size;
}
