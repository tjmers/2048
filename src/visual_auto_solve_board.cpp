#include "visual_auto_solve_board.h"

#include <functional>

VisualAutoSolveBoard::VisualAutoSolveBoard(std::function<Move(const Board&, int)> get_next_move, int depth) : VisualBoard(), get_next_move(get_next_move), depth(depth) {

}


void VisualAutoSolveBoard::update() {
    if (game_over()) return;

    Move move = get_next_move(*this, depth);
    
    switch (move) {
        case Move::LEFT:
            perform_left();
            break;
        case Move::RIGHT:
            perform_right();
            break;
        case Move::UP:
            perform_up();
            break;
        case Move::DOWN:
            perform_down();
            break;
    }

    // Says that we should draw the board again
    change();
    generate_new_square();
}