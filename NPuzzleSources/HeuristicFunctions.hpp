#pragma once

#include "Types.hpp"

class Manhattan
{
public:
	Manhattan(const Matrix& i_solution);
	std::size_t operator()(const Matrix& i_matrix, const std::size_t i) const;
private:
	std::size_t distanceX(const Matrix& i_matrix, const std::size_t i) const;
	std::size_t distanceY(const Matrix& i_matrix, const std::size_t i) const;

private:
	ValueToPosition m_mapper;
};
