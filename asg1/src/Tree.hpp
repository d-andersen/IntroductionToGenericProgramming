/**
 * @file Tree.hpp
 * @author Dennis Andersen - deand17
 * @brief Binary Tree header file.
 * @date 2022-04-01
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 1 - Spring 2022
 *
 * Declaration and documentation of Binary Search Tree mapping integers to strings.
 *
 * The tree is DefaultConstructible, Copyable, and EqualityComparable and should
 * therefore be a Regular type.
 *
 * The implementation is largely based on ch. 12 - Binary Search Trees from CLRS.
 *
 * References:
 *
 * [CLRS] Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *        Ch. 12 - Binary Search Trees, pp. 286--307.
 *        Introduction to Algorithms, 3rd ed.
 *        The MIT Press, 2009.
 */
#ifndef TREE_HPP
#define TREE_HPP

#include <string>

namespace DM852
{
class Tree
{
public:
    class Node;

    /**
     * Default constructor.
     */
    Tree();

    /**
     * Constructs a copy of the tree given by other.
     *
     * First finds the root of other and then uses a queue (Queue.hpp) to
     * construct a new tree from other in a BFS manner.
     *
     * Finding the root is an O(h) operation, but since the tree is unbalanced,
     * h = n in the worst case and this becomes an O(n) operation and obviously
     * constructing the tree itself is an O(n) operation, so we have O(n) + O(n)
     * = O(2n), which is still O(n).
     *
     * @param other Tree to construct a copy from.
     */
    Tree(const Tree &other);

    /**
     * Destructor.
     *
     * Uses clear to delete all nodes.
     *
     * This is obviously an O(n) operation.
     */
    ~Tree();

    /**
     * Copy assignment operator.
     *
     * Uses the copy constructor and the copy-and-swap idiom.
     *
     * References:
     * https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#c60-make-copy-assignment-non-virtual-take-the-parameter-by-const-and-return-by-non-const
     * https://en.cppreference.com/w/cpp/language/operators
     * https://stackoverflow.com/a/3279550
     *
     * @param other Tree to copy.
     * @return A copy of other.
     */
    Tree &operator=(const Tree &other);

    /**
     * Returns the number of elements stored.
     *
     * @return the number of elements stored.
     */
    int size() const;

    /**
     * Returns true iff the container is empty, i.e. empty() == (size() == 0).
     *
     * @return true if the tree is empty and false otherwise.
     */
    bool empty() const;

    /**
     * Inserts a new element in the tree or overwrites the value for key if it
     * already exists. Returns a pointer to the newly inserted/updated node,
     * and a boolean being true if a new node was inserted, and false if an
     * existing node was updated.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @param key The key to insert.
     * @param value The value to insert.
     * @return A pair (first, second).
     *         If the key did not already exist in the tree, then
     *         - first is a pointer to the newly inserted node, and
     *         - second is true, indicating that the operation was successful.
     *         otherwise, if the key did already exist, then
     *         - first is nullptr, and
     *         - second is false indicating that an existing node was updated
     *           instead of a new node inserted.
     */
    std::pair<Node*, bool> insert(int key, const std::string &value);

    /**
     * Looks up the given key and returns a pointer to the node containing it,
     * or nullptr if no such node exists.
     *
     * Uses iterative_tree_search to iteratively search the tree for the given key.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @param key The key to search for.
     * @return A pointer to the node if it exists and nullptr otherwise.
     */
    Node *find(int key);

    /**
     * Looks up the given key and returns a pointer to the node containing it,
     * or nullptr if no such node exists.
     *
     * Uses iterative_tree_search to iteratively search the tree for the given key.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @param key The key to search for.
     * @return A const pointer to the node if it exists and nullptr otherwise.
     */
    const Node *find(int key) const;

    /**
     * Erases all elements.
     *
     * Uses postorder_erase_tree to recursively delete all nodes in a post-order
     * traversal.
     *
     * This is of course an O(n) operation.
     */
    void clear();

    /**
     * Erases the key-value pair with the given key, or does nothing if no
     * such key exists.
     *
     * Uses find to locate the key-value pair with the given key, and if
     * found, passes a pointer to that node to the erase function taking
     * a node pointer, which then takes care of deleting the node.
     *
     * Since the tree is unbalanced, in the worst case the height of the tree
     * h = n, the number of elements stored. Thus the find operation is O(n)
     * worst case, and erase (which is based on CLRS Tree-Delete) is also
     * O(n) worst case, so we have O(n) + O(n) = O(2n), which is still O(n).
     *
     * @param key The key to erase.
     */
    void erase(int key);

    /**
     * Erases the element stored in node.
     *
     * Based on Tree-Delete from CLRS ch. 12, p. 298, which relies on
     * Transplant also from CLRS ch. 12, p. 296. It is the responsibility
     * of the caller to ensure that node is not nullptr.
     *
     * This is an O(h) operation due to the call to tree_minimum, but since
     * the tree is unbalanced, h = n in the worst case and this becomes an
     * O(n) operation.
     *
     * @param node The node to erase.
     */
    void erase(const Node *node);


