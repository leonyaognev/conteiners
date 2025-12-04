#include <cstddef>

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
 private:
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
     * @brief Node constructor.
     * @param v Value to store in the node.
     */
    Node(const T& v);
  };

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

  Pair<Node*, bool> ins(const T& value);

 protected:
  using value_type = T;           ///< Type of the elements
  using size_type = std::size_t;  ///< Type for sizes

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
  Pair<Node*, bool> insert(const T& value);

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
   * @brief Removes a specific node from the tree.
   * @param node Node to remove.
   */
  void erase(Node* node);

  /**
   * @brief Returns the root of the tree.
   * @return Pointer to the root node.
   */
  Node* getRoot() const { return root; }

  /**
   * @brief Fixes the red-black properties after delete node.
   * @param z Newly inserted node.
   */
  void fixDelete(Node* x);

 protected:
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
   * Red-black deletion involves:
   * - Finding the node y to actually remove,
   * - Identifying node x that replaces y,
   * - Adjusting colors and structure,
   * - Freeing memory.
   */
  void deleteNode(Node* z);
};
