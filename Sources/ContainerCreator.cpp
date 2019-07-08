#include "ContainerCreator.hpp"

#include "Set.hpp"

ContainerCreator::ContainerCreator(ContainerType i_type)
	: m_type(i_type)
{
}

IContainerUP ContainerCreator::create() const
{
	switch (m_type)
	{
		case ContainerType::Set:
			return std::make_unique<Set>();
		default:
			throw "Unimplemented";
	};
}
