#pragma once

#include "Types.hpp"

#include <unordered_set>
#include <string>

class Hash
{
public:
	Hash();
	bool contains(const State& i_state) const;
	void push(const State& i_state);
	void pop(const State& i_state);
private:
	using HashFunctionType = std::function<std::size_t(const State&)>;
	using EqFunctionType = std::function<bool(const State&, const State&)>;
	using HashType = std::unordered_set<State, HashFunctionType, EqFunctionType>;
	HashType m_data;
};
