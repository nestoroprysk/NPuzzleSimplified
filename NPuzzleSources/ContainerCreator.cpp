#include "ContainerCreator.hpp"
#include "Set.hpp"
#include "Utils.hpp"
#include "Queue.hpp"

template <std::size_t N>
ContainerCreator<N>::ContainerCreator(ContainerType i_type)
		: m_type(i_type)
{
}

template <std::size_t N>
IContainerUP<N> ContainerCreator<N>::create() const
{
	switch (m_type)
	{
		case ContainerType::Set:
			return std::make_unique<Set<N>>();
		case ContainerType::QueueOnVector:
			return std::make_unique<Queue<N, std::vector<State<N>>>>();
		default:
			throw "Unimplemented";
	};
}


EXPLICITLY_INSTANTIATE_CLASS(ContainerCreator);
