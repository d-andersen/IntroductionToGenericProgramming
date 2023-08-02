/**
 * @file TreeTest.cpp
 * @author Dennis Andersen - deand17
 * @brief Generic doubly linked list test.
 * @date 2022-05-14
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 2 - Spring 2022
 *
 * Test of functions specified in assignment 2 for generic doubly linked list.
 */
#include "List.hpp"

#include <iostream>
#include <string>

int main()
{
    auto l1{DM852::List<std::string>()};

    std::string s1{"s1"};
    std::string s2{"s2"};
    std::string s3{"s3"};

    l1.push_back(std::move(s1));
    l1.push_back(std::move(s2));
    l1.push_back(std::move(s3));

    for (auto &it : l1) {
        std::cout << it << '\n';
        it += "wat";
        std::cout << it << '\n';
    }

    for (DM852::List<std::string>::const_iterator it = l1.begin(); it != l1.end(); ++it) {
        std::cout << *it << '\n';
    }

    auto l2{DM852::List<std::string>()};
    auto l3{DM852::List<std::string>()};

    l2.push_back("1");
    l2.push_back("2");
    l2.push_back("3");
    l3.push_back("1");
    l3.push_back("2");
    l3.push_back("3");

    std::cout << std::boolalpha << "(l2 == l3)? " << (l2 == l3) << '\n';
    std::cout << std::boolalpha << "(l2 != l3)? " << (l2 != l3) << '\n';

    l3.push_back("unequal");

    std::cout << std::boolalpha << "(l2 == l3)? " << (l2 == l3) << '\n';
    std::cout << std::boolalpha << "(l2 != l3)? " << (l2 != l3) << '\n';

    return 0;
}
