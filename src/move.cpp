#include "move.h"

#ifdef DEBUG
#include <iostream>
#endif

#ifdef DEBUG


/// @brief Overloads the << operator so that it is easier to print a move
/// @param os output stream to output data to 
/// @param m the move to be outputted 
/// @return the same os that was inputted, with the additional data added from the move 
std::ostream& operator<<(std::ostream& os, Move m) {
    switch (m) {
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