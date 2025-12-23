#pragma once

#include <cstddef>
#include <initializer_list>

#include "RedBlackTree/BaseTree.h"
namespace s21 {

/**
 * @brief Container that stores unique elements following a specific order.
 *
 * Implemented as a Red-Black Tree, ensuring logarithmic time complexity
 * for search, insertion, and removal.
 *
 * @tparam T Type of elements stored in the set.
 * @tparam Compare Comparison function object type.
 */
template <typename T, typename Compare = std::less<T>>
class Set : protected RBBase<T, Compare> {
 private:
  using Base = RBBase<T, Compare>;  ///< Base RB-Tree implementation
  using Node = typename Base::Node;

 public:
  using iterator = typename Base::iterator;  ///< Bidirectional iterator

  /** @name Constructors and assignment
   * @brief Inherit and define lifecycle operations.
   */
  ///@{
  using Base::Base;
  Set();

  Set(const Set& other);

  Set(Set&& other) noexcept;

  Set(std::initializer_list<T> ilist);

  template <typename InputIt>
  Set(InputIt first, InputIt last);

  Set& operator=(const Set& other);
  ///@}

  /** @name Iterators
   * @brief Access to the beginning and end of the set.
   */
  ///@{
  using Base::begin;
  using Base::end;
  ///@}

  /** @name Capacity
   * @brief Size-related operations.
   */
  ///@{
  using Base::empty;
  using Base::max_size;
  using Base::size;
  ///@}

  /** @name Modifiers
   * @brief Operations that modify the set content.
   */
  ///@{
  void clear();
  using Base::insert;
  using Base::insert_many;
  void erase(iterator pos);
  void swap(Set& other);
  void merge(Set& other);
  ///@}

  /** @name Lookup
   * @brief Operations to find or count elements.
   */
  ///@{
  using Base::contains;
  iterator find(const T& val) const;
  size_t count(const T& val) const;
  ///@}
};

};  // namespace s21

#include "impl/Set.tpp"
