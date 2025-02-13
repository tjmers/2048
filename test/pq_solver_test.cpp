// Compilation command: g++ test/pq_solver_test.cpp -o test/pq_solver_test.exe src/pq_solver.cpp src/move.cpp src/board.cpp structures/priority_deque.cpp -DDEBUG -DSOLVER
// Test cases for pq_solver

#include <iostream>

#include "../src/board.h"
#include "../src/move.cpp"
#include "../src/pq_solver.h"

int main(void) {

    Board b({0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0});
    
    Move sol = pq_solver::solve(b, 4);

    std::cout << sol << '\n';


    return 0;
}