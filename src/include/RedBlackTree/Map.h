#pragma once

#include "RedBlackTree/BaseTree.h"
#include "helpers.h"

namespace s21 {

/**
 * @brief Associative container that stores elements formed by a combination of
 * a unique key and a mapped value.
 *
 * Implemented as a Red-Black Tree for logarithmic time complexity for search,
 * insertion, and removal.
 *
 * @tparam Key Type of the keys.
 * @tparam T Type of the mapped values.
 * @tparam Compare Comparison function object type for keys.
 */
template <typename Key, typename T, typename Compare = std::less<Key>>
class Map
    : protected RBBase<Pair<const Key, T>, MapKeyCompare<Key, T, Compare>> {
 public:
  using value_type = Pair<const Key, T>;  ///< Element type (key-value pair)

 private:
  using Base =
      RBBase<value_type,
             MapKeyCompare<Key, T, Compare>>;  ///< Base RB-Tree implementation
  using Node = typename Base::Node;

 public:
  using iterator = typename Base::iterator;    ///< Bidirectional iterator
  using size_type = typename Base::size_type;  ///< Size type
  using key_type = Key;
  using mapped_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using const_iterator = const iterator;

  /** @name Constructors and assignment
   * @brief Standard lifecycle operations.
   */
  ///@{
  Map();
  Map(const Map& other);
  Map(Map&& other) noexcept;
  Map(std::initializer_list<value_type> ilist);

  template <typename InputIt>
  Map(InputIt first, InputIt last);

  Map& operator=(const Map& other);
  ///@}

  /** @name Element access
   * @brief Access or modify elements by key.
   */
  ///@{
  T& operator[](const Key& key);
  T& operator[](Key&& key);

  T& at(const Key& key);
  const T& at(const Key& key) const;
  ///@}

  /** @name Iterators
   * @brief Points to the elements within the map.
   */
  ///@{
  using Base::begin;
  using Base::end;
  ///@}

  /** @name Capacity
   * @brief Information about the container size.
   */
  ///@{
  using Base::empty;
  using Base::max_size;
  using Base::size;
  ///@}

  /** @name Modifiers
   * @brief Operations that change the map's content.
   */
  ///@{
  void clear();
  using Base::insert;
  Pair<iterator, bool> insert(const Key& key, const T& obj);

  template <typename M>
  Pair<iterator, bool> insert_or_assign(const Key& key, M&& obj);

  template <typename... Args>
  auto insert_many(Args&&... args) {
    return Base::insert_many(std::forward<Args>(args)...);
  }

  void erase(iterator pos);
  void erase(const Key& key);

  void swap(Map& other);
  void merge(Map& other);
  ///@}

  /** @name Lookup
   * @brief Search operations for specific keys.
   */
  ///@{
  iterator find(const Key& key);
  iterator find(const Key& key) const;

  bool contains(const Key& key) const;
  ///@}
};

}  // namespace s21

#include "impl/Map.tpp"
