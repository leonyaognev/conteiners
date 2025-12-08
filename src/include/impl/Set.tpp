#pragma once

#include "RedBlackTree/Set.h"

template <typename T, typename Compare>
bool Set<T, Compare>::empty() const {
  return this->tree_size == 0;
}

template <typename T, typename Compare>
size_t Set<T, Compare>::size() const {
  return this->tree_size;
}

template <typename T, typename Compare>
template <typename InputIt>
void Set<T, Compare>::insert(InputIt first, InputIt last) {
  for (auto it = first; it != last; ++it) insert(*it);
}

template <typename T, typename Compare>
void Set<T, Compare>::erase(const T& val) {
  Base::erase(Base::find(val));
}

template <typename T, typename Compare>
void Set<T, Compare>::clear() {
  Base::clearTree(this->root);
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
typename Set<T, Compare>::iterator Set<T, Compare>::begin() {
  return iterator(this->root);
}

template <typename T, typename Compare>
typename Set<T, Compare>::iterator Set<T, Compare>::end() {
  return iterator(this->nil);
}
