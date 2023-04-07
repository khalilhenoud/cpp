/**
 * @file ref.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-10-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <functional>
#include <vector>


REFERENCES(
R"--(
https://github.com/AnthonyCalandra/modern-cpp-features#stdref
https://en.cppreference.com/w/cpp/utility/functional/ref
)--"
)

TEST(
  std_ref,
R"--(
std::ref(val) is used to create object of type std::reference_wrapper that holds
reference of val. Used in cases when usual reference passing using '&' does not
compile or '&' is dropped due to type deduction. std::cref is similar but
created reference wrapper holds a const reference to val.
)--",
  SECTION(
    "example",
    IN(int32_t val = 99;)
    IN(std::reference_wrapper<int32_t> i_ref = std::ref(val);)
    IN(++i_ref;)
    print_safe("\n");
    IN(std::reference_wrapper<const int32_t> ci_ref = std::cref(val);)
    IN_ERROR(++ci_ref;, "error C3892: 'ci_ref': you cannot assign to a variable that is const!")
    print_safe("\n");
    IN_ERROR(std::vector<int32_t &> vec;, "compile error!")
    IN_DESC(std::vector<std::reference_wrapper<int32_t>> vec;, "use reference_wrapper instead")
    IN(vec.push_back(i_ref);)
    IN(++vec[0];)
    IN(print_safe("\t%i\n", val);)
    IN(print_safe("\t%i\n", vec[0].get());)
    IN(print_safe("\t%i\n", i_ref.get());)
    IN(print_safe("\t%i\n", ci_ref.get());)
  )
)