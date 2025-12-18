#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>
#include <vector>

#include "array/Vector.h"
#include "helpers.h"

/**
 * @brief Base class for a red-black tree.
 *
 * Serves as the foundation for containers like map, set, and multiset.
 * Provides sorted storage with logarithmic access time.
 *
 * @tparam T Type of elements stored in the tree.
 * @tparam Compare Comparator function for ordering elements.
 */
template <typename T, typename Compare>
class RBBase {
 protected:
  /**
   * @brief Node color in red-black tree.
   */
  enum Color { Red, Black };

  /**
   * @brief Tree node structure.
   */
  struct Node {
    T value;       ///< Stored value
    Node* parent;  ///< Parent node
    Node* left;    ///< Left child
    Node* right;   ///< Right child
    Color color;   ///< Node color (Red or Black)

    /**
     * @brief Node constructor for sentinel (NIL).
     */
    Node() = default;

    /**
     * @brief Node constructor.
     * @param v Value to store in the node.
     */
    Node(const T& v);
    Node(T&& v);
  };

 public:  // Iterator может быть публичным, как в std::map/set
  class iterator {
    const RBBase<T, Compare>* tree;
    Node* current;
    void leftMost(Node* node);

   public:
    using valueType = T;   ///< Value type
    using pointer = T*;    ///< Pointer type
    using reference = T&;  ///< Reference type

    iterator();
    iterator(const RBBase<T, Compare>* const tree);
    iterator(const RBBase<T, Compare>* const tree, Node* cur);

    reference operator*() const;
    pointer operator->() const;

    iterator& operator++();
    iterator operator++(int);

    iterator& operator--();
    iterator operator--(int);

    bool operator==(const iterator& other) const;

    bool operator!=(const iterator& other) const;
  };

 protected:
  using size_type = std::size_t;  ///< Type for sizes

  size_type tree_size = 0;
  Node* root = nullptr;  ///< Root of the tree
  Node* nil = nullptr;   ///< Sentinel node representing the end of the tree
  Compare comp;          ///< Comparator object

  /**
   * @brief Copies a red-black subtree.
   *
   * Returns a clone of @p n, mapping @p otherNil to this tree's @c nil.
   *
   * @return New subtree root or @c nil.
   */
  Node* copyTree(Node* n, Node* otherNil);

  template <typename forward_t>
  Pair<Node*, bool> ins(forward_t&& value);

  /**
   * @brief Default constructor.
   *
   * Initializes an empty tree with a sentinel node.
   */
  RBBase();

  /** @brief Copy constructor. */
  RBBase(const RBBase& other);

  /** @brief Move constructor. */
  RBBase(RBBase&& other);

  /** @brief Initializer list constructor. */
  RBBase(std::initializer_list<T> ilist);

  /** @brief Range constructor. */
  template <typename InputIt>
  RBBase(InputIt first, InputIt last);

  /** @brief Copy assignment. */
  RBBase& operator=(const RBBase& other);

  /**
   * @brief Destructor.
   *
   * Deletes all nodes in the tree and frees memory.
   */
  ~RBBase();

  /**
   * @brief Inserts a value into the tree.
   * @param value Value to insert.
   * @return Pair containing pointer to the inserted/found node and a bool
   * flag indicating success.
   */
  Pair<iterator, bool> insert(const T& value);

  /**
   * @brief Move a value into the tree.
   * @param value Value to insert.
   * @return Pair containing pointer to the inserted/found node and a bool
   * flag indicating success.
   */
  Pair<iterator, bool> insert(T&& value);

  /**
   * @brief Inserts a range into the tree.
   * @param first start range.
   * @param last end range.
   */
  template <typename InputIt>
  void insert(InputIt first, InputIt last);

  /**
   * @brief Inserts a list into the tree.
   * @param ilist initializer list with values.
   */
  void insert(std::initializer_list<T> ilist);

  template <typename... Args>
  std::vector<Pair<iterator, bool>> insert_many(Args&&... args);

