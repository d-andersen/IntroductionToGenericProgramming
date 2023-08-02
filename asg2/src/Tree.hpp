/**
 * @file Tree.hpp
 * @author Dennis Andersen - deand17
 * @brief Generic binary tree.
 * @date 2022-05-16
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 2 - Spring 2022
 *
 * Implementation of generic binary tree.
 *
 * The tree is DefaultConstructible, Copyable, and EqualityComparable and should
 * therefore be a Regular type. It is also MoveConstructible and Movable.
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

#include <concepts>
#include <iostream>

#include <queue>

namespace DM852
{
/**
 * Generic binary search tree.
 *
 * We require that Keys model a strict weak ordering, as well as Keys and
 * Values being default constructible, such that we are sure we can always
 * compare Keys.
 *
 * @tparam Key Default constructible type modeling a strict weak ordering
 * @tparam Value Default constructible type
 * @tparam Comp Comparator. Defaults to std::less<Key>.
 */
template<typename Key, typename Value, typename Comp = std::less<Key>>
requires std::strict_weak_order<std::less<Key>, Key const&, Key const&>
         && std::default_initializable<Key>
         && std::default_initializable<Value>
struct Tree
{
private:
    struct Tree_node
    {
        using value_type = std::pair<const Key, Value>;

        Tree_node() = delete;

        Tree_node(const Key k, Value v)
                : m_parent(nullptr), m_left(nullptr), m_right(nullptr),
                  m_data(std::move(k), std::move(v))
        {}

        explicit
        Tree_node(value_type elem)
                : m_parent(nullptr), m_left(nullptr), m_right(nullptr),
                  m_data(std::move(elem))
        {}

        Tree_node(const Tree_node &other)
                : m_parent(other.m_parent),
                  m_left(other.m_left),
                  m_right(other.m_right),
                  m_data(other.m_data)
        {}

        Tree_node(Tree_node &&other) noexcept
                : m_parent(std::move(other.m_parent)),
                  m_left(std::move(other.m_left)),
                  m_right(std::move(other.m_right)),
                  m_data(std::move(other.m_data))
        {}

        ~Tree_node() = default;

        Tree_node &operator=(const Tree_node &other)
        {
            m_parent = other.m_parent;
            m_left = other.m_left;
            m_right = other.m_right;
            m_data = other.m_data;
            return *this;
        }

        Tree_node &operator=(Tree_node &&other) noexcept
        {
            m_parent = std::move(other.m_parent);
            m_left = std::move(other.m_left);
            m_right = std::move(other.m_right);
            m_data = std::move(other.m_data);
            return *this;
        }

        Key key() const
        {
            return m_data.first;
        }

        Value value() const
        {
            return m_data.second;
        }

        void set_value(Value v)
        {
            m_data.second = std::move(v);
        }

        Tree_node *m_parent;
        Tree_node *m_left;
        Tree_node *m_right;

        value_type m_data;
    };

    using Node = Tree_node;

public:
    struct Tree_iterator;
    struct Const_tree_iterator;

    using iterator = Tree_iterator;
    using const_iterator = Const_tree_iterator;
    using value_type = std::pair<const Key, Value>;

    /**
     * Struct defining an iterator
     */
    struct Tree_iterator
    {
        friend struct Tree;

        using Node = Tree_node;

        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::pair<const Key, Value>;
        using pointer = std::pair<const Key, Value> *;
        using reference = std::pair<const Key, Value> &;

        Tree_iterator(Tree *t, Node *x)
                : t(t), m_node(x)
        {}

        // copy ctor
        Tree_iterator(const Tree_iterator &other)
                : t(other.t), m_node(other.m_node)
        {}

        ~Tree_iterator() = default;

        Tree_iterator &operator=(const iterator &other)
        {
            auto tmp = other;
            f_swap(*this, tmp);
            return *this;
        }

        reference operator*()
        {
            return m_node ? m_node->m_data : t->m_sentinel.m_data;
        }

        pointer operator->()
        {
            pointer p{m_node ? m_node->m_data : t->m_sentinel.m_data};
            return p;
        }

        Tree_iterator &operator++()
        {
            m_node = t->next(m_node);
            return *this;
        }

        Tree_iterator operator++(int)
        {
            Tree_iterator tmp = *this;
            m_node = t->next(m_node);
            return tmp;
        }

