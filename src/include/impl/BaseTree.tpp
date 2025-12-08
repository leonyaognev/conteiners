#pragma once

#include <stdexcept>

#include "RedBlackTree/BaseTree.h"

template <typename T, typename Compare>
void RBBase<T, Compare>::iterator::leftMost(Node* node) {
  while (node && node->left) node = node->left;
  current = node;
}

template <typename T, typename Compare>
RBBase<T, Compare>::iterator::iterator() : current(nullptr) {}

template <typename T, typename Compare>
RBBase<T, Compare>::iterator::iterator(RBBase<T, Compare>* tree, Node* cur)
    : tree(tree), current(cur) {}

template <typename T, typename Compare>
RBBase<T, Compare>::iterator::iterator(RBBase<T, Compare>* tree) : tree(tree) {
  leftMost(tree->root);
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::iterator::reference
RBBase<T, Compare>::iterator::operator*() const {
  return current->value;
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::iterator::pointer
RBBase<T, Compare>::iterator::operator->() const {
  return &(current->value);
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::iterator&
RBBase<T, Compare>::iterator::operator++() {
  current = tree->successor(current);
  return *this;
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::iterator RBBase<T, Compare>::iterator::operator++(
    int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::iterator&
RBBase<T, Compare>::iterator::operator--() {
  current = tree->predecessor(current);
  return *this;
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::iterator RBBase<T, Compare>::iterator::operator--(
    int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T, typename Compare>
bool RBBase<T, Compare>::iterator::operator==(const iterator& other) const {
  return current == other.current;
}

template <typename T, typename Compare>
bool RBBase<T, Compare>::iterator::operator!=(const iterator& other) const {
  return current != other.current;
}

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

    // Copy compare
    comp = other.comp;

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
  // If we hit NIL, this branch is empty
  if (n == nil) return;

  // Recursively delete the right subtree first
  clearTree(n->right);

  // Then delete the left subtree
  clearTree(n->left);

  // Finally, delete the current node
  delete n;
}

template <typename T, typename Compare>
void RBBase<T, Compare>::fixDelete(Node* x) {
  // Restore red-black properties after deletion
  while (x != root && x->color == Black) {
    Node* parent = x->parent;
    bool isLeft = (x == parent->left);
    Node* w = isLeft ? parent->right : parent->left;

    // If sibling is red, rotate and recolor to convert case
    if (w->color == Red) {
      w->color = Black;
      parent->color = Red;

      if (isLeft)
        leftRotate(parent);
      else
        rightRotate(parent);

      // Update sibling pointer after rotation
      w = isLeft ? parent->right : parent->left;
    }

    // If both children of the sibling are black
    // recolor and move up the tree
    if (w->left->color == Black && w->right->color == Black) {
      w->color = Red;
      x = parent;

    } else {
      // Otherwise, fix the side configuration before the final adjustment
      if ((isLeft && w->right->color == Black) ||
          (!isLeft && w->left->color == Black)) {
        if (isLeft) {
          w->left->color = Black;
          w->color = Red;
          rightRotate(w);
          w = parent->right;
        } else {
          w->right->color = Black;
          w->color = Red;
          leftRotate(w);
          w = parent->left;
        }
      }

      // Final recoloring and rotation to restore balance
      w->color = parent->color;
      parent->color = Black;

      if (isLeft) {
        w->right->color = Black;
        leftRotate(parent);
      } else {
        w->left->color = Black;
        rightRotate(parent);
      }

      x = root;  // We are done fixing
    }
  }

  // Ensure the root (or target) is black after fixup
  x->color = Black;
}

template <typename T, typename Compare>
void RBBase<T, Compare>::deleteNode(Node* z) {
  // Helper lambda to replace one subtree with another
  auto transplant = [this](Node* z, Node* v) {
    if (z->parent == nil)
      root = v;
    else if (z == z->parent->left)
      z->parent->left = v;
    else
      z->parent->right = v;

    v->parent = z->parent;
  };

  Node* y = z;               // Node to delete or swap with
  Node* x;                   // Child pointer for fix-up
  Color orcolor = y->color;  // Save original color of y

  // Case 1: left subtree empty
  if (z->left == nil) {
    x = z->right;
    transplant(z, z->right);

    // Case 2: right subtree empty
  } else if (z->right == nil) {
    x = z->left;
    transplant(z, z->left);

    // Case 3: two children, replace with successor
  } else {
    Node* y = minimum(z->right);
    Color orcolor = y->color;
    Node* x = y->right;

    // Successor is direct child
    if (y->parent == z) {
      x->parent = y;
    } else {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;  // Preserve original color
  }

  // Remove the node
  delete z;

  // If a black node was removed, tree properties might be broken,
  // so perform fix-up
  if (orcolor == Black) {
    fixDelete(x);
  }
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::Node* RBBase<T, Compare>::find(
    const T& value) const {
  Node* cur = root;

  // Standard BST lookup
  while (cur != nil) {
    if (comp(cur->value, value) < 0) {
      cur = cur->left;
    } else if (comp(cur->value, value) > 0) {
      cur = cur->right;
    } else {
      return cur;  // Value found
    }
  }

  return nullptr;  // Value not in tree
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::Node* RBBase<T, Compare>::minimum(Node* n) const {
  // Move to the leftmost node
  while (n && n->left) n = n->left;
  return n;
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::Node* RBBase<T, Compare>::maximum(Node* n) const {
  // Move to the rightmost node
  while (n && n->right) n = n->right;
  return n;
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::Node* RBBase<T, Compare>::successor(
    Node* n) const {
  if (n == nil) {
    throw std::runtime_error("Successor called with NIL node.");
  }

  // If right subtree exists, successor is its minimum
  if (n->right != nil) {
    n = n->right;
    while (n->left != nil) {
      n = n->left;
    }
    return n;
  }

  // Otherwise, walk upward until we find ancestor
  // where we come from its left side
  while (n->parent != nil && n != n->parent->left) {
    n = n->parent;
  }

  return n->parent == nil ? nil : n->parent;
}

template <typename T, typename Compare>
typename RBBase<T, Compare>::Node* RBBase<T, Compare>::predecessor(
    Node* n) const {
  if (n == nil) {
    throw std::runtime_error("Predecessor called with NIL node.");
  }

  // If left subtree exists, predecessor is its maximum
  if (n->left != nil) {
    n = n->left;
    while (n->right != nil) {
      n = n->right;
    }
    return n;
  }

  // Otherwise, walk upward until we find ancestor
  // where we come from its right side
  while (n->parent != nil && n != n->parent->right) {
    n = n->parent;
  }

  return n->parent == nil ? nil : n->parent;
}

template <typename T, typename Compare>
void RBBase<T, Compare>::erase(Node* node) {
  // Do nothing if null
  if (!node) return;

  // Delegate real deletion to deleteNode (with RB fix-up)
  deleteNode(node);
}

template <typename T, typename Compare>
void RBBase<T, Compare>::swap(const RBBase& other) {
  Node* tmp = other.root;
  other.root = root;
  root = tmp;

  tmp = other.nil;
  other.nil = nil;
  nil = other.nil;

  Compare ctmp = other.comp;
  other.comp = comp;
  comp = ctmp;
}
