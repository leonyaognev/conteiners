#pragma once

#include <cstddef>

template <typename Ptr>
  /**
   * @brief Iterator for traversing array elements.
   *
   * Supports dereference, increment, decrement, and comparison operations.
   */
class ArrayIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = std::remove_pointer_t<Ptr>;
    using difference_type   = std::ptrdiff_t;
    using pointer           = Ptr;
    using reference         = value_type&;

    pointer current;

    ArrayIterator(pointer ptr = nullptr) : current(ptr) {}

    reference operator*() const { return *current; }
    pointer operator->() const { return current; }

    ArrayIterator& operator++() { ++current; return *this; }
    ArrayIterator operator++(int) { auto tmp = *this; ++current; return tmp; }

    ArrayIterator& operator--() { --current; return *this; }
    ArrayIterator operator--(int) { auto tmp = *this; --current; return tmp; }

	ArrayIterator operator+(std::size_t n) { return ArrayIterator(current + n);}
	ArrayIterator operator-(std::size_t n) { return ArrayIterator(current - n);}
	
	difference_type operator-(const ArrayIterator& other) const {
        return current - other.current;
    }
	
    bool operator==(const ArrayIterator& other) const { return current == other.current; }
    bool operator!=(const ArrayIterator& other) const { return current != other.current; }
};