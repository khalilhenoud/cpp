/**
 * @file begin_end.cpp
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

#include <iostream>
#include <vector>
#include <algorithm>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#stdbeginend")

namespace {
template<typename T>
int32_t count_twos(const T& container)
{
  return std::count_if(std::begin(container), std::end(container), [](int32_t entry) {
    return entry == 2;
  });
}
}

TEST(
  std_begin_end,
  "std::begin and std::end free functions were added to return begin and end\n" 
  "iterators of a container generically. These functions also work with raw\n" 
  "arrays which do not have begin and end member functions.",
  SECTION(
    "example",
    std::cout << GIVEN[0] << std::endl;
    IN(PROTECT(std::vector<int32_t> vec = {1, 2, 4, 2, 43, 122, 325, 2};))
    IN(PROTECT(int32_t arr[] = {120, 11, 2, 424, 111, 22, 1, 2, 5};))
    IN(std::cout << '\t' << count_twos(vec) << std::endl;)
    IN(std::cout << '\t' << count_twos(arr) << std::endl;)
  )
)