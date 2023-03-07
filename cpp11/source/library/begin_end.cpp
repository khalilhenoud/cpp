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
R"--(
std::begin and std::end free functions were added to return begin and end
iterators of a container generically. These functions also work with raw arrays
which do not have begin and end member functions.
)--",
  SECTION(
    "example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(std::vector<int32_t> vec = {1, 2, 4, 2, 43, 122, 325, 2};))
    IN(PROTECT(int32_t arr[] = {120, 11, 2, 424, 111, 22, 1, 2, 5};))
    IN(print_safe("\t%i\n", count_twos(vec));)
    IN(print_safe("\t%i\n", count_twos(arr));)
  )
)