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
  using Base::operator=;
  using Base::begin;
  using Base::empty;
  using Base::end;
  using Base::erase;
  using Base::insert;
  using Base::insert_many;
  using Base::merge;
  using Base::size;
  using Base::swap;

  void erase(const T& val);
  void clear();

  iterator find(const T& val) const;
  size_t count(const T& val) const;
};

#include "impl/Set.tpp"
