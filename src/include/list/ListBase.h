#pragma once

#include <cstddef>
#include <utility>

/**
 * @brief Basic doubly linked list with a circular "dummy" node.
 *
 * @tparam T type of elements stored in the list.
 */
template <typename T>
class ListBase {
 private:
  /**
   * @brief Node of the doubly linked list.
   *
   * Each node contains data and pointers to the previous and next elements.
   * The "dummy" node closes the list into a ring.
   */
  class node {
   public:
    T data;      ///< Node data
    node* next;  ///< Pointer to the next node
    node* prev;  ///< Pointer to the previous node

    /** @brief Constructor of the dummy node (points to itself). */
    node();

    /**
     * @brief Constructor with copy initialization.
     * @param value value to initialize node's data.
     */
    node(const T& value);

    /**
     * @brief Constructor with move initialization.
     * @param value value to initialize node's data.
     */
    node(T&& value);
  };

  /**
   * @brief Iterator for traversing list elements.
   *
   * Supports dereference, increment, decrement, and comparison operations.
   */
  class iterator {
   public:
    using valueType = T;   ///< Value type
    using pointer = T*;    ///< Pointer type
    using reference = T&;  ///< Reference type

    node* current;  ///< Pointer to the current node

    /** @brief Default constructor (nullptr). */
    iterator();
    /** @brief Constructor from a node pointer. */
    iterator(node* ptr);
    /** @brief Copy constructor. */
    iterator(const iterator& it);

    /** @brief Dereference operator. */
    reference operator*();
    /** @brief Member access operator. */
    pointer operator->();

    /** @brief Prefix increment. */
    iterator& operator++();
    /** @brief Postfix increment. */
    iterator operator++(int);

    /** @brief Prefix decrement. */
    iterator& operator--();
    /** @brief Postfix decrement. */
    iterator operator--(int);

    /** @brief Equality comparison. */
    bool operator==(const iterator& other) const;
    /** @brief Inequality comparison. */
    bool operator!=(const iterator& other) const;
  };

  node dummy;             ///< Dummy node (closes the list in a ring)
  std::size_t _size = 0;  ///< Number of elements in the list

 protected:
  using iterator_type = iterator;

  /** @brief Default constructor. */
  ListBase();

  /**
   * @brief Constructs a list with a number of identical elements.
   * @param count Number of elements
   * @param value Value to initialize elements
   */
  ListBase(std::size_t count, const T& value);

  /**
   * @brief Constructs a list from a range of elements.
   * @tparam InputIt Input iterator type
   * @param first Start of the range
   * @param last End of the range
   */
  template <typename InputIt>
  ListBase(InputIt first, InputIt last);

  /** @brief Copy constructor. */
  ListBase(const ListBase& other);

  /** @brief Move constructor. */
  ListBase(ListBase&& other) noexcept;

  /** @brief Destructor, clears the list. */
  ~ListBase() noexcept;

  /** @brief Assigns `count` copies of `value` to the list. */
  void assign(std::size_t count, const T& value);

  /** @brief Assigns elements from a range to the list. */
  template <typename InputIt>
  void assign(InputIt first, InputIt last);

  /** @brief Access first element. */
  T& front() noexcept;
  /** @brief Access first element (const). */
  const T& front() const noexcept;

  /** @brief Access last element. */
  T& back() noexcept;
  /** @brief Access last element (const). */
  const T& back() const noexcept;

  /** @brief Inserts a copy of `value` before `pos`. */
  iterator insert(iterator pos, const T& value);

  /**
   * @brief Inserts a moved `value` before `pos`.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  iterator insert(iterator pos, T&& value);

  /**
   * @brief Inserts `count` copies of `value` before `pos`.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  iterator insert(iterator pos, std::size_t count, const T& value);

  /**
   * @brief Inserts a range of elements before `pos`.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  template <typename InputIt>
  iterator insert(iterator pos, InputIt first, InputIt last);

  /**
   * @brief Constructs element(s) in place before `pos`.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  template <typename... Args>
  iterator emplace(iterator pos, Args&&... args);

  /** @brief Erases element at `pos`. */
  iterator erase(iterator pos);

  /** @brief Erases elements in range [first, last). */
  iterator erase(iterator first, iterator last);

  /** @brief Pushes a copy of `value` to the front. */
  void pushFront(const T& value);
  /** @brief Pushes a moved `value` to the front. */
  void pushFront(T&& value);

  /**
   * @brief Pushes a copy of `value` to the back.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  void pushBack(const T& value);
  /**
   * @brief Pushes a moved `value` to the back.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  void pushBack(T&& value);

  /**
   * @brief Constructs element(s) in place at the front. */
  template <typename... Args>
  void emplaceFront(Args&&... args);

  /**
   * @brief Constructs element(s) in place at the back.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  template <typename... Args>
  void emplaceBack(Args&&... args);

  /** @brief Removes the first element. */
  void popFront();
  /** @brief Removes the last element. */
  void popBack();
  /** @brief Resizes the list to contain `count` default elements. */
  void resize(std::size_t count);
  /**
   * @brief Resizes the list to contain `count` copies of `value`.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  void resize(std::size_t count, const T& value);

  /** @brief Swaps contents with `other`. */
  void swap(ListBase& other) noexcept;

  /** @brief Merges sorted list `other` into this list. */
  void merge(ListBase& other);

  /** @brief Merges sorted list `other` using custom comparator. */
  template <typename Compare>
  void merge(ListBase& other, Compare comp);

  /** @brief Moves all elements from `other` before `pos`. */
  void splice(iterator pos, ListBase& other);

  /** @brief Moves single element from `other` before `pos`. */
  void splice(iterator pos, ListBase& other, iterator it);

  /** @brief Moves range [first, last) from `other` before `pos`. */
  template <typename InputIt>
  void splice(iterator pos, ListBase& other, InputIt first, InputIt last);

  /** @brief Removes elements equal to `value`. */
  void remove(const T& value);

  /** @brief Removes elements matching predicate `p`. */
  template <typename BinaryPredicate>
  void remove(BinaryPredicate p);

  /** @brief Removes consecutive duplicates. */
  void unique();

  /** @brief Removes consecutive duplicates matching predicate `p`. */
  template <typename BinaryPredicate>
  void unique(BinaryPredicate p);

  /** @brief Sorts the list. */
  void sort();

  /** @brief Sorts the list using comparator `comp`. */
  template <typename Compare>
  void sort(Compare comp);

  /** @brief Iterator to the beginning. */
  iterator begin() noexcept;
  /** @brief Iterator to the end (dummy node). */
  iterator end() noexcept;
  /** @brief Reverse iterator to the last element. */
  iterator rbegin() noexcept;
  /** @brief Reverse iterator to dummy node (rend). */
  iterator rend() noexcept;

  /** @brief Returns number of elements. */
  std::size_t size() const noexcept;
  /** @brief Clears the list. */
  void clear() noexcept;
  /** @brief Checks if list is empty. */
  bool empty() const noexcept;

  /**
   * @brief Copy assignment operator.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  ListBase& operator=(const ListBase& other);
  /** @brief Move assignment operator. */
  ListBase& operator=(ListBase&& other) noexcept;
};

#include "impl/BaseList.tpp"