        Tree_iterator &operator--()
        {
            m_node = t->prev(m_node);
            return *this;
        }

        Tree_iterator operator--(int)
        {
            Tree_iterator tmp = *this;
            m_node = t->prev(m_node);
            return tmp;
        }

        friend
        bool operator==(const Tree_iterator &x, const Tree_iterator &y)
        {
            return x.m_node == y.m_node;
        };

        friend
        bool operator!=(const Tree_iterator &x, const Tree_iterator &y)
        {
            return x.m_node != y.m_node;
        };

        friend
        void f_swap(Tree_iterator &lhs, Tree_iterator &rhs)
        {
            using std::swap;
            swap(lhs.t, rhs.t);
            swap(lhs.m_node, rhs.m_node);
        }

    private:
        Tree *t;
        Node *m_node;
    };

    /**
     * Struct defining a const_iterator
     */
    struct Const_tree_iterator
    {
        friend struct Tree;

        using Node = Tree_node;

        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::pair<const Key, Value>;
        using pointer = const std::pair<const Key, Value> *;
        using reference = const std::pair<const Key, Value> &;

        Const_tree_iterator(const Tree *t, const Node *x)
                : t(t), m_node(x)
        {}

        Const_tree_iterator(const Tree *t, const iterator it)
                : t(t), m_node(it.m_node)
        {}

        ~Const_tree_iterator() = default;

        Const_tree_iterator &operator=(const const_iterator &other)
        {
            auto tmp = other;
            f_swap(*this, tmp);
            return *this;
        }

        reference operator*() const
        {
            return m_node ? m_node->m_data : t->m_sentinel.m_data;
        }

        pointer operator->() const
        {
            pointer p{m_node ? m_node->m_data : t->m_sentinel.m_data};
            return p;
        }

        Const_tree_iterator &operator++()
        {
            m_node = t->next(m_node);
            return *this;
        }

        Const_tree_iterator operator++(int)
        {
            Const_tree_iterator tmp = *this;
            m_node = t->next(m_node);
            return tmp;
        }

        Const_tree_iterator &operator--()
        {
            m_node = t->prev(m_node);
            return *this;
        }

        Const_tree_iterator operator--(int)
        {
            Const_tree_iterator tmp = *this;
            m_node = t->prev(m_node);
            return tmp;
        }

        friend
        bool operator==(const Const_tree_iterator &x, const Const_tree_iterator &y)
        {
            return x.m_node == y.m_node;
        };

        friend
        bool operator!=(const Const_tree_iterator &x, const Const_tree_iterator &y)
        {
            return x.m_node != y.m_node;
        };

        friend
        void f_swap(Const_tree_iterator &lhs, Const_tree_iterator &rhs)
        {
            using std::swap;
            swap(lhs.t, rhs.t);
            swap(lhs.m_node, rhs.m_node);
        }

    private:
        const Tree *t;
        const Node *m_node;
    };


    /**
     * Default constructor.
     */
    Tree()
        : m_size(0), m_comp(std::less<Key>()), m_sentinel(Key(), Value())
    {
        m_init();
    }

    /**
     * Constructor for constructing a tree with a specific comparator instance.
     *
     * @param comp Comparator to use.
     */
    explicit
    Tree(Comp comp)
        : m_size(0), m_comp(comp), m_sentinel(Key(), Value())
    {
        m_init();
    }

    /**
     * Copy constructor.
     *
     * @param other Tree to copy.
     */
    Tree(const Tree &other)
        : m_size(0), m_comp(other.m_comp), m_sentinel(Key(), Value())
    {
        m_init();
        for (auto it = other.begin(); it != other.end(); ++it) {
            auto [k, v] = *it;
            insert(k, v);
        }
    }

    /**
     * Move constructor.
     *
     * @param other Tree to move from.
     */
    Tree(Tree &&other) noexcept
        : m_size(std::move(other.m_size)),
          m_comp(std::move(other.m_comp)),
          m_sentinel(Key(), Value())
    {
        m_init();
        m_sentinel.m_parent = other.m_sentinel.m_parent;
        m_sentinel.m_left = other.m_sentinel.m_left;
        m_sentinel.m_right = other.m_sentinel.m_right;
        m_sentinel.m_right->m_right = &m_sentinel;

        other.m_init();
    }

    /**
     * Default destructor.
     */
    ~Tree()
    {
        m_postorder_erase_tree(m_root());
    }

