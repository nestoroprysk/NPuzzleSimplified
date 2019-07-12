#pragma once

#include "Move.hpp"

#include <array>

template <std::size_t N>
class Matrix
{
public:
	template <typename... Args>
	Matrix(Args... i_args);
	std::size_t operator[](const std::size_t i) const;
	std::size_t getMovingPointIndex() const;
	void move(Move i_move);
private:
	std::array<char, N * N> m_data;
	std::size_t m_moving_point_index;
};

template <std::size_t N>
template <typename... Args>
Matrix<N>::Matrix(Args... i_args)
	: m_data{static_cast<char>(i_args)...}
	, m_moving_point_index(std::distance(m_data.cbegin(),
		std::find(m_data.cbegin(), m_data.cend(), 0)))
{
	static_assert(sizeof...(i_args) == N * N);
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
				m_data[m_moving_point_index - N]);
			m_moving_point_index -= N;
			break;
		}
		case Move::Down:{
			std::swap(m_data[m_moving_point_index],
				m_data[m_moving_point_index + N]);
			m_moving_point_index += N;
			break;
		}
		default:
			throw std::logic_error("Invalid move type");
	}
}
