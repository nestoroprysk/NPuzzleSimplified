#pragma once

#include <ostream>

enum class Move { Left, Right, Up, Down };

inline std::ostream& operator<<(std::ostream& o_s, Move i_m)
{
    switch (i_m){
        case Move::Left: o_s << "Left"; return o_s;
        case Move::Right: o_s << "Right"; return o_s;
        case Move::Up: o_s << "Up"; return o_s;
        case Move::Down: o_s << "Down"; return o_s;
        default: throw std::logic_error("<<(move), invalid move");
    }
}
