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


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#default-functions
https://stackoverflow.com/questions/37276413/default-move-constructor-assignment-and-deleted-copy-constructor-assignment
)--"
  )

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

TEST(
  default_functions,
R"--(
A more elegant, efficient way to provide a default implementation of a function,
such as a constructor.
)--",
  SECTION(
    "basics",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(A a, b;))
    IN(print_safe("\t%i %i\n", a.i, b.i);)
    IN(b.i = 111;)
    IN(A c(b);)
    IN(print_safe("\t%i\n", c.i);)
    IN_DESC(b = std::move(a);, "since move assignment is deleted implicitely, copy assignment operator is used!")
  )
  SECTION(
    "defaulted functions in inheritance context",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(B b;)
    IN_ERROR(B b2(b);, "error C2280: 'B::B(const B &)': attempting to reference a deleted function")
    IN(B b2;)
    IN_ERROR(b2 = b;, "error C2280: 'B &B::operator =(const B &)': attempting to reference a deleted function")
    print_safe("\n");
    IN(C c;)
    IN_ERROR(C c2 = c;, "error C2280: 'C::C(const C &)': attempting to reference a deleted function")
    IN(C c2;)
    IN(c2 = std::move(c);)
  )
)

