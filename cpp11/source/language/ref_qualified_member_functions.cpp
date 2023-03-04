/**
 * @file ref_qualified_member_functions.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#ref-qualified-member-functions")

namespace {
struct foo {
  int32_t get_value()& { return 1; }
  int32_t get_value() const& { return 2; }
  int32_t get_value()&& { return 3; }
  int32_t get_value() const&& { return 4; }
};
}

TEST(
  ref_qualified_member_functions,
R"--(
Member functions can now be qualified depending on whether '*this' is an lvalue
or rvalue reference.
)--",
  SECTION(
    "basic example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(foo f;)
    IN(const foo cf;)
    IN(print_safe("%i\n", f.get_value());)
    IN(print_safe("%i\n", cf.get_value());)
    IN(print_safe("%i\n", std::move(f).get_value());)
    IN(print_safe("%i\n", std::move(cf).get_value());)
    IN(print_safe("%i\n", foo().get_value());)
  )
)

