#include "brute_solver.h"

#include <array>
#include <cstdlib>
#ifdef DEBUG
#include <iostream>
#endif
#include <vector>
#include <utility>

#include "board.h"


/// @brief Finds all possible board combinations that can be created when calling Board::generate_new_square() /// @param b the board to analyze 
/// @return a vector that contains all board possibilities and its probability
std::vector<std::pair<Board, float>> brute_solver::get_all_possible_boards(const Board& b) {
    const std::array<int, Board::BOARD_SIZE> start = b.get_board();

    std::vector<std::pair<Board, float>> possibilities;

    // Find all open squares in the board
    std::vector<int> open;
    for (int i = 0; i < Board::BOARD_SIZE; ++i) {
        if (start[i] == 0)
            open.push_back(i);
    }

    // Probabilties that every board that generates a 2 will be assigned
    const float two_prob = 1.0f / open.size() * (1 - (Board::FOUR_PERCENTAGE / 100.0f));

    // Probabilities that every board that generates a 4 will be assigned
    const float four_prob = 1.0f / open.size() * (Board::FOUR_PERCENTAGE / 100.0f);

    // Create board and add them to the possibilities vector
    for (const int& i : open) {
        // Copy the starting vector
        std::array<int, Board::BOARD_SIZE> current_two(start);
        std::array<int, Board::BOARD_SIZE> current_four(start);

        // Add the elements
        current_two[i] = 2;
        current_two[i] = 4;

        // Convert to board objects and add to vector using std::move for performance
        possibilities.push_back({Board(std::move(current_two), b.get_score()), two_prob});
        possibilities.push_back({Board(std::move(current_four), b.get_score()), four_prob});
    }


    return possibilities;

}

/// @brief Gets the expected value of a board
/// @param b the board to get the expected value of 
/// @param depth number of moves to calculate
/// @return the expected value of the board 
float brute_solver::get_board_ev(const Board& b, int depth) {
    // Base case
    if (depth == 0)
        return b.get_score();

    std::vector<std::pair<Board, float>> boards = get_all_possible_boards(b);

    float ev = 0;

    for (const std::pair<Board, float>& b : boards) {
        if (b.first.game_over()) continue;
        int n_moves = b.first.can_perform_up() + b.first.can_perform_down() + b.first.can_perform_left() + b.first.can_perform_right();

        if (b.first.can_perform_up()) {
            // Copy the board
            Board current(b.first);

            // Perform the move
            current.perform_up();

            // Add the weighted average to the ev
            // Since the game is not over, n_moves > 0, so no division error can occur.
            ev += get_board_ev(current, depth - 1) * b.second * (1.0f / n_moves);
        }
        
        // Repeat for all other directions
        if (b.first.can_perform_down()) {
            Board current(b.first);
            current.perform_down();
            ev += get_board_ev(current, depth - 1) * b.second * (1.0f / n_moves);
        }
        if (b.first.can_perform_left()) {
            Board current(b.first);
            current.perform_left();
            ev += get_board_ev(current, depth - 1) * b.second * (1.0f / n_moves);
        }
        if (b.first.can_perform_right()) {
            Board current(b.first);
            current.perform_right();
            ev += get_board_ev(current, depth - 1) * b.second * (1.0f / n_moves);
        }
    }

    return ev;
}

Move brute_solver::next_move(Board& board, int depth) {

    std::array<float, 4> move_ev;

    // Create all boards for each direction
    Board left_board(board);
    Board right_board(board);
    Board up_board(board);
    Board down_board(board);
    left_board.perform_left();
    right_board.perform_right();
    up_board.perform_up();
    down_board.perform_down();

    // Add their expected values to the vector
    move_ev[static_cast<int>(Move::LEFT)] = get_board_ev(left_board, depth - 1);
    move_ev[static_cast<int>(Move::RIGHT)] = get_board_ev(right_board, depth - 1);
    move_ev[static_cast<int>(Move::UP)] = get_board_ev(up_board, depth - 1);
    move_ev[static_cast<int>(Move::DOWN)] = get_board_ev(down_board, depth - 1);

    // Find the maximum score
    float max_score = move_ev[0];

    for (int i = 0; i < 4; ++i) {
        max_score = std::max(max_score, move_ev[i]);
    }

    // Find the max score and return its move
    for (int i = 0; i < 4; ++i) {
        if (move_ev[i] == max_score) {
            return static_cast<Move>(i);
        }
    }

    // If this is reached, something went wrong
    std::exit(1);
}