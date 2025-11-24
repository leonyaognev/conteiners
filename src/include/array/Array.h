#pragma once

#include <cstddef>

template <typename T, std::size_t N>
class Array {
 private:

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

  class const_iterator {
	public:
    using valueType = T;
    using pointer = const T*;
    using reference = const T&;

    pointer current;

    const_iterator() : current(nullptr) {}
    const_iterator(pointer ptr) : current(ptr) {}
    const_iterator(const const_iterator& it) : current(it.current) {}

    reference operator*() const { return *current; }
    pointer operator->() const { return current; }

    const_iterator& operator++() { ++current; return *this; }
    const_iterator operator++(int) { const_iterator tmp(*this); ++current; return tmp; }

    const_iterator& operator--() { --current; return *this; }
    const_iterator operator--(int) { const_iterator tmp(*this); --current; return tmp; }

    bool operator==(const const_iterator& other) const { return current == other.current; }
    bool operator!=(const const_iterator& other) const { return current != other.current; }
};

 public:
  T _data[N];
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::size_t size_type;

  using Iterator = iterator;  ///< Alias for iterator

  reference at(size_type off);

  reference back() noexcept;
  constexpr const_reference back() const; //!
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  T* data();
  const T* data() const;

  constexpr bool empty() const;
  constexpr size_type size() const;
  constexpr size_type max_size() const;

  void fill(const T& val);
  void swap(Array& right);

  iterator end();
  const_iterator end() const; //!
  reference front(); //!
  constexpr const_reference front() const; //!

  reference operator[](size_type off);
  const_reference operator[](size_type off) const;

  Array& operator=(Array& right);

  void Print();
};

#include "impl/Array.tpp"