  /**
   * @brief Finds a node with a given value.
   * @param value Value to search for.
   * @return Pointer to the node if found, nullptr otherwise.
   */
  Node* find(const T& value) const;

  /**
   * @brief Finds the minimum node in a subtree.
   * @param n Root of the subtree.
   * @return Pointer to the minimum node.
   */
  Node* minimum(Node* n) const;

  /**
   * @brief Finds the maximum node in a subtree.
   * @param n Root of the subtree.
   * @return Pointer to the maximum node.
   */
  Node* maximum(Node* n) const;

  /**
   * @brief Finds the successor node in in-order traversal.
   * @param n Node to find the successor of.
   * @return Pointer to the successor node.
   */
  Node* successor(Node* n) const;

  /**
   * @brief Finds the predecessor node in in-order traversal.
   * @param n Node to find the predecessor of.
   * @return Pointer to the predecessor node.
   */
  Node* predecessor(Node* n) const;

  /**
   * @brief Removes a specific node from the tree.
   * @param node Node to remove.
   */
  void erase(Node* node);

  /**
   * @brief Swap tree with other.
   * @param Other tree.
   */
  void swap(RBBase& other);  // Исправлено: не const

  void merge(RBBase& other);

  /**
   * @brief Returns the root of the tree.
   * @return Pointer to the root node.
   */
  Node* getRoot() const { return root; }

  /**
   * @brief Fixes the red-black properties after delete node.
   * @param x Node that replaced the removed node (or nil).
   */
  void fixDelete(Node* x);

  /**
   * @brief Recursively clears a subtree.
   * @param n Root of the subtree to clear.
   */
  void clearTree(Node* n);

  /**
   * @brief Performs left rotation around a node.
   * @param x Node to rotate around.
   */
  void rotateLeft(Node* x);

  /**
   * @brief Performs right rotation around a node.
   * @param y Node to rotate around.
   */
  void rotateRight(Node* y);

  /**
   * @brief Fixes the red-black properties after insertion.
   * @param z Newly inserted node.
   */
  void fixTree(Node* z);

  /**
   * @brief Deletes a node from the tree (skeleton implementation).
   * @param z Node to delete.
   *
   * Red-black deletion involves: Finding the node y to actually remove,
   * - Identifying node x that replaces y,
   * - Adjusting colors and structure,
   * - Freeing memory.
   */
  void deleteNode(Node* z);

  /**
   * @brief Checks if the container is empty.
   * @return True if the tree contains no elements, false otherwise.
   */
  bool empty() const { return tree_size == 0; }

  /**
   * @brief Returns the number of elements in the tree.
   * @return The number of elements currently stored in the tree.
   */
  size_type size() const { return tree_size; }

  /**
   * @brief Returns an iterator to the beginning.
   *
   * The element pointed to is the one with the smallest key (first element
   * in in-order traversal).
   *
   * @return An iterator to the first element.
   */
  iterator begin() const;

  /**
   * @brief Returns an iterator to the end.
   *
   * The iterator refers to the theoretical element *after* the last element
   * (the one with the largest key) in the tree.
   * This element acts as a placeholder and should not be dereferenced.
   *
   * @return An iterator to the element following the last element.
   */
  iterator end() const;

  bool contains(const T&);

  //============================================================================
  //=================== template debug functions ===============================
  //============================================================================

 public:
  /**
   * @brief Displays the tree structure to the console.
   *
   * Renders the tree structure horizontally (or vertically, depending on
   * implementation) to make it readable, showing hierarchy and node color.
   */
  void displayTree() const;

  /**
   * @brief Recursively prints the subtree rooted at 'node'.
   * @param node Current node to print.
   * @param level Current depth in the tree (used for indentation).
   * @param prefix String prefix to visualize the connection from parent.
   */
  void printNode(Node* node, int level, const std::string& prefix) const;
};

#include "impl/BaseTree.tpp"
