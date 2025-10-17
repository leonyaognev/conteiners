#pragma once

#include <cstddef>

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
    iterator();
    /** @brief Iterator from a pointer. */
    iterator(pointer ptr);
    /** @brief Copy constructor. */
    iterator(const iterator& it);

    /** @brief Dereference operator. */
    reference operator*() const;
    /** @brief Member access operator. */
    pointer operator->() const;

    /** @brief Prefix increment. */
    iterator& operator++();
    /** @brief Postfix increment. */
    iterator operator++(int);

    /** @brief Prefix decrement. */
    iterator& operator--();
    /** @brief Postfix decrement. */
    iterator operator--(int);

    /** @brief Equality comparison. */
    bool operator==(const iterator& other) const;
    /** @brief Inequality comparison. */
    bool operator!=(const iterator& other) const;
  };

  using Iterator = iterator;  ///< Alias for iterator

 public:
  /** @brief Default constructor, creates empty array. */
  BaseArray();
  /** @brief Constructor with initial size. */
  BaseArray(std::size_t n);
  /** @brief Constructor with initial size and value. */
  BaseArray(std::size_t n, const T& value);

  ///< Copy constructor
  BaseArray(const BaseArray& other);

  ///< Move constructor
  BaseArray(BaseArray&& other);
  BaseArray& operator=(const BaseArray& other);  ///< Copy assignment
  BaseArray& operator=(BaseArray&& other);       ///< Move assignment

  /** @brief Destructor, frees array memory. */
  ~BaseArray();

  /** @brief Iterator to first element. */
  iterator begin() const;
  /** @brief Iterator past the last element. */
  iterator end() const;

  /** @brief Access element at index (with bounds checking optional). */
  T& at(std::size_t n);
  const T& at(std::size_t n) const;

  /** @brief Access first element. */
  T& front();
  const T& front() const;

  /** @brief Access last element. */
  T& back();
  const T& back() const;

  /** @brief Pointer to underlying array. */
  T* data();
  const T* data() const;

  /** @brief Checks if array is empty. */
  bool empty() const noexcept;

  /** @brief Returns number of elements. */
  std::size_t size() const noexcept;
  /** @brief Returns allocated capacity. */
  std::size_t capacity() const noexcept;

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
  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;

  /** @brief Three-way comparison operator. */
  auto operator<=>(const BaseArray& other) const = default;

  /**
   * @brief Print array contents via logger.
   *
   * Format: [elem1, elem2, ...]
   */
  void Print();
};

#include "impl/BaseArray.tpp"
