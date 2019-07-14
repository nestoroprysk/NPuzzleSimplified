#pragma once

#include "Move.hpp"

#include <string>

class Matrix
{
public:
	Matrix(std::string i_data);
	char operator[](const std::size_t i) const;
	std::size_t getMovingPointIndex() const;
	void move(Move i_move);
	std::size_t size() const;
	std::size_t sizeSquared() const;
	const std::string& data() const;
private:
	std::string m_data;
	std::size_t m_moving_point_index;
	std::size_t m_size;
};