    /**
     * Accesses the first element.
     *
     * Uses tree_minimum to find the key-value pair with smallest key,
     * returning a reference to the value if it exists. It is the
     * responsibility of the caller to to verify that the tree is non-empty.
     *
     * This is an O(h) operation due to the call to tree_minimum, but since
     * the tree is unbalanced, h = n in the worst case and this becomes an
     * O(n) operation.
     *
     * @return A reference to the string in the node with the smallest key
     *         in the tree if the tree is non-empty.
     */
    std::string &front();

    /**
     * Accesses the first element.
     *
     * Uses tree_minimum to find the key-value pair with smallest key,
     * returning a reference to the value if it exists. It is the
     * responsibility of the caller to to verify that the tree is non-empty.
     *
     * This is an O(h) operation due to the call to tree_minimum, but since
     * the tree is unbalanced, h = n in the worst case and this becomes an
     * O(n) operation.
     *
     * @return A const reference to the string in the node with the smallest
     *         key in the tree if the tree is non-empty.
     */
    const std::string &front() const;


    /**
     * Accesses the last element.
     *
     * Uses tree_maximum to find the key-value pair with largest key,
     * returning a reference to the value if it exists. It is the
     * responsibility of the caller to to verify that the tree is non-empty.
     *
     * This is an O(h) operation due to the call to tree_maximum, but since
     * the tree is unbalanced, h = n in the worst case and this becomes an
     * O(n) operation.
     *
     * @return A reference to the string in the node with the largest key
     *         in the tree if the tree is non-empty.
     */
    std::string &back();

    /**
     * Accesses the last element.
     *
     * Uses tree_maximum to find the key-value pair with largest key,
     * returning a reference to the value if it exists. It is the
     * responsibility of the caller to to verify that the tree is non-empty.
     *
     * This is an O(h) operation due to the call to tree_maximum, but since
     * the tree is unbalanced, h = n in the worst case and this becomes an
     * O(n) operation.
     *
     * @return A const reference to the string in the node with the largest
     *         key in the tree if the tree is non-empty.
     */
    const std::string &back() const;

    /**
     * Accesses the node storing the first element.
     *
     * Uses tree_minimum to find and return a pointer to the node with the
     * smallest key or nullptr if the tree is empty.
     *
     * This is an O(h) operation due to the call to tree_minimum, but since
     * the tree is unbalanced, h = n in the worst case and this becomes an
     * O(n) operation.
     *
     * @return A pointer to the node with the smallest key if the tree is
     *         non-empty and nullptr otherwise.
     */
    Node * begin();

    /**
     * Accesses the node storing the first element.
     *
     * Uses tree_minimum to find and return a pointer to the node with the
     * smallest key or nullptr if the tree is empty.
     *
     * This is an O(h) operation due to the call to tree_minimum, but since
     * the tree is unbalanced, h = n in the worst case and this becomes an
     * O(n) operation.
     *
     * @return A pointer to the node with the smallest key if the tree is
     *         non-empty and nullptr otherwise.
     */
    const Node * begin() const;

    /**
     * Returns a pointer to the node past the last element, meaning this function
     * always returns nullptr.
     *
     * @return nullptr.
     */
    Node * end();

    /**
     * Returns a pointer to the node past the last element, meaning this function
     * always returns nullptr.
     *
     * @return nullptr.
     */
    const Node * end() const;

    /**
     * Finds the smallest key-value pair in the tree by following the leftmost path.
     * It is the responsibility of the caller to to verify that the tree is non-empty.
     *
     * Based on Tree-Minimum from CLRS ch. 12, p. 291.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @return A pointer to the node with the smallest key.
     */
    static Node *tree_minimum(Node *node);

    /**
     * Finds the largest key-value pair in the tree by following the rightmost path.
     * It is the responsibility of the caller to to verify that the tree is non-empty.
     *
     * Based on Tree-Maximum from CLRS ch. 12, p. 291.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @return A pointer to the node with the largest key.
     */
    static Node *tree_maximum(Node *node);

    /**
     * Swap function for applying the copy-and-swap idiom.
     *
     * References:
     * https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#c83-for-value-like-types-consider-providing-a-noexcept-swap-function
     * https://stackoverflow.com/a/3279550
     *
     * @param lhs Left-hand side operand to be swapped.
     * @param rhs Right-hand side operand to be swapped.
     */
    friend void swap(Tree &lhs, Tree &rhs) noexcept;

    /**
     * Enables printing of the tree. Uses a queue (Queue.hpp) to print the tree in
     * a BFS manner. This has mainly been used as a convenience function for debugging.
     *
     * Complexity is O(n) since we of course need to print all nodes in the tree.
     */
    friend std::ostream &operator<<(std::ostream &s, const Tree &t);

    class Node
    {
    public:
        /**
         * Default constructor.
         *
         * @param key The immutable key to store in this node.
         * @param value The value to store with the key in this node.
         */
        Node(int key, std::string value);

        /**
         * Default destructor.
         */
        ~Node();

