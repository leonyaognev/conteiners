#pragma once

#include <cstddef>

/**
 * @brief Dynamic array similar to std::vector.
 *
 * @tparam T type of elements stored in the array.
 */
template <typename T>
class Vector {
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
    /** @brief Increase operator */
    iterator operator+(size_t n);
    /** @brief Decrease operator */
    iterator operator-(size_t n);
    /** @brief Prefix increment. */
    iterator& operator++();
    /** @brief Postfix increment. */
    iterator operator++(int);

    /** @brief Prefix decrement. */
    iterator& operator--();
    /** @brief Postfix decrement. */
    iterator operator--(int);
    /** @brief support command for copy*/
    iterator operator=(const iterator& other);
    /** @brief Equality comparison. */
    bool operator==(const iterator& other) const;
    /** @brief Inequality comparison. */
    bool operator!=(const iterator& other) const;
  };

  using Iterator = iterator;  ///< Alias for iterator

 public:
  /** @brief Default constructor, creates empty array. */
  Vector();
  /** @brief Constructor with initial size. */
  Vector(std::size_t n);
  /** @brief Constructor with initial size and value. */
  Vector(std::size_t n, const T& value);

  ///< Copy constructor
  Vector(const Vector& other);

  ///< Move constructor
  Vector(Vector&& other);
  Vector& operator=(const Vector& other);  ///< Copy assignment
  Vector& operator=(Vector&& other);       ///< Move assignment

  /** @brief Destructor, frees array memory. */
  ~Vector();

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

  /** @brief Support method to extend allocated memory and increase capacity */
  void extend();
  /** @brief Support method to edit allocated memory, also can decrease
   * capacity*/
  void extend(std::size_t newCapacity);

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
  /** @brief Inserts new elements into the container directly before pos. */
  template <typename... Args>
  iterator insert_many(iterator pos,
                       Args&&... args);  //! switch iterator to const_iterator
  /** @brief Appends new elements to the end of the container. */
  template <typename... Args>
  void insert_many_back(Args&&... args);

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
  void resize(std::size_t newSize);
  /** @brief Resize array and fill new elements with value. */
  void resize(std::size_t newSize, const T& value);

  /** @brief Swap contents with another array. */
  void swap(Vector& other);

  /** @brief Erases a vector and copies the specified elements to the empty
   * vector. */
  void assign(std::size_t count, const T& value);
  // void assign(initializer_list<T> init_list);

  void assign(iterator first, iterator last);

  /** @brief Index access operator. */
  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;

  /** @brief Three-way comparison operator. */
  auto operator<=>(const Vector& other) const = default;

  /**
   * @brief Print array contents via logger.
   *
   * Format: [elem1, elem2, ...]
   */
  void Print();
};

#include "impl/Vector.tpp"
