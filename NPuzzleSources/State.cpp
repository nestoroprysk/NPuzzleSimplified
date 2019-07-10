#include "State.hpp"
#include "Matrix.hpp"

State::State(const MatrixSP& ip_matrix, const std::size_t i_heuristic_cost)
	: mp_data(ip_matrix)
	, m_heuristic_cost(i_heuristic_cost)
{
}
