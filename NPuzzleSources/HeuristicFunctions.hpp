#pragma once

#include "Types.hpp"

namespace Heuristic {

std::size_t manhattan(const Matrix& i_matrix, const Matrix& i_solution);
std::size_t inversions(const Matrix& i_matrix, const RowMatrix& i_solution);

}
