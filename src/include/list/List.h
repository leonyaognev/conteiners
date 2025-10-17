#pragma once
#include "ListBase.h"

/**
 * @brief Doubly linked list container.
 *
 * STL-like bidirectional list implemented as a doubly linked structure with a
 * dummy node. Provides constant-time insertion and removal anywhere in the
 * list.
 *
 * @tparam T Type of elements stored in the list.
 *
 * @note All core functionality (constructors, modifiers, iterators, etc.)
 *       is inherited from the internal base class ListBase<T>.
 */
template <typename T>
class list : protected ListBase<T> {
 public:
  using Base = ListBase<T>;          ///< Base implementation of the list
  using value_type = T;              ///< Element type
  using size_type = std::size_t;     ///< Size type
  using reference = T&;              ///< Reference to element
  using const_reference = const T&;  ///< Constant reference to element
  using iterator = typename Base::iterator_type;  ///< Iterator type

  /** @name Constructors and assignment
   *  @brief Inherit all constructors and assignment operators from ListBase.
   */
  ///@{
  using Base::Base;       ///< Inherit all constructors
  using Base::operator=;  ///< Inherit assignment operators
  ///@}

  /** @name Element access
   *  @brief Provides access to list elements.
   */
  ///@{
  using Base::back;   ///< Access last element
  using Base::front;  ///< Access first element
  ///@}

  /** @name Iterators
   *  @brief Standard bidirectional iterators.
   */
  ///@{
  using Base::begin;
  using Base::end;
  using Base::rbegin;
  using Base::rend;
  ///@}

  /** @name Capacity
   *  @brief Size-related operations.
   */
  ///@{
  using Base::empty;
  using Base::size;
  ///@}

  /** @name Modifiers
   *  @brief Operations that modify the contents of the list.
   */
  ///@{
  using Base::assign;
  using Base::clear;
  using Base::emplace;
  using Base::emplaceBack;
  using Base::emplaceFront;
  using Base::erase;
  using Base::insert;
  using Base::popBack;
  using Base::popFront;
  using Base::pushBack;
  using Base::pushFront;
  using Base::resize;
  using Base::swap;
  ///@}

  /** @name Operations
   *  @brief List-specific algorithms.
   */
  ///@{
  using Base::merge;
  using Base::remove;
  using Base::sort;
  using Base::splice;
  using Base::unique;
  ///@}
};
