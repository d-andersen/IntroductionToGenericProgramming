/**
 * @file Tree.cpp
 * @author Dennis Andersen - deand17
 * @brief Binary Tree source file.
 * @date 2022-04-01
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 1 - Spring 2022
 *
 * Implementation of Binary Search Tree mapping integers to strings.
 */
#include "Queue.hpp"
#include "Tree.hpp"

#include <iostream>
#include <string>

namespace DM852
{
Tree::Tree() : n(0), root(nullptr) {}

Tree::Tree(const Tree &other) : n(0), root(nullptr)
{
    auto q {Queue<const Node *>()};
    auto x = other.begin();
    while (x->parent) { // find root of other
        x = x->parent;
    }
    q.push(x);
    while(!q.empty()) {
        auto node = q.front();
        q.pop();
        if (node) {
            insert(node->key, node->value);
            q.push(node->left);
            q.push(node->right);
        }
    }
}

Tree::~Tree()
{
    clear();
}

Tree &Tree::operator=(const Tree &other)
{
    auto tmp = other;
    swap(*this, tmp);
    return *this;
}

int Tree::size() const
{
    return n;
}

bool Tree::empty() const
{
    return size() == 0;
}

std::pair<Tree::Node*, bool> Tree::insert(int key, const std::string &value)
{
    if (root && key == root->key) {
        root->value = value;
        return std::make_pair(root, false);
    }
    Node *y {nullptr};
    auto x {root};
    auto z {new Node(key, value)};
    while (x) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (!y) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else if (z->key == y->key) {
        y->value = value;
        delete z;
        return std::make_pair(y, false);
    } else {
        y->right = z;
    }
    ++n;
    return std::make_pair(z, true);
}

Tree::Node *Tree::find(int key)
{
    return iterative_tree_search(key);
}

const Tree::Node *Tree::find(int key) const
{
    return iterative_tree_search(key);
}

void Tree::clear()
{
    postorder_erase_tree(root);
    root = nullptr;
    n = 0;
}

void Tree::erase(int key)
{
    auto node = find(key);
    if (node) {
        erase(node);
    }
}

void Tree::erase(const Node *node)
{
    if (empty() || !node) {
        return;
    }
    if (!node->left) {
        transplant(const_cast<Node *>(node), node->right);
    } else if (!node->right) {
        transplant(const_cast<Node *>(node), node->left);
    } else {
        auto y = tree_minimum(node->right);
        if (y->parent != node) {
            transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(const_cast<Node *>(node), y);
        y->left = node->left;
        y->left->parent = y;
    }
    delete node;
    --n;
}

std::string &Tree::front()
{
    return tree_minimum(root)->value;
}

const std::string &Tree::front() const
{
    return tree_minimum(root)->value;
}

std::string &Tree::back()
{
    return tree_maximum(root)->value;
}

const std::string &Tree::back() const
{
    return tree_maximum(root)->value;
}

Tree::Node * Tree::begin()
{
    return root ? tree_minimum(root) : nullptr;
}

const Tree::Node *Tree::begin() const
{
    return root ? tree_minimum(root) : nullptr;
}

Tree::Node *Tree::end()
{
    return nullptr;
}

const Tree::Node *Tree::end() const
{
    return nullptr;
}

Tree::Node *Tree::tree_minimum(Tree::Node* node)
{
    while (node->left) {
        node = node->left;
    }
    return node;
}

Tree::Node *Tree::tree_maximum(Tree::Node* node)
{
    while (node->right) {
        node = node->right;
    }
    return node;
}

void swap(Tree &lhs, Tree &rhs) noexcept
{
    using std::swap;
    swap(lhs.n, rhs.n);
    swap(lhs.root, rhs.root);
}

std::ostream &operator<<(std::ostream &s, const Tree &t)
{
    auto q {Queue<const Tree::Node *>()};
    q.push(t.root);
    while(!q.empty()) {
        auto *node = q.front();
        q.pop();

        if (node) {
            s << node->key << ": ";
            if (node->left) {
                s << "L: " << node->left->key << " ";
            } else {
                s << "L: null ";
            }
            if (node->right) {
                s << "R: " << node->right->key << " ";
            } else {
                s << "R: null ";
            }
            s << std::endl;
            q.push(node->left);
            q.push(node->right);
        }
    }
    return s;
}

Tree::Node::Node(const int key, std::string value) :
        key(key), value(std::move(value)), parent(nullptr), left(nullptr), right(nullptr) {}

Tree::Node::~Node() = default;

Tree::Node *Tree::Node::next()
{
    auto x {this};
    if (x->right) {
        return tree_minimum(x->right);
    }
    auto y {x->parent};
    while (y && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

const Tree::Node *Tree::Node::next() const
{
    auto x {this};
    if (x->right) {
        return tree_minimum(x->right);
    }
    auto y {x->parent};
    while (y && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

Tree::Node *Tree::Node::prev()
{
    auto x {this};
    if (x->left) {
        return tree_maximum(x->left);
    }
    auto y {x->parent};
    while (y && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

const Tree::Node *Tree::Node::prev() const
{
    auto x {this};
    if (x->left) {
        return tree_maximum(x->left);
    }
    auto y {x->parent};
    while (y && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

Tree::Node *Tree::iterative_tree_search(int key) const
{
    auto node {root};
    while (node && key != node->key) {
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

void Tree::transplant(Node *u, Node *v)
{
    if (!u->parent) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v) {
        v->parent = u->parent;
    }
}

void Tree::postorder_erase_tree(Node *x)
{
    if (x) {
        postorder_erase_tree(x->left);
        postorder_erase_tree(x->right);
        delete x;
    }
}

bool operator==(const Tree &lhs, const Tree &rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }
    auto rhs_node = rhs.begin();
    for (auto lhs_node = lhs.begin(); lhs_node != lhs.end(); lhs_node = lhs_node->next()) {
        if (lhs_node->key != rhs_node->key) {
            return false;
        }
        if (lhs_node->value != rhs_node->value) {
            return false;
        }
        rhs_node = rhs_node->next();
    }
    return true;
}

bool operator!=(const Tree &lhs, const Tree &rhs)
{
    return !(lhs == rhs);
}

} // namespace DM852