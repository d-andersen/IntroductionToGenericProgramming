/**
 * @file List.hpp
 * @author Dennis Andersen - deand17
 * @brief Doubly Linked List header file.
 * @date 2022-04-01
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 1 - Spring 2022
 *
 * Declaration and documentation of Doubly Linked List for strings.
 *
 * The list is DefaultConstructible, Copyable, and EqualityComparable and should
 * therefore be a Regular type.
 */
#ifndef LIST_HPP
#define LIST_HPP

#include <string>

namespace DM852
{
class List
{
public:
    class Node;

    /**
     * Default constructor.
     */
    List();

    /**
     * Constructs a copy of the list given by other.
     *
     * The copy is constructed in the obvious way, by copying each element
     * of other by going from head to tail.
     *
     * This is obviously an O(n) operation.
     *
     * @param other List to construct a copy from.
     */
    List(const List& other);

    /**
     * Destructor.
     *
     * Uses clear to delete all nodes.
     *
     * This is obviously an O(n) operation.
     */
    ~List();

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
    List &operator=(const List &other) noexcept;

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
     * Inserts a new element in the end.
     *
     * Uses insert_node to insert the element in constant time.
     *
     * @param elem The element to insert.
     */
    void push_back(const std::string &elem);

    /**
     * Inserts a new element before the one stored in node, and returns
     * a pointer to the node for the newly inserted element.
     *
     * Uses insert_node to insert the element in constant time.
     *
     * @param node The node to insert.
     * @param elem The element stored in the node.
     * @return A pointer to the node for the newly inserted element.
     */
    Node *insert(Node *node, const std::string &elem);

    /**
     * Erases all elements.
     *
     * While the list is non-empty, uses pop_back to erase elements.
     * If this list is empty, this does nothing.
     *
     * This is of course an O(n) operation.
     */
    void clear();

    /**
     * Erases the last element.
     *
     * Uses erase_node to erase the last element in constant time.
     * If the list is empty, this does nothing.
     */
    void pop_back();

    /**
     * Erases the element stored in node.
     *
     * Uses erase_node to erase the element in constant time.
     * If the list is empty, this does nothing.
     */
    void erase(Node *node);

    /**
     * Accesses the first element.
     *
     * It is the responsibility of the caller to to verify that the list is
     * non-empty.
     *
     * @return A reference to the string in the head of the list if the list
     *         is non-empty.
     */
    std::string &front();

    /**
     * Accesses the first element.
     *
     * It is the responsibility of the caller to to verify that the list is
     * non-empty.
     *
     * @return A const reference to the string in the head of the list if the
     *         list is non-empty.
     */
    const std::string &front() const;

    /**
     * Accesses the last element.
     *
     * It is the responsibility of the caller to to verify that the list is
     * non-empty.
     *
     * @return A reference to the string in the tail of the list if the list
     *         is non-empty.
     */
    std::string &back();

    /**
     * Accesses the last element.
     *
     * It is the responsibility of the caller to to verify that the list is
     * non-empty.
     *
     * @return A const reference to the string in the tail of the list if the
     *         list is non-empty.
     */
    const std::string &back() const;


    /**
     * Accesses the node storing the first element.
     *
     * @return A pointer to the node at the head of the list if the list is
     *         non-empty and nullptr otherwise.
     */
    Node *begin();

    /**
     * Accesses the node storing the first element.
     *
     * @return A const pointer to the node at the head of the list if the list
     *         is non-empty and nullptr otherwise.
     */
    const Node *begin() const;


    /**
     * Returns a pointer to the node past the last element, meaning this function
     * always returns nullptr.
     *
     * @return nullptr.
     */
    Node *end();

    /**
     * Returns a pointer to the node past the last element, meaning this function
     * always returns nullptr.
     *
     * @return nullptr.
     */
    const Node *end() const;

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
    friend void swap(List &lhs, List &rhs) noexcept;

