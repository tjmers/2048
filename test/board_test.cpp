// Test cases for the board
// Compilation command: g++ test/board_test.cpp src/board.cpp -o test/board_test.exe -DDEBUG

#include "../src/board.h"

#include <functional>
#include <iostream>

#include <cstdlib>

template <typename T>
void assert(T expected, T observed) {
    if (expected != observed) {
        std::cout << "Assertation failed:\nExpected:\n" << expected << "\nbut was:\n" << observed << '\n';
        std::exit(EXIT_FAILURE); 
    }
}

// Test cases for the perform_direction methods

/// @brief Test case for perform up where nothing should happen.
void test_perform_up_nothing() {
    Board board({2, 2, 2, 2, 4, 4, 8, 8, 0, 0, 2, 0, 0, 0, 0, 0});

    Board expected_board({2, 2, 2, 2, 4, 4, 8, 8, 0, 0, 2, 0, 0, 0, 0, 0});

    int expected_score = 0;

    board.perform_up();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform up where some blocks move up.
void test_perform_up_move() {
    Board board({2, 0, 4, 16, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2});

    Board expected_board({2, 8, 4, 16, 4, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0});

    int expected_score = 0;

    board.perform_up();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform up where some block get combined.
void test_perform_up_combine() {
    Board board({0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0});

    Board expected_board({32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    int expected_score = 32;

    board.perform_up();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform down where nothing happens.
void test_perform_down_nothing() {
    Board board({0, 0, 0, 0, 0, 0, 0, 2, 4, 4, 4, 4, 2, 2, 2, 2});

    Board expected_board({0, 0, 0, 0, 0, 0, 0, 2, 4, 4, 4, 4, 2, 2, 2, 2});

    int expected_score = 0;

    board.perform_down();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform down where some blocks move down.
void test_perform_down_move() {
    Board board({0, 0, 0, 2, 0, 4, 0, 0, 2, 0, 0, 4, 0, 0, 0, 0});

    Board expected_board({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 4, 0, 4});

    int expected_score = 0;

    board.perform_down();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform down where some blocks get combined.
void test_perform_down_combine() {
    Board board({16, 0, 0, 0, 0, 8, 0, 0, 16, 0, 0, 0, 0, 8, 0, 0});

    Board expected_board({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 16, 0, 0});

    int expected_score = 48;

    board.perform_down();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform right where nothing should happen.
void test_perform_right_nothing() {
    Board board({0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 8, 16, 0, 0, 0, 2});

    Board expected_board({0, 0, 2, 4, 0, 0, 0, 0, 2, 4, 8, 16, 0, 0, 0, 2});

    int expected_score = 0;

    board.perform_right();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform right where some block are moved.
void test_perform_right_move() {
    Board board({0, 2, 0, 0, 2, 0, 4, 0, 0, 4, 0, 2, 2, 4, 0, 0});

    Board expected_board({0, 0, 0, 2, 0, 0, 2, 4, 0, 0, 4, 2, 0, 0, 2, 4});

    int expected_score = 0;

    board.perform_right();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform right where some blocks get combined.
void test_perform_right_combine() {
    Board board({2, 2, 2, 2, 4, 4, 0, 0, 0, 4, 0, 4, 0, 0, 4, 4});

    Board expected_board({0, 0, 4, 4, 0, 0, 0, 8, 0, 0, 0, 8, 0, 0, 0, 8});

    int expected_score = 32;

    board.perform_right();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform left where nothing happens.
void test_perform_left_nothing() {
    Board board({2, 4, 0, 0, 0, 0, 0, 0, 2, 4, 8, 16, 16, 8, 4, 2});

    Board expected_board({2, 4, 0, 0, 0, 0, 0, 0, 2, 4, 8, 16, 16, 8, 4, 2});

    int expected_score = 0;

    board.perform_left();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform left where some blocks get moved.
void test_perform_left_move() {
    Board board({0, 4, 16, 32, 2, 0, 16, 4, 2, 4, 0, 8, 2, 4, 8, 16});

    Board expected_board({4, 16, 32, 0, 2, 16, 4, 0, 2, 4, 8, 0, 2, 4, 8, 16});

    int expected_score = 0;

    board.perform_left();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}

/// @brief Test case for perform left where some blocks get combined.
void test_perform_left_combine() {
    Board board({2, 2, 2, 2, 0, 0, 4, 4, 16, 8, 8, 0, 4, 0, 0, 4});

    Board expected_board({4, 4, 0, 0, 8, 0, 0, 0, 16, 16, 0, 0, 8, 0, 0, 0});

    int expected_score = 40;

    board.perform_left();

    assert(expected_board, board);
    assert(expected_score, board.get_score());
}


// Test cases for can_perform_direction methods


/// @brief Test case for can perform up where it returns false.
void test_can_perform_up_false() {

    Board board({2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    Board expected_board({2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    bool expected_result = false;

    bool result = board.can_perform_up();

    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform up where it returns true.
void test_can_perform_up_true() {
    Board board({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4});
    Board expected_board({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4});

    bool expected_result = true;
    bool result = board.can_perform_up();
    
    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform up where it returns false and the board is full.
void test_can_perform_up_false_full() {
    Board board({2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16});
    Board expected_board({2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16});

    bool expected_result = false;
    bool result = board.can_perform_up();

    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform up where it returns true and the board is full
void test_can_perform_up_true_full() {
    Board board({2, 2, 2 ,2, 2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8});
    Board expected_board({2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8});

    bool expected_result = true;
    bool result = board.can_perform_up();

    assert(expected_result, result);
    assert(expected_board, board);
}


/// @brief Test case for can perform down where it returns false.
void test_can_perform_down_false() {

    Board board({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0});

    Board expected_board({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0});

    bool expected_result = false;

    bool result = board.can_perform_down();

    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform down where it returns true.
void test_can_perform_down_true() {
    Board board({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    Board expected_board({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    bool expected_result = true;
    bool result = board.can_perform_down();
    
    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform down where it returns false and the board is full.
void test_can_perform_down_false_full() {
    Board board({2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16});
    Board expected_board({2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16});

    bool expected_result = false;
    bool result = board.can_perform_down();

    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform down where it returns true and the board is full
void test_can_perform_down_true_full() {
    Board board({2, 2, 2 ,2, 2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8});
    Board expected_board({2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8});

    bool expected_result = true;
    bool result = board.can_perform_down();

    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform right were it returns false
void test_can_perform_right_false() {
    Board board({0, 0, 0, 2, 0, 0, 2, 4, 0, 2, 4, 8, 2, 4, 8, 16});
    Board expected_board({0, 0, 0, 2, 0, 0, 2, 4, 0, 2, 4, 8, 2, 4, 8, 16});

    bool expected_result = false;
    bool result = board.can_perform_right();

    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform right where it returns true.
void test_can_perform_right_true() {
    Board board({2, 2, 2, 2, 2, 4, 8, 16, 2, 4, 8, 16, 2, 4, 8, 16});
    Board expected_board({2, 2, 2, 2, 2, 4, 8, 16, 2, 4, 8, 16, 2, 4, 8, 16});

    bool expected_result = true;
    bool result = board.can_perform_right();

    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform lest that returns false.
void test_can_perform_left_false() {
    Board board({2, 4, 8, 16, 2, 4, 8, 16, 16, 8, 4, 2, 16, 8, 4, 2});
    Board expected_board({2, 4, 8, 16, 2, 4, 8, 16, 16, 8, 4, 2, 16, 8, 4, 2});

    bool expected_result = false;
    bool result = board.can_perform_left();

    assert(expected_result, result);
    assert(expected_board, board);
}

/// @brief Test case for can perform left that returns true.
void test_can_perform_left_true() {
    Board board({2, 2, 2, 2, 2, 4, 8, 16, 2, 4, 8, 16, 2, 4, 8, 16});
    Board expected_board({2, 2, 2, 2, 2, 4, 8, 16, 2, 4, 8, 16, 2, 4, 8, 16});

    bool expected_result = true;
    bool result = board.can_perform_left();

    assert(expected_result, result);
    assert(expected_board, board);
}

// Test cases for game_over method

/// @brief Test case for game over where the board is not full (returns false).
void test_game_over_not_full() {
    Board board({2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    assert(false, board.game_over());
}

/// @brief Test case for game over that returns false
void test_game_over_full_false() {
    Board board({2, 4, 8, 16, 16, 8, 4, 2, 2, 32, 4, 16, 32, 64, 128, 256});

    assert(false, board.game_over());
}

/// @brief Test case for game over that return true
void test_game_over_full_true() {
    Board board({2, 4, 8, 16, 16, 8, 4, 2, 2, 4, 8, 16, 16, 8, 4, 2});

    assert(true, board.game_over());
}



int main() {

    // Initialze the board class
    Board::init();

    std::vector<std::function<void()>> test_cases = {
        test_perform_up_nothing, test_perform_up_move, test_perform_up_combine,
        test_perform_down_nothing, test_perform_down_move, test_perform_down_combine,
        test_perform_right_nothing, test_perform_right_move, test_perform_right_combine,
        test_perform_left_nothing, test_perform_left_move, test_perform_left_combine,
        test_can_perform_up_false, test_can_perform_up_true, test_can_perform_up_false_full, test_can_perform_up_true_full,
        test_can_perform_down_false, test_can_perform_down_true, test_can_perform_down_false_full, test_can_perform_down_true_full,
        test_can_perform_right_false, test_can_perform_right_true,
        test_can_perform_left_false, test_can_perform_left_true,
        test_game_over_not_full, test_game_over_full_false, test_game_over_full_true
    };

    // Call test cases
    for (int i = 0; i < test_cases.size(); ++i) {
        test_cases[i]();
        std::cout << "Test case " << (i + 1) << " passed.\n";
    }

    std::cout << "All test cases passed\n";

    return 0;
}