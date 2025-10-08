#pragma once

#include <cstddef>
#include <sstream>
#include <string>

#include "logger.h"

/**
 * @brief Dynamic array similar to std::vector.
 *
 * @tparam T type of elements stored in the array.
 */
template <typename T>
class BaseArray {
 private:
  T* _data;               ///< Pointer to array data
  std::size_t _capacity;  ///< Allocated memory capacity
  std::size_t _size;      ///< Current number of elements

  /**
   * @brief Iterator for traversing array elements.
   *
   * Supports dereference, increment, decrement, and comparison operations.
   */
  class iterator {
   public:
    using valueType = T;   ///< Value type
    using pointer = T*;    ///< Pointer type
    using reference = T&;  ///< Reference type

    pointer current;  ///< Pointer to the current element

    /** @brief Default constructor (nullptr). */
    iterator() : current(nullptr) {}
    /** @brief Iterator from a pointer. */
    iterator(pointer ptr) : current(ptr) {}
    /** @brief Copy constructor. */
    iterator(const iterator& it) : current(it.current) {}

    /** @brief Dereference operator. */
    reference operator*() const { return *current; }
    /** @brief Member access operator. */
    pointer operator->() const { return current; }

    /** @brief Prefix increment. */
    iterator& operator++() {
      ++current;
      return *this;
    }
    /** @brief Postfix increment. */
    iterator operator++(int) {
      iterator tmp = *this;
      ++current;
      return tmp;
    }

    /** @brief Prefix decrement. */
    iterator& operator--() {
      --current;
      return *this;
    }
    /** @brief Postfix decrement. */
    iterator operator--(int) {
      iterator tmp = *this;
      --current;
      return tmp;
    }

    /** @brief Equality comparison. */
    bool operator==(const iterator& other) const {
      return current == other.current;
    }
    /** @brief Inequality comparison. */
    bool operator!=(const iterator& other) const {
      return current != other.current;
    }
  };

  using Iterator = iterator;  ///< Alias for iterator

 public:
  /** @brief Default constructor, creates empty array. */
  BaseArray() : _data(nullptr), _size(0), _capacity(0) {}
  /** @brief Constructor with initial size. */
  BaseArray(std::size_t n) : _data(new T[n]), _size(n), _capacity(n) {}
  /** @brief Constructor with initial size and value. */
  BaseArray(std::size_t n, const T& value)
      : _data(new T[n]), _size(n), _capacity(n) {
    for (std::size_t i = 0; i < _size; i++) {
      _data[i] = value;
    }
  }

  BaseArray(const BaseArray& other);            ///< Copy constructor
  BaseArray(BaseArray&& other);                 ///< Move constructor
  BaseArray operator=(const BaseArray& other);  ///< Copy assignment
  BaseArray operator=(BaseArray&& other);       ///< Move assignment

  /** @brief Destructor, frees array memory. */
  ~BaseArray() { delete[] _data; }

  /** @brief Iterator to first element. */
  iterator begin() const { return iterator(_data); }
  /** @brief Iterator past the last element. */
  iterator end() const { return iterator(_data + _size); }

  /** @brief Access element at index (with bounds checking optional). */
  T& at(std::size_t n) { return _data[n]; }
  const T& at(std::size_t n) const { return _data[n]; }

  /** @brief Access first element. */
  T& front() { return _data[0]; }
  const T& front() const { return _data[0]; }

  /** @brief Access last element. */
  T& back() { return _data[_size - 1]; }
  const T& back() const { return _data[_size - 1]; }

  /** @brief Pointer to underlying array. */
  T* data() { return _data; }
  const T* data() const { return _data; }

  /** @brief Checks if array is empty. */
  bool empty() const noexcept { return _size == 0; }

  /** @brief Returns number of elements. */
  std::size_t size() const noexcept { return _size; }
  /** @brief Returns allocated capacity. */
  std::size_t capacity() const noexcept { return _capacity; }

  /** @brief Reserve memory for at least new_cap elements. */
  void reserve(std::size_t new_cap);
  /** @brief Shrink capacity to fit current size. */
  void shrink_to_fit();

  /** @brief Clears all elements. */
  void clear();

  /** @brief Insert element at position (copy). */
  iterator insert(iterator pos, const T& value);
  /** @brief Insert element at position (move). */
  iterator insert(iterator pos, T&& value);
  /** @brief Insert count copies of value at position. */
  iterator insert(iterator pos, std::size_t count, const T& value);
  /** @brief Insert range of elements at position. */
  template <typename InputIt>
  iterator insert(iterator pos, InputIt first, InputIt last);

  /** @brief Emplace element at position. */
  template <typename... Args>
  iterator emplace(iterator pos, Args&&... args);

  /** @brief Erase element at position. */
  iterator erase(iterator pos);
  /** @brief Erase elements in range [first, last). */
  iterator erase(iterator first, iterator last);

  /** @brief Append element to the end (copy). */
  void push_back(const T& value);
  /** @brief Append element to the end (move). */
  void push_back(T&& value);

  /** @brief Emplace element at the end. */
  template <typename... Args>
  T& emplace_back(Args&&... args);

  /** @brief Remove last element. */
  void pop_back();

  /** @brief Resize array to count elements. */
  void resize(std::size_t count);
  /** @brief Resize array and fill new elements with value. */
  void resize(std::size_t count, const T& value);

  /** @brief Swap contents with another array. */
  void swap(BaseArray& other);

  /** @brief Index access operator. */
  T& operator[](std::size_t index) { return _data[index]; }
  const T& operator[](std::size_t index) const { return _data[index]; }

  /** @brief Three-way comparison operator. */
  auto operator<=>(BaseArray other);

  /**
   * @brief Print array contents via logger.
   *
   * Format: [elem1, elem2, ...]
   */
  void Print() {
    std::stringstream out;
    out << "[";
    for (size_t i = 0; i < _size; i++) {
      out << _data[i];
      if (i != _size - 1) {
        out << ", ";
      }
    }
    out << "]";
    std::string str = out.str();
    log_info("Array: %s", str.c_str());
  }
};
