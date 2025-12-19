#pragma once

#include "RedBlackTree/Map.h"

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map() : Base() {}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map(const Map& other) : Base(other) {}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map(Map&& other) noexcept : Base(std::move(other)) {}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map(std::initializer_list<value_type> ilist)
    : Base(ilist) {}

template <typename Key, typename T, typename Compare>
template <typename InputIt>
Map<Key, T, Compare>::Map(InputIt first, InputIt last) : Base(first, last) {}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>& Map<Key, T, Compare>::operator=(const Map& other) {
  Base::operator=(other);
  return *this;
}

template <typename Key, typename T, typename Compare>
T& Map<Key, T, Compare>::at(const Key& key) {
  iterator it = find(key);
  if (it == end()) {
    throw std::out_of_range("Map::at: key not found");
  }
  return (*it).second;
}

template <typename Key, typename T, typename Compare>
const T& Map<Key, T, Compare>::at(const Key& key) const {
  iterator it = find(key);
  if (it == end()) {
    throw std::out_of_range("Map::at: key not found");
  }
  return (*it).second;
}

template <typename Key, typename T, typename Compare>
T& Map<Key, T, Compare>::operator[](const Key& key) {
  iterator it = find(key);
  if (it != end()) {
    return (*it).second;
  }
  auto res = Base::insert(value_type(key, T()));
  return (*(res.first)).second;
}

template <typename Key, typename T, typename Compare>
T& Map<Key, T, Compare>::operator[](Key&& key) {
  iterator it = find(key);
  if (it != end()) {
    return (*it).second;
  }
  auto res = Base::insert(value_type(std::move(key), T()));
  return (*(res.first)).second;
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::find(
    const Key& key) {
  Node* node = Base::find(value_type(key, T()));
  return iterator(this, node);
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::find(
    const Key& key) const {
  Node* node = Base::find(value_type(key, T()));
  return iterator(this, node);
}

template <typename Key, typename T, typename Compare>
bool Map<Key, T, Compare>::contains(const Key& key) const {
  return Base::find(value_type(key, T())) != this->nil;
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::erase(iterator pos) {
  if (pos == end()) return;
  Base::erase(Base::find(*pos));
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::erase(const Key& key) {
  Node* node = Base::find(value_type(key, T()));
  if (node) {
    Base::erase(node);
  }
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::swap(Map& other) {
  Base::swap(other);
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::merge(Map& other) {
  Base::merge(other);
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::clear() {
  Base::clearTree(this->root);
  this->root = this->nil;
  this->tree_size = 0;
}

template <typename Key, typename T, typename Compare>
Pair<typename Map<Key, T, Compare>::iterator, bool>
Map<Key, T, Compare>::insert(const Key& key, const T& obj) {
  return Base::insert(value_type(key, obj));
}

template <typename Key, typename T, typename Compare>
template <typename M>
Pair<typename Map<Key, T, Compare>::iterator, bool>
Map<Key, T, Compare>::insert_or_assign(const Key& key, M&& obj) {
  iterator it = find(key);

  if (it != end()) {
    (*it).second = std::forward<M>(obj);
    return {it, false};
  } else {
    auto res = Base::insert(value_type(key, std::forward<M>(obj)));
    return {res.first, true};
  }
}
