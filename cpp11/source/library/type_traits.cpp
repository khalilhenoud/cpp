/**
 * @file type_traits.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <type_traits>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#type-traits")

namespace {
static_assert(std::is_integral<int>::value);
}

TEST(
  type_traits,
R"--(
Type traits defines a compile-time template-based interface to query or modify
the properties of types.
)--",
  SECTION(
    "example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(print_safe("%i\n", std::is_integral<int>::value);)
    IN(PROTECT(print_safe("%i\n", std::is_same<int, int>::value);))
    IN(PROTECT(print_safe("%i\n", std::is_same<std::conditional<true, int, double>::type, int>::value);))
    IN(PROTECT(print_safe("%i\n", std::is_same<std::conditional<false, int, double>::type, int>::value);))
  )
)