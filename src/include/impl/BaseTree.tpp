#include "RedBlackTree/BaseTree.h"

template <typename T, typename Compare>
typename RBBase<T, Compare>::Node* RBBase<T, Compare>::copyTree(
    Node* n, Node* otherNil) {
  // If we reached the sentinel node of the other tree,
  // return our own sentinel to maintain structural consistency.
  if (n == otherNil) {
    return nil;
  }

  // Create a new node copying the value
  Node* x = new Node(n->value);
  // Copy the color (red or black)
  x->color = n->color;

  // Recursively copy the right subtree
  x->right = copyTree(n->right, otherNil);
  // Recursively copy the left subtree
  x->left = copyTree(n->left, otherNil);

  // Restore parent pointers if the children are not sentinel nodes
  if (x->right != nil) x->right->parent = x;
  if (x->left != nil) x->left->parent = x;

  return x;
}

template <typename T, typename Compare>
RBBase<T, Compare>::RBBase(const RBBase<T, Compare>& other) : comp(other.comp) {
  // Create our sentinel node
  nil = new Node();
  nil->left = nil->right = nil->parent = nil;
  nil->color = Black;

  // Deep copy the other tree starting from its root
  root = copyTree(other.root, other.nil);
}

template <typename T, typename Compare>
RBBase<T, Compare>& RBBase<T, Compare>::operator=(const RBBase& other) {
  // Check for self-assignment
  if (this != &other) {
    // Clear the current tree
    clearTree(root);

    // Create a new sentinel node
    nil = new Node();
    nil->left = nil->right = nil->parent = nil;
    nil->color = Black;

    // Deep copy of the other tree
    root = copyTree(other.root, other.nil);
  }

  return *this;
}

template <typename T, typename Compare>
RBBase<T, Compare>::RBBase(RBBase<T, Compare>&& other) : comp(other.comp) {
  // Steal the tree pointers from the other instance
  root = other.root;
  nil = other.nil;

  // Leave the other instance in a safe empty state
  other.root = nullptr;
  other.nil = nullptr;
}

template <typename T, typename Compare>
RBBase<T, Compare>::RBBase() : comp(Compare()) {
  // Create the sentinel node that acts as NIL
  nil = new Node(T{});
  nil->color = Black;

  // Empty tree: root points to the sentinel
  root = nil;
}

template <typename T, typename Compare>
RBBase<T, Compare>::~RBBase() {
  // Remove all tree nodes except the sentinel
  clearTree(root);

  // Delete the sentinel
  delete nil;
}

template <typename T, typename Compare>
RBBase<T, Compare>::Node::Node(const T& v)
    : value(v), parent(nullptr), left(nullptr), right(nullptr), color(Red) {
  // Node constructor:
  // newly created nodes are red by default, following RB-tree rules.
}
