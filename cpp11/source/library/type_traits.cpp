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
#include <iostream>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#type-traits")

namespace {
static_assert(std::is_integral<int>::value);
}

TEST(
  type_traits,
  "Type traits defines a compile-time template-based interface to query or\n" 
  "modify the properties of types.",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
    IN(std::cout << std::is_integral<int>::value << std::endl;)
    IN(PROTECT(std::cout << std::is_same<int, int>::value << std::endl;))
    IN(PROTECT(std::cout << std::is_same<std::conditional<true, int, double>::type, int>::value << std::endl;))
    IN(PROTECT(std::cout << std::is_same<std::conditional<false, int, double>::type, int>::value << std::endl;))
  )
)