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


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#delegating-constructors")

namespace {
struct Foo {
  int32_t i = -1;
  Foo(int32_t val) : i{ val } {}
  Foo() : Foo(0) {}
};
}

TEST(
  delegating_constructors,
R"--(
Constructors can now call other constructors in the same class using an
initializer list.
)--",
  SECTION(
    "example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(Foo foo;)
    IN(print_safe("\t%i\n", foo.i);)
  )
)