    /**
     * Enables printing of the list.
     * This has mainly been used as a convenience function for debugging.
     *
     * Complexity is O(n) since we of course need to print all nodes in the list.
     */
    friend std::ostream &operator<<(std::ostream &s, const List &l);

    class Node
    {
    public:
        /**
         * Default constructor.
         *
         * @param data The string to store in this node.
         */
        explicit Node(std::string data);

        /**
         * Default destructor.
         */
        ~Node();

        std::string data;

        /**
         * Pointer to the Node storing the next element, or nullptr if this node
         * is the tail.
         */
        Node *next;

        /**
         * Pointer to the Node storing the previous element, or nullptr if this
         * node is the head.
         */
        Node *prev;
    };

private:
    /**
     * The number of elements (nodes) in the list.
     */
    int n;

    Node *head;
    Node *tail;

    /**
     * Delegator function to handle where to insert a node.
     *
     * The first argument, node, is a pointer to the node before which a new
     * node should be inserted. If node is nullptr, instead of causing an error,
     * this is interpreted as inserting at the back of list and is equivalent to
     * calling push_back.
     *
     * @param node Pointer to the node before which new_node should be inserted.
     * @param new_node Pointer to the node to be inserted.
     */
    void insert_node(Node *node, Node * new_node);

    /**
     * Handles insertion of an element into an empty list, i.e. setting head and
     * tail pointers.
     *
     * @param new_node Pointer to the node to be inserted.
     */
    void insert_into_empty_list(Node *new_node);

    /**
     * Handles insertion of an element at the back of the list.
     *
     * @param new_node Pointer to the node to be inserted.
     */
    void insert_back(Node *new_node);

    /**
     * Handles insertion of an element at the front of the list.
     *
     * @param new_node Pointer to the node to be inserted.
     */
    void insert_front(Node *new_node);

    /**
     * Handles insertion of an element before node somewhere in the list.
     *
     * @param node Pointer to the node before which new_node should be inserted.
     * @param new_node Pointer to the node to be inserted.
     */
    void insert_middle(Node *node, Node *new_node);

    /**
     * Delegator function to handle where to erase a node.
     *
     * If the list is empty or node is nullptr, this does nothing.
     *
     * @param node Pointer to the node to be erased.
     */
    void erase_node(Node *node);

    /**
     * Handles erasure of a single element list, i.e. resetting head and tail
     * pointers to nullptr.
     */
    void erase_single_elem_list();

    /**
     * Handles erasure of an element at the back of the list.
     */
    void erase_back();

    /**
     * Handles erasure of an element at the front of the list.
     */
    void erase_front();

    /**
     * Handles erasure of an element somewhere in the list.
     *
     * @param node Pointer to the node to be erased.
     */
    void erase_middle(Node *node);
};

/**
 * Checks for equality between the strings stored in each list.
 *
 * First compares sizes as a sanity check and returns false if the two lists are not
 * the same size. If sizes are equal, then traverses the lists from head to tail,
 * and for each position, compares the strings of each list at that position. If this
 * pairwise comparison matches at all positions, the function returns true. In other
 * words, the structure and order of elements matters. For example, although the
 * contents of the following two lists are identical, they are NOT considered equal:
 *
 *     lhs: ["1"]<->["2"]<->["3"] != ["3"]<->["1"]<->["2"] :rhs
 *
 * This behaviour is in agreement with std::list.
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
bool operator==(const List &lhs, const List &rhs);

/**
 * Checks for inequality between the strings stored in each list.
 *
 * Uses the negation of operator== to check for inequality.
 * Please refer to operator== for further details.
 *
 * This is an O(n * m) operation in the worst case as operator== is an O(n * m)
 * operation in the worst case, where m is the length of the longest string stored
 * in any node.
 *
 * @param lhs Left-hand side operand of inequality operator.
 * @param rhs right-hand side operand of inequality operator.
 * @return true if lhs is not equal to rhs and false otherwise.
 */
bool operator!=(const List &lhs, const List &rhs);
}

#endif //LIST_HPP
