#pragma once

#include "Types.hpp"

#include <array>

class IMatrix
{
public:
    virtual MatrixSP clone() const = 0;
	virtual std::size_t size() const = 0;
	virtual char& at(const std::size_t i, const std::size_t j) = 0;
	virtual ~IMatrix(){}
};

template <std::size_t N>
class MatrixBase : public IMatrix
{
public:
	template <typename... Args>
	MatrixBase(Args... i_args);
	MatrixBase(std::array<char, N * N> i_data);
    virtual MatrixSP clone() const override;
	virtual std::size_t size() const override;
	virtual char& at(const std::size_t, const std::size_t) override;
private:
	std::array<char, N * N> m_data;
};

template <std::size_t N>
template <typename... Args>
MatrixBase<N>::MatrixBase(Args... i_args)
	: m_data{static_cast<char>(i_args)...}
{
	static_assert(sizeof...(i_args) == N * N);
}

template <std::size_t N>
MatrixBase<N>::MatrixBase(std::array<char, N * N> i_data)
    : m_data(i_data)
{
}

template <std::size_t N>
MatrixSP MatrixBase<N>::clone() const
{
    return std::make_shared<MatrixBase<N>>(m_data);
}

template <std::size_t N>
std::size_t MatrixBase<N>::size() const
{
	return N;
}

template <std::size_t N>
char& MatrixBase<N>::at(const std::size_t i, const std::size_t j)
{
	return m_data.at(i * N + j);
}

using Matrix3x3 = MatrixBase<3>;
using Matrix4x4 = MatrixBase<4>;
using Matrix5x5 = MatrixBase<5>;
