#include "State.hpp"

State::State(const Matrix& i_matrix, const std::size_t i_heuristic_cost)
	: mp_data(std::make_shared<Matrix>(i_matrix))
	, m_heuristic_cost(i_heuristic_cost)
{
}
