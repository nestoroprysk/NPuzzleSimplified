#include "ContainerCreator.hpp"
#include "Set.hpp"
#include "Queue.hpp"

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
		case ContainerType::Queue:
			return std::make_unique<Queue>();
		default:
			throw "Unimplemented";
	};
}
