#pragma once

#include <cstddef>

template <typename Ptr>
class ArrayIterator {
public:
    using pointer = Ptr;
    using reference = std::remove_pointer_t<Ptr>&;

    pointer current;

    ArrayIterator(pointer ptr = nullptr) : current(ptr) {}

    reference operator*() const { return *current; }
    pointer operator->() const { return current; }

    ArrayIterator& operator++() { ++current; return *this; }
    ArrayIterator operator++(int) { auto tmp = *this; ++current; return tmp; }

    ArrayIterator& operator--() { --current; return *this; }
    ArrayIterator operator--(int) { auto tmp = *this; --current; return tmp; }

    bool operator==(const ArrayIterator& other) const { return current == other.current; }
    bool operator!=(const ArrayIterator& other) const { return current != other.current; }
};