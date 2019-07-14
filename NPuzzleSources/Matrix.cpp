#include "Matrix.hpp"

#include <cmath>

Matrix::Matrix(std::string i_data)
	: m_data(std::move(i_data))
	, m_moving_point_index(std::distance(m_data.cbegin(),
		std::find(m_data.cbegin(), m_data.cend(), 0)))
	, m_size(std::floor(std::sqrt(m_data.size())))
{
}

char Matrix::operator[](const std::size_t i) const
{
	return m_data[i];
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
				m_data[m_moving_point_index - m_data.size()]);
			m_moving_point_index -= m_data.size();
			break;
		}
		case Move::Down:{
			std::swap(m_data[m_moving_point_index],
				m_data[m_moving_point_index + m_data.size()]);
			m_moving_point_index += m_data.size();
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

const std::string& Matrix::data() const
{
	return m_data;
}
