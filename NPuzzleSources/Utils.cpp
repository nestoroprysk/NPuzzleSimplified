#include "Utils.hpp"
#include "State.hpp"
#include "SolverConfiguration.hpp"

#include <unordered_set>
#include <deque>
#include <random>
#include <chrono>

template <typename Container>
class Queue;

class Set;

auto Utils::possibleMoves(const Matrix& i_matrix) -> std::vector<Move>
{
    auto result = std::vector<Move>();
    const auto movingPointIndex = i_matrix.getMovingPointIndex();
    if (movingPointIndex % i_matrix.size() != 0)
        result.push_back(Move::Left);
    if (movingPointIndex % i_matrix.size() != i_matrix.size() - 1)
        result.push_back(Move::Right);
    if (movingPointIndex / i_matrix.size() != 0)
        result.push_back(Move::Up);
    if (movingPointIndex / i_matrix.size() != i_matrix.size() - 1)
        result.push_back(Move::Down);
    return result;
}

MatrixSP Utils::move(const MatrixSP& ip_matrix, Move i_move)
{
    auto p_result = std::make_shared<Matrix>(*ip_matrix);
    p_result->move(i_move);
    return p_result;
}

Matrix Utils::move(const Matrix& i_matrix, Move i_move)
{
    auto result = i_matrix;
    result.move(i_move);
    return result;
}

Move Utils::inferMove(Matrix const& i_from, Matrix const& i_to)
{
    auto& matrix = const_cast<Matrix&>(i_from);
    for (auto const m : Utils::possibleMoves(i_from)) {
        const auto reverseMove = oppositeMove(m);
        matrix.move(m);
        if (eq(matrix, i_to)){
            matrix.move(reverseMove);
            return m;
        }
        matrix.move(reverseMove);
    }
    throw std::logic_error("Impossible to reach the state in a single move");
}

bool Utils::eq(const Matrix& i_lhs, const Matrix& i_rhs)
{
    for (std::size_t i = 0; i < i_lhs.sizeSquared(); ++i)
        if (i_lhs[i] != i_rhs[i])
            return false;
    return true;
}

bool Utils::cmp(const Matrix& i_lhs, const Matrix& i_rhs)
{
    for (std::size_t i = 0; i < i_lhs.sizeSquared(); ++i)
        if (i_lhs[i] != i_rhs[i])
            return i_lhs[i] < i_rhs[i];
    return false;
}

// the formula is taken from https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
bool Utils::solvable(const Matrix& i_matrix, const Matrix& i_solution)
{
    const auto gridWidthOdd = i_matrix.size() % 2 != 0;
    const auto inversionsEven = countInversions(i_matrix, map(i_solution)) % 2 == 0;
    if (gridWidthOdd && inversionsEven)
        return true;
    const auto blankRow = i_matrix.getMovingPointIndex() / i_matrix.size();
    const auto blankIndexInSolution = i_solution.getMovingPointIndex();
    const auto blankRowInSolution = blankIndexInSolution / i_solution.size();
    const auto blankOnOddRowFromButtom = (i_matrix.size() - 1 - blankRow + blankRowInSolution) % 2 != 0;
    return !gridWidthOdd && blankOnOddRowFromButtom == inversionsEven;
}

std::size_t Utils::countInversions(const Matrix& i_matrix, const ValueToPosition& i_mapper)
{
    auto result = 0;
    for (std::size_t i = 0; i < i_matrix.sizeSquared() - 1; ++i)
        for (std::size_t j = i + 1; j < i_matrix.sizeSquared(); ++j)
            if (isInverted(i_mapper, i_matrix[i], i_matrix[j]))
                ++result;
    return result;
}

bool Utils::eq(const State& i_lhs, const State& i_rhs)
{
    return i_lhs.m_heuristic_cost == i_rhs.m_heuristic_cost
        && Utils::eq(Utils::data(i_lhs), Utils::data(i_rhs));
}

auto Utils::data(const State& i_state) -> const Matrix&
{
    return *i_state.mp_data;
}

