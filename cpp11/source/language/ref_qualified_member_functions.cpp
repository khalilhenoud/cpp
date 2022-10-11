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

#include <iostream>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#ref-qualified-member-functions\n")

//<<
namespace {
struct foo {
  int32_t get_value()& { return 1; }
  int32_t get_value() const& { return 2; }
  int32_t get_value()&& { return 3; }
  int32_t get_value() const&& { return 4; }
};
}
//>>

TEST(
  ref_qualified_member_functions,
  "Member functions can now be qualified depending on whether '*this' is an\n"
  "lvalue or rvalue reference.\n",
  SECTION(
    "basic example",
    std::cout << GIVEN[0] << std::endl;
    foo f;
    const foo cf;
    IN(std::cout << '\t' << f.get_value() << std::endl;)
    IN(std::cout << '\t' << cf.get_value() << std::endl;)
    IN(std::cout << '\t' << std::move(f).get_value() << std::endl;)
    IN(std::cout << '\t' << std::move(cf).get_value() << std::endl;)
    IN(std::cout << '\t' << foo().get_value() << std::endl;)
  )
)

