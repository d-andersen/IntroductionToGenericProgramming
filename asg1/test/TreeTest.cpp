/**
 * @file TreeTest.cpp
 * @author Dennis Andersen - deand17
 * @brief Binary Tree source file.
 * @date 2022-04-04
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 1 - Spring 2022
 *
 * Test of functions specified in assignment 1 for Binary Search Tree.
 */
#include "Tree.hpp"

#include <iomanip>
#include <iostream>
#include <string>

int passed {0};
int failed {0};

void assert(bool assertion, const std::string& test_name)
{
    std::cout << "  Test: " << std::setfill(' ') << std::setw(68) << std::left << test_name;
    if (assertion) {
        ++passed;
        std::cout << "OK\n";
    } else {
        ++failed;
        std::cout << "FAIL\n";
    }
}

void print_header()
{
    std::cout << std::setfill('#') << std::setw(80) << "" << '\n';
    std::cout << "# DM852::Tree    Test of functions specified in assignment 1\n";
    std::cout << std::setfill('#') << std::setw(80) << "" << '\n';
}

void print_results()
{
    std::cout << std::setfill('#') << std::setw(80) << "" << '\n';
    std::cout << "# Results\n";
    std::cout << std::setfill('#') << std::setw(80) << "" << '\n';
    std::cout << "  Test cases:" << std::setfill(' ') << std::setw(65) << std::right << passed + failed << '\n';
    std::cout << "  Tests passed:" << std::setw(63) << std::right << passed << '\n';
    std::cout << "  Tests failed:" << std::setw(63) << std::right << failed << '\n';
    std::cout << std::setfill('#') << std::setw(80) << "" << '\n';
}

void test_size()
{
    auto t {DM852::Tree()};
    assert(t.size() == 0, "size()");
}

void test_empty()
{
    auto t {DM852::Tree()};
    assert(t.empty(), "empty()");
}

void test_insert_root()
{
    auto t {DM852::Tree()};
    auto p = t.insert(1, "1");
    assert(t.size() == 1 && p.second && p.first->key == 1,
           "insert() - root");
}

void test_insert_left_child()
{
    auto t {DM852::Tree()};
    auto p2 = t.insert(2, "2");
    auto p1 = t.insert(1, "1");
    assert(t.size() == 2
           && p1.second
           && p2.first->left->key == 1 && p1.first->parent->key == 2,
           "insert() - left child");
}

void test_insert_right_child()
{
    auto t {DM852::Tree()};
    auto p2 = t.insert(2, "2");
    auto p3 = t.insert(3, "3");
    assert(t.size() == 2
           && p3.second
           && p2.first->right->key == 3 && p3.first->parent->key == 2,
           "insert() - right child");
}

void test_insert_duplicate()
{
    auto t {DM852::Tree()};
    t.insert(1, "o");
    auto p_dup = t.insert(1, "r");
    assert(t.size() == 1
           && p_dup.first->key == 1 && p_dup.first->value == "r",
           "insert() - duplicate");
}

void test_begin_empty()
{
    auto l {DM852::Tree()};
    auto e {l.begin()};
    assert(!e, "begin() - on empty tree");
}

void test_begin()
{
    auto t {DM852::Tree()};
    auto p = t.insert(1, "1");
    auto e {t.begin()};
    assert(p.first == e, "begin()");
}

void test_end()
{
    auto t {DM852::Tree()};
    auto e = t.end();
    assert(!e, "end()");
}

void test_find_key_exists()
{
    auto t {DM852::Tree()};
    t.insert(21, "21");
    t.insert(47, "47");
    t.insert(39, "39");
    t.insert(42, "42");
    auto n = t.find(42);
    assert(n->key == 42, "find() - key exists");
}

void test_find_key_not_exists()
{
    auto t {DM852::Tree()};
    t.insert(21, "21");
    t.insert(47, "47");
    t.insert(39, "39");
    t.insert(43, "43");
    auto n = t.find(42);
    assert(!n, "find() - key does not exist");
}

void test_erase_key()
{
    auto t {DM852::Tree()};
    t.insert(21, "21");
    t.insert(47, "47");
    t.insert(39, "39");
    t.insert(42, "42");
    t.erase(42);
    auto n = t.find(42);
    assert(!n, "erase() - by key");
}

void test_erase_node()
{
    auto t {DM852::Tree()};
    t.insert(21, "21");
    t.insert(47, "47");
    t.insert(39, "39");
    t.insert(42, "42");
    const auto p = t.find(42);
    t.erase(p);
    auto n = t.find(42);
    assert(!n, "erase() - by node");
}

void test_clear()
{
    auto t {DM852::Tree()};
    t.insert(42, "42");
    t.insert(35, "35");
    t.insert(45, "45");
    t.insert(25, "25");
    t.insert(40, "40");
    t.insert(44, "44");
    t.insert(47, "47");
    t.clear();
    assert(t.empty(), "clear()");
}

void test_front()
{
    auto t {DM852::Tree()};
    t.insert(42, "42");
    t.insert(35, "35");
    t.insert(45, "45");
    t.insert(25, "25");
    t.insert(40, "40");
    t.insert(44, "44");
    t.insert(47, "47");
    auto front {t.front()};
    assert(front == "25", "front()");
}

void test_back()
{
    auto t {DM852::Tree()};
    t.insert(42, "42");
    t.insert(35, "35");
    t.insert(45, "45");
    t.insert(25, "25");
    t.insert(40, "40");
    t.insert(44, "44");
    t.insert(47, "47");
    auto back {t.back()};
    assert(back == "47", "back()");
}

void test_operator_equal()
{
    auto t1 {DM852::Tree()};
    auto t2 {DM852::Tree()};
    t1.insert(1, "1");
    t1.insert(2, "2");
    t1.insert(3, "3");
    t2.insert(1, "1");
    t2.insert(2, "2");
    t2.insert(3, "3");
    assert(t1 == t2, "operator==");
}

void test_operator_not_equal()
{
    auto t1 {DM852::Tree()};
    auto t2 {DM852::Tree()};
    t1.insert(1, "1");
    t1.insert(2, "2");
    t1.insert(3, "3");
    t2.insert(42, "42");
    t2.insert(43, "43");
    assert(t1 != t2, "operator!=");
}

void test_copy_ctor()
{
    auto t1 {DM852::Tree()};
    t1.insert(1, "1");
    t1.insert(2, "2");
    t1.insert(3, "3");
    auto t2 {t1};
    assert(t1 == t2, "copy ctor");
}

void test_copy_assign()
{
    auto t1 {DM852::Tree()};
    auto t2 {DM852::Tree()};
    t1.insert(1, "1");
    t1.insert(2, "2");
    t1.insert(3, "3");
    t2.insert(42, "42");
    t2.insert(43, "43");
    t2 = t1;
    assert(t1 == t2, "copy assign");
}

int main()
{
    print_header();
    test_size();
    test_empty();
    test_insert_root();
    test_insert_left_child();
    test_insert_right_child();
    test_insert_duplicate();
    test_begin_empty();
    test_begin();
    test_end();
    test_find_key_exists();
    test_find_key_not_exists();
    test_erase_key();
    test_erase_node();
    test_clear();
    test_front();
    test_back();
    test_operator_equal();
    test_operator_not_equal();
    test_copy_ctor();
    test_copy_assign();
    print_results();

    return 0;
}


