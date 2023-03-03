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


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#explicit-conversion-functions")

namespace {
struct A {
  operator bool() const { return false; }
};

struct B {
  explicit operator bool() const { return true; }
};
}

TEST(
  explicit_conversion_functions,
  "Conversion functions can now be made explicit using the explicit specifier.",
  SECTION(
    "basic_example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(A a;)
    IN(bool ba = a;)
    IN(print_safe("\t%i\n", ba);)
    IN(B b;)
    IN_ERROR(bool bb = b;, "error C2440: 'initializing': cannot convert from 'B' to 'bool'")
    IN_DESC(bool bb = (bool)b;, "has to be explicit!")
  )
)