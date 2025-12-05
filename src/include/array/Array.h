#pragma once

#include <cstddef>
#include "Iterator.h"

template <typename T, std::size_t N>
class Array {
 private:
 using iterator = ArrayIterator<T*>;
 using const_iterator = ArrayIterator<const T*>;

 public:	
 //constexpr Array() noexcept {}

 T _data[N];

  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef std::size_t size_type;

  reference at(size_type off);

  reference back() noexcept;
  constexpr const_reference back() const noexcept;
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator data();
  const_iterator data() const;

  constexpr bool empty() const;
  constexpr size_type size() const;
  constexpr size_type max_size() const;

  void fill(const_reference val);
  void swap(Array& right);

  iterator end() noexcept;
  const_iterator end() const noexcept; 
  reference front(); 
  constexpr const_reference front() const;

  reference operator[](size_type off);
  const_reference operator[](size_type off) const;

//   Array& operator=(Array& right);
//   Array& operator=(Array&& right) noexcept;

  void Print();
};

#include "impl/Array.tpp"
