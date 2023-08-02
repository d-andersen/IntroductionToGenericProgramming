/**
 * @file ListTest.cpp
 * @author Dennis Andersen - deand17
 * @brief Binary Tree source file.
 * @date 2022-04-06
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 1 - Spring 2022
 *
 * Test of functions specified in assignment 1 for Doubly Linked List.
 */
#include "List.hpp"

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
    std::cout << "# DM852::List    Test of functions specified in assignment 1\n";
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
    auto l {DM852::List()};
    assert(l.size() == 0, "size()");
}

void test_empty()
{
    auto l {DM852::List()};
    assert(l.empty(), "empty()");
}

void test_push_back()
{
    auto l {DM852::List()};
    l.push_back("1");
    assert(l.size() == 1, "push_back()");
}

void test_begin_empty()
{
    auto l {DM852::List()};
    auto e {l.begin()};
    assert(!e, "begin() - on empty list");
}

void test_begin()
{
    auto l {DM852::List()};
    l.push_back("1");
    auto e {l.begin()};
    assert(e, "begin()");
}

void test_end()
{
    auto l {DM852::List()};
    auto e = l.end();
    assert(!e, "end()");
}

void test_insert_front()
{
    auto l {DM852::List()};
    l.push_back("1");
    auto e1 {l.begin()};
    auto e2 = l.insert(e1, "2");
    assert((e1->prev->data == "2" && e2->next->data == "1" && l.size() == 2), "insert() - front");
}

void test_insert()
{
    auto l {DM852::List()};
    l.insert(nullptr, "1");
    auto e2 {l.insert(nullptr, "2")};
    auto e3 {l.insert(nullptr, "3")};
    l.insert(nullptr, "4");
    l.insert(e3, "5");
    assert((e2->next->data == "5" && e3->prev->data == "5" && l.size() == 5), "insert()");
}

void test_pop_back()
{
    auto l {DM852::List()};
    l.push_back("1");
    l.pop_back();
    assert(l.empty(), "pop_back()");
}

void test_erase()
{
    auto l {DM852::List()};
    auto e1 {l.insert(nullptr, "1")};
    auto e2 {l.insert(nullptr, "2")};
    auto e3 {l.insert(nullptr, "3")};
    l.erase(e2);
    assert((e1->next->data == "3" && e3->prev->data == "1" && l.size() == 2), "erase()");
}

void test_clear()
{
    auto l {DM852::List()};
    l.push_back("1");
    l.push_back("2");
    l.push_back("3");
    l.clear();
    assert(l.empty(), "clear()");
}

void test_front()
{
    auto l {DM852::List()};
    l.push_back("1");
    l.push_back("2");
    l.push_back("3");
    auto front {l.front()};
    assert(front == "1", "front()");
}

void test_back()
{
    auto l {DM852::List()};
    l.push_back("1");
    l.push_back("2");
    l.push_back("3");
    auto back {l.back()};
    assert(back == "3", "back()");
}

void test_operator_equal()
{
    auto l1 {DM852::List()};
    auto l2 {DM852::List()};
    l1.push_back("1");
    l1.push_back("2");
    l1.push_back("3");
    l2.push_back("1");
    l2.push_back("2");
    l2.push_back("3");
    assert(l1 == l2, "operator==");
}

void test_operator_not_equal()
{
    auto l1 {DM852::List()};
    auto l2 {DM852::List()};
    l1.push_back("1");
    l1.push_back("2");
    l1.push_back("3");
    l2.push_back("3");
    l2.push_back("2");
    assert(l1 != l2, "operator!=");
}

void test_copy_ctor()
{
    auto l1 {DM852::List()};
    l1.push_back("1");
    l1.push_back("2");
    l1.push_back("3");
    auto l2 {l1};
    assert(l1 == l2, "copy ctor");
}

void test_copy_assign()
{
    auto l1 {DM852::List()};
    auto l2 {DM852::List()};
    l1.push_back("1");
    l1.push_back("2");
    l1.push_back("3");
    l2.push_back("4");
    l2.push_back("5");
    l2 = l1;
    assert(l1 == l2, "copy assign");
}

int main()
{
    print_header();
    test_size();
    test_empty();
    test_push_back();
    test_begin_empty();
    test_begin();
    test_end();
    test_insert_front();
    test_insert();
    test_pop_back();
    test_erase();
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


