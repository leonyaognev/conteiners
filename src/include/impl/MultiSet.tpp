#pragma once

#include "RedBlackTree/MultiSet.h"
#include "array/Vector.h"

namespace s21 {

template <typename T, typename Compare>
MultiSet<T, Compare>::MultiSet() : Base() {}

template <typename T, typename Compare>
MultiSet<T, Compare>::MultiSet(const MultiSet& other) : Base(other) {}

template <typename T, typename Compare>
MultiSet<T, Compare>::MultiSet(MultiSet&& other) noexcept
    : Base(std::move(other)) {}

template <typename T, typename Compare>
MultiSet<T, Compare>::MultiSet(std::initializer_list<value_type> ilist)
    : Base() {
  for (const auto& item : ilist) {
    insert(item);
  }
}

template <typename T, typename Compare>
template <typename InputIt>
MultiSet<T, Compare>::MultiSet(InputIt first, InputIt last) : Base() {
  for (auto it = first; it != last; ++it) {
    insert(*it);
  }
}

template <typename T, typename Compare>
MultiSet<T, Compare>::~MultiSet() {
  clear();
}

template <typename T, typename Compare>
MultiSet<T, Compare>& MultiSet<T, Compare>::operator=(const MultiSet& other) {
  if (this != &other) {
    Base::operator=(other);
  }
  return *this;
}

template <typename T, typename Compare>
MultiSet<T, Compare>& MultiSet<T, Compare>::operator=(
    MultiSet&& other) noexcept {
  if (this != &other) {
    clear();
    this->swap(other);
  }
  return *this;
}

template <typename T, typename Compare>
template <typename ValT>
typename MultiSet<T, Compare>::iterator MultiSet<T, Compare>::insert_impl(
    ValT&& value) {
  Node* z = new Node(std::forward<ValT>(value));
  Node* y = this->nil;
  Node* x = this->root;

  while (x != this->nil) {
    y = x;

    if (this->comp(z->value, x->value)) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;
  if (y == this->nil) {
    this->root = z;
  } else if (this->comp(z->value, y->value)) {
    y->left = z;
  } else {
    y->right = z;
  }

  z->left = z->right = this->nil;
  z->color = Base::Red;

  this->fixTree(z);
  this->tree_size++;
  return iterator(this, z);
}

template <typename T, typename Compare>
typename MultiSet<T, Compare>::iterator MultiSet<T, Compare>::insert(
    const value_type& value) {
  return insert_impl(value);
}

template <typename T, typename Compare>
typename MultiSet<T, Compare>::iterator MultiSet<T, Compare>::insert(
    value_type&& value) {
  return insert_impl(std::move(value));
}

template <typename T, typename Compare>
void MultiSet<T, Compare>::insert(std::initializer_list<value_type> ilist) {
  for (const auto& item : ilist) insert(item);
}

template <typename T, typename Compare>
template <typename InputIt>
void MultiSet<T, Compare>::insert(InputIt first, InputIt last) {
  for (auto it = first; it != last; ++it) insert(*it);
}

template <typename T, typename Compare>
template <typename... Args>
Vector<Pair<typename MultiSet<T, Compare>::iterator, bool>>
MultiSet<T, Compare>::insert_many(Args&&... args) {
  Vector<Pair<iterator, bool>> results;
  results.reserve(sizeof...(args));
  (results.push_back({insert(std::forward<Args>(args)), true}), ...);
  return results;
}

template <typename T, typename Compare>
void MultiSet<T, Compare>::clear() {
  this->clearTree(this->root);
  this->root = this->nil;
  this->tree_size = 0;
}

template <typename T, typename Compare>
void MultiSet<T, Compare>::erase(iterator pos) {
  this->Base::erase(pos);
}

template <typename T, typename Compare>
void MultiSet<T, Compare>::erase(iterator first, iterator last) {
  while (first != last) {
    iterator tmp = first;
    ++first;
    erase(tmp);
  }
}

template <typename T, typename Compare>
typename MultiSet<T, Compare>::size_type MultiSet<T, Compare>::erase(
    const key_type& key) {
  size_type count = 0;
  iterator it = lower_bound(key);
  iterator last = upper_bound(key);

  while (it != last) {
    iterator tmp = it;
    ++it;

    Node* node = this->Base::find(*tmp);
    if (node != this->nil) {
      this->Base::erase(node);
      count++;
    }
  }
  return count;
}

template <typename T, typename Compare>
void MultiSet<T, Compare>::swap(MultiSet& other) {
  Base::swap(other);
}

template <typename T, typename Compare>
void MultiSet<T, Compare>::merge(MultiSet& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}

template <typename T, typename Compare>
typename MultiSet<T, Compare>::size_type MultiSet<T, Compare>::count(
    const key_type& key) const {
  size_type c = 0;

  auto range = equal_range(key);
  for (auto it = range.first; it != range.second; ++it) {
    c++;
  }
  return c;
}

template <typename T, typename Compare>
typename MultiSet<T, Compare>::iterator MultiSet<T, Compare>::find(
    const key_type& key) const {
  Node* result = this->Base::find(key);
  return iterator(this, result);
}

template <typename T, typename Compare>
bool MultiSet<T, Compare>::contains(const key_type& key) const {
  return this->Base::contains(key);
}

template <typename T, typename Compare>
typename MultiSet<T, Compare>::iterator MultiSet<T, Compare>::lower_bound(
    const key_type& key) const {
  Node* x = this->root;
  Node* y = this->nil;

  while (x != this->nil) {
    if (!this->comp(x->value, key)) {
      y = x;
      x = x->left;
    } else {
      x = x->right;
    }
  }
  return iterator(this, y);
}

template <typename T, typename Compare>
typename MultiSet<T, Compare>::iterator MultiSet<T, Compare>::upper_bound(
    const key_type& key) const {
  Node* x = this->root;
  Node* y = this->nil;

  while (x != this->nil) {
    if (this->comp(key, x->value)) {
      y = x;
      x = x->left;
    } else {
      x = x->right;
    }
  }
  return iterator(this, y);
}

template <typename T, typename Compare>
Pair<typename MultiSet<T, Compare>::iterator,
     typename MultiSet<T, Compare>::iterator>
MultiSet<T, Compare>::equal_range(const key_type& key) const {
  return Pair<typename MultiSet<T, Compare>::iterator,
              typename MultiSet<T, Compare>::iterator>(lower_bound(key),
                                                       upper_bound(key));
}

};  // namespace s21