    /**
     * Copy assignment operator.
     *
     * @param other Tree to copy.
     * @return A copy of other.
     */
    Tree &operator=(const Tree &other)
    {
        clear();
        auto tmp = other;

        m_size = tmp.m_size;
        m_sentinel.m_parent = tmp.m_sentinel.m_parent;
        m_sentinel.m_left = tmp.m_sentinel.m_left;
        m_sentinel.m_right = tmp.m_sentinel.m_right;
        tmp.m_sentinel.m_right->m_right = &m_sentinel;
        tmp.m_init();

        return *this;
    }

    /**
     * Move assignment operator.
     *
     * @param other Tree to assign from.
     * @return Tree with the contents of other.
     */
    Tree &operator=(Tree &&other)
    {
        clear();
        m_size = std::move(other.m_size);
        m_sentinel.m_parent = other.m_sentinel.m_parent;
        m_sentinel.m_left = other.m_sentinel.m_left;
        m_sentinel.m_right = other.m_sentinel.m_right;
        m_sentinel.m_right->m_right = &m_sentinel;

        other.m_init();
        return *this;
    }

    /**
     * Returns the number of elements stored.
     *
     * @return the number of elements stored.
     */
    [[nodiscard]]
    int size() const
    {
        return m_size;
    }

    /**
     * Returns true iff the container is empty, i.e. empty() == (size() == 0).
     *
     * @return true if the tree is empty and false otherwise.
     */
    [[nodiscard]]
    bool empty() const
    {
        return (size() == 0);
    }

    /**
     * Inserts a new element in the tree or overwrites the Value for Key if it
     * already exists. Returns a pair (iterator it, bool b), where it is an
     * iterator pointing at the newly inserted/updated node, and b a boolean
     * being true if a new node was inserted, and false if an existing node was
     * updated.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * Uses private method m_insert for the insertion.
     *
     * @param z The node to insert.
     * @return A pair (iterator it, bool b).
     *         If the key did not already exist in the tree, then
     *         - it is an iterator to the newly inserted node, and
     *         - b is true, indicating that the operation was successful.
     *         otherwise, if the Key did already exist, then
     *         - it is a past-the-end iterator equivalent to calling end(), and
     *         - b is false indicating that an existing node was updated
     *           instead of a new node inserted.
     */
    std::pair<iterator, bool> insert(const Key &key, const Value &value)
    {
        value_type elem{key, value};
        Node *z{m_create_node(elem)};
        return m_insert(z);
    }

    /**
     * Inserts a new element in the tree or overwrites the Value for Key if it
     * already exists. Returns a pair (iterator it, bool b), where it is an
     * iterator pointing at the newly inserted/updated node, and b a boolean
     * being true if a new node was inserted, and false if an existing node was
     * updated.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * Uses private method m_insert for the insertion.
     *
     * @param z The node to insert.
     * @return A pair (iterator it, bool b).
     *         If the key did not already exist in the tree, then
     *         - it is an iterator to the newly inserted node, and
     *         - b is true, indicating that the operation was successful.
     *         otherwise, if the Key did already exist, then
     *         - it is a past-the-end iterator equivalent to calling end(), and
     *         - b is false indicating that an existing node was updated
     *           instead of a new node inserted.
     */
    std::pair<iterator, bool> insert(Key &&key, Value &&value)
    {
        value_type elem{std::move(key), std::move(value)};
        Node *z{m_create_node(std::move(elem))};
        return m_insert(z);
    }

    /**
     * Looks up the given Key and returns a iterator to the
     * the node containing it or a past-the-end iterator if
     * no such node exists.
     *
     * Uses iterative_tree_search to iteratively search the tree
     * for the given key.
     *
     * This is an O(h) operation, but since the tree is unbalanced,
     * h = n in the worst case and this becomes an O(n) operation.
     *
     * @param key The Key to search for.
     * @return A iterator to the node if it exists and a past-
     *         the-end iterator otherwise.
     */
    iterator find(const Key &key)
    {
        Node *x{m_iterative_tree_search(key)};
        if (x == &m_sentinel) {
            return iterator(this, &m_sentinel);
        }
        return iterator(this, x);
    }

