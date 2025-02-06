#pragma once

#ifdef DEBUG
#include <iostream>
#endif
#include <vector>

#include "board.h"
#include "move.h"

namespace brute_solver {


std::vector<std::pair<Board, float>> get_all_possible_boards(const Board& b);

float get_board_ev(const Board& b, int depth);

Move next_move(const Board& board, int depth);



}