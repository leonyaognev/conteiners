#pragma once

#include <cstddef>
#include <initializer_list>

#include "RedBlackTree/BaseTree.h"
#include "array/Vector.h"

namespace s21 {

template <typename T, typename Compare = std::less<T>>
class MultiSet : protected RBBase<T, Compare> {
 private:
  using Base = RBBase<T, Compare>;
  using Node = typename Base::Node;

 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Base::iterator;
  using const_iterator = typename Base::iterator;
  using size_type = std::size_t;

  MultiSet();
  MultiSet(const MultiSet& other);
  MultiSet(MultiSet&& other) noexcept;
  MultiSet(std::initializer_list<value_type> ilist);

  template <typename InputIt>
  MultiSet(InputIt first, InputIt last);

  ~MultiSet();

  MultiSet& operator=(const MultiSet& other);
  MultiSet& operator=(MultiSet&& other) noexcept;

  using Base::begin;
  using Base::end;

  using Base::empty;
  using Base::max_size;
  using Base::size;

  void clear();

  iterator insert(const value_type& value);
  iterator insert(value_type&& value);
  void insert(std::initializer_list<value_type> ilist);

  template <typename InputIt>
  void insert(InputIt first, InputIt last);

  template <typename... Args>
  Vector<Pair<iterator, bool>> insert_many(Args&&... args);

  void erase(iterator pos);
  void erase(iterator first, iterator last);
  size_type erase(const key_type& key);

  void swap(MultiSet& other);
  void merge(MultiSet& other);

  size_type count(const key_type& key) const;
  iterator find(const key_type& key) const;
  bool contains(const key_type& key) const;

  Pair<iterator, iterator> equal_range(const key_type& key) const;
  iterator lower_bound(const key_type& key) const;
  iterator upper_bound(const key_type& key) const;

  using Base::displayTree;

 private:
  template <typename ValT>
  iterator insert_impl(ValT&& value);

  Node* get_node_from_iter(iterator it) const;
};

}  // namespace s21

#include "impl/MultiSet.tpp"
