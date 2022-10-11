/**
 * @file delegating_constructors.cpp
 * @author khalilhenoud@gmailcom
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


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features\n")

//<<
namespace {
struct Foo {
  int32_t i = -1;
  Foo(int32_t val) : i{ val } {}
  Foo() : Foo(0) {}
};
}
//>>

TEST(
  delegating_constructors,
  "Constructors can now call other constructors in the same class using an\n"
  "initializer list.\n",
  SECTION(
    "basic",
    std::cout << GIVEN[0] << std::endl;
    IN(Foo foo;)
    IN(std::cout << '\t' << foo.i << std::endl;)
  )
)

