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


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#special-member-functions-for-move-semantics
https://stackoverflow.com/questions/9029368/is-return-value-always-a-temporary
https://en.cppreference.com/w/cpp/language/return#Notes
https://en.cppreference.com/w/cpp/language/copy_elision
)--"
)

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

TEST(
  special_member_functions_for_move_semantics,
R"--(
The copy constructor and copy assignment operator are called when copies are
made, and with C++11's introduction of move semantics, there is now a move
constructor and move assignment operator for moves.
)--",
  SECTION(
    "basic example",
    print_safe("%s\n", GIVEN[0].c_str());
    DESC_IN("copy elision is guaranteed in this context in C++11/14!", namedA m = g();)
    DESC_IN("C++11/14 does not guarantee copy elision in this context, @see ref [3]", namedA a = f(namedA{});)
    IN(PROTECT(namedA john("john", false);))
    IN(namedA boby = std::move(john);)
    print_safe("\n");
    IN(namedA c = namedA{};)
    IN(namedA d = c;)
    IN(d = c;)
    print_safe("\n");
    IN(PROTECT(namedA b{"b", false};))
    IN(a = std::move(b);)
    print_safe("\n");
    IN(a = f(b);)
    print_safe("DESTRUCTORS:\n");
  )
)

