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


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#trailing-return-types")

namespace {
auto return_float() -> float 
{
  return 1.5f;
}

auto&& one = []() -> int { return 1; };
}

namespace {
// NOTE: This does not compile! a and b in decltype are not defined yet.
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
R"--(
C++11 allows functions and lambdas an alternative syntax for specifying their
return types.
)--",
  SECTION(
    "basic examples",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(print_safe("\t%f\n", return_float());)
    IN(print_safe("\t%i\n", one());)
  )
  SECTION(
R"--(
This feature is especially useful when certain return types cannot be resolved:
)--",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(print_safe("\t%f\n", add(1, 2.4f));)
  )
)

