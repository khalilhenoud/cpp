/**
 * @file smart_pointers.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"
#include "utilities\classes\named.h"

#include <iostream>
#include <memory>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#smart-pointers\n"
  "https://en.cppreference.com/w/cpp/memory/weak_ptr\n"
  "https://stackoverflow.com/questions/12030650/when-is-stdweak-ptr-useful")

TEST(
  smart_pointers,
  "C++11 introduces new smart pointers: std::unique_ptr, std::shared_ptr,\n" 
  "std::weak_ptr. std::auto_ptr now becomes deprecated and then eventually\n" 
  "removed in C++17.",
  SECTION(
    "std::unique_ptr is a non-copyable, movable pointer that manages its own\n" 
    "heap-allocated memory. Note: Prefer using the std::make_X helper functions\n" 
    "as opposed to using constructors. std::unique_ptr replaces std::auto_ptr:",
    IN_DESC(std::unique_ptr<named<true>> p1 {new named<true>("peter", false)};, "use std::make_unique in c++14.")
    IN(if (p1) p1->print_data();)
    IN(std::unique_ptr<named<true>> p2 {std::move(p1)};)
    IN(if (p1) p1->print_data();)
    IN(if (p2) p2->print_data();)
    IN(p1 = std::move(p2);)
    IN(if (p1) p1->print_data();)
    IN(if (p2) p2->print_data();)
    IN(std::cout << std::endl;)
  )
  SECTION(
    "std::shared_ptr is a smart pointer that manages a resource that is\n" 
    "shared across multiple owners. A shared pointer holds a control block\n" 
    "which has a few components such as the managed object and a reference\n" 
    "counter. All control block access is thread-safe, however, manipulating\n" 
    "the managed object itself is not thread-safe.",
    IN(std::shared_ptr<named<true>> p1 = std::make_shared<named<true>>("john", true);)
    IN(auto p2 = p1;)
    IN(p1->print_data();)
    IN(p2->print_data();)
    IN(p1->clear_data();)
    IN(p1->print_data();)
    IN(p2->print_data();)
    IN(std::cout << std::endl;)
  )
  SECTION(
    "std::weak_ptr is a very good way to solve the dangling pointer problem.\n" 
    "By just using raw pointers it is impossible to know if the referenced data\n" 
    "has been deallocated or not. Instead, by letting a std::shared_ptr manage\n" 
    "the data, and supplying std::weak_ptr to users of the data, the users can\n" 
    "check validity of the data by calling expired() or lock().",
    IN(std::shared_ptr<named<true>> p1 = std::make_shared<named<true>>("tim", false);)
    IN(std::weak_ptr<named<true>> w1 = p1;)
    IN(if (auto tmp = w1.lock()) tmp->print_data();)
    IN(p1 = std::make_shared<named<true>>("chris", false);)
    IN_DESC(if (auto tmp = w1.lock()) tmp->print_data();, "object has expired")
    IN(std::cout << std::endl;)
  )
)