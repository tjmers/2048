#pragma once

#ifdef DEBUG
#include <iostream>
#endif

enum Move {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


#ifdef DEBUG
std::ostream& operator<<(std::ostream& os, Move move);
#endif