    /**
     * Looks up the given Key and returns a const_iterator to the
     * the node containing it or a past-the-end const_iterator if
     * no such node exists.
     *
     * Uses iterative_tree_search to iteratively search the tree
     * for the given key.
     *
     * This is an O(h) operation, but since the tree is unbalanced,
     * h = n in the worst case and this becomes an O(n) operation.
     *
     * @param key The Key to search for.
     * @return A const_iterator to the node if it exists and a past-
     *         the-end const_iterator otherwise.
     */
    const_iterator find(const Key &key) const
    {
        Node *x{m_iterative_tree_search(key)};
        if (x == &m_sentinel) {
            return const_iterator(this, &m_sentinel);
        }
        return const_iterator(this, x);
    }

    /**
     * Erases all elements and resets the container.
     *
     * Uses postorder_erase_tree to recursively delete all nodes in
     * a post-order traversal.
     */
    void clear()
    {
        m_postorder_erase_tree(m_root());
        m_init();
    }

    /**
     * Erases the node with Key key.
     *
     * Iterators pointed at the erased node are invalidated.
     * Note that a past-the-end iterator may also be invalidated
     * if the erased node was the node with the largest Key.
     */
    void erase(const Key &key)
    {
        // TODO
        const_iterator z{this, find(key)};
        if (z.m_node) {
            m_erase(const_cast<Node *>(z.m_node));
        }
    }

    /**
     * Erases the node stored at iterator position pos.
     *
     * Iterators pointed at the erased node are invalidated.
     * Note that a past-the-end iterator may also be invalidated
     * if the erased node was the node with the largest Key.
     */
    void erase(const_iterator pos)
    {
        // TODO
        if (pos->m_node) {
            m_erase(pos->m_node);
        }
    }

    /**
     * Accesses the first element.
     *
     * @return Reference to the first element.
     */
    value_type &front()
    {
        return *begin();
    }

    /**
     * Accesses the first element.
     *
     * @return Const reference to the first element.
     */
    const value_type &front() const
    {
        return *begin();
    }

    /**
     * Accesses the last element.
     *
     * @return Reference to the last element.
     */
    value_type &back()
    {
        iterator tmp{*this, end()};
        --tmp;
        return *tmp;
    }

    /**
     * Accesses the last element.
     *
     * @return Const reference to the last element.
     */
    const value_type &back() const
    {
        const_iterator tmp{*this, end()};
        --tmp;
        return *tmp;
    }

    /**
     * Returns an iterator for accessing the first element
     * or a past-the-end iterator if the container is empty.
     *
     * @return iterator for accessing the first element or a
     *         past-the-end iterator if the container is empty.
     */
    iterator begin()
    {
        return iterator(this, m_sentinel.m_left);
    }

    /**
     * Returns a const_iterator for accessing the first element
     * or a past-the-end const_iterator if the container is empty.
     *
     * @return const_iterator for accessing the first element or a
     *         past-the-end const_iterator if the container is empty.
     */
    const_iterator begin() const
    {
        return const_iterator(this, m_sentinel.m_left);
    }

    /**
     * Returns a past-the-end iterator.
     *
     * @return Past-the-end iterator.
     */
    iterator end()
    {
        return iterator(this, &m_sentinel);
    }

    /**
     * Returns a past-the-end const_iterator.
     *
     * @return Past-the-end const_iterator.
     */
    const_iterator end() const
    {
        return const_iterator(this, &m_sentinel);
    }

private:
    /**
     * Private initializer method.
     */
    void m_init()
    {
        m_sentinel.m_parent = nullptr; // root
        m_sentinel.m_left = nullptr; // begin() == tree minimum
        m_sentinel.m_right = nullptr; // --end() == tree maximum
        m_size = 0;
    }

    /**
     * Recursive function performing a post-order traversal of the tree, deleting
     * each visited node in the process.
     *
     * @param x Root of the subtree to be deleted.
     */
    void m_postorder_erase_tree(Node *x)
    {
        if (x && x != &m_sentinel) {
            m_postorder_erase_tree(x->m_left);
            m_postorder_erase_tree(x->m_right);
            delete x;
        }
    }

    /**
     * Creates a new node with the value_type provided
     * in elem.
     *
     * @param elem value_type to construct node with.
     * @return Pointer to the newly created node.
     */
    Node *m_create_node(value_type &elem)
    {
        return new Node(elem);
    }

