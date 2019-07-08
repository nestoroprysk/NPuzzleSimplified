#pragma once

#include "Types.hpp"

class ContainerCreator
{
public:
	ContainerCreator(ContainerType i_type);
	IContainerUP create() const;
private:
	const ContainerType m_type;
};
