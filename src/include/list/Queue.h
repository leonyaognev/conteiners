#pragma once

#include "ListBase.h"

/**
 * @brief FIFO (First-In First-Out) queue container.
 *
 * Adapter over ListBase implemented via protected inheritance.
 * Exposes a minimal queue interface: push/emplace at the back, pop from the
 * front, front/back access, size/empty and swap. Internals (nodes, iterators,
 * etc.) remain hidden in the base class.
 *
 * @tparam T Type of elements stored in the queue.
 */
template <typename T>
class Queue : protected ListBase<T> {
 private:
  using Base = ListBase<T>;  ///< Base implementation of the list

 public:
  using value_type = T;              ///< Element type
  using size_type = std::size_t;     ///< Size type
  using reference = T&;              ///< Reference to element
  using const_reference = const T&;  ///< Constant reference to element

  /**
   * @name Constructors and assignment
   * @brief Inherit all constructors and assignment operators from ListBase.
   */
  ///@{
  Queue() = default;
  Queue(const Queue& other) : Base(other) {}
  Queue(Queue&& other) noexcept : Base(std::move(other)) {}

  using Base::operator=;  ///< Inherit assignment operators
  ///@}

  /**
   * @name Element access
   * @brief Provides access to elements.
   */
  ///@{
  using Base::back;   ///< Access last element
  using Base::front;  ///< Access first element
  ///@}

  /**
   * @name Capacity
   * @brief Size-related operations.
   */
  ///@{
  using Base::empty;
  using Base::size;
  ///@}

  /**
   * @name Modifiers
   * @brief Operations that modify the contents of the container
   */
  ///@{
  using Base::swap;

  void push(const T& value) { Base::pushBack(value); }
  void push(T&& value) { Base::pushBack(std::move(value)); }

  template <typename... Args>
  void emplace(Args&&... args) {
    Base::emplaceBack(std::forward<Args>(args)...);
  }

  void pop() { Base::popFront(); }
  ///@}
};