    /**
     * Creates a new node and move constructs it with the value_type provided
     * in elem.
     *
     * @param elem value_type to move construct node with.
     * @return Pointer to the newly created node.
     */
    Node *m_create_node(value_type &&elem)
    {
        return new Node(std::move(elem));
    }

    /**
     * Destroys a node.
     *
     * @param x Node to be destroyed.
     */
    void m_destroy_node(Node *x)
    {
        delete x;
    }

    /**
     * Retrieves a pointer to the root.
     *
     * @return A pointer to the root.
     */
    Node *m_root()
    {
        return m_sentinel.m_parent;
    }

    /**
     * Finds the smallest Key-Value pair in the tree by following the leftmost path.
     * It is the responsibility of the caller to to verify that the tree is non-empty.
     *
     * Based on Tree-Minimum from CLRS ch. 12, p. 291.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @return A pointer to the node with the smallest Key.
     */
    Tree_node *m_tree_minimum(Tree_node *x)
    {
        while (x->m_left) {
            x = x->m_left;
        }
        return x;
    }

    /**
     * Finds the smallest Key-Value pair in the tree by following the leftmost path.
     * It is the responsibility of the caller to to verify that the tree is non-empty.
     *
     * Based on Tree-Minimum from CLRS ch. 12, p. 291.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @return A pointer to the node with the smallest Key.
     */
    const Tree_node *m_tree_minimum(const Tree_node *x) const
    {
        while (x->m_left) {
            x = x->m_left;
        }
        return x;
    }

    /**
     * Finds the largest Key-Value pair in the tree by following the rightmost path.
     * It is the responsibility of the caller to to verify that the tree is non-empty.
     *
     * Based on Tree-Maximum from CLRS ch. 12, p. 291.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @return A pointer to the node with the largest Key.
     */
    Tree_node *m_tree_maximum(Tree_node *x)
    {
        while (x->m_right) {
            x = x->m_right;
        }
        return x;
    }

    /**
     * Finds the largest Key-Value pair in the tree by following the rightmost path.
     * It is the responsibility of the caller to to verify that the tree is non-empty.
     *
     * Based on Tree-Maximum from CLRS ch. 12, p. 291.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @return A pointer to the node with the largest Key.
     */
    const Tree_node *m_tree_maximum(const Tree_node *x) const
    {
        while (x->m_right) {
            x = x->m_right;
        }
        return x;
    }

    /**
     * Returns the node with the smallest Key larger than the Key in
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
    Node *next(Node *x)
    {
        if (x->m_right == &m_sentinel) {
            return x->m_right;
        }
        if (x->m_right) {
            return m_tree_minimum(x->m_right);
        }
        auto y{x->m_parent};
        while (y && x == y->m_right) {
            x = y;
            y = y->m_parent;
        }
        return y;
    }

    /**
     * Returns the node with the smallest Key larger than the Key in
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
    const Node *next(const Node *x) const
    {
        if (x->m_right == &m_sentinel) {
            return x->m_right;
        }
        if (x->m_right) {
            return m_tree_minimum(x->m_right);
        }
        auto y{x->m_parent};
        while (y && x == y->m_right) {
            x = y;
            y = y->m_parent;
        }
        return y;
    }

    /**
     * Returns the node with the largest Key smaller than the Key in
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
    Node *prev(Node *x)
    {
        if (x->m_left) {
            return m_tree_maximum(x->m_left);
        }
        auto y{x->m_parent};
        while (y && x == y->m_left) {
            x = y;
            y = y->m_parent;
        }
        return y;
    }

    /**
     * Returns the node with the largest Key smaller than the Key in
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
    const Node *prev(const Node *x) const
    {
        if (x->m_left) {
            return m_tree_maximum(x->m_left);
        }
        auto y{x->m_parent};
        while (y && x == y->m_left) {
            x = y;
            y = y->m_parent;
        }
        return y;
    }

    /**
     * Iteratively searches the tree for the given Key.
     *
     * Based on Iterative-Tree-Search from CLRS ch. 12, p. 291.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @param key The Key to search for.
     * @return Pointer to the node with the given search key if it exists and
     *         nullptr otherwise.
     */
    Node *m_iterative_tree_search(const Key key)
    {
        auto x{m_root()};
        while (x && !(!m_comp(key, x->key()) && !m_comp(x->key(), key))) {
            if (m_comp(key, x->key())) {
                x = x->m_left;
            } else {
                x = x->m_right;
            }
        }
        return x;
    }

