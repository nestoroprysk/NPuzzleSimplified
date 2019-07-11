#include "ContainerCreator.hpp"
#include "Set.hpp"
#include "Utils.hpp"

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
        default:
            throw "Unimplemented";
    };
}


EXPLICITLY_INSTANTIATE_CLASS(ContainerCreator);
