#pragma once

#include "Types.hpp"

namespace Heuristic {

std::size_t manhattan(const MatrixSP& ip_matrix, const MatrixSP& ip_solution);
std::size_t inversions(const MatrixSP& ip_matrix, const RowMatrix& i_solution);

}
