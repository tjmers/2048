#include "priority_deque.h"

#include <functional>
#include <vector>

template class PriorityDeque<int>;

template<typename T>
PriorityDeque<T>::PriorityDeque(std::function<int(T, T)> comparator) : comparator(comparator), rep() {
}

template<typename T>
void PriorityDeque<T>::add(T item) {
    // Find the position to insert item based off of the given less than function

    // Use a binary search since it is not guaranteeded that the comparator is O(1)

    int low = 0;
    int high = rep.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = comparator(item, rep[mid]);

        if (cmp < 0) {
            // Item is less than rep[mid]. Discard the right half.
            high = mid - 1;
        } else {
            // Item is greater than rep[mid]. Discard the left half.
            low = mid + 1;
        } 
    }

    // Low is not at the correct position
    rep.insert(rep.begin() + low, item);

}