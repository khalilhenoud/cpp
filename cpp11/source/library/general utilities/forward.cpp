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

#include <type_traits>


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#stdforward
https://github.com/AnthonyCalandra/modern-cpp-features#forwarding-references
https://stackoverflow.com/questions/25245453/what-is-a-nondeduced-context
https://en.cppreference.com/w/cpp/language/template_argument_deduction
)--"
)

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
R"--(
Returns the arguments passed to it while maintaining their value category and
cv-qualifiers. Useful for generic code and factories. Used in conjunction with 
forwarding references, @see [2].
)--",
  SECTION(
    "examples",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(carray<int, true> data{5, 1};))
    IN_DESC(PROTECT(non_std::wrapper(carray<int, true>{5, 6});), "moved")
    IN_DESC(PROTECT(wrapper(carray<int, true>{5, 6});), "moved")
    IN_DESC(auto tmp = non_std::wrapper(data);, "copied")
    IN_DESC(wrapper(std::move(data));, "moved")
  )
)
