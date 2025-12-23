#pragma once

#include <cstddef>
#include <initializer_list>

#include "RedBlackTree/BaseTree.h"

template <typename T, typename Compare = std::less<T>>
class Set : public RBBase<T, Compare> {
 private:
  using Base = RBBase<T, Compare>;
  using Node = typename Base::Node;

 public:
  using iterator = typename Base::iterator;

  using Base::Base;
  Set();

  Set(const Set& other);

  Set(Set&& other) noexcept;

  Set(std::initializer_list<T> ilist);

  template <typename InputIt>
  Set(InputIt first, InputIt last);

  Set& operator=(const Set& other);

  using Base::begin;
  using Base::contains;
  using Base::empty;
  using Base::end;
  using Base::insert;
  using Base::insert_many;
  using Base::max_size;
  using Base::merge;
  using Base::size;

  void swap(Set& other);

  void merge(Set& other);

  void erase(iterator pos);
  void clear();

  iterator find(const T& val) const;
  size_t count(const T& val) const;
};

#include "impl/Set.tpp"
