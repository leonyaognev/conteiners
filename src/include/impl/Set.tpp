#pragma once

#include "RedBlackTree/Set.h"

template <typename T, typename Compare>
typename Set<T, Compare>::iterator Set<T, Compare>::erase(iterator pos) {
  return Base::erase(Base::find(*pos));
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
