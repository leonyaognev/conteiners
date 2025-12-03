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

template <typename T, typename Compare>
Pair<typename RBBase<T, Compare>::Node*, bool> RBBase<T, Compare>::ins(
    const T& value) {
  Node* cur = root;    // Start from the root
  Node* parent = nil;  // Keep track of parent for insertion

  while (cur != nil) {
    int c = comp(cur->value, value);  // Compare current node with value
    parent = cur;  // Update parent (bug: shadowing variable here)
    if (c < 0) {
      cur = cur->left;  // Go left if value is smaller
    } else if (c > 0) {
      cur = cur->right;  // Go right if value is larger
    } else {
      return Pair(cur, false);  // Value already exists
    }
  }

  Node* n = new Node(value);  // Allocate new node
  n->parent = parent;         // Set parent
  n->left = n->right = nil;   // Initialize children
  n->color = Red;             // New nodes are red by default

  return Pair(n, true);  // Return node and success flag
}

template <typename T, typename Compare>
void RBBase<T, Compare>::rotateLeft(Node* x) {
  Node* y = x->right;  // Right child becomes pivot
  x->right = y->left;  // Move y's left subtree to x's right
  if (y->left != nil) {
    y->left->parent = x;  // Update parent pointer
  }

  y->parent = x->parent;  // y takes x's parent
  if (x->parent == nil) {
    root = y;  // Update root if needed
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;  // x becomes left child of y
  x->parent = y;
}

template <typename T, typename Compare>
void RBBase<T, Compare>::rotateRight(Node* x) {
  Node* y = x->left;
  x->left = y->right;
  if (y->right != nil) {
    y->right->parent = x;
  }

  y->parent = x->parent;
  if (x->parent == nil) {
    root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }

  y->right = x;
  x->parent = y;
}

template <typename T, typename Compare>
void RBBase<T, Compare>::fixTree(Node* z) {
  // Fix red-black properties after insertion
  while (z->color == Red && z->parent->color == Red && z->parent != nil) {
    if (z->parent->parent->left == z->parent) {
      Node* uncle = z->parent->parent->right;
      if (uncle->color == Red) {  // Case 1: uncle is red
        z->parent->color = uncle->color = Black;
        z->parent->parent->color = Red;
        z = z->parent->parent;  // Move up the tree
      } else {
        if (z == z->parent->right) {  // Case 2: triangle
          z = z->parent;
          rotateLeft(z);
        }
        z->parent->color = Black;  // Case 3: line
        z->parent->parent->color = Red;
        rotateRight(z->parent->parent);
      }
    } else {  // Mirror cases
      Node* uncle = z->parent->parent->left;
      if (uncle->color == Red) {
        z->parent->color = uncle->color = Black;
        z->parent->parent->color = Red;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotateRight(z);
        }
        z->parent->color = Black;
        z->parent->parent->color = Red;
        rotateLeft(z->parent->parent);
      }
    }
  }
  root->color = Black;  // Root is always black
}

template <typename T, typename Compare>
Pair<typename RBBase<T, Compare>::Node*, bool> RBBase<T, Compare>::insert(
    const T& value) {
  // Insert node in BST manner
  Pair res = ins(value);
  // Fix red-black violations
  fixTree(res.first);
  return res;
}

template <typename T, typename Compare>
void RBBase<T, Compare>::clearTree(Node* n) {
  if (n == nil) return;

  clearTree(n->right);
  clearTree(n->left);

  delete n;
}
