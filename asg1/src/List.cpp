/**
 * @file List.cpp
 * @author Dennis Andersen - deand17
 * @brief Doubly Linked List source file.
 * @date 2022-04-01
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 1 - Spring 2022
 *
 * Implementation of Doubly Linked List for strings.
 */
#include "List.hpp"

#include <iostream>
#include <string>

namespace DM852
{
List::List() : n(0), head(nullptr), tail(nullptr) {}

List::List(const List& other) : n(0), head(nullptr), tail(nullptr)
{
    for (auto node = other.begin(); node != other.end(); node = node->next) {
        push_back(node->data);
    }
}

List::~List()
{
    clear();
}

List &List::operator=(const List &other) noexcept
{
    auto tmp = other;
    swap(*this, tmp);
    return *this;
}

int List::size() const
{
    return n;
}

bool List::empty() const
{
    return size() == 0;
}

void List::push_back(const std::string &elem)
{
    auto *new_node {new Node(elem)};
    insert_node(nullptr, new_node);
}

List::Node *List::insert(Node *node, const std::string &elem)
{
    auto *new_node {new Node(elem)};
    insert_node(node, new_node);
    return new_node;
}

void List::clear()
{
    while (size() > 0) {
        pop_back();
    }
}

void List::pop_back()
{
    erase_node(tail);
}

void List::erase(Node *node)
{
    erase_node(node);
}

std::string &List::front()
{
    return head->data;
}

const std::string &List::front() const
{
    return head->data;
}

std::string &List::back()
{
    return tail->data;
}

const std::string &List::back() const
{
    return tail->data;
}

List::Node *List::begin()
{
    return head;
}

const List::Node *List::begin() const
{
    return head;
}

List::Node *List::end()
{
    return nullptr;
}

const List::Node *List::end() const
{
    return nullptr;
}

List::Node::Node(std::string data) : data(std::move(data)), next(nullptr), prev(nullptr) {}

List::Node::~Node() = default;

void swap(List &lhs, List &rhs) noexcept
{
    using std::swap;
    swap(lhs.n, rhs.n);
    swap(lhs.head, rhs.head);
    swap(lhs.tail, rhs.tail);
}

std::ostream &operator<<(std::ostream &s, const List &l)
{
    List::Node *node = l.head;
    for (int i = 0; i != l.size(); ++i) {
        if (i > 0) {
            s << "<->";
        }
        s << "[" << node->data << "]";
        node = node->next;
    }
    return s;
}

void List::insert_node(Node *node, Node *new_node)
{
    if (empty()) {
        insert_into_empty_list(new_node);
    } else if (!node) {
        insert_back(new_node);
    } else if (node == head) {
        insert_front(new_node);
    } else {
        insert_middle(node, new_node);
    }
    ++n;
}

void List::insert_into_empty_list(Node *new_node)
{
    head = new_node;
    tail = head;
}

void List::insert_back(Node *new_node)
{
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
}

void List::insert_front(Node *new_node)
{
    head->prev = new_node;
    new_node->next = head;
    head = new_node;
}

void List::insert_middle(Node *node, Node *new_node)
{
    new_node->prev = node->prev;
    new_node->next = node;
    node->prev->next = new_node;
    node->prev = new_node;
}

void List::erase_node(Node *node)
{
    if (empty() || !node) {
        return;
    }

    if (node == tail && tail == head) {
        erase_single_elem_list();
    } else if (node == tail) {
        erase_back();
    } else if (node == head) {
        erase_front();
    } else {
        erase_middle(node);
    }
    --n;
}

void List::erase_single_elem_list()
{
    delete tail;
    head = nullptr;
    tail = nullptr;
}

void List::erase_back()
{
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
}

void List::erase_front()
{
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
}

void List::erase_middle(Node *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

bool operator==(const List &lhs, const List &rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }
    auto rhs_node = rhs.begin();
    for (auto lhs_node = lhs.begin(); lhs_node != lhs.end(); lhs_node = lhs_node->next) {
        if (lhs_node->data != rhs_node->data) {
            return false;
        }
        rhs_node = rhs_node->next;
    }
    return true;
}

bool operator!=(const List &lhs, const List &rhs)
{
    return !(lhs == rhs);
}

} // namespace DM852