        /**
         * Returns the node with the smallest key larger than the key in
         * this node if it exists and nullptr otherwise.
         *
         * Based on Tree-Successor from CLRS ch. 12, p. 291.
         *
         * This is an O(h) operation, but since the tree is unbalanced, h = n in the
         * worst case and this becomes an O(n) operation.
         *
         * @return A pointer to the successor of this node if exists and
         *         nullptr otherwise.
         */
        Node *next();

        /**
         * Returns the node with the smallest key larger than the key in
         * this node if it exists and nullptr otherwise.
         *
         * Based on Tree-Successor from CLRS ch. 12, p. 291.
         *
         * This is an O(h) operation, but since the tree is unbalanced, h = n in the
         * worst case and this becomes an O(n) operation.
         *
         * @return A const pointer to the successor of this node if exists and
         *         nullptr otherwise.
         */
        const Node *next() const;

        /**
         * Returns the node with the largest key smaller than the key in
         * this node if it exists and nullptr otherwise.
         *
         * Based on Tree-Predecessor from CLRS ch. 12, p. 291.
         *
         * This is an O(h) operation, but since the tree is unbalanced, h = n in the
         * worst case and this becomes an O(n) operation.
         *
         * @return A pointer to the predecessor of this node if exists and
         *         nullptr otherwise.
         */
        Node *prev();

        /**
         * Returns the node with the largest key smaller than the key in
         * this node if it exists and nullptr otherwise.
         *
         * Based on Tree-Predecessor from CLRS ch. 12, p. 291.
         *
         * This is an O(h) operation, but since the tree is unbalanced, h = n in the
         * worst case and this becomes an O(n) operation.
         *
         * @return A const pointer to the predecessor of this node if exists and
         *         nullptr otherwise.
         */
        const Node *prev() const;

        const int key;
        std::string value;

        /**
         * Pointer to the parent Node of this node in the tree, or nullptr if
         * this node is the root.
         */
        Node *parent;

        /**
         * Pointer to left child Node of this node in the tree, or nullptr if no
         * such child exists.
         */
        Node *left;

        /**
         * Pointer to right child Node of this node in the tree, or nullptr if no
         * such child exists.
         */
        Node *right;
    };

private:
    /**
     * The number of key-value pairs (nodes) in the tree.
     */
    int n;

    Node *root;

    /**
     * Searches the tree iteratively for the given key.
     *
     * Based on Iterative-Tree-Search from CLRS ch. 12, p. 291.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @param key The key to search for.
     * @return Pointer to the node with the given search key if it exists and
     *         nullptr otherwise.
     */
    Node *iterative_tree_search(int key) const;

    /**
     * Replaces on subtree as a child of its parent with another subtree.
     *
     * Based on Transplant from CLRS ch. 12, p. 296.
     *
     * @param u Subtree to be replaced by v.
     * @param v Subtree to replace u.
     */
    void transplant(Node *u, Node *v);

    /**
     * Recursive function performing a post-order traversal of the tree, deleting
     * each visited node in the process.
     *
     * This is of course an O(n) operation, since we must visit each node in the tree.
     *
     * @param x Root of the subtree to be deleted.
     */
    void postorder_erase_tree(Node *x);
};

/**
 * Checks for equality between the key-value pairs stored in each tree.
 *
 * First compares sizes as a sanity check and returns false if the two trees are not
 * the same size. If sizes are equal, then performs an in-order traversal, where for
 * each node, first the keys are compared and if the match, the values are compared.
 * If all key-value pairs are equal, the function returns true. Note however, that
 * true only means equality of contents and not of structure. In other words, these
 * two trees are considered equal:
 *
 *             --------------      --------------
 *            | k: 2, v: "2" |    | k: 1, v: "1" |
 *             --------------      --------------
 *               /             ==            \
 *        --------------                --------------
 *       | k: 1, v: "1" |              | k: 2, v: "2" |
 *        --------------                --------------
 *
 * Since values are strings, let m be the length of the longest string stored in any
 * node. Then the worst case complexity is O(n * m), since to verify that two trees
 * are equal, we need to compare all n nodes, which may each contain a string of up to
 * length m.
 *
 * @param lhs Left-hand side operand of inequality operator.
 * @param rhs right-hand side operand of inequality operator.
 * @return true if lhs is equal to rhs and false otherwise.
 */
bool operator==(const Tree &lhs, const Tree &rhs);

/**
 * Checks for inequality between the key-value pairs stored in each tree.
 *
 * Uses the negation of operator== to check for inequality. Please refer to operator==
 * for further details.
 *
 * This is an O(n * m) operation in the worst case as operator== is an O(n * m)
 * operation in the worst case, where m is the length of the longest string stored
 * in any node.
 *
 * @param lhs Left-hand side operand of inequality operator.
 * @param rhs right-hand side operand of inequality operator.
 * @return true if lhs is not equal to rhs and false otherwise.
 */
bool operator!=(const Tree &lhs, const Tree &rhs);

} // namespace DM852

#endif //TREE_HPP
