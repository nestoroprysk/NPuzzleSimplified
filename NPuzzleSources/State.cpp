#include "State.hpp"
#include "Utils.hpp"

template <std::size_t N>
State<N>::State(const MatrixSP<N>& ip_matrix, const std::size_t i_heuristic_cost)
	: mp_data(ip_matrix)
	, m_heuristic_cost(i_heuristic_cost)
{
}

EXPLICITLY_INSTANTIATE_STRUCT(State);
