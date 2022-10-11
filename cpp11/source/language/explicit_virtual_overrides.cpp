/**
 * @file explicit_virtual_overrides.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#explicit-virtual-overrides\n")

//<<
namespace {
struct A {
  virtual const char* foo()
  {
    return "A";
  }

  void bar()
  {}
};

struct B : A {
  const char* foo() override
  {
    return "B";
  }

  //void bar() override; // error C3668: 'B::bar': method with override
  //specifier 'override' did not override any base class method
  //void baz() override; // error C3668: 'B::baz': method with override
  //specifier 'override' did not override any base class methods
};
}
//>>

TEST(
  explicit_virtual_overrides,
  "Specifies that a virtual function overrides another virtual function. If the\n" 
  "virtual function does not override a parent's virtual function, throws a\n" 
  "compiler error.\n",
  std::cout << GIVEN[0] << std::endl;
  IN(B b;)
  IN(A* ptr = &b;)
  IN(std::cout << '\t' << ptr->foo() << std::endl;)
)

