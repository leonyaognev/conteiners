#pragma once
#include "ListBase.h"

/**
 * @brief FIFO (First-In First-Out) queue container.
 *
 * @tparam T type of elements stored in the queue.
 */
template <typename T>
class queue {
 private:
  ListBase<T> container;

 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using const_reference = const T&;

  /** @brief Default constructor. */
  queue() = default;

  /**
   * @brief Constructs a queue from a range of elements.
   * @tparam InputIt Input iterator type
   * @param first Start of the range
   * @param last End of the range
   */
  template <typename InputIt>
  queue(InputIt first, InputIt last) : container(first, last) {}

  /** @brief Copy constructor. */
  queue(const queue& other) : container(other.container) {}

  /** @brief Move constructor. */
  queue(queue&& other) noexcept : container(std::move(other.container)) {}

  /** @brief Destructor. */
  ~queue() = default;

  /** @brief Copy assignment operator. */
  queue& operator=(const queue& other) {
    container = other.container;
    return *this;
  }

  /** @brief Move assignment operator. */
  queue& operator=(queue&& other) noexcept {
    container = std::move(other.container);
    return *this;
  }

  /**
   * @brief Accesses the first element.
   * @return Reference to the first element.
   */

  reference front() { return container.front(); }
  const_reference front() const { return container.front(); }

  /**
   * @brief Accesses the last element.
   * @return Reference to the last element.
   */
  reference back() { return container.back(); }
  const_reference back() const { return container.back(); }

  /**
   * @brief Checks if the queue is empty.
   * @return true if queue is empty, false otherwise.
   */

  bool empty() const { return container.empty(); }

  /**
   * @brief Returns the number of elements.
   * @return Number of elements in the queue.
   */

  size_type size() const { return container.size(); }

  /**
   * @brief Inserts element at the end.
   * @param value Value to insert.
   */
  void push(const T& value) { container.pushBack(value); }
  void push(T&& value) { container.pushBack(std::move(value)); }

  /**
   * @brief Constructs element in place at the end.
   * @tparam Args Argument types
   * @param args Arguments to forward to constructor
   */
  template <typename... Args>
  void emplace(Args&&... args) {
    container.emplaceBack(std::forward<Args>(args)...);
  }

  /**
   * @brief Removes the first element.
   */
  void pop() { container.popFront(); }

  /**
   * @brief Swaps contents with another queue.
   * @param other Queue to swap with
   */
  void swap(queue& other) noexcept { container.swap(other.container); }
};