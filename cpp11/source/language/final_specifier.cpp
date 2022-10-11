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

#include <iostream>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#final-specifier\n")
TODO(
  "1- Provide a way to indicate error in parsed code see 'struct C' without\n" 
  "commenting the code.\n")

//<<
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
//>>

//<<
struct D final : A {
  const char* foo() override
  {
    return "D";
  }
};

// error C3246: 'E': cannot inherit from 'D' as it has been declared as 'final'
// struct E : D {};
//>>

TEST(
  final_specifier,
  "Specifies that a virtual function cannot be overridden in a derived class or\n" 
  "that a class cannot be inherited from.\n",
  SECTION(
    "final virtual member functions",
    std::cout << GIVEN[0] << std::endl;
    IN(A a;)
    IN(B b;)
    IN(C c;)
    IN(A* ptr = &a;)
    IN(std::cout << '\t' << ptr->foo() << std::endl;)
    IN(ptr = &b;)
    IN(std::cout << '\t' << ptr->foo() << std::endl;)
    IN(ptr = &c;)
    IN(std::cout << '\t' << ptr->foo() << std::endl;)
  )
  SECTION(
    "A class marked final cannot be inherited at all!",
    std::cout << GIVEN[1] << std::endl;
    IN(D d;)
    IN(A* ptr = &d;)
    IN(std::cout << '\t' << ptr->foo() << std::endl;)
  )
)

