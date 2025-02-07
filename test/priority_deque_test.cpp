// Compilation command: g++ test/priority_deque_test.cpp structures/priority_deque.cpp -o test/priority_deque.exe

#include "../structures/priority_deque.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

// Test cases are only needed for the add method.
// All other methods have very simple implementations.

/// @brief Comparator for two ints.
/// @param i1 the first integer
/// @param i2 the second integer
/// @return compare > 0 iff i1 > i2, compare < 0 iff i1 < i2, compare = 0 iff i1 = i2.
int compare(int i1, int i2) {
    return i1 - i2;
}

// One test case will be performed in the main method.
int main(void) {

    PriorityDeque<int> deque(compare);

    // Add 1000 random numbers between 0 and 99.
    srand(time(NULL));
    for (int i = 0; i < 1000; ++i) {
        deque.add(rand() % 100);
    }

    // Make sure that the deque is in order
    int previous_number = 0;
    while (!deque.empty()) {
        int current = deque.pop_least();
        std::cout << current << '\n';
        if (previous_number > current) {
            std::cout << "Error: deque is not in order (1)\n";
            return 1;
        }

        previous_number = current;
    }

    std::cout << "First test case passed.\n";

    // Deque is now empty

    // Repeat process going the opposite direction
    for (int i = 0; i < 1000; ++i) {
        deque.add(rand() % 100);
    }

    // Make sure that the deque is in order
    previous_number = 100;
    while (!deque.empty()) {
        int current = deque.pop_greatest();
        std::cout << current << '\n';

        if (previous_number < current) {
            std::cout << "Error: deque is not in order (2)\n";
            return 1;
        }

        previous_number = current;
    }

    std::cout << "Test case 2 passed.\n";



    std::cout << "All test cases passed.\n";
    return 0;
}