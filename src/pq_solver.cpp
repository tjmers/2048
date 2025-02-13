#include "pq_solver.h"

#include <chrono>
#include <queue>
#include <thread>

#include "board.h"
#include "move.h"
#include "../structures/priority_deque.h"

int pq_solver::evaulate(const Board& b) {
    // Statement fine tuned through trial and error
    return static_cast<int>((b.get_score()) / (b.get_num_moves() + 1) * (1 + b.get_num_open() / 16.0f));
}


Move pq_solver::solve(const Board& b, int depth) {

    // Priority Queue for the Board and depth
    PriorityDeque<std::tuple<Board, int, Move>> pq(
        [] (const std::tuple<Board, int, Move>& b1, const std::tuple<Board, int, Move>& b2) -> int {
            return evaulate(std::get<0>(b1)) - evaulate(std::get<0>(b2));
        });

    // Add the down board the the PrirityQueue
    if (b.can_perform_down()) {
        Board board(b);
        board.perform_down();
        pq.add(std::make_tuple(std::move(board), depth, Move::DOWN));
    }

    // Add the rest of the board to the queue
    if (b.can_perform_left()) {
        Board board(b);
        board.perform_left();
        pq.add(std::make_tuple(std::move(board), depth, Move::LEFT));
    }

    if (b.can_perform_right()) {
        Board board(b);
        board.perform_right();
        pq.add(std::make_tuple(std::move(board), depth, Move::RIGHT));
    }

    if (b.can_perform_up()) {
        Board board(b);
        board.perform_up();
        pq.add(std::make_tuple(std::move(board), depth, Move::UP));
    }

    while (!pq.empty()) {
        auto current = pq.pop_greatest();

        if (std::get<1>(current) == 0) {
            return std::get<2>(current);
        }
        
        // Add all possible paths with a 2 being generated to the priority queue.
        // Fours are ignored since it happens infrequently

        auto current_array = std::get<0>(current).get_board();

        for (int i = 0; i < Board::BOARD_SIZE; ++i) {
            if (current_array[i] == 0) {
                auto array_copy(current_array);
                array_copy[i] = 2;
                
                Board board_copy(array_copy, std::get<0>(current).get_score(), std::get<0>(current).get_num_moves());

                if (board_copy.can_perform_down()) {
                    Board down_copy(board_copy);
                    down_copy.perform_down();
                    pq.add(std::make_tuple(std::move(down_copy), std::get<1>(current) - 1, std::get<2>(current)));
                }

                if (board_copy.can_perform_left()) {
                    Board left_copy(board_copy);
                    left_copy.perform_left();
                    pq.add(std::make_tuple(std::move(left_copy), std::get<1>(current) - 1, std::get<2>(current)));
                }

                if (board_copy.can_perform_right()) {
                    Board right_copy(board_copy);
                    right_copy.perform_right();
                    pq.add(std::make_tuple(std::move(right_copy), std::get<1>(current) - 1, std::get<2>(current)));
                }

                if (board_copy.can_perform_up()) {
                    Board up_copy(std::move(board_copy));
                    up_copy.perform_up();
                    pq.add(std::make_tuple(std::move(up_copy), std::get<1>(current) - 1, std::get<2>(current)));
                }

            }
        }
        
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::exit(0);
    
}