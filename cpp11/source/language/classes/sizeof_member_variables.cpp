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


REFERENCES("https://en.wikipedia.org/wiki/C%2B%2B11#Allow_sizeof_to_work_on_members_of_classes_without_an_explicit_object")

namespace {
struct simple_wrapper {
  struct example_type {};
  carray<int32_t, false> data;
};
}

TEST(
  sizeof_member_variables,
R"--(
In C++03, the sizeof operator can be used on types and objects. But it cannot be
used on members of a class without an explicit object. C++11 allows this usage,
this is also applicable to alignof.
)--",
  SECTION(
    "example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(print_safe("%llu\n", sizeof(simple_wrapper::data));)
    IN(print_safe("%llu\n", alignof(simple_wrapper::example_type));)
    IN(print_safe("%llu\n", alignof(simple_wrapper));)
  )
)