#include "Hash.hpp"
#include "Utils.hpp"
#include "State.hpp"

Hash::Hash()
    : m_data(Utils::g_bucket_count,
            [h = std::hash<std::string>()](const auto& i_state){ return h(Utils::data(i_state).data()); },
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
