/**
 * @file final_specifier.cpp
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


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#final-specifier")

namespace {
struct A {
  virtual const char* foo()
  {
    return "A";
  }
};

struct B : A {
  virtual const char* foo() override final
  {
    return "B";
  }
};

struct C : B {
  // error C3248: 'B::foo': function declared as 'final' cannot be overridden by 'C::foo'
  //virtual const char* foo() override{ return "C"; }
};
}

namespace {
struct D final : A {
  const char* foo() override
  {
    return "D";
  }
};

// error C3246: 'E': cannot inherit from 'D' as it has been declared as 'final'
// struct E : D {};
}

TEST(
  final_specifier,
R"--(
Specifies that a virtual function cannot be overridden in a derived class or
that a class cannot be inherited from.
)--",
  SECTION(
    "final virtual member functions",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(A a;)
    IN(B b;)
    IN(C c;)
    IN(A* ptr = &a;)
    IN(print_safe("\t%s\n", ptr->foo());)
    IN(ptr = &b;)
    IN(print_safe("\t%s\n", ptr->foo());)
    IN(ptr = &c;)
    IN(print_safe("\t%s\n", ptr->foo());)
  )
  SECTION(
    "A class marked final cannot be inherited at all!",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(D d;)
    IN(A* ptr = &d;)
    IN(print_safe("\t%s\n", ptr->foo());)
  )
)

