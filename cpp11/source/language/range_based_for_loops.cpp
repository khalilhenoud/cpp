/**
 * @file range_based_for_loops.cpp
 * @author khalilhenoud@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-09-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utilities\shared.h"
#include "utilities\registrar.h"

#include <array>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#range-based-for-loops")

namespace {
void print_container(std::array<int32_t, 5>& container)
{
  print_safe("\t");
  for (auto& elem : container)
    print_safe("%i ", elem);
  print_safe("\n");
}
}

TEST(
  range_based_for_loops,
  "Syntactic sugar for iterating over a container's elements.",
  SECTION(
    "basic example",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(std::array<int32_t, 5> intarray = {1, 2, 3, 4, 5};))
    IN(for (int32_t& i : intarray) i *= 2;)
    IN(print_container(intarray);)
  )
  SECTION(
    "Note the difference when using int32_t as opposed to int32_t&:",
    print_safe("%s\n", GIVEN[0].c_str());
    IN(PROTECT(std::array<int32_t, 5> intarray = {1, 2, 3, 4, 5};))
    IN(for (int32_t i : intarray) i *= 2;)
    IN(print_container(intarray);)
  )
)

