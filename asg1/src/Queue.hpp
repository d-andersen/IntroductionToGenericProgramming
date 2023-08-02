/**
 * @file Queue.hpp
 * @author Dennis Andersen - deand17
 * @brief Binary Tree source file.
 * @date 2022-04-04
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 1 - Spring 2022
 *
 * This is a very naive and basic implementation of a FIFO queue to serve as a
 * replacement for std::queue.
 *
 * The reason this exists is because I wanted to be able to do a BFS traversal
 * of the binary tree, which is made easier by having a FIFO queue and I was
 * unsure if I was allowed to use std::queue, so to be on the safe side, I
 * decided to just implement a very basic queue myself to do only what I needed.
 */
#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace DM852
{

template<class T>
class Queue
{
public:
    /**
     * Default constructor
     */
    Queue() : n(0), head(nullptr), tail(nullptr) {}

    /**
     * Destructor
     */
    ~Queue()
    {
        while (!empty()) {
            pop();
        }
    }

    /**
     * Returns the number of elements stored.
     *
     * @return the number of elements stored.
     */
    int size() const
    {
        return n;
    }

    /**
     * Returns true iff the container is empty, i.e. empty() == (size() == 0).
     *
     * @return true if the queue is empty and false otherwise.
     */
    bool empty() const
    {
        return n == 0;
    }

    /**
     * Push an element to the back of the queue.
     *
     * @param elem Element to add to the back of the queue.
     */
    void push(const T &elem);

    /**
     * Remove an element from the front of the queue.
     */
    void pop();

    /**
     * Get the element at the front of the queue.
     *
     * @return Return a copy of the element at the front of the queue.
     */
    T front() const;

    class Node
    {
    public:
        explicit Node(T data) : data(data), next(nullptr), prev(nullptr) {}

        ~Node() = default;

        T data;
        Node *next;
        Node *prev;
    };

private:
    int n;
    Node *head;
    Node *tail;
};

template<class T>
void Queue<T>::push(const T &elem)
{
    auto *new_node {new Node(elem)};
    if (empty()) {
        head = new_node;
        tail = head;
    } else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    ++n;
}

template<class T>
void Queue<T>::pop()
{
    if (n > 1) {
        head = head->next;
        delete head->prev;
        --n;
        if (n == 1) {
            tail = head;
        }
    } else if (n == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        --n;
    }
}

template<class T>
T Queue<T>::front() const
{
    return head ? head->data : nullptr;
}

}

#endif //QUEUE_HPP
