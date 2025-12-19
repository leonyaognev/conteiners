#pragma once

#include <stdexcept>
#include <utility>

#include "RedBlackTree/BaseTree.h"
#include "helpers.h"

template <typename Key, typename T, typename Compare = std::less<Key>>
class Map : public RBBase<Pair<const Key, T>, MapKeyCompare<Key, T, Compare>> {
 public:
  using value_type = Pair<const Key, T>;

 private:
  using Base = RBBase<value_type, MapKeyCompare<Key, T, Compare>>;
  using Node = typename Base::Node;

 public:
  using iterator = typename Base::iterator;
  using size_type = typename Base::size_type;

  Map();
  Map(const Map& other);
  Map(Map&& other) noexcept;
  Map(std::initializer_list<value_type> ilist);

  template <typename InputIt>
  Map(InputIt first, InputIt last);

  Map& operator=(const Map& other);

  T& operator[](const Key& key);
  T& operator[](Key&& key);

  T& at(const Key& key);
  const T& at(const Key& key) const;

  using Base::begin;
  using Base::empty;
  using Base::end;
  using Base::insert;
  using Base::insert_many;
  using Base::max_size;
  using Base::merge;
  using Base::size;
  using Base::swap;

  Pair<iterator, bool> insert(const Key& key, const T& obj);

  template <typename M>
  Pair<iterator, bool> insert_or_assign(const Key& key, M&& obj);

  void swap(Map& other);
  void merge(Map& other);

  iterator find(const Key& key);
  iterator find(const Key& key) const;

  bool contains(const Key& key) const;

  void erase(iterator pos);

  void erase(const Key& key);

  void clear();
};

#include "impl/Map.tpp"
