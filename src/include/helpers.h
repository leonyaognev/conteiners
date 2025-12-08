#pragma once

/**
 * @brief Template class for a pair of values.
 *
 * Used for storing two related values, e.g., key-value pairs in a map.
 *
 * @tparam T1 Type of the first element.
 * @tparam T2 Type of the second element.
 */
template <typename T1, typename T2>
class Pair {
 public:
  T1 first;   ///< First element of the pair
  T2 second;  ///< Second element of the pair

  /**
   * @brief Default constructor.
   * Initializes both elements with default values.
   */
  Pair() : first(), second() {}

  /**
   * @brief Constructor with initialization.
   * @param a Value for the first element.
   * @param b Value for the second element.
   */
  Pair(const T1& a, const T2& b) : first(a), second(b) {}

  /** @brief Copy constructor. */
  Pair(const Pair& other) : first(other.first), second(other.second) {}
};
