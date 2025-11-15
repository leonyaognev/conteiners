#pragma once

#include <cstddef>

template <typename T, std::size_t N>
class array {
 private:
  T _data[N];

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

 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

  using Iterator = iterator;  ///< Alias for iterator

  reference at(size_type off);

  reference back() noexcept;
  iterator begin() noexcept;

  T* data();
  const T* data() const;

  constexpr bool empty() const;
  constexpr size_type size() const;
  constexpr size_type max_size() const;

  void fill(const T& val);
  void swap(array& right);

  iterator end();
  iterator front();

  reference operator[](size_type off);
  const_reference operator[](size_type off) const;

  array& operator=(array& right);
};

#include "impl/Array.tpp"
