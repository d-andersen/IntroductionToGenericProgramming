/**
 * @file List.hpp
 * @author Dennis Andersen - deand17
 * @brief Generic doubly linked list.
 * @date 2022-05-16
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 2 - Spring 2022
 *
 * Implementation of generic doubly linked list.
 *
 * The list is DefaultConstructible, Copyable, and EqualityComparable and should
 * therefore be a Regular type. It is also MoveConstructible and Movable.
 */
#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <memory>

namespace DM852
{
/**
 * Generic doubly linked list.
 * @tparam T Type to store.
 */
template<typename T>
struct List
{
private:
    struct List_node
    {
        using value_type = T;

        List_node() = default;

        explicit
        List_node(value_type data)
            : m_next(nullptr), m_prev(nullptr),
              m_data(std::move(data)) { }

        ~List_node() = default;

        List_node *m_next;
        List_node *m_prev;

        value_type m_data;
    };

    using Node           = List_node;

public:
    struct List_iterator;
    struct Const_list_iterator;

    using iterator       = List_iterator;
    using const_iterator = Const_list_iterator;
    using value_type     = T;

    struct List_iterator
    {
        friend struct List;

        using Node              = List_node;

        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        List_iterator(Node *x)
            : m_node(x) { }

        ~List_iterator() = default;

        reference operator*()
        {
            return m_node->m_data;
        }

        pointer operator->()
        {
            pointer p{m_node->m_data};
            return p;
        }

        List_iterator& operator++()
        {
            m_node = m_node->m_next;
            return *this;
        }

        List_iterator operator++(int)
        {
            List_iterator tmp = *this;
            m_node = m_node->m_next;
            return tmp;
        }

        List_iterator& operator--()
        {
            m_node = m_node->m_prev;
            return *this;
        }

        List_iterator operator--(int)
        {
            List_iterator tmp = *this;
            m_node = m_node->m_prev;
            return tmp;
        }

        friend bool operator==(const List_iterator& x, const List_iterator& y)
        {
            return x.m_node == y.m_node;
        };

        friend bool operator!=(const List_iterator& x, const List_iterator& y)
        {
            return x.m_node != y.m_node;
        };

    private:
        Node *m_node;
    };

    struct Const_list_iterator
    {
        friend struct List;

        using Node              = List_node;

        using difference_type   = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;

        explicit
        Const_list_iterator(const Node *x)
            : m_node(x) { }

        Const_list_iterator(const iterator it)
            : m_node(it.m_node) { }

        ~Const_list_iterator() = default;

        reference operator*() const
        {
            return m_node->m_data;
        }

        pointer operator->() const
        {
            pointer p{m_node->m_data};
            return p;
        }

        Const_list_iterator& operator++()
        {
            m_node = m_node->m_next;
            return *this;
        }

        Const_list_iterator operator++(int)
        {
            Const_list_iterator tmp = *this;
            m_node = m_node->m_next;
            return tmp;
        }

        Const_list_iterator& operator--()
        {
            m_node = m_node->m_prev;
            return *this;
        }

        Const_list_iterator operator--(int)
        {
            Const_list_iterator tmp = *this;
            m_node = m_node->m_prev;
            return tmp;
        }

        friend bool operator==(const Const_list_iterator& x, const Const_list_iterator& y)
        {
            return x.m_node == y.m_node;
        };

        friend bool operator!=(const Const_list_iterator& x, const Const_list_iterator& y)
        {
            return x.m_node != y.m_node;
        };

    private:
        const Node *m_node;
    };

    /**
     * Default constructor.
     */
    List()
        : m_size(0)
    {
        m_init();
    }

    /**
     * Copy constructor.
     *
     * @param other List to copy.
     */
    List(const List &other)
        : m_size(0)
    {
        m_init();
        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(*it);
        }
    }

