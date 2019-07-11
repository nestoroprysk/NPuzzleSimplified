#pragma once

#include "Types.hpp"

template <std::size_t N>
class ContainerCreator
{
public:
	ContainerCreator(ContainerType i_type);
	IContainerUP<N> create() const;
private:
	const ContainerType m_type;
};
