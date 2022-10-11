/**
 * @file special_member_functions_for_move_semantics.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"
#include "utilities\classes\named.h"

#include <iostream>


REFERENCES(
  "[1] https://github.com/AnthonyCalandra/modern-cpp-features#special-member-functions-for-move-semantics\n"
  "[2] https://stackoverflow.com/questions/9029368/is-return-value-always-a-temporary\n"
  "[3] https://en.cppreference.com/w/cpp/language/return#Notes\n"
  "[4] https://en.cppreference.com/w/cpp/language/copy_elision\n")

//<<
namespace {
// @see utilities\classes\named.h for the definition of the named class.
using namedA = named<true>;

namedA f(namedA a)
{
  return a;
}

// Copy elision is guaranteed in this case in C++11/14. C++17 copy elision rules
// are different enough to warant a different test. @see ref [4]
namedA g()
{
  return namedA{};
}
}
//>>

TEST(
  special_member_functions_for_move_semantics,
  "The copy constructor and copy assignment operator are called when copies are\n"
  "made, and with C++11's introduction of move semantics, there is now a move\n"
  "constructor and move assignment operator for moves.\n",
  SECTION(
    "basic example",
    std::cout << GIVEN[0] << std::endl;
    DESC_IN("// copy elision is guaranteed in this context in C++11/14!", namedA m = g();)
    DESC_IN("// C++11/14 does not guarantee copy elision in this context, @see ref [3]", namedA a = f(namedA{});)
    IN(PROTECT(namedA john("john", false);))
    IN(namedA boby = std::move(john);)
    std::cout << std::endl;
    IN(namedA c = namedA{};)
    IN(namedA d = c;)
    IN(d = c;)
    std::cout << std::endl;
    IN(PROTECT(namedA b{"b", false};))
    IN(a = std::move(b);)
    std::cout << std::endl;
    IN(a = f(b);)
    std::cout << "DESTRUCTORS:" << std::endl;
  )
)

