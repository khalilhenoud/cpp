/**
 * @file variadic_templates.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <numeric>
#include <vector>
#include <type_traits>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#variadic-templates")

namespace {
template<typename... T>
struct arity {
  constexpr static int value = sizeof...(T);
};
}

namespace {
template<typename First, typename... Args>
auto sum(First first, Args... args) -> decltype(first)
{
  const auto acc = { first, args... };
  return std::accumulate(acc.begin(), acc.end(), static_cast<First>(0));
}
}

TEST(
  variadic_templates_basics,
R"--(
The ... syntax creates a parameter pack or expands one. A template parameter
pack is a template parameter that accepts zero or more template arguments
(non-types, types, or templates). A template with at least one parameter pack is
called a variadic template.
)--",
  SECTION(
    "Use 'sizeof...(pack)' to query the number of elements in a parameter pack.",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(print_safe("\t%i\n", arity<>::value);)
    IN(print_safe("\t%i\n", PROTECT(arity<char, int, float, double>)::value);)
  )
  SECTION(
    "Write a variadic summation function with a deduced return type",
    print_safe("%s\n", GIVEN[1].c_str());
    IN(print_safe("\t%i\n", sum(1, 2, 3));)
    IN(print_safe("\t%f\n", sum(1.9, 2.9, 3.9));)
    IN(print_safe("\t%f\n", sum(1.2f, 2.f, 54.f));)
    IN_ERROR(print_safe("\t%f\n", sum(1.2f, 2, 54.f));, "error: all elements in an initializer list must be same type.")
  )
)

