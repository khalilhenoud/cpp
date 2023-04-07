/**
 * @file tuple.cpp
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

#include <tuple>


REFERENCES("https://github.com/AnthonyCalandra/modern-cpp-features#tuples")

TEST(
  tuples,
R"--(
Tuples are a fixed-size collection of heterogeneous values. Access the elements
of a std::tuple by unpacking using std::tie, or using std::get.
)--",
  SECTION(
    "example",
    IN(PROTECT(std::tuple<int32_t, const char*, const char*> playerProfile = std::make_tuple(51, "Tom Henderson", "NYC");))
    IN(print_safe("\tage: %i\n", std::get<0>(playerProfile));)
    IN(print_safe("\tname: %s\n", std::get<1>(playerProfile));)
    IN(print_safe("\tlocation: %s\n", std::get<2>(playerProfile));)
  )
)

