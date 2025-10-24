#pragma once

#include "ListBase.h"

/**
 * @brief LIFO (Last-In First-Out) stack container.
 *
 * Adapter over ListBase implemented via protected inheritance.
 * Exposes a minimal stack interface: push/emplace at the top, pop from the
 * top, top access, size/empty and swap. Internals (nodes, iterators, etc.)
 * remain hidden.
 *
 * @tparam T Type of elements stored in the stack.
 */
template <typename T>
class Stack : protected ListBase<T> {
 private:
  using Base = ListBase<T>;  ///< Base implementation of the list

 public:
  using value_type = T;              ///< Element type
  using size_type = std::size_t;     ///< Size type
  using reference = T&;              ///< Reference to element
  using const_reference = const T&;  ///< Constant reference to element

  /** @name Constructors and assignment
   *  @brief Standard constructors and assignment operators.
   */
  ///@{
  Stack() = default;
  Stack(const Stack& other) : Base(other) {}
  Stack(Stack&& other) noexcept : Base(std::move(other)) {}
  using Base::operator=;  ///< Inherit assignment operators
  ///@}

  /** @name Element access
   *  @brief Provides access to stack elements.
   */
  ///@{
  reference top() { return Base::back(); }  ///< Access the top element
  const_reference top() const {
    return Base::back();
  }  ///< Access the top element (const)
  ///@}

  /** @name Capacity
   *  @brief Size-related operations.
   */
  ///@{
  using Base::empty;
  using Base::size;
  ///@}

  /** @name Modifiers
   *  @brief Operations that modify the contents of the stack.
   */
  ///@{
  using Base::swap;

  void push(const T& value) { Base::pushBack(value); }
  void push(T&& value) { Base::pushBack(std::move(value)); }

  template <typename... Args>
  void emplace(Args&&... args) {
    Base::emplaceBack(std::forward<Args>(args)...);
  }

  void pop() { Base::popBack(); }
  ///@}
};