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
    node() : next(this), prev(this) {}

    /**
     * @brief Constructor with copy initialization.
     * @param value value to initialize node's data.
     */
    node(const T& value) : data(value) {}

    /**
     * @brief Constructor with move initialization.
     * @param value value to initialize node's data.
     */
    node(T&& value) : data(std::move(value)) {}
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
    iterator() : current(nullptr) {}
    /** @brief Constructor from a node pointer. */
    iterator(node* ptr) : current(ptr) {}
    /** @brief Copy constructor. */
    iterator(const iterator& it) : current(it.current) {}

    /** @brief Dereference operator. */
    reference operator*() const { return current->data; }
    /** @brief Member access operator. */
    pointer operator->() const { return &current->data; }

    /** @brief Prefix increment. */
    iterator& operator++() {
      current = current->next;
      return *this;
    }
    /** @brief Postfix increment. */
    iterator operator++(int) {
      iterator tmp = *this;
      current = current->next;
      return tmp;
    }

    /** @brief Prefix decrement. */
    iterator& operator--() {
      current = current->prev;
      return *this;
    }
    /** @brief Postfix decrement. */
    iterator operator--(int) {
      iterator tmp = *this;
      current = current->prev;
      return tmp;
    }

    /** @brief Equality comparison. */
    bool operator==(const iterator& other) const {
      return current == other.current;
    }
    /** @brief Inequality comparison. */
    bool operator!=(const iterator& other) const {
      return current != other.current;
    }
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
  ~ListBase() noexcept { clear(); }

  /** @brief Assigns `count` copies of `value` to the list. */
  void assign(std::size_t count, const T& value);

  /** @brief Assigns elements from a range to the list. */
  template <typename InputIt>
  void assign(InputIt first, InputIt last);

  /** @brief Access first element. */
  T& front() noexcept { return dummy.next->data; }
  /** @brief Access first element (const). */
  const T& front() const noexcept { return dummy.next->data; }

  /** @brief Access last element. */
  T& back() noexcept { return dummy.prev->data; }
  /** @brief Access last element (const). */
  const T& back() const noexcept { return dummy.prev->data; }

  /** @brief Inserts a copy of `value` before `pos`. */
  iterator insert(iterator pos, const T& value) {
    return insert(pos, T(value));
  }

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
  void pushFront(const T& value) { insert(begin(), value); }
  /** @brief Pushes a moved `value` to the front. */
  void pushFront(T&& value) { insert(begin(), std::move(value)); }

  /**
   * @brief Pushes a copy of `value` to the back.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  void pushBack(const T& value) { insert(end(), value); }
  /**
   * @brief Pushes a moved `value` to the back.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  void pushBack(T&& value) { insert(end(), std::move(value)); }

  /**
   * @brief Constructs element(s) in place at the front. */
  template <typename... Args>
  void emplaceFront(Args&&... args) {
    emplace(begin(), std::forward<Args>(args)...);
  }

  /**
   * @brief Constructs element(s) in place at the back.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  template <typename... Args>
  void emplaceBack(Args&&... args) {
    emplace(end(), std::forward<Args>(args)...);
  }

  /** @brief Removes the first element. */
  void popFront() {
    if (!empty()) erase(begin());
  }
  /** @brief Removes the last element. */
  void popBack() {
    if (!empty()) erase(--end());
  }

  /** @brief Resizes the list to contain `count` default elements. */
  void resize(std::size_t count) { resize(count, T()); }

  /**
   * @brief Resizes the list to contain `count` copies of `value`.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  void resize(std::size_t count, const T& value);

  /** @brief Swaps contents with `other`. */
  void swap(ListBase& other) noexcept;

  /** @brief Merges sorted list `other` into this list. */
  void merge(ListBase& other) {
    merge(other, [](const T& a, const T& b) { return a < b; });
  }

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
  void unique() {
    unique([](const T& a, const T& b) { return a == b; });
  }

  /** @brief Removes consecutive duplicates matching predicate `p`. */
  template <typename BinaryPredicate>
  void unique(BinaryPredicate p);

  /** @brief Sorts the list. */
  void sort() {
    sort([](const T& a, const T& b) { return a < b; });
  }

  /** @brief Sorts the list using comparator `comp`. */
  template <typename Compare>
  void sort(Compare comp);

  /** @brief Iterator to the beginning. */
  iterator begin() noexcept { return iterator(dummy.next); }
  /** @brief Iterator to the end (dummy node). */
  iterator end() noexcept { return iterator(&dummy); }
  /** @brief Reverse iterator to the last element. */
  iterator rbegin() noexcept { return iterator(dummy.prev); }
  /** @brief Reverse iterator to dummy node (rend). */
  iterator rend() noexcept { return iterator(&dummy); }

  /** @brief Returns number of elements. */
  std::size_t size() const noexcept { return _size; }
  /** @brief Clears the list. */
  void clear() noexcept;
  /** @brief Checks if list is empty. */
  bool empty() const noexcept { return _size == 0; }

  /**
   * @brief Copy assignment operator.
   * @throws std::bad_alloc if memory allocation fails iterator
   */
  ListBase& operator=(const ListBase& other);
  /** @brief Move assignment operator. */
  ListBase& operator=(ListBase&& other) noexcept;
};

#include "impl/BaseList.tpp"
