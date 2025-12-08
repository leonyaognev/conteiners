#pragma once

#include <cstddef>
#include <initializer_list>

#include "RedBlackTree/BaseTree.h"

template <typename T, typename Compare = std::less<T>>
class Set : RBBase<T, Compare> {
 private:
  using Base = RBBase<T, Compare>;
  using Node = typename RBBase<T, Compare>::Node;

 public:
  using iterator = typename Base::iterator;

  using Base::Base;
  using Base::operator=;
  using Base::insert;
  using Base::swap;

  bool empty() const;
  size_t size() const;

  template <typename InputIt>
  void insert(InputIt first, InputIt last);

  void erase(const T& val);
  void clear();

  iterator find(const T& val) const;
  size_t count(const T& val) const;

  iterator begin();
  iterator end();
};
