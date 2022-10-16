/**
 * @file trailing_return_types.cpp
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


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#trailing-return-types")

namespace {
auto return_float() -> float 
{
  return 1.5f;
}

auto&& one = []() -> int { return 1; };
}

namespace {
// NOTE: This does not compile!
// template <typename T, typename U>
// decltype(a + b) add(T a, U b) {
//     return a + b;
// }

template<typename T, typename L>
auto add(T a, L b) -> decltype(a + b)
{
  return a + b;
}
}

TEST(
  trailing_return_types,
  "C++11 allows functions and lambdas an alternative syntax for specifying their\n" 
  "return types.",
  SECTION(
    "basic examples",
    std::cout << GIVEN[0] << std::endl;
    IN(std::cout << '\t' << return_float() << std::endl;)
    IN(std::cout << '\t' << one() << std::endl;)
  )
  SECTION(
    "This feature is especially useful when certain return types cannot be\n" 
    "resolved:",
    std::cout << GIVEN[1] << std::endl;
    IN(std::cout << '\t' << add(1, 2.4f) << std::endl;)
  )
)

