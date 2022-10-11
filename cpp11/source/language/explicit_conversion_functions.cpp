/**
 * @file explicit_conversion_functions.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <iostream>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#explicit-conversion-functions\n")

//<<
namespace {
struct A {
  operator bool() const { return false; }
};

struct B {
  explicit operator bool() const { return true; }
};
}
//>>

TEST(
  explicit_conversion_functions,
  "Conversion functions can now be made explicit using the explicit specifier.\n",
  SECTION(
    "basic_example",
    std::cout << GIVEN[0] << std::endl;
    IN(A a;)
    IN(bool ba = a;)
    IN(std::cout << '\t' << ba << std::endl;)
    IN(B b;)
    IN_ERROR(bool bb = b;, "error C2440: 'initializing': cannot convert from 'B' to 'bool'")
    IN_DESC(bool bb = (bool)b;, "has to be explicit!")
  )
)