#pragma once

#include <functional>

#include "move.h"
#include "visual_board.h"

class VisualAutoSolveBoard : public VisualBoard {

private:
    std::function<Move(const Board&, int)> get_next_move;
    const int depth;

public:
    VisualAutoSolveBoard(std::function<Move(const Board&, int)> get_next_move, int depth);
    VisualAutoSolveBoard() = delete;

    void update();
};