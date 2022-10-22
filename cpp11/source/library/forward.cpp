/**
 * @file forward.cpp
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
#include "utilities\classes\carray.h"

#include <iostream>
#include <type_traits>


REFERENCES(
  "[1] https://github.com/AnthonyCalandra/modern-cpp-features#stdforward\n"
  "[2] https://github.com/AnthonyCalandra/modern-cpp-features#forwarding-references\n"
  "[3] https://stackoverflow.com/questions/25245453/what-is-a-nondeduced-context\n"
  "[4] https://en.cppreference.com/w/cpp/language/template_argument_deduction")

namespace {
namespace non_std {
// forward<>() requires the type to be explicitly specified, this is due to 
// nondeduced context, check refs [3, 4] for a full explanation.
template<typename T>
T&& forward(typename std::remove_reference<T>::type& arg)
{
  return static_cast<T&&>(arg);
}

template<typename T>
T wrapper(T&& arg) 
{
  return T{forward<T>(arg)};
}
}

template<typename T>
T wrapper(T&& arg) 
{
  return T{std::forward<T>(arg)};
}
}

TEST(
  std_forward,
  "Returns the arguments passed to it while maintaining their value category\n" 
  "and cv-qualifiers. Useful for generic code and factories. Used in conjunction\n" 
  "with forwarding references, @see [2]",
  SECTION(
    "examples",
    std::cout << GIVEN[0] << std::endl;
    IN(PROTECT(carray<int, true> data{5, 1};))
    IN_DESC(PROTECT(non_std::wrapper(carray<int, true>{5, 6});), "moved")
    IN_DESC(PROTECT(wrapper(carray<int, true>{5, 6});), "moved")
    IN_DESC(auto tmp = non_std::wrapper(data);, "copied")
    IN_DESC(wrapper(std::move(data));, "moved")
  )
)
