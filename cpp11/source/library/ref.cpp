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
#include <iostream>
#include <vector>


REFERENCES(
  "https://github.com/AnthonyCalandra/modern-cpp-features#stdref\n"
  "https://en.cppreference.com/w/cpp/utility/functional/ref")

TEST(
  std_ref,
  "std::ref(val) is used to create object of type std::reference_wrapper that\n" 
  "holds reference of val. Used in cases when usual reference passing using '&'\n" 
  "does not compile or '&' is dropped due to type deduction. std::cref is\n" 
  "similar but created reference wrapper holds a const reference to val.",
  SECTION(
    "example",
    IN(int32_t val = 99;)
    IN(std::reference_wrapper<int32_t> i_ref = std::ref(val);)
    IN(++i_ref;)
    std::cout << std::endl;
    IN(std::reference_wrapper<const int32_t> ci_ref = std::cref(val);)
    IN_ERROR(++ci_ref;, "error C3892: 'ci_ref': you cannot assign to a variable that is const!")
    std::cout << std::endl;
    IN_ERROR(std::vector<int32_t &> vec;, "compile error!")
    IN_DESC(std::vector<std::reference_wrapper<int32_t>> vec;, "use reference_wrapper instead")
    IN(vec.push_back(i_ref);)
    IN(++vec[0];)
    IN(std::cout << '\t' << val << std::endl;)
    IN(std::cout << '\t' << vec[0] << std::endl;)
    IN(std::cout << '\t' << i_ref << std::endl;)
    IN(std::cout << '\t' << ci_ref << std::endl;)
  )
)