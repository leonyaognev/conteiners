#pragma once
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
     * @brief Copy constructor for value initialization.
     * @param value value to initialize data.
     */
    node(const T& value) : data(value) {}

    /**
     * @brief Move constructor for value initialization.
     * @param value value to initialize data.
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
    /** @brief Iterator from a node pointer. */
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
    };

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

  node dummy;             ///< Dummy node (closes the list in a ring).
  std::size_t _size = 0;  ///< Number of elements in the list.

 public:
  /** @brief Default constructor. */
  ListBase();
  /** @brief Copy constructor. */
  ListBase(const ListBase& other);
  /** @brief Move constructor. */
  ListBase(ListBase&& other) noexcept;
  /** @brief Destructor, clears the list. */
  ~ListBase() noexcept { clear(); };

  /**
   * @brief Inserts an element before the iterator position.
   * @param pos insertion position.
   * @param data element value.
   * @return iterator to the inserted element.
   */
  iterator insert(iterator pos, const T& data);

  /**
   * @brief Inserts an element (by move) before the iterator position.
   * @param pos insertion position.
   * @param data element value.
   * @return iterator to the inserted element.
   */
  iterator insert(iterator pos, T&& data);

  /**
   * @brief Inserts several identical elements.
   * @param pos insertion position.
   * @param count number of copies.
   * @param data element value.
   * @return iterator to the first inserted element.
   */
  iterator insert(iterator pos, std::size_t count, const T& data);

  /**
   * @brief Inserts a range of elements.
   * @tparam InputIt input iterator type.
   * @param pos insertion position.
   * @param first range start.
   * @param last range end.
   * @return iterator to the first inserted element.
   */
  template <typename InputIt>
  iterator insert(iterator pos, InputIt first, InputIt last);

  /**
   * @brief Erases an element.
   * @param pos iterator to the element.
   * @return iterator to the next element.
   */
  iterator erase(iterator pos);

  /**
   * @brief Erases a range of elements.
   * @param first range start.
   * @param last range end.
   * @return iterator to the element following the last erased.
   */
  iterator erase(iterator first, iterator last);

  /** @brief Adds an element to the front (by move). */
  void pushFront(T&& data);
  /** @brief Adds an element to the front (by copy). */
  void pushFront(const T& data);

  /** @brief Adds an element to the back (by move). */
  void pushBack(T&& data);
  /** @brief Adds an element to the back (by copy). */
  void pushBack(const T& data);

  /** @brief Removes the first element. */
  void popFront();
  /** @brief Removes the last element. */
  void popBack();

  /** @brief Iterator to the beginning of the container. */
  iterator begin() noexcept { return iterator(dummy.next); }
  /** @brief Iterator to the end of the container (dummy node). */
  iterator end() noexcept { return iterator(dummy); }
  /** @brief Iterator to the last element. */
  iterator rbegin() noexcept { return iterator(dummy.prev); }
  /** @brief Iterator to the dummy node (used as r-end). */
  iterator rend() noexcept { return iterator(dummy); }

  /** @brief Number of elements in the list. */
  std::size_t size() const noexcept { return _size; };
  /** @brief Clears all elements. */
  void clear() noexcept;
  /** @brief Checks if the list is empty. */
  bool empty() const noexcept { return _size == 0; };

  /** @brief Copy assignment operator. */
  ListBase& operator=(const ListBase& other);
  /** @brief Move assignment operator. */
  ListBase& operator=(ListBase&& other) noexcept;
};
