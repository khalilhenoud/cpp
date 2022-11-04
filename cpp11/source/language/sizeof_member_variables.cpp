/**
 * @file sizeof_member_variables.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"
#include "utilities\classes\carray.h"

#include <iostream>


REFERENCES("https://en.wikipedia.org/wiki/C%2B%2B11#Allow_sizeof_to_work_on_members_of_classes_without_an_explicit_object")

namespace {
struct simple_wrapper {
  struct example_type {};
  carray<int32_t, false> data;
};
}

TEST(
  sizeof_member_variables,
  "In C++03, the sizeof operator can be used on types and objects. But it cannot\n" 
  "be used on members of a class without an explicit object. C++11 allows this\n"
  "usage, this is also applicable to alignof",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
    IN(std::cout << '\t' << sizeof(simple_wrapper::data) << std::endl;)
    IN(std::cout << '\t' << alignof(simple_wrapper::example_type) << std::endl;)
    IN(std::cout << '\t' << alignof(simple_wrapper) << std::endl;)
  )
)