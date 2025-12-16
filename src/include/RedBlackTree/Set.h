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
  Set() : Base() {}
  Set(const Set& other) : Base(other) {}
  Set(Set&& other) noexcept : Base(std::move(other)) {}
  Set(std::initializer_list<T> ilist) : Base(ilist) {}
  template <typename InputIt>
  Set(InputIt first, InputIt last) : Base(first, last) {}
  Set& operator=(const Set& other) {
    Base::operator=(other);
    return *this;
  }

  using Base::operator=;
  using Base::begin;
  using Base::empty;
  using Base::end;
  using Base::insert;
  using Base::insert_many;
  using Base::merge;
  using Base::size;
  using Base::swap;

  iterator erase(iterator pos);
  void clear();

  iterator find(const T& val) const;
  size_t count(const T& val) const;

  Node* rooter() { return this->root; }
  Node* niller() { return this->nil; }
};

#include "impl/Set.tpp"
