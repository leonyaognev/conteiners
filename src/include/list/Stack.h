#pragma once
#include "ListBase.h"

/**
 * @brief LIFO (Last-In First-Out) stack container.
 *
 * @tparam T type of elements stored in the stack.
 */

template <typename T>
class stack {
 private:
  ListBase<T> container;

 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using const_reference = const T&;

  /** @brief Default constructor. */
  stack() = default;

  /**
   * @brief Constructs a stack from a range of elements.
   * @tparam InputIt Input iterator type
   * @param first Start of the range
   * @param last End of the range
   */

  template <typename InputIt>
  stack(InputIt first, InputIt last) : container(first, last) {}

  /** @brief Copy constructor. */
  stack(const stack& other) : container(other.container) {}

  /** @brief Move constructor. */
  stack(stack&& other) noexcept : container(std::move(other.container)) {}

  /** @brief Destructor. */
  ~stack() = default;

  /** @brief Copy assignment operator. */

  stack& operator=(const stack& other) {
    container = other.container;
    return *this;
  }

  /** @brief Move assignment operator. */
  stack& operator=(stack&& other) noexcept {
    container = std::move(other.container);
    return *this;
  }

  /**
   * @brief Accesses the top element.
   * @return Reference to the top element.
   */
  reference top() { return container.back(); }
  const_reference top() const { return container.back(); }

  /**
   * @brief Checks if the stack is empty.
   * @return true if stack is empty, false otherwise.
   */
  bool empty() const { return container.empty(); }

  /**
   * @brief Returns the number of elements.
   * @return Number of elements in the stack.
   */

  size_type size() const { return container.size(); }

  /**
   * @brief Inserts element at the top.
   * @param value Value to insert.
   */
  void push(const T& value) { container.pushBack(value); }
  void push(T&& value) { container.pushBack(std::move(value)); }

  /**
   * @brief Constructs element in place at the top.
   * @tparam Args Argument types
   * @param args Arguments to forward to constructor
   */
  template <typename... Args>
  void emplace(Args&&... args) {
    container.emplaceBack(std::forward<Args>(args)...);
  }

  /**
   * @brief Removes the top element.
   */
  void pop() { container.popBack(); }

  /**
   * @brief Swaps contents with another stack.
   * @param other Stack to swap with
   */
  void swap(stack& other) noexcept { container.swap(other.container); }
};