std::vector<State> Utils::expand(const State& i_state, const HeuristicFunction& i_heuristic_function)
{
    const auto ms = possibleMoves(data(i_state));
    auto result = std::vector<State>();
    const auto& matrix = data(i_state);
    const auto heuristicCost = i_state.m_heuristic_cost;
    for (const auto m : ms){
        auto p_matrix = move(i_state.mp_data, m);
        const auto cost = updateCost(matrix, *p_matrix, i_heuristic_function, heuristicCost);
        result.emplace_back(p_matrix, cost);
    }
    return result;
}

const std::size_t& Utils::h(State& i_state)
{
    return i_state.m_heuristic_cost;
}

std::size_t& Utils::g(State& i_state)
{
    return i_state.m_distance;
}

const StateSP& Utils::predecessor(const State& i_state)
{
    return i_state.mp_predecessor;
}

StateSP& Utils::predecessor(State& i_state)
{
    return i_state.mp_predecessor;
}

std::list<Move> Utils::collectMoves(const State& i_state)
{
    return collectMovesImpl(i_state, predecessor(i_state));
}

bool Utils::isInverted(const ValueToPosition& i_mapper, const std::size_t l, const std::size_t r)
{
    if (l == 0 || r == 0)
        return false;
    return i_mapper.at(l) > i_mapper.at(r);
}

std::list<Move> Utils::collectMovesImpl(const State& i_state,
                                 const StateSP& i_opt_predecessor,
                                 std::list<Move> o_result)
{
    if (i_opt_predecessor)
    {
        o_result.push_front(Utils::inferMove(Utils::data(*i_opt_predecessor), Utils::data(i_state)));
        return collectMovesImpl(*i_opt_predecessor, Utils::predecessor(*i_opt_predecessor), std::move(o_result));
    }
    return o_result;
}

ValueToPosition Utils::map(const Matrix& i_solution)
{
    ValueToPosition result;
    for (std::size_t i = 0; i < i_solution.sizeSquared(); ++i)
        result[i_solution[i]] = i;
    return result;
}

std::size_t Utils::accumulateHeuristicCost(const Matrix& i_matrix, const HeuristicFunction& i_h)
{
    auto result = std::size_t(0);
    for (std::size_t i = 0; i < i_matrix.sizeSquared(); ++i)
        result += i_h(i_matrix, i);
    return result;
}

std::size_t Utils::updateCost(const Matrix& i_old, const Matrix& i_new,
        const HeuristicFunction& i_heuristic_function, const std::size_t i_old_cost)
{
    const auto oldCost = i_old_cost;
    const auto oldMovingPointIndex = i_old.getMovingPointIndex();
    const auto newMovingPointIndex = i_new.getMovingPointIndex();
    const auto oldCostA = i_heuristic_function(i_old, oldMovingPointIndex);
    const auto oldCostB = i_heuristic_function(i_old, newMovingPointIndex);
    const auto newCostA = i_heuristic_function(i_new, oldMovingPointIndex);
    const auto newCostB = i_heuristic_function(i_new, newMovingPointIndex);
    return oldCost - oldCostA + newCostA - oldCostB + newCostB;
}

Move Utils::oppositeMove(Move i_move)
{
    switch (i_move){
        case Move::Left: return Move::Right;
        case Move::Right: return Move::Left;
        case Move::Up: return Move::Down;
        case Move::Down: return Move::Up;
        default: throw std::logic_error("oppositeMove(), invalid move type");
    }
}

namespace {

using It = Solution::const_iterator;

bool isCorrectlySolvedImpl(Matrix i_matrix, const Matrix& i_desired, It const& i_it, It const& i_end)
{
    if (i_it == i_end)
        return Utils::eq(i_matrix, i_desired);
    i_matrix.move(*i_it);
    return isCorrectlySolvedImpl(std::move(i_matrix), i_desired, std::next(i_it), i_end);
}

}

bool Utils::isCorrectlySolved(Matrix i_initial, const Matrix& i_desired, const Solution& i_solution)
{
    return isCorrectlySolvedImpl(std::move(i_initial), i_desired, i_solution.cbegin(), i_solution.cend());
}

