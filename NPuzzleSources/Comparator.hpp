#pragma once

#include "SolverConfiguration.hpp"
#include "Utils.hpp"
#include "State.hpp"

template <typename Order>
class Comparator
{
public:
	Comparator(SolverConfiguration i_config);
	bool operator()(const State& i_lhs, const State& i_rhs) const;
private:
	std::size_t f(const State& i_state) const;
	bool cmpImpl(const State& i_lhs, const State& i_rhs) const;
private:
	const SolverConfiguration m_configuration;
};

template <typename Order>
Comparator<Order>::Comparator(SolverConfiguration i_config)
	: m_configuration(std::move(i_config))
{
}

template <typename Order>
bool Comparator<Order>::operator()(const State&, const State&) const
{
	throw std::logic_error("comparator<T>(), Less or NotLess expected");
}

template <>
inline bool Comparator<Less>::operator()(const State& i_lhs, const State& i_rhs) const
{
	return cmpImpl(i_lhs, i_rhs);
}

template <>
inline bool Comparator<NotLess>::operator()(const State& i_lhs, const State& i_rhs) const
{
	return !cmpImpl(i_lhs, i_rhs);	
}

template <typename Order>
std::size_t Comparator<Order>::f(const State& i_state) const
{
	return i_state.m_heuristic_cost * m_configuration.m_heuristic_function_weight +
			i_state.m_distance * m_configuration.m_distance_weight;
}

template <typename Order>
bool Comparator<Order>::cmpImpl(const State& i_lhs, const State& i_rhs) const
{
	const auto lhsCost = f(i_lhs);
	const auto rhsCost = f(i_rhs);
	return lhsCost < rhsCost ||
		(lhsCost == rhsCost && Utils::cmp(Utils::data(i_lhs), Utils::data(i_rhs)));
}
