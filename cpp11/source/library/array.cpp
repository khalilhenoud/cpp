/**
 * @file array.cpp
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
#include <algorithm>
#include <array>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#stdarray")

TEST(
  array,
  "std::array is a container built on top of a C-style array. Supports common\n"
  "container operations such as sorting.",
  SECTION(
    "example",
    IN(PROTECT(std::array<int32_t, 3> a = {2, 1, 3};))
    IN(std::sort(std::begin(a), std::end(a));)
    IN(std::cout << a[0] << ", " << a[1] << ", " << a[2] << std::endl;)
    IN(for(auto& val : a) val *=2;)
    IN(std::cout << a[0] << ", " << a[1] << ", " << a[2] << std::endl;)
  )
)