namespace {

class SnakeIterator
{
public:
    SnakeIterator(const std::size_t i_n)
        : m_data(i_n, std::vector<bool>(i_n, false)){}
    std::size_t operator*() const{return m_val;}
    void operator++(){
        m_data[m_at.i][m_at.j] = true;
        ++m_val;
        move();
    }
    std::size_t at() const{
        return m_at.i * m_data.size() + m_at.j;
    }
private:
    enum class Direction { Right, Down, Left, Up };
    static Direction getNext(const Direction i_direction){
        switch (i_direction){
            case Direction::Right: return Direction::Down;
            case Direction::Down: return Direction::Left;
            case Direction::Left: return Direction::Up;
            case Direction::Up: return Direction::Right;
            default: throw std::logic_error("getNext(), invalid direction");
        };
    }
    void move(){
        const auto ms = possibleMoves();
        if (ms.empty())
            throw std::logic_error("move(), no moves left");
        if (ms.size() == 1){
            move(ms[0]);
            return;
        }
        while (!move(m_direction, ms))
            m_direction = getNext(m_direction);
    }
    std::vector<Move> possibleMoves() const{
        auto result = std::vector<Move>();
        if (m_at.j != m_data.size() - 1 && !m_data[m_at.i][m_at.j + 1])
            result.push_back(Move::Right);
        if (m_at.i != m_data.size() - 1 && !m_data[m_at.i + 1][m_at.j])
            result.push_back(Move::Down);
        if (m_at.j != 0 && !m_data[m_at.i][m_at.j - 1])
            result.push_back(Move::Left);
        if (m_at.i != 0 && !m_data[m_at.i - 1][m_at.j])
            result.push_back(Move::Up);
        return result;
    }
    void move(const Move i_move){
        switch (i_move){
            case Move::Right: {
                ++m_at.j;
                break;
            }
            case Move::Down: {
                ++m_at.i;
                break;
            }
            case Move::Left: {
                --m_at.j;
                break;
            }
            case Move::Up: {
                --m_at.i;
                break;
            }
            default: throw std::logic_error("move(m), invalid move");
        }
    }
    bool move(const Direction i_direction, std::vector<Move> i_ms){
        switch (i_direction){
            case Direction::Right: {
                if (std::none_of(i_ms.cbegin(), i_ms.cend(),
                    [](const auto i_m){ return i_m == Move::Right; }))
                        return false;
                ++m_at.j;
                return true;
            }
            case Direction::Down: {
                if (std::none_of(i_ms.cbegin(), i_ms.cend(),
                    [](const auto i_m){ return i_m == Move::Down; }))
                        return false;
                ++m_at.i;
                return true;
            }
            case Direction::Left: {
                if (std::none_of(i_ms.cbegin(), i_ms.cend(),
                    [](const auto i_m){ return i_m == Move::Left; }))
                        return false;
                --m_at.j;
                return true;
            }
            case Direction::Up: {
                if (std::none_of(i_ms.cbegin(), i_ms.cend(),
                    [](const auto i_m){ return i_m == Move::Up; }))
                        return false;
                --m_at.i;
                return true;
            }
            default: throw std::logic_error("move(direction, moves), invalid direction");
        }
    }
private:
    std::vector<std::vector<bool>> m_data;
    struct {
        std::size_t i = 0;
        std::size_t j = 0;
    } m_at;
    std::size_t m_val = 1;
    Direction m_direction = Direction::Right;
};

}

Matrix Utils::generateSnakeSolution(const std::size_t i_n)
{
    if (i_n < g_min_n || i_n > g_max_n)
        throw std::logic_error("generateSnakeSolution(n), invalid n");
    auto result = std::vector<std::size_t>(i_n * i_n, 0);
    auto it = SnakeIterator(i_n);
    for (std::size_t i = 0; i < result.size() - 1; ++i){
        result[it.at()] = *it;
        ++it;
    }
    return result;
}

Matrix Utils::generateRandomMap(const std::size_t i_n)
{
    auto result = std::vector<std::size_t>(i_n * i_n, 0);
    for (std::size_t i = 0; i < result.size(); ++i)
        result[i] = i;
    const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto random_engine = std::default_random_engine{static_cast<unsigned>(seed)};
    std::shuffle(std::begin(result), std::end(result), random_engine);
    return result;
}

std::string Utils::generateTestName()
{
    static std::size_t n = 0;
    return "test " + std::to_string(++n);
}
