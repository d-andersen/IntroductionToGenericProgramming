/**
 * @file TreeTest.cpp
 * @author Dennis Andersen - deand17
 * @brief Generic binary tree test.
 * @date 2022-05-14
 *
 * DM852 Introduction to Generic Programming
 *
 * Assignment 2 - Spring 2022
 *
 * Test of functions specified in assignment 2 for generic binary tree.
 */
#include "Tree.hpp"

#include <iostream>
#include <string>

int main()
{

    auto t1{DM852::Tree<int, std::string>()};

    t1.insert(42, std::string("s42"));
    t1.insert(10, std::string("s10"));
    t1.insert(87, std::string("s87"));

    std::cout << t1 << "\n";

    auto t2{DM852::Tree<int, std::string>()};

    t2.insert(42, std::string("s42"));
    t2.insert(10, std::string("s10"));
    t2.insert(87, std::string("s87"));
    t2.insert(56, std::string("s56"));

    std::cout << t2 << "\n";

    std::cout << std::boolalpha << "(t1 == t2)? " << (t1 == t2) << '\n';
    std::cout << std::boolalpha << "(t1 != t2)? " << (t1 != t2) << '\n';

    auto t{DM852::Tree<int, std::string>()};

    t.insert(42, std::string("s42"));
    t.insert(10, std::string("s10"));
    t.insert(87, std::string("s87"));
    t.insert(56, std::string("s56"));
    t.insert(99, std::string("s99"));
    t.insert(56, std::string("s56"));
    t.insert(57, std::string("s57"));
    t.insert(18, std::string("s18"));

    t.insert(2, std::string("s2"));

    t.insert(42, std::string("s42updated"));

    t.insert(18, std::string("s18updated"));

    std::cout << t << '\n';
    std::cout << t.size() << '\n';

    auto it = t.find(42);
    auto [k, v] = *it;

    std::cout << "searched for 42, found: " << k << ", " << v << '\n';

    it = t.find(2);
    auto [k1, v1] = *it;

    std::cout << "searched for 2, found: " << k1 << ", " << v1 << '\n';

    it = t.find(99);
    auto [k2, v2] = *it;
    std::cout << "searched for 99, found: " << k2 << ", " << v2 << '\n';

    it = t.find(43);
    auto [k3, v3] = *it;
    std::cout << "searched for 43, found: " << k3 << ", " << v3 << '\n';

    t.erase(42);

    std::cout << t << '\n';
    std::cout << t.size() << '\n';
    for (auto [k, v] : t) {
        std::cout << "k: " << k << ", " << v << " :v\n";
    }

    t.erase(2);

    std::cout << t << '\n';
    std::cout << t.size() << '\n';
    for (auto [k, v] : t) {
        std::cout << "k: " << k << ", " << v << " :v\n";
    }

    t.erase(99);

    std::cout << t << '\n';
    std::cout << t.size() << '\n';
    for (auto [k, v] : t) {
        std::cout << "k: " << k << ", " << v << " :v\n";
    }

    t.erase(18);

    std::cout << t << '\n';
    std::cout << t.size() << '\n';
    for (auto [k, v] : t) {
        std::cout << "k: " << k << ", " << v << " :v\n";
    }

    t.erase(10);

    std::cout << t << '\n';
    std::cout << t.size() << '\n';
    for (auto [k, v] : t) {
        std::cout << "k: " << k << ", " << v << " :v\n";
    }

    t.erase(87);

    std::cout << t << '\n';
    std::cout << t.size() << '\n';
    for (auto [k, v] : t) {
        std::cout << "k: " << k << ", " << v << " :v\n";
    }

    t.erase(56);

    std::cout << t << '\n';
    std::cout << t.size() << '\n';
    for (auto [k, v] : t) {
        std::cout << "k: " << k << ", " << v << " :v\n";
    }

    t.erase(57);

    std::cout << t << '\n';
    std::cout << t.size() << '\n';
    for (auto [k, v] : t) {
        std::cout << "k: " << k << ", " << v << " :v\n";
    }

    auto t3{DM852::Tree<int, std::string>()};

    t.insert(118, std::string("s118"));
    t.insert(112, std::string("s112"));
    t.insert(114, std::string("s114"));

    t3 = std::move(t);

    std::cout << t3 << '\n';




    return 0;
}
