// Testing the brute force solver
// Compilation command: g++ test/brute_solver_test.cpp src/brute_solver.cpp src/board.cpp -o test/brute_solver_test.exe -DSOLVER -DDEBUG
#include "../src/brute_solver.h"

#include <iostream>

int main(void) {

    Board b({2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    brute_solver::Move next_move = brute_solver::next_move(b, 3);

    std::cout << next_move << '\n';

    return 0;
}