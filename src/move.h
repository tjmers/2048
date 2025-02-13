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
/// @brief Overloads the << operator so that it is easier to print a move
/// @param os output stream to output data to 
/// @param m the move to be outputted 
/// @return the same os that was inputted, with the additional data added from the move 
inline std::ostream& operator<<(std::ostream& os, const Move& move) {
    switch (move) {
        case Move::UP:
            os << "Up";
            break;
        case Move::DOWN:
            os << "Down";
            break;
        case Move::LEFT:
            os << "Left";
            break;
        case Move::RIGHT:
            os << "Right";
            break;
    }

    return os;
}
#endif