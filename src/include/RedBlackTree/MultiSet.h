#pragma once

#include <cstddef>
#include <initializer_list>

#include "RedBlackTree/BaseTree.h"
#include "array/Vector.h"

namespace s21 {

/**
 * @brief Associative container that contains a sorted set of objects of type T.
 *
 * Unlike Set, MultiSet allows multiple elements to have equivalent values.
 * Implemented as a Red-Black Tree for logarithmic time complexity.
 *
 * @tparam T Type of elements stored in the multiset.
 * @tparam Compare Comparison function object type.
 */
template <typename T, typename Compare = std::less<T>>
class MultiSet : protected RBBase<T, Compare> {
 private:
  using Base = RBBase<T, Compare>;  ///< Base RB-Tree implementation
  using Node = typename Base::Node;

 public:
  using key_type = T;                         ///< Key type
  using value_type = T;                       ///< Value type
  using reference = value_type&;              ///< Reference to value
  using const_reference = const value_type&;  ///< Const reference to value
  using iterator = typename Base::iterator;   ///< Bidirectional iterator
  using const_iterator =
      typename Base::iterator;    ///< Constant bidirectional iterator
  using size_type = std::size_t;  ///< Size type

  /** @name Constructors and destructor
   * @brief Lifecycle management operations.
   */
  ///@{
  MultiSet();
  MultiSet(const MultiSet& other);
  MultiSet(MultiSet&& other) noexcept;
  MultiSet(std::initializer_list<value_type> ilist);

  template <typename InputIt>
  MultiSet(InputIt first, InputIt last);

  ~MultiSet();
  ///@}

  /** @name Assignment operators
   * @brief Copy and move assignment logic.
   */
  ///@{
  MultiSet& operator=(const MultiSet& other);
  MultiSet& operator=(MultiSet&& other) noexcept;
  ///@}

  /** @name Iterators
   * @brief Standard bidirectional iterators.
   */
  ///@{
  using Base::begin;
  using Base::end;
  ///@}

  /** @name Capacity
   * @brief Size and emptiness checks.
   */
  ///@{
  using Base::empty;
  using Base::max_size;
  using Base::size;
  ///@}

  /** @name Modifiers
   * @brief Operations that alter the multiset.
   */
  ///@{
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
  ///@}

  /** @name Lookup
   * @brief Search and range operations.
   */
  ///@{
  size_type count(const key_type& key) const;
  iterator find(const key_type& key) const;
  bool contains(const key_type& key) const;

  Pair<iterator, iterator> equal_range(const key_type& key) const;
  iterator lower_bound(const key_type& key) const;
  iterator upper_bound(const key_type& key) const;
  ///@}

  /** @name Debug
   * @brief Visualization utilities.
   */
  ///@{
  using Base::displayTree;
  ///@}

 private:
  template <typename ValT>
  iterator insert_impl(ValT&& value);

  Node* get_node_from_iter(iterator it) const;
};

}  // namespace s21

#include "impl/MultiSet.tpp"
