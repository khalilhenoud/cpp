/**
 * @file nullptr.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#nullptr\n"
  "https://stackoverflow.com/questions/1282295/what-exactly-is-nullptr#:~:text=According%20to%20cppreference%2C%20nullptr%20is,any%20pointer%20to%20member%20type")

namespace {
const char* foo(int n)
{
  return "foo(int)";
}

const char* foo(char* c)
{
  return "foo(char *)";
}
}

TEST(
  nullptr_basics,
  "C++11 introduces a new null pointer type designed to replace C's NULL macro.\n" 
  "nullptr itself is of type std::nullptr_t and can be implicitly converted into\n"
  "pointer types, and unlike NULL, not convertible to integral types except bool.",
  SECTION(
    "nullptr is a prvalue and a pointer literal of std::nullptr_t type.",
    std::cout << GIVEN[0] << std::endl;
    IN_ERROR(std::cout << foo(NULL) << std::endl;, "error: call of overloaded 'foo(NULL)' is ambiguous")
    IN(std::cout << foo(nullptr) << std::endl;)
    IN(std::cout << (sizeof(nullptr) == sizeof(void*)) << std::endl;)
  )
)