    /**
     * Inserts a new element in the tree or overwrites the Value for Key if it
     * already exists. Returns a pair (iterator it, bool b), where it is an
     * iterator pointing at the newly inserted/updated node, and b a boolean
     * being true if a new node was inserted, and false if an existing node was
     * updated.
     *
     * This is an O(h) operation, but since the tree is unbalanced, h = n in the
     * worst case and this becomes an O(n) operation.
     *
     * @param z The node to insert.
     * @return A pair (iterator it, bool b).
     *         If the key did not already exist in the tree, then
     *         - it is an iterator to the newly inserted node, and
     *         - b is true, indicating that the operation was successful.
     *         otherwise, if the Key did already exist, then
     *         - it is a past-the-end iterator equivalent to calling end(), and
     *         - b is false indicating that an existing node was updated
     *           instead of a new node inserted.
     */
    std::pair<iterator, bool> m_insert(Node *z)
    {
        if ((m_sentinel.m_parent)
            && (!m_comp(z->key(), m_sentinel.m_parent->key()) && !m_comp(m_sentinel.m_parent->key(), z->key()))) {
            m_sentinel.m_parent->set_value(std::move(z->m_data.second));
            m_destroy_node(z);
            return std::make_pair(iterator(this, m_root()), false);
        }
        Node *y{nullptr};
        auto x{m_sentinel.m_parent};
        while (x && x != &m_sentinel) {
            y = x;
            if (m_comp(z->key(), x->key())) {
                x = x->m_left;
            } else {
                x = x->m_right;
            }
        }
        z->m_parent = y;
        if (!y) { // tree was empty
            m_sentinel.m_parent = z;
            m_sentinel.m_left = z;
            m_sentinel.m_right = z;
            z->m_right = &m_sentinel;
        } else if (m_comp(z->key(), y->key())) {
            y->m_left = z;
            if (y == m_sentinel.m_left) { // y is the minimum and new node z is smaller
                m_sentinel.m_left = z;    // so update tree minimum
            }
        } else if (!m_comp(z->key(), y->key()) && !m_comp(y->key(), z->key())) {
            y->set_value(std::move(z->m_data.second));
            m_destroy_node(z);
            return std::make_pair(iterator(this, y), false);
        } else {
            y->m_right = z;
            if (y == m_sentinel.m_right) { // y is the maximum and new node z is greater
                m_sentinel.m_right = z;    // so update tree maximum
                z->m_right = &m_sentinel;
            }
        }
        ++m_size;
        return std::make_pair(iterator(this, z), true);
    }

    /**
     * Replaces a subtree as a child of its parent with another subtree.
     *
     * Based on Transplant from CLRS ch. 12, p. 296.
     *
     * @param u Subtree to be replaced by v.
     * @param v Subtree to replace u.
     */
    void m_transplant(Node *u, Node *v)
    {
        if (!u->m_parent) {
            m_sentinel.m_parent = v;
        } else if (u == u->m_parent->m_left) {
            u->m_parent->m_left = v;
        } else {
            u->m_parent->m_right = v;
        }
        if (v) {
            v->m_parent = u->m_parent;
        }
    }

    /**
     * Erases the node z.
     *
     * Based on Tree-Delete from CLRS ch. 12, p. 298, which relies on
     * Transplant also from CLRS ch. 12, p. 296. It is the responsibility
     * of the caller to ensure that node is not nullptr.
     *
     * This is an O(h) operation due to the call to m_tree_minimum, but since
     * the tree is unbalanced, h = n in the worst case and this becomes an
     * O(n) operation.
     *
     * @param z The node to erase.
     */
    void m_erase(Node *z)
    {
        if (empty() || !z) {
            return;
        }
        Node *tree_next{next(z)};
        Node *tree_prev{prev(z)};
        if (z->m_right == &m_sentinel) {
            z->m_right = nullptr;
        }
        if (!z->m_left) {
            m_transplant(const_cast<Node *>(z), z->m_right);
        } else if (!z->m_right) {
            m_transplant(const_cast<Node *>(z), z->m_left);
        } else {
            auto y = m_tree_minimum(z->m_right);
            if (y->m_parent != z) {
                m_transplant(y, y->m_right);
                y->m_right = z->m_right;
                y->m_right->m_parent = y;
            }
            m_transplant(const_cast<Node *>(z), y);
            y->m_left = z->m_left;
            y->m_left->m_parent = y;
        }
        if (z == m_sentinel.m_left) {
            m_sentinel.m_left = tree_next;
        }
        if (z == m_sentinel.m_right) {
            m_sentinel.m_right = tree_prev;
            if (m_sentinel.m_right) {
                m_sentinel.m_right->m_right = &m_sentinel;
            }
        }
        delete z;
        --m_size;
    }

