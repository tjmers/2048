#pragma once

#include "board.h"
#include "move.h"

namespace pq_solver {

/// @brief Assignes an int to a board, with a greater value representing a "better" board.
/// @param b the board to evaulte
/// @return the evaulation of the board.
int evaulate(const Board& b);

/// @brief Determines the next best move for the Board.
/// @param b board to solve
/// @param depth depth to solve the board with
/// @return 
Move solve(const Board& b, int depth);


}