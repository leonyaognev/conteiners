#pragma once
#include "ListBase.h"

/**
 * @brief Doubly linked list container.
 *
 * @tparam T type of elements stored in the list.
 */
template <typename T>
class list : public ListBase<T> {
 public:
  using Base = ListBase<T>;
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using const_reference = const T&;
  using iterator = typename Base::iterator_type;

  /** @brief Default constructor. */
  list() : Base() {}

  /**
   * @brief Constructs a list with a number of identical elements.
   * @param count Number of elements
   * @param value Value to initialize elements
   */

  list(size_type count, const T& value) : Base(count, value) {}

  /**
   * @brief Constructs a list from a range of elements.
   * @tparam InputIt Input iterator type
   * @param first Start of the range
   * @param last End of the range
   */

  template <typename InputIt>
  list(InputIt first, InputIt last) : Base(first, last) {}

  /** @brief Copy constructor. */
  list(const list& other) : Base(other) {}

  /** @brief Move constructor. */
  list(list&& other) noexcept : Base(std::move(other)) {}

  /** @brief Destructor. */
  ~list() = default;

  /** @brief Copy assignment operator. */
  list& operator=(const list& other) {
    Base::operator=(other);
    return *this;
  }

  /** @brief Move assignment operator. */
  list& operator=(list&& other) noexcept {
    Base::operator=(std::move(other));
    return *this;
  }
};