    /**
     * Allows the tree to be printed to stdout. This is mainly intended for debugging.
     */
    friend
    std::ostream &operator<<(std::ostream &s, const Tree<Key, Value, Comp> &t)
    {
        using TNode = Tree<Key, Value, Comp>::Tree_node;

        auto q{std::queue<TNode *>()};
        q.push(t.m_sentinel.m_parent);
        s << "&m_sentinel: " << &t.m_sentinel
          << " P: " << t.m_sentinel.m_parent
          << " L: " << t.m_sentinel.m_left
          << " R: " << t.m_sentinel.m_right << '\n';
        while (!q.empty()) {
            TNode *node = q.front();
            q.pop();

            if (node && node != &t.m_sentinel) {
                s << node << ": " << node->key() << ", " << node->value() << ": P: " << node->m_parent << " ";
                if (node->m_left) {
                    s << "L: " << node->m_left << ": " << node->m_left->key() << ", " << node->m_left->value() << " ";
                } else {
                    s << "L: " << node->m_left << ": null ";
                }
                if (node->m_right) {
                    s << "R: " << node->m_right << ": " << node->m_right->key() << ", " << node->m_right->value()
                      << " ";
                } else {
                    s << "R: " << node->m_right << ": null ";
                }
                s << std::endl;
                q.push(node->m_left);
                q.push(node->m_right);
            }
        }
        return s;
    }

    /**
     * Number of elements (Key-Value pairs / nodes) stored in this tree
     */
    int m_size;

    /**
     * Comparator to compare Keys. Defaults to std::less<Key>
     */
    Comp m_comp;

    /**
     * We store a sentinel node to have a past-the-end node to return when
     * calling end(). In addition, we use it as a storage for pointers, where
     *
     *   - m_sentinel.m_parent    is a pointer to the root
     *   - m_sentinel.m_left      is a pointer to the smallest Key in the tree,
     *                            i.e. it allows begin() and front() to return
     *                            in constant time.
     *   - m_sentinel.m_right     is a pointer to the largest Key in the tree,
     *                            i.e. it allows back() to return in constant
     *                            time.
     *
     * Note that unlike in a Red-Black Tree, we do not use the sentinel as a
     * replacement for NIL, meaning all nodes still use nullptr to indicate a that
     * a node does not exist, with ONE exception: we allow the node with the largest
     * Key (i.e. the node one would get by calling m_tree_maximum(m_sentinel.m_parent))
     * to have its right child m_right point to the sentinel, as this then places the
     * sentinel correctly as the past-the-end node for when iterating over the tree.
     */
    Node m_sentinel;
};

/**
 * Checks for equality between the key-value pairs stored in the trees.
 *
 * Uses std::equal and iterators from each tree as in the stl implementation.
 *
 * In the worst case, we have to check all elements thus this is an O(n) time operation.
 *
 * @param lhs Left-hand side operand of inequality operator.
 * @param rhs right-hand side operand of inequality operator.
 * @return true if lhs is equal to rhs and false otherwise.
 */
template<typename Key, typename Value, typename Comp = std::less<Key>>
bool operator==(const Tree<Key, Value, Comp> &lhs, const Tree<Key, Value, Comp> &rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/**
 * Checks for inequality between the key-value pairs stored in each tree.
 *
 * Uses the negation of operator== to check for inequality. Please refer to operator==
 * for further details.
 *
 * In the worst case, we have to check all elements thus this is an O(n) time operation.
 *
 * @param lhs Left-hand side operand of inequality operator.
 * @param rhs right-hand side operand of inequality operator.
 * @return true if lhs is not equal to rhs and false otherwise.
 */
template<typename Key, typename Value, typename Comp = std::less<Key>>
bool operator!=(const Tree<Key, Value, Comp> &lhs, const Tree<Key, Value, Comp> &rhs)
{
    return !(lhs == rhs);
}

} // namespace DM852

#endif //TREE_HPP
