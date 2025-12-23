#pragma once

#include "RedBlackTree/Set.h"

template <typename T, typename Compare>
Set<T, Compare>::Set() : Base() {}

template <typename T, typename Compare>
Set<T, Compare>::Set(const Set& other) : Base(other) {}

template <typename T, typename Compare>
Set<T, Compare>::Set(Set&& other) noexcept : Base(std::move(other)) {}

template <typename T, typename Compare>
Set<T, Compare>::Set(std::initializer_list<T> ilist) : Base(ilist) {}

template <typename T, typename Compare>
template <typename InputIt>
Set<T, Compare>::Set(InputIt first, InputIt last) : Base(first, last) {}

template <typename T, typename Compare>
Set<T, Compare>& Set<T, Compare>::operator=(const Set& other) {
  Base::operator=(other);
  return *this;
}

template <typename T, typename Compare>
void Set<T, Compare>::erase(iterator pos) {
  Base::erase(pos);
}

template <typename T, typename Compare>
void Set<T, Compare>::clear() {
  Base::clearTree(this->root);
  this->root = this->nil;
  this->tree_size = 0;
}

template <typename T, typename Compare>
typename Set<T, Compare>::iterator Set<T, Compare>::find(const T& val) const {
  return iterator(this, Base::find(val));
}

template <typename T, typename Compare>
size_t Set<T, Compare>::count(const T& val) const {
  return find(val) != end() ? 1 : 0;
}

template <typename T, typename Compare>
void Set<T, Compare>::swap(Set& other) {
  Base::swap(other);
}

template <typename T, typename Compare>
void Set<T, Compare>::merge(Set& other) {
  Base::merge(other);
}
