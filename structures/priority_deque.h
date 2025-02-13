#pragma once

#include <functional>
#include <vector>

template <typename T>
class PriorityDeque {

private:

    /// @brief Comparator for elements in this. Should return an int less than zero when the first 
    /// object is less than the second, greater than zero when the first object is greater than the second,
    /// and exactly zero if and only if the two objects are equal.
    std::function<int(T, T)> comparator;

    /// @brief Representation of the this.
    std::vector<T> rep;

    /// @brief Maximum size of this. This implementation will remove the lowest value of a value is attemted to be added to a full queue.
    constexpr static int MAX_SIZE = 64;

public:

    PriorityDeque(std::function<int(T, T)> comparator);

    /// @brief Adds the item to this, with its positision determined by the given funtion.
    /// @param item item to add to this
    void add(T item);

    /// @brief Returns the size of this.
    /// @return the size of this
    inline int size() const { return rep.size(); }

    /// @brief Returns whether or not this is empty.
    /// @return whether or not this is empty
    inline bool empty() const { return rep.empty(); }

    /// @brief Finds the least item in this. Requires that this is not empty.
    /// @return the least item in this
    inline const T& peek_least() const { return rep[0]; }

    /// @brief Finds the greatest item in this. Requires that this is not empty.
    /// @return the greatest item in this
    inline const T& peek_greatest() const { return rep[rep.size() - 1]; }

    inline T pop_least() {
        T item = rep[0];
        rep.erase(rep.begin());
        return item;
    }

    /// @brief Removes the greatest item in this and returns it.
    /// @return the greatest item in this
    inline T pop_greatest() { 
        T item = rep.back();
        rep.pop_back();
        return item;
    }

};