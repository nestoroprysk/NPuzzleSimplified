#include "Hash.hpp"
#include "Utils.hpp"
#include "State.hpp"

namespace {

std::size_t hash(const State& i_state)
{
    std::hash<std::size_t> hasher;
    auto result = std::size_t(0);;
    const auto& array = Utils::data(i_state);
    for(std::size_t i = 0; i < array.sizeSquared(); ++i)
        result = (result << 1) ^ hasher(array[i]);
    return result;
}

}

Hash::Hash()
    : m_data(Utils::g_bucket_count,
            [](const auto& i_state){ return hash(i_state); },
            [](const auto& i_lhs, const auto& i_rhs){ return Utils::eq(i_lhs, i_rhs); })
{
}

bool Hash::contains(const State& i_state) const
{
    return m_data.find(i_state) != m_data.end();
}

void Hash::push(const State& i_state)
{
    m_data.insert(i_state);
}

void Hash::pop(const State& i_state)
{
    m_data.erase(i_state);
}

std::size_t Hash::size() const
{
    return m_data.size();
}