    /**
     * Move constructor.
     *
     * @param other List to move from.
     */
    List(List &&other) noexcept
        : m_size(0)
    {
        m_init();
        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(std::move(*it));
        }
        other.clear();
        other.m_init();
    }

    /**
     * Default destructor.
     */
    ~List()
    {
        clear();
    }

    /**
     * Copy assignment operator.
     *
     * @param other List to copy.
     * @return A copy of other.
     */
    List &operator=(const List &other)
    {
        auto tmp = other;
        swap(*this, tmp);
        tmp.m_sentinel.m_next = &tmp.m_sentinel;
        tmp.m_sentinel.m_prev = &tmp.m_sentinel;
        m_sentinel.m_next->m_prev = &m_sentinel;
        m_sentinel.m_prev->m_next = &m_sentinel;

        return *this;
    }

    /**
     * Move assignment operator.
     *
     * @param other List to move assign from.
     * @return List with the contents of other.
     */
    List &operator=(List &&other) noexcept
    {
        std::cout << "List::operator= move assignment\n";
        m_size = std::move(other.m_size);
        m_sentinel = std::move(other.m_sentinel);
        m_sentinel.m_next->m_prev = &m_sentinel;
        m_sentinel.m_prev->m_next = &m_sentinel;
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
        return m_sentinel.m_next == &m_sentinel;
    }

    /**
     * Inserts a new element in the end, either by copy or by move.
     *
     * @param elem Element to insert.
     */
    void push_back(const value_type &elem)
    {
        Node *node{m_create_node(elem)};
        m_insert(end(), node);
    }

    /**
     * Inserts a new element in the end, either by copy or by move.
     *
     * @param elem Element to insert.
     */
    void push_back(value_type &&elem)
    {
        Node *node{m_create_node(std::move(elem))};
        m_insert(end(), node);
    }

    /**
     * Inserts a new element before the one stored at pos, and
     * returns an iterator to the node for the newly inserted element.
     *
     * @param pos Iterator to position to insert before.
     * @param elem Element to insert.
     * @return iterator to the newly inserted element.
     */
    iterator insert(const_iterator pos, const value_type &elem)
    {
        Node *node{m_create_node(elem)};
        m_insert(pos, node);
    }

    /**
     * Inserts a new element before the one stored at pos, and
     * returns an iterator to the node for the newly inserted element.
     *
     * @param pos Iterator to position to insert before.
     * @param elem Element to insert.
     * @return iterator to the newly inserted element.
     */
    iterator insert(const_iterator pos, value_type &&elem)
    {
        std::cout << "insert(value_type &&elem) called\n";
        Node *node{m_create_node(std::move(elem))};
        m_insert(pos, node);
    }

    /**
     * Erases all elements.
     */
    void clear()
    {
        while (size() > 0) {
            pop_back();
        }
        m_init();
    }

    /**
     * Erases the last element.
     */
    void pop_back()
    {
        m_erase(iterator(m_sentinel.m_prev));
    }

    /**
     * Erases the element stored at pos.
     *
     * @param pos Position of element to be deleted.
     */
    void erase(const_iterator pos)
    {
        m_erase(pos);
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
     * @return Reference to the first element.
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
        iterator tmp{end()};
        --tmp;
        return *tmp;
    }

    /**
     * Accesses the last element.
     *
     * @return Reference to the last element.
     */
    const value_type &back() const
    {
        const_iterator tmp{end()};
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
        return iterator(m_sentinel.m_next);
    }

    /**
     * Returns a const_iterator for accessing the first element
     * or a past-the-end iterator if the container is empty.
     *
     * @return iterator for accessing the first element or a
     *         past-the-end const_iterator if the container is empty.
     */
    const_iterator begin() const
    {
        return const_iterator(m_sentinel.m_next);
    }

    /**
     * Returns a past-the-end iterator.
     *
     * @return Past-the-end iterator.
     */
    iterator end()
    {
        return iterator(&m_sentinel);
    }

    /**
     * Returns a past-the-end const_iterator.
     *
     * @return Past-the-end const_iterator.
     */
    const_iterator end() const
    {
        return const_iterator(&m_sentinel);
    }

    /**
     * Swap function for applying the copy-and-swap idiom.
     *
     * @param lhs Left-hand side operand to be swapped.
     * @param rhs Right-hand side operand to be swapped.
     */
    friend
    void swap(List &lhs, List &rhs)
    {
        using std::swap;
        swap(lhs.m_size, rhs.m_size);
        swap(lhs.m_sentinel, rhs.m_sentinel);
    }

private:
    /**
     * Private initializer method.
     */
    void m_init()
    {
        m_sentinel.m_next = &m_sentinel;
        m_sentinel.m_prev = &m_sentinel;
        m_size = 0;
    }

    /**
     * Creates a new node with the value_type provided
     * in elem.
     *
     * @param elem value_type to construct node with.
     * @return Pointer to the newly created node.
     */
    Node *m_create_node(const value_type &elem)
    {
        return new List_node(elem);
    }

    /**
     * Creates a new node with the value_type provided
     * in elem.
     *
     * @param elem value_type to move construct node with.
     * @return Pointer to the newly created node.
     */
    Node *m_create_node(value_type &&elem)
    {
        return new List_node(std::move(elem));
    }

    /**
     * Inserts the node x before the iterator at position pos.
     *
     * In the worst case, this is an O(n) operation, since we may have to
     * traverse the entire list.
     *
     * Does not invalidate any iterators.
     *
     * @param pos iterator to position to insert before.
     * @param x The node to insert.
     */
    void m_insert(iterator pos, Node *x)
    {
        x->m_next = pos.m_node;
        x->m_prev = pos.m_node->m_prev;
        pos.m_node->m_prev->m_next = x;
        pos.m_node->m_prev = x;
        ++m_size;
    }

    /**
     * Erases the node stored at position pos.
     *
     * @param pos iterator to position to erase.
     */
    void m_erase(const_iterator pos)
    {
        pos.m_node->m_prev->m_next = pos.m_node->m_next;
        pos.m_node->m_next->m_prev = pos.m_node->m_prev;
        delete pos.m_node;
        --m_size;
    }

    /**
     * Number of elements stored in this list.
     */
    int m_size{};

    /**
     * We store a sentinel node to have a past-the-end node to return when
     * calling end(). In addition, we use it as a storage for pointers, where
     *
     *   - m_sentinel.m_next    is a pointer to the first element of the list
     *   - m_sentinel.m_prev    is a pointer to the last element of the list,
     *
     * The sentinel allows begin(), front(), back(), and end() to return in
     * constant time.
     */
    Node m_sentinel;
};

/**
 * Checks for equality between the value_types in the lists.
 *
 * In the worst case, we have to check all elements thus this is an O(n) time operation.
 *
 * @param lhs Left-hand side operand of inequality operator.
 * @param rhs right-hand side operand of inequality operator.
 * @return true if lhs is equal to rhs and false otherwise.
 */
template<typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/**
 * Checks for inequality between the value_types stored in each list.
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
template<typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs)
{
    return !(lhs == rhs);
}

} // namespace DM852

#endif //LIST_HPP