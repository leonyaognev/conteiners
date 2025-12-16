#pragma once

#include "RedBlackTree/Set.h"

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
