#pragma once

#include "Move.hpp"

#include <string>
#include <cmath>

template <std::size_t N>
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
	std::size_t m_moving_point_index;
	std::size_t m_size;
};

template <std::size_t N>
Matrix<N>::Matrix(std::string i_args)
	: m_data(std::move(i_args))
	, m_moving_point_index(std::distance(m_data.cbegin(),
		std::find(m_data.cbegin(), m_data.cend(), 0)))
	, m_size(std::floor(std::sqrt(m_data.size())))
{
}

template <std::size_t N>
std::size_t Matrix<N>::operator[](const std::size_t i) const
{
	return m_data[i];
}

template <std::size_t N>
std::size_t Matrix<N>::getMovingPointIndex() const
{
	return m_moving_point_index;
}

template <std::size_t N>
void Matrix<N>::move(Move i_move)
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

template <std::size_t N>
const std::string&  Matrix<N>::data() const
{
	return m_data;
}

template <std::size_t N>
std::size_t Matrix<N>::size() const
{
	return m_size;
}

template <std::size_t N>
std::size_t Matrix<N>::sizeSquared() const
{
	return m_size * m_size;
}
