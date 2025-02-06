#pragma once

#ifdef DEBUG
#include <iostream>
#endif
#include <vector>

#include "board.h"

namespace brute_solver {

enum Move {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

std::vector<std::pair<Board, float>> get_all_possible_boards(const Board& b);

float get_board_ev(const Board& b, int depth);

Move next_move(Board& board, int depth);

#ifdef DEBUG
std::ostream& operator<<(std::ostream& os, Move move);
#endif


}