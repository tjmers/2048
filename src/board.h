#pragma once

#include <array>
#ifdef DEBUG
#include <iostream>
#endif


class Board {

public:

    constexpr static int BOARD_SIZE = 16;
    constexpr static int FOUR_PERCENTAGE = 10;

private:


    
    /// @brief the representation of the board, with the top left being slot 0
    std::array<int, BOARD_SIZE> board;


    int score;

    // Number of zeros in the board
    int open_spaces;

    int moves;

#if defined(DEBUG) || defined(SOLVER)
    static int calculate_open_spaces(const std::array<int, BOARD_SIZE>& board);
#endif

public:


    static void init();

    Board();
    Board(const Board& other);
    Board(Board&& other);
    Board* operator=(const Board& other);
    Board* operator=(Board&& other);
#if defined(DEBUG) || defined(SOLVER)
    Board(const std::array<int, BOARD_SIZE>& board);
    Board(const std::array<int, BOARD_SIZE>&& board);
    Board(const std::array<int, BOARD_SIZE>& board, int score);
    Board(const std::array<int, BOARD_SIZE>&& board, int score);
    Board(const std::array<int, BOARD_SIZE>& board, int score, int moves);
    Board(const std::array<int, BOARD_SIZE>&& board, int score, int moves);
#endif

    void perform_up();
    void perform_down();
    void perform_left();
    void perform_right();
    bool can_perform_up() const;
    bool can_perform_down() const;
    bool can_perform_left() const;
    bool can_perform_right() const;

    inline int get_score() const { return score; }
    inline int get_num_open() const { return open_spaces; }
    inline int get_num_moves() const { return moves; }

    bool game_over() const;

    void generate_new_square();

    const std::array<int, BOARD_SIZE>& get_board() const; 

#ifdef DEBUG
    bool operator==(const Board& other);
    bool operator!=(const Board& other);
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
#endif

};