/**
 * @file deleted_functions.cpp
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

#include <iostream>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#deleted-functions\n")

//<<
namespace {
struct A {
  A(int32_t val) : i{ val } {}
  A(const A&) = delete;
  A& operator=(const A&) = delete;

  int32_t i = 0;
};
}
//>>

TEST(
  deleted_functions,
  "A more elegant, efficient way to provide a deleted implementation of a\n"
  "function. Useful for preventing copies on objects.\n",
  SECTION(
    "basics",
    std::cout << GIVEN[0] << std::endl;
    IN(A a(100);)
    IN(A b(200);)
    IN_ERROR(A c = a;, "error C2280: 'A::A(const A &)': attempting to reference a deleted function")
    IN_ERROR(a = b;, "error C2280: 'A &A::operator =(const A &)': attempting to reference a deleted function")
  )
)

