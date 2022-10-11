/**
 * @file attributes.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#attributes\n"
  "https://en.cppreference.com/w/cpp/language/attributes\n")

//<<
namespace {
// `noreturn` attribute indicates `f` doesn't return.
[[noreturn]] void f()
{
  throw "error";
}
}
//>>

TEST(
  attributes,
  "Attributes provide a universal syntax over __attribute__(...), __declspec,\n"
  "etc. C++11 only defines 2 attributes (noreturn, carries_dependency), more\n"
  "attributes can be supported based on the compiler. However the usage of\n"
  "attributes can be greatly extended in the proper context, see the link below:\n"
  "https://www.codesynthesis.com/~boris/blog/2012/04/18/cxx11-generalized-attributes/\n",
  SECTION(
    "'noreturn' function example",
    std::cout << GIVEN[0] << std::endl;
    IN(
      try
      {
        f();
      }
      catch (...)
      {
        std::cout << "Caught the [[noreturn]] exception throwing function. " << std::endl;
      }
    )
  )
)

