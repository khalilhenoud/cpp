/**
 * @file default_functions.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>


REFERENCES(
  "[0] https://github.com/AnthonyCalandra/modern-cpp-features#default-functions\n"
  "[1] https://stackoverflow.com/questions/37276413/default-move-constructor-assignment-and-deleted-copy-constructor-assignment\n")

TODO(
  "Provide an encapsulation output functionality 'std::cout'... This becomes\n"
  "necessary when switching to a non-console display.\n")

//<<
namespace {
struct A {
  A() = default;
  // see ref [1] in regards to the deleting of move constructors/operators.
  A(const A&) = default;
  A& operator=(const A& rhs)
  {
    ANNOUNCE(true);
    i = rhs.i;
    return *this;
  }

  int32_t i = 10;
};
}
//>>

//<< 
namespace {
struct B {
  B() : i(1000) {}
  virtual ~B() = default;
  // note: 'B::B(const B &)': function was implicitly deleted because 'B' has a
  // user-defined move constructor
  B(B&&) noexcept = default;
  // note: 'B &B::operator =(const B &)': function was implicitly deleted
  // because 'B' has a user-defined move constructor
  B& operator=(B&&) noexcept = default;

  int32_t i = -1;
};

struct C : B {
  C() = default;
  // note: 'C::C(const C &)': function was implicitly deleted because a base
  // class invokes a deleted or inaccessible function 'B::B(const B &)'
};
}
//>>

TEST(
  default_functions,
  "A more elegant, efficient way to provide a default implementation of a\n" 
  "function, such as a constructor.\n",
  SECTION(
    "basics",
    std::cout << GIVEN[0] << std::endl;
    IN(PROTECT(A a, b;))
    IN(std::cout << '\t' << a.i << std::ends << b.i << std::endl;)
    IN(b.i = 111;)
    IN(A c(b);)
    IN(std::cout << '\t' << c.i << std::endl;)
    IN_DESC(b = std::move(a);, "since move assignment is deleted implicitely, copy assignment operator is used!")
  )
  SECTION(
    "defaulted functions in inheritance context",
    std::cout << GIVEN[1] << std::endl;
    IN(B b;)
    IN_ERROR(B b2(b);, "error C2280: 'B::B(const B &)': attempting to reference a deleted function")
    IN(B b2;)
    IN_ERROR(b2 = b;, "error C2280: 'B &B::operator =(const B &)': attempting to reference a deleted function")
    std::cout << std::endl;
    IN(C c;)
    IN_ERROR(C c2 = c;, "error C2280: 'C::C(const C &)': attempting to reference a deleted function")
    IN(C c2;)
    IN(c2 = std::move(c);)
  )
)

