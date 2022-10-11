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

#include <iostream>
#include <numeric>
#include <vector>
#include <type_traits>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#variadic-templates\n")

//<<
template<typename... T>
struct arity {
  constexpr static int value = sizeof...(T);
};
//>>

//<<
template<typename First, typename... Args>
auto sum(First first, Args... args) -> decltype(first)
{
  const auto acc = { first, args... };
  return std::accumulate(acc.begin(), acc.end(), static_cast<First>(0));
}
//>>

TEST(
  variadic_templates_basics,
  "The ... syntax creates a parameter pack or expands one. A template parameter\n"
  "pack is a template parameter that accepts zero or more template arguments\n"
  "(non-types, types, or templates). A template with at least one parameter\n"
  "pack is called a variadic template.\n",
  SECTION(
    "Use 'sizeof...(pack)' to query the number of elements in a parameter pack.",
    std::cout << GIVEN[0] << std::endl;
    IN(std::cout << arity<>::value << std::endl;)
    IN(std::cout << PROTECT(arity<char, int, float, double>)::value << std::endl;)
  )
  SECTION(
    "Write a variadic summation function with a deduced return type",
    std::cout << GIVEN[1] << std::endl;
    IN(std::cout << sum(1, 2, 3) << std::endl;)
    IN(std::cout << sum(1.9, 2.9, 3.9) << std::endl;)
    IN(std::cout << sum(1.2f, 2.f, 54.f) << std::endl;)
    IN_ERROR(std::cout << sum(1.2f, 2, 54.f) << std::endl;, "error: all elements in an initializer list must be same type.")
